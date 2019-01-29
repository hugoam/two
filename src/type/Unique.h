//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/memory.h>

#ifndef MUD_CPP_20
#ifdef MUD_TRACK_MEMORY
#include <type/Cls.h>
#include <stl/type_traits.h>
#include <stl/function.h>
#endif
#endif

namespace mud
{
#ifdef MUD_TRACK_MEMORY
	template <class T>
	struct object_ptr_tracker
	{
		static void increment() { type<T>().debugTotalCount += 1; type<T>().debugTotalMemory += sizeof(T); }
		static void decrement() { type<T>().debugTotalCount -= 1; type<T>().debugTotalMemory -= sizeof(T); }
	};

	template <class T>
	void delete_tracked(void* object)
	{
		object_ptr_tracker<T>::decrement();
		delete static_cast<T*>(object);
	}

	template <class T>
	using object = unique<T, function<void(void*)>>;

	template<class T, class... Types>
	inline object<T> oconstruct(Types&&... args)
	{
		object_ptr_tracker<T>::increment();
		return (object<T>(new T(static_cast<Types&&>(args)...), &delete_tracked<T>));
	}
#else
	export_ template <class T>
	using object = unique<T>;

	export_ template <typename T, typename... Args>
	object<T> oconstruct(Args&&... args)
	{
		return construct<T>(static_cast<Args&&>(args)...);
	}
#endif
}
