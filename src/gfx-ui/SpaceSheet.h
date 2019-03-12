//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <ui/UiRoot.h>
#endif
#include <gfx-ui/Forward.h>

namespace mud
{
	class SpaceQuad;

	export_ class refl_ MUD_GFX_UI_EXPORT SpaceSheet : public Ui
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
