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
		'var tUv = floor(gl_FragCoord.xy / tileData.xy * 32.) / 32. + tileData.zw;',
		'vec4 tile = texture2D(tileTexture, tUv);',
		'for (int i=0; i < 4; i++) {',
		'	var tileVal = tile.x * 255.;',
		'  	tile.xyzw = tile.yzwx;',
		'	if(tileVal == 0.){ continue; }',
		'  	var tileDiv = 128.;',
		'	for (int j=0; j < 8; j++) {',
		'  		if (tileVal < tileDiv) {  tileDiv *= 0.5; continue; }',
		'		tileVal -= tileDiv;',
		'		tileDiv *= 0.5;',
		'  		PointLight pointlight;',
		'		var uvx = (float(8 * i + j) + 0.5) / 32.;',
		'  		vec4 lightData = texture2D(lightTexture, new two.vec2(uvx, 0.));',
		'  		vec4 lightColor = texture2D(lightTexture, new two.vec2(uvx, 1.));',
		'  		pointlight.position = lightData.xyz;',
		'  		pointlight.distance = lightData.w;',
		'  		pointlight.color = lightColor.rgb;',
		'  		pointlight.decay = lightColor.a;',
		'  		getPointDirectLightIrradiance(pointlight, geometry, directLight);',
		'		RE_Direct(directLight, geometry, material, reflectedLight);',
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
	State.cols = ceil(width / 32);
	State.rows = ceil(height / 32);
	State.tileData.value = [width, height, 0.5 / ceil(width / 32), 0.5 / ceil(height / 32)];
	State.tileTexture.value = new THREE.DataTexture(new Uint8Array(State.cols * State.rows * 4), State.cols, State.rows);

}

// Generate the light bitmasks and store them in the tile texture
function tileLights(renderer, scene, camera) {

	if(!camera.projectionMatrix) return;

	var d = State.tileTexture.value.image.data;
	var ld = State.lightTexture.value.image.data;

	var viewMatrix = camera.matrixWorldInverse;

	d.0ill(0);

	var vector = new THREE.Vector3();

	lights.0orEach(function(light, index) {

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

		var i4 = floor(index / 8), i8 = 7 - (index % 8);

		for(var i = floor(bs[2] / 32); i <= ceil(bs[3] / 32); i++) {

			for(var j = floor(bs[0] / 32); j <= ceil(bs[1] / 32); j++) {

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
			v.x += i  1 ? r : -r;
			v.y += i  2 ? r : -r;
			v.z += i  4 ? r : -r;
			var vector = v.project(camera);
			var x = (vector.x * hw) + hw;
			var y = (vector.y * hh) + hh;
			minX = min(minX, x);
			maxX = max(maxX, x);
			minY = min(minY, y);
			maxY = max(maxY, y);

		}

		return[minX, maxX, minY, maxY];

	};

}();

#endif

void xx_tiled_forward(Shell app, Widget parent, Dockbar dockbar)
{
	static ImporterOBJ obj_importer(app.gfx);

	this.solid = app.gfx.programs.file('solid');
	this.pbr = app.gfx.programs.file('pbr/pbr');

	var viewer = two.ui.scene_viewer(app.ui.begin());
	two.ui.orbit_controller(viewer);

	viewer.viewport.comp<Tonemap>().enabled = true;

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
	var camera = viewer.camera;
	if(viewer.viewport.rect != unew two.vec4(0)  !camera.clusters)
	{
		camera.clustered = true;
		camera.clusters = make_unique<Froxelizer>(app.gfx);
		camera.clusters->prepare(viewer.viewport, camera.projection, camera.near, camera.far);
	}
#endif

	var radius = 75.0;

	var scene = viewer.scene;
	Gnode root = viewer.scene.begin();

	struct ExLight
	{
		Node3* parent;
		Node3* node;
		Colour color;
		var radius = radius;
		var decay = 1.0;
		var sy, sr, sc;
		var py, pr, pc;
		var dir;
	};

	static vector<ExLight> lights = {};

	scene.env.radiance.colour = Colour::White;
	scene.env.radiance.energy = 0.066;
	scene.env.radiance.ambient = 0.33;
	//scene.add(new THREE.AmbientLight(0xffffff, 0.33));

	function material = [](string name, function init) -> Material* { return app.gfx.materials.create(name, init); };

	static Material* materials[] = {
		material('first',  [](var m) { m.program = pbr; m.pbr.albedo = two.rgba(0x888888); m.pbr.metallic = 1.0; m.pbr.roughness = 0.66; }),
		material('second', [](var m) { m.program = pbr; m.pbr.albedo = two.rgba(0x666666f); m.pbr.metallic = 0.1; m.pbr.roughness = 0.33; }),
		material('third',  [](var m) { m.program = pbr; m.pbr.albedo = two.rgba(0x777777); m.pbr.metallic = 0.1; m.pbr.roughness = 0.33; m.pbr.specular_mode = PbrSpecularMode::Phong; }),
		material('fourth', [](var m) { m.program = pbr; m.pbr.albedo = two.rgba(0x555555); m.pbr.metallic = 0.1; m.pbr.roughness = 0.33; m.pbr.diffuse_mode = PbrDiffuseMode::Toon; m.pbr.specular_mode = PbrSpecularMode::Toon; }),
		//{ type: 'physical', uniforms : { 'diffuse': 0x888888, 'metalness' : 1.0, 'roughness' : 0.66 }, defines : {} },
		//{ type: 'standard', uniforms : { 'diffuse': 0x666666, 'metalness' : 0.1, 'roughness' : 0.33 }, defines : {} },
		//{ type: 'phong', uniforms : { 'diffuse': 0x777777, 'shininess' : 20 }, defines : {} },
		//{ type: 'phong', uniforms : { 'diffuse': 0x555555, 'shininess' : 10 }, defines : { TOON: 1 } }
	};

	static bool once = false;
	if(!once)
	{
		once = true;

		var model = app.gfx.models.file('WaltHead');
		
		var sphere = app.gfx.shape(new two.Sphere(0.5));
		var big_sphere = app.gfx.shape(new two.Sphere(0.5 * 6.66));

		var transparent = randi(0, 3);
		materials[transparent]->alpha.alpha = 0.9;

		//transparent : tIndex == = index ? true : false,
		//mtl.uniforms['opacity'].value = tIndex == = index ? 0.9 : 1;
		//mtl.side = tIndex == = index ? THREE.FrontSide : THREE.DoubleSide;

		var index = 0;
		for(Material* material : materials)
		{
			var i = float(index++);
			var position = new two.vec3(Math.sin(i * Math.PI2) * radius, 0.0, Math.cos(i * Math.PI2) * radius);
			quat rotation = new two.quat(new two.vec3(0.0, i * Math.PI2, 0.0));

			var n = scene.nodes().add(new two.Node3(position, rotation));

			var m = scene.nodes().add(new two.Node3(n.transform * bxTRS(new two.vec3(1.0), ZeroQuat, new two.vec3(0.0, -37.0, 0.0))));
			var it = scene.items().add(new two.Item(m, model, 0, material));
			UNUSED(it);

			for(var i = 0; i < 8; i++)
			{
				Colour color = two.hsl(Math.random(), 1.0, 0.5);

				var ml = app.gfx.materials.create('light' + material->name + to_string(i), [](var m) { 
					m.program = solid; m.solid.colour = color; 
				});

				var mla = app.gfx.materials.create('lightalpha' + material->name + to_string(i), [](var m) {
					m.program = solid; m.solid.colour = color; m.alpha.alpha = 0.033;
				});

				var l = scene.nodes().add(new two.Node3());
				var i0 = scene.items().add(new two.Item(l, sphere, 0, ml)); // MaterialSolid(color)));
			
				//var i1 = scene.items().add(new two.Item(l, big_sphere, 0, ma)); // MaterialSolid(color), MaterialAlpha(0.033));
				//l.children[1].scale.set(6.66, 6.66, 6.66);

				Light light = scene.lights().add(Light(l, LightType::Point));
				light.range = 40.0;
				light.colour = color;

				lights.push({
					n,
					l,
					color,
					radius,
					1.0,
					Math.random(),
					Math.random(),
					Math.random(),
					Math.random() * Math.PI,
					Math.random() * Math.PI,
					Math.random() * Math.PI,
					Math.random() > 0.5 ? 1.0 : -1.0
				});
			}
		}
	}

	this.testmat = app.gfx.materials.create('test', [](var m) {
		m.program = pbr; m.pbr.albedo = two.rgba(0x888888); m.pbr.metallic = 1.0; m.pbr.roughness = 0.66;
	});

	//two.gfx.radiance(root, 'radiance/tiber_1_1k.hdr', BackgroundMode::Radiance);

	two.gfx.shape(root, new two.Sphere(), 0, testmat);

	var time = app.gfx.time;

	for(ExLight l : lights)
	{
		var r = 0.8 + 0.2 * Math.sin(l.pr + (0.6 + 0.3 * l.sr) * time);
		var x = (Math.sin(l.pc + (0.8 + 0.2 * l.sc) * time * l.dir)) * r * radius;
		var z = (Math.cos(l.pc + (0.8 + 0.2 * l.sc) * time * l.dir)) * r * radius;
		var y = Math.sin(l.py + (0.8 + 0.2 * l.sy) * time) * r * 32.0;
		l.node->transform = l.parent->transform * bxTRS(new two.vec3(1.0), ZeroQuat, new two.vec3(x, y, z));
	}
}