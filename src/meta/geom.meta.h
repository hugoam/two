#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <geom/Forward.h>
//#include <geom/Types.h>

#ifndef MUD_GEOM_REFL_EXPORT
#define MUD_GEOM_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_GEOM_REFL_EXPORT mud_geom : public mud::Module
	{
	private:
		mud_geom();
		
	public:
		static mud_geom& m() { static mud_geom instance; return instance; }
	};
}

#ifdef MUD_GEOM_MODULE
extern "C"
MUD_GEOM_REFL_EXPORT Module& getModule();
#endif
