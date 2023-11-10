//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Cpp20.h>

#ifdef TWO_MODULES
module two.gfx;
#else
#include <stl/algorithm.h>
#include <gfx/Types.h>
#include <gfx/Effects.h>
#include <gfx/Filter.h>
#include <gfx/RenderTarget.h>
#include <gfx/GfxSystem.h>
#endif

namespace two
{
	void pass_resolve(GfxSystem& gfx, Render& render)
	{
		// process effects

		if(!render.m_is_mrt) return;
		
		// @todo three passes to resolve ? this is terrible :( but we can't read and write from the same buffer at the same time can we
		FrameBuffer& fbo = render.m_target->m_ping_pong.swap();
		gfx.m_copy->quad(render.composite_pass("resolve diffuse"), fbo, render.m_target->m_diffuse);
		gfx.m_copy->quad(render.composite_pass("resolve specular"), fbo, render.m_target->m_specular, BGFX_STATE_BLEND_ADD);

		gfx.m_copy->quad(render.composite_pass("resolve"), *render.m_fbo, render.m_target->m_ping_pong.last());
	}

	void pass_effects(GfxSystem& gfx, Render& render)
	{
		UNUSED(gfx); UNUSED(render);
		// submit ssao
		// submit ssr
		// submit sss
	}
}