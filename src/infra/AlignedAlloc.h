//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#if defined(WIN32)
#include <malloc.h>
#else
#include <cstdlib>
#endif


namespace two
{
	inline void* aligned_alloc(size_t size, size_t align) noexcept
	{
		assert(align && !(align & (align - 1)));
		void* p = nullptr;

		// must be a power of two and >= sizeof(void*)
		while(align < sizeof(void*))
			align <<= 1;

#if defined(WIN32)
		p = ::_aligned_malloc(size, align);
#else
		::posix_memalign(&p, align, size);
#endif
		return p;
	}

	inline void aligned_free(void* p) noexcept
	{
#if defined(WIN32)
		::_aligned_free(p);
#else
		::free(p);
#endif
	}

#ifndef USE_STL
	template <class T>
	class TinystlAlignedAllocator
	{
	public:
		static inline T* static_allocate(size_t bytes) { return (T*)aligned_alloc(bytes, alignof(T)); };
		static inline void static_deallocate(T* ptr, size_t /*bytes*/) { aligned_free(ptr); }
	};
#else
	export_ template <class T>
	class STLAlignedAllocator
	{
		static_assert(!(alignof(T) & (alignof(T)-1)), "alignof(T) must be a power of two");

	public:
		using value_type = T;
		using pointer = T*;
		using const_pointer = const T*;
		using reference = T&;
		using const_reference = const T&;
		using size_type = size_t;
		using difference_type = std::ptrdiff_t;
		using propagate_on_container_move_assignment = std::true_type;
		using is_always_equal = std::true_type;

		template <class U>
		struct rebind { using other = STLAlignedAllocator<U>; };

	public:
		inline STLAlignedAllocator() noexcept = default;
		inline ~STLAlignedAllocator() noexcept = default;

		template <class U>
		inline explicit STLAlignedAllocator(const STLAlignedAllocator<U>&) noexcept {}

		inline pointer allocate(size_type n) noexcept { return (pointer)aligned_alloc(n * sizeof(value_type), alignof(T)); }
		inline void deallocate(pointer p, size_type) { aligned_free(p); }

		inline bool operator==(const STLAlignedAllocator<T>&) const { return true; }
		inline bool operator!=(const STLAlignedAllocator<T>&) const { return false; }
	};
#endif
}
