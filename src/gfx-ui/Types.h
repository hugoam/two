#pragma once

#include <gfx-ui/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
//#include <proto/Proto.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <obj/Types.h>
#include <refl/Types.h>
#include <srlz/Types.h>
#include <lang/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <ctx/Types.h>
#include <ui/Types.h>
#include <uio/Types.h>
#include <gfx/Types.h>
#include <gfx-pbr/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> MUD_GFX_UI_EXPORT Type& type<mud::ViewerController>();
    export_ template <> MUD_GFX_UI_EXPORT Type& type<mud::SceneViewer>();
    export_ template <> MUD_GFX_UI_EXPORT Type& type<mud::Viewer>();
    export_ template <> MUD_GFX_UI_EXPORT Type& type<mud::SpaceSheet>();
}
