//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/span.h>
#include <type/Unique.h>
#include <type/Ref.h>
#include <pool/Forward.h>

#include <cstddef>

namespace two
{
	export_ class refl_ TWO_POOL_EXPORT Pool
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
	class refl_ TPool : public Pool
	{
	public:
		TPool(size_t size = 64);
		~TPool();

		//meth_ T& add(T&& value);
		meth_ T& add(const T& value);
		meth_ span<T> addvec(span<T> values);

		meth_ T* talloc();
		meth_ void tdestroy(T& object);
		meth_ void tfree(T& object);

		virtual void alloc(Ref& ref);
		virtual Ref alloc();

		virtual void destroy(Ref object);
		virtual void free(Ref object);

		void reset(size_t size);
		virtual void reset();
		virtual void clear();

		template <class... Types>
		T& construct(Types&&... args);

		template <class T_Func>
		void iterate(T_Func func) const;

		template <class T_Test>
		T* find(T_Test test) const;

		unique<VecPool<T>> m_vec_pool;
	};
}
