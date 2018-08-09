//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Ref.h>
#include <ui/Ui.h>
#endif
#include <uio/Forward.h>

namespace mud
{
	export_ MUD_UIO_EXPORT void set_meta_palette(const std::vector<uint32_t>& palette);

	export_ MUD_UIO_EXPORT void meta_description(Widget& parent, Type& type);

	export_ MUD_UIO_EXPORT void meta_constructors(Widget& parent, Class& cls);
	export_ MUD_UIO_EXPORT void meta_methods(Widget& parent, Class& cls);
	export_ MUD_UIO_EXPORT void meta_fields(Widget& parent, Class& cls);

	export_ MUD_UIO_EXPORT void meta_enum(Widget& parent, Enum& enu);

	export_ MUD_UIO_EXPORT void meta_synopsis(Widget& parent, Function& function);
	export_ MUD_UIO_EXPORT void meta_synopsis(Widget& parent, Method& method);
	export_ MUD_UIO_EXPORT void meta_synopsis(Widget& parent, Type& type);

	export_ MUD_UIO_EXPORT void class_edit(Widget& parent, Class& cls);
	export_ MUD_UIO_EXPORT void meta_edit(Widget& parent, Type& type);

	export_ MUD_UIO_EXPORT void meta_browser(Widget& parent, Module& m);
	export_ MUD_UIO_EXPORT void meta_browser(Widget& parent);

	export_ MUD_UIO_EXPORT void type_browser(Widget& parent);
}
