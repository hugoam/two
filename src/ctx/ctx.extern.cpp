#ifndef USE_STL
module two.ctx;

namespace stl
{
	using namespace two;
	template class TWO_CTX_EXPORT vector<EventBatch>;
	template class TWO_CTX_EXPORT vector<KeyEvent>;
	template class TWO_CTX_EXPORT vector<MouseEvent>;
	template class TWO_CTX_EXPORT unordered_map<int, InputEvent*>;
}
#endif
