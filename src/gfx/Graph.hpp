//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Graph.h>
#include <gfx/Scene.h>
#include <pool/ObjectPool.h>

namespace two
{
	template <class T, class... Args>
	T* Gnode::instantiate(Scene& scene, Args&&... args)
	{
		m_object = (void*) &scene.m_pool->template pool<T>().construct(static_cast<Args&&>(args)...);
		m_type = &type<T>();
		m_deleter = [this]() {
			m_scene->m_pool->template pool<T>().tdestroy(*((T*)m_object));
			m_object = nullptr; };
		return (T*)m_object;
	}

	template <class T>
	T* Gnode::as()
	{
		if (m_type == &type<T>())
			return (T*)m_object;
		return nullptr;
	}
}
