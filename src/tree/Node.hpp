//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <tree/Node.h>
#include <stl/algorithm.h>

namespace mud
{
	template <class T>
	Graph<T>::Graph() {}
	template <class T>
	Graph<T>::Graph(T* parent, void* identity) : m_parent(parent), m_identity(identity) {}
	template <class T>
	Graph<T>::~Graph() {}

	//template <class T>
	//T& Graph<T>::impl() { return static_cast<T&>(*this); }

	template <class T>
	template <class Child, class... Args>
	inline Child& Graph<T>::append(Args... args, void* identity) { m_nodes.push_back(construct<Child>(&impl(), identity, args...)); return static_cast<Child&>(*m_nodes.back()); }

	template <class T>
	void Graph<T>::clear() { m_nodes.clear(); }

	template <class T>
	inline T& Graph<T>::update(T& node) { node.m_heartbeat = m_heartbeat; node.m_next = 0; return node; }

	template <class T>
	template <class Child, class... Args>
	inline Child& Graph<T>::subx(uint16_t index, Args... args)
	{
		while (m_nodes.size() <= index)
			append<Child, Args...>(args..., nullptr);
		return static_cast<Child&>(update(*m_nodes[index]));
	}

	template <class T>
	template <class Child, class... Args>
	inline Child& Graph<T>::suba(Args... args)
	{
		return subx<Child, Args...>(m_next++, args...);
	}

	template <class T>
	template <class Child, class... Args>
	inline Child& Graph<T>::subi(void* identity, Args... args)
	{
		uint16_t index = m_next++;

		if (m_nodes.size() <= index)
			append<Child, Args...>(args..., identity);

		if (m_nodes[index]->m_identity != identity)
			m_nodes.insert(m_nodes.begin() + index, make_unique<Child>(&impl(), identity, args...));

		return static_cast<Child&>(update(*m_nodes[index]));
	}

	template <class T>
	inline T& Graph<T>::root() { if (m_parent) return m_parent->root(); return impl(); }

	template <class T>
	template <class T_State, class... Args>
	inline T_State& Graph<T>::state(Args&&... args)
	{
		if (!m_state)
			m_state = make_unique<T_State>(static_cast<Args&&>(args)...);
		return static_cast<T_State&>(*m_state);
	}

	template <class T>
	void Graph<T>::clean_tree(size_t heartbeat)
	{
		remove_if(m_nodes, [=](unique<T>& node) { return node->m_heartbeat < heartbeat; });
		for(auto& child : m_nodes)
			child->clean_tree(heartbeat);
	}

	template <class T>
	void Graph<T>::clean_tree_preserve(size_t heartbeat)
	{
		for(auto& child : m_nodes)
		{
			if(child->m_heartbeat < heartbeat)
				child->clear();
			child->clean_tree_preserve(heartbeat);
		}
	}

	template <class T>
	inline T& Graph<T>::begin(bool preserve)
	{
		if(preserve)
			this->clean_tree_preserve(m_heartbeat);
		else
			this->clean_tree(m_heartbeat);
		m_heartbeat++;
		m_next = 0;
		return this->impl();
	}

	template <class T>
	template <class Visitor>
	inline void Graph<T>::visit(const Visitor& visitor)
	{
		bool visit = true;
		visitor(this->impl(), visit);

		if(visit)
			for(auto& child : m_nodes)
				child->visit(visitor);
	}
}
