// material_translucent.js

// @author daoshengmu / http://dsmu.me/

var translucent_fragment = `$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal

    #include <encode.sh>
    #include <pbr/pbr.sh>
    #include <pbr/light.sh>
    #include <pbr/light_brdf_three.sh>
    #include <pbr/radiance.sh>

    #define s_thickness s_user0

    struct TranslucentMaterial
	{
		PhongMaterial phong;
		UserMaterial scatter;
	};

	void direct_scatter(vec3 energy, vec3 l, Fragment fragment, TranslucentMaterial mat, inout vec3 diffuse, inout vec3 specular)
	{
		direct_blinn_phong(energy, l, fragment, mat.phong, diffuse, specular);

		float power       = mat.scatter.p0.x;
		float scale       = mat.scatter.p0.y;
		float distortion  = mat.scatter.p0.z;
		float ambient     = mat.scatter.p0.w;
		float attenuation = mat.scatter.p1.x;
		vec3  color       = mat.scatter.p1.yzw;

		vec3 thickness = color * texture2D(s_thickness, fragment.uv).r;
		vec3 scatteringHalf = normalize(l + (fragment.normal * distortion));
		float scatteringDot = pow(saturate(dot(fragment.view, -scatteringHalf)), power) * scale;
		vec3 scatteringIllu = (scatteringDot + ambient) * thickness;
	
		diffuse += scatteringIllu * attenuation * energy;
	}

    #define direct_brdf direct_scatter

    void main()
    {
    #include <pbr/fs_fragment.sh>
    
    #include <pbr/fs_phong_material.sh>
		TranslucentMaterial material;
		material.phong = matphong;
		material.scatter = matuser;
    
    #include <pbr/fs_phong.sh>
    #include <pbr/fs_out_pbr.sh>
    gl_FragColor = LinearToGamma(gl_FragColor, 2.0);
    //gl_FragColor = vec4(texture2D(s_thickness, fragment.uv).rgb, 1.0);
    }`;

var translucent_vertex = `#include <geometry_vs.sc>`;

var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controls(viewer);

var scene = viewer.scene;

if(init) {
    this.importerOBJ = new two.ImporterOBJ(app.gfx);

    var camera = viewer.camera;
    camera.fov = 40.0; camera.near = 1.0; camera.far = 5000.0;
    camera.eye = new two.vec3(0.0, 300.0 * 0.75, 400.0 * 4.0 * 0.75);

    //Tonemap tonemap = viewer.viewport.comp<Tonemap>();
    //tonemap.enabled = true;

    // Lights

    scene.env.radiance.ambient = two.rgb(0x888888);

    var dir = two.look_dir(new two.vec3(0.0, -0.5, -0.5));
    var dn = scene.nodes().add(new two.Node3(new two.vec3(0.0), dir));
    var dl = scene.lights().add(new two.Light(dn, two.LightType.Direct, false, two.rgb(0xffffff), 0.03));

    var zeroq = new two.quat(new two.vec3(0.0));
    
    var sphere = app.gfx.shape(new two.Sphere(4.0));
    
    var pn0 = scene.nodes().add(new two.Node3(new two.vec3(0.0, -50.0, 350.0), zeroq));
    var pl0 = scene.lights().add(new two.Light(pn0, two.LightType.Point, false, two.rgb(0x888888), 7.0, 300.0));
    scene.items().add(new two.Item(pn0, sphere, 0, two.gfx.solid_material(app.gfx, 'l0', two.rgb(0x888888))));

    var pn1 = scene.nodes().add(new two.Node3(new two.vec3(-100.0, 20.0, -260.0), zeroq));
    var pl1 = scene.lights().add(new two.Light(pn1, two.LightType.Point, false, two.rgb(0x888800), 1.0, 500.0));
    scene.items().add(new two.Item(pn1, sphere, 0, two.gfx.solid_material(app.gfx, 'l1', two.rgb(0x888800))));

    var white = app.gfx.textures.file('white.jpg');
    var texture = app.gfx.textures.file('bunny_thickness.jpg');

    this.phong = { diffuse: new two.Colour(1.0, 0.2, 0.2), shininess: 500.0 };
    // specular = two.rgb(0xffffff);
    // emissive = two.rgb(0x000000);
    // opacity = 1.0;

    this.thickness = { texture: texture, color: new two.Colour(0.5, 0.3, 0.0), distortion: 0.1, ambient: 0.4, 
                       attenuation: 0.8, power: 2.0, scale: 16.0 };

    var pbr = app.gfx.programs.fetch('pbr/pbr');

    var program = app.gfx.programs.create('translucent');
        program.set_block(two.MaterialBlock.Lit);
        program.set_block(two.MaterialBlock.Phong);
        program.set_block(two.MaterialBlock.User);
        program.set_source(two.ShaderType.Vertex, translucent_vertex);
        program.set_source(two.ShaderType.Fragment, translucent_fragment);
        program.register_blocks(pbr);

    var material = app.gfx.materials.create('translucent'); var m = material;
        m.program = program;
        m.phong.diffuse.value = new two.Colour(1.0, 0.2, 0.2);
        m.phong.shininess.value = 500.0;
        m.user.tex0 = thickness.texture;
        m.user.attr0 = new two.vec4(thickness.power, thickness.scale, thickness.distortion, thickness.ambient);
        m.user.attr1 = new two.vec4(thickness.attenuation, thickness.color.r, thickness.color.g, thickness.color.b);


    var bunny = app.gfx.models.file('bunny');

    var n = scene.nodes().add(new two.Node3(new two.vec3(0.0, 0.0, 10.0), zeroq));
    var it = scene.items().add(new two.Item(n, bunny, 0, material));
    this.node = n;
}

//if(Widget* dock = two.ui.dockitem(dockbar, 'Game', { 1U }))
//{
//    var sheet = two.ui.sheet(*dock);
//
//    auto panel = [](const string name) . Widget
//    {
//        var s = two.ui.expandbox(sheet, name.c_str());
//        return two.ui.columns(s, { 0.3, 0.7f });
//    };
//
//    var a = panel('Thickness Control');
//
//    two.ui.slider_field_float(a, 'distortion', { thickness.distortion,  { 0.01, 1.0, 0.01 } });
//    two.ui.slider_field_float(a, 'ambient', { thickness.ambient,     { 0.01, 5.f, 0.05 } });
//    two.ui.slider_field_float(a, 'attenuation', { thickness.attenuation, { 0.01, 5.f, 0.05 } });
//    two.ui.slider_field_float(a, 'power', { thickness.power,       { 0.01, 16.f, 0.1 } });
//    two.ui.slider_field_float(a, 'scale', { thickness.scale,       { 0.01, 50.0, 0.1 } });
//}

//var y = app.gfx.time / 5.0;
var y = time / 5.0;
this.node.apply(new two.vec3(0.0, 0.0, 10.0), new two.quat(new two.vec3(0.0, y, 0.0)));
