//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <pool/Pool.h>
#include <tree/Graph.h>
#ifdef _MSC_VER
#include <tree/Graph.hpp>
#endif
#endif
#include <gfx/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Light.h>

namespace mud
{
	class SoundManager;
	class Sound;

#ifndef _MSC_VER
	export_ extern template class Graph<Gnode>;
#endif

	export_ class refl_ MUD_GFX_EXPORT Gnode : public Graph<Gnode>
	{
	public:
		Gnode();
		Gnode(Scene& scene, SoundManager* sound_manager = nullptr);
		Gnode(Gnode* parent, void* identity);
		~Gnode();
		
		void clear();

		// @todo fix this shit by making each node contain one object from one pool and destroy it with that pool
		Scene* m_scene = nullptr;
		Node3* m_attach = nullptr;
		Node3* m_node = nullptr;
		Item* m_item = nullptr;
		Batch* m_batch = nullptr;
		Mime* m_animated = nullptr;
		Flare* m_particles = nullptr;
		Light* m_light = nullptr;
		GIProbe* m_gi_probe = nullptr;
		LightmapAtlas* m_lightmap_atlas = nullptr;
		SoundManager* m_sound_manager = nullptr;
		Sound* m_sound = nullptr;
	};

	export_ extern template class refl_ TPool<Node3>;
	export_ extern template class refl_ TPool<Item>;
	export_ extern template class refl_ TPool<Mime>;
	export_ extern template class refl_ TPool<Light>;
	export_ extern template class refl_ TPool<Flare>;

	export_ MUD_GFX_EXPORT void debug_tree(Gnode& node, size_t index = 0, size_t depth = 0);
}
