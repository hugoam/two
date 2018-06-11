
#pragma once

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/obj/Module.h>
#include <meta/refl/Module.h>
#endif
        
#include <proto/Forward.h>
#include <proto/Types.h>
#include <proto/Api.h>

#include <meta/proto/Convert.h>

#ifndef MUD_PROTO_REFL_EXPORT
#define MUD_PROTO_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_PROTO_REFL_EXPORT mud_proto : public Module
	{
	private:
		mud_proto();

	public:
		static mud_proto& m() { static mud_proto instance; return instance; }
	};
}

#ifdef MUD_PROTO_MODULE
extern "C"
MUD_PROTO_REFL_EXPORT Module& getModule();
#endif
