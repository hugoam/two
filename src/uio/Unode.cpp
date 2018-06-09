//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.uio;
#else
#include <ui/Structs/Window.h>
#include <ui/Structs/Container.h>
#include <uio/Unode.h>
#endif

namespace mud
{
	DispatchItem::DispatchItem()
	{}

	bool modal_dialog(Widget& parent, cstring name, bool query)
	{
		Widget& self = ui::window(parent.root(), name);
		bool closed = !self.m_body || ui::button(parent, query ? "Done" : "Cancel").activated();
		//if(closed)
		//	self.close();
		return closed;
	}
}
