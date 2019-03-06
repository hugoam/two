// shadow_point.js

function generateTexture(gfx, width, height, m) {
    
    var texture = gfx.textures.create('half');

    var buffer = new Int32Array(width * height);

    for(var x = 0; x < width; ++x)
        for(var y = 0; y < height; ++y)
        {
            if(y % m == 0) buffer[x + y * width] = 0xffffffff;
            else buffer[x + y * width] = 0x00000000;
        }

    //texture.upload(2, 2, buffer);
    two.load_texture_rgba(texture, 2, 2, buffer);
    return texture;
}

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);
two.ui.trackball_controller(viewer);

var scene = viewer.scene;

if(typeof this.state == 'undefined') {
    this.state = 1;
        
    //scene.add(new THREE.AmbientLight(0x111122));

    var pbr = app.gfx.programs.file('pbr/pbr');

    var c = app.gfx.materials.fetch('cube');
    c.program = pbr;
    c.base.cull_mode = two.CullMode.Front;
    c.pbr.albedo.value = two.rgba(0xa0adafff);
    c.pbr.normal.value = -1.0;
    //	shininess: 10,
    //	specular: 0x111111,
    this.cubemat = c;

    var s = app.gfx.materials.fetch('sphere');
    s.program = pbr;
    s.base.cull_mode = two.CullMode.None;
    s.base.uv0_scale = new two.vec2(1.0, 3.5);
    s.alpha.alpha_test = true;
    s.alpha.alpha.texture = generateTexture(app.gfx, 2, 2, 2);
    s.pbr.normal = -1.0; // @todo @bug @hack check why gl_FrontFacing in shader inverts normals
    this.spheremat = s;

    var colors = [0x0088ff, 0xff8888];
    
    this.lights = [];
    for(var i = 0; i < 2; ++i) {
        
        var color = two.rgb(colors[i]);
        var intensity = 1.5;
        var range = 20.0;
        
        var sphere0 = app.gfx.shape(new two.Sphere(0.3));
        var sphere1 = app.gfx.shape(new two.Sphere(2.0));
        
        var node = scene.nodes().add(new two.Node3());
        var inner = scene.items().add(new two.Item(node, sphere0, 0, app.gfx.symbol_material(new two.Symbol(color), two.PLAIN)));// * intensity));
        var outer = scene.items().add(new two.Item(node, sphere1, 0, this.spheremat));
        
        var light = scene.lights().add(new two.Light(node, two.LightType.Point, false, color, intensity, range)); //, 0.6));// intensity);
        //light.shadow_bias = 0.005;
        
        this.lights.push(node);
    }
        
    var cube = new two.Cube(new two.vec3(15.0));
    var node = scene.nodes().add(new two.Node3());// , Y3 * 10.0);
    scene.items().add(new two.Item(node, app.gfx.shape(cube), 0, this.cubemat));

    viewer.scene.env.radiance.ambient = 0.2;
}

function pos(time) {
    return new two.vec3(Math.sin(time * 0.6) * 9, Math.sin(time * 0.7) * 9 + 5, Math.sin(time * 0.8) * 9);
};

function rot(time) {
    return new two.quat(new two.vec3(time, 0.0, time));
};

var scene = viewer.scene.begin();

two.gfx.radiance(scene, 'radiance/tiber_1_1k.hdr', two.BackgroundMode.Radiance);

var time0 = time;
this.lights[0].apply(pos(time), rot(time));

var time1 = time + Math.PI;
this.lights[1].apply(pos(time1), rot(time1));
