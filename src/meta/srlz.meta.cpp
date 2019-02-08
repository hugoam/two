#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.srlz;
#else
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/refl.meta.h>
#include <meta/srlz.meta.h>
#endif

namespace mud
{
	mud_srlz::mud_srlz()
		: Module("mud::srlz", { &mud_infra::m(), &mud_type::m(), &mud_refl::m() })
	{}
}

#ifdef MUD_SRLZ_MODULE
extern "C"
Module& getModule()
{
		return mud_srlz::m();
}
#endif
