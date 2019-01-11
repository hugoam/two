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
        .property("type", &mud::Indexer::m_type)
        .property("objects", &mud::Indexer::m_objects)
        ;
    class_<mud::Ref>("Ref")
        ;
    class_<mud::Type>("Type")
        .property("id", &mud::Type::m_id)
        .property("name", &mud::Type::m_name)
        .property("size", &mud::Type::m_size)
        .property("base", &mud::Type::m_base)
        ;
    class_<mud::Var>("Var")
        ;
    
    // Functions
    function("indexed", &mud::indexed);
    
}
