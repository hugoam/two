// lines_fat.js

var viewer = two.ui.scene_viewer(app.ui.begin());
two.ui.orbit_controller(viewer);
//controls.minDistance = 10;
//controls.maxDistance = 500;

var scene = viewer.scene;

//camera2 = new THREE.PerspectiveCamera(40, 1, 1, 1000);
//camera2.position.copy(camera.position);

this.program = app.gfx.programs.fetch('line');

this.material = app.gfx.materials.create('line'); var m = material;
    m.program = program;
    m.solid.colour = two.rgb(0xffffff);
    m.line.line_width = 5.0;
    m.line.dashed = true;
    m.base.shader_color = two.ShaderColor.Vertex;

this.batch = nullptr;
//vector<Lines::Segment> segments;

if(typeof this.state == 'undefined') {
    this.state = 1;

    var camera = viewer.camera;
    camera.fov = 40.0; camera.near = 1.0; camera.far = 1000.0;
    camera.eye = new two.vec3(-40.0, 0.0, 60.0);

    var lines = new two.Lines(app.gfx);

    //vector<vec3> points = hilbert3d(new two.vec3(0.0), 20.0, 1);

    var curve = new two.CurveCatmullRom3(points);
    var divisions = round(12 * points.length);
    var l = float(divisions);

    for(var i = 0; i < divisions - 1; i++)
    {
        var start = curve.point(float(i+0) / l);
        var end   = curve.point(float(i+1) / l);

        var color_start = two.hsl(float(i+0) / l, 1.0, 0.5);
        var color_end   = two.hsl(float(i+1) / l, 1.0, 0.5);

        lines.segments.push({ start, 0.0, end, 0.0, color_start, color_end });
    }

    lines.compute_distances();

    segments = lines.segments;

    var n = scene.nodes().add(new two.Node3());
    var it = scene.items().add(new two.Item(n, *lines.model, 0, material));
    batch = two.gfx.batches(scene).add(new two.Batch(it));
    it.batch = batch;

    //line = new THREE.Line2(geometry, matLine);
    //line.computeLineDistances();
    //line.scale.set(1, 1, 1);
    //scene.add(line);


    // THREE.Line (BufferGeometry, LineBasicMaterial) - rendered with gl.LINE_STRIP

    /*var geo = new THREE.BufferGeometry();
    geo.addAttribute('position', new THREE.Float32BufferAttribute(positions, 3));
    geo.addAttribute('color', new THREE.Float32BufferAttribute(colors, 3));

    matLineBasic = new THREE.LineBasicMaterial({ vertexColors: THREE.VertexColors });
    matLineDashed = new THREE.LineDashedMaterial({ vertexColors: THREE.VertexColors, scale: 2, dashSize: 1, gapSize: 1 });

    line1 = new THREE.Line(geo, matLineBasic);
    line1.computeLineDistances();
    line1.visible = false;
    scene.add(line1);

    initGui();*/
}

var root = scene.begin();
two.gfx.radiance(root, 'radiance/tiber_1_1k.hdr', BackgroundMode::Radiance);

span<float> memory = batch->begin(segments.length, sizeof(Lines::Segment));
memcpy(memory.data(), segments.data(), memory.length * sizeof(float));

//if(Widget* dock = two.ui.dockitem(dockbar, 'Game', { 1U }))
//{
//    var sheet = two.ui.columns(*dock, { 0.3, 0.7 });
//
//    two.ui.slider_field<float>(sheet, 'line width', { material.line.line_width, { 0.0, 20.0, 0.1 } });
//
//    two.ui.input_field<bool>(sheet, 'dased', material.line.dashed);
//    two.ui.slider_field<float>(sheet, 'dash scale', { material.line.dash_scale, { 0.0, 20.0, 0.1 } });
//    two.ui.slider_field<float>(sheet, 'dash size', { material.line.dash_size,  { 0.0, 20.0, 0.1 } });
//    two.ui.slider_field<float>(sheet, 'dash gap', { material.line.dash_gap,   { 0.0, 20.0, 0.1 } });
//}
