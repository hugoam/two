//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Generated/Forward.h>
#include <obj/Unique.h>

namespace mud
{
	using cstring = const char*;

	class _refl_ MUD_UI_EXPORT Style
	{
	public:
		Style(cstring name, Style* base, const Args& args);
		Style(cstring name, Style& base, const Args& args) : Style(name, &base, args) {}
		~Style();

		Style(const Style& other);
		Style& operator=(const Style& other);
		
		void prepare();

		InkStyle& state_skin(WidgetState state);
		InkStyle& decline_skin(WidgetState state);

		_attr_ Style* m_base;
		_attr_ cstring name();
		_attr_ Layout& layout();
		_attr_ InkStyle& skin();
		
		struct Impl;
		unique_ptr<Impl> m_impl;

		bool m_defined;
	};
}
