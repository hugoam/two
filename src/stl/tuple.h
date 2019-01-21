#pragma once
#include <infra/Config.h>

#ifndef MUD_NO_STL
#ifndef MUD_CPP_20
#include <tuple>
#endif
namespace mud
{
	export_ using std::tuple;
	export_ using std::get;
}
#else
#include <cstddef>
namespace mud
{
	template <size_t...>
	struct index_sequence
	{};

	template <size_t N, size_t... Next>
	struct index_sequence_type : public index_sequence_type<N - 1U, N - 1U, Next...>
	{};

	template <size_t... Next>
	struct index_sequence_type<0U, Next...>
	{
		using type = index_sequence<Next...>;
	};

	template <size_t N>
	using make_index_sequence = typename index_sequence_type<N>::type;

	template<size_t i, class T>
	struct tuple_leaf
	{
		T value;
	};

	template<size_t i, class... Items>
	struct tuple_base;

	template<size_t i>
	struct tuple_base<i> {};

	template<size_t i, class Head, class... Tail>
	struct tuple_base<i, Head, Tail...>
		: public tuple_leaf<i, Head>
		, public tuple_base<i + 1, Tail...>
	{};

	template<size_t i, class Head, class... Tail>
	Head& at(tuple_base<i, Head, Tail...>& tup) { return tup.tuple_leaf<i, Head>::value; }

	template<size_t i, class Head, class... Tail>
	Head& at(const tuple_base<i, Head, Tail...>& tup) { return tup.tuple_leaf<i, Head>::value; }

	template<class... Items>
	using tuple = tuple_base<0, Items...>;

	template<class... Types>
	constexpr tuple<Types...> to_tuple(Types&&... args)
	{
		typedef tuple<Types...> Tuple;
		return (Tuple(static_cast<Types&&>(args)...));
	}
}
#endif
