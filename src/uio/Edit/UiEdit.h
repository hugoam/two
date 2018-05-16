//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <uio/Generated/Forward.h>
#include <uio/Unode.h>

namespace mud
{
	MUD_UIO_EXPORT void ui_debug_modal(Widget& parent, Widget& target);
	MUD_UIO_EXPORT void ui_debug_layout(Widget& parent, Widget& target);
	MUD_UIO_EXPORT void ui_debug(Widget& parent, Widget& target);

	MUD_UIO_EXPORT void ui_edit(Widget& parent, Sequence& selection);
	MUD_UIO_EXPORT void ui_editor(Widget& parent);
}
