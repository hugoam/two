// effect_sobel.js

// @author alteredq / http://alteredqualia.com/
// Luminosity http://en.wikipedia.org/wiki/Luminosity

var luminosity_vertex = `$input a_position, a_texcoord0
    $output v_uv0

    #include <filter.sh>

    void main()
    {
    	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;
    	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;


var luminosity_fragment = `$input v_uv0

    #include <filter.sh>

    float linearToRelativeLuminance(const in vec3 color) {
    	vec3 weights = vec3(0.2126, 0.7152, 0.0722);
    	return dot(weights, color.rgb);
    }

    void main()
    {
        vec4 texel = texture2D(s_source_0, v_uv0);
        float l = linearToRelativeLuminance(texel.rgb);

        gl_FragColor = vec4(l, l, l, texel.w);
    }`;

// @author Mugen87 / https://github.com/Mugen87
// Sobel Edge Detection (see https://youtu.be/uihBwtPIBxM)

var sobel_vertex = `$input a_position, a_texcoord0
    $output v_uv0

    #include <filter.sh>

    void main()
    {
    	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;
    	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;

var sobel_fragment = `$input v_uv0

    #include <filter.sh>

    void main() {

        vec2 texel = u_pixel_size;

        // kernel definition (in glsl matrices are filled in column-major order)

        const mat3 Gx = mat3(-1, -2, -1, 0, 0, 0, 1, 2, 1); // x direction kernel
        const mat3 Gy = mat3(-1, 0, 1, -2, 0, 2, -1, 0, 1); // y direction kernel

        // fetch the 3x3 neighbourhood of a fragment

        // first column

        float tx0y0 = texture2D(s_source_0, v_uv0 + texel * vec2(-1, -1)).r;
        float tx0y1 = texture2D(s_source_0, v_uv0 + texel * vec2(-1,  0)).r;
        float tx0y2 = texture2D(s_source_0, v_uv0 + texel * vec2(-1,  1)).r;

        // second column

        float tx1y0 = texture2D(s_source_0, v_uv0 + texel * vec2(0, -1)).r;
        float tx1y1 = texture2D(s_source_0, v_uv0 + texel * vec2(0,  0)).r;
        float tx1y2 = texture2D(s_source_0, v_uv0 + texel * vec2(0,  1)).r;

        // third column

        float tx2y0 = texture2D(s_source_0, v_uv0 + texel * vec2(1, -1)).r;
        float tx2y1 = texture2D(s_source_0, v_uv0 + texel * vec2(1,  0)).r;
        float tx2y2 = texture2D(s_source_0, v_uv0 + texel * vec2(1,  1)).r;

        // gradient value in x direction

        float valueGx = Gx[0][0] * tx0y0 + Gx[1][0] * tx1y0 + Gx[2][0] * tx2y0 + 
            Gx[0][1] * tx0y1 + Gx[1][1] * tx1y1 + Gx[2][1] * tx2y1 + 
            Gx[0][2] * tx0y2 + Gx[1][2] * tx1y2 + Gx[2][2] * tx2y2; 

        // gradient value in y direction

        float valueGy = Gy[0][0] * tx0y0 + Gy[1][0] * tx1y0 + Gy[2][0] * tx2y0 + 
            Gy[0][1] * tx0y1 + Gy[1][1] * tx1y1 + Gy[2][1] * tx2y1 + 
            Gy[0][2] * tx0y2 + Gy[1][2] * tx1y2 + Gy[2][2] * tx2y2; 

        // magnitute of the total gradient

        float G = sqrt((valueGx * valueGx) + (valueGy * valueGy));

        gl_FragColor = vec4(vec3_splat(G), 1);

    }`;

function pass_grayscale(gfx, render) {
    
    // color to grayscale conversion

    var program = new two.ProgramVersion(gfx.programs.fetch('sobel_lum'));

    var pass = render.next_pass('sobel_lum', two.PassType.PostProcess);
    gfx.filter.source0(render.target.diffuse);
    gfx.filter.quad(pass, render.target.post.swap(), program);
}

function pass_sobel(gfx, render) {
    // you might want to use a gaussian blur filter before
    // the next pass to improve the result of the Sobel operator

    // Sobel operator

    var program = new two.ProgramVersion(gfx.programs.fetch('sobel'));

    var pass = render.next_pass('sobel', two.PassType.PostProcess);
    gfx.filter.source0(render.target.post.last());
    gfx.filter.quad(pass, render.target.post.swap(), program);

    var flip = render.next_pass('flip', two.PassType.PostProcess);
    gfx.copy.quad(flip, render.fbo, render.target.post.last());
}

var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controls(viewer);
viewer.viewport.autorender = false;

var scene = viewer.scene;
var camera = viewer.camera;

if(init) {
    camera.fov = 70.0; camera.near = 1.0; camera.far = 1000.0;
    camera.eye = new two.vec3(0.0, 10.0, 25.0);

    this.enabled = true;

    var lum = app.gfx.programs.create('sobel_lum');
    lum.set_source(two.ShaderType.Vertex, luminosity_vertex);
    lum.set_source(two.ShaderType.Fragment, luminosity_fragment);

    var sobel = app.gfx.programs.create('sobel');
    sobel.set_source(two.ShaderType.Vertex, sobel_vertex);
    sobel.set_source(two.ShaderType.Fragment, sobel_fragment);

    var symbol = new two.Symbol(new two.Colour(1.0)); symbol.subdiv = new two.uvec2(256, 32);
    var geometry = app.gfx.shape(new two.TorusKnot(8.0, 3.0), symbol);

    var phong = app.gfx.programs.fetch('pbr/phong');

    var material = app.gfx.materials.create('sobel'); var m = material;
        m.program = phong;
        m.phong.diffuse.value = two.rgb(0xffff00);

    var n = scene.nodes().add(new two.Node3());
    scene.items().add(new two.Item(n, geometry, 0, material));

    scene.env.radiance.ambient = two.rgb(0xcccccc); //0.4;
    
    var ln = scene.nodes().add(new two.Node3());
    var l = scene.lights().add(new two.Light(ln, two.LightType.Point, false, two.rgb(0xffffff), 0.8, 0.0));
    this.light = ln;
}

this.light.apply(camera.eye);

//gui.add(params, 'enable');

function renderer(gfx, render, enabled) {
    
    two.begin_pbr_render(gfx, render);

    two.pass_clear(gfx, render);
    two.pass_opaque(gfx, render);

    if(enabled) {
        pass_grayscale(gfx, render);
        pass_sobel(gfx, render);
    }
}

var render = new two.Render(two.Shading.Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame);
app.gfx.renderer.gather(render);
app.gfx.renderer.begin(render);

renderer(app.gfx, render, this.enabled);

app.gfx.renderer.end(render);
