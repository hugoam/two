#ifndef USE_STL
module two.ctx;

namespace stl
{
	using namespace two;
	template class TWO_CTX_EXPORT vector<EventDispatcher::Received>;
	template class TWO_CTX_EXPORT vector<KeyEvent>;
	template class TWO_CTX_EXPORT vector<MouseEvent>;
}
#endif
