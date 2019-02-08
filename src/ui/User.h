//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <type/Ref.h>
#endif
#include <ui/Forward.h>

namespace mud
{
	export_ class refl_ MUD_UI_EXPORT User
	{
	public:
		vector<Ref> m_selection;
	};
}
