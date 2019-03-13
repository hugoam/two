// lines_fat.js

var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controller(viewer);
//controls.minDistance = 10;
//controls.maxDistance = 500;

var scene = viewer.scene;

function hilbert3d(center, size, iterations, v0, v1, v2, v3, v4, v5, v6, v7) {

    // Default Vars
    var center = center !== undefined ? center : { x: 0, y: 0, z: 0 },
        size = size !== undefined ? size : 10,
        half = size / 2,
        iterations = iterations !== undefined ? iterations : 1,
        v0 = v0 !== undefined ? v0 : 0,
        v1 = v1 !== undefined ? v1 : 1,
        v2 = v2 !== undefined ? v2 : 2,
        v3 = v3 !== undefined ? v3 : 3,
        v4 = v4 !== undefined ? v4 : 4,
        v5 = v5 !== undefined ? v5 : 5,
        v6 = v6 !== undefined ? v6 : 6,
        v7 = v7 !== undefined ? v7 : 7
    ;
    
    var px = center.x + half; var py = center.y + half; var pz = center.z + half;
    var nx = center.x - half; var ny = center.y - half; var nz = center.z - half;
    var corners = [
        { x: nx, y: py, z: nz },
        { x: nx, y: py, z: pz },
        { x: nx, y: ny, z: pz },
        { x: nx, y: ny, z: nz },
        { x: px, y: ny, z: nz },
        { x: px, y: ny, z: pz },
        { x: px, y: py, z: pz },
        { x: px, y: py, z: nz }
    ];

    var vec = [ corners[v0], corners[v1], corners[v2], corners[v3], corners[v4], corners[v5], corners[v6], corners[v7] ];

    // Recurse iterations
    if (--iterations >= 0) {

        var tmp = [];

        Array.prototype.push.apply(tmp, hilbert3d(vec[0], half, iterations, v0, v3, v4, v7, v6, v5, v2, v1));
        Array.prototype.push.apply(tmp, hilbert3d(vec[1], half, iterations, v0, v7, v6, v1, v2, v5, v4, v3));
        Array.prototype.push.apply(tmp, hilbert3d(vec[2], half, iterations, v0, v7, v6, v1, v2, v5, v4, v3));
        Array.prototype.push.apply(tmp, hilbert3d(vec[3], half, iterations, v2, v3, v0, v1, v6, v7, v4, v5));
        Array.prototype.push.apply(tmp, hilbert3d(vec[4], half, iterations, v2, v3, v0, v1, v6, v7, v4, v5));
        Array.prototype.push.apply(tmp, hilbert3d(vec[5], half, iterations, v4, v3, v2, v5, v6, v1, v0, v7));
        Array.prototype.push.apply(tmp, hilbert3d(vec[6], half, iterations, v4, v3, v2, v5, v6, v1, v0, v7));
        Array.prototype.push.apply(tmp, hilbert3d(vec[7], half, iterations, v6, v5, v2, v1, v0, v3, v4, v7));

        // Return recursive call
        return tmp;
    }

    // Return complete Hilbert Curve.
    return vec;
}

if (init) {
    var camera = viewer.camera;
    camera.fov = 40.0; camera.near = 1.0; camera.far = 1000.0;
    camera.eye = new two.vec3(-40.0, 0.0, 60.0);

    var program = app.gfx.programs.fetch('line');

    var material = app.gfx.materials.create('line'); var m = material;
        m.program = program;
        m.solid.colour = two.rgb(0xffffff);
        m.line.line_width = 5.0;
        m.line.dashed = true;
        m.base.shader_color = two.ShaderColor.Vertex;

    this.lines = new two.Lines(app.gfx);

    var points = hilbert3d(new two.vec3(0.0), 20.0, 1);
    var curve = new two.CurveCatmullRom3(points);

    for(var i = 0; i < points.length; i++)
    {
        var p = points[i];
        curve.add_point(new two.vec3(p.x, p.y, p.z));
    }

    var div = Math.round(12 * points.length);
    
    this.lines.start(curve.point(0.0), two.hsl(0.0, 1.0, 0.5));
    
    for(var i = 0; i < div; i++)
    {
        var p = curve.point(i / div);
        var c = two.hsl(i / div, 1.0, 0.5);
        
        this.lines.next(p, c);
    }

    var n = scene.nodes().add(new two.Node3());
    var it = scene.items().add(new two.Item(n, this.lines.model, 0, material));
    this.batch = scene.batches().add(new two.Batch(it));
    it.batch = this.batch;
}

var root = scene.begin();
two.gfx.radiance(root, 'radiance/tiber_1_1k.hdr', two.BackgroundMode.Radiance);

this.lines.commit(this.batch);
