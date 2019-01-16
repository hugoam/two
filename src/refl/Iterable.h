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
		using Size = size_t(*)(Ref); Size size;
		using At = Ref(*)(Ref, size_t); At at;

		template <class T_Visitor>
		void iterate(Ref vec, T_Visitor visitor) const
		{
			size_t count = this->size(vec);
			for(size_t i = 0; i < count; ++i)
				visitor(this->at(vec, i));
		}

		template <class T_Visitor>
		void iteratei(Ref vec, T_Visitor visitor) const
		{
			size_t count = this->size(vec);
			for(size_t i = 0; i < count; ++i)
				visitor(i, this->at(vec, i));
		}
	};

	export_ class MUD_REFL_EXPORT Sequence
	{
	public:
		using Add = void(*)(Ref, Ref); Add add;
		using Remove = void(*)(Ref, Ref); Remove remove;
	};
}
