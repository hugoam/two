#pragma once

#include <infra/Api.h>
#include <jobs/Api.h>
#include <type/Api.h>
#include <pool/Api.h>
#include <tree/Api.h>
#include <math/Api.h>
#include <geom/Api.h>
#include <refl/Api.h>
#include <srlz/Api.h>
#include <lang/Api.h>
#include <ui/Api.h>
#include <uio/Api.h>
//#include <noise/Api.h>
//#include <wfc/Api.h>
//#include <fract/Api.h>

#if defined MUD_RENDERER_BGFX
#include <bgfx/Forward.h>
#if !defined MUD_NO_GFX
#include <gfx/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>
#include <gfx-gltf/Api.h>
#include <gfx-ui/Api.h>
#include <gfx-edit/Api.h>
#include <wfc-gfx/Api.h>
#include <tool/Api.h>
//#include <frame/Api.h>
#endif
#endif

#ifdef MUD_PLATFORM_EMSCRIPTEN
#define MUD_RESOURCE_PATH "/data/"
#endif
