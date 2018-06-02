//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/NonCopy.h>
#include <obj/Strung.h>
#include <math/Vec.h>
#include <geom/Shape.h>
#include <geom/Symbol.h>
#include <ui/Controller/Controller.h>
#include <edit/Generated/Forward.h>
#include <edit/Action.h>
#include <edit/Viewer/Viewer.h>

#ifndef MUD_CPP_20
#include <functional>
#endif

namespace mud
{
	export_ struct _refl_ MUD_EDIT_EXPORT ToolContext
	{
		Camera* m_camera = nullptr;
		Plane* m_work_plane = nullptr;
		ActionStack* m_action_stack = nullptr;
	};

	export_ class _refl_ MUD_EDIT_EXPORT ToolOption
	{
	public:
		ToolOption(cstring name) : m_name(name) {}
		virtual ~ToolOption() {}

		/*_attr_*/ strung m_name;

		virtual void activate() = 0;
		virtual void deactivate() = 0;
	};

	typedef std::vector<object_ptr<ToolOption>> OptionVector;

	export_ enum class _refl_ ToolState : unsigned int
	{
		Inactive = 0,
		Done = 1,
		Active = 2
	};

	export_ class _refl_ MUD_EDIT_EXPORT Tool : public NonCopy
	{
	public:
		using Callback = std::function<void(Tool&)>;

	public:
		Tool(ToolContext& context, cstring name, Type& type);

		_attr_ Type& m_type;
		_attr_ ToolContext& m_context;
		_attr_ strung m_name;
		_attr_ ToolState m_state;

		OptionVector m_options;

		bool active() { return m_state == ToolState::Active; }

		void add_option(object_ptr<ToolOption> option);

		virtual void activate();
		virtual void deactivate();

		void commit(object_ptr<EditorAction> action);

		virtual bool enabled(const std::vector<Ref>& selection) { UNUSED(selection); return true; }

	protected:
		Callback m_callback;
	};

	export_ class _refl_ MUD_EDIT_EXPORT ViewportTool : public Tool //, public ViewerController
	{
	public:
		ViewportTool(ToolContext& context, cstring name, Type& type);

		vec3 m_symbol_position;
	};

	export_ class _refl_ MUD_EDIT_EXPORT SpatialTool : public ViewportTool
	{
	public:
		SpatialTool(ToolContext& context, cstring name, Type& type);

		virtual void paint(Gnode& parent) = 0;

		virtual void process(Viewer& viewer, const std::vector<Ref>& selection) = 0;
	};

	export_ struct _refl_ MUD_EDIT_EXPORT Gizmo
	{
		std::function<Item*(Gnode&)> m_draw_handle;
		std::function<void(Gnode&, bool)> m_draw_gizmo;
		Item* m_handle;
		bool m_highlighted;
		std::function<vec3(Viewer&, const vec2&)> m_grab_point;
	};

	MUD_EDIT_EXPORT Colour gizmo_colour(float hue, bool active);
	MUD_EDIT_EXPORT vec3 gizmo_grab_linear(Viewer& viewer, const Transform& space, Axis axis);
	MUD_EDIT_EXPORT vec3 gizmo_grab_planar(Viewer& viewer, const Transform& space, Axis normal);

	export_ class _refl_ MUD_EDIT_EXPORT TransformAction : public EditorAction
	{
	public:
		TransformAction(const std::vector<Transform*>& targets);

		virtual void apply() final;
		virtual void undo() final;

		virtual void update(const vec3& start, const vec3& end) = 0;

		virtual void apply(Transform& transform) = 0;
		virtual void undo(Transform& transform) = 0;

	public:
		std::vector<Transform*> m_targets;

	};

	export_ class _refl_ MUD_EDIT_EXPORT TransformTool : public SpatialTool
	{
	public:
		TransformTool(ToolContext& context, cstring name, Type& type);
		~TransformTool();
		
		Gizmo& gizmo(Item& item);

		void refresh();

		virtual void paint(Gnode& parent) override;

		virtual void process(Viewer& viewer, const std::vector<Ref>& selection) override;

		virtual bool enabled(const std::vector<Ref>& selection) override;

		virtual object_ptr<TransformAction> create_action(const std::vector<Transform*>& targets) = 0;
		virtual bool test_target(Ref target) { UNUSED(target); return true; }

	protected:
		std::vector<Gizmo> m_gizmos;
		Gizmo* m_current = nullptr;
		Gizmo* m_dragging = nullptr;

		Transform m_transform = {};
		vec2 m_drag_start;
		vec3 m_grab_start;
		vec3 m_grab_end;

		object_ptr<TransformAction> m_action;
	};
}
