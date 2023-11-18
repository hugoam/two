#include <two/infra.refl.h>
#include <two/refl.h>
#include <two/infra.h>


module two.infra;

namespace two
{
	two_infra::two_infra()
		: Module("two::infra", {  })
	{}
}

#ifdef TWO_INFRA_MODULE
extern "C"
Module& getModule()
{
	return two_infra::m();
}
#endif
