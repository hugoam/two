//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Ref.h>
#include <ui/Ui.h>
#endif
#include <uio/Generated/Forward.h>

namespace mud
{
	export_ MUD_UIO_EXPORT void meta_description(Widget& parent, Type& type);
	export_ MUD_UIO_EXPORT void meta_methods(Widget& parent, Type& type);
	export_ MUD_UIO_EXPORT void meta_fields(Widget& parent, Type& type);

	export_ MUD_UIO_EXPORT void meta_synopsis(Widget& parent, Function& function);
	export_ MUD_UIO_EXPORT void meta_synopsis(Widget& parent, Method& method);
	export_ MUD_UIO_EXPORT void meta_synopsis(Widget& parent, Type& type);

	export_ MUD_UIO_EXPORT void meta_edit(Widget& parent, Type& type);

	export_ MUD_UIO_EXPORT void meta_browser(Widget& parent, Module& m);
	export_ MUD_UIO_EXPORT void meta_browser(Widget& parent);

	export_ MUD_UIO_EXPORT void type_browser(Widget& parent);
}
