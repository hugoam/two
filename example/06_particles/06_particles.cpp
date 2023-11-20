#include <infra/Cpp20.h>
import two.frame;

#include <06_particles/06_particles.h>

using namespace two;

template <class T_Asset>
void add_asset_loader(AssetStore<T_Asset>& store, cstring format)
{
	auto loader = [&](T_Asset& asset, const string& path, NoConfig)
	{
		unpack_json_file(Ref(&asset), path + store.m_formats[0]);
	};

	store.add_format(format, loader);
}

struct ParticleItem
{
	size_t m_index;
	Flow* m_emitter;
	Flare* m_particles;
};

namespace two
{
	template <> Type& type<ParticleItem>() { static Type ty("ParticleItem"); return ty; }
}

vector<ParticleItem> create_particles(GfxSystem& gfx, span<string> names)
{
	vector<ParticleItem> particles_vector;

	size_t index = 0;
	for(const string& name : names)
	{
		Flow* emitter = gfx.flows().file(name.c_str());
		particles_vector.push_back({ index++, emitter, nullptr });
	}

	return particles_vector;
}

Flow flow0()
{
	Flow f;
	f.m_loop = true;
	f.m_blend = { { 0.f, 1.f } };
	f.m_blend_mode = BlendMode::Add;

	f.m_colour = { { Colour(0.074f, 0.166f, 0.326f), Colour(0.087f, 0.219f, 0.513f), Colour(0.710f, 0.260f, 0.760f) } };
	f.m_rate = { 40U };
	f.m_scale = { { 0.2f, 1.f, 0.1f } };
	f.m_shape = Circle(1.f);
	f.m_speed = { 0.f };
	f.m_sprite_name = "particle.ktx";
	return f;
}

void ex_06_particles(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	OrbitController& controller = ui::orbit_controller(viewer);

	Gnode& scene = viewer.m_scene.begin();

	//static vector<string> particles_names = { "particles_0" };//, "particles_1" }; //, "particles_2" };
	//static vector<ParticleItem> particles_vector = create_particles(app.m_gfx, particles_names);

	static Flow flow = flow0();
	static ParticleItem particles[] = { { 0, &flow, nullptr } };
	static ParticleItem* edited = &particles[0];

	float middle = 0.f;//particles_vector.size() * 10.f / 2.f;
	for(ParticleItem& item : particles)
	{
		Gnode& node = gfx::node(scene, vec3(-middle + item.m_index * 10.f, 0.f, 0.f));
		item.m_particles = &gfx::flows(node, *item.m_emitter);

		if(item.m_particles->ended())
			item.m_particles->m_time = 0.f;

		//node.m_node->m_object = Ref(&item);

		gfx::shape(node, *item.m_particles->m_shape, Symbol::wire(&item == edited ? Colour::White : Colour::AlphaGrey));
		gfx::shape(node, Cube(0.1f), Symbol::wire(Colour::White), ItemFlag::Default | ItemFlag::Selectable);
		gfx::shape(node, Cube(), Symbol(Colour::Transparent), ItemFlag::Default | ItemFlag::Selectable);
	}

	if(MouseEvent event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
	{
		auto callback = [&controller, middle](Item* item)
		{
			if(item == nullptr) return;
			//edited = &val<ParticleItem>(item->m_node->m_object);
			controller.m_position = vec3(-middle + edited->m_index * 10.f, 0.f, 0.f);
		};
		viewer.picker(0).pick_point(viewer.m_viewport, event.m_relative, callback, ItemFlag::Default | ItemFlag::Selectable);
	}

	if(edited)
	{
		//if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
		//	particle_edit(*dock, viewer.m_gfx, edited->m_call); // "Particle Editor" // identity = edited
	}
}

#ifdef _06_PARTICLES_EXE
void pump(Shell& app, ShellWindow& window)
{
	shell_context(window.m_ui->begin(), app.m_editor);
	ex_06_particles(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(TWO_RESOURCE_PATH, exec_path(argc, argv));
	System::instance().load_modules({ &two_gfx::m() });
	add_asset_loader(app.m_gfx.flows(), ".ptc");
	app.m_gfx.add_resource_path("examples/06_particles");
	app.m_gfx.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif
