#pragma once

#include <15_script/Forward.h>

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
#include <math/Types.h>
#include <geom/Types.h>
#include <lang/Types.h>
#include <ctx/Types.h>
#include <ui/Types.h>
#include <uio/Types.h>
#include <snd/Types.h>
#include <bgfx/Types.h>
#include <gfx/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    
    export_ template <> _15_SCRIPT_EXPORT Type& type<GameObject>();
    
	export_ template struct _15_SCRIPT_EXPORT Typed<std::vector<GameObject*>>;
}
