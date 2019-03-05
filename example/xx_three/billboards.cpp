//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

#include <cstring>

#define INSTANCING 1

void xx_billboards(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Camera& camera = viewer.m_camera;
	camera.m_near = 2.f; camera.m_far = 2000.f;
	camera.m_eye.z = 1000.f;

	Scene& scene = viewer.m_scene;
	//scene.fog = new THREE.FogExp2(0x000000, 0.001);

	static Program& program = app.m_gfx.programs().fetch("point");

	static Texture& sprite = *app.m_gfx.textures().file("sprites/disc.png");

	//Material& material = new THREE.PointsMaterial({ size: 35, sizeAttenuation : false, map : sprite, alphaTest : 0.5, transparent : true });
	static Material& material = app.m_gfx.materials().create("points", [&](Material& m) {
		m.m_program = &program;
#if INSTANCING
		m.m_base.m_geometry_filter = uint32_t(1 << uint(PrimitiveType::Triangles));
#else
		m.m_base.m_geometry_filter = uint32_t(1 << uint(PrimitiveType::Points));
#endif
		m.m_solid.m_colour = hsl(1.f, 0.3f, 0.7f);
		m.m_solid.m_colour = &sprite;
	});

	constexpr size_t num = 10000;
	//constexpr size_t num = 1;

#if INSTANCING
	static Batch* batch = nullptr;
	struct Instance { vec4 d0; vec4 d1; };
	static vector<Instance> instances = vector<Instance>(num);
#endif

	static bool once = false;
	if(!once)
	{
		once = true;

#if INSTANCING
		Model& model = *app.m_gfx.models().get("point");
#else
		MeshPacker geometry;
		geometry.m_primitive = PrimitiveType::Points;
#endif

		for(size_t i = 0; i < num; i++)
		{
			vec3 pos = vec3(randf(), randf(), randf()) * 2000.f - 1000.f;
#if INSTANCING
			vec2 scale = vec2(1.f);
			instances[i] = { vec4(pos, 0.f), vec4(scale, vec2(0.f)) };
#else
			geometry.m_positions.push_back(pos);
			geometry.m_indices.push_back(i);
#endif
		}

#if !INSTANCING
		Model& model = app.m_gfx.create_model("points", geometry);
#endif

		Node3& n = gfx::nodes(scene).add(Node3());
		Item& it = gfx::items(scene).add(Item(n, model, 0U, &material));

#if INSTANCING
		batch = &gfx::batches(scene).add(Batch(it));
		it.m_batch = batch;
#endif
	}

	//ui::slider_field(viewer, "sizeAttenuation", { material.sizeAttenuation, { 0.f, 1000.f, 1.f } })

	float time = app.m_gfx.m_time;

	static vec2 mouse = vec2(0.f);
	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse = (event.m_relative - viewer.m_frame.m_size / 2.f);
	}

	viewer.m_camera.m_eye.x += (mouse.x - viewer.m_camera.m_eye.x) * 0.05f;
	viewer.m_camera.m_eye.y += (-mouse.y - viewer.m_camera.m_eye.y) * 0.05f;

	//viewer.m_camera.m_target = scene.position;

	float h = fmod(360.f * (1.f + time), 360.f) / 360.f;
	material.m_solid.m_colour = hsl(h, 0.5f, 0.5f);

#if INSTANCING
	span<float> memory = batch->begin(instances.size(), sizeof(Instance));
	memcpy(memory.data(), instances.data(), memory.size() * sizeof(float));
#endif
}