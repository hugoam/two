#include <mud/mud.h>
#include <07_prefabs/07_prefabs.h>

using namespace mud;

void ex_07_prefabs_init(Shell& app)
{
	app.m_gfx_system.particles().load_files(MUD_RESOURCE_PATH "examples/07_prefabs/");
	app.m_gfx_system.models().load_files(MUD_RESOURCE_PATH "examples/07_gltf/");
	//app.m_gfx_system.models().load_files(MUD_RESOURCE_PATH "models/");
}

void ex_07_prefabs(Shell& app, Widget& parent, Dockbar& dockbar)
{
	static bool once = false;
	if(!once)
	{
		ex_07_prefabs_init(app);
		once = true;
	}

	static PrefabNode prefab;
	static PrefabNode* selected = nullptr;

	Widget& board = ui::board(parent);
	Widget& right = ui::layout_span(board, 0.2f);
	Widget& left = ui::layout_span(board, 0.8f);

	asset_browser(right, app.m_gfx_system);

	SceneViewer& viewer = ui::scene_viewer(left);
	ui::orbit_controller(viewer);
	app.m_editor.m_viewer = &viewer;

	Gnode& scene = viewer.m_scene->begin();
	prefab.draw(scene);

	gfx::directional_light_node(scene, sun_rotation(M_PI / 4.f, M_PI / 4.f));
	//gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);

	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::DraggedTarget))
		if(parent.root_sheet().m_drop.m_object)
		{
			Widget& tooltip = ui::widget(viewer.root_sheet(), styles().tooltip).layer();
			tooltip.m_frame.set_position(mouse_event.m_pos);
			ui::label(tooltip, "dropping");
		}

	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Dropped))
		if(parent.root_sheet().m_drop.m_object)
		{
			if(parent.root_sheet().m_drop.m_object.type().is<Model>())
			{
				PrefabNode node;
				node.m_prefab_type = PrefabType::Item;
				node.m_call = { function(gfx::item) };
				node.m_call.m_arguments[1] = parent.root_sheet().m_drop.m_object;
				node.m_call.m_arguments[2] = var(uint32_t(ITEM_SELECTABLE));
				prefab.m_nodes.push_back(node);
				selected = &prefab.m_nodes.back();
			}
			if(parent.root_sheet().m_drop.m_object.type().is<ParticleGenerator>())
			{
				PrefabNode node;
				node.m_prefab_type = PrefabType::Particles;
				node.m_call = { function(gfx::particles) };
				node.m_call.m_arguments[1] = parent.root_sheet().m_drop.m_object;
				node.m_call.m_arguments[2] = var(uint32_t(ITEM_SELECTABLE));
				prefab.m_nodes.push_back(node);
				selected = &prefab.m_nodes.back();
			}
		}

	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
	{
		auto select = [&](Item* item) { selected = &val<PrefabNode>(item->m_node.m_object); };
		viewer.pick_point(mouse_event.m_relative, select, ITEM_SELECTABLE);
	}

	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<uint16_t, 1>{ 1U }))
	{
		prefab_edit(*dock, viewer.m_gfx_system, prefab, selected, app.m_editor); // "Particle Editor" // identity = edited
		if(selected)
			app.m_editor.m_selection = { &selected->m_transform };
		else
			app.m_editor.m_selection = {};
	}

	if(selected)
	{
		Gnode& node = gfx::node(scene, selected, selected->m_transform);
		if(selected->m_prefab_type == PrefabType::Item)
		{
			if(!selected->m_call.m_arguments[1].null())
			{
				Model& model = val<Model>(selected->m_call.m_arguments[1]);
				gfx::draw(node, model.m_aabb, Symbol());
			}
		}
	}
}

#ifdef _07_PREFABS_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_07_prefabs(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	cstring prefab_path		= MUD_RESOURCE_PATH "examples/07_prefabs/";
	cstring gtlf_path		= MUD_RESOURCE_PATH "examples/07_gltf/";
	//cstring character_path	= MUD_RESOURCE_PATH "examples/07_character/";
	Shell app(cstrarray(MUD_RESOURCE_PATH, prefab_path, gtlf_path), argc, argv);
	app.run(pump);
}
#endif
