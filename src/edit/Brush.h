//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <geom/Poisson.h>
#include <edit/Generated/Forward.h>
#include <edit/Tool.h>
#include <obj/Reflect/Injector.h>

namespace mud
{
	class _refl_ MUD_EDIT_EXPORT Brush : public SpatialTool
	{
	public:
		Brush(ToolContext& context, cstring name, Type& type);

		bool m_world_snap;
		Plane m_work_plane;

		virtual void process(Viewer& viewer, const std::vector<Ref>& selection);

		virtual void begin(const vec3& position) { UNUSED(position); }
		virtual void update(const vec3& position) = 0;
		virtual void end() {}

	protected:
		vec3 raycast_target(Viewer& viewer, MouseEvent& mouse_event);

	protected:
		vec3 m_position;
	};

	class _refl_ MUD_EDIT_EXPORT PlaneSnapOption : public ToolOption
	{
	public:
		PlaneSnapOption(Brush& tool);

		void activate();
		void deactivate();

	private:
		Brush& m_tool;
	};

	class _refl_ MUD_EDIT_EXPORT WorldSnapOption : public ToolOption
	{
	public:
		WorldSnapOption(Brush& tool);

		void activate();
		void deactivate();

	private:
		Brush& m_tool;
	};

	class _refl_ MUD_EDIT_EXPORT PlaceBrush : public Brush
	{
	public:
		PlaceBrush(ToolContext& context);

		_attr_ Creator m_creator;

		virtual void activate();
		virtual void update(const vec3& position);
		virtual void paint(Gnode& parent);
	};

	class _refl_ MUD_EDIT_EXPORT CircleBrush : public Brush
	{
	public:
		CircleBrush(ToolContext& context);

		_attr_ Creator m_creator;
		_attr_ _mut_ float m_radius;
		_attr_ _mut_ float m_maxSpotRadius;

		virtual void activate();
		virtual void update(const vec3& position);
		virtual void paint(Gnode& parent);

		void clearStroke(const vec3& center);

		bool filter(const vec3& center, vec3& position);

	protected:
		std::vector<Ref> m_stroke;

		object_ptr<Poisson> m_distribution;

		bool m_accumulate;
	};


	class _refl_ MUD_EDIT_EXPORT ScriptedBrush : public Brush
	{
	public:
		ScriptedBrush(ToolContext& context, VisualScript& script);

		_attr_ Call m_call;
		
		virtual void activate();
		virtual void update(const vec3& position);
		virtual void paint(Gnode& parent);

	protected:
		VisualScript& m_script;
	};
}
