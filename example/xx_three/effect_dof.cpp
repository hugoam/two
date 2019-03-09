//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

void xx_effect_dof(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	//camera = new THREE.PerspectiveCamera(70, width / height, 1, 3000);
	//camera.position.z = 200;

	Gnode& scene = viewer.m_scene.begin();

	static int xgrid = 14;
	static int ygrid = 9;
	static int zgrid = 14;
	static bool single_material = false;

	static vec2 mouse;
	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse.x = event.m_relative.x - viewer.m_frame.m_size.x / 2.f;
		mouse.y = event.m_relative.y - viewer.m_frame.m_size.y / 2.f;
	}

	if(MouseEvent event = viewer.mouse_event(DeviceType::Touch, EventType::Pressed))
		//or(MouseEvent event = viewer.mouse_event(DeviceType::Touch, EventType::Moved))
	{
		//if(event.touches.length == 1) {
		//	event.preventDefault();
		//	mouseX = event.touches[0].pageX - windowHalfX;
		//	mouseY = event.touches[0].pageY - windowHalfY;
		//}
	}

	int nobjects = xgrid * ygrid * zgrid;

	static Model& geo = app.m_gfx.shape(Sphere(1.f));

	static Program& pbr = *app.m_gfx.programs().file("pbr/pbr");

	static vector<Material*> materials;

	Texture& texcube = *app.m_gfx.textures().file("SwedishRoyalCastle.cube");

	for(int i = 0; i < nobjects; ++i)
	{
		const string name = "object" + to_string(i);
		Material& material = app.m_gfx.materials().create(name, [&](Material& m) {
			m.m_program = &pbr;
			m.m_base.m_cull_mode = CullMode::None;
			m.m_pbr.m_albedo = rgb(0xff1100);
		});
		materials.push_back(&material);
	}

	int count = 0;
	for(int i = 0; i < xgrid; i++)
		for(int j = 0; j < ygrid; j++)
			for(int k = 0; k < zgrid; k++)
			{
				int x = 200 * (i - xgrid / 2);
				int y = 200 * (j - ygrid / 2);
				int z = 200 * (k - zgrid / 2);
				Gnode& n = gfx::node(scene, {}, vec3(ivec3(x, y, z)), ZeroQuat, vec3(60.f));
				gfx::item(n, geo, 0U, single_material ? materials[0] : materials[count]);
				count++;
			}

	struct Parameters { float focus = 500.f; float aperture = 5.f; float maxblur = 1.f; };
	Parameters params;

	Widget& controls = ui::stack(viewer);
	ui::slider_field<float>(controls, "focus",    { params.focus,    { 10.f, 3000.f, 10.f } });
	ui::slider_field<float>(controls, "aperture", { params.aperture, { 0.f, 10.f, 0.1f } });
	ui::slider_field<float>(controls, "maxblur",  { params.maxblur,  { 0.f, 3.f, 0.025f } });

	auto update = []()
	{
		//bokeh.uniforms["focus"].value = params.focus;
		//bokeh.uniforms["aperture"].value = params.aperture * 0.00001;
		//bokeh.uniforms["maxblur"].value = params.maxblur;
	};

	//var postprocessing = {};

	const float time = app.m_gfx.m_time;

	Camera& camera = viewer.m_camera;
	camera.m_eye.x += (mouse.x - camera.m_eye.x) * 0.036f;
	camera.m_eye.y += (-(mouse.y)-camera.m_eye.y) * 0.036f;
	//camera.m_target = scene.position;

	if(!single_material)
		for(int i = 0; i < nobjects; i++)
		{
			float h = fmod(360.f * (float(i) / float(nobjects) + time), 360.f) / 360.f;
			materials[i]->m_solid.m_colour = hsl(h, 1.f, 0.5f);
		}
	
	//postprocessing.composer.render(0.1);

	auto render = [](GfxSystem& gfx, Render& render)
	{
		pass_clear(gfx, render);
		pass_opaque(gfx, render);
		//pass_bokeh(gfx, render);
		pass_effects(gfx, render);
		pass_post_process(gfx, render);
	};

	app.m_gfx.set_renderer(Shading::Shaded, render);
}
