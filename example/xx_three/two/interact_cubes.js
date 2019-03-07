//var mouse = new two.vec2(0.0); // , INTERSECTED;
var radius = 100; var theta = 0;

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

var scene = viewer.scene;
var camera = viewer.camera;

bool once = false;
if(!once)
{
    once = true;

    camera.fov = 70.0; camera.near = 1.0; camera.far = 10000.0;

    //scene.background = new THREE.Color(0xf000);

    scene.lights().add(new two.Light(scene.root_node, two.LightType.Direct, false));
    //var light = new THREE.DirectionalLight(0xffffff, 1);
    //light.position.set(1, 1, 1).normalize();
    //scene.add(light);

    //var geometry = new THREE.BoxBufferGeometry(20, 20, 20);
    var model = app.gfx.shape(new two.Cube(20.0));

    for(var i = 0; i < 2000; i++)
    {
        // new THREE.MeshLambertMaterial({ color: random() * 0xffffff })
        var material = app.gfx.fetch_material('material' + to_string(i), 'pbr/pbr');
        material.pbr.albedo = two.hsl(Math.random(), 0.7, 0.5);

        var pos = new two.vec3(Math.random(), Math.random(), Math.random()) * 800.0 - 400.0;
        var angles = new two.vec3(Math.random(), Math.random(), Math.random()) * 2 * Math.PI;
        var scale = new two.vec3(Math.random(), Math.random(), Math.random()) + 0.5;

        var n = scene.nodes().add(new two.Node3(pos, new two.quat(angles), scale));
        var it = scene.items().add(new two.Item(n, model, ItemFlag::Default | ItemFlag::Selectable, material));
    }

    //raycaster = new THREE.Raycaster();
}

//if(var mouse_event)
//{
//	mouse.x = (event.clientX / window.innerWidth) * 2 - 1;
//	mouse.y = -(event.clientY / window.innerHeight) * 2 + 1;
//}

theta += 0.1;

camera.eye.x = radius * Math.sin(to_radians(theta));
camera.eye.y = radius * Math.sin(to_radians(theta));
camera.eye.z = radius * Math.cos(to_radians(theta));
//camera.target = scene.position;

Item* hovered = nullptr;

function hover = [](var item) { item.material->pbr.emissive = two.rgba(0xff0000f); };
function unhover = [](var item) { item.material->pbr.emissive = two.rgba(0x00000000); };

if(var mouse_event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved))
{
    function pick = [](Item* item) { if(hovered) unhover(*hovered); hovered = item; if(hovered) hover(*hovered); };
    viewer.picker(0).pick_point(viewer.viewport, mouse_event.relative, pick, ItemFlag::Selectable);
}

// find intersections
//raycaster.setFromCamera(mouse, camera);
//
//var intersects = raycaster.intersectObjects(scene.children);
//
//if(intersects.length > 0) {
//
//	if(INTERSECTED != intersects[0].object) {
//
//		if(INTERSECTED) INTERSECTED.material.emissive.setHex(INTERSECTED.currentHex);
//
//		INTERSECTED = intersects[0].object;
//		INTERSECTED.currentHex = INTERSECTED.material.emissive.getHex();
//		INTERSECTED.material.emissive.setHex(0xff0000);
//
//	}
//
//}
//else {
//
//	if(INTERSECTED) INTERSECTED.material.emissive.setHex(INTERSECTED.currentHex);
//
//	INTERSECTED = null;
//
//}