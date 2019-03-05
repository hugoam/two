//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

void xx_refraction_balls(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controller(viewer);

	Scene& scene = viewer.m_scene;

	static Texture& refraction = *app.m_gfx.textures().file("Park3Med.jpg.cube");

	static vector<Node3*> spheres;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_fov = 60.f; camera.m_near = 1.f; camera.m_far = 100000.f;
		camera.m_eye.z = 3200.f;

		Model& sphere = app.m_gfx.shape(Sphere(100.f));

		Material& material = gfx::pbr_material(app.m_gfx, "material", rgb(0xffffff));
		material.m_pbr.m_refraction = 0.95f;
		//material.envMap.mapping = THREE.CubeRefractionMapping;

		for(size_t i = 0; i < 500; i++)
		{
			vec3 p = vec3(randf(), randf(), randf()) * 10000.f - 5000.f;
			vec3 s = vec3(randf()) * 3.f + 1.f;
			Node3& n = gfx::nodes(scene).add(Node3(p, ZeroQuat, s));
			gfx::items(scene).add(Item(n, sphere, 0U, &material));

			spheres.push_back(&n);
		}
	}

	static vec2 mouse = vec2(0.f);
	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse = (event.m_relative - viewer.m_frame.m_size / 2.f) * 10.f;
	}//

	float timer = app.m_gfx.m_time * -0.0001f;
	
	for(size_t i = 0; i < spheres.size(); i++)
	{
		vec3 p = vec3(cos(timer + float(i)), sin(timer + float(i) * 1.1f), 0.f) * 5000.f;
		spheres[i]->m_transform = bxTRS(vec3(1.f), ZeroQuat, p);
	}

	Camera& camera = viewer.m_camera;
	camera.m_eye.x += (mouse.x - camera.m_eye.x) * .05f;
	camera.m_eye.y += (-mouse.y - camera.m_eye.y) * .05f;

	//camera.lookAt(scene.position);
}