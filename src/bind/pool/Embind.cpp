#include <pool/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_pool)
{
    
    // Enums
    
    // Sequences
    
    // Arrays
    
    // Structs
    
    // Classes
    class_<mud::HandlePool>("HandlePool")
        ;
    class_<mud::Pool>("Pool")
        ;
    
    // Functions
    
}
