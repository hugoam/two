// effect_glitch.js

// @author felixturner / http://airtight.cc/

var glitch_vertex = `$input a_position, a_texcoord0
    $output v_uv0
    
    #include <filter.sh>
    
    void main() {
    	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;
    	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;

var glitch_fragment = `$input v_uv0
    
    #include <filter.sh>
    
    uniform vec4 u_glitch_p0;
    #define u_amount u_glitch_p0.x
    #define u_angle u_glitch_p0.y
    #define u_seed u_glitch_p0.y

    uniform vec4 u_glitch_p1;
    #define u_scale u_glitch_p1.xy
    #define u_distort u_glitch_p1.zw
    
    //uniform float col_s;
    
    float rand(vec2 co){
    	return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
    }
    
    void main() {
    	const float col_s = 0.5;
    	vec2 p = v_uv0;
    	float xs = floor(gl_FragCoord.x / 0.5);
    	float ys = floor(gl_FragCoord.y / 0.5);
    	//based on staffantans glitch shader for unity https://github.com/staffantan/unityglitch 
    	vec4 normal = texture2D(s_source_1, p * u_seed * u_seed);
    	if(p.y < u_distort.x + col_s && p.y > u_distort.x - col_s * u_seed) {
    		if(u_scale.x > 0.0) {
    			p.y = 1.0 - (p.y + u_distort.y);
    		}
    		else {
    			p.y = u_distort.y;
    		}
    	}
    	if(p.x < u_distort.y + col_s && p.x > u_distort.y - col_s * u_seed) {
    		if(u_scale.y > 0.0){
    			p.x = u_distort.x;
    		}
    		else {
    			p.x = 1.0 - (p.x + u_distort.x);
    		}
    	}
    	p.x += normal.x * u_scale.x * (u_seed / 5.0);
    	p.y += normal.y * u_scale.y * (u_seed / 5.0);
    	//base from RGB shift shader
    	vec2 offset = u_amount * vec2(cos(u_angle), sin(u_angle));
    	vec4 cr = texture2D(s_source_0, p + offset);
    	vec4 cga = texture2D(s_source_0, p);
    	vec4 cb = texture2D(s_source_0, p - offset);
    	gl_FragColor = vec4(cr.r, cga.g, cb.b, cga.a);
    	//add noise
    	vec4 snow = 200.0 * u_amount * vec4_splat(rand(vec2(xs * u_seed, ys * u_seed * 50.0)) * 0.2);
    	gl_FragColor = gl_FragColor + snow;
    }`;

var speed = 2;

function glitch_heightmap(gfx, size) {
	var texture = gfx.textures.create('glitch');

	var array = new Float32Array(size * size * 4);

	var count = size * size;
	for(var i = 0; i < count; i++) {
        
		var val = Math.random();
		array[i * 4 + 0] = val;
		array[i * 4 + 1] = val;
		array[i * 4 + 2] = val;
		array[i * 4 + 3] = 0.0;
	}

	//load_texture_rgba(texture, size, size, *memory);
	two.load_texture_float(texture, new two.uvec2(size), array);
	return texture;
}

function randFloat(min, max) {
    return Math.random() * (max - min) + min;
}

function randInt(min, max) {
    min = Math.ceil(min);
    max = Math.floor(max);
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

function pass_glitch(gfx, render, glitch, dt_size) {

    //dt_size = 64;
    var disp = glitch_heightmap(gfx, dt_size);

    var amount = 0.0;
    var angle = 0.0;
    var scale = new two.vec2(0.0);
    var distort = new two.vec2(0.0);

    var frame = glitch.frame % glitch.randX;
    if(frame == 0 || glitch.gowild == true)
    {
        amount = Math.random() / 30.0;
        angle = randFloat(-Math.PI, Math.PI);
        scale = new two.vec2(randFloat(-1, 1), randFloat(-1, 1));
        distort = new two.vec2(randFloat(0, 1), randFloat(0, 1));
        glitch.frame = 0;
        glitch.randX = randInt(120, 240) * speed;

    }
    else if(frame < glitch.randX / 5)
    {
        amount = Math.random() / 90.0;
        angle = randFloat(-Math.PI, Math.PI);
        scale = new two.vec2(randFloat(-0.3, 0.3), randFloat(-0.3, 0.3));
        distort = new two.vec2(randFloat(0, 1), randFloat(0, 1));
    }
    else if(glitch.gowild == false)
    {
        glitch.frame++;
        return;
    }

    glitch.frame++;

    var program = new two.ProgramVersion(app.gfx.programs.fetch('glitch'));

    var pass = render.next_pass('glitch', two.PassType.PostProcess);

    gfx.filter.uniform(pass, 'u_glitch_p0', new two.vec4(amount, angle, glitch.seed, 0.0));
    gfx.filter.uniform(pass, 'u_glitch_p1', new two.vec4(scale.x, scale.y, distort.x, distort.y));

    gfx.filter.source0(render.target.diffuse);
    gfx.filter.sourcedepth(disp);

    var target = render.target;
    gfx.filter.quad(pass, target.post.swap(), program);

    var flip = render.next_pass('flip', two.PassType.PostProcess);
    gfx.copy.quad(flip, render.target_fbo, target.post.last());
}

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controls(viewer);
viewer.viewport.active = false;

var scene = viewer.scene;

if(init) {
    var camera = viewer.camera;
    camera.fov = 70.0; camera.near = 1.0; camera.far = 1000.0;
    camera.eye.z = 400.0;

    //scene.fog = new THREE.Fog(0x000000, 1, 1000);

    var glitch = app.gfx.programs.create('glitch');
    glitch.set_source(two.ShaderType.Vertex, glitch_vertex);
    glitch.set_source(two.ShaderType.Fragment, glitch_fragment);

    var symbol = new two.Symbol(new two.Colour(1.0)); symbol.subdiv = new two.uvec2(4);
    var geometry = app.gfx.shape(new two.Sphere(1.0), symbol);
    //var geometry = app.gfx.shape(Sphere(1.0));

    var pbr = app.gfx.programs.fetch('pbr/pbr');

    var group = scene.nodes().add(new two.Node3());
    this.object = group;

    this.nodes = [];
    for(var i = 0; i < 100; i++) {
        var name = 'object' + i.toString();
        var material = app.gfx.materials.create(name); var m = material;
            m.program = pbr;
            m.base.flat_shaded = true;
            m.pbr.albedo.value = two.rgb(Math.random() * 0xffffff);
        
        //var material = new THREE.MeshPhongMaterial({ color: 0xffffff * Math.random(),  });

        var d = Math.random() * 400.0;
        var p = new two.vec3((Math.random() - 0.5) * d, (Math.random() - 0.5) * d, (Math.random() - 0.5) * d);
        var a = new two.vec3(Math.random() * 2.0, Math.random() * 2.0, Math.random() * 2.0);
        var s = new two.vec3(Math.random() * 50.0);

        var n = scene.nodes().add(new two.Node3(p, quat(a), s));
        scene.items().add(new two.Item(n, geometry, 0, material));
        this.nodes.push({ p: p, a: a, s: s, n: n });
    }

    //scene.add(new THREE.AmbientLight(0x222222));

    var dir = two.look_dir(new two.vec3(-1.0, -1.0, -1.0));
    var n = scene.nodes().add(new two.Node3(new two.vec3(0.0), dir));
    var light = scene.lights().add(new two.Light(n, two.LightType.Direct, false));

    this.glitch = { seed: Math.random(), randX: randInt(120, 240) * speed, gowild: false, bypass: 0, frame:0 };
	//int randX = randi(120, 240) * speed;
    
    this.angles = new two.vec3(0.0);
}

var delta = app.gfx.frame_time;

this.angles.x += 0.2 * delta;
this.angles.y += 0.4 * delta;

this.object.apply(new two.vec3(0.0), new two.quat(this.angles));

for(var i = 0; i < this.nodes.length; ++i) {
    var node = this.nodes[i];
    node.n.derive(this.object, node.p, new two.quat(node.a), node.s);
}

function renderer(gfx, render, glitch) {
    
    two.begin_pbr_render(gfx, render);

    two.pass_clear(gfx, render);
    two.pass_opaque(gfx, render);
    pass_glitch(gfx, render, glitch);
}

var render = new two.Render(two.Shading.Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame);
app.gfx.renderer.gather(render);

app.gfx.renderer.begin(render);
renderer(app.gfx, render, this.glitch);
app.gfx.renderer.end(render);

