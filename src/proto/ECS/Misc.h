#pragma once

#include <infra/Array.h>
#include <proto/ECS/ECS.h>

#include <vector>
#include <string>

template <class V0, class V1>
class DualRef { // overrides copy semantics of std::pair
protected:
	V0& m_v0;
	V1& m_v1;

public:
	DualRef(V0& v0, V1& v1) : m_v0(v0), m_v1(v1) {}

	void swap(DualRef& other)
	{
		std::swap(m_v0, other.m_v0);
		std::swap(m_v1, other.m_v1);
	}

	operator std::pair<V0, V1>() const // both g++ and msvc sort requires this (to get a pivot)
	{
		return std::pair<V0, V1>(m_v0, m_v1);
	}

	DualRef& operator=(std::pair<V0, V1> v) // both g++ and msvc sort requires this (for insertion sort)
	{
		m_v0 = v.first;
		m_v1 = v.second;
		return *this;
	}

	DualRef& operator=(const DualRef& other) // required by g++ (for _GLIBCXX_MOVE)
	{
		m_v0 = other.m_v0;
		m_v1 = other.m_v1;
		return *this;
	}
};

template <class V0, class V1>
inline bool operator<(std::pair<V0, V1> a, DualRef<V0, V1> b) // required by both g++ and msvc
{
	return a < std::pair<V0, V1>(b); // default pairwise lexicographical comparison
}

template <class V0, class V1>
inline bool operator<(DualRef<V0, V1> a, std::pair<V0, V1> b) // required by both g++ and msvc
{
	return std::pair<V0, V1>(a) < b; // default pairwise lexicographical comparison
}

template <class V0, class V1>
inline bool operator<(DualRef<V0, V1> a, DualRef<V0, V1> b) // required by both g++ and msvc
{
	return std::pair<V0, V1>(a) < std::pair<V0, V1>(b); // default pairwise lexicographical comparison
}

namespace std {

	template <class V0, class V1>
	inline void swap(DualRef<V0, V1>& a, DualRef<V0, V1>& b)
	{
		a.swap(b);
	}

} // ~std

template <class It0, class It1>
class DualIterator : public std::random_access_iterator_tag {
public:
	typedef typename std::iterator_traits<It0>::value_type value_type0;
	typedef typename std::iterator_traits<It1>::value_type value_type1;
	typedef std::pair<value_type0, value_type1> value_type;
	typedef typename std::iterator_traits<It0>::difference_type difference_type;
	typedef /*typename std::iterator_traits<It0>::distance_type*/difference_type distance_type; // no distance_type in g++, only in msvc
	typedef typename std::iterator_traits<It0>::iterator_category iterator_category;
	typedef DualRef<value_type0, value_type1> reference;
	typedef reference *pointer; // not so sure about this, probably can't be implemented in a meaningful way, won't be able to overload ->
								// keep the iterator traits happy

protected:
	It0 m_it0;
	It1 m_it1;

public:
	DualIterator(const DualIterator& r_other) : m_it0(r_other.m_it0), m_it1(r_other.m_it1) {}
	DualIterator(It0 it0 = It0(), It1 it1 = It1()) : m_it0(it0), m_it1(it1) {}

	reference operator*() { return reference(*m_it0, *m_it1); }
	value_type operator*() const { return value_type(*m_it0, *m_it1); }

	difference_type operator-(const DualIterator& other) const
	{
		assert(m_it0 - other.m_it0 == m_it1 - other.m_it1);
		// the iterators always need to have the same position
		// (incomplete check but the best we can do without having also begin / end in either vector)

		return m_it0 - other.m_it0;
	}

	bool operator==(const DualIterator& other) const
	{
		assert(m_it0 - other.m_it0 == m_it1 - other.m_it1);
		return m_it0 == other.m_it0;
	}

	bool operator!=(const DualIterator& other) const { return !(*this == other); }

	bool operator<(const DualIterator& other) const
	{
		assert(m_it0 - other.m_it0 == m_it1 - other.m_it1);
		return m_it0 < other.m_it0;
	}

	bool operator>=(const DualIterator& other) const { return !(*this < other); }
	bool operator<=(const DualIterator& other) const { return !(other < *this); }
	bool operator>(const DualIterator& other) const { return other < *this; }

	DualIterator operator+(distance_type d) const { return DualIterator(m_it0 + d, m_it1 + d); }
	DualIterator operator-(distance_type d) const { return *this + -d; }

	DualIterator& operator+=(distance_type d){ return *this = *this + d; }
	DualIterator& operator-=(distance_type d) { return *this = *this + -d; }

	DualIterator& operator++() { return *this += 1; }
	DualIterator& operator--() { return *this += -1; }

	DualIterator operator++(int) // msvc sort actually needs this, g++ does not
	{
		DualIterator old = *this;
		++(*this);
		return old;
	}

	DualIterator operator--(int)
	{
		DualIterator old = *this;
		--(*this);
		return old;
	}
};

template <class It0, class It1>
inline DualIterator<It0, It1> make_dual_iterator(It0 it0, It1 it1)
{
	return DualIterator<It0, It1>(it0, it1);
}

using namespace mud; namespace toy
{
	using string = std::string;

	/*class StopWatchExtensions
	{
	public:
		static float ElapsedMicroseconds(this Stopwatch sw)
		{
			return sw.ElapsedTicks / (Stopwatch.Frequency / 1000000f);
		}
	};*/

	class MiscUtils
	{
	public:
		template <class T>
		static std::vector<int> GetSortMap(array<T> original, array<T> sorted)
		{
			auto deltas = new int[original.m_count];
			for(auto i = 0; i < original.m_count; i++)
				deltas[i] = sorted.IndexOf(original[i]);
			return deltas;
		}
	};

	class BitUtils
	{
	public:
		static int BitPosition(uint32_t flag)
		{
			for(int i = 0; i < 32; i++)
				if(flag >> i == 1)
					return i;
			return -1;
		}

		static int BitPosition(uint64_t flag)
		{
			for(int i = 0; i < 64; i++)
				if(flag >> i == 1)
					return i;
			return -1;
		}

		static uint32_t BitCount(uint32_t flags)
		{
			flags = flags - ((flags >> 1)&  0x55555555u);
			flags = (flags&  0x33333333u) + ((flags >> 2)&  0x33333333u);
			return (((flags + (flags >> 4))&  0x0F0F0F0Fu) * 0x01010101u) >> 24;
		}

#define unchecked(x) x

		static uint64_t BitCount(uint64_t flags)
		{
			flags = flags - ((flags >> 1)&  0x5555555555555555ul);
			flags = (flags&  0x3333333333333333ul) + ((flags >> 2)&  0x3333333333333333ul);
			return unchecked(((flags + (flags >> 4))&  0xF0F0F0F0F0F0F0Ful) * 0x101010101010101ul) >> 56;
		}
#undef unchecked
	};

	class IDebugString
	{
	public:
		virtual string GetDebugString(bool detailed) = 0;
	};
}