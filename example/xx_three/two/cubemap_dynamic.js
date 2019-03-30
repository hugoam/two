// cubemap_dynamic.js

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controls(viewer);
viewer.viewport.active = false;

var scene = viewer.scene;

if(init)
{
    this.count = 0;

    this.lon = 0.0; this.lat = 0.0;
    this.phi = 0.0; this.theta = 0.0;

    var camera = viewer.camera;
    camera.fov = 60.0; camera.near = 1.0; camera.far = 1000.0;
    //camera.fov = 120.0;

    this.envmap = app.gfx.textures.file('cabin.jpg');
    //this.envmap = app.gfx.textures.file('cube/cabin.png.cube');

    scene.env.radiance.texture = this.envmap;
    scene.env.radiance.energy = 1.0;
    scene.env.radiance.filter = false;
    scene.env.background.texture = this.envmap;
    scene.env.background.mode = two.BackgroundMode.Panorama;

    this.cube0 = new two.CubeCamera(scene, 1.0, 1000.0, 256);
    this.cube1 = new two.CubeCamera(scene, 1.0, 1000.0, 256);

    var basic = app.gfx.programs.fetch('pbr/basic');

    var material = app.gfx.materials.create('material'); var m = material;
        m.program = basic;
        m.pbr.albedo.value = two.rgb(0xffffff);
        //m.pbr.metallic = 1.0;

    var sphere = scene.nodes().add(new two.Node3());
    //isphere = scene.items().add(new two.Item(sphere, app.gfx.shape(new two.Icosaedr(20.0))));
    this.isphere = scene.items().add(new two.Item(sphere, app.gfx.shape(new two.Sphere(20.0)), 0, material));

    this.cube = scene.nodes().add(new two.Node3());
    scene.items().add(new two.Item(cube, app.gfx.shape(new two.Cube(10.0)), 0, material));
    
    this.torus = scene.nodes().add(new two.Node3());
    scene.items().add(new two.Item(torus, app.gfx.shape(new two.TorusKnot(10.0, 5.0)), 0, material));
    
    this.cubea = new two.vec3(0.0);
    this.torusa = new two.vec3(0.0);
    
    this.presslat = 0.0; this.presslon = 0.0;
    this.pressed = false;
    this.pressX = 0.0;
    this.pressY = 0.0;
}

{
    var event = viewer.mouse_event(two.DeviceType.MouseLeft, two.EventType.Pressed);
    if(event.valid())
    {
        this.pressX = event.relative.x; this.pressY = event.relative.y;
        this.presslon = this.lon;
        this.presslat = this.lat;
        this.pressed = true;
    }
}

{
    var event = viewer.mouse_event(two.DeviceType.MouseLeft, two.EventType.Released);
    if(event.valid())
        this.pressed = false;
}

{
    var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved);
    if(event.valid() && this.pressed)
    {
        this.lon = (event.relative.x - this.pressX) * 0.1 + this.presslon;
        this.lat = (event.relative.y - this.pressY) * 0.1 + this.presslat;
    }
}

{
    var event = viewer.mouse_event(two.DeviceType.MouseMiddle, two.EventType.Moved)
    if(event.valid())
    {
        viewer.camera.fov = Math.min(Math.max(viewer.camera.fov + event.deltaZ, 10.0), 75.0);
    }
}

this.lon += 0.15;

function toRadians(degrees) {
  return degrees * Math.PI / 180;
}

this.lat = Math.max(-85.0, Math.min(85.0, this.lat));
this.phi = toRadians(90.0 - this.lat);
this.theta = toRadians(this.lon);

function trigo3(a, f) { return new two.vec3(Math.cos(a) * f, Math.sin(a) * f, Math.sin(a) * f); };

var cubep = trigo3(time, 30.0);
this.cubea.x += 0.02; this.cubea.y += 0.03;
this.cube.apply(cubep, new two.quat(this.cubea));

var torusp = trigo3(time + 10.0, 30.0);
this.torusa.x += 0.02; this.cubea.y += 0.03;
this.torus.apply(torusp, new two.quat(this.torusa));

var camera = viewer.camera;
camera.eye.x = 100.0 * Math.sin(this.phi) * Math.cos(this.theta);
camera.eye.y = 100.0 * Math.cos(this.phi);
camera.eye.z = 100.0 * Math.sin(this.phi) * Math.sin(this.theta);

scene.env.radiance.texture = this.envmap;
scene.env.background.texture = this.envmap;

var render = new two.Render(two.Shading.Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame);
app.gfx.renderer.gather(render);
app.gfx.renderer.begin(render);

two.begin_pbr_render(app.gfx, render);

function render_probe(gfx, render, probe) {
    
    for(var axis = 0; axis < 6; ++axis) {
        
        var probe_render = probe.render(gfx, render, axis);
        gfx.renderer.gather(probe_render);
        gfx.renderer.begin(probe_render);
        
        two.pass_clear(gfx, render);
        two.pass_opaque(gfx, render);
        two.pass_background(gfx, render);
        
        gfx.renderer.end(probe_render);
        render.pass_index = probe_render.pass_index;
    }
}

// @todo shouldn't be necessary because faces outward, but somehow it gets rendered by the probe :(
this.isphere.visible = false;

// pingpong

if(this.count % 2 === 0) {
    scene.env.radiance.texture = this.cube0.cubemap.cubemap;
    render_probe(app.gfx, render, this.cube1);
}
else {
    scene.env.radiance.texture = this.cube1.cubemap.cubemap;
    render_probe(app.gfx, render, this.cube0);
}

this.isphere.visible = true;

two.pass_clear(app.gfx, render);
two.pass_opaque(app.gfx, render);

//scene.env.background.texture = cube0.cubemap.cubemap;
two.pass_background(app.gfx, render);

app.gfx.renderer.end(render);

this.count++;
