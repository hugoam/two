//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <pool/Forward.h>
#include <pool/Pool.h>

namespace two
{
	// a pool of objects stored in chunks of a fixed number of slots, where the objects don't move
	// each chunk holds the objects of a single colour: an optional hint from the caller to group the objects used together, e.g the states of the nodes of one tree
	export_ template <class T>
	class refl_ ChunkedPool : public Pool
	{
	public:
		static constexpr uint32_t none = UINT32_MAX;

		// the memory of an object, constructed and destroyed in place: an object never moves, it doesn't need to be movable
		struct Slot { alignas(T) uint8_t m_bytes[sizeof(T)]; };

		struct Chunk
		{
			uint32_t m_colour = 0;
			uint32_t m_count = 0;		// the slots holding an object
			uint32_t m_index = 0;		// position in the chunks of its colour
			uint32_t m_open = none;		// position in the chunks of its colour with a free slot, or none
			vector<uint64_t> m_live;	// which slots hold an object
			vector<Slot> m_storage;		// the memory of the slots
			T* m_slots = nullptr;
		};

		struct Colour
		{
			vector<Chunk*> m_chunks;
			vector<Chunk*> m_open;
		};

		ChunkedPool(uint32_t chunk_size = 64);
		~ChunkedPool();

		ChunkedPool(const ChunkedPool& other) = delete;
		ChunkedPool& operator=(const ChunkedPool& other) = delete;

		meth_ T& add(const T& value, uint32_t colour = 0);
		vector<T*> addvec(span<T> values, uint32_t colour = 0);

		meth_ T* talloc(uint32_t colour = 0);
		meth_ void tdestroy(T& object);
		meth_ void tfree(T& object);

		virtual void alloc(Ref& ref) override;
		virtual Ref alloc() override;

		virtual void destroy(Ref object) override;
		virtual void free(Ref object) override;

		virtual void reset() override;
		virtual void clear() override;

		template <class... Types>
		T& construct(Types&&... args);

		template <class... Types>
		T& construct_in(uint32_t colour, Types&&... args);

		template <class T_Func>
		void iterate(T_Func func) const;

		template <class T_Func>
		void iterate(uint32_t colour, T_Func func) const;

		template <class T_Test>
		T* find(T_Test test) const;

		uint32_t m_chunk_size;
		uint32_t m_words;

		vector<unique<Chunk>> m_chunks;				// all the chunks, sorted by address, to find the chunk of an object
		vector<Chunk*> m_empty;							// the empty chunks, recycled for any colour
		vector<Colour> m_colours;
		unordered_map<uint32_t, uint32_t> m_colour_index;

	private:
		Colour& find_colour(uint32_t colour);
		Chunk* create_chunk();
		Chunk* chunk_of(T* object) const;

		template <class T_Func>
		static void iterate_chunk(const Chunk& chunk, uint32_t words, T_Func func);
	};
}
