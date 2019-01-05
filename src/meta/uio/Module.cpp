#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <meta/uio/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/uio/Convert.h>
#endif
#define MUD_UIO_REFLECTION_IMPL
#include <meta/uio/Meta.h>

namespace mud
{
	mud_uio::mud_uio()
		: Module("mud::uio", { &mud_infra::m(), &mud_tree::m(), &mud_type::m(), &mud_ecs::m(), &mud_pool::m(), 
							   &mud_refl::m(), &mud_math::m(), &mud_lang::m(), &mud_ctx::m(), &mud_ui::m() })
	{
        // setup reflection meta data
		mud_uio_meta(*this);
	}
}

#ifdef MUD_UIO_MODULE
extern "C"
Module& getModule()
{
	return mud_uio::m();
}
#endif
