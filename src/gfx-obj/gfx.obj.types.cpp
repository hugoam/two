#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-obj;
#else
#include <gfx-obj/Types.h>
#include <gfx-obj/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    
    
    template <> MUD_GFX_OBJ_EXPORT Type& type<mud::ImporterOBJ>() { static Type ty("ImporterOBJ", sizeof(mud::ImporterOBJ)); return ty; }
    template <> MUD_GFX_OBJ_EXPORT Type& type<mud::ImporterPLY>() { static Type ty("ImporterPLY", sizeof(mud::ImporterPLY)); return ty; }
}
