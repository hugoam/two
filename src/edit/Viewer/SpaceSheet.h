//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <ui/Structs/RootSheet.h>
#endif
#include <edit/Forward.h>

namespace mud
{
	class SpaceQuad;

	export_ class refl_ MUD_EDIT_EXPORT SpaceSheet : public RootSheet
	{
	public:
		SpaceSheet(Widget& parent, SpaceViewport& viewport);
		~SpaceSheet();

		void next_frame();

		void updateSize();

		void transformCoordinates(MouseEvent& mouse_event);

		virtual void receiveEvent(InputEvent& inputEvent);

	private:
		SpaceViewport& m_viewport;
		//GfxDynamicTexture& m_texture;

		float m_width;
		float m_height;

		unique_ptr<SpaceQuad> m_quad;

		float m_size_ratio;
	};
}
