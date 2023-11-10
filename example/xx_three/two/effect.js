// effect.js

// @author alteredq / http://alteredqualia.com/
// Dot screen shader

var dotscreen_vertex = `$input a_position, a_texcoord0
    $output v_uv0
    
    #include <filter.sh>
    
    void main() {
    	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;
    	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;

var dotscreen_fragment = `$input v_uv0
    
    #include <filter.sh>
    
    uniform vec4 u_dotscreen_p0;
    #define u_center u_dotscreen_p0.xy
    #define u_angle  u_dotscreen_p0.z
    #define u_scale  u_dotscreen_p0.w
    
    uniform vec4 u_dotscreen_p1;
    #define u_size u_dotscreen_p1.xy
    
    #define s_diffuse s_source_0
    
    float pattern(vec2 uv) {
        float s = sin(u_angle), c = cos(u_angle);

        vec2 tex = uv * u_size - u_center;
        vec2 p = vec2(c * tex.x - s * tex.y, s * tex.x + c * tex.y) * u_scale;

        return (sin(p.x) * sin(p.y)) * 4.0;
    }

    void main() {

        vec4 color = texture2D(s_diffuse, v_uv0);

        float average = (color.r + color.g + color.b) / 3.0;

        gl_FragColor = vec4(vec3_splat(average * 10.0 - 5.0 + pattern(v_uv0)), color.a);

    }`;

// @author felixturner / http://airtight.cc/
// RGB Shift Shader

var rgbshift_vertex = `$input a_position, a_texcoord0
    $output v_uv0
    
    #include <filter.sh>
    
    void main() {
    	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;
    	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;
	
var rgbshift_fragment =  `$input v_uv0
    
    #include <filter.sh>
    
    uniform vec4 u_rgbshift_p0;
    #define u_amount u_rgbshift_p0.xy
    #define u_angle  u_rgbshift_p0.z
    
    #define s_diffuse s_source_0
    
    void main() {

        vec2 offset = u_amount * vec2(cos(u_angle), sin(u_angle));
        vec4 cr = texture2D(s_diffuse, v_uv0 + offset);
        vec4 cga = texture2D(s_diffuse, v_uv0);
        vec4 cb = texture2D(s_diffuse, v_uv0 - offset);
        gl_FragColor = vec4(cr.r, cga.g, cb.b, cga.a);

    }`;

function pass_dotscreen(gfx, render, p) {
    
    var program = new two.ProgramVersion(app.gfx.programs.fetch('dotscreen'));

    var pass = render.next_pass('dotscreen', two.PassType.PostProcess);

    gfx.filter.uniform(pass, 'u_dotscreen_p0', new two.vec4(p.center.x, p.center.y, p.angle, p.scale));
    gfx.filter.uniform(pass, 'u_dotscreen_p1', new two.vec4(p.size.x, p.size.y, 0.0, 0.0));

    gfx.filter.source0(render.target.diffuse);

    gfx.filter.quad(pass, render.target.post.swap(), program);
}

function pass_rgbshift(gfx, render, p) {

    var program = new two.ProgramVersion(app.gfx.programs.fetch('rgbshift'));

    var pass = render.next_pass('rgbshift', two.PassType.PostProcess);

    gfx.filter.uniform(pass, 'u_rgbshift_p0', new two.vec4(p.amount, p.angle, 0.0, 0.0));

    //gfx.filter.source0(render.target.diffuse);
    gfx.filter.source0(render.target.post.last());

    gfx.filter.quad(pass, render.target.post.swap(), program);

    var flip = render.next_pass('flip', two.PassType.PostProcess);
    gfx.copy.quad(flip, render.fbo, render.target.post.last());
}

var viewer = two.ui.scene_viewer(panel);
viewer.viewport.autorender = false;

var scene = viewer.scene;

if(init) {
    var camera = viewer.camera;
    camera.fov = 70.0; camera.near = 1.0; camera.far = 1000.0;
    camera.eye.z = 400.0;
    
	var dotscreen = app.gfx.programs.create('dotscreen');
	dotscreen.set_source(two.ShaderType.Vertex, dotscreen_vertex);
	dotscreen.set_source(two.ShaderType.Fragment, dotscreen_fragment);

    var rgbshift = app.gfx.programs.create('rgbshift');
    rgbshift.set_source(two.ShaderType.Vertex, rgbshift_vertex);
    rgbshift.set_source(two.ShaderType.Fragment, rgbshift_fragment);

    this.dotscreen = { size: new two.vec2(256.0), center: new two.vec2(0.5), angle: 1.57, scale: 4.0 };
    this.rgbshift = { amount: 0.0015, angle: 0.0 };

    var env = scene.env;
    
    env.radiance.ambient = two.rgb(0x222222);

    env.fog.enabled = true;
    env.fog.colour = two.rgb(0x000000);
    env.fog.depth_begin = 1.0;
    env.fog.depth_end = 1000.0;

    var object = scene.nodes().add(new two.Node3());
    this.node = object;

    var symbol = new two.Symbol(new two.Colour(1.0)); symbol.subdiv = new two.uvec2(4);
    var geometry = app.gfx.shape(new two.Sphere(1.0), symbol);

    var pbr = app.gfx.programs.fetch('pbr/pbr');

    var material = app.gfx.materials.create('effect'); var m = material;
        m.program = pbr;
        m.base.flat_shaded = true;
        m.pbr.albedo.value = two.rgb(0xffffff);

    this.nodes = [];
    for(var i = 0; i < 100; i++) {
        
        var d = Math.random() * 400.0;
        var p = new two.vec3((Math.random() - 0.5) * d, (Math.random() - 0.5) * d, (Math.random() - 0.5) * d);
        var a = new two.vec3(Math.random() * 2.0, Math.random() * 2.0, Math.random() * 2.0);
        var s = new two.vec3(Math.random() * 50.0);

        var n = scene.nodes().add(new two.Node3(p, quat(a), s));
        scene.items().add(new two.Item(n, geometry, 0, material));
        this.nodes.push({ p: p, r: new two.quat(a), s: s, node: n });
    }
    
    //scene.add(new THREE.AmbientLight(0x222222));

    var dir = two.look_dir(new two.vec3(-1.0));
    var ln = scene.nodes().add(new two.Node3(new two.vec3(0.0), dir));
    var l = scene.lights().add(new two.Light(ln, two.LightType.Direct, false, two.rgb(0xffffff)));

    this.angles = new two.vec3(0.0);
}

this.angles.x += 0.005;
this.angles.y += 0.01;

this.node.apply(new two.vec3(0.0), new two.quat(this.angles));

for(var i = 0; i < this.nodes.length; ++i) {
    var n = this.nodes[i];
    n.node.derive(this.node, n.p, n.r, n.s);
}

function renderer(gfx, render, dotscreen, rgbshift) {
    
    two.begin_pbr_render(gfx, render);

    two.pass_clear(gfx, render);
    two.pass_opaque(gfx, render);
    pass_dotscreen(gfx, render, dotscreen);
    pass_rgbshift(gfx, render, rgbshift);
}

var render = new two.Render(two.Shading.Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame);
app.gfx.renderer.gather(render);
app.gfx.renderer.begin(render);

renderer(app.gfx, render, this.dotscreen, this.rgbshift);

app.gfx.renderer.end(render);
