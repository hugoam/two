//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ui-nanovg-bgfx/VgNanoBgfx.h>

#include <nanovg_bgfx.h>

#define NANOVG_NULL_IMPLEMENTATION
#include <nanovg_null.h>

namespace mud
{
	VgNanoBgfx::VgNanoBgfx(cstring resource_path)
		: VgNano(resource_path)
	{}

	void VgNanoBgfx::setup_context()
	{
		if(m_null)
			m_ctx = nvgCreateNull();
		else
			m_ctx = nvgCreate(1, 250);

		if(m_ctx == nullptr)
		{
			printf("ERROR: Could not init nanovg.\n");
			return;
		}
	}

	void VgNanoBgfx::release_context()
	{
		if(m_null)
			nvgDeleteNull(m_ctx);
		else
			nvgDelete(m_ctx);

		m_ctx = nullptr;
	}
}
