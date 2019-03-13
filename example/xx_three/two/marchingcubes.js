// marching_cubes.js

function upload_cubes(cubes, mesh) {

    var num_tris = cubes.count();

    if(num_tris == 0) return;
    var vertex_format = (1 << 0) | (1 << 3);
    //var vertex_format = two.VertexAttribute.Position | two.VertexAttribute.Normal;
    var vertex_count = num_tris * 3;

    var direct = mesh.direct(vertex_format, vertex_count);
    cubes.direct(direct);
}

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;

if (init) {
    var camera = viewer.camera;
    camera.fov = 45.0; camera.near = 1.0; camera.far = 10000.0;
    camera.eye = new two.vec3(-500.0, 500.0, 1500.0);

    this.controller = {
        material: null,

        speed: 1.0,
        numBlobs: 10,
        resolution: 28,
        isolation: 80.0,

        floor: false,
        wallx: false,
        wallz: false,

        hue: 0.0,
        saturation: 0.8,
        lightness: 0.1,

        lhue: 0.0,
        lsaturation: 0.8,
        llightness: 0.1,

        lx: 0.5,
        ly: 0.5,
        lz: 1.0,

        postprocessing: false
    };

    var resolution = 28;

    var normal = app.gfx.programs.fetch('normal');

    var material = app.gfx.materials.create('normal'); var m = material;
        m.program = normal;

    var reflection = app.gfx.textures.file('SwedishRoyalCastle.cube');
    var refraction = reflection;
    //refractionCube.mapping = THREE.CubeRefractionMapping;

    this.cubes = new two.MarchingCubes(resolution);

    this.model = app.gfx.create_model('cubes');
    this.mesh = model.get_mesh(0);
    this.mesh.is_direct = true;

    var n = scene.nodes().add(new two.Node3(new two.vec3(0.0), new two.quat(new two.vec3(0.0)), new two.vec3(700.0)));
    scene.items().add(new two.Item(n, model, 0, material));
    
    //scene.background = new THREE.Color(0x050505);

}

var root = viewer.scene.begin();
two.gfx.radiance(root, 'radiance/tiber_1_1k.hdr', two.BackgroundMode.Radiance);

function add_blobs(cubes, time, numblobs, floor, wallx, wallz) {
    cubes.reset();

    // fill the field with some metaballs

    var subtract = 12;
    var strength = 1.2 / ((Math.sqrt(numblobs) - 1) / 4 + 1);

    for(var i = 0; i < numblobs; i++)
    {
        var ballx = Math.sin(i + 1.26 * time * (1.03 + 0.5 * Math.cos(0.21 * i))) * 0.27 + 0.5;
        var bally = Math.abs(Math.cos(i + 1.12 * time * Math.cos(1.22 + 0.1424 * i))) * 0.77; // dip into the floor
        var ballz = Math.cos(i + 1.32 * time * 0.1 * Math.sin((0.92 + 0.53 * i))) * 0.27 + 0.5;

        two.add_ball(cubes, new two.vec3(ballx, bally, ballz), strength, subtract);
    }

    if(floor) two.add_planeY(cubes, 2, 12);
    if(wallz) two.add_planeZ(cubes, 2, 12);
    if(wallx) two.add_planeX(cubes, 2, 12);
};

//var time = 0.0;

//var delta = app.gfx.frame_time;
//
//time += delta * controller.speed * 0.5;

add_blobs(this.cubes, time, this.controller.numBlobs, this.controller.floor, this.controller.wallx, this.controller.wallz);

upload_cubes(this.cubes, this.mesh);
