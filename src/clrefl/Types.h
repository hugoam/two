#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <clrefl/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <infra/Types.h>
#include <type/Types.h>
#include <pool/Types.h>
#endif

namespace two
{
    // Exported types
}
