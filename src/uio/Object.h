//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <type/Ref.h>
#include <type/Dispatch.h>
#include <infra/Global.h>
#include <ui/Ui.h>
#endif
#include <uio/Forward.h>

#ifndef MUD_CPP_20
#include <string>
#endif

namespace mud
{
	using string = std::string;

	export_ MUD_UIO_EXPORT string object_name(Ref object);
	export_ MUD_UIO_EXPORT string object_icon(Ref object);

	export_ MUD_UIO_EXPORT Widget& object_button(Widget& parent, Ref object);
	export_ MUD_UIO_EXPORT Widget& object_item(Widget& parent, Ref object);
	export_ MUD_UIO_EXPORT bool object_item(Widget& parent, Ref object, Ref& selection);
	export_ MUD_UIO_EXPORT bool object_item(Widget& parent, Ref object, std::vector<Ref>& selection);
}
