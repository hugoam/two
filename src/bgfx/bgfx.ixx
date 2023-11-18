module;
#define BX_COMPILER_MSVC_CONFORMANCE
#include <infra/Cpp20.h>
#include <infra/Config.h>
#include <bx/bx.h>
#include <bx/allocator.h>
#include <bx/timer.h>
#include <bx/timer.h>
#include <bgfx/bgfx.h>
//#include <bgfx/platform.h>

export module two.bgfx;

export import two.infra;
export import two.type;
export import two.math;
export import two.ctx;
export import two.ctx.glfw;

#include <bgfx/Api.h>

