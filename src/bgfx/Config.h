//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Config.h>

#if defined MUD_BGFX_LIB || defined MUD_GFX_LIB
#define MUD_BGFX_EXPORT MUD_EXPORT
#else
#define MUD_BGFX_EXPORT MUD_IMPORT
#endif
