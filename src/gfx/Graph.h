//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/function.h>
#include <pool/Pool.h>
#include <tree/Graph.h>
#ifdef _MSC_VER
#include <tree/Graph.hpp>
#endif
#endif
#include <gfx/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Light.h>

namespace two
{
	class SoundManager;
	class Sound;

#ifndef _MSC_VER
	extern template class Graph<Gnode>;
#endif

	export_ class refl_ TWO_GFX_EXPORT Gnode : public Graph<Gnode>
	{
	public:
		Gnode();
		Gnode(Scene& scene, SoundManager* sound_manager = nullptr);
		Gnode(Gnode* parent, void* identity);
		~Gnode();
		
		void clear();

		template <class T, class... Args>
		T* instantiate(Scene& scene, Args&&... args);
		
		template <class T>
		T* as();

		Scene* m_scene = nullptr;
		Node3* m_attach = nullptr;
		
		Type* m_type = nullptr;
		void* m_object = nullptr;
		function<void()> m_deleter;

		Sound* m_sound = nullptr;
		SoundManager* m_sound_manager = nullptr;
	};

	extern template class refl_ TPool<Node3>;
	extern template class refl_ TPool<Item>;
	extern template class refl_ TPool<Batch>;
	extern template class refl_ TPool<Direct>;
	extern template class refl_ TPool<Mime>;
	extern template class refl_ TPool<Light>;
	extern template class refl_ TPool<Flare>;

	export_ TWO_GFX_EXPORT void debug_tree(Gnode& node, size_t index = 0, size_t depth = 0);
}
