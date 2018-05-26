#pragma once

#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
#include <lang/Generated/Module.h>
#include <ui/Generated/Module.h>
#include <uio/Generated/Module.h>

#ifdef MUD_RENDERER_BGFX
#include <gfx/Generated/Module.h>
#include <gfx-pbr/Generated/Module.h>
#include <gfx-obj/Generated/Module.h>
#include <gfx-gltf/Generated/Module.h>
#include <gen/Generated/Module.h>
#include <edit/Generated/Module.h>

#include <mud/Shell.h>
#endif

#ifdef MUD_PLATFORM_EMSCRIPTEN
#define MUD_RESOURCE_PATH "/data/"
#endif
