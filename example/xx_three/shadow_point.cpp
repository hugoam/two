//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

Texture& generateTexture(GfxSystem& gfx_system)
{
	Texture& texture = gfx_system.textures().create("half");

	uint16_t width = 2U;
	uint16_t height = 2U;

	const bgfx::Memory* memory = bgfx::alloc(width * height * 4);

	uint32_t* data = (uint32_t*)memory->data;
	for(uint16_t x = 0; x < width; ++x)
		for(uint16_t y = 0; y < height; ++y)
		{
			if(y == 0) data[x + y * width] = 0xffffffff;
			else data[x + y * width] = 0x00000000;
		}

	load_texture_rgba(texture, 2U, 2U, *memory);
	return texture;
}

void xx_shadow_point(Shell& app, Widget& parent, Dockbar& dockbar)
{
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	//scene.add( new THREE.AmbientLight( 0x111122 ) );

	static Material* cube_material = nullptr;
	static Material* sphere_material = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Program* pbr = app.m_gfx_system.programs().file("pbr/pbr");

		Material& c = app.m_gfx_system.materials().fetch("cube");
		c.m_program = pbr;
		c.m_base.m_cull_mode = CullMode::Front;
		c.m_pbr = MaterialPbr(from_rgba(0xa0adafff));
		c.m_pbr.m_normal = -1.f;
		//	shininess: 10,
		//	specular: 0x111111,
		cube_material = &c;

		Material& s = app.m_gfx_system.materials().fetch("sphere");
		s.m_program = pbr;
		s.m_base.m_cull_mode = CullMode::None;
		s.m_base.m_uv0_scale = { 1.f, 3.5f };
		s.m_alpha.m_alpha_test = true;
		s.m_alpha.m_alpha.m_texture = &generateTexture(app.m_gfx_system);
		s.m_pbr.m_normal = -1.f; // @todo @bug @hack check why gl_FrontFacing in shader inverts normals
		sphere_material = &s;

		viewer.m_scene.m_env.m_radiance.m_ambient = 0.2f;
	}

	auto light_source = [&](Gnode& parent, Colour color, vec3 pos, quat rot) -> Gnode&
	{
		float intensity = 1.5f;
		float range = 20.f;

		Gnode& node = gfx::node(parent, {}, pos, rot);

		Item& inner = gfx::shape(node, Sphere(0.3f), Symbol::plain(color * intensity));
		Item& outer = gfx::shape(node, Sphere(2.0f), Symbol::plain(Colour::White), 0U, sphere_material);
		
		Light& light = gfx::light(node, LightType::Point, true, color, range, 0.6f);// intensity);
		light.m_range = range;
		light.m_energy = intensity;
		light.m_shadow_bias = 0.005f;

		return node;
	};

	auto light_pos = [](float time) -> vec3
	{
		return vec3(sin(time * 0.6) * 9, sin(time * 0.7) * 9 + 5, sin(time * 0.8) * 9);
	};

	auto light_rot = [](float time) -> quat
	{
		return quat(vec3(time, 0.f, time));
	};

	Gnode& scene = viewer.m_scene.begin();

	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);

	static bool moving = true;
	static double time = 0.0;
	if(moving)
		time = app.m_gfx_system.m_time;

	vec3 pos0 = light_pos(time); // vec3(0.f, 10.f, 0.f);
	quat rot0 = light_rot(time); // quat(vec3(0.f, c_pi / 2.f + c_pi / 4.f, c_pi / 2.f + c_pi / 4.f));
	Gnode& light0 = light_source(scene, from_rgba(0x0088ffff), pos0, rot0);

	gfx::shape(scene, Cylinder(X3, 0.1f, 1.f, Axis::X), Symbol::plain(Colour::Red));
	gfx::shape(scene, Cylinder(Y3, 0.1f, 1.f, Axis::Y), Symbol::plain(Colour::Green));
	gfx::shape(scene, Cylinder(Z3, 0.1f, 1.f, Axis::Z), Symbol::plain(Colour::Blue));

	vec3 pos1 = light_pos(time + c_pi);
	quat rot1 = light_rot(time + c_pi);
	Gnode& light1 = light_source(scene, from_rgba(0xff8888ff), pos1, rot1);

	Box box = Cube(vec3(15.f));
	Gnode& node = gfx::node(scene, {});// , Y3 * 10.f);
	//gfx::shape(node, box, Symbol::plain(Colour::White), 0U, cube_material); // @todo fix that shadow pass bug
	gfx::shape(node, box, Symbol::plain(Colour::White), ItemFlag::Render | ItemFlag::LodAll, cube_material);
	//mesh.receiveShadow = true;
}
