#pragma once

#include <stl/vector.h>
#include <stl/ubuffer.h>
#include <stl/new.h>

namespace stl {

	template <typename T> void construct(void* dest) { new (placeholder(), (T*)dest) T; }
	template <typename T> void destruct(void* dest) { ((T*)dest)->~T(); }
	template <typename T> void copy_construct(void* dest, const void* src) { new (placeholder(), (T*)dest) T(*(T*)src); }
	template <typename T> void move_construct(void* dest, void* src) { new (placeholder(), (T*)dest) T(move(*(T*)src)); }
	template <typename T> void copy_assign(void* dest, const void* src) { *(T*)dest = *(T*)src; }
	template <typename T> void move_assign(void* dest, void* src) { *(T*)dest = move(*(T*)src); }
	template <typename T> bool equal(const void* a, const void* b) { return (*(const T*)a) == (*(const T*)b); }

	template <class T, bool test = __has_trivial_constructor(T) || !is_default_constructible<T>>
	struct uconstruct { constexpr static ConstructPtr func = nullptr; };

	template <class T>
	struct uconstruct<T, false> { constexpr static ConstructPtr func = construct<T>; };

	template <class T, bool test = __has_trivial_copy(T)>
	struct ucopy_construct { constexpr static CopyConstructPtr func = nullptr; };

	template <class T>
	struct ucopy_construct<T, false> { constexpr static CopyConstructPtr func = copy_construct<T>; };

	template <class T, bool test = __has_trivial_copy(T)>
	struct umove { constexpr static MovePtr func = nullptr; };

	template <class T>
	struct umove<T, false> { constexpr static MovePtr func = move_assign<T>; };

	template <class T, bool test = __has_trivial_destructor(T)>
	struct udestruct { constexpr static DestructPtr func = nullptr; };

	template <class T>
	struct udestruct<T, false> { constexpr static DestructPtr func = destruct<T>; };

	namespace
	{
		template <class T>
		enable_if<is_copy_constructible<T>, void> ubufconstruct(uvector<T>& self, const uvector<T>& other) { self.m_ubuffer.construct(other.m_ubuffer, ucopy_construct<T>::func); }

		template <class T>
		enable_if<!is_copy_constructible<T>, void> ubufconstruct(uvector<T>& self, const uvector<T>& other) { (void)self; (void)other; }

		template <class T>
		enable_if<is_copy_constructible<T>, void> ubufconstruct(uvector<T>& self, size_t size, const T& value) { self.m_ubuffer.construct(sizeof(T), size, &value, ucopy_construct<T>::func); }

		template <class T>
		enable_if<!is_copy_constructible<T>, void> ubufconstruct(uvector<T>& self, size_t size, const T& value) { (void)self; (void)size; (void)value; }

		template <class T>
		enable_if<is_copy_constructible<T>, void> ubufconstruct(uvector<T>& self, const T* first, const T* last) { self.m_ubuffer.construct(sizeof(T), first, last, ucopy_construct<T>::func); }

		template <class T>
		enable_if<!is_copy_constructible<T>, void> ubufconstruct(uvector<T>& self, const T* first, const T* last) { (void)self; (void)first; (void)last; }

		//template <class T>
		//enable_if<is_copy_constructible<T>, T&> upush_back(const uvector<T>& self, const T& entry) { return *(T*)m_ubuffer.push_back(&entry, move_construct<T>, ucopy_construct<T>::func, udestruct<T>::func); }
		//
		//template <class T>
		//enable_if<!is_copy_constructible<T>, T&> upush_back(const uvector<T>& self, const T& entry) {}

		template <class T>
		enable_if<is_copy_constructible<T>, void> uassign(uvector<T>& self, const uvector<T>& other) { m_ubuffer.assign(other.m_ubuffer, ucopy_construct<T>::func, udestruct<T>::func); }
	}

	template <typename T>
	uvector<T>::uvector() { m_ubuffer.construct(sizeof(T)); }
	template <typename T>
	uvector<T>::uvector(const uvector& other) { ubufconstruct(*this, other); }
	template <typename T>
	uvector<T>::uvector(uvector&& other) { ubufconstruct(*this, other); }
	template <typename T>
	uvector<T>::uvector(size_t size) { m_ubuffer.construct(sizeof(T), size, uconstruct<T>::func); }
	template <typename T>
	uvector<T>::uvector(size_t size, const T& value) { ubufconstruct(*this, size, value); }
	template <typename T>
	uvector<T>::uvector(const T* first, const T* last) { ubufconstruct(*this, first, last); }
	template <typename T>
	uvector<T>::uvector(std::initializer_list<T> list) { ubufconstruct(*this, list.begin(), list.end()); }
	template <typename T>
	uvector<T>::~uvector() { m_ubuffer.destruct(udestruct<T>::func); }

	//template <typename T>
	//void uvector<T>::alloc(size_t size);
	//template <typename T>
	//void uvector<T>::realloc(size_t size, bool dealloc = true);
	template <typename T>
	void uvector<T>::reserve(size_t capacity) { m_ubuffer.reserve(capacity, move_construct<T>, udestruct<T>::func); }
	template <typename T>
	void uvector<T>::resize(size_t size) { m_ubuffer.resize(size, uconstruct<T>::func, move_construct<T>, udestruct<T>::func); }
	template <typename T>
	void uvector<T>::resize(size_t size, const T& val) { m_ubuffer.resize(size, &val, uconstruct<T>::func, move_construct<T>, udestruct<T>::func); }
	//template <typename T>
	//void uvector<T>::resize(size_t size, const T& value);
	template <typename T>
	void uvector<T>::clear() { m_ubuffer.clear(udestruct<T>::func); }

	template <typename T>
	void uvector<T>::push_back(const T& value) { (void)value;/*m_ubuffer.push_back(&value, move_construct<T>, udestruct<T>::func);*/ }
	template <typename T>
	void uvector<T>::push_back(T&& value) { m_ubuffer.push_back(&value, move_construct<T>, udestruct<T>::func); }
	template <typename T>
	void uvector<T>::emplace_back() { m_ubuffer.emplace_back(uconstruct<T>::func, udestruct<T>::func); }
	template <typename T>
	void uvector<T>::pop_back() { m_ubuffer.pop_back(udestruct<T>::func); }

	//template <typename T>
	//void uvector<T>::add(const T& entry) { m_ubuffer.add(&entry, ucopy_construct<T>::func, udestruct<T>::func, Equal<T>); }

	template <typename T>
	void uvector<T>::remove(size_t index) { m_ubuffer.remove(index, udestruct<T>::func, umove<T>::func); }
	template <typename T>
	void uvector<T>::remove(size_t start, size_t count) { m_ubuffer.remove(start, count, udestruct<T>::func, umove<T>::func); }
	template <typename T>
	void uvector<T>::remove_unstable(size_t index) { m_ubuffer.remove_unstable(index, udestruct<T>::func, umove<T>::func); }

	template <typename T>
	void uvector<T>::erase(iterator where) { m_ubuffer.remove(size_t(where - m_items), udestruct<T>::func, umove<T>::func); }
	template <typename T>
	void uvector<T>::erase(iterator start, iterator end) { m_ubuffer.remove(size_t(start - m_items), size_t(end - start), udestruct<T>::func, umove<T>::func); }

	template <typename T>
	typename uvector<T>::iterator uvector<T>::insert(iterator where) { return where; }
	template <typename T>
	typename uvector<T>::iterator uvector<T>::insert(iterator where, const T& value) { (void)value; return where; }
	template <typename T>
	typename uvector<T>::iterator uvector<T>::insert(iterator where, T&& value) { (void)value; return where; }
	template <typename T>
	typename uvector<T>::iterator uvector<T>::insert(iterator where, const T* first, const T* last) { (void)first; (void)last; return where; }

}
