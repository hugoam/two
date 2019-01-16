#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <fract/Forward.h>
#include <fract/Types.h>

#ifndef MUD_FRACT_REFL_EXPORT
#define MUD_FRACT_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_FRACT_REFL_EXPORT mud_fract : public Module
	{
	private:
		mud_fract();
		
	public:
		static mud_fract& m() { static mud_fract instance; return instance; }
	};
}

#ifdef MUD_FRACT_MODULE
extern "C"
MUD_FRACT_REFL_EXPORT Module& getModule();
#endif
