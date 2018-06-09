
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/obj/Module.h>
#endif
        
#include <pool/Forward.h>
#include <pool/Types.h>
#include <pool/Api.h>

#include <meta/pool/Convert.h>

#ifndef MUD_POOL_REFL_EXPORT
#define MUD_POOL_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_POOL_REFL_EXPORT mudpool : public Module
	{
	private:
		mudpool();

	public:
		static mudpool& m() { static mudpool instance; return instance; }
	};
}

#ifdef MUD_POOL_MODULE
extern "C"
MUD_POOL_REFL_EXPORT Module& getModule();
#endif
