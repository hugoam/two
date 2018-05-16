//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Var.h>

#include <functional>

namespace mud
{
	class MUD_OBJ_EXPORT Iterable
	{
	public:
		virtual ~Iterable() {}
		virtual size_t size() const = 0;
		virtual void iterate(const std::function<void(Ref)>& callback) const = 0;
		virtual bool has(Ref object) const = 0;
	};

	class MUD_OBJ_EXPORT Sequence : public Iterable
	{
	public:
		virtual void add(Ref value) = 0;
		virtual void remove(Ref value) = 0;
	};
}
