#pragma once

#include <lang/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <obj/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <obj/Types.h>
#include <pool/Types.h>
#include <refl/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_LANG_EXPORT Type& type<mud::StreamModifier>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ValveKind>();
    
    export_ template <> MUD_LANG_EXPORT Type& type<mud::LuaInterpreter>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Pipe>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Process>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::StreamBranch>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Valve>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Script>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessFunction>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessMethod>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessScript>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::LuaScript>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::VisualScript>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessCallable>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessCreate>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessDisplay>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessGetMember>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessSetMember>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessValue>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessInput>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::ProcessOutput>();
    export_ template <> MUD_LANG_EXPORT Type& type<mud::Stream>();
    
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::LuaInterpreter*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::Pipe*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::Process*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::StreamBranch*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::Valve*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::Script*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::ProcessFunction*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::ProcessMethod*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::ProcessScript*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::LuaScript*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::VisualScript*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::ProcessCallable*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::ProcessCreate*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::ProcessDisplay*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::ProcessGetMember*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::ProcessSetMember*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::ProcessValue*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::ProcessInput*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::ProcessOutput*>>;
	export_ template struct MUD_LANG_EXPORT Typed<std::vector<mud::Stream*>>;
}
