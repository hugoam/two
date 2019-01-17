#include <mud/core.h>
#include <gfx-pbr/Api.h>

#include <11_selection/11_selection.h>
#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>

using namespace mud;

vec4 abs_rect(const vec2& start, const vec2& size)
{
	vec2 position = { size.x > 0.f ? start.x : start.x + size.x,
		size.y > 0.f ? start.y : start.y + size.y };
	return{ position, abs(size) };
}

void ex_11_selection(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app); UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Gnode& scene = viewer.m_scene->begin();

	Material& material = milky_white(viewer.m_gfx_system);

	//gfx::direct_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	static std::vector<ShapeVar> shapes = { Cube(1.f), Sphere(), Cylinder() }; // @todo Circle() looks weird
	static std::vector<ShapeInstance > shape_items = create_shape_grid(10U, 10U, shapes);
	static Symbol symbol;

	shape_grid(scene, { shape_items.data(), 10U, 10U }, &symbol, false, &material);

	static std::vector<Item*> selected = {};
	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
	{
		//viewer.picker(0).pick_point(viewer.m_viewport, mouse_event.m_relative, [&](Item* item) { selected = { item }; }, ItemFlag::Default | ItemFlag::Selectable);
	}

	static vec4 select_rect = Zero4;
	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
	{
		vec2 start = viewer.m_frame.local_position(mouse_event.m_pressed);
		vec2 end = mouse_event.m_relative;
		select_rect = abs_rect(start, end - start);
	}

	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
	{
		//auto select = [&](array<Item*> items) { selected = to_vector(items); };
		//viewer.picker(0).pick_rectangle(viewer.m_viewport, select_rect, select, ItemFlag::Default | ItemFlag::Selectable);
		//select_rect = Zero4;
	}

	if(select_rect != Zero4)
		ui::rectangle(viewer, select_rect);

	for(Item* selected_item : selected)
		if(selected_item)
			gfx::draw(scene, selected_item->m_aabb, Symbol::wire(Colour::White));
}

#ifdef _11_SELECTION_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_11_selection(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv).c_str());
	app.m_gfx_system.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif
