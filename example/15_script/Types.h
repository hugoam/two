#pragma once

#include <15_script/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

namespace two
{
    // Exported types
    
    template <> _15_SCRIPT_EXPORT Type& type<GameObject>();
    
	export_ template struct _15_SCRIPT_EXPORT Typed<std::vector<GameObject*>>;
}
