#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>

#ifndef MUD_POOL_EXPORT
#define MUD_POOL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	template <class T> class VecPool;
	template <class T> class TPool;

	template <class T> struct SparseHandle;
	template <class T> struct OwnedHandle;

	class HandlePool;
    class Pool;
    class ObjectPool;
}

#ifdef MUD_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
}
#endif
