#pragma once

#include <stl/stddef.h>
#include <stl/traits.h>

namespace stl {

	template <class Key, class Value>
	struct pair {
		pair();
		pair(const pair& other);
		pair(pair&& other);
		pair(const Key& key, const Value& value);
		pair(const Key& key, Value&& value);
		pair(Key&& key, Value&& value);

		pair& operator=(const pair& other);
		pair& operator=(pair&& other);

		Key first;
		Value second;
	};

	template <class Key, class Value>
	struct unordered_hash_node {
		unordered_hash_node(const Key& key, const Value& value);
		unordered_hash_node(Key&& key, Value&& value);

		const Key first;
		Value second;
		unordered_hash_node* next;
		unordered_hash_node* prev;

	private:
		unordered_hash_node& operator=(const unordered_hash_node&);
	};

	template <class Key>
	struct unordered_hash_node<Key, void> {
		explicit unordered_hash_node(const Key& key);
		explicit unordered_hash_node(Key&& key);

		const Key first;
		unordered_hash_node* next;
		unordered_hash_node* prev;

	private:
		unordered_hash_node& operator=(const unordered_hash_node&);
	};

	template <class Node>
	struct unordered_hash_iterator {
		Node* operator->() const;
		Node& operator*() const;
		Node* node;
	};

	template <class Node>
	struct unordered_hash_iterator<const Node> {
		unordered_hash_iterator() {}
		unordered_hash_iterator(unordered_hash_iterator<Node> other)
			: node(other.node)
		{
		}
		const Node* operator->() const;
		const Node& operator*() const;
		const Node* node;
	};

	template <class Key>
	struct unordered_hash_iterator<const unordered_hash_node<Key, void> > {
		const Key* operator->() const;
		const Key& operator*() const;
		unordered_hash_node<Key, void>* node;
	};

	template <class LNode, class RNode>
	static inline bool operator==(const unordered_hash_iterator<LNode>& lhs, const unordered_hash_iterator<RNode>& rhs) {
		return lhs.node == rhs.node;
	}

	template <class LNode, class RNode>
	static inline bool operator!=(const unordered_hash_iterator<LNode>& lhs, const unordered_hash_iterator<RNode>& rhs) {
		return lhs.node != rhs.node;
	}

	template <class Node>
	static inline void operator++(unordered_hash_iterator<Node>& lhs) {
		lhs.node = lhs.node->next;
	}
}
