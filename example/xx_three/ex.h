//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#if UI
#define EX(name) void name(ShellX& app, Widget& parent, Dockbar& dockbar, bool init)
#else
#define EX(name) void name(ShellX& app, WindowX& window, bool init)
#endif

#ifndef TWO_MODULES
#define CONSTEXPR constexpr
#else
#define CONSTEXPR
#endif

#define TEXTURE_CLAMP  BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP

#ifdef TWO_PLATFORM_EMSCRIPTEN
// webgl doesn't usually support sampling depth textures with filtering on
#define TEXTURE_DEPTH TEXTURE_POINT
#else
#define TEXTURE_DEPTH 0
#endif
