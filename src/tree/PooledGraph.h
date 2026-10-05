//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <tree/Key.h>
#include <tree/Graph.h>

// checks the structure of the graphs each time they begin, in debug
#ifndef TWO_DEBUG_GRAPH
#ifdef NDEBUG
#define TWO_DEBUG_GRAPH 0
#else
#define TWO_DEBUG_GRAPH 1
#endif
#endif

namespace two
{
	export_ template <class T>
	class PooledNode;

	export_ TWO_TREE_EXPORT uint32_t next_state_type();

	// a sequential id for each type of node state, to find the store of its states in an array
	export_ template <class T>
	inline uint32_t state_type() { static uint32_t id = next_state_type(); return id; }

	// the state of a node, found or created, and whether it was just created
	export_ template <class T>
	struct FoundState
	{
		T& state;
		bool created;
	};

	// the states of one type, by node index: the states are stored in a pool, where they don't move, and found by the index of their node
	// the states of the nodes of one tree are stored together, in the chunks of the colour of the tree
	export_ class StateStore
	{
	public:
		virtual ~StateStore() {}
		virtual void release(uint32_t node) = 0;

		inline void* find(uint32_t node) { return m_handles.has(node) ? m_states[m_handles[node]] : nullptr; }

		SparseHandles m_handles;	// the position of the state of each node
		vector<void*> m_states;		// the states, by position
	};

	export_ template <class T>
	class TStateStore : public StateStore
	{
	public:
		TStateStore(uint32_t chunk_size = 64) : m_pool(chunk_size) {}

		template <class... Args>
		inline T& create(uint32_t node, uint32_t tree, Args&&... args)
		{
			T& state = m_pool.construct_in(tree, static_cast<Args&&>(args)...);
			if(node >= m_handles.capacity())
				m_handles.ensure(node + 1);
			m_handles.add(node);
			m_states.push_back(&state);
			return state;
		}

		// a state goes away with its node
		virtual void release(uint32_t node) override
		{
			if(!m_handles.has(node))
				return;
			T* state = static_cast<T*>(m_states[m_handles[node]]);
			uint32_t index = m_handles.remove(node);
			swap_pop(m_states, index);
			m_pool.tdestroy(*state);
		}

		// visits the states of the nodes of a tree
		template <class T_Func>
		inline void iterate(uint32_t tree, T_Func func) const { m_pool.iterate(tree, func); }

		ChunkedPool<T> m_pool;
	};

	// the single object holding all the nodes of a graph, and their structure
	// each node has an index, stable for the life of the node, and reused once it's destroyed: the structure of the graph is stored in arrays, by node index
	// the nodes are ordered depth-first: each node is followed by its descendants, the children of a node are found by jumping over the descendants of each child
	// a node destroyed leaves its slots in the order empty, the following nodes don't move
	// a top node is identified by its key in the whole graph, and ordered at the top of the graph: it's independent of the node it's declared in, its parent
	// the root has the index 0, it's not in the order: its descendants are the whole order
	export_ template <class T>
	class PooledGraph
	{
	public:
		static constexpr uint32_t none = UINT32_MAX;

		enum Flags : uint8_t
		{
			Top = 1 << 0,
			Retain = 1 << 1
		};

		PooledGraph()
		{
			this->add_index();
		}

		T* m_root = nullptr;

		// the nodes, by index: the root is owned outside of the graph
		vector<unique<T>> m_nodes;
		vector<uint32_t> m_free;

		// the structure, by node index
		vector<uint32_t> m_parent;
		vector<uint32_t> m_slot;
		vector<uint32_t> m_descendants;
		vector<uint32_t> m_cursor;
		vector<uint32_t> m_heartbeat;
		vector<uint16_t> m_next;
		vector<uint16_t> m_sibling;
		vector<uint64_t> m_key;
		vector<uint8_t> m_flags;
		vector<uint32_t> m_tree;	// the top-level tree of the node: the index of its top node, or the root
		vector<unique<vector<uint32_t>>> m_attached;

		// the nodes in depth-first order, and for each slot left empty by a node destroyed with its descendants, the number of slots to jump over
		vector<uint32_t> m_order;
		vector<uint32_t> m_holes;

		unordered_map<uint64_t, uint32_t> m_tops;
		// the states of the nodes, a store for each type of state: a node can have several, of different types
		vector<unique<StateStore>> m_stores;

		inline T& node(uint32_t index) { return index == 0 ? *m_root : *m_nodes[index]; }
		inline T* node_or_null(uint32_t index) { return index == none ? nullptr : &this->node(index); }

		inline uint32_t jump(uint32_t slot) const { return m_order[slot] != none ? m_descendants[m_order[slot]] + 1 : m_holes[slot]; }

		inline uint32_t first_slot(uint32_t index) const { return m_slot[index] + 1; }
		inline uint32_t end_slot(uint32_t index) const { return m_slot[index] + 1 + m_descendants[index]; }

		inline bool top(uint32_t index) const { return (m_flags[index] & Top) != 0; }
		inline bool retain(uint32_t index) const { return (m_flags[index] & Retain) != 0; }

		// the node whose descendants a node is ordered in: its parent, or the root for a top node
		inline uint32_t storage_parent(uint32_t index) const { return this->top(index) ? 0 : m_parent[index]; }

		template <class T_State>
		inline TStateStore<T_State>* find_store()
		{
			uint32_t id = state_type<T_State>();
			return id < m_stores.size() ? static_cast<TStateStore<T_State>*>(m_stores[id].get()) : nullptr;
		}

		// the store of a type of state, created with the given size of its chunks on first use
		template <class T_State, class... Args>
		inline TStateStore<T_State>& store(Args&&... args)
		{
			uint32_t id = state_type<T_State>();
			if(id >= m_stores.size())
				m_stores.resize(id + 1);
			if(!m_stores[id])
				m_stores[id] = make_unique<TStateStore<T_State>>(static_cast<Args&&>(args)...);
			return static_cast<TStateStore<T_State>&>(*m_stores[id]);
		}

		template <class T_State>
		inline T_State* find_state(uint32_t index)
		{
			TStateStore<T_State>* store = this->template find_store<T_State>();
			return store ? static_cast<T_State*>(store->find(index)) : nullptr;
		}

		template <class T_State, class... Args>
		inline FoundState<T_State> find_or_create_state(uint32_t index, Args&&... args)
		{
			TStateStore<T_State>& store = this->template store<T_State>();
			if(void* state = store.find(index))
				return { *static_cast<T_State*>(state), false };
			return { store.create(index, m_tree[index], static_cast<Args&&>(args)...), true };
		}

		template <class T_State, class... Args>
		inline T_State& node_state(uint32_t index, Args&&... args)
		{
			return this->template find_or_create_state<T_State>(index, static_cast<Args&&>(args)...).state;
		}

		inline T& update(uint32_t parent, uint32_t index)
		{
			m_heartbeat[index] = m_heartbeat[parent];
			m_next[index] = 0;
			m_cursor[index] = 1;
			return this->node(index);
		}

		inline T& begin(uint32_t index, bool preserve)
		{
#if TWO_DEBUG_GRAPH
			assert(this->validate());
#endif
			if (preserve)
				this->clean_tree_preserve(index);
			else
				this->clean_tree(index);
			m_heartbeat[index]++;
			m_next[index] = 0;
			m_cursor[index] = 1;
			return this->node(index);
		}

		inline void clear(uint32_t index)
		{
			if (m_descendants[index])
				this->remove_nodes(index, this->first_slot(index), m_descendants[index]);
		}

		inline T& subx(uint32_t parent, uint16_t index)
		{
			uint32_t slot = this->first_slot(parent);
			for (uint16_t i = 0; i <= index; ++i)
			{
				while (slot < this->end_slot(parent) && m_order[slot] == none)
					slot += m_holes[slot];
				if (slot == this->end_slot(parent))
					this->insert_node(parent, slot, this->create_node(parent));
				if (i < index)
					slot += this->jump(slot);
			}

			// the next positional children come after this one
			if (m_slot[parent] + m_cursor[parent] <= slot)
				m_cursor[parent] = slot - m_slot[parent] + this->jump(slot);
			if (m_next[parent] <= index)
				m_next[parent] = index + 1;
			m_sibling[m_order[slot]] = index;
			return this->update(parent, m_order[slot]);
		}

		// a keyed child is looked up by its key from the current position, and moved there: it keeps its state when the children before it change
		// a child without key is matched by its position
		inline T& sub(uint32_t parent, NodeKey key)
		{
			uint32_t slot = m_slot[parent] + m_cursor[parent];
			uint32_t end = this->end_slot(parent);

			auto match = [&](uint32_t index) { return index != none && m_key[index] == key.m_value && m_heartbeat[index] != m_heartbeat[parent]; };
			uint32_t found = slot;
			if (key.m_value)
				while (found < end && !match(m_order[found]))
					found += this->jump(found);
			else if (found < end && (m_order[found] == none || m_key[m_order[found]]))
				found = end;

			if (found == end)
			{
				uint32_t index = this->create_node(parent);
				m_key[index] = key.m_value;
				this->insert_node(parent, slot, index);
			}
			else if (found != slot)
				this->move_node(found, slot);

			return this->place_node(parent, slot);
		}

		// a top node is looked up by its key in the whole graph, and attached to this node, whatever node it was attached to before
		inline T& sub_top(uint32_t parent, NodeKey key)
		{
			auto it = m_tops.find(key.m_value);
			uint32_t index = it != m_tops.end() ? it->second : none;

			if (index == none)
			{
				index = this->create_node(parent, true);
				m_key[index] = key.m_value;
				this->insert_node(0, this->end_slot(0), index);
				m_tops[key.m_value] = index;
				this->link_top(parent, index);
			}
			else if (m_parent[index] != parent)
			{
				uint32_t old = m_parent[index];
				this->unlink_top(index);
				m_parent[index] = parent;
				this->link_top(parent, index);
				this->node(index).reparent(this->node_or_null(old));
			}

			m_sibling[index] = m_next[parent]++;
			return this->update(parent, index);
		}

		// visits each node once, in the order they are stored
		template <class Visitor>
		inline void visit(uint32_t index, const Visitor& visitor)
		{
			bool visit = true;
			visitor(this->node(index), visit);

			if (visit)
				for (uint32_t slot = this->first_slot(index); slot < this->end_slot(index); slot += this->jump(slot))
					if (m_order[slot] != none)
						this->visit(m_order[slot], visitor);
		}

		// checks the structure is consistent: the slots of the nodes, their descendants nested in their parent, the free indices
		bool validate()
		{
			bool valid = true;
			auto check = [&](bool condition) { valid &= condition; return condition; };
			for (uint32_t slot = 0; slot < m_order.size(); ++slot)
				if (m_order[slot] != none)
				{
					uint32_t index = m_order[slot];
					check(m_nodes[index] != nullptr && m_slot[index] == slot);
					uint32_t parent = this->storage_parent(index);
					if (parent != none)
						check(slot >= this->first_slot(parent) && slot + m_descendants[index] < this->end_slot(parent));
				}
			for (uint32_t index : m_free)
				check(m_nodes[index] == nullptr);
			return valid;
		}

	private:
		// an index for a new node: a free one, or a new one
		inline uint32_t add_index()
		{
			if (!m_free.empty())
			{
				uint32_t index = m_free.back();
				m_free.pop_back();
				return index;
			}

			m_nodes.emplace_back();
			m_parent.push_back(none);
			m_slot.push_back(none);
			m_descendants.push_back(0);
			m_cursor.push_back(1);
			m_heartbeat.push_back(0);
			m_next.push_back(0);
			m_sibling.push_back(0);
			m_key.push_back(0);
			m_flags.push_back(0);
			m_tree.push_back(0);
			m_attached.emplace_back();
			return uint32_t(m_nodes.size() - 1);
		}

		// the node is destroyed, and its index freed, reset for the next node to take it
		inline void free_index(uint32_t index)
		{
			m_nodes[index] = nullptr;
			m_parent[index] = none;
			m_slot[index] = none;
			m_descendants[index] = 0;
			m_cursor[index] = 1;
			m_heartbeat[index] = 0;
			m_next[index] = 0;
			m_sibling[index] = 0;
			m_key[index] = 0;
			m_flags[index] = 0;
			m_tree[index] = 0;
			m_attached[index] = nullptr;
			m_free.push_back(index);
		}

		// a top node is its own tree, any other node is in the tree of its parent, for its whole life: keyed matching only moves a node among the children of its parent
		inline uint32_t create_node(uint32_t parent, bool top = false)
		{
			uint32_t index = this->add_index();
			m_parent[index] = parent;
			m_flags[index] = top ? Top : 0;
			m_tree[index] = top ? index : m_tree[parent];
			m_nodes[index] = make_unique<T>(&this->node(parent));
			m_nodes[index]->m_index = index;
			return index;
		}

		// a top node is listed in its parent, unless its parent is the root, which orders it already
		inline void link_top(uint32_t parent, uint32_t index)
		{
			if (parent == 0)
				return;
			if (!m_attached[parent])
				m_attached[parent] = make_unique<vector<uint32_t>>();
			m_attached[parent]->push_back(index);
		}

		inline void unlink_top(uint32_t index)
		{
			uint32_t parent = m_parent[index];
			if (parent != none && m_attached[parent])
				remove(*m_attached[parent], index);
		}

		inline void detach_top(uint32_t index)
		{
			uint32_t old = m_parent[index];
			this->unlink_top(index);
			m_parent[index] = none;
			this->node(index).reparent(this->node_or_null(old));
		}

		// a node going away releases its states, its key if it's a top node, and detaches the top nodes attached to it
		inline void release(uint32_t index)
		{
			if (this->top(index))
			{
				this->unlink_top(index);
				m_tops.erase(m_key[index]);
			}
			if (m_attached[index])
				for (uint32_t top : *m_attached[index])
				{
					m_parent[top] = none;
					this->node(top).reparent(&this->node(index));
				}
			for(unique<StateStore>& store : m_stores)
				if(store)
					store->release(index);
		}

		// destroys the nodes in the slots from the deepest, once they all released what refers to them, and leaves the slots empty
		// the descendants of a node are destroyed before it, so its own clear() is a no-op
		inline void destroy(uint32_t slot, uint32_t count)
		{
			for (uint32_t i = slot; i < slot + count; ++i)
				if (m_order[i] != none)
				{
					m_descendants[m_order[i]] = 0;
					this->release(m_order[i]);
				}
			for (uint32_t i = slot + count; i-- > slot;)
				if (m_order[i] != none)
				{
					this->free_index(m_order[i]);
					m_order[i] = none;
				}
		}

		// the node at the slot is the next child: the following children go after its descendants
		inline T& place_node(uint32_t parent, uint32_t slot)
		{
			uint32_t index = m_order[slot];
			m_cursor[parent] = slot - m_slot[parent] + this->jump(slot);
			m_sibling[index] = m_next[parent]++;
			return this->update(parent, index);
		}

		// orders a child at the slot: it fills the slot if it's empty, otherwise it makes room for it in the ancestors
		inline void insert_node(uint32_t parent, uint32_t slot, uint32_t index)
		{
			if (slot < this->end_slot(parent) && m_order[slot] == none)
			{
				uint32_t hole = m_holes[slot];
				m_order[slot] = index;
				m_slot[index] = slot;
				m_holes[slot] = 0;
				if (hole > 1)
					m_holes[slot + 1] = hole - 1;
				return;
			}

			m_order.insert(m_order.begin() + slot, index);
			m_holes.insert(m_holes.begin() + slot, 0);
			for (uint32_t i = slot; i < m_order.size(); ++i)
				if (m_order[i] != none)
					m_slot[m_order[i]] = i;

			for (uint32_t ancestor = parent; ancestor != none; ancestor = this->storage_parent(ancestor))
			{
				m_descendants[ancestor]++;
				if (m_slot[ancestor] + m_cursor[ancestor] >= slot)
					m_cursor[ancestor]++;
			}
		}

		// removes the slots, which are whole subtrees of the descendants of the node
		inline void remove_nodes(uint32_t parent, uint32_t slot, uint32_t count)
		{
			this->destroy(slot, count);

			m_order.erase(m_order.begin() + slot, m_order.begin() + slot + count);
			m_holes.erase(m_holes.begin() + slot, m_holes.begin() + slot + count);
			for (uint32_t i = slot; i < m_order.size(); ++i)
				if (m_order[i] != none)
					m_slot[m_order[i]] = i;

			for (uint32_t ancestor = parent; ancestor != none; ancestor = this->storage_parent(ancestor))
			{
				m_descendants[ancestor] -= count;
				if (m_slot[ancestor] + m_cursor[ancestor] >= slot + count)
					m_cursor[ancestor] -= count;
			}
		}

		// moves the child in the slot from, with its descendants, to the slot to, before it
		inline void move_node(uint32_t from, uint32_t to)
		{
			uint32_t end = from + this->jump(from);
			reverse(m_order.begin() + to, m_order.begin() + from);
			reverse(m_order.begin() + from, m_order.begin() + end);
			reverse(m_order.begin() + to, m_order.begin() + end);
			reverse(m_holes.begin() + to, m_holes.begin() + from);
			reverse(m_holes.begin() + from, m_holes.begin() + end);
			reverse(m_holes.begin() + to, m_holes.begin() + end);
			for (uint32_t i = to; i < end; ++i)
				if (m_order[i] != none)
					m_slot[m_order[i]] = i;
		}

		// the descendants which were not declared since the last frame are destroyed with their descendants, leaving their slots empty
		// top nodes to retain are kept whole, and detached from their parent until they're declared again
		inline void clean_tree(uint32_t root)
		{
			for (uint32_t slot = this->first_slot(root); slot < this->end_slot(root);)
			{
				uint32_t index = m_order[slot];
				uint32_t jump = this->jump(slot);
				if (index != none && m_heartbeat[index] < m_heartbeat[root] && this->top(index) && this->retain(index))
				{
					if (m_parent[index] != none)
						this->detach_top(index);
				}
				else if (index != none && m_heartbeat[index] < m_heartbeat[root])
				{
					this->destroy(slot, jump);
					m_holes[slot] = jump;
				}
				else if (index != none)
					jump = 1;
				slot += jump;
			}
		}

		// the descendants which were not declared since the last frame are kept, but their own descendants are cleared
		inline void clean_tree_preserve(uint32_t root)
		{
			for (uint32_t slot = this->first_slot(root); slot < this->end_slot(root); ++slot)
			{
				uint32_t index = m_order[slot];
				if (index != none && m_heartbeat[index] < m_heartbeat[root] && m_descendants[index])
					this->node(index).clear();
			}
		}
	};

	// a node of a pooled graph: it knows its index in the graph, which holds its structure, and declares its children, matching them to the ones of the last frame
	export_ template <class T>
	class PooledNode
	{
	public:
		PooledNode(PooledGraph<T>& graph) : m_graph(&graph), m_index(0) {}
		PooledNode(T* parent) : m_graph(parent->m_graph) {}

		PooledNode(PooledNode<T>&& other) = default;
		PooledNode<T>& operator=(PooledNode<T>&& other) = default;

		PooledGraph<T>* m_graph = nullptr;
		uint32_t m_index = PooledGraph<T>::none;

		inline T& impl() { return static_cast<T&>(*this); }

		inline T& root() { return *m_graph->m_root; }
		inline T* parent() { return m_graph->node_or_null(m_graph->m_parent[m_index]); }
		inline uint16_t sibling() const { return m_graph->m_sibling[m_index]; }
		inline uint16_t next() const { return m_graph->m_next[m_index]; }
		inline uint32_t heartbeat() const { return m_graph->m_heartbeat[m_index]; }
		inline bool top() const { return m_graph->top(m_index); }

		inline void set_retain(bool retain) { uint8_t& flags = m_graph->m_flags[m_index]; flags = uint8_t(retain ? flags | PooledGraph<T>::Retain : flags & ~PooledGraph<T>::Retain); }

		// the children of a node, in the layout sense: the nodes ordered under it which it's the parent of, then the top nodes attached to it
		struct Children
		{
			struct iterator
			{
				PooledGraph<T>* graph; uint32_t parent; uint32_t slot; uint32_t last; vector<uint32_t>* attached; size_t index;

				T& operator*() const { return slot < last ? graph->node(graph->m_order[slot]) : graph->node((*attached)[index]); }
				iterator& operator++() { if (slot < last) { slot += graph->jump(slot); skip(); } else ++index; return *this; }
				bool operator!=(const iterator& other) const { return slot != other.slot || index != other.index; }
				bool operator==(const iterator& other) const { return slot == other.slot && index == other.index; }
				void skip() { while (slot < last && (graph->m_order[slot] == PooledGraph<T>::none || graph->m_parent[graph->m_order[slot]] != parent)) slot += graph->jump(slot); }
			};

			PooledGraph<T>* graph; uint32_t parent; uint32_t first; uint32_t last; vector<uint32_t>* attached;
			iterator begin() const { iterator it = { graph, parent, first, last, attached, 0 }; it.skip(); return it; }
			iterator end() const { return { graph, parent, last, last, attached, attached ? attached->size() : 0 }; }
		};

		inline Children children() { return { m_graph, m_index, m_graph->first_slot(m_index), m_graph->end_slot(m_index), m_graph->m_attached[m_index].get() }; }
		// the indices of the descendants in their order, which can be empty slots
		inline span<uint32_t> descendants() { return { m_graph->m_order.data() + m_graph->first_slot(m_index), m_graph->m_descendants[m_index] }; }
		// the indices of the top nodes attached
		inline span<uint32_t> attached() { vector<uint32_t>* attached = m_graph->m_attached[m_index].get(); return attached ? span<uint32_t>(*attached) : span<uint32_t>(); }
		inline T& child(uint32_t index) { auto it = this->children().begin(); while (index--) ++it; return *it; }
		inline uint32_t child_count() { uint32_t count = 0; for (auto it = this->children().begin(); it != this->children().end(); ++it) ++count; return count; }
		inline bool is_first(T& child) { return &*this->children().begin() == &child; }
		inline bool is_last(T& child)
		{
			vector<uint32_t>* attached = m_graph->m_attached[m_index].get();
			if (attached && !attached->empty())
				return attached->back() == child.m_index;
			auto it = this->children().begin();
			it.slot = m_graph->m_slot[child.m_index];
			return !(++it != this->children().end());
		}

		inline void clear() { m_graph->clear(m_index); }
		inline T& begin(bool preserve = false) { return m_graph->begin(m_index, preserve); }

		inline T& subx(uint16_t index) { return m_graph->subx(m_index, index); }
		inline T& sub(NodeKey key) { return m_graph->sub(m_index, key); }
		inline T& sub_top(NodeKey key) { return m_graph->sub_top(m_index, key); }
		inline T& suba() { return m_graph->subx(m_index, m_graph->m_next[m_index]++); }

		// the state of this node of the given type, created on first use, and destroyed with the node
		template <class T_State, class... Args>
		inline T_State& state(Args&&... args)
		{
			return m_graph->template node_state<T_State>(m_index, static_cast<Args&&>(args)...);
		}

		// the state of this node of the given type, and whether it was just created, to set it up once
		template <class T_State, class... Args>
		inline FoundState<T_State> find_or_create_state(Args&&... args)
		{
			return m_graph->template find_or_create_state<T_State>(m_index, static_cast<Args&&>(args)...);
		}

		// the state of this node of the given type, if it has one
		template <class T_State>
		inline T_State* find_state() { return m_graph->template find_state<T_State>(m_index); }

		// visits each node once, in the order they are stored
		template <class Visitor>
		inline void visit(const Visitor& visitor) { m_graph->visit(m_index, visitor); }
	};
}
