// EditContext
function EditContext() { throw "cannot construct a EditContext, no constructor in IDL" }
EditContext.prototype = Object.create(WrapperObject.prototype);
EditContext.prototype.constructor = EditContext;
EditContext.prototype.__class__ = EditContext;
EditContext.__cache__ = {};
Module['EditContext'] = EditContext;
Object.defineProperty(EditContext.prototype, "undo_tool", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_EditContext__get_undo_tool(self), UndoTool);
    }});
Object.defineProperty(EditContext.prototype, "redo_tool", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_EditContext__get_redo_tool(self), RedoTool);
    }});
Object.defineProperty(EditContext.prototype, "work_plane", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_EditContext__get_work_plane(self), Plane);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_EditContext__set_work_plane(self, value.ptr);
    }
});
Object.defineProperty(EditContext.prototype, "translate_tool", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_EditContext__get_translate_tool(self), TranslateTool);
    }});
Object.defineProperty(EditContext.prototype, "rotate_tool", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_EditContext__get_rotate_tool(self), RotateTool);
    }});
Object.defineProperty(EditContext.prototype, "scale_tool", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_EditContext__get_scale_tool(self), ScaleTool);
    }});
Object.defineProperty(EditContext.prototype, "viewer", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_EditContext__get_viewer(self), Viewer);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_EditContext__set_viewer(self, value.ptr);
    }
});
Object.defineProperty(EditContext.prototype, "tool", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_EditContext__get_tool(self), ViewportTool);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_EditContext__set_tool(self, value.ptr);
    }
});
Object.defineProperty(EditContext.prototype, "spatial_tool", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_EditContext__get_spatial_tool(self), SpatialTool);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_EditContext__set_spatial_tool(self, value.ptr);
    }
});
Object.defineProperty(EditContext.prototype, "brush", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_EditContext__get_brush(self), Brush);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_EditContext__set_brush(self, value.ptr);
    }
});
EditContext.prototype["__destroy__"] = EditContext.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_EditContext__destroy(self);
};
// EditorAction
function EditorAction() { throw "cannot construct a EditorAction, no constructor in IDL" }
EditorAction.prototype = Object.create(WrapperObject.prototype);
EditorAction.prototype.constructor = EditorAction;
EditorAction.prototype.__class__ = EditorAction;
EditorAction.__cache__ = {};
Module['EditorAction'] = EditorAction;
EditorAction.prototype["__destroy__"] = EditorAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_EditorAction__destroy(self);
};
// Gizmo
function Gizmo() { throw "cannot construct a Gizmo, no constructor in IDL" }
Gizmo.prototype = Object.create(WrapperObject.prototype);
Gizmo.prototype.constructor = Gizmo;
Gizmo.prototype.__class__ = Gizmo;
Gizmo.__cache__ = {};
Module['Gizmo'] = Gizmo;
Gizmo.prototype["__destroy__"] = Gizmo.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Gizmo__destroy(self);
};
// Tool
function Tool() { throw "cannot construct a Tool, no constructor in IDL" }
Tool.prototype = Object.create(WrapperObject.prototype);
Tool.prototype.constructor = Tool;
Tool.prototype.__class__ = Tool;
Tool.__cache__ = {};
Module['Tool'] = Tool;
Object.defineProperty(Tool.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Tool__get_type(self), Type);
    }});
Object.defineProperty(Tool.prototype, "context", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Tool__get_context(self), ToolContext);
    }});
Object.defineProperty(Tool.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Tool__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Tool__set_name(self, ensureString(value));
    }
});
Object.defineProperty(Tool.prototype, "state", {
    get: function() {
        var self = this.ptr;
        return _mud_Tool__get_state(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Tool__set_state(self, value);
    }
});
Tool.prototype["__destroy__"] = Tool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Tool__destroy(self);
};
// ToolContext
function ToolContext() {
    this.ptr = _mud_ToolContext__construct_0(); this.type = ToolContext; getCache(ToolContext)[this.ptr] = this;
};
ToolContext.prototype = Object.create(WrapperObject.prototype);
ToolContext.prototype.constructor = ToolContext;
ToolContext.prototype.__class__ = ToolContext;
ToolContext.__cache__ = {};
Module['ToolContext'] = ToolContext;
ToolContext.prototype["__destroy__"] = ToolContext.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ToolContext__destroy(self);
};
// ToolOption
function ToolOption() { throw "cannot construct a ToolOption, no constructor in IDL" }
ToolOption.prototype = Object.create(WrapperObject.prototype);
ToolOption.prototype.constructor = ToolOption;
ToolOption.prototype.__class__ = ToolOption;
ToolOption.__cache__ = {};
Module['ToolOption'] = ToolOption;
ToolOption.prototype["__destroy__"] = ToolOption.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ToolOption__destroy(self);
};
// Brush
function Brush() { throw "cannot construct a Brush, no constructor in IDL" }
Brush.prototype = Object.create(SpatialTool.prototype);
Brush.prototype.constructor = Brush;
Brush.prototype.__class__ = Brush;
Brush.__cache__ = {};
Module['Brush'] = Brush;
Brush.prototype["__destroy__"] = Brush.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Brush__destroy(self);
};
// CircleBrush
function CircleBrush(a0) {
    this.ptr = _mud_CircleBrush__construct_1(/*context*/a0.ptr); this.type = CircleBrush; getCache(CircleBrush)[this.ptr] = this;
};
CircleBrush.prototype = Object.create(Brush.prototype);
CircleBrush.prototype.constructor = CircleBrush;
CircleBrush.prototype.__class__ = CircleBrush;
CircleBrush.__cache__ = {};
Module['CircleBrush'] = CircleBrush;
Object.defineProperty(CircleBrush.prototype, "creator", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_CircleBrush__get_creator(self), Creator);
    }});
Object.defineProperty(CircleBrush.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_CircleBrush__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_CircleBrush__set_radius(self, value);
    }
});
Object.defineProperty(CircleBrush.prototype, "maxSpotRadius", {
    get: function() {
        var self = this.ptr;
        return _mud_CircleBrush__get_maxSpotRadius(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_CircleBrush__set_maxSpotRadius(self, value);
    }
});
CircleBrush.prototype["__destroy__"] = CircleBrush.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_CircleBrush__destroy(self);
};
// PlaceBrush
function PlaceBrush(a0) {
    this.ptr = _mud_PlaceBrush__construct_1(/*context*/a0.ptr); this.type = PlaceBrush; getCache(PlaceBrush)[this.ptr] = this;
};
PlaceBrush.prototype = Object.create(Brush.prototype);
PlaceBrush.prototype.constructor = PlaceBrush;
PlaceBrush.prototype.__class__ = PlaceBrush;
PlaceBrush.__cache__ = {};
Module['PlaceBrush'] = PlaceBrush;
Object.defineProperty(PlaceBrush.prototype, "creator", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PlaceBrush__get_creator(self), Creator);
    }});
PlaceBrush.prototype["__destroy__"] = PlaceBrush.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_PlaceBrush__destroy(self);
};
// PlaneSnapOption
function PlaneSnapOption() { throw "cannot construct a PlaneSnapOption, no constructor in IDL" }
PlaneSnapOption.prototype = Object.create(ToolOption.prototype);
PlaneSnapOption.prototype.constructor = PlaneSnapOption;
PlaneSnapOption.prototype.__class__ = PlaneSnapOption;
PlaneSnapOption.__cache__ = {};
Module['PlaneSnapOption'] = PlaneSnapOption;
PlaneSnapOption.prototype["__destroy__"] = PlaneSnapOption.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_PlaneSnapOption__destroy(self);
};
// RedoTool
function RedoTool() { throw "cannot construct a RedoTool, no constructor in IDL" }
RedoTool.prototype = Object.create(Tool.prototype);
RedoTool.prototype.constructor = RedoTool;
RedoTool.prototype.__class__ = RedoTool;
RedoTool.__cache__ = {};
Module['RedoTool'] = RedoTool;
RedoTool.prototype["__destroy__"] = RedoTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_RedoTool__destroy(self);
};
// ScriptedBrush
function ScriptedBrush(a0, a1) {
    this.ptr = _mud_ScriptedBrush__construct_2(/*context*/a0.ptr, /*script*/a1.ptr); this.type = ScriptedBrush; getCache(ScriptedBrush)[this.ptr] = this;
};
ScriptedBrush.prototype = Object.create(Brush.prototype);
ScriptedBrush.prototype.constructor = ScriptedBrush;
ScriptedBrush.prototype.__class__ = ScriptedBrush;
ScriptedBrush.__cache__ = {};
Module['ScriptedBrush'] = ScriptedBrush;
Object.defineProperty(ScriptedBrush.prototype, "call", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ScriptedBrush__get_call(self), Call);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ScriptedBrush__set_call(self, value.ptr);
    }
});
ScriptedBrush.prototype["__destroy__"] = ScriptedBrush.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ScriptedBrush__destroy(self);
};
// TransformAction
function TransformAction() { throw "cannot construct a TransformAction, no constructor in IDL" }
TransformAction.prototype = Object.create(EditorAction.prototype);
TransformAction.prototype.constructor = TransformAction;
TransformAction.prototype.__class__ = TransformAction;
TransformAction.__cache__ = {};
Module['TransformAction'] = TransformAction;
TransformAction.prototype["__destroy__"] = TransformAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TransformAction__destroy(self);
};
// TransformGizmo
function TransformGizmo() { throw "cannot construct a TransformGizmo, no constructor in IDL" }
TransformGizmo.prototype = Object.create(Gizmo.prototype);
TransformGizmo.prototype.constructor = TransformGizmo;
TransformGizmo.prototype.__class__ = TransformGizmo;
TransformGizmo.__cache__ = {};
Module['TransformGizmo'] = TransformGizmo;
TransformGizmo.prototype["__destroy__"] = TransformGizmo.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TransformGizmo__destroy(self);
};
// ViewportTool
function ViewportTool() { throw "cannot construct a ViewportTool, no constructor in IDL" }
ViewportTool.prototype = Object.create(Tool.prototype);
ViewportTool.prototype.constructor = ViewportTool;
ViewportTool.prototype.__class__ = ViewportTool;
ViewportTool.__cache__ = {};
Module['ViewportTool'] = ViewportTool;
ViewportTool.prototype["__destroy__"] = ViewportTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ViewportTool__destroy(self);
};
// SpatialTool
function SpatialTool() { throw "cannot construct a SpatialTool, no constructor in IDL" }
SpatialTool.prototype = Object.create(ViewportTool.prototype);
SpatialTool.prototype.constructor = SpatialTool;
SpatialTool.prototype.__class__ = SpatialTool;
SpatialTool.__cache__ = {};
Module['SpatialTool'] = SpatialTool;
SpatialTool.prototype["__destroy__"] = SpatialTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_SpatialTool__destroy(self);
};
// TransformTool
function TransformTool() { throw "cannot construct a TransformTool, no constructor in IDL" }
TransformTool.prototype = Object.create(SpatialTool.prototype);
TransformTool.prototype.constructor = TransformTool;
TransformTool.prototype.__class__ = TransformTool;
TransformTool.__cache__ = {};
Module['TransformTool'] = TransformTool;
TransformTool.prototype["__destroy__"] = TransformTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TransformTool__destroy(self);
};
// CopyTool
function CopyTool() { throw "cannot construct a CopyTool, no constructor in IDL" }
CopyTool.prototype = Object.create(TransformTool.prototype);
CopyTool.prototype.constructor = CopyTool;
CopyTool.prototype.__class__ = CopyTool;
CopyTool.__cache__ = {};
Module['CopyTool'] = CopyTool;
CopyTool.prototype["__destroy__"] = CopyTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_CopyTool__destroy(self);
};
// RotateAction
function RotateAction() { throw "cannot construct a RotateAction, no constructor in IDL" }
RotateAction.prototype = Object.create(TransformAction.prototype);
RotateAction.prototype.constructor = RotateAction;
RotateAction.prototype.__class__ = RotateAction;
RotateAction.__cache__ = {};
Module['RotateAction'] = RotateAction;
RotateAction.prototype["__destroy__"] = RotateAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_RotateAction__destroy(self);
};
// RotateTool
function RotateTool() { throw "cannot construct a RotateTool, no constructor in IDL" }
RotateTool.prototype = Object.create(TransformTool.prototype);
RotateTool.prototype.constructor = RotateTool;
RotateTool.prototype.__class__ = RotateTool;
RotateTool.__cache__ = {};
Module['RotateTool'] = RotateTool;
RotateTool.prototype["__destroy__"] = RotateTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_RotateTool__destroy(self);
};
// ScaleAction
function ScaleAction() { throw "cannot construct a ScaleAction, no constructor in IDL" }
ScaleAction.prototype = Object.create(TransformAction.prototype);
ScaleAction.prototype.constructor = ScaleAction;
ScaleAction.prototype.__class__ = ScaleAction;
ScaleAction.__cache__ = {};
Module['ScaleAction'] = ScaleAction;
ScaleAction.prototype["__destroy__"] = ScaleAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ScaleAction__destroy(self);
};
// ScaleTool
function ScaleTool() { throw "cannot construct a ScaleTool, no constructor in IDL" }
ScaleTool.prototype = Object.create(TransformTool.prototype);
ScaleTool.prototype.constructor = ScaleTool;
ScaleTool.prototype.__class__ = ScaleTool;
ScaleTool.__cache__ = {};
Module['ScaleTool'] = ScaleTool;
ScaleTool.prototype["__destroy__"] = ScaleTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ScaleTool__destroy(self);
};
// TranslateAction
function TranslateAction() { throw "cannot construct a TranslateAction, no constructor in IDL" }
TranslateAction.prototype = Object.create(TransformAction.prototype);
TranslateAction.prototype.constructor = TranslateAction;
TranslateAction.prototype.__class__ = TranslateAction;
TranslateAction.__cache__ = {};
Module['TranslateAction'] = TranslateAction;
TranslateAction.prototype["__destroy__"] = TranslateAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TranslateAction__destroy(self);
};
// CopyAction
function CopyAction() { throw "cannot construct a CopyAction, no constructor in IDL" }
CopyAction.prototype = Object.create(TranslateAction.prototype);
CopyAction.prototype.constructor = CopyAction;
CopyAction.prototype.__class__ = CopyAction;
CopyAction.__cache__ = {};
Module['CopyAction'] = CopyAction;
CopyAction.prototype["__destroy__"] = CopyAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_CopyAction__destroy(self);
};
// FrameViewTool
function FrameViewTool() { throw "cannot construct a FrameViewTool, no constructor in IDL" }
FrameViewTool.prototype = Object.create(ViewportTool.prototype);
FrameViewTool.prototype.constructor = FrameViewTool;
FrameViewTool.prototype.__class__ = FrameViewTool;
FrameViewTool.__cache__ = {};
Module['FrameViewTool'] = FrameViewTool;
FrameViewTool.prototype["__destroy__"] = FrameViewTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FrameViewTool__destroy(self);
};
// TranslateTool
function TranslateTool() { throw "cannot construct a TranslateTool, no constructor in IDL" }
TranslateTool.prototype = Object.create(TransformTool.prototype);
TranslateTool.prototype.constructor = TranslateTool;
TranslateTool.prototype.__class__ = TranslateTool;
TranslateTool.__cache__ = {};
Module['TranslateTool'] = TranslateTool;
TranslateTool.prototype["__destroy__"] = TranslateTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TranslateTool__destroy(self);
};
// UndoTool
function UndoTool() { throw "cannot construct a UndoTool, no constructor in IDL" }
UndoTool.prototype = Object.create(Tool.prototype);
UndoTool.prototype.constructor = UndoTool;
UndoTool.prototype.__class__ = UndoTool;
UndoTool.__cache__ = {};
Module['UndoTool'] = UndoTool;
UndoTool.prototype["__destroy__"] = UndoTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_UndoTool__destroy(self);
};
// ViewAction
function ViewAction() { throw "cannot construct a ViewAction, no constructor in IDL" }
ViewAction.prototype = Object.create(EditorAction.prototype);
ViewAction.prototype.constructor = ViewAction;
ViewAction.prototype.__class__ = ViewAction;
ViewAction.__cache__ = {};
Module['ViewAction'] = ViewAction;
ViewAction.prototype["__destroy__"] = ViewAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ViewAction__destroy(self);
};
// ViewTool
function ViewTool() { throw "cannot construct a ViewTool, no constructor in IDL" }
ViewTool.prototype = Object.create(ViewportTool.prototype);
ViewTool.prototype.constructor = ViewTool;
ViewTool.prototype.__class__ = ViewTool;
ViewTool.__cache__ = {};
Module['ViewTool'] = ViewTool;
ViewTool.prototype["__destroy__"] = ViewTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ViewTool__destroy(self);
};
// WorkPlaneAction
function WorkPlaneAction() { throw "cannot construct a WorkPlaneAction, no constructor in IDL" }
WorkPlaneAction.prototype = Object.create(EditorAction.prototype);
WorkPlaneAction.prototype.constructor = WorkPlaneAction;
WorkPlaneAction.prototype.__class__ = WorkPlaneAction;
WorkPlaneAction.__cache__ = {};
Module['WorkPlaneAction'] = WorkPlaneAction;
WorkPlaneAction.prototype["__destroy__"] = WorkPlaneAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_WorkPlaneAction__destroy(self);
};
// WorkPlaneTool
function WorkPlaneTool() { throw "cannot construct a WorkPlaneTool, no constructor in IDL" }
WorkPlaneTool.prototype = Object.create(Tool.prototype);
WorkPlaneTool.prototype.constructor = WorkPlaneTool;
WorkPlaneTool.prototype.__class__ = WorkPlaneTool;
WorkPlaneTool.__cache__ = {};
Module['WorkPlaneTool'] = WorkPlaneTool;
WorkPlaneTool.prototype["__destroy__"] = WorkPlaneTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_WorkPlaneTool__destroy(self);
};
// WorldSnapOption
function WorldSnapOption() { throw "cannot construct a WorldSnapOption, no constructor in IDL" }
WorldSnapOption.prototype = Object.create(ToolOption.prototype);
WorldSnapOption.prototype.constructor = WorldSnapOption;
WorldSnapOption.prototype.__class__ = WorldSnapOption;
WorldSnapOption.__cache__ = {};
Module['WorldSnapOption'] = WorldSnapOption;
WorldSnapOption.prototype["__destroy__"] = WorldSnapOption.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_WorldSnapOption__destroy(self);
};

(function() {
    function setup() {
        EditContext.__type__ = _mud_EditContext__type();
        EditorAction.__type__ = _mud_EditorAction__type();
        Gizmo.__type__ = _mud_Gizmo__type();
        Tool.__type__ = _mud_Tool__type();
        ToolContext.__type__ = _mud_ToolContext__type();
        ToolOption.__type__ = _mud_ToolOption__type();
        Brush.__type__ = _mud_Brush__type();
        CircleBrush.__type__ = _mud_CircleBrush__type();
        PlaceBrush.__type__ = _mud_PlaceBrush__type();
        PlaneSnapOption.__type__ = _mud_PlaneSnapOption__type();
        RedoTool.__type__ = _mud_RedoTool__type();
        ScriptedBrush.__type__ = _mud_ScriptedBrush__type();
        TransformAction.__type__ = _mud_TransformAction__type();
        TransformGizmo.__type__ = _mud_TransformGizmo__type();
        ViewportTool.__type__ = _mud_ViewportTool__type();
        SpatialTool.__type__ = _mud_SpatialTool__type();
        TransformTool.__type__ = _mud_TransformTool__type();
        CopyTool.__type__ = _mud_CopyTool__type();
        RotateAction.__type__ = _mud_RotateAction__type();
        RotateTool.__type__ = _mud_RotateTool__type();
        ScaleAction.__type__ = _mud_ScaleAction__type();
        ScaleTool.__type__ = _mud_ScaleTool__type();
        TranslateAction.__type__ = _mud_TranslateAction__type();
        CopyAction.__type__ = _mud_CopyAction__type();
        FrameViewTool.__type__ = _mud_FrameViewTool__type();
        TranslateTool.__type__ = _mud_TranslateTool__type();
        UndoTool.__type__ = _mud_UndoTool__type();
        ViewAction.__type__ = _mud_ViewAction__type();
        ViewTool.__type__ = _mud_ViewTool__type();
        WorkPlaneAction.__type__ = _mud_WorkPlaneAction__type();
        WorkPlaneTool.__type__ = _mud_WorkPlaneTool__type();
        WorldSnapOption.__type__ = _mud_WorldSnapOption__type();
        // ToolState
        Module['ToolState'] = Module['ToolState'] || {};
        Module['ToolState']['Inactive'] = _mud_ToolState_Inactive();
        Module['ToolState']['Done'] = _mud_ToolState_Done();
        Module['ToolState']['Active'] = _mud_ToolState_Active();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
