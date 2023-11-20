#pragma once

#include <15_script/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> _15_SCRIPT_EXPORT Type& type<GameObject>();
    
	export_ template struct _15_SCRIPT_EXPORT Typed<std::vector<GameObject*>>;
}
