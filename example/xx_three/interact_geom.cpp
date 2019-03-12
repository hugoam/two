//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_interact_geom(Shell& app, Widget& parent, Dockbar& dockbar)
{
	constexpr size_t triangles = 5000;

	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	static Program& pbr = *app.m_gfx.programs().file("pbr/pbr");

	static Material& material = app.m_gfx.materials().create("first",  [&](Material& m) {
		m.m_program = &pbr; m.m_pbr.m_albedo = rgb(0xaaaaaa); m.m_pbr.m_metallic = 1.0f; m.m_pbr.m_roughness = 0.66f;
		m.m_base.m_shader_color = ShaderColor::Vertex;
	});

	//var material = new THREE.MeshPhongMaterial({
	//	color: 0xaaaaaa, specular: 0xffffff, shininess: 250,
	//	side: THREE.DoubleSide, vertexColors: THREE.VertexColors
	//});

	static Node3* node = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 27.f; camera.m_near = 1.f; camera.m_far = 3500.f;
		camera.m_eye.z = 2750.f;

		//scene.background = new THREE.Color(0x050505);
		//scene.fog = new THREE.Fog(0x050505, 2000, 3500);

		//scene.add(new THREE.AmbientLight(0x444444));

		Node3& l1 = gfx::nodes(scene).add(Node3(vec3(0.f), facing(vec3(1.f, 1.f, 1.f))));
		gfx::lights(scene).add(Light(l1, LightType::Direct, false, rgb(0xffffff), 0.5f));

		Node3& l2 = gfx::nodes(scene).add(Node3(vec3(0.f), facing(vec3(0.f, -1.f, 0.f))));
		gfx::lights(scene).add(Light(l2, LightType::Direct, false, rgb(0xffffff), 1.5f));
		
		MeshPacker geometry;

		float s = 800; float s2 = s / 2;	// triangles spread in the cube
		float d = 120; float d2 = d / 2;	// individual triangle size

		for(size_t i = 0; i < triangles; i++)
		{
			vec3 p = vec3(randf(), randf(), randf()) * s - s2;

			vec3 a = p + vec3(randf(), randf(), randf()) * d - d2;
			vec3 b = p + vec3(randf(), randf(), randf()) * d - d2;
			vec3 c = p + vec3(randf(), randf(), randf()) * d - d2;

			vec3 position[3] = { a, b, c };

			vec3 cb = c - b;
			vec3 ab = a - b;
			vec3 normal = normalize(cross(cb, ab));

			Colour colour = to_colour(p / s + 0.5f);

			for(size_t j = 0; j < 3; ++j)
			{
				geometry.m_positions.push_back(position[j]);
				geometry.m_normals.push_back(normal);
				geometry.m_colours.push_back(colour);
			}
		}

		Model& model = app.m_gfx.create_model_geo("geometry", geometry);

		Node3& n = gfx::nodes(scene).add(Node3());
		Item& it = gfx::items(scene).add(Item(n, model, 0U, &material));
		node = &n;
		UNUSED(it);

		//raycaster = new THREE.Raycaster();

		//mouse = new THREE.Vector2();

		//var geometry = new THREE.BufferGeometry();
		//geometry.addAttribute('position', new THREE.BufferAttribute(new Float32Array(4 * 3), 3));
		//
		//var material = new THREE.LineBasicMaterial({ color: 0xffffff, transparent: true });
		//
		//line = new THREE.Line(geometry, material);
		//scene.add(line);

		auto hover = [](Item& item) {};
		auto unhover = [](Item& item) {};

		if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
		{
			//auto pick = [&](Item* item) { if(hovered) unhover(*hovered); hovered = item; if(hovered) hover(*hovered); };
			//viewer.picker(0).pick_point(viewer.m_viewport, mouse_event.m_relative, pick, ItemFlag::Selectable);
		}
	}

	const float time = app.m_gfx.m_time;

	vec3 angles = vec3(time * 0.15f, time * 0.25f, 0.f);
	node->apply(vec3(0.f), quat(angles));

	//raycaster.setFromCamera(mouse, camera);
	//
	//var intersects = raycaster.intersectObject(mesh);
	//
	//if (intersects.length > 0) {
	//
	//	var intersect = intersects[0];
	//	var face = intersect.face;
	//
	//	var linePosition = line.geometry.attributes.position;
	//	var meshPosition = mesh.geometry.attributes.position;
	//
	//	linePosition.copyAt(0, meshPosition, face.a);
	//	linePosition.copyAt(1, meshPosition, face.b);
	//	linePosition.copyAt(2, meshPosition, face.c);
	//	linePosition.copyAt(3, meshPosition, face.a);
	//
	//	mesh.updateMatrix();
	//
	//	line.geometry.applyMatrix(mesh.matrix);
	//
	//	line.visible = true;
	//
	//} else {
	//
	//	line.visible = false;
	//
	//}
}