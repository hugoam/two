//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

#define CLUSTERED 1

#if 0
// Simple form of tiled forward lighting
// using texels as bitmasks of 32 lights

THREE.ShaderChunk['lights_pars_begin'] += [
	'',
		'#if defined TILED_FORWARD',
		'uniform vec4 tileData;',
		'uniform sampler2D tileTexture;',
		'uniform sampler2D lightTexture;',
		'#endif'
].join('\n');

THREE.ShaderChunk['lights_fragment_end'] += [
	'',
		'#if defined TILED_FORWARD',
		'vec2 tUv = floor(gl_FragCoord.xy / tileData.xy * 32.) / 32. + tileData.zw;',
		'vec4 tile = texture2D(tileTexture, tUv);',
		'for (int i=0; i < 4; i++) {',
		'	float tileVal = tile.x * 255.;',
		'  	tile.xyzw = tile.yzwx;',
		'	if(tileVal == 0.){ continue; }',
		'  	float tileDiv = 128.;',
		'	for (int j=0; j < 8; j++) {',
		'  		if (tileVal < tileDiv) {  tileDiv *= 0.5; continue; }',
		'		tileVal -= tileDiv;',
		'		tileDiv *= 0.5;',
		'  		PointLight pointlight;',
		'		float uvx = (float(8 * i + j) + 0.5) / 32.;',
		'  		vec4 lightData = texture2D(lightTexture, vec2(uvx, 0.));',
		'  		vec4 lightColor = texture2D(lightTexture, vec2(uvx, 1.));',
		'  		pointlight.position = lightData.xyz;',
		'  		pointlight.distance = lightData.w;',
		'  		pointlight.color = lightColor.rgb;',
		'  		pointlight.decay = lightColor.a;',
		'  		getPointDirectLightIrradiance( pointlight, geometry, directLight );',
		'		RE_Direct( directLight, geometry, material, reflectedLight );',
		'	}',
		'}',
		'#endif'
].join('\n');


var State = {
	rows: 0,
	cols : 0,
	width : 0,
	height : 0,
	tileData : { value: null },
	tileTexture : { value: null },
	lightTexture : {
		value: new THREE.DataTexture(new Float32Array(32 * 2 * 4), 32, 2, THREE.RGBAFormat, THREE.FloatType)
	},
};

function resizeTiles() {

	var width = window.innerWidth;
	var height = window.innerHeight;

	State.width = width;
	State.height = height;
	State.cols = Math.ceil(width / 32);
	State.rows = Math.ceil(height / 32);
	State.tileData.value = [width, height, 0.5 / Math.ceil(width / 32), 0.5 / Math.ceil(height / 32)];
	State.tileTexture.value = new THREE.DataTexture(new Uint8Array(State.cols * State.rows * 4), State.cols, State.rows);

}

// Generate the light bitmasks and store them in the tile texture
function tileLights(renderer, scene, camera) {

	if(!camera.projectionMatrix) return;

	var d = State.tileTexture.value.image.data;
	var ld = State.lightTexture.value.image.data;

	var viewMatrix = camera.matrixWorldInverse;

	d.fill(0);

	var vector = new THREE.Vector3();

	lights.forEach(function(light, index) {

		vector.setFromMatrixPosition(light.matrixWorld);

		var bs = lightBounds(camera, vector, light._light.radius);

		vector.applyMatrix4(viewMatrix);
		vector.toArray(ld, 4 * index);
		ld[4 * index + 3] = light._light.radius;
		light._light.color.toArray(ld, 32 * 4 + 4 * index);
		ld[32 * 4 + 4 * index + 3] = light._light.decay;

		if(bs[1] < 0 || bs[0] > State.width || bs[3] < 0 || bs[2] > State.height) return;
		if(bs[0] < 0) bs[0] = 0;
		if(bs[1] > State.width) bs[1] = State.width;
		if(bs[2] < 0) bs[2] = 0;
		if(bs[3] > State.height) bs[3] = State.height;

		var i4 = Math.floor(index / 8), i8 = 7 - (index % 8);

		for(var i = Math.floor(bs[2] / 32); i <= Math.ceil(bs[3] / 32); i++) {

			for(var j = Math.floor(bs[0] / 32); j <= Math.ceil(bs[1] / 32); j++) {

				d[(State.cols * i + j) * 4 + i4] |= 1 << i8;

			}

		}

	});

	State.tileTexture.value.needsUpdate = true;
	State.lightTexture.value.needsUpdate = true;

}

// Screen rectangle bounds from light sphere's world AABB
var lightBounds = function() {

	var v = new THREE.Vector3();
	return function(camera, pos, r) {

		var minX = State.width, maxX = 0, minY = State.height, maxY = 0, hw = State.width / 2, hh = State.height / 2;

		for(var i = 0; i < 8; i++) {

			v.copy(pos);
			v.x += i & 1 ? r : -r;
			v.y += i & 2 ? r : -r;
			v.z += i & 4 ? r : -r;
			var vector = v.project(camera);
			var x = (vector.x * hw) + hw;
			var y = (vector.y * hh) + hh;
			minX = Math.min(minX, x);
			maxX = Math.max(maxX, x);
			minY = Math.min(minY, y);
			maxY = Math.max(maxY, y);

		}

		return[minX, maxX, minY, maxY];

	};

}();

#endif

void xx_tiled_forward(Shell& app, Widget& parent, Dockbar& dockbar)
{
	static ImporterOBJ obj_importer(app.m_gfx_system);

	static Program& solid = *app.m_gfx_system.programs().file("solid");
	static Program& pbr = *app.m_gfx_system.programs().file("pbr/pbr");

	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	viewer.m_viewport.comp<Tonemap>().m_enabled = true;

	//var controls = new THREE.OrbitControls(camera, renderer.domElement);
	//controls.minDistance = 120;
	//controls.maxDistance = 320;

	//renderer.toneMapping = THREE.LinearToneMapping;

	//var bloom = new THREE.UnrealBloomPass(new THREE.Vector2(), 0.8, 0.6, 0.8);
	//bloom.renderToScreen = true;

	//var camera = new THREE.PerspectiveCamera(40, window.innerWidth / window.innerHeight, 1, 2000);
	//camera.position.set(0.0, 0.0, 240.0);

	//scene.background = new THREE.Color(0x111111);

#if CLUSTERED
	Camera& camera = viewer.m_camera;
	if(viewer.m_viewport.m_rect != uvec4(0U) && !camera.m_clusters)
	{
		camera.m_clustered = true;
		camera.m_clusters = make_unique<Froxelizer>(app.m_gfx_system);
		camera.m_clusters->prepare(viewer.m_viewport, camera.m_projection, camera.m_near, camera.m_far);
	}
#endif

	float radius = 75.f;

	Scene& scene = viewer.m_scene;
	Gnode& root = viewer.m_scene.begin();

	struct ExLight
	{
		Node3* parent;
		Node3* node;
		Colour color;
		float radius = radius;
		float decay = 1.f;
		float sy, sr, sc;
		float py, pr, pc;
		float dir;
	};

	static vector<ExLight> lights = {};

	scene.m_env.m_radiance.m_colour = Colour::White;
	scene.m_env.m_radiance.m_energy = 0.066f;
	scene.m_env.m_radiance.m_ambient = 0.33f;
	//scene.add(new THREE.AmbientLight(0xffffff, 0.33));

	auto material = [&](const string& name, auto init) -> Material* { return &app.m_gfx_system.materials().create(name, init); };

	static Material* materials[] = {
		material("first",  [&](Material& m) { m.m_program = &pbr; m.m_pbr.m_albedo = rgba(0x888888ff); m.m_pbr.m_metallic = 1.0f; m.m_pbr.m_roughness = 0.66f; }),
		material("second", [&](Material& m) { m.m_program = &pbr; m.m_pbr.m_albedo = rgba(0x666666ff); m.m_pbr.m_metallic = 0.1f; m.m_pbr.m_roughness = 0.33f; }),
		material("third",  [&](Material& m) { m.m_program = &pbr; m.m_pbr.m_albedo = rgba(0x777777ff); m.m_pbr.m_metallic = 0.1f; m.m_pbr.m_roughness = 0.33f; m.m_pbr.m_specular_mode = PbrSpecularMode::Phong; }),
		material("fourth", [&](Material& m) { m.m_program = &pbr; m.m_pbr.m_albedo = rgba(0x555555ff); m.m_pbr.m_metallic = 0.1f; m.m_pbr.m_roughness = 0.33f; m.m_pbr.m_diffuse_mode = PbrDiffuseMode::Toon; m.m_pbr.m_specular_mode = PbrSpecularMode::Toon; }),
		//{ type: 'physical', uniforms : { "diffuse": 0x888888, "metalness" : 1.0, "roughness" : 0.66 }, defines : {} },
		//{ type: 'standard', uniforms : { "diffuse": 0x666666, "metalness" : 0.1, "roughness" : 0.33 }, defines : {} },
		//{ type: 'phong', uniforms : { "diffuse": 0x777777, "shininess" : 20 }, defines : {} },
		//{ type: 'phong', uniforms : { "diffuse": 0x555555, "shininess" : 10 }, defines : { TOON: 1 } }
	};

	static bool once = false;
	if(!once)
	{
		once = true;

		Model& model = *app.m_gfx_system.models().file("WaltHead");
		
		Model& sphere = app.m_gfx_system.fetch_symbol(Symbol(), Sphere(0.5f), PLAIN);
		Model& big_sphere = app.m_gfx_system.fetch_symbol(Symbol(), Sphere(0.5f * 6.66f), PLAIN);

		size_t transparent = randi(0, 3);
		materials[transparent]->m_alpha.m_alpha = 0.9f;

		//transparent : tIndex == = index ? true : false,
		//mtl.uniforms["opacity"].value = tIndex == = index ? 0.9 : 1;
		//mtl.side = tIndex == = index ? THREE.FrontSide : THREE.DoubleSide;

		size_t index = 0;
		for(Material* material : materials)
		{
			float i = float(index++);
			vec3 position = vec3(sin(i * c_pi2) * radius, 0.f, cos(i * c_pi2) * radius);
			quat rotation = quat(vec3(0.f, i * c_pi2, 0.f));

			Node3& n = gfx::nodes(scene).add(Node3(position, rotation));

			Node3& m = gfx::nodes(scene).add(Node3(n.m_transform * bxTRS(vec3(1.f), ZeroQuat, vec3(0.f, -37.f, 0.f))));
			Item& it = gfx::items(scene).add(Item(m, model, 0U, material));

			for(size_t i = 0; i < 8; i++)
			{
				Colour color = hsl(randf(), 1.0, 0.5f);

				Material& m = app.m_gfx_system.materials().create("l" + material->m_name + to_string(i), [&](Material& m) { 
					m.m_program = &solid; m.m_solid.m_colour = color; 
				});

				Material& ma = app.m_gfx_system.materials().create("la" + material->m_name + to_string(i), [&](Material& m) {
					m.m_program = &solid; m.m_solid.m_colour = color; m.m_alpha.m_alpha = 0.033f;
				});

				Node3& l = gfx::nodes(scene).add(Node3());
				Item& i0 = gfx::items(scene).add(Item(l, sphere, 0U, &m)); // MaterialSolid(color)));
			
				//Item& i1 = gfx::items(scene).add(Item(l, big_sphere, 0U, &ma)); // MaterialSolid(color), MaterialAlpha(0.033f));
				//l.children[1].scale.set(6.66, 6.66, 6.66);

				Light& light = gfx::lights(scene).add(Light(l, LightType::Point));
				light.m_range = 40.f;
				light.m_colour = color;

				lights.push_back({
					&n,
					&l,
					color,
					radius,
					1.f,
					randf(),
					randf(),
					randf(),
					randf() * c_pi,
					randf() * c_pi,
					randf() * c_pi,
					randf() > 0.5 ? 1.f : -1.f
				});
			}
		}
	}

	static Material& testmat = app.m_gfx_system.materials().create("test", [&](Material& m) {
		m.m_program = &pbr; m.m_pbr.m_albedo = rgba(0x888888ff); m.m_pbr.m_metallic = 1.0f; m.m_pbr.m_roughness = 0.66f;
	});

	//gfx::radiance(root, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);

	gfx::shape(root, Sphere(), Symbol(), 0U, &testmat);

	float time = app.m_gfx_system.m_time;

	for(ExLight& l : lights)
	{
		float r = 0.8 + 0.2 * sin(l.pr + (0.6 + 0.3 * l.sr) * time);
		float x = (sin(l.pc + (0.8 + 0.2 * l.sc) * time * l.dir)) * r * radius;
		float z = (cos(l.pc + (0.8 + 0.2 * l.sc) * time * l.dir)) * r * radius;
		float y = sin(l.py + (0.8 + 0.2 * l.sy) * time) * r * 32.f;
		l.node->m_transform = l.parent->m_transform * bxTRS(vec3(1.f), ZeroQuat, vec3(x, y, z));
	}
}