#pragma once

#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/bgfx.h>
#include <mud/ctx.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/type.h>
#include <mud/bgfx.refl.h>

#ifdef MUD_MODULES
module mud.bgfx;
#else
#endif


namespace mud
{
	void mud_bgfx_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	}
}

namespace mud
{
	mud_bgfx::mud_bgfx()
		: Module("mud::bgfx", { &mud_infra::m(), &mud_type::m(), &mud_math::m(), &mud_ctx::m() })
	{
		// setup reflection meta data
		mud_bgfx_meta(*this);
	}
}

#ifdef MUD_BGFX_MODULE
extern "C"
Module& getModule()
{
		return mud_bgfx::m();
}
#endif
