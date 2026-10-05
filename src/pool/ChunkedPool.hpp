//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <pool/ChunkedPool.h>

namespace two
{
	// the index of the lowest bit set
	inline uint32_t lowest_bit(uint64_t bits)
	{
		static const uint8_t indices[64] = {
			 0,  1, 48,  2, 57, 49, 28,  3, 61, 58, 50, 42, 38, 29, 17,  4,
			62, 55, 59, 36, 53, 51, 43, 22, 45, 39, 33, 30, 24, 18, 12,  5,
			63, 47, 56, 27, 60, 41, 37, 16, 54, 35, 52, 21, 44, 32, 23, 11,
			46, 26, 40, 15, 34, 20, 31, 10, 25, 14, 19,  9, 13,  8,  7,  6
		};
		return indices[((bits & (~bits + 1)) * 0x03f79d71b4cb0a89ULL) >> 58];
	}

	template <class T>
	ChunkedPool<T>::ChunkedPool(uint32_t chunk_size)
		: m_chunk_size(chunk_size)
		, m_words((chunk_size + 63) / 64)
	{}

	template <class T>
	ChunkedPool<T>::~ChunkedPool()
	{
		this->clear();
	}

	template <class T>
	inline T& ChunkedPool<T>::add(const T& value, uint32_t colour)
	{
		T* at = this->talloc(colour);
		new (stl::placeholder(), at) T(value);
		return *at;
	}

	// an object of a colour goes in a chunk of that colour with a free slot, or in a new chunk for that colour
	template <class T>
	inline T* ChunkedPool<T>::talloc(uint32_t colour)
	{
		Colour& group = this->find_colour(colour);
		if(group.m_open.empty())
		{
			Chunk* chunk = m_empty.empty() ? this->create_chunk() : pop(m_empty);
			chunk->m_colour = colour;
			chunk->m_index = uint32_t(group.m_chunks.size());
			chunk->m_open = uint32_t(group.m_open.size());
			group.m_chunks.push_back(chunk);
			group.m_open.push_back(chunk);
		}

		Chunk& chunk = *group.m_open.back();
		uint32_t word = 0;
		while(chunk.m_live[word] == ~uint64_t(0))
			++word;
		uint32_t bit = lowest_bit(~chunk.m_live[word]);
		chunk.m_live[word] |= uint64_t(1) << bit;

		if(++chunk.m_count == m_chunk_size)
		{
			group.m_open.pop_back();
			chunk.m_open = none;
		}
		return &chunk.m_slots[word * 64 + bit];
	}

	template <class T>
	inline void ChunkedPool<T>::tdestroy(T& object)
	{
		any_destruct(object);
		this->tfree(object);
	}

	// a chunk with a free slot is open for its colour again, and an empty chunk is recycled
	template <class T>
	inline void ChunkedPool<T>::tfree(T& object)
	{
		Chunk& chunk = *this->chunk_of(&object);
		uint32_t slot = uint32_t(&object - chunk.m_slots);
		chunk.m_live[slot / 64] &= ~(uint64_t(1) << (slot % 64));

		Colour& group = this->find_colour(chunk.m_colour);
		auto unlist = [](vector<Chunk*>& chunks, uint32_t index, uint32_t Chunk::*position)
		{
			chunks.back()->*position = index;
			swap_pop(chunks, index);
		};

		if(--chunk.m_count == 0)
		{
			if(chunk.m_open != none)
				unlist(group.m_open, chunk.m_open, &Chunk::m_open);
			unlist(group.m_chunks, chunk.m_index, &Chunk::m_index);
			m_empty.push_back(&chunk);
		}
		else if(chunk.m_open == none)
		{
			chunk.m_open = uint32_t(group.m_open.size());
			group.m_open.push_back(&chunk);
		}
	}

	template <class T>
	void ChunkedPool<T>::alloc(Ref& ref) { setval<T>(ref, this->talloc()); }
	template <class T>
	Ref ChunkedPool<T>::alloc() { return Ref(this->talloc(), type<T>()); }
	template <class T>
	void ChunkedPool<T>::destroy(Ref object) { this->tdestroy(val<T>(object)); }
	template <class T>
	void ChunkedPool<T>::free(Ref object) { this->tfree(val<T>(object)); }

	template <class T>
	void ChunkedPool<T>::reset() { this->clear(); }

	template <class T>
	void ChunkedPool<T>::clear()
	{
		for(unique<Chunk>& chunk : m_chunks)
			iterate_chunk(*chunk, m_words, [](T& object) { any_destruct(object); });
		m_chunks.clear();
		m_empty.clear();
		m_colours.clear();
		m_colour_index.clear();
	}

	template <class T>
	template <class... Types>
	inline T& ChunkedPool<T>::construct(Types&&... args)
	{
		return this->construct_in(0, static_cast<Types&&>(args)...);
	}

	template <class T>
	template <class... Types>
	inline T& ChunkedPool<T>::construct_in(uint32_t colour, Types&&... args)
	{
		T* at = this->talloc(colour);
		new (stl::placeholder(), at) T(static_cast<Types&&>(args)...);
		return *at;
	}

	template <class T>
	template <class T_Func>
	inline void ChunkedPool<T>::iterate_chunk(const Chunk& chunk, uint32_t words, T_Func func)
	{
		for(uint32_t word = 0; word < words; ++word)
			for(uint64_t bits = chunk.m_live[word]; bits; bits &= bits - 1)
				func(chunk.m_slots[word * 64 + lowest_bit(bits)]);
	}

	template <class T>
	template <class T_Func>
	inline void ChunkedPool<T>::iterate(T_Func func) const
	{
		for(const unique<Chunk>& chunk : m_chunks)
			if(chunk->m_count)
				iterate_chunk(*chunk, m_words, func);
	}

	template <class T>
	template <class T_Func>
	inline void ChunkedPool<T>::iterate(uint32_t colour, T_Func func) const
	{
		auto it = m_colour_index.find(colour);
		if(it != m_colour_index.end())
			for(Chunk* chunk : m_colours[it->second].m_chunks)
				iterate_chunk(*chunk, m_words, func);
	}

	template <class T>
	template <class T_Test>
	inline T* ChunkedPool<T>::find(T_Test test) const
	{
		T* found = nullptr;
		this->iterate([&](T& object) { if(!found && test(object)) found = &object; });
		return found;
	}

	template <class T>
	inline typename ChunkedPool<T>::Colour& ChunkedPool<T>::find_colour(uint32_t colour)
	{
		auto it = m_colour_index.find(colour);
		if(it != m_colour_index.end())
			return m_colours[it->second];
		m_colour_index[colour] = uint32_t(m_colours.size());
		m_colours.emplace_back();
		return m_colours.back();
	}

	// the storage of a chunk never grows: the objects never move
	template <class T>
	inline typename ChunkedPool<T>::Chunk* ChunkedPool<T>::create_chunk()
	{
		unique<Chunk> chunk = make_unique<Chunk>();
		chunk->m_live.resize(m_words, 0);
		chunk->m_storage.resize(m_chunk_size);
		chunk->m_slots = reinterpret_cast<T*>(chunk->m_storage.data());

		Chunk* result = chunk.get();
		size_t at = m_chunks.size();
		while(at > 0 && m_chunks[at - 1]->m_slots > result->m_slots)
			--at;
		m_chunks.insert(m_chunks.begin() + at, move(chunk));
		return result;
	}

	template <class T>
	inline typename ChunkedPool<T>::Chunk* ChunkedPool<T>::chunk_of(T* object) const
	{
		size_t first = 0;
		size_t count = m_chunks.size();
		while(count > 0)
		{
			size_t step = count / 2;
			if(m_chunks[first + step]->m_slots <= object)
			{
				first += step + 1;
				count -= step + 1;
			}
			else
				count = step;
		}
		return m_chunks[first - 1].get();
	}

	template <class T>
	inline ChunkedPool<T>& global_pool()
	{
		if(!g_pools[type<T>().m_id])
			g_pools[type<T>().m_id] = make_unique<ChunkedPool<T>>();
		return as<ChunkedPool<T>>(*g_pools[type<T>().m_id].get());
	}
}
