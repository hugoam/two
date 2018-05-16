//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Reflect/Member.h>
#include <gfx/Generated/Types.h>
#include <ui/Structs/RootSheet.h>

#include <gfx/Texture.h>
#include <gfx/Material.h>
#include <gfx/Mesh.h>
#include <gfx/Node3.h>
#include <gfx/Item.h>

namespace mud
{
	class _refl_ MUD_GFX_EXPORT SpaceQuad
	{
	public:
		SpaceQuad(Viewport& viewport, size_t width, size_t height, float scale);

		Texture m_texture;
		Material m_material;
		Model m_model;
		Node3 m_node;
		Item m_item;
	};

	class _refl_ MUD_GFX_EXPORT SpaceSheet : public RootSheet
	{
	public:
		SpaceSheet(Widget& parent, SpaceViewport& viewport);

		void next_frame(size_t tick, size_t delta);

		void updateSize();

		void transformCoordinates(MouseEvent& mouse_event);

		virtual void receiveEvent(InputEvent& inputEvent);

	private:
		SpaceViewport& m_viewport;
		//GfxDynamicTexture& m_texture;

		float m_width;
		float m_height;

		object_ptr<SpaceQuad> m_quad;

		float m_size_ratio;
	};
}
