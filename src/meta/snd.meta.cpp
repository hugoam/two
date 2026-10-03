module;
#include <infra/Cpp20.h>
module two.snd.meta;

namespace two
{
	two_snd::two_snd()
		: Module("two::snd", { &two_type::m(), &two_math::m() })
	{}
}

#ifdef TWO_SND_MODULE
extern "C"
Module& getModule()
{
	return two_snd::m();
}
#endif
