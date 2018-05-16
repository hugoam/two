//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.
//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Ref.h>
#include <obj/Generated/Forward.h>
#include <obj/Memory/VecPool.h>
#include <obj/Any.h>

namespace mud
{
	class _refl_ MUD_OBJ_EXPORT Pool
	{
	public:
		virtual void reset() = 0;
		virtual void clear() = 0;

		virtual void alloc(Ref& ref) = 0;
		virtual Ref alloc() = 0;

		virtual void destroy(Ref object) = 0;
		virtual void free(Ref object) = 0;
	};

	template <class T>
	class TPool : public Pool
	{
	public:
		TPool(size_t size = 12) : m_vec_pool(make_unique<VecPool<T>>(size)) {}
		~TPool() {}

		inline T* talloc() { return m_vec_pool->alloc(); }
		inline void tdestroy(T& object) { m_vec_pool->destroy(&object); }
		inline void tfree(T& object) { m_vec_pool->free(&object); }

		virtual void alloc(Ref& ref) { set<T>(ref, m_vec_pool->alloc()); }
		virtual Ref alloc() { return Ref(m_vec_pool->alloc(), type<T>()); }

		virtual void destroy(Ref object) { m_vec_pool->destroy(&val<T>(object)); }
		virtual void free(Ref object) { m_vec_pool->free(&val<T>(object)); }

		inline void reset(size_t size) { m_vec_pool = make_unique<VecPool<T>>(size); }
		inline void reset() { m_vec_pool = make_unique<VecPool<T>>(12); }
		inline void clear() { m_vec_pool = nullptr; }

		template<class... Types>
		inline T& construct(Types&&... args)
		{
			T* at = this->talloc();
			new (at) T(std::forward<Types>(args)...);
			return *at;
		}

		unique_ptr<VecPool<T>> m_vec_pool;
	};
}
