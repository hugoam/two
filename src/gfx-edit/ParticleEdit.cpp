//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.gfx-edit;
#else
#include <infra/File.h>
#include <type/Var.h>
#include <tree/Graph.hpp>
#include <srlz/Serial.h>
#include <geom/Shapes.h>
#include <geom/Symbol.h>
#include <gfx/Gfx.h>
#include <gfx/GfxSystem.h>
#include <ui/Section.h>
#include <ui/Ui.h>
#include <uio/Inspector.h>
#include <uio/ValueEdit.h>
#include <gfx/Particles.h>
#include <gfx-ui/Types.h>
#include <gfx-ui/Viewer.h>
#include <gfx-edit/ParticleEdit.h>
#endif

namespace two
{
	struct ParticleEditorState : public NodeState
	{
		ParticleEditorState() {}
		Flow m_particles;
	};

	void cube_test(Gnode& parent)
	{
		Gnode& self = gfx::node(parent);
		gfx::shape(self, Cube(1.f), Symbol());
	}

	void particle_editor_viewer(Widget& parent, Flow& particles)
	{
		SceneViewer& viewer = ui::scene_viewer(parent, vec2(500.f));
		ui::orbit_controller(viewer);

		//viewer.m_clear_colour = Colour::DarkGrey;
		//viewer.m_camera.set_isometric(SOUTH, vec3(0.f));

		Gnode& scene = viewer.m_scene.begin();
		gfx::flows(scene, particles);

		Shape* shape = particles.m_shape.m_shape.get();
		if(shape)
			gfx::shape(scene, *shape, Symbol());

		cube_test(scene);
	}

	enum ParticleEditSwitch
	{
		OPEN_PARTICLES = 1 << 0,
		SAVE_PARTICLES = 1 << 1
	};

	void open_particles(Widget& parent, GfxSystem& system, Flow& generator)
	{
		static string location = "";
		if(select_value(parent, OPEN_PARTICLES, location, true))
		{
			if(file_exists(system.m_resource_path + "/" + location))
			{
				unpack_json_file(Ref(&generator), system.m_resource_path + "/" + location);
			}
		}
	}

	void save_particles(Widget& parent, GfxSystem& system, Flow& generator)
	{
		static string destination = "";
		if(select_value(parent, SAVE_PARTICLES, destination, true))
		{
			pack_json_file(Ref(&generator), system.m_resource_path + "/" + destination);
		}
	}

	void particle_edit(Widget& parent, GfxSystem& system, Flow& generator)
	{
		Section& self = section(parent, "Particle Editor");

		object_edit(*self.m_body, Ref(&generator));
		particle_editor_viewer(self, generator);

		if(ui::modal_button(self, *self.m_toolbar, "Open", OPEN_PARTICLES))
			open_particles(self, system, generator);
		if(ui::modal_button(self, *self.m_toolbar, "Save", SAVE_PARTICLES))
			save_particles(self, system, generator);
	}

	void particle_editor(Widget& parent, GfxSystem& system)
	{
		Widget& self = ui::sheet(parent);
		ParticleEditorState& state = self.state<ParticleEditorState>();
		particle_edit(self, system, state.m_particles);
	}
}
