#pragma once

#include <infra/Config.h>
#ifndef TWO_MODULES
#include <stl/base.h>
#endif

#ifndef TWO_INFRA_EXPORT
#define TWO_INFRA_EXPORT TWO_IMPORT
#endif

#ifdef USE_STL
#ifndef TWO_MODULES
#include <cstddef>
#endif
namespace stl
{
	template <class T> struct span;
	template <class T, size_t Size> struct array;
}
#else
#include <stl/decls.h>
#endif

namespace two
{
	using stl::array;
	using stl::span;

    export_ struct Filepath;
    export_ struct swallow;
}

#ifdef TWO_META_GENERATOR // #ifdef TWO_META_GENERATOR
#include <stl/decls.h>
namespace stl
{
}
#endif
