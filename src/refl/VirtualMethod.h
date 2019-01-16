//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <type/Ref.h>
#include <type/Any.h>
#include <refl/Forward.h>

#include <functional>

namespace mud
{
	export_ using VirtualMethod = std::function<void(Method&, Ref, array<Var>)>;

	export_ template <> MUD_REFL_EXPORT Type& type<VirtualMethod>();
}
