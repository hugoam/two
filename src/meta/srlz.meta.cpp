#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.srlz;
#else
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/refl.meta.h>
#include <meta/srlz.meta.h>
#endif

namespace two
{
	two_srlz::two_srlz()
		: Module("two::srlz", { &two_infra::m(), &two_type::m(), &two_refl::m() })
	{}
}

#ifdef TWO_SRLZ_MODULE
extern "C"
Module& getModule()
{
	return two_srlz::m();
}
#endif
