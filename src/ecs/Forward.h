#pragma once

#include <infra/Config.h>

#ifndef TWO_MODULES
#include <infra/Forward.h>
#include <type/Forward.h>
#endif

#ifndef TWO_ECS_EXPORT
#define TWO_ECS_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ template <class T> struct ComponentHandle;
	export_ template <class T> struct EntityHandle;

	export_ struct Entity;
	export_ struct Entt;
	export_ class OEntt;
	export_ class ECS;
	export_ class GridECS;
	export_ class Complex;
}

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
}
#endif
