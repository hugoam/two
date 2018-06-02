//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Ref.h>
#include <uio/Generated/Forward.h>
#include <ui/Ui.h>

namespace mud
{
	MUD_UIO_EXPORT void meta_description(Widget& parent, Type& type);
	MUD_UIO_EXPORT void meta_methods(Widget& parent, Type& type);
	MUD_UIO_EXPORT void meta_fields(Widget& parent, Type& type);

	MUD_UIO_EXPORT void meta_synopsis(Widget& parent, Function& function);
	MUD_UIO_EXPORT void meta_synopsis(Widget& parent, Method& method);
	MUD_UIO_EXPORT void meta_synopsis(Widget& parent, Type& type);

	MUD_UIO_EXPORT void meta_edit(Widget& parent, Type& type);

	MUD_UIO_EXPORT void meta_browser(Widget& parent, Module& m);
	MUD_UIO_EXPORT void meta_browser(Widget& parent);

	MUD_UIO_EXPORT void type_browser(Widget& parent);
}
