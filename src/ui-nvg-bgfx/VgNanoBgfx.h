//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Generated/Forward.h>
#include <ui-nanovg/VgNano.h>

namespace two
{
	class VgNanoBgfx : public VgNano
	{
	public:
		VgNanoBgfx(cstring resource_path);

		// init
		virtual void setup_context() final;
		virtual void release_context() final;
	};
}
