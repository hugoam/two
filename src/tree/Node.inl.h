//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <tree/Node.h>
#include <infra/Vector.h>

namespace mud
{
	export_ template <class T_Node>
	void clean_node_tree(T_Node& node, size_t heartbeat)
	{
		vector_remove_if(node.m_nodes, [=](unique_ptr<T_Node>& node) { return node->m_heartbeat < heartbeat; });
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
