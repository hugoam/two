#include <ecs/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_ecs)
{
    
    // Enums
    
    // Sequences
    
    // Arrays
    
    // Structs
    value_object<mud::Entity>("Entity")
        ;
    
    // Classes
    class_<mud::Complex>("Complex")
        .constructor<mud::Id, mud::Type&>()
        .constructor<mud::Id, mud::Type&, const std::vector<mud::Ref>&>()
        .property("id", &mud::Complex::id)
        .property("type", &mud::Complex::type)
        .property("prototype", &mud::Complex::prototype)
        .property("parts", &mud::Complex::parts)
        .function("setup", &mud::Complex::setup)
        .function("add_part", &mud::Complex::add_part)
        .function("has_part", &mud::Complex::has_part)
        .function("part", &mud::Complex::part)
        .function("try_part", &mud::Complex::try_part)
        ;
    class_<mud::Prototype>("Prototype")
        ;
    
    // Functions
    
}
