//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <uio/Forward.h>

namespace two
{
	export_ class TWO_UIO_EXPORT DispatchItem : public Dispatch<Widget&, Widget&>, public LazyGlobal<DispatchItem>
	{
	public:
		DispatchItem();
	};
}
