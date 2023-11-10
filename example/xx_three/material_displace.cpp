#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;
#else
#include <xx_three/xx_three.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>
#endif

using namespace two;

EX(xx_material_displace)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	static ImporterOBJ obj_importer(app.m_gfx);

#if UI
	ui::orbit_controls(viewer);
	//controls.enableZoom = false;
	//controls.enableDamping = true;
#endif

	constexpr int height = 500; // of camera frustum

	static float r = 0.0;

	static Material* material = nullptr;
	static Node3* light = nullptr;

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 40.f; camera.m_near = 1.f; camera.m_far = 10000.f;
		camera.m_eye.z = 1500.f;

		viewer.m_viewport.m_to_gamma = true;

		//var aspect = window.innerWidth / window.innerHeight;
		//camera = new THREE.OrthographicCamera(-height * aspect, height * aspect, height, -height, 1, 10000);
		//camera.position.z = 1500;
		//scene.add(camera);

		Texture& reflection = *app.m_gfx.textures().file("cube/royal.jpg.cube");

		Zone& env = scene.m_env;
		env.m_radiance.m_texture = &reflection;
		env.m_radiance.m_ambient = rgb(0xffffff) * 0.2f;
		env.m_radiance.m_colour = rgb(0xffffff);

		// lights

		Node3& ln0 = gfx::nodes(scene).add(Node3(vec3(0.f, 0.f, 2500.f)));
		gfx::lights(scene).add(Light(ln0, LightType::Point, false, rgb(0xff0000), 0.5f, 0.f));
		light = &ln0;

		Node3& ln1 = gfx::nodes(scene).add(Node3(vec3(0.f)));
		gfx::lights(scene).add(Light(ln1, LightType::Point, false, rgb(0xff6666), 1.f, 0.f));

		Node3& ln2 = gfx::nodes(scene).add(Node3(vec3(-1000.f, 0.f, 1000.f)));
		gfx::lights(scene).add(Light(ln2, LightType::Point, false, rgb(0x0000ff), 1.f, 0.f));

		Program& three = *app.m_gfx.programs().file("pbr/three");

		Material& mat = app.m_gfx.materials().create("ninja",  [&](Material& m) {
			m.m_program = &three;
			m.m_base.m_cull_mode = CullMode::None;
			m.m_pbr.m_albedo = rgb(0x888888);
			m.m_pbr.m_metallic = 1.f;
			m.m_pbr.m_roughness = 0.4f;
			m.m_lit.m_normal = app.m_gfx.textures().file("ninja/normal.jpg");
			m.m_lit.m_occlusion = app.m_gfx.textures().file("ninja/ao.jpg");
			m.m_lit.m_displace = app.m_gfx.textures().file("ninja/displacement.jpg");
			m.m_lit.m_displace = 2.436143; // from original model
			m.m_lit.m_displace_bias = -0.428408f;
			// normalScale: vec2(1, -1), // why does the normal map require negation in this case?
		});

		// float envMapIntensity = 1.0;

		material = &mat;

		Model& model = *app.m_gfx.models().file("ninjaHead_Low"); // .obj");
		//geometry.attributes.uv2 = geometry.attributes.uv;
		//geometry.center();

		Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f, -175.f, 0.f) * 25.f, ZeroQuat, vec3(25.f)));
		gfx::items(scene).add(Item(n, model, 0U, &mat));
	}

#if UI
	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Widget& sheet = ui::sheet(*dock);

		auto panel = [&](const string& name) -> Widget&
		{
			Widget& s = ui::expandbox(sheet, name.c_str());
			return ui::columns(s, { 0.3f, 0.7f });
		};

		Widget& a = panel("Material");

		ui::slider_field(a, "metalness",    material->m_pbr.m_metallic.m_value,  { 0.f, 1.f, 0.01f });
		ui::slider_field(a, "roughness",    material->m_pbr.m_roughness.m_value, { 0.f, 1.f, 0.01f });
		ui::slider_field(a, "occlusion",    material->m_lit.m_occlusion.m_value, { 0.f, 1.f, 0.01f });
		ui::slider_field(a, "displacement", material->m_lit.m_displace.m_value,  { 0.f, 5.f, 0.01f });
		ui::slider_field(a, "normal scale", material->m_lit.m_normal.m_value,    { -1.f, 1.f, 0.01f });

		ui::color_field(a, "ambient", scene.m_env.m_radiance.m_ambient);

		// envMapIntensity
	}
#endif

	light->apply(vec3(2500.f * cos(r), 2500.f * sin(r), 0.f));

	r += 0.01;
}
