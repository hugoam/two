#include <mud/mud.h>
#include <06_particles/06_particles.h>

#include <srlz/Serial.h>
#include <edit/Ui/GfxEdit.h>

#include <fstream>

using namespace mud;

struct ParticleItem
{
	Call m_call;
	size_t m_index;
	Particles* m_particles;
};

namespace mud
{
	template <> Type& type<ParticleItem>() { static Type ty("ParticleItem"); return ty; }
}

std::vector<ParticleItem> create_particles(GfxSystem& gfx_system, const std::vector<string>& names)
{
	std::vector<ParticleItem> particles_vector;

	size_t index = 0;
	for(const string& name : names)
	{
		Call particles = Call(function(gfx::particles));

		string filename = "prefabs/" + name;
		LocatedFile location = gfx_system.locate_file(filename.c_str());
		if(location.m_location)
		{
			string path = string(location.m_location) + filename;
			unpack_json_file(particles.m_arguments[1], path);
		}

		particles_vector.push_back({ particles, index++, nullptr });
	}

	return particles_vector;
}

void ex_06_particles(Shell& app, Widget& parent, Dockbar& dockbar)
{
	UNUSED(app);
	SceneViewer& viewer = ui::scene_viewer(parent);
	OrbitController& controller = ui::orbit_controller(viewer);

	viewer.m_filters.m_tonemap.m_enabled = false;

	Gnode& groot = viewer.m_scene->begin();

	static std::vector<string> particles_names = { "particles_0" };//, "particles_1" }; //, "particles_2" };
	static std::vector<ParticleItem> particles_vector = create_particles(viewer.m_gfx_system, particles_names);
	static ParticleItem* edited = &particles_vector[0];

	float middle = 0.f;//particles_vector.size() * 10.f / 2.f;
	for(ParticleItem& item : particles_vector)
	{
		Gnode& particle_node = gfx::node(groot, {}, vec3{ -middle + item.m_index * 10.f, 0.f, 0.f });

		item.m_call.m_arguments[0] = Ref(&particle_node);
		Var result = item.m_call();
		item.m_particles = &val<Particles>(result);

		particle_node.m_node->m_object = Ref(&item);

		gfx::shape(particle_node, *item.m_particles->m_emitter.m_shape, Symbol(&item == edited ? Colour::White : Colour::AlphaGrey));
		gfx::shape(particle_node, Cube(0.1f), Symbol(Colour::White), ITEM_SELECTABLE);
		gfx::shape(particle_node, Cube(), Symbol(Colour::None, Colour::Transparent), ITEM_SELECTABLE);
	}

	if(MouseEvent mouse_event = viewer.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
	{
		auto callback = [&controller, middle](Item* item)
		{
			edited = &val<ParticleItem>(item->m_node.m_object);
			controller.m_position = vec3{ -middle + edited->m_index * 10.f, 0.f, 0.f };
		};
		viewer.pick_point(mouse_event.m_relative, callback, ITEM_SELECTABLE);
	}

	if(edited)
	{
		if(Widget* dock = ui::dockitem(dockbar, "Game", carray<uint16_t, 1>{ 1U }))
			particle_edit(*dock, viewer.m_gfx_system, edited->m_call); // "Particle Editor" // identity = edited
	}
}

#ifdef _06_PARTICLES_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_06_particles(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	cstring example_path = MUD_RESOURCE_PATH "examples/06_particles/";
	Shell app(carray<cstring, 2>{ MUD_RESOURCE_PATH, example_path }, argc, argv);
	app.run(pump);
}
#endif
