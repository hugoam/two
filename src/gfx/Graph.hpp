//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Graph.h>
#include <gfx/Scene.h>

namespace two
{
	// the object of a node is a state of the node, stored in the pool of its type in the scene, which the scene goes through, e.g to render the items
	template <class T, class... Args>
	T* Gnode::instantiate(Scene& scene, Args&&... args)
	{
		m_graph->template store<T>(*scene.m_pool->template pool<T>().m_vec_pool);
		return &this->template state<T>(static_cast<Args&&>(args)...);
	}

	template <class T>
	T* Gnode::as()
	{
		return this->template find_state<T>();
	}
}
