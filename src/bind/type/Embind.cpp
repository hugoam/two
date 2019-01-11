#include <type/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_type)
{
    
    // Enums
    
    // Sequences
    
    // Arrays
    
    // Structs
    
    // Classes
    class_<mud::Index>("Index")
        .function("indexer", &mud::Index::indexer)
        .class_property("me", &mud::Index::me)
        ;
    class_<mud::Indexer>("Indexer")
        .property("type", &mud::Indexer::type)
        .property("objects", &mud::Indexer::objects)
        ;
    class_<mud::Ref>("Ref")
        ;
    class_<mud::Type>("Type")
        .property("id", &mud::Type::id)
        .property("name", &mud::Type::name)
        .property("size", &mud::Type::size)
        .property("base", &mud::Type::base)
        ;
    class_<mud::Var>("Var")
        ;
    
    // Functions
    function("indexed", &mud::indexed);
    
}
