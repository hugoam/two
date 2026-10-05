//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>

#ifndef TWO_TREE_EXPORT
#define TWO_TREE_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_TREE_EXPORT NodeState
	{
	public:
		virtual ~NodeState() {}
	};

	// identifies a type, e.g of the states of a node
	export_ template <class T>
	inline const void* node_type() { static const char tag = 0; return &tag; }
}
