//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <GLFW/glfw3.h>

#if defined TWO_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined TWO_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#elif defined TWO_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#include <GLFW/glfw3native.h>

#if defined TWO_PLATFORM_WINDOWS
#undef max
#undef min
#undef near
#undef far
#undef NEAR
#undef FAR
#undef OPAQUE
#elif defined TWO_PLATFORM_LINUX
#undef None
#endif