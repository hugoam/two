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

    texture.load_rgba(new two.uvec2(width, height), buffer);
    return texture;
}

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controller(viewer);
var control = two.ui.trackball_controller(viewer);

var scene = viewer.scene;

if (init) {
    
    var camera = viewer.camera;
    camera.fov = 45.0; camera.near = 1.0; camera.far = 1000.0;
    camera.eye = new two.vec3(0.0, 10.0, 40.0);

    control.target = new two.vec3(0.0, 10.0, 0.0);
        
	var env = scene.env;
    env.radiance.ambient = two.rgb(0x111122);

    var phong = app.gfx.programs.file('pbr/phong');

    var c = app.gfx.materials.fetch('cube');
    c.program = phong;
    c.base.cull_mode = two.CullMode.Front;
    c.lit.normal.value = -1.0;
    c.phong.diffuse.value = two.rgb(0xa0adaf);
    c.phong.specular.value = two.rgb(0x111111);
    c.phong.shininess.value = 10.0;
    this.cubemat = c;

    var s = app.gfx.materials.fetch('sphere');
    s.program = phong;
    s.base.cull_mode = two.CullMode.None;
    s.base.uv0_scale = new two.vec2(1.0, 3.5);
    s.alpha.alpha_test = true;
    s.alpha.alpha.texture = generateTexture(app.gfx, 2, 2, 2);
    s.lit.normal.value = -1.0; // @todo @bug @hack check why gl_FrontFacing in shader inverts normals
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
        
        var light = scene.lights().add(new two.Light(node, two.LightType.Point, true, color, intensity, range)); //, 0.6));// intensity);
        //light.shadow_bias = 0.005;
        
        this.lights.push(node);
    }
        
    var zeroq = new two.quat(new two.vec3(0.0));
    var cube = new two.Cube(new two.vec3(15.0));
    var node = scene.nodes().add(new two.Node3(new two.vec3(0.0, 10.0, 0.0), zeroq));
    scene.items().add(new two.Item(node, app.gfx.shape(cube), 0, this.cubemat));
}

function pos(time) {
    return new two.vec3(Math.sin(time * 0.6) * 9, Math.sin(time * 0.7) * 9 + 5, Math.sin(time * 0.8) * 9);
};

function rot(time) {
    return new two.quat(new two.vec3(time, 0.0, time));
};

var time = app.gfx.time;

var time0 = time;
this.lights[0].apply(pos(time0), rot(time0));

var time1 = time + 10000;
this.lights[1].apply(pos(time1), rot(time1));
