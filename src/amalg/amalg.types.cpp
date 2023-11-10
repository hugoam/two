#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.amalg;
#else
#include <amalg/Types.h>
#include <amalg/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
}
