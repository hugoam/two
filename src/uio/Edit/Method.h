//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <uio/Generated/Forward.h>
#include <uio/Unode.h>

namespace mud
{
	MUD_UIO_EXPORT bool call_edit(Widget& parent, Call& call);

	MUD_UIO_EXPORT void callable_edit(Widget& parent, Callable& callable);
	MUD_UIO_EXPORT void function_edit(Widget& parent, Function& function);
	MUD_UIO_EXPORT void method_edit(Widget& parent, Ref object, Method& method);
	MUD_UIO_EXPORT void method_hook(Widget& parent, Ref object, Method& method);
}
