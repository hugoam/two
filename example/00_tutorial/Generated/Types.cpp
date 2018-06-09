

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module .ex_00_tutorial;
#else
#include <00_tutorial/Types.h>
#include <00_tutorial/Refl/Module.h>
#include <proto/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> _00_TUTORIAL_EXPORT Type& type<ShapeType>() { static Type ty("ShapeType"); return ty; }
    
    template <> _00_TUTORIAL_EXPORT Type& type<MyObject>() { static Type ty("MyObject"); return ty; }
}
