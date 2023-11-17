//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>

namespace two
{
	export_ struct TWO_UI_EXPORT Section : public Widget
	{
		Section(Widget* parent, void* identity) : Widget(parent, identity) {}
		Widget* m_toolbar = nullptr;
	};

	export_ TWO_UI_EXPORT Section& section(Widget& parent, const string& name, bool no_toolbar = false);
	export_ TWO_UI_EXPORT bool section_action(Section& parent, const string& name);
}
