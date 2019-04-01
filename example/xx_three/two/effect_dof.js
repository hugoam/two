// effect_dof.js

var bokeh_vertex = `$input a_position, a_texcoord0
    $output v_uv0

    #include <filter.sh>

    void main() {
        v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;
        gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;

var bokeh_fragment = `$input v_uv0

    #include <filter.sh>

    uniform vec4 u_bokeh_p0;
    #define u_focus u_bokeh_p0.x
    #define u_aperture u_bokeh_p0.y // aperture - bigger values for shallower depth of field
    #define u_maxblur u_bokeh_p0.z  // max blur amount

    float getViewZ(float depth) {
        return perspectiveDepthToViewZ(depth);
    }

    void main() {

    vec2 aspect = vec2(1.0, u_aspect);

    float depth = texture2D(s_source_depth, v_uv0).x;
    float viewZ = getViewZ(depth);

    float factor = (u_focus + viewZ);  // viewZ is <= 0, so this is a difference equation

    vec2 dofblur = vec2_splat(clamp(factor * u_aperture, -u_maxblur, u_maxblur));

    vec2 dofblur9 = dofblur * 0.9;
    vec2 dofblur7 = dofblur * 0.7;
    vec2 dofblur4 = dofblur * 0.4;

    vec4 col = vec4_splat(0.0);

    col += texture2D(s_source_0, v_uv0);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.0,   0.4) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.15,  0.37) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.29,  0.29) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.37,  0.15) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.40,  0.0) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.37, -0.15) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.29, -0.29) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.15, -0.37) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.0,  -0.4) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.15,  0.37) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.29,  0.29) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.37,  0.15) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.4,   0.0) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.37, -0.15) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.29, -0.29) * aspect) * dofblur);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.15, -0.37) * aspect) * dofblur);

    col += texture2D(s_source_0, v_uv0 + (vec2(0.15,  0.37) * aspect) * dofblur9);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.37,  0.15) * aspect) * dofblur9);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.37, -0.15) * aspect) * dofblur9);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.15, -0.37) * aspect) * dofblur9);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.15,  0.37) * aspect) * dofblur9);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.37,  0.15) * aspect) * dofblur9);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.37, -0.15) * aspect) * dofblur9);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.15, -0.37) * aspect) * dofblur9);

    col += texture2D(s_source_0, v_uv0 + (vec2(0.29,  0.29) * aspect) * dofblur7);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.40,  0.0) * aspect) * dofblur7);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.29, -0.29) * aspect) * dofblur7);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.0,  -0.4) * aspect) * dofblur7);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.29,  0.29) * aspect) * dofblur7);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.4,   0.0) * aspect) * dofblur7);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.29, -0.29) * aspect) * dofblur7);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.0,   0.4) * aspect) * dofblur7);

    col += texture2D(s_source_0, v_uv0 + (vec2(0.29,  0.29) * aspect) * dofblur4);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.4,   0.0) * aspect) * dofblur4);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.29, -0.29) * aspect) * dofblur4);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.0,  -0.4) * aspect) * dofblur4);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.29,  0.29) * aspect) * dofblur4);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.4,   0.0) * aspect) * dofblur4);
    col += texture2D(s_source_0, v_uv0 + (vec2(-0.29, -0.29) * aspect) * dofblur4);
    col += texture2D(s_source_0, v_uv0 + (vec2(0.0,   0.4) * aspect) * dofblur4);

    gl_FragColor = vec4(col.rgb / 41.0, 1.0);
    //gl_FragColor = vec4(vec3_splat(-viewZ / u_z_far), 1.0);
    //gl_FragColor = vec4(vec3_splat(1.0 + viewZ / u_z_far), 1.0);

    }`;

function pass_bokeh(gfx, render, bokeh) {

    var program = new two.ProgramVersion(gfx.programs.fetch('bokeh'));

    var pass = render.next_pass('bokeh', two.PassType.PostProcess);

    gfx.filter.uniform(pass, 'u_bokeh_p0', new two.vec4(bokeh.focus, bokeh.aperture * 0.00001, bokeh.maxblur, 0.0));

    gfx.filter.source0(render.target.diffuse);
    gfx.filter.sourcedepth(render.target.depth);

    gfx.filter.quad(pass, render.target.post.swap(), program);

    var flip = render.next_pass('flip', two.PassType.PostProcess);
    gfx.copy.quad(flip, render.target_fbo, render.target.post.last());
}

var enabled = true;

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controller(viewer);
if (enabled) {
    viewer.viewport.active = false;
}

var scene = viewer.scene;

var bokeh = {
    focus : 500.0,
    aperture : 5.0,
    maxblur : 1.0
};

function renderer(gfx, render) {
    
    two.begin_pbr_render(gfx, render);

    two.pass_clear(gfx, render);
    two.pass_opaque(gfx, render);
    pass_bokeh(gfx, render, bokeh);
}

if (init) {
    this.mouse = new two.vec2(0.0);

    var camera = viewer.camera;
    camera.fov = 70.0; camera.near = 1.0; camera.far = 3000.0;
    camera.eye.z = 200.0;

    var basic = app.gfx.programs.fetch('pbr/basic');
    
    var texcube = app.gfx.textures.file('radiance/tiber_1_1k.hdr');
    //var texcube = app.gfx.textures.file('cube/royal.jpg.cube');
    scene.env.radiance.texture = texcube;
    //scene.env.radiance.energy = 1.0;

    var xgrid = 14;
    var ygrid = 9;
    var zgrid = 14;
    this.nobjects = xgrid * ygrid * zgrid;

    this.materials = [];

    for(var i = 0; i < this.nobjects; ++i)
    {
        var name = 'object' + i.toString();
        var material = app.gfx.materials.create(name); var m = material;
            m.program = basic;
            m.pbr.albedo.value = two.rgb(0xff1100);
            //m.pbr.metallic.value = 1.0;

        this.materials.push(material);
    }

    var geometry = app.gfx.shape(new two.Sphere(1.0));
    var count = 0;
    for(var i = 0; i < xgrid; i++)
        for(var j = 0; j < ygrid; j++)
            for(var k = 0; k < zgrid; k++)
            {
                var x = 200 * (i - xgrid / 2);
                var y = 200 * (j - ygrid / 2);
                var z = 200 * (k - zgrid / 2);
                var n = scene.nodes().add(new two.Node3(new two.vec3(x, y, z), new two.quat(new two.vec3(0.0)), new two.vec3(60.0)));
                scene.items().add(new two.Item(n, geometry, 0, this.materials[count]));
                count++;
            }

    var program = app.gfx.programs.create('bokeh');
    program.set_source(two.ShaderType.Vertex, bokeh_vertex);
    program.set_source(two.ShaderType.Fragment, bokeh_fragment);
}

var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved);
if(event.valid())
{
    this.mouse.x = event.relative.x - viewer.frame.size.x / 2.0;
    this.mouse.y = event.relative.y - viewer.frame.size.y / 2.0;
}

//var time = app.gfx.time * 0.05;

var camera = viewer.camera;
camera.eye.x += (this.mouse.x - camera.eye.x) * 0.036;
camera.eye.y += (-(this.mouse.y) - camera.eye.y) * 0.036;
//camera.target = scene.position;

for(var i = 0; i < this.nobjects; i++)
{
    var h = (360.0 * (i / this.nobjects + time * 0.1) % 360.0) / 360.0;
    this.materials[i].solid.colour.value = two.hsl(h, 1.0, 0.5);
    this.materials[i].pbr.albedo.value = two.hsl(h, 1.0, 0.5);
}

//if(var dock = two.ui.dockitem(dockbar, 'Game', { 1U }))
//{
//	var sheet = two.ui.sheet(*dock);
//
//	var controls = two.ui.stack(sheet);
//	two.ui.slider_field_float(controls, 'focus',    { bokeh.focus,    { 10.0, 3000.0, 10.0 } });
//	two.ui.slider_field_float(controls, 'aperture', { bokeh.aperture, { 0.0, 10.0, 0.1 } });
//	two.ui.slider_field_float(controls, 'maxblur',  { bokeh.maxblur,  { 0.0, 3.f, 0.025 } });
//}

if (enabled) {
    var render = new two.Render(two.Shading.Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame);
    app.gfx.renderer.gather(render);
    app.gfx.renderer.begin(render);
    renderer(app.gfx, render);
    app.gfx.renderer.end(render);
}
