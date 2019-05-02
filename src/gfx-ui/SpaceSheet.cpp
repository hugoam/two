//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.gfx.ui;
#else
#include <geom/Intersect.h>
#include <geom/Shapes.h>
#include <geom/Shape/Quad.h>
#include <ctx/InputDevice.h>
#include <ui/Frame/Layer.h>
#include <gfx/Texture.h>
#include <gfx/Material.h>
#include <gfx/Mesh.h>
#include <gfx/Model.h>
#include <gfx/Node3.h>
#include <gfx/Item.h>
#include <gfx/Draw.h>
#include <gfx/Asset.h>
#include <gfx/GfxSystem.h>
#include <gfx-ui/SpaceSheet.h>
#include <gfx-ui/Viewer3.h>
#endif

#include <cstdio>

namespace two
{
	class SpaceQuad
	{
	public:
		SpaceQuad(Viewport& viewport, const uvec2& size, float scale);

		Texture m_texture;
		Material m_material;
		Model m_model;
		Node3 m_node;
		Item m_item;
	};

	SpaceQuad::SpaceQuad(Viewport& viewport, const uvec2& size, float scale)
		: m_texture("SpaceSheetTexture")
		, m_material("SpaceSheetMaterial")
		, m_model("SpaceSheet")
		, m_item(m_node, m_model, ItemFlag::Ui, &m_material)
	{
		m_texture.load_rgba(size, span<uint32_t>{});
		m_material.m_program = viewport.m_scene->m_gfx.programs().file("debug");
		m_material.m_solid.m_colour = &m_texture;

		//m_target = oconstruct<FrameBuffer>(*m_viewport.ui_window().m_renderer, as<Layer>(*m_frame), m_viewport.m_scene, m_viewport.m_camera, gfx, *m_texture);

		Symbol symbol = { Colour::White, Colour::None, true };
		Quad quad = { vec2(size) * scale };
		gen_model({ symbol, &quad, PLAIN }, m_model);
	}

	SpaceSheet::SpaceSheet(Widget& parent, SpaceViewport& viewport)
		: Ui(parent.ui_window()) // , { Input{ &parent }, &type<SpaceSheet>() }
		, m_viewer(viewport)
		, m_size_ratio(0.01f)
	{
		//m_propagate = parent.m_parent; // we skip the SpaceViewport
		//m_frame = oconstruct<Layer>(parent.m_frame.get(), viewer_styles().space_sheet, *this, SPACE_LAYER);
		//this->update_style();
	}

	SpaceSheet::~SpaceSheet()
	{}

	void SpaceSheet::next_frame()
	{
		//Ui::next_frame();

		//if(m_viewport.m_active)
		this->updateSize();

		static Clock clock;
		if(m_quad)
		{
			//quat rotation = { vec3(0.002f * float(clock.step()), 0.f, 0.f) };
			//m_quad->m_node.m_rotation = m_quad->m_node.m_rotation * rotation;
		}
	}

	void SpaceSheet::updateSize()
	{
		if(m_size == m_frame.m_size)
			return;

		m_size = m_frame.m_size;

		printf("SpaceSheet :: updateSize () %f, %f\n", m_size.x, m_size.y);

		if(m_size != vec2(0.f))
			m_quad = oconstruct<SpaceQuad>(m_viewer.m_viewport, uvec2(m_size), m_size_ratio);
	}

	void SpaceSheet::transformCoordinates(MouseEvent& event)
	{
		Ray ray = m_viewer.m_viewport.ray(event.m_relative);

		vec3 p0 = m_quad->m_node.position();
		vec3 p1 = p0 + m_quad->m_node.axis(X3);
		vec3 p2 = p0 + m_quad->m_node.axis(Y3);

		vec3 pos = plane_segment_intersection(p0, p1, p2, ray.m_start, ray.m_end);

		vec3 rel = vec3(0.f); UNUSED(pos); //inverse(m_quad->m_node.m_rotation) * pos - m_quad->m_node.m_position;

		event.m_pos.x = rel[0] / m_size_ratio + m_frame.m_size.x / 2.f;
		event.m_pos.y = -rel[1] / m_size_ratio + m_frame.m_size.y / 2.f;
	}

	void SpaceSheet::receive_event(InputEvent& inputEvent)
	{
		UNUSED(inputEvent);
		//inputEvent.dispatch(m_mouse, m_keyboard);
	}
}
