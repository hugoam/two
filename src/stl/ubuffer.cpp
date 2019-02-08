#pragma once

#include <stl/vector.h>
#include <stl/ubuffer.h>
#include <stl/ubuffer.hpp>

#if defined(WIN32)
#include <malloc.h>
#else
#include <cstdlib>
#endif

#include <cstring>
#include <cassert>

namespace stl {

	void ubuffer::construct(size_t type_size)
	{
		m_type_size = type_size;
	}

	void ubuffer::construct(const ubuffer& rhs, CopyConstructPtr copy_constructor)
	{
		// Copy properties from source ubuffer
		m_size = rhs.m_size;
		m_capacity = rhs.m_capacity;
		m_type_size = rhs.m_type_size;

		// Allocate m_capacity
		m_items = (uint8_t*)malloc(m_capacity * m_type_size);

		if(copy_constructor)
		{
			// Copy m_construct all m_items from source ubuffer
			uint8_t* dest_item = m_items;
			uint8_t* src_item = rhs.m_items;
			for(size_t i = 0; i < m_size; i++)
			{
				copy_constructor(dest_item, src_item);
				dest_item += m_type_size;
				src_item += m_type_size;
			}
		}

		else
		{
			// Memory copy is safe otherwise
			memcpy(m_items, rhs.m_items, m_size * m_type_size);
		}
	}


	void ubuffer::construct(size_t type_size, size_t size)
	{
		m_size = size;
		m_capacity = size;
		m_type_size = type_size;

		// Allocate m_capacity
		m_items = (uint8_t*)malloc(m_capacity * m_type_size);
	}

	void ubuffer::construct(size_t type_size, size_t size, ConstructPtr constructor)
	{
		this->construct(type_size, size);

		// Call default constructor for all m_items
		uint8_t* item_ptr = m_items;
		for(size_t i = 0; i < m_size; i++)
		{
			constructor(item_ptr);
			item_ptr += m_type_size;
		}
	}

	void ubuffer::destruct(DestructPtr destructor)
	{
		if(m_items != nullptr)
		{
			this->clear(destructor);
			free(m_items);
		}
	}

	void ubuffer::reserve(size_t capacity, MoveConstructPtr move_constructor, DestructPtr destructor)
	{
		// Only reserve larger capacities
		if(capacity > m_capacity)
		{
			// Allocate a new set of data with an aligned m_size
			m_capacity = capacity;//AlignPow2(capacity, 16);
			uint8_t* new_items = (uint8_t*)malloc(m_capacity * m_type_size);

			// Need to copy existing m_items to the new storage area
			if(m_items != nullptr)
			{
				// Memory walk is far more expensive than an extra outer loop branch so try to do everything in
				// one pass with trickier code than using the simpler two pass approach.

				if(move_constructor)
				{
					if(destructor)
					{
						// Copy m_construct the old data to the new location while destructing the old data
						uint8_t* dest_item = new_items;
						uint8_t* src_item = m_items;
						for(size_t i = 0; i < m_size; i++)
						{
							move_constructor(dest_item, src_item);
							destructor(src_item);
							dest_item += m_type_size;
							src_item += m_type_size;
						}
					}

					else
					{
						// Destruction not required so just copy m_construct all m_items to the new location
						uint8_t* dest_item = new_items;
						uint8_t* src_item = m_items;
						for(size_t i = 0; i < m_size; i++)
						{
							move_constructor(dest_item, src_item);
							dest_item += m_type_size;
							src_item += m_type_size;
						}
					}
				}

				else
				{
					// No construction required so use a byte copy
					memcpy(new_items, m_items, m_size * m_type_size);

					// Call destructor on old m_items if required
					if(destructor)
					{
						uint8_t* item_ptr = m_items;
						for(size_t i = 0; i < m_size; i++)
						{
							destructor(item_ptr);
							item_ptr += m_type_size;
						}
					}
				}

				// Release old item storage
				free(m_items);
			}

			m_items = new_items;
		}
	}


	void ubuffer::resize(size_t size, ConstructPtr constructor, MoveConstructPtr move_constructor, DestructPtr destructor)
	{
		// Ensure there's enough allocated memory
		// TODO: Better growth strategy
		if(size > m_capacity)
			this->reserve(size, move_constructor, destructor);

		// Destruct elements above the new m_size
		if(size < m_size && destructor)
		{
			uint8_t* item_ptr = m_items + size * m_type_size;
			for(size_t i = size; i < m_size; i++)
			{
				destructor(item_ptr);
				item_ptr += m_type_size;
			}
		}

		// Default m_construct elements above the old m_size
		else if(size > m_size && constructor)
		{
			uint8_t* item_ptr = m_items + m_size * m_type_size;
			for(size_t i = m_size; i < size; i++)
			{
				constructor(item_ptr);
				item_ptr += m_type_size;
			}
		}

		m_size = size;
	}

	void ubuffer::clear(DestructPtr destructor)
	{
		// Destruct all m_items if required
		if(destructor)
		{
			uint8_t* item_ptr = m_items;
			for(size_t i = 0; i < m_size; i++)
			{
				destructor(item_ptr);
				item_ptr += m_type_size;
			}
		}

		m_size = 0;
	}

	void* ubuffer::push_back(const void* object, MoveConstructPtr move_constructor, CopyConstructPtr copy_constructor, DestructPtr destructor)
	{
		// Ensure there's enough space to store the new item
		this->reserve(m_size + 1, move_constructor, destructor);

		// Copy new item to the end of the vector
		// TODO: Improve performance with a switch on common integer types sizes?
		uint8_t* dest_item = m_items + m_size * m_type_size;
		if(copy_constructor)
			copy_constructor(dest_item, object);
		else
			memcpy(dest_item, object, m_type_size);

		m_size++;

		return dest_item;
	}

	void* ubuffer::push_back(void* object, MoveConstructPtr move_constructor, DestructPtr destructor)
	{
		// Ensure there's enough space to store the new item
		this->reserve(m_size + 1, move_constructor, destructor);

		// Copy new item to the end of the vector
		// TODO: Improve performance with a switch on common integer types sizes?
		uint8_t* dest_item = m_items + m_size * m_type_size;
		if(move_constructor)
			move_constructor(dest_item, object);
		else
			memcpy(dest_item, object, m_type_size);

		m_size++;

		return dest_item;
	}

#if 0
	void ubuffer::add(const void* object, CopyConstructPtr copy_constructor, DestructPtr destructor, EqualPtr equal)
	{
		// Leave, not adding if the item already exists
		uint8_t* item_ptr = m_items;
		for(size_t i = 0; i < m_size; i++)
		{
			if(equal(item_ptr, object))
				return;
		}

		this->push_back(object, copy_constructor, destructor);
	}
#endif

	void ubuffer::pop_back(DestructPtr destructor)
	{
		assert(m_size > 0);

		m_size--;

		if(destructor)
			destructor(m_items + m_size * m_type_size);
	}


	void ubuffer::remove_unstable(size_t index, DestructPtr destructor, MovePtr move)
	{
		// Copy from the back over the top of the item being removed
		// Copy function will always contain the optimal compiler-generated copy,
		// which includes calling the destructor on the dest object
		uint8_t* last_item = m_items + (m_size - 1) * m_type_size;
		move(m_items + index * m_type_size, last_item);

		// Destruct the copied item
		if(destructor)
			destructor(last_item);

		m_size--;
	}


	void ubuffer::remove(size_t index, DestructPtr destructor, MovePtr move)
	{
		// Shift all m_items above the removed item, one down
		// TODO: memcpy everything for trivial destructor + assignment
		uint8_t* item_ptr = m_items + index * m_type_size;
		for(size_t i = index; i < m_size - 1; i++)
		{
			move(item_ptr, item_ptr + m_type_size);
			item_ptr += m_type_size;
		}

		// Destruct the left over item
		if(destructor)
			destructor(item_ptr);

		m_size--;
	}


	void ubuffer::remove(size_t start, size_t count, DestructPtr destructor, MovePtr move)
	{
		size_t end = start + count;
		assert(end <= m_size);
		size_t left_over = m_size - end;

		// Shift all m_items above the removed m_items down
		// TODO: memcpy? Needs trivial assign detection
		uint8_t* dest_item = m_items + start * m_type_size;
		uint8_t* src_item = dest_item + count * m_type_size;
		for(size_t i = 0; i < left_over; i++)
		{
			move(dest_item, src_item);
			dest_item += m_type_size;
			src_item += m_type_size;
		}

		// Destruct the m_items left behind at the top
		if(destructor)
		{
			uint8_t* item_ptr = m_items + end * m_type_size;
			for(size_t i = end; i < m_size; i++)
			{
				destructor(item_ptr);
				item_ptr += m_type_size;
			}
		}

		m_size -= count;
	}


	void ubuffer::assign(const ubuffer& src, MoveConstructPtr move_constructor, CopyConstructPtr copy_constructor, DestructPtr destructor)
	{
		// Empty and ensure there's enough m_capacity
		this->clear(destructor);
		this->reserve(src.m_size, move_constructor, destructor);

		if(copy_constructor)
		{
			// Copy m_construct all m_items over from source
			uint8_t* dest_item = m_items;
			uint8_t* src_item = src.m_items;
			for(size_t i = 0; i < src.m_size; i++)
			{
				copy_constructor(dest_item, src_item);
				dest_item += m_type_size;
				src_item += m_type_size;
			}
		}
		else
		{
			// Bit copy instead
			memcpy(m_items, src.m_items, src.m_size * m_type_size);
		}

		m_size = src.m_size;
	}
}
