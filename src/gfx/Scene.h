//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/NonCopy.h>
#include <math/Vec.h>
#endif
#include <gfx/Generated/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Graph.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

#ifndef MUD_CPP_20
#include <functional>
#endif

namespace mud
{
	export_ struct refl_ Sun
	{
		attr_ mut_ float azimuth;
		attr_ mut_ float elevation;
		attr_ mut_ Colour m_colour = { 0.8f, 0.8f, 0.0f };
		attr_ mut_ float m_intensity = 0.f;
	};

	export_ struct refl_ Radiance
	{
		attr_ mut_ float m_energy = 1.0f;
		attr_ mut_ float m_ambient = 1.0f;
		attr_ mut_ Colour m_colour = Colour::Black;
		attr_ mut_ Texture* m_texture = nullptr;
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
		attr_ mut_ BackgroundMode m_mode = BackgroundMode::None;
		attr_ mut_ Colour m_colour = Colour::Black;
		attr_ mut_ Program* m_custom_program = nullptr;
		std::function<void(Render&)> m_custom_function;
	};

	export_ struct refl_ Environment
	{
		attr_ mut_ Background m_background;
		attr_ mut_ Radiance m_radiance;
		attr_ mut_ Sun m_sun;
		//Fog* m_fog = nullptr;
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
		attr_ mut_ Environment m_environment;

		meth_ Gnode& begin();
		void update();

		void gather_render(Render& render);
	};
}
