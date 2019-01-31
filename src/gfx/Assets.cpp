

#include <gfx/Assets.h>
#include <gfx/Asset.hpp>

namespace mud
{
	template class MUD_GFX_EXPORT AssetStore<Texture>;
	template class MUD_GFX_EXPORT AssetStore<Program>;
	template class MUD_GFX_EXPORT AssetStore<Material>;
	template class MUD_GFX_EXPORT AssetStore<Model>;
	template class MUD_GFX_EXPORT AssetStore<ParticleFlow>;
	template class MUD_GFX_EXPORT AssetStore<Prefab>;
}
