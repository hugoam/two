//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

#define WATER 1
#define COLOURS 1

string water_vertex()
{
	string shader =

		'$input a_position\n'
		'$output v_world, v_mirrored\n'
		'\n'
		'#include <common.sh>\n'
		'\n'
		'uniform mat4 u_mirror;\n'
		'\n'
		//THREE.ShaderChunk['fog_pars_vertex'],
		//THREE.ShaderChunk['shadowmap_pars_vertex'],
		'\n'
		'void main() {\n'
		'	vec4 world = mul(u_model[0], vec4(a_position.xyz, 1.0));\n'
		'	v_world = world.xyz;\n'
		'	v_mirrored = mul(u_mirror, world);\n'
		'	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n'
		'\n'
		//THREE.ShaderChunk['fog_vertex'],
		//THREE.ShaderChunk['shadowmap_vertex'],
		'}\n';

	return shader;
}

string water_fragment()
{
	string shader =

		'$input v_world, v_mirrored\n'
		'\n'
		'#include <common.sh>\n'
		'\n'
		'#define s_mirror s_user0\n'
		'#define s_normal s_user1\n'
		'\n'
		'#define u_alpha u_user_p0.x\n'
		'#define u_size u_user_p0.y\n'
		'#define u_distortion u_user_p0.z\n'
		'#define u_sun_color u_user_p1.xyz\n'
		'#define u_sun_dir u_user_p2.xyz\n'
		'#define u_eye u_user_p3.xyz\n'
		'#define u_water_color u_user_p4.xyz\n'
		'\n'
		'vec4 getNoise(vec2 uv) {\n'
		'	vec2 uv0 = (uv / 103.0) + vec2(u_time / 17.0, u_time / 29.0);\n'
		'	vec2 uv1 = uv / 107.0 - vec2(u_time / -19.0, u_time / 31.0);\n'
		'	vec2 uv2 = uv / vec2(8907.0, 9803.0) + vec2(u_time / 101.0, u_time / 97.0);\n'
		'	vec2 uv3 = uv / vec2(1091.0, 1027.0) - vec2(u_time / 109.0, u_time / -113.0);\n'
		'	vec4 noise = texture2D(s_normal, uv0) +\n'
		'		texture2D(s_normal, uv1) +\n'
		'		texture2D(s_normal, uv2) +\n'
		'		texture2D(s_normal, uv3);\n'
		'	return noise * 0.5 - 1.0;\n'
		'}\n'
		'\n'
		'void sunLight(vec3 normal, vec3 view, float shiny, float fspec, float fdiff, inout vec3 diffuse, inout vec3 specular) {\n'
		'	vec3 reflection = normalize(reflect(-u_sun_dir, normal));\n'
		'	float direction = max(0.0, dot(view, reflection));\n'
		'	specular += pow(direction, shiny) * u_sun_color * fspec;\n'
		'	diffuse += max(dot(u_sun_dir, normal), 0.0) * u_sun_color * fdiff;\n'
		'}\n'

		//THREE.ShaderChunk['common'],
		//THREE.ShaderChunk['packing'],
		//THREE.ShaderChunk['bsdfs'],
		//THREE.ShaderChunk['fog_pars_fragment'],
		//THREE.ShaderChunk['lights_pars_begin'],
		//THREE.ShaderChunk['shadowmap_pars_fragment'],
		//THREE.ShaderChunk['shadowmask_pars_fragment'],

		'void main() {\n'
		'	vec4 noise = getNoise(v_world.xz * u_size);\n'
		'	vec3 normal = normalize(noise.xzy * vec3(1.5, 1.0, 1.5));\n'
		//'	gl_FragColor = vec4(normal * 0.5 + 0.5, 1.0);\n'
		'\n'
		'	vec3 diffuse = vec3_splat(0.0);\n'
		'	vec3 specular = vec3_splat(0.0);\n'
		'\n'
		'	vec3 ray = u_eye - v_world.xyz;\n'
		'	float distance = length(ray);\n'
		'	vec3 dir = normalize(ray);\n'
		'	sunLight(normal, dir, 100.0, 2.0, 0.5, diffuse, specular);\n'
		'\n'
		'\n'
		'	vec2 distortion = normal.xz * (0.001 + 1.0 / distance) * u_distortion;\n'
		'	vec3 reflection = texture2D(s_mirror, v_mirrored.xy / v_mirrored.w + distortion).rgb;\n'
		//'   vec2 uv = v_mirrored.xy / v_mirrored.w + distortion;\n'
		//'   vec2 uv = v_mirrored.xy / v_mirrored.w + distortion;\n'
		//'   vec2 uv = vec2_splat(distance / 1000.0);\n'
		//'	gl_FragColor = vec4(vec3(uv.x, 0.0, uv.y), u_alpha);\n'
		//'	gl_FragColor = vec4(reflection, u_alpha);\n'
		'\n'
		'	float theta = max(dot(dir, normal), 0.0);\n'
		'	float rf0 = 0.3;\n'
		'	float reflectance = rf0 + (1.0 - rf0) * pow((1.0 - theta), 5.0);\n'
		'	vec3 scatter = max(0.0, dot(normal, dir)) * u_water_color;\n'
		'	diffuse = (u_sun_color * diffuse * 0.3 + scatter);\n' // * getShadowMask()
		'	specular = (vec3_splat(0.1) + reflection * 0.9 + reflection * specular);\n'
		'	vec3 albedo = mix(diffuse, specular, reflectance);\n'
		'	vec3 light = albedo;\n'
		'	gl_FragColor = vec4(light, u_alpha);\n'

		//THREE.ShaderChunk['tonemapping_fragment'],
		//THREE.ShaderChunk['fog_fragment'],

		'}\n';

	return shader;
}

struct WaterParams
{
	uvec2 resolution = uvec2(512U);
	float clipBias = 0.0;
	float alpha = 1.0;
	float time = 0.0;
	Texture* normals = nullptr;
	//var normalSampler = options.waterNormals != = undefined ? options.waterNormals : null;
	vec3 sunDirection = vec3(0.70707f, 0.70707f, 0.0);
	Colour sunColor = two.rgb(0xffffff); // two.rgb(0x7f7f7f);
	Colour waterColor = two.rgb(0x7f7f7f); // two.rgb(0x555555);
	//vec3 eye = vec3(0.0);
	float distortionScale = 20.0;
	float size = 1.0;
	//var side = options.side != = undefined ? options.side : THREE.FrontSide;
	bool fog = false;
};

inline Plane operator*(const mat4 mat, const Plane p)
{
	const mat4 normalmat = transpose(inverse(mat));
	const vec3 point = p.normal * -p.distance;
	const vec3 refpoint = mulp(mat, point);
	const vec3 normal = muln(mat, p.normal);
	const float d = dot(-refpoint, normal);
	return { normal, d };
}

mat4 rotation(const mat4 mat)
{
	mat4 result = mat;
	result[3] = vec4(0.0, 0.0, 0.0, 1.0);
	return result;
}

class Water : public WaterParams
{
public:
	Node3* node;
	Item* item;
	
	FrameBuffer fbo;

	mat4 mirror;
	vec3 eye;

	Material* material;

	Water() {}
	void create(GfxSystem gfx, var scene, var geometry, uvec2 resolution = uvec2(512U))
	{
		var program = gfx.programs.create('water');
		program.set_pass(two.PassType.Opaque);
		program.set_block(two.MaterialBlock.User);
		program.set_source(two.ShaderType.Vertex, water_vertex());
		program.set_source(two.ShaderType.Fragment, water_fragment());

		var material = gfx.materials.create('water', [](var m) {
			m.program = program;
		});
		material = material;

		node = scene.nodes().add(new two.Node3());
		item = scene.items().add(new two.Item(*node, geometry, 0, material));
		//THREE.Mesh.call(this, geometry);

		fbo = { resolution, btwo.gfx.TextureFormat::RGBA8 };
		
		material.submit = [this](btwo.gfx.Encoder encoder) { this.submit(encoder); };
	}

	void submit(btwo.gfx.Encoder encoder)
	{
		btwo.gfx.UniformHandle u_mirror = btwo.gfx.createUniform('u_mirror', btwo.gfx.UniformType::Mat4, 1U);

		encoder.setUniform(u_mirror, mirror);
	}

	void update(var material)
	{
		material.user.tex0 = fbo.tex;
		material.user.tex1 = normals;

		material.user.attr0 = { alpha, size, distortionScale, 0.0 };
		material.user.attr1 = { to_vec3(sunColor), 0.0 };
		material.user.attr2 = { sunDirection, 0.0 };
		material.user.attr3 = { eye, 0.0 };
		material.user.attr4 = { to_vec3(waterColor), 0.0 };
	}

	void pass_mirror(GfxSystem gfx, Render render) //(renderer, scene, camera) {
	{
		const var sourcecam = *render.camera;

		mat4 rotation = ::rotation(node.transform);
		vec3 mirror = vec3(node.transform[3]);
		//vec3 normal = muln(node.transform, Z3);
		vec3 normal = muln(rotation, Y3);
		vec3 dir = mirror - sourcecam.eye;

		// Avoid rendering when mirror is facing away
		if (dot(dir, normal) > 0) return;

		auto reflect = [](const vec3 i, const vec3 n) . vec3 { return i - 2.0 * dot(n, i) * n; };

		rotation = ::rotation(inverse(sourcecam.transform));
		vec3 eye = -reflect(dir, normal) + mirror;
		vec3 lookat = muln(rotation, -Z3) + sourcecam.eye;
		vec3 target = -reflect(mirror - lookat, normal) + mirror;
		vec3 up = reflect(muln(rotation, Y3), normal);

		Camera camera = Camera(eye, target, up, sourcecam.fov, sourcecam.aspect, sourcecam.near, sourcecam.far);

		mat4 bias = bias_mat_bgfx(btwo.gfx.getCaps().originBottomLeft, false);
		//mirror = bias * camera.projection * inverse(camera.transform);
		mirror = bias * camera.projection * camera.transform;

		//mirror = inverse(camera.transform) * camera.projection * bias;
		//mirror = camera.transform * camera.projection * bias;

		eye = vec3(inverse(sourcecam.transform)[3]); // mat4_position(camera.matrixWorld);

		item.visible = false;

		Viewport viewport = Viewport(camera, *render.scene, uvec4(uvec2(0), fbo.size));
		Render subrender = { Shading::Shaded, viewport, *render.target, fbo, gfx.render_frame };

		gfx.renderer.gather(subrender);

		// Now update projection matrix with new clip plane, implementing code from: http://www.terathon.com/code/oblique.html
		// Paper explaining this technique: http://www.terathon.com/lengyel/Lengyel-Oblique.pdf
		Plane plane = Plane(mirror, normal);
		plane = camera.transform * plane;

		vec4 clipPlane = vec4(plane.normal.x, plane.normal.y, plane.normal.z, plane.distance);

		mat4 proj = camera.projection;

		if(true)
		{
			vec4 q;
			q.x = (sign(clipPlane.x) + proj.f[8]) / proj.f[0];
			q.y = (sign(clipPlane.y) + proj.f[9]) / proj.f[5];
			q.z = -1.0;
			q.w = (1.0 + proj.f[10]) / proj.f[14];

			// Calculate the scaled plane vector
			clipPlane *= 2.0 / dot(clipPlane, q);

			// Replacing the third row of the projection matrix
			proj.f[2] = clipPlane.x;
			proj.f[6] = clipPlane.y;
			proj.f[10] = clipPlane.z + 1.0 - clipBias;
			proj.f[14] = clipPlane.w;
		}

		gfx.renderer.subrender(render, subrender, render_pbr_forward);

		item.visible = true;

		//gfx.copy.debug_show_texture(render, fbo, vec4(0.0));
	}
};

string sky_vertex()
{
	string shader =

		'$input a_position\n'
		'$output v_world, v_sundir, v_sunp0, v_betaR, v_betaM\n'
		'\n'
		'#include <common.sh>\n'
		'\n'
		'#define u_sun_position u_user_p0.xyz\n'
		'#define u_turbidity u_user_p1.x\n'
		'#define u_rayleigh u_user_p1.y\n'
		'#define u_mieCoefficient u_user_p2.x\n'

		'CONST(vec3) up = vec3(0.0, 1.0, 0.0);\n'

		// constants for atmospheric scattering
		'CONST(float) e = 2.71828182845904523536028747135266249775724709369995957;\n'
		'CONST(float) pi = 3.141592653589793238462643383279502884197169;\n'

		// wavelength of used primaries, according to preetham
		'CONST(vec3) lambda = vec3(680E-9, 550E-9, 450E-9);\n'
		// this pre-calcuation replaces older TotalRayleigh(vec3 lambda) function:
		// (8.0 * pow(pi, 3.0) * pow(pow(n, 2.0) - 1.0, 2.0) * (6.0 + 3.0 * pn)) / (3.0 * N * pow(lambda, vec3(4.0)) * (6.0 - 7.0 * pn))
		'CONST(vec3) totalRayleigh = vec3(5.804542996261093E-6, 1.3562911419845635E-5, 3.0265902468824876E-5);\n'

		// mie stuff
		// K coefficient for the primaries
		'CONST(float) v = 4.0;\n'
		'CONST(vec3) K = vec3(0.686, 0.678, 0.666);\n'
		// MieConst = pi * pow((2.0 * pi) / lambda, vec3(v - 2.0)) * K
		'CONST(vec3) MieConst = vec3(1.8399918514433978E14, 2.7798023919660528E14, 4.0790479543861094E14);\n'

		// earth shadow hack
		// cutoffAngle = pi / 1.95;
		'CONST(float) cutoffAngle = 1.6110731556870734;\n'
		'CONST(float) steepness = 1.5;\n'
		'CONST(float) EE = 1000.0;\n'

		'float sunIntensity(float zenithAngleCos) {\n'
		'	zenithAngleCos = clamp(zenithAngleCos, -1.0, 1.0);\n'
		'	return EE * max(0.0, 1.0 - pow(e, -((cutoffAngle - acos(zenithAngleCos)) / steepness)));\n'
		'}\n'

		'vec3 totalMie(float T) {\n'
		'	float c = (0.2 * T) * 10E-18;\n'
		'	return 0.434 * c * MieConst;\n'
		'}\n'

		'void main() {\n'

		'	vec4 worldPosition = mul(u_model[0], vec4(a_position.xyz, 1.0));\n'
		'	v_world = worldPosition.xyz;\n'

		'	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n'
		'	gl_Position.z = gl_Position.w;\n' // set z to camera.far

		'	v_sundir = normalize(u_sun_position);\n'

		'	float sunE = sunIntensity(dot(v_sundir, up));\n'
		'	float sunfade = 1.0 - clamp(1.0 - exp((u_sun_position.y / 450000.0)), 0.0, 1.0);\n'
		'	v_sunp0 = vec2(sunfade, sunE);\n'

		'	float rayleighCoefficient = u_rayleigh - (1.0 * (1.0 - sunfade));\n'

		// extinction (absorbtion + out scattering)
		// rayleigh coefficients
		'	v_betaR = totalRayleigh * rayleighCoefficient;\n'

		// mie coefficients
		'	v_betaM = totalMie(u_turbidity) * u_mieCoefficient;\n'

		'}\n';

	return shader;
}

string sky_fragment()
{
	string shader =

		'$input v_world, v_sundir, v_sunp0, v_betaR, v_betaM\n'
		'\n'
		'#include <common.sh>\n'
		'\n'
		'#define u_luminance u_user_p1.z\n'
		'#define u_mieDirectionalG u_user_p2.y\n'

		'CONST(vec3) cameraPos = vec3(0.0, 0.0, 0.0);\n'

		// constants for atmospheric scattering
		'CONST(float) pi = 3.141592653589793238462643383279502884197169;\n'

		'CONST(float) n = 1.0003;\n'   // refractive index of air
		'CONST(float) N = 2.545E25;\n' // number of molecules per unit volume for air at
									  // 288.15K and 1013mb (sea level -45 celsius)

		// optical length at zenith for molecules
		'CONST(float) rayleighZenithLength = 8.4E3;\n'
		'CONST(float) mieZenithLength = 1.25E3;\n'
		'CONST(vec3) up = vec3(0.0, 1.0, 0.0);\n'
		// 66 arc seconds . degrees, and the cosine of that
		'CONST(float) sunAngularDiameterCos = 0.999956676946448443553574619906976478926848692873900859324;\n'

		// 3.0 / (16.0 * pi)
		'CONST(float) d3b16pi = 0.05968310365946075;\n'
		// 1.0 / (4.0 * pi)
		'CONST(float) d1b4pi = 0.07957747154594767;\n'

		'float rayleighPhase(float cosTheta) {\n'
		'	return d3b16pi * (1.0 + pow(cosTheta, 2.0));\n'
		'}\n'

		'float hgPhase(float cosTheta, float g) {\n'
		'	float g2 = pow(g, 2.0);\n'
		'	float inverse = 1.0 / pow(1.0 - 2.0 * g * cosTheta + g2, 1.5);\n'
		'	return d1b4pi * ((1.0 - g2) * inverse);\n'
		'}\n'

		// Filmic ToneMapping http://filmicgames.com/archives/75
		'CONST(float) A = 0.15;\n'
		'CONST(float) B = 0.50;\n'
		'CONST(float) C = 0.10;\n'
		'CONST(float) D = 0.20;\n'
		'CONST(float) E = 0.02;\n'
		'CONST(float) F = 0.30;\n'

		'CONST(float) whiteScale = 1.0748724675633854;\n' // 1.0 / Uncharted2Tonemap(1000.0)

		'vec3 Uncharted2Tonemap(vec3 x) {\n'
		'	return ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;\n'
		'}\n'


		'void main() {\n'
		// optical length
		// cutoff angle at 90 to avoid singularity in next formula.
		'	float zenithAngle = acos(max(0.0, dot(up, normalize(v_world - cameraPos))));\n'
		'	float inverse = 1.0 / (cos(zenithAngle) + 0.15 * pow(93.885 - ((zenithAngle * 180.0) / pi), -1.253));\n'
		'	float sR = rayleighZenithLength * inverse;\n'
		'	float sM = mieZenithLength * inverse;\n'

		// combined extinction factor
		'	vec3 Fex = exp(-(v_betaR * sR + v_betaM * sM));\n'

		// in scattering
		'	float cosTheta = dot(normalize(v_world - cameraPos), v_sundir);\n'

		'	float rPhase = rayleighPhase(cosTheta * 0.5 + 0.5);\n'
		'	vec3 betaRTheta = v_betaR * rPhase;\n'

		'	float mPhase = hgPhase(cosTheta, u_mieDirectionalG);\n'
		'	vec3 betaMTheta = v_betaM * mPhase;\n'

		'	float sunE = v_sunp0.y;'
		'	vec3 Lin = pow(sunE * ((betaRTheta + betaMTheta) / (v_betaR + v_betaM)) * (1.0 - Fex), vec3_splat(1.5));\n'
		'	Lin *= mix(vec3_splat(1.0), pow(sunE * ((betaRTheta + betaMTheta) / (v_betaR + v_betaM)) * Fex, vec3_splat(1.0 / 2.0)), clamp(pow(1.0 - dot(up, v_sundir), 5.0), 0.0, 1.0));\n'

		// nightsky
		'	vec3 direction = normalize(v_world - cameraPos);\n'
		'	float theta = acos(direction.y);\n' // elevation -. y-axis, [-pi/2, pi/2]
		'	float phi = atan2(direction.z, direction.x);\n' // azimuth -. x-axis [-pi/2, pi/2]
		'	vec2 uv = vec2(phi, theta) / vec2(2.0 * pi, pi) + vec2(0.5, 0.0);\n'
		'	vec3 L0 = vec3_splat(0.1) * Fex;\n'

		// composition + solar disc
		'	float sundisk = smoothstep(sunAngularDiameterCos, sunAngularDiameterCos + 0.00002, cosTheta);\n'
		'	L0 += (sunE * 19000.0 * Fex) * sundisk;\n'

		'	vec3 texColor = (Lin + L0) * 0.04 + vec3(0.0, 0.0003, 0.00075);\n'

		'	vec3 curr = Uncharted2Tonemap((log2(2.0 / pow(u_luminance, 4.0))) * texColor);\n'
		'	vec3 color = curr * whiteScale;\n'

		'	float sunfade = v_sunp0.x;'
		'	vec3 retColor = pow(color, vec3_splat(1.0 / (1.2 + (1.2 * sunfade))));\n'

		'	gl_FragColor = vec4(retColor, 1.0);\n'
		//'	gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);\n'

		'}\n';

	return shader;
}

class Sky
{
public:
	Sky() {}
	void create(GfxSystem gfx, var scene)
	{
		var program = gfx.programs.create('sky');
		program.set_pass(two.PassType.Opaque);
		program.set_block(two.MaterialBlock.User);
		program.set_source(two.ShaderType.Vertex, sky_vertex());
		program.set_source(two.ShaderType.Fragment, sky_fragment());

		var material = gfx.materials.create('sky', [](var m) {
			m.program = program;
			m.base.cull_mode = CullMode::Front;
		});

		material = material;

		var geometry = gfx.shape(Cube(0.5));

		node = scene.nodes().add(new two.Node3());
		item = scene.items().add(new two.Item(*node, geometry, 0, material));

		this.update(material);
	}

	void update(var material)
	{
		material.user.attr0 = { sun_position, 0.0 };
		material.user.attr1 = { turbidity, rayleigh, luminance, 0.0 };
		material.user.attr2 = { mieCoefficient, mieDirectionalG, 0.0, 0.0 };
	}

	vec3 sun_position = Y3;
	float turbidity = 2.0; // 10.0
	float rayleigh = 1.0; // 2.0
	float luminance = 1.0;
	float mieCoefficient = 0.005;
	float mieDirectionalG = 0.8;

	Material* material;

	Item* item;
	Node3* node;
};

void xx_shader_ocean(Shell app, var parent, Dockbar dockbar, bool init)
{
	UNUSED(dockbar);
	var viewer = two.ui.scene_viewer(panel);
	//two.ui.orbit_controls(viewer);
	two.ui.orbit_controls(viewer);
	viewer.viewport.autorender = false;

	var scene = viewer.scene;

	//controls = new THREE.OrbitControls(camera, renderer.domElement);
	//controls.maxPolarAngle = c_pi * 0.495;
	//controls.target.set(0, 10, 0);
	//controls.minDistance = 40.0;
	//controls.maxDistance = 200.0;
	//camera.lookAt(controls.target);

	var pbr = app.gfx.programs.fetch('pbr/pbr');

	Node3* sphere = nullptr;
	Node3* sun = nullptr;

#if WATER
	Water water;
#endif
	Sky sky;

	struct Parameters { float distance = 400.0; float inclination = 0.49f; float azimuth = 0.205; };
	Parameters params;

	unique<CubeCamera> probe;

	if(init)
	{
		var camera = viewer.camera;
		camera.fov = 55.f; camera.near = 1.0; camera.far = 20000.0;
		camera.eye = vec3(30.0, 30.0, 100.0);

		// Sun

		vec3 light;
		var ln = scene.nodes().add(new two.Node3());
		var l = scene.lights().add(new two.Light(ln, two.LightType.Direct, false, two.rgb(0xffffff), 0.8));
		sun = ln;

		// Probe
		probe = construct<CubeCamera>(scene, 1.0, 20000.0, 256U);
		//cubeCamera.renderTarget.texture.generateMipmaps = true;
		//cubeCamera.renderTarget.texture.minFilter = THREE.LinearMipMapLinearFilter;

		// Water

		var plane = app.gfx.shape(Rect(vec2(0.0), vec2(10000.0, 10000.0)));

		var normals = app.gfx.textures.file('waternormals.jpg');
		
#if WATER
		water.create(app.gfx, scene, plane, app.gfx.main_target().size / 4U);
		water.normals = normals;
		water.alpha = 1.0;
		water.sunDirection = sun.direction();
		water.sunColor = two.rgb(0xffffff);
		water.waterColor = two.rgb(0x001e0);
		water.distortionScale = 3.7f;
#endif

		//water.rotation.x = -c_pi / 2;

		// Skybox

		sky.create(app.gfx, scene);
		sky.node.apply(vec3(0.0), ZeroQuat, vec3(10000.0));
		sky.turbidity = 10.0;
		sky.rayleigh = 2.0;

		// Sphere

#if COLOURS
		MeshPacker geo;
		Icosaedr shape = Icosaedr(20.0);
		gen_geom({ Symbol(), shape, PLAIN }, geo, PLAIN);

		//var count = geometry.attributes.position.count;

		for(size_t i = 0; i < geo.positions.size(); i += 3)
		{
			Colour color = two.rgb(randi<uint32_t>());
			geo.colours.push_back(color);
			geo.colours.push_back(color);
			geo.colours.push_back(color);
		}

		var ico = app.gfx.create_model_geo('ico', geo);
#else
		//var ico = app.gfx.shape(Icosaedr(20.0));
		var ico = app.gfx.shape(Sphere(20.0));
#endif

		var material = app.gfx.materials.create('ocean', [](var m) {
			m.program = pbr;
			m.base.flat_shaded = true;
			m.base.cull_mode = CullMode::None;
			m.base.shader_color = ShaderColor::Vertex;
			m.pbr.roughness = 0.0;
			//envMap: cubeCamera.renderTarget.texture,
		});

		var n = scene.nodes().add(new two.Node3());
		var i = scene.items().add(new two.Item(n, ico, 0, material));
		sphere = n;
		UNUSED(i);
	}

	auto updateSun = []() {
	
		float theta = c_pi * (params.inclination - 0.5);
		float phi = c_2pi * (params.azimuth - 0.5);
	
		vec3 dir = params.distance * vec3(cos(phi), sin(phi) * sin(theta), sin(phi) * cos(theta));
		sun.apply(vec3(0.0), facing(dir));

		sky.sun_position = dir;
		sky.update(*sky.material);

#if WATER
		water.sunDirection = normalize(dir);
		water.update(*water.material);
#endif
	};
	
	updateSun();

	if(Widget* dock = two.ui.dockitem(dockbar, 'Game', { 1U }))
	{
		var sheet = two.ui.sheet(*dock);

		auto panel = [](const string name) . Widget
		{
			var s = two.ui.expandbox(sheet, name.c_str());
			return two.ui.columns(s, { 0.3, 0.7f });
		};

		var a = panel('Sky');
		two.ui.slider_field_float(a, 'inclination', { params.inclination,  { 0.0, 0.5, 0.0001 } });
		two.ui.slider_field_float(a, 'azimuth',     { params.azimuth,      { 0.0, 1.0,  0.0001 } });
	
#if WATER
		var b = panel('Water');
		two.ui.slider_field_float(b, 'distortion', { water.distortionScale,	{ 0.0, 8.f, 0.1 } });
		two.ui.slider_field_float(b, 'size',		 { water.size,				{ 0.1, 10.0, 0.1 } });
		two.ui.slider_field_float(b, 'alpha',		 { water.alpha,				{ 0.9f, 1.0, 0.001 } });
#endif
	}

	const float time = app.gfx.time;

	vec3 position = vec3(0.0, sin(time) * 20.0 + 5.f, 0.0);
	vec3 angles = vec3(time * 0.5, 0.0, time * 0.51);
	sphere.apply(position, quat(angles));

	//water.material.uniforms['time'].value += 1.0 / 60.0;

	Render render = { Shading::Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame };
	app.gfx.renderer.gather(render);
	app.gfx.renderer.begin(render);

	begin_pbr_render(app.gfx, render);

#if WATER
	water.pass_mirror(app.gfx, render);
#endif

	auto renderer = [](GfxSystem gfx, Render render)
	{
		pass_clear(gfx, render);
		//pass_opaque(gfx, render);
		pass_background(gfx, render);
	};

	probe.render(app.gfx, render, renderer);
	scene.env.radiance.texture = probe.cubemap.cubemap;

	pass_clear(app.gfx, render);
	pass_opaque(app.gfx, render);
	pass_background(app.gfx, render);

	app.gfx.renderer.end(render);
}