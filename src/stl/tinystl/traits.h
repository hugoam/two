#pragma once

#include <stl/tinystl/new.h>

#if defined(__GNUC__)
#	define TINYSTL_TRY_POD_OPTIMIZATION(t) __is_pod(t)
#elif defined(_MSC_VER)
#	define TINYSTL_TRY_POD_OPTIMIZATION(t) (!__is_class(t) || __is_pod(t))
#else
#	define TINYSTL_TRY_POD_OPTIMIZATION(t) false
#endif

namespace tinystl {

	template<class T>
	struct remove_reference { using type = T; };

	template<class T>
	struct remove_reference<T&> { using type = T; };

	template<class T>
	struct remove_reference<T&&> { using type = T; };

	template<class T>
	using remove_reference_t = typename remove_reference<T>::type;

	template<class T>
	constexpr remove_reference_t<T>&& move(T&& arg, tinystl::placeholder) noexcept
	{
		return (static_cast<remove_reference_t<T>&&>(arg));
	}

	template<typename T, bool pod = TINYSTL_TRY_POD_OPTIMIZATION(T)> struct pod_traits {};

	template<typename T, T t> struct swap_holder;

	template<typename T>
	static inline void move_impl(T& a, T& b, ...) {
		a = move(b, placeholder());
	}

	template<typename T>
	static inline void move_impl(T& a, T& b, T*, swap_holder<void (T::*)(T&), &T::swap>* = 0) {
		a.swap(b);
	}

	template<typename T>
	static inline void move(T& a, T&b) {
		move_impl(a, b, (T*)0);
	}

	template<typename T>
	static inline void move_construct_impl(T* a, T& b, ...) {
		new(placeholder(), a) T(move(b, placeholder()));
	}

	template<typename T>
	static inline void move_construct_impl(T* a, T& b, void*, swap_holder<void (T::*)(T&), &T::swap>* = 0) {
		// If your type T does not have a default constructor, simply insert:
		// struct tinystl_nomove_construct;
		// in the class definition
		new(placeholder(), a) T;
		a->swap(b);
	}

	template<typename T>
	static inline void move_construct_impl(T* a, T& b, T*, typename T::tinystl_nomove_construct* = 0) {
		new(placeholder(), a) T(b);
	}

	template<typename T>
	static inline void move_construct(T* a, T& b) {
		move_construct_impl(a, b, (T*)0);
	}
}
