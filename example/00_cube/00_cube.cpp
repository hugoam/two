#define HEADER_ONLY 0

#if !HEADER_ONLY
#if TWO_MODULES
#include <infra/Config.h>
import std;
import two.infra;
import two.pool;
import two.jobs;
import two.type;
import two.ecs;
import two.math;
import two.geom;
import two.bgfx;
import two.gfx;
import two.ctx;
import two.ui;
import two.gfx;
import two.ctx.glfw;
import two.ui.vg;
import two.frame;
#else
//#include <two/frame.h>
#include <frame/Api.h>
#endif
#else
#ifdef _MSC_VER
#include <Windows.h>
#undef near
#undef far
#undef min
#undef max
#undef small
#undef NEAR
#undef FAR
#endif

#include <two/infra.cpp>
#include <two/pool.cpp>
#include <two/jobs.cpp>
#include <two/type.cpp>
#include <two/ecs.cpp>
#include <two/math.cpp>
#include <two/geom.cpp>
#include <two/bgfx.cpp>
#include <two/gfx.cpp>
#include <two/ctx.cpp>
#include <two/ui.cpp>
#include <two/gfx.ui.cpp>
#include <two/ctx.glfw.cpp>
#include <two/ui.vg.cpp>
#include <two/frame.cpp>
#endif

#include <00_cube/00_cube.h>

using namespace two;

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
		{ Key::Up,   -z3 }, { Key::W, -z3 },
		{ Key::Down,  z3 }, { Key::S,  z3 },
		{ Key::Left, -x3 }, { Key::A, -x3 },
		{ Key::Right, x3 }, { Key::D,  x3 }
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

	static vec3 position = vec3(0.f);
	static vec3 speed = vec3(0.f);

	velocity_controller(viewer, speed, 0.01f);
	position += speed;

	Gnode& scene = viewer.m_scene.begin();
    Gnode& node = gfx::node(scene, position);
	gfx::shape(node, Cube(), Symbol::wire(Colour::Pink));
}

#ifdef _00_CUBE_EXE
void pump(Shell& app, ShellWindow& window)
{
	shell_context(window.m_ui->begin(), app.m_editor);
	ex_00_cube(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(TWO_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif
