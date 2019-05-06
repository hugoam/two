#ifndef USE_STL
#ifdef TWO_MODULES
module two.ctx;
#else
#include <stl/vector.hpp>
#include <stl/unordered_set.hpp>
#include <stl/unordered_map.hpp>
#include <ctx/Api.h>
#endif

namespace stl
{
	using namespace two;
	template class TWO_CTX_EXPORT vector<EventBatch>;
	template class TWO_CTX_EXPORT vector<KeyEvent>;
	template class TWO_CTX_EXPORT vector<MouseEvent>;
	template class TWO_CTX_EXPORT unordered_map<int, InputEvent*>;
}
#endif
