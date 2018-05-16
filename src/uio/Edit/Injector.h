//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Reflect/Injector.h>
#include <uio/Generated/Forward.h>
#include <uio/Unode.h>

namespace mud
{
	MUD_UIO_EXPORT void meta_object_creator(Widget& parent);
	MUD_UIO_EXPORT void object_injector(Widget& parent, Injector& injector);
	MUD_UIO_EXPORT bool object_creator(Widget& parent, Creator& creator);

	MUD_UIO_EXPORT bool object_creator(Widget& parent, Type& type);
}
