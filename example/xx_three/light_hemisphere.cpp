//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-gltf/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

static string skydome_vertex()
{
	string shader =

		"varying vec3 vWorldPosition;\n"

		"void main() {\n"

		"	vec4 worldPosition = modelMatrix * vec4( position, 1.0 );\n"
		"	vWorldPosition = worldPosition.xyz;\n"

		"	gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );\n"

		"}\n";

	return shader;
}

static string skydome_fragment()
{
	string shader =

		"uniform vec3 topColor;\n"
		"uniform vec3 bottomColor;\n"
		"uniform float offset;\n"
		"uniform float exponent;\n"

		"varying vec3 vWorldPosition;\n"

		"void main() {\n"

		"	float h = normalize( vWorldPosition + offset ).y;\n"
		"	gl_FragColor = vec4( mix( bottomColor, topColor, max( pow( max( h , 0.0), exponent ), 0.0 ) ), 1.0 );\n"

		"}\n";

	return shader;
}

void xx_light_hemisphere(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);

#if 0
	function init() {

		var container = document.getElementById( 'container' );

		camera = new THREE.PerspectiveCamera( 30, window.innerWidth / window.innerHeight, 1, 5000 );
		camera.position.set( 0, 0, 250 );

		scene = new THREE.Scene();
		scene.background = new THREE.Color().setHSL( 0.6, 0, 1 );
		scene.fog = new THREE.Fog( scene.background, 1, 5000 );

		// LIGHTS

		hemiLight = new THREE.HemisphereLight( 0xffffff, 0xffffff, 0.6 );
		hemiLight.color.setHSL( 0.6, 1, 0.6 );
		hemiLight.groundColor.setHSL( 0.095, 1, 0.75 );
		hemiLight.position.set( 0, 50, 0 );
		scene.add( hemiLight );

		hemiLightHelper = new THREE.HemisphereLightHelper( hemiLight, 10 );
		scene.add( hemiLightHelper );

		//

		dirLight = new THREE.DirectionalLight( 0xffffff, 1 );
		dirLight.color.setHSL( 0.1, 1, 0.95 );
		dirLight.position.set( - 1, 1.75, 1 );
		dirLight.position.multiplyScalar( 30 );
		scene.add( dirLight );

		dirLight.castShadow = true;

		dirLight.shadow.mapSize.width = 2048;
		dirLight.shadow.mapSize.height = 2048;

		var d = 50;

		dirLight.shadow.camera.left = - d;
		dirLight.shadow.camera.right = d;
		dirLight.shadow.camera.top = d;
		dirLight.shadow.camera.bottom = - d;

		dirLight.shadow.camera.far = 3500;
		dirLight.shadow.bias = - 0.0001;

		dirLightHeper = new THREE.DirectionalLightHelper( dirLight, 10 );
		scene.add( dirLightHeper );

		// GROUND

		var groundGeo = new THREE.PlaneBufferGeometry( 10000, 10000 );
		var groundMat = new THREE.MeshLambertMaterial( { color: 0xffffff } );
		groundMat.color.setHSL( 0.095, 1, 0.75 );

		var ground = new THREE.Mesh( groundGeo, groundMat );
		ground.position.y = - 33;
		ground.rotation.x = - Math.PI / 2;
		ground.receiveShadow = true;
		scene.add( ground );

		// SKYDOME

		var vertexShader = document.getElementById( 'vertexShader' ).textContent;
		var fragmentShader = document.getElementById( 'fragmentShader' ).textContent;
		var uniforms = {
			"topColor": { value: new THREE.Color( 0x0077ff ) },
			"bottomColor": { value: new THREE.Color( 0xffffff ) },
			"offset": { value: 33 },
			"exponent": { value: 0.6 }
		};
		uniforms[ "topColor" ].value.copy( hemiLight.color );

		scene.fog.color.copy( uniforms[ "bottomColor" ].value );

		var skyGeo = new THREE.SphereBufferGeometry( 4000, 32, 15 );
		var skyMat = new THREE.ShaderMaterial( {
			uniforms: uniforms,
			vertexShader: vertexShader,
			fragmentShader: fragmentShader,
			side: THREE.BackSide
		} );

		var sky = new THREE.Mesh( skyGeo, skyMat );
		scene.add( sky );

		// MODEL

		var loader = new THREE.GLTFLoader();

		loader.load( 'models/gltf/Flamingo.glb', function ( gltf ) {

			var mesh = gltf.scene.children[ 0 ];

			var s = 0.35;
			mesh.scale.set( s, s, s );
			mesh.position.y = 15;
			mesh.rotation.y = - 1;

			mesh.castShadow = true;
			mesh.receiveShadow = true;

			scene.add( mesh );

			var mixer = new THREE.AnimationMixer( mesh );
			mixer.clipAction( gltf.animations[ 0 ] ).setDuration( 1 ).play();
			mixers.push( mixer );

		} );

		// RENDERER

		renderer = new THREE.WebGLRenderer( { antialias: true } );
		renderer.setPixelRatio( window.devicePixelRatio );
		renderer.setSize( window.innerWidth, window.innerHeight );
		container.appendChild( renderer.domElement );

		renderer.gammaInput = true;
		renderer.gammaOutput = true;

		renderer.shadowMap.enabled = true;

		// STATS

		stats = new Stats();
		container.appendChild( stats.dom );

		//

		window.addEventListener( 'resize', onWindowResize, false );
		document.addEventListener( 'keydown', onKeyDown, false );

	}

	function onWindowResize() {

		camera.aspect = window.innerWidth / window.innerHeight;
		camera.updateProjectionMatrix();

		renderer.setSize( window.innerWidth, window.innerHeight );

	}

	function onKeyDown( event ) {

		switch ( event.keyCode ) {

			case 72: // h

				hemiLight.visible = ! hemiLight.visible;
				hemiLightHelper.visible = ! hemiLightHelper.visible;
				break;

			case 68: // d

				dirLight.visible = ! dirLight.visible;
				dirLightHeper.visible = ! dirLightHeper.visible;
				break;

		}

	}

	//

	function animate() {

		requestAnimationFrame( animate );

		render();
		stats.update();

	}

	function render() {

		var delta = clock.getDelta();

		for ( var i = 0; i < mixers.length; i ++ ) {

			mixers[ i ].update( delta );

		}

		renderer.render( scene, camera );

	}
#endif
}
