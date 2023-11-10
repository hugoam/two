#pragma once

#ifndef TWO_MODULES
#include <cassert>
#include <atomic>
#include <stl/stddef.h>
#endif
#include <jobs/Forward.h>

namespace two
{
	template <class T, size_t Count>
	class StealQueue
	{
		static_assert(!(Count & (Count - 1)), "Count must be a power of two");
		static constexpr size_t Mask = Count - 1;
		std::atomic<int32_t> m_top = { 0 };      // written/read in pop()/steal()
		std::atomic<int32_t> m_bottom = { 0 };   // written only in pop(), read in push(), steal()
		T m_items[Count];

		T at(int32_t index) { return m_items[index & Mask]; }
		void set(int32_t index, T item) { m_items[index & Mask] = item; }

	public:
		using value_type = T;

		inline void push(T item);
		inline T pop();
		inline T steal();

		size_t size() const { return Count; }

		bool empty() const
		{
			uint32_t bottom = (uint32_t)m_bottom.load(std::memory_order_relaxed);
			uint32_t top = (uint32_t)m_top.load(std::memory_order_seq_cst);
			return top >= bottom;
		}

		int32_t count() const
		{
			int32_t bottom = m_bottom.load(std::memory_order_relaxed);
			int32_t top = m_top.load(std::memory_order_relaxed);
			return bottom - top;
		}
	};


	template <class T, size_t Count>
	void StealQueue<T, Count>::push(T item)
	{
		int32_t bottom = m_bottom.load(std::memory_order_relaxed);
		set(bottom, item);
		m_bottom.store(bottom + 1, std::memory_order_release);
	}

	template <class T, size_t Count>
	T StealQueue<T, Count>::pop()
	{
		int32_t bottom = m_bottom.fetch_sub(1, std::memory_order_relaxed) - 1;
		int32_t top = m_top.load(std::memory_order_seq_cst);

		if(top < bottom)
		{
			return at(bottom);
		}

		T item{};
		if(top == bottom)
		{
			item = at(bottom);

			if(m_top.compare_exchange_strong(top, top + 1, std::memory_order_seq_cst, std::memory_order_relaxed))
			{
				top++;
			}
			else
			{
				item = T();
			}
		}

		m_bottom.store(top, std::memory_order_relaxed);
		return item;
	}

	template <class T, size_t Count>
	T StealQueue<T, Count>::steal()
	{
		do {
			int32_t top = m_top.load(std::memory_order_seq_cst);
			int32_t bottom = m_bottom.load(std::memory_order_acquire);

			if(top >= bottom)
			{
				return T();
			}

			T item(at(top));
			if(m_top.compare_exchange_strong(top, top + 1, std::memory_order_seq_cst, std::memory_order_relaxed))
			{
				return item;
			}
		} while(true);
	}
}
