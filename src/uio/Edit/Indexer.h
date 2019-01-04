//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <type/Dispatch.h>
#include <infra/Global.h>
#endif
#include <uio/Forward.h>
#include <uio/Unode.h>

namespace mud
{
	export_ class MUD_UIO_EXPORT DispatchSelector : public Dispatch<bool, Widget&>, public LazyGlobal<DispatchSelector>
	{
	public:
		DispatchSelector();
	};

	export_ MUD_UIO_EXPORT void complex_indexer(Widget& parent, Indexer& indexer, std::vector<Ref>* selection = nullptr);
	export_ MUD_UIO_EXPORT void object_indexer(Widget& parent, Indexer& indexer, std::vector<Ref>* selection = nullptr);

	export_ MUD_UIO_EXPORT bool object_selector(Widget& parent, Indexer& indexer, Ref& result);
	export_ MUD_UIO_EXPORT bool object_selector(Widget& parent, Ref& result);

	export_ MUD_UIO_EXPORT void object_indexer_modal(Widget& parent, Indexer& indexer);
	export_ MUD_UIO_EXPORT bool object_selector_modal(Widget& screen, Widget& parent, Ref& result);
}
