//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Generated/Forward.h>
#include <obj/Ref.h>

#include <vector>

namespace mud
{
	class _refl_ MUD_UI_EXPORT User
	{
	public:
		std::vector<Ref> m_selection;
	};
}
