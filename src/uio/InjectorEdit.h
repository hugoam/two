//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <refl/Injector.h>
#endif
#include <uio/Forward.h>

namespace two
{
	export_ TWO_UIO_EXPORT void meta_object_creator(Widget& parent);
	export_ TWO_UIO_EXPORT void object_injector(Widget& parent, Injector& injector);
	export_ TWO_UIO_EXPORT bool object_creator(Widget& parent, Creator& creator);

	export_ TWO_UIO_EXPORT bool object_switch_creator(Widget& parent, span<Type*> types);
	export_ TWO_UIO_EXPORT bool object_creator(Widget& parent, Type& type);
}
