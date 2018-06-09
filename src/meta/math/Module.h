
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/obj/Module.h>
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
	export_ class MUD_MATH_REFL_EXPORT mudmath : public Module
	{
	private:
		mudmath();

	public:
		static mudmath& m() { static mudmath instance; return instance; }
	};
}

#ifdef MUD_MATH_MODULE
extern "C"
MUD_MATH_REFL_EXPORT Module& getModule();
#endif
