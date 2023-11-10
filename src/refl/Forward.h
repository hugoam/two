#pragma once

#include <infra/Config.h>

#ifndef TWO_MODULES
#include <infra/Forward.h>
#include <type/Forward.h>
#include <pool/Forward.h>
#endif

#ifndef TWO_REFL_EXPORT
#define TWO_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ enum class ConstructorIndex : unsigned int;
    export_ enum class TypeClass : unsigned int;
    
	export_ struct QualType;
    export_ class Param;
    export_ class Signature;
    export_ class Callable;
    export_ class Function;
	export_ struct Operator;
    export_ class Method;
    export_ class Constructor;
    export_ class CopyConstructor;
    export_ class Destructor;
    export_ struct Call;
    export_ class Meta;
    export_ class Static;
    export_ class Member;
	export_ struct Alias;
    export_ class Class;
    export_ class Convert;
    export_ class TypeConverter;
    export_ class Enum;
    export_ class Injector;
    export_ class Creator;
    export_ class Iterable;
    export_ class Sequence;
    export_ class Namespace;
    export_ class Module;
    export_ class System;
}

#ifdef TWO_META_GENERATOR
#include <stl/span.h>
#include <stl/vector.h>
namespace stl
{
	extern template struct refl_ span_ span<two::Type*>;

	extern template class refl_ seque_ vector<two::Var>;
	extern template class refl_ seque_ vector<void*>;

	extern template class refl_ seque_ vector<two::Module*>;
	extern template class refl_ seque_ vector<two::Type*>;
	extern template class refl_ seque_ vector<two::Alias*>;
	extern template class refl_ seque_ vector<two::Function*>;
}
#endif
