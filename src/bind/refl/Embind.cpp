#include <refl/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_refl)
{
    
    // Enums
    enum_<mud::TypeClass>("mud::TypeClass")
        .value("None", mud::TypeClass::None)
        .value("Object", mud::TypeClass::Object)
        .value("Struct", mud::TypeClass::Struct)
        .value("Sequence", mud::TypeClass::Sequence)
        .value("BaseType", mud::TypeClass::BaseType)
        .value("Enum", mud::TypeClass::Enum)
        ;
    
    // Sequences
    
    // Arrays
    
    // Structs
    value_object<mud::Call>("Call")
        .field("arguments", &mud::Call::m_arguments)
        .field("result", &mud::Call::m_result)
        ;
    value_object<mud::Operator>("Operator")
        .field("function", &mud::Operator::m_function)
        .field("type", &mud::Operator::m_type)
        .field("name", &mud::Operator::m_name)
        .field("sign", &mud::Operator::m_sign)
        ;
    
    // Classes
    class_<mud::Callable>("Callable")
        ;
    class_<mud::Class>("Class")
        ;
    class_<mud::Convert>("Convert")
        ;
    class_<mud::Creator>("Creator")
        .property("type", &mud::Creator::m_type)
        .property("construct", &mud::Creator::m_construct)
        .property("prototype", &mud::Creator::m_prototype)
        .property("injector", &mud::Creator::injector, &mud::Creator::setInjector)
        ;
    class_<mud::Enum>("Enum")
        ;
    class_<mud::Member>("Member")
        ;
    class_<mud::Meta>("Meta")
        ;
    class_<mud::Module>("Module")
        .property("name", &mud::Module::m_name)
        .property("deps", &mud::Module::m_deps)
        .property("types", &mud::Module::m_types)
        .property("functions", &mud::Module::m_functions)
        .property("path", &mud::Module::m_path)
        ;
    class_<mud::Namespace>("Namespace")
        ;
    class_<mud::Param>("Param")
        ;
    class_<mud::Signature>("Signature")
        ;
    class_<mud::Static>("Static")
        ;
    class_<mud::System>("System")
        .property("modules", &mud::System::m_modules)
        .property("types", &mud::System::m_types)
        .property("functions", &mud::System::m_functions)
        ;
    class_<mud::Constructor>("Constructor")
        ;
    class_<mud::CopyConstructor>("CopyConstructor")
        ;
    class_<mud::Destructor>("Destructor")
        ;
    class_<mud::Function>("Function")
        ;
    class_<mud::Injector>("Injector")
        ;
    class_<mud::Method>("Method")
        ;
    
    // Functions
    function("system", &mud::system);
    
}
