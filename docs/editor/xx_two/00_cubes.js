
var viewer = two.ui.scene_viewer(app.ui.begin());
two.ui.orbit_controller(viewer);

var scene = viewer.scene.begin();

time += 0.01;

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
        two.gfx.shape(n, cube, new two.Symbol(empty, color));
    }
}
