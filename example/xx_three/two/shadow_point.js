// shadow_point.js

function generateTexture(gfx) {
    
    var texture = gfx.textures.create('half');

    var width = 2;
    var height = 2;

    var buffer = new Float32Array(width * height * 4);

    for(var x = 0; x < width; ++x)
        for(var y = 0; y < height; ++y)
        {
            if(y == 0) data[x + y * width] = 0xffffffff;
            else data[x + y * width] = 0x00000000;
        }

    two.load_texture_rgba(texture, 2, 2, buffer);
    return texture;
}

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);
two.ui.trackball_controller(viewer);

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
    s.alpha.alpha.texture = generateTexture(app.gfx);
    s.pbr.normal = -1.0; // @todo @bug @hack check why gl_FrontFacing in shader inverts normals
    this.spheremat = s;

    viewer.scene.env.radiance.ambient = 0.2;
}

function light_source(parent, color, pos, rot)
{
    var intensity = 1.5;
    var range = 20.0;

    var node = two.gfx.node(parent, null, pos, rot);

    var inner = two.gfx.shape(node, new two.Sphere(0.3), new two.Symbol(color));// * intensity));
    var outer = two.gfx.shape(node, new two.Sphere(2.0), new two.Symbol(new two.Colour(1.0)), 0, sphere_material);
    
    var light = two.gfx.light(node, two.LightType.Point, true, color, range, 0.6);// intensity);
    light.range = range;
    light.energy = intensity;
    light.shadow_bias = 0.005;

    return node;
};

function light_pos(time)
{
    return new two.vec3(Math.sin(time * 0.6) * 9, Math.sin(time * 0.7) * 9 + 5, Math.sin(time * 0.8) * 9);
};

function light_rot(time)
{
    return new two.quat(new two.vec3(time, 0.0, time));
};

var scene = viewer.scene.begin();

two.gfx.radiance(scene, 'radiance/tiber_1_1k.hdr', two.BackgroundMode.Radiance);

var pos0 = light_pos(time);
var rot0 = light_rot(time);
var light0 = light_source(scene, two.rgba(0x0088ff), pos0, rot0);

//two.gfx.shape(scene, Cylinder(X3, 0.1, 1.0, Axis::X), new two.Symbol(two.rgb(0xff0000));
//two.gfx.shape(scene, Cylinder(Y3, 0.1, 1.0, Axis::Y), new two.Symbol(two.rgb(0x00ff00));
//two.gfx.shape(scene, Cylinder(Z3, 0.1, 1.0, Axis::Z), new two.Symbol(two.rgb(0x0000ff));

var pos1 = light_pos(time + Math.PI);
var rot1 = light_rot(time + Math.PI);
var light1 = light_source(scene, two.rgba(0xff8888), pos1, rot1);

var box = new two.Cube(new two.vec3(15.0));
var node = two.gfx.node(scene);// , Y3 * 10.0);
two.gfx.shape(node, box, new two.Symbol(), 0, this.cubemat);
