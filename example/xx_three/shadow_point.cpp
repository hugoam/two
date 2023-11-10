#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
#include <bgfx/bgfx.h>
module two.xxthree;
#else
#include <xx_three/xx_three.h>
#include <gfx-pbr/Api.h>
#endif

using namespace two;

#define IMMEDIATE 0

Texture& generateTexture(GfxSystem& gfx)
{
	Texture& texture = gfx.textures().create("half");

	const uvec2 size = uvec2(2U);
	const bgfx::Memory* memory = bgfx::alloc(size.x * size.y * 4);

	uint32_t* data = (uint32_t*)memory->data;
	for(uint16_t x = 0; x < size.x; ++x)
		for(uint16_t y = 0; y < size.y; ++y)
		{
			if(y == 0) data[x + y * size.x] = 0xffffffff;
			else data[x + y * size.x] = 0x00000000;
		}

	texture.load_rgba(uvec2(2U), *memory);
	return texture;
}

EX(xx_shadow_point)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	constexpr uint32_t colors[] = { 0x0088ff, 0xff8888 };
	constexpr float intensity = 1.5f;
	constexpr float range = 20.0f;

#if UI
	TrackballController& control = ui::trackball_controller(viewer);
#endif

	static Material* cubemat = nullptr;
	static Material* spheremat = nullptr;

#if !IMMEDIATE
	static Node3* lights[2] = { nullptr, nullptr };
#endif

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 45.f; camera.m_near = 1.f; camera.m_far = 1000.f;
		camera.m_eye = vec3(0.f, 10.f, 40.f);

#if UI
		control.m_target = vec3(0.f, 10.f, 0.f);
#endif

		Zone& env = scene.m_env;
		env.m_radiance.m_ambient = rgb(0x111122);

		Program& phong = *app.m_gfx.programs().file("pbr/phong");

		Material& c = app.m_gfx.materials().fetch("cube");
		//c.m_program = &pbr;
		c.m_program = &phong;
		c.m_base.m_cull_mode = CullMode::Front;
		c.m_lit.m_normal = -1.f;
		c.m_phong.m_diffuse = rgb(0xa0adaf);
		c.m_phong.m_specular = rgb(0x111111);
		c.m_phong.m_shininess = 10.f;
		cubemat = &c;

		Material& s = app.m_gfx.materials().fetch("sphere");
		//s.m_program = &pbr;
		s.m_program = &phong;
		s.m_base.m_cull_mode = CullMode::None;
		s.m_base.m_uv0_scale = { 1.f, 3.5f };
		s.m_alpha.m_alpha_test = true;
		s.m_alpha.m_alpha = &generateTexture(app.m_gfx);
		s.m_lit.m_normal = -1.f; // @todo @bug @hack check why gl_FrontFacing in shader inverts normals
		spheremat = &s;

#if !IMMEDIATE
		for(size_t i = 0; i < 2; ++i) {

			Colour color = rgb(colors[i]);

			Model& sphere0 = app.m_gfx.shape(Sphere(0.3f));
			Model& sphere1 = app.m_gfx.shape(Sphere(2.0f));

			Node3& node = gfx::nodes(scene).add(Node3());
			Item& inner = gfx::items(scene).add(Item(node, sphere0, 0, &app.m_gfx.symbol_material(Symbol(color * intensity))));
			Item& outer = gfx::items(scene).add(Item(node, sphere1, 0, spheremat));
			UNUSED(inner); UNUSED(outer);

			Light& light = gfx::lights(scene).add(Light(node, LightType::Point, true, color, intensity, range)); //, 0.6));// intensity);
			//light.m_attenuation = 0.6f;
			//light.shadow_bias = 0.005;

			lights[i] = &node;
		}

		Node3& node = gfx::nodes(scene).add(Node3(vec3(0.f, 10.f, 0.f)));
		gfx::items(scene).add(Item(node, app.m_gfx.shape(Cube(vec3(15.f))), 0, cubemat));
#endif
	}

#if IMMEDIATE
	auto light_source = [&](Gnode& parent, Colour color, vec3 pos, quat rot) -> Gnode&
	{
		float intensity = 1.5f;
		float range = 20.f;

		Gnode& node = gfx::node(parent, pos, rot);

		Item& inner = gfx::shape(node, Sphere(0.3f), Symbol::plain(color * intensity));
		Item& outer = gfx::shape(node, Sphere(2.0f), Symbol::plain(Colour::White), 0U, spheremat);
		
		Light& light = gfx::light(node, LightType::Point, true, color, range, 0.6f);// intensity);
		light.m_range = range;
		light.m_energy = intensity;
		light.m_shadow_bias = 0.005f;

		return node;
	};
#endif

	auto pos = [](float time) -> vec3
	{
		return vec3(sin(time * 0.6f) * 9, sin(time * 0.7f) * 9.f + 5.f, sin(time * 0.8f) * 9.f);
	};

	auto rot = [](float time) -> quat
	{
		return quat(vec3(time, 0.f, time));
	};
	
	static bool moving = true;
	static float time = 0.f;
	if(moving)
		time = app.m_gfx.m_time;

	// vec3 pos = vec3(0.f, 10.f, 0.f);
	// quat rot = quat(vec3(0.f, c_pi2 + c_pi4, c_pi2 + c_pi4));

#if IMMEDIATE
	Gnode& light0 = light_source(scene, rgb(0x0088ff), pos(time), rot(time));
	Gnode& light1 = light_source(scene, rgb(0xff8888), pos(time + c_pi), rot(time + c_pi));
#else
	lights[0]->apply(pos(time), rot(time));
	lights[1]->apply(pos(time + 10000.f), rot(time + 10000.f));
#endif

#if IMMEDIATE
	Box box = Cube(vec3(15.f));
	Gnode& node = gfx::node(scene);// , y3 * 10.f);
	gfx::shape(node, box, Symbol::plain(Colour::White), 0U, cubemat);

	gfx::shape(scene, Cylinder(x3, 0.1f, 1.f, Axis::X), Symbol::plain(Colour::Red));
	gfx::shape(scene, Cylinder(y3, 0.1f, 1.f, Axis::Y), Symbol::plain(Colour::Green));
	gfx::shape(scene, Cylinder(z3, 0.1f, 1.f, Axis::Z), Symbol::plain(Colour::Blue));
#endif

}
