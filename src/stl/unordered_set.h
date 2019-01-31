#pragma once

#ifdef USE_STL
#include <unordered_set>
#else
#include <stl/allocator.h>
#include <stl/buffer.h>
#include <stl/hash.h>
#include <stl/hash_base.h>

namespace stl {

	template <class Key, class Alloc = TINYSTL_ALLOCATOR>
	class unordered_set {
	public:
		unordered_set();
		unordered_set(const unordered_set& other);
		unordered_set(unordered_set&& other);
		~unordered_set();

		unordered_set& operator=(const unordered_set& other);
		unordered_set& operator=(unordered_set&& other);

		typedef unordered_hash_iterator<const unordered_hash_node<Key, void> > const_iterator;
		typedef const_iterator iterator;

		iterator begin() const;
		iterator end() const;

		void clear();
		bool empty() const;
		size_t size() const;

		iterator find(const Key& key) const;
		pair<iterator, bool> insert(const Key& key);
		pair<iterator, bool> emplace(Key&& key);
		void erase(iterator where);
		size_t erase(const Key& key);

		void swap(unordered_set& other);

	private:

		void rehash(size_t nbuckets);

		typedef unordered_hash_node<Key, void>* pointer;

		size_t m_size;
		stl::buffer<pointer, Alloc> m_buckets;
	};

}
#endif

namespace mud
{
	using stl::unordered_set;
}