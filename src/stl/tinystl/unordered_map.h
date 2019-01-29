#pragma once

#include <stl/tinystl/allocator.h>
#include <stl/tinystl/buffer.h>
#include <stl/tinystl/hash.h>
#include <stl/tinystl/hash_base.h>

namespace tinystl {

	template<typename Key, typename Value, typename Alloc = TINYSTL_ALLOCATOR>
	class unordered_map {
	public:
		unordered_map();
		unordered_map(const unordered_map& other);
		unordered_map(unordered_map&& other);
		~unordered_map();

		unordered_map& operator=(const unordered_map& other);
		unordered_map& operator=(unordered_map&& other);

		typedef pair<Key, Value> value_type;

		typedef unordered_hash_iterator<const unordered_hash_node<Key, Value> > const_iterator;
		typedef unordered_hash_iterator<unordered_hash_node<Key, Value> > iterator;

		iterator begin();
		iterator end();

		const_iterator begin() const;
		const_iterator end() const;

		void clear();
		bool empty() const;
		size_t size() const;

		const_iterator find(const Key& key) const;
		iterator find(const Key& key);
		pair<iterator, bool> insert(const pair<Key, Value>& p);
		pair<iterator, bool> insert(pair<Key, Value>&& p);
		pair<iterator, bool> emplace(pair<Key, Value>&& p);
		void erase(const_iterator where);
		void erase(const Key& key);

		Value& operator[](const Key& key);

		void swap(unordered_map& other);

	private:

		void rehash(size_t nbuckets);

		typedef unordered_hash_node<Key, Value>* pointer;

		size_t m_size;
		tinystl::buffer<pointer, Alloc> m_buckets;
	};
}
