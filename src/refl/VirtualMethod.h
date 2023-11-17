//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>

namespace two
{
	//extern template class refl_ function<void(Method&, Ref, span<Var>)>;
	export_ using VirtualMethod = function<void(Method&, Ref, span<Var>)>;

	export_ template <> TWO_REFL_EXPORT Type& type<VirtualMethod>();
}
