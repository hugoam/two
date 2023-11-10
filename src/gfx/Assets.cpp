

#ifdef TWO_MODULES
module;
#include <gfx/Cpp20.h>
module two.gfx;
#else
#include <gfx/Assets.h>
#include <gfx/Asset.hpp>
#endif

namespace two
{
	template class TWO_GFX_EXPORT AssetStore<Texture>;
	template class TWO_GFX_EXPORT AssetStore<Program>;
	template class TWO_GFX_EXPORT AssetStore<Material>;
	template class TWO_GFX_EXPORT AssetStore<Model>;
	template class TWO_GFX_EXPORT AssetStore<Flow>;
	template class TWO_GFX_EXPORT AssetStore<Prefab>;
}
