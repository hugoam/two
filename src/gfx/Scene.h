//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/NonCopy.h>
#include <type/Unique.h>
#include <math/Vec.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Graph.h>

#include <bgfx/bgfx.h>

#ifndef MUD_CPP_20
#include <functional>
#endif

namespace mud
{
	export_ struct refl_ Sun
	{
		attr_ float azimuth;
		attr_ float elevation;
		attr_ Colour m_colour = { 0.8f, 0.8f, 0.0f };
		attr_ float m_intensity = 0.f;
	};

	export_ struct refl_ Radiance
	{
		attr_ float m_energy = 1.0f;
		attr_ float m_ambient = 1.0f;
		attr_ Colour m_colour = Colour::Black;
		attr_ Texture* m_texture = nullptr;
		bgfx::TextureHandle m_roughness_array = BGFX_INVALID_HANDLE;
		bool m_preprocessed = false;
	};

	export_ enum class refl_ BackgroundMode : unsigned int
	{
		None,
		Panorama,
		Radiance,
		Custom
	};

	export_ struct refl_ Background
	{
		attr_ BackgroundMode m_mode = BackgroundMode::None;
		attr_ Colour m_colour = Colour::Black;
		attr_ Program* m_custom_program = nullptr;
		std::function<void(Render&)> m_custom_function;
	};

	export_ struct refl_ Fog
	{
		attr_ bool m_enabled = false;
		attr_ float m_density = 0.01f;
		attr_ Colour m_colour = Colour::White;

		attr_ bool m_depth = false;
		attr_ float m_depth_begin = 0.f;
		attr_ float m_depth_curve = 1.f;

		attr_ bool m_height = false;
		attr_ float m_height_min = 0.f;
		attr_ float m_height_max = 1.f;
		attr_ float m_height_curve = 0.1f;

		attr_ bool m_transmit = false;
		attr_ float m_transmit_curve = 1.f;
	};

	export_ struct refl_ Environment
	{
		attr_ Background m_background;
		attr_ Radiance m_radiance;
		attr_ Sun m_sun;
		attr_ Fog m_fog;
	};

	class Shot;

	export_ class refl_ MUD_GFX_EXPORT Scene : public NonCopy
	{
	public:
		Scene(GfxSystem& gfx_system);
		~Scene();

		GfxSystem& m_gfx_system;

		object_ptr<ImmediateDraw> m_immediate;
		object_ptr<ParticleSystem> m_particle_system;
		object_ptr<PassJobs> m_pass_jobs;

		unique_ptr<ObjectPool> m_pool;

		attr_ Gnode m_graph;
		attr_ Node3 m_root_node;
		attr_ Environment m_environment;
		attr_ Ref m_user;

		meth_ Gnode& begin();
		void update();

		void gather_render(Render& render);

		std::vector<Sound*> m_orphan_sounds;
	};
}
