// perf_twosided.js

var simple_vertex = `$input a_position, a_normal
    $output v_view, v_normal

    #include <common.sh>

    void main()
    {
        v_view = mul(u_modelView, vec4(a_position.xyz, 1.0)).xyz;

        v_normal = normalize(mul(u_modelView, vec4(a_normal, 0.0)).xyz);
        
        gl_Position = mul(u_proj, vec4(v_view, 1.0));
    }`;

var simple_fragment = `$input v_view, v_normal

    #include <encode.sh>
    #include <pbr/pbr.sh>
    #include <pbr/light.sh>
    #define BRDF_BLINN_PHONG
    #include <pbr/light_brdf_three.sh>
    #include <pbr/radiance.sh>
    #include <fog.sh>

    void main()
    {
        Fragment fragment;
        fragment.coord = gl_FragCoord;
        fragment.position = v_view.xyz;
        fragment.view = normalize(-v_view.xyz);
        fragment.normal = normalize(v_normal);
    #ifdef DOUBLE_SIDED
        fragment.normal = fragment.normal * (float(gl_FrontFacing) * 2.0 - 1.0);
    #endif

    #include <pbr/fs_phong_material.sh>
        PhongMaterial material = matphong;
        
        int zone_index = int(u_state_zone);
        Zone zone = read_zone(zone_index);
        
        vec3 diffuse = vec3_splat(0.0);
        vec3 specular = vec3_splat(0.0);

    #include <pbr/fs_indirect.sh>
        diffuse += zone.ambient * PI;
        diffuse *= BRDF_Diffuse_Lambert(matphong.diffuse);

        int i = 0;

#ifdef SHADOWS
        float direct_shadows[4];
        float point_shadows[MAX_LIGHTS];
        float spot_shadows[MAX_LIGHTS];

        //#ifdef CSM_SHADOW
        for(i = 0; i < int(u_shadow_counts[LIGHT_DIRECT]); i++)
        {
            CSMShadow shadow = read_csm_shadow(int(u_light_indices[i][LIGHT_DIRECT]));
            direct_shadows[i] = shadow_csm(shadow, fragment.position, fragment.depth);
        }
        //#endif

        for(i = 0; i < int(u_shadow_counts[LIGHT_POINT]); i++)
        {
            Shadow shadow = read_shadow(int(u_light_indices[i][LIGHT_POINT]));
            point_shadows[i] = shadow_point(shadow, fragment.position);
        }

        for(i = 0; i < int(u_shadow_counts[LIGHT_SPOT]); i++)
        {
            Shadow shadow = read_shadow(int(u_light_indices[i][LIGHT_SPOT]));
            spot_shadows[i] = shadow_spot(shadow, fragment.position);
        }
#endif

        for(i = 0; i < int(u_light_counts[LIGHT_DIRECT]); i++)
        {
            Light direct = read_light(int(u_light_indices[i][LIGHT_DIRECT]));
#ifdef SHADOWS
            float factor = (i < int(u_shadow_counts[LIGHT_DIRECT]) ? direct_shadows[i] : 1.0);
#else
            float factor = 1.0;
#endif
            direct_brdf(direct.energy * factor, -direct.direction, fragment, material, diffuse, specular);
        }

        for(i = 0; i < int(u_light_counts[LIGHT_POINT]); i++)
        {
            Light light = read_light(int(u_light_indices[i][LIGHT_POINT]));
            vec3 l = light.position - fragment.position;
#ifdef SHADOWS
            float a = omni_attenuation(l, light) * (i < int(u_shadow_counts[LIGHT_POINT]) ? point_shadows[i] : 1.0);
#else
            float a = omni_attenuation(l, light);
#endif
            direct_brdf(light.energy * a, normalize(l), fragment, material, diffuse, specular);
        }

        for(i = 0; i < int(u_light_counts[LIGHT_SPOT]); i++)
        {
            Light light = read_light(int(u_light_indices[i][LIGHT_SPOT]));
            vec3 l = light.position - fragment.position;
#ifdef SHADOWS
            float a = spot_attenuation(l, light) * (i < int(u_shadow_counts[LIGHT_SPOT]) ? spot_shadows[i] : 1.0);
#else
            float a = spot_attenuation(l, light);
#endif
            direct_brdf(light.energy * a, normalize(l), fragment, material, diffuse, specular);
        }

    #include <pbr/fs_phong_ibl.sh>
    #include <pbr/fs_out_pbr.sh>
    #include <fs_fog_simple.sh>
    }`

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controller(viewer);

var camera = viewer.camera;
var scene = viewer.scene;

if (init) {
    this.mouse = new two.vec2(0.0);
    
    camera.fov = 50.0; camera.near = 1.0; camera.far = 20000.0;
    camera.eye.z = 3200.0;

    viewer.viewport.to_gamma = true;

    viewer.viewport.clear_colour = two.to_linear(two.rgb(0x050505));

    var reflection = app.gfx.textures.file('cube/royal.jpg.cube');
    reflection.reload(app.gfx, false, true);

    var env = scene.env;
    env.radiance.texture = reflection;
    env.radiance.filter = false;
    env.radiance.colour = two.rgb(0x050505);

    var zeroq = new two.quat(new two.vec3(0.0));
    
    var l0 = scene.nodes().add(new two.Node3(new two.vec3(4000.0, 0.0, 0.0), zeroq));
    scene.lights().add(new two.Light(l0, two.LightType.Point, false, two.rgb(0x0011ff), 1.0, 5500.0));

    var l1 = scene.nodes().add(new two.Node3(new two.vec3(-4000.0, 0.0, 0.0), zeroq));
    scene.lights().add(new two.Light(l1, two.LightType.Point, false, two.rgb(0xff1100), 1.0, 5500.0));

    var l2 = scene.nodes().add(new two.Node3(new two.vec3(0.0), zeroq));
    scene.lights().add(new two.Light(l2, two.LightType.Point, false, two.rgb(0xffaa00), 2.0, 3000.0));

    var phong = app.gfx.programs.file('pbr/phong');

    var program = app.gfx.programs.fetch('custom');
    program.set_block(two.MaterialBlock.Alpha);
    program.set_block(two.MaterialBlock.Lit);
    program.set_block(two.MaterialBlock.Phong);
    program.set_source(two.ShaderType.Vertex, simple_vertex);
    program.set_source(two.ShaderType.Fragment, simple_fragment);
    program.register_blocks(phong);
    
    var material = app.gfx.materials.create('twosided'); var m = material;
        m.program = program;
        m.base.cull_mode = two.CullMode.None;
        m.phong.specular.value = two.rgb(0x101010);
        m.phong.shininess.value = 100.0;
        m.phong.reflectivity.value = 0.1;
        m.phong.env_blend = two.PhongEnvBlendMode.Mix;
    
    
    var symbol = new two.Symbol(new two.Colour(1.0)); symbol.subdiv = new two.uvec2(32, 16);
    var geometry = app.gfx.shape(new two.Sphere(1.0, 0.0, Math.PI), symbol);

    for(var i = 0; i < 5000; ++i)
    {
        var p = new two.vec3(Math.random() * 10000.0 - 5000.0, Math.random() * 10000.0 - 5000.0, Math.random() * 10000.0 - 5000.0);
        var a = new two.vec3(Math.random() * 2 * Math.PI, Math.random() * 2 * Math.PI, 0.0);
        var s = new two.vec3(Math.random() * 50.0 + 100.0);

        var n = scene.nodes().add(new two.Node3(p, new two.quat(a), s));
        //scene.items().add(new two.Item(n, geometry, 0, material));
        scene.items().add(new two.Item(n, geometry, 7937, material));
    }
}

var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved);
if(event.valid())
{
    this.mouse.x = (event.relative.x - viewer.frame.size.x / 2.0) * 10.0;
    this.mouse.y = (event.relative.y - viewer.frame.size.y / 2.0) * 10.0;
}

var camera = viewer.camera;
camera.eye.x += (this.mouse.x - camera.eye.x) * .05;
camera.eye.y += (-this.mouse.y - camera.eye.y) * .05;
