#pragma once

#include <stl/new.h>
#include <stl/traits.h>
#include <stl/move.h>

#if defined(__GNUC__)
#	define TINYSTL_TRY_POD_OPTIMIZATION(t) __is_pod(t)
#elif defined(_MSC_VER)
#	define TINYSTL_TRY_POD_OPTIMIZATION(t) (!__is_class(t) || __is_pod(t))
#else
#	define TINYSTL_TRY_POD_OPTIMIZATION(t) false
#endif

namespace stl {

	template <class T, bool pod = TINYSTL_TRY_POD_OPTIMIZATION(T)> struct pod_traits {};

	template <class T, T t> struct swap_holder;

	template <class T>
	static inline void move_impl(T& a, T& b, ...) {
		a = move(b);
	}

	template <class T>
	static inline void move_impl(T& a, T& b, T*, swap_holder<void (T::*)(T&), &T::swap>* = 0) {
		a.swap(b);
	}

	template <class T>
	static inline void move(T& a, T&b) {
		move_impl(a, b, (T*)0);
	}

	template <class T>
	static inline void move_construct_impl(T* a, T& b, ...) {
		new(placeholder(), a) T(move(b));
	}

	template <class T>
	static inline void move_construct_impl(T* a, T& b, void*, swap_holder<void (T::*)(T&), &T::swap>* = 0) {
		// If your type T does not have a default constructor, simply insert:
		// struct stl_nomove_construct;
		// in the class definition
		new(placeholder(), a) T;
		a->swap(b);
	}

	template <class T>
	static inline void move_construct_impl(T* a, T& b, T*, typename T::stl_nomove_construct* = 0) {
		new(placeholder(), a) T(b);
	}

	template <class T>
	static inline void move_construct(T* a, T& b) {
		move_construct_impl(a, b, (T*)0);
	}
}
