//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Cpp20.h>
#ifdef TWO_MODULES
#define _GLIBCXX_TYPE_TRAITS
#include <xmmintrin.h>
#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bimg/bimg.h>

#define ZONES_BUFFER 0
#define MATERIALS_BUFFER 0
#define LIGHTS_BUFFER 0
#define ZONES_LIGHTS_BUFFER 0

#define TEXTURE_CLAMP  BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP
#define TEXTURE_CLAMP3 BGFX_SAMPLER_U_CLAMP | BGFX_SAMPLER_V_CLAMP | BGFX_SAMPLER_W_CLAMP
#define TEXTURE_POINT  BGFX_SAMPLER_MIN_POINT | BGFX_SAMPLER_MAG_POINT | BGFX_SAMPLER_MIP_POINT

#define TEXTURE_DEPTH 0

#endif

