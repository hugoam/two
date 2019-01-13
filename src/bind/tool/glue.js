
// Bindings utilities
function WrapperObject() {
}
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
        return _EditContext_get_undo_tool(self);
    },
    set: function(undo_tool) {
        var self = this.ptr;
        /* undo_tool <UndoTool> [] */
        _EditContext_set_undo_tool(self, undo_tool);
    }
});
Object.defineProperty(EditContext.prototype, "redo_tool", {
    get: function() {
        var self = this.ptr;
        return _EditContext_get_redo_tool(self);
    },
    set: function(redo_tool) {
        var self = this.ptr;
        /* redo_tool <RedoTool> [] */
        _EditContext_set_redo_tool(self, redo_tool);
    }
});
Object.defineProperty(EditContext.prototype, "work_plane", {
    get: function() {
        var self = this.ptr;
        return _EditContext_get_work_plane(self);
    },
    set: function(work_plane) {
        var self = this.ptr;
        /* work_plane <Plane> [] */
        _EditContext_set_work_plane(self, work_plane);
    }
});
Object.defineProperty(EditContext.prototype, "translate_tool", {
    get: function() {
        var self = this.ptr;
        return _EditContext_get_translate_tool(self);
    },
    set: function(translate_tool) {
        var self = this.ptr;
        /* translate_tool <TranslateTool> [] */
        _EditContext_set_translate_tool(self, translate_tool);
    }
});
Object.defineProperty(EditContext.prototype, "rotate_tool", {
    get: function() {
        var self = this.ptr;
        return _EditContext_get_rotate_tool(self);
    },
    set: function(rotate_tool) {
        var self = this.ptr;
        /* rotate_tool <RotateTool> [] */
        _EditContext_set_rotate_tool(self, rotate_tool);
    }
});
Object.defineProperty(EditContext.prototype, "scale_tool", {
    get: function() {
        var self = this.ptr;
        return _EditContext_get_scale_tool(self);
    },
    set: function(scale_tool) {
        var self = this.ptr;
        /* scale_tool <ScaleTool> [] */
        _EditContext_set_scale_tool(self, scale_tool);
    }
});
Object.defineProperty(EditContext.prototype, "viewer", {
    get: function() {
        var self = this.ptr;
        return _EditContext_get_viewer(self);
    },
    set: function(viewer) {
        var self = this.ptr;
        /* viewer <Viewer> [] */
        _EditContext_set_viewer(self, viewer);
    }
});
Object.defineProperty(EditContext.prototype, "tool", {
    get: function() {
        var self = this.ptr;
        return _EditContext_get_tool(self);
    },
    set: function(tool) {
        var self = this.ptr;
        /* tool <ViewportTool> [] */
        _EditContext_set_tool(self, tool);
    }
});
Object.defineProperty(EditContext.prototype, "spatial_tool", {
    get: function() {
        var self = this.ptr;
        return _EditContext_get_spatial_tool(self);
    },
    set: function(spatial_tool) {
        var self = this.ptr;
        /* spatial_tool <SpatialTool> [] */
        _EditContext_set_spatial_tool(self, spatial_tool);
    }
});
Object.defineProperty(EditContext.prototype, "brush", {
    get: function() {
        var self = this.ptr;
        return _EditContext_get_brush(self);
    },
    set: function(brush) {
        var self = this.ptr;
        /* brush <Brush> [] */
        _EditContext_set_brush(self, brush);
    }
});
EditContext.prototype["__destroy__"] = EditContext.prototype.__destroy__ = function() {
    var self = this.ptr;
    _EditContext___destroy__(self);
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
    _EditorAction___destroy__(self);
};
// Gizmo
function Gizmo() {
    var self = this.ptr;
    this.ptr = _Gizmo_Gizmo_0(self); getCache(Gizmo)[this.ptr] = this;
};
Gizmo.prototype = Object.create(WrapperObject.prototype);
Gizmo.prototype.constructor = Gizmo;
Gizmo.prototype.__class__ = Gizmo;
Gizmo.__cache__ = {};
Module['Gizmo'] = Gizmo;
Gizmo.prototype["__destroy__"] = Gizmo.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Gizmo___destroy__(self);
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
        return _Tool_get_type(self);
    },
    set: function(type) {
        var self = this.ptr;
        /* type <Type> [] */
        _Tool_set_type(self, type);
    }
});
Object.defineProperty(Tool.prototype, "context", {
    get: function() {
        var self = this.ptr;
        return _Tool_get_context(self);
    },
    set: function(context) {
        var self = this.ptr;
        /* context <ToolContext> [] */
        _Tool_set_context(self, context);
    }
});
Object.defineProperty(Tool.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_Tool_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _Tool_set_name(self, name);
    }
});
Object.defineProperty(Tool.prototype, "state", {
    get: function() {
        var self = this.ptr;
        return _Tool_get_state(self);
    },
    set: function(state) {
        var self = this.ptr;
        /* state <ToolState> [] */
        _Tool_set_state(self, state);
    }
});
Tool.prototype["__destroy__"] = Tool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Tool___destroy__(self);
};
// ToolContext
function ToolContext() {
    var self = this.ptr;
    this.ptr = _ToolContext_ToolContext_0(self); getCache(ToolContext)[this.ptr] = this;
};
ToolContext.prototype = Object.create(WrapperObject.prototype);
ToolContext.prototype.constructor = ToolContext;
ToolContext.prototype.__class__ = ToolContext;
ToolContext.__cache__ = {};
Module['ToolContext'] = ToolContext;
ToolContext.prototype["__destroy__"] = ToolContext.prototype.__destroy__ = function() {
    var self = this.ptr;
    _ToolContext___destroy__(self);
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
    _ToolOption___destroy__(self);
};
// RedoTool
function RedoTool() { throw "cannot construct a RedoTool, no constructor in IDL" }
RedoTool.prototype = Object.create(WrapperObject.prototype);
RedoTool.prototype.constructor = RedoTool;
RedoTool.prototype.__class__ = RedoTool;
RedoTool.__cache__ = {};
Module['RedoTool'] = RedoTool;
RedoTool.prototype["__destroy__"] = RedoTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _RedoTool___destroy__(self);
};
// ViewportTool
function ViewportTool() { throw "cannot construct a ViewportTool, no constructor in IDL" }
ViewportTool.prototype = Object.create(WrapperObject.prototype);
ViewportTool.prototype.constructor = ViewportTool;
ViewportTool.prototype.__class__ = ViewportTool;
ViewportTool.__cache__ = {};
Module['ViewportTool'] = ViewportTool;
ViewportTool.prototype["__destroy__"] = ViewportTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _ViewportTool___destroy__(self);
};
// SpatialTool
function SpatialTool() { throw "cannot construct a SpatialTool, no constructor in IDL" }
SpatialTool.prototype = Object.create(WrapperObject.prototype);
SpatialTool.prototype.constructor = SpatialTool;
SpatialTool.prototype.__class__ = SpatialTool;
SpatialTool.__cache__ = {};
Module['SpatialTool'] = SpatialTool;
SpatialTool.prototype["__destroy__"] = SpatialTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _SpatialTool___destroy__(self);
};
// Brush
function Brush() { throw "cannot construct a Brush, no constructor in IDL" }
Brush.prototype = Object.create(WrapperObject.prototype);
Brush.prototype.constructor = Brush;
Brush.prototype.__class__ = Brush;
Brush.__cache__ = {};
Module['Brush'] = Brush;
Brush.prototype["__destroy__"] = Brush.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Brush___destroy__(self);
};
// CircleBrush
function CircleBrush(context) {
    var self = this.ptr;
    /* context <ToolContext> [] */
    this.ptr = _CircleBrush_CircleBrush_1(self, context); getCache(CircleBrush)[this.ptr] = this;
};
CircleBrush.prototype = Object.create(WrapperObject.prototype);
CircleBrush.prototype.constructor = CircleBrush;
CircleBrush.prototype.__class__ = CircleBrush;
CircleBrush.__cache__ = {};
Module['CircleBrush'] = CircleBrush;
Object.defineProperty(CircleBrush.prototype, "creator", {
    get: function() {
        var self = this.ptr;
        return _CircleBrush_get_creator(self);
    },
    set: function(creator) {
        var self = this.ptr;
        /* creator <Creator> [] */
        _CircleBrush_set_creator(self, creator);
    }
});
Object.defineProperty(CircleBrush.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _CircleBrush_get_radius(self);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <float> [] */
        _CircleBrush_set_radius(self, radius);
    }
});
Object.defineProperty(CircleBrush.prototype, "maxSpotRadius", {
    get: function() {
        var self = this.ptr;
        return _CircleBrush_get_maxSpotRadius(self);
    },
    set: function(maxSpotRadius) {
        var self = this.ptr;
        /* maxSpotRadius <float> [] */
        _CircleBrush_set_maxSpotRadius(self, maxSpotRadius);
    }
});
CircleBrush.prototype["__destroy__"] = CircleBrush.prototype.__destroy__ = function() {
    var self = this.ptr;
    _CircleBrush___destroy__(self);
};
// PlaceBrush
function PlaceBrush(context) {
    var self = this.ptr;
    /* context <ToolContext> [] */
    this.ptr = _PlaceBrush_PlaceBrush_1(self, context); getCache(PlaceBrush)[this.ptr] = this;
};
PlaceBrush.prototype = Object.create(WrapperObject.prototype);
PlaceBrush.prototype.constructor = PlaceBrush;
PlaceBrush.prototype.__class__ = PlaceBrush;
PlaceBrush.__cache__ = {};
Module['PlaceBrush'] = PlaceBrush;
Object.defineProperty(PlaceBrush.prototype, "creator", {
    get: function() {
        var self = this.ptr;
        return _PlaceBrush_get_creator(self);
    },
    set: function(creator) {
        var self = this.ptr;
        /* creator <Creator> [] */
        _PlaceBrush_set_creator(self, creator);
    }
});
PlaceBrush.prototype["__destroy__"] = PlaceBrush.prototype.__destroy__ = function() {
    var self = this.ptr;
    _PlaceBrush___destroy__(self);
};
// PlaneSnapOption
function PlaneSnapOption() { throw "cannot construct a PlaneSnapOption, no constructor in IDL" }
PlaneSnapOption.prototype = Object.create(WrapperObject.prototype);
PlaneSnapOption.prototype.constructor = PlaneSnapOption;
PlaneSnapOption.prototype.__class__ = PlaneSnapOption;
PlaneSnapOption.__cache__ = {};
Module['PlaneSnapOption'] = PlaneSnapOption;
PlaneSnapOption.prototype["__destroy__"] = PlaneSnapOption.prototype.__destroy__ = function() {
    var self = this.ptr;
    _PlaneSnapOption___destroy__(self);
};
// ScriptedBrush
function ScriptedBrush(context, script) {
    var self = this.ptr;
    /* context <ToolContext> [] */
    /* script <Script> [] */
    this.ptr = _ScriptedBrush_ScriptedBrush_2(self, context, script); getCache(ScriptedBrush)[this.ptr] = this;
};
ScriptedBrush.prototype = Object.create(WrapperObject.prototype);
ScriptedBrush.prototype.constructor = ScriptedBrush;
ScriptedBrush.prototype.__class__ = ScriptedBrush;
ScriptedBrush.__cache__ = {};
Module['ScriptedBrush'] = ScriptedBrush;
Object.defineProperty(ScriptedBrush.prototype, "call", {
    get: function() {
        var self = this.ptr;
        return _ScriptedBrush_get_call(self);
    },
    set: function(call) {
        var self = this.ptr;
        /* call <Call> [] */
        _ScriptedBrush_set_call(self, call);
    }
});
ScriptedBrush.prototype["__destroy__"] = ScriptedBrush.prototype.__destroy__ = function() {
    var self = this.ptr;
    _ScriptedBrush___destroy__(self);
};
// TransformAction
function TransformAction() { throw "cannot construct a TransformAction, no constructor in IDL" }
TransformAction.prototype = Object.create(WrapperObject.prototype);
TransformAction.prototype.constructor = TransformAction;
TransformAction.prototype.__class__ = TransformAction;
TransformAction.__cache__ = {};
Module['TransformAction'] = TransformAction;
TransformAction.prototype["__destroy__"] = TransformAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _TransformAction___destroy__(self);
};
// RotateAction
function RotateAction() { throw "cannot construct a RotateAction, no constructor in IDL" }
RotateAction.prototype = Object.create(WrapperObject.prototype);
RotateAction.prototype.constructor = RotateAction;
RotateAction.prototype.__class__ = RotateAction;
RotateAction.__cache__ = {};
Module['RotateAction'] = RotateAction;
RotateAction.prototype["__destroy__"] = RotateAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _RotateAction___destroy__(self);
};
// TransformTool
function TransformTool() { throw "cannot construct a TransformTool, no constructor in IDL" }
TransformTool.prototype = Object.create(WrapperObject.prototype);
TransformTool.prototype.constructor = TransformTool;
TransformTool.prototype.__class__ = TransformTool;
TransformTool.__cache__ = {};
Module['TransformTool'] = TransformTool;
TransformTool.prototype["__destroy__"] = TransformTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _TransformTool___destroy__(self);
};
// RotateTool
function RotateTool() { throw "cannot construct a RotateTool, no constructor in IDL" }
RotateTool.prototype = Object.create(WrapperObject.prototype);
RotateTool.prototype.constructor = RotateTool;
RotateTool.prototype.__class__ = RotateTool;
RotateTool.__cache__ = {};
Module['RotateTool'] = RotateTool;
RotateTool.prototype["__destroy__"] = RotateTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _RotateTool___destroy__(self);
};
// ScaleAction
function ScaleAction() { throw "cannot construct a ScaleAction, no constructor in IDL" }
ScaleAction.prototype = Object.create(WrapperObject.prototype);
ScaleAction.prototype.constructor = ScaleAction;
ScaleAction.prototype.__class__ = ScaleAction;
ScaleAction.__cache__ = {};
Module['ScaleAction'] = ScaleAction;
ScaleAction.prototype["__destroy__"] = ScaleAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _ScaleAction___destroy__(self);
};
// ScaleTool
function ScaleTool() { throw "cannot construct a ScaleTool, no constructor in IDL" }
ScaleTool.prototype = Object.create(WrapperObject.prototype);
ScaleTool.prototype.constructor = ScaleTool;
ScaleTool.prototype.__class__ = ScaleTool;
ScaleTool.__cache__ = {};
Module['ScaleTool'] = ScaleTool;
ScaleTool.prototype["__destroy__"] = ScaleTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _ScaleTool___destroy__(self);
};
// TranslateAction
function TranslateAction() { throw "cannot construct a TranslateAction, no constructor in IDL" }
TranslateAction.prototype = Object.create(WrapperObject.prototype);
TranslateAction.prototype.constructor = TranslateAction;
TranslateAction.prototype.__class__ = TranslateAction;
TranslateAction.__cache__ = {};
Module['TranslateAction'] = TranslateAction;
TranslateAction.prototype["__destroy__"] = TranslateAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _TranslateAction___destroy__(self);
};
// CopyAction
function CopyAction() { throw "cannot construct a CopyAction, no constructor in IDL" }
CopyAction.prototype = Object.create(WrapperObject.prototype);
CopyAction.prototype.constructor = CopyAction;
CopyAction.prototype.__class__ = CopyAction;
CopyAction.__cache__ = {};
Module['CopyAction'] = CopyAction;
CopyAction.prototype["__destroy__"] = CopyAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _CopyAction___destroy__(self);
};
// CopyTool
function CopyTool() { throw "cannot construct a CopyTool, no constructor in IDL" }
CopyTool.prototype = Object.create(WrapperObject.prototype);
CopyTool.prototype.constructor = CopyTool;
CopyTool.prototype.__class__ = CopyTool;
CopyTool.__cache__ = {};
Module['CopyTool'] = CopyTool;
CopyTool.prototype["__destroy__"] = CopyTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _CopyTool___destroy__(self);
};
// FrameViewTool
function FrameViewTool() { throw "cannot construct a FrameViewTool, no constructor in IDL" }
FrameViewTool.prototype = Object.create(WrapperObject.prototype);
FrameViewTool.prototype.constructor = FrameViewTool;
FrameViewTool.prototype.__class__ = FrameViewTool;
FrameViewTool.__cache__ = {};
Module['FrameViewTool'] = FrameViewTool;
FrameViewTool.prototype["__destroy__"] = FrameViewTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _FrameViewTool___destroy__(self);
};
// TranslateTool
function TranslateTool() { throw "cannot construct a TranslateTool, no constructor in IDL" }
TranslateTool.prototype = Object.create(WrapperObject.prototype);
TranslateTool.prototype.constructor = TranslateTool;
TranslateTool.prototype.__class__ = TranslateTool;
TranslateTool.__cache__ = {};
Module['TranslateTool'] = TranslateTool;
TranslateTool.prototype["__destroy__"] = TranslateTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _TranslateTool___destroy__(self);
};
// UndoTool
function UndoTool() { throw "cannot construct a UndoTool, no constructor in IDL" }
UndoTool.prototype = Object.create(WrapperObject.prototype);
UndoTool.prototype.constructor = UndoTool;
UndoTool.prototype.__class__ = UndoTool;
UndoTool.__cache__ = {};
Module['UndoTool'] = UndoTool;
UndoTool.prototype["__destroy__"] = UndoTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _UndoTool___destroy__(self);
};
// ViewAction
function ViewAction() { throw "cannot construct a ViewAction, no constructor in IDL" }
ViewAction.prototype = Object.create(WrapperObject.prototype);
ViewAction.prototype.constructor = ViewAction;
ViewAction.prototype.__class__ = ViewAction;
ViewAction.__cache__ = {};
Module['ViewAction'] = ViewAction;
ViewAction.prototype["__destroy__"] = ViewAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _ViewAction___destroy__(self);
};
// ViewTool
function ViewTool() { throw "cannot construct a ViewTool, no constructor in IDL" }
ViewTool.prototype = Object.create(WrapperObject.prototype);
ViewTool.prototype.constructor = ViewTool;
ViewTool.prototype.__class__ = ViewTool;
ViewTool.__cache__ = {};
Module['ViewTool'] = ViewTool;
ViewTool.prototype["__destroy__"] = ViewTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _ViewTool___destroy__(self);
};
// WorkPlaneAction
function WorkPlaneAction() { throw "cannot construct a WorkPlaneAction, no constructor in IDL" }
WorkPlaneAction.prototype = Object.create(WrapperObject.prototype);
WorkPlaneAction.prototype.constructor = WorkPlaneAction;
WorkPlaneAction.prototype.__class__ = WorkPlaneAction;
WorkPlaneAction.__cache__ = {};
Module['WorkPlaneAction'] = WorkPlaneAction;
WorkPlaneAction.prototype["__destroy__"] = WorkPlaneAction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _WorkPlaneAction___destroy__(self);
};
// WorkPlaneTool
function WorkPlaneTool() { throw "cannot construct a WorkPlaneTool, no constructor in IDL" }
WorkPlaneTool.prototype = Object.create(WrapperObject.prototype);
WorkPlaneTool.prototype.constructor = WorkPlaneTool;
WorkPlaneTool.prototype.__class__ = WorkPlaneTool;
WorkPlaneTool.__cache__ = {};
Module['WorkPlaneTool'] = WorkPlaneTool;
WorkPlaneTool.prototype["__destroy__"] = WorkPlaneTool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _WorkPlaneTool___destroy__(self);
};
// WorldSnapOption
function WorldSnapOption() { throw "cannot construct a WorldSnapOption, no constructor in IDL" }
WorldSnapOption.prototype = Object.create(WrapperObject.prototype);
WorldSnapOption.prototype.constructor = WorldSnapOption;
WorldSnapOption.prototype.__class__ = WorldSnapOption;
WorldSnapOption.__cache__ = {};
Module['WorldSnapOption'] = WorldSnapOption;
WorldSnapOption.prototype["__destroy__"] = WorldSnapOption.prototype.__destroy__ = function() {
    var self = this.ptr;
    _WorldSnapOption___destroy__(self);
};

(function() {
    function setupEnums() {
        // ToolState
        Module['ToolState']['Inactive'] = _emscripten_enum_ToolState_Inactive();
        Module['ToolState']['Done'] = _emscripten_enum_ToolState_Done();
        Module['ToolState']['Active'] = _emscripten_enum_ToolState_Active();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
