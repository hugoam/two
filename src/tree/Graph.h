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

	export_ template <class T>
	class Graph
	{
	public:
		Graph() {}
		Graph(T* parent, void* identity) : m_parent(parent), m_identity(identity) {}
		virtual ~Graph() {}

		Graph(Graph<T>&& other) = default;
		Graph<T>& operator=(Graph<T>&& other) = default;

		inline T& impl() { return static_cast<T&>(*this); }

		T* m_parent = nullptr;
		void* m_identity = nullptr;
		uint64_t m_key = 0;
		const void* m_node_type = nullptr;
		size_t m_heartbeat = 0;
		vector<unique<T>> m_nodes;
		unique<NodeState> m_state;
		uint16_t m_next = 0;

		template <class Child = T, class... Args>
		inline unique<T> create(void* identity, Args... args)
		{
			unique<T> node = make_unique<Child>(&impl(), identity, args...);
			node->m_node_type = node_type<Child>();
			return node;
		}

		template <class Child = T>
		inline bool is(T& node) { return node.m_node_type == node_type<Child>(); }

		template <class Child = T, class... Args>
		inline Child& append(Args... args, void* identity = nullptr)
		{
			m_nodes.push_back(create<Child, Args...>(identity, args...)); return static_cast<Child&>(*m_nodes.back());
		}

		void clear() { m_nodes.clear(); }

		inline T& begin(bool preserve = false)
		{
			if (preserve)
				this->clean_tree_preserve(m_heartbeat);
			else
				this->clean_tree(m_heartbeat);
			m_heartbeat++;
			m_next = 0;
			return this->impl();
		}

		inline T& update(T& node) { node.m_heartbeat = m_heartbeat; node.m_next = 0; return node; }

		template <class Child = T, class... Args>
		inline Child& subx(uint16_t index, Args... args)
		{
			while (m_nodes.size() <= index)
				append<Child, Args...>(args..., nullptr);
			if (!is<Child>(*m_nodes[index]))
				m_nodes[index] = create<Child, Args...>(nullptr, args...);
			// the next positional children come after this one
			if (m_next <= index)
				m_next = index + 1;
			return static_cast<Child&>(update(*m_nodes[index]));
		}

		// a keyed child is looked up by its key from the current position, and moved there: it keeps its state when the children before it change
		// a child without key is matched by its position
		template <class Child = T, class... Args>
		inline Child& sub(NodeKey key, Args... args)
		{
			uint16_t index = m_next++;

			size_t found = index;
			if (key.m_value)
				while (found < m_nodes.size() && (m_nodes[found]->m_key != key.m_value || !is<Child>(*m_nodes[found]) || m_nodes[found]->m_heartbeat == m_heartbeat))
					++found;
			else if (found < m_nodes.size() && (m_nodes[found]->m_key || m_nodes[found]->m_identity || !is<Child>(*m_nodes[found])))
				found = m_nodes.size();

			if (found == m_nodes.size())
			{
				m_nodes.insert(m_nodes.begin() + index, create<Child, Args...>(nullptr, args...));
				m_nodes[index]->m_key = key.m_value;
			}
			else if (found != index)
			{
				unique<T> node = move(m_nodes[found]);
				m_nodes.erase(m_nodes.begin() + found);
				m_nodes.insert(m_nodes.begin() + index, move(node));
			}

			return static_cast<Child&>(update(*m_nodes[index]));
		}
		
		template <class Child = T, class... Args>
		inline Child& suba(Args... args)
		{
			return subx<Child, Args...>(m_next++, args...);
		}

		template <class Child = T, class... Args>
		inline Child& subi(void* identity, Args... args)
		{
			uint16_t index = m_next++;

			if (m_nodes.size() <= index)
				append<Child, Args...>(args..., identity);

			if (m_nodes[index]->m_identity != identity || !is<Child>(*m_nodes[index]))
				m_nodes.insert(m_nodes.begin() + index, create<Child, Args...>(identity, args...));

			return static_cast<Child&>(update(*m_nodes[index]));
		}

		inline T& root() { if (m_parent) return m_parent->root(); return impl(); }

		template <class T_State, class... Args>
		inline T_State& state(Args&&... args)
		{
			if (!m_state)
				m_state = make_unique<T_State>(static_cast<Args&&>(args)...);
			return static_cast<T_State&>(*m_state);
		}

		inline void clean_tree(size_t heartbeat)
		{
			remove_if(m_nodes, [=](unique<T>& node) { return node->m_heartbeat < heartbeat; });
			for (auto& child : m_nodes)
				child->clean_tree(heartbeat);
		}

		inline void clean_tree_preserve(size_t heartbeat)
		{
			for (auto& child : m_nodes)
			{
				if (child->m_heartbeat < heartbeat)
					child->clear();
				child->clean_tree_preserve(heartbeat);
			}
		}

		template <class Visitor>
		inline void visit(const Visitor& visitor)
		{
			bool visit = true;
			visitor(this->impl(), visit);

			if (visit)
				for (auto& child : m_nodes)
					child->visit(visitor);
		}
	};
}
