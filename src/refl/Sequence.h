//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>
#include <refl/Class.h>
#include <refl/Iterable.h>

namespace mud
{
	export_ inline size_t sequence_size(Ref object)
	{
		unique_ptr<Iterable> iterable = cls(object).m_iterable(object);
		return iterable->size();
	}

	export_ inline void iterate_dict(Ref object, const std::function<void(Ref, Ref)>& callback)
	{
		UNUSED(object); UNUSED(callback);
	}

	export_ inline void iterate_sequence(Ref object, const std::function<void(size_t, Ref)>& callback)
	{
		UNUSED(object); UNUSED(callback);
	}

	export_ inline void iterate_sequence(Ref object, const std::function<void(Ref)>& callback)
	{
		if(cls(object).m_is_iterable)
		{
			((Iterable*) object.m_value)->iterate(callback);
		}
		else
		{
			unique_ptr<Iterable> iterable = cls(object).m_iterable(object);
			iterable->iterate(callback);
		}
	}

	export_ inline void add_sequence(Ref value, Ref element)
	{
		unique_ptr<Sequence> sequence = cls(value).m_sequence(value);
		sequence->add(element);
	}

	export_ inline void remove_sequence(Ref value, Ref element)
	{
		unique_ptr<Sequence> sequence = cls(value).m_sequence(value);
		sequence->remove(element);
	}
}
