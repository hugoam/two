//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Ref.h>
#include <obj/Util/Dispatch.h>
#include <obj/Util/Global.h>
#include <ui/Ui.h>
#endif
#include <uio/Generated/Forward.h>

namespace mud
{
	export_ MUD_UIO_EXPORT bool modal_dialog(Widget& parent, cstring name, bool query = false);

	export_ class MUD_UIO_EXPORT DispatchItem : public Dispatch<Widget&, Widget&>, public LazyGlobal<DispatchItem>
	{
	public:
		DispatchItem();
	};
}
