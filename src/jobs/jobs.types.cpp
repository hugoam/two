#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.jobs;
#else
#include <jobs/Types.h>
#include <jobs/Api.h>
#include <type/Vector.h>
#endif

namespace two
{
    // Exported types
    
    
    template <> TWO_JOBS_EXPORT Type& type<two::JobSystem>() { static Type ty("JobSystem", sizeof(two::JobSystem)); return ty; }
}
