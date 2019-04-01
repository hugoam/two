
var filter_vertex = `$input a_position, a_texcoord0
    $output v_uv0
    
    #include <filter.sh>
    
    void main() {
        v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;
        gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;
	
var luminosity_fragment = `$input v_uv0
    
    #include <filter.sh>
    
    uniform vec4 u_glow_lup0;
    #define u_threshold u_glow_lup0.x
    #define u_smooth_width u_glow_lup0.y
    
    //uniform vec3 defaultColor;
    //uniform float defaultOpacity;
    
    void main() {

        vec4 texel = texture2D(s_source_0, v_uv0);

        vec3 luma = vec3(0.299, 0.587, 0.114);
        float v = dot(texel.xyz, luma);

        vec4 outputColor = vec4(0.0, 0.0, 0.0, 0.0); //vec4(defaultColor.rgb, defaultOpacity);

        float alpha = smoothstep(u_threshold, u_threshold + u_smooth_width, v);

        gl_FragColor = mix(outputColor, texel, alpha);

    }`;

// @author spidersharma / http://eduperiment.com/

var blur_fragment = `$input v_uv0
    
    #include <filter.sh>
    #include <convert.sh>
    
    #define SIGMA KERNEL_RADIUS
    
    uniform vec4 u_glow_blur_p0;
    #define u_direction u_glow_blur_p0.xy
    
    float gaussianPdf(in float x, in float sigma) {
        return 0.39894 * exp(-0.5 * x * x/(sigma * sigma)) / sigma;
    }
    void main() {
        float fSigma = float(SIGMA);
        float weightSum = gaussianPdf(0.0, fSigma);
        vec3 diffuseSum = texture2DLod(s_source_0, v_uv0, float(u_source_0_level)).rgb * weightSum;
        for(int i = 1; i < KERNEL_RADIUS; i++) {
            float x = float(i);
            float w = gaussianPdf(x, fSigma);
            vec2 uvOffset = u_direction * u_pixel_size * x;
            vec3 sample1 = texture2DLod(s_source_0, v_uv0 + uvOffset, float(u_source_0_level)).rgb;
            vec3 sample2 = texture2DLod(s_source_0, v_uv0 - uvOffset, float(u_source_0_level)).rgb;
            diffuseSum += (sample1 + sample2) * w;
            weightSum += 2.0 * w;
        }
        gl_FragColor = vec4(diffuseSum / weightSum, 1.0);
    //	gl_FragColor = vec4(hsl_to_rgb(vec3(u_source_0_level / 5.0, 1.0, 0.5)), 1.0);
    //	gl_FragColor = vec4(vec3_splat(float(u_source_0_level) / 5.0), 1.0);
    }`;


var merge_fragment = `$input v_uv0
    
    #include <filter.sh>
    
    uniform vec4 u_glow_merge_p0;
    #define u_glow_strength u_glow_merge_p0.x
    #define u_glow_radius u_glow_merge_p0.y
    
    uniform vec4 u_glow_levels[2];
    uniform vec4 u_glow_colors[5];
    
    float lerpBloomFactor(float factor) { 
        float mirrorFactor = 1.2 - factor;
        return mix(factor, mirrorFactor, u_glow_radius);
    }
    
    void main() {
        gl_FragColor = u_glow_strength * (lerpBloomFactor(u_glow_levels[0].x) * u_glow_colors[0] * texture2DLod(s_source_0, v_uv0, 1.0) + 
                                          lerpBloomFactor(u_glow_levels[0].y) * u_glow_colors[1] * texture2DLod(s_source_0, v_uv0, 2.0) + 
                                          lerpBloomFactor(u_glow_levels[0].z) * u_glow_colors[2] * texture2DLod(s_source_0, v_uv0, 3.0) + 
                                          lerpBloomFactor(u_glow_levels[0].w) * u_glow_colors[3] * texture2DLod(s_source_0, v_uv0, 4.0) + 
                                          lerpBloomFactor(u_glow_levels[1].x) * u_glow_colors[4] * texture2DLod(s_source_0, v_uv0, 5.0));
    //	gl_FragColor = texture2DLod(s_source_0, v_uv0, 0.0);
    }`;


function pass_unreal_bloom(gfx, render, bloom) {
    
	function pass_lum(gfx, render, bloom, fbo) {
        
		var program = gfx.programs.fetch('bloom_lum');

		// create color only once here, reuse it later inside the render function
		var clearColor = new two.Colour(0.0);

		// luminosity high pass material

		var pass = render.next_pass('bloom_lum', two.PassType.PostProcess);

		gfx.filter.uniform(pass, 'u_glow_lup0', new two.vec4(bloom.threshold, 0.01, 0.0, 0.0));

		gfx.filter.source0(render.target.diffuse);

		gfx.filter.quad(pass, fbo, program);
	}

	var BlurH = 0; var BlurV = 1;
	var KERNEL_SIZE = 0;

	function pass_blur(gfx, render, d, source, level, dest, kernel_size) {

		var program = gfx.programs.fetch('bloom_blur');

		var pass = render.next_pass('bloom_blur', two.PassType.PostProcess);

		var dirs = [ new two.vec2(1.0, 0.0), new two.vec2(0.0, 1.0) ];

		gfx.filter.uniform(pass, 'u_glow_blur_p0', new two.vec4(dirs[d].x, dirs[d].y, 0.0, 0.0));

		var version = new two.ProgramVersion(program);
		gfx.filter.source0(source, version, level);

		version.set_mode(0, KERNEL_SIZE, kernel_size);

        // @todo (this is the one taking a ProgramVersion)
		gfx.filter.quad(pass, dest, version);
	}

	function pass_merge(gfx, render, bloom, source) {
        
		var program = gfx.programs.fetch('bloom_merge');

		var pass = render.next_pass('bloom_merge', two.PassType.PostProcess);

		var white = new two.vec4(1.0);
		var glow_levels = new Float32Array([1.0, 0.8, 0.6f, 0.4, 0.2, 0.0, 0.0, 0.0]);
		//var glow_tint = [ white, white, white, white, white ];

		gfx.filter.uniform(pass, 'u_glow_merge_p0', new two.vec4(bloom.strength, bloom.radius, 0.0, 0.0));
        // @todo
		gfx.filter.uniforms(pass, 'u_glow_levels', glow_levels);
		//gfx.filter.uniforms(pass, 'u_glow_colors', glow_tint, 5);

		gfx.filter.source0(source);

		var target = render.target;
		gfx.filter.quad(pass, target.post.swap(), program);

		// additive blend bloom over target
        var merge = render.next_pass('flip', two.PassType.PostProcess);
		//gfx.copy.quad(merge, render.target_fbo, target.post.last());
		//gfx.copy.quad(merge, render.target_fbo, target.post.last(), pass.viewport.rect, BGFX_STATE_BLEND_ADD);
		gfx.copy.quad(merge, render.target_fbo, target.post.last(), pass.viewport.rect, 35790848);
	};

	// 1. Extract bright areas
	pass_lum(gfx, render, bloom, render.target.ping_pong.swap());

	//copy.debug_show_texture(render, render.target.ping_pong.last(), vec4(0.0));

	// 2. Blur all the mips progressively
	//SwapCascade swap = render.target.swap_cascade;
	if(this.swap === undefined) {
        this.swap = new two.SwapCascade();
		this.swap.create(bloom.resolution, two.TextureFormat.RGBA8);
		//swap.create(bloom.resolution, two.TextureFormat.RGBA16F);
    }

	var source = render.target.ping_pong.last();

	var kernel_sizes = [ 3, 5, 7, 9, 11 ];

	for(var i = 1; i < 6; i++) {
        
		var h = this.swap.swap();
		pass_blur(gfx, render, BlurH, source, i - 1, h.fbos[i], kernel_sizes[i]);

		var v = this.swap.swap();
		pass_blur(gfx, render, BlurV, h.texture, i, v.fbos[i], kernel_sizes[i]);

		source = v.texture;
	}

	//gfx.copy.debug_show_texture(render, this.swap.last().texture, vec4(0.0), 3);
	//gfx.copy.debug_show_texture(render, *source, vec4(0.0));

	// Composite all the mips
	pass_merge(gfx, render, bloom, source);
}

var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controls(viewer);
//controls.maxPolarAngle = c_pi * 0.5;
//controls.minDistance = 1;
//controls.maxDistance = 10;
viewer.viewport.active = false;

//Tonemap tonemap = viewer.viewport.comp<Tonemap>();
//tonemap.enabled = true;
//tonemap.mode = two.TonemapMode.Reinhardt;
//tonemap.exposure = 3.f;

var scene = viewer.scene;

if(init) {
    this.importerGltf = new two.ImporterGltf(app.gfx);

    var camera = viewer.camera;
    camera.fov = 40.0; camera.near = 1.0; camera.far = 100.0;
    camera.eye = vec3(-5.f, 2.5, -3.5);

    this.bloom = { exposure: 1.0, strength: 1.5, radius: 0.0, threshold: 0.0 };
    this.bloom.resolution = app.gfx.main_target().size;

    scene.env.radiance.colour = two.rgb(0x404040);
    scene.env.radiance.energy = 1.0;
    scene.env.radiance.ambient = 1.0;
    //scene.add(new THREE.AmbientLight(0x404040));

    var highpass = gfx.programs.create('bloom_lum');
    highpass.set_source(two.ShaderType.Vertex, filter_vertex);
    highpass.set_source(two.ShaderType.Fragment, luminosity_fragment);

    var blur_block = new two.ShaderBlock();
    blur_block.index = 0;
    blur_block.add_mode('KERNEL_RADIUS');
    
    var blur = gfx.programs.create('bloom_blur');
    blur.set_source(two.ShaderType.Vertex, filter_vertex);
    blur.set_source(two.ShaderType.Fragment, blur_fragment);
    blur.register_block(gfx.filter.shader_block);
    blur.register_block(blur_block);
    //blur.register_modes(0, { 'KERNEL_RADIUS' });

    var merge = gfx.programs.create('bloom_merge');
    program.set_source(two.ShaderType.Vertex, filter_vertex);
    program.set_source(two.ShaderType.Fragment, merge_fragment);

    var ln = scene.nodes().add(new two.Node3());
    scene.lights().add(new two.Light(ln, two.LightType.Point, false, two.rgb(0xffffff), 1.0));

    var model = app.gfx.models.file('PrimaryIonDrive'); // .glb

    var n = scene.nodes().add(new two.Node3());
    scene.items().add(new two.Item(n, model));

    // Mesh contains self-intersecting semi-transparent faces, which display
    // z-fighting unless depthWrite is disabled.
    //var core = model.getObjectByName('geo1_HoloFillDark_0');
    //core.material.depthWrite = false;

    //mixer = new THREE.AnimationMixer(model);
    //var clip = gltf.animations[0];
    //mixer.clipAction(clip.optimize()).play();
}

//if(var dock = two.ui.dockitem(dockbar, 'Game', { 1U }))
//{
//	var sheet = two.ui.sheet(*dock);
//
//	var controls = two.ui.stack(sheet);
//	two.ui.slider_field_float(controls, 'threshold', { bloom.threshold, { 0.0, 1.0, 0.01 } });
//	two.ui.slider_field_float(controls, 'strength',  { bloom.strength,  { 0.0, 3.f, 0.1 } });
//	two.ui.slider_field_float(controls, 'radius',    { bloom.radius,    { 0.0, 1.0, 0.01 } });
//
//
//	two.ui.slider_field_float(controls, 'exposure', { tonemap.exposure, { 0.1, 2.0, 0.01 } });
//	// exposure = pow(value, 4.0)
//}


function renderer(gfx, render, bloom) {
    
    two.begin_pbr_render(gfx, render);

    two.pass_clear(gfx, render);
    two.pass_opaque(gfx, render);
    pass_unreal_bloom(gfx, render, bloom);

    two.pass_post(gfx, render);
}

var render = new two.Render(two.Shading.Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame);
app.gfx.renderer.gather(render);
app.gfx.renderer.begin(render);

renderer(app.gfx, render, this.bloom);

app.gfx.renderer.end(render);

//const float delta = clock.getDelta();

//mixer.update(delta);
