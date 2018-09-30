//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>
#include <type/Ref.h>

#ifndef MUD_CPP_20
#include <functional>
#endif

namespace mud
{
	export_ class MUD_REFL_EXPORT Iterable
	{
	public:
		virtual ~Iterable() {}
		virtual size_t size() const = 0;
		virtual void iterate(const std::function<void(Ref)>& callback) const = 0;
		virtual bool has(Ref object) const = 0;
	};

	export_ class MUD_REFL_EXPORT Sequence : public Iterable
	{
	public:
		virtual void add(Ref value) = 0;
		virtual void remove(Ref value) = 0;
	};
}
