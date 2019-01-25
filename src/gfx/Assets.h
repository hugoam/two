//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
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

namespace mud
{
	export_ extern template class refl_ AssetStore<Texture>;
	export_ extern template class refl_ AssetStore<Program>;
	export_ extern template class refl_ AssetStore<Material>;
	export_ extern template class refl_ AssetStore<Model>;
	export_ extern template class refl_ AssetStore<ParticleFlow>;
	export_ extern template class refl_ AssetStore<Prefab>;
}
