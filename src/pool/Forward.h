#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>

#ifndef TWO_POOL_EXPORT
#define TWO_POOL_EXPORT TWO_IMPORT
#endif

namespace two
{
	template <class T> class VecPool;
	template <class T> class TPool;

	template <class T> struct SparseHandle;
	template <class T> struct OwnedHandle;

	class HandlePool;
    class Pool;
    class ObjectPool;
}

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
}
#endif
