#pragma once

#if 1 //def USE_STL
#include <initializer_list>
#else
#include <stl/stddef.h>
namespace std
{
	template <class T>
	class initializer_list
	{
		const T* ptr_;
		size_t size_;

		// GCC/clang
		constexpr initializer_list(const T* ptr, size_t size)
			: ptr_(ptr), size_(size)
		{}

	public:
		// MSVC
		constexpr initializer_list(const T* begin, const T* end)
			: ptr_(begin), size_(end - begin) {}

		constexpr const T* begin() const { return ptr_; }
		constexpr const T* end() const { return ptr_ + size_; }
	};
}
#endif
