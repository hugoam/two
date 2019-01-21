Module['glm'] = Module['glm'] || {};
Module['ui'] = Module['ui'] || {};
Module['gfx'] = Module['gfx'] || {};
// Object
function Object() { throw "cannot construct a Object, no constructor in IDL" }
Object.prototype = Object.create(WrapperObject.prototype);
Object.prototype.constructor = Object;
Object.prototype.__class__ = Object;
Object.__cache__ = {};
Module['Object'] = Object;
Object.prototype["__destroy__"] = Object.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Object__destroy(self);
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
OrbitController.prototype = Object.create(WrapperObject.prototype);
OrbitController.prototype.constructor = OrbitController;
OrbitController.prototype.__class__ = OrbitController;
OrbitController.__cache__ = {};
Module['OrbitController'] = OrbitController;
OrbitController.prototype["set_eye"] = OrbitController.prototype.set_eye = function(self, rotation) {
    var self = this.ptr;
    /* rotation <quat> [] */
    rotation = rotation.ptr;
    _mud_OrbitController_set_eye_1(self, rotation);
};
OrbitController.prototype["set_target"] = OrbitController.prototype.set_target = function(self, position) {
    var self = this.ptr;
    /* position <vec3> [] */
    position = position.ptr;
    _mud_OrbitController_set_target_1(self, position);
};
Object.defineProperty(OrbitController.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_OrbitController__get_position(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _mud_OrbitController__set_position(self, value);
    }
});
Object.defineProperty(OrbitController.prototype, "yaw", {
    get: function() {
        var self = this.ptr;
        return _mud_OrbitController__get_yaw(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
        _mud_OrbitController__set_distance(self, value);
    }
});
OrbitController.prototype["__destroy__"] = OrbitController.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_OrbitController__destroy(self);
};
// FreeOrbitController
function FreeOrbitController() { throw "cannot construct a FreeOrbitController, no constructor in IDL" }
FreeOrbitController.prototype = Object.create(WrapperObject.prototype);
FreeOrbitController.prototype.constructor = FreeOrbitController;
FreeOrbitController.prototype.__class__ = FreeOrbitController;
FreeOrbitController.__cache__ = {};
Module['FreeOrbitController'] = FreeOrbitController;
FreeOrbitController.prototype["__destroy__"] = FreeOrbitController.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FreeOrbitController__destroy(self);
};
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
        /* value <Scene> [] */
        value = value.ptr;
        _mud_Viewer__set_scene(self, value);
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
        return wrapPointer(_mud_Viewer__get_position(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_Viewer__set_position(self, value);
    }
});
Object.defineProperty(Viewer.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewer__get_size(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_Viewer__set_size(self, value);
    }
});
Viewer.prototype["__destroy__"] = Viewer.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Viewer__destroy(self);
};
// SceneViewer
function SceneViewer() { throw "cannot construct a SceneViewer, no constructor in IDL" }
SceneViewer.prototype = Object.create(WrapperObject.prototype);
SceneViewer.prototype.constructor = SceneViewer;
SceneViewer.prototype.__class__ = SceneViewer;
SceneViewer.__cache__ = {};
Module['SceneViewer'] = SceneViewer;
SceneViewer.prototype["__destroy__"] = SceneViewer.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_SceneViewer__destroy(self);
};
Module['ui']['viewer'] = function(parent, scene) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* scene <Scene> [] */
    scene = scene.ptr;
    return wrapPointer(_mud_ui_viewer_2(parent, scene), Viewer);
};
Module['ui']['scene_viewer'] = function(parent, size) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* size <vec2> [] */
    if(typeof size !== "undefined" && size !== null) { size = size.ptr; }
    if (size === undefined) { return wrapPointer(_mud_ui_scene_viewer_1(parent), SceneViewer); }
    return wrapPointer(_mud_ui_scene_viewer_2(parent, size), SceneViewer);
};
Module['ui']['orbit_controller'] = function(viewer, yaw, pitch, distance) {
    var self = this.ptr;
    /* viewer <Viewer> [] */
    viewer = viewer.ptr;
    /* yaw <float> [] */
    /* pitch <float> [] */
    /* distance <float> [] */
    if (distance === undefined) { return wrapPointer(_mud_ui_orbit_controller_3(viewer, yaw, pitch), OrbitController); }
    return wrapPointer(_mud_ui_orbit_controller_4(viewer, yaw, pitch, distance), OrbitController);
};
Module['ui']['free_orbit_controller'] = function(viewer) {
    var self = this.ptr;
    /* viewer <Viewer> [] */
    viewer = viewer.ptr;
    return wrapPointer(_mud_ui_free_orbit_controller_1(viewer), FreeOrbitController);
};
Module['ui']['isometric_controller'] = function(viewer, topdown) {
    var self = this.ptr;
    /* viewer <Viewer> [] */
    viewer = viewer.ptr;
    /* topdown <bool> [] */
    if (topdown === undefined) { return wrapPointer(_mud_ui_isometric_controller_1(viewer), OrbitController); }
    return wrapPointer(_mud_ui_isometric_controller_2(viewer, topdown), OrbitController);
};
Module['ui']['hybrid_controller'] = function(viewer, mode, entity, aiming, angles, modal) {
    var self = this.ptr;
    /* viewer <Viewer> [] */
    viewer = viewer.ptr;
    /* mode <OrbitMode> [] */
    if (mode && typeof mode === "object") mode = mode.ptr;
    /* entity <Transform> [] */
    entity = entity.ptr;
    /* aiming <bool> [] */
    /* angles <vec2> [] */
    angles = angles.ptr;
    /* modal <bool> [] */
    if (modal === undefined) { return wrapPointer(_mud_ui_hybrid_controller_5(viewer, mode, entity, aiming, angles), OrbitController); }
    return wrapPointer(_mud_ui_hybrid_controller_6(viewer, mode, entity, aiming, angles, modal), OrbitController);
};
Module['ui']['velocity_controller'] = function(viewer, linear, angular, speed) {
    var self = this.ptr;
    /* viewer <Viewer> [] */
    viewer = viewer.ptr;
    /* linear <vec3> [] */
    linear = linear.ptr;
    /* angular <vec3> [] */
    angular = angular.ptr;
    /* speed <float> [] */
    if (speed === undefined) { _mud_ui_velocity_controller_3(viewer, linear, angular); return; }
    _mud_ui_velocity_controller_4(viewer, linear, angular, speed);
};

(function() {
    function setup() {
        Object.__type__ = _mud_Object__type();
        ViewerController.__type__ = _mud_ViewerController__type();
        OrbitController.__type__ = _mud_OrbitController__type();
        FreeOrbitController.__type__ = _mud_FreeOrbitController__type();
        SpaceSheet.__type__ = _mud_SpaceSheet__type();
        Viewer.__type__ = _mud_Viewer__type();
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
