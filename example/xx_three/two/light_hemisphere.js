// light_hemisphere.js

var skydome_vertex = `$input a_position, a_texcoord0
    $output v_world
    
    #include <common.sh>
    
    void main()
    {
        vec4 world = mul(u_model[0], vec4(a_position.xyz, 1.0));
        v_world = world.xyz;
        gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;

var skydome_fragment = `$input v_world

    #include <common.sh>

    #define u_top_color u_user_p0.xyz
    #define u_bottom_color u_user_p1.xyz
    #define u_offset u_user_p2.x
    #define u_exponent u_user_p2.y

    void main()
    {
        float h = normalize(v_world + u_offset).y;
        gl_FragColor = vec4(mix(u_bottom_color, u_top_color, max(pow(max(h, 0.0), u_exponent), 0.0)), 1.0);
    }`;

var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controls(viewer);

var scene = viewer.scene;

if(init) {
    this.importerGltf = new two.ImporterGltf(app.gfx);
    
    var camera = viewer.camera;
    camera.fov = 30.0; camera.near = 1.0; camera.far = 5000.0;
    camera.eye = new two.vec3(0.0, 0.0, 250.0);

    viewer.viewport.clear_colour = two.hsl(0.6, 0.0, 1.0);
    scene.env.background.colour = two.hsl(0.6, 0.0, 1.0);
    scene.env.radiance.ambient = 0.0;

    //scene.fog = new THREE.Fog( scene.background, 1, 5000 );

    // LIGHTS

    var skylight = two.hsl(0.6, 1.0, 0.6);
    skylight = new two.Colour(skylight.r, skylight.g, skylight.b);
    
    //scene.env.skylight = new two.Skylight(true, 0.6, new two.vec3(0.0, 50.0, 0.0), new two.vec3(0.0), skylight, two.hsl(0.095, 1.0, 0.75));
    scene.env.skylight.enabled = true;
    scene.env.skylight.intensity = 0.6;
    scene.env.skylight.position = new two.vec3(0.0, 50.0, 0.0);
    scene.env.skylight.color = skylight;
    scene.env.skylight.ground = two.hsl(0.095, 1.0, 0.75);

    //var dir = new two.vec3(1.0 * 30.0, -1.75 * 30.0, -1.0 * 30.0);
    var r = new two.quat(-0.458, -0.261, 0.0, 0.850);

    var nl = scene.nodes().add(new two.Node3(new two.vec3(0.0), r)); //two.look_dir(dir)));
    var l = scene.lights().add(new two.Light(nl, two.LightType.Direct, true, two.hsl(0.1, 1.0, 0.95), 1.0));

    // shadow.camera.extent = 50;
    l.shadow_range = 3500.0;
    //l.shadow_bias = -0.0001;
    l.shadow_bias = 0.5;

    // GROUND

    var pbr = app.gfx.programs.file('pbr/pbr');
    var phong = app.gfx.programs.file('pbr/phong');

    var groundmat = app.gfx.materials.create('ground'); var m = groundmat;
        m.program = phong;
        m.phong.diffuse.value = two.hsl(0.095, 1, 0.75);

    var zeroq = new two.quat(new two.vec3(0.0));
    
    var ground = app.gfx.shape(new two.Rect(new two.vec2(0.0), new two.vec2(10000.0)));
    var nground = scene.nodes().add(new two.Node3(new two.vec3(0.0, -33.0, 0.0), zeroq));
    scene.items().add(new two.Item(nground, ground, 0, groundmat));

    // SKYDOME

    var skydome = app.gfx.programs.create('skydome');
    skydome.set_block(two.MaterialBlock.Solid);
    skydome.set_block(two.MaterialBlock.User);
    skydome.set_source(two.ShaderType.Vertex, skydome_vertex);
    skydome.set_source(two.ShaderType.Fragment, skydome_fragment);

    var dome = {
        top: two.rgb(0x0077ff),
        bottom: two.rgb(0xffffff),
        offset: 33,
        exponent: 0.6
    };
    
    dome.top = skylight;

    //scene.fog.color.copy( uniforms[ bottomColor ].value );

    var skysphere = app.gfx.shape(new two.Sphere(4000.0)); //  new THREE.SphereBufferGeometry(4000, 32, 15);
    var skymat = app.gfx.materials.create('skydome'); m = skymat;
        m.program = skydome;
        m.base.cull_mode = two.CullMode.Front;
        m.user.attr0 = new two.vec4(dome.top.r, dome.top.g, dome.top.b, 0.0);
        m.user.attr1 = new two.vec4(dome.bottom.r, dome.bottom.g, dome.bottom.b, 0.0);
        m.user.attr2 = new two.vec4(dome.offset, dome.exponent, 0.0, 0.0);

    var nsky = scene.nodes().add(new two.Node3());
    scene.items().add(new two.Item(nsky, skysphere, 0, skymat));

    // MODEL

    var model = app.gfx.models.file('Flamingo'); // .glb
    
    var n = scene.nodes().add(new two.Node3(new two.vec3(0.0, -1.0, 0.0), new two.quat(new two.vec3(0.0, -1.0, 0.0)), new two.vec3(0.35)));
    var it = scene.items().add(new two.Item(n, model));
}

//scene.update();
