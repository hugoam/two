//#include <mud/frame.h>
#include <frame/Api.h>
#include <refl/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-gltf/Api.h>
#include <gfx-edit/Api.h>
#include <meta/gfx.gltf.meta.h>

#include <04_lights/04_lights.h>
#include <03_materials/03_materials.h>

#ifndef USE_STL
#include <stl/vector.hpp>
#endif

using namespace mud;

class Human
{
public:
	Human(vec3 position = Zero3) : m_position(position) { m_states.push_back({ "Idle", 1.f }); }

	struct State
	{
		string m_action;
		float m_action_speed;
	};

	vec3 m_position = Zero3;
	quat m_rotation = ZeroQuat;

	vec3 m_linear_velocity = Zero3;
	vec3 m_angular_velocity = Zero3;

	vector<State> m_states;
};

Animated& paint_human(Gnode& parent, Human& human, bool high_lod)
{
	Gnode& self = gfx::node(parent, {}, human.m_position, human.m_rotation);
	gfx::shape(self, Circle(0.35f), Symbol::wire(Colour::White), ItemFlag::Default | ItemFlag::Selectable);
	Item* item = gfx::model(self, high_lod ? "human" : "human00", ItemFlag::Default | ItemFlag::Selectable);
	Animated& animated = gfx::animated(self, *item);
	return animated;
}

struct KeyMove
{
	Key key;
	vec3 velocity;
	string action;
	float action_speed;
};

void human_control_key(Widget& widget, Human& human, vec3& speed, const KeyMove& move)
{
	if(widget.key_event(move.key, EventType::Pressed))
	{
		human.m_states.push_back({ move.action, move.action_speed });
		speed += move.velocity;
	}
	if(widget.key_event(move.key, EventType::Released))
	{
		remove_if(human.m_states, [&](Human::State& state) { return state.m_action == move.action && state.m_action_speed == move.action_speed; });
		speed -= move.velocity;
	}
}

static void human_velocity_controller(Widget& widget, Human& human)
{
	bool shift = widget.ui().m_keyboard.m_shift;

	const KeyMove moves[4] =
	{
		{ Key::Up,   -Z3 * 2.f, "Walk",  1.f }, { Key::W,  -Z3 * 2.f, "Walk",  1.f },
		{ Key::Down,  Z3 * 2.f, "Walk", -1.f }, { Key::S,   Z3 * 2.f, "Walk", -1.f },
	};

	const KeyMove shift_moves[4] =
	{
		{ Key::Up,  -Z3 * 12.f, "Run",  1.f }, { Key::W, -Z3 * 12.f, "Run",  1.f },
		{ Key::Down, Z3 * 12.f, "Run", -1.f }, { Key::S,  Z3 * 12.f, "Run", -1.f },
	};

	for(const KeyMove& key_move : (shift ? shift_moves : moves))
		human_control_key(widget, human, human.m_linear_velocity, key_move);

	const KeyMove rotations[4] =
	{
		{ Key::Right, -Y3 * 4.f, "Step",  1.f }, { Key::D, -Y3 * 4.f, "Step",  1.f },
		{ Key::Left,   Y3 * 4.f, "Step", -1.f }, { Key::A,  Y3 * 4.f, "Step", -1.f },
	};

	for(const KeyMove& key_rotation: rotations)
		human_control_key(widget, human, human.m_angular_velocity, key_rotation);
}

void human_controller_3rdperson(Viewer& viewer, Human& human)
{
	human_velocity_controller(viewer, human);
}

void ex_05_character(Shell& app, Widget& parent, Dockbar& dockbar)
{
	static ImporterGltf gltf_importer(app.m_gfx_system);

	SceneViewer& viewer = ui::scene_viewer(parent);
	OrbitController& orbit = ui::orbit_controller(viewer);
	viewer.take_focus();

	Gnode& scene = viewer.m_scene->begin();

	Material& material = milky_white(viewer.m_gfx_system);

	gfx::shape(scene, Rect(vec2{ -50.f, -50.f }, vec2{ 100.f }), Symbol::plain(Colour::White), 0U, &material);

	gfx::direct_light_node(scene);
	gfx::radiance(scene, "radiance/tiber_1_1k.hdr", BackgroundMode::None);

	static bool once = false;

	constexpr size_t num_characters = 1;
	static Human characters[num_characters] = {};
	static Human* selected = &characters[0];
	static cstring animations[] = { "TPose", "Idle", "Walk", "Run", "WalkFight" };
	static size_t animation = 1;
	static Animated* animated = nullptr;
	static bool follow_character = false;
	static bool anim_editor = false;
	static bool model_high_lod = false;

	if(!once)
	{
		orbit.m_yaw = c_pi;
		orbit.m_pitch = - c_pi / 4.f;
		orbit.m_distance = 4.f;
		orbit.m_position = Y3 * 1.f;

		for(size_t i = 1; i < num_characters; ++i)
			characters[i].m_position = { random_scalar<float>(-10.f, 10.f), 0.f, random_scalar<float>(-10.f, 10.f) };

		once = true;
	}

	for(size_t i = 0; i < num_characters; ++i)
	{
		animated = &paint_human(scene, characters[i], model_high_lod);
		cstring state = characters[i].m_states.back().m_action.c_str();

		if(anim_editor && selected == &characters[i])
			continue;

		if(animated->m_playing.empty() || animated->playing() != state)
		{
			const Human::State& state = characters[i].m_states.back();
			animated->start(state.m_action.c_str(), true, 0.f, state.m_action_speed);
		}
	}

	human_controller_3rdperson(viewer, *selected);
	if(follow_character)
		orbit.set_target(characters[0].m_position);

	static Clock clock;
	float timestep = clock.step();

	vec3 velocity = rotate(selected->m_rotation, selected->m_linear_velocity);
	selected->m_position += velocity * timestep;

	if(selected->m_angular_velocity != Zero3)
	{
		float angular_speed = length(selected->m_angular_velocity);
		selected->m_rotation = rotate(selected->m_rotation, timestep * angular_speed, selected->m_angular_velocity / angular_speed);
	}

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		anim_editor = true;
		animation_edit(*dock, *animated);
	}
	else
	{
		anim_editor = false;
	}

}

#ifdef _05_CHARACTER_EXE
void pump(Shell& app)
{
	shell_context(app.m_ui->begin(), app.m_editor);
	ex_05_character(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	Shell app(MUD_RESOURCE_PATH, exec_path(argc, argv));
	app.m_gfx_system.add_resource_path("examples/05_character");
	app.m_gfx_system.init_pipeline(pipeline_pbr);
	app.run(pump);
}
#endif
