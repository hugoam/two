

#if 0

"#ifdef VERTEX_TEXTURES",

	"uniform sampler2D tDisplacement;",
	"uniform float uDisplacementScale;",
	"uniform float uDisplacementBias;",

"#endif",

"varying vec3 vNormal;",
"varying vec2 v_uv0;",

"varying vec3 vViewPosition;",

THREE.ShaderChunk[ "common" ],
THREE.ShaderChunk[ "fog_pars_vertex" ],

"void main() {",

	"vec4 worldPosition = modelMatrix * vec4( position, 1.0 );",

	"vec4 mvPosition = modelViewMatrix * vec4( position, 1.0 );",

	"vViewPosition = -mvPosition.xyz;",

	"vNormal = normalize( normalMatrix * normal );",

	"v_uv0 = uv;",

	// displacement mapping

	"#ifdef VERTEX_TEXTURES",

		"vec3 dv = texture2D( tDisplacement, uv ).xyz;",
		"float df = uDisplacementScale * dv.x + uDisplacementBias;",
		"vec4 displacedPosition = vec4( vNormal.xyz * df, 0.0 ) + mvPosition;",
		"gl_Position = projectionMatrix * displacedPosition;",

	"#else",

		"gl_Position = projectionMatrix * mvPosition;",

	"#endif",

	THREE.ShaderChunk[ "fog_vertex" ],

"}",

#endif

//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>

#include <xx_three/xx_three.h>

void xx_material_displace(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	static ImporterOBJ obj_importer(app.m_gfx);

	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controls(viewer);
	//controls.enableZoom = false;
	//controls.enableDamping = true;

	Scene& scene = viewer.m_scene;

	//var settings = {
	//	metalness: 1.0,
	//	roughness: 0.4,
	//	ambientIntensity: 0.2,
	//	aoMapIntensity: 1.0,
	//	envMapIntensity: 1.0,
	//	displacementScale: 2.436143, // from original model
	//	normalScale: 1.0
	//};

	int height = 500; // of camera frustum

	float r = 0.0;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 40.f; camera.m_near = 1.f; camera.m_far = 10000.f;
		camera.m_eye = vec3(-5.f, 2.5f, -3.5f);

		//renderer.gammaInput = true;
		//renderer.gammaOutput = true;

		//var aspect = window.innerWidth / window.innerHeight;
		//camera = new THREE.OrthographicCamera(-height * aspect, height * aspect, height, -height, 1, 10000);
		//camera.position.z = 1500;
		//scene.add(camera);

#if 0
		// lights

		ambientLight = new THREE.AmbientLight(0xffffff, settings.ambientIntensity);
		scene.add(ambientLight);

		pointLight = new THREE.PointLight(0xff0000, 0.5);
		pointLight.position.z = 2500;
		scene.add(pointLight);

		var pointLight2 = new THREE.PointLight(0xff6666, 1);
		camera.add(pointLight2);

		var pointLight3 = new THREE.PointLight(0x0000ff, 0.5);
		pointLight3.position.x = -1000;
		pointLight3.position.z = 1000;
		scene.add(pointLight3);

		// env map

		var path = "textures/cube/SwedishRoyalCastle/";
		var format = '.jpg';
		var urls = [
			path + 'px' + format, path + 'nx' + format,
				path + 'py' + format, path + 'ny' + format,
				path + 'pz' + format, path + 'nz' + format
		];

		var reflectionCube = new THREE.CubeTextureLoader().load(urls);

		// textures

		var textureLoader = new THREE.TextureLoader();
		var normalMap = textureLoader.load("models/obj/ninja/normal.jpg");
		var aoMap = textureLoader.load("models/obj/ninja/ao.jpg");
		var displacementMap = textureLoader.load("models/obj/ninja/displacement.jpg");

		// material

		material = new THREE.MeshStandardMaterial({

			color: 0x888888,
			roughness : settings.roughness,
			metalness : settings.metalness,

			normalMap : normalMap,
			normalScale : new THREE.Vector2(1, -1), // why does the normal map require negation in this case?

			aoMap : aoMap,
			aoMapIntensity : 1,

			displacementMap : displacementMap,
			displacementScale : settings.displacementScale,
			displacementBias : -0.428408, // from original model

			envMap : reflectionCube,
			envMapIntensity : settings.envMapIntensity,

			side : THREE.DoubleSide

			});

		//

		var loader = new THREE.OBJLoader();
		loader.load("models/obj/ninja/ninjaHead_Low.obj", function(group) {

			var geometry = group.children[0].geometry;
			geometry.attributes.uv2 = geometry.attributes.uv;
			geometry.center();

			mesh = new THREE.Mesh(geometry, material);
			mesh.scale.multiplyScalar(25);
			scene.add(mesh);

		});
#endif
	}

	//var gui = new dat.GUI();
	////var gui = gui.addFolder( "Material" );
	//gui.add( settings, "metalness" ).min( 0 ).max( 1 ).onChange( function ( value ) {
	//	material.metalness = value;
	//} );
	//
	//gui.add( settings, "roughness" ).min( 0 ).max( 1 ).onChange( function ( value ) {
	//	material.roughness = value;
	//} );
	//
	//gui.add( settings, "aoMapIntensity" ).min( 0 ).max( 1 ).onChange( function ( value ) {
	//	material.aoMapIntensity = value;
	//} );
	//
	//gui.add( settings, "ambientIntensity" ).min( 0 ).max( 1 ).onChange( function ( value ) {
	//	ambientLight.intensity = value;
	//} );
	//
	//gui.add( settings, "envMapIntensity" ).min( 0 ).max( 3 ).onChange( function ( value ) {
	//	material.envMapIntensity = value;
	//} );
	//
	//gui.add( settings, "displacementScale" ).min( 0 ).max( 3.0 ).onChange( function ( value ) {
	//	material.displacementScale = value;
	//} );
	//
	//gui.add( settings, "normalScale" ).min( - 1 ).max( 1 ).onChange( function ( value ) {
	//	material.normalScale.set( 1, - 1 ).multiplyScalar( value );
	//} );


	//pointLight.position.x = 2500 * Math.cos( r );
	//pointLight.position.z = 2500 * Math.sin( r );
	//
	//r += 0.01;
}
