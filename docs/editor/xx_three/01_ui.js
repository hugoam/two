var ui = panel;
var b = two.ui.board(ui);
var d1 = two.ui.div(b);

var r = two.ui.row(d1);
two.ui.button(r, '(arrow_right)');
two.ui.button(r, '(arrow_left)');
two.ui.button(r, '(arrow_down)');
two.ui.button(r, '(arrow_up)');
two.ui.button(r, 'test button');
//two.ui.multi_button(r, { '(folder_15)', 'test' }, nil)

var col = new two.Colour(1, 0, 1); //Colour.Pink
//two.ui.color_edit(d1, col);

/*var d2 = two.ui.layout(b);

var viewer_size = new two.vec2(200, 170);
var viewers = []
var colours = []

var c = two.ui.canvas(d2);
// @todo default values don't work because we are using same call object under the hood (value from previous call is persisted)
var main_viewer = two.ui.scene_viewer(d2, new two.vec2(0));
var prev_output = null;

function next_colour() {
    col = two.rgba_to_hsla(col);
    col.r = (col.r + 0.13) % 1.0;
    col = two.hsla_to_rgba(col);
}

for(var i = 0; i < 4; ++i) {
    next_colour();
    colours.push(col);

    var n = two.ui.node(c, 'Node ' + i.toString(), new two.vec2(200 + i * (viewer_size.x + 50), 100), 0);
    var input = two.ui.node_input(n, 'Input', '(file_15)', col, 1, 0);
    var output = two.ui.node_output(n, 'Output', '', col, 1, 0);
    
    // @todo comment these two fixes the main viewer wrong parent issue . investigate
    var viewer = two.ui.scene_viewer(n, viewer_size);
    viewers.push(viewer);
    
    if(prev_output !== null) {
        two.ui.node_cable(c, prev_output, input);
    }
    prev_output = output;
}

//var main_viewer = two.ui.scene_viewer(d2, new two.vec2(0))
next_colour();
colours.push(col);
viewers.push(main_viewer);

var rotation = new two.vec3(0, time, 0);

for(var i = 0; i < 5; ++i) {
    var scene = viewers[i].scene.begin();
    
    var cn2 = two.gfx.node(scene, null, new two.vec3(0), new two.quat(rotation), new two.vec3(1));
    two.gfx.shape(cn2, new two.Cube(), new two.Symbol(colours[i], new two.Colour(0, 0, 0, 0))); //two.Colour.None
    
    var cn1 = two.gfx.node(scene, null, new two.vec3(0), new two.quat(rotation), new two.vec3(2));
    two.gfx.shape(cn1, new two.Cube(), new two.Symbol(new two.Colour(0, 0, 0, 0), colours[i])); //two.Colour.None
}

//var viewer = two.ui.viewer(d2)                                          
// @todo ^ this should silently fail but it crashes, but scene arg is not nullable
// . lua wrapper should detect it and not call
*/
