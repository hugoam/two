#ifndef USE_STL
module two.ecs;

namespace stl
{
	using namespace two;
	template class TWO_ECS_EXPORT vector<Buffer*>;
	template class TWO_ECS_EXPORT vector<EntityStream*>;
	template class TWO_ECS_EXPORT vector<EntityStream>;
	template class TWO_ECS_EXPORT vector<unique<Buffer>>;
}
#endif
