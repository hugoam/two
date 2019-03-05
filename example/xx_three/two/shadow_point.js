//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

Texture generateTexture(GfxSystem gfx)
{
	Texture texture = gfx.textures.create('half');

	uint16_t width = 2U;
	uint16_t height = 2U;

	btwo.gfx.Memory* memory = btwo.gfx.alloc(width * height * 4);

	uint32_t* data = (uint32_t*)memory->data;
	for(uint16_t x = 0; x < width; ++x)
		for(uint16_t y = 0; y < height; ++y)
		{
			if(y == 0) data[x + y * width] = 0xffffffff;
			else data[x + y * width] = 0x00000000;
		}

	load_texture_two.rgba(texture, 2U, 2U, *memory);
	return texture;
}

void xx_shadow_point(Shell app, Widget parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(app.ui.begin());
	//two.ui.orbit_controller(viewer);
	two.ui.trackball_controller(viewer);

	//scene.add(new THREE.AmbientLight(0x111122));

	static Material* cube_material = nullptr;
	static Material* sphere_material = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Program* pbr = app.gfx.programs.file('pbr/pbr');

		var c = app.gfx.materials.fetch('cube');
		c.program = pbr;
		c.base.cull_mode = two.CullMode.Front;
		c.pbr = MaterialPbr(two.rgba(0xa0adafff));
		c.pbr.normal = -1.0;
		//	shininess: 10,
		//	specular: 0x111111,
		cube_material = c;

		var s = app.gfx.materials.fetch('sphere');
		s.program = pbr;
		s.base.cull_mode = two.CullMode.None;
		s.base.uv0_scale = { 1.0, 3.5 };
		s.alpha.alpha_test = true;
		s.alpha.alpha = generateTexture(app.gfx);
		s.pbr.normal = -1.0; // @todo @bug @hack check why gl_FrontFacing in shader inverts normals
		sphere_material = s;

		viewer.scene.env.radiance.ambient = 0.2;
	}

	function light_source = [](Gnode parent, Colour color, var pos, quat rot) -> Gnode
	{
		var intensity = 1.5;
		var range = 20.0;

		Gnode node = two.gfx.node(parent, {}, pos, rot);

		var inner = two.gfx.shape(node, new two.Sphere(0.3), Symbol::plain(color * intensity));
		var outer = two.gfx.shape(node, new two.Sphere(2.0), Symbol::plain(Colour::White), 0, sphere_material);
		
		Light light = two.gfx.light(node, LightType::Point, true, color, range, 0.6);// intensity);
		light.range = range;
		light.energy = intensity;
		light.shadow_bias = 0.005;

		return node;
	};

	function light_pos = [](var time) -> vec3
	{
		return new two.vec3(Math.sin(time * 0.6) * 9, Math.sin(time * 0.7) * 9 + 5, Math.sin(time * 0.8) * 9);
	};

	function light_rot = [](var time) -> quat
	{
		return new two.quat(new two.vec3(time, 0.0, time));
	};

	Gnode scene = viewer.scene.begin();

	two.gfx.radiance(scene, 'radiance/tiber_1_1k.hdr', BackgroundMode::Radiance);

	static bool moving = true;
	static var time = 0.0;
	if(moving)
		time = app.gfx.time;

	var pos0 = light_pos(time); // new two.vec3(0.0, 10.0, 0.0);
	quat rot0 = light_rot(time); // new two.quat(new two.vec3(0.0, Math.PI / 2.0 + Math.PI / 4.0, Math.PI / 2.0 + Math.PI / 4.0));
	Gnode light0 = light_source(scene, two.rgba(0x0088ff), pos0, rot0);

	two.gfx.shape(scene, Cylinder(X3, 0.1, 1.0, Axis::X), Symbol::plain(Colour::Red));
	two.gfx.shape(scene, Cylinder(Y3, 0.1, 1.0, Axis::Y), Symbol::plain(Colour::Green));
	two.gfx.shape(scene, Cylinder(Z3, 0.1, 1.0, Axis::Z), Symbol::plain(Colour::Blue));

	var pos1 = light_pos(time + Math.PI);
	quat rot1 = light_rot(time + Math.PI);
	Gnode light1 = light_source(scene, two.rgba(0xff8888), pos1, rot1);

	Box box = new two.Cube(new two.vec3(15.0));
	Gnode node = two.gfx.node(scene, {});// , Y3 * 10.0);
	two.gfx.shape(node, box, Symbol::plain(Colour::White), 0, cube_material);
}
