// shader_ocean.js

var water_vertex = `$input a_position
    $output v_world, v_mirrored
    
    #include <common.sh>
    
    uniform mat4 u_mirror;
    
    void main() {
    	vec4 world = mul(u_model[0], vec4(a_position.xyz, 1.0));
    	v_world = world.xyz;
    	v_mirrored = mul(u_mirror, world);
    	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;

var water_fragment = `$input v_world, v_mirrored
    
    #include <common.sh>
    
    #define s_mirror s_user0
    #define s_normal s_user1
    
    vec4 getNoise(vec2 uv) {
    	vec2 uv0 = (uv / 103.0) + vec2(u_time / 17.0, u_time / 29.0);
    	vec2 uv1 = uv / 107.0 - vec2(u_time / -19.0, u_time / 31.0);
    	vec2 uv2 = uv / vec2(8907.0, 9803.0) + vec2(u_time / 101.0, u_time / 97.0);
    	vec2 uv3 = uv / vec2(1091.0, 1027.0) - vec2(u_time / 109.0, u_time / -113.0);
    	vec4 noise = texture2D(s_normal, uv0) +
    		texture2D(s_normal, uv1) +
    		texture2D(s_normal, uv2) +
    		texture2D(s_normal, uv3);
    	return noise * 0.5 - 1.0;
    }

    void sunLight(vec3 normal, vec3 view, vec3 sundir, vec3 suncolor, float shiny, float fspec, float fdiff, inout vec3 diffuse, inout vec3 specular) {
        vec3 reflection = normalize(reflect(-sundir, normal));
        float direction = max(0.0, dot(view, reflection));
        specular += pow(direction, shiny) * suncolor * fspec;
        diffuse += max(dot(sundir, normal), 0.0) * suncolor * fdiff;
    }

    void main() {
		int material_index = int(u_state_material);
		UserMaterial mat = read_user_material(material_index);

		float alpha      = mat.p0.x;
		float size       = mat.p0.y;
		float distortion = mat.p0.z;
		vec3 suncolor    = mat.p1.xyz;
		vec3 sundir      = normalize(mat.p2.xyz);
		vec3 eye         = mat.p3.xyz;
		vec3 water_color = mat.p4.xyz;

		vec4 noise = getNoise(v_world.xz * size);
		vec3 normal = normalize(noise.xzy * vec3(1.5, 1.0, 1.5));

		vec3 diffuse = vec3_splat(0.0);
		vec3 specular = vec3_splat(0.0);
		
		vec3 ray = eye - v_world.xyz;
		float distance = length(ray);
		vec3 dir = normalize(ray);
		sunLight(normal, dir, sundir, suncolor, 100.0, 2.0, 0.5, diffuse, specular);
		
		
		vec2 distort = normal.xz * (0.001 + 1.0 / distance) * distortion;
		vec3 reflection = texture2D(s_mirror, v_mirrored.xy / v_mirrored.w + distort).rgb;

		float theta = max(dot(dir, normal), 0.0);
		float rf0 = 0.3;
		float reflectance = rf0 + (1.0 - rf0) * pow((1.0 - theta), 5.0);
		vec3 scatter = max(0.0, dot(normal, dir)) * water_color;
		diffuse = (suncolor * diffuse * 0.3 + scatter); // * getShadowMask()
		specular = (vec3_splat(0.1) + reflection * 0.9 + reflection * specular);
		vec3 albedo = mix(diffuse, specular, reflectance);
		vec3 light = albedo;
		gl_FragColor = vec4(light, alpha);
    }`;


function Water()
{
    this.resolution = new two.uvec2(512);
    this.clipBias = 0.0;
    this.alpha = 1.0;
    this.time = 0.0;
    this.normals = null;
    this.sunDirection = new two.vec3(0.70707, 0.70707, 0.0);
    this.sunColor = two.rgb(0xffffff); // two.rgb(0x7f7f7f);
    this.waterColor = two.rgb(0x7f7f7f); // two.rgb(0x555555);
    this.distortionScale = 20.0;
    this.size = 1.0;
    this.fog = false;
}

Water.prototype = Object.assign(Object.create(Object.prototype), {

    constructor: Water,

    create: function(gfx, scene, geometry, resolution) {
        
        // resolution = uvec2(512U)
        var program = gfx.programs.create('water');
        program.set_pass(two.PassType.Opaque);
        program.set_block(two.MaterialBlock.User);
        program.set_source(two.ShaderType.Vertex, water_vertex);
        program.set_source(two.ShaderType.Fragment, water_fragment);

        var material = gfx.materials.create('water'); var m = material;
            m.program = program;
        
        this.material = material;

        this.node = scene.nodes().add(new two.Node3());
        this.item = scene.items().add(new two.Item(this.node, geometry, 0, material));
        //THREE.Mesh.call(this, geometry);
        
        this.eye = new two.vec3(0.0);

        this.fbo = new two.FrameBuffer(resolution, two.TextureFormat.RGBA8);
        
        //material.submit = [this](btwo.gfx.Encoder encoder) { this.submit(encoder); };
    },

    //submit: function(btwo.gfx.Encoder encoder)
    //{
    //	btwo.gfx.UniformHandle u_mirror = btwo.gfx.createUniform('u_mirror', btwo.gfx.UniformType::Mat4, 1U);
    //
    //	encoder.setUniform(u_mirror, mirror);
    //}

    update: function(material) {

        material.user.tex0 = this.fbo.tex;
        material.user.tex1 = this.normals;

        material.user.attr0 = new two.vec4(this.alpha, this.size, this.distortionScale, 0.0);
        material.user.attr1 = new two.vec4(this.sunColor.r, this.sunColor.g, this.sunColor.b, 0.0);
        material.user.attr2 = new two.vec4(this.sunDirection.x, this.sunDirection.y, this.sunDirection.z, 0.0);
        material.user.attr3 = new two.vec4(this.eye.x, this.eye.y, this.eye.z, 0.0);
        material.user.attr4 = new two.vec4(this.waterColor.r, this.waterColor.g, this.waterColor.b, 0.0);
    },

    pass_mirror: function(gfx, render) {
        
        var sourcecam = render.camera;
        var mirrorcam = two.mirror_camera(sourcecam, this.node);
        if(!mirrorcam.visible) return;

        this.mirror = mirrorcam.mirror;
        this.eye = sourcecam.eye;

        this.item.visible = false;

        var viewport = new two.Viewport(mirrorcam.camera, render.scene, new two.vec4(0, 0, 1, 1));
        var subrender = new two.Render(two.Shading.Shaded, viewport, render.target, this.fbo, gfx.render_frame);
        gfx.renderer.gather(subrender);
        
        app.gfx.renderer.begin(subrender);
        two.render_pbr_forward(app.gfx, subrender);
        app.gfx.renderer.end(subrender);
        render.pass_index = subrender.pass_index;
        
        //gfx.renderer.subrender(render, subrender, render_pbr_forward);

        this.item.visible = true;
    }
});

var sky_vertex = `$input a_position
    $output v_world, v_sundir, v_sunp0, v_betaR, v_betaM
    
    #include <common.sh>
    
    CONST(vec3) up = vec3(0.0, 1.0, 0.0);

    // constants for atmospheric scattering
    CONST(float) e = 2.71828182845904523536028747135266249775724709369995957;
    CONST(float) pi = 3.141592653589793238462643383279502884197169;

    // wavelength of used primaries, according to preetham
    CONST(vec3) lambda = vec3(680E-9, 550E-9, 450E-9);
    // this pre-calcuation replaces older TotalRayleigh(vec3 lambda) function:
    // (8.0 * pow(pi, 3.0) * pow(pow(n, 2.0) - 1.0, 2.0) * (6.0 + 3.0 * pn)) / (3.0 * N * pow(lambda, vec3(4.0)) * (6.0 - 7.0 * pn))
    CONST(vec3) totalRayleigh = vec3(5.804542996261093E-6, 1.3562911419845635E-5, 3.0265902468824876E-5);

    // mie stuff
    // K coefficient for the primaries
    CONST(float) v = 4.0;
    CONST(vec3) K = vec3(0.686, 0.678, 0.666);
    // MieConst = pi * pow((2.0 * pi) / lambda, vec3(v - 2.0)) * K
    CONST(vec3) MieConst = vec3(1.8399918514433978E14, 2.7798023919660528E14, 4.0790479543861094E14);

    // earth shadow hack
    // cutoffAngle = pi / 1.95;
    CONST(float) cutoffAngle = 1.6110731556870734;
    CONST(float) steepness = 1.5;
    CONST(float) EE = 1000.0;

    float sunIntensity(float zenithAngleCos) {
    	zenithAngleCos = clamp(zenithAngleCos, -1.0, 1.0);
    	return EE * max(0.0, 1.0 - pow(e, -((cutoffAngle - acos(zenithAngleCos)) / steepness)));
    }

    vec3 totalMie(float T) {
    	float c = (0.2 * T) * 10E-18;
    	return 0.434 * c * MieConst;
    }

    void main() {
		int material_index = int(u_state_material_vertex);
		UserMaterial mat = read_user_material(material_index);

		vec3 sunposition     = mat.p0.xyz;
		float turbidity      = mat.p1.x;
		float rayleigh       = mat.p1.y;
		float mieCoefficient = mat.p2.x;

		vec4 worldPosition = mul(u_model[0], vec4(a_position.xyz, 1.0));
		v_world = worldPosition.xyz;

		gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
		gl_Position.z = gl_Position.w; // set z to camera.far

		v_sundir = normalize(sunposition);

		float sunE = sunIntensity(dot(v_sundir, up));
		float sunfade = 1.0 - clamp(1.0 - exp((sunposition.y / 450000.0)), 0.0, 1.0);
		v_sunp0 = vec2(sunfade, sunE);

		float rayleighCoefficient = rayleigh - (1.0 * (1.0 - sunfade));

		// extinction (absorbtion + out scattering)
		// rayleigh coefficients
		v_betaR = totalRayleigh * rayleighCoefficient;

		// mie coefficients
		v_betaM = totalMie(turbidity) * mieCoefficient;
    }`;

var sky_fragment = `$input v_world, v_sundir, v_sunp0, v_betaR, v_betaM
    
    #include <common.sh>
    
    #define u_luminance u_user_p1.z
    #define u_mieDirectionalG u_user_p2.y

    CONST(vec3) cameraPos = vec3(0.0, 0.0, 0.0);

    // constants for atmospheric scattering
    CONST(float) pi = 3.141592653589793238462643383279502884197169;

    CONST(float) n = 1.0003;   // refractive index of air
    CONST(float) N = 2.545E25; // number of molecules per unit volume for air at
                                  // 288.15K and 1013mb (sea level -45 celsius)

    // optical length at zenith for molecules
    CONST(float) rayleighZenithLength = 8.4E3;
    CONST(float) mieZenithLength = 1.25E3;
    CONST(vec3) up = vec3(0.0, 1.0, 0.0);
    // 66 arc seconds . degrees, and the cosine of that
    CONST(float) sunAngularDiameterCos = 0.999956676946448443553574619906976478926848692873900859324;

    // 3.0 / (16.0 * pi)
    CONST(float) d3b16pi = 0.05968310365946075;
    // 1.0 / (4.0 * pi)
    CONST(float) d1b4pi = 0.07957747154594767;

    float rayleighPhase(float cosTheta) {
    	return d3b16pi * (1.0 + pow(cosTheta, 2.0));
    }

    float hgPhase(float cosTheta, float g) {
    	float g2 = pow(g, 2.0);
    	float inverse = 1.0 / pow(1.0 - 2.0 * g * cosTheta + g2, 1.5);
    	return d1b4pi * ((1.0 - g2) * inverse);
    }

    // Filmic ToneMapping http://filmicgames.com/archives/75
    CONST(float) A = 0.15;
    CONST(float) B = 0.50;
    CONST(float) C = 0.10;
    CONST(float) D = 0.20;
    CONST(float) E = 0.02;
    CONST(float) F = 0.30;

    CONST(float) whiteScale = 1.0748724675633854; // 1.0 / Uncharted2Tonemap(1000.0)

    vec3 Uncharted2Tonemap(vec3 x) {
    	return ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;
    }


    void main() {
		int material_index = int(u_state_material);
		UserMaterial mat = read_user_material(material_index);

		float luminance       = mat.p1.z;
		float mieDirectionalG = mat.p2.y;

		// optical length
		// cutoff angle at 90 to avoid singularity in next formula.
		float zenithAngle = acos(max(0.0, dot(up, normalize(v_world - cameraPos))));
		float inverse = 1.0 / (cos(zenithAngle) + 0.15 * pow(93.885 - ((zenithAngle * 180.0) / pi), -1.253));
		float sR = rayleighZenithLength * inverse;
		float sM = mieZenithLength * inverse;

		// combined extinction factor
		vec3 Fex = exp(-(v_betaR * sR + v_betaM * sM));

		// in scattering
		float cosTheta = dot(normalize(v_world - cameraPos), v_sundir);

		float rPhase = rayleighPhase(cosTheta * 0.5 + 0.5);
		vec3 betaRTheta = v_betaR * rPhase;

		float mPhase = hgPhase(cosTheta, mieDirectionalG);
		vec3 betaMTheta = v_betaM * mPhase;

		float sunE = v_sunp0.y;
		vec3 Lin = pow(sunE * ((betaRTheta + betaMTheta) / (v_betaR + v_betaM)) * (1.0 - Fex), vec3_splat(1.5));
		Lin *= mix(vec3_splat(1.0), pow(sunE * ((betaRTheta + betaMTheta) / (v_betaR + v_betaM)) * Fex, vec3_splat(1.0 / 2.0)), clamp(pow(1.0 - dot(up, v_sundir), 5.0), 0.0, 1.0));

		// nightsky
		vec3 direction = normalize(v_world - cameraPos);
		float theta = acos(direction.y); // elevation --> y-axis, [-pi/2, pi/2]
		float phi = atan2(direction.z, direction.x); // azimuth --> x-axis [-pi/2, pi/2]
		vec2 uv = vec2(phi, theta) / vec2(2.0 * pi, pi) + vec2(0.5, 0.0);
		vec3 L0 = vec3_splat(0.1) * Fex;

		// composition + solar disc
		float sundisk = smoothstep(sunAngularDiameterCos, sunAngularDiameterCos + 0.00002, cosTheta);
		L0 += (sunE * 19000.0 * Fex) * sundisk;

		vec3 texColor = (Lin + L0) * 0.04 + vec3(0.0, 0.0003, 0.00075);

		vec3 curr = Uncharted2Tonemap((log2(2.0 / pow(luminance, 4.0))) * texColor);
		vec3 color = curr * whiteScale;

		float sunfade = v_sunp0.x;
		vec3 retColor = pow(color, vec3_splat(1.0 / (1.2 + (1.2 * sunfade))));

		gl_FragColor = vec4(retColor, 1.0);
		//gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
    }`;

function Sky()
{
    this.sun_position = new two.vec3(0.0, 1.0, 0.0);
    this.turbidity = 2.0; // 10.0
    this.rayleigh = 1.0; // 2.0
    this.luminance = 1.0;
    this.mieCoefficient = 0.005;
    this.mieDirectionalG = 0.8;
}

Sky.prototype = Object.assign(Object.create(Object.prototype), {

    constructor: Sky,

    create: function(gfx, scene) {
        var program = gfx.programs.create('sky');
        program.set_pass(two.PassType.Opaque);
        program.set_block(two.MaterialBlock.User);
        program.set_source(two.ShaderType.Vertex, sky_vertex);
        program.set_source(two.ShaderType.Fragment, sky_fragment);

        var material = gfx.materials.create('sky'); var m = material;
            m.program = program;
            m.base.cull_mode = two.CullMode.Front;

        this.material = material;

        var geometry = gfx.shape(new two.Cube(new two.vec3(0.5)));

        this.node = scene.nodes().add(new two.Node3());
        this.item = scene.items().add(new two.Item(this.node, geometry, 0, material));

        this.update(material);
    },

    update: function(material) {
        material.user.attr0 = new two.vec4(this.sun_position.x, this.sun_position.y, this.sun_position.z, 0.0);
        material.user.attr1 = new two.vec4(this.turbidity, this.rayleigh, this.luminance, 0.0);
        material.user.attr2 = new two.vec4(this.mieCoefficient, this.mieDirectionalG, 0.0, 0.0);
    }
});

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controls(viewer);
two.ui.orbit_controls(viewer);
viewer.viewport.autorender = false;

var scene = viewer.scene;

//controls.maxPolarAngle = c_pi * 0.495;
//controls.target.set(0, 10, 0);
//controls.minDistance = 40.0;
//controls.maxDistance = 200.0;
//camera.lookAt(controls.target);

if(init) {
    var camera = viewer.camera;
    camera.fov = 55.0; camera.near = 1.0; camera.far = 20000.0;
    camera.eye = new two.vec3(30.0, 30.0, 100.0);

    this.params = {
        distance: 400.0,
        inclination: 0.49,
        azimuth: 0.205
    };

    this.water = new Water();
    this.sky = new Sky();

    // Probe
    
    this.probe = new two.CubeCamera(scene, 1.0, 20000.0, 256);
    
    // Sun

    var light = new two.vec3();
    var ln = scene.nodes().add(new two.Node3());
    var l = scene.lights().add(new two.Light(ln, two.LightType.Direct, false, two.rgb(0xffffff), 0.8));
    this.sun = ln;


    // Water

    var plane = app.gfx.shape(new two.Rect(new two.vec2(0.0), new two.vec2(10000.0, 10000.0)));

    var normals = app.gfx.textures.file('waternormals.jpg');
    
    water.create(app.gfx, scene, plane, app.gfx.main_target().size / 4);
    water.normals = normals;
    water.alpha = 1.0;
    water.sunDirection = sun.direction();
    water.sunColor = two.rgb(0xffffff);
    water.waterColor = two.rgb(0x001e0f);
    water.distortionScale = 3.7;

    //water.rotation.x = -c_pi / 2;

    // Skybox

    var zeroq = new two.quat(new two.vec3(0.0));
    sky.create(app.gfx, scene);
    sky.node.apply(new two.vec3(0.0), zeroq, new two.vec3(10000.0));
    sky.turbidity = 10.0;
    sky.rayleigh = 2.0;

    // Sphere

    //var geo = new two.MeshPacker;
    //var shape = new two.Icosaedr(20.0);
    //// @todo
    ////gen_geom({ Symbol(), shape, PLAIN }, geo, PLAIN);
    //
    ////var count = geometry.attributes.position.count;
    //
    //for(var i = 0; i < geo.num_vertices(); i += 3)
    //{
    //    var color = two.rgb(Math.random() * 0xffffff);
    //    geo.colour(color);
    //    geo.colour(color);
    //    geo.colour(color);
    //}
    //
    //var ico = app.gfx.create_model_geo('ico', geo);

    
    var ico = app.gfx.shape(new two.Icosaedr(20.0));
        
    var pbr = app.gfx.programs.fetch('pbr/pbr');

    var material = app.gfx.materials.create('ocean'); var m = material;
        m.program = pbr;
        m.base.flat_shaded = true;
        m.base.cull_mode = two.CullMode.None;
        m.base.shader_color = two.ShaderColor.Vertex;
        m.pbr.roughness = 0.0;
        //envMap: cubeCamera.renderTarget.texture,

    var n = scene.nodes().add(new two.Node3());
    var i = scene.items().add(new two.Item(n, ico, 0, material));
    this.sphere = n;
}

function updateSun() {

    var theta = Math.PI * (params.inclination - 0.5);
    var phi = 2 * Math.PI * (params.azimuth - 0.5);
    
    var d = params.distance;
    var dir = new two.vec3(d * Math.cos(phi), d * Math.sin(phi) * Math.sin(theta), d * Math.sin(phi) * Math.cos(theta));
    sun.apply(new two.vec3(0.0), two.look_dir(new two.vec3(-dir.x, -dir.y, -dir.z)));

    sky.sun_position = dir;
    sky.update(sky.material);

    // @todo
    water.sunDirection = dir; //two.normalize(dir);
    water.update(water.material);
};

updateSun();

//var dock = two.ui.dockitem(dockbar, 'Game', [1])
//if(dock.valid())
//{
//    var sheet = two.ui.sheet(dock);
//
//    function panel(name)
//    {
//        var s = two.ui.expandbox(sheet, name.c_str());
//        return two.ui.columns(s, [0.3, 0.7]);
//    };
//
//    var a = panel('Sky');
//    two.ui.slider_field_float(a, 'inclination', { params.inclination,  { 0.0, 0.5, 0.0001 } });
//    two.ui.slider_field_float(a, 'azimuth',     { params.azimuth,      { 0.0, 1.0,  0.0001 } });
//
//    var b = panel('Water');
//    two.ui.slider_field_float(b, 'distortion',   { water.distortionScale,	{ 0.0, 8.0, 0.1 } });
//    two.ui.slider_field_float(b, 'size',		 { water.size,				{ 0.1, 10.0, 0.1 } });
//    two.ui.slider_field_float(b, 'alpha',		 { water.alpha,				{ 0.9f, 1.0, 0.001 } });
//}

var time = app.gfx.time;

var position = new two.vec3(0.0, Math.sin(time) * 20.0 + 5.0, 0.0);
var angles = new two.vec3(time * 0.5, 0.0, time * 0.51);
sphere.apply(position, new two.quat(angles));

//water.material.uniforms['time'].value += 1.0 / 60.0;

var render = new two.Render(two.Shading.Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame);
app.gfx.renderer.gather(render);
app.gfx.renderer.begin(render);

two.begin_pbr_render(app.gfx, render);

water.pass_mirror(app.gfx, render);

function renderer(gfx, render)
{
    two.pass_clear(gfx, render);
    //two.pass_opaque(gfx, render);
    two.pass_background(gfx, render);
};

probe.render(app.gfx, render, renderer);
scene.env.radiance.texture = probe.cubemap.cubemap;

two.pass_clear(app.gfx, render);
two.pass_opaque(app.gfx, render);
two.pass_background(app.gfx, render);

app.gfx.renderer.end(render);
