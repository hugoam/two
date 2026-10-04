module;
#include <infra/Cpp20.h>
module two.tree;

namespace two
{
    // Exported types
    
    
    template <> TWO_TREE_EXPORT Type& type<two::NodeKey>() { static Type ty("NodeKey", sizeof(two::NodeKey)); return ty; }
}
