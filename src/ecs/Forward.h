#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>

#ifndef TWO_ECS_EXPORT
#define TWO_ECS_EXPORT TWO_IMPORT
#endif

namespace two
{
	template <class T> struct ComponentHandle;
	template <class T> struct EntityHandle;

    class Prototype;
	struct Entity;
	struct Entt;
	class OEntt;
	class ECS;
	class GridECS;
	class Complex;
}

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
}
#endif
