//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <gfx/Forward.h>
#include <gfx/Texture.h>

#include <bgfx/bgfx.h>

class MaskedOcclusionCulling;

namespace two
{
	export_ class refl_ TWO_GFX_EXPORT Culler
	{
	public:
		Culler(Viewport& viewport);
		~Culler();

		attr_ Viewport* m_viewport;

		MaskedOcclusionCulling* m_moc = nullptr;

		void render(Render& render);

		void begin(Render& render);
		void rasterize(Render& render);
		void cull(Render& render);
		void debug(Render& render);

		vector<float> m_depth_data;
		Texture m_depth_texture;
	};
}
