//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>

namespace two
{
	export_ class TWO_INFRA_EXPORT NonCopy
	{
	public:
		NonCopy() {}
		NonCopy(const NonCopy&) = delete;
		NonCopy& operator=(const NonCopy&) = delete;
	};
}
