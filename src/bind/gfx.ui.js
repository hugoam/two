Module['ui'] = Module['ui'] || {};
// SpaceSheet
function SpaceSheet() { throw "cannot construct a SpaceSheet, no constructor in IDL" }
SpaceSheet.prototype = Object.create(Ui.prototype);
SpaceSheet.prototype.constructor = SpaceSheet;
SpaceSheet.prototype.__class = SpaceSheet;
SpaceSheet.__base = Ui;
SpaceSheet.__cache = {};
Module['SpaceSheet'] = SpaceSheet;
SpaceSheet.prototype["__destroy"] = SpaceSheet.prototype.__destroy = function() {
    _two_SpaceSheet__destroy(this.__ptr);
};
// ViewerController
function ViewerController() { throw "cannot construct a ViewerController, no constructor in IDL" }
ViewerController.prototype = Object.create(WrapperObject.prototype);
ViewerController.prototype.constructor = ViewerController;
ViewerController.prototype.__class = ViewerController;
ViewerController.__cache = {};
Module['ViewerController'] = ViewerController;
ViewerController.prototype["__destroy"] = ViewerController.prototype.__destroy = function() {
    _two_ViewerController__destroy(this.__ptr);
};
// Viewer
function Viewer() { throw "cannot construct a Viewer, no constructor in IDL" }
Viewer.prototype = Object.create(WrapperObject.prototype);
Viewer.prototype.constructor = Viewer;
Viewer.prototype.__class = Viewer;
Viewer.__cache = {};
Module['Viewer'] = Viewer;
Object.defineProperty(Viewer.prototype, "scene", {
    get: function() {
        return wrapPointer(_two_Viewer__get_scene(this.__ptr), Scene);
    },
    set: function(value) {
        if (!checkClass(value, Scene)) throw Error('Viewer.scene: expected Scene');
        _two_Viewer__set_scene(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Viewer.prototype, "camera", {
    get: function() {
        return wrapPointer(_two_Viewer__get_camera(this.__ptr), Camera);
    }});
Object.defineProperty(Viewer.prototype, "viewport", {
    get: function() {
        return wrapPointer(_two_Viewer__get_viewport(this.__ptr), Viewport);
    }});
Object.defineProperty(Viewer.prototype, "position", {
    get: function() {
        return wrapPointer(_two_Viewer__get_position(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('Viewer.position: expected v2<float>');
        _two_Viewer__set_position(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Viewer.prototype, "size", {
    get: function() {
        return wrapPointer(_two_Viewer__get_size(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('Viewer.size: expected v2<float>');
        _two_Viewer__set_size(this.__ptr, value.__ptr);
    }
});
Viewer.prototype["__destroy"] = Viewer.prototype.__destroy = function() {
    _two_Viewer__destroy(this.__ptr);
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
    _two_SceneViewer__destroy(this.__ptr);
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
    if (!checkClass(a0, quat)) throw Error('set_eye(0:rotation): expected quat');
    _two_OrbitController_set_eye_1(this.__ptr, /*rotation*/a0.__ptr);
};
OrbitController.prototype["set_target"] = OrbitController.prototype.set_target = function(a0) {
    if (!checkClass(a0, v3_float)) throw Error('set_target(0:position): expected v3<float>');
    _two_OrbitController_set_target_1(this.__ptr, /*position*/a0.__ptr);
};
Object.defineProperty(OrbitController.prototype, "position", {
    get: function() {
        return wrapPointer(_two_OrbitController__get_position(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('OrbitController.position: expected v3<float>');
        _two_OrbitController__set_position(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(OrbitController.prototype, "yaw", {
    get: function() {
        return _two_OrbitController__get_yaw(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('OrbitController.yaw: expected number');
        _two_OrbitController__set_yaw(this.__ptr, value);
    }
});
Object.defineProperty(OrbitController.prototype, "pitch", {
    get: function() {
        return _two_OrbitController__get_pitch(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('OrbitController.pitch: expected number');
        _two_OrbitController__set_pitch(this.__ptr, value);
    }
});
Object.defineProperty(OrbitController.prototype, "distance", {
    get: function() {
        return _two_OrbitController__get_distance(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('OrbitController.distance: expected number');
        _two_OrbitController__set_distance(this.__ptr, value);
    }
});
OrbitController.prototype["__destroy"] = OrbitController.prototype.__destroy = function() {
    _two_OrbitController__destroy(this.__ptr);
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
        return _two_TrackballController__get_rotateSpeed(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('TrackballController.rotateSpeed: expected number');
        _two_TrackballController__set_rotateSpeed(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "zoomSpeed", {
    get: function() {
        return _two_TrackballController__get_zoomSpeed(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('TrackballController.zoomSpeed: expected number');
        _two_TrackballController__set_zoomSpeed(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "panSpeed", {
    get: function() {
        return _two_TrackballController__get_panSpeed(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('TrackballController.panSpeed: expected number');
        _two_TrackballController__set_panSpeed(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "staticMoving", {
    get: function() {
        return !!(_two_TrackballController__get_staticMoving(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('TrackballController.staticMoving: expected boolean');
        _two_TrackballController__set_staticMoving(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "dynamicDampingFactor", {
    get: function() {
        return _two_TrackballController__get_dynamicDampingFactor(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('TrackballController.dynamicDampingFactor: expected number');
        _two_TrackballController__set_dynamicDampingFactor(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "minDistance", {
    get: function() {
        return _two_TrackballController__get_minDistance(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('TrackballController.minDistance: expected number');
        _two_TrackballController__set_minDistance(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "maxDistance", {
    get: function() {
        return _two_TrackballController__get_maxDistance(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('TrackballController.maxDistance: expected number');
        _two_TrackballController__set_maxDistance(this.__ptr, value);
    }
});
Object.defineProperty(TrackballController.prototype, "target", {
    get: function() {
        return wrapPointer(_two_TrackballController__get_target(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('TrackballController.target: expected v3<float>');
        _two_TrackballController__set_target(this.__ptr, value.__ptr);
    }
});
TrackballController.prototype["__destroy"] = TrackballController.prototype.__destroy = function() {
    _two_TrackballController__destroy(this.__ptr);
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
    _two_OrbitControls__destroy(this.__ptr);
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
    _two_FreeOrbitController__destroy(this.__ptr);
};
// ViewerBox
function ViewerBox() {
    this.__ptr = _two_ViewerBox__construct_0(); getCache(ViewerBox)[this.__ptr] = this;
};
ViewerBox.prototype = Object.create(WrapperObject.prototype);
ViewerBox.prototype.constructor = ViewerBox;
ViewerBox.prototype.__class = ViewerBox;
ViewerBox.__cache = {};
Module['ViewerBox'] = ViewerBox;
Object.defineProperty(ViewerBox.prototype, "self", {
    get: function() {
        return wrapPointer(_two_ViewerBox__get_self(this.__ptr), Widget);
    },
    set: function(value) {
        if (!checkClass(value, Widget)) throw Error('ViewerBox.self: expected Widget');
        _two_ViewerBox__set_self(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ViewerBox.prototype, "viewer", {
    get: function() {
        return wrapPointer(_two_ViewerBox__get_viewer(this.__ptr), Viewer);
    },
    set: function(value) {
        if (!checkClass(value, Viewer)) throw Error('ViewerBox.viewer: expected Viewer');
        _two_ViewerBox__set_viewer(this.__ptr, value.__ptr);
    }
});
ViewerBox.prototype["__destroy"] = ViewerBox.prototype.__destroy = function() {
    _two_ViewerBox__destroy(this.__ptr);
};
// SceneViewerBox
function SceneViewerBox() {
    this.__ptr = _two_SceneViewerBox__construct_0(); getCache(SceneViewerBox)[this.__ptr] = this;
};
SceneViewerBox.prototype = Object.create(WrapperObject.prototype);
SceneViewerBox.prototype.constructor = SceneViewerBox;
SceneViewerBox.prototype.__class = SceneViewerBox;
SceneViewerBox.__cache = {};
Module['SceneViewerBox'] = SceneViewerBox;
Object.defineProperty(SceneViewerBox.prototype, "self", {
    get: function() {
        return wrapPointer(_two_SceneViewerBox__get_self(this.__ptr), Widget);
    },
    set: function(value) {
        if (!checkClass(value, Widget)) throw Error('SceneViewerBox.self: expected Widget');
        _two_SceneViewerBox__set_self(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(SceneViewerBox.prototype, "viewer", {
    get: function() {
        return wrapPointer(_two_SceneViewerBox__get_viewer(this.__ptr), SceneViewer);
    },
    set: function(value) {
        if (!checkClass(value, SceneViewer)) throw Error('SceneViewerBox.viewer: expected SceneViewer');
        _two_SceneViewerBox__set_viewer(this.__ptr, value.__ptr);
    }
});
SceneViewerBox.prototype["__destroy"] = SceneViewerBox.prototype.__destroy = function() {
    _two_SceneViewerBox__destroy(this.__ptr);
};
Module['ui']['viewer'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('viewer(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('viewer(1:parent): expected Widget'); if (!checkClass(a2, Scene)) throw Error('viewer(2:scene): expected Scene');
    return wrapPointer(_two_ui_viewer_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*scene*/a2.__ptr), ViewerBox);
};
Module['ui']['scene_viewer'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('scene_viewer(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('scene_viewer(1:parent): expected Widget'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('scene_viewer(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('scene_viewer(1:parent): expected Widget'); if (!checkClass(a2, v2_float)) throw Error('scene_viewer(2:size): expected v2<float>'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_scene_viewer_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), SceneViewerBox); }
    else { return wrapPointer(_two_ui_scene_viewer_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*size*/a2.__ptr), SceneViewerBox); }
};
Module['ui']['trackball_controller'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('trackball_controller(0:self): expected Widget'); if (!checkClass(a1, Viewer)) throw Error('trackball_controller(1:viewer): expected Viewer');
    return wrapPointer(_two_ui_trackball_controller_2(/*self*/a0.__ptr, /*viewer*/a1.__ptr), TrackballController);
};
Module['ui']['orbit_controls'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('orbit_controls(0:self): expected Widget'); if (!checkClass(a1, Viewer)) throw Error('orbit_controls(1:viewer): expected Viewer');
    return wrapPointer(_two_ui_orbit_controls_2(/*self*/a0.__ptr, /*viewer*/a1.__ptr), OrbitControls);
};
Module['ui']['orbit_controller'] = function(a0, a1, a2, a3, a4) {
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('orbit_controller(0:self): expected Widget'); if (!checkClass(a1, Viewer)) throw Error('orbit_controller(1:viewer): expected Viewer'); }
    else if (a3 === undefined) { if (!checkClass(a0, Widget)) throw Error('orbit_controller(0:self): expected Widget'); if (!checkClass(a1, Viewer)) throw Error('orbit_controller(1:viewer): expected Viewer'); if (typeof a2 !== 'number') throw Error('orbit_controller(2:yaw): expected number'); }
    else if (a4 === undefined) { if (!checkClass(a0, Widget)) throw Error('orbit_controller(0:self): expected Widget'); if (!checkClass(a1, Viewer)) throw Error('orbit_controller(1:viewer): expected Viewer'); if (typeof a2 !== 'number') throw Error('orbit_controller(2:yaw): expected number'); if (typeof a3 !== 'number') throw Error('orbit_controller(3:pitch): expected number'); }
    else { if (!checkClass(a0, Widget)) throw Error('orbit_controller(0:self): expected Widget'); if (!checkClass(a1, Viewer)) throw Error('orbit_controller(1:viewer): expected Viewer'); if (typeof a2 !== 'number') throw Error('orbit_controller(2:yaw): expected number'); if (typeof a3 !== 'number') throw Error('orbit_controller(3:pitch): expected number'); if (typeof a4 !== 'number') throw Error('orbit_controller(4:distance): expected number'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_orbit_controller_2(/*self*/a0.__ptr, /*viewer*/a1.__ptr), OrbitController); }
    else if (a3 === undefined) { return wrapPointer(_two_ui_orbit_controller_3(/*self*/a0.__ptr, /*viewer*/a1.__ptr, /*yaw*/a2), OrbitController); }
    else if (a4 === undefined) { return wrapPointer(_two_ui_orbit_controller_4(/*self*/a0.__ptr, /*viewer*/a1.__ptr, /*yaw*/a2, /*pitch*/a3), OrbitController); }
    else { return wrapPointer(_two_ui_orbit_controller_5(/*self*/a0.__ptr, /*viewer*/a1.__ptr, /*yaw*/a2, /*pitch*/a3, /*distance*/a4), OrbitController); }
};
Module['ui']['free_orbit_controller'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('free_orbit_controller(0:self): expected Widget'); if (!checkClass(a1, Viewer)) throw Error('free_orbit_controller(1:viewer): expected Viewer');
    return wrapPointer(_two_ui_free_orbit_controller_2(/*self*/a0.__ptr, /*viewer*/a1.__ptr), FreeOrbitController);
};
Module['ui']['isometric_controller'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('isometric_controller(0:self): expected Widget'); if (!checkClass(a1, Viewer)) throw Error('isometric_controller(1:viewer): expected Viewer'); }
    else { if (!checkClass(a0, Widget)) throw Error('isometric_controller(0:self): expected Widget'); if (!checkClass(a1, Viewer)) throw Error('isometric_controller(1:viewer): expected Viewer'); if (typeof a2 !== 'boolean') throw Error('isometric_controller(2:topdown): expected boolean'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_isometric_controller_2(/*self*/a0.__ptr, /*viewer*/a1.__ptr), OrbitController); }
    else { return wrapPointer(_two_ui_isometric_controller_3(/*self*/a0.__ptr, /*viewer*/a1.__ptr, /*topdown*/a2), OrbitController); }
};
Module['ui']['hybrid_controller'] = function(a0, a1, a2, a3, a4, a5, a6) {
    if (a6 === undefined) { if (!checkClass(a0, Widget)) throw Error('hybrid_controller(0:self): expected Widget'); if (!checkClass(a1, Viewer)) throw Error('hybrid_controller(1:viewer): expected Viewer'); if (typeof a2 !== 'number') throw Error('hybrid_controller(2:mode): expected integer'); if (!checkClass(a3, Transform)) throw Error('hybrid_controller(3:entity): expected Transform'); if (typeof a4 !== 'boolean') throw Error('hybrid_controller(4:aiming): expected boolean'); if (!checkClass(a5, v2_float)) throw Error('hybrid_controller(5:angles): expected v2<float>'); }
    else { if (!checkClass(a0, Widget)) throw Error('hybrid_controller(0:self): expected Widget'); if (!checkClass(a1, Viewer)) throw Error('hybrid_controller(1:viewer): expected Viewer'); if (typeof a2 !== 'number') throw Error('hybrid_controller(2:mode): expected integer'); if (!checkClass(a3, Transform)) throw Error('hybrid_controller(3:entity): expected Transform'); if (typeof a4 !== 'boolean') throw Error('hybrid_controller(4:aiming): expected boolean'); if (!checkClass(a5, v2_float)) throw Error('hybrid_controller(5:angles): expected v2<float>'); if (typeof a6 !== 'boolean') throw Error('hybrid_controller(6:modal): expected boolean'); }
    if (a6 === undefined) { return wrapPointer(_two_ui_hybrid_controller_6(/*self*/a0.__ptr, /*viewer*/a1.__ptr, /*mode*/a2, /*entity*/a3.__ptr, /*aiming*/a4, /*angles*/a5.__ptr), OrbitController); }
    else { return wrapPointer(_two_ui_hybrid_controller_7(/*self*/a0.__ptr, /*viewer*/a1.__ptr, /*mode*/a2, /*entity*/a3.__ptr, /*aiming*/a4, /*angles*/a5.__ptr, /*modal*/a6), OrbitController); }
};
Module['ui']['velocity_controller'] = function(a0, a1, a2, a3, a4) {
    if (a4 === undefined) { if (!checkClass(a0, Widget)) throw Error('velocity_controller(0:self): expected Widget'); if (!checkClass(a1, Viewer)) throw Error('velocity_controller(1:viewer): expected Viewer'); if (!checkClass(a2, v3_float)) throw Error('velocity_controller(2:linear): expected v3<float>'); if (!checkClass(a3, v3_float)) throw Error('velocity_controller(3:angular): expected v3<float>'); }
    else { if (!checkClass(a0, Widget)) throw Error('velocity_controller(0:self): expected Widget'); if (!checkClass(a1, Viewer)) throw Error('velocity_controller(1:viewer): expected Viewer'); if (!checkClass(a2, v3_float)) throw Error('velocity_controller(2:linear): expected v3<float>'); if (!checkClass(a3, v3_float)) throw Error('velocity_controller(3:angular): expected v3<float>'); if (typeof a4 !== 'number') throw Error('velocity_controller(4:speed): expected number'); }
    if (a4 === undefined) { _two_ui_velocity_controller_4(/*self*/a0.__ptr, /*viewer*/a1.__ptr, /*linear*/a2.__ptr, /*angular*/a3.__ptr); }
    else { _two_ui_velocity_controller_5(/*self*/a0.__ptr, /*viewer*/a1.__ptr, /*linear*/a2.__ptr, /*angular*/a3.__ptr, /*speed*/a4); }
};

(function() {
    function setup() {
        SpaceSheet.prototype.__type = _two_SpaceSheet__type();
        ViewerController.prototype.__type = _two_ViewerController__type();
        Viewer.prototype.__type = _two_Viewer__type();
        SceneViewer.prototype.__type = _two_SceneViewer__type();
        OrbitController.prototype.__type = _two_OrbitController__type();
        TrackballController.prototype.__type = _two_TrackballController__type();
        OrbitControls.prototype.__type = _two_OrbitControls__type();
        FreeOrbitController.prototype.__type = _two_FreeOrbitController__type();
        ViewerBox.prototype.__type = _two_ViewerBox__type();
        SceneViewerBox.prototype.__type = _two_SceneViewerBox__type();
        // OrbitMode
        Module['ui']['OrbitMode'] = Module['ui']['OrbitMode'] || {};
        Module['ui']['OrbitMode']['ThirdPerson'] = _two_ui_OrbitMode_ThirdPerson();
        Module['ui']['OrbitMode']['Isometric'] = _two_ui_OrbitMode_Isometric();
        Module['ui']['OrbitMode']['PseudoIsometric'] = _two_ui_OrbitMode_PseudoIsometric();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
