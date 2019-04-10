#include <mud/srlz.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.refl.h>
#include <mud/refl.h>
#include <mud/infra.h>


#ifdef MUD_MODULES
module mud.srlz;
#else
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
