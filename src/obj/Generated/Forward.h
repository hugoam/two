

#pragma once

#include <obj/Config.h>


#if defined MUD_OBJ_LIB
#define MUD_OBJ_EXPORT MUD_EXPORT
#else
#define MUD_OBJ_EXPORT MUD_IMPORT
#endif


    
    

namespace mud {

    enum class TypeKind : unsigned int;
    enum VarMode : unsigned int;
    enum class ConstructorIndex : unsigned int;
    enum class TypeClass : unsigned int;
    
    template <class T> struct array;
    
    class Module;
    class ModuleLoader;
    class Namespace;
    class System;
    struct Address;
    class Type;
    struct ProtoPart;
    class Prototype;
    class Ref;
    class None;
    class Any;
    class Val;
    class Var;
    struct swallow;
    class Complex;
    class Construct;
    class NonCopy;
    class Movabl;
    class Indexer;
    class Index;
    struct strung;
    class NodeState;
    class Iterable;
    class Sequence;
    class Pool;
    class ObjectPool;
    class GlobalPool;
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
    class DoubleDispatch;
    class Convert;
    class TypeConverter;
    class Enum;
    class Injector;
    class Creator;
    struct Filepath;
    struct Time;
    struct TimeSpan;
    class Clock;
    class Updatable;
}

