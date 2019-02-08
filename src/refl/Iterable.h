//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>
#include <type/Ref.h>

namespace mud
{
	export_ class MUD_REFL_EXPORT Iterable
	{
	public:
		Type* m_element_type;

		using Size = size_t(*)(void*); Size m_size;
		using At = void*(*)(void*, size_t); At m_at;

		inline size_t size(Ref vec) const { return m_size(vec.m_value); }
		inline Ref at(Ref vec, size_t i) const { return Ref(m_at(vec.m_value, i), *m_element_type); }
		inline Ref front(Ref vec) const { return at(vec, 0); }
		inline Ref back(Ref vec) const { return at(vec, size(vec) - 1); }

		template <class Visitor>
		void iterate(Ref vec, Visitor visitor) const
		{
			const size_t count = this->size(vec);
			for(size_t i = 0; i < count; ++i)
				visitor(this->at(vec, i));
		}

		template <class Visitor>
		void iteratei(Ref vec, Visitor visitor) const
		{
			const size_t count = this->size(vec);
			for(size_t i = 0; i < count; ++i)
				visitor(i, this->at(vec, i));
		}
	};

	export_ class MUD_REFL_EXPORT Sequence
	{
	public:
		using Push = void(*)(void*); Push m_push;
		using Add = void(*)(void*, void*); Add m_add;
		using Remove = void(*)(void*, void*); Remove m_remove;

		inline void push(Ref vec) const { m_push(vec.m_value); }
		inline void add(Ref vec, Ref element) const { m_add(vec.m_value, element.m_value); }
		inline void remove(Ref vec, Ref element) const { m_remove(vec.m_value, element.m_value); }
	};
}
