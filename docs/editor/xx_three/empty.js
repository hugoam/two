// empty.js

var viewer = two.ui.scene_viewer(panel);
viewer.viewport.autorender = false;

var scene = viewer.scene;

if(init) {
    var camera = viewer.camera;
    camera.fov = 70.0; camera.near = 1.0; camera.far = 1000.0;
    camera.eye.z = 400.0;
}

