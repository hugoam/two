#include <mud/frame.h>
#include <gfx-pbr/Api.h>
#include <refl/Api.h>
#include <uio/Api.h>
#include <meta/gfx/Module.h>

#include <03_materials/03_materials.h>

using namespace mud;

Material& milky_white(GfxSystem& gfx_system, const string& name)
{
	Material& mat = gfx_system.fetch_material(name.c_str(), "pbr/pbr");
	PbrMaterialBlock& pbr = mat.m_pbr_block;
	pbr.m_enabled = true;
	pbr.m_albedo.m_value = Colour::White;
	pbr.m_metallic.m_value = 0.4f;
	pbr.m_roughness.m_value = 0.35f;
	//mat.m_pbr_block.m_roughness.m_value = 0.8f;
	return mat;
}

Material& mirror(GfxSystem& gfx_system)
{
	Material& mat = gfx_system.fetch_material("mirror", "pbr/pbr");
	PbrMaterialBlock& pbr = mat.m_pbr_block;
	pbr.m_enabled = true;
	pbr.m_albedo.m_value = Colour::White;
	pbr.m_metallic.m_value = 1.f;
	pbr.m_roughness.m_value = 0.02f;
	return mat;
}

Material& material(GfxSystem& gfx_system, const string& name)
{
	Material& mat = gfx_system.fetch_material(name.c_str(), "pbr/pbr");
	PbrMaterialBlock& pbr = mat.m_pbr_block;

	pbr.m_enabled = true;
	pbr.m_albedo.m_texture = gfx_system.textures().file(name + "/" + name + "_col.jpg");
	pbr.m_normal.m_texture = gfx_system.textures().file(name + "/" + name + "_nrm.jpg");
	pbr.m_roughness.m_texture = gfx_system.textures().file(name + "/" + name + "_rgh.jpg");

	if(Texture* ao = gfx_system.textures().file(name + "/" + name + "_AO.jpg"))
		pbr.m_ambient_occlusion.m_texture = ao;
	if(Texture* depth = gfx_system.textures().file(name + "/" + name + "_disp.jpg"))
		pbr.m_depth.m_texture = depth;
	if(Texture* met = gfx_system.textures().file(name + "/" + name + "_met.jpg"))
	{
		pbr.m_metallic.m_texture = met;
		pbr.m_metallic.m_value = 1.f;
	}

	return mat;
}

Material& fabric_08(GfxSystem& gfx_system)
{
	Material& mat = material(gfx_system, "Fabric08");
	mat.m_pbr_block.m_deep_parallax = true;
	mat.m_pbr_block.m_depth.m_value = -0.05f;
	return mat;
}

Material& paving_stones_08(GfxSystem& gfx_system)
{
	Material& mat = material(gfx_system, "PavingStones08");
	mat.m_pbr_block.m_deep_parallax = true;
	mat.m_pbr_block.m_depth.m_value = -0.04f;
	return mat;
}

Material& metal_plates_02(GfxSystem& gfx_system)
{
	Material& mat = material(gfx_system, "MetalPlates02");
	//mat.m_pbr_block.m_deep_parallax = true;
	//mat.m_pbr_block.m_depth.m_value = -0.04f;
	return mat;
}

Material& paving_stones_11(GfxSystem& gfx_system)
{
	Material& mat = material(gfx_system, "PavingStones11");
	mat.m_pbr_block.m_deep_parallax = true;
	mat.m_pbr_block.m_depth.m_value = -0.04f;
	return mat;
}

Material& rocks_01(GfxSystem& gfx_system)
{
	Material& mat = material(gfx_system, "Rocks01");
	mat.m_pbr_block.m_deep_parallax = true;
	mat.m_pbr_block.m_depth.m_value = -0.08f;
	return mat;
}

Material& wood_floor_05(GfxSystem& gfx_system)
{
	Material& mat = material(gfx_system, "WoodFloor05");
	return mat;
}

Material& roughness_material(GfxSystem& gfx_system, const string& name, Colour albedo, float metallic, float roughness)
{
	Material& mat = gfx_system.fetch_material(name.c_str(), "pbr/pbr");
	PbrMaterialBlock& pbr = mat.m_pbr_block;
	pbr.m_enabled = true;
	pbr.m_albedo.m_value = albedo;
	pbr.m_metallic.m_value = metallic;
	pbr.m_roughness.m_value = roughness;
	return mat;
}

vector<Material*> create_roughness_dielectric_materials(GfxSystem& gfx_system)
{
	vector<Material*> materials;
	for(size_t i = 0; i < 8; ++i)
	{
		float roughness = i / float(8 - 1);
		materials.push_back(&roughness_material(gfx_system, "roughness_dieletric_" + to_string(roughness), Colour::Black, 0.f, roughness));
	}
	return materials;
}

vector<Material*> create_roughness_metallic_materials(GfxSystem& gfx_system)
{
	vector<Material*> materials;
	for(size_t i = 0; i < 8; ++i)
	{
		float roughness = i / float(8 - 1);
		materials.push_back(&roughness_material(gfx_system, "roughness_metallic_" + to_string(roughness), Colour::White, 1.f, roughness));
	}
	return materials;
}

void material_spheres(Gnode& parent, array<Material*> materials)
{
	float spacing = 2.f;
	float center = (materials.size() - 1) * spacing / 2.f;

	for(size_t i = 0; i < materials.size(); ++i)
	{
		Gnode& material_node = gfx::node(parent, Ref(materials[i]), vec3{ -center + float(i) * spacing, 0.f, 0.f });
		gfx::shape(material_node, Sphere(), Symbol(), 0, materials[i]);
		//gfx::model(material_node, "sphere", 0, materials[i]);
	}
}

void roughness_spheres(Gnode& parent)
{
	GfxSystem& gfx_system = parent.m_scene->m_gfx_system;

	static vector<Material*> roughness_dielectric_materials = create_roughness_dielectric_materials(gfx_system);
	static vector<Material*> roughness_metallic_materials = create_roughness_metallic_materials(gfx_system);

	float dielectric_center = roughness_dielectric_materials.size() * 2.f / 2.f;
	for(size_t i = 0; i < roughness_dielectric_materials.size(); ++i)
	{
		Gnode& material_node = gfx::node(parent, {}, vec3{ -dielectric_center + float(i) * 2.f, 0.f, 0.f });
		//Item& item = gfx::shape(material_node, Sphere(), Symbol());
		gfx::shape(material_node, Sphere(), Symbol(), 0U, roughness_dielectric_materials[i]);
	}

	float metallic_center = roughness_metallic_materials.size() * 2.f / 2.f;
	for(size_t i = 0; i < roughness_metallic_materials.size(); ++i)
	{
		Gnode& material_node = gfx::node(parent, {}, vec3{ -metallic_center + float(i) * 2.f, 0.f, 4.f });
		//Item& item = gfx::shape(material_node, Sphere(), Symbol());
		gfx::shape(material_node, Sphere(), Symbol(), 0U, roughness_metallic_materials[i]);
	}
}

void ex_03_materials(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	OrbitController& controller = ui::orbit_controller(viewer);
	UNUSED(controller);

	Gnode& scene = viewer.m_scene->begin();

	Gnode& ground_node = gfx::node(scene, {}, vec3{ 0.f, -1.f, 0.f });
	gfx::shape(ground_node, Rect(vec2{ -50.f, -50.f }, vec2{ 100.f }), Symbol(), 0U, &milky_white(viewer.m_gfx_system));

	gfx::direct_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);

	GfxSystem& gfx_system = scene.m_scene->m_gfx_system;
	
	//static vector<Material*> materials = { &milky_white(gfx_system), &mirror(gfx_system), &rocks_01(gfx_system), &fabric_08(gfx_system), &paving_stones_11(gfx_system), 
	//											&wood_floor_05(gfx_system), &paving_stones_08(gfx_system) };
	static vector<Material*> materials = { &paving_stones_11(gfx_system), &metal_plates_02(gfx_system), &paving_stones_08(gfx_system) };

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
			controller.m_position = vec3{ -center + index * 4.f, 0.f, 0.f };
		};
		viewer.picker(0).pick_point(viewer.m_viewport, mouse_event.m_relative, callback, ItemFlag::Default | ItemFlag::Selectable);
	}

	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<uint16_t, 1>{ 1U }))
	{
		Widget& sheet = ui::columns(*dock, carray<float, 2>{ 0.3f, 0.7f });

		ui::label(sheet, "Environment :");
		ui::number_field<float>(sheet, "Ambient", { viewer.m_environment.m_radiance.m_ambient, { 0.f, 100.f, 0.01f } });

		if(edited)
			object_edit(*dock, Ref(edited)); // "Particle Editor" // identity = edited
	}
}

#ifdef _03_MATERIALS_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_03_materials(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	System::instance().load_modules({ &mud_gfx::m() });
	app.m_gfx_system.add_resource_path("examples/03_materials");
	app.m_gfx_system.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif