#pragma once

#include <stl/swap.h>
#include <stl/initializer_list.h>
#include <stl/traits.h>
#include <stdint.h>

namespace stl {

	typedef void (*ConstructPtr)(void* dest);
	typedef void (*CopyConstructPtr)(void* dest, const void* src);
	typedef void (*MoveConstructPtr)(void* dest, void* src);
	typedef void (*DestructPtr)(void* dest);
	typedef void (*CopyPtr)(void* dest, const void* src);
	typedef void (*MovePtr)(void* dest, void* src);
	typedef bool (*EqualPtr)(const void* a, const void* b);

	struct ubuffer
	{
		void construct(size_t type_size);
		void construct(const ubuffer& rhs, CopyConstructPtr copy_constructor);
		void construct(size_t type_size, size_t size);
		void construct(size_t type_size, size_t size, ConstructPtr constructor);
		void construct(size_t type_size, size_t size, const void* value, CopyConstructPtr copy_constructor);
		void construct(size_t type_size, const void* first, const void* last, CopyConstructPtr copy_constructor);
		void destruct(DestructPtr destructor);
		void reserve(size_t capacity, MoveConstructPtr move_constructor, DestructPtr destructor);
		void resize(size_t size, ConstructPtr constructor, MoveConstructPtr move_constructor, DestructPtr destructor);
		void resize(size_t size, const void* value, ConstructPtr constructor, MoveConstructPtr move_constructor, DestructPtr destructor);
		//void clear_resize(size_t size, ConstructPtr constructor, CopyConstructPtr copy_constructor, DestructPtr destructor);
		void clear(DestructPtr destructor);
		void* push_back(const void* item, MoveConstructPtr move_constructor, CopyConstructPtr copy_constructor, DestructPtr destructor);
		void* push_back(void* item, MoveConstructPtr move_constructor, DestructPtr destructor);
		void* emplace_back(ConstructPtr constructor, DestructPtr destructor);
		//void add(const void* item, CopyConstructPtr copy_constructor, DestructPtr destructor, EqualPtr equal);
		void pop_back(DestructPtr destructor);
		void remove_unstable(size_t index, DestructPtr destructor, MovePtr copy);
		void remove(size_t index, DestructPtr destructor, MovePtr copy);
		void remove(size_t start, size_t count, DestructPtr destructor, MovePtr copy);
		void assign(const ubuffer& src, MoveConstructPtr move_constructor, CopyConstructPtr copy_constructor, DestructPtr destructor);

		// Untyped storage
		uint8_t* m_items = nullptr;
		size_t m_size = 0;
		size_t m_capacity = 0;

		// Type traits
		size_t m_type_size;
	};

	template <typename T>
	class uvector
	{
	public:
		uvector();
		uvector(const uvector& other);
		uvector(uvector&& other);
		explicit uvector(size_t size);
		uvector(size_t size, const T& value);
		uvector(const T* first, const T* last);
		uvector(std::initializer_list<T> list);
		~uvector();

		uvector& operator=(const uvector& other) { uvector(other).swap(*this); return *this; }
		uvector& operator=(uvector&& other) { other.swap(*this); return *this; }

		void swap(uvector& other) { using stl::swap; swap(m_ubuffer, other.m_ubuffer); }

		const T* data() const { return m_items; }
		T* data() { return m_items; }

		size_t size() const { return m_ubuffer.m_size; }
		size_t capacity() const { return m_ubuffer.m_capacity; }
		bool empty() const { return m_ubuffer.m_size == 0; }

		const T& operator [] (size_t i) const { return *(m_items + i); }
		T& operator [] (size_t i) { return *(m_items + i); }

		void reserve(size_t capacity);
		void resize(size_t size);
		void resize(size_t size, const T& value);
		void clear();
		
		using value_type = T;
		using pointer = T*;

		const T& front() const { return *m_items; }
		T& front() { return *m_items; }
		const T& back() const { return *(m_items + m_ubuffer.m_size - 1); }
		T& back() { return *(m_items + m_ubuffer.m_size - 1); }

		void push_back(const T& entry);
		void push_back(T&& entry);
		void emplace_back();
		template <class... Params>
		void emplace_back(Params&&... params);
		//void add(const T& entry);
		void pop_back();

		void remove(size_t index);
		void remove(size_t start, size_t count);
		void remove_unstable(size_t index);

		size_t byte_size() const { return m_ubuffer.m_size * sizeof(T); }
		
		using iterator = T*;
		using const_iterator = const T*;

		iterator begin() { return m_items; }
		iterator end() { return m_items + m_ubuffer.m_size; }

		const_iterator begin() const { return m_items; }
		const_iterator end() const { return m_items + m_ubuffer.m_size; }

		void erase(iterator where);
		void erase(iterator start, iterator end);

		iterator insert(iterator where);
		iterator insert(iterator where, const T& value);
		iterator insert(iterator where, T&& value);
		iterator insert(iterator where, const T* first, const T* last);

	//private:
		union
		{
			ubuffer m_ubuffer;
			T* m_items;
		};
	};
}
