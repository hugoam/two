#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.proto;
#else
#include <meta/proto/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/proto/Convert.h>
#endif
#define MUD_PROTO_REFLECTION_IMPL
#include <meta/proto/Meta.h>

namespace mud
{
	mud_proto::mud_proto()
		: Module("mud::proto")
	{
        // ensure dependencies are instantiated
        mud_infra::m();
        mud_obj::m();
        mud_refl::m();

        // setup reflection meta data
		mud_proto_meta(*this);
	}
}

#ifdef MUD_PROTO_MODULE
extern "C"
Module& getModule()
{
	return mud_proto::m();
}
#endif
