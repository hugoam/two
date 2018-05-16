//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Generated/Forward.h>
#include <gfx/Renderer.h>
#include <gfx/Particles.h>

namespace mud
{
	class _refl_ MUD_GFX_EXPORT BlockParticles : public DrawBlock
	{
	public:
		BlockParticles(GfxSystem& gfx_system);

		ParticleSystem m_particle_system;

		virtual void init_gfx_block() final;

		virtual void begin_gfx_block(Render& render) final;
		virtual void submit_gfx_block(Render& render) final;

		virtual void begin_gfx_pass(Render& render) final;
		virtual void submit_gfx_element(Render& render, Pass& render_pass, DrawElement& element) final;
	};

	class MUD_GFX_EXPORT PassParticles : public RenderPass
	{
	public:
		PassParticles(GfxSystem& gfx_system, BlockParticles& pass_particles);

		virtual void begin_render_pass(Render& render) final;
		virtual void submit_render_pass(Render& render) final;

		BlockParticles& m_block_particles;
	};
}
