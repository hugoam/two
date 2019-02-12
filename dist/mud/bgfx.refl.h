#pragma once

#include <mud/bgfx.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <bgfx/Types.h>

#ifndef MUD_BGFX_REFL_EXPORT
#define MUD_BGFX_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_BGFX_REFL_EXPORT mud_bgfx : public mud::Module
	{
	private:
		mud_bgfx();
		
	public:
		static mud_bgfx& m() { static mud_bgfx instance; return instance; }
	};
}

#ifdef MUD_BGFX_MODULE
extern "C"
MUD_BGFX_REFL_EXPORT Module& getModule();
#endif


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	
}
