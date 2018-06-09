

#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>

#ifndef MUD_OBJ_EXPORT
#define MUD_OBJ_EXPORT MUD_IMPORT
#endif


    
    

namespace mud {

    enum class TypeKind : unsigned int;
    enum VarMode : unsigned int;
    
    
    struct Address;
    class Type;
    class Ref;
    class None;
    class Any;
    class Val;
    class Var;
    class DoubleDispatch;
    class Indexer;
    class Index;
}

