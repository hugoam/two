//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/function.h>
#include <type/Ref.h>
#include <type/Any.h>
#endif
#include <refl/Forward.h>

namespace two
{
	//extern template class refl_ function<void(Method&, Ref, span<Var>)>;
	export_ using VirtualMethod = function<void(Method&, Ref, span<Var>)>;

	export_ template <> TWO_REFL_EXPORT Type& type<VirtualMethod>();
}
