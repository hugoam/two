//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#include <math/Axis.h>
#include <infra/NonCopy.h>
#include <infra/Global.h>
#include <type/Dispatch.h>
#include <math/Vec.h>
#include <geom/Shape.h>
#include <geom/Symbol.h>
#include <ui/Controller/Controller.h>
#endif
#include <tool/Forward.h>
#include <tool/Action.h>
#include <gfx-ui/Viewer.h>

namespace mud
{
	export_ struct refl_ MUD_TOOL_EXPORT ToolContext
	{
		Camera* m_camera = nullptr;
		Plane* m_work_plane = nullptr;
		ActionStack* m_action_stack = nullptr;
		vector<Ref>* m_selection = nullptr;
	};

	export_ class refl_ MUD_TOOL_EXPORT ToolOption
	{
	public:
		ToolOption(cstring name) : m_name(name) {}
		virtual ~ToolOption() {}

		/*attr_*/ string m_name;

		virtual void activate() = 0;
		virtual void deactivate() = 0;
	};

	typedef vector<object_ptr<ToolOption>> OptionVector;

	export_ enum class refl_ ToolState : unsigned int
	{
		Inactive = 0,
		Done = 1,
		Active = 2
	};

	export_ class refl_ MUD_TOOL_EXPORT Tool : public NonCopy
	{
	public:
		using Callback = void(*)(Tool&);

	public:
		Tool(ToolContext& context, cstring name, Type& type);
		virtual ~Tool() {}

		attr_ Type& m_type;
		attr_ ToolContext& m_context;
		attr_ string m_name;
		attr_ ToolState m_state;

		OptionVector m_options;

		bool active() { return m_state == ToolState::Active; }

		void add_option(object_ptr<ToolOption> option);

		virtual void activate();
		virtual void deactivate();

		void commit(object_ptr<EditorAction> action);

		virtual bool enabled(const vector<Ref>& selection) { UNUSED(selection); return true; }

	protected:
		Callback m_callback;
	};

	export_ class refl_ MUD_TOOL_EXPORT ViewportTool : public Tool //, public ViewerController
	{
	public:
		ViewportTool(ToolContext& context, cstring name, Type& type);

		vector<Transform*> gather_transforms(const vector<Ref>& selection);

		vec3 m_symbol_position;
	};

	export_ class refl_ MUD_TOOL_EXPORT SpatialTool : public ViewportTool
	{
	public:
		SpatialTool(ToolContext& context, cstring name, Type& type);

		virtual void paint(Gnode& parent) = 0;

		virtual void process(Viewer& viewer, const vector<Ref>& selection) = 0;
	};

	export_ class refl_ MUD_TOOL_EXPORT Gizmo
	{
	public:
		virtual ~Gizmo() {}
		virtual Item* draw_handle(Gnode&) = 0;
		virtual void draw_gizmo(Gnode&, bool) = 0;
		virtual vec3 grab_point(Viewer&, const vec2&) = 0;

		Item* m_handle = nullptr;
		bool m_highlighted = false;
	};

	MUD_TOOL_EXPORT Colour gizmo_colour(float hue, bool active);
	MUD_TOOL_EXPORT vec3 gizmo_grab_linear(Viewer& viewer, const Transform& space, Axis axis);
	MUD_TOOL_EXPORT vec3 gizmo_grab_planar(Viewer& viewer, const Transform& space, Axis normal);

	export_ class refl_ MUD_TOOL_EXPORT TransformAction : public EditorAction
	{
	public:
		TransformAction(array<Transform*> targets);

		virtual void apply() final;
		virtual void undo() final;

		virtual void update(const vec3& start, const vec3& end) = 0;

		virtual void apply(Transform& transform) = 0;
		virtual void undo(Transform& transform) = 0;

	public:
		vector<Transform*> m_targets;
	};

	export_ class refl_ MUD_TOOL_EXPORT TransformTool : public SpatialTool
	{
	public:
		TransformTool(ToolContext& context, cstring name, Type& type);
		~TransformTool();
		
		Gizmo& gizmo(Item& item);

		void refresh();

		virtual void paint(Gnode& parent) override;

		virtual void process(Viewer& viewer, const vector<Ref>& selection) override;

		virtual bool enabled(const vector<Ref>& selection) override;

		virtual object_ptr<TransformAction> create_action(array<Transform*> targets) = 0;
		virtual bool test_target(Ref target) { UNUSED(target); return true; }

	public:
		vector<unique_ptr<Gizmo>> m_gizmos;
		Gizmo* m_current = nullptr;
		Gizmo* m_dragging = nullptr;

		Transform m_transform = {};
		vec2 m_drag_start;
		vec3 m_grab_start;
		vec3 m_grab_end;

		object_ptr<TransformAction> m_action;
	};

	export_ class refl_ MUD_TOOL_EXPORT TransformGizmo : public Gizmo
	{
	public:
		TransformGizmo(TransformTool& tool, Axis axis = Axis::X, float hue = 0.f) : m_tool(tool), m_axis(axis), m_hue(hue) {}

		TransformTool& m_tool;
		Axis m_axis;
		float m_hue;
	};
}
