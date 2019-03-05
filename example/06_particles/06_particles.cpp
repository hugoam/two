//#include <mud/frame.h>
#include <frame/Api.h>
#include <srlz/Api.h>
#include <refl/Api.h>
#include <gfx/Api.h>
#include <meta/gfx.meta.h>

#include <06_particles/06_particles.h>

#include <stl/vector.hpp>

using namespace mud;

template <class T_Asset>
void add_asset_loader(AssetStore<T_Asset>& store, cstring format)
{
	auto loader = [&](T_Asset& asset, const string& path)
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

namespace mud
{
	template <> Type& type<ParticleItem>() { static Type ty("ParticleItem"); return ty; }
}

vector<ParticleItem> create_particles(GfxSystem& gfx, const vector<string>& names)
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

void ex_06_particles(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	OrbitController& controller = ui::orbit_controller(viewer);

	Gnode& scene = viewer.m_scene.begin();

	static vector<string> particles_names = { "particles_0" };//, "particles_1" }; //, "particles_2" };
	static vector<ParticleItem> particles_vector = create_particles(app.m_gfx, particles_names);
	static ParticleItem* edited = &particles_vector[0];

	float middle = 0.f;//particles_vector.size() * 10.f / 2.f;
	for(ParticleItem& item : particles_vector)
	{
		Gnode& node = gfx::node(scene, {}, vec3{ -middle + item.m_index * 10.f, 0.f, 0.f });
		item.m_particles = &gfx::flows(node, *item.m_emitter);

		if(item.m_particles->ended())
			item.m_particles->m_time = 0.f;

		node.m_node->m_object = Ref(&item);

		gfx::shape(node, *item.m_particles->m_shape, Symbol::wire(&item == edited ? Colour::White : Colour::AlphaGrey));
		gfx::shape(node, Cube(0.1f), Symbol::wire(Colour::White), ItemFlag::Default | ItemFlag::Selectable);
		gfx::shape(node, Cube(), Symbol(Colour::Transparent), ItemFlag::Default | ItemFlag::Selectable);
	}

	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
	{
		auto callback = [&controller, middle](Item* item)
		{
			if(item == nullptr) return;
			edited = &val<ParticleItem>(item->m_node->m_object);
			controller.m_position = vec3{ -middle + edited->m_index * 10.f, 0.f, 0.f };
		};
		viewer.picker(0).pick_point(viewer.m_viewport, mouse_event.m_relative, callback, ItemFlag::Default | ItemFlag::Selectable);
	}

	if(edited)
	{
		//if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
		//	particle_edit(*dock, viewer.m_gfx, edited->m_call); // "Particle Editor" // identity = edited
	}
}

#ifdef _06_PARTICLES_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_06_particles(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	System::instance().load_modules({ &mud_gfx::m() });
	add_asset_loader(app.m_gfx.flows(), ".ptc");
	app.m_gfx.add_resource_path("examples/06_particles");
	app.m_gfx.init_pipeline(pipeline_minimal);
	app.run(pump);
}
#endif
