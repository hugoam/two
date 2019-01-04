//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>
#include <gfx/Asset.h>
#include <gfx/Asset.impl.h>
#include <gfx/Texture.h>
#include <gfx/Program.h>
#include <gfx/Material.h>
#include <gfx/Model.h>
#include <gfx/Particles.h>
#include <gfx/Prefab.h>

namespace mud
{
	export_ template class refl_ MUD_GFX_EXPORT AssetStore<Texture>;
	export_ template class refl_ MUD_GFX_EXPORT AssetStore<Program>;
	export_ template class refl_ MUD_GFX_EXPORT AssetStore<Material>;
	export_ template class refl_ MUD_GFX_EXPORT AssetStore<Model>;
	export_ template class refl_ MUD_GFX_EXPORT AssetStore<ParticleGenerator>;
	export_ template class refl_ MUD_GFX_EXPORT AssetStore<Prefab>;
}
