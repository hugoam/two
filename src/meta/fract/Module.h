
#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#endif
        
#include <fract/Forward.h>
#include <fract/Types.h>
#include <fract/Api.h>

#include <meta/fract/Convert.h>

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
