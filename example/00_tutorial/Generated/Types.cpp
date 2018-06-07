

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module .ex_00_tutorial;
#else
#include <00_tutorial/Generated/Types.h>
#include <00_tutorial/Generated/Module.h>
#include <obj/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> _00_TUTORIAL_EXPORT Type& type<ShapeType>() { static Type ty("ShapeType"); return ty; }
    
    template <> _00_TUTORIAL_EXPORT Type& type<MyObject>() { static Type ty("MyObject"); return ty; }
}
