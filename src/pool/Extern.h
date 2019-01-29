#pragma once

#include <stl/vector.h>
#include <stl/unordered_map.h>
#include <pool/Api.h>

using namespace mud;
namespace tinystl
{
	export_ extern template class vector<unique<Pool>>;
}
