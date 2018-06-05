//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Ref.h>
#endif
#include <uio/Generated/Forward.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	MUD_UIO_EXPORT void structure_node(Widget& parent, Ref object, std::vector<Ref>& selection);
	MUD_UIO_EXPORT void structure_view(Widget& parent, Ref object, std::vector<Ref>& selection);
}
