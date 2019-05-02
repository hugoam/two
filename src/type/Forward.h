#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>

#ifndef TWO_TYPE_EXPORT
#define TWO_TYPE_EXPORT TWO_IMPORT
#endif

namespace two
{
    enum VarMode : unsigned int;
    
    struct Address;
    class Type;
    class Ref;
    class None;
    class Any;
    class Var;
    class DoubleDispatch;
    class Indexer;
    class Index;
	class Prototype;
}

#ifdef TWO_META_GENERATOR
#include <stl/string.h>
#include <stl/vector.h>
namespace stl
{
	export_ extern template class refl_ seque_ vector<string>;
	export_ extern template class refl_ seque_ vector<two::Ref>;
}
#endif
