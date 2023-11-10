#pragma once

#include <infra/Config.h>

#ifndef TWO_MODULES
#include <infra/Forward.h>
#include <type/Forward.h>
#include <refl/Forward.h>
#include <srlz/Forward.h>
#include <math/Forward.h>
#include <geom/Forward.h>
#include <gfx/Forward.h>
#include <gltf/Forward.h>
#endif

#ifndef TWO_GFX_GLTF_EXPORT
#define TWO_GFX_GLTF_EXPORT TWO_IMPORT
#endif

namespace two
{
	class ImporterGltf;
}
