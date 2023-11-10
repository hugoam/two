#pragma once

#include <00_tutorial/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <pool/Types.h>
#include <refl/Types.h>
#include <ecs/Types.h>
#include <tree/Types.h>
#include <srlz/Types.h>
#include <math/Types.h>
#include <geom/Types.h>
#include <noise/Types.h>
#include <wfc/Types.h>
#include <fract/Types.h>
#include <lang/Types.h>
#include <ctx/Types.h>
#include <ui/Types.h>
#include <uio/Types.h>
#include <snd/Types.h>
#include <ctx-glfw/Types.h>
#include <ui-vg/Types.h>
#include <bgfx/Types.h>
#include <gfx/Types.h>
#include <gfx-pbr/Types.h>
#include <gfx-obj/Types.h>
#include <gfx-gltf/Types.h>
#include <gfx-ui/Types.h>
#include <tool/Types.h>
#include <wfc-gfx/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    export_ template <> _00_TUTORIAL_EXPORT Type& type<ShapeType>();
    
    export_ template <> _00_TUTORIAL_EXPORT Type& type<MyObject>();
    
	export_ template struct _00_TUTORIAL_EXPORT Typed<std::vector<MyObject*>>;
}
