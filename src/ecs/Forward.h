#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>

#ifndef MUD_ECS_EXPORT
#define MUD_ECS_EXPORT MUD_IMPORT
#endif

namespace mud
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

#ifdef MUD_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
}
#endif
