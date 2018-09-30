
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/tree/Module.h>
#include <meta/obj/Module.h>
#include <meta/ecs/Module.h>
#include <meta/pool/Module.h>
#include <meta/refl/Module.h>
#include <meta/math/Module.h>
#include <meta/lang/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#endif
        
#include <uio/Forward.h>
#include <uio/Types.h>
#include <uio/Api.h>

#include <meta/uio/Convert.h>

#ifndef MUD_UIO_REFL_EXPORT
#define MUD_UIO_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_UIO_REFL_EXPORT mud_uio : public Module
	{
	private:
		mud_uio();

	public:
		static mud_uio& m() { static mud_uio instance; return instance; }
	};
}

#ifdef MUD_UIO_MODULE
extern "C"
MUD_UIO_REFL_EXPORT Module& getModule();
#endif
