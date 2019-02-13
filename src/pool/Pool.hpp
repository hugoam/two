//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/new.h>
#include <stl/move.h>
#include <pool/Pool.h>
#include <pool/VecPool.hpp>
#include <type/RefVal.h>

namespace mud
{
	template <class T>
	TPool<T>::TPool(size_t size) : m_vec_pool(make_unique<VecPool<T>>(size)) {}
	template <class T>
	TPool<T>::~TPool() {}

	template <class T>
	inline T* TPool<T>::talloc() { return m_vec_pool->alloc(); }
	template <class T>
	//inline T& TPool<T>::tconstruct(T&& value)
	inline T& TPool<T>::tconstruct(const T& value)
	{
		T* at = this->talloc();
		new (stl::placeholder(), at) T(value);
		return *at;
	}
	template <class T>
	inline void TPool<T>::tdestroy(T& object) { m_vec_pool->destroy(&object); }
	template <class T>
	inline void TPool<T>::tfree(T& object) { m_vec_pool->free(&object); }

	template <class T>
	void TPool<T>::alloc(Ref& ref) { setval<T>(ref, m_vec_pool->alloc()); }
	template <class T>
	Ref TPool<T>::alloc() { return Ref(m_vec_pool->alloc(), type<T>()); }
	template <class T>
	void TPool<T>::destroy(Ref object) { m_vec_pool->destroy(&val<T>(object)); }
	template <class T>
	void TPool<T>::free(Ref object) { m_vec_pool->free(&val<T>(object)); }

	template <class T>
	inline void TPool<T>::reset(size_t size) { m_vec_pool = make_unique<VecPool<T>>(size); }
	template <class T>
	void TPool<T>::reset() { m_vec_pool = make_unique<VecPool<T>>(12); }
	template <class T>
	void TPool<T>::clear() { m_vec_pool = nullptr; }

	template <class T>
	template <class... Types>
	inline T& TPool<T>::construct(Types&&... args)
	{
		T* at = this->talloc();
		new (stl::placeholder(), at) T(static_cast<Types&&>(args)...);
		return *at;
	}

	template <class T>
	template <class T_Func>
	inline void TPool<T>::iterate(T_Func func) const
	{
		VecPool<T>* pool = m_vec_pool.get();
		for(; pool; pool = pool->m_next.get())
			for(T* object : pool->m_objects)
				func(*object);
	}

	template <class T>
	template <class T_Test>
	inline T* TPool<T>::find(T_Test test) const
	{
		VecPool<T>* pool = m_vec_pool.get();
		for(; pool; pool = pool->m_next.get())
			for(T* object : pool->m_objects)
				if(test(*object))
					return object;
		return nullptr;
	}
}
