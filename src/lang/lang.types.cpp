#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.lang;
#else
#include <lang/Types.h>
#include <lang/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_LANG_EXPORT Type& type<mud::Language>() { static Type ty("Language", sizeof(mud::Language)); return ty; }
    
    
    template <> MUD_LANG_EXPORT Type& type<mud::Interpreter>() { static Type ty("Interpreter", sizeof(mud::Interpreter)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Pipe>() { static Type ty("Pipe", sizeof(mud::Pipe)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Process>() { static Type ty("Process", sizeof(mud::Process)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ScriptClass>() { static Type ty("ScriptClass", sizeof(mud::ScriptClass)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ScriptError>() { static Type ty("ScriptError", sizeof(mud::ScriptError)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::StreamBranch>() { static Type ty("StreamBranch", sizeof(mud::StreamBranch)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Valve>() { static Type ty("Valve", sizeof(mud::Valve)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::LuaInterpreter>() { static Type ty("LuaInterpreter", type<mud::Interpreter>(), sizeof(mud::LuaInterpreter)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessCallable>() { static Type ty("ProcessCallable", type<mud::Process>(), sizeof(mud::ProcessCallable)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessCreate>() { static Type ty("ProcessCreate", type<mud::Process>(), sizeof(mud::ProcessCreate)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessDisplay>() { static Type ty("ProcessDisplay", type<mud::Process>(), sizeof(mud::ProcessDisplay)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessFunction>() { static Type ty("ProcessFunction", type<mud::ProcessCallable>(), sizeof(mud::ProcessFunction)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessGetMember>() { static Type ty("ProcessGetMember", type<mud::Process>(), sizeof(mud::ProcessGetMember)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessInput>() { static Type ty("ProcessInput", type<mud::Process>(), sizeof(mud::ProcessInput)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessMethod>() { static Type ty("ProcessMethod", type<mud::ProcessCallable>(), sizeof(mud::ProcessMethod)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessOutput>() { static Type ty("ProcessOutput", type<mud::Process>(), sizeof(mud::ProcessOutput)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessScript>() { static Type ty("ProcessScript", type<mud::ProcessCallable>(), sizeof(mud::ProcessScript)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessSetMember>() { static Type ty("ProcessSetMember", type<mud::Process>(), sizeof(mud::ProcessSetMember)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessValue>() { static Type ty("ProcessValue", type<mud::Process>(), sizeof(mud::ProcessValue)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Script>() { static Type ty("Script", type<mud::Callable>(), sizeof(mud::Script)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Stream>() { static Type ty("Stream", type<mud::StreamBranch>(), sizeof(mud::Stream)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::TextScript>() { static Type ty("TextScript", type<mud::Script>(), sizeof(mud::TextScript)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::VisualScript>() { static Type ty("VisualScript", type<mud::Script>(), sizeof(mud::VisualScript)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::WrenInterpreter>() { static Type ty("WrenInterpreter", type<mud::Interpreter>(), sizeof(mud::WrenInterpreter)); return ty; }
}
