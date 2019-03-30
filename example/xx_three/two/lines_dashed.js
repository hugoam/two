// lines_dashed.js

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

function cube_model(gfx, size) {

    var h = size * 0.5;

    var geometry = new two.MeshPacker();
    geometry.primitive = two.PrimitiveType.Lines;

    var positions = [
        new two.vec3(-h, -h, -h), new two.vec3(-h,  h, -h),
        new two.vec3(-h,  h, -h), new two.vec3( h,  h, -h),
        new two.vec3( h,  h, -h), new two.vec3( h, -h, -h),
        new two.vec3( h, -h, -h), new two.vec3(-h, -h, -h),
        new two.vec3(-h, -h,  h), new two.vec3(-h,  h,  h),
        new two.vec3(-h,  h,  h), new two.vec3( h,  h,  h),
        new two.vec3( h,  h,  h), new two.vec3( h, -h,  h),
        new two.vec3( h, -h,  h), new two.vec3(-h, -h,  h),
        new two.vec3(-h, -h, -h), new two.vec3(-h, -h,  h),
        new two.vec3(-h,  h, -h), new two.vec3(-h,  h,  h),
        new two.vec3( h,  h, -h), new two.vec3( h,  h,  h),
        new two.vec3( h, -h, -h), new two.vec3( h, -h,  h)
    ];

    for(var i = 0; i < positions.length; ++i) {
        geometry.position(positions[i]);
    }
    
    return gfx.create_model_geo('cube', geometry);
}

var viewer = two.ui.scene_viewer(panel);

var scene = viewer.scene;

if(init) {
    var camera = viewer.camera;
    camera.fov = 60.0; camera.near = 1.0; camera.far = 200.0;
    camera.eye.z = 150.0;

    //scene.background = new THREE.Color(0x111111);
    //scene.fog = new THREE.Fog(0x111111, 150, 200);

    var subdivisions = 6;
    var recursion = 1;

    var points = hilbert3d(new two.vec3(0.0), 25.0, recursion);
    var curve = new two.CurveCatmullRom3(); //points);

    for(var i = 0; i < points.length; i++)
    {
        var p = points[i];
        curve.add_point(new two.vec3(p.x, p.y, p.z));
    }
    
    var geometry = new two.MeshPacker();
    geometry.primitive = two.PrimitiveType.Lines;
    
    var div = points.length * subdivisions;
    for(var i = 0; i < div; i++) {
        var p = curve.point(i / div);
        geometry.position(p);
    }
    
    var spline = app.gfx.create_model_geo('spline', geometry);
    
    var program = app.gfx.programs.fetch('line');
    
    function dash_material(colour, dash_size, dash_gap) {
        var material = app.gfx.materials.create('line'); var m = material;
            m.program = program;
            m.solid.colour = colour;
            m.line.dashed = true;
            m.line.dash_size = dash_size;
            m.line.dash_gap = dash_gap;
            m.base.shader_color = two.ShaderColor.Vertex;
    };
    
    var mat0 = dash_material(two.rgb(0xffffff), 1.0, 0.5);
    var n0 = scene.nodes().add(new two.Node3());
    scene.items().add(new two.Item(n0, spline, 0, mat0));
    this.node0 = n0;
    
    var cube = cube_model(app.gfx, 50.0);
    
    var mat1 = dash_material(two.rgb(0xffaa00), 3.0, 1.0);
    var n1 = scene.nodes().add(new two.Node3());
    scene.items().add(new two.Item(n1, cube, 0, mat1));
    this.node1 = n1;
}

var time = app.gfx.time;

var angles = new two.vec3(0.25 * time, 0.25 * time, 0.0);

this.node0.apply(new two.vec3(0.0), new two.quat(angles));
this.node1.apply(new two.vec3(0.0), new two.quat(angles));

