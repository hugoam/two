#pragma once

#include <mud/infra.h>
#include <mud/type.h>


#include <stl/vector.h>
#include <stl/memory.h>

#ifndef MUD_CPP_20
#include <stdint.h>
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
		vector<unique<T_Node>> m_nodes;
		unique<NodeState> m_state;
		uint16_t m_next = 0;
		
		template <class T_Child = T_Node, class... T_Args>
		inline T_Child& append(T_Args... args, void* identity = nullptr) { m_nodes.push_back(construct<T_Child>(&impl(), identity, args...)); return static_cast<T_Child&>(*m_nodes.back()); }

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



namespace mud
{
	export_ template <class T_Node>
	void clean_node_tree(T_Node& node, size_t heartbeat)
	{
		vector_remove_if(node.m_nodes, [=](unique<T_Node>& node) { return node->m_heartbeat < heartbeat; });
		for(auto& child : node.m_nodes)
			clean_node_tree(*child, heartbeat);
	}

	export_ template <class T_Node>
	void clean_node_tree_preserve(T_Node& node, size_t heartbeat)
	{
		for(auto& child : node.m_nodes)
		{
			if(child->m_heartbeat < heartbeat)
				child->clear();
			clean_node_tree_preserve(*child, heartbeat);
		}
	}

	export_ template <class T_Node>
	inline T_Node& begin_node(T_Node& node, bool preserve = false)
	{
		if(preserve)
			clean_node_tree_preserve<T_Node>(node, node.m_heartbeat);
		else
			clean_node_tree<T_Node>(node, node.m_heartbeat);
		node.m_heartbeat++;
		node.m_next = 0;
		return node;
	}

	export_ template <class T_Node, class T_Visitor>
	inline void visit_node(T_Node& node, const T_Visitor& visitor)
	{
		bool visit = true;
		visitor(node.impl(), visit);

		if(visit)
			for(auto& child : node.m_nodes)
				visit_node(*child, visitor);
	}
}






#ifndef MUD_TREE_EXPORT
#define MUD_TREE_EXPORT MUD_IMPORT
#endif


    
    

namespace mud {

    
    
    class NodeState;
}



#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <stdint.h>
#endif


namespace mud
{
    // Exported types
    
    
}
