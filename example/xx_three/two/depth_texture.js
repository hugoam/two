// depth_texture.js

var vertex_shader = `$input a_position, a_texcoord0
    $output v_uv0
    
    #include <filter.sh>
    
    void main() {
    	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;
    	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;

var fragment_shader = `$input v_uv0
    
    #include <filter.sh>
    
    float readDepth(sampler2D depthSampler, vec2 coord)
    {
    	float depth = texture2D(depthSampler, coord).x;
    	float viewZ = perspectiveDepthToViewZ(depth);
    	return viewZToOrthographicDepth(viewZ);
    //	return linearize_depth(depth);
    }
    
    void main() {
    //	vec3 diffuse = texture2D(s_source_0, v_uv0).rgb;
    	float depth = readDepth(s_source_depth, v_uv0);
    //	float depth = texture2D(s_source_depth, v_uv0).x;
    
    	gl_FragColor = vec4(1.0 - vec3_splat(depth), 1.0);
    }`;

    
function pass_todepth(gfx, render) {
    
    var program = gfx.programs.fetch('todepth');

    var target = render.target;

    var pass = render.next_pass('todepth', two.PassType.PostProcess);

    gfx.filter.sourcedepth(render.target.depth);

    gfx.filter.quad(pass, target.post.swap(), program);

    var flip = render.next_pass('flip', two.PassType.PostProcess);
    gfx.copy.quad(flip, render.fbo, target.post.last());
}


var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controls(viewer);
//controls.dampingFactor = 0.25;
//controls.rotateSpeed = 0.35;

viewer.viewport.active = false;

var scene = viewer.scene;

if (init) {
    var camera = viewer.camera;
    camera.fov = 70.0; camera.near = 0.01; camera.far = 50.0;
    camera.eye.z = 4.0;

    var geometry = app.gfx.shape(new two.TorusKnot(1.0, 0.3));

    var program = app.gfx.programs.create('todepth');
    program.set_source(two.ShaderType.Vertex, vertex_shader);
    program.set_source(two.ShaderType.Fragment, fragment_shader);
    
    var material = app.gfx.materials.create('material'); var m = material;
    m.program = app.gfx.programs.fetch('solid');
    m.solid.colour = new two.Colour(0.0, 0.0, 1.0); //two.Colour.Blue;
    
    var count = 50;
    var scale = 5.0;
    
    for(var i = 0; i < count; i++)
    {
        var r = Math.random() * 2.0 * Math.PI;
        var z = (Math.random() * 2.0) - 1.0;
        var distscale = Math.sqrt(1.0 - z * z) * scale;
    
        var p = new two.vec3(Math.cos(r) * distscale, Math.sin(r) * distscale, z * scale);
        var a = new two.vec3(Math.random(), Math.random(), Math.random());
        var n = scene.nodes().add(new two.Node3(p, new two.quat(a)));
        scene.items().add(new two.Item(n, geometry, 0, material));
    }
}

function renderer(gfx, render) {

    two.begin_pbr_render(gfx, render);

    two.pass_clear(gfx, render);
    two.pass_solid(gfx, render);
    pass_todepth(gfx, render);
}

var render = new two.Render(two.Shading.Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame);
app.gfx.renderer.gather(render);
app.gfx.renderer.begin(render);
renderer(app.gfx, render);
app.gfx.renderer.end(render);
