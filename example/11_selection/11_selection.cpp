//#include <two/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <infra/Vector.h>

#include <11_selection/11_selection.h>
#include <01_shapes/01_shapes.h>
#include <03_materials/03_materials.h>

#include <stl/vector.hpp>

using namespace two;

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

	Gnode& scene = viewer.m_scene.begin();

	Material& material = milky_white(app.m_gfx);

	//gfx::direct_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	static vector<ShapeVar> shapes = { Cube(1.f), Sphere(), Cylinder() }; // @todo Circle() looks weird
	static vector<ShapeInstance > shape_items = create_shape_grid(10U, 10U, shapes);
	static Symbol symbol;

	shape_grid(scene, { shape_items.data(), 10U, 10U }, &symbol, false, &material);

	static vector<Item*> selected = {};
	if(MouseEvent event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
	{
		auto pick = [&](Item* item) { selected = { item }; };
		viewer.picker(0).pick_point(viewer.m_viewport, event.m_relative, pick, ItemFlag::Default | ItemFlag::Selectable);
	}

	static vec4 select_rect = vec4(0.f);
	if(MouseEvent event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Dragged))
	{
		vec2 start = viewer.m_frame.local_position(mouse_event.m_pressed);
		vec2 end = event.m_relative;
		select_rect = abs_rect(start, end - start);
	}

	if(MouseEvent event = viewer.mouse_event(DeviceType::MouseLeft, EventType::DragEnded))
	{
		auto select = [&](span<Item*> items) { selected = to_vector(items); };
		viewer.picker(0).pick_rectangle(viewer.m_viewport, select_rect, select, ItemFlag::Default | ItemFlag::Selectable);
		select_rect = vec4(0.f);
	}

	if(select_rect != vec4(0.f))
		ui::rectangle(viewer, select_rect);

	for(Item* selected_item : selected)
		if(selected_item)
			gfx::draw(scene, Cube(selected_item->m_aabb), Symbol::wire(Colour::White));
}

#ifdef _11_SELECTION_EXE
void pump(Shell& app, ShellWindow& window)
{
	shell_context(window.m_ui->begin(), app.m_editor);
	ex_11_selection(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(TWO_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif
