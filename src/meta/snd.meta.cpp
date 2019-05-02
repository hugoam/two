#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.snd;
#else
#include <refl/Module.h>
#include <meta/snd.meta.h>
#endif

namespace two
{
	two_snd::two_snd()
		: Module("two::snd", {  })
	{}
}

#ifdef TWO_SND_MODULE
extern "C"
Module& getModule()
{
	return two_snd::m();
}
#endif
