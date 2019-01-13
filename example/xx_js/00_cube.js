
ex_00_cube = function (app, parent, dockbar) {
	var viewer = ui.scene_viewer(parent);
	ui.orbit_controller(viewer);
	viewer.take_focus();
    
	var scene = viewer.scene.begin();
    var node = gfx.node(scene, null, position);
	gfx.shape(node, new Cube(), Symbol.wire(Colour.Red));
}

pump = function(app) {
	shell_context(app.ui.begin(), app.editor);
	ex_00_cube(app, app.editor.screen, app.editor.dockbar);
}

main = function() {
	Shell app("/data/");
	app.gfx_system.init_pipeline(pipeline_minimal);
	app.run(pump);
}
