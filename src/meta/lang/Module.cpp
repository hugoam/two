#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.lang;
#else
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/pool/Module.h>
#include <meta/refl/Module.h>
#include <meta/lang/Module.h>
#include <meta/lang/Convert.h>
#endif

#include <lang/Api.h>
#define MUD_LANG_REFLECTION_IMPL
#include <meta/lang/Meta.h>

namespace mud
{
	mud_lang::mud_lang()
		: Module("mud::lang", { &mud_infra::m(), &mud_type::m(), &mud_pool::m(), &mud_refl::m() })
	{
		// setup reflection meta data
		mud_lang_meta(*this);
	}
}

#ifdef MUD_LANG_MODULE
extern "C"
Module& getModule()
{
		return mud_lang::m();
}
#endif
