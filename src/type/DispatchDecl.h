//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Dispatch.h>
#include <type/DoubleDispatch.h>
#include <type/Any.h>

namespace mud
{
	export_ template <class T, class T_Function, class T_Return, class... T_Args>
	void dispatch_branch(Dispatch<T_Return, T_Args...>& dispatch, T_Function func)
	{
		dispatch.m_branches[type<T>().m_id] = [func](Ref ref, T_Args... args) -> T_Return { return func(val<T>(ref), std::forward<T_Args>(args)...); };
	}

	export_ template <class T, class T_Function, class T_Return, class... T_Args>
	void dispatch_ref_branch(Dispatch<T_Return, T_Args...>& dispatch, T_Function func)
	{
		dispatch.m_branches[type<T>().m_id] = [func](Ref ref, T_Args... args) -> T_Return { return func(ref, val<T>(ref), std::forward<T_Args>(args)...); };
	}

	export_ template <class T_First, class T_Second, void(*func)(T_First&, T_Second&)>
	void dispatch_branch(DoubleDispatch& dispatch)
	{
		dispatch.resize(type<T_First>(), type<T_Second>());
		dispatch.m_branches[type<T_First>().m_id][type<T_Second>().m_id] = [](Ref first, Ref second) { func(val<T_First>(first), val<T_Second>(second)); };
	}
}
