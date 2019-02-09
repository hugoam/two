#pragma once

#include <infra/Config.h>
#include <stl/base.h>

#ifndef MUD_INFRA_EXPORT
#define MUD_INFRA_EXPORT MUD_IMPORT
#endif

#ifdef USE_STL
#include <cstddef>
namespace stl
{
	template <class T> struct span;
	template <class T, size_t Size> struct array;
}
#else
#include <stl/decls.h>
#endif

namespace mud
{
	using stl::array;
	using stl::span;

    struct Filepath;
    struct swallow;
    class NonCopy;
    class Movabl;
}

#ifdef MUD_META_GENERATOR // #ifdef MUD_META_GENERATOR
#include <stl/decls.h>
namespace stl
{
}
#endif
