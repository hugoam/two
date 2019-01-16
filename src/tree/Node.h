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

	export_ template <class T_Node>
	class Graph
	{
	public:
		Graph() {}
		Graph(T_Node* parent, void* identity) : m_parent(parent), m_identity(identity) {}
		virtual ~Graph() {}

		Graph(Graph<T_Node>&& other) = default;
		Graph<T_Node>& operator=(Graph<T_Node>&& other) = default;

		T_Node& impl() { return static_cast<T_Node&>(*this); }

		T_Node* m_parent = nullptr;
		void* m_identity = nullptr;
		size_t m_heartbeat = 0;
		vector<unique_ptr<T_Node>> m_nodes;
		unique_ptr<NodeState> m_state;
		uint16_t m_next = 0;
		
		template <class T_Child = T_Node, class... T_Args>
		inline T_Child& append(T_Args... args, void* identity = nullptr) { m_nodes.emplace_back(construct<T_Child>(&impl(), identity, args...)); return static_cast<T_Child&>(*m_nodes.back()); }

		void clear() { m_nodes.clear(); }

		inline T_Node& update(T_Node& node) { node.m_heartbeat = m_heartbeat; node.m_next = 0; return node; }

		template <class T_Child = T_Node, class... T_Args>
		inline T_Child& subx(uint16_t index, T_Args... args)
		{
			while(m_nodes.size() <= index)
				append<T_Child, T_Args...>(args..., nullptr);
			return static_cast<T_Child&>(update(*m_nodes[index]));
		}
		
		template <class T_Child = T_Node, class... T_Args>
		inline T_Child& suba(T_Args... args)
		{
			return subx<T_Child, T_Args...>(m_next++, args...);
		}

		template <class T_Child = T_Node, class... T_Args>
		inline T_Child& subi(void* identity, T_Args... args)
		{
			uint16_t index = m_next++;

			if(m_nodes.size() <= index)
				append<T_Child, T_Args...>(args..., identity);

			if(m_nodes[index]->m_identity != identity)
				m_nodes.insert(m_nodes.begin() + index, make_unique<T_Child>(&impl(), identity, args...));

			return static_cast<T_Child&>(update(*m_nodes[index]));
		}

		inline T_Node& root() { if(m_parent) return m_parent->root(); return impl(); }

		template <class T_State, class... T_Args>
		inline T_State& state(T_Args&&... args)
		{
			if(!m_state)
				m_state = make_unique<T_State>(static_cast<T_Args&&>(args)...);
			return static_cast<T_State&>(*m_state);
		}
	};
}
