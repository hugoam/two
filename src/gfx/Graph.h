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

	export_ class refl_ struct_ TWO_GFX_EXPORT Gnode : public PooledNode<Gnode>
	{
	public:
		Gnode() {}
		Gnode(nullptr_t) {}
		Gnode(PooledGraph<Gnode>& graph, uint32_t index) : PooledNode(graph, index) {}

		// the gfx nodes have no top nodes, they never change parent
		void reparent(Gnode old) { UNUSED(old); }
		// a sound still playing in the node goes to the orphan sounds of the scene
		void release();

		Scene& scene();
		SoundManager* sound_manager();

		// the transform the objects of the node are attached to: its own, or the one of its parent
		Node3& attach();
		void set_attach(Node3& node);
	};

	// the sound played in a node, a state of the node
	export_ struct NodeSound
	{
		Sound* m_sound = nullptr;
	};

	export_ TWO_GFX_EXPORT void debug_tree(Gnode node, size_t index = 0, size_t depth = 0);
}
