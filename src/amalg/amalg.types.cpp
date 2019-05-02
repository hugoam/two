#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.amalg;
#else
#include <amalg/Types.h>
#include <amalg/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
}
