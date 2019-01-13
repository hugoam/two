#include <mud/core.h>
#include <00_cube/00_cube.h>

using namespace mud;

void speed_key(Widget& widget, vec3& speed, Key key, vec3 speed_offset)
{
	if(widget.key_event(key, EventType::Pressed))
		speed += speed_offset;
	if(widget.key_event(key, EventType::Released))
		speed -= speed_offset;
}

void velocity_controller(Widget& widget, vec3& speed, float velocity)
{
	struct KeyMove { Key key; vec3 dir; };
	const KeyMove moves[8] =
	{
		{ Key::Up,   -Z3 }, { Key::W, -Z3 },
		{ Key::Down,  Z3 }, { Key::S,  Z3 },
		{ Key::Left, -X3 }, { Key::A, -X3 },
		{ Key::Right, X3 }, { Key::D,  X3 }
	};

	for(const KeyMove& key_move : moves)
		speed_key(widget, speed, key_move.key, key_move.dir * velocity);
}

void ex_00_cube(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app); UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);
	viewer.take_focus();

	static vec3 position = Zero3;
	static vec3 speed = Zero3;

	velocity_controller(viewer, speed, 0.01f);
	position += speed;

	Gnode& scene = viewer.m_scene->begin();
    Gnode& node = gfx::node(scene, {}, position);
	gfx::shape(node, Cube(), Symbol::wire(Colour::Red));
}

#ifdef _00_CUBE_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_00_cube(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv).c_str());
	app.m_gfx_system.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif
