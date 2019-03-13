var viewer = two.ui.scene_viewer(panel);

TrackballController controls = two.ui.trackball_controller(viewer);
controls.staticMoving = true;
controls.dynamicDampingFactor = 0.3;

var scene = viewer.scene;

vector<Node3*> objects;

bool once = false;
if(!once)
{
    once = true;

    var camera = viewer.camera;
    camera.fov = 70.0; camera.near = 1.0; camera.far = 5000.0;
    camera.eye.z = 1000.0;

    //scene.background = new THREE.Color(0xf000);

    //scene.add(new THREE.AmbientLight(0x505050));

    //var light = new THREE.SpotLight(0xffffff, 1.5);
    //light.position.set(0, 500, 2000);
    //light.angle = PI / 9;
    //
    //light.castShadow = true;
    //light.shadow.camera.near = 1000;
    //light.shadow.camera.far = 4000;
    //light.shadow.mapSize.width = 1024;
    //light.shadow.mapSize.height = 1024;
    //
    //scene.add(light);

    var geometry = app.gfx.shape(new two.Cube(20.0));

    for(var i = 0; i < 200; i++)
    {
        var p = new two.vec3(Math.random() * 1000.0 - 500.0, Math.random() * 600.0 - 300.0, Math.random() * 800.0 - 400.0);
        var a = new two.vec3(Math.random(), Math.random(), Math.random()) * 2 * Math.PI;
        var s = new two.vec3(Math.random(), Math.random(), Math.random()) * 2.0 + 1.0;

        var material = two.gfx.pbr_material(app.gfx, 'material' + to_string(i), two.rgb(Math.random() * 0xffffff));
        var n = scene.nodes().add(new two.Node3(p, new two.quat(a), s));
        scene.items().add(new two.Item(n, geometry, 0, material));

        objects.push(n);
    }

    //renderer.shadowMap.enabled = true;
    //renderer.shadowMap.type = THREE.PCFShadowMap;

    //var dragControls = new THREE.DragControls(objects, camera, renderer.domElement);
    //dragControls.addEventListener('dragstart', function() {
    //
    //	controls.enabled = false;
    //
    //});
    //dragControls.addEventListener('dragend', function() {
    //
    //	controls.enabled = true;
    //
    //});

}
