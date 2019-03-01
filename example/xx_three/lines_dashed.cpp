//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

//Model& cube(float size)
void cube(float size)
{
	float h = size * 0.5;

	//var geometry = new THREE.BufferGeometry();
	vector<vec3> positions = {
		vec3(-h, -h, -h), vec3(-h,  h, -h),
		vec3(-h,  h, -h), vec3( h,  h, -h),
		vec3( h,  h, -h), vec3( h, -h, -h),
		vec3( h, -h, -h), vec3(-h, -h, -h),
		vec3(-h, -h,  h), vec3(-h,  h,  h),
		vec3(-h,  h,  h), vec3( h,  h,  h),
		vec3( h,  h,  h), vec3( h, -h,  h),
		vec3( h, -h,  h), vec3(-h, -h,  h),
		vec3(-h, -h, -h), vec3(-h, -h,  h),
		vec3(-h,  h, -h), vec3(-h,  h,  h),
		vec3( h,  h, -h), vec3( h,  h,  h),
		vec3( h, -h, -h), vec3( h, -h,  h)
	};

	//geometry.addAttribute('position', new THREE.Float32BufferAttribute(position, 3));

	//return geometry;
}

void xx_lines_dashed(Shell& app, Widget& parent, Dockbar& dockbar)
{
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Camera& camera = viewer.m_camera;
	camera.m_fov = 60.f; camera.m_near = 1.f; camera.m_far = 200.f;
	camera.m_eye.z = 150.f;

	Scene& scene = viewer.m_scene;
	//scene.background = new THREE.Color( 0x111111 );
	//scene.fog = new THREE.Fog( 0x111111, 150, 200 );

	size_t subdivisions = 6;
	size_t recursion = 1;

	//var points = hilbert3D( new THREE.Vector3( 0, 0, 0 ), 25.0, recursion, 0, 1, 2, 3, 4, 5, 6, 7 );
	//var spline = new THREE.CatmullRomCurve3( points );
	/*
	var samples = spline.getPoints(points.length * subdivisions);
	var geometrySpline = new THREE.BufferGeometry().setFromPoints(samples);

	var line = new THREE.Line(geometrySpline, new THREE.LineDashedMaterial({ color: 0xffffff, dashSize : 1, gapSize : 0.5 }));
	line.computeLineDistances();

	objects.push(line);
	scene.add(line);

	var geometryCube = cube(50);

	var lineSegments = new THREE.LineSegments(geometryCube, new THREE.LineDashedMaterial({ color: 0xffaa00, dashSize : 3, gapSize : 1 }));
	lineSegments.computeLineDistances();

	objects.push(lineSegments);
	scene.add(lineSegments);



	float time = app.m_gfx_system.m_time;

	scene.traverse(function(object) {

		if(object.isLine) {

			object.rotation.x = 0.25 * time;
			object.rotation.y = 0.25 * time;

		}

	});

	renderer.render(scene, camera);
	*/
}
