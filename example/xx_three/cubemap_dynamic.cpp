//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_cubemap_dynamic(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	size_t count = 0;

	float lon = 0.f; float lat = 0.f;
	float phi = 0.f; float theta = 0.f;

	Texture& texture = *app.m_gfx.textures().file("2294472375_24a3b8ef46_o.jpg");
	UNUSED(texture);

	static Node3* sphere = nullptr;
	static Node3* cube = nullptr;
	static Node3* torus = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 60.f; camera.m_near = 1.f; camera.m_far = 1000.f;

		//var options = {
		//	resolution: 1024,
		//
		//	generateMipmaps : true,
		//	minFilter : THREE.LinearMipMapLinearFilter,
		//	magFilter : THREE.LinearFilter
		//};
		//
		//scene.background = new THREE.CubemapGenerator(renderer).fromEquirectangular(texture, options);

		//cubeCamera1 = new THREE.CubeCamera(1, 1000, 256);
		//cubeCamera1.renderTarget.texture.generateMipmaps = true;
		//cubeCamera1.renderTarget.texture.minFilter = THREE.LinearMipMapLinearFilter;
		//scene.add(cubeCamera1);
		//
		//cubeCamera2 = new THREE.CubeCamera(1, 1000, 256);
		//cubeCamera2.renderTarget.texture.generateMipmaps = true;
		//cubeCamera2.renderTarget.texture.minFilter = THREE.LinearMipMapLinearFilter;
		//scene.add(cubeCamera2);

		//material = new THREE.MeshBasicMaterial({
		//	envMap: cubeCamera2.renderTarget.texture
		//});

		sphere = &gfx::nodes(scene).add(Node3());
		gfx::items(scene).add(Item(*sphere, app.m_gfx.shape(Icosahedron(20.f))));

		cube = &gfx::nodes(scene).add(Node3());
		gfx::items(scene).add(Item(*cube, app.m_gfx.shape(Cube(20.f))));

		torus = &gfx::nodes(scene).add(Node3());
		gfx::items(scene).add(Item(*torus, app.m_gfx.shape(TorusKnot(10.f, 5.f))));
	}

	//function onDocumentMouseDown(event) {
	//
	//	event.preventDefault();
	//
	//	onPointerDownPointerX = event.clientX;
	//	onPointerDownPointerY = event.clientY;
	//
	//	onPointerDownLon = lon;
	//	onPointerDownLat = lat;
	//
	//	document.addEventListener('mousemove', onDocumentMouseMove, false);
	//	document.addEventListener('mouseup', onDocumentMouseUp, false);
	//
	//}

	//function onDocumentMouseMove(event) {
	//
	//	lon = (event.clientX - onPointerDownPointerX) * 0.1 + onPointerDownLon;
	//	lat = (event.clientY - onPointerDownPointerY) * 0.1 + onPointerDownLat;
	//
	//}


	//function onDocumentMouseWheel(event) {
	//
	//	var fov = camera.fov + event.deltaY * 0.05;
	//
	//	camera.fov = THREE.clamp(fov, 10, 75);
	//
	//	camera.updateProjectionMatrix();
	//
	//}

	const float time = app.m_gfx.m_time;

	lon += 0.15f;

	lat = max(-85.f, min(85.f, lat));
	phi = to_radians(90.f - lat);
	theta = to_radians(lon);

	static vec3 cubea = vec3(0.f);
	static vec3 torusa = vec3(0.f);

	auto trigo3 = [](const vec3& a) { return vec3(cos(a.x), sin(a.y), sin(a.z)); };

	vec3 cubep = trigo3(vec3(time * 0.001f)) * 30.f;
	cubea += vec3(0.02f, 0.03f, 0.f);

	vec3 torusp = trigo3(vec3(time * 0.001f + 10.f)) * 30.f;
	torusa += vec3(0.02f, 0.03f, 0.f);

	Camera& camera = viewer.m_camera;
	camera.m_eye.x = 100.f * sin(phi) * cos(theta);
	camera.m_eye.y = 100.f * cos(phi);
	camera.m_eye.z = 100.f * sin(phi) * sin(theta);

	//camera.lookAt(scene.position);

	//sphere.visible = false;

	// pingpong

	//if(count % 2 == 0) {
	//	material.envMap = cubeCamera1.renderTarget.texture;
	//	cubeCamera2.update(renderer, scene);
	//}
	//else {
	//	material.envMap = cubeCamera2.renderTarget.texture;
	//	cubeCamera1.update(renderer, scene);
	//}

	count++;

	//sphere.visible = true;
}
