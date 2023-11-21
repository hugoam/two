#ifndef USE_STL
module two.snd;

namespace stl
{
	using namespace two;
	template class TWO_SND_EXPORT vector<unique<Sound>>;
	template class TWO_SND_EXPORT unordered_map<string, unique<SharedBuffer>>;
}
#endif
