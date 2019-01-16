//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <stl/memory.h>
#include <infra/Config.h>

#ifndef MUD_CPP_20
#include <cstdint>
#endif

#ifndef MUD_TREE_EXPORT
#define MUD_TREE_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_TREE_EXPORT NodeState
	{
	public:
		virtual ~NodeState() {}
	};

	export_ class Graph
	{
	public:
		Graph() {}
		Graph(Graph* parent, void* identity) : m_parent(parent), m_identity(identity) {}

		Graph(Graph&& other) = default;
		Graph& operator=(Graph&& other) = default;

		Graph* m_parent = nullptr;
		void* m_identity = nullptr;
		size_t m_heartbeat = 0;
		vector<unique<Graph>> m_nodes;
		unique<NodeState> m_state;
		uint16_t m_next = 0;
		
		template <class T_Node>
		inline T_Node& append(void* identity = nullptr) { m_nodes.emplace_back(make_unique<Graph>(&impl(), identity)); return m_nodes.back()->impl<T_Node>(); }

		void clear() { m_nodes.clear(); }

		inline Graph& update(Graph& node) { node.m_heartbeat = m_heartbeat; node.m_next = 0; return node; }

		template <class T_Node>
		inline T_Node& sub(uint16_t index)
		{
			while(m_nodes.size() <= index)
				append<T_Node>();
			return update(*m_nodes[index]).impl<T_Node>();
		}
		
		template <class T_Node>
		inline T_Node& sub()
		{
			return sub<T_Node>(m_next++);
		}

		template <class T_Node>
		inline T_Node& sub(void* identity)
		{
			uint16_t index = m_next++;

			if(m_nodes.size() <= index)
				append<T_Node>(identity);

			if(m_nodes[index]->m_identity != identity)
				m_nodes.insert(m_nodes.begin() + index, make_unique<T_Node>(&impl(), identity));

			return static_cast<T_Node&>(update(*m_nodes[index]));
		}

		template <class T_Node, class... T_Args>
		T_Node& child_args(T_Args... args, void* identity = nullptr) { size_t index = m_next++; if(m_nodes.size() <= index) m_nodes.emplace_back(make_unique<T_Child>(&impl(), identity, args...)); update(*m_nodes[index]); return static_cast<T_Child&>(*m_nodes[index]); }

		inline Graph& root() { if(m_parent) return m_parent->root(); return *this; }

		template <class T_State, class... T_Args>
		inline T_State& state(T_Args&&... args)
		{
			if(!m_state)
				m_state = make_unique<T_State>(static_cast<T_Args&&>(args)...);
			return static_cast<T_State&>(*m_state);
		}
	};
}
