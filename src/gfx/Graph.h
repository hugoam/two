//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Light.h>

namespace two
{
	class SoundManager;
	class Sound;

#ifndef _MSC_VER
	extern template class PooledNode<Gnode>;
#endif

	export_ class refl_ TWO_GFX_EXPORT Gnode : public PooledNode<Gnode>
	{
	public:
		Gnode(PooledGraph<Gnode>& graph, Scene& scene, SoundManager* sound_manager = nullptr);
		Gnode(Gnode* parent);
		~Gnode();
		
		void clear();

		// the gfx nodes have no top nodes, they never change parent
		void reparent(Gnode* old) { UNUSED(old); }

		template <class T, class... Args>
		T* instantiate(Scene& scene, Args&&... args);
		
		template <class T>
		T* as();

		Scene* m_scene = nullptr;
		Node3* m_attach = nullptr;
		
		Sound* m_sound = nullptr;
		SoundManager* m_sound_manager = nullptr;
	};

	extern template class refl_ ChunkedPool<Node3>;
	extern template class refl_ ChunkedPool<Item>;
	extern template class refl_ ChunkedPool<Batch>;
	extern template class refl_ ChunkedPool<Direct>;
	extern template class refl_ ChunkedPool<Mime>;
	extern template class refl_ ChunkedPool<Light>;
	extern template class refl_ ChunkedPool<Flare>;

	export_ TWO_GFX_EXPORT void debug_tree(Gnode& node, size_t index = 0, size_t depth = 0);
}
