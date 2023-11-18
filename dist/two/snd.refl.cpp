#include <two/snd.refl.h>
#include <two/refl.h>
#include <two/infra.h>


module two.snd;

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
