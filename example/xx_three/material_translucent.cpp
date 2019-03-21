//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

// @author daoshengmu / http://dsmu.me/

/* ------------------------------------------------------------------------------------------
//	Subsurface Scattering shader
// 		- Base on GDC 2011 – Approximating Translucency for a Fast, Cheap and Convincing Subsurface Scattering Look
// 			https://colinbarrebrisebois.com/2011/03/07/gdc-2011-approximating-translucency-for-a-fast-cheap-and-convincing-subsurface-scattering-look/
// ------------------------------------------------------------------------------------------ */

#if 0
THREE.TranslucentShader = function TranslucentShader() {

	this.uniforms = THREE.UniformsUtils.merge([

		THREE.UniformsLib["common"],
			THREE.UniformsLib["lights"],

		{
			"color":  { value: new THREE.Color(0xffffff) },
			"diffuse" : { value: new THREE.Color(0xffffff) },
			"specular" : { value: new THREE.Color(0xffffff) },
			"emissive" : { value: new THREE.Color(0x000000) },
			"opacity" : { value: 1 },
			"shininess" : { value: 1 },

			"thicknessMap" : { value: null },
			"thicknessColor" : { value: new THREE.Color(0xffffff) },
			"thicknessDistortion" : { value: 0.1 },
			"thicknessAmbient" : { value: 0.0 },
			"thicknessAttenuation" : { value: 0.1 },
			"thicknessPower" : { value: 2.0 },
			"thicknessScale" : { value: 10.0 }
		}

	]);

};
#endif

static string translucent_fragment()
{
	string shader =
		
		"#define USE_MAP\n"
		"#define PHONG\n"
		"#define TRANSLUCENT\n"
		"#include <common>\n"
		"#include <bsdfs>\n"
		"#include <uv_pars_fragment>\n"
		"#include <map_pars_fragment>\n"
		"#include <lights_phong_pars_fragment>\n"

		"varying vec3 vColor;\n"

		"uniform vec3 diffuse;\n"
		"uniform vec3 specular;\n"
		"uniform vec3 emissive;\n"
		"uniform float opacity;\n"
		"uniform float shininess;\n"

		// Translucency
		"uniform sampler2D thicknessMap;\n"
		"uniform float thicknessPower;\n"
		"uniform float thicknessScale;\n"
		"uniform float thicknessDistortion;\n"
		"uniform float thicknessAmbient;\n"
		"uniform float thicknessAttenuation;\n"
		"uniform vec3 thicknessColor;\n"

		//THREE.ShaderChunk["lights_pars_begin"],

		"void RE_Direct_Scattering(IncidentLight directLight, vec2 uv, GeometricContext geometry, inout ReflectedLight reflectedLight) {\n"
		"	vec3 thickness = thicknessColor * texture2D(thicknessMap, uv).r;\n"
		"	vec3 scatteringHalf = normalize(directLight.direction + (geometry.normal * thicknessDistortion));\n"
		"	float scatteringDot = pow(saturate(dot(geometry.viewDir, -scatteringHalf)), thicknessPower) * thicknessScale;\n"
		"	vec3 scatteringIllu = (scatteringDot + thicknessAmbient) * thickness;\n"
		"	reflectedLight.directDiffuse += scatteringIllu * thicknessAttenuation * directLight.color;\n"
		"}\n"

		"void main() {\n"

		"	vec3 normal = normalize(vNormal);\n"

		"	vec3 viewerDirection = normalize(vViewPosition);\n"

		"	vec4 diffuseColor = vec4(diffuse, opacity);\n"
		"	ReflectedLight reflectedLight = ReflectedLight(vec3(0.0), vec3(0.0), vec3(0.0), vec3(0.0));\n"

			//THREE.ShaderChunk["map_fragment"],
			//THREE.ShaderChunk["color_fragment"],
			//THREE.ShaderChunk["specularmap_fragment"],

		"	vec3 totalEmissiveRadiance = emissive;\n"

			//THREE.ShaderChunk["lights_phong_fragment"],

		// Doing lights fragment begin.
		"	GeometricContext geometry;\n"
		"	geometry.position = - vViewPosition;\n"
		"	geometry.normal = normal;\n"
		"	geometry.viewDir = normalize(vViewPosition);\n"

		"	IncidentLight directLight;\n"

		"	#if (NUM_POINT_LIGHTS > 0) && defined(RE_Direct)\n"

		"		PointLight pointLight;\n"

		"		#pragma unroll_loop\n"
		"		for (int i = 0; i < NUM_POINT_LIGHTS; i ++) {\n"
		"		 	pointLight = pointLights[i];\n"
		"		 	getPointDirectLightIrradiance(pointLight, geometry, directLight);\n"

		"			#ifdef USE_SHADOWMAP\n"
		"			directLight.color *= all(bvec2(pointLight.shadow, directLight.visible)) ? getPointShadow(pointShadowMap[i], pointLight.shadowMapSize, pointLight.shadowBias, pointLight.shadowRadius, vPointShadowCoord[i], pointLight.shadowCameraNear, pointLight.shadowCameraFar) : 1.0;\n"
		"			#endif\n"

		"			RE_Direct(directLight, geometry, material, reflectedLight);\n"

		"			#if defined(TRANSLUCENT) && defined(USE_MAP)\n"
		"			RE_Direct_Scattering(directLight, v_uv0, geometry, reflectedLight);\n"
		"			#endif\n"
		"		}\n"

		"		#endif\n"

		"	#if (NUM_DIR_LIGHTS > 0) && defined(RE_Direct)\n"

		"		DirectionalLight directionalLight;\n"

		"		#pragma unroll_loop\n"
		"		for (int i = 0; i < NUM_DIR_LIGHTS; i ++) {\n"
		"			directionalLight = directionalLights[i];\n"
		"			getDirectionalDirectLightIrradiance(directionalLight, geometry, directLight);\n"

		"			#ifdef USE_SHADOWMAP\n"
		"			directLight.color *= all(bvec2(directionalLight.shadow, directLight.visible)) ? getShadow(directionalShadowMap[i], directionalLight.shadowMapSize, directionalLight.shadowBias, directionalLight.shadowRadius, vDirectionalShadowCoord[i]) : 1.0;\n"
		"			#endif\n"

		"			RE_Direct(directLight, geometry, material, reflectedLight);\n"

		"			#if defined(TRANSLUCENT) && defined(USE_MAP)\n"
		"			RE_Direct_Scattering(directLight, v_uv0, geometry, reflectedLight);\n"
		"			#endif\n"
		"		}\n"

		"	#endif\n"

		"	#if defined(RE_IndirectDiffuse)\n"

		"		vec3 irradiance = getAmbientLightIrradiance(ambientLightColor);\n"

		"		#if (NUM_HEMI_LIGHTS > 0)\n"

		"			#pragma unroll_loop\n"
		"			for (int i = 0; i < NUM_HEMI_LIGHTS; i ++) {\n"

		"				irradiance += getHemisphereLightIrradiance(hemisphereLights[i], geometry);\n"

		"			}\n"

		"		#endif\n"

		"	#endif\n"

		"	#if defined(RE_IndirectSpecular)\n"

		"		vec3 radiance = vec3(0.0);\n"
		"		vec3 clearCoatRadiance = vec3(0.0);\n"

		"	#endif\n"
			//THREE.ShaderChunk["lights_fragment_end"],

		"	vec3 outgoingLight = reflectedLight.directDiffuse + reflectedLight.indirectDiffuse + reflectedLight.directSpecular + reflectedLight.indirectSpecular + totalEmissiveRadiance;\n"
		"	gl_FragColor = vec4(outgoingLight, diffuseColor.a);\n"	// TODO, this should be pre-multiplied to allow for bright highlights on very transparent objects

			//THREE.ShaderChunk["encodings_fragment"],

		"}";

	return shader;
}

string sss_vertex()
{
	string shader =

		"varying vec3 vNormal;\n"
		"varying vec2 v_uv0;\n"

		"varying vec3 vViewPosition;\n"

		//THREE.ShaderChunk["common"],

		"void main() {\n"

		"	vec4 worldPosition = u_model * vec4(a_position.xyz, 1.0);\n"

		"	vec4 mvPosition = mul(u_modelView, vec4(a_position.xyz, 1.0));\n"

		"	vViewPosition = -mvPosition.xyz;\n"

		//"	vNormal = normalize(normalMatrix * normal);\n"
		"	vNormal = normalize(u_normalModelViewProj * normal);\n"

		"	v_uv0 = uv;\n"

		"	gl_Position = u_proj * mvPosition;\n"

		"}\n";

	return shader;
}

//<script src="js/loaders/FBXLoader.js"></script>

void xx_material_translucent(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
#if 0
	if(init)
	{
		container = document.createElement('div');
		document.body.appendChild(container);

		camera = new THREE.PerspectiveCamera(40, window.innerWidth / window.innerHeight, 1, 5000);
		camera.position.set(0.0, 300, 400 * 4);

		scene = new THREE.Scene();

		// Lights

		scene.add(new THREE.AmbientLight(0x888888));

		var directionalLight = new THREE.DirectionalLight(0xffffff, 0.03);
		directionalLight.position.set(0.0, 0.5, 0.5).normalize();
		scene.add(directionalLight);

		var pointLight1 = new THREE.Mesh(new THREE.SphereBufferGeometry(4, 8, 8), new THREE.MeshBasicMaterial({ color: 0x888888 }));
		pointLight1.add(new THREE.PointLight(0x888888, 7.0, 300));
		scene.add(pointLight1);
		pointLight1.position.x = 0;
		pointLight1.position.y = -50;
		pointLight1.position.z = 350;

		var pointLight2 = new THREE.Mesh(new THREE.SphereBufferGeometry(4, 8, 8), new THREE.MeshBasicMaterial({ color: 0x888800 }));
		pointLight2.add(new THREE.PointLight(0x888800, 1.0, 500));
		scene.add(pointLight2);
		pointLight2.position.x = -100;
		pointLight2.position.y = 20;
		pointLight2.position.z = -260;

		renderer = new THREE.WebGLRenderer({ antialias: true });
		renderer.setPixelRatio(window.devicePixelRatio);
		renderer.setSize(window.innerWidth, window.innerHeight);
		container.appendChild(renderer.domElement);

		renderer.gammaInput = true;
		renderer.gammaOutput = true;

		//

		stats = new Stats();
		container.appendChild(stats.dom);

		var controls = new THREE.OrbitControls(camera, container);

		window.addEventListener('resize', onWindowResize, false);

		initMaterial();
	}

	function initMaterial() {

		var loader = new THREE.TextureLoader();
		var imgTexture = loader.load('models/fbx/white.jpg');
		var thicknessTexture = loader.load('models/fbx/bunny_thickness.jpg');
		imgTexture.wrapS = imgTexture.wrapT = THREE.RepeatWrapping;

		var shader = new THREE.TranslucentShader();
		var uniforms = THREE.UniformsUtils.clone(shader.uniforms);

		uniforms['map'].value = imgTexture;

		uniforms['diffuse'].value = new THREE.Vector3(1.0, 0.2, 0.2);
		uniforms['shininess'].value = 500;

		uniforms['thicknessMap'].value = thicknessTexture;
		uniforms['thicknessColor'].value = new THREE.Vector3(0.5, 0.3, 0.0);
		uniforms['thicknessDistortion'].value = 0.1;
		uniforms['thicknessAmbient'].value = 0.4;
		uniforms['thicknessAttenuation'].value = 0.8;
		uniforms['thicknessPower'].value = 2.0;
		uniforms['thicknessScale'].value = 16.0;

		var material = new THREE.ShaderMaterial({
			uniforms: uniforms,
			vertexShader : shader.vertexShader,
			fragmentShader : shader.fragmentShader,
			lights : true
			});
		material.extensions.derivatives = true;

		// LOADER

		var loader = new THREE.FBXLoader();
		loader.load('models/fbx/stanford-bunny.fbx', function(object) {

			model = object.children[0];
			model.position.set(0, 0, 10);
			model.scale.setScalar(1);
			model.material = material;
			scene.add(model);

		});

		initGUI(uniforms);

	}

	function initGUI(uniforms) {

		var gui = new dat.GUI();

		var ThicknessControls = function() {

			this.distoration = uniforms['thicknessDistortion'].value;
			this.ambient = uniforms['thicknessAmbient'].value;
			this.attenuation = uniforms['thicknessAttenuation'].value;
			this.power = uniforms['thicknessPower'].value;
			this.scale = uniforms['thicknessScale'].value;

		};

		var thicknessControls = new ThicknessControls();
		var thicknessFolder = gui.addFolder('Thickness Control');

		thicknessFolder.add(thicknessControls, 'distoration').min(0.01).max(1).step(0.01).onChange(function() {

			uniforms['thicknessDistortion'].value = thicknessControls.distoration;

		});

		thicknessFolder.add(thicknessControls, 'ambient').min(0.01).max(5.0).step(0.05).onChange(function() {

			uniforms['thicknessAmbient'].value = thicknessControls.ambient;

		});

		thicknessFolder.add(thicknessControls, 'attenuation').min(0.01).max(5.0).step(0.05).onChange(function() {

			uniforms['thicknessAttenuation'].value = thicknessControls.attenuation;

		});

		thicknessFolder.add(thicknessControls, 'power').min(0.01).max(16.0).step(0.1).onChange(function() {

			uniforms['thicknessPower'].value = thicknessControls.power;

		});

		thicknessFolder.add(thicknessControls, 'scale').min(0.01).max(50.0).step(0.1).onChange(function() {

			uniforms['thicknessScale'].value = thicknessControls.scale;

		});

		thicknessFolder.open();

	}

	function onWindowResize() {

		camera.aspect = window.innerWidth / window.innerHeight;
		camera.updateProjectionMatrix();

		renderer.setSize(window.innerWidth, window.innerHeight);

	}

	//

	function animate() {

		requestAnimationFrame(animate);

		render();

		stats.update();

	}

	function render() {

		if(model) model.rotation.y = performance.now() / 5000;

		renderer.render(scene, camera);

	}
#endif
}
