#pragma once

#include <infra/Config.h>

export_ namespace stl
{}

namespace stl
{
	export_ template <bool Test, class T = void>
	struct enable_if_base {};

	export_ template <class T>
	struct enable_if_base<true, T> { using type = T; };

	export_ template <bool Test, class T = void>
	using enable_if = typename enable_if_base<Test, T>::type;

	export_ template <class T>
	struct remove_reference_base { using type = T; };

	export_ template <class T>
	struct remove_reference_base<T&> { using type = T; };

	export_ template <class T>
	struct remove_reference_base<T&&> { using type = T; };

	export_ template <class T>
	struct remove_pointer_base { using type = T; };

	export_ template <class T>
	struct remove_pointer_base<T*> { using type = T; };

	export_ template <class T>
	struct remove_pointer_base<T* const> { using type = T; };

	export_ template <class T>
	using remove_reference = typename remove_reference_base<T>::type;

	export_ template <class T>
	using remove_pointer = typename remove_pointer_base<T>::type;

	export_ template <class T>
	struct remove_cv_base { using type = T; };

	export_ template <class T>
	struct remove_cv_base<const T> { using type = T; };

	export_ template <class T>
	struct remove_cv_base<volatile T> { using type = T; };

	export_ template <class T>
	struct remove_cv_base<const volatile T> { using type = T; };

	export_ template <class T>
	using remove_cv = typename remove_cv_base<T>::type;

	export_ template <class... Types>
	using void_t = void;

	export_ template <class T, class = void>
	struct add_lvalue_reference_base { using type = T; };

	export_ template <class T, class = void>
	struct add_rvalue_reference_base { using type = T; };

	export_ template <class T>
	struct add_lvalue_reference_base<T, void_t<T&>> { using type = T&; };

	export_ template <class T>
	struct add_rvalue_reference_base<T, void_t<T&>> { using type = T&&; };

	export_ template <class T>
	using add_lvalue_reference = typename add_lvalue_reference_base<T>::type;

	export_ template <class T>
	using add_rvalue_reference = typename add_rvalue_reference_base<T>::type;

	export_ template <class T>
	add_rvalue_reference<T> declval() noexcept;

	export_ template <class T>
	using add_const = const T;

	export_ template <class T>
	constexpr bool is_void = false;
	
	export_ template <>
	inline constexpr bool is_void<void> = true;

	export_ template<class T1, class T2>
	constexpr bool is_same = false;

	export_ template<class T1>
	constexpr bool is_same<T1, T1> = true;

	export_ template <class, class T, class... Args>
	constexpr bool is_constructible_impl = false;

	export_ template <class T, class... Args>
	constexpr bool is_constructible_impl<void_t<decltype(T(declval<Args>()...))>, T, Args...> = true;

	export_ template <class T, class... Args>
	constexpr bool is_constructible = is_constructible_impl<void_t<>, T, Args...>;

	export_ template <class T>
	constexpr bool is_copy_constructible = is_constructible<T, add_lvalue_reference<const T>>;
	
	export_ template <class T>
	constexpr bool is_default_constructible = is_constructible<T>;

	export_ template<class T, class U, typename = void>
	constexpr bool is_assignable = false;

	export_ template<class T, class U>
	constexpr bool is_assignable<T, U, decltype(declval<T&>() = declval<U&>(), void())> = true;

	export_ template<class T>
	constexpr bool is_copy_assignable = is_assignable<T, T>;

#if 1
	template<class _Tp, typename = void>
	struct __success_type { typedef _Tp type; };

	struct __failure_type { };

	template<class F, class... Args>
	struct __result_of_impl
	{
		template<class U>
		static __success_type<decltype(declval<U>()(declval<Args>()...)), void()> test(int);

		template<class...>
		static __failure_type test(...);

		typedef decltype(test<F>(0)) type;
	};

	template<class F, class... Args>
	using invoke_result = typename __result_of_impl<F, Args...>::type;

	template<class Result, class Ret, typename = void>
	constexpr bool __is_invocable_impl = false;

	template<class Result, class Ret>
	constexpr bool __is_invocable_impl<Result, Ret, void_t<typename Result::type>>
		= is_void<Ret> || is_same<typename Result::type, Ret>; //is_convertible<typename Result::type, Ret>>::type

	export_ template<class F, class... Args>
	constexpr bool is_invocable = __is_invocable_impl<invoke_result<F, Args...>, void>;

	export_ template<class Ret, class F, class... Args>
	constexpr bool is_invocable_r = __is_invocable_impl<invoke_result<F, Args...>, Ret>;

#elif 0
	export_ template <class, class T, class... Args>
	constexpr bool is_invocable = false;

	export_ template <class T, class... Args>
	constexpr bool is_invocable<void_t<decltype(declval<T>()(declval<Args>()...))>, T, Args...> = true;
#elif 1
	template <class F, class... Args>
	struct is_invocable_base
	{
		template <class U>
		static auto test(U* p) -> decltype((*p)(declval<Args>()...), void(), true_type());
		template <class U>
		static auto test(...) -> decltype(false_type());

		static constexpr bool value = decltype(test<F>(0))::value;
	};

	export_ template <class, class T, class... Args>
	constexpr bool is_invocable = is_invocable_base<T, Args...>::value;
#endif

	export_ template<class T>
	constexpr bool is_pointer = false;

	export_ template<class T>
	constexpr bool is_pointer<T*> = true;

	export_ template<class T>
	constexpr bool is_pointer<T* const> = true;

	export_ template<class _Ty>
	constexpr bool is_float_impl = false;

	export_ template <> inline constexpr bool is_float_impl<float> = true;
	export_ template <> inline constexpr bool is_float_impl<double> = true;

	export_ template<class T>
	constexpr bool is_float = is_float_impl<remove_cv<T>>;

	export_ template<class _Ty>
	constexpr bool is_integral_impl = false;

	export_ template <> inline constexpr bool is_integral_impl<bool> = true;
	export_ template <> inline constexpr bool is_integral_impl<char> = true;
	export_ template <> inline constexpr bool is_integral_impl<unsigned char> = true;
	export_ template <> inline constexpr bool is_integral_impl<signed char> = true;
	export_ template <> inline constexpr bool is_integral_impl<unsigned short> = true;
	export_ template <> inline constexpr bool is_integral_impl<short> = true;
	export_ template <> inline constexpr bool is_integral_impl<unsigned int> = true;
	export_ template <> inline constexpr bool is_integral_impl<int> = true;
	export_ template <> inline constexpr bool is_integral_impl<unsigned long> = true;
	export_ template <> inline constexpr bool is_integral_impl<long> = true;
	export_ template <> inline constexpr bool is_integral_impl<unsigned long long> = true;
	export_ template <> inline constexpr bool is_integral_impl<long long> = true;

	export_ template<class T>
	constexpr bool is_integral = is_integral_impl<remove_cv<T>>;

	export_ template<class T, bool = is_integral<T> || is_float<T>>
	constexpr bool is_signed = T(-1) < T(0);
 
	export_ template<class T>
	constexpr bool is_signed<T, false> = false;

	export_ template<class T, bool = is_integral<T> || is_float<T>>
	constexpr bool is_unsigned = T(0) < T(-1);

	export_ template<class T>
	constexpr bool is_unsigned<T, false> = false;

	export_ template<class T>
	constexpr bool is_number = is_float<T> || (is_integral<T> && !is_same<T, bool>);
}

namespace two
{
	export_ using stl::declval;
	export_ using stl::enable_if;
	export_ using stl::remove_pointer; export_ using stl::remove_reference; export_ using stl::remove_cv;
	export_ using stl::is_same;
	export_ using stl::is_invocable; export_ using stl::is_invocable_r;
	export_ using stl::is_copy_assignable;
	export_ using stl::is_constructible; export_ using stl::is_copy_constructible; export_ using stl::is_default_constructible;
	export_ using stl::is_pointer; export_ using stl::is_integral; export_ using stl::is_signed; export_ using stl::is_unsigned; export_ using stl::is_float; export_ using stl::is_number;
}