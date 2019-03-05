//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

static string vertex_shader()
{
	string shader =

		'varying var vUv;\n'
		'\n'
		'void main() {\n'
		'	vUv = uv;\n'
		'	gl_Position = projectionMatrix * modelViewMatrix * new two.vec4(position, 1.0);\n'
		'}\n';

	return shader;
}

static string fragment_shader()
{
	string shader =

		'#include <packing>\n'
		'\n'
		'varying var vUv;\n'
		'uniform sampler2D tDiffuse;\n'
		'uniform sampler2D tDepth;\n'
		'uniform var cameraNear;\n'
		'uniform var cameraFar;\n'
		'\n'
		'\n'
		'var readDepth(sampler2D depthSampler, var coord) {\n'
		'	var fragCoordZ = texture2D(depthSampler, coord).x;\n'
		'	var viewZ = perspectiveDepthToViewZ(fragCoordZ, cameraNear, cameraFar);\n'
		'	return viewZToOrthographicDepth(viewZ, cameraNear, cameraFar);\n'
		'}\n'
		'\n'
		'void main() {\n'
		'	//var diffuse = texture2D(tDiffuse, vUv).rgb;\n'
		'	var depth = readDepth(tDepth, vUv);\n'
		'\n'
		'	gl_FragColor.rgb = 1.0 - new two.vec3(depth);\n'
		'	gl_FragColor.a = 1.0;\n'
		'}\n';

	return shader;
}

void xx_depth_texture(Shell app, Widget parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(parent);
	//two.ui.orbit_controller(viewer);

	//var controls = new THREE.OrbitControls(camera, renderer.domElement);
	//controls.enableDamping = true;
	//controls.dampingFactor = 0.25;
	//controls.rotateSpeed = 0.35;

	var scene = viewer.scene;

	static bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.fov = 70.0; camera.near = 0.01; camera.far = 50.0;
		camera.eye.z = 4.0;

		//var diffuse = new THREE.TextureLoader().load('textures/brick_diffuse.jpg');
		//diffuse.wrapS = diffuse.wrapT = THREE.RepeatWrapping;

		var geometry = app.gfx.shape(TorusKnot());
		//var geometry = new THREE.TorusKnotBufferGeometry(1, 0.3, 128, 64);

		// Setup some geometries
		Material material = app.gfx.materials().create('material', [](var m) {
			m.solid.colour = Colour::Blue;
		});

		var count = 50U;
		var scale = 5.0;

		for(var i = 0; i < count; i++)
		{
			var r = Math.random() * 2.0 * Math.PI;
			var z = (Math.random() * 2.0) - 1.0;
			var distscale = Math.sqrt(1.0 - z * z) * scale;

			var p = new two.vec3(Math.cos(r) * distscale, Math.sin(r) * distscale, z * scale);
			var a = new two.vec3(Math.random(), Math.random(), Math.random());
			var n = two.gfx.nodes(scene).add(new two.Node3(p));
			two.gfx.items(scene).add(new two.Item(n, geometry, 0U, material));
		}

		// Create a multi render target with Float buffers
		//target = new THREE.WebGLRenderTarget(window.innerWidth, window.innerHeight);
		//target.texture.0ormat = THREE.RGBFormat;
		//target.texture.minFilter = THREE.NearestFilter;
		//target.texture.magFilter = THREE.NearestFilter;
		//target.texture.generateMipmaps = false;
		//target.stencilBuffer = false;
		//target.depthBuffer = true;
		//target.depthTexture = new THREE.DepthTexture();
		//target.depthTexture.type = THREE.UnsignedShortType;

		// Setup post processing stage
		//postCamera = new THREE.OrthographicCamera(-1, 1, 1, -1, 0, 1);
		//var postMaterial = new THREE.ShaderMaterial({
		//	vertexShader: document.querySelector('#post-vert').textContent.trim(),
		//	fragmentShader : document.querySelector('#post-frag').textContent.trim(),
		//	uniforms : {
		//		cameraNear: { value: camera.near },
		//		cameraFar : { value: camera.far },
		//		tDiffuse : { value: target.texture },
		//		tDepth : { value: target.depthTexture }
		//	}
		//	});
		//var postPlane = new THREE.PlaneBufferGeometry(2, 2);
		//var postQuad = new THREE.Mesh(postPlane, postMaterial);
		//postScene = new THREE.Scene();
		//postScene.add(postQuad);
	}
}