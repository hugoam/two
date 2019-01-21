//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <type/Ref.h>
#endif
#include <ui/Forward.h>

namespace mud
{
namespace ui
{
	export_ MUD_UI_EXPORT func_ Sequence& sequence(Widget& parent);
	export_ MUD_UI_EXPORT func_ Sequence& scroll_sequence(Widget& parent);

	export_ MUD_UI_EXPORT func_ bool multiselect_logic(Widget& element, Ref object, vector<Ref>& selection);
	export_ MUD_UI_EXPORT func_ bool select_logic(Widget& element, Ref object, Ref& selection);

	export_ MUD_UI_EXPORT func_ Widget& element(Widget& parent, Ref object);
	export_ MUD_UI_EXPORT Widget& element(Widget& parent, Ref object, vector<Ref>& selection);

	export_ MUD_UI_EXPORT func_ Widget& sequence_element(Sequence& parent, Ref object);
}
}
