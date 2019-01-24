#pragma once

#include <mud/srlz.refl.h>
#include <mud/gfx.obj.h>
#include <mud/geom.refl.h>
#include <mud/gfx.obj.refl.h>
#include <mud/gfx.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.gfx-obj;
#else
#endif


namespace mud
{
	void mud_gfx_obj_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	}
}

namespace mud
{
	mud_gfx_obj::mud_gfx_obj()
		: Module("mud::gfx-obj", { &mud_infra::m(), &mud_type::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m(), &mud_gfx::m() })
	{
		// setup reflection meta data
		mud_gfx_obj_meta(*this);
	}
}

#ifdef MUD_GFX_OBJ_MODULE
extern "C"
Module& getModule()
{
		return mud_gfx_obj::m();
}
#endif
