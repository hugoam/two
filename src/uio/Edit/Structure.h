//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Ref.h>
#include <uio/Generated/Forward.h>

#include <vector>

namespace mud
{
	MUD_UIO_EXPORT void structure_node(Widget& parent, Ref object, std::vector<Ref>& selection);
	MUD_UIO_EXPORT void structure_view(Widget& parent, Ref object, std::vector<Ref>& selection);
}
