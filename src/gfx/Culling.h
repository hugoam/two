//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <gfx/Forward.h>
#include <gfx/Texture.h>

#include <bgfx/bgfx.h>

class MaskedOcclusionCulling;

namespace mud
{
	export_ class refl_ MUD_GFX_EXPORT Culler
	{
	public:
		Culler(Viewport& viewport);
		~Culler();

		attr_ Viewport* m_viewport;

		MaskedOcclusionCulling* m_moc = nullptr;

		void render(Render& render);

		void begin(Viewport& viewport);
		void rasterize(Render& render);
		void cull(Render& render);
		void debug(Render& render);

		vector<float> m_depth_data;
		Texture m_depth_texture;
	};
}
