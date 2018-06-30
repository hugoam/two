//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Ref.h>
#include <obj/Type.h>

#ifndef MUD_CPP_20
#include <vector>
#include <functional>
#endif

namespace mud
{
	export_ class MUD_OBJ_EXPORT DoubleDispatch
	{
	public:
		DoubleDispatch()
			: m_branches()
		{}

		void resize(Type& first, Type& second)
		{
			if(first.m_id + 1U > m_branches.size())
				m_branches.resize(first.m_id + 1U);
			if(second.m_id + 1U > m_branches[first.m_id].size())
				m_branches[first.m_id].resize(second.m_id + 1U);
		}

		void dispatch(Ref first, Ref second)
		{
			return m_branches[first.m_type->m_id][second.m_type->m_id](first, second);
		}

		bool check(Ref first, Ref second)
		{
			return check(*first.m_type, *second.m_type);
		}

		bool check(Type& first, Type& second)
		{
			if(m_branches.size() > first.m_id && m_branches[first.m_id].size() > second.m_id)
				return m_branches[first.m_id][second.m_id] != nullptr;
			return false;
		}

		std::vector<std::vector<std::function<void (Ref, Ref)>>> m_branches;
	};
}
