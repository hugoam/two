// shadow_point_im.js

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

if (init) {
    //scene.add(new THREE.AmbientLight(0x111122));

    var pbr = app.gfx.programs.file('pbr/pbr');

    var c = app.gfx.materials.fetch('cube');
    c.program = pbr;
    c.base.cull_mode = two.CullMode.Front;
    c.pbr.albedo.value = two.rgb(0xa0adaf);
    c.pbr.normal.value = -1.0;
    // shininess: 10,
    // specular: 0x111111,

    this.cubemat = c;

    var s = app.gfx.materials.fetch('sphere');
    s.program = pbr;
    s.base.cull_mode = two.CullMode.None;
    s.base.uv0_scale = new two.vec2(1.0, 3.5);
    s.alpha.alpha_test = true;
    s.alpha.alpha.texture = generateTexture(app.gfx, 2, 2, 2);
    s.pbr.normal = -1.0; // @todo @bug @hack check why gl_FrontFacing in shader inverts normals

    this.spheremat = s;

    viewer.scene.env.radiance.ambient = 0.2;

    //orbit.eye = new two.vec3(0, 10, 40);
    //orbit.position = new two.vec3(0, 10, 0);
    //orbit.distance = 40;
}

function light_source(n, color, pos, rot) {
    var intensity = 1.5;
    var range = 20.0;

    var node = two.gfx.node(n, null, pos, rot);

    var inner = two.gfx.shape(node, new two.Sphere(0.3), new two.Symbol(color)); //  * intensity
    var outer = two.gfx.shape(node, new two.Sphere(2.0), new two.Symbol(new two.Colour(1.0)), 0, this.spheremat);

    var light = two.gfx.light(node, two.LightType.Point, false, color, range, 0.6);
    light.energy = intensity;
    //light.shadow_bias = -0.005; // reduces self-shadowing on double-sided objects

    return node;
};

function pos(time) {
    return new two.vec3(Math.sin(time * 0.6) * 9, Math.sin(time * 0.7) * 9 + 5, Math.sin(time * 0.8) * 9);
}

function rot(time) {
    return new two.quat(new two.vec3(time, 0.0, time));
}

var scene = viewer.scene.begin();

two.gfx.radiance(scene, 'radiance/tiber_1_1k.hdr', two.BackgroundMode.Radiance);

var light0 = light_source(scene, two.rgba(0x0088ff), pos(time), rot(time));
var light1 = light_source(scene, two.rgba(0xff8888), pos(time + Math.PI), rot(time + Math.PI));

var box = new two.Cube(new two.vec3(30.0));

var node = two.gfx.node(scene, null, new two.vec3(0, 10, 0));
two.gfx.shape(node, box, new two.Symbol(), 0, this.cubemat);//, new two.Colour(0, 0, 0, 0), false, true));
//mesh.receiveShadow = true;
