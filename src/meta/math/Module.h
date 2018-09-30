
#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/refl/Module.h>
#include <meta/srlz/Module.h>
#endif
        
#include <math/Forward.h>
#include <math/Types.h>
#include <math/Api.h>

#include <meta/math/Convert.h>

#ifndef MUD_MATH_REFL_EXPORT
#define MUD_MATH_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_MATH_REFL_EXPORT mud_math : public Module
	{
	private:
		mud_math();

	public:
		static mud_math& m() { static mud_math instance; return instance; }
	};
}

#ifdef MUD_MATH_MODULE
extern "C"
MUD_MATH_REFL_EXPORT Module& getModule();
#endif
