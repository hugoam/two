//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <edit/Generated/Forward.h>
#include <ui/Structs/RootSheet.h>

namespace mud
{
	class SpaceQuad;

	export_ class _refl_ MUD_GFX_EXPORT SpaceSheet : public RootSheet
	{
	public:
		SpaceSheet(Widget& parent, SpaceViewport& viewport);
		~SpaceSheet();

		void next_frame(size_t tick, size_t delta);

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
