#pragma once

#include <infra/Config.h>

#ifndef TWO_MODULES
#include <infra/Forward.h>
#include <type/Forward.h>
#include <math/Forward.h>
#include <ctx/Forward.h>
#include <ctx-glfw/Forward.h>
#endif

#ifndef TWO_BGFX_EXPORT
#define TWO_BGFX_EXPORT TWO_IMPORT
#endif

namespace two
{
    class BgfxContext;
    class BgfxSystem;
}
