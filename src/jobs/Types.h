#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <jobs/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#endif


namespace mud
{
    // Exported types
    
    
    export_ template <> MUD_JOBS_EXPORT Type& type<mud::JobSystem>();
}
