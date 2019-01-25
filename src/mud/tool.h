#pragma once

#include <mud/gfx.h>
#include <mud/geom.h>
#include <mud/ui.h>
#include <mud/srlz.h>
#include <mud/uio.h>
#include <mud/gfx.pbr.h>
#include <mud/tree.h>
#include <mud/lang.h>
#include <mud/gfx.edit.h>
#include <mud/math.h>
#include <mud/refl.h>
#include <mud/ctx.h>
#include <mud/gfx.ui.h>
#include <mud/infra.h>
#include <mud/type.h>





#ifndef MUD_TOOL_EXPORT
#define MUD_TOOL_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum class ToolState : unsigned int;
    
    
    class EditorAction;
    struct ToolContext;
    class ToolOption;
    class Tool;
    class ViewportTool;
    class SpatialTool;
    class Gizmo;
    class TransformAction;
    class TransformTool;
	class TransformGizmo;
    class ActionStack;
    class UndoTool;
    class RedoTool;
    class Brush;
    class PlaneSnapOption;
    class WorldSnapOption;
    class PlaceBrush;
    class CircleBrush;
    class ScriptedBrush;
    class TranslateAction;
    class TranslateTool;
    class RotateAction;
    class RotateTool;
    class ScaleAction;
    class ScaleTool;
    class CopyAction;
    class CopyTool;
    class ViewAction;
    class FrameViewTool;
    class ViewTool;
    struct ViewTools;
    class EditContext;
    class WorkPlaneAction;
    class WorkPlaneTool;
}

namespace mud
{
	export_ class refl_ MUD_TOOL_EXPORT EditorAction
	{
	public:
		virtual ~EditorAction() {}
		virtual void apply() = 0;
		virtual void undo() = 0;
	};
}


#ifndef MUD_MODULES
#endif


#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/string.h>
#endif

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

	typedef vector<object<ToolOption>> OptionVector;

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

		void add_option(object<ToolOption> option);

		virtual void activate();
		virtual void deactivate();

		void commit(object<EditorAction> action);

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

		virtual object<TransformAction> create_action(array<Transform*> targets) = 0;
		virtual bool test_target(Ref target) { UNUSED(target); return true; }

	public:
		vector<unique<Gizmo>> m_gizmos;
		Gizmo* m_current = nullptr;
		Gizmo* m_dragging = nullptr;

		Transform m_transform = {};
		vec2 m_drag_start;
		vec3 m_grab_start;
		vec3 m_grab_end;

		object<TransformAction> m_action;
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

namespace mud
{
	export_ class MUD_TOOL_EXPORT ActionStack : public NonCopy
	{
	public:
		ActionStack();

		void push(object<EditorAction> action);

		void redo();
		void undo();

	private:
		vector<object<EditorAction>> m_done;
		vector<object<EditorAction>> m_undone;
	};

	export_ class refl_ MUD_TOOL_EXPORT UndoTool : public Tool
	{
	public:
		UndoTool(ToolContext& context);

		virtual void activate() final;
	};

	export_ class refl_ MUD_TOOL_EXPORT RedoTool : public Tool
	{
	public:
		RedoTool(ToolContext& context);

		virtual void activate() final;
	};
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ class refl_ MUD_TOOL_EXPORT Brush : public SpatialTool
	{
	public:
		Brush(ToolContext& context, cstring name, Type& type);

		bool m_world_snap;
		Plane m_work_plane;

		virtual void process(Viewer& viewer, const vector<Ref>& selection);

		virtual void begin(const vec3& position) { UNUSED(position); }
		virtual void update(const vec3& position) = 0;
		virtual void end() {}

	protected:
		vec3 raycast_target(Viewer& viewer, MouseEvent& mouse_event);

	protected:
		vec3 m_position;
	};

	export_ class refl_ MUD_TOOL_EXPORT PlaneSnapOption : public ToolOption
	{
	public:
		PlaneSnapOption(Brush& tool);

		void activate();
		void deactivate();

	private:
		Brush& m_tool;
	};

	export_ class refl_ MUD_TOOL_EXPORT WorldSnapOption : public ToolOption
	{
	public:
		WorldSnapOption(Brush& tool);

		void activate();
		void deactivate();

	private:
		Brush& m_tool;
	};

	export_ class refl_ MUD_TOOL_EXPORT PlaceBrush : public Brush
	{
	public:
		constr_ PlaceBrush(ToolContext& context);

		attr_ Creator m_creator;

		virtual void activate();
		virtual void update(const vec3& position);
		virtual void paint(Gnode& parent);
	};

	export_ class refl_ MUD_TOOL_EXPORT CircleBrush : public Brush
	{
	public:
		constr_ CircleBrush(ToolContext& context);

		attr_ Creator m_creator;
		attr_ float m_radius;
		attr_ float m_maxSpotRadius;

		virtual void activate();
		virtual void update(const vec3& position);
		virtual void paint(Gnode& parent);

		void clearStroke(const vec3& center);

		bool filter(const vec3& center, vec3& position);

	protected:
		vector<Ref> m_stroke;

		object<Poisson> m_distribution;

		bool m_accumulate;
	};


	export_ class refl_ MUD_TOOL_EXPORT ScriptedBrush : public Brush
	{
	public:
		constr_ ScriptedBrush(ToolContext& context, Script& script);

		attr_ Call m_call;
		
		virtual void activate();
		virtual void update(const vec3& position);
		virtual void paint(Gnode& parent);

	protected:
		Script& m_script;
	};
}


#ifndef MUD_MODULES
#endif




#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	export_ class refl_ MUD_TOOL_EXPORT TranslateAction : public TransformAction
	{
	public:
		TranslateAction(array<Transform*> targets);

		virtual void apply(Transform& transform) override;
		virtual void undo(Transform& transform) override;

		virtual void update(const vec3& start, const vec3& end) override;

	protected:
		vec3 m_translation;
	};

	export_ class refl_ MUD_TOOL_EXPORT TranslateTool final : public TransformTool
	{
	public:
		TranslateTool(ToolContext& context);

		unique<Gizmo> linear_gizmo(Axis axis, float hue);
		unique<Gizmo> planar_gizmo(Axis normal, float hue);

		virtual object<TransformAction> create_action(array<Transform*> transforms);
	};
}


#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	export_ class refl_ MUD_TOOL_EXPORT RotateAction : public TransformAction
	{
	public:
		RotateAction(array<Transform*> targets, const vec3& axis);

		virtual void apply(Transform& transform) final;
		virtual void undo(Transform& transform) final;

		virtual void update(const vec3& start, const vec3& end);

	private:
		vec3 m_axis;
		float m_angle;
	};

	export_ class refl_ MUD_TOOL_EXPORT RotateTool final : public TransformTool
	{
	public:
		RotateTool(ToolContext& context);

		unique<Gizmo> rotation_gizmo(Axis axis, float hue);

		virtual object<TransformAction> create_action(array<Transform*> transforms);
	};
}


#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	export_ class refl_ MUD_TOOL_EXPORT ScaleAction : public TransformAction
	{
	public:
		ScaleAction(array<Transform*> targets);

		virtual void apply(Transform& transform) override;
		virtual void undo(Transform& transform) override;

		virtual void update(const vec3& start, const vec3& end) override;

	protected:
		vec3 m_scale_offset;
	};

	export_ class refl_ MUD_TOOL_EXPORT ScaleTool final : public TransformTool
	{
	public:
		ScaleTool(ToolContext& context);

		unique<Gizmo> linear_gizmo(Axis axis, float hue);
		unique<Gizmo> planar_gizmo(Axis normal, float hue);
		unique<Gizmo> uniform_gizmo();

		virtual object<TransformAction> create_action(array<Transform*> transforms);
	};

}


#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	export_ class refl_ MUD_TOOL_EXPORT CopyAction : public TranslateAction
	{
	public:
		CopyAction(array<Transform*> targets);

		virtual void apply(Transform& transform) final;
		virtual void undo(Transform& transform) final;

	private:
		//vector<Transform*> m_copies;
		//Injector m_injector;
	};

	export_ class refl_ MUD_TOOL_EXPORT CopyTool final : public TransformTool
	{
	public:
		CopyTool(ToolContext& context);

		void begin(const vec3& position);
		void update(const vec3& position);
		void end();

		virtual object<TransformAction> create_action(array<Transform*> targets) final;

	private:
		object<CopyAction> m_action;
	};
}


#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ class refl_ ViewAction : public EditorAction
	{
	public:
		ViewAction(Camera& camera, const vec3& eye, const vec3& target);

		virtual void apply() final;
		virtual void undo() final;

		enum State
		{
			START = 0,
			End = 1
		};

	private:
		Camera& m_camera;

		vec3 m_eye[2];
		vec3 m_target[2];
	};

	export_ class refl_ FrameViewTool final : public ViewportTool
	{
	public:
		FrameViewTool(ToolContext& context);

		virtual void activate() final;
	};

	export_ class refl_ ViewTool final : public ViewportTool
	{
	public:
		ViewTool(ToolContext& context, cstring name, const vec3& offset);

		ViewTool(const ViewTool& other) = default;
		ViewTool& operator=(const ViewTool& other) = default;

		virtual void activate() final;

		vec3 m_offset;
	};

	struct ViewTools
	{
		ViewTools(ToolContext& context) : m_context(context) {}
		ToolContext& m_context;
		ViewTool m_top		= { m_context, "Top View",	   Y3 };
		ViewTool m_bottom	= { m_context, "Bottom View", -Y3 };
		ViewTool m_front	= { m_context, "Front View",  -Z3 };
		ViewTool m_back		= { m_context, "Back View",	   Z3 };
		ViewTool m_left		= { m_context, "Left View",	   X3 };
		ViewTool m_right	= { m_context, "Right View",  -X3 };
	};
}



namespace mud
{
	export_ class refl_ MUD_TOOL_EXPORT EditContext : public NonCopy
    {
    public:
		EditContext(GfxSystem& gfx_system);
        ~EditContext();

		void set_tool(ViewportTool& tool, Viewer& viewer);

		GfxSystem& m_gfx_system;

		vector<Ref> m_selection;

		ActionStack m_action_stack;
		ToolContext m_tool_context;

		attr_ UndoTool m_undo_tool;
		attr_ RedoTool m_redo_tool;

		attr_ Plane m_work_plane;
		attr_ TranslateTool m_translate_tool;
		attr_ RotateTool m_rotate_tool;
		attr_ ScaleTool m_scale_tool;

		ViewTools m_view_tools;

		//PlaceBrush m_place_brush;

		attr_ Viewer* m_viewer = nullptr;
		attr_ ViewportTool* m_tool = nullptr;
		attr_ SpatialTool* m_spatial_tool = nullptr;
		attr_ Brush* m_brush = nullptr;

		vector<unique<Brush>> m_custom_brushes;

		ScriptEditor m_script_editor;

		Docksystem m_docksystem;
		Dockbar* m_dockbar = nullptr;
		Widget* m_screen = nullptr;
    };

	MUD_TOOL_EXPORT void brush_preview(Widget& parent, Brush& brush);
	MUD_TOOL_EXPORT void brush_options(Widget& parent, Brush& brush);
	MUD_TOOL_EXPORT void current_brush_edit(Widget& parent, EditContext& context);

	MUD_TOOL_EXPORT void object_editor(Widget& parent, const vector<Ref>& selection);

	MUD_TOOL_EXPORT void tools_transform(Widget& toolbar, EditContext& context);
	MUD_TOOL_EXPORT void edit_transform(Widget& parent, EditContext& context);
	MUD_TOOL_EXPORT void edit_tools(Widget& screen, Docker& docker, EditContext& context);
	MUD_TOOL_EXPORT void edit_tools(Widget& screen, EditContext& context);
	MUD_TOOL_EXPORT void edit_context(Widget& parent, EditContext& context, bool tools = false);
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <cstdint>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ToolState>();
    
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::EditContext>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::EditorAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::Gizmo>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::Tool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ToolContext>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ToolOption>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::RedoTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ViewportTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::SpatialTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::Brush>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::CircleBrush>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::PlaceBrush>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::PlaneSnapOption>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ScriptedBrush>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::TransformAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::RotateAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::TransformGizmo>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::TransformTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::RotateTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ScaleAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ScaleTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::TranslateAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::CopyAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::CopyTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::FrameViewTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::TranslateTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::UndoTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ViewAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::ViewTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::WorkPlaneAction>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::WorkPlaneTool>();
    export_ template <> MUD_TOOL_EXPORT Type& type<mud::WorldSnapOption>();
    
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::EditContext*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::EditorAction*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::Gizmo*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::Tool*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::ToolContext*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::ToolOption*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::RedoTool*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::ViewportTool*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::SpatialTool*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::Brush*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::CircleBrush*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::PlaceBrush*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::PlaneSnapOption*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::ScriptedBrush*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::TransformAction*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::RotateAction*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::TransformGizmo*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::TransformTool*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::RotateTool*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::ScaleAction*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::ScaleTool*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::TranslateAction*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::CopyAction*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::CopyTool*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::FrameViewTool*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::TranslateTool*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::UndoTool*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::ViewAction*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::ViewTool*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::WorkPlaneAction*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::WorkPlaneTool*>>;
    export_ template struct MUD_TOOL_EXPORT Typed<vector<mud::WorldSnapOption*>>;
}



#ifndef MUD_CPP_20
#include <stl/vector.h>
#endif

namespace mud
{
	export_ class refl_ WorkPlaneAction : public EditorAction
	{
	public:
		WorkPlaneAction(Plane& workPlane, const Plane& plane);

		virtual void apply() final;
		virtual void undo() final;

	private:
		Plane& m_workPlane;
		Plane m_startPlane;
		Plane m_endPlane;
	};

	export_ class refl_ WorkPlaneTool final : public Tool
	{
	public:
		WorkPlaneTool(ToolContext& context, cstring name, const Plane& plane);

		virtual void activate() final;

	private:
		object<WorkPlaneAction> m_action;
		Plane m_plane;
	};

	inline unique<WorkPlaneTool> xy_work_plane_tool(ToolContext& context) { return make_unique<WorkPlaneTool>(context, "XY Work Plane", Plane{ Zero3, X3, Y3 }); }
	inline unique<WorkPlaneTool> yz_work_plane_tool(ToolContext& context) { return make_unique<WorkPlaneTool>(context, "YZ Work Plane", Plane{ Zero3, Y3, Z3 }); }
	inline unique<WorkPlaneTool> xz_work_plane_tool(ToolContext& context) { return make_unique<WorkPlaneTool>(context, "XZ Work Plane", Plane{ Zero3, X3, Z3 }); }
}

