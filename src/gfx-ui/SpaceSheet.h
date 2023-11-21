//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx-ui/Forward.h>

namespace two
{
	class SpaceQuad;

	export_ class refl_ TWO_GFX_UI_EXPORT SpaceSheet : public Ui
	{
	public:
		SpaceSheet(Widget& parent, SpaceViewport& viewport);
		~SpaceSheet();

		void next_frame();

		void updateSize();

		void transformCoordinates(MouseEvent& mouse_event);

		virtual void receive_event(InputEvent& inputEvent);

	private:
		SpaceViewport& m_viewer;
		//GfxDynamicTexture& m_texture;

		vec2 m_size;

		unique<SpaceQuad> m_quad;

		float m_size_ratio;
	};
}
