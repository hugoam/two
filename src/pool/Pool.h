//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Unique.h>
#include <type/Ref.h>
#include <pool/Forward.h>

#include <cstddef>

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
		TPool(size_t size = 12);
		~TPool();

		inline T* talloc();
		inline void tdestroy(T& object);
		inline void tfree(T& object);

		virtual void alloc(Ref& ref);
		virtual Ref alloc();

		virtual void destroy(Ref object);
		virtual void free(Ref object);

		inline void reset(size_t size);
		virtual void reset();
		virtual void clear();

		template <class... Types>
		inline T& construct(Types&&... args);

		template <class T_Func>
		inline void iterate(T_Func func) const;

		template <class T_Test>
		inline T* find(T_Test test) const;

		unique<VecPool<T>> m_vec_pool;
	};
}
