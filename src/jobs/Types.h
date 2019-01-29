#pragma once

#include <jobs/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> MUD_JOBS_EXPORT Type& type<mud::JobSystem>();
    
    export_ template <> MUD_JOBS_EXPORT Type& type<vector<mud::JobSystem*>>();
}
