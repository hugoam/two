#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>
#include <pool/Forward.h>

#ifndef TWO_REFL_EXPORT
#define TWO_REFL_EXPORT TWO_IMPORT
#endif

namespace two
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

#ifdef TWO_META_GENERATOR
#include <stl/span.h>
#include <stl/vector.h>
namespace stl
{
	export_ extern template struct refl_ span_ span<two::Type*>;

	export_ extern template class refl_ seque_ vector<two::Var>;
	export_ extern template class refl_ seque_ vector<void*>;

	export_ extern template class refl_ seque_ vector<two::Module*>;
	export_ extern template class refl_ seque_ vector<two::Type*>;
	export_ extern template class refl_ seque_ vector<two::Alias*>;
	export_ extern template class refl_ seque_ vector<two::Function*>;
}
#endif
