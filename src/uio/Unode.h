//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Ref.h>
#include <uio/Generated/Forward.h>
#include <ui/Ui.h>

namespace mud
{
	using Id = uint32_t;

	MUD_UIO_EXPORT bool modal_dialog(Widget& parent, cstring name, bool query = false);

	MUD_UIO_EXPORT void object_hook(Widget& parent, Ref object);
	MUD_UIO_EXPORT bool object_trigger(Widget& parent, Ref object);
}
