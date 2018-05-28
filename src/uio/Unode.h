//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Ref.h>
#include <obj/Util/Dispatch.h>
#include <obj/Util/Global.h>
#include <uio/Generated/Forward.h>
#include <ui/Ui.h>

namespace mud
{
	using Id = uint32_t;

	MUD_UIO_EXPORT bool modal_dialog(Widget& parent, cstring name, bool query = false);

	class MUD_UIO_EXPORT DispatchItem : public Dispatch<Widget&, Widget&>, public LazyGlobal<DispatchItem>
	{
	public:
		DispatchItem();
	};

	MUD_UIO_EXPORT Widget& object_button(Widget& parent, Ref object);
	MUD_UIO_EXPORT Widget& object_item(Widget& parent, Ref object);
	MUD_UIO_EXPORT bool object_item(Widget& parent, Ref object, Ref& selection);
	MUD_UIO_EXPORT bool object_item(Widget& parent, Ref object, std::vector<Ref>& selection);
}
