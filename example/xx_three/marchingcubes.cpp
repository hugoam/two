#include <xx_three/xx_three.h>
#include <gfx-pbr/Api.h>

#include <geom/Primitive.hpp>
#include <stl/vector.hpp>

#include <cstdio>
#include <cstring>

using namespace two;

#define DIRECT 1
#define NORMAL 1

// @author mrdoob / http://mrdoob.com/
// @author alteredq / http://alteredqualia.com/

static string normal_vertex =

	"$input a_position, a_normal\n"
	"$output v_normal\n"

	"#include <common.sh>\n"

	"void main()\n"
	"{\n"
		"gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
		"v_normal = normalize(mul(u_modelView, vec4(a_normal, 0.0)).xyz);\n"
		//"v_normal = normalize(normalMatrix * a_normal);\n"
	"}\n";

static string toon1_vertex =

	"$input a_position, a_normal\n"
	"$output v_normal, v_refract\n"

	"void main()\n"
	"{\n"
		"vec4 world = mul(u_model[0], vec4(a_position.xyz, 1.0));\n"
		"vec4 view = mul(u_modelView, vec4(a_position.xyz, 1.0));\n"
		"vec3 worldNormal = normalize(mul(u_model[0], vec4(a_normal, 0.0));\n"

		"v_normal = normalize(mul(u_modelView, vec4(a_normal, 0.0)));\n"

		"vec3 I = world.xyz - cameraPosition;\n"
		"v_refract = refract(normalize(I), worldNormal, 1.02);\n"

		"gl_Position = mul(u_proj, view);\n"
	"}\n";

static string toon1_fragment =

	"$input v_normal, v_refract\n"

	"#include <common.sh>\n"

	"#define toon_color1 p0.xyz\n"
	"#define toon_color2 p0.xyz\n"

	"#define light_dir   p1.xyz\n"
	"#define light_color p2.xyz\n"

	"#define ambient p3.xyz\n"

	"void main()\n"
	"{\n"
		"int material_index = int(u_state_material);\n"
		"SolidMaterial solid = read_solid_material(material_index);\n"
		"UserMaterial mat = read_user_material(material_index);\n"

		"float directionalLightWeighting = max(dot(normalize(v_normal), -mat.light_dir), 0.0);\n"
		"vec3 lightWeighting = mat.ambient + mat.light_color * directionalLightWeighting;\n"

		"float intensity = smoothstep(- 0.5, 1.0, pow(length(lightWeighting), 20.0));\n"
		"intensity += length(lightWeighting) * 0.2;\n"

		"float cameraWeighting = dot(normalize(v_normal), v_refract);\n"
		"intensity += pow(1.0 - length(cameraWeighting), 6.0);\n"
		"intensity = intensity * 0.2 + 0.3;\n"

		"if (intensity < 0.50) {\n"
			"gl_FragColor = vec4(2.0 * intensity * solid.color.rgb, 1.0);\n"
		"} else {\n"
			"gl_FragColor = vec4(1.0 - 2.0 * (1.0 - intensity) * (1.0 - solid.color.rgb), 1.0);\n"
		"}\n"
	"}\n";

static Program& toon1_program(GfxSystem& gfx)
{
	static Program& program = gfx.programs().create("toon1");
	program.set_source(ShaderType::Vertex, toon1_vertex);
	program.set_source(ShaderType::Fragment, toon1_fragment);
	return program;
}

static string toon2_vertex =
	normal_vertex;

static string toon2_fragment =

	"$input v_normal\n"

	"#include <common.sh>\n"

	"#define toon_color1 p0.xyz\n"
	"#define toon_color2 p0.xyz\n"

	"#define light_dir   p1.xyz\n"
	"#define light_color p2.xyz\n"

	"#define ambient     p3.xyz\n"

	"void main()\n"
	"{\n"
		"int material_index = int(u_state_material);\n"
		"SolidMaterial solid = read_solid_material(material_index);\n"

		"float camera = max(dot(normalize(v_normal), vec3(0.0, 0.0, 1.0)), 0.4);\n"
		"float light = max(dot(normalize(v_normal), -u_light_dir), 0.0);\n"

		"gl_FragColor = vec4(solid.color.rgb, 1.0);\n"

		"if (length(u_ambient + u_light_color * light) < 1.00) {\n"
			"gl_FragColor *= vec4(u_toon_color1, 1.0);\n" // uLineColor1
		"}\n"

		"if (length(u_ambient + u_light_color * camera) < 0.50) {\n"
			"gl_FragColor *= vec4(u_toon_color1, 1.0);\n" // uLineColor2
		"}\n"
	"}\n";

static Program& toon2_program(GfxSystem& gfx)
{
	static Program& program = gfx.programs().create("toon2");
	program.set_source(ShaderType::Vertex, toon2_vertex);
	program.set_source(ShaderType::Fragment, toon2_fragment);
	return program;
}

static string hatching_vertex =
	normal_vertex;

static string hatching_fragment =

	"$input v_normal\n"

	"#include <common.sh>\n"

	"#define hatch_color p0.xyz\n"

	"#define light_dir   p1.xyz\n"
	"#define light_color p2.xyz\n"

	"#define ambient     p3.xyz\n"

	"void main()\n"
	"{\n"
		"int material_index = int(u_state_material);\n"
		"SolidMaterial solid = read_solid_material(material_index);\n"
		"UserMaterial mat = read_user_material(material_index);\n"

		"float directionalLightWeighting = max(dot(normalize(v_normal), -mat.light_dir), 0.0);\n"
		"vec3 lightWeighting = mat.ambient + mat.light_color * directionalLightWeighting;\n"

		"gl_FragColor = vec4(solid.color.rgb, 1.0);\n"

		"if (length(lightWeighting) < 1.00) {\n"
			"if (mod(gl_FragCoord.x + gl_FragCoord.y, 10.0) == 0.0) {\n"
				"gl_FragColor = vec4(mat.hatch_color, 1.0);\n" // uLineColor1
			"}\n"
		"}\n"

		"if (length(lightWeighting) < 0.75) {\n"
			"if (mod(gl_FragCoord.x - gl_FragCoord.y, 10.0) == 0.0) {\n"
				"gl_FragColor = vec4(mat.hatch_color, 1.0);\n" // uLineColor2
			"}\n"
		"}\n"

		"if (length(lightWeighting) < 0.50) {\n"
			"if (mod(gl_FragCoord.x + gl_FragCoord.y - 5.0, 10.0) == 0.0) {\n"
				"gl_FragColor = vec4(mat.hatch_color, 1.0);\n" // uLineColor3
			"}\n"
		"}\n"

		"if (length(lightWeighting) < 0.3465) {\n"
			"if (mod(gl_FragCoord.x - gl_FragCoord.y - 5.0, 10.0) == 0.0) {\n"
				"gl_FragColor = vec4(mat.hatch_color, 1.0);\n" // uLineColor4
			"}\n"
		"}\n"
	"}\n";

static Program& hatching_program(GfxSystem& gfx)
{
	static Program& program = gfx.programs().create("hatching");
	program.set_source(ShaderType::Vertex, hatching_vertex);
	program.set_source(ShaderType::Fragment, hatching_fragment);
	return program;
}

static string dotted_vertex =
	normal_vertex;

static string dotted_fragment =

	"$input v_normal\n"

	"#include <common.sh>\n"

	"#define dot_color   p0.xyz\n"

	"#define light_dir   p1.xyz\n"
	"#define light_color p2.xyz\n"

	"#define ambient     p3.xyz\n"

	"void main()\n"
	"{\n"
		"int material_index = int(u_state_material);\n"
		"SolidMaterial solid = read_solid_material(material_index);\n"
		"UserMaterial mat = read_user_material(material_index);\n"

		"float directionalLightWeighting = max(dot(normalize(v_normal), -mat.light_dir), 0.0);\n"
		"vec3 lightWeighting = mat.ambient + mat.light_color * directionalLightWeighting;\n"

		"gl_FragColor = vec4(solid.color.rgb, 1.0);\n"

		"if (length(lightWeighting) < 1.00) {\n"
			"if ((mod(gl_FragCoord.x, 4.001) + mod(gl_FragCoord.y, 4.0)) > 6.00) {\n"
				"gl_FragColor = vec4(mat.dot_color, 1.0);\n"
			"}\n"
		"}\n"

		"if (length(lightWeighting) < 0.50) {\n"
			"if ((mod(gl_FragCoord.x + 2.0, 4.001) + mod(gl_FragCoord.y + 2.0, 4.0)) > 6.00) {\n"
				"gl_FragColor = vec4(mat.dot_color, 1.0);\n"
			"}\n"
		"}\n"
	"}\n";

static Program& dotted_program(GfxSystem& gfx)
{
	static Program& program = gfx.programs().create("dotted");
	program.set_source(ShaderType::Vertex, dotted_vertex);
	program.set_source(ShaderType::Fragment, dotted_fragment);
	program.set_blocks({ MaterialBlock::Solid, MaterialBlock::User });
	return program;
}

struct ExMaterial { string name; Material* material; ColourHSL color; };

vector<ExMaterial> gen_materials(GfxSystem& gfx, const string& prefix)
{
	vector<ExMaterial> materials;

	auto add = [&](const string& name, auto init)
	{
		materials.push_back({ name, &gfx.materials().create(prefix + name), {} });
		ExMaterial& m = materials.back();
		init(*m.material, m.color);
	};

	add("normal", [&](Material& m, ColourHSL& hsl) { m.m_program = &gfx.programs().fetch("normal"); });
	
	// toons

	add("toon1", [&](Material& m, ColourHSL& hsl) { m.m_program = &toon1_program(gfx); hsl = { 0.2f, 1.f, 0.75f }; });

	add("toon2", [&](Material& m, ColourHSL& hsl) { m.m_program = &toon2_program(gfx); hsl = { 0.4f, 1.f, 0.75f }; });

	add("hatching", [&](Material& m, ColourHSL& hsl) {
		m.m_program = &hatching_program(gfx);
		hsl = { 0.2f, 1.f, 0.9f };
	});

	add("dotted", [&](Material& m, ColourHSL& hsl) {
		m.m_program = &dotted_program(gfx); m.m_user.m_attr0 = vec4(to_vec3(rgb(0x000000)), 0.f);
		hsl = { 0.2f, 1.f, 0.9f };
	});

	Texture& texture = *gfx.textures().file("UV_Grid_Sm.jpg");

	Program& pbr = gfx.programs().fetch("pbr/pbr");
	Program& lambert = gfx.programs().fetch("pbr/lambert");
	Program& phong = gfx.programs().fetch("pbr/phong");

	add("chrome", [&](Material& m, ColourHSL& hsl) { m.m_program = &lambert; hsl = { 0.f, 0.f, 1.f }; });
	
	add("liquid", [&](Material& m, ColourHSL& hsl) { m.m_program = &lambert; m.m_phong.m_refraction = 0.85f;  hsl = { 0.f, 0.f, 1.f }; });
	
	add("shiny", [&](Material& m, ColourHSL& hsl) {
		m.m_program = &pbr; m.m_pbr.m_albedo = rgb(0x550000); m.m_pbr.m_roughness = 0.1f; m.m_pbr.m_metallic = 1.f;
		hsl = { 0.f, 0.8f, 0.2f };
	});

	add("matte", [&](Material& m, ColourHSL& hsl) {
		m.m_program = &phong; m.m_phong.m_specular = rgb(0x111111); m.m_phong.m_shininess = 1.f; m.m_lit.m_no_envmap = true;
		hsl = { 0.f, 0.f, 1.f };
	});

	add("flat", [&](Material& m, ColourHSL& hsl) {
		m.m_program = &phong; m.m_base.m_flat_shaded = true; m.m_lit.m_no_envmap = true;
		hsl = { 0.f, 0.f, 1.f };
	});

	add("textured", [&](Material& m, ColourHSL& hsl) {
		m.m_program = &phong; m.m_phong.m_diffuse.m_texture = &texture; 
		m.m_phong.m_specular = rgb(0x111111); m.m_phong.m_shininess = 1.f;
		hsl = { 0.f, 0.f, 1.f };
	});

	add("colors", [&](Material& m, ColourHSL& hsl) {
		m.m_program = &phong; m.m_phong.m_specular = rgb(0xffffff); m.m_phong.m_shininess = 2.f;
		m.m_base.m_shader_color = ShaderColor::Vertex; m.m_lit.m_no_envmap = true;
		hsl = { 0.f, 0.f, 1.f };
	});

	add("multiColors", [&](Material& m, ColourHSL& hsl) {
		m.m_program = &phong; m.m_phong.m_shininess = 2.f;
		m.m_base.m_shader_color = ShaderColor::Vertex; m.m_lit.m_no_envmap = true;
		hsl = { 0.f, 0.f, 1.f };
	});

	add("plastic", [&](Material& m, ColourHSL& hsl) {
		m.m_program = &phong; m.m_phong.m_specular = rgb(0x888888); m.m_phong.m_shininess = 250.f;
		m.m_lit.m_no_envmap = true;
		hsl = { 0.6f, 0.8f, 0.1f };
	});
	
	return materials;
}

vector<cstring> material_labels(span<ExMaterial> materials)
{
	vector<cstring> vec;
	for(ExMaterial& m : materials)
		vec.push_back(m.name.c_str());
	return vec;
}

void upload_cubes(MarchingCubes& cubes, Mesh& mesh, bool colors, bool uvs)
{
	const uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal
		| (colors ? VertexAttribute::Colour : 0)
		| (uvs ? VertexAttribute::TexCoord0 : 0);

#if DIRECT
	const uint32_t num_tris = cubes.count();
	
	if(num_tris == 0) return;
	const uint32_t vertex_count = num_tris * 3;

	MeshAdapter& direct = mesh.direct(vertex_format, vertex_count);
	cubes.direct(direct);
#else
	static MeshPacker geometry;
	geometry.clear();

	cubes.render(geometry);

	if(geometry.vertex_count() == 0) return;
	const uint32_t vertex_count = geometry.vertex_count();

	MeshAdapter& direct = mesh.direct(vertex_format, vertex_count);
	geometry.pack(direct);
#endif
}

EX(xx_marching_cubes)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	struct Controller
	{
		Material* material = nullptr;

		float speed = 1.f;
		uint32_t numBlobs = 10;
		uint32_t resolution = 28;
		float isolation = 80.f;

		bool floor = true;
		bool wallx = false;
		bool wallz = false;

		float lhue = 0.f;
		float lsaturation = 0.8f;
		float llightness = 0.1f;

		float lx = 0.5f;
		float ly = 0.5f;
		float lz = 1.0f;
	};

	static Controller controller = {};
	static vector<ExMaterial> materials;
	static ExMaterial* current = nullptr;

	constexpr uint32_t resolution = 28;

	static MarchingCubes cubes = { resolution };
	static Mesh* mesh = nullptr;
	static Item* item = nullptr;
	static Node3* nlight = nullptr;
	static Light* light = nullptr;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 45.f; camera.m_near = 1.f; camera.m_far = 10000.f;
		camera.m_eye = vec3(-500.f, 500.f, 1500.f);


		Model& model = app.m_gfx.create_model("cubes");
		mesh = model.m_items[0].m_mesh;
		mesh->m_is_direct = true;

		Texture& reflection = *app.m_gfx.textures().file("cube/royal.jpg.cube");

		viewer.m_viewport.m_to_gamma = true;
		viewer.m_viewport.m_clear_colour = to_linear(rgb(0x050505));

		Zone& env = scene.m_env;
		env.m_background.m_colour = rgb(0x050505);
		env.m_radiance.m_texture = &reflection;
		//env.m_radiance.m_filter = false;
		env.m_radiance.m_ambient = rgb(0x080808);

		vec3 t = look_dir(-normalize(vec3(0.5f, 0.5f, 1.f))) * -z3;

		Node3& l0 = gfx::nodes(scene).add(Node3(vec3(0.f), look_dir(-vec3(0.5f, 0.5f, 1.f))));
		Light& l = gfx::lights(scene).add(Light(l0, LightType::Direct, false, rgb(0xffffff)));
		nlight = &l0;
		light = &l;

		Node3& l1 = gfx::nodes(scene).add(Node3(vec3(0.f, 0.f, 100.f)));
		gfx::lights(scene).add(Light(l1, LightType::Point, false, rgb(0xff3300), 1.f, 0.f));

		materials = gen_materials(app.m_gfx, "marching");
		current = &materials[7];

		Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f), ZeroQuat, vec3(700.f)));
		Item& it = gfx::items(scene).add(Item(n, model, 0U, current->material));
		item = &it;
	}

#if UI
	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Widget& sheet = ui::sheet(*dock);

		auto panel = [&](const string& name) -> Widget&
		{
			Widget& s = ui::expandbox(sheet, name.c_str());
			return ui::columns(s, { 0.3f, 0.7f });
		};

		// material (type)

		Widget& a = panel("Material");

		static vector<cstring> labels = material_labels(materials);
		static uint32_t material_index = 0;
		bool changed = ui::radio_switch(sheet, labels, material_index, Axis::Y);
		//bool changed = ui::dropdown_field(sheet, "material", labels, material_index);
		if(changed)
		{
			current = &materials[material_index];
			item->m_material = current->material;
		}

		// material (color)

		Widget& b = panel("Material color");

		ui::slider_field(b, "hue",        current->color.h, { 0.f, 1.f, 0.025f });
		ui::slider_field(b, "saturation", current->color.s, { 0.f, 1.f, 0.025f });
		ui::slider_field(b, "lightness",  current->color.l, { 0.f, 1.f, 0.025f });

		// light (point)

		Widget& c = panel("Point light color");

		ui::slider_field(c, "hue",        controller.lhue,        { 0.f, 1.f, 0.025f });
		ui::slider_field(c, "saturation", controller.lsaturation, { 0.f, 1.f, 0.025f });
		ui::slider_field(c, "lightness",  controller.llightness,  { 0.f, 1.f, 0.025f });

		// light (directional)

		Widget& d = panel("Directional light orientation");

		ui::slider_field(d, "x", controller.lx, { -1.f, 1.f, 0.025f });
		ui::slider_field(d, "y", controller.ly, { -1.f, 1.f, 0.025f });
		ui::slider_field(d, "z", controller.lz, { -1.f, 1.f, 0.025f });

		// simulation

		Widget& e = panel("Simulation");

		ui::slider_field(e,    "speed",      controller.speed,      { 0.1f, 8.0f, 0.05f });
		ui::slider_field(e, "numBlobs",   controller.numBlobs,   { 1, 50, 1 });
		ui::slider_field(e, "resolution", controller.resolution, { 14, 100, 1 });
		ui::slider_field(e,    "isolation",  controller.isolation,  { 10.f, 300.f, 1.f });

		ui::field(e, "floor", controller.floor);
		ui::field(e, "wallx", controller.wallx);
		ui::field(e, "wallz", controller.wallz);
	}
#endif

	// this controls content of marching cubes voxel field

	static float time = 0.f;

	auto add_blobs = [&](MarchingCubes& object, float time, float numblobs, bool floor, bool wallx, bool wallz)
	{
		object.reset();

		// fill the field with some metaballs

		static const Colour rainbow[] = 
			{ rgb(0xff0000), rgb(0xff7f00), rgb(0xffff00), rgb(0x00ff00), rgb(0x0000ff), rgb(0x4b0082), rgb(0x9400d3) };

		float subtract = 12.f;
		float strength = 1.2f / ((sqrt(numblobs) - 1.f) / 4.f + 1.f);

		for(size_t i = 0; i < numblobs; i++)
		{
			float fi = float(i);
			float ballx = sin(fi + 1.26f * time * (1.03f + 0.5f * cos(0.21f * fi))) * 0.27f + 0.5f;
			float bally = abs(cos(fi + 1.12f * time * cos(1.22f + 0.1424f * fi))) * 0.77f; // dip into the floor
			float ballz = cos(fi + 1.32f * time * 0.1f * sin((0.92f + 0.53f * fi))) * 0.27f + 0.5f;

			if(current->name == "multiColors")
				add_ball(object, vec3(ballx, bally, ballz), strength, subtract, rainbow[i % 7]);
			else
				add_ball(object, vec3(ballx, bally, ballz), strength, subtract);
		}

		if(floor) add_planeY(object, 2, 12);
		if(wallz) add_planeZ(object, 2, 12);
		if(wallx) add_planeX(object, 2, 12);
	};

	float delta = app.m_gfx.m_frame_time;

	time += delta * controller.speed * 0.5f;

	// marching cubes

	if(controller.resolution != cubes.m_subdiv)
		cubes = { controller.resolution };

	cubes.m_isolation = controller.isolation;

	add_blobs(cubes, time, controller.numBlobs, controller.floor, controller.wallx, controller.wallz);

	const bool need_colors = current->material->m_base.m_shader_color == ShaderColor::Vertex;
	const bool need_uvs = false;
	upload_cubes(cubes, *mesh, need_colors, need_uvs);

	// materials

	current->material->m_solid.m_colour = hsl(current->color);
	current->material->m_pbr.m_albedo = hsl(current->color);
	current->material->m_phong.m_diffuse = hsl(current->color);
	
	current->material->m_user.m_attr1 = vec4(nlight->direction(), 0.f);
	current->material->m_user.m_attr2 = vec4(to_vec3(light->m_colour) * light->m_energy, 0.f);

	current->material->m_user.m_attr3 = vec4(to_vec3(scene.m_env.m_radiance.m_ambient), 0.f);

	viewer.m_viewport.m_to_gamma = current->name != "normal";

	//if(effect.material instanceof THREE.ShaderMaterial) {
	//
	//	if(current_material == "dotted2") {
	//
	//		effect.material.uniforms["uLineColor1"].value.setHSL(effectController.hue, effectController.saturation, effectController.lightness);
	//
	//	}
	//	else if(current_material == "hatching2") {
	//
	//		var u = effect.material.uniforms;
	//
	//		u.uLineColor1.value.setHSL(effectController.hue, effectController.saturation, effectController.lightness);
	//		u.uLineColor2.value.setHSL(effectController.hue, effectController.saturation, effectController.lightness);
	//		u.uLineColor3.value.setHSL(effectController.hue, effectController.saturation, effectController.lightness);
	//		u.uLineColor4.value.setHSL((effectController.hue + 0.2 % 1.0), effectController.saturation, effectController.lightness);
	//
	//	}
	//	else {
	//
	//		effect.material.uniforms["uBaseColor"].value.setHSL(effectController.hue, effectController.saturation, effectController.lightness);
	//
	//	}
	//
	//}
	//else {
	//
	//	effect.material.color.setHSL(effectController.hue, effectController.saturation, effectController.lightness);
	//
	//}

	// lights

	//light.position.set(effectController.lx, effectController.ly, effectController.lz);
	//light.position.normalize();
	//
	//pointLight.color.setHSL(effectController.lhue, effectController.lsaturation, effectController.llightness);
}
