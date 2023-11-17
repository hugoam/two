//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <bgfx/Config.h>
#include <ui-nanovg/VgNano.h>

namespace two
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
