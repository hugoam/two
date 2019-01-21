#pragma once
#include <infra/Config.h>

#ifndef MUD_NO_STL
#ifndef MUD_CPP_20
#include <tuple>
#endif
namespace mud
{
	export_ using std::tuple;
	export_ using std::index_sequence;
	export_ using std::make_index_sequence;

	template<size_t Num>
	using index_tuple = make_index_sequence<Num>;

	template<size_t i, class... Types>
	auto at(tuple<Types...>& tup) { return std::get<i>(tup); }

	template<size_t i, class... Types>
	auto at(const tuple<Types...>& tup) { return std::get<i>(tup); }
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

	template <size_t N>
	using index_tuple = typename index_sequence_type<N>::type;

	template<size_t i, class T>
	struct tuple_leaf
	{
		constexpr tuple_leaf(T&& val) : value(static_cast<T&&>(val)) {}
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
	{
		constexpr tuple_base(Head&& head, Tail&&... tail)
			: tuple_leaf<i, Head>(static_cast<Head&&>(head))
			, tuple_base<i + 1, Tail...>(static_cast<Tail&&>(tail)...)
		{}
	};

	template<size_t i, class Head, class... Tail>
	Head& at(tuple_base<i, Head, Tail...>& tup) { return tup.tuple_leaf<i, Head>::value; }

	template<size_t i, class Head, class... Tail>
	Head& at(const tuple_base<i, Head, Tail...>& tup) { return tup.tuple_leaf<i, Head>::value; }

	template<class... Items>
	using tuple = tuple_base<0, Items...>;

	template<class... Types>
	constexpr tuple<Types...> to_tuple(Types&&... args)
	{
		return tuple<Types...>(static_cast<Types&&>(args)...);
	}
}
#endif
