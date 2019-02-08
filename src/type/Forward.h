#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>

#ifndef MUD_TYPE_EXPORT
#define MUD_TYPE_EXPORT MUD_IMPORT
#endif

namespace mud
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

#ifdef MUD_META_GENERATOR
#include <stl/string.h>
#include <stl/vector.h>
namespace stl
{
	export_ extern template class refl_ seque_ vector<string>;
	export_ extern template class refl_ seque_ vector<mud::Ref>;
}
#endif
