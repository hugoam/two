#pragma once

#include <stl/vector.h>
#include <infra/Api.h>

#ifdef USE_UVECTOR
#define vector uvector
#elif defined USE_BUFFER
#define vector buffer
#endif

namespace stl
{
	using namespace mud;
	export_ extern template class vector<string>;
	export_ extern template class vector<uchar>;
}
