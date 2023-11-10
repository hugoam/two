
#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.jobs; 
#else
#include <infra/Config.h>
#include <jobs/Job.h>
#endif

namespace two
{
}
