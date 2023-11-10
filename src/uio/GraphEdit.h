//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
#include <type/Ref.h>
#endif
#include <uio/Forward.h>

namespace two
{
	export_ TWO_UIO_EXPORT void structure_node(Widget& parent, Ref object, vector<Ref>& selection);
	export_ TWO_UIO_EXPORT void structure_view(Widget& parent, Ref object, vector<Ref>& selection);
}
