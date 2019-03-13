
var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controller(viewer);

var camera = viewer.camera;
camera.near = 2.0; camera.far = 2000.0;
camera.eye.z = 1000.0;

var scene = viewer.scene;
//scene.fog = new THREE.FogExp2(0x000000, 0.001);

var num = 10000;
//var num = 1;

this.batch = nullptr;
//struct Instance { vec4 d0; vec4 d1; };

if (init) {
    this.program = app.gfx.programs.fetch('point');

    this.sprite = app.gfx.textures.file('sprites/disc.png');

    this.material = app.gfx.materials.create('points');
    
    var m = this.material;
    m.program = program;
    m.solid.colour.value = two.hsl(1.0, 0.3, 0.7);
    m.solid.colour.texture = sprite;
    m.point.size = 35.0;
    m.point.project = false;
    m.alpha.alpha_test = 0.5;
    m.alpha.is_alpha = true;

    var model = app.gfx.models.get('point');

    this.instances = [];
    
    for(var i = 0; i < num; i++)
    {
        var pos = new two.vec3(Math.random(), Math.random(), Math.random()) * 2000.0 - 1000.0;
        var scale = new two.vec2(1.0);
        this.instances[i] = { d0: new two.vec4(pos, 0.0), d1: new two.vec4(scale, new two.vec2(0.0)) };
    }

    var n = scene.nodes().add(new two.Node3());
    var it = scene.items().add(new two.Item(n, model, 0, material));

    this.batch = two.gfx.batches(scene).add(new two.Batch(it));
    it.batch = this.batch;
}

//two.ui.slider_field(viewer, 'sizeAttenuation', { material.sizeAttenuation, { 0.0, 1000.0, 1.0 } })

var time = app.gfx.time;

this.mouse = new two.vec2(0.0);
if(var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved))
{
    mouse = (event.relative - viewer.frame.size / 2.0);
}

viewer.camera.eye.x += (mouse.x - viewer.camera.eye.x) * 0.05;
viewer.camera.eye.y += (-mouse.y - viewer.camera.eye.y) * 0.05;

//viewer.camera.target = scene.position;

var h = ((360.0 * (1.0 + time)) % 360.0) / 360.0;
this.material.solid.colour = two.hsl(h, 0.5, 0.5);

span<float> memory = batch->begin(instances.length, sizeof(Instance));
memcpy(memory.data(), instances.data(), memory.length * sizeof(float));
