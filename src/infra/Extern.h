#pragma once

#include <stl/vector.h>
#include <infra/Api.h>

using namespace mud;
namespace tinystl
{
	export_ extern template class vector<string>;
	export_ extern template class vector<uchar>;
}
