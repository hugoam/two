#pragma once

#include <infra/Config.h>

#ifndef TWO_TYPE_EXPORT
#define TWO_TYPE_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ enum class VarMode : unsigned int;
    
    export_ struct Address;
    export_ class Type;
    export_ class Ref;
    export_ class None;
    export_ class Any;
    export_ class Var;
    export_ class DoubleDispatch;
    export_ class Indexer;
    export_ class Index;
	export_ class Prototype;
}

#ifdef TWO_META_GENERATOR
#include <stl/string.h>
#include <stl/vector.h>
namespace stl
{
	extern template class refl_ seque_ vector<string>;
	extern template class refl_ seque_ vector<two::Ref>;
}
#endif
