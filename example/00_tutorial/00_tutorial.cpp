#include <mud/mud.h>
#include <00_tutorial/00_tutorial.h>
#include <meta/00_tutorial/Module.h>

MyObject::MyObject(ShapeType shape, Colour colour)
	: m_shape(shape)
	, m_colour(colour)
{}

int MyObject::method()
{
	printf("MyObject::method() called !\n");
	return m_number;
};

void foo(int arg)
{
	UNUSED(arg);
	printf("foo() called !\n");
}

void bar(MyObject& object)
{
	UNUSED(object);
	printf("bar() called !\n");
}

void ex_00_tutorial_pump(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app); UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	Gnode& scene = viewer.m_scene->begin();
	Gnode& node = gfx::node(scene, {}, Zero3);
    gfx::shape(node, Cube(), Symbol(Colour::Red));

	static std::vector<Var> objects = { var(MyObject(ShapeType::Sphere, Colour::Pink)) };
	static size_t selected = SIZE_MAX;

	Widget& modal = ui::popup(viewer, styles().modal, { 800, 600 }, ui::PopupFlags::None);
	//Widget& modal = ui::modal(viewer, { 800, 600 });
	Widget& board = ui::board(*modal.m_body);
	multi_inspector(board, type<MyObject>(), objects, selected);
	
	if(selected != SIZE_MAX)
	{
		Widget& div = ui::layout_span(board, 0.3f);
		inspector(div, objects[selected]);
	}
}

#ifdef _00_TUTORIAL_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_00_tutorial_pump(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	_00_tutorial::m();
	Shell app(cstrarray(MUD_RESOURCE_PATH), argc, argv);
	app.run(pump);
}
#endif
