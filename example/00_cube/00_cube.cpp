#include <mud/mud.h>
#include <00_cube/00_cube.h>

using namespace mud;

void speed_key(Widget& widget, vec3& speed, KeyCode key, vec3 speed_offset)
{
	if(widget.key_event(key, EventType::Pressed))
		speed += speed_offset;
	if(widget.key_event(key, EventType::Released))
		speed -= speed_offset;
}

void velocity_controller(Widget& widget, vec3& speed, float velocity)
{
	struct KeyMove { KeyCode key; vec3 dir; };
	const KeyMove moves[8] =
	{
		{ KC_UP,   -Z3 },{ KC_W, -Z3 },
		{ KC_DOWN,  Z3 },{ KC_S,  Z3 },
		{ KC_LEFT, -X3 },{ KC_A, -X3 },
		{ KC_RIGHT, X3 },{ KC_D,  X3 }
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

	Gnode& groot = viewer.m_scene->begin();
	gfx::node_shape(groot, Cube(), Symbol(Colour::Red), position);
}

#ifdef _00_CUBE_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_00_cube(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(cstrarray(MUD_RESOURCE_PATH), argc, argv);
	app.run(pump);
}
#endif
