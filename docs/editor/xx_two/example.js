function update(two, app, time) {
    var board = two.ui.board(app.ui.begin());
    //var button = two.ui.button(board, "Teeeeeeeeeeeeeeeeeest");
    var screen = two.ui.board(board);

    var viewer = two.ui.scene_viewer(screen);
    two.ui.orbit_controller();
    var scene = viewer.scene.begin();
    
    var empty = new two.Colour(0, 0, 0, 0);
    var zero3 = new two.vec3(0);
    var cube = new two.Cube();
    
    for(var x = 0; x < 11; ++x)
    {
        for(var y = 0; y < 11; ++y)
        {
            var angles = new two.vec3(time + x * 0.21, 0.0, time + y * 0.37);
            var pos = new two.vec3(-15.0 + x * 3.0, 0, -15.0 + y * 3.0);

            var r = Math.cos(time + x * 0.21) + 1 / 2;
            var b = Math.sin(time + y * 0.37) + 1 / 2;
            var g = Math.cos(time) + 1 / 2;
            var color = new two.Colour(r, g, b);

            var n = two.gfx.node(scene, null, pos, new two.quat(angles));
            two.gfx.shape(n, cube, new two.Symbol(color, empty));
        }
    }
}
