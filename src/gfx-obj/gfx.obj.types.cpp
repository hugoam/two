module;
#include <infra/Cpp20.h>
module two.gfx.obj;

namespace two
{
    // Exported types
    
    
    template <> TWO_GFX_OBJ_EXPORT Type& type<two::ImporterOBJ>() { static Type ty("ImporterOBJ", sizeof(two::ImporterOBJ)); return ty; }
    template <> TWO_GFX_OBJ_EXPORT Type& type<two::ImporterPLY>() { static Type ty("ImporterPLY", sizeof(two::ImporterPLY)); return ty; }
}
