//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
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
#include <gfx/Widget/Viewer.h>

namespace mud
{
	struct _refl_ MUD_EDIT_EXPORT ToolContext
	{
		Camera* m_camera = nullptr;
		Plane* m_work_plane = nullptr;
		ActionStack* m_action_stack = nullptr;
	};

	class _refl_ MUD_EDIT_EXPORT ToolOption
	{
	public:
		ToolOption(cstring name) : m_name(name) {}
		virtual ~ToolOption() {}

		/*_attr_*/ strung m_name;

		virtual void activate() = 0;
		virtual void deactivate() = 0;
	};

	typedef std::vector<object_ptr<ToolOption>> OptionVector;

	enum class _refl_ ToolState : unsigned int
	{
		INACTIVE = 0,
		DONE = 1,
		ACTIVE = 2
	};

	class _refl_ MUD_EDIT_EXPORT Tool : public NonCopy
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

		bool active() { return m_state == ToolState::ACTIVE; }

		void add_option(object_ptr<ToolOption> option);

		bool activate();
		void deactivate();

		void commit(object_ptr<EditorAction> action);

		virtual ToolState start() { return ToolState::ACTIVE; }
		virtual void stop() {}

		virtual bool enabled(const std::vector<Ref>& selection) { UNUSED(selection); return true; }

	protected:
		Callback m_callback;
	};

	class _refl_ MUD_EDIT_EXPORT ViewportTool : public Tool //, public ViewerController
	{
	public:
		ViewportTool(ToolContext& context, cstring name, Type& type);

		bool activate(Viewer& viewer);

		virtual ToolState start(Viewer& viewer);
		virtual void stop();

		vec3 m_symbol_position;
	};

	class _refl_ MUD_EDIT_EXPORT SpatialTool : public ViewportTool
	{
	public:
		SpatialTool(ToolContext& context, cstring name, Type& type);

		virtual void paint(Gnode& parent) = 0;

		virtual void process(Viewer& viewer, const std::vector<Ref>& selection) = 0;
	};

	struct _refl_ MUD_EDIT_EXPORT Gizmo
	{
		Symbol m_symbol;
		ShapeVar m_shape;
		Item* m_item;
		bool m_highlighted;
		std::function<vec3(Viewer&)> m_grab_point;
	};

	class _refl_ MUD_EDIT_EXPORT TransformAction : public EditorAction
	{
	public:
		TransformAction(const std::vector<Transform*>& targets) : EditorAction(), m_targets(targets) {}

		virtual void apply() final;
		virtual void undo() final;

		virtual void update(const vec3& start, const vec3& end) = 0;

		virtual void apply(Transform& transform) = 0;
		virtual void undo(Transform& transform) = 0;

	public:
		std::vector<Transform*> m_targets;

	};

	class _refl_ MUD_EDIT_EXPORT TransformTool : public ViewportTool
	{
	public:
		TransformTool(ToolContext& context, cstring name, Type& type);
		~TransformTool();
		
		Gizmo& gizmo(Item& item);

		void refresh();

		virtual void process(Viewer& viewer, const std::vector<Ref>& selection);

		virtual bool enabled(const std::vector<Ref>& selection);

		virtual void paint(Gnode& parent);

		virtual object_ptr<TransformAction> create_action(const std::vector<Transform*>& targets) = 0;
		virtual bool test_target(Ref target) { UNUSED(target); return true; }

	protected:
		std::vector<Gizmo> m_gizmos;
		Gizmo* m_current = nullptr;
		Gizmo* m_dragging = nullptr;

		vec3 m_center;
		vec3 m_grab_start;
		vec3 m_grab_end;

		object_ptr<TransformAction> m_action;
	};
}
