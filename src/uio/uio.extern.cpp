#ifndef USE_STL
module two.uio;

namespace stl
{
	using namespace two;
	template class TWO_UIO_EXPORT vector<EditSpec>;
	template class TWO_UIO_EXPORT unordered_map<Module*, bool>;
	template class TWO_UIO_EXPORT unordered_map<const Type*, Colour>;
}
#endif
