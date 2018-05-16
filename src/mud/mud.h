#pragma once

#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
#include <gen/Generated/Module.h>
#include <lang/Generated/Module.h>
#include <ui/Generated/Module.h>
#include <uio/Generated/Module.h>
#include <gfx/Generated/Module.h>
#include <edit/Generated/Module.h>

#include <mud/Shell.h>

#if MUD_PLATFORM_EMSCRIPTEN
#define MUD_RESOURCE_PATH "/data/"
#endif
