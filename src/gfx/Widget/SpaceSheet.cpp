//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <gfx/Widget/SpaceSheet.h>
#include <gfx/Widget/SpaceViewer.h>

#include <geom/Intersect.h>

#include <ctx/InputDevice.h>
#include <ui/Frame/Layer.h>

#include <geom/Shape/Quad.h>

#include <gfx/Draw.h>

namespace mud
{
	SpaceQuad::SpaceQuad(Viewport& viewport, size_t width, size_t height, float scale)
		: m_texture(viewport.m_scene->m_gfx_system, "SpaceSheetTexture", uint16_t(width), uint16_t(height), {})
		, m_material("SpaceSheetMaterial", "debug")
		, m_model(viewport.m_scene->m_gfx_system, "SpaceSheet")
		, m_node(viewport.m_scene, this)
		, m_item(m_node, m_model, ITEM_UI, &m_material)
	{
		m_material.m_unshaded_block.m_enabled = true;
		m_material.m_unshaded_block.m_colour.m_texture = &m_texture;

		//m_target = make_object<FrameBuffer>(*m_viewport.ui_window().m_renderer, as<Layer>(*m_frame), m_viewport.m_scene, m_viewport.m_camera, gfx_system, *m_texture);

		Symbol symbol = { Colour::None, Colour::White, true };
		Quad quad = { vec2 { width * scale, height * scale } };
		draw_model(ProcShape{ symbol, &quad, PLAIN, Zero3 }, m_model);
	}

	SpaceSheet::SpaceSheet(Widget& parent, SpaceViewport& viewport)
		: RootSheet(parent.ui_window()) // , { Input{ &parent }, &type<SpaceSheet>() }
		, m_viewport(viewport)
		, m_size_ratio(0.01f)
	{
		//m_propagate = parent.m_parent; // we skip the SpaceViewport
		//m_frame = make_object<Layer>(parent.m_frame.get(), viewer_styles().space_sheet, *this, SPACE_LAYER);
		//this->update_style();
	}

	void SpaceSheet::next_frame(size_t tick, size_t delta)
	{
		RootSheet::next_frame(tick, delta);

		//if(m_viewport.m_active)
		this->updateSize();

		if(m_quad)
		{
			quat rotation = { vec3{ 0.002f * float(delta), 0.f, 0.f } };
			m_quad->m_node.m_rotation = m_quad->m_node.m_rotation * rotation;
		}

	}

	void SpaceSheet::updateSize()
	{
		if(m_width == m_frame.m_size.x && m_height == m_frame.m_size.y)
			return;

		m_width = m_frame.m_size.x;
		m_height = m_frame.m_size.y;

		printf("SpaceSheet :: updateSize () %f, %f\n", m_width, m_height);

		if(m_width > 0.f && m_height > 0.f)
			m_quad = make_object<SpaceQuad>(m_viewport.m_viewport, size_t(m_width), size_t(m_height), m_size_ratio);
	}

	void SpaceSheet::transformCoordinates(MouseEvent& mouse_event)
	{
		Ray ray = m_viewport.m_viewport.ray(mouse_event.m_relative);

		vec3 p0 = m_quad->m_node.m_position;
		vec3 p1 = rotate(m_quad->m_node.m_rotation, X3);
		vec3 p2 = rotate(m_quad->m_node.m_rotation, Y3);

		vec3 pos = plane_segment_intersection(p0, p1, p2, ray.m_start, ray.m_end);

		vec3 rel = inverse(m_quad->m_node.m_rotation) * pos - m_quad->m_node.m_position;

		mouse_event.m_pos.x = rel[0] / m_size_ratio + m_frame.m_size.x / 2.f;
		mouse_event.m_pos.y = -rel[1] / m_size_ratio + m_frame.m_size.y / 2.f;
	}

	void SpaceSheet::receiveEvent(InputEvent& inputEvent)
	{
		inputEvent.dispatch(m_mouse, m_keyboard);
	}
}
