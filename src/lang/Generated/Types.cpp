

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.lang;
#else
#include <lang/Generated/Types.h>
#include <lang/Generated/Module.h>
#include <obj/Proto.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_LANG_EXPORT Type& type<mud::Process::State>() { static Type ty("mud::Process::State"); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::StreamModifier>() { static Type ty("mud::StreamModifier"); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ValveKind>() { static Type ty("mud::ValveKind"); return ty; }
    
    template <> MUD_LANG_EXPORT Type& type<mud::LuaInterpreter>() { static Type ty("LuaInterpreter"); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Pipe>() { static Type ty("Pipe"); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Process>() { static Type ty("Process"); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::StreamBranch>() { static Type ty("StreamBranch"); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Valve>() { static Type ty("Valve"); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Script>() { static Type ty("Script", type<mud::Callable>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::LuaScript>() { static Type ty("LuaScript", type<mud::Script>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::VisualScript>() { static Type ty("VisualScript", type<mud::Script>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessFunction>() { static Type ty("ProcessFunction", type<mud::ProcessCallable>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessMethod>() { static Type ty("ProcessMethod", type<mud::ProcessCallable>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessScript>() { static Type ty("ProcessScript", type<mud::ProcessCallable>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessCallable>() { static Type ty("ProcessCallable", type<mud::Process>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessCreate>() { static Type ty("ProcessCreate", type<mud::Process>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessDisplay>() { static Type ty("ProcessDisplay", type<mud::Process>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessGetMember>() { static Type ty("ProcessGetMember", type<mud::Process>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessSetMember>() { static Type ty("ProcessSetMember", type<mud::Process>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessValue>() { static Type ty("ProcessValue", type<mud::Process>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessInput>() { static Type ty("ProcessInput", type<mud::Process>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessOutput>() { static Type ty("ProcessOutput", type<mud::Process>()); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Stream>() { static Type ty("Stream", type<mud::StreamBranch>()); return ty; }
}
