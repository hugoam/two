//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <geom/Primitive.hpp>
#include <stl/vector.hpp>

#include <cstdio>
#include <cstring>

using namespace mud;

#define DIRECT 1
#define NORMAL 1

/**
 * @author mrdoob / http://mrdoob.com/
 * @author alteredq / http://alteredqualia.com/
 *
 * ShaderToon currently contains:
 *
 *	toon1
 *	toon2
 *	hatching
 *	dotted
 */

#if 0
uniforms: {

	"uDirLightPos": { value: new THREE.Vector3() },
	"uDirLightColor": { value: new THREE.Color( 0xeeeeee ) },

	"uAmbientLightColor": { value: new THREE.Color( 0x050505 ) },

	"uBaseColor": { value: new THREE.Color( 0xffffff ) }

},
#endif

static string toon1_vertex()
{
	string shader = 

		"varying vec3 vNormal;\n"
		"varying vec3 vRefract;\n"

		"void main() {\n"

			"vec4 worldPosition = modelMatrix * vec4( position, 1.0 );\n"
			"vec4 mvPosition = modelViewMatrix * vec4( position, 1.0 );\n"
			"vec3 worldNormal = normalize ( mat3( modelMatrix[0].xyz, modelMatrix[1].xyz, modelMatrix[2].xyz ) * normal );\n"

			"vNormal = normalize( normalMatrix * normal );\n"

			"vec3 I = worldPosition.xyz - cameraPosition;\n"
			"vRefract = refract( normalize( I ), worldNormal, 1.02 );\n"

			"gl_Position = projectionMatrix * mvPosition;\n"

		"}\n";

	return shader;
}
static string toon1_fragment()
{
	string shader =

		"uniform vec3 uBaseColor;\n"

		"uniform vec3 uDirLightPos;\n"
		"uniform vec3 uDirLightColor;\n"

		"uniform vec3 uAmbientLightColor;\n"

		"varying vec3 vNormal;\n"

		"varying vec3 vRefract;\n"

		"void main() {\n"

			"float directionalLightWeighting = max( dot( normalize( vNormal ), uDirLightPos ), 0.0);\n"
			"vec3 lightWeighting = uAmbientLightColor + uDirLightColor * directionalLightWeighting;\n"

			"float intensity = smoothstep( - 0.5, 1.0, pow( length(lightWeighting), 20.0 ) );\n"
			"intensity += length(lightWeighting) * 0.2;\n"

			"float cameraWeighting = dot( normalize( vNormal ), vRefract );\n"
			"intensity += pow( 1.0 - length( cameraWeighting ), 6.0 );\n"
			"intensity = intensity * 0.2 + 0.3;\n"

			"if ( intensity < 0.50 ) {\n"

				"gl_FragColor = vec4( 2.0 * intensity * uBaseColor, 1.0 );\n"

			"} else {\n"

				"gl_FragColor = vec4( 1.0 - 2.0 * ( 1.0 - intensity ) * ( 1.0 - uBaseColor ), 1.0 );\n"

			"}\n"

		"}\n";

	return shader;
}

static Program& toon1_program(GfxSystem& gfx)
{
	static Program& program = gfx.programs().create("toon1");
	program.set_source(ShaderType::Vertex, toon1_vertex());
	program.set_source(ShaderType::Fragment, toon1_fragment());
	return program;
}

#if 0
uniforms: {

	"uDirLightPos": { value: new THREE.Vector3() },
	"uDirLightColor": { value: new THREE.Color( 0xeeeeee ) },

	"uAmbientLightColor": { value: new THREE.Color( 0x050505 ) },

	"uBaseColor": { value: new THREE.Color( 0xeeeeee ) },
	"uLineColor1": { value: new THREE.Color( 0x808080 ) },
	"uLineColor2": { value: new THREE.Color( 0x000000 ) },
	"uLineColor3": { value: new THREE.Color( 0x000000 ) },
	"uLineColor4": { value: new THREE.Color( 0x000000 ) }

},
#endif

static string toon2_vertex()
{
	string shader =

			"varying vec3 vNormal;\n"

			"void main() {\n"

				"gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );\n"
				"vNormal = normalize( normalMatrix * normal );\n"

			"}\n";

	return shader;
}

static string toon2_fragment()
{
	string shader =

		"uniform vec3 uBaseColor;\n"
		"uniform vec3 uLineColor1;\n"
		"uniform vec3 uLineColor2;\n"
		"uniform vec3 uLineColor3;\n"
		"uniform vec3 uLineColor4;\n"

		"uniform vec3 uDirLightPos;\n"
		"uniform vec3 uDirLightColor;\n"

		"uniform vec3 uAmbientLightColor;\n"

		"varying vec3 vNormal;\n"

		"void main() {\n"

			"float camera = max( dot( normalize( vNormal ), vec3( 0.0, 0.0, 1.0 ) ), 0.4);\n"
			"float light = max( dot( normalize( vNormal ), uDirLightPos ), 0.0);\n"

			"gl_FragColor = vec4( uBaseColor, 1.0 );\n"

			"if ( length(uAmbientLightColor + uDirLightColor * light) < 1.00 ) {\n"

				"gl_FragColor *= vec4( uLineColor1, 1.0 );\n"

			"}\n"

			"if ( length(uAmbientLightColor + uDirLightColor * camera) < 0.50 ) {\n"

				"gl_FragColor *= vec4( uLineColor2, 1.0 );\n"

			"}\n"

		"}\n";

	return shader;
}

static Program& toon2_program(GfxSystem& gfx)
{
	static Program& program = gfx.programs().create("toon2");
	program.set_source(ShaderType::Vertex, toon2_vertex());
	program.set_source(ShaderType::Fragment, toon2_fragment());
	return program;
}

#if 0
"uDirLightPos":	{ value: new THREE.Vector3() },
"uDirLightColor": { value: new THREE.Color( 0xeeeeee ) },

"uAmbientLightColor": { value: new THREE.Color( 0x050505 ) },

"uBaseColor":  { value: new THREE.Color( 0xffffff ) },
"uLineColor1": { value: new THREE.Color( 0x000000 ) },
"uLineColor2": { value: new THREE.Color( 0x000000 ) },
"uLineColor3": { value: new THREE.Color( 0x000000 ) },
"uLineColor4": { value: new THREE.Color( 0x000000 ) }
#endif

static string hatching_vertex()
{
	string shader =

		"varying vec3 vNormal;\n"

		"void main() {\n"

			"gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );\n"
			"vNormal = normalize( normalMatrix * normal );\n"

		"}\n";

	return shader;
}

static string hatching_fragment()
{
	string shader =

		"uniform vec3 uBaseColor;\n"
		"uniform vec3 uLineColor1;\n"
		"uniform vec3 uLineColor2;\n"
		"uniform vec3 uLineColor3;\n"
		"uniform vec3 uLineColor4;\n"

		"uniform vec3 uDirLightPos;\n"
		"uniform vec3 uDirLightColor;\n"

		"uniform vec3 uAmbientLightColor;\n"

		"varying vec3 vNormal;\n"

		"void main() {\n"

			"float directionalLightWeighting = max( dot( normalize(vNormal), uDirLightPos ), 0.0);\n"
			"vec3 lightWeighting = uAmbientLightColor + uDirLightColor * directionalLightWeighting;\n"

			"gl_FragColor = vec4( uBaseColor, 1.0 );\n"

			"if ( length(lightWeighting) < 1.00 ) {\n"

				"if ( mod(gl_FragCoord.x + gl_FragCoord.y, 10.0) == 0.0) {\n"

					"gl_FragColor = vec4( uLineColor1, 1.0 );\n"

				"}\n"

			"}\n"

			"if ( length(lightWeighting) < 0.75 ) {\n"

				"if (mod(gl_FragCoord.x - gl_FragCoord.y, 10.0) == 0.0) {\n"

					"gl_FragColor = vec4( uLineColor2, 1.0 );\n"

				"}\n"
			"}\n"

			"if ( length(lightWeighting) < 0.50 ) {\n"

				"if (mod(gl_FragCoord.x + gl_FragCoord.y - 5.0, 10.0) == 0.0) {\n"

					"gl_FragColor = vec4( uLineColor3, 1.0 );\n"

				"}\n"
			"}\n"

			"if ( length(lightWeighting) < 0.3465 ) {\n"

				"if (mod(gl_FragCoord.x - gl_FragCoord.y - 5.0, 10.0) == 0.0) {\n"

					"gl_FragColor = vec4( uLineColor4, 1.0 );\n"

				"}\n"
			"}\n"

		"}\n";

	return shader;
}

static Program& hatching_program(GfxSystem& gfx)
{
	static Program& program = gfx.programs().create("hatching");
	program.set_source(ShaderType::Vertex, hatching_vertex());
	program.set_source(ShaderType::Fragment, hatching_fragment());
	return program;
}

#if 0
	"uDirLightPos":	{ value: new THREE.Vector3() },
	"uDirLightColor": { value: new THREE.Color( 0xeeeeee ) },

	"uAmbientLightColor": { value: new THREE.Color( 0x050505 ) },

	"uBaseColor":  { value: new THREE.Color( 0xffffff ) },
	"uLineColor1": { value: new THREE.Color( 0x000000 ) }
#endif

static string dotted_vertex()
{
	string shader =

		"varying vec3 vNormal;\n"

		"void main() {\n"

			"gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );\n"
			"vNormal = normalize( normalMatrix * normal );\n"

		"}\n";

	return shader;
}

static string dotted_fragment()
{
	string shader =

		"uniform vec3 uBaseColor;\n"
		"uniform vec3 uLineColor1;\n"
		"uniform vec3 uLineColor2;\n"
		"uniform vec3 uLineColor3;\n"
		"uniform vec3 uLineColor4;\n"

		"uniform vec3 uDirLightPos;\n"
		"uniform vec3 uDirLightColor;\n"

		"uniform vec3 uAmbientLightColor;\n"

		"varying vec3 vNormal;\n"

		"void main() {\n"

			"float directionalLightWeighting = max( dot( normalize(vNormal), uDirLightPos ), 0.0);\n"
			"vec3 lightWeighting = uAmbientLightColor + uDirLightColor * directionalLightWeighting;\n"

			"gl_FragColor = vec4( uBaseColor, 1.0 );\n"

			"if ( length(lightWeighting) < 1.00 ) {\n"

				"if ( ( mod(gl_FragCoord.x, 4.001) + mod(gl_FragCoord.y, 4.0) ) > 6.00 ) {\n"

					"gl_FragColor = vec4( uLineColor1, 1.0 );\n"

				"}\n"

			"}\n"

			"if ( length(lightWeighting) < 0.50 ) {\n"

				"if ( ( mod(gl_FragCoord.x + 2.0, 4.001) + mod(gl_FragCoord.y + 2.0, 4.0) ) > 6.00 ) {\n"

					"gl_FragColor = vec4( uLineColor1, 1.0 );\n"

				"}\n"

			"}\n"

		"}\n";
	
	return shader;
}

static Program& dotted_program(GfxSystem& gfx)
{
	static Program& program = gfx.programs().create("dotted");
	program.set_source(ShaderType::Vertex, dotted_vertex());
	program.set_source(ShaderType::Fragment, dotted_fragment());
	return program;
}

//function createShaderMaterial(id, light, ambientLight) {
//
//	material.uniforms["uDirLightPos"].value = light.position;
//	material.uniforms["uDirLightColor"].value = light.color;
//
//	material.uniforms["uAmbientLightColor"].value = ambientLight.color;
//
//}

struct DottedMaterial
{
	Colour m_base_color;
	Colour m_line_color1;
};

struct HatchingMaterial
{
	Colour m_base_color;
	Colour m_line_color1;
	Colour m_line_color2;
	Colour m_line_color3;
	Colour m_line_color4;
};

vector<Material*> gen_materials(GfxSystem& gfx, const string& prefix)
{
	Material& normal = gfx.materials().create(prefix + "normal", [&](Material& m) { m.m_program = &gfx.programs().fetch("normal"); });

	// toons

	Material& toon1 = gfx.materials().create(prefix + "toon1", [&](Material& m) { m.m_program = &toon1_program(gfx); });
	// h : 0.2, s : 1, l : 0.75

	Material& toon2 = gfx.materials().create(prefix + "toon2", [&](Material& m) { m.m_program = &toon2_program(gfx); });
	// h : 0.4, s : 1, l : 0.75

	Material& hatching1 = gfx.materials().create(prefix + "hatching", [&](Material& m) { m.m_program = &hatching_program(gfx); });
	// h : 0.2, s : 1, l : 0.9

	Material& hatching2 = gfx.materials().create(prefix + "hatching2", [&](Material& m) { m.m_program = &hatching_program(gfx); });
	// h : 0.0, s : 0.8, l : 0.5

	Material& dotted1 = gfx.materials().create(prefix + "dotted", [&](Material& m) { m.m_program = &dotted_program(gfx); });
	// h : 0.2, s : 1, l : 0.9

	Material& dotted2 = gfx.materials().create(prefix + "dotted2", [&](Material& m) { m.m_program = &dotted_program(gfx); });
	// h : 0.1, s : 1, l : 0.5

	HatchingMaterial h2;
	h2.m_base_color = Colour(0.f);
	h2.m_line_color1 = hsl(0.f, 0.8f, 0.5f);
	h2.m_line_color2 = hsl(0.f, 0.8f, 0.5f);
	h2.m_line_color3 = hsl(0.f, 0.8f, 0.5f);
	h2.m_line_color4 = hsl(0.1f, 0.8f, 0.5f);

	DottedMaterial d2;
	d2.m_base_color = Colour(0.f);
	d2.m_line_color1 = hsl(0.05f, 1.0f, 0.5f);

	Texture& texture = *gfx.textures().file("UV_Grid_Sm.jpg");
	//texture.wrapS = texture.wrapT = THREE.RepeatWrapping;

	Program& pbr = *gfx.programs().file("pbr/pbr");

	//new THREE.MeshLambertMaterial({ color: 0xffffff, envMap : reflectionCube });
	Material& chrome = gfx.materials().create("chrome", [&](Material& m) { m.m_program = &pbr; m.m_pbr.m_metallic = 1.f; });
	// h : 0, s : 0, l : 1

	// new THREE.MeshLambertMaterial({ color: 0xffffff, envMap : refractionCube, refractionRatio : 0.85 })
	Material& liquid = gfx.materials().create("liquid", [&](Material& m) { m.m_program = &pbr; m.m_pbr.m_metallic = 1.f; m.m_pbr.m_refraction = 0.85f; });
	// h : 0, s : 0, l : 1

	// new THREE.MeshStandardMaterial({ color: 0x550000, envMap : reflectionCube, roughness : 0.1, metalness : 1.0 })
	Material& shiny = gfx.materials().create("shiny", [&](Material& m) { m.m_program = &pbr; m.m_pbr.m_roughness = 0.1f; m.m_pbr.m_metallic = 1.f; });
	// h : 0, s : 0.8, l : 0.2

	// new THREE.MeshPhongMaterial({ color: 0x000000, specular : 0x111111, shininess : 1 })
	Material& matte = gfx.materials().create("matte", [&](Material& m) { m.m_program = &pbr; m.m_pbr.m_roughness = 1.f; });
	// h : 0, s : 0, l : 1
	
	// new THREE.MeshLambertMaterial({ color: 0x000000, flatShading : true })
	Material& flat = gfx.materials().create("flat", [&](Material& m) { m.m_program = &pbr; m.m_base.m_flat_shaded = true; });
	// h : 0, s : 0, l : 1
	
	// new THREE.MeshPhongMaterial({ color: 0xffffff, specular : 0x111111, shininess : 1, map : texture })
	Material& textured = gfx.materials().create("textured", [&](Material& m) { m.m_program = &pbr; m.m_pbr.m_albedo = &texture; });
	// h : 0, s : 0, l : 1	
	
	// new THREE.MeshPhongMaterial({ color: 0xffffff, specular : 0xffffff, shininess : 2, vertexColors : THREE.VertexColors })
	Material& colors = gfx.materials().create("colors", [&](Material& m) { m.m_program = &pbr; m.m_base.m_shader_color = ShaderColor::Vertex; m.m_pbr.m_roughness = 0.9f; });
	// h : 0, s : 0, l : 1	

	// new THREE.MeshPhongMaterial({ color: 0x000000, specular : 0x888888, shininess : 250 })
	Material& plastic = gfx.materials().create("plastic", [&](Material& m) { m.m_program = &pbr; m.m_pbr.m_albedo = rgb(0x000000); m.m_pbr.m_roughness = 0.f; });
	// h : 0.6, s : 0.8, l : 0.1

	vector<Material*> materials = { &chrome, &liquid, &shiny, &matte, &flat, &textured, &colors, &plastic, &toon1, &toon2, &hatching1, &hatching2, &dotted1, &dotted2 };
	return materials;
}

vector<cstring> material_labels(span<Material*> materials)
{
	vector<cstring> vec;
	for(Material* m : materials)
		vec.push_back(m->m_name.c_str());
	return vec;
}

void upload_cubes(MarchingCubes& cubes, Mesh& mesh)
{
#if DIRECT
	const uint32_t num_tris = cubes.count();
	
	if(num_tris == 0) return;
	//uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal | VertexAttribute::TexCoord0;
	const uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal;
	const uint32_t vertex_count = num_tris * 3;

	MeshAdapter& direct = mesh.direct(vertex_format, vertex_count);
	cubes.direct(direct);
#else
	static MeshPacker geometry;
	geometry.clear();

	cubes.render(geometry);

	if(geometry.vertex_count() == 0) return;
	//uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal | VertexAttribute::TexCoord0;
	const uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal;
	const uint32_t vertex_count = geometry.vertex_count();

	MeshAdapter& direct = mesh.direct(vertex_format, vertex_count);
	geometry.pack(direct);
#endif
}

void xx_marching_cubes(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);

	Scene& scene = viewer.m_scene;

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

		float hue = 0.f;
		float saturation = 0.8f;
		float lightness = 0.1f;

		float lhue = 0.f;
		float lsaturation = 0.8f;
		float llightness = 0.1f;

		float lx = 0.5f;
		float ly = 0.5f;
		float lz = 1.0f;
	};

	static Controller controller = {};
	static vector<Material*> materials;
	static Material* material = nullptr;

	constexpr uint32_t resolution = 28;

	static MarchingCubes cubes = { resolution };
	static Mesh* mesh = nullptr;
	static Item* item = nullptr;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 45.f; camera.m_near = 1.f; camera.m_far = 10000.f;
		camera.m_eye = vec3(-500.f, 500.f, 1500.f);

		Texture& reflection = *app.m_gfx.textures().file("cube/royal.jpg.cube");
		scene.m_env.m_radiance.m_energy = 1.f;
		scene.m_env.m_radiance.m_texture = &reflection;

		Model& model = app.m_gfx.create_model("cubes");
		mesh = model.m_items[0].m_mesh;
		mesh->m_is_direct = true;

		//scene.background = new THREE.Color(0x050505);

		Node3& l0 = gfx::nodes(scene).add(Node3(vec3(0.f), quat(facing(vec3(0.5f, 0.5f, 1.f)))));
		gfx::lights(scene).add(Light(l0, LightType::Direct, false, rgb(0xffffff)));
		
		Node3& l1 = gfx::nodes(scene).add(Node3(vec3(0.f, 0.f, 100.f)));
		gfx::lights(scene).add(Light(l1, LightType::Point, false, rgb(0xff3300)));

		//ambientLight = new THREE.AmbientLight(0x080808);
		//scene.add(ambientLight);

		materials = gen_materials(app.m_gfx, "marching");
		material = materials[0];
		//material = "shiny";

		Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f), ZeroQuat, vec3(700.f)));
		Item& it = gfx::items(scene).add(Item(n, model, 0U, material));
		item = &it;
	}

	//static float h, s, l;
	//
	//auto set_material = []()
	//{
	//	current_material = id;
	//
	//	var mat = materials[id];
	//	effect.material = mat.m;
	//
	//	h = mat.h;
	//	s = mat.s;
	//	l = mat.l;
	//
	//	//effect.enableUvs = (current_material == "textured") ? true : false;
	//	//effect.enableColors = (current_material == "colors") ? true : false;
	//};

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
		//bool changed = ui::radio_switch(sheet, labels, material_index, Axis::Y);
		bool changed = ui::dropdown_field(sheet, "material", labels, material_index);
		if(changed)
		{
			material = materials[material_index];
			item->m_material = material;
		}

		// material (color)


		Widget& b = panel("Material color");

		ui::slider_field<float>(b, "hue",        { controller.hue,        { 0.f, 1.f, 0.025f } });
		ui::slider_field<float>(b, "saturation", { controller.saturation, { 0.f, 1.f, 0.025f } });
		ui::slider_field<float>(b, "lightness",  { controller.lightness,  { 0.f, 1.f, 0.025f } });

		// light (point)

		Widget& c = panel("Point light color");

		ui::slider_field<float>(c, "hue",        { controller.lhue,        { 0.f, 1.f, 0.025f } });
		ui::slider_field<float>(c, "saturation", { controller.lsaturation, { 0.f, 1.f, 0.025f } });
		ui::slider_field<float>(c, "lightness",  { controller.llightness,  { 0.f, 1.f, 0.025f } });

		// light (directional)

		Widget& d = panel("Directional light orientation");

		ui::slider_field<float>(d, "x", { controller.lx, { -1.f, 1.f, 0.025f } });
		ui::slider_field<float>(d, "y", { controller.ly, { -1.f, 1.f, 0.025f } });
		ui::slider_field<float>(d, "z", { controller.lz, { -1.f, 1.f, 0.025f } });

		// simulation

		Widget& e = panel("Simulation");

		ui::slider_field<float>(e,    "speed",      { controller.speed,      { 0.1f, 8.0f, 0.05f } });
		ui::slider_field<uint32_t>(e, "numBlobs",   { controller.numBlobs,   { 1, 50, 1 } });
		ui::slider_field<uint32_t>(e, "resolution", { controller.resolution, { 14, 100, 1 } });
		ui::slider_field<float>(e,    "isolation",  { controller.isolation,  { 10.f, 300.f, 1.f } });

		ui::input_field<bool>(e, "floor", controller.floor);
		ui::input_field<bool>(e, "wallx", controller.wallx);
		ui::input_field<bool>(e, "wallz", controller.wallz);
	}

	// this controls content of marching cubes voxel field

	static float time = 0.f;

	auto add_blobs = [&](MarchingCubes& object, float time, float numblobs, bool floor, bool wallx, bool wallz)
	{
		object.reset();

		// fill the field with some metaballs

		float subtract = 12.f;
		float strength = 1.2f / ((sqrt(numblobs) - 1.f) / 4.f + 1.f);

		for(size_t i = 0; i < numblobs; i++)
		{
			float fi = float(i);
			float ballx = sin(fi + 1.26f * time * (1.03f + 0.5f * cos(0.21f * fi))) * 0.27f + 0.5f;
			float bally = abs(cos(fi + 1.12f * time * cos(1.22f + 0.1424f * fi))) * 0.77f; // dip into the floor
			float ballz = cos(fi + 1.32f * time * 0.1f * sin((0.92f + 0.53f * fi))) * 0.27f + 0.5f;

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

	upload_cubes(cubes, *mesh);

	// materials

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
