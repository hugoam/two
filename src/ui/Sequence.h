//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Ref.h>
#include <ui/Generated/Forward.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
namespace ui
{
	MUD_UI_EXPORT _func_ Sequence& sequence(Widget& parent);
	MUD_UI_EXPORT _func_ bool select_logic(Widget& element, Ref object, std::vector<Ref>& selection);
	MUD_UI_EXPORT _func_ bool select_logic(Widget& element, Ref object, Ref& selection);
	MUD_UI_EXPORT _func_ Widget& element(Widget& parent, Ref object);
	MUD_UI_EXPORT _func_ Widget& element(Widget& parent, Ref object, std::vector<Ref>& selection);
	MUD_UI_EXPORT _func_ Widget& element(Sequence& parent, Ref object);
}
}
