#pragma once

#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/noise/Module.h>
#include <meta/wfc/Module.h>
#include <meta/fract/Module.h>
#include <meta/lang/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>

#if defined MUD_RENDERER_BGFX
#if !defined MUD_NO_GFX
#include <meta/gfx/Module.h>
#include <meta/gfx-pbr/Module.h>
#include <meta/gfx-obj/Module.h>
#include <meta/gfx-gltf/Module.h>
#include <meta/gfx-ui/Module.h>
#include <meta/tool/Module.h>
#endif
#endif

