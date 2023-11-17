//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Ref.h>
#include <type/Type.h>

namespace two
{
	export_ template <class T_Return, class... Args>
	class Dispatch
	{
	public:
		using HandlerFunc = T_Return(*)(void*, Ref, Args...);
		struct Func { void* f = nullptr; HandlerFunc handler = nullptr; };

		Dispatch() {}

		void function(Type& type, HandlerFunc func)
		{
			m_branches[type.m_id] = { nullptr, func };
		}

		template <class T>
		void function(HandlerFunc func)
		{
			m_branches[type<T>().m_id] = { nullptr, func };
		}

		T_Return dispatch(Ref ref, Args... args)
		{
			const Func& func = m_branches[ref.m_type->m_id];
			return func.handler(func.f, ref, static_cast<Args&&>(args)...);
		}

		bool check(Type& type)
		{
			return m_branches[type.m_id].handler != nullptr;
		}

		bool check(Ref ref)
		{
			return m_branches[ref.m_type->m_id].handler != nullptr;
		}

		Func m_branches[c_max_types] = {};
	};
}
