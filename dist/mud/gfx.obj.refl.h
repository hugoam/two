#pragma once

#include <mud/gfx.obj.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <gfx-obj/Types.h>

#ifndef MUD_GFX_OBJ_REFL_EXPORT
#define MUD_GFX_OBJ_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GFX_OBJ_REFL_EXPORT mud_gfx_obj : public mud::Module
	{
	private:
		mud_gfx_obj();
		
	public:
		static mud_gfx_obj& m() { static mud_gfx_obj instance; return instance; }
	};
}

#ifdef MUD_GFX_OBJ_MODULE
extern "C"
MUD_GFX_OBJ_REFL_EXPORT Module& getModule();
#endif


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	
}
