#include <mud/mud.h>
#include <14_live_gfx/14_live_gfx.h>

using namespace mud;

static LuaScript& create_script(LuaInterpreter& interpreter)
{
	Signature signature = { { Param{ "scene", Ref(type<Gnode>()) } } };
	static LuaScript script = { "Example Script", signature };
	script.m_interpreter = &interpreter;

	script.m_script =
		"\n"
		"--local n = gfx.node(scene, nil, vec3(0), quat(0,0,0,1), vec3(1))" "\n"
		"--gfx.shape(n, Symbol(Colour.White, Colour.None), Cube())" "\n"
		"\n"
		"if time == nil then" "\n"
		"    time = 0.0" "\n"
		"end" "\n"
		"\n"
		"time = time + 0.01" "\n"
		"\n"
		"for x = 1,11 do" "\n"
		"    for y = 1,11 do" "\n"
		"\n"
		"        local angles = vec3(time + x * 0.21, 0, time + y * 0.37)" "\n"
		"        local pos = vec3(-15 + x * 3, 0, -15 + y * 3)" "\n"
		"\n"
		"        local r = (math.cos(time + x * 0.21) + 1.0) / 2.0" "\n"
		"        local b = (math.sin(time + y * 0.37) + 1.0) / 2.0" "\n"
		"        local g = (math.cos(time) + 1.0) / 2.0" "\n"
		"        local color = Colour(r, g, b)" "\n"
		"\n"
		"        local n = gfx.node(scene, nil, pos, quat(angles), vec3(1))" "\n"
		"        gfx.draw(n, Cube(), Symbol(color, Colour.None))" "\n"
		"\n"
		"    end" "\n"
		"end" "\n"
		"\n"
		;

	return script;
}

void ex_14_live_gfx(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Gnode& scene = viewer.m_scene->begin();

	static LuaInterpreter lua = { true };
	static LuaScript& script = create_script(lua);

	if(Widget* dock = ui::dockitem(dockbar, "Game", carray<uint16_t, 1>{ 1U }))
	{
		script_edit(*dock, script);
	}

	std::vector<Var> args = { Ref(&scene) };
	script(args);
}

#ifdef _14_LIVE_GFX_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_14_live_gfx(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(cstrarray(MUD_RESOURCE_PATH), argc, argv);
	app.run(pump);
}
#endif

