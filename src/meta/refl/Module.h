
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/obj/Module.h>
#include <meta/pool/Module.h>
#endif
        
#include <refl/Forward.h>
#include <refl/Types.h>
#include <refl/Api.h>

#include <meta/refl/Convert.h>

#ifndef MUD_REFL_REFL_EXPORT
#define MUD_REFL_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_REFL_REFL_EXPORT mudrefl : public Module
	{
	private:
		mudrefl();

	public:
		static mudrefl& m() { static mudrefl instance; return instance; }
	};
}

#ifdef MUD_REFL_MODULE
extern "C"
MUD_REFL_REFL_EXPORT Module& getModule();
#endif
