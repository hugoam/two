//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <pool/Forward.h>
#include <pool/VecPool.h>
#include <type/RefVal.h>
#include <type/Var.h>

#include <new>

namespace mud
{
	export_ class refl_ MUD_POOL_EXPORT Pool
	{
	public:
		virtual ~Pool() {}

		virtual void reset() = 0;
		virtual void clear() = 0;

		virtual void alloc(Ref& ref) = 0;
		virtual Ref alloc() = 0;

		virtual void destroy(Ref object) = 0;
		virtual void free(Ref object) = 0;
	};

	export_ template <class T>
	class TPool : public Pool
	{
	public:
		TPool(size_t size = 12) : m_vec_pool(make_unique<VecPool<T>>(size)) {}
		~TPool() {}

		inline T* talloc() { return m_vec_pool->alloc(); }
		inline void tdestroy(T& object) { m_vec_pool->destroy(&object); }
		inline void tfree(T& object) { m_vec_pool->free(&object); }

		virtual void alloc(Ref& ref) { setval<T>(ref, m_vec_pool->alloc()); }
		virtual Ref alloc() { return Ref(m_vec_pool->alloc(), type<T>()); }

		virtual void destroy(Ref object) { m_vec_pool->destroy(&val<T>(object)); }
		virtual void free(Ref object) { m_vec_pool->free(&val<T>(object)); }

		inline void reset(size_t size) { m_vec_pool = make_unique<VecPool<T>>(size); }
		virtual void reset() { m_vec_pool = make_unique<VecPool<T>>(12); }
		virtual void clear() { m_vec_pool = nullptr; }

		template <class... Types>
		inline T& construct(Types&&... args)
		{
			T* at = this->talloc();
			new (at) T(static_cast<Types&&>(args)...);
			return *at;
		}

		template <class T_Func>
		inline void iterate(T_Func func) const
		{
			VecPool<T>* pool = m_vec_pool.get();
			for(; pool; pool = pool->m_next.get())
				for(T* object : pool->m_objects)
					func(*object);
		}

		template <class T_Test>
		inline T* find(T_Test test) const
		{
			VecPool<T>* pool = m_vec_pool.get();
			for(; pool; pool = pool->m_next.get())
				for(T* object : pool->m_objects)
					if(test(*object))
						return object;
			return nullptr;
		}

		unique<VecPool<T>> m_vec_pool;
	};
}
