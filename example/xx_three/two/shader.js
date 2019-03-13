
var vertex_shader = `$input a_position, a_texcoord0
    $output v_uv0
    
    #include <common.sh>
    
    void main()
    {
        var material_index = int(u_state_material);
        Basevar basic = read_base_material(material_index);
        
       v_uv0 = vec4((a_texcoord0 * basic.uv0_scale) + basic.uv0_offset, 0.0, 0.0);
        gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
    }`;


var fragment_shader =`$input v_uv0
    
    #include <filter/filter.sh>
    
    void main() {
    
        vec2 p = - 1.0 + 2.0 * v_uv0;
        float a = u_time * 40.0;
        float d, e, f, g = 1.0 / 40.0 ,h ,i ,r ,q;
    
        e = 400.0 * (p.x * 0.5 + 0.5);
        f = 400.0 * (p.y * 0.5 + 0.5);
        i = 200.0 + sin(e * g + a / 150.0) * 20.0;
        d = 200.0 + cos(f * g / 2.0) * 18.0 + cos(e * g) * 7.0;
        r = sqrt(pow(abs(i - e), 2.0) + pow(abs(d - f), 2.0));
        q = f / r;
        e = (r * cos(q)) - a / 2.0;
        f = (r * sin(q)) - a / 2.0;
        d = sin(e * g) * 176.0 + sin(e * g) * 164.0 + r;
        h = ((f + d) + a / 2.0) * g;
        i = cos(h + r * p.x / 1.3) * (e + e + a) + cos(q * g * 6.0) * (r + h / 3.0);
        h = sin(f * g) * 144.0 - sin(e * g) * 212.0 * p.x;
        h = (h + (f - e) * q + sin(r - (a + h) / 7.0) * 10.0 + i / 4.0) * g;
        i += cos(h * 2.3 * sin(a / 350.0 - q)) * 184.0 * sin(q - (r * 4.3 + a / 12.0) * g) + tan(r * g + h) * 184.0 * cos(r * g + h);
        i = mod(i / 5.6, 256.0) / 64.0;
        if (i < 0.0) i += 4.0;
        if (i >= 2.0) i = 4.0 - i;
        d = r / 350.0;
        d += sin(d * d * 8.0) * 0.52;
        f = (sin(a * g) + 1.0) / 2.0;
        gl_FragColor = vec4(vec3(f * i / 1.6, i / 2.0 + d / 13.0, i) * d * p.x + vec3(i / 1.3 + d / 8.0, i / 2.0 + d / 18.0, i) * d * (1.0 - p.x), 1.0);
    
    }`;

var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controller(viewer);

if (init) {
    var program = app.gfx.programs.create("custom");
    program.set_block(two.MaterialBlock.Solid);
    program.set_source(two.ShaderType.Vertex, vertex_shader);
    program.set_source(two.ShaderType.Fragment, fragment_shader);

    var material = app.gfx.materials.create("custom");
    var m = material;
    m.program = program;
    m.base.cull_mode = two.CullMode.None;
    
    //var model = app.gfx.shape(new two.Quad(1.0));
    var model = app.gfx.shape(new two.Rect(0.0, 0.0, 1.0, 1.0));

    var scene = viewer.scene;

    var node = scene.nodes().add(new two.Node3());
    var it = scene.items().add(new two.Item(node, model, 0, material));
}
