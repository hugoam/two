#pragma once

#include <cassert>
#include <stl/stddef.h>
#include <stdint.h>
#include <climits>

#include <stl/traits.h>

namespace stl
{
	template <class T>
	inline T popcount(T v)
	{
		static_assert(sizeof(T) * 8 <= 128, "popcount() only support up to 128 bits");
		const T ONES = ~T(0);
		v = v - ((v >> 1) & ONES / 3);
		v = (v & ONES / 15 * 3) + ((v >> 2) & ONES / 15 * 3);
		v = (v + (v >> 4)) & ONES / 255 * 15;
		return (T)(v * (ONES / 255)) >> (sizeof(T) - 1) * CHAR_BIT;
	}

	template <class T>
	inline T clz(T x)
	{
		static_assert(sizeof(T) <= sizeof(uint64_t), "clz() only support up to 64 bits");
		x |= (x >> 1);
		x |= (x >> 2);
		x |= (x >> 4);
		x |= (x >> 8);
		x |= (x >> 16);
		if(sizeof(T) * 8 > 32) { // if() only needed to quash compiler warnings
			x |= (x >> 32);
		}
		return (sizeof(T) * CHAR_BIT) - popcount(x);
	}

	template <class T>
	inline T ctz(T x)
	{
		static_assert(sizeof(T) <= sizeof(uint64_t), "ctz() only support up to 64 bits");
		T c = sizeof(T) * 8;
		x &= -signed(x);
		if(x) c--;
		if(sizeof(T) * 8 > 32) { // if() only needed to quash compiler warnings
			if(x & 0x00000000FFFFFFFF) c -= 32;
		}
		if(x & 0x0000FFFF) c -= 16;
		if(x & 0x00FF00FF) c -= 8;
		if(x & 0x0F0F0F0F) c -= 4;
		if(x & 0x33333333) c -= 2;
		if(x & 0x55555555) c -= 1;
		return c;
	}

	// This bitset<> class is different from std::bitset<> in that it allows us to control
	// the exact storage size. This is useful for small bitset (e.g. < 64, on 64-bits machines).
	// It also allows for lexicographical compares (i.e. sorting).

	template <class T, size_t N = 1, typename = enable_if<is_integral<T> && is_unsigned<T>>>
	class bitset {
		T storage[N] = {};

	public:
		static constexpr T BITS_PER_WORD = sizeof(T) * 8;
		static constexpr T BIT_COUNT = BITS_PER_WORD * N;
		static constexpr T WORLD_COUNT = N;
		using container_type = T;

		bitset()
		{}

		T at(size_t n) const
		{
			return storage[n];
		}

		T& at(size_t n)
		{
			return storage[n];
		}

		T get_bits() const
		{
			static_assert(N == 1, "bitfield must only have one storage word");
			return storage[0];
		}

		void set_bits(T value)
		{
			static_assert(N == 1, "bitfield must only have one storage word");
			storage[0] = value;
		}

		template <class F>
		void for_each(F exec) const
		{
			for(size_t i = 0; i < N; i++)
			{
				T v = storage[i];
				while(v)
				{
					T k = ctz(v);
					v &= ~(T(1) << k);
					exec(size_t(k + BITS_PER_WORD * i));
				}
			}
		}

		size_t size() const { return N * BITS_PER_WORD; }

		bool test(size_t bit) const { return operator[](bit); }

		void set(size_t b)
		{
			storage[b / BITS_PER_WORD] |= T(1) << (b % BITS_PER_WORD);
		}

		void set(size_t b, bool value)
		{
			storage[b / BITS_PER_WORD] &= ~(T(1) << (b % BITS_PER_WORD));
			storage[b / BITS_PER_WORD] |= T(value) << (b % BITS_PER_WORD);
		}

		void unset(size_t b)
		{
			storage[b / BITS_PER_WORD] &= ~(T(1) << (b % BITS_PER_WORD));
		}

		void flip(size_t b)
		{
			storage[b / BITS_PER_WORD] ^= T(1) << (b % BITS_PER_WORD);
		}

		void reset()
		{
			*this = {};
		}

		bool operator[](size_t b) const
		{
			return (storage[b / BITS_PER_WORD] & (T(1) << (b % BITS_PER_WORD))) != 0;
		}

		T count() const
		{
			T r = popcount(storage[0]);
			for(size_t i = 1; i < N; ++i)
				r += popcount(storage[i]);
			return r;
		}

		bool any() const
		{
			T r = storage[0];
			for(size_t i = 1; i < N; ++i)
				r |= storage[i];
			return r != 0;
		}

		bool none() const { return !any(); }

		bool all() const
		{
			T r = storage[0];
			for(size_t i = 1; i < N; ++i)
				r &= storage[i];
			return T(~r) == T(0);
		}

		bool operator!=(const bitset& b) const
		{
			T r = storage[0] ^ b.storage[0];
			for(size_t i = 1; i < N; ++i)
				r |= storage[i] ^ b.storage[i];
			return r != 0;
		}

		bool operator==(const bitset& b) const { return !operator!=(b); }

		bitset& operator&=(const bitset& b) { for(size_t i = 0; i < N; ++i) storage[i] &= b.storage[i]; return *this; }
		bitset& operator|=(const bitset& b) { for(size_t i = 0; i < N; ++i) storage[i] |= b.storage[i]; return *this; }
		bitset& operator^=(const bitset& b) { for(size_t i = 0; i < N; ++i) storage[i] ^= b.storage[i]; return *this; }
		bitset operator~() const { bitset r; for(size_t i = 0; i < N; ++i) r.storage[i] = ~storage[i]; return r; }

	private:

		friend bitset operator&(const bitset& lhs, const bitset& rhs) { return bitset(lhs) &= rhs; }
		friend bitset operator|(const bitset& lhs, const bitset& rhs) { return bitset(lhs) |= rhs; }
		friend bitset operator^(const bitset& lhs, const bitset& rhs) { return bitset(lhs) ^= rhs; }
	};

	using bitset8 = bitset<uint8_t>;
	using bitset32 = bitset<uint32_t>;
	using bitset256 = bitset<uint64_t, 4>;

	static_assert(sizeof(bitset8) == sizeof(uint8_t), "bitset8 isn't 8 bits!");
	static_assert(sizeof(bitset32) == sizeof(uint32_t), "bitset32 isn't 32 bits!");

}

namespace mud
{
	using stl::bitset;
}