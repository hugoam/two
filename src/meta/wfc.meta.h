#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <wfc/Forward.h>
//#include <wfc/Types.h>

#ifndef MUD_WFC_REFL_EXPORT
#define MUD_WFC_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_WFC_REFL_EXPORT mud_wfc : public mud::Module
	{
	private:
		mud_wfc();
		
	public:
		static mud_wfc& m() { static mud_wfc instance; return instance; }
	};
}

#ifdef MUD_WFC_MODULE
extern "C"
MUD_WFC_REFL_EXPORT Module& getModule();
#endif
