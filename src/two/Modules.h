#pragma once

#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/tree.meta.h>
#include <meta/pool.meta.h>
#include <meta/ecs.meta.h>
#include <meta/refl.meta.h>
#include <meta/srlz.meta.h>
#include <meta/math.meta.h>
#include <meta/geom.meta.h>
//#include <meta/noise.meta.h>
//#include <meta/wfc.meta.h>
//#include <meta/fract.meta.h>
#include <meta/lang.meta.h>
#include <meta/ctx.meta.h>
#include <meta/ui.meta.h>
#include <meta/uio.meta.h>

#if defined TWO_RENDERER_BGFX
#if !defined TWO_NO_GFX
#include <meta/gfx.meta.h>
#include <meta/gfx.pbr.meta.h>
#include <meta/gfx.obj.meta.h>
#include <meta/gfx.gltf.meta.h>
#include <meta/gfx.ui.meta.h>
#include <meta/tool.meta.h>
#endif
#endif

