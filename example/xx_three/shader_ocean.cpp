//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

#define WATER 1
#define COLOURS 1

string water_vertex =

	"$input a_position\n"
	"$output v_world, v_mirrored\n"
		
	"#include <common.sh>\n"
		
	"uniform mat4 u_mirror;\n"
		
	//THREE.ShaderChunk['fog_pars_vertex'],
	//THREE.ShaderChunk['shadowmap_pars_vertex'],
		
	"void main() {\n"
	"	vec4 world = mul(u_model[0], vec4(a_position.xyz, 1.0));\n"
	"	v_world = world.xyz;\n"
	"	v_mirrored = mul(u_mirror, world);\n"
	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
		
	//THREE.ShaderChunk['fog_vertex'],
	//THREE.ShaderChunk['shadowmap_vertex'],
	"}\n";

string water_fragment =

	"$input v_world, v_mirrored\n"
		
	"#include <common.sh>\n"
		
	"#define s_mirror s_user0\n"
	"#define s_normal s_user1\n"
		
	"#define u_alpha u_user_p0.x\n"
	"#define u_size u_user_p0.y\n"
	"#define u_distortion u_user_p0.z\n"
	"#define u_sun_color u_user_p1.xyz\n"
	"#define u_sun_dir u_user_p2.xyz\n"
	"#define u_eye u_user_p3.xyz\n"
	"#define u_water_color u_user_p4.xyz\n"
		
	"vec4 getNoise(vec2 uv) {\n"
	"	vec2 uv0 = (uv / 103.0) + vec2(u_time / 17.0, u_time / 29.0);\n"
	"	vec2 uv1 = uv / 107.0 - vec2(u_time / -19.0, u_time / 31.0);\n"
	"	vec2 uv2 = uv / vec2(8907.0, 9803.0) + vec2(u_time / 101.0, u_time / 97.0);\n"
	"	vec2 uv3 = uv / vec2(1091.0, 1027.0) - vec2(u_time / 109.0, u_time / -113.0);\n"
	"	vec4 noise = texture2D(s_normal, uv0) +\n"
	"		texture2D(s_normal, uv1) +\n"
	"		texture2D(s_normal, uv2) +\n"
	"		texture2D(s_normal, uv3);\n"
	"	return noise * 0.5 - 1.0;\n"
	"}\n"
		
	"void sunLight(vec3 normal, vec3 view, float shiny, float fspec, float fdiff, inout vec3 diffuse, inout vec3 specular) {\n"
	"	vec3 reflection = normalize(reflect(-u_sun_dir, normal));\n"
	"	float direction = max(0.0, dot(view, reflection));\n"
	"	specular += pow(direction, shiny) * u_sun_color * fspec;\n"
	"	diffuse += max(dot(u_sun_dir, normal), 0.0) * u_sun_color * fdiff;\n"
	"}\n"

	//THREE.ShaderChunk['common'],
	//THREE.ShaderChunk['packing'],
	//THREE.ShaderChunk['bsdfs'],
	//THREE.ShaderChunk['fog_pars_fragment'],
	//THREE.ShaderChunk['lights_pars_begin'],
	//THREE.ShaderChunk['shadowmap_pars_fragment'],
	//THREE.ShaderChunk['shadowmask_pars_fragment'],

	"void main() {\n"
	"	vec4 noise = getNoise(v_world.xz * u_size);\n"
	"	vec3 normal = normalize(noise.xzy * vec3(1.5, 1.0, 1.5));\n"
	//"	gl_FragColor = vec4(normal * 0.5 + 0.5, 1.0);\n"
		
	"	vec3 diffuse = vec3_splat(0.0);\n"
	"	vec3 specular = vec3_splat(0.0);\n"
		
	"	vec3 ray = u_eye - v_world.xyz;\n"
	"	float distance = length(ray);\n"
	"	vec3 dir = normalize(ray);\n"
	"	sunLight(normal, dir, 100.0, 2.0, 0.5, diffuse, specular);\n"
		
		
	"	vec2 distortion = normal.xz * (0.001 + 1.0 / distance) * u_distortion;\n"
	"	vec3 reflection = texture2D(s_mirror, v_mirrored.xy / v_mirrored.w + distortion).rgb;\n"
	//"   vec2 uv = v_mirrored.xy / v_mirrored.w + distortion;\n"
	//"   vec2 uv = v_mirrored.xy / v_mirrored.w + distortion;\n"
	//"   vec2 uv = vec2_splat(distance / 1000.0);\n"
	//"	gl_FragColor = vec4(vec3(uv.x, 0.0, uv.y), u_alpha);\n"
	//"	gl_FragColor = vec4(reflection, u_alpha);\n"
		
	"	float theta = max(dot(dir, normal), 0.0);\n"
	"	float rf0 = 0.3;\n"
	"	float reflectance = rf0 + (1.0 - rf0) * pow((1.0 - theta), 5.0);\n"
	"	vec3 scatter = max(0.0, dot(normal, dir)) * u_water_color;\n"
	"	diffuse = (u_sun_color * diffuse * 0.3 + scatter);\n" // * getShadowMask()
	"	specular = (vec3_splat(0.1) + reflection * 0.9 + reflection * specular);\n"
	"	vec3 albedo = mix(diffuse, specular, reflectance);\n"
	"	vec3 light = albedo;\n"
	"	gl_FragColor = vec4(light, u_alpha);\n"

	//THREE.ShaderChunk['tonemapping_fragment'],
	//THREE.ShaderChunk['fog_fragment'],

	"}\n";

struct WaterParams
{
	uvec2 resolution = uvec2(512U);
	float clipBias = 0.0f;
	float alpha = 1.0f;
	float time = 0.0f;
	Texture* normals = nullptr;
	//var normalSampler = options.waterNormals != = undefined ? options.waterNormals : null;
	vec3 sunDirection = vec3(0.70707f, 0.70707f, 0.0f);
	Colour sunColor = rgb(0xffffff); // rgb(0x7f7f7f);
	Colour waterColor = rgb(0x7f7f7f); // rgb(0x555555);
	//vec3 eye = vec3(0.f);
	float distortionScale = 20.f;
	float size = 1.f;
	//var side = options.side != = undefined ? options.side : THREE.FrontSide;
	bool fog = false;
};

inline Plane operator*(const mat4& mat, const Plane& p)
{
	const mat4 normalmat = transpose(inverse(mat));
	const vec3 point = p.m_normal * -p.m_distance;
	const vec3 refpoint = mulp(mat, point);
	const vec3 normal = muln(mat, p.m_normal);
	const float d = dot(-refpoint, normal);
	return { normal, d };
}

mat4 rotation(const mat4& mat)
{
	mat4 result = mat;
	result[3] = vec4(0.f, 0.f, 0.f, 1.f);
	return result;
}

class Water : public WaterParams
{
public:
	Node3* m_node;
	Item* m_item;
	
	FrameBuffer m_fbo;

	mat4 m_mirror;
	vec3 m_eye;

	Material* m_material;

	Water() {}
	void create(GfxSystem& gfx, Scene& scene, Model& geometry, const uvec2& resolution = uvec2(512U))
	{
		static Program& program = gfx.programs().create("water");
		program.set_pass(PassType::Opaque);
		program.set_block(MaterialBlock::User);
		program.set_source(ShaderType::Vertex, water_vertex);
		program.set_source(ShaderType::Fragment, water_fragment);

		Material& material = gfx.materials().create("water", [&](Material& m) {
			m.m_program = &program;
		});
		m_material = &material;

		m_node = &gfx::nodes(scene).add(Node3());
		m_item = &gfx::items(scene).add(Item(*m_node, geometry, 0U, &material));
		//THREE.Mesh.call(this, geometry);

		m_fbo = { resolution, TextureFormat::RGBA8 };
		
		material.m_submit = [this](bgfx::Encoder& encoder) { this->submit(encoder); };
	}

	void submit(bgfx::Encoder& encoder)
	{
		static bgfx::UniformHandle u_mirror = bgfx::createUniform("u_mirror", bgfx::UniformType::Mat4, 1U);

		encoder.setUniform(u_mirror, &m_mirror);
	}

	void update(Material& material)
	{
		material.m_user.m_tex0 = &m_fbo.m_tex;
		material.m_user.m_tex1 = normals;

		material.m_user.m_attr0 = { alpha, size, distortionScale, 0.f };
		material.m_user.m_attr1 = { to_vec3(sunColor), 0.f };
		material.m_user.m_attr2 = { sunDirection, 0.f };
		material.m_user.m_attr3 = { m_eye, 0.f };
		material.m_user.m_attr4 = { to_vec3(waterColor), 0.f };
	}

	void pass_mirror(GfxSystem& gfx, Render& render) //(renderer, scene, camera) {
	{
		const Camera& sourcecam = *render.m_camera;

		mat4 rotation = ::rotation(m_node->m_transform);
		vec3 mirror = vec3(m_node->m_transform[3]);
		//vec3 normal = muln(m_node->m_transform, Z3);
		vec3 normal = muln(rotation, Y3);
		vec3 dir = mirror - sourcecam.m_eye;

		// Avoid rendering when mirror is facing away
		if (dot(dir, normal) > 0) return;

		auto reflect = [](const vec3& i, const vec3& n) -> vec3 { return i - 2.f * dot(n, i) * n; };

		rotation = ::rotation(inverse(sourcecam.m_transform));
		vec3 eye = -reflect(dir, normal) + mirror;
		vec3 lookat = muln(rotation, -Z3) + sourcecam.m_eye;
		vec3 target = -reflect(mirror - lookat, normal) + mirror;
		vec3 up = reflect(muln(rotation, Y3), normal);

		Camera camera = Camera(eye, target, up, sourcecam.m_fov, sourcecam.m_aspect, sourcecam.m_near, sourcecam.m_far);

		static mat4 bias = bias_mat_bgfx(bgfx::getCaps()->originBottomLeft, false);
		//m_mirror = bias * camera.m_projection * inverse(camera.m_transform);
		m_mirror = bias * camera.m_projection * camera.m_transform;

		//m_mirror = inverse(camera.m_transform) * camera.m_projection * bias;
		//m_mirror = camera.m_transform * camera.m_projection * bias;

		m_eye = vec3(inverse(sourcecam.m_transform)[3]); // mat4_position(camera.matrixWorld);

		m_item->m_visible = false;

		Viewport viewport = Viewport(camera, *render.m_scene, Rect4);
		Render subrender = { Shading::Shaded, viewport, *render.m_target, m_fbo, gfx.m_render_frame };

		gfx.m_renderer.gather(subrender);

		// Now update projection matrix with new clip plane, implementing code from: http://www.terathon.com/code/oblique.html
		// Paper explaining this technique: http://www.terathon.com/lengyel/Lengyel-Oblique.pdf
		Plane plane = Plane(mirror, normal);
		plane = camera.m_transform * plane;

		vec4 clipPlane = vec4(plane.m_normal.x, plane.m_normal.y, plane.m_normal.z, plane.m_distance);

		mat4& proj = camera.m_projection;

		if(true)
		{
			vec4 q;
			q.x = (sign(clipPlane.x) + proj.f[8]) / proj.f[0];
			q.y = (sign(clipPlane.y) + proj.f[9]) / proj.f[5];
			q.z = -1.0f;
			q.w = (1.0f + proj.f[10]) / proj.f[14];

			// Calculate the scaled plane vector
			clipPlane *= 2.f / dot(clipPlane, q);

			// Replacing the third row of the projection matrix
			proj.f[2] = clipPlane.x;
			proj.f[6] = clipPlane.y;
			proj.f[10] = clipPlane.z + 1.0f - clipBias;
			proj.f[14] = clipPlane.w;
		}

		gfx.m_renderer.subrender(render, subrender, render_pbr_forward);

		m_item->m_visible = true;

		//gfx.m_copy->debug_show_texture(render, m_fbo, vec4(0.f));
	}
};

static string sky_vertex =

	"$input a_position\n"
	"$output v_world, v_sundir, v_sunp0, v_betaR, v_betaM\n"
		
	"#include <common.sh>\n"
		
	"#define u_sun_position u_user_p0.xyz\n"
	"#define u_turbidity u_user_p1.x\n"
	"#define u_rayleigh u_user_p1.y\n"
	"#define u_mieCoefficient u_user_p2.x\n"

	"CONST(vec3) up = vec3(0.0, 1.0, 0.0);\n"

	// constants for atmospheric scattering
	"CONST(float) e = 2.71828182845904523536028747135266249775724709369995957;\n"
	"CONST(float) pi = 3.141592653589793238462643383279502884197169;\n"

	// wavelength of used primaries, according to preetham
	"CONST(vec3) lambda = vec3(680E-9, 550E-9, 450E-9);\n"
	// this pre-calcuation replaces older TotalRayleigh(vec3 lambda) function:
	// (8.0 * pow(pi, 3.0) * pow(pow(n, 2.0) - 1.0, 2.0) * (6.0 + 3.0 * pn)) / (3.0 * N * pow(lambda, vec3(4.0)) * (6.0 - 7.0 * pn))
	"CONST(vec3) totalRayleigh = vec3(5.804542996261093E-6, 1.3562911419845635E-5, 3.0265902468824876E-5);\n"

	// mie stuff
	// K coefficient for the primaries
	"CONST(float) v = 4.0;\n"
	"CONST(vec3) K = vec3(0.686, 0.678, 0.666);\n"
	// MieConst = pi * pow((2.0 * pi) / lambda, vec3(v - 2.0)) * K
	"CONST(vec3) MieConst = vec3(1.8399918514433978E14, 2.7798023919660528E14, 4.0790479543861094E14);\n"

	// earth shadow hack
	// cutoffAngle = pi / 1.95;
	"CONST(float) cutoffAngle = 1.6110731556870734;\n"
	"CONST(float) steepness = 1.5;\n"
	"CONST(float) EE = 1000.0;\n"

	"float sunIntensity(float zenithAngleCos) {\n"
	"	zenithAngleCos = clamp(zenithAngleCos, -1.0, 1.0);\n"
	"	return EE * max(0.0, 1.0 - pow(e, -((cutoffAngle - acos(zenithAngleCos)) / steepness)));\n"
	"}\n"

	"vec3 totalMie(float T) {\n"
	"	float c = (0.2 * T) * 10E-18;\n"
	"	return 0.434 * c * MieConst;\n"
	"}\n"

	"void main() {\n"

	"	vec4 worldPosition = mul(u_model[0], vec4(a_position.xyz, 1.0));\n"
	"	v_world = worldPosition.xyz;\n"

	"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
	"	gl_Position.z = gl_Position.w;\n" // set z to camera.far

	"	v_sundir = normalize(u_sun_position);\n"

	"	float sunE = sunIntensity(dot(v_sundir, up));\n"
	"	float sunfade = 1.0 - clamp(1.0 - exp((u_sun_position.y / 450000.0)), 0.0, 1.0);\n"
	"	v_sunp0 = vec2(sunfade, sunE);\n"

	"	float rayleighCoefficient = u_rayleigh - (1.0 * (1.0 - sunfade));\n"

	// extinction (absorbtion + out scattering)
	// rayleigh coefficients
	"	v_betaR = totalRayleigh * rayleighCoefficient;\n"

	// mie coefficients
	"	v_betaM = totalMie(u_turbidity) * u_mieCoefficient;\n"

	"}\n";

static string sky_fragment =

	"$input v_world, v_sundir, v_sunp0, v_betaR, v_betaM\n"
		
	"#include <common.sh>\n"
		
	"#define u_luminance u_user_p1.z\n"
	"#define u_mieDirectionalG u_user_p2.y\n"

	"CONST(vec3) cameraPos = vec3(0.0, 0.0, 0.0);\n"

	// constants for atmospheric scattering
	"CONST(float) pi = 3.141592653589793238462643383279502884197169;\n"

	"CONST(float) n = 1.0003;\n"   // refractive index of air
	"CONST(float) N = 2.545E25;\n" // number of molecules per unit volume for air at
									// 288.15K and 1013mb (sea level -45 celsius)

	// optical length at zenith for molecules
	"CONST(float) rayleighZenithLength = 8.4E3;\n"
	"CONST(float) mieZenithLength = 1.25E3;\n"
	"CONST(vec3) up = vec3(0.0, 1.0, 0.0);\n"
	// 66 arc seconds -> degrees, and the cosine of that
	"CONST(float) sunAngularDiameterCos = 0.999956676946448443553574619906976478926848692873900859324;\n"

	// 3.0 / (16.0 * pi)
	"CONST(float) d3b16pi = 0.05968310365946075;\n"
	// 1.0 / (4.0 * pi)
	"CONST(float) d1b4pi = 0.07957747154594767;\n"

	"float rayleighPhase(float cosTheta) {\n"
	"	return d3b16pi * (1.0 + pow(cosTheta, 2.0));\n"
	"}\n"

	"float hgPhase(float cosTheta, float g) {\n"
	"	float g2 = pow(g, 2.0);\n"
	"	float inverse = 1.0 / pow(1.0 - 2.0 * g * cosTheta + g2, 1.5);\n"
	"	return d1b4pi * ((1.0 - g2) * inverse);\n"
	"}\n"

	// Filmic ToneMapping http://filmicgames.com/archives/75
	"CONST(float) A = 0.15;\n"
	"CONST(float) B = 0.50;\n"
	"CONST(float) C = 0.10;\n"
	"CONST(float) D = 0.20;\n"
	"CONST(float) E = 0.02;\n"
	"CONST(float) F = 0.30;\n"

	"CONST(float) whiteScale = 1.0748724675633854;\n" // 1.0 / Uncharted2Tonemap(1000.0)

	"vec3 Uncharted2Tonemap(vec3 x) {\n"
	"	return ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;\n"
	"}\n"


	"void main() {\n"
	// optical length
	// cutoff angle at 90 to avoid singularity in next formula.
	"	float zenithAngle = acos(max(0.0, dot(up, normalize(v_world - cameraPos))));\n"
	"	float inverse = 1.0 / (cos(zenithAngle) + 0.15 * pow(93.885 - ((zenithAngle * 180.0) / pi), -1.253));\n"
	"	float sR = rayleighZenithLength * inverse;\n"
	"	float sM = mieZenithLength * inverse;\n"

	// combined extinction factor
	"	vec3 Fex = exp(-(v_betaR * sR + v_betaM * sM));\n"

	// in scattering
	"	float cosTheta = dot(normalize(v_world - cameraPos), v_sundir);\n"

	"	float rPhase = rayleighPhase(cosTheta * 0.5 + 0.5);\n"
	"	vec3 betaRTheta = v_betaR * rPhase;\n"

	"	float mPhase = hgPhase(cosTheta, u_mieDirectionalG);\n"
	"	vec3 betaMTheta = v_betaM * mPhase;\n"

	"	float sunE = v_sunp0.y;"
	"	vec3 Lin = pow(sunE * ((betaRTheta + betaMTheta) / (v_betaR + v_betaM)) * (1.0 - Fex), vec3_splat(1.5));\n"
	"	Lin *= mix(vec3_splat(1.0), pow(sunE * ((betaRTheta + betaMTheta) / (v_betaR + v_betaM)) * Fex, vec3_splat(1.0 / 2.0)), clamp(pow(1.0 - dot(up, v_sundir), 5.0), 0.0, 1.0));\n"

	// nightsky
	"	vec3 direction = normalize(v_world - cameraPos);\n"
	"	float theta = acos(direction.y);\n" // elevation --> y-axis, [-pi/2, pi/2]
	"	float phi = atan2(direction.z, direction.x);\n" // azimuth --> x-axis [-pi/2, pi/2]
	"	vec2 uv = vec2(phi, theta) / vec2(2.0 * pi, pi) + vec2(0.5, 0.0);\n"
	"	vec3 L0 = vec3_splat(0.1) * Fex;\n"

	// composition + solar disc
	"	float sundisk = smoothstep(sunAngularDiameterCos, sunAngularDiameterCos + 0.00002, cosTheta);\n"
	"	L0 += (sunE * 19000.0 * Fex) * sundisk;\n"

	"	vec3 texColor = (Lin + L0) * 0.04 + vec3(0.0, 0.0003, 0.00075);\n"

	"	vec3 curr = Uncharted2Tonemap((log2(2.0 / pow(u_luminance, 4.0))) * texColor);\n"
	"	vec3 color = curr * whiteScale;\n"

	"	float sunfade = v_sunp0.x;"
	"	vec3 retColor = pow(color, vec3_splat(1.0 / (1.2 + (1.2 * sunfade))));\n"

	"	gl_FragColor = vec4(retColor, 1.0);\n"
	//"	gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);\n"

	"}\n";

class Sky
{
public:
	Sky() {}
	void create(GfxSystem& gfx, Scene& scene)
	{
		static Program& program = gfx.programs().create("sky");
		program.set_pass(PassType::Opaque);
		program.set_block(MaterialBlock::User);
		program.set_source(ShaderType::Vertex, sky_vertex);
		program.set_source(ShaderType::Fragment, sky_fragment);

		Material& material = gfx.materials().create("sky", [&](Material& m) {
			m.m_program = &program;
			m.m_base.m_cull_mode = CullMode::Front;
		});

		m_material = &material;

		Model& geometry = gfx.shape(Cube(0.5f));

		m_node = &gfx::nodes(scene).add(Node3());
		m_item = &gfx::items(scene).add(Item(*m_node, geometry, 0U, &material));

		this->update(material);
	}

	void update(Material& material)
	{
		material.m_user.m_attr0 = { m_sun_position, 0.f };
		material.m_user.m_attr1 = { m_turbidity, m_rayleigh, m_luminance, 0.f };
		material.m_user.m_attr2 = { m_mieCoefficient, m_mieDirectionalG, 0.f, 0.f };
	}

	vec3 m_sun_position = Y3;
	float m_turbidity = 2.f; // 10.f
	float m_rayleigh = 1.f; // 2.f
	float m_luminance = 1.f;
	float m_mieCoefficient = 0.005f;
	float m_mieDirectionalG = 0.8f;

	Material* m_material;

	Item* m_item;
	Node3* m_node;
};

void xx_shader_ocean(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);
	ui::orbit_controls(viewer);
	viewer.m_viewport.m_autorender = false;

	Scene& scene = viewer.m_scene;

	//controls = new THREE.OrbitControls(camera, renderer.domElement);
	//controls.maxPolarAngle = c_pi * 0.495;
	//controls.target.set(0, 10, 0);
	//controls.minDistance = 40.0;
	//controls.maxDistance = 200.0;
	//camera.lookAt(controls.target);

	static Program& pbr = app.m_gfx.programs().fetch("pbr/pbr");

	static Node3* sphere = nullptr;
	static Node3* sun = nullptr;

#if WATER
	static Water water;
#endif
	static Sky sky;

	struct Parameters { float distance = 400.f; float inclination = 0.49f; float azimuth = 0.205f; };
	Parameters params;

	static unique<CubeCamera> probe;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 55.f; camera.m_near = 1.f; camera.m_far = 20000.f;
		camera.m_eye = vec3(30.f, 30.f, 100.f);

		// Sun

		vec3 light;
		Node3& ln = gfx::nodes(scene).add(Node3());
		Light& l = gfx::lights(scene).add(Light(ln, LightType::Direct, false, rgb(0xffffff), 0.8f));
		sun = &ln;

		// Probe
		probe = construct<CubeCamera>(scene, 1.f, 20000.f, 256U);
		//cubeCamera.renderTarget.texture.generateMipmaps = true;
		//cubeCamera.renderTarget.texture.minFilter = THREE.LinearMipMapLinearFilter;

		// Water

		Model& plane = app.m_gfx.shape(Rect(vec2(0.f), vec2(10000.f, 10000.f)));

		Texture& normals = *app.m_gfx.textures().file("waternormals.jpg");
		
#if WATER
		water.create(app.m_gfx, scene, plane, app.m_gfx.main_target().m_size / 4U);
		water.normals = &normals;
		water.alpha = 1.f;
		water.sunDirection = sun->direction();
		water.sunColor = rgb(0xffffff);
		water.waterColor = rgb(0x001e0f);
		water.distortionScale = 3.7f;
#endif

		//water.rotation.x = -c_pi / 2;

		// Skybox

		sky.create(app.m_gfx, scene);
		sky.m_node->apply(vec3(0.f), ZeroQuat, vec3(10000.f));
		sky.m_turbidity = 10.f;
		sky.m_rayleigh = 2.f;

		// Sphere

#if COLOURS
		MeshPacker geo;
		Icosaedr shape = Icosaedr(20.f);
		gen_geom({ Symbol(), &shape, PLAIN }, geo, PLAIN);

		//var count = geometry.attributes.position.count;

		for(size_t i = 0; i < geo.m_positions.size(); i += 3)
		{
			Colour color = rgb(randi<uint32_t>());
			geo.m_colours.push_back(color);
			geo.m_colours.push_back(color);
			geo.m_colours.push_back(color);
		}

		Model& ico = app.m_gfx.create_model_geo("ico", geo);
#else
		//Model& ico = app.m_gfx.shape(Icosaedr(20.f));
		Model& ico = app.m_gfx.shape(Sphere(20.f));
#endif

		Material& material = app.m_gfx.materials().create("ocean", [](Material& m) {
			m.m_program = &pbr;
			m.m_base.m_flat_shaded = true;
			m.m_base.m_cull_mode = CullMode::None;
			m.m_base.m_shader_color = ShaderColor::Vertex;
			m.m_pbr.m_roughness = 0.f;
			//envMap: cubeCamera.renderTarget.texture,
		});

		Node3& n = gfx::nodes(scene).add(Node3());
		Item& i = gfx::items(scene).add(Item(n, ico, 0U, &material));
		sphere = &n;
		UNUSED(i);
	}

	auto updateSun = [&]() {
	
		float theta = c_pi * (params.inclination - 0.5f);
		float phi = c_2pi * (params.azimuth - 0.5f);
	
		vec3 dir = params.distance * vec3(cos(phi), sin(phi) * sin(theta), sin(phi) * cos(theta));
		sun->apply(vec3(0.f), facing(dir));

		sky.m_sun_position = dir;
		sky.update(*sky.m_material);

#if WATER
		water.sunDirection = normalize(dir);
		water.update(*water.m_material);
#endif
	};
	
	updateSun();

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Widget& sheet = ui::sheet(*dock);

		auto panel = [&](const string& name) -> Widget&
		{
			Widget& s = ui::expandbox(sheet, name.c_str());
			return ui::columns(s, { 0.3f, 0.7f });
		};

		Widget& a = panel("Sky");
		ui::slider_field<float>(a, "inclination", { params.inclination,  { 0.f, 0.5f, 0.0001f } });
		ui::slider_field<float>(a, "azimuth",     { params.azimuth,      { 0.f, 1.f,  0.0001f } });
	
#if WATER
		Widget& b = panel("Water");
		ui::slider_field<float>(b, "distortion", { water.distortionScale,	{ 0.f, 8.f, 0.1f } });
		ui::slider_field<float>(b, "size",		 { water.size,				{ 0.1f, 10.f, 0.1f } });
		ui::slider_field<float>(b, "alpha",		 { water.alpha,				{ 0.9f, 1.f, 0.001f } });
#endif
	}

	const float time = app.m_gfx.m_time;

	vec3 position = vec3(0.f, sin(time) * 20.f + 5.f, 0.f);
	vec3 angles = vec3(time * 0.5f, 0.f, time * 0.51f);
	sphere->apply(position, quat(angles));

	//water.material.uniforms["time"].value += 1.0 / 60.0;

	Render render = { Shading::Shaded, viewer.m_viewport, app.m_gfx.main_target(), app.m_gfx.m_render_frame };
	app.m_gfx.m_renderer.gather(render);
	app.m_gfx.m_renderer.begin(render);

	begin_pbr_render(app.m_gfx, render);

#if WATER
	water.pass_mirror(app.m_gfx, render);
#endif

	auto renderer = [](GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
		//pass_opaque(gfx, render);
		pass_background(gfx, render);
	};

	probe->render(app.m_gfx, render, renderer);
	scene.m_env.m_radiance.m_texture = &probe->m_cubemap.m_cubemap;

	pass_clear(app.m_gfx, render);
	pass_opaque(app.m_gfx, render);
	pass_background(app.m_gfx, render);

	app.m_gfx.m_renderer.end(render);
}