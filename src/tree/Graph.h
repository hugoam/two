//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stdint.h>
#include <stl/vector.h>
#include <stl/memory.h>
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

	export_ template <class T>
	class Graph
	{
	public:
		Graph();
		Graph(T* parent, void* identity);
		virtual ~Graph();

		Graph(Graph<T>&& other) = default;
		Graph<T>& operator=(Graph<T>&& other) = default;

		inline T& impl() { return static_cast<T&>(*this); }

		T* m_parent = nullptr;
		void* m_identity = nullptr;
		size_t m_heartbeat = 0;
		vector<unique<T>> m_nodes;
		unique<NodeState> m_state;
		uint16_t m_next = 0;
		
		template <class Child = T, class... Args>
		inline Child& append(Args... args, void* identity = nullptr);

		void clear();

		inline T& begin(bool preserve = false);

		inline T& update(T& node);

		template <class Child = T, class... Args>
		inline Child& subx(uint16_t index, Args... args);
		
		template <class Child = T, class... Args>
		inline Child& suba(Args... args);

		template <class Child = T, class... Args>
		inline Child& subi(void* identity, Args... args);

		inline T& root();

		template <class T_State, class... Args>
		inline T_State& state(Args&&... args);

		inline void clean_tree(size_t heartbeat);
		inline void clean_tree_preserve(size_t heartbeat);

		template <class Visitor>
		inline void visit(const Visitor& visitor);
	};
}
