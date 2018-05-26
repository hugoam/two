//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Renderer.h>

namespace mud
{
	enum ShaderOptionResolve : unsigned int
	{
	};

	class _refl_ MUD_GFX_EXPORT BlockResolve : public GfxBlock
	{
	public:
		BlockResolve(GfxSystem& gfx_system, BlockCopy& copy);

		virtual void init_gfx_block() final;

		virtual void begin_gfx_block(Render& render) final;
		virtual void submit_gfx_block(Render& render) final;

		BlockCopy& m_copy;
	};

	class MUD_GFX_EXPORT PassEffects : public RenderPass
	{
	public:
		PassEffects(GfxSystem& gfx_system);

		virtual void begin_render_pass(Render& render) final;
		virtual void submit_render_pass(Render& render) final;
	};

	class MUD_GFX_EXPORT PassPostProcess : public RenderPass
	{
	public:
		PassPostProcess(GfxSystem& gfx_system, BlockCopy& copy);

		virtual void begin_render_pass(Render& render) final;
		virtual void submit_render_pass(Render& render) final;

		BlockCopy& m_copy;
	};
}
