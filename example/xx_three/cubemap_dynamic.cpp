#include <xx_three/xx_three.h>
#include <gfx-pbr/Api.h>

#include <infra/Vector.h>
#include <stl/vector.hpp>

using namespace two;

#define SPHERE 1
#define AXES 0

EX(xx_cubemap_dynamic)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	viewer.m_viewport.m_autorender = false;

	static size_t count = 0;

	static float lon = 0.f; static float lat = 0.f;
	static float phi = 0.f; static float theta = 0.f;

	static Texture& texture = *app.m_gfx.textures().file("cabin.jpg");
	//static Texture& texture = *app.m_gfx.textures().file("cube/cabin.png.cube");

	static Program& basic = app.m_gfx.programs().fetch("pbr/basic");

	static Item* isphere = nullptr;
	static Node3* cube = nullptr;
	static Node3* torus = nullptr;

	static unique<CubeCamera> cube0;
	static unique<CubeCamera> cube1;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 60.f; camera.m_near = 1.f; camera.m_far = 1000.f;
		//camera.m_fov = 120.f;

		// @todo why if this is turned off we get a black render ?
		scene.m_env.m_radiance.m_filter = false;
		scene.m_env.m_background.m_texture = &texture;
		scene.m_env.m_background.m_mode = BackgroundMode::Panorama;

		cube0 = construct<CubeCamera>(scene, 1.f, 1000.f, 256U);
		cube1 = construct<CubeCamera>(scene, 1.f, 1000.f, 256U);

		//cube0 = gfx::probes(scene).add(Probe(1.f, 1000.f, 256U));
		//cube1 = gfx::probes(scene).add(Probe(1.f, 1000.f, 256U));

		Material& material = app.m_gfx.materials().create("material", [&](Material& m) {
			m.m_program = &basic;
			m.m_pbr.m_albedo = rgb(0xffffff);
			//m.m_pbr.m_metallic = 1.f;
		});

#if SPHERE
		Node3& sphere = gfx::nodes(scene).add(Node3());
		//isphere = &gfx::items(scene).add(Item(sphere, app.m_gfx.shape(Icosaedr(20.f))));
		isphere = &gfx::items(scene).add(Item(sphere, app.m_gfx.shape(Sphere(20.f)), 0U, &material));
#endif

		cube = &gfx::nodes(scene).add(Node3());
		gfx::items(scene).add(Item(*cube, app.m_gfx.shape(Cube(10.f)), 0U, &material));
		
		torus = &gfx::nodes(scene).add(Node3());
		gfx::items(scene).add(Item(*torus, app.m_gfx.shape(TorusKnot(10.f, 5.f)), 0U, &material));
	}

	static vec2 presscoord = vec2(0.f);
	static float presslat = 0.f; static float presslon = 0.f;
	static bool pressed = false;
#if UI
	if(MouseEvent event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
	{
		presscoord = event.m_relative;
		presslon = lon;
		presslat = lat;
		pressed = true;
	}

	if(MouseEvent event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Released))
		pressed = false;

	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		if(pressed)
		{
			lon = (event.m_relative.x - presscoord.x) * 0.1f + presslon;
			lat = (event.m_relative.y - presscoord.y) * 0.1f + presslat;
		}
	}

	if(MouseEvent event = viewer.mouse_event(DeviceType::MouseMiddle, EventType::Moved))
	{
		viewer.m_camera.m_fov = clamp(viewer.m_camera.m_fov + event.m_deltaZ * 0.5f, 10.f, 75.f);
	}
#endif

	const float time = app.m_gfx.m_time;

	lon += 0.15f;

	lat = max(-85.f, min(85.f, lat));
	phi = to_radians(90.f - lat);
	theta = to_radians(lon);

	static vec3 cubea = vec3(0.f);
	static vec3 torusa = vec3(0.f);

	auto trigo3 = [](const vec3& a) { return vec3(cos(a.x), sin(a.y), sin(a.z)); };

	vec3 cubep = trigo3(vec3(time)) * 30.f;
	cubea += vec3(0.02f, 0.03f, 0.f);
	cube->apply(cubep, quat(cubea));

	vec3 torusp = trigo3(vec3(time + 10.f)) * 30.f;
	torusa += vec3(0.02f, 0.03f, 0.f);
	torus->apply(torusp, quat(torusa));

	Camera& camera = viewer.m_camera;
	camera.m_eye.x = 100.f * sin(phi) * cos(theta);
	camera.m_eye.y = 100.f * cos(phi);
	camera.m_eye.z = 100.f * sin(phi) * sin(theta);

	//camera.lookAt(scene.position);

	//static Texture& tiber = *app.m_gfx.textures().file("radiance/tiber_1_1k.hdr");
	//scene.m_env.m_radiance.m_texture = &tiber;
	scene.m_env.m_radiance.m_texture = &texture;

#if AXES
	Gnode& root = scene.begin();
	gfx::shape(root, Cylinder(X3 * 30.f, 1.f, 30.f, Axis::X), Symbol::plain(Colour::Red));
	gfx::shape(root, Cylinder(Y3 * 30.f, 1.f, 30.f, Axis::Y), Symbol::plain(Colour::Green));
	gfx::shape(root, Cylinder(Z3 * 30.f, 1.f, 30.f, Axis::Z), Symbol::plain(Colour::Blue));
#endif

	Render render = { Shading::Shaded, viewer.m_viewport, app.m_gfx.main_target(), app.m_gfx.m_render_frame };
	app.m_gfx.m_renderer.gather(render);
	app.m_gfx.m_renderer.begin(render);

	begin_pbr_render(app.m_gfx, render);

	// pingpong

	scene.m_env.m_background.m_texture = &texture;

	auto renderer = [](GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
		pass_opaque(gfx, render);
		pass_background(gfx, render);
	};

	// @todo shouldn't be necessary because faces outward, but somehow it gets rendered by the probe :(
	isphere->m_visible = false;

	if(count % 2 == 0) {
		scene.m_env.m_radiance.m_texture = &cube0->m_cubemap.m_cubemap;
		cube1->render(app.m_gfx, render, renderer);
	}
	else {
		scene.m_env.m_radiance.m_texture = &cube1->m_cubemap.m_cubemap;
		cube0->render(app.m_gfx, render, renderer);
	}

	isphere->m_visible = true;

	pass_clear(app.m_gfx, render);
	pass_opaque(app.m_gfx, render);
	pass_background(app.m_gfx, render);
	pass_solid(app.m_gfx, render);

	//app.m_gfx.m_copy->debug_show_texture(render, cube1->m_cubemap.m_cubemap, vec4(0.f));

	app.m_gfx.m_renderer.end(render);

	count++;
}
