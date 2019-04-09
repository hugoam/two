#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>
#include <pool/Forward.h>

#ifndef MUD_REFL_EXPORT
#define MUD_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum class ConstructorIndex : unsigned int;
    enum class TypeClass : unsigned int;
    
	struct QualType;
    class Param;
    class Signature;
    class Callable;
    class Function;
	struct Operator;
    class Method;
    class Constructor;
    class CopyConstructor;
    class Destructor;
    struct Call;
    class Meta;
    class Static;
    class Member;
	struct Alias;
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
	class Prototype;
}

#ifdef MUD_META_GENERATOR
#include <stl/span.h>
#include <stl/vector.h>
namespace stl
{
	export_ extern template struct refl_ span_ span<mud::Type*>;

	export_ extern template class refl_ seque_ vector<mud::Var>;
	export_ extern template class refl_ seque_ vector<void*>;

	export_ extern template class refl_ seque_ vector<mud::Module*>;
	export_ extern template class refl_ seque_ vector<mud::Type*>;
	export_ extern template class refl_ seque_ vector<mud::Alias*>;
	export_ extern template class refl_ seque_ vector<mud::Function*>;
}
#endif
