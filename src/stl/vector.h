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

#include <stl/stddef.h>
#include <stl/decls.h>
#include <stl/allocator.h>
//#include <stl/buffer.h>

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
	class refl_ seque_ vector {
	public:
		vector();
		vector(const vector& other);
		vector(vector&& other);
		explicit vector(size_t size);
		vector(size_t size, const T& value);
		vector(const T* first, const T* last);
		vector(std::initializer_list<T> list);
		~vector();

		vector& operator=(const vector& other);
		vector& operator=(vector&& other);

		void swap(vector& other);

		const T* data() const { return m_first; }
		T* data() { return m_first; }
		size_t size() const { return size_t(m_last - m_first); }
		size_t capacity() const { return size_t(m_capacity - m_first); }
		bool empty() const { return m_last == m_first; }

		T& operator[](size_t idx) { return m_first[idx]; }
		const T& operator[](size_t idx) const { return m_first[idx]; }

		void alloc(size_t size);
		void realloc(size_t size, bool dealloc = true);
		void reserve(size_t capacity, bool dealloc = true);
		void resize(size_t size);
		void resize(size_t size, const T& value);
		void clear();

		using value_type = T;
		using pointer = T * ;

		const T& front() const { return this->m_first[0]; }
		T& front() { return this->m_first[0]; }
		const T& back() const { return this->m_last[-1]; }
		T& back() { return this->m_last[-1]; }

		void grow(size_t size, bool dealloc = true);

		void push_back(const T& t);
		void push_back(T&& t);
		void emplace_back();
		template <class... Params>
		void emplace_back(Params&&... params);
		void pop_back();

		void append(const T* first, const T* last);

		void shrink_to_fit();

		T* spread(T* where, size_t count, bool dealloc = true);

		using iterator = T * ;
		using const_iterator = const T*;

		iterator begin() { return this->m_first; }
		iterator end() { return this->m_last; }

		const_iterator begin() const { return this->m_first; }
		const_iterator end() const { return this->m_last; }

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
		
	//protected:
		T* m_first = 0;
		T* m_last = 0;
		T* m_capacity = 0;
	};
#endif

	template <class T, class Alloc>
	template <class... Params>
	inline void vector<T, Alloc>::emplace_back(Params&&... params) {
		this->grow(this->size() + 1);
		new(placeholder(), this->m_last) T(static_cast<Params&&>(params)...);
		this->m_last++;
	}

	template <class T, class Alloc>
	inline bool operator==(const vector<T, Alloc>& left, const vector<T, Alloc>& right);
}
#endif

namespace mud
{
	using stl::vector;
}
