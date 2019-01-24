//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

/* mud */
#include <bgfx/Config.h>
#include <ui-nanovg/VgNano.h>

namespace mud
{
	class VgNanoGl : public VgNano
	{
	public:
		VgNanoGl(cstring resource_path, bool clear = true);

		virtual void setup_context() final;
		virtual void release_context() final;

		void render(UiTarget& target);

		bool m_clear;
	};
}
