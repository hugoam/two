// effect_halftone.js

// @author meatbags / xavierburrow.com, github/meatbags
// RGB Halftone shader for three.js.

var halftone_vertex = `$input a_position, a_texcoord0
    $output v_uv0

    #include <filter.sh>

    void main()
    {
    	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;
    	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;

var halftone_fragment = `$input v_uv0

    #include <filter.sh>

    #define SQRT2_MINUS_ONE 0.41421356
    #define SQRT2_HALF_MINUS_ONE 0.20710678

    #define SHAPE_DOT 1
    #define SHAPE_ELLIPSE 2
    #define SHAPE_LINE 3
    #define SHAPE_SQUARE 4

    #define BLENDING_LINEAR 1
    #define BLENDING_MULTIPLY 2
    #define BLENDING_ADD 3
    #define BLENDING_LIGHTER 4
    #define BLENDING_DARKER 5

    uniform vec4 u_halftone_p0;
    #define u_radius u_halftone_p0.x
    #define u_rotateR u_halftone_p0.y
    #define u_rotateG u_halftone_p0.z
    #define u_rotateB u_halftone_p0.w

    uniform vec4 u_halftone_p1;
    #define u_shape int(u_halftone_p1.x)
    #define u_scatter u_halftone_p1.y
    #define u_blending u_halftone_p1.z
    #define u_blend_mode int(u_halftone_p1.w)

    uniform vec4 u_halftone_p2;
    #define u_disable bool(u_halftone_p2.x)
    #define u_greyscale bool(u_halftone_p2.y)

    CONST(int) samples = 8;

    float blend(float a, float b, float t) {
        // linear blend
        return a * (1.0 - t) + b * t;
    }

    float hypot(float x, float y) {
        // vector magnitude
        return sqrt(x * x + y * y);
    }

    float rand2(vec2 seed){
        // get pseudo-random number
        return fract(sin(dot(seed.xy, vec2(12.9898, 78.233))) * 43758.5453);
    }

    float distanceToDotRadius(float channel, vec2 coord, vec2 normal, vec2 p, float angle, float rad_max) {

        // apply shape-specific transforms
        float dist = hypot(coord.x - p.x, coord.y - p.y);
        float rad = channel;

        if (u_shape == SHAPE_DOT) {
            rad = pow(abs(rad), 1.125) * rad_max;
        } else if (u_shape == SHAPE_ELLIPSE) {
            rad = pow(abs(rad), 1.125) * rad_max;
            if (dist != 0.0) {
                float dot_p = abs((p.x - coord.x) / dist * normal.x + (p.y - coord.y) / dist * normal.y);
                dist = (dist * (1.0 - SQRT2_HALF_MINUS_ONE)) + dot_p * dist * SQRT2_MINUS_ONE;
            }
        } else if (u_shape == SHAPE_LINE) {
            rad = pow(abs(rad), 1.5) * rad_max;
            float dot_p = (p.x - coord.x) * normal.x + (p.y - coord.y) * normal.y;
            dist = hypot(normal.x * dot_p, normal.y * dot_p);
        } else if (u_shape == SHAPE_SQUARE) {
            float theta = atan2(p.y - coord.y, p.x - coord.x) - angle;
            float sin_t = abs(sin(theta));
            float cos_t = abs(cos(theta));
            rad = pow(abs(rad), 1.4);
            rad = rad_max * (rad + ((sin_t > cos_t) ? rad - sin_t * rad : rad - cos_t * rad));
        }

        return rad - dist;
    }

    struct Cell {
        // grid sample positions
        vec2 normal;
        vec2 p1;
        vec2 p2;
        vec2 p3;
        vec2 p4;
        float samp2;
        float samp1;
        float samp3;
        float samp4;
    };

    vec4 getSample(vec2 uv) {
        // multi-sampled point
        vec4 tex = texture2D(s_source_0, uv * u_pixel_size);
        float base = rand2(vec2(floor(uv.x), floor(uv.y))) * PI2;
        float step = PI2 / float(samples);
        float dist = u_radius * 0.66;

        for (int i = 0; i < samples; ++i) {
            float r = base + step * float(i);
            vec2 coord = uv + vec2(cos(r) * dist, sin(r) * dist);
            tex += texture2D(s_source_0, coord * u_pixel_size);
        }

        tex /= float(samples) + 1.0;
        return tex;
    }

    float getDotColour(Cell c, vec2 p, int channel, float angle, float aa) {

        // get colour for given point
        float dist_c_1, dist_c_2, dist_c_3, dist_c_4, res;

        if (channel == 0) {
            c.samp1 = getSample(c.p1).r;
            c.samp2 = getSample(c.p2).r;
            c.samp3 = getSample(c.p3).r;
            c.samp4 = getSample(c.p4).r;
        } else if (channel == 1) {
            c.samp1 = getSample(c.p1).g;
            c.samp2 = getSample(c.p2).g;
            c.samp3 = getSample(c.p3).g;
            c.samp4 = getSample(c.p4).g;
        } else {
            c.samp1 = getSample(c.p1).b;
            c.samp3 = getSample(c.p3).b;
            c.samp2 = getSample(c.p2).b;
            c.samp4 = getSample(c.p4).b;
        }

        dist_c_1 = distanceToDotRadius(c.samp1, c.p1, c.normal, p, angle, u_radius);
        dist_c_2 = distanceToDotRadius(c.samp2, c.p2, c.normal, p, angle, u_radius);
        dist_c_3 = distanceToDotRadius(c.samp3, c.p3, c.normal, p, angle, u_radius);
        dist_c_4 = distanceToDotRadius(c.samp4, c.p4, c.normal, p, angle, u_radius);
        res = (dist_c_1 > 0.0) ? clamp(dist_c_1 / aa, 0.0, 1.0) : 0.0;
        res += (dist_c_2 > 0.0) ? clamp(dist_c_2 / aa, 0.0, 1.0) : 0.0;
        res += (dist_c_3 > 0.0) ? clamp(dist_c_3 / aa, 0.0, 1.0) : 0.0;
        res += (dist_c_4 > 0.0) ? clamp(dist_c_4 / aa, 0.0, 1.0) : 0.0;
        res = clamp(res, 0.0, 1.0);

        return res;
    }

    Cell getReferenceCell(vec2 p, vec2 origin, float grid_angle, float step) {

        // get containing cell
        Cell c;

        // calc grid
        vec2 n = vec2(cos(grid_angle), sin(grid_angle));
        float threshold = step * 0.5;
        float dot_normal = n.x * (p.x - origin.x) + n.y * (p.y - origin.y);
        float dot_line = -n.y * (p.x - origin.x) + n.x * (p.y - origin.y);
        vec2 offset = vec2(n.x * dot_normal, n.y * dot_normal);
        float offset_normal = mod(hypot(offset.x, offset.y), step);
        float normal_dir = (dot_normal < 0.0) ? 1.0 : -1.0;
        float normal_scale = ((offset_normal < threshold) ? -offset_normal : step - offset_normal) * normal_dir;
        float offset_line = mod(hypot((p.x - offset.x) - origin.x, (p.y - offset.y) - origin.y), step);
        float line_dir = (dot_line < 0.0) ? 1.0 : -1.0;
        float line_scale = ((offset_line < threshold) ? -offset_line : step - offset_line) * line_dir;

        // get closest corner
        c.normal = n;
        c.p1.x = p.x - n.x * normal_scale + n.y * line_scale;
        c.p1.y = p.y - n.y * normal_scale - n.x * line_scale;

        // scatter
        if (u_scatter != 0.0) {

            float off_mag = u_scatter * threshold * 0.5;
            float off_angle = rand2(vec2(floor(c.p1.x), floor(c.p1.y))) * PI2;
            c.p1.x += cos(off_angle) * off_mag;
            c.p1.y += sin(off_angle) * off_mag;
        }

        // find corners
        float normal_step = normal_dir * ((offset_normal < threshold) ? step : -step);
        float line_step = line_dir * ((offset_line < threshold) ? step : -step);
        c.p2.x = c.p1.x - n.x * normal_step;
        c.p2.y = c.p1.y - n.y * normal_step;
        c.p3.x = c.p1.x + n.y * line_step;
        c.p3.y = c.p1.y - n.x * line_step;
        c.p4.x = c.p1.x - n.x * normal_step + n.y * line_step;
        c.p4.y = c.p1.y - n.y * normal_step - n.x * line_step;

        return c;
    }

    float blendColour(float a, float b, float t) {

        // blend colours
        if (u_blend_mode == BLENDING_LINEAR) {
            return blend(a, b, 1.0 - t);
        } else if (u_blend_mode == BLENDING_ADD) {
            return blend(a, min(1.0, a + b), t);
        } else if (u_blend_mode == BLENDING_MULTIPLY) {
            return blend(a, max(0.0, a * b), t);
        } else if (u_blend_mode == BLENDING_LIGHTER) {
            return blend(a, max(a, b), t);
        } else if (u_blend_mode == BLENDING_DARKER) {
            return blend(a, min(a, b), t);
        } else {
            return blend(a, b, 1.0 - t);
        }
    }

    void main() {

        if (!u_disable) {
            // setup
            vec2 p = v_uv0 * u_screen_size;
            vec2 origin = vec2(0, 0);
            float aa = (u_radius < 2.5) ? u_radius * 0.5 : 1.25;

            // get channel samples
            Cell cell_r = getReferenceCell(p, origin, u_rotateR, u_radius);
            Cell cell_g = getReferenceCell(p, origin, u_rotateG, u_radius);
            Cell cell_b = getReferenceCell(p, origin, u_rotateB, u_radius);
            float r = getDotColour(cell_r, p, 0, u_rotateR, aa);
            float g = getDotColour(cell_g, p, 1, u_rotateG, aa);
            float b = getDotColour(cell_b, p, 2, u_rotateB, aa);

            // blend with original
            vec4 colour = texture2D(s_source_0, v_uv0);
            r = blendColour(r, colour.r, u_blending);
            g = blendColour(g, colour.g, u_blending);
            b = blendColour(b, colour.b, u_blending);

            if (u_greyscale) {
                r = g = b = (r + b + g) / 3.0;
            }

            gl_FragColor = vec4(r, g, b, 1.0);

        } else {

            gl_FragColor = texture2D(s_source_0, v_uv0);

        }

    }`;

// @author meatbags / xavierburrow.com, github/meatbags
// RGB Halftone pass for three.js effects composer. Requires THREE.HalftoneShader.

function pass_halftone(gfx, render, halftone) {
    
    var program = new two.ProgramVersion(gfx.programs.fetch('halftone'));

    var pass = render.next_pass('halftone', two.PassType.PostProcess);

    gfx.filter.uniform(pass, 'u_halftone_p0', new two.vec4(halftone.radius, halftone.rotate.r, halftone.rotate.g, halftone.rotate.b));
    gfx.filter.uniform(pass, 'u_halftone_p1', new two.vec4(halftone.shape, halftone.scatter, halftone.blending, halftone.blend_mode));
    gfx.filter.uniform(pass, 'u_halftone_p2', new two.vec4(halftone.disable, halftone.grayscale, 0.0, 0.0));

    gfx.filter.source0(render.target.diffuse);

    gfx.filter.quad(pass, render.target.post.swap(), program);

    var flip = render.next_pass('flip', two.PassType.PostProcess);
    gfx.copy.quad(flip, render.fbo, render.target.post.last());
}

var basic_vertex = `$input a_position, a_normal, a_texcoord0
    $output v_normal, v_uv0

    #include <common.sh>

    void main()
    {
        v_uv0 = a_texcoord0;
        v_normal = vec3(a_normal);
        gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;

var basic_fragment = `$input v_normal, v_uv0

    #include <common.sh>

    void main()
    {
        vec4 c = vec4(abs(v_normal) + vec3(v_uv0, 0.0), 0.0);
        gl_FragColor = c;
    }`;

var HalftoneShape = {};
HalftoneShape.Dot = 1;
HalftoneShape.Ellipse = 2;
HalftoneShape.Line = 3;
HalftoneShape.Square = 4;

var HalftoneBlend = {};
HalftoneBlend.Linear = 1;
HalftoneBlend.Multiply = 2;
HalftoneBlend.Add = 3;
HalftoneBlend.Lighter = 4;
HalftoneBlend.Darker = 5;

var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controls(viewer);
viewer.viewport.autorender = false;

var rotationSpeed = Math.PI / 64.0;

var scene = viewer.scene;

if(init) {
    var camera = viewer.camera;
    camera.fov = 75.0; camera.near = 1.0; camera.far = 1000.0;
    camera.eye.z = 12.0;

    this.halftone = {
        shape: HalftoneShape.Dot,
        blend_mode: HalftoneBlend.Linear,
        radius: 4.0,
        rotate: new two.vec3(Math.PI / 12.0 * 1.0, Math.PI / 12.0 * 2.0, Math.PI / 12.0 * 3.0),
        scatter: 0.0,
        blending: 1.0,
        grayscale: false,
        disable: false,
    };

    viewer.viewport.clear_colour = two.rgb(0x444444);
    scene.env.background.colour = two.rgb(0x444444);

    var program = app.gfx.programs.create('halftone');
    program.set_source(two.ShaderType.Vertex, halftone_vertex);
    program.set_source(two.ShaderType.Fragment, halftone_fragment);

    var quad = app.gfx.shape(new two.Cube(new two.vec3(100.0, 1.0, 100.0)));
    var cube = app.gfx.shape(new two.Cube(new two.vec3(1.0)));

    var group = scene.nodes().add(new two.Node3());
    this.node = group;

    var zeroq = new two.quat(new two.vec3(0.0));
    
    var ln = scene.nodes().add(new two.Node3(new two.vec3(0.0, 2.0, 0.0), zeroq));
    var l = scene.lights().add(new two.Light(ln, two.LightType.Point, false, two.rgb(0xffffff), 1.0, 50.0)); // 2

    var fn = scene.nodes().add(new two.Node3(new two.vec3(0.0, -10.0, 0.0), zeroq));
    var g = scene.items().add(new two.Item(fn, quad)); // new THREE.MeshPhongMaterial({}));
    
    var basic = app.gfx.programs.create('halftonebasic');
    basic.set_pass(two.PassType.Opaque);
    basic.set_source(two.ShaderType.Vertex, basic_vertex);
    basic.set_source(two.ShaderType.Fragment, basic_fragment);

    var mat = app.gfx.materials.create('halftonebasic'); var m = mat;
        m.program = basic;

    this.nodes = [];
    for (var i = 0; i < 50; ++i) {
        
        // fill scene with coloured cubes
        var p = new two.vec3(Math.random() * 16.0 - 8.0, Math.random() * 16.0 - 8.0, Math.random() * 16.0 - 8.0);
        var a = new two.vec3(Math.random() * 2 * Math.PI, Math.random() * 2 * Math.PI, Math.random() * 2 * Math.PI);

        var n = scene.nodes().add(new two.Node3(p, new two.quat(a)));
        var g = scene.items().add(new two.Item(n, cube, 0, mat));
        this.nodes.push({ p: p, r: new two.quat(a), node: n });
    }
    
    this.angles = new two.vec3(0.0);
}


var delta = app.gfx.frame_time;
this.angles.y += delta * rotationSpeed;

this.node.apply(new two.vec3(0.0), new two.quat(this.angles));

for(var i = 0; i < this.nodes.length; ++i) {
    var n = this.nodes[i];
    n.node.derive(this.node, n.p, n.r);
}

function renderer(gfx, render, halftone) {
    
    two.begin_pbr_render(gfx, render);

    two.pass_clear(gfx, render);
    two.pass_opaque(gfx, render);
    pass_halftone(gfx, render, halftone);
}

var render = new two.Render(two.Shading.Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame);
app.gfx.renderer.gather(render);
app.gfx.renderer.begin(render);

renderer(app.gfx, render, this.halftone);

app.gfx.renderer.end(render);

