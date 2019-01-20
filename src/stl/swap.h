#pragma once

#include <infra/Config.h>

#ifndef MUD_NO_STL
#include <utility>
namespace mud
{
	using std::swap;
}
#else
#include <stl/move.h>
namespace mud
{
	namespace
	{
		template<typename T>
		inline void swap(T& t1, T& t2)
		{
			T temp = move(t1);
			t1 = move(t2);
			t2 = move(temp);
		}
	}
}
#endif

