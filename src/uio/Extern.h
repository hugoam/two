#pragma once

#include <stl/vector.h>
#include <stl/unordered_map.h>
#include <uio/Api.h>

#ifdef USE_UVECTOR
#define vector uvector
#elif defined USE_BUFFER
#define vector buffer
#endif

namespace stl
{
	using namespace mud;
	export_ extern template class vector<EditSpec>;
	export_ extern template class unordered_map<Module*, bool>;
}
