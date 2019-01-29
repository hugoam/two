#pragma once

#include <stl/vector.h>
#include <stl/unordered_map.h>
#include <uio/Api.h>

namespace tinystl
{
	using namespace mud;
	export_ extern template class vector<EditSpec>;
	export_ extern template class unordered_map<Module*, bool>;
}
