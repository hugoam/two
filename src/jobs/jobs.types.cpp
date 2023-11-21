module;
#include <infra/Cpp20.h>
module two.jobs;

namespace two
{
    // Exported types
    
    
    template <> TWO_JOBS_EXPORT Type& type<two::JobSystem>() { static Type ty("JobSystem", sizeof(two::JobSystem)); return ty; }
}
