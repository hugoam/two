//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/function.h>
#include <type/Ref.h>
#include <type/Any.h>
#include <refl/Forward.h>

namespace mud
{
	export_ using VirtualMethod = function<void(Method&, Ref, span<Var>)>;

	export_ template <> MUD_REFL_EXPORT Type& type<VirtualMethod>();
}
