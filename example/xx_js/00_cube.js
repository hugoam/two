mud = Module.mud;
ui = Module.mud.ui;
gfx = Module.mud.gfx;

render = function (app) {
    var board = ui.board(app.ui.begin());
    var screen = ui.board(board);

    var viewer = ui.scene_viewer(screen);
    ui.orbit_controller(viewer);
    viewer.take_focus();

    var scene = viewer.scene.begin();
    var node = gfx.node(scene, null, new vec3(0));
    gfx.shape(node, new Cube(), Symbol.wire(Colour.Red));
}

main = function() {
	var app = new mud.Shell("/data/");
    app.gfx_system.default_pipeline();
    while (true) {
        app.frame();
        render(app);
    }
}
