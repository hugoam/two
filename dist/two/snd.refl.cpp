#include <two/snd.refl.h>
#include <two/refl.h>
#include <two/infra.h>


#ifdef TWO_MODULES
module two.snd;
#else
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
