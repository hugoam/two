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
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> MUD_JOBS_EXPORT Type& type<mud::JobSystem>();
    
    export_ template struct MUD_JOBS_EXPORT Typed<std::vector<mud::JobSystem*>>;
}
