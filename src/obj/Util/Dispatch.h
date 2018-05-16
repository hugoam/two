//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Ref.h>
#include <obj/Type.h>

/* std */
#include <vector>
#include <functional>

namespace mud
{
	template <class T_Return, class... T_Args>
	class Dispatch
	{
	public:
		Dispatch()
			: m_branches(MUD_MAX_TYPES)
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
