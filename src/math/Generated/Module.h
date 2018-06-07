
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/System/System.h>
#endif

#ifndef MUD_MODULES
#include <obj/Generated/Module.h>
#include <srlz/Generated/Module.h>
#endif
        
#include <math/Generated/Forward.h>
#include <math/Generated/Types.h>
#include <math/Api.h>

#include <math/Generated/Convert.h>

namespace mud
{
	export_ class MUD_MATH_EXPORT mudmath : public Module
	{
	private:
		mudmath();

	public:
		static mudmath& m() { static mudmath instance; return instance; }
	};
}

#ifdef MUD_MATH_MODULE
extern "C"
MUD_MATH_EXPORT Module& getModule();
#endif
