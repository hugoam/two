//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>
#ifndef MUD_CPP_20
#include <fstream>
#endif

#ifdef MUD_MODULES
module mud.edit;
#else
#include <obj/Reflect/Method.h>
#include <srlz/Serial.h>
#include <obj/System/System.h>
#include <geom/Shapes.h>
#include <geom/Symbol.h>
#include <gfx/Gfx.h>
#include <gfx/GfxSystem.h>
#include <uio/Unode.h>
#include <uio/Edit/Inspector.h>
#include <uio/Edit/Section.h>
#include <uio/Edit/Value.h>
#include <edit/Generated/Types.h>
#include <edit/Ui/ParticleEdit.h>
#include <edit/Viewer/Viewer.h>
#endif

namespace mud
{
	struct ParticleEditorState : public NodeState
	{
		ParticleEditorState() : m_particles(function(gfx::particles)) {}
		Call m_particles;
	};

	void cube_test(Gnode& parent)
	{
		Gnode& self = gfx::node(parent);
		gfx::shape(self, Cube(1.f), Symbol());
	}

	void particle_editor_viewer(Widget& parent, Call& particles)
	{
		SceneViewer& viewer = ui::scene_viewer(parent, vec2{ 500.f });
		ui::orbit_controller(viewer);

		//viewer.m_viewport.m_clear_colour = Colour::DarkGrey;
		//viewer.m_camera.set_isometric(SOUTH, Zero3);

		Gnode& scene = viewer.m_scene->begin();
		particles.m_arguments[0] = Ref(&parent);
		particles.m_arguments[1] = var(string("particle.ktx"));
		particles();
		
		Shape* shape = val<ParticleGenerator>(particles.m_arguments[2]).m_shape.m_shape.get();
		if(shape)
			gfx::shape(scene, *shape, Symbol());

		cube_test(scene);
	}

	enum ParticleEditSwitch
	{
		OPEN_PARTICLES = 1 << 0,
		SAVE_PARTICLES = 1 << 1
	};

	void open_particles(Widget& parent, GfxSystem& system, ParticleGenerator& generator)
	{
		static string location = "";
		if(select_value(parent, OPEN_PARTICLES, location, true))
		{
			if(std::fstream(string(system.m_resource_path) + location).good())
			{
				unpack_json_file(&generator, string(system.m_resource_path) + location);
			}
		}
	}

	void save_particles(Widget& parent, GfxSystem& system, ParticleGenerator& generator)
	{
		static string destination = "";
		if(select_value(parent, SAVE_PARTICLES, destination, true))
		{
			pack_json_file(Ref(&generator), string(system.m_resource_path) + destination);
		}
	}

	void particle_edit(Widget& parent, GfxSystem& system, ParticleGenerator& generator)
	{
		Section& self = section(parent, "Particle Editor");

		//call_edit(self, generator);
		object_edit(*self.m_body, &generator);
		//particle_editor_viewer(self, particles);

		if(ui::modal_button(self, *self.m_toolbar, "Open", OPEN_PARTICLES))
			open_particles(self, system, generator);
		if(ui::modal_button(self, *self.m_toolbar, "Save", SAVE_PARTICLES))
			save_particles(self, system, generator);
	}

	void particle_edit(Widget& parent, GfxSystem& system, Call& particles_call)
	{
		particle_edit(parent, system, val<ParticleGenerator>(particles_call.m_arguments[1]));
	}

	void particle_editor(Widget& parent, GfxSystem& system)
	{
		Widget& self = ui::sheet(parent);
		ParticleEditorState& state = self.state<ParticleEditorState>();
		particle_edit(self, system, state.m_particles);
	}
}
