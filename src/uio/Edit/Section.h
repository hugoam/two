//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Strung.h>
#include <ui/Structs/Widget.h>
#endif
#include <uio/Generated/Forward.h>
#include <uio/Unode.h>

namespace mud
{
	using Callback = std::function<void()>;

	export_ struct MUD_UIO_EXPORT SectionAction
	{
		strung m_name;
		Callback m_action;
	};

	using ActionList = std::vector<SectionAction>;

	export_ struct MUD_UIO_EXPORT Section : public Widget
	{
		Section(Widget* parent, void* identity) : Widget(parent, identity) {}
		Widget* m_toolbar = nullptr;
	};

	MUD_UIO_EXPORT Section& section(Widget& parent, cstring name, const ActionList& actions = {}, bool no_toolbar = false);
}
