Module['ui'] = Module['ui'] || {};
// SpaceSheet
function SpaceSheet() { throw "cannot construct a SpaceSheet, no constructor in IDL" }
SpaceSheet.prototype = Object.create(WrapperObject.prototype);
SpaceSheet.prototype.constructor = SpaceSheet;
SpaceSheet.prototype.__class__ = SpaceSheet;
SpaceSheet.__cache__ = {};
Module['SpaceSheet'] = SpaceSheet;
SpaceSheet.prototype["__destroy__"] = SpaceSheet.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_SpaceSheet__destroy(self);
};
// Viewer
function Viewer() { throw "cannot construct a Viewer, no constructor in IDL" }
Viewer.prototype = Object.create(WrapperObject.prototype);
Viewer.prototype.constructor = Viewer;
Viewer.prototype.__class__ = Viewer;
Viewer.__cache__ = {};
Module['Viewer'] = Viewer;
Object.defineProperty(Viewer.prototype, "scene", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewer__get_scene(self), Scene);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Viewer__set_scene(self, value.ptr);
    }
});
Object.defineProperty(Viewer.prototype, "viewport", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewer__get_viewport(self), Viewport);
    }});
Object.defineProperty(Viewer.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewer__get_position(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Viewer__set_position(self, value.ptr);
    }
});
Object.defineProperty(Viewer.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewer__get_size(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Viewer__set_size(self, value.ptr);
    }
});
Viewer.prototype["__destroy__"] = Viewer.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Viewer__destroy(self);
};
// ViewerController
function ViewerController() { throw "cannot construct a ViewerController, no constructor in IDL" }
ViewerController.prototype = Object.create(WrapperObject.prototype);
ViewerController.prototype.constructor = ViewerController;
ViewerController.prototype.__class__ = ViewerController;
ViewerController.__cache__ = {};
Module['ViewerController'] = ViewerController;
ViewerController.prototype["__destroy__"] = ViewerController.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ViewerController__destroy(self);
};
// OrbitController
function OrbitController() { throw "cannot construct a OrbitController, no constructor in IDL" }
OrbitController.prototype = Object.create(ViewerController.prototype);
OrbitController.prototype.constructor = OrbitController;
OrbitController.prototype.__class__ = OrbitController;
OrbitController.__cache__ = {};
Module['OrbitController'] = OrbitController;
OrbitController.prototype["set_eye"] = OrbitController.prototype.set_eye = function(self, a0) {
    var self = this.ptr;
    _mud_OrbitController_set_eye_1(self, /*rotation*/a0.ptr);
};
OrbitController.prototype["set_target"] = OrbitController.prototype.set_target = function(self, a0) {
    var self = this.ptr;
    _mud_OrbitController_set_target_1(self, /*position*/a0.ptr);
};
Object.defineProperty(OrbitController.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_OrbitController__get_position(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_OrbitController__set_position(self, value.ptr);
    }
});
Object.defineProperty(OrbitController.prototype, "yaw", {
    get: function() {
        var self = this.ptr;
        return _mud_OrbitController__get_yaw(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_OrbitController__set_yaw(self, value);
    }
});
Object.defineProperty(OrbitController.prototype, "pitch", {
    get: function() {
        var self = this.ptr;
        return _mud_OrbitController__get_pitch(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_OrbitController__set_pitch(self, value);
    }
});
Object.defineProperty(OrbitController.prototype, "distance", {
    get: function() {
        var self = this.ptr;
        return _mud_OrbitController__get_distance(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_OrbitController__set_distance(self, value);
    }
});
OrbitController.prototype["__destroy__"] = OrbitController.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_OrbitController__destroy(self);
};
// FreeOrbitController
function FreeOrbitController() { throw "cannot construct a FreeOrbitController, no constructor in IDL" }
FreeOrbitController.prototype = Object.create(OrbitController.prototype);
FreeOrbitController.prototype.constructor = FreeOrbitController;
FreeOrbitController.prototype.__class__ = FreeOrbitController;
FreeOrbitController.__cache__ = {};
Module['FreeOrbitController'] = FreeOrbitController;
FreeOrbitController.prototype["__destroy__"] = FreeOrbitController.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FreeOrbitController__destroy(self);
};
// SceneViewer
function SceneViewer() { throw "cannot construct a SceneViewer, no constructor in IDL" }
SceneViewer.prototype = Object.create(Viewer.prototype);
SceneViewer.prototype.constructor = SceneViewer;
SceneViewer.prototype.__class__ = SceneViewer;
SceneViewer.__cache__ = {};
Module['SceneViewer'] = SceneViewer;
SceneViewer.prototype["__destroy__"] = SceneViewer.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_SceneViewer__destroy(self);
};
Module['ui']['viewer'] = function(a0, a1) {
    return wrapPointer(_mud_ui_viewer_2(/*parent*/a0.ptr, /*scene*/a1.ptr), Viewer);
};
Module['ui']['scene_viewer'] = function(a0, a1) {
    if (a1 === undefined) { return wrapPointer(_mud_ui_scene_viewer_1(/*parent*/a0.ptr), SceneViewer); }
    return wrapPointer(_mud_ui_scene_viewer_2(/*parent*/a0.ptr, /*size*/a1.ptr), SceneViewer);
};
Module['ui']['orbit_controller'] = function(a0, a1, a2, a3) {
    if (a1 === undefined) { return wrapPointer(_mud_ui_orbit_controller_1(/*viewer*/a0.ptr), OrbitController); }
    if (a2 === undefined) { return wrapPointer(_mud_ui_orbit_controller_2(/*viewer*/a0.ptr, /*yaw*/a1), OrbitController); }
    if (a3 === undefined) { return wrapPointer(_mud_ui_orbit_controller_3(/*viewer*/a0.ptr, /*yaw*/a1, /*pitch*/a2), OrbitController); }
    return wrapPointer(_mud_ui_orbit_controller_4(/*viewer*/a0.ptr, /*yaw*/a1, /*pitch*/a2, /*distance*/a3), OrbitController);
};
Module['ui']['free_orbit_controller'] = function(a0) {
    return wrapPointer(_mud_ui_free_orbit_controller_1(/*viewer*/a0.ptr), FreeOrbitController);
};
Module['ui']['isometric_controller'] = function(a0, a1) {
    if (a1 === undefined) { return wrapPointer(_mud_ui_isometric_controller_1(/*viewer*/a0.ptr), OrbitController); }
    return wrapPointer(_mud_ui_isometric_controller_2(/*viewer*/a0.ptr, /*topdown*/a1), OrbitController);
};
Module['ui']['hybrid_controller'] = function(a0, a1, a2, a3, a4, a5) {
    if (a5 === undefined) { return wrapPointer(_mud_ui_hybrid_controller_5(/*viewer*/a0.ptr, /*mode*/a1, /*entity*/a2.ptr, /*aiming*/a3, /*angles*/a4.ptr), OrbitController); }
    return wrapPointer(_mud_ui_hybrid_controller_6(/*viewer*/a0.ptr, /*mode*/a1, /*entity*/a2.ptr, /*aiming*/a3, /*angles*/a4.ptr, /*modal*/a5), OrbitController);
};
Module['ui']['velocity_controller'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { _mud_ui_velocity_controller_3(/*viewer*/a0.ptr, /*linear*/a1.ptr, /*angular*/a2.ptr); return; }
    _mud_ui_velocity_controller_4(/*viewer*/a0.ptr, /*linear*/a1.ptr, /*angular*/a2.ptr, /*speed*/a3);
};

(function() {
    function setup() {
        SpaceSheet.__type__ = _mud_SpaceSheet__type();
        Viewer.__type__ = _mud_Viewer__type();
        ViewerController.__type__ = _mud_ViewerController__type();
        OrbitController.__type__ = _mud_OrbitController__type();
        FreeOrbitController.__type__ = _mud_FreeOrbitController__type();
        SceneViewer.__type__ = _mud_SceneViewer__type();
        // OrbitMode
        Module['ui']['OrbitMode'] = Module['ui']['OrbitMode'] || {};
        Module['ui']['OrbitMode']['ThirdPerson'] = _mud_ui_OrbitMode_ThirdPerson();
        Module['ui']['OrbitMode']['Isometric'] = _mud_ui_OrbitMode_Isometric();
        Module['ui']['OrbitMode']['PseudoIsometric'] = _mud_ui_OrbitMode_PseudoIsometric();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
