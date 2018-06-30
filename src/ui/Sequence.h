//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Ref.h>
#endif
#include <ui/Forward.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
namespace ui
{
	export_ MUD_UI_EXPORT func_ Sequence& sequence(Widget& parent);
	export_ MUD_UI_EXPORT func_ Sequence& scroll_sequence(Widget& parent);
	export_ MUD_UI_EXPORT func_ bool select_logic(Widget& element, Ref object, std::vector<Ref>& selection);
	export_ MUD_UI_EXPORT func_ bool select_logic(Widget& element, Ref object, Ref& selection);
	export_ MUD_UI_EXPORT func_ Widget& element(Widget& parent, Ref object);
	export_ MUD_UI_EXPORT func_ Widget& element(Widget& parent, Ref object, std::vector<Ref>& selection);
	export_ MUD_UI_EXPORT func_ Widget& element(Sequence& parent, Ref object);
}
}
