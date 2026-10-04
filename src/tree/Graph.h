//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>

#ifndef TWO_TREE_EXPORT
#define TWO_TREE_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_TREE_EXPORT NodeState
	{
	public:
		virtual ~NodeState() {}
	};

	// identifies the type of a node: a node is only ever reused as the type it was created as
	export_ template <class T>
	inline const void* node_type() { static const char tag = 0; return &tag; }

	// the nodes of a graph are stored flat in its root, in depth-first order: each node is followed by its descendants
	// the children of a node are found by jumping over the descendants of each child
	// a node destroyed leaves its slots empty, the following nodes don't move
	// a top node is identified by its key in the whole graph, and stored at the top of the graph: it's independent of the node it's declared in, its parent
	export_ template <class T>
	class Graph
	{
	public:
		Graph() {}
		Graph(T* parent, void* identity) : m_parent(parent), m_root(parent->m_root ? parent->m_root : parent), m_identity(identity) {}
		virtual ~Graph() {}

		Graph(Graph<T>&& other) = default;
		Graph<T>& operator=(Graph<T>&& other) = default;

		inline T& impl() { return static_cast<T&>(*this); }

		using Nodes = vector<unique<T>>;
		using Tops = map<uint64_t, T*>;

		// the nodes in depth-first order, and for each slot left empty by a node destroyed with its descendants, the number of slots to jump over
		struct Storage
		{
			Nodes nodes;
			vector<uint32_t> holes;

			inline uint32_t jump(uint32_t slot) const { return nodes[slot] ? nodes[slot]->m_descendants + 1 : holes[slot]; }
		};

		T* m_parent = nullptr;
		T* m_root = nullptr;
		void* m_identity = nullptr;
		uint64_t m_key = 0;
		const void* m_node_type = nullptr;
		size_t m_heartbeat = 0;
		unique<NodeState> m_state;
		uint16_t m_next = 0;

		uint32_t m_slot = uint32_t(-1);
		uint32_t m_descendants = 0;
		uint32_t m_cursor = 1;
		uint16_t m_sibling = 0;
		unique<Storage> m_storage;

		bool m_top = false;
		bool m_retain = false;
		unique<vector<T*>> m_attached;
		unique<Tops> m_tops;

		// called when the parent of a top node changes
		virtual void reparent(T* old) { UNUSED(old); }

		// the children of a node, in the layout sense: the nodes stored under it which it's the parent of, then the top nodes attached to it
		struct Children
		{
			struct iterator
			{
				Storage* storage; T* parent; uint32_t slot; uint32_t last; vector<T*>* attached; size_t index;

				T& operator*() const { return slot < last ? *storage->nodes[slot] : *(*attached)[index]; }
				iterator& operator++() { if (slot < last) { slot += storage->jump(slot); skip(); } else ++index; return *this; }
				bool operator!=(const iterator& other) const { return slot != other.slot || index != other.index; }
				bool operator==(const iterator& other) const { return slot == other.slot && index == other.index; }
				void skip() { while (slot < last && (!storage->nodes[slot] || storage->nodes[slot]->m_parent != parent)) slot += storage->jump(slot); }
			};

			Storage* storage; T* parent; uint32_t first; uint32_t last; vector<T*>* attached;
			iterator begin() const { iterator it = { storage, parent, first, last, attached, 0 }; it.skip(); return it; }
			iterator end() const { return { storage, parent, last, last, attached, attached ? attached->size() : 0 }; }
		};

		inline T& root() { return m_root ? *m_root : impl(); }

		inline Storage& storage()
		{
			Graph& root = this->root();
			if (!root.m_storage)
				root.m_storage = make_unique<Storage>();
			return *root.m_storage;
		}

		inline Graph* storage_parent() { return m_top ? &this->root() : m_parent; }

		inline uint32_t first_slot() const { return m_slot + 1; }
		inline uint32_t end_slot() const { return m_slot + 1 + m_descendants; }

		inline Children children() { return { &this->storage(), &impl(), this->first_slot(), this->end_slot(), m_attached.get() }; }
		// the slots of the descendants, which can be empty
		inline span<unique<T>> descendants() { return { this->storage().nodes.data() + this->first_slot(), m_descendants }; }
		inline span<T*> attached() { return m_attached ? span<T*>(*m_attached) : span<T*>(); }
		inline T& child(uint32_t index) { auto it = this->children().begin(); while (index--) ++it; return *it; }
		inline uint32_t child_count() { uint32_t count = 0; for (auto it = this->children().begin(); it != this->children().end(); ++it) ++count; return count; }
		inline bool is_first(T& child) { return &*this->children().begin() == &child; }
		inline bool is_last(T& child)
		{
			if (m_attached && !m_attached->empty())
				return m_attached->back() == &child;
			auto it = this->children().begin();
			it.slot = child.m_slot;
			return !(++it != this->children().end());
		}

		template <class Child = T, class... Args>
		inline unique<T> create_node(void* identity, Args... args)
		{
			unique<T> node = make_unique<Child>(&impl(), identity, args...);
			node->m_node_type = node_type<Child>();
			return node;
		}

		template <class Child = T>
		inline bool is_type(T& node) { return node.m_node_type == node_type<Child>(); }

		template <class Child = T, class... Args>
		inline Child& append(Args... args, void* identity = nullptr)
		{
			return static_cast<Child&>(this->insert_node(this->end_slot(), create_node<Child, Args...>(identity, args...)));
		}

		void clear()
		{
			if (m_descendants)
				this->remove_nodes(this->first_slot(), m_descendants);
		}

		inline T& begin(bool preserve = false)
		{
			if (preserve)
				this->clean_tree_preserve();
			else
				this->clean_tree();
			m_heartbeat++;
			m_next = 0;
			m_cursor = 1;
			return this->impl();
		}

		inline T& update(T& node) { node.m_heartbeat = m_heartbeat; node.m_next = 0; node.m_cursor = 1; return node; }

		template <class Child = T, class... Args>
		inline Child& subx(uint16_t index, Args... args)
		{
			Storage& storage = this->storage();
			uint32_t slot = this->first_slot();
			for (uint16_t i = 0; i <= index; ++i)
			{
				while (slot < this->end_slot() && !storage.nodes[slot])
					slot += storage.holes[slot];
				if (slot == this->end_slot())
					this->insert_node(slot, create_node<Child, Args...>(nullptr, args...));
				if (i < index)
					slot += storage.jump(slot);
			}

			if (!is_type<Child>(*storage.nodes[slot]))
			{
				this->remove_nodes(slot, storage.jump(slot));
				this->insert_node(slot, create_node<Child, Args...>(nullptr, args...));
			}

			// the next positional children come after this one
			if (m_slot + m_cursor <= slot)
				m_cursor = slot - m_slot + storage.jump(slot);
			if (m_next <= index)
				m_next = index + 1;
			storage.nodes[slot]->m_sibling = index;
			return static_cast<Child&>(update(*storage.nodes[slot]));
		}

		// a keyed child is looked up by its key from the current position, and moved there: it keeps its state when the children before it change
		// a child without key is matched by its position
		template <class Child = T, class... Args>
		inline Child& sub(NodeKey key, Args... args)
		{
			Storage& storage = this->storage();
			uint32_t slot = m_slot + m_cursor;

			auto match = [&](T* node) { return node && node->m_key == key.m_value && is_type<Child>(*node) && node->m_heartbeat != m_heartbeat; };
			uint32_t found = slot;
			if (key.m_value)
				while (found < this->end_slot() && !match(storage.nodes[found].get()))
					found += storage.jump(found);
			else if (found < this->end_slot() && (!storage.nodes[found] || storage.nodes[found]->m_key || storage.nodes[found]->m_identity || !is_type<Child>(*storage.nodes[found])))
				found = this->end_slot();

			if (found == this->end_slot())
				this->insert_node(slot, create_node<Child, Args...>(nullptr, args...)).m_key = key.m_value;
			else if (found != slot)
				this->move_node(found, slot);

			return static_cast<Child&>(this->place_node(slot));
		}

		// a top node is looked up by its key in the whole graph, and attached to this node, whatever node it was attached to before
		template <class Child = T, class... Args>
		inline Child& sub_top(NodeKey key, Args... args)
		{
			Graph& root = this->root();
			Tops& tops = root.tops();
			auto it = tops.find(key.m_value);
			T* node = it != tops.end() ? it->second : nullptr;

			if (node && !is_type<Child>(*node))
			{
				root.remove_nodes(node->m_slot, node->m_descendants + 1);
				node = nullptr;
			}

			if (!node)
			{
				node = &root.insert_node(root.end_slot(), create_node<Child, Args...>(nullptr, args...));
				node->m_top = true;
				node->m_key = key.m_value;
				root.tops()[key.m_value] = node;
				this->link_top(*node);
			}
			else if (node->m_parent != &impl())
			{
				T* old = node->m_parent;
				Graph::unlink_top(*node);
				node->m_parent = &impl();
				this->link_top(*node);
				node->reparent(old);
			}

			node->m_sibling = m_next++;
			return static_cast<Child&>(update(*node));
		}

		template <class Child = T, class... Args>
		inline Child& suba(Args... args)
		{
			return subx<Child, Args...>(m_next++, args...);
		}

		template <class Child = T, class... Args>
		inline Child& subi(void* identity, Args... args)
		{
			Storage& storage = this->storage();
			uint32_t slot = m_slot + m_cursor;

			T* node = slot < this->end_slot() ? storage.nodes[slot].get() : nullptr;
			if (!node || node->m_identity != identity || !is_type<Child>(*node))
				this->insert_node(slot, create_node<Child, Args...>(identity, args...));

			return static_cast<Child&>(this->place_node(slot));
		}

		template <class T_State, class... Args>
		inline T_State& state(Args&&... args)
		{
			if (!m_state)
				m_state = make_unique<T_State>(static_cast<Args&&>(args)...);
			return static_cast<T_State&>(*m_state);
		}

		// visits each node once, in the order they are stored
		template <class Visitor>
		inline void visit(const Visitor& visitor)
		{
			bool visit = true;
			visitor(this->impl(), visit);

			if (visit)
			{
				Storage& storage = this->storage();
				for (uint32_t slot = this->first_slot(); slot < this->end_slot(); slot += storage.jump(slot))
					if (storage.nodes[slot])
						storage.nodes[slot]->visit(visitor);
			}
		}

	private:
		inline Tops& tops()
		{
			if (!m_tops)
				m_tops = make_unique<Tops>();
			return *m_tops;
		}

		// a top node is listed in its parent, unless its parent is the root, which stores it already
		inline void link_top(T& node)
		{
			if (&impl() == &this->root())
				return;
			if (!m_attached)
				m_attached = make_unique<vector<T*>>();
			m_attached->push_back(&node);
		}

		static inline void unlink_top(T& node)
		{
			if (node.m_parent && node.m_parent->m_attached)
				remove(*node.m_parent->m_attached, &node);
		}

		static inline void detach_top(T& node)
		{
			T* old = node.m_parent;
			unlink_top(node);
			node.m_parent = nullptr;
			node.reparent(old);
		}

		// a node going away releases its key if it's a top node, and detaches the top nodes attached to it
		static inline void release(T& node)
		{
			if (node.m_top)
			{
				unlink_top(node);
				node.root().tops().erase(node.m_key);
			}
			if (node.m_attached)
				for (T* top : *node.m_attached)
				{
					top->m_parent = nullptr;
					top->reparent(&node);
				}
		}

		// destroys the nodes in the slots from the deepest, once they all released what refers to them
		// the descendants of a node are destroyed before it, so its own clear() is a no-op
		static inline void destroy(Nodes& nodes, uint32_t slot, uint32_t count)
		{
			for (uint32_t i = slot; i < slot + count; ++i)
				if (nodes[i])
				{
					nodes[i]->m_descendants = 0;
					release(*nodes[i]);
				}
			for (uint32_t i = slot + count; i-- > slot;)
				nodes[i] = nullptr;
		}

		// the node at the slot is the next child: the following children go after its descendants
		inline T& place_node(uint32_t slot)
		{
			Storage& storage = this->storage();
			T& node = *storage.nodes[slot];
			m_cursor = slot - m_slot + storage.jump(slot);
			node.m_sibling = m_next++;
			return update(node);
		}

		// adds a child at the slot: it fills the slot if it's empty, otherwise it makes room for it in the ancestors
		inline T& insert_node(uint32_t slot, unique<T> node)
		{
			Storage& storage = this->storage();
			if (slot < this->end_slot() && !storage.nodes[slot])
			{
				uint32_t hole = storage.holes[slot];
				storage.nodes[slot] = move(node);
				storage.nodes[slot]->m_slot = slot;
				storage.holes[slot] = 0;
				if (hole > 1)
					storage.holes[slot + 1] = hole - 1;
				return *storage.nodes[slot];
			}

			storage.nodes.insert(storage.nodes.begin() + slot, move(node));
			storage.holes.insert(storage.holes.begin() + slot, 0);
			for (uint32_t i = slot; i < storage.nodes.size(); ++i)
				if (storage.nodes[i])
					storage.nodes[i]->m_slot = i;

			for (Graph* ancestor = this; ancestor; ancestor = ancestor->storage_parent())
			{
				ancestor->m_descendants++;
				if (ancestor->m_slot + ancestor->m_cursor >= slot)
					ancestor->m_cursor++;
			}
			return *storage.nodes[slot];
		}

		// removes the slots, which are whole subtrees of the descendants of this node
		inline void remove_nodes(uint32_t slot, uint32_t count)
		{
			Storage& storage = this->storage();
			destroy(storage.nodes, slot, count);

			storage.nodes.erase(storage.nodes.begin() + slot, storage.nodes.begin() + slot + count);
			storage.holes.erase(storage.holes.begin() + slot, storage.holes.begin() + slot + count);
			for (uint32_t i = slot; i < storage.nodes.size(); ++i)
				if (storage.nodes[i])
					storage.nodes[i]->m_slot = i;

			for (Graph* ancestor = this; ancestor; ancestor = ancestor->storage_parent())
			{
				ancestor->m_descendants -= count;
				if (ancestor->m_slot + ancestor->m_cursor >= slot + count)
					ancestor->m_cursor -= count;
			}
		}

		// moves the child in the slot from, with its descendants, to the slot to, before it
		inline void move_node(uint32_t from, uint32_t to)
		{
			Storage& storage = this->storage();
			uint32_t end = from + storage.jump(from);
			reverse(storage.nodes.begin() + to, storage.nodes.begin() + from);
			reverse(storage.nodes.begin() + from, storage.nodes.begin() + end);
			reverse(storage.nodes.begin() + to, storage.nodes.begin() + end);
			reverse(storage.holes.begin() + to, storage.holes.begin() + from);
			reverse(storage.holes.begin() + from, storage.holes.begin() + end);
			reverse(storage.holes.begin() + to, storage.holes.begin() + end);
			for (uint32_t i = to; i < end; ++i)
				if (storage.nodes[i])
					storage.nodes[i]->m_slot = i;
		}

		// the descendants which were not declared since the last frame are destroyed with their descendants, leaving their slots empty
		// top nodes to retain are kept whole, and detached from their parent until they're declared again
		inline void clean_tree()
		{
			Storage& storage = this->storage();
			for (uint32_t slot = this->first_slot(); slot < this->end_slot();)
			{
				T* node = storage.nodes[slot].get();
				uint32_t jump = storage.jump(slot);
				if (node && node->m_heartbeat < m_heartbeat && node->m_top && node->m_retain)
				{
					if (node->m_parent)
						detach_top(*node);
				}
				else if (node && node->m_heartbeat < m_heartbeat)
				{
					destroy(storage.nodes, slot, jump);
					storage.holes[slot] = jump;
				}
				else if (node)
					jump = 1;
				slot += jump;
			}
		}

		// the descendants which were not declared since the last frame are kept, but their own descendants are cleared
		inline void clean_tree_preserve()
		{
			Storage& storage = this->storage();
			for (uint32_t slot = this->first_slot(); slot < this->end_slot(); ++slot)
			{
				T* node = storage.nodes[slot].get();
				if (node && node->m_heartbeat < m_heartbeat && node->m_descendants)
					node->clear();
			}
		}
	};
}
