//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <refl/Api.h>
#include <uio/Api.h>
#include <meta/gfx.meta.h>

#include <03_materials/03_materials.h>

using namespace mud;

Material& phong_white(GfxSystem& gfx, const string& name)
{
	Material& mat = gfx.fetch_material(name.c_str(), "pbr/phong");
	mat.m_phong.m_diffuse.m_value = Colour::White;
	mat.m_phong.m_shininess.m_value = 100.f;
	return mat;
}

Material& milky_white(GfxSystem& gfx, const string& name)
{
	Material& mat = gfx.fetch_material(name.c_str(), "pbr/pbr");
	mat.m_pbr.m_albedo.m_value = Colour::White;
	mat.m_pbr.m_metallic.m_value = 0.4f;
	mat.m_pbr.m_roughness.m_value = 0.35f;
	return mat;
}

Material& mirror(GfxSystem& gfx)
{
	Material& mat = gfx.fetch_material("mirror", "pbr/pbr");
	MaterialPbr& pbr = mat.m_pbr;
	pbr.m_albedo.m_value = Colour::White;
	pbr.m_metallic.m_value = 1.f;
	pbr.m_roughness.m_value = 0.02f;
	return mat;
}

Material& material(GfxSystem& gfx, const string& name)
{
	Material& mat = gfx.fetch_material(name.c_str(), "pbr/pbr");

	mat.m_pbr.m_albedo = gfx.textures().file(name + "/" + name + "_col.jpg");
	mat.m_lit.m_normal = gfx.textures().file(name + "/" + name + "_nrm.jpg");
	mat.m_pbr.m_roughness = gfx.textures().file(name + "/" + name + "_rgh.jpg");

	if(Texture* ao = gfx.textures().file(name + "/" + name + "_AO.jpg"))
		mat.m_lit.m_occlusion = ao;
	if(Texture* depth = gfx.textures().file(name + "/" + name + "_disp.jpg"))
		mat.m_pbr.m_depth = depth;
	if(Texture* met = gfx.textures().file(name + "/" + name + "_met.jpg"))
	{
		mat.m_pbr.m_metallic = met;
		mat.m_pbr.m_metallic.m_value = 1.f;
	}

	return mat;
}

Material& fabric_08(GfxSystem& gfx)
{
	Material& mat = material(gfx, "Fabric08");
	mat.m_pbr.m_deep_parallax = true;
	mat.m_pbr.m_depth.m_value = -0.05f;
	return mat;
}

Material& paving_stones_08(GfxSystem& gfx)
{
	Material& mat = material(gfx, "PavingStones08");
	mat.m_pbr.m_deep_parallax = true;
	mat.m_pbr.m_depth.m_value = -0.04f;
	return mat;
}

Material& metal_plates_02(GfxSystem& gfx)
{
	Material& mat = material(gfx, "MetalPlates02");
	//mat.m_pbr.m_deep_parallax = true;
	//mat.m_pbr.m_depth.m_value = -0.04f;
	return mat;
}

Material& paving_stones_11(GfxSystem& gfx)
{
	Material& mat = material(gfx, "PavingStones11");
	mat.m_pbr.m_deep_parallax = true;
	mat.m_pbr.m_depth.m_value = -0.04f;
	return mat;
}

Material& rocks_01(GfxSystem& gfx)
{
	Material& mat = material(gfx, "Rocks01");
	mat.m_pbr.m_deep_parallax = true;
	mat.m_pbr.m_depth.m_value = -0.08f;
	return mat;
}

Material& wood_floor_05(GfxSystem& gfx)
{
	Material& mat = material(gfx, "WoodFloor05");
	return mat;
}

Material& roughness_material(GfxSystem& gfx, const string& name, Colour albedo, float metallic, float roughness)
{
	Material& mat = gfx.fetch_material(name.c_str(), "pbr/pbr");
	MaterialPbr& pbr = mat.m_pbr;
	pbr.m_albedo.m_value = albedo;
	pbr.m_metallic.m_value = metallic;
	pbr.m_roughness.m_value = roughness;
	return mat;
}

vector<Material*> create_roughness_dielectric_materials(GfxSystem& gfx)
{
	vector<Material*> materials;
	for(size_t i = 0; i < 8; ++i)
	{
		float roughness = i / float(8 - 1);
		materials.push_back(&roughness_material(gfx, "roughness_dieletric_" + to_string(roughness), Colour::Black, 0.f, roughness));
	}
	return materials;
}

vector<Material*> create_roughness_metallic_materials(GfxSystem& gfx)
{
	vector<Material*> materials;
	for(size_t i = 0; i < 8; ++i)
	{
		float roughness = i / float(8 - 1);
		materials.push_back(&roughness_material(gfx, "roughness_metallic_" + to_string(roughness), Colour::White, 1.f, roughness));
	}
	return materials;
}

void material_spheres(Gnode& parent, span<Material*> materials)
{
	float spacing = 2.f;
	float center = (materials.size() - 1) * spacing / 2.f;

	for(size_t i = 0; i < materials.size(); ++i)
	{
		Gnode& material_node = gfx::node(parent, Ref(materials[i]), vec3(-center + float(i) * spacing, 0.f, 0.f));
		gfx::shape(material_node, Sphere(), Symbol(), 0, materials[i]);
		//gfx::model(material_node, "sphere", 0, materials[i]);
	}
}

void roughness_spheres(Gnode& parent)
{
	GfxSystem& gfx = parent.m_scene->m_gfx;

	static vector<Material*> dielectric = create_roughness_dielectric_materials(gfx);
	static vector<Material*> metallic = create_roughness_metallic_materials(gfx);

	float di_center = dielectric.size() * 2.f / 2.f;
	for(size_t i = 0; i < dielectric.size(); ++i)
	{
		Gnode& material_node = gfx::node(parent, {}, vec3(-di_center + float(i) * 2.f, 0.f, 0.f));
		gfx::shape(material_node, Sphere(), Symbol(), 0U, dielectric[i]);
	}

	float met_center = metallic.size() * 2.f / 2.f;
	for(size_t i = 0; i < metallic.size(); ++i)
	{
		Gnode& material_node = gfx::node(parent, {}, vec3(-met_center + float(i) * 2.f, 0.f, 4.f));
		gfx::shape(material_node, Sphere(), Symbol(), 0U, metallic[i]);
	}
}

void ex_03_materials(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	OrbitController& controller = ui::orbit_controller(viewer);
	UNUSED(controller);

	viewer.m_viewport.m_to_gamma = true;

	Gnode& scene = viewer.m_scene.begin();

	Gnode& ground_node = gfx::node(scene, {}, -Y3);
	gfx::shape(ground_node, Rect(vec2(-50.f), vec2(100.f)), Symbol(), 0U, &milky_white(app.m_gfx));

	gfx::direct_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);

	GfxSystem& gfx = scene.m_scene->m_gfx;
	
	//static vector<Material*> materials = { &milky_white(gfx), &mirror(gfx), &rocks_01(gfx), &fabric_08(gfx), &paving_stones_11(gfx), 
	//											&wood_floor_05(gfx), &paving_stones_08(gfx) };
	static vector<Material*> materials = { &paving_stones_11(gfx), &metal_plates_02(gfx), &paving_stones_08(gfx) };

	static Material* edited = materials[0];

	//roughness_spheres(scene);
	material_spheres(scene, materials);

	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
	{
		auto callback = [&](Item* item)
		{
			if(!item->m_node->m_object) return;
			edited = &val<Material>(item->m_node->m_object);
			float center = float(materials.size()) * 4.f / 2.f;
			size_t index = edited->m_index - materials[0]->m_index;
			controller.m_position = { -center + index * 4.f, 0.f, 0.f };
		};
		viewer.picker(0).pick_point(viewer.m_viewport, mouse_event.m_relative, callback, ItemFlag::Default | ItemFlag::Selectable);
	}

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Widget& sheet = ui::columns(*dock, { 0.3f, 0.7f });

		ui::label(sheet, "Zone :");
		ui::color_field(sheet, "Ambient", viewer.m_scene.m_env.m_radiance.m_ambient);

		if(edited)
			object_edit(*dock, Ref(edited)); // "Particle Editor" // identity = edited
	}
}

#ifdef _03_MATERIALS_EXE
void pump(Shell& app, ShellWindow& window)
{
	shell_context(window.m_ui->begin(), app.m_editor);
	ex_03_materials(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	System::instance().load_modules({ &mud_gfx::m() });
	app.m_gfx.add_resource_path("examples/03_materials");
	app.m_gfx.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif