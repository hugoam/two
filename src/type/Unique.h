//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/memory.h>
#include <type/Cls.h>

#ifndef MUD_CPP_20
#ifdef MUD_TRACK_MEMORY
#include <functional>
#include <type_traits>
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
	using object_ptr = unique_ptr<T, std::function<void(void*)>>;

	template<class T, class... Types>
	inline typename std::enable_if<!std::is_array<T>::value, object_ptr<T>>::type make_object(Types&&... args)
	{
		object_ptr_tracker<T>::increment();
		return (object_ptr<T>(new T(static_cast<Types&&>(args)...), &delete_tracked<T>));
	}
#else
	export_ template <class T>
	using object_ptr = unique_ptr<T>;

	export_ template <typename T, typename... Args>
	object_ptr<T> make_object(Args&&... args)
	{
		return make_unique<T>(static_cast<Args&&>(args)...);
	}
#endif
}
