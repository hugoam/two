//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Ref.h>
#include <type/Type.h>

#ifndef MUD_CPP_20
#include <vector>
#include <functional>
#endif

namespace mud
{
	export_ template <class T_Return, class... T_Args>
	class Dispatch
	{
	public:
		Dispatch()
			: m_branches(c_max_types)
		{}

		void function(Type& type, const std::function<T_Return(Ref, T_Args...)>& func)
		{
			m_branches[type.m_id] = func;
		}

		template <class T>
		void function(const std::function<T_Return(Ref, T_Args...)>& func)
		{
			m_branches[type<T>().m_id] = func;
		}

		T_Return dispatch(Ref ref, T_Args... args)
		{
			return m_branches[ref.m_type->m_id](ref, std::forward<T_Args>(args)...);
		}

		bool check(Type& type)
		{
			return m_branches[type.m_id] != nullptr;
		}

		bool check(Ref ref)
		{
			return m_branches[ref.m_type->m_id] != nullptr;
		}

		std::vector<std::function<T_Return(Ref, T_Args...)>> m_branches;
	};
}
