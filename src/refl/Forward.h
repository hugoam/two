

#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <obj/Forward.h>
#include <pool/Forward.h>

#ifndef MUD_REFL_EXPORT
#define MUD_REFL_EXPORT MUD_IMPORT
#endif


    
    

namespace mud {

    enum class ConstructorIndex : unsigned int;
    enum class TypeClass : unsigned int;
    
    
    class Param;
    class Signature;
    class Callable;
    class Function;
    class Method;
    class Constructor;
    class CopyConstructor;
    class Destructor;
    struct Call;
    class Meta;
    class Static;
    class Member;
    class Class;
    class Convert;
    class TypeConverter;
    class Enum;
    class Injector;
    class Creator;
    class Iterable;
    class Sequence;
    class Namespace;
    class Module;
    class System;
}

