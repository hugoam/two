#include <two/infra.h>

module;
module two.srlz.meta;

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
