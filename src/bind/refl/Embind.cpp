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
        .field("arguments", &mud::Call::arguments)
        .field("result", &mud::Call::result)
        ;
    value_object<mud::Operator>("Operator")
        .field("function", &mud::Operator::function)
        .field("type", &mud::Operator::type)
        .field("name", &mud::Operator::name)
        .field("sign", &mud::Operator::sign)
        ;
    
    // Classes
    class_<mud::Callable>("Callable")
        ;
    class_<mud::Class>("Class")
        ;
    class_<mud::Convert>("Convert")
        ;
    class_<mud::Creator>("Creator")
        .property("type", &mud::Creator::type)
        .property("construct", &mud::Creator::construct)
        .property("prototype", &mud::Creator::prototype)
        .property("injector", &mud::Creator::injector, &mud::Creator::setInjector)
        ;
    class_<mud::Enum>("Enum")
        ;
    class_<mud::Member>("Member")
        ;
    class_<mud::Meta>("Meta")
        ;
    class_<mud::Module>("Module")
        .property("name", &mud::Module::name)
        .property("deps", &mud::Module::deps)
        .property("types", &mud::Module::types)
        .property("functions", &mud::Module::functions)
        .property("path", &mud::Module::path)
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
        .property("modules", &mud::System::modules)
        .property("types", &mud::System::types)
        .property("functions", &mud::System::functions)
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
