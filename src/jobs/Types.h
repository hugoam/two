#pragma once

#include <jobs/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    
    
    template <> TWO_JOBS_EXPORT Type& type<two::JobSystem>();
}
