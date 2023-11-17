//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <uio/Forward.h>

namespace two
{
	export_ class TWO_UIO_EXPORT DispatchSelector : public Dispatch<bool, Widget&>, public LazyGlobal<DispatchSelector>
	{
	public:
		DispatchSelector();
	};

	export_ TWO_UIO_EXPORT void complex_indexer(Widget& parent, Indexer& indexer, vector<Ref>* selection = nullptr);
	export_ TWO_UIO_EXPORT void object_indexer(Widget& parent, Indexer& indexer, vector<Ref>* selection = nullptr);

	export_ TWO_UIO_EXPORT bool object_selector(Widget& parent, Indexer& indexer, Ref& result);
	export_ TWO_UIO_EXPORT bool object_selector(Widget& parent, Ref& result);

	export_ TWO_UIO_EXPORT void object_indexer_modal(Widget& parent, Indexer& indexer);
	export_ TWO_UIO_EXPORT bool object_selector_modal(Widget& screen, Widget& parent, Ref& result);
}
