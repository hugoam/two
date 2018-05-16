//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Reflect/Class.h>
#include <obj/Iterable/Iterable.h>

namespace mud
{
	inline void iterate_dict(Ref object, const std::function<void(Ref, Ref)>& callback)
	{
		UNUSED(object); UNUSED(callback);
	}

	inline void iterate_sequence(Ref object, const std::function<void(size_t, Ref)>& callback)
	{
		UNUSED(object); UNUSED(callback);
	}

	inline void iterate_sequence(Ref object, const std::function<void(Ref)>& callback)
	{
		unique_ptr<Iterable> iterable = cls(object).m_iterable(object);
		iterable->iterate(callback);
	}

	inline void add_sequence(Ref value, Ref element)
	{
		unique_ptr<Sequence> sequence = cls(value).m_sequence(value);
		sequence->add(element);
	}

	inline void remove_sequence(Ref value, Ref element)
	{
		unique_ptr<Sequence> sequence = cls(value).m_sequence(value);
		sequence->remove(element);
	}
}
