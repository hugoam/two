

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.proto;
#else
#include <proto/Types.h>
#include <proto/Api.h>
#include <obj/Vector.h>
//#include <proto/Proto.h>
#endif

namespace mud
{
    // Exported types
    
    template <> MUD_PROTO_EXPORT Type& type<mud::Complex>() { static Type ty("Complex"); return ty; }
    template <> MUD_PROTO_EXPORT Type& type<mud::Construct>() { static Type ty("Construct"); return ty; }
    template <> MUD_PROTO_EXPORT Type& type<mud::Prototype>() { static Type ty("Prototype"); return ty; }
}
