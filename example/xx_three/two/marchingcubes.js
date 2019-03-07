
function upload_cubes(cubes, mesh) {
    
    var nutris = cubes.count();

    if(nutris == 0) return;
    var vertex_format = two.VertexAttribute.Position | two.VertexAttribute.Normal;
    var vertex_count = nutris * 3;

    var direct = mesh.direct(vertex_format, vertex_count);

    var output = new two.MeshAdapter(vertex_format, { direct.vertices.data, vertex_count });
    cubes.render(output);
}

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

struct Controller
{
    Material* material = nullptr;

    var speed = 1.0;
    var numBlobs = 10;
    var resolution = 28;
    var isolation = 80.0;

    bool floor = true;
    bool wallx = false;
    bool wallz = false;

    var hue = 0.0;
    var saturation = 0.8;
    var lightness = 0.1;

    var lhue = 0.0;
    var lsaturation = 0.8;
    var llightness = 0.1;

    var lx = 0.5;
    var ly = 0.5;
    var lz = 1.0;

    bool postprocessing = false;
};

Controller controller = {};
//controller.material = ;

constexpr uint32_t resolution = 28;

this.normal = app.gfx.programs.fetch('normal');
normal.blocks[MaterialBlock::Pbr] = true;

this.material = app.gfx.materials.create('normal'); var m = material;
    m.program = normal;
});

this.reflection = app.gfx.textures.file('SwedishRoyalCastle.cube');
this.refraction = reflection;
//refractionCube.mapping = THREE.CubeRefractionMapping;

//this.material = two.gfx.solid_material(app.gfx, 'material', two.hsl(0.3, 1.0, 0.5));
//material.base.cull_mode = two.CullMode.None;

MarchingCubes cubes = { resolution };

this.model = app.gfx.create_model('cubes');
Mesh mesh = model.items[0].mesh;
mesh.is_direct = true;

if(typeof this.state == 'undefined') {
    this.state = 1;

    var camera = viewer.camera;
    camera.fov = 45.0; camera.near = 1.0; camera.far = 10000.0;
    camera.eye = new two.vec3(-500.0, 500.0, 1500.0);

    //scene.background = new THREE.Color(0x050505);

    var l0 = scene.nodes().add(new two.Node3(new two.vec3(0.0), new two.quat(facing(new two.vec3(0.5, 0.5, 1.0)))));
    scene.lights().add(new two.Light(l0, two.LightType.Direct, false, rgb(0xffffff)));
    
    var l1 = scene.nodes().add(new two.Node3(new two.vec3(0.0, 0.0, 100.0)));
    scene.lights().add(new two.Light(l1, two.LightType.Point, false, rgb(0xff3300)));

    //ambientvar = new THREE.AmbientLight(0x080808);
    //scene.add(ambientLight);

    //materials = generateMaterials();
    //var current_material = 'shiny';

    var n = scene.nodes().add(new two.Node3(new two.vec3(0.0), ZeroQuat, new two.vec3(700.0)));
    scene.items().add(new two.Item(n, model, 0, material));
}

var root = viewer.scene.begin();
two.gfx.radiance(root, 'radiance/tiber_1_1k.hdr', BackgroundMode::Radiance);

var time = 0.0;

function add_blobs(object, time, numblobs, floor, wallx, wallz) {
    object.reset();

    // fill the field with some metaballs

    var subtract = 12;
    var strength = 1.2 / ((Math.sqrt(numblobs) - 1) / 4 + 1);

    for(var i = 0; i < numblobs; i++)
    {
        var ballx = Math.sin(i + 1.26 * time * (1.03 + 0.5 * Math.cos(0.21 * i))) * 0.27 + 0.5;
        var bally = abs(Math.cos(i + 1.12 * time * Math.cos(1.22 + 0.1424 * i))) * 0.77; // dip into the floor
        var ballz = Math.cos(i + 1.32 * time * 0.1 * Math.sin((0.92 + 0.53 * i))) * 0.27 + 0.5;

        add_ball(object, new two.vec3(ballx, bally, ballz), strength, subtract);
    }

    if(floor) add_planeY(object, 2, 12);
    if(wallz) add_planeZ(object, 2, 12);
    if(wallx) add_planeX(object, 2, 12);
};

var delta = app.gfx.frame_time;

time += delta * controller.speed * 0.5;

upload_cubes(cubes, mesh);

add_blobs(cubes, time, controller.numBlobs, controller.0loor, controller.wallx, controller.wallz);
