//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <uio/Forward.h>

namespace two
{
	export_ TWO_UIO_EXPORT bool call_edit(Widget& parent, Call& call);

	export_ TWO_UIO_EXPORT void callable_edit(Widget& parent, Callable& callable);
	export_ TWO_UIO_EXPORT void function_edit(Widget& parent, Function& function);
	export_ TWO_UIO_EXPORT void method_edit(Widget& parent, Ref object, Method& method);
	export_ TWO_UIO_EXPORT void method_hook(Widget& parent, Ref object, Method& method);
}
