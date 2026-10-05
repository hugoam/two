//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>

namespace two
{
	// a section with a title, and a toolbar: the content goes in the body, scrolled
	export_ struct Section
	{
		Widget& self;
		Widget* toolbar;
		Widget& body;
		operator Widget&() const { return self; }
	};

	export_ TWO_UI_EXPORT Section section(NodeKey id, Widget& parent, const string& name, bool no_toolbar = false);
	export_ TWO_UI_EXPORT bool section_action(Section& parent, const string& name);
}
