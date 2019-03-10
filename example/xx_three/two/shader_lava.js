
var vertex_shader = `$input a_position, a_texcoord0
    $output v_position, v_uv0
    
    #include <common.sh>
    
    void main()
    {
        var material_index = int(u_state_material);
        Basevar basic = read_base_material(material_index);
        
        v_uv0 = vec4((a_texcoord0 * basic.uv0_scale) + basic.uv0_offset, 0.0, 0.0);
        vec4 view = mul(u_modelView, vec4(a_position, 1.0));
        v_position = mul(u_proj, view);
        gl_Position = v_position;
    }`;

var fragment_shader = `$input v_position, v_uv0
    
    #include <common.sh>
    #include <pbr/fog.sh>
    
    void main()
    {
        vec2 uv = v_uv0;
        vec2 position = - 1.0 + 2.0 * uv;
    
        vec4 noise = texture2D(s_user0, uv);
        vec2 T1 = uv + vec2(1.5, - 1.5) * u_time * 0.02;
        vec2 T2 = uv + vec2(- 0.5, 2.0) * u_time * 0.01;
    
        T1.x += noise.x * 2.0;
        T1.y += noise.y * 2.0;
        T2.x -= noise.y * 0.2;
        T2.y += noise.z * 0.2;
    
        float p = texture2D(s_user0, T1 * 2.0).a;
    
        vec4 lava = texture2D(s_user1, T2 * 2.0);
        vec4 color = lava * (vec4(p, p, p, p) * 2.0) + (lava * lava - 0.1);
    
        if(color.r > 1.0) { color.bg += clamp(color.r - 2.0, 0.0, 100.0); }
        if(color.g > 1.0) { color.rb += color.g - 1.0; }
        if(color.b > 1.0) { color.rg += color.b - 1.0; }
    
        gl_FragColor = color;
    
    #if BGFX_SHADER_LANGUAGE_HLSL
    //	float depth = v_position.z;
        float depth = gl_FragCoord.z * gl_FragCoord.w;
    #else
    //	float depth = (v_position.z + v_position.w) * 0.5;
        float depth = gl_FragCoord.z / gl_FragCoord.w;
    #endif
        const float LOG2 = 1.442695;
        float fogFactor = exp2(-u_fog_density * u_fog_density * depth * depth * LOG2);
        fogFactor = 1.0 - clamp(fogFactor, 0.0, 1.0);
    
        gl_FragColor = mix(color, vec4(vec3(0.0, 0.0, 0.0), color.w), fogFactor);
    }`;

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

if(typeof this.state == 'undefined') {
    this.state = 1;
    
    var camera = viewer.camera;
    camera.fov = 35.0; camera.near = 1.0; camera.far = 3000.0;
    camera.eye.z = 4.0;

    var fog_density = 0.45;
    var fog_color = new two.Colour(0.0);

    scene.env.fog.density = fog_density;
    scene.env.fog.colour = fog_color;

    var program = app.gfx.programs.create('lava'); //new two.Program('lava');
    program.set_block(two.MaterialBlock.Solid);
    program.set_block(two.MaterialBlock.User);
    program.set_source(two.ShaderType.Vertex, vertex_shader);
    program.set_source(two.ShaderType.Fragment, fragment_shader);
        
    var cloud = app.gfx.textures.file('lava/cloud.png');
    var lava = app.gfx.textures.file('lava/lavatile.jpg');

    var material = app.gfx.materials.create('lava');
    var m = material;
    m.program = program;
    m.base.uv0_scale = new two.vec2(3.0, 1.0);
    m.user.attr0.texture = cloud;
    m.user.attr1.texture = lava;
    
    // material.submit = submit;

    this.angles = new two.vec3(0.3, 0.0, 0.0);

    var size = 0.65;

    this.model = app.gfx.shape(new two.Torus(size, 0.3));

    this.node = scene.nodes().add(new two.Node3(new two.vec3(0.0), new two.quat(angles)));
    var it = scene.items().add(new two.Item(node, model, 0, material));

    //var renderModel = new THREE.RenderPass(scene, camera);
    //var effectBloom = new THREE.BloomPass(1.25);
    //var effectFilm = new THREE.FilmPass(0.35, 0.95, 2048, false);
    //effectFilm.renderToScreen = true;

    //composer = new THREE.EffectComposer(renderer);
    //
    //composer.addPass(renderModel);
    //composer.addPass(effectBloom);
    //composer.addPass(effectFilm);
}

var delta = 5.0 * app.gfx.frame_time;

//uniforms['time'].value += 0.2 * delta;

this.angles.y += 0.0125 * delta;
this.angles.x += 0.05 * delta;

this.node.apply(new two.vec3(0.0), new two.quat(this.angles));

//renderer.clear();
//composer.render(0.01);
