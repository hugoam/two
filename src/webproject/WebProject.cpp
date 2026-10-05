#include <frame/Api.h>
#include <webcl/WebProject.h>


void web_project()
{
    Shell app(TWO_RESOURCE_PATH, exec_path(argc, argv), false);
	Window& w0 = app.window("two", uvec2(1600U, 900U));

	app.m_gfx.init_pipeline(pipeline_pbr);

	Scene scene(app.m_gfx);
	GfxViewer viewer(window, scene);

    Node3& ln = Node3().add(scene.m_graph);
    Light& l = Light(ln, LightType::Point, false, rgb(0xffffff), 2.f, 0.f).add(scene.m_graph);
    
    Model& model = *app.m_gfx.models().file("WaltHead");

    Node3& n0 = Node3(vec3(0.f, -500.f, 0.f), ZeroQuat, vec3(15.f)).add(scene.m_graph);
    Item& i = Item(n0, model, 0U, &material1).add(scene.m_graph);

    while(true)
    {
        bool pursue = app.begin_frame();

        OrbitControls& controls = ui::orbit_controls(viewer);
        controls.enableDamping = true;
        controls.dampingFactor = 0.25f;
        controls.rotateSpeed = 0.35f;

		app.end_frame();
		if(!pursue) break;
    }
}
