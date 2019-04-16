Module['ui'] = Module['ui'] || {};
// ViewerController
function ViewerController() { throw "cannot construct a ViewerController, no constructor in IDL" }
ViewerController.prototype = Object.create(WrapperObject.prototype);
ViewerController.prototype.constructor = ViewerController;
ViewerController.prototype.__class = ViewerController;
ViewerController.__cache = {};
Module['ViewerController'] = ViewerController;
ViewerController.prototype["__destroy"] = ViewerController.prototype.__destroy = function() {
    _mud_ViewerController__destroy(this.__ptr);
};
// OrbitController
function OrbitController() { throw "cannot construct a OrbitController, no constructor in IDL" }
OrbitController.prototype = Object.create(ViewerController.prototype);
OrbitController.prototype.constructor = OrbitController;
OrbitController.prototype.__class = OrbitController;
OrbitController.__base = ViewerController;
OrbitController.__cache = {};
Module['OrbitController'] = OrbitController;
OrbitController.prototype["set_eye"] = OrbitController.prototype.set_eye = function(a0) {
    if (!checkClass(a0, quat) { throw Error('set_eye(0:rotation): expected quat'); }
    _mud_OrbitController_set_eye_1(this.__ptr, /*rotation*/a0.__ptr);
};
OrbitController.prototype["set_target"] = OrbitController.prototype.set_target = function(a0) {
    if (!checkClass(a0, v3_float) { throw Error('set_target(0:position): expected v3<float>'); }
    _mud_OrbitController_set_target_1(this.__ptr, /*position*/a0.__ptr);
};
Object.defineProperty(OrbitController.prototype, "position", {
    get: function() {
        return wrapPointer(_mud_OrbitController__get_position(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_OrbitController__set_position(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(OrbitController.prototype, "yaw", {
    get: function() {
        return _mud_OrbitController__get_yaw(this.__ptr);
    },
    set: function(value) {
        _mud_OrbitController__set_yaw(this.__ptr, value);
    }
});
Object.defineProperty(OrbitController.prototype, "pitch", {
    get: function() {
        return _mud_OrbitController__get_pitch(this.__ptr);
    },
    set: function(value) {
        _mud_OrbitController__set_pitch(this.__ptr, value);
    }
});
Object.defineProperty(OrbitController.prototype, "distance", {
    get: function() {
        return _mud_OrbitController__get_distance(this.__ptr);
    },
    set: function(value) {
        _mud_OrbitController__set_distance(this.__ptr, value);
    }
});
OrbitController.prototype["__destroy"] = OrbitController.prototype.__destroy = function() {
    _mud_OrbitController__destroy(this.__ptr);
};
// FreeOrbitController
function FreeOrbitController() { throw "cannot construct a FreeOrbitController, no constructor in IDL" }
FreeOrbitController.prototype = Object.create(OrbitController.prototype);
FreeOrbitController.prototype.constructor = FreeOrbitController;
FreeOrbitController.prototype.__class = FreeOrbitController;
FreeOrbitController.__base = OrbitController;
FreeOrbitController.__cache = {};
Module['FreeOrbitController'] = FreeOrbitController;
FreeOrbitController.prototype["__destroy"] = FreeOrbitController.prototype.__destroy = function() {
    _mud_FreeOrbitController__destroy(this.__ptr);
};
// OrbitControls
function OrbitControls() { throw "cannot construct a OrbitControls, no constructor in IDL" }
OrbitControls.prototype = Object.create(ViewerController.prototype);
OrbitControls.prototype.constructor = OrbitControls;
OrbitControls.prototype.__class = OrbitControls;
OrbitControls.__base = ViewerController;
OrbitControls.__cache = {};
Module['OrbitControls'] = OrbitControls;
OrbitControls.prototype["__destroy"] = OrbitControls.prototype.__destroy = function() {
    _mud_OrbitControls__destroy(this.__ptr);
};
// Viewer
function Viewer() { throw "cannot construct a Viewer, no constructor in IDL" }
Viewer.prototype = Object.create(Widget.prototype);
Viewer.prototype.constructor = Viewer;
Viewer.prototype.__class = Viewer;
Viewer.__base = Widget;
Viewer.__cache = {};
Module['Viewer'] = Viewer;
Object.defineProperty(Viewer.prototype, "scene", {
    get: function() {
        return wrapPointer(_mud_Viewer__get_scene(this.__ptr), Scene);
    },
    set: function(value) {
        _mud_Viewer__set_scene(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Viewer.prototype, "camera", {
    get: function() {
        return wrapPointer(_mud_Viewer__get_camera(this.__ptr), Camera);
    }});
Object.defineProperty(Viewer.prototype, "viewport", {
    get: function() {
        return wrapPointer(_mud_Viewer__get_viewport(this.__ptr), Viewport);
    }});
Object.defineProperty(Viewer.prototype, "position", {
    get: function() {
        return wrapPointer(_mud_Viewer__get_position(this.__ptr), v2_float);
    },
    set: function(value) {
        _mud_Viewer__set_position(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Viewer.prototype, "size", {
    get: function() {
        return wrapPointer(_mud_Viewer__get_size(this.__ptr), v2_float);
    },
    set: function(value) {
        _mud_Viewer__set_size(this.__ptr, value.__ptr);
    }
});
Viewer.prototype["__destroy"] = Viewer.prototype.__destroy = function() {
    _mud_Viewer__destroy(this.__ptr);
};
// SceneViewer
function SceneViewer() { throw "cannot construct a SceneViewer, no constructor in IDL" }
SceneViewer.prototype = Object.create(Viewer.prototype);
SceneViewer.prototype.constructor = SceneViewer;
SceneViewer.prototype.__class = SceneViewer;
SceneViewer.__base = Viewer;
SceneViewer.__cache = {};
Module['SceneViewer'] = SceneViewer;
SceneViewer.prototype["__destroy"] = SceneViewer.prototype.__destroy = function() {
    _mud_SceneViewer__destroy(this.__ptr);
};
// SpaceSheet
function SpaceSheet() { throw "cannot construct a SpaceSheet, no constructor in IDL" }
SpaceSheet.prototype = Object.create(Ui.prototype);
SpaceSheet.prototype.constructor = SpaceSheet;
SpaceSheet.prototype.__class = SpaceSheet;
SpaceSheet.__base = Ui;
SpaceSheet.__cache = {};
Module['SpaceSheet'] = SpaceSheet;
SpaceSheet.prototype["__destroy"] = SpaceSheet.prototype.__destroy = function() {
    _mud_SpaceSheet__destroy(this.__ptr);
};
// TrackballController
function TrackballController() { throw "cannot construct a TrackballController, no constructor in IDL" }
TrackballController.prototype = Object.create(ViewerController.prototype);
TrackballController.prototype.constructor = TrackballController;
TrackballController.prototype.__class = TrackballController;
TrackballController.__base = ViewerController;
TrackballController.__cache = {};
Module['TrackballController'] = TrackballController;
Object.defineProperty(TrackballController.prototype, "rotateSpeed", {
    get: function() {
        return _mud_TrackballController__get_rotateSpeed(this.__ptr);
    },
    set: function(value) {
        _mud_TrackballController__set_rotateSpeed(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "zoomSpeed", {
    get: function() {
        return _mud_TrackballController__get_zoomSpeed(this.__ptr);
    },
    set: function(value) {
        _mud_TrackballController__set_zoomSpeed(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "panSpeed", {
    get: function() {
        return _mud_TrackballController__get_panSpeed(this.__ptr);
    },
    set: function(value) {
        _mud_TrackballController__set_panSpeed(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "staticMoving", {
    get: function() {
        return !!(_mud_TrackballController__get_staticMoving(this.__ptr));
    },
    set: function(value) {
        _mud_TrackballController__set_staticMoving(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "dynamicDampingFactor", {
    get: function() {
        return _mud_TrackballController__get_dynamicDampingFactor(this.__ptr);
    },
    set: function(value) {
        _mud_TrackballController__set_dynamicDampingFactor(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "minDistance", {
    get: function() {
        return _mud_TrackballController__get_minDistance(this.__ptr);
    },
    set: function(value) {
        _mud_TrackballController__set_minDistance(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "maxDistance", {
    get: function() {
        return _mud_TrackballController__get_maxDistance(this.__ptr);
    },
    set: function(value) {
        _mud_TrackballController__set_maxDistance(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "target", {
    get: function() {
        return wrapPointer(_mud_TrackballController__get_target(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_TrackballController__set_target(this.__ptr, value.__ptr);
    }
});
TrackballController.prototype["__destroy"] = TrackballController.prototype.__destroy = function() {
    _mud_TrackballController__destroy(this.__ptr);
};
Module['ui']['viewer'] = function(a0, a1) {
    if (!checkClass(a0, Widget) { throw Error('viewer(0:parent): expected Widget'); } if (!checkClass(a1, Scene) { throw Error('viewer(1:scene): expected Scene'); }
    return wrapPointer(_mud_ui_viewer_2(/*parent*/a0.__ptr, /*scene*/a1.__ptr), Viewer);
};
Module['ui']['scene_viewer'] = function(a0, a1) {
    if (a1 === undefined) { if (!checkClass(a0, Widget) { throw Error('scene_viewer(0:parent): expected Widget'); } }
    else { if (!checkClass(a0, Widget) { throw Error('scene_viewer(0:parent): expected Widget'); } if (!checkClass(a1, v2_float) { throw Error('scene_viewer(1:size): expected v2<float>'); } }
    if (a1 === undefined) { return wrapPointer(_mud_ui_scene_viewer_1(/*parent*/a0.__ptr), SceneViewer); }
    else { return wrapPointer(_mud_ui_scene_viewer_2(/*parent*/a0.__ptr, /*size*/a1.__ptr), SceneViewer); }
};
Module['ui']['trackball_controller'] = function(a0) {
    if (!checkClass(a0, Viewer) { throw Error('trackball_controller(0:viewer): expected Viewer'); }
    return wrapPointer(_mud_ui_trackball_controller_1(/*viewer*/a0.__ptr), TrackballController);
};
Module['ui']['orbit_controls'] = function(a0) {
    if (!checkClass(a0, Viewer) { throw Error('orbit_controls(0:viewer): expected Viewer'); }
    return wrapPointer(_mud_ui_orbit_controls_1(/*viewer*/a0.__ptr), OrbitControls);
};
Module['ui']['orbit_controller'] = function(a0, a1, a2, a3) {
    if (a1 === undefined) { if (!checkClass(a0, Viewer) { throw Error('orbit_controller(0:viewer): expected Viewer'); } }
    else if (a2 === undefined) { if (!checkClass(a0, Viewer) { throw Error('orbit_controller(0:viewer): expected Viewer'); } if (typeof a1 !== 'number') { throw Error('orbit_controller(1:yaw): expected number'); } }
    else if (a3 === undefined) { if (!checkClass(a0, Viewer) { throw Error('orbit_controller(0:viewer): expected Viewer'); } if (typeof a1 !== 'number') { throw Error('orbit_controller(1:yaw): expected number'); } if (typeof a2 !== 'number') { throw Error('orbit_controller(2:pitch): expected number'); } }
    else { if (!checkClass(a0, Viewer) { throw Error('orbit_controller(0:viewer): expected Viewer'); } if (typeof a1 !== 'number') { throw Error('orbit_controller(1:yaw): expected number'); } if (typeof a2 !== 'number') { throw Error('orbit_controller(2:pitch): expected number'); } if (typeof a3 !== 'number') { throw Error('orbit_controller(3:distance): expected number'); } }
    if (a1 === undefined) { return wrapPointer(_mud_ui_orbit_controller_1(/*viewer*/a0.__ptr), OrbitController); }
    else if (a2 === undefined) { return wrapPointer(_mud_ui_orbit_controller_2(/*viewer*/a0.__ptr, /*yaw*/a1), OrbitController); }
    else if (a3 === undefined) { return wrapPointer(_mud_ui_orbit_controller_3(/*viewer*/a0.__ptr, /*yaw*/a1, /*pitch*/a2), OrbitController); }
    else { return wrapPointer(_mud_ui_orbit_controller_4(/*viewer*/a0.__ptr, /*yaw*/a1, /*pitch*/a2, /*distance*/a3), OrbitController); }
};
Module['ui']['free_orbit_controller'] = function(a0) {
    if (!checkClass(a0, Viewer) { throw Error('free_orbit_controller(0:viewer): expected Viewer'); }
    return wrapPointer(_mud_ui_free_orbit_controller_1(/*viewer*/a0.__ptr), FreeOrbitController);
};
Module['ui']['isometric_controller'] = function(a0, a1) {
    if (a1 === undefined) { if (!checkClass(a0, Viewer) { throw Error('isometric_controller(0:viewer): expected Viewer'); } }
    else { if (!checkClass(a0, Viewer) { throw Error('isometric_controller(0:viewer): expected Viewer'); } if (typeof a1 !== 'boolean') { throw Error('isometric_controller(1:topdown): expected boolean'); } }
    if (a1 === undefined) { return wrapPointer(_mud_ui_isometric_controller_1(/*viewer*/a0.__ptr), OrbitController); }
    else { return wrapPointer(_mud_ui_isometric_controller_2(/*viewer*/a0.__ptr, /*topdown*/a1), OrbitController); }
};
Module['ui']['hybrid_controller'] = function(a0, a1, a2, a3, a4, a5) {
    if (a5 === undefined) { if (!checkClass(a0, Viewer) { throw Error('hybrid_controller(0:viewer): expected Viewer'); } if (typeof a1 !== 'number') { throw Error('hybrid_controller(1:mode): expected integer'); } if (!checkClass(a2, Transform) { throw Error('hybrid_controller(2:entity): expected Transform'); } if (typeof a3 !== 'boolean') { throw Error('hybrid_controller(3:aiming): expected boolean'); } if (!checkClass(a4, v2_float) { throw Error('hybrid_controller(4:angles): expected v2<float>'); } }
    else { if (!checkClass(a0, Viewer) { throw Error('hybrid_controller(0:viewer): expected Viewer'); } if (typeof a1 !== 'number') { throw Error('hybrid_controller(1:mode): expected integer'); } if (!checkClass(a2, Transform) { throw Error('hybrid_controller(2:entity): expected Transform'); } if (typeof a3 !== 'boolean') { throw Error('hybrid_controller(3:aiming): expected boolean'); } if (!checkClass(a4, v2_float) { throw Error('hybrid_controller(4:angles): expected v2<float>'); } if (typeof a5 !== 'boolean') { throw Error('hybrid_controller(5:modal): expected boolean'); } }
    if (a5 === undefined) { return wrapPointer(_mud_ui_hybrid_controller_5(/*viewer*/a0.__ptr, /*mode*/a1, /*entity*/a2.__ptr, /*aiming*/a3, /*angles*/a4.__ptr), OrbitController); }
    else { return wrapPointer(_mud_ui_hybrid_controller_6(/*viewer*/a0.__ptr, /*mode*/a1, /*entity*/a2.__ptr, /*aiming*/a3, /*angles*/a4.__ptr, /*modal*/a5), OrbitController); }
};
Module['ui']['velocity_controller'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { if (!checkClass(a0, Viewer) { throw Error('velocity_controller(0:viewer): expected Viewer'); } if (!checkClass(a1, v3_float) { throw Error('velocity_controller(1:linear): expected v3<float>'); } if (!checkClass(a2, v3_float) { throw Error('velocity_controller(2:angular): expected v3<float>'); } }
    else { if (!checkClass(a0, Viewer) { throw Error('velocity_controller(0:viewer): expected Viewer'); } if (!checkClass(a1, v3_float) { throw Error('velocity_controller(1:linear): expected v3<float>'); } if (!checkClass(a2, v3_float) { throw Error('velocity_controller(2:angular): expected v3<float>'); } if (typeof a3 !== 'number') { throw Error('velocity_controller(3:speed): expected number'); } }
    if (a3 === undefined) { _mud_ui_velocity_controller_3(/*viewer*/a0.__ptr, /*linear*/a1.__ptr, /*angular*/a2.__ptr); }
    else { _mud_ui_velocity_controller_4(/*viewer*/a0.__ptr, /*linear*/a1.__ptr, /*angular*/a2.__ptr, /*speed*/a3); }
};

(function() {
    function setup() {
        ViewerController.prototype.__type = _mud_ViewerController__type();
        OrbitController.prototype.__type = _mud_OrbitController__type();
        FreeOrbitController.prototype.__type = _mud_FreeOrbitController__type();
        OrbitControls.prototype.__type = _mud_OrbitControls__type();
        Viewer.prototype.__type = _mud_Viewer__type();
        SceneViewer.prototype.__type = _mud_SceneViewer__type();
        SpaceSheet.prototype.__type = _mud_SpaceSheet__type();
        TrackballController.prototype.__type = _mud_TrackballController__type();
        // OrbitMode
        Module['ui']['OrbitMode'] = Module['ui']['OrbitMode'] || {};
        Module['ui']['OrbitMode']['ThirdPerson'] = _mud_ui_OrbitMode_ThirdPerson();
        Module['ui']['OrbitMode']['Isometric'] = _mud_ui_OrbitMode_Isometric();
        Module['ui']['OrbitMode']['PseudoIsometric'] = _mud_ui_OrbitMode_PseudoIsometric();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
