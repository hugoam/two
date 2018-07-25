//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Ref.h>
#include <obj/Dispatch.h>
#include <infra/Global.h>
#include <ui/Ui.h>
#endif
#include <uio/Forward.h>

namespace mud
{
	export_ class MUD_UIO_EXPORT DispatchItem : public Dispatch<Widget&, Widget&>, public LazyGlobal<DispatchItem>
	{
	public:
		DispatchItem();
	};
}
