//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/Vec.h>
#include <ui/Generated/Forward.h>
#include <ui/Frame/Dim.h>

namespace mud
{
	struct _refl_ MUD_UI_EXPORT UiRect
	{
		_attr_ _mut_ vec2 m_position = Zero2;
		_attr_ _mut_ vec2 m_size = Zero2;
		_attr_ _mut_ vec2 m_content = Zero2;
		_attr_ _mut_ vec2 m_span = Unit2;
		_attr_ _mut_ float m_scale = 1.f;
	};
}
