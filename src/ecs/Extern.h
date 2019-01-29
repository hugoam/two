#pragma once

#include <stl/vector.h>
#include <stl/unordered_map.h>
#include <ecs/Api.h>

namespace mud
{
	export_ extern template class vector<Buffer*>;
	export_ extern template class vector<EntityData>;
	export_ extern template class vector<EntityStream>;
	export_ extern template class vector<unique<Buffer>>;
}
