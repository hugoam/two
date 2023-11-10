//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <ecs/Entity.h>
#endif
#include <gfx-pbr/Forward.h>

namespace two
{
	template <> struct TypedBuffer<Tonemap> { static uint32_t index() { return 0; } };
	template <> struct TypedBuffer<BCS> { static uint32_t index() { return 1; } };
	template <> struct TypedBuffer<Glow> { static uint32_t index() { return 2; } };
	template <> struct TypedBuffer<DofBlur> { static uint32_t index() { return 3; } };
}
