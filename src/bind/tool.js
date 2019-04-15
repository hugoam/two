// EditContext
function EditContext() { throw "cannot construct a EditContext, no constructor in IDL" }
EditContext.prototype = Object.create(WrapperObject.prototype);
EditContext.prototype.constructor = EditContext;
EditContext.prototype.__class = EditContext;
EditContext.__cache = {};
Module['EditContext'] = EditContext;
Object.defineProperty(EditContext.prototype, "undo_tool", {
    get: function() {
        return wrapPointer(_mud_EditContext__get_undo_tool(this.__ptr), UndoTool);
    }});
Object.defineProperty(EditContext.prototype, "redo_tool", {
    get: function() {
        return wrapPointer(_mud_EditContext__get_redo_tool(this.__ptr), RedoTool);
    }});
Object.defineProperty(EditContext.prototype, "work_plane", {
    get: function() {
        return wrapPointer(_mud_EditContext__get_work_plane(this.__ptr), Plane);
    },
    set: function(value) {
        _mud_EditContext__set_work_plane(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(EditContext.prototype, "translate_tool", {
    get: function() {
        return wrapPointer(_mud_EditContext__get_translate_tool(this.__ptr), TranslateTool);
    }});
Object.defineProperty(EditContext.prototype, "rotate_tool", {
    get: function() {
        return wrapPointer(_mud_EditContext__get_rotate_tool(this.__ptr), RotateTool);
    }});
Object.defineProperty(EditContext.prototype, "scale_tool", {
    get: function() {
        return wrapPointer(_mud_EditContext__get_scale_tool(this.__ptr), ScaleTool);
    }});
Object.defineProperty(EditContext.prototype, "viewer", {
    get: function() {
        return wrapPointer(_mud_EditContext__get_viewer(this.__ptr), Viewer);
    },
    set: function(value) {
        _mud_EditContext__set_viewer(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(EditContext.prototype, "tool", {
    get: function() {
        return wrapPointer(_mud_EditContext__get_tool(this.__ptr), ViewportTool);
    },
    set: function(value) {
        _mud_EditContext__set_tool(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(EditContext.prototype, "spatial_tool", {
    get: function() {
        return wrapPointer(_mud_EditContext__get_spatial_tool(this.__ptr), SpatialTool);
    },
    set: function(value) {
        _mud_EditContext__set_spatial_tool(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(EditContext.prototype, "brush", {
    get: function() {
        return wrapPointer(_mud_EditContext__get_brush(this.__ptr), Brush);
    },
    set: function(value) {
        _mud_EditContext__set_brush(this.__ptr, value.__ptr);
    }
});
EditContext.prototype["__destroy"] = EditContext.prototype.__destroy = function() {
    _mud_EditContext__destroy(this.__ptr);
};
// EditorAction
function EditorAction() { throw "cannot construct a EditorAction, no constructor in IDL" }
EditorAction.prototype = Object.create(WrapperObject.prototype);
EditorAction.prototype.constructor = EditorAction;
EditorAction.prototype.__class = EditorAction;
EditorAction.__cache = {};
Module['EditorAction'] = EditorAction;
EditorAction.prototype["__destroy"] = EditorAction.prototype.__destroy = function() {
    _mud_EditorAction__destroy(this.__ptr);
};
// Gizmo
function Gizmo() { throw "cannot construct a Gizmo, no constructor in IDL" }
Gizmo.prototype = Object.create(WrapperObject.prototype);
Gizmo.prototype.constructor = Gizmo;
Gizmo.prototype.__class = Gizmo;
Gizmo.__cache = {};
Module['Gizmo'] = Gizmo;
Gizmo.prototype["__destroy"] = Gizmo.prototype.__destroy = function() {
    _mud_Gizmo__destroy(this.__ptr);
};
// Selection
function Selection() {
    
    this.__ptr = _mud_Selection__construct_0(); getCache(Selection)[this.__ptr] = this;
};
Selection.prototype = Object.create(WrapperObject.prototype);
Selection.prototype.constructor = Selection;
Selection.prototype.__class = Selection;
Selection.__cache = {};
Module['Selection'] = Selection;
Selection.prototype["__destroy"] = Selection.prototype.__destroy = function() {
    _mud_Selection__destroy(this.__ptr);
};
// Tool
function Tool() { throw "cannot construct a Tool, no constructor in IDL" }
Tool.prototype = Object.create(WrapperObject.prototype);
Tool.prototype.constructor = Tool;
Tool.prototype.__class = Tool;
Tool.__cache = {};
Module['Tool'] = Tool;
Object.defineProperty(Tool.prototype, "type", {
    get: function() {
        return wrapPointer(_mud_Tool__get_type(this.__ptr), Type);
    }});
Object.defineProperty(Tool.prototype, "context", {
    get: function() {
        return wrapPointer(_mud_Tool__get_context(this.__ptr), ToolContext);
    }});
Object.defineProperty(Tool.prototype, "name", {
    get: function() {
        return UTF8ToString(_mud_Tool__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Tool__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Tool.prototype, "state", {
    get: function() {
        return _mud_Tool__get_state(this.__ptr);
    },
    set: function(value) {
        _mud_Tool__set_state(this.__ptr, value);
    }
});
Tool.prototype["__destroy"] = Tool.prototype.__destroy = function() {
    _mud_Tool__destroy(this.__ptr);
};
// ToolContext
function ToolContext() {
    
    this.__ptr = _mud_ToolContext__construct_0(); getCache(ToolContext)[this.__ptr] = this;
};
ToolContext.prototype = Object.create(WrapperObject.prototype);
ToolContext.prototype.constructor = ToolContext;
ToolContext.prototype.__class = ToolContext;
ToolContext.__cache = {};
Module['ToolContext'] = ToolContext;
ToolContext.prototype["__destroy"] = ToolContext.prototype.__destroy = function() {
    _mud_ToolContext__destroy(this.__ptr);
};
// ToolOption
function ToolOption() { throw "cannot construct a ToolOption, no constructor in IDL" }
ToolOption.prototype = Object.create(WrapperObject.prototype);
ToolOption.prototype.constructor = ToolOption;
ToolOption.prototype.__class = ToolOption;
ToolOption.__cache = {};
Module['ToolOption'] = ToolOption;
ToolOption.prototype["__destroy"] = ToolOption.prototype.__destroy = function() {
    _mud_ToolOption__destroy(this.__ptr);
};
// Brush
function Brush() { throw "cannot construct a Brush, no constructor in IDL" }
Brush.prototype = Object.create(SpatialTool.prototype);
Brush.prototype.constructor = Brush;
Brush.prototype.__class = Brush;
Brush.__base = SpatialTool;
Brush.__cache = {};
Module['Brush'] = Brush;
Brush.prototype["__destroy"] = Brush.prototype.__destroy = function() {
    _mud_Brush__destroy(this.__ptr);
};
// CircleBrush
function CircleBrush(a0) {
    assert(checkClass(a0, ToolContext), '[ERROR] CircleBrush(0:context): expected ToolContext');
    this.__ptr = _mud_CircleBrush__construct_1(/*context*/a0.__ptr); getCache(CircleBrush)[this.__ptr] = this;
};
CircleBrush.prototype = Object.create(Brush.prototype);
CircleBrush.prototype.constructor = CircleBrush;
CircleBrush.prototype.__class = CircleBrush;
CircleBrush.__base = Brush;
CircleBrush.__cache = {};
Module['CircleBrush'] = CircleBrush;
Object.defineProperty(CircleBrush.prototype, "creator", {
    get: function() {
        return wrapPointer(_mud_CircleBrush__get_creator(this.__ptr), Creator);
    }});
Object.defineProperty(CircleBrush.prototype, "radius", {
    get: function() {
        return _mud_CircleBrush__get_radius(this.__ptr);
    },
    set: function(value) {
        _mud_CircleBrush__set_radius(this.__ptr, value);
    }
});
Object.defineProperty(CircleBrush.prototype, "maxSpotRadius", {
    get: function() {
        return _mud_CircleBrush__get_maxSpotRadius(this.__ptr);
    },
    set: function(value) {
        _mud_CircleBrush__set_maxSpotRadius(this.__ptr, value);
    }
});
CircleBrush.prototype["__destroy"] = CircleBrush.prototype.__destroy = function() {
    _mud_CircleBrush__destroy(this.__ptr);
};
// PlaceBrush
function PlaceBrush(a0) {
    assert(checkClass(a0, ToolContext), '[ERROR] PlaceBrush(0:context): expected ToolContext');
    this.__ptr = _mud_PlaceBrush__construct_1(/*context*/a0.__ptr); getCache(PlaceBrush)[this.__ptr] = this;
};
PlaceBrush.prototype = Object.create(Brush.prototype);
PlaceBrush.prototype.constructor = PlaceBrush;
PlaceBrush.prototype.__class = PlaceBrush;
PlaceBrush.__base = Brush;
PlaceBrush.__cache = {};
Module['PlaceBrush'] = PlaceBrush;
Object.defineProperty(PlaceBrush.prototype, "creator", {
    get: function() {
        return wrapPointer(_mud_PlaceBrush__get_creator(this.__ptr), Creator);
    }});
PlaceBrush.prototype["__destroy"] = PlaceBrush.prototype.__destroy = function() {
    _mud_PlaceBrush__destroy(this.__ptr);
};
// PlaneSnapOption
function PlaneSnapOption() { throw "cannot construct a PlaneSnapOption, no constructor in IDL" }
PlaneSnapOption.prototype = Object.create(ToolOption.prototype);
PlaneSnapOption.prototype.constructor = PlaneSnapOption;
PlaneSnapOption.prototype.__class = PlaneSnapOption;
PlaneSnapOption.__base = ToolOption;
PlaneSnapOption.__cache = {};
Module['PlaneSnapOption'] = PlaneSnapOption;
PlaneSnapOption.prototype["__destroy"] = PlaneSnapOption.prototype.__destroy = function() {
    _mud_PlaneSnapOption__destroy(this.__ptr);
};
// RedoTool
function RedoTool() { throw "cannot construct a RedoTool, no constructor in IDL" }
RedoTool.prototype = Object.create(Tool.prototype);
RedoTool.prototype.constructor = RedoTool;
RedoTool.prototype.__class = RedoTool;
RedoTool.__base = Tool;
RedoTool.__cache = {};
Module['RedoTool'] = RedoTool;
RedoTool.prototype["__destroy"] = RedoTool.prototype.__destroy = function() {
    _mud_RedoTool__destroy(this.__ptr);
};
// RotateAction
function RotateAction() { throw "cannot construct a RotateAction, no constructor in IDL" }
RotateAction.prototype = Object.create(TransformAction.prototype);
RotateAction.prototype.constructor = RotateAction;
RotateAction.prototype.__class = RotateAction;
RotateAction.__base = TransformAction;
RotateAction.__cache = {};
Module['RotateAction'] = RotateAction;
RotateAction.prototype["__destroy"] = RotateAction.prototype.__destroy = function() {
    _mud_RotateAction__destroy(this.__ptr);
};
// RotateTool
function RotateTool() { throw "cannot construct a RotateTool, no constructor in IDL" }
RotateTool.prototype = Object.create(TransformTool.prototype);
RotateTool.prototype.constructor = RotateTool;
RotateTool.prototype.__class = RotateTool;
RotateTool.__base = TransformTool;
RotateTool.__cache = {};
Module['RotateTool'] = RotateTool;
RotateTool.prototype["__destroy"] = RotateTool.prototype.__destroy = function() {
    _mud_RotateTool__destroy(this.__ptr);
};
// ScaleAction
function ScaleAction() { throw "cannot construct a ScaleAction, no constructor in IDL" }
ScaleAction.prototype = Object.create(TransformAction.prototype);
ScaleAction.prototype.constructor = ScaleAction;
ScaleAction.prototype.__class = ScaleAction;
ScaleAction.__base = TransformAction;
ScaleAction.__cache = {};
Module['ScaleAction'] = ScaleAction;
ScaleAction.prototype["__destroy"] = ScaleAction.prototype.__destroy = function() {
    _mud_ScaleAction__destroy(this.__ptr);
};
// ScaleTool
function ScaleTool() { throw "cannot construct a ScaleTool, no constructor in IDL" }
ScaleTool.prototype = Object.create(TransformTool.prototype);
ScaleTool.prototype.constructor = ScaleTool;
ScaleTool.prototype.__class = ScaleTool;
ScaleTool.__base = TransformTool;
ScaleTool.__cache = {};
Module['ScaleTool'] = ScaleTool;
ScaleTool.prototype["__destroy"] = ScaleTool.prototype.__destroy = function() {
    _mud_ScaleTool__destroy(this.__ptr);
};
// ScriptedBrush
function ScriptedBrush(a0, a1) {
    assert(checkClass(a0, ToolContext), '[ERROR] ScriptedBrush(0:context): expected ToolContext'); assert(checkClass(a1, Script), '[ERROR] ScriptedBrush(1:script): expected Script');
    this.__ptr = _mud_ScriptedBrush__construct_2(/*context*/a0.__ptr, /*script*/a1.__ptr); getCache(ScriptedBrush)[this.__ptr] = this;
};
ScriptedBrush.prototype = Object.create(Brush.prototype);
ScriptedBrush.prototype.constructor = ScriptedBrush;
ScriptedBrush.prototype.__class = ScriptedBrush;
ScriptedBrush.__base = Brush;
ScriptedBrush.__cache = {};
Module['ScriptedBrush'] = ScriptedBrush;
Object.defineProperty(ScriptedBrush.prototype, "call", {
    get: function() {
        return wrapPointer(_mud_ScriptedBrush__get_call(this.__ptr), Call);
    },
    set: function(value) {
        _mud_ScriptedBrush__set_call(this.__ptr, value.__ptr);
    }
});
ScriptedBrush.prototype["__destroy"] = ScriptedBrush.prototype.__destroy = function() {
    _mud_ScriptedBrush__destroy(this.__ptr);
};
// TranslateAction
function TranslateAction() { throw "cannot construct a TranslateAction, no constructor in IDL" }
TranslateAction.prototype = Object.create(TransformAction.prototype);
TranslateAction.prototype.constructor = TranslateAction;
TranslateAction.prototype.__class = TranslateAction;
TranslateAction.__base = TransformAction;
TranslateAction.__cache = {};
Module['TranslateAction'] = TranslateAction;
TranslateAction.prototype["__destroy"] = TranslateAction.prototype.__destroy = function() {
    _mud_TranslateAction__destroy(this.__ptr);
};
// CopyAction
function CopyAction() { throw "cannot construct a CopyAction, no constructor in IDL" }
CopyAction.prototype = Object.create(TranslateAction.prototype);
CopyAction.prototype.constructor = CopyAction;
CopyAction.prototype.__class = CopyAction;
CopyAction.__base = TranslateAction;
CopyAction.__cache = {};
Module['CopyAction'] = CopyAction;
CopyAction.prototype["__destroy"] = CopyAction.prototype.__destroy = function() {
    _mud_CopyAction__destroy(this.__ptr);
};
// CopyTool
function CopyTool() { throw "cannot construct a CopyTool, no constructor in IDL" }
CopyTool.prototype = Object.create(TransformTool.prototype);
CopyTool.prototype.constructor = CopyTool;
CopyTool.prototype.__class = CopyTool;
CopyTool.__base = TransformTool;
CopyTool.__cache = {};
Module['CopyTool'] = CopyTool;
CopyTool.prototype["__destroy"] = CopyTool.prototype.__destroy = function() {
    _mud_CopyTool__destroy(this.__ptr);
};
// FrameViewTool
function FrameViewTool() { throw "cannot construct a FrameViewTool, no constructor in IDL" }
FrameViewTool.prototype = Object.create(ViewportTool.prototype);
FrameViewTool.prototype.constructor = FrameViewTool;
FrameViewTool.prototype.__class = FrameViewTool;
FrameViewTool.__base = ViewportTool;
FrameViewTool.__cache = {};
Module['FrameViewTool'] = FrameViewTool;
FrameViewTool.prototype["__destroy"] = FrameViewTool.prototype.__destroy = function() {
    _mud_FrameViewTool__destroy(this.__ptr);
};
// TranslateTool
function TranslateTool() { throw "cannot construct a TranslateTool, no constructor in IDL" }
TranslateTool.prototype = Object.create(TransformTool.prototype);
TranslateTool.prototype.constructor = TranslateTool;
TranslateTool.prototype.__class = TranslateTool;
TranslateTool.__base = TransformTool;
TranslateTool.__cache = {};
Module['TranslateTool'] = TranslateTool;
TranslateTool.prototype["__destroy"] = TranslateTool.prototype.__destroy = function() {
    _mud_TranslateTool__destroy(this.__ptr);
};
// ViewAction
function ViewAction() { throw "cannot construct a ViewAction, no constructor in IDL" }
ViewAction.prototype = Object.create(EditorAction.prototype);
ViewAction.prototype.constructor = ViewAction;
ViewAction.prototype.__class = ViewAction;
ViewAction.__base = EditorAction;
ViewAction.__cache = {};
Module['ViewAction'] = ViewAction;
ViewAction.prototype["__destroy"] = ViewAction.prototype.__destroy = function() {
    _mud_ViewAction__destroy(this.__ptr);
};
// ViewTool
function ViewTool() { throw "cannot construct a ViewTool, no constructor in IDL" }
ViewTool.prototype = Object.create(ViewportTool.prototype);
ViewTool.prototype.constructor = ViewTool;
ViewTool.prototype.__class = ViewTool;
ViewTool.__base = ViewportTool;
ViewTool.__cache = {};
Module['ViewTool'] = ViewTool;
ViewTool.prototype["__destroy"] = ViewTool.prototype.__destroy = function() {
    _mud_ViewTool__destroy(this.__ptr);
};
// ViewportTool
function ViewportTool() { throw "cannot construct a ViewportTool, no constructor in IDL" }
ViewportTool.prototype = Object.create(Tool.prototype);
ViewportTool.prototype.constructor = ViewportTool;
ViewportTool.prototype.__class = ViewportTool;
ViewportTool.__base = Tool;
ViewportTool.__cache = {};
Module['ViewportTool'] = ViewportTool;
ViewportTool.prototype["__destroy"] = ViewportTool.prototype.__destroy = function() {
    _mud_ViewportTool__destroy(this.__ptr);
};
// SpatialTool
function SpatialTool() { throw "cannot construct a SpatialTool, no constructor in IDL" }
SpatialTool.prototype = Object.create(ViewportTool.prototype);
SpatialTool.prototype.constructor = SpatialTool;
SpatialTool.prototype.__class = SpatialTool;
SpatialTool.__base = ViewportTool;
SpatialTool.__cache = {};
Module['SpatialTool'] = SpatialTool;
SpatialTool.prototype["__destroy"] = SpatialTool.prototype.__destroy = function() {
    _mud_SpatialTool__destroy(this.__ptr);
};
// TransformAction
function TransformAction() { throw "cannot construct a TransformAction, no constructor in IDL" }
TransformAction.prototype = Object.create(EditorAction.prototype);
TransformAction.prototype.constructor = TransformAction;
TransformAction.prototype.__class = TransformAction;
TransformAction.__base = EditorAction;
TransformAction.__cache = {};
Module['TransformAction'] = TransformAction;
TransformAction.prototype["__destroy"] = TransformAction.prototype.__destroy = function() {
    _mud_TransformAction__destroy(this.__ptr);
};
// TransformGizmo
function TransformGizmo() { throw "cannot construct a TransformGizmo, no constructor in IDL" }
TransformGizmo.prototype = Object.create(Gizmo.prototype);
TransformGizmo.prototype.constructor = TransformGizmo;
TransformGizmo.prototype.__class = TransformGizmo;
TransformGizmo.__base = Gizmo;
TransformGizmo.__cache = {};
Module['TransformGizmo'] = TransformGizmo;
TransformGizmo.prototype["__destroy"] = TransformGizmo.prototype.__destroy = function() {
    _mud_TransformGizmo__destroy(this.__ptr);
};
// TransformTool
function TransformTool() { throw "cannot construct a TransformTool, no constructor in IDL" }
TransformTool.prototype = Object.create(SpatialTool.prototype);
TransformTool.prototype.constructor = TransformTool;
TransformTool.prototype.__class = TransformTool;
TransformTool.__base = SpatialTool;
TransformTool.__cache = {};
Module['TransformTool'] = TransformTool;
TransformTool.prototype["__destroy"] = TransformTool.prototype.__destroy = function() {
    _mud_TransformTool__destroy(this.__ptr);
};
// UndoTool
function UndoTool() { throw "cannot construct a UndoTool, no constructor in IDL" }
UndoTool.prototype = Object.create(Tool.prototype);
UndoTool.prototype.constructor = UndoTool;
UndoTool.prototype.__class = UndoTool;
UndoTool.__base = Tool;
UndoTool.__cache = {};
Module['UndoTool'] = UndoTool;
UndoTool.prototype["__destroy"] = UndoTool.prototype.__destroy = function() {
    _mud_UndoTool__destroy(this.__ptr);
};
// WorkPlaneAction
function WorkPlaneAction() { throw "cannot construct a WorkPlaneAction, no constructor in IDL" }
WorkPlaneAction.prototype = Object.create(EditorAction.prototype);
WorkPlaneAction.prototype.constructor = WorkPlaneAction;
WorkPlaneAction.prototype.__class = WorkPlaneAction;
WorkPlaneAction.__base = EditorAction;
WorkPlaneAction.__cache = {};
Module['WorkPlaneAction'] = WorkPlaneAction;
WorkPlaneAction.prototype["__destroy"] = WorkPlaneAction.prototype.__destroy = function() {
    _mud_WorkPlaneAction__destroy(this.__ptr);
};
// WorkPlaneTool
function WorkPlaneTool() { throw "cannot construct a WorkPlaneTool, no constructor in IDL" }
WorkPlaneTool.prototype = Object.create(Tool.prototype);
WorkPlaneTool.prototype.constructor = WorkPlaneTool;
WorkPlaneTool.prototype.__class = WorkPlaneTool;
WorkPlaneTool.__base = Tool;
WorkPlaneTool.__cache = {};
Module['WorkPlaneTool'] = WorkPlaneTool;
WorkPlaneTool.prototype["__destroy"] = WorkPlaneTool.prototype.__destroy = function() {
    _mud_WorkPlaneTool__destroy(this.__ptr);
};
// WorldSnapOption
function WorldSnapOption() { throw "cannot construct a WorldSnapOption, no constructor in IDL" }
WorldSnapOption.prototype = Object.create(ToolOption.prototype);
WorldSnapOption.prototype.constructor = WorldSnapOption;
WorldSnapOption.prototype.__class = WorldSnapOption;
WorldSnapOption.__base = ToolOption;
WorldSnapOption.__cache = {};
Module['WorldSnapOption'] = WorldSnapOption;
WorldSnapOption.prototype["__destroy"] = WorldSnapOption.prototype.__destroy = function() {
    _mud_WorldSnapOption__destroy(this.__ptr);
};

(function() {
    function setup() {
        EditContext.prototype.__type = _mud_EditContext__type();
        EditorAction.prototype.__type = _mud_EditorAction__type();
        Gizmo.prototype.__type = _mud_Gizmo__type();
        Selection.prototype.__type = _mud_Selection__type();
        Tool.prototype.__type = _mud_Tool__type();
        ToolContext.prototype.__type = _mud_ToolContext__type();
        ToolOption.prototype.__type = _mud_ToolOption__type();
        Brush.prototype.__type = _mud_Brush__type();
        CircleBrush.prototype.__type = _mud_CircleBrush__type();
        PlaceBrush.prototype.__type = _mud_PlaceBrush__type();
        PlaneSnapOption.prototype.__type = _mud_PlaneSnapOption__type();
        RedoTool.prototype.__type = _mud_RedoTool__type();
        RotateAction.prototype.__type = _mud_RotateAction__type();
        RotateTool.prototype.__type = _mud_RotateTool__type();
        ScaleAction.prototype.__type = _mud_ScaleAction__type();
        ScaleTool.prototype.__type = _mud_ScaleTool__type();
        ScriptedBrush.prototype.__type = _mud_ScriptedBrush__type();
        TranslateAction.prototype.__type = _mud_TranslateAction__type();
        CopyAction.prototype.__type = _mud_CopyAction__type();
        CopyTool.prototype.__type = _mud_CopyTool__type();
        FrameViewTool.prototype.__type = _mud_FrameViewTool__type();
        TranslateTool.prototype.__type = _mud_TranslateTool__type();
        ViewAction.prototype.__type = _mud_ViewAction__type();
        ViewTool.prototype.__type = _mud_ViewTool__type();
        ViewportTool.prototype.__type = _mud_ViewportTool__type();
        SpatialTool.prototype.__type = _mud_SpatialTool__type();
        TransformAction.prototype.__type = _mud_TransformAction__type();
        TransformGizmo.prototype.__type = _mud_TransformGizmo__type();
        TransformTool.prototype.__type = _mud_TransformTool__type();
        UndoTool.prototype.__type = _mud_UndoTool__type();
        WorkPlaneAction.prototype.__type = _mud_WorkPlaneAction__type();
        WorkPlaneTool.prototype.__type = _mud_WorkPlaneTool__type();
        WorldSnapOption.prototype.__type = _mud_WorldSnapOption__type();
        // ToolState
        Module['ToolState'] = Module['ToolState'] || {};
        Module['ToolState']['Inactive'] = _mud_ToolState_Inactive();
        Module['ToolState']['Done'] = _mud_ToolState_Done();
        Module['ToolState']['Active'] = _mud_ToolState_Active();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
