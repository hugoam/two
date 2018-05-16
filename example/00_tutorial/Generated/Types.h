#pragma once

#include <00_tutorial/Generated/Forward.h>

#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>
#include <ui/Generated/Types.h>
#include <uio/Generated/Types.h>
#include <gfx/Generated/Types.h>
#include <edit/Generated/Types.h>
#include <gen/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>


namespace mud
{
    // Exported types
    template <> _00_TUTORIAL_EXPORT Type& type<ShapeType>();
    
    template <> _00_TUTORIAL_EXPORT Type& type<MyObject>();
}
