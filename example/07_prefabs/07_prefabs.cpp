#include <mud/frame.h>
#include <gfx-pbr/Api.h>
#include <gfx-gltf/Api.h>

#include <07_prefabs/07_prefabs.h>

using namespace mud;

namespace mud
{
	//MUD_GFX_UI_EXPORT void prefab_edit(Widget& parent, GfxSystem& gfx_system, PrefabNode& node, PrefabNode*& selected, EditContext& context);

	void prefab_edit(Widget& parent, GfxSystem& gfx_system, PrefabNode& node, PrefabNode*& selected, EditContext& context)
	{
		prefab_edit(parent, gfx_system, node, selected);
		Widget& layout = ui::layout(*context.m_viewer);
		//Widget& toolbar = ui::toolbar(layout);
		Widget& toolbar = ui::row(layout);
		tools_transform(toolbar, context);
	}
}

PrefabNode& add_node(Prefab& prefab, PrefabType type, Function& function, Ref object)
{
	PrefabNode node;
	node.m_prefab_type = type;
	node.m_object = object;
	node.m_call = { function };
	node.m_call.m_arguments[1] = object;
	node.m_call.m_arguments[2] = var(uint32_t(ItemFlag::Default | ItemFlag::Selectable));
	prefab.m_node.m_nodes.push_back(node);
	return prefab.m_node.m_nodes.back();
}

void ex_07_prefabs_init(Shell& app)
{
#ifdef MUD_PLATFORM_EMSCRIPTEN
	app.m_gfx_system.particles().load_files(MUD_RESOURCE_PATH);
	app.m_gfx_system.models().load_files(MUD_RESOURCE_PATH);
#else
	app.m_gfx_system.particles().load_files(MUD_RESOURCE_PATH "examples/07_prefabs/");
	app.m_gfx_system.models().load_files(MUD_RESOURCE_PATH "examples/07_gltf/");
#endif
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

	static Prefab& prefab = app.m_gfx_system.prefabs().create("Prefab");
	static PrefabNode* selected = nullptr;

	Widget& board = ui::board(parent);
	Widget& right = ui::layout_span(board, 0.2f);
	Widget& left = ui::layout_span(board, 0.8f);

	asset_browser(right, app.m_gfx_system);

	SceneViewer& viewer = ui::scene_viewer(left);
	ui::orbit_controller(viewer);
	app.m_editor.m_viewer = &viewer;

	Gnode& scene = viewer.m_scene->begin();
	prefab.m_node.draw(scene);

	gfx::direct_light_node(scene, sun_rotation(c_pi / 4.f, c_pi / 4.f));
	//gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::Radiance);

	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::DraggedTarget))
		if(parent.ui().m_drop.m_object)
		{
			Widget& tooltip = ui::widget(viewer.ui(), styles().tooltip).layer();
			tooltip.m_frame.set_position(mouse_event.m_pos);
			ui::label(tooltip, "dropping");
		}

	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Dropped))
		if(parent.ui().m_drop.m_object)
		{
			if(type(parent.ui().m_drop.m_object).is<Model>())
				selected = &add_node(prefab, PrefabType::Item, function(gfx::item), parent.ui().m_drop.m_object);
			if(type(parent.ui().m_drop.m_object).is<ParticleGenerator>())
				selected = &add_node(prefab, PrefabType::Particles, function(gfx::particles), parent.ui().m_drop.m_object);
		}

	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
	{
		auto select = [&](Item* item) { selected = &val<PrefabNode>(item->m_node->m_object); };
		viewer.picker(0).pick_point(viewer.m_viewport, mouse_event.m_relative, select, ItemFlag::Default | ItemFlag::Selectable);
	}

	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<uint16_t, 1>{ 1U }))
	{
		prefab_edit(*dock, viewer.m_gfx_system, prefab.m_node, selected, app.m_editor); // "Particle Editor" // identity = edited
		if(selected)
			app.m_editor.m_selection = { Ref(&selected->m_transform) };
		else
			app.m_editor.m_selection = {};
	}

	if(selected)
	{
		Gnode& node = gfx::node(scene, Ref(selected), selected->m_transform);
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
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_07_prefabs(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	cstring prefab_path		= MUD_RESOURCE_PATH "examples/07_prefabs/";
	cstring gtlf_path		= MUD_RESOURCE_PATH "examples/07_gltf/";
	//cstring character_path	= MUD_RESOURCE_PATH "examples/07_character/";
	Shell app(cstrarray(MUD_RESOURCE_PATH, prefab_path, gtlf_path), argc, argv);
	app.m_gfx_system.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif
