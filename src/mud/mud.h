#pragma once

#include <infra/Api.h>
#include <jobs/Api.h>
#include <obj/Api.h>
#include <pool/Api.h>
#include <tree/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <lang/Api.h>
#include <ui/Api.h>
#include <uio/Api.h>

#if defined MUD_RENDERER_BGFX
#include <bgfx/Config.h>
#if !defined MUD_NO_GFX
#include <gfx/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>
#include <gfx-gltf/Api.h>
#include <gfx-ui/Api.h>
#include <procgen/Api.h>
#include <procgen-gfx/Api.h>
#include <tool/Api.h>

#include <mud/Shell.h>
#endif
#endif

#ifdef MUD_PLATFORM_EMSCRIPTEN
#define MUD_RESOURCE_PATH "/data/"
#endif
