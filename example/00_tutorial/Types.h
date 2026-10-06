#pragma once

#include <00_tutorial/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

namespace two
{
    // Exported types
    template <> _00_TUTORIAL_EXPORT Type& type<ShapeType>();
    
    template <> _00_TUTORIAL_EXPORT Type& type<MyObject>();
    
	export_ template struct _00_TUTORIAL_EXPORT Typed<std::vector<MyObject*>>;
}
