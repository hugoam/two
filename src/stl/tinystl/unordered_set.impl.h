#pragma once

#include <stl/tinystl/buffer_base.h>
#include <stl/tinystl/unordered_set.h>

namespace tinystl {

	template<typename Key, typename Alloc>
	inline unordered_set<Key, Alloc>::unordered_set()
		: m_size(0)
	{
		buffer_resize<pointer, Alloc>(m_buckets, 9, 0);
	}

	template<typename Key, typename Alloc>
	inline unordered_set<Key, Alloc>::unordered_set(const unordered_set& other)
		: m_size(other.m_size)
	{
		const size_t nbuckets = (size_t)(other.m_buckets.last - other.m_buckets.first);
		buffer_resize<pointer, Alloc>(m_buckets, nbuckets, 0);

		for (pointer it = *other.m_buckets.first; it; it = it->next) {
			unordered_hash_node<Key, void>* newnode = new(placeholder(), Alloc::static_allocate(sizeof(unordered_hash_node<Key, void>))) unordered_hash_node<Key, void>(*it);
			newnode->next = newnode->prev = 0;
			unordered_hash_node_insert(newnode, hash(it->first), m_buckets.first, nbuckets - 1);
		}
	}

	template<typename Key, typename Alloc>
	inline unordered_set<Key, Alloc>::unordered_set(unordered_set&& other)
		: m_size(other.m_size)
	{
		buffer_move(m_buckets, other.m_buckets);
		other.m_size = 0;
	}

	template<typename Key, typename Alloc>
	inline unordered_set<Key, Alloc>::~unordered_set() {
		if (m_buckets.first != m_buckets.last)
			clear();
		buffer_destroy<pointer, Alloc>(m_buckets);
	}

	template<typename Key, typename Alloc>
	inline unordered_set<Key, Alloc>& unordered_set<Key, Alloc>::operator=(const unordered_set<Key, Alloc>& other) {
		unordered_set<Key, Alloc>(other).swap(*this);
		return *this;
	}

	template<typename Key, typename Alloc>
	inline unordered_set<Key, Alloc>& unordered_set<Key, Alloc>::operator=(unordered_set&& other) {
		unordered_set(static_cast<unordered_set&&>(other)).swap(*this);
		return *this;
	}

	template<typename Key, typename Alloc>
	inline typename unordered_set<Key, Alloc>::iterator unordered_set<Key, Alloc>::begin() const {
		iterator cit;
		cit.node = *m_buckets.first;
		return cit;
	}

	template<typename Key, typename Alloc>
	inline typename unordered_set<Key, Alloc>::iterator unordered_set<Key, Alloc>::end() const {
		iterator cit;
		cit.node = 0;
		return cit;
	}

	template<typename Key, typename Alloc>
	inline bool unordered_set<Key, Alloc>::empty() const {
		return m_size == 0;
	}

	template<typename Key, typename Alloc>
	inline size_t unordered_set<Key, Alloc>::size() const {
		return m_size;
	}

	template<typename Key, typename Alloc>
	inline void unordered_set<Key, Alloc>::clear() {
		pointer it = *m_buckets.first;
		while (it) {
			const pointer next = it->next;
			it->~unordered_hash_node<Key, void>();
			Alloc::static_deallocate(it, sizeof(unordered_hash_node<Key, void>));

			it = next;
		}

		m_buckets.last = m_buckets.first;
		buffer_resize<pointer, Alloc>(m_buckets, 9, 0);
		m_size = 0;
	}

	template<typename Key, typename Alloc>
	inline typename unordered_set<Key, Alloc>::iterator unordered_set<Key, Alloc>::find(const Key& key) const {
		iterator result;
		result.node = unordered_hash_find(key, m_buckets.first, (size_t)(m_buckets.last - m_buckets.first));
		return result;
	}

	template<typename Key, typename Alloc>
	inline void unordered_set<Key, Alloc>::rehash(size_t nbuckets) {
		if (m_size + 1 > 4 * nbuckets) {
			pointer root = *m_buckets.first;

			const size_t newnbuckets = ((size_t)(m_buckets.last - m_buckets.first) - 1) * 8;
			m_buckets.last = m_buckets.first;
			buffer_resize<pointer, Alloc>(m_buckets, newnbuckets + 1, 0);
			unordered_hash_node<Key, void>** buckets = m_buckets.first;

			while (root) {
				const pointer next = root->next;
				root->next = root->prev = 0;
				unordered_hash_node_insert(root, hash(root->first), buckets, newnbuckets);
				root = next;
			}
		}
	}

	template<typename Key, typename Alloc>
	inline pair<typename unordered_set<Key, Alloc>::iterator, bool> unordered_set<Key, Alloc>::insert(const Key& key) {
		pair<iterator, bool> result;
		result.second = false;

		result.first = find(key);
		if (result.first.node != 0)
			return result;

		unordered_hash_node<Key, void>* newnode = new(placeholder(), Alloc::static_allocate(sizeof(unordered_hash_node<Key, void>))) unordered_hash_node<Key, void>(key);
		newnode->next = newnode->prev = 0;

		const size_t nbuckets = (size_t)(m_buckets.last - m_buckets.first);
		unordered_hash_node_insert(newnode, hash(key), m_buckets.first, nbuckets - 1);

		++m_size;
		rehash(nbuckets);

		result.first.node = newnode;
		result.second = true;
		return result;
	}

	template<typename Key, typename Alloc>
	inline pair<typename unordered_set<Key, Alloc>::iterator, bool> unordered_set<Key, Alloc>::emplace(Key&& key) {
				pair<iterator, bool> result;
		result.second = false;

		result.first = find(key);
		if (result.first.node != 0)
			return result;

		const size_t keyhash = hash(key);
		unordered_hash_node<Key, void>* newnode = new(placeholder(), Alloc::static_allocate(sizeof(unordered_hash_node<Key, void>))) unordered_hash_node<Key, void>(static_cast<Key&&>(key));
		newnode->next = newnode->prev = 0;

		const size_t nbuckets = (size_t)(m_buckets.last - m_buckets.first);
		unordered_hash_node_insert(newnode, keyhash, m_buckets.first, nbuckets - 1);

		++m_size;
		rehash(nbuckets);

		result.first.node = newnode;
		result.second = true;
		return result;
	}

	template<typename Key, typename Alloc>
	inline void unordered_set<Key, Alloc>::erase(iterator where) {
		unordered_hash_node_erase(where.node, hash(where.node->first), m_buckets.first, (size_t)(m_buckets.last - m_buckets.first) - 1);

		where.node->~unordered_hash_node<Key, void>();
		Alloc::static_deallocate((void*)where.node, sizeof(unordered_hash_node<Key, void>));
		--m_size;
	}

	template<typename Key, typename Alloc>
	inline size_t unordered_set<Key, Alloc>::erase(const Key& key) {
		const iterator it = find(key);
		if (it.node == 0)
			return 0;

		erase(it);
		return 1;
	}

	template <typename Key, typename Alloc>
	void unordered_set<Key, Alloc>::swap(unordered_set& other) {
		size_t tsize = other.m_size;
		other.m_size = m_size, m_size = tsize;
		buffer_swap(m_buckets, other.m_buckets);
	}

}
