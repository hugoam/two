#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.jobs;
#else
#include <jobs/Types.h>
#include <jobs/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    
    template <> MUD_JOBS_EXPORT Type& type<mud::JobSystem>() { static Type ty("JobSystem"); return ty; }
}
