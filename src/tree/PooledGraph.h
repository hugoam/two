//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>
#include <tree/Key.h>
#include <tree/Graph.h>

namespace two
{
	export_ template <class T>
	class PooledNode;

	// the single object holding all the nodes of a graph: the nodes are stored flat, in depth-first order, each node followed by its descendants
	// a node destroyed leaves its slots empty, the following nodes don't move
	// each node has an id unique in the graph, under which the graph keeps the states of the node, and its top nodes by their key
	export_ template <class T>
	class PooledGraph
	{
	public:
		PooledGraph() {}

		// the state of a node, by its type: a node can have several, of different types, they go away with the node
		struct NodeStateSlot
		{
			const void* type;
			unique<NodeState> state;
		};

		T* m_root = nullptr;

		// the nodes in depth-first order, and for each slot left empty by a node destroyed with its descendants, the number of slots to jump over
		vector<unique<T>> m_nodes;
		vector<uint32_t> m_holes;

		unordered_map<uint64_t, T*> m_tops;
		unordered_map<uint64_t, T*> m_ids;
		unordered_map<uint64_t, vector<NodeStateSlot>> m_states;

		inline uint32_t jump(uint32_t slot) const { return m_nodes[slot] ? m_nodes[slot]->m_descendants + 1 : m_holes[slot]; }

		// the id of a node is derived from the id of its parent and its own key or position: when it's taken already, by a node declared with the same key, it's derived again
		inline uint64_t add_id(T& node, uint64_t id)
		{
			while (m_ids.find(id) != m_ids.end())
				id = key_mix(id, 1);
			m_ids[id] = &node;
			return id;
		}

		template <class T_State, class... Args>
		inline T_State& node_state(uint64_t id, Args&&... args)
		{
			vector<NodeStateSlot>& states = m_states[id];
			for (NodeStateSlot& slot : states)
				if (slot.type == node_type<T_State>())
					return static_cast<T_State&>(*slot.state);
			states.push_back({ node_type<T_State>(), make_unique<T_State>(static_cast<Args&&>(args)...) });
			return static_cast<T_State&>(*states.back().state);
		}
	};

	// a node of a pooled graph: it knows its place in the graph, and declares its children, matching them to the ones of the last frame
	// the children of a node are found by jumping over the descendants of each child
	// a top node is identified by its key in the whole graph, and stored at the top of the graph: it's independent of the node it's declared in, its parent
	export_ template <class T>
	class PooledNode
	{
	public:
		PooledNode(PooledGraph<T>& graph) : m_graph(&graph) {}
		PooledNode(T* parent) : m_graph(parent->m_graph), m_parent(parent) {}

		PooledNode(PooledNode<T>&& other) = default;
		PooledNode<T>& operator=(PooledNode<T>&& other) = default;

		inline T& impl() { return static_cast<T&>(*this); }

		PooledGraph<T>* m_graph = nullptr;
		T* m_parent = nullptr;
		uint64_t m_key = 0;
		uint64_t m_id = 0;
		size_t m_heartbeat = 0;
		uint16_t m_next = 0;

		uint32_t m_slot = uint32_t(-1);
		uint32_t m_descendants = 0;
		uint32_t m_cursor = 1;
		uint16_t m_sibling = 0;

		bool m_top = false;
		bool m_retain = false;
		unique<vector<T*>> m_attached;

		// the children of a node, in the layout sense: the nodes stored under it which it's the parent of, then the top nodes attached to it
		struct Children
		{
			struct iterator
			{
				PooledGraph<T>* graph; T* parent; uint32_t slot; uint32_t last; vector<T*>* attached; size_t index;

				T& operator*() const { return slot < last ? *graph->m_nodes[slot] : *(*attached)[index]; }
				iterator& operator++() { if (slot < last) { slot += graph->jump(slot); skip(); } else ++index; return *this; }
				bool operator!=(const iterator& other) const { return slot != other.slot || index != other.index; }
				bool operator==(const iterator& other) const { return slot == other.slot && index == other.index; }
				void skip() { while (slot < last && (!graph->m_nodes[slot] || graph->m_nodes[slot]->m_parent != parent)) slot += graph->jump(slot); }
			};

			PooledGraph<T>* graph; T* parent; uint32_t first; uint32_t last; vector<T*>* attached;
			iterator begin() const { iterator it = { graph, parent, first, last, attached, 0 }; it.skip(); return it; }
			iterator end() const { return { graph, parent, last, last, attached, attached ? attached->size() : 0 }; }
		};

		inline T& root() { return *m_graph->m_root; }

		inline PooledNode* storage_parent() { return m_top ? &this->root() : m_parent; }

		inline uint32_t first_slot() const { return m_slot + 1; }
		inline uint32_t end_slot() const { return m_slot + 1 + m_descendants; }

		inline Children children() { return { m_graph, &impl(), this->first_slot(), this->end_slot(), m_attached.get() }; }
		// the slots of the descendants, which can be empty
		inline span<unique<T>> descendants() { return { m_graph->m_nodes.data() + this->first_slot(), m_descendants }; }
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

		inline unique<T> create_node(uint64_t id)
		{
			unique<T> node = make_unique<T>(&impl());
			node->m_id = m_graph->add_id(*node, id);
			return node;
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

		inline T& subx(uint16_t index)
		{
			PooledGraph<T>& graph = *m_graph;
			uint32_t slot = this->first_slot();
			for (uint16_t i = 0; i <= index; ++i)
			{
				while (slot < this->end_slot() && !graph.m_nodes[slot])
					slot += graph.m_holes[slot];
				if (slot == this->end_slot())
					this->insert_node(slot, create_node(key_mix(m_id, i)));
				if (i < index)
					slot += graph.jump(slot);
			}

			// the next positional children come after this one
			if (m_slot + m_cursor <= slot)
				m_cursor = slot - m_slot + graph.jump(slot);
			if (m_next <= index)
				m_next = index + 1;
			graph.m_nodes[slot]->m_sibling = index;
			return update(*graph.m_nodes[slot]);
		}

		// a keyed child is looked up by its key from the current position, and moved there: it keeps its state when the children before it change
		// a child without key is matched by its position
		inline T& sub(NodeKey key)
		{
			PooledGraph<T>& graph = *m_graph;
			uint32_t slot = m_slot + m_cursor;

			auto match = [&](T* node) { return node && node->m_key == key.m_value && node->m_heartbeat != m_heartbeat; };
			uint32_t found = slot;
			if (key.m_value)
				while (found < this->end_slot() && !match(graph.m_nodes[found].get()))
					found += graph.jump(found);
			else if (found < this->end_slot() && (!graph.m_nodes[found] || graph.m_nodes[found]->m_key))
				found = this->end_slot();

			if (found == this->end_slot())
				this->insert_node(slot, create_node(key_mix(m_id, key.m_value ? key.m_value : m_next))).m_key = key.m_value;
			else if (found != slot)
				this->move_node(found, slot);

			return this->place_node(slot);
		}

		// a top node is looked up by its key in the whole graph, and attached to this node, whatever node it was attached to before
		inline T& sub_top(NodeKey key)
		{
			PooledGraph<T>& graph = *m_graph;
			T& root = this->root();
			auto it = graph.m_tops.find(key.m_value);
			T* node = it != graph.m_tops.end() ? it->second : nullptr;

			if (!node)
			{
				node = &root.insert_node(root.end_slot(), create_node(key_mix(root.m_id, key.m_value)));
				node->m_top = true;
				node->m_key = key.m_value;
				graph.m_tops[key.m_value] = node;
				this->link_top(*node);
			}
			else if (node->m_parent != &impl())
			{
				T* old = node->m_parent;
				PooledNode::unlink_top(*node);
				node->m_parent = &impl();
				this->link_top(*node);
				node->reparent(old);
			}

			node->m_sibling = m_next++;
			return update(*node);
		}

		inline T& suba()
		{
			return subx(m_next++);
		}

		// the state of this node of the given type, created on first use, and destroyed with the node
		template <class T_State, class... Args>
		inline T_State& state(Args&&... args)
		{
			return m_graph->template node_state<T_State>(m_id, static_cast<Args&&>(args)...);
		}

		// visits each node once, in the order they are stored
		template <class Visitor>
		inline void visit(const Visitor& visitor)
		{
			bool visit = true;
			visitor(this->impl(), visit);

			if (visit)
			{
				PooledGraph<T>& graph = *m_graph;
				for (uint32_t slot = this->first_slot(); slot < this->end_slot(); slot += graph.jump(slot))
					if (graph.m_nodes[slot])
						graph.m_nodes[slot]->visit(visitor);
			}
		}

	private:
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

		// a node going away releases its id and its states, its key if it's a top node, and detaches the top nodes attached to it
		static inline void release(T& node)
		{
			PooledGraph<T>& graph = *node.m_graph;
			if (node.m_top)
			{
				unlink_top(node);
				graph.m_tops.erase(node.m_key);
			}
			if (node.m_attached)
				for (T* top : *node.m_attached)
				{
					top->m_parent = nullptr;
					top->reparent(&node);
				}
			graph.m_ids.erase(node.m_id);
			graph.m_states.erase(node.m_id);
		}

		// destroys the nodes in the slots from the deepest, once they all released what refers to them
		// the descendants of a node are destroyed before it, so its own clear() is a no-op
		static inline void destroy(vector<unique<T>>& nodes, uint32_t slot, uint32_t count)
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
			PooledGraph<T>& graph = *m_graph;
			T& node = *graph.m_nodes[slot];
			m_cursor = slot - m_slot + graph.jump(slot);
			node.m_sibling = m_next++;
			return update(node);
		}

		// adds a child at the slot: it fills the slot if it's empty, otherwise it makes room for it in the ancestors
		inline T& insert_node(uint32_t slot, unique<T> node)
		{
			PooledGraph<T>& graph = *m_graph;
			if (slot < this->end_slot() && !graph.m_nodes[slot])
			{
				uint32_t hole = graph.m_holes[slot];
				graph.m_nodes[slot] = move(node);
				graph.m_nodes[slot]->m_slot = slot;
				graph.m_holes[slot] = 0;
				if (hole > 1)
					graph.m_holes[slot + 1] = hole - 1;
				return *graph.m_nodes[slot];
			}

			graph.m_nodes.insert(graph.m_nodes.begin() + slot, move(node));
			graph.m_holes.insert(graph.m_holes.begin() + slot, 0);
			for (uint32_t i = slot; i < graph.m_nodes.size(); ++i)
				if (graph.m_nodes[i])
					graph.m_nodes[i]->m_slot = i;

			for (PooledNode* ancestor = this; ancestor; ancestor = ancestor->storage_parent())
			{
				ancestor->m_descendants++;
				if (ancestor->m_slot + ancestor->m_cursor >= slot)
					ancestor->m_cursor++;
			}
			return *graph.m_nodes[slot];
		}

		// removes the slots, which are whole subtrees of the descendants of this node
		inline void remove_nodes(uint32_t slot, uint32_t count)
		{
			PooledGraph<T>& graph = *m_graph;
			destroy(graph.m_nodes, slot, count);

			graph.m_nodes.erase(graph.m_nodes.begin() + slot, graph.m_nodes.begin() + slot + count);
			graph.m_holes.erase(graph.m_holes.begin() + slot, graph.m_holes.begin() + slot + count);
			for (uint32_t i = slot; i < graph.m_nodes.size(); ++i)
				if (graph.m_nodes[i])
					graph.m_nodes[i]->m_slot = i;

			for (PooledNode* ancestor = this; ancestor; ancestor = ancestor->storage_parent())
			{
				ancestor->m_descendants -= count;
				if (ancestor->m_slot + ancestor->m_cursor >= slot + count)
					ancestor->m_cursor -= count;
			}
		}

		// moves the child in the slot from, with its descendants, to the slot to, before it
		inline void move_node(uint32_t from, uint32_t to)
		{
			PooledGraph<T>& graph = *m_graph;
			uint32_t end = from + graph.jump(from);
			reverse(graph.m_nodes.begin() + to, graph.m_nodes.begin() + from);
			reverse(graph.m_nodes.begin() + from, graph.m_nodes.begin() + end);
			reverse(graph.m_nodes.begin() + to, graph.m_nodes.begin() + end);
			reverse(graph.m_holes.begin() + to, graph.m_holes.begin() + from);
			reverse(graph.m_holes.begin() + from, graph.m_holes.begin() + end);
			reverse(graph.m_holes.begin() + to, graph.m_holes.begin() + end);
			for (uint32_t i = to; i < end; ++i)
				if (graph.m_nodes[i])
					graph.m_nodes[i]->m_slot = i;
		}

		// the descendants which were not declared since the last frame are destroyed with their descendants, leaving their slots empty
		// top nodes to retain are kept whole, and detached from their parent until they're declared again
		inline void clean_tree()
		{
			PooledGraph<T>& graph = *m_graph;
			for (uint32_t slot = this->first_slot(); slot < this->end_slot();)
			{
				T* node = graph.m_nodes[slot].get();
				uint32_t jump = graph.jump(slot);
				if (node && node->m_heartbeat < m_heartbeat && node->m_top && node->m_retain)
				{
					if (node->m_parent)
						detach_top(*node);
				}
				else if (node && node->m_heartbeat < m_heartbeat)
				{
					destroy(graph.m_nodes, slot, jump);
					graph.m_holes[slot] = jump;
				}
				else if (node)
					jump = 1;
				slot += jump;
			}
		}

		// the descendants which were not declared since the last frame are kept, but their own descendants are cleared
		inline void clean_tree_preserve()
		{
			PooledGraph<T>& graph = *m_graph;
			for (uint32_t slot = this->first_slot(); slot < this->end_slot(); ++slot)
			{
				T* node = graph.m_nodes[slot].get();
				if (node && node->m_heartbeat < m_heartbeat && node->m_descendants)
					node->clear();
			}
		}
	};
}
