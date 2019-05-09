
var viewer = two.ui.scene_viewer(app.ui.begin());
two.ui.orbit_controller(viewer);

var scene = viewer.scene.begin();

var empty = new two.Colour(0, 0, 0, 0);
var zero3 = new two.vec3(0);
var cube = new two.Cube();

if(typeof this.state == 'undefined') {
    this.state = 1;
    
    this.lights = [];
    
    var size = 5;
    for(var x = 0; x < size; ++x)
        for(var y = 0; y < size; ++y)
        {
            this.lights.push(two.hsl(Math.random(), 1, 0.5));
        }
}


var size = 5;
var spacing = 4 * 2;
//vec3 center = { (size-1) * spacing * -0.5, 0, (size-1) * spacing * -0.5 };

for(var x = 0; x < size; ++x)
    for(var y = 0; y < size; ++y)
    {
        var colour = this.lights[x + y * size];

        var moving = true;
        var height = moving ? Math.sin(time + (y + x) * 0.21) * 5 : 5;

        var pos = center + vec3{ x * spacing, height, y * spacing }
        var rot = two.angle_axis(Math.PI / 2, new two.vec3(1, 0, 0));
        var node = two.gfx.node(scene, null, pos);
        var light = two.gfx.light(node, two.LightType.Point, false, colour, 9, 0.4);

        two.gfx.shape(node, new two.Cube(new two.vec3(0.1)), new two.Symbol(), 0);
        
    }