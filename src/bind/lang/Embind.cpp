#include <lang/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_lang)
{
    
    // Enums
    enum_<mud::Language>("mud::Language")
        .value("Cpp", mud::Language::Cpp)
        .value("Lua", mud::Language::Lua)
        .value("Wren", mud::Language::Wren)
        ;
    
    // Sequences
    
    // Arrays
    
    // Structs
    value_object<mud::ScriptError>("ScriptError")
        ;
    
    // Classes
    class_<mud::Interpreter>("Interpreter")
        ;
    class_<mud::Pipe>("Pipe")
        ;
    class_<mud::Process>("Process")
        .property("type", &mud::Process::m_type)
        ;
    class_<mud::ScriptClass>("ScriptClass")
        .constructor<const std::string&, const std::vector<mud::Type*>&>()
        .property("name", &mud::ScriptClass::m_name)
        .property("class_type", &mud::ScriptClass::m_class_type)
        .property("class", &mud::ScriptClass::m_class)
        ;
    class_<mud::StreamBranch>("StreamBranch")
        ;
    class_<mud::Valve>("Valve")
        ;
    class_<mud::LuaInterpreter>("LuaInterpreter")
        ;
    class_<mud::ProcessCallable>("ProcessCallable")
        .constructor<mud::VisualScript&, mud::Callable&>()
        ;
    class_<mud::ProcessCreate>("ProcessCreate")
        .constructor<mud::VisualScript&, mud::Type&, const mud::Constructor&>()
        ;
    class_<mud::ProcessDisplay>("ProcessDisplay")
        ;
    class_<mud::ProcessFunction>("ProcessFunction")
        .constructor<mud::VisualScript&, mud::Function&>()
        ;
    class_<mud::ProcessGetMember>("ProcessGetMember")
        .constructor<mud::VisualScript&, mud::Member&>()
        ;
    class_<mud::ProcessInput>("ProcessInput")
        ;
    class_<mud::ProcessMethod>("ProcessMethod")
        .constructor<mud::VisualScript&, mud::Method&>()
        ;
    class_<mud::ProcessOutput>("ProcessOutput")
        ;
    class_<mud::ProcessScript>("ProcessScript")
        .constructor<mud::VisualScript&, mud::VisualScript&>()
        ;
    class_<mud::ProcessSetMember>("ProcessSetMember")
        .constructor<mud::VisualScript&, mud::Member&>()
        ;
    class_<mud::ProcessValue>("ProcessValue")
        .constructor<mud::VisualScript&, const mud::Var&>()
        ;
    class_<mud::Script>("Script")
        .property("index", &mud::Script::m_index)
        .property("type", &mud::Script::m_type)
        .property("name", &mud::Script::m_name)
        .property("locked", &mud::Script::m_locked)
        ;
    class_<mud::Stream>("Stream")
        ;
    class_<mud::TextScript>("TextScript")
        .constructor<const char*, mud::Language, const mud::Signature&>()
        .property("language", &mud::TextScript::m_language)
        .property("script", &mud::TextScript::m_script)
        .property("dirty", &mud::TextScript::m_dirty)
        ;
    class_<mud::VisualScript>("VisualScript")
        .constructor<const char*, const mud::Signature&>()
        ;
    class_<mud::WrenInterpreter>("WrenInterpreter")
        ;
    
    // Functions
    
}
