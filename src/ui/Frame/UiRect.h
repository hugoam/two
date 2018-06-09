//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <math/Vec.h>
#endif
#include <ui/Forward.h>
#include <ui/Frame/Dim.h>

namespace mud
{
	export_ struct refl_ MUD_UI_EXPORT UiRect
	{
		attr_ mut_ vec2 m_position = Zero2;
		attr_ mut_ vec2 m_size = Zero2;
		attr_ mut_ vec2 m_content = Zero2;
		attr_ mut_ vec2 m_span = Unit2;
		attr_ mut_ float m_scale = 1.f;
	};
}
