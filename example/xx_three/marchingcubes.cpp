//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

#include <cstdio>
#include <cstring>

using namespace mud;

#define DIRECT 0
#define NORMAL 1

//<script src = "js/controls/OrbitControls.js">< / script>
//
//<script src = "js/shaders/CopyShader.js">< / script>
//<script src = "js/shaders/FXAAShader.js">< / script>
//<script src = "js/shaders/HorizontalTiltShiftShader.js">< / script>
//<script src = "js/shaders/VerticalTiltShiftShader.js">< / script>
//
//<script src = "js/postprocessing/EffectComposer.js">< / script>
//<script src = "js/postprocessing/RenderPass.js">< / script>
//<script src = "js/postprocessing/BloomPass.js">< / script>
//<script src = "js/postprocessing/ShaderPass.js">< / script>
//<script src = "js/postprocessing/MaskPass.js">< / script>
//<script src = "js/postprocessing/SavePass.js">< / script>
//
//<script src = "js/MarchingCubes.js">< / script>
//<script src = "js/ShaderToon.js">< / script>
//
//<script src = "js/WebGL.js">< / script>
//<script src = "js/libs/stats.min.js">< / script>
//<script src = "js/libs/dat.gui.min.js">< / script>

#if 0
function createShaderMaterial(id, light, ambientLight) {

	var shader = THREE.ShaderToon[id];

	var u = THREE.UniformsUtils.clone(shader.uniforms);

	var vs = shader.vertexShader;
	var fs = shader.fragmentShader;

	var material = new THREE.ShaderMaterial({ uniforms: u, vertexShader : vs, fragmentShader : fs });

	material.uniforms["uDirLightPos"].value = light.position;
	material.uniforms["uDirLightColor"].value = light.color;

	material.uniforms["uAmbientLightColor"].value = ambientLight.color;

	return material;

}

void generateMaterials()
{
	// toons

	var toonMaterial1 = createShaderMaterial("toon1", light, ambientLight),
		toonMaterial2 = createShaderMaterial("toon2", light, ambientLight),
		hatchingMaterial = createShaderMaterial("hatching", light, ambientLight),
		hatchingMaterial2 = createShaderMaterial("hatching", light, ambientLight),
		dottedMaterial = createShaderMaterial("dotted", light, ambientLight),
		dottedMaterial2 = createShaderMaterial("dotted", light, ambientLight);

	hatchingMaterial2.uniforms["uBaseColor"].value.setRGB(0, 0, 0);
	hatchingMaterial2.uniforms["uLineColor1"].value.setHSL(0, 0.8, 0.5);
	hatchingMaterial2.uniforms["uLineColor2"].value.setHSL(0, 0.8, 0.5);
	hatchingMaterial2.uniforms["uLineColor3"].value.setHSL(0, 0.8, 0.5);
	hatchingMaterial2.uniforms["uLineColor4"].value.setHSL(0.1, 0.8, 0.5);

	dottedMaterial2.uniforms["uBaseColor"].value.setRGB(0, 0, 0);
	dottedMaterial2.uniforms["uLineColor1"].value.setHSL(0.05, 1.0, 0.5);

	var texture = new THREE.TextureLoader().load("textures/UV_Grid_Sm.jpg");
	texture.wrapS = texture.wrapT = THREE.RepeatWrapping;

	var materials = {

		"chrome":
	{
		m: new THREE.MeshLambertMaterial({ color: 0xffffff, envMap : reflectionCube }),
		h : 0, s : 0, l : 1
	},

		"liquid":
	{
		m: new THREE.MeshLambertMaterial({ color: 0xffffff, envMap : refractionCube, refractionRatio : 0.85 }),
		h : 0, s : 0, l : 1
	},

		"shiny":
	{
		m: new THREE.MeshStandardMaterial({ color: 0x550000, envMap : reflectionCube, roughness : 0.1, metalness : 1.0 }),
		h : 0, s : 0.8, l : 0.2
	},

		"matte":
	{
		m: new THREE.MeshPhongMaterial({ color: 0x000000, specular : 0x111111, shininess : 1 }),
		h : 0, s : 0, l : 1
	},

		"flat":
	{
		m: new THREE.MeshLambertMaterial({ color: 0x000000, flatShading : true }),
		h : 0, s : 0, l : 1
	},

		"textured":
	{
		m: new THREE.MeshPhongMaterial({ color: 0xffffff, specular : 0x111111, shininess : 1, map : texture }),
		h : 0, s : 0, l : 1
	},

		"colors":
	{
		m: new THREE.MeshPhongMaterial({ color: 0xffffff, specular : 0xffffff, shininess : 2, vertexColors : THREE.VertexColors }),
		h : 0, s : 0, l : 1
	},

		"plastic":
	{
		m: new THREE.MeshPhongMaterial({ color: 0x000000, specular : 0x888888, shininess : 250 }),
		h : 0.6, s : 0.8, l : 0.1
	},

		"toon1":
	{
		m: toonMaterial1,
		h : 0.2, s : 1, l : 0.75
	},

		"toon2":
	{
		m: toonMaterial2,
		h : 0.4, s : 1, l : 0.75
	},

		"hatching":
	{
		m: hatchingMaterial,
		h : 0.2, s : 1, l : 0.9
	},

		"hatching2":
	{
		m: hatchingMaterial2,
		h : 0.0, s : 0.8, l : 0.5
	},

		"dotted":
	{
		m: dottedMaterial,
		h : 0.2, s : 1, l : 0.9
	},

		"dotted2":
	{
		m: dottedMaterial2,
		h : 0.1, s : 1, l : 0.5
	}

	};

	return materials;

}
#endif

void upload_cubes(MarchingCubes& cubes, Mesh& mesh)
{
	static MarchingCubes::Cache cache;

#if DIRECT
	const uint32_t num_tris = cubes.count();
	
	if(num_tris == 0) return;
	//uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal | VertexAttribute::TexCoord0;
	const uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal;
	const uint32_t vertex_count = num_tris * 3;

	Mesh::Direct& direct = mesh.direct(vertex_format, vertex_count);

	MeshAdapter output = { vertex_format, { direct.m_vertices.data, vertex_count } };
	cubes.begin(cache);
	cubes.render(output, cache);
#else
	MeshPacker geometry;

	cubes.begin(cache);
	cubes.render(geometry, cache);

	if(geometry.vertex_count() == 0) return;
	//uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal | VertexAttribute::TexCoord0;
	const uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal;
	const uint32_t vertex_count = geometry.vertex_count();

	Mesh::Direct& direct = mesh.direct(vertex_format, vertex_count);

	MeshAdapter writer = { vertex_format, { direct.m_vertices.data, vertex_count } };
	for(size_t i = 0; i < geometry.m_positions.size(); ++i)
	{
		writer.position(geometry.m_positions[i]);
		writer.normal(geometry.m_normals[i]);
		//writer.uv0(uvs[i]);
	}
#endif
}

void xx_marching_cubes(Shell& app, Widget& parent, Dockbar& dockbar)
{
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	struct Controller
	{
		Material* material = nullptr;

		float speed = 1.f;
		size_t numBlobs = 10;
		size_t resolution = 28;
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

		bool postprocessing = false;
	};

	static Controller controller = {};
	//controller.material = ;

	constexpr uint32_t resolution = 28;

#if NORMAL
	static Program& normal = app.m_gfx.programs().fetch("normal");
	normal.m_blocks[MaterialBlock::Pbr] = true;

	static Material& material = app.m_gfx.materials().create("normal", [&](Material& m) {
		m.m_program = &normal;
	});
#else
	static Program& pbr = *app.m_gfx.programs().file("pbr/pbr");

	static Material& material = app.m_gfx.materials().create("material", [&](Material& m) {
		m.m_program = &pbr; m.m_pbr.m_albedo = rgb(0xaaaaaa); m.m_pbr.m_metallic = 0.0f; m.m_pbr.m_roughness = 0.66f;
		//m.m_base.m_cull_mode = CullMode::None;
	});
#endif

	static Texture& reflection = *app.m_gfx.textures().file("SwedishRoyalCastle.cube");
	static Texture& refraction = reflection;
	//refractionCube.mapping = THREE.CubeRefractionMapping;

	//static Material& material = gfx::solid_material(app.m_gfx, "material", hsl(0.3f, 1.f, 0.5f));
	//material.m_base.m_cull_mode = CullMode::None;

	static MarchingCubes cubes = { resolution };

	static Model& model = app.m_gfx.create_model("cubes");
	static Mesh& mesh = *model.m_items[0].m_mesh;
	mesh.m_is_direct = true;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 45.f; camera.m_near = 1.f; camera.m_far = 10000.f;
		camera.m_eye = vec3(-500.f, 500.f, 1500.f);

		//scene.background = new THREE.Color(0x050505);

		Node3& l0 = gfx::nodes(scene).add(Node3(vec3(0.f), quat(facing(vec3(0.5f, 0.5f, 1.f)))));
		gfx::lights(scene).add(Light(l0, LightType::Direct, false, rgb(0xffffff)));
		
		Node3& l1 = gfx::nodes(scene).add(Node3(vec3(0.f, 0.f, 100.f)));
		gfx::lights(scene).add(Light(l1, LightType::Point, false, rgb(0xff3300)));

		//ambientLight = new THREE.AmbientLight(0x080808);
		//scene.add(ambientLight);

		//materials = generateMaterials();
		//string current_material = "shiny";

		Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f), ZeroQuat, vec3(700.f)));
		gfx::items(scene).add(Item(n, model, 0U, &material));

		// COMPOSER

		//renderer.autoClear = false;
		//
		//var renderTargetParameters = { minFilter: THREE.LinearFilter, magFilter: THREE.LinearFilter, format: THREE.RGBFormat, stencilBuffer: false };
		//var renderTarget = new THREE.WebGLRenderTarget(SCREEN_WIDTH, SCREEN_HEIGHT, renderTargetParameters);
		//
		//effectFXAA = new THREE.ShaderPass(THREE.FXAAShader);
		//
		//hblur = new THREE.ShaderPass(THREE.HorizontalTiltShiftShader);
		//vblur = new THREE.ShaderPass(THREE.VerticalTiltShiftShader);
		//
		//var bluriness = 8;
		//
		//hblur.uniforms['h'].value = bluriness / SCREEN_WIDTH;
		//vblur.uniforms['v'].value = bluriness / SCREEN_HEIGHT;
		//
		//hblur.uniforms['r'].value = vblur.uniforms['r'].value = 0.5;
		//
		//effectFXAA.uniforms['resolution'].value.set(1 / SCREEN_WIDTH, 1 / SCREEN_HEIGHT);
		//
		//var renderModel = new THREE.RenderPass(scene, camera);
		//
		//vblur.renderToScreen = true;
		////effectFXAA.renderToScreen = true;
		//
		//composer = new THREE.EffectComposer(renderer, renderTarget);
		//
		//composer.addPass(renderModel);
		//
		//composer.addPass(effectFXAA);
		//
		//composer.addPass(hblur);
		//composer.addPass(vblur);

		//function onWindowResize() {
		//
		//	hblur.uniforms['h'].value = 4 / SCREEN_WIDTH;
		//	vblur.uniforms['v'].value = 4 / SCREEN_HEIGHT;
		//
		//	effectFXAA.uniforms['resolution'].value.set(1 / SCREEN_WIDTH, 1 / SCREEN_HEIGHT);
		//
		//}

		//
	}

	Gnode& root = viewer.m_scene.begin();
	gfx::radiance(root, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);

	//gfx::shape(root, Sphere(500.f), Symbol(), 0U, &material);

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

		// material (type)

		//h = gui.addFolder("Materials");
		//
		//for(var m in materials) {
		//
		//	effectController[m] = createHandler(m);
		//	h.add(effectController, m).name(m);
		//
		//}

		// material (color)

		auto panel = [&](const string& name) -> Widget&
		{
			Widget& s = ui::expandbox(sheet, name.c_str());
			return ui::columns(s, { 0.3f, 0.7f });
		};

		Widget& a = panel("Material color");

		ui::slider_field<float>(a, "hue",        { controller.hue,        { 0.f, 1.f, 0.025f } });
		ui::slider_field<float>(a, "saturation", { controller.saturation, { 0.f, 1.f, 0.025f } });
		ui::slider_field<float>(a, "lightness",  { controller.lightness,  { 0.f, 1.f, 0.025f } });

		// light (point)

		Widget& b = panel("Point light color");

		ui::slider_field<float>(b, "hue",        { controller.lhue,        { 0.f, 1.f, 0.025f } });
		ui::slider_field<float>(b, "saturation", { controller.lsaturation, { 0.f, 1.f, 0.025f } });
		ui::slider_field<float>(b, "lightness",  { controller.llightness,  { 0.f, 1.f, 0.025f } });

		// light (directional)

		Widget& c = panel("Directional light orientation");

		ui::slider_field<float>(c, "x", { controller.lx, { -1.f, 1.f, 0.025f } });
		ui::slider_field<float>(c, "y", { controller.ly, { -1.f, 1.f, 0.025f } });
		ui::slider_field<float>(c, "z", { controller.lz, { -1.f, 1.f, 0.025f } });

		// simulation

		Widget& d = panel("Simulation");

		ui::slider_field<float>(d, "speed",       { controller.speed,      { 0.1f, 8.0f, 0.05f } });
		ui::slider_field<size_t>(d, "numBlobs",   { controller.numBlobs,   { 1, 50, 1 } });
		ui::slider_field<size_t>(d, "resolution", { controller.resolution, { 14, 100, 1 } });
		ui::slider_field<float>(d, "isolation",   { controller.isolation,  { 10.f, 300.f, 1.f } });

		ui::input_field<bool>(d, "floor", controller.floor);
		ui::input_field<bool>(d, "wallx", controller.wallx);
		ui::input_field<bool>(d, "wallz", controller.wallz);

		// rendering

		Widget& e = panel("Rendering");
		ui::input_field<bool>(e, "postprocessing", controller.postprocessing);
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

	upload_cubes(cubes, mesh);

	// marching cubes

	//if(effectController.resolution != = resolution) {
	//
	//	resolution = effectController.resolution;
	//	effect.init(floor(resolution));
	//
	//}
	//
	//if(effectController.isolation != = effect.isolation) {
	//
	//	effect.isolation = effectController.isolation;
	//
	//}

	add_blobs(cubes, time, controller.numBlobs, controller.floor, controller.wallx, controller.wallz);

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

	// render

	//if(effectController.postprocessing) {
	//
	//	composer.render(delta);
	//
	//}
	//else {
	//
	//	renderer.clear();
	//	renderer.render(scene, camera);
	//
	//}
}
