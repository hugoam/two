//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <math/Vec.h>
#endif
#include <ui/Forward.h>
#include <ui/Frame/Dim.h>

namespace two
{
	export_ struct refl_ TWO_UI_EXPORT UiRect
	{
		attr_ vec2 m_position = vec2(0.f);
		attr_ vec2 m_size = vec2(0.f);
		attr_ vec2 m_content = vec2(0.f);
		attr_ vec2 m_span = vec2(1.f);
		attr_ float m_scale = 1.f;
	};
}
