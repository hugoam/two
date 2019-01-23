#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>

#ifndef MUD_ECS_EXPORT
#define MUD_ECS_EXPORT MUD_IMPORT
#endif

namespace mud
{
    class Prototype;
	struct Entity;
	class ECS;
	class GridECS;
	class Complex;
}
