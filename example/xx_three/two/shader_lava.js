// shader_lava.js

// @author alteredq / http://alteredqualia.com/
// Film grain & scanlines shader

var film_vertex = `$input a_position, a_texcoord0
    $output v_uv0

    #include <filter.sh>

    void main() {
        v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;
        gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;


var film_fragment = `$input v_uv0

    #include <filter.sh>

    uniform vec4 u_film_p0;
    #define u_noise     u_film_p0.x
    #define u_intensity u_film_p0.y
    #define u_count     int(u_film_p0.z)
    #define u_grayscale bool(u_film_p0.w)
        
    void main() {

        vec3 source = texture2D(s_source_0, v_uv0).rgb;

        // noise
        float dx = rand(v_uv0 + u_time);
        vec3 color = source + source * clamp(0.1 + dx, 0.0, 1.0);

        // scanlines
        vec2 sc = vec2(sin(v_uv0.y * u_count), cos(v_uv0.y * u_count));
        color += source * vec3(sc.x, sc.y, sc.x) * u_intensity;

        // interpolate between source and result by intensity
        color = source + clamp(u_noise, 0.0, 1.0) * (color - source);

        // convert to grayscale if desired
        if(u_grayscale) {
            color = vec3_splat(color.r * 0.3 + color.g * 0.59 + color.b * 0.11);
        }

        gl_FragColor = vec4(color, 1.0);
    }`;

// @author alteredq / http://alteredqualia.com/

function pass_film(gfx, render, film) {

    var program = new two.ProgramVersion(gfx.programs.fetch('film'));

    var pass = render.next_pass('film', two.PassType.PostProcess);

    gfx.filter.uniform(pass, 'u_film_p0', new two.vec4(film.noise, film.scanlines, film.num_scanlines, film.grayscale));
    gfx.filter.source0(render.target.post.last());
    gfx.filter.quad(pass, render.target.post.swap(), program);

    var flip = render.next_pass('flip', two.PassType.PostProcess);
    gfx.copy.quad(flip, render.fbo, render.target.post.last());
}

var vertex_shader = `$input a_position, a_texcoord0
    $output v_position, v_uv0
    
    #include <common.sh>
    
    void main()
    {
        int material_index = int(u_state_material);
        BaseMaterial basic = read_base_material(material_index);
        
        v_uv0 = (a_texcoord0 * basic.uv0_scale) + basic.uv0_offset;
        vec4 view = mul(u_modelView, vec4(a_position.xyz, 1.0));
        v_position = mul(u_proj, view);
        gl_Position = v_position;
    }`;

var fragment_shader = `$input v_position, v_uv0
    
    #include <common.sh>
    

    #define u_fog_density u_user_p0.x
    #define u_fog_source u_user_p0.yzw
    
    void main()
    {
        vec2 uv = v_uv0;
        vec2 position = - 1.0 + 2.0 * uv;
    
        vec4 noise = texture2D(s_user0, uv);
        vec2 T1 = uv + vec2(1.5, - 1.5) * u_time * 0.02;
        vec2 T2 = uv + vec2(- 0.5, 2.0) * u_time * 0.01;
    
        T1.x += noise.x * 2.0;
        T1.y += noise.y * 2.0;
        T2.x -= noise.y * 0.2;
        T2.y += noise.z * 0.2;
    
        float p = texture2D(s_user0, T1 * 2.0).a;
    
        vec4 lava = texture2D(s_user1, T2 * 2.0);
        vec4 color = lava * (vec4(p, p, p, p) * 2.0) + (lava * lava - 0.1);
    
        if(color.r > 1.0) { color.bg += clamp(color.r - 2.0, 0.0, 100.0); }
        if(color.g > 1.0) { color.rb += color.g - 1.0; }
        if(color.b > 1.0) { color.rg += color.b - 1.0; }
    
        gl_FragColor = color;
    
    #if BGFX_SHADER_LANGUAGE_HLSL
    //	float depth = v_position.z;
        float depth = gl_FragCoord.z * gl_FragCoord.w;
    #else
    //	float depth = (v_position.z + v_position.w) * 0.5;
        float depth = gl_FragCoord.z / gl_FragCoord.w;
    #endif
        float fogFactor = exp2(-u_fog_density * u_fog_density * depth * depth * LOG2);
        fogFactor = 1.0 - clamp(fogFactor, 0.0, 1.0);
    
        gl_FragColor = mix(color, vec4(vec3(0.0, 0.0, 0.0), color.w), fogFactor);
    }`;

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controller(viewer);
viewer.viewport.autorender = false;

var scene = viewer.scene;

if (init) {
    var camera = viewer.camera;
    camera.fov = 35.0; camera.near = 1.0; camera.far = 3000.0;
    camera.eye.z = 4.0;

    var fog_density = 0.45;
    var fog_color = new two.Colour(0.0);

    var program = app.gfx.programs.create('lava'); //new two.Program('lava');
    program.set_block(two.MaterialBlock.Solid);
    program.set_block(two.MaterialBlock.User);
    program.set_source(two.ShaderType.Vertex, vertex_shader);
    program.set_source(two.ShaderType.Fragment, fragment_shader);

    var film = app.gfx.programs.create('film');
    film.set_source(two.ShaderType.Vertex, film_vertex);
    film.set_source(two.ShaderType.Fragment, film_fragment);
    
    var cloud = app.gfx.textures.file('lava/cloud.png');
    var lava = app.gfx.textures.file('lava/lavatile.jpg');

    var material = app.gfx.materials.create('lava');
    var m = material;
    m.program = program;
    m.base.uv0_scale = new two.vec2(3.0, 1.0);
    m.user.attr0 = new two.vec4(fog_density, fog_color.r, fog_color.g, fog_color.b);
    m.user.tex0 = cloud;
    m.user.tex1 = lava;
    
    // material.submit = submit;

    this.angles = new two.vec3(0.3, 0.0, 0.0);

    var size = 0.65;

    this.model = app.gfx.shape(new two.Torus(size, 0.3));

    this.node = scene.nodes().add(new two.Node3(new two.vec3(0.0), new two.quat(angles)));
    var it = scene.items().add(new two.Item(node, model, 0, material));
        
    this.film = {
        noise: 0.5,
        scanlines: 0.05,
        num_scanlines: 4096,
        grayscale: true
    };

}

var delta = 0.05; //5.0 * app.gfx.frame_time;

this.angles.y += 0.0125 * delta;
this.angles.x += 0.05 * delta;

this.node.apply(new two.vec3(0.0), new two.quat(this.angles));


function renderer(gfx, render, film) {
    
    two.begin_pbr_render(gfx, render);

    two.pass_clear(gfx, render);
    two.pass_solid(gfx, render);
    
    //pass_film(gfx, render, film);
    
    two.pass_flip(gfx, render);
}

var render = new two.Render(two.Shading.Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame);
app.gfx.renderer.gather(render);
app.gfx.renderer.begin(render);
renderer(app.gfx, render, this.film);
app.gfx.renderer.end(render);
