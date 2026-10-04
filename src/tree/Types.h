#pragma once

#include <tree/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    
    
    template <> TWO_TREE_EXPORT Type& type<two::NodeKey>();
}
