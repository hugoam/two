#pragma once

#include <infra/Config.h>

#ifndef TWO_MODULES
#include <infra/Forward.h>
#include <type/Forward.h>
#endif

#ifndef TWO_POOL_EXPORT
#define TWO_POOL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ template <class T> class VecPool;
	export_ template <class T> class TPool;

	export_ template <class T> struct SparseHandle;
	export_ template <class T> struct OwnedHandle;

	export_ class HandlePool;
    export_ class Pool;
    export_ class ObjectPool;
}

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
}
#endif
