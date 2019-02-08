#pragma once
#include <infra/Config.h>

#ifdef USE_STL
#include <vector>
namespace stl
{
	using std::vector;
}
#else
#include <stl/initializer_list.h>

#include <stl/decls.h>
#include <stl/allocator.h>
#include <stl/buffer.h>
#include <stl/stddef.h>

//#define USE_UVECTOR

#ifdef USE_UVECTOR
#include <stl/ubuffer.h>
#endif

namespace stl {

#ifdef USE_UVECTOR
	template <class T, class Alloc>
	using vector = uvector<T>;
#elif defined USE_BUFFER
	template <class T, class Alloc>
	using vector = buffer<T>;
#else
	template <class T, class Alloc>
	class refl_ seque_ vector : public buffer<T, Alloc> {
	public:
		using buffer<T, Alloc>::buffer;

		using value_type = T;
		using pointer = T*;
		using iterator = T*;
		using const_iterator = const T*;

		void assign(const T* first, const T* last);

		iterator insert(iterator where);
		iterator insert(iterator where, const T& value);
		iterator insert(iterator where, T&& value);
		iterator insert(iterator where, const T* first, const T* last);

		template <class... Params>
		void emplace(iterator where, Params&&... params);

		iterator erase(iterator where);
		iterator erase(iterator first, iterator last);

		iterator erase_unstable(iterator where);
		iterator erase_unstable(iterator first, iterator last);
	};
#endif
	
	template <class T, class Alloc>
	inline bool operator==(const vector<T, Alloc>& left, const vector<T, Alloc>& right);
}
#endif

namespace mud
{
	using stl::vector;
}
