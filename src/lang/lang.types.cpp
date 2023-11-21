module;
#include <infra/Cpp20.h>
module two.lang;

namespace two
{
    // Exported types
    template <> TWO_LANG_EXPORT Type& type<two::Language>() { static Type ty("Language", sizeof(two::Language)); return ty; }
    
    
    template <> TWO_LANG_EXPORT Type& type<two::Script>() { static Type ty("Script", type<two::Callable>(), sizeof(two::Script)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::ScriptError>() { static Type ty("ScriptError", sizeof(two::ScriptError)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::TextScript>() { static Type ty("TextScript", type<two::Script>(), sizeof(two::TextScript)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::Interpreter>() { static Type ty("Interpreter", sizeof(two::Interpreter)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::ScriptClass>() { static Type ty("ScriptClass", sizeof(two::ScriptClass)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::LuaInterpreter>() { static Type ty("LuaInterpreter", type<two::Interpreter>(), sizeof(two::LuaInterpreter)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::StreamBranch>() { static Type ty("StreamBranch", sizeof(two::StreamBranch)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::Stream>() { static Type ty("Stream", type<two::StreamBranch>(), sizeof(two::Stream)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::Valve>() { static Type ty("Valve", sizeof(two::Valve)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::Pipe>() { static Type ty("Pipe", sizeof(two::Pipe)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::Process>() { static Type ty("Process", sizeof(two::Process)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::VisualScript>() { static Type ty("VisualScript", type<two::Script>(), sizeof(two::VisualScript)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::ProcessInput>() { static Type ty("ProcessInput", type<two::Process>(), sizeof(two::ProcessInput)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::ProcessOutput>() { static Type ty("ProcessOutput", type<two::Process>(), sizeof(two::ProcessOutput)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::ProcessValue>() { static Type ty("ProcessValue", type<two::Process>(), sizeof(two::ProcessValue)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::ProcessCreate>() { static Type ty("ProcessCreate", type<two::Process>(), sizeof(two::ProcessCreate)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::ProcessCallable>() { static Type ty("ProcessCallable", type<two::Process>(), sizeof(two::ProcessCallable)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::ProcessScript>() { static Type ty("ProcessScript", type<two::ProcessCallable>(), sizeof(two::ProcessScript)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::ProcessFunction>() { static Type ty("ProcessFunction", type<two::ProcessCallable>(), sizeof(two::ProcessFunction)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::ProcessMethod>() { static Type ty("ProcessMethod", type<two::ProcessCallable>(), sizeof(two::ProcessMethod)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::ProcessGetMember>() { static Type ty("ProcessGetMember", type<two::Process>(), sizeof(two::ProcessGetMember)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::ProcessSetMember>() { static Type ty("ProcessSetMember", type<two::Process>(), sizeof(two::ProcessSetMember)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::ProcessDisplay>() { static Type ty("ProcessDisplay", type<two::Process>(), sizeof(two::ProcessDisplay)); return ty; }
    template <> TWO_LANG_EXPORT Type& type<two::WrenInterpreter>() { static Type ty("WrenInterpreter", type<two::Interpreter>(), sizeof(two::WrenInterpreter)); return ty; }
}
