//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

static string vertex_shader()
{
	string shader =

		"varying vec2 vUv;\n"
		"\n"
		"void main() {\n"
		"	vUv = uv;\n"
		"	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);\n"
		"}\n";

	return shader;
}

static string fragment_shader()
{
	string shader =

		"#include <packing>\n"
		"\n"
		"varying vec2 vUv;\n"
		"uniform sampler2D tDiffuse;\n"
		"uniform sampler2D tDepth;\n"
		"uniform float cameraNear;\n"
		"uniform float cameraFar;\n"
		"\n"
		"\n"
		"float readDepth(sampler2D depthSampler, vec2 coord) {\n"
		"	float fragCoordZ = texture2D(depthSampler, coord).x;\n"
		"	float viewZ = perspectiveDepthToViewZ(fragCoordZ, cameraNear, cameraFar);\n"
		"	return viewZToOrthographicDepth(viewZ, cameraNear, cameraFar);\n"
		"}\n"
		"\n"
		"void main() {\n"
		"	//vec3 diffuse = texture2D(tDiffuse, vUv).rgb;\n"
		"	float depth = readDepth(tDepth, vUv);\n"
		"\n"
		"	gl_FragColor.rgb = 1.0 - vec3(depth);\n"
		"	gl_FragColor.a = 1.0;\n"
		"}\n";

	return shader;
}

void xx_depth_texture(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	//var controls = new THREE.OrbitControls(camera, renderer.domElement);
	//controls.enableDamping = true;
	//controls.dampingFactor = 0.25;
	//controls.rotateSpeed = 0.35;

	Scene& scene = viewer.m_scene;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 70.f; camera.m_near = 0.01f; camera.m_far = 50.f;
		camera.m_eye.z = 4.f;

		//var diffuse = new THREE.TextureLoader().load('textures/brick_diffuse.jpg');
		//diffuse.wrapS = diffuse.wrapT = THREE.RepeatWrapping;

		Model& geometry = app.m_gfx.shape(TorusKnot());
		//var geometry = new THREE.TorusKnotBufferGeometry(1, 0.3, 128, 64);

		// Setup some geometries
		Material material = app.m_gfx.materials().create("material", [](Material& m) {
			m.m_solid.m_colour = Colour::Blue;
		});

		const size_t count = 50U;
		const float scale = 5.f;

		for(size_t i = 0; i < count; i++)
		{
			const float r = randf() * 2.f * c_pi;
			const float z = (randf() * 2.f) - 1.f;
			const float distscale = sqrt(1.f - z * z) * scale;

			const vec3 p = vec3(cos(r) * distscale, sin(r) * distscale, z * scale);
			const vec3 a = vec3(randf(), randf(), randf());
			Node3& n = gfx::nodes(scene).add(Node3(p));
			gfx::items(scene).add(Item(n, geometry, 0U, &material));
		}

		// Create a multi render target with Float buffers
		//target = new THREE.WebGLRenderTarget(window.innerWidth, window.innerHeight);
		//target.texture.format = THREE.RGBFormat;
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