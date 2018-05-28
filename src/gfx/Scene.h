//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/NonCopy.h>
#include <math/Vec.h>
#include <gfx/Generated/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Graph.h>

#ifndef MUD_GENERATOR_SKIP_INCLUDES
#include <bgfx/bgfx.h>
#endif

#include <functional>

namespace mud
{
	struct _refl_ Sun
	{
		_attr_ _mut_ float azimuth;
		_attr_ _mut_ float elevation;
		_attr_ _mut_ Colour m_colour = { 0.8f, 0.8f, 0.0f };
		_attr_ _mut_ float m_intensity = 0.f;
	};

	struct _refl_ Radiance
	{
		_attr_ _mut_ float m_energy = 1.0f;
		_attr_ _mut_ float m_ambient = 1.0f;
		_attr_ _mut_ Colour m_colour = Colour::Black;
		_attr_ _mut_ Texture* m_texture = nullptr;
		bgfx::TextureHandle m_roughness_array = BGFX_INVALID_HANDLE;
		bool m_preprocessed = false;
	};

	enum class _refl_ BackgroundMode : unsigned int
	{
		None,
		Panorama,
		Radiance,
		Custom
	};

	struct _refl_ Background
	{
		_attr_ _mut_ BackgroundMode m_mode = BackgroundMode::None;
		_attr_ _mut_ Colour m_colour = Colour::Black;
		_attr_ _mut_ Program* m_custom_program = nullptr;
		std::function<void(Render&)> m_custom_function;
	};

	struct _refl_ Environment
	{
		_attr_ _mut_ Background m_background;
		_attr_ _mut_ Radiance m_radiance;
		_attr_ _mut_ Sun m_sun;
		//Fog* m_fog = nullptr;
	};

	class Shot;

	class _refl_ MUD_GFX_EXPORT Scene : public NonCopy
	{
	public:
		Scene(GfxSystem& gfx_system);
		~Scene();

		GfxSystem& m_gfx_system;

		object_ptr<ImmediateDraw> m_immediate;
		object_ptr<ParticleSystem> m_particle_system;
		object_ptr<PassJobs> m_pass_jobs;

		unique_ptr<ObjectPool> m_pool;

		_attr_ Gnode m_graph;
		_attr_ Node3 m_root_node;
		_attr_ _mut_ Environment m_environment;

		_meth_ Gnode& begin();
		void update();

		void gather_render(Render& render);
	};
}
