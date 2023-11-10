//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
#endif
#include <type/Ref.h>
#include <type/Type.h>

namespace two
{
	export_ class TWO_TYPE_EXPORT DoubleDispatch
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

		bool check(const Type& first, const Type& second)
		{
			if(m_branches.size() > first.m_id && m_branches[first.m_id].size() > second.m_id)
				return m_branches[first.m_id][second.m_id] != nullptr;
			return false;
		}

		vector<vector<void (*)(Ref, Ref)>> m_branches;
	};
}
