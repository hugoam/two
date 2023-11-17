//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>
#include <gfx/Asset.h>
#include <gfx/Texture.h>
#include <gfx/Program.h>
#include <gfx/Material.h>
#include <gfx/Model.h>
#include <gfx/Particles.h>
#include <gfx/Prefab.h>

namespace two
{
	extern template class refl_ AssetStore<Texture>;
	extern template class refl_ AssetStore<Program>;
	extern template class refl_ AssetStore<Material>;
	extern template class refl_ AssetStore<Model>;
	extern template class refl_ AssetStore<Flow>;
	extern template class refl_ AssetStore<Prefab>;
}
