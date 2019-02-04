//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/vector.h>
#include <type/Ref.h>
#include <type/Dispatch.h>
#include <infra/Global.h>
#include <ui/Ui.h>
#endif
#include <uio/Forward.h>

namespace mud
{
	export_ MUD_UIO_EXPORT string object_name(Ref object);
	export_ MUD_UIO_EXPORT string object_icon(Ref object);

	export_ MUD_UIO_EXPORT Widget& object_button(Widget& parent, Ref object);
	export_ MUD_UIO_EXPORT Widget& object_item(Widget& parent, Ref object);
	export_ MUD_UIO_EXPORT bool object_item(Widget& parent, Ref object, Ref& selection);
	export_ MUD_UIO_EXPORT bool object_item(Widget& parent, Ref object, vector<Ref>& selection);
}
