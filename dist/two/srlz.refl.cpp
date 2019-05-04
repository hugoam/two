#include <two/srlz.refl.h>
#include <two/infra.refl.h>
#include <two/type.refl.h>
#include <two/refl.refl.h>
#include <two/refl.h>
#include <two/infra.h>


#ifdef TWO_MODULES
module two.srlz;
#else
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
