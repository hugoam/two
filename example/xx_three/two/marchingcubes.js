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

//<script src = 'js/controls/OrbitControls.js'>< / script>
//
//<script src = 'js/shaders/CopyShader.js'>< / script>
//<script src = 'js/shaders/FXAAShader.js'>< / script>
//<script src = 'js/shaders/HorizontalTiltShiftShader.js'>< / script>
//<script src = 'js/shaders/VerticalTiltShiftShader.js'>< / script>
//
//<script src = 'js/postprocessing/EffectComposer.js'>< / script>
//<script src = 'js/postprocessing/RenderPass.js'>< / script>
//<script src = 'js/postprocessing/BloomPass.js'>< / script>
//<script src = 'js/postprocessing/ShaderPass.js'>< / script>
//<script src = 'js/postprocessing/MaskPass.js'>< / script>
//<script src = 'js/postprocessing/SavePass.js'>< / script>
//
//<script src = 'js/MarchingCubes.js'>< / script>
//<script src = 'js/ShaderToon.js'>< / script>
//
//<script src = 'js/WebGL.js'>< / script>
//<script src = 'js/libs/stats.min.js'>< / script>
//<script src = 'js/libs/dat.gui.min.js'>< / script>

#if 0
function createShaderMaterial(id, light, ambientLight) {

	var shader = THREE.ShaderToon[id];

	var u = THREE.UniformsUtils.clone(shader.uniforms);

	var vs = shader.vertexShader;
	var fs = shader.0ragmentShader;

	var material = new THREE.ShaderMaterial({ uniforms: u, vertexShader : vs, fragmentShader : fs });

	material.uniforms['uDirLightPos'].value = light.position;
	material.uniforms['uDirLightColor'].value = light.color;

	material.uniforms['uAmbientLightColor'].value = ambientLight.color;

	return material;

}

void generateMaterials()
{
	// toons

	var toonMaterial1 = createShaderMaterial('toon1', light, ambientLight),
		toonMaterial2 = createShaderMaterial('toon2', light, ambientLight),
		hatchingMaterial = createShaderMaterial('hatching', light, ambientLight),
		hatchingMaterial2 = createShaderMaterial('hatching', light, ambientLight),
		dottedMaterial = createShaderMaterial('dotted', light, ambientLight),
		dottedMaterial2 = createShaderMaterial('dotted', light, ambientLight);

	hatchingMaterial2.uniforms['uBaseColor'].value.setRGB(0, 0, 0);
	hatchingMaterial2.uniforms['uLineColor1'].value.setHSL(0, 0.8, 0.5);
	hatchingMaterial2.uniforms['uLineColor2'].value.setHSL(0, 0.8, 0.5);
	hatchingMaterial2.uniforms['uLineColor3'].value.setHSL(0, 0.8, 0.5);
	hatchingMaterial2.uniforms['uLineColor4'].value.setHSL(0.1, 0.8, 0.5);

	dottedMaterial2.uniforms['uBaseColor'].value.setRGB(0, 0, 0);
	dottedMaterial2.uniforms['uLineColor1'].value.setHSL(0.05, 1.0, 0.5);

	var texture = new THREE.TextureLoader().load('textures/UV_Grid_Sm.jpg');
	texture.wrapS = texture.wrapT = THREE.RepeatWrapping;

	var materials = {

		'chrome':
	{
		m: new THREE.MeshLambertMaterial({ color: 0xffffff, envMap : reflectionCube }),
		h : 0, s : 0, l : 1
	},

		'liquid':
	{
		m: new THREE.MeshLambertMaterial({ color: 0xffffff, envMap : refractionCube, refractionRatio : 0.85 }),
		h : 0, s : 0, l : 1
	},

		'shiny':
	{
		m: new THREE.MeshStandardMaterial({ color: 0x550000, envMap : reflectionCube, roughness : 0.1, metalness : 1.0 }),
		h : 0, s : 0.8, l : 0.2
	},

		'matte':
	{
		m: new THREE.MeshPhongMaterial({ color: 0x000000, specular : 0x111111, shininess : 1 }),
		h : 0, s : 0, l : 1
	},

		'flat':
	{
		m: new THREE.MeshLambertMaterial({ color: 0x000000, flatShading : true }),
		h : 0, s : 0, l : 1
	},

		'textured':
	{
		m: new THREE.MeshPhongMaterial({ color: 0xffffff, specular : 0x111111, shininess : 1, map : texture }),
		h : 0, s : 0, l : 1
	},

		'colors':
	{
		m: new THREE.MeshPhongMaterial({ color: 0xffffff, specular : 0xffffff, shininess : 2, vertexColors : THREE.VertexColors }),
		h : 0, s : 0, l : 1
	},

		'plastic':
	{
		m: new THREE.MeshPhongMaterial({ color: 0x000000, specular : 0x888888, shininess : 250 }),
		h : 0.6, s : 0.8, l : 0.1
	},

		'toon1':
	{
		m: toonMaterial1,
		h : 0.2, s : 1, l : 0.75
	},

		'toon2':
	{
		m: toonMaterial2,
		h : 0.4, s : 1, l : 0.75
	},

		'hatching':
	{
		m: hatchingMaterial,
		h : 0.2, s : 1, l : 0.9
	},

		'hatching2':
	{
		m: hatchingMaterial2,
		h : 0.0, s : 0.8, l : 0.5
	},

		'dotted':
	{
		m: dottedMaterial,
		h : 0.2, s : 1, l : 0.9
	},

		'dotted2':
	{
		m: dottedMaterial2,
		h : 0.1, s : 1, l : 0.5
	}

	};

	return materials;

}
#endif

void upload_cubes(MarchingCubes cubes, Mesh mesh)
{
	static MarchingCubes::Cache cache;

#if DIRECT
	uint32_t nutris = cubes.count();
	
	if(nutris == 0) return;
	//uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal | VertexAttribute::TexCoord0;
	uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal;
	uint32_t vertex_count = nutris * 3;

	Mesh::Direct direct = mesh.direct(vertex_format, vertex_count);

	MeshAdapter output = { vertex_format, { direct.vertices.data, vertex_count } };
	cubes.begin(cache);
	cubes.render(output, cache);
#else
	MeshPacker geometry;

	cubes.begin(cache);
	cubes.render(geometry, cache);

	if(geometry.vertex_count() == 0) return;
	//uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal | VertexAttribute::TexCoord0;
	uint32_t vertex_format = VertexAttribute::Position | VertexAttribute::Normal;
	uint32_t vertex_count = geometry.vertex_count();

	Mesh::Direct direct = mesh.direct(vertex_format, vertex_count);

	MeshAdapter writer = { vertex_format, { direct.vertices.data, vertex_count } };
	for(var i = 0; i < geometry.positions.length; ++i)
	{
		writer.position(geometry.positions[i]);
		writer.normal(geometry.normals[i]);
		//writer.uv0(uvs[i]);
	}
#endif
}

void xx_marching_cubes(Shell app, Widget parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(app.ui.begin());
	//two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	struct Controller
	{
		Material* material = nullptr;

		var speed = 1.0;
		var numBlobs = 10;
		var resolution = 28;
		var isolation = 80.0;

		bool floor = true;
		bool wallx = false;
		bool wallz = false;

		var hue = 0.0;
		var saturation = 0.8;
		var lightness = 0.1;

		var lhue = 0.0;
		var lsaturation = 0.8;
		var llightness = 0.1;

		var lx = 0.5;
		var ly = 0.5;
		var lz = 1.0;

		bool postprocessing = false;
	};

	static Controller controller = {};
	//controller.material = ;

	constexpr uint32_t resolution = 28;

#if NORMAL
	this.normal = app.gfx.programs.fetch('normal');
	normal.blocks[MaterialBlock::Pbr] = true;

	this.material = app.gfx.materials.create('normal', [](var m) {
		m.program = normal;
	});
#else
	this.pbr = app.gfx.programs.file('pbr/pbr');

	this.material = app.gfx.materials.create('material', [](var m) {
		m.program = pbr; m.pbr.albedo = two.rgba(0xaaaaaaff); m.pbr.metallic = 0.0; m.pbr.roughness = 0.66;
		//m.base.cull_mode = two.CullMode.None;
	});
#endif

	this.reflection = app.gfx.textures.file('SwedishRoyalCastle.cube');
	this.refraction = reflection;
	//refractionCube.mapping = THREE.CubeRefractionMapping;

	//this.material = two.gfx.solid_material(app.gfx, 'material', two.hsl(0.3, 1.0, 0.5));
	//material.base.cull_mode = two.CullMode.None;

	static MarchingCubes cubes = { resolution };

	this.model = app.gfx.create_model('cubes');
	static Mesh mesh = model.items[0].mesh;
	mesh.is_direct = true;

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 45.0; camera.near = 1.0; camera.far = 10000.0;
		camera.eye = new two.vec3(-500.0, 500.0, 1500.0);

		//scene.background = new THREE.Color(0x050505);

		var l0 = scene.nodes().add(new two.Node3(new two.vec3(0.0), new two.quat(facing(new two.vec3(0.5, 0.5, 1.0)))));
		scene.lights().add(Light(l0, LightType::Direct, false, rgb(0xffffff)));
		
		var l1 = scene.nodes().add(new two.Node3(new two.vec3(0.0, 0.0, 100.0)));
		scene.lights().add(Light(l1, LightType::Point, false, rgb(0xff3300)));

		//ambientLight = new THREE.AmbientLight(0x080808);
		//scene.add(ambientLight);

		//materials = generateMaterials();
		//string current_material = 'shiny';

		var n = scene.nodes().add(new two.Node3(new two.vec3(0.0), ZeroQuat, new two.vec3(700.0)));
		scene.items().add(new two.Item(n, model, 0, material));

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

	Gnode root = viewer.scene.begin();
	two.gfx.radiance(root, 'radiance/tiber_1_1k.hdr', BackgroundMode::Radiance);

	//two.gfx.shape(root, new two.Sphere(500.0), new two.Symbol(), 0, material);

	//static var h, s, l;
	//
	//function set_material = []()
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
	//	//effect.enableUvs = (current_material == 'textured') ? true : false;
	//	//effect.enableColors = (current_material == 'colors') ? true : false;
	//};

	if(Widget* dock = two.ui.dockitem(dockbar, 'Game', { 1U }))
	{
		Widget sheet = two.ui.sheet(*dock);

		// material (type)

		//h = gui.addFolder('Materials');
		//
		//for(var m in materials) {
		//
		//	effectController[m] = createHandler(m);
		//	h.add(effectController, m).name(m);
		//
		//}

		// material (color)

		function panel = [](string name) -> Widget
		{
			Widget s = two.ui.expandbox(sheet, name.c_str());
			return two.ui.columns(s, { 0.3, 0.7 });
		};

		Widget a = panel('Material color');

		two.ui.slider_field<float>(a, 'hue',        { controller.hue,        { 0.0, 1.0, 0.025 } });
		two.ui.slider_field<float>(a, 'saturation', { controller.saturation, { 0.0, 1.0, 0.025 } });
		two.ui.slider_field<float>(a, 'lightness',  { controller.lightness,  { 0.0, 1.0, 0.025 } });

		// light (point)

		Widget b = panel('Point light color');

		two.ui.slider_field<float>(b, 'hue',        { controller.lhue,        { 0.0, 1.0, 0.025 } });
		two.ui.slider_field<float>(b, 'saturation', { controller.lsaturation, { 0.0, 1.0, 0.025 } });
		two.ui.slider_field<float>(b, 'lightness',  { controller.llightness,  { 0.0, 1.0, 0.025 } });

		// light (directional)

		Widget c = panel('Directional light orientation');

		two.ui.slider_field<float>(c, 'x', { controller.lx, { -1.0, 1.0, 0.025 } });
		two.ui.slider_field<float>(c, 'y', { controller.ly, { -1.0, 1.0, 0.025 } });
		two.ui.slider_field<float>(c, 'z', { controller.lz, { -1.0, 1.0, 0.025 } });

		// simulation

		Widget d = panel('Simulation');

		two.ui.slider_field<float>(d, 'speed',       { controller.speed,      { 0.1, 8.0, 0.05 } });
		two.ui.slider_field<size_t>(d, 'numBlobs',   { controller.numBlobs,   { 1, 50, 1 } });
		two.ui.slider_field<size_t>(d, 'resolution', { controller.resolution, { 14, 100, 1 } });
		two.ui.slider_field<float>(d, 'isolation',   { controller.isolation,  { 10.0, 300.0, 1.0 } });

		two.ui.input_field<bool>(d, 'floor', controller.0loor);
		two.ui.input_field<bool>(d, 'wallx', controller.wallx);
		two.ui.input_field<bool>(d, 'wallz', controller.wallz);

		// rendering

		Widget e = panel('Rendering');
		two.ui.input_field<bool>(e, 'postprocessing', controller.postprocessing);
	}

	// this controls content of marching cubes voxel field

	static var time = 0.0;

	function add_blobs = [](MarchingCubes object, var time, var numblobs, bool floor, bool wallx, bool wallz)
	{
		object.reset();

		// fill the field with some metaballs

		var subtract = 12;
		var strength = 1.2 / ((Math.sqrt(numblobs) - 1) / 4 + 1);

		for(var i = 0; i < numblobs; i++)
		{
			var ballx = Math.sin(i + 1.26 * time * (1.03 + 0.5 * Math.cos(0.21 * i))) * 0.27 + 0.5;
			var bally = abs(Math.cos(i + 1.12 * time * Math.cos(1.22 + 0.1424 * i))) * 0.77; // dip into the floor
			var ballz = Math.cos(i + 1.32 * time * 0.1 * Math.sin((0.92 + 0.53 * i))) * 0.27 + 0.5;

			add_ball(object, new two.vec3(ballx, bally, ballz), strength, subtract);
		}

		if(floor) add_planeY(object, 2, 12);
		if(wallz) add_planeZ(object, 2, 12);
		if(wallx) add_planeX(object, 2, 12);
	};

	var delta = app.gfx.frame_time;

	time += delta * controller.speed * 0.5;

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

	add_blobs(cubes, time, controller.numBlobs, controller.0loor, controller.wallx, controller.wallz);

	// materials

	//if(effect.material instanceof THREE.ShaderMaterial) {
	//
	//	if(current_material == 'dotted2') {
	//
	//		effect.material.uniforms['uLineColor1'].value.setHSL(effectController.hue, effectController.saturation, effectController.lightness);
	//
	//	}
	//	else if(current_material == 'hatching2') {
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
	//		effect.material.uniforms['uBaseColor'].value.setHSL(effectController.hue, effectController.saturation, effectController.lightness);
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
