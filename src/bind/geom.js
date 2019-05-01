Module['stl'] = Module['stl'] || {};
// Aabb
function Aabb(a0, a1) {
    if (a0 === undefined) {  }
    else { if (!checkClass(a0, v3_float)) throw Error('Aabb(0:center): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('Aabb(1:extents): expected v3<float>'); }
    if (a0 === undefined) { this.__ptr = _mud_Aabb__construct_0(); getCache(Aabb)[this.__ptr] = this; }
    else { this.__ptr = _mud_Aabb__construct_2(/*center*/a0.__ptr, /*extents*/a1.__ptr); getCache(Aabb)[this.__ptr] = this; }
};
Aabb.prototype = Object.create(WrapperObject.prototype);
Aabb.prototype.constructor = Aabb;
Aabb.prototype.__class = Aabb;
Aabb.__cache = {};
Module['Aabb'] = Aabb;
Object.defineProperty(Aabb.prototype, "center", {
    get: function() {
        return wrapPointer(_mud_Aabb__get_center(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Aabb.center: expected v3<float>');
        _mud_Aabb__set_center(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Aabb.prototype, "extents", {
    get: function() {
        return wrapPointer(_mud_Aabb__get_extents(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Aabb.extents: expected v3<float>');
        _mud_Aabb__set_extents(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Aabb.prototype, "empty", {
    get: function() {
        return !!(_mud_Aabb__get_empty(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Aabb.empty: expected boolean');
        _mud_Aabb__set_empty(this.__ptr, value);
    }
});
Aabb.prototype["__destroy"] = Aabb.prototype.__destroy = function() {
    _mud_Aabb__destroy(this.__ptr);
};
// Curve2
function Curve2() { throw "cannot construct a Curve2, no constructor in IDL" }
Curve2.prototype = Object.create(WrapperObject.prototype);
Curve2.prototype.constructor = Curve2;
Curve2.prototype.__class = Curve2;
Curve2.__cache = {};
Module['Curve2'] = Curve2;
Curve2.prototype["point"] = Curve2.prototype.point = function(a0) {
    if (typeof a0 !== 'number') throw Error('point(0:t): expected number');
    return wrapPointer(_mud_Curve2_point_1(this.__ptr, /*t*/a0), v2_float);
};
Curve2.prototype["__destroy"] = Curve2.prototype.__destroy = function() {
    _mud_Curve2__destroy(this.__ptr);
};
// Curve3
function Curve3() { throw "cannot construct a Curve3, no constructor in IDL" }
Curve3.prototype = Object.create(WrapperObject.prototype);
Curve3.prototype.constructor = Curve3;
Curve3.prototype.__class = Curve3;
Curve3.__cache = {};
Module['Curve3'] = Curve3;
Curve3.prototype["point"] = Curve3.prototype.point = function(a0) {
    if (typeof a0 !== 'number') throw Error('point(0:t): expected number');
    return wrapPointer(_mud_Curve3_point_1(this.__ptr, /*t*/a0), v3_float);
};
Curve3.prototype["__destroy"] = Curve3.prototype.__destroy = function() {
    _mud_Curve3__destroy(this.__ptr);
};
// CurveSpline
function CurveSpline() {
    
    this.__ptr = _mud_CurveSpline__construct_0(); getCache(CurveSpline)[this.__ptr] = this;
};
CurveSpline.prototype = Object.create(Curve2.prototype);
CurveSpline.prototype.constructor = CurveSpline;
CurveSpline.prototype.__class = CurveSpline;
CurveSpline.__base = Curve2;
CurveSpline.__cache = {};
Module['CurveSpline'] = CurveSpline;
Object.defineProperty(CurveSpline.prototype, "points", {
    get: function() {
        return _mud_CurveSpline__get_points(this.__ptr);
    }});
CurveSpline.prototype["__destroy"] = CurveSpline.prototype.__destroy = function() {
    _mud_CurveSpline__destroy(this.__ptr);
};
// CurveSpline3
function CurveSpline3() {
    
    this.__ptr = _mud_CurveSpline3__construct_0(); getCache(CurveSpline3)[this.__ptr] = this;
};
CurveSpline3.prototype = Object.create(Curve3.prototype);
CurveSpline3.prototype.constructor = CurveSpline3;
CurveSpline3.prototype.__class = CurveSpline3;
CurveSpline3.__base = Curve3;
CurveSpline3.__cache = {};
Module['CurveSpline3'] = CurveSpline3;
Object.defineProperty(CurveSpline3.prototype, "points", {
    get: function() {
        return _mud_CurveSpline3__get_points(this.__ptr);
    }});
CurveSpline3.prototype["__destroy"] = CurveSpline3.prototype.__destroy = function() {
    _mud_CurveSpline3__destroy(this.__ptr);
};
// CurveBezierCubic
function CurveBezierCubic() {
    
    this.__ptr = _mud_CurveBezierCubic__construct_0(); getCache(CurveBezierCubic)[this.__ptr] = this;
};
CurveBezierCubic.prototype = Object.create(Curve2.prototype);
CurveBezierCubic.prototype.constructor = CurveBezierCubic;
CurveBezierCubic.prototype.__class = CurveBezierCubic;
CurveBezierCubic.__base = Curve2;
CurveBezierCubic.__cache = {};
Module['CurveBezierCubic'] = CurveBezierCubic;
Object.defineProperty(CurveBezierCubic.prototype, "v0", {
    get: function() {
        return wrapPointer(_mud_CurveBezierCubic__get_v0(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('CurveBezierCubic.v0: expected v2<float>');
        _mud_CurveBezierCubic__set_v0(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(CurveBezierCubic.prototype, "v1", {
    get: function() {
        return wrapPointer(_mud_CurveBezierCubic__get_v1(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('CurveBezierCubic.v1: expected v2<float>');
        _mud_CurveBezierCubic__set_v1(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(CurveBezierCubic.prototype, "v2", {
    get: function() {
        return wrapPointer(_mud_CurveBezierCubic__get_v2(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('CurveBezierCubic.v2: expected v2<float>');
        _mud_CurveBezierCubic__set_v2(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(CurveBezierCubic.prototype, "v3", {
    get: function() {
        return wrapPointer(_mud_CurveBezierCubic__get_v3(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('CurveBezierCubic.v3: expected v2<float>');
        _mud_CurveBezierCubic__set_v3(this.__ptr, value.__ptr);
    }
});
CurveBezierCubic.prototype["__destroy"] = CurveBezierCubic.prototype.__destroy = function() {
    _mud_CurveBezierCubic__destroy(this.__ptr);
};
// CurveBezierCubic3
function CurveBezierCubic3() {
    
    this.__ptr = _mud_CurveBezierCubic3__construct_0(); getCache(CurveBezierCubic3)[this.__ptr] = this;
};
CurveBezierCubic3.prototype = Object.create(Curve3.prototype);
CurveBezierCubic3.prototype.constructor = CurveBezierCubic3;
CurveBezierCubic3.prototype.__class = CurveBezierCubic3;
CurveBezierCubic3.__base = Curve3;
CurveBezierCubic3.__cache = {};
Module['CurveBezierCubic3'] = CurveBezierCubic3;
Object.defineProperty(CurveBezierCubic3.prototype, "v0", {
    get: function() {
        return wrapPointer(_mud_CurveBezierCubic3__get_v0(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('CurveBezierCubic3.v0: expected v3<float>');
        _mud_CurveBezierCubic3__set_v0(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(CurveBezierCubic3.prototype, "v1", {
    get: function() {
        return wrapPointer(_mud_CurveBezierCubic3__get_v1(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('CurveBezierCubic3.v1: expected v3<float>');
        _mud_CurveBezierCubic3__set_v1(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(CurveBezierCubic3.prototype, "v2", {
    get: function() {
        return wrapPointer(_mud_CurveBezierCubic3__get_v2(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('CurveBezierCubic3.v2: expected v3<float>');
        _mud_CurveBezierCubic3__set_v2(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(CurveBezierCubic3.prototype, "v3", {
    get: function() {
        return wrapPointer(_mud_CurveBezierCubic3__get_v3(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('CurveBezierCubic3.v3: expected v3<float>');
        _mud_CurveBezierCubic3__set_v3(this.__ptr, value.__ptr);
    }
});
CurveBezierCubic3.prototype["__destroy"] = CurveBezierCubic3.prototype.__destroy = function() {
    _mud_CurveBezierCubic3__destroy(this.__ptr);
};
// CurveLine
function CurveLine() {
    
    this.__ptr = _mud_CurveLine__construct_0(); getCache(CurveLine)[this.__ptr] = this;
};
CurveLine.prototype = Object.create(Curve2.prototype);
CurveLine.prototype.constructor = CurveLine;
CurveLine.prototype.__class = CurveLine;
CurveLine.__base = Curve2;
CurveLine.__cache = {};
Module['CurveLine'] = CurveLine;
Object.defineProperty(CurveLine.prototype, "v0", {
    get: function() {
        return wrapPointer(_mud_CurveLine__get_v0(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('CurveLine.v0: expected v2<float>');
        _mud_CurveLine__set_v0(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(CurveLine.prototype, "v1", {
    get: function() {
        return wrapPointer(_mud_CurveLine__get_v1(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('CurveLine.v1: expected v2<float>');
        _mud_CurveLine__set_v1(this.__ptr, value.__ptr);
    }
});
CurveLine.prototype["__destroy"] = CurveLine.prototype.__destroy = function() {
    _mud_CurveLine__destroy(this.__ptr);
};
// CurveLine3
function CurveLine3() {
    
    this.__ptr = _mud_CurveLine3__construct_0(); getCache(CurveLine3)[this.__ptr] = this;
};
CurveLine3.prototype = Object.create(Curve3.prototype);
CurveLine3.prototype.constructor = CurveLine3;
CurveLine3.prototype.__class = CurveLine3;
CurveLine3.__base = Curve3;
CurveLine3.__cache = {};
Module['CurveLine3'] = CurveLine3;
Object.defineProperty(CurveLine3.prototype, "v0", {
    get: function() {
        return wrapPointer(_mud_CurveLine3__get_v0(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('CurveLine3.v0: expected v3<float>');
        _mud_CurveLine3__set_v0(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(CurveLine3.prototype, "v1", {
    get: function() {
        return wrapPointer(_mud_CurveLine3__get_v1(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('CurveLine3.v1: expected v3<float>');
        _mud_CurveLine3__set_v1(this.__ptr, value.__ptr);
    }
});
CurveLine3.prototype["__destroy"] = CurveLine3.prototype.__destroy = function() {
    _mud_CurveLine3__destroy(this.__ptr);
};
// CurveBezierQuadratic
function CurveBezierQuadratic() {
    
    this.__ptr = _mud_CurveBezierQuadratic__construct_0(); getCache(CurveBezierQuadratic)[this.__ptr] = this;
};
CurveBezierQuadratic.prototype = Object.create(Curve2.prototype);
CurveBezierQuadratic.prototype.constructor = CurveBezierQuadratic;
CurveBezierQuadratic.prototype.__class = CurveBezierQuadratic;
CurveBezierQuadratic.__base = Curve2;
CurveBezierQuadratic.__cache = {};
Module['CurveBezierQuadratic'] = CurveBezierQuadratic;
Object.defineProperty(CurveBezierQuadratic.prototype, "v0", {
    get: function() {
        return wrapPointer(_mud_CurveBezierQuadratic__get_v0(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('CurveBezierQuadratic.v0: expected v2<float>');
        _mud_CurveBezierQuadratic__set_v0(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(CurveBezierQuadratic.prototype, "v1", {
    get: function() {
        return wrapPointer(_mud_CurveBezierQuadratic__get_v1(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('CurveBezierQuadratic.v1: expected v2<float>');
        _mud_CurveBezierQuadratic__set_v1(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(CurveBezierQuadratic.prototype, "v2", {
    get: function() {
        return wrapPointer(_mud_CurveBezierQuadratic__get_v2(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('CurveBezierQuadratic.v2: expected v2<float>');
        _mud_CurveBezierQuadratic__set_v2(this.__ptr, value.__ptr);
    }
});
CurveBezierQuadratic.prototype["__destroy"] = CurveBezierQuadratic.prototype.__destroy = function() {
    _mud_CurveBezierQuadratic__destroy(this.__ptr);
};
// CurveBezierQuadratic3
function CurveBezierQuadratic3() {
    
    this.__ptr = _mud_CurveBezierQuadratic3__construct_0(); getCache(CurveBezierQuadratic3)[this.__ptr] = this;
};
CurveBezierQuadratic3.prototype = Object.create(Curve3.prototype);
CurveBezierQuadratic3.prototype.constructor = CurveBezierQuadratic3;
CurveBezierQuadratic3.prototype.__class = CurveBezierQuadratic3;
CurveBezierQuadratic3.__base = Curve3;
CurveBezierQuadratic3.__cache = {};
Module['CurveBezierQuadratic3'] = CurveBezierQuadratic3;
Object.defineProperty(CurveBezierQuadratic3.prototype, "v0", {
    get: function() {
        return wrapPointer(_mud_CurveBezierQuadratic3__get_v0(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('CurveBezierQuadratic3.v0: expected v3<float>');
        _mud_CurveBezierQuadratic3__set_v0(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(CurveBezierQuadratic3.prototype, "v1", {
    get: function() {
        return wrapPointer(_mud_CurveBezierQuadratic3__get_v1(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('CurveBezierQuadratic3.v1: expected v3<float>');
        _mud_CurveBezierQuadratic3__set_v1(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(CurveBezierQuadratic3.prototype, "v2", {
    get: function() {
        return wrapPointer(_mud_CurveBezierQuadratic3__get_v2(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('CurveBezierQuadratic3.v2: expected v3<float>');
        _mud_CurveBezierQuadratic3__set_v2(this.__ptr, value.__ptr);
    }
});
CurveBezierQuadratic3.prototype["__destroy"] = CurveBezierQuadratic3.prototype.__destroy = function() {
    _mud_CurveBezierQuadratic3__destroy(this.__ptr);
};
// CurveCatmullRom3
function CurveCatmullRom3() {
    
    this.__ptr = _mud_CurveCatmullRom3__construct_0(); getCache(CurveCatmullRom3)[this.__ptr] = this;
};
CurveCatmullRom3.prototype = Object.create(Curve3.prototype);
CurveCatmullRom3.prototype.constructor = CurveCatmullRom3;
CurveCatmullRom3.prototype.__class = CurveCatmullRom3;
CurveCatmullRom3.__base = Curve3;
CurveCatmullRom3.__cache = {};
Module['CurveCatmullRom3'] = CurveCatmullRom3;
CurveCatmullRom3.prototype["add_point"] = CurveCatmullRom3.prototype.add_point = function(a0) {
    if (!checkClass(a0, v3_float)) throw Error('add_point(0:point): expected v3<float>');
    _mud_CurveCatmullRom3_add_point_1(this.__ptr, /*point*/a0.__ptr);
};
Object.defineProperty(CurveCatmullRom3.prototype, "points", {
    get: function() {
        return _mud_CurveCatmullRom3__get_points(this.__ptr);
    }});
Object.defineProperty(CurveCatmullRom3.prototype, "closed", {
    get: function() {
        return !!(_mud_CurveCatmullRom3__get_closed(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('CurveCatmullRom3.closed: expected boolean');
        _mud_CurveCatmullRom3__set_closed(this.__ptr, value);
    }
});
Object.defineProperty(CurveCatmullRom3.prototype, "curve_type", {
    get: function() {
        return _mud_CurveCatmullRom3__get_curve_type(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('CurveCatmullRom3.curve_type: expected integer');
        _mud_CurveCatmullRom3__set_curve_type(this.__ptr, value);
    }
});
Object.defineProperty(CurveCatmullRom3.prototype, "tension", {
    get: function() {
        return _mud_CurveCatmullRom3__get_tension(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('CurveCatmullRom3.tension: expected number');
        _mud_CurveCatmullRom3__set_tension(this.__ptr, value);
    }
});
CurveCatmullRom3.prototype["__destroy"] = CurveCatmullRom3.prototype.__destroy = function() {
    _mud_CurveCatmullRom3__destroy(this.__ptr);
};
// Plane
function Plane() {
    
    this.__ptr = _mud_Plane__construct_0(); getCache(Plane)[this.__ptr] = this;
};
Plane.prototype = Object.create(WrapperObject.prototype);
Plane.prototype.constructor = Plane;
Plane.prototype.__class = Plane;
Plane.__cache = {};
Module['Plane'] = Plane;
Object.defineProperty(Plane.prototype, "normal", {
    get: function() {
        return wrapPointer(_mud_Plane__get_normal(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Plane.normal: expected v3<float>');
        _mud_Plane__set_normal(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Plane.prototype, "distance", {
    get: function() {
        return _mud_Plane__get_distance(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Plane.distance: expected number');
        _mud_Plane__set_distance(this.__ptr, value);
    }
});
Plane.prototype["__destroy"] = Plane.prototype.__destroy = function() {
    _mud_Plane__destroy(this.__ptr);
};
// Plane3
function Plane3() {
    
    this.__ptr = _mud_Plane3__construct_0(); getCache(Plane3)[this.__ptr] = this;
};
Plane3.prototype = Object.create(WrapperObject.prototype);
Plane3.prototype.constructor = Plane3;
Plane3.prototype.__class = Plane3;
Plane3.__cache = {};
Module['Plane3'] = Plane3;
Object.defineProperty(Plane3.prototype, "origin", {
    get: function() {
        return wrapPointer(_mud_Plane3__get_origin(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Plane3.origin: expected v3<float>');
        _mud_Plane3__set_origin(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Plane3.prototype, "a", {
    get: function() {
        return wrapPointer(_mud_Plane3__get_a(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Plane3.a: expected v3<float>');
        _mud_Plane3__set_a(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Plane3.prototype, "b", {
    get: function() {
        return wrapPointer(_mud_Plane3__get_b(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Plane3.b: expected v3<float>');
        _mud_Plane3__set_b(this.__ptr, value.__ptr);
    }
});
Plane3.prototype["__destroy"] = Plane3.prototype.__destroy = function() {
    _mud_Plane3__destroy(this.__ptr);
};
// Face3
function Face3() {
    
    this.__ptr = _mud_Face3__construct_0(); getCache(Face3)[this.__ptr] = this;
};
Face3.prototype = Object.create(WrapperObject.prototype);
Face3.prototype.constructor = Face3;
Face3.prototype.__class = Face3;
Face3.__cache = {};
Module['Face3'] = Face3;
Face3.prototype["__destroy"] = Face3.prototype.__destroy = function() {
    _mud_Face3__destroy(this.__ptr);
};
// Segment
function Segment() {
    
    this.__ptr = _mud_Segment__construct_0(); getCache(Segment)[this.__ptr] = this;
};
Segment.prototype = Object.create(WrapperObject.prototype);
Segment.prototype.constructor = Segment;
Segment.prototype.__class = Segment;
Segment.__cache = {};
Module['Segment'] = Segment;
Object.defineProperty(Segment.prototype, "start", {
    get: function() {
        return wrapPointer(_mud_Segment__get_start(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Segment.start: expected v3<float>');
        _mud_Segment__set_start(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Segment.prototype, "end", {
    get: function() {
        return wrapPointer(_mud_Segment__get_end(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Segment.end: expected v3<float>');
        _mud_Segment__set_end(this.__ptr, value.__ptr);
    }
});
Segment.prototype["__destroy"] = Segment.prototype.__destroy = function() {
    _mud_Segment__destroy(this.__ptr);
};
// Ray
function Ray() {
    
    this.__ptr = _mud_Ray__construct_0(); getCache(Ray)[this.__ptr] = this;
};
Ray.prototype = Object.create(WrapperObject.prototype);
Ray.prototype.constructor = Ray;
Ray.prototype.__class = Ray;
Ray.__cache = {};
Module['Ray'] = Ray;
Object.defineProperty(Ray.prototype, "start", {
    get: function() {
        return wrapPointer(_mud_Ray__get_start(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Ray.start: expected v3<float>');
        _mud_Ray__set_start(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Ray.prototype, "end", {
    get: function() {
        return wrapPointer(_mud_Ray__get_end(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Ray.end: expected v3<float>');
        _mud_Ray__set_end(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Ray.prototype, "dir", {
    get: function() {
        return wrapPointer(_mud_Ray__get_dir(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Ray.dir: expected v3<float>');
        _mud_Ray__set_dir(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Ray.prototype, "inv_dir", {
    get: function() {
        return wrapPointer(_mud_Ray__get_inv_dir(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Ray.inv_dir: expected v3<float>');
        _mud_Ray__set_inv_dir(this.__ptr, value.__ptr);
    }
});
Ray.prototype["__destroy"] = Ray.prototype.__destroy = function() {
    _mud_Ray__destroy(this.__ptr);
};
// MeshAdapter
function MeshAdapter() {
    
    this.__ptr = _mud_MeshAdapter__construct_0(); getCache(MeshAdapter)[this.__ptr] = this;
};
MeshAdapter.prototype = Object.create(WrapperObject.prototype);
MeshAdapter.prototype.constructor = MeshAdapter;
MeshAdapter.prototype.__class = MeshAdapter;
MeshAdapter.__cache = {};
Module['MeshAdapter'] = MeshAdapter;
MeshAdapter.prototype["rewind"] = MeshAdapter.prototype.rewind = function() {
    
    _mud_MeshAdapter_rewind_0(this.__ptr);
};
MeshAdapter.prototype["copy"] = MeshAdapter.prototype.copy = function(a0) {
    if (!checkClass(a0, MeshAdapter)) throw Error('copy(0:dest): expected MeshAdapter');
    _mud_MeshAdapter_copy_1(this.__ptr, /*dest*/a0.__ptr);
};
MeshAdapter.prototype["xcopy"] = MeshAdapter.prototype.xcopy = function(a0, a1) {
    if (!checkClass(a0, MeshAdapter)) throw Error('xcopy(0:dest): expected MeshAdapter'); if (!checkClass(a1, mat4)) throw Error('xcopy(1:transform): expected mat4');
    _mud_MeshAdapter_xcopy_2(this.__ptr, /*dest*/a0.__ptr, /*transform*/a1.__ptr);
};
MeshAdapter.prototype["next"] = MeshAdapter.prototype.next = function() {
    
    _mud_MeshAdapter_next_0(this.__ptr);
};
MeshAdapter.prototype["position"] = MeshAdapter.prototype.position = function(a0) {
    if (!checkClass(a0, v3_float)) throw Error('position(0:p): expected v3<float>');
    return wrapPointer(_mud_MeshAdapter_position_1(this.__ptr, /*p*/a0.__ptr), MeshAdapter);
};
MeshAdapter.prototype["position4"] = MeshAdapter.prototype.position4 = function(a0) {
    if (!checkClass(a0, v4_float)) throw Error('position4(0:p): expected v4<float>');
    return wrapPointer(_mud_MeshAdapter_position4_1(this.__ptr, /*p*/a0.__ptr), MeshAdapter);
};
MeshAdapter.prototype["normal"] = MeshAdapter.prototype.normal = function(a0) {
    if (!checkClass(a0, v3_float)) throw Error('normal(0:n): expected v3<float>');
    return wrapPointer(_mud_MeshAdapter_normal_1(this.__ptr, /*n*/a0.__ptr), MeshAdapter);
};
MeshAdapter.prototype["colour"] = MeshAdapter.prototype.colour = function(a0) {
    if (!checkClass(a0, Colour)) throw Error('colour(0:c): expected Colour');
    return wrapPointer(_mud_MeshAdapter_colour_1(this.__ptr, /*c*/a0.__ptr), MeshAdapter);
};
MeshAdapter.prototype["tangent"] = MeshAdapter.prototype.tangent = function(a0) {
    if (!checkClass(a0, v4_float)) throw Error('tangent(0:t): expected v4<float>');
    return wrapPointer(_mud_MeshAdapter_tangent_1(this.__ptr, /*t*/a0.__ptr), MeshAdapter);
};
MeshAdapter.prototype["bitangent"] = MeshAdapter.prototype.bitangent = function(a0) {
    if (!checkClass(a0, v3_float)) throw Error('bitangent(0:b): expected v3<float>');
    return wrapPointer(_mud_MeshAdapter_bitangent_1(this.__ptr, /*b*/a0.__ptr), MeshAdapter);
};
MeshAdapter.prototype["uv0"] = MeshAdapter.prototype.uv0 = function(a0) {
    if (!checkClass(a0, v2_float)) throw Error('uv0(0:uv): expected v2<float>');
    return wrapPointer(_mud_MeshAdapter_uv0_1(this.__ptr, /*uv*/a0.__ptr), MeshAdapter);
};
MeshAdapter.prototype["uv1"] = MeshAdapter.prototype.uv1 = function(a0) {
    if (!checkClass(a0, v2_float)) throw Error('uv1(0:uv): expected v2<float>');
    return wrapPointer(_mud_MeshAdapter_uv1_1(this.__ptr, /*uv*/a0.__ptr), MeshAdapter);
};
MeshAdapter.prototype["joints"] = MeshAdapter.prototype.joints = function(a0) {
    if (typeof a0 !== 'number') throw Error('joints(0:j): expected integer');
    return wrapPointer(_mud_MeshAdapter_joints_1(this.__ptr, /*j*/a0), MeshAdapter);
};
MeshAdapter.prototype["weights"] = MeshAdapter.prototype.weights = function(a0) {
    if (!checkClass(a0, v4_float)) throw Error('weights(0:w): expected v4<float>');
    return wrapPointer(_mud_MeshAdapter_weights_1(this.__ptr, /*w*/a0.__ptr), MeshAdapter);
};
Object.defineProperty(MeshAdapter.prototype, "vertex_format", {
    get: function() {
        return _mud_MeshAdapter__get_vertex_format(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('MeshAdapter.vertex_format: expected integer');
        _mud_MeshAdapter__set_vertex_format(this.__ptr, value);
    }
});
Object.defineProperty(MeshAdapter.prototype, "index32", {
    get: function() {
        return !!(_mud_MeshAdapter__get_index32(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('MeshAdapter.index32: expected boolean');
        _mud_MeshAdapter__set_index32(this.__ptr, value);
    }
});
Object.defineProperty(MeshAdapter.prototype, "vertex_count", {
    get: function() {
        return _mud_MeshAdapter__get_vertex_count(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('MeshAdapter.vertex_count: expected integer');
        _mud_MeshAdapter__set_vertex_count(this.__ptr, value);
    }
});
Object.defineProperty(MeshAdapter.prototype, "index_count", {
    get: function() {
        return _mud_MeshAdapter__get_index_count(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('MeshAdapter.index_count: expected integer');
        _mud_MeshAdapter__set_index_count(this.__ptr, value);
    }
});
Object.defineProperty(MeshAdapter.prototype, "vertex_stride", {
    get: function() {
        return _mud_MeshAdapter__get_vertex_stride(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('MeshAdapter.vertex_stride: expected integer');
        _mud_MeshAdapter__set_vertex_stride(this.__ptr, value);
    }
});
MeshAdapter.prototype["__destroy"] = MeshAdapter.prototype.__destroy = function() {
    _mud_MeshAdapter__destroy(this.__ptr);
};
// Shape
function Shape() { throw "cannot construct a Shape, no constructor in IDL" }
Shape.prototype = Object.create(WrapperObject.prototype);
Shape.prototype.constructor = Shape;
Shape.prototype.__class = Shape;
Shape.__cache = {};
Module['Shape'] = Shape;
Object.defineProperty(Shape.prototype, "type", {
    get: function() {
        return wrapPointer(_mud_Shape__get_type(this.__ptr), Type);
    }});
Shape.prototype["__destroy"] = Shape.prototype.__destroy = function() {
    _mud_Shape__destroy(this.__ptr);
};
// ShapeVar
function ShapeVar(a0) {
    if (a0 === undefined) {  }
    else { if (!checkClass(a0, Shape)) throw Error('ShapeVar(0:shape): expected Shape'); }
    if (a0 === undefined) { this.__ptr = _mud_ShapeVar__construct_0(); getCache(ShapeVar)[this.__ptr] = this; }
    else { this.__ptr = _mud_ShapeVar__construct_1(/*shape*/a0.__ptr); getCache(ShapeVar)[this.__ptr] = this; }
};
ShapeVar.prototype = Object.create(WrapperObject.prototype);
ShapeVar.prototype.constructor = ShapeVar;
ShapeVar.prototype.__class = ShapeVar;
ShapeVar.__cache = {};
Module['ShapeVar'] = ShapeVar;
Object.defineProperty(ShapeVar.prototype, "shape", {
    get: function() {
        return wrapPointer(_mud_ShapeVar__get_shape(this.__ptr), Shape);
    }});
ShapeVar.prototype["__destroy"] = ShapeVar.prototype.__destroy = function() {
    _mud_ShapeVar__destroy(this.__ptr);
};
// Geometry
function Geometry() {
    
    this.__ptr = _mud_Geometry__construct_0(); getCache(Geometry)[this.__ptr] = this;
};
Geometry.prototype = Object.create(Shape.prototype);
Geometry.prototype.constructor = Geometry;
Geometry.prototype.__class = Geometry;
Geometry.__base = Shape;
Geometry.__cache = {};
Module['Geometry'] = Geometry;
Geometry.prototype["__destroy"] = Geometry.prototype.__destroy = function() {
    _mud_Geometry__destroy(this.__ptr);
};
// MeshPacker
function MeshPacker() {
    
    this.__ptr = _mud_MeshPacker__construct_0(); getCache(MeshPacker)[this.__ptr] = this;
};
MeshPacker.prototype = Object.create(WrapperObject.prototype);
MeshPacker.prototype.constructor = MeshPacker;
MeshPacker.prototype.__class = MeshPacker;
MeshPacker.__cache = {};
Module['MeshPacker'] = MeshPacker;
MeshPacker.prototype["position"] = MeshPacker.prototype.position = function(a0) {
    if (!checkClass(a0, v3_float)) throw Error('position(0:p): expected v3<float>');
    _mud_MeshPacker_position_1(this.__ptr, /*p*/a0.__ptr);
};
MeshPacker.prototype["normal"] = MeshPacker.prototype.normal = function(a0) {
    if (!checkClass(a0, v3_float)) throw Error('normal(0:n): expected v3<float>');
    _mud_MeshPacker_normal_1(this.__ptr, /*n*/a0.__ptr);
};
MeshPacker.prototype["colour"] = MeshPacker.prototype.colour = function(a0) {
    if (!checkClass(a0, Colour)) throw Error('colour(0:c): expected Colour');
    _mud_MeshPacker_colour_1(this.__ptr, /*c*/a0.__ptr);
};
MeshPacker.prototype["tangent"] = MeshPacker.prototype.tangent = function(a0) {
    if (!checkClass(a0, v4_float)) throw Error('tangent(0:t): expected v4<float>');
    _mud_MeshPacker_tangent_1(this.__ptr, /*t*/a0.__ptr);
};
MeshPacker.prototype["bitangent"] = MeshPacker.prototype.bitangent = function(a0) {
    if (!checkClass(a0, v3_float)) throw Error('bitangent(0:b): expected v3<float>');
    _mud_MeshPacker_bitangent_1(this.__ptr, /*b*/a0.__ptr);
};
MeshPacker.prototype["uv0"] = MeshPacker.prototype.uv0 = function(a0) {
    if (!checkClass(a0, v2_float)) throw Error('uv0(0:uv): expected v2<float>');
    _mud_MeshPacker_uv0_1(this.__ptr, /*uv*/a0.__ptr);
};
MeshPacker.prototype["uv1"] = MeshPacker.prototype.uv1 = function(a0) {
    if (!checkClass(a0, v2_float)) throw Error('uv1(0:uv): expected v2<float>');
    _mud_MeshPacker_uv1_1(this.__ptr, /*uv*/a0.__ptr);
};
MeshPacker.prototype["bones"] = MeshPacker.prototype.bones = function(a0) {
    if (!checkClass(a0, v4_int)) throw Error('bones(0:j): expected v4<int>');
    _mud_MeshPacker_bones_1(this.__ptr, /*j*/a0.__ptr);
};
MeshPacker.prototype["weights"] = MeshPacker.prototype.weights = function(a0) {
    if (!checkClass(a0, v4_float)) throw Error('weights(0:w): expected v4<float>');
    _mud_MeshPacker_weights_1(this.__ptr, /*w*/a0.__ptr);
};
MeshPacker.prototype["index"] = MeshPacker.prototype.index = function(a0) {
    if (typeof a0 !== 'number') throw Error('index(0:i): expected integer');
    _mud_MeshPacker_index_1(this.__ptr, /*i*/a0);
};
MeshPacker.prototype["resize"] = MeshPacker.prototype.resize = function(a0, a1, a2) {
    if (typeof a0 !== 'number') throw Error('resize(0:vertex_count): expected integer'); if (typeof a1 !== 'number') throw Error('resize(1:index_count): expected integer'); if (typeof a2 !== 'number') throw Error('resize(2:vertex_format): expected integer');
    _mud_MeshPacker_resize_3(this.__ptr, /*vertex_count*/a0, /*index_count*/a1, /*vertex_format*/a2);
};
MeshPacker.prototype["clear"] = MeshPacker.prototype.clear = function() {
    
    _mud_MeshPacker_clear_0(this.__ptr);
};
MeshPacker.prototype["pack"] = MeshPacker.prototype.pack = function(a0) {
    if (!checkClass(a0, MeshAdapter)) throw Error('pack(0:writer): expected MeshAdapter');
    _mud_MeshPacker_pack_1(this.__ptr, /*writer*/a0.__ptr);
};
MeshPacker.prototype["xpack"] = MeshPacker.prototype.xpack = function(a0, a1) {
    if (!checkClass(a0, MeshAdapter)) throw Error('xpack(0:writer): expected MeshAdapter'); if (!checkClass(a1, mat4)) throw Error('xpack(1:transform): expected mat4');
    _mud_MeshPacker_xpack_2(this.__ptr, /*writer*/a0.__ptr, /*transform*/a1.__ptr);
};
MeshPacker.prototype["unpack"] = MeshPacker.prototype.unpack = function(a0, a1) {
    if (!checkClass(a0, MeshAdapter)) throw Error('unpack(0:reader): expected MeshAdapter'); if (!checkClass(a1, mat4)) throw Error('unpack(1:transform): expected mat4');
    _mud_MeshPacker_unpack_2(this.__ptr, /*reader*/a0.__ptr, /*transform*/a1.__ptr);
};
MeshPacker.prototype["gen_normals"] = MeshPacker.prototype.gen_normals = function(a0) {
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'boolean') throw Error('gen_normals(0:area_weighted): expected boolean'); }
    if (a0 === undefined) { _mud_MeshPacker_gen_normals_0(this.__ptr); }
    else { _mud_MeshPacker_gen_normals_1(this.__ptr, /*area_weighted*/a0); }
};
MeshPacker.prototype["gen_flat_normals"] = MeshPacker.prototype.gen_flat_normals = function() {
    
    _mud_MeshPacker_gen_flat_normals_0(this.__ptr);
};
MeshPacker.prototype["gen_tangents"] = MeshPacker.prototype.gen_tangents = function() {
    
    _mud_MeshPacker_gen_tangents_0(this.__ptr);
};
MeshPacker.prototype["smooth_normals"] = MeshPacker.prototype.smooth_normals = function() {
    
    _mud_MeshPacker_smooth_normals_0(this.__ptr);
};
Object.defineProperty(MeshPacker.prototype, "primitive", {
    get: function() {
        return _mud_MeshPacker__get_primitive(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('MeshPacker.primitive: expected integer');
        _mud_MeshPacker__set_primitive(this.__ptr, value);
    }
});
Object.defineProperty(MeshPacker.prototype, "positions", {
    get: function() {
        return _mud_MeshPacker__get_positions(this.__ptr);
    }});
Object.defineProperty(MeshPacker.prototype, "normals", {
    get: function() {
        return _mud_MeshPacker__get_normals(this.__ptr);
    }});
Object.defineProperty(MeshPacker.prototype, "colours", {
    get: function() {
        return _mud_MeshPacker__get_colours(this.__ptr);
    }});
Object.defineProperty(MeshPacker.prototype, "ucolours", {
    get: function() {
        return _mud_MeshPacker__get_ucolours(this.__ptr);
    }});
Object.defineProperty(MeshPacker.prototype, "tangents", {
    get: function() {
        return _mud_MeshPacker__get_tangents(this.__ptr);
    }});
Object.defineProperty(MeshPacker.prototype, "bitangents", {
    get: function() {
        return _mud_MeshPacker__get_bitangents(this.__ptr);
    }});
Object.defineProperty(MeshPacker.prototype, "uv0s", {
    get: function() {
        return _mud_MeshPacker__get_uv0s(this.__ptr);
    }});
Object.defineProperty(MeshPacker.prototype, "uv1s", {
    get: function() {
        return _mud_MeshPacker__get_uv1s(this.__ptr);
    }});
Object.defineProperty(MeshPacker.prototype, "bones", {
    get: function() {
        return _mud_MeshPacker__get_bones(this.__ptr);
    }});
Object.defineProperty(MeshPacker.prototype, "weights", {
    get: function() {
        return _mud_MeshPacker__get_weights(this.__ptr);
    }});
Object.defineProperty(MeshPacker.prototype, "indices", {
    get: function() {
        return _mud_MeshPacker__get_indices(this.__ptr);
    }});
Object.defineProperty(MeshPacker.prototype, "quantize", {
    get: function() {
        return !!(_mud_MeshPacker__get_quantize(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('MeshPacker.quantize: expected boolean');
        _mud_MeshPacker__set_quantize(this.__ptr, value);
    }
});
MeshPacker.prototype["__destroy"] = MeshPacker.prototype.__destroy = function() {
    _mud_MeshPacker__destroy(this.__ptr);
};
// Line
function Line(a0, a1) {
    if (a0 === undefined) {  }
    else { if (!checkClass(a0, v3_float)) throw Error('Line(0:start): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('Line(1:end): expected v3<float>'); }
    if (a0 === undefined) { this.__ptr = _mud_Line__construct_0(); getCache(Line)[this.__ptr] = this; }
    else { this.__ptr = _mud_Line__construct_2(/*start*/a0.__ptr, /*end*/a1.__ptr); getCache(Line)[this.__ptr] = this; }
};
Line.prototype = Object.create(Shape.prototype);
Line.prototype.constructor = Line;
Line.prototype.__class = Line;
Line.__base = Shape;
Line.__cache = {};
Module['Line'] = Line;
Object.defineProperty(Line.prototype, "start", {
    get: function() {
        return wrapPointer(_mud_Line__get_start(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Line.start: expected v3<float>');
        _mud_Line__set_start(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Line.prototype, "end", {
    get: function() {
        return wrapPointer(_mud_Line__get_end(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Line.end: expected v3<float>');
        _mud_Line__set_end(this.__ptr, value.__ptr);
    }
});
Line.prototype["__destroy"] = Line.prototype.__destroy = function() {
    _mud_Line__destroy(this.__ptr);
};
// Rect
function Rect(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else if (a2 === undefined) { if (!checkClass(a0, v2_float)) throw Error('Rect(0:position): expected v2<float>'); if (!checkClass(a1, v2_float)) throw Error('Rect(1:size): expected v2<float>'); }
    else { if (typeof a0 !== 'number') throw Error('Rect(0:x): expected number'); if (typeof a1 !== 'number') throw Error('Rect(1:y): expected number'); if (typeof a2 !== 'number') throw Error('Rect(2:w): expected number'); if (typeof a3 !== 'number') throw Error('Rect(3:h): expected number'); }
    if (a0 === undefined) { this.__ptr = _mud_Rect__construct_0(); getCache(Rect)[this.__ptr] = this; }
    else if (a2 === undefined) { this.__ptr = _mud_Rect__construct_2(/*position*/a0.__ptr, /*size*/a1.__ptr); getCache(Rect)[this.__ptr] = this; }
    else { this.__ptr = _mud_Rect__construct_4(/*x*/a0, /*y*/a1, /*w*/a2, /*h*/a3); getCache(Rect)[this.__ptr] = this; }
};
Rect.prototype = Object.create(Shape.prototype);
Rect.prototype.constructor = Rect;
Rect.prototype.__class = Rect;
Rect.__base = Shape;
Rect.__cache = {};
Module['Rect'] = Rect;
Object.defineProperty(Rect.prototype, "position", {
    get: function() {
        return wrapPointer(_mud_Rect__get_position(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('Rect.position: expected v2<float>');
        _mud_Rect__set_position(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Rect.prototype, "size", {
    get: function() {
        return wrapPointer(_mud_Rect__get_size(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('Rect.size: expected v2<float>');
        _mud_Rect__set_size(this.__ptr, value.__ptr);
    }
});
Rect.prototype["__destroy"] = Rect.prototype.__destroy = function() {
    _mud_Rect__destroy(this.__ptr);
};
// Quad
function Quad(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else { if (!checkClass(a0, v3_float)) throw Error('Quad(0:a): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('Quad(1:b): expected v3<float>'); if (!checkClass(a2, v3_float)) throw Error('Quad(2:c): expected v3<float>'); if (!checkClass(a3, v3_float)) throw Error('Quad(3:d): expected v3<float>'); }
    if (a0 === undefined) { this.__ptr = _mud_Quad__construct_0(); getCache(Quad)[this.__ptr] = this; }
    else { this.__ptr = _mud_Quad__construct_4(/*a*/a0.__ptr, /*b*/a1.__ptr, /*c*/a2.__ptr, /*d*/a3.__ptr); getCache(Quad)[this.__ptr] = this; }
};
Quad.prototype = Object.create(Shape.prototype);
Quad.prototype.constructor = Quad;
Quad.prototype.__class = Quad;
Quad.__base = Shape;
Quad.__cache = {};
Module['Quad'] = Quad;
Quad.prototype["__destroy"] = Quad.prototype.__destroy = function() {
    _mud_Quad__destroy(this.__ptr);
};
// Grid2
function Grid2(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (!checkClass(a0, v2_float)) throw Error('Grid2(0:size): expected v2<float>'); }
    else { if (!checkClass(a0, v2_float)) throw Error('Grid2(0:size): expected v2<float>'); if (!checkClass(a1, v2_float)) throw Error('Grid2(1:space): expected v2<float>'); }
    if (a0 === undefined) { this.__ptr = _mud_Grid2__construct_0(); getCache(Grid2)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _mud_Grid2__construct_1(/*size*/a0.__ptr); getCache(Grid2)[this.__ptr] = this; }
    else { this.__ptr = _mud_Grid2__construct_2(/*size*/a0.__ptr, /*space*/a1.__ptr); getCache(Grid2)[this.__ptr] = this; }
};
Grid2.prototype = Object.create(Shape.prototype);
Grid2.prototype.constructor = Grid2;
Grid2.prototype.__class = Grid2;
Grid2.__base = Shape;
Grid2.__cache = {};
Module['Grid2'] = Grid2;
Object.defineProperty(Grid2.prototype, "size", {
    get: function() {
        return wrapPointer(_mud_Grid2__get_size(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('Grid2.size: expected v2<float>');
        _mud_Grid2__set_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Grid2.prototype, "space", {
    get: function() {
        return wrapPointer(_mud_Grid2__get_space(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('Grid2.space: expected v2<float>');
        _mud_Grid2__set_space(this.__ptr, value.__ptr);
    }
});
Grid2.prototype["__destroy"] = Grid2.prototype.__destroy = function() {
    _mud_Grid2__destroy(this.__ptr);
};
// Triangle
function Triangle(a0) {
    if (a0 === undefined) {  }
    else { if (!checkClass(a0, v2_float)) throw Error('Triangle(0:size): expected v2<float>'); }
    if (a0 === undefined) { this.__ptr = _mud_Triangle__construct_0(); getCache(Triangle)[this.__ptr] = this; }
    else { this.__ptr = _mud_Triangle__construct_1(/*size*/a0.__ptr); getCache(Triangle)[this.__ptr] = this; }
};
Triangle.prototype = Object.create(Shape.prototype);
Triangle.prototype.constructor = Triangle;
Triangle.prototype.__class = Triangle;
Triangle.__base = Shape;
Triangle.__cache = {};
Module['Triangle'] = Triangle;
Object.defineProperty(Triangle.prototype, "size", {
    get: function() {
        return wrapPointer(_mud_Triangle__get_size(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('Triangle.size: expected v2<float>');
        _mud_Triangle__set_size(this.__ptr, value.__ptr);
    }
});
Triangle.prototype["__destroy"] = Triangle.prototype.__destroy = function() {
    _mud_Triangle__destroy(this.__ptr);
};
// Circle
function Circle(a0, a1, a2) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('Circle(0:radius): expected number'); }
    else if (a2 === undefined) { if (typeof a0 !== 'number') throw Error('Circle(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('Circle(1:axis): expected integer'); }
    else { if (!checkClass(a0, v3_float)) throw Error('Circle(0:center): expected v3<float>'); if (typeof a1 !== 'number') throw Error('Circle(1:radius): expected number'); if (typeof a2 !== 'number') throw Error('Circle(2:axis): expected integer'); }
    if (a0 === undefined) { this.__ptr = _mud_Circle__construct_0(); getCache(Circle)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _mud_Circle__construct_1(/*radius*/a0); getCache(Circle)[this.__ptr] = this; }
    else if (a2 === undefined) { this.__ptr = _mud_Circle__construct_2(/*radius*/a0, /*axis*/a1); getCache(Circle)[this.__ptr] = this; }
    else { this.__ptr = _mud_Circle__construct_3(/*center*/a0.__ptr, /*radius*/a1, /*axis*/a2); getCache(Circle)[this.__ptr] = this; }
};
Circle.prototype = Object.create(Shape.prototype);
Circle.prototype.constructor = Circle;
Circle.prototype.__class = Circle;
Circle.__base = Shape;
Circle.__cache = {};
Module['Circle'] = Circle;
Object.defineProperty(Circle.prototype, "radius", {
    get: function() {
        return _mud_Circle__get_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Circle.radius: expected number');
        _mud_Circle__set_radius(this.__ptr, value);
    }
});
Object.defineProperty(Circle.prototype, "axis", {
    get: function() {
        return _mud_Circle__get_axis(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Circle.axis: expected integer');
        _mud_Circle__set_axis(this.__ptr, value);
    }
});
Circle.prototype["__destroy"] = Circle.prototype.__destroy = function() {
    _mud_Circle__destroy(this.__ptr);
};
// Torus
function Torus(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else if (a2 === undefined) { if (typeof a0 !== 'number') throw Error('Torus(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('Torus(1:tube): expected number'); }
    else if (a3 === undefined) { if (typeof a0 !== 'number') throw Error('Torus(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('Torus(1:tube): expected number'); if (typeof a2 !== 'number') throw Error('Torus(2:axis): expected integer'); }
    else { if (!checkClass(a0, v3_float)) throw Error('Torus(0:center): expected v3<float>'); if (typeof a1 !== 'number') throw Error('Torus(1:radius): expected number'); if (typeof a2 !== 'number') throw Error('Torus(2:tube): expected number'); if (typeof a3 !== 'number') throw Error('Torus(3:axis): expected integer'); }
    if (a0 === undefined) { this.__ptr = _mud_Torus__construct_0(); getCache(Torus)[this.__ptr] = this; }
    else if (a2 === undefined) { this.__ptr = _mud_Torus__construct_2(/*radius*/a0, /*tube*/a1); getCache(Torus)[this.__ptr] = this; }
    else if (a3 === undefined) { this.__ptr = _mud_Torus__construct_3(/*radius*/a0, /*tube*/a1, /*axis*/a2); getCache(Torus)[this.__ptr] = this; }
    else { this.__ptr = _mud_Torus__construct_4(/*center*/a0.__ptr, /*radius*/a1, /*tube*/a2, /*axis*/a3); getCache(Torus)[this.__ptr] = this; }
};
Torus.prototype = Object.create(Shape.prototype);
Torus.prototype.constructor = Torus;
Torus.prototype.__class = Torus;
Torus.__base = Shape;
Torus.__cache = {};
Module['Torus'] = Torus;
Object.defineProperty(Torus.prototype, "radius", {
    get: function() {
        return _mud_Torus__get_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Torus.radius: expected number');
        _mud_Torus__set_radius(this.__ptr, value);
    }
});
Object.defineProperty(Torus.prototype, "tube", {
    get: function() {
        return _mud_Torus__get_tube(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Torus.tube: expected number');
        _mud_Torus__set_tube(this.__ptr, value);
    }
});
Object.defineProperty(Torus.prototype, "axis", {
    get: function() {
        return _mud_Torus__get_axis(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Torus.axis: expected integer');
        _mud_Torus__set_axis(this.__ptr, value);
    }
});
Torus.prototype["__destroy"] = Torus.prototype.__destroy = function() {
    _mud_Torus__destroy(this.__ptr);
};
// TorusKnot
function TorusKnot(a0, a1, a2, a3, a4) {
    if (a0 === undefined) {  }
    else if (a2 === undefined) { if (typeof a0 !== 'number') throw Error('TorusKnot(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('TorusKnot(1:tube): expected number'); }
    else if (a3 === undefined) { if (typeof a0 !== 'number') throw Error('TorusKnot(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('TorusKnot(1:tube): expected number'); if (typeof a2 !== 'number') throw Error('TorusKnot(2:p): expected number'); }
    else if (a4 === undefined) { if (typeof a0 !== 'number') throw Error('TorusKnot(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('TorusKnot(1:tube): expected number'); if (typeof a2 !== 'number') throw Error('TorusKnot(2:p): expected number'); if (typeof a3 !== 'number') throw Error('TorusKnot(3:q): expected number'); }
    else { if (!checkClass(a0, v3_float)) throw Error('TorusKnot(0:center): expected v3<float>'); if (typeof a1 !== 'number') throw Error('TorusKnot(1:radius): expected number'); if (typeof a2 !== 'number') throw Error('TorusKnot(2:tube): expected number'); if (typeof a3 !== 'number') throw Error('TorusKnot(3:p): expected number'); if (typeof a4 !== 'number') throw Error('TorusKnot(4:q): expected number'); }
    if (a0 === undefined) { this.__ptr = _mud_TorusKnot__construct_0(); getCache(TorusKnot)[this.__ptr] = this; }
    else if (a2 === undefined) { this.__ptr = _mud_TorusKnot__construct_2(/*radius*/a0, /*tube*/a1); getCache(TorusKnot)[this.__ptr] = this; }
    else if (a3 === undefined) { this.__ptr = _mud_TorusKnot__construct_3(/*radius*/a0, /*tube*/a1, /*p*/a2); getCache(TorusKnot)[this.__ptr] = this; }
    else if (a4 === undefined) { this.__ptr = _mud_TorusKnot__construct_4(/*radius*/a0, /*tube*/a1, /*p*/a2, /*q*/a3); getCache(TorusKnot)[this.__ptr] = this; }
    else { this.__ptr = _mud_TorusKnot__construct_5(/*center*/a0.__ptr, /*radius*/a1, /*tube*/a2, /*p*/a3, /*q*/a4); getCache(TorusKnot)[this.__ptr] = this; }
};
TorusKnot.prototype = Object.create(Shape.prototype);
TorusKnot.prototype.constructor = TorusKnot;
TorusKnot.prototype.__class = TorusKnot;
TorusKnot.__base = Shape;
TorusKnot.__cache = {};
Module['TorusKnot'] = TorusKnot;
Object.defineProperty(TorusKnot.prototype, "radius", {
    get: function() {
        return _mud_TorusKnot__get_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('TorusKnot.radius: expected number');
        _mud_TorusKnot__set_radius(this.__ptr, value);
    }
});
Object.defineProperty(TorusKnot.prototype, "tube", {
    get: function() {
        return _mud_TorusKnot__get_tube(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('TorusKnot.tube: expected number');
        _mud_TorusKnot__set_tube(this.__ptr, value);
    }
});
Object.defineProperty(TorusKnot.prototype, "p", {
    get: function() {
        return _mud_TorusKnot__get_p(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('TorusKnot.p: expected number');
        _mud_TorusKnot__set_p(this.__ptr, value);
    }
});
Object.defineProperty(TorusKnot.prototype, "q", {
    get: function() {
        return _mud_TorusKnot__get_q(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('TorusKnot.q: expected number');
        _mud_TorusKnot__set_q(this.__ptr, value);
    }
});
TorusKnot.prototype["__destroy"] = TorusKnot.prototype.__destroy = function() {
    _mud_TorusKnot__destroy(this.__ptr);
};
// Ring
function Ring(a0, a1, a2) {
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'number') throw Error('Ring(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('Ring(1:min): expected number'); if (typeof a2 !== 'number') throw Error('Ring(2:max): expected number'); }
    if (a0 === undefined) { this.__ptr = _mud_Ring__construct_0(); getCache(Ring)[this.__ptr] = this; }
    else { this.__ptr = _mud_Ring__construct_3(/*radius*/a0, /*min*/a1, /*max*/a2); getCache(Ring)[this.__ptr] = this; }
};
Ring.prototype = Object.create(Shape.prototype);
Ring.prototype.constructor = Ring;
Ring.prototype.__class = Ring;
Ring.__base = Shape;
Ring.__cache = {};
Module['Ring'] = Ring;
Object.defineProperty(Ring.prototype, "radius", {
    get: function() {
        return _mud_Ring__get_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Ring.radius: expected number');
        _mud_Ring__set_radius(this.__ptr, value);
    }
});
Object.defineProperty(Ring.prototype, "min", {
    get: function() {
        return _mud_Ring__get_min(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Ring.min: expected number');
        _mud_Ring__set_min(this.__ptr, value);
    }
});
Object.defineProperty(Ring.prototype, "max", {
    get: function() {
        return _mud_Ring__get_max(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Ring.max: expected number');
        _mud_Ring__set_max(this.__ptr, value);
    }
});
Ring.prototype["__destroy"] = Ring.prototype.__destroy = function() {
    _mud_Ring__destroy(this.__ptr);
};
// Ellipsis
function Ellipsis(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (!checkClass(a0, v2_float)) throw Error('Ellipsis(0:radius): expected v2<float>'); }
    else { if (!checkClass(a0, v2_float)) throw Error('Ellipsis(0:radius): expected v2<float>'); if (typeof a1 !== 'number') throw Error('Ellipsis(1:axis): expected integer'); }
    if (a0 === undefined) { this.__ptr = _mud_Ellipsis__construct_0(); getCache(Ellipsis)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _mud_Ellipsis__construct_1(/*radius*/a0.__ptr); getCache(Ellipsis)[this.__ptr] = this; }
    else { this.__ptr = _mud_Ellipsis__construct_2(/*radius*/a0.__ptr, /*axis*/a1); getCache(Ellipsis)[this.__ptr] = this; }
};
Ellipsis.prototype = Object.create(Shape.prototype);
Ellipsis.prototype.constructor = Ellipsis;
Ellipsis.prototype.__class = Ellipsis;
Ellipsis.__base = Shape;
Ellipsis.__cache = {};
Module['Ellipsis'] = Ellipsis;
Object.defineProperty(Ellipsis.prototype, "radius", {
    get: function() {
        return wrapPointer(_mud_Ellipsis__get_radius(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('Ellipsis.radius: expected v2<float>');
        _mud_Ellipsis__set_radius(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Ellipsis.prototype, "axis", {
    get: function() {
        return _mud_Ellipsis__get_axis(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Ellipsis.axis: expected integer');
        _mud_Ellipsis__set_axis(this.__ptr, value);
    }
});
Ellipsis.prototype["__destroy"] = Ellipsis.prototype.__destroy = function() {
    _mud_Ellipsis__destroy(this.__ptr);
};
// Arc
function Arc(a0, a1, a2) {
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'number') throw Error('Arc(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('Arc(1:start): expected number'); if (typeof a2 !== 'number') throw Error('Arc(2:end): expected number'); }
    if (a0 === undefined) { this.__ptr = _mud_Arc__construct_0(); getCache(Arc)[this.__ptr] = this; }
    else { this.__ptr = _mud_Arc__construct_3(/*radius*/a0, /*start*/a1, /*end*/a2); getCache(Arc)[this.__ptr] = this; }
};
Arc.prototype = Object.create(Shape.prototype);
Arc.prototype.constructor = Arc;
Arc.prototype.__class = Arc;
Arc.__base = Shape;
Arc.__cache = {};
Module['Arc'] = Arc;
Object.defineProperty(Arc.prototype, "radius", {
    get: function() {
        return _mud_Arc__get_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Arc.radius: expected number');
        _mud_Arc__set_radius(this.__ptr, value);
    }
});
Object.defineProperty(Arc.prototype, "start", {
    get: function() {
        return _mud_Arc__get_start(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Arc.start: expected number');
        _mud_Arc__set_start(this.__ptr, value);
    }
});
Object.defineProperty(Arc.prototype, "end", {
    get: function() {
        return _mud_Arc__get_end(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Arc.end: expected number');
        _mud_Arc__set_end(this.__ptr, value);
    }
});
Arc.prototype["__destroy"] = Arc.prototype.__destroy = function() {
    _mud_Arc__destroy(this.__ptr);
};
// ArcLine
function ArcLine(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else if (a3 === undefined) { if (!checkClass(a0, v3_float)) throw Error('ArcLine(0:start): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('ArcLine(1:middle): expected v3<float>'); if (!checkClass(a2, v3_float)) throw Error('ArcLine(2:end): expected v3<float>'); }
    else { if (!checkClass(a0, v3_float)) throw Error('ArcLine(0:center): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('ArcLine(1:start): expected v3<float>'); if (!checkClass(a2, v3_float)) throw Error('ArcLine(2:middle): expected v3<float>'); if (!checkClass(a3, v3_float)) throw Error('ArcLine(3:end): expected v3<float>'); }
    if (a0 === undefined) { this.__ptr = _mud_ArcLine__construct_0(); getCache(ArcLine)[this.__ptr] = this; }
    else if (a3 === undefined) { this.__ptr = _mud_ArcLine__construct_3(/*start*/a0.__ptr, /*middle*/a1.__ptr, /*end*/a2.__ptr); getCache(ArcLine)[this.__ptr] = this; }
    else { this.__ptr = _mud_ArcLine__construct_4(/*center*/a0.__ptr, /*start*/a1.__ptr, /*middle*/a2.__ptr, /*end*/a3.__ptr); getCache(ArcLine)[this.__ptr] = this; }
};
ArcLine.prototype = Object.create(Shape.prototype);
ArcLine.prototype.constructor = ArcLine;
ArcLine.prototype.__class = ArcLine;
ArcLine.__base = Shape;
ArcLine.__cache = {};
Module['ArcLine'] = ArcLine;
Object.defineProperty(ArcLine.prototype, "start", {
    get: function() {
        return wrapPointer(_mud_ArcLine__get_start(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('ArcLine.start: expected v3<float>');
        _mud_ArcLine__set_start(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ArcLine.prototype, "middle", {
    get: function() {
        return wrapPointer(_mud_ArcLine__get_middle(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('ArcLine.middle: expected v3<float>');
        _mud_ArcLine__set_middle(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ArcLine.prototype, "end", {
    get: function() {
        return wrapPointer(_mud_ArcLine__get_end(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('ArcLine.end: expected v3<float>');
        _mud_ArcLine__set_end(this.__ptr, value.__ptr);
    }
});
ArcLine.prototype["__destroy"] = ArcLine.prototype.__destroy = function() {
    _mud_ArcLine__destroy(this.__ptr);
};
// Cylinder
function Cylinder(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else if (a2 === undefined) { if (typeof a0 !== 'number') throw Error('Cylinder(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('Cylinder(1:height): expected number'); }
    else if (a3 === undefined) { if (typeof a0 !== 'number') throw Error('Cylinder(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('Cylinder(1:height): expected number'); if (typeof a2 !== 'number') throw Error('Cylinder(2:axis): expected integer'); }
    else { if (!checkClass(a0, v3_float)) throw Error('Cylinder(0:center): expected v3<float>'); if (typeof a1 !== 'number') throw Error('Cylinder(1:radius): expected number'); if (typeof a2 !== 'number') throw Error('Cylinder(2:height): expected number'); if (typeof a3 !== 'number') throw Error('Cylinder(3:axis): expected integer'); }
    if (a0 === undefined) { this.__ptr = _mud_Cylinder__construct_0(); getCache(Cylinder)[this.__ptr] = this; }
    else if (a2 === undefined) { this.__ptr = _mud_Cylinder__construct_2(/*radius*/a0, /*height*/a1); getCache(Cylinder)[this.__ptr] = this; }
    else if (a3 === undefined) { this.__ptr = _mud_Cylinder__construct_3(/*radius*/a0, /*height*/a1, /*axis*/a2); getCache(Cylinder)[this.__ptr] = this; }
    else { this.__ptr = _mud_Cylinder__construct_4(/*center*/a0.__ptr, /*radius*/a1, /*height*/a2, /*axis*/a3); getCache(Cylinder)[this.__ptr] = this; }
};
Cylinder.prototype = Object.create(Shape.prototype);
Cylinder.prototype.constructor = Cylinder;
Cylinder.prototype.__class = Cylinder;
Cylinder.__base = Shape;
Cylinder.__cache = {};
Module['Cylinder'] = Cylinder;
Object.defineProperty(Cylinder.prototype, "radius", {
    get: function() {
        return _mud_Cylinder__get_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Cylinder.radius: expected number');
        _mud_Cylinder__set_radius(this.__ptr, value);
    }
});
Object.defineProperty(Cylinder.prototype, "height", {
    get: function() {
        return _mud_Cylinder__get_height(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Cylinder.height: expected number');
        _mud_Cylinder__set_height(this.__ptr, value);
    }
});
Object.defineProperty(Cylinder.prototype, "axis", {
    get: function() {
        return _mud_Cylinder__get_axis(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Cylinder.axis: expected integer');
        _mud_Cylinder__set_axis(this.__ptr, value);
    }
});
Cylinder.prototype["__destroy"] = Cylinder.prototype.__destroy = function() {
    _mud_Cylinder__destroy(this.__ptr);
};
// Capsule
function Capsule(a0, a1, a2) {
    if (a0 === undefined) {  }
    else if (a2 === undefined) { if (typeof a0 !== 'number') throw Error('Capsule(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('Capsule(1:height): expected number'); }
    else { if (typeof a0 !== 'number') throw Error('Capsule(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('Capsule(1:height): expected number'); if (typeof a2 !== 'number') throw Error('Capsule(2:axis): expected integer'); }
    if (a0 === undefined) { this.__ptr = _mud_Capsule__construct_0(); getCache(Capsule)[this.__ptr] = this; }
    else if (a2 === undefined) { this.__ptr = _mud_Capsule__construct_2(/*radius*/a0, /*height*/a1); getCache(Capsule)[this.__ptr] = this; }
    else { this.__ptr = _mud_Capsule__construct_3(/*radius*/a0, /*height*/a1, /*axis*/a2); getCache(Capsule)[this.__ptr] = this; }
};
Capsule.prototype = Object.create(Shape.prototype);
Capsule.prototype.constructor = Capsule;
Capsule.prototype.__class = Capsule;
Capsule.__base = Shape;
Capsule.__cache = {};
Module['Capsule'] = Capsule;
Object.defineProperty(Capsule.prototype, "radius", {
    get: function() {
        return _mud_Capsule__get_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Capsule.radius: expected number');
        _mud_Capsule__set_radius(this.__ptr, value);
    }
});
Object.defineProperty(Capsule.prototype, "height", {
    get: function() {
        return _mud_Capsule__get_height(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Capsule.height: expected number');
        _mud_Capsule__set_height(this.__ptr, value);
    }
});
Object.defineProperty(Capsule.prototype, "axis", {
    get: function() {
        return _mud_Capsule__get_axis(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Capsule.axis: expected integer');
        _mud_Capsule__set_axis(this.__ptr, value);
    }
});
Capsule.prototype["__destroy"] = Capsule.prototype.__destroy = function() {
    _mud_Capsule__destroy(this.__ptr);
};
// Cube
function Cube(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (!checkClass(a0, v3_float)) throw Error('Cube(0:extents): expected v3<float>'); }
    else { if (!checkClass(a0, v3_float)) throw Error('Cube(0:center): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('Cube(1:extents): expected v3<float>'); }
    if (a0 === undefined) { this.__ptr = _mud_Cube__construct_0(); getCache(Cube)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _mud_Cube__construct_1(/*extents*/a0.__ptr); getCache(Cube)[this.__ptr] = this; }
    else { this.__ptr = _mud_Cube__construct_2(/*center*/a0.__ptr, /*extents*/a1.__ptr); getCache(Cube)[this.__ptr] = this; }
};
Cube.prototype = Object.create(Shape.prototype);
Cube.prototype.constructor = Cube;
Cube.prototype.__class = Cube;
Cube.__base = Shape;
Cube.__cache = {};
Module['Cube'] = Cube;
Object.defineProperty(Cube.prototype, "extents", {
    get: function() {
        return wrapPointer(_mud_Cube__get_extents(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Cube.extents: expected v3<float>');
        _mud_Cube__set_extents(this.__ptr, value.__ptr);
    }
});
Cube.prototype["__destroy"] = Cube.prototype.__destroy = function() {
    _mud_Cube__destroy(this.__ptr);
};
// Tetraedr
function Tetraedr(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('Tetraedr(0:radius): expected number'); }
    else { if (!checkClass(a0, v3_float)) throw Error('Tetraedr(0:center): expected v3<float>'); if (typeof a1 !== 'number') throw Error('Tetraedr(1:radius): expected number'); }
    if (a0 === undefined) { this.__ptr = _mud_Tetraedr__construct_0(); getCache(Tetraedr)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _mud_Tetraedr__construct_1(/*radius*/a0); getCache(Tetraedr)[this.__ptr] = this; }
    else { this.__ptr = _mud_Tetraedr__construct_2(/*center*/a0.__ptr, /*radius*/a1); getCache(Tetraedr)[this.__ptr] = this; }
};
Tetraedr.prototype = Object.create(Shape.prototype);
Tetraedr.prototype.constructor = Tetraedr;
Tetraedr.prototype.__class = Tetraedr;
Tetraedr.__base = Shape;
Tetraedr.__cache = {};
Module['Tetraedr'] = Tetraedr;
Object.defineProperty(Tetraedr.prototype, "radius", {
    get: function() {
        return _mud_Tetraedr__get_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Tetraedr.radius: expected number');
        _mud_Tetraedr__set_radius(this.__ptr, value);
    }
});
Tetraedr.prototype["__destroy"] = Tetraedr.prototype.__destroy = function() {
    _mud_Tetraedr__destroy(this.__ptr);
};
// Sphere
function Sphere(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('Sphere(0:radius): expected number'); }
    else if (a2 === undefined) { if (typeof a0 !== 'number') throw Error('Sphere(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('Sphere(1:start): expected number'); }
    else if (a3 === undefined) { if (typeof a0 !== 'number') throw Error('Sphere(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('Sphere(1:start): expected number'); if (typeof a2 !== 'number') throw Error('Sphere(2:end): expected number'); }
    else { if (!checkClass(a0, v3_float)) throw Error('Sphere(0:center): expected v3<float>'); if (typeof a1 !== 'number') throw Error('Sphere(1:radius): expected number'); if (typeof a2 !== 'number') throw Error('Sphere(2:start): expected number'); if (typeof a3 !== 'number') throw Error('Sphere(3:end): expected number'); }
    if (a0 === undefined) { this.__ptr = _mud_Sphere__construct_0(); getCache(Sphere)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _mud_Sphere__construct_1(/*radius*/a0); getCache(Sphere)[this.__ptr] = this; }
    else if (a2 === undefined) { this.__ptr = _mud_Sphere__construct_2(/*radius*/a0, /*start*/a1); getCache(Sphere)[this.__ptr] = this; }
    else if (a3 === undefined) { this.__ptr = _mud_Sphere__construct_3(/*radius*/a0, /*start*/a1, /*end*/a2); getCache(Sphere)[this.__ptr] = this; }
    else { this.__ptr = _mud_Sphere__construct_4(/*center*/a0.__ptr, /*radius*/a1, /*start*/a2, /*end*/a3); getCache(Sphere)[this.__ptr] = this; }
};
Sphere.prototype = Object.create(Shape.prototype);
Sphere.prototype.constructor = Sphere;
Sphere.prototype.__class = Sphere;
Sphere.__base = Shape;
Sphere.__cache = {};
Module['Sphere'] = Sphere;
Object.defineProperty(Sphere.prototype, "radius", {
    get: function() {
        return _mud_Sphere__get_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Sphere.radius: expected number');
        _mud_Sphere__set_radius(this.__ptr, value);
    }
});
Object.defineProperty(Sphere.prototype, "start", {
    get: function() {
        return _mud_Sphere__get_start(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Sphere.start: expected number');
        _mud_Sphere__set_start(this.__ptr, value);
    }
});
Object.defineProperty(Sphere.prototype, "end", {
    get: function() {
        return _mud_Sphere__get_end(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Sphere.end: expected number');
        _mud_Sphere__set_end(this.__ptr, value);
    }
});
Sphere.prototype["__destroy"] = Sphere.prototype.__destroy = function() {
    _mud_Sphere__destroy(this.__ptr);
};
// SphereRing
function SphereRing(a0, a1, a2) {
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'number') throw Error('SphereRing(0:radius): expected number'); if (typeof a1 !== 'number') throw Error('SphereRing(1:min): expected number'); if (typeof a2 !== 'number') throw Error('SphereRing(2:max): expected number'); }
    if (a0 === undefined) { this.__ptr = _mud_SphereRing__construct_0(); getCache(SphereRing)[this.__ptr] = this; }
    else { this.__ptr = _mud_SphereRing__construct_3(/*radius*/a0, /*min*/a1, /*max*/a2); getCache(SphereRing)[this.__ptr] = this; }
};
SphereRing.prototype = Object.create(Shape.prototype);
SphereRing.prototype.constructor = SphereRing;
SphereRing.prototype.__class = SphereRing;
SphereRing.__base = Shape;
SphereRing.__cache = {};
Module['SphereRing'] = SphereRing;
Object.defineProperty(SphereRing.prototype, "radius", {
    get: function() {
        return _mud_SphereRing__get_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('SphereRing.radius: expected number');
        _mud_SphereRing__set_radius(this.__ptr, value);
    }
});
Object.defineProperty(SphereRing.prototype, "min", {
    get: function() {
        return _mud_SphereRing__get_min(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('SphereRing.min: expected number');
        _mud_SphereRing__set_min(this.__ptr, value);
    }
});
Object.defineProperty(SphereRing.prototype, "max", {
    get: function() {
        return _mud_SphereRing__get_max(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('SphereRing.max: expected number');
        _mud_SphereRing__set_max(this.__ptr, value);
    }
});
SphereRing.prototype["__destroy"] = SphereRing.prototype.__destroy = function() {
    _mud_SphereRing__destroy(this.__ptr);
};
// Spheroid
function Spheroid(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('Spheroid(0:radius): expected number'); }
    else { if (!checkClass(a0, v3_float)) throw Error('Spheroid(0:center): expected v3<float>'); if (typeof a1 !== 'number') throw Error('Spheroid(1:radius): expected number'); }
    if (a0 === undefined) { this.__ptr = _mud_Spheroid__construct_0(); getCache(Spheroid)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _mud_Spheroid__construct_1(/*radius*/a0); getCache(Spheroid)[this.__ptr] = this; }
    else { this.__ptr = _mud_Spheroid__construct_2(/*center*/a0.__ptr, /*radius*/a1); getCache(Spheroid)[this.__ptr] = this; }
};
Spheroid.prototype = Object.create(Shape.prototype);
Spheroid.prototype.constructor = Spheroid;
Spheroid.prototype.__class = Spheroid;
Spheroid.__base = Shape;
Spheroid.__cache = {};
Module['Spheroid'] = Spheroid;
Object.defineProperty(Spheroid.prototype, "radius", {
    get: function() {
        return _mud_Spheroid__get_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Spheroid.radius: expected number');
        _mud_Spheroid__set_radius(this.__ptr, value);
    }
});
Spheroid.prototype["__destroy"] = Spheroid.prototype.__destroy = function() {
    _mud_Spheroid__destroy(this.__ptr);
};
// Icosaedr
function Icosaedr(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('Icosaedr(0:radius): expected number'); }
    else { if (!checkClass(a0, v3_float)) throw Error('Icosaedr(0:center): expected v3<float>'); if (typeof a1 !== 'number') throw Error('Icosaedr(1:radius): expected number'); }
    if (a0 === undefined) { this.__ptr = _mud_Icosaedr__construct_0(); getCache(Icosaedr)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _mud_Icosaedr__construct_1(/*radius*/a0); getCache(Icosaedr)[this.__ptr] = this; }
    else { this.__ptr = _mud_Icosaedr__construct_2(/*center*/a0.__ptr, /*radius*/a1); getCache(Icosaedr)[this.__ptr] = this; }
};
Icosaedr.prototype = Object.create(Shape.prototype);
Icosaedr.prototype.constructor = Icosaedr;
Icosaedr.prototype.__class = Icosaedr;
Icosaedr.__base = Shape;
Icosaedr.__cache = {};
Module['Icosaedr'] = Icosaedr;
Object.defineProperty(Icosaedr.prototype, "radius", {
    get: function() {
        return _mud_Icosaedr__get_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Icosaedr.radius: expected number');
        _mud_Icosaedr__set_radius(this.__ptr, value);
    }
});
Icosaedr.prototype["__destroy"] = Icosaedr.prototype.__destroy = function() {
    _mud_Icosaedr__destroy(this.__ptr);
};
// Distribution
function Distribution() { throw "cannot construct a Distribution, no constructor in IDL" }
Distribution.prototype = Object.create(WrapperObject.prototype);
Distribution.prototype.constructor = Distribution;
Distribution.prototype.__class = Distribution;
Distribution.__cache = {};
Module['Distribution'] = Distribution;
Distribution.prototype["__destroy"] = Distribution.prototype.__destroy = function() {
    _mud_Distribution__destroy(this.__ptr);
};
// Poisson
function Poisson(a0, a1) {
    if (!checkClass(a0, v2_float)) throw Error('Poisson(0:size): expected v2<float>'); if (typeof a1 !== 'number') throw Error('Poisson(1:maxRadius): expected number');
    this.__ptr = _mud_Poisson__construct_2(/*size*/a0.__ptr, /*maxRadius*/a1); getCache(Poisson)[this.__ptr] = this;
};
Poisson.prototype = Object.create(Distribution.prototype);
Poisson.prototype.constructor = Poisson;
Poisson.prototype.__class = Poisson;
Poisson.__base = Distribution;
Poisson.__cache = {};
Module['Poisson'] = Poisson;
Poisson.prototype["distribute"] = Poisson.prototype.distribute = function(a0) {
    if (typeof a0 !== 'number') throw Error('distribute(0:radius): expected number');
    return _mud_Poisson_distribute_1(this.__ptr, /*radius*/a0);
};
Poisson.prototype["addPoint"] = Poisson.prototype.addPoint = function(a0, a1) {
    if (typeof a0 !== 'number') throw Error('addPoint(0:radius): expected number'); if (!checkClass(a1, v3_float)) throw Error('addPoint(1:point): expected v3<float>');
    return !!(_mud_Poisson_addPoint_2(this.__ptr, /*radius*/a0, /*point*/a1.__ptr));
};
Poisson.prototype["__destroy"] = Poisson.prototype.__destroy = function() {
    _mud_Poisson__destroy(this.__ptr);
};
// Polygon
function Polygon(a0) {
    if (a0 === undefined) {  }
    else {  }
    if (a0 === undefined) { this.__ptr = _mud_Polygon__construct_0(); getCache(Polygon)[this.__ptr] = this; }
    else { this.__ptr = _mud_Polygon__construct_1(ensureFloat32(/*vertices*/a0), /*vertices*/a0.length); getCache(Polygon)[this.__ptr] = this; }
};
Polygon.prototype = Object.create(Shape.prototype);
Polygon.prototype.constructor = Polygon;
Polygon.prototype.__class = Polygon;
Polygon.__base = Shape;
Polygon.__cache = {};
Module['Polygon'] = Polygon;
Polygon.prototype["__destroy"] = Polygon.prototype.__destroy = function() {
    _mud_Polygon__destroy(this.__ptr);
};
// Box
function Box() {
    
    this.__ptr = _mud_Box__construct_0(); getCache(Box)[this.__ptr] = this;
};
Box.prototype = Object.create(Shape.prototype);
Box.prototype.constructor = Box;
Box.prototype.__class = Box;
Box.__base = Shape;
Box.__cache = {};
Module['Box'] = Box;
Box.prototype["__destroy"] = Box.prototype.__destroy = function() {
    _mud_Box__destroy(this.__ptr);
};
// Points
function Points(a0) {
    if (a0 === undefined) {  }
    else {  }
    if (a0 === undefined) { this.__ptr = _mud_Points__construct_0(); getCache(Points)[this.__ptr] = this; }
    else { this.__ptr = _mud_Points__construct_1(ensureFloat32(/*points*/a0), /*points*/a0.length); getCache(Points)[this.__ptr] = this; }
};
Points.prototype = Object.create(Shape.prototype);
Points.prototype.constructor = Points;
Points.prototype.__class = Points;
Points.__base = Shape;
Points.__cache = {};
Module['Points'] = Points;
Object.defineProperty(Points.prototype, "points", {
    get: function() {
        return _mud_Points__get_points(this.__ptr);
    }});
Points.prototype["__destroy"] = Points.prototype.__destroy = function() {
    _mud_Points__destroy(this.__ptr);
};
// Grid3
function Grid3(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (!checkClass(a0, v2_uint)) throw Error('Grid3(0:size): expected v2<uint>'); }
    else { if (!checkClass(a0, v2_uint)) throw Error('Grid3(0:size): expected v2<uint>');  }
    if (a0 === undefined) { this.__ptr = _mud_Grid3__construct_0(); getCache(Grid3)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _mud_Grid3__construct_1(/*size*/a0.__ptr); getCache(Grid3)[this.__ptr] = this; }
    else { this.__ptr = _mud_Grid3__construct_2(/*size*/a0.__ptr, ensureFloat32(/*points*/a1), /*points*/a1.length); getCache(Grid3)[this.__ptr] = this; }
};
Grid3.prototype = Object.create(Shape.prototype);
Grid3.prototype.constructor = Grid3;
Grid3.prototype.__class = Grid3;
Grid3.__base = Shape;
Grid3.__cache = {};
Module['Grid3'] = Grid3;
Object.defineProperty(Grid3.prototype, "size", {
    get: function() {
        return wrapPointer(_mud_Grid3__get_size(this.__ptr), v2_uint);
    },
    set: function(value) {
        if (!checkClass(value, v2_uint)) throw Error('Grid3.size: expected v2<uint>');
        _mud_Grid3__set_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Grid3.prototype, "points", {
    get: function() {
        return _mud_Grid3__get_points(this.__ptr);
    }});
Grid3.prototype["__destroy"] = Grid3.prototype.__destroy = function() {
    _mud_Grid3__destroy(this.__ptr);
};
// ConvexHull
function ConvexHull(a0) {
    if (a0 === undefined) {  }
    else {  }
    if (a0 === undefined) { this.__ptr = _mud_ConvexHull__construct_0(); getCache(ConvexHull)[this.__ptr] = this; }
    else { this.__ptr = _mud_ConvexHull__construct_1(ensureFloat32(/*vertices*/a0), /*vertices*/a0.length); getCache(ConvexHull)[this.__ptr] = this; }
};
ConvexHull.prototype = Object.create(Shape.prototype);
ConvexHull.prototype.constructor = ConvexHull;
ConvexHull.prototype.__class = ConvexHull;
ConvexHull.__base = Shape;
ConvexHull.__cache = {};
Module['ConvexHull'] = ConvexHull;
Object.defineProperty(ConvexHull.prototype, "vertices", {
    get: function() {
        return _mud_ConvexHull__get_vertices(this.__ptr);
    }});
ConvexHull.prototype["__destroy"] = ConvexHull.prototype.__destroy = function() {
    _mud_ConvexHull__destroy(this.__ptr);
};
// Symbol
function Symbol(a0, a1, a2, a3, a4) {
    if (a1 === undefined) { if (!checkClass(a0, Colour)) throw Error('Symbol(0:fill): expected Colour'); }
    else if (a2 === undefined) { if (!checkClass(a0, Colour)) throw Error('Symbol(0:fill): expected Colour'); if (!checkClass(a1, Colour)) throw Error('Symbol(1:outline): expected Colour'); }
    else if (a3 === undefined) { if (!checkClass(a0, Colour)) throw Error('Symbol(0:fill): expected Colour'); if (!checkClass(a1, Colour)) throw Error('Symbol(1:outline): expected Colour'); if (typeof a2 !== 'boolean') throw Error('Symbol(2:overlay): expected boolean'); }
    else if (a4 === undefined) { if (!checkClass(a0, Colour)) throw Error('Symbol(0:fill): expected Colour'); if (!checkClass(a1, Colour)) throw Error('Symbol(1:outline): expected Colour'); if (typeof a2 !== 'boolean') throw Error('Symbol(2:overlay): expected boolean'); if (typeof a3 !== 'boolean') throw Error('Symbol(3:double_sided): expected boolean'); }
    else { if (!checkClass(a0, Colour)) throw Error('Symbol(0:fill): expected Colour'); if (!checkClass(a1, Colour)) throw Error('Symbol(1:outline): expected Colour'); if (typeof a2 !== 'boolean') throw Error('Symbol(2:overlay): expected boolean'); if (typeof a3 !== 'boolean') throw Error('Symbol(3:double_sided): expected boolean'); if (typeof a4 !== 'number') throw Error('Symbol(4:detail): expected integer'); }
    if (a1 === undefined) { this.__ptr = _mud_Symbol__construct_1(/*fill*/a0.__ptr); getCache(Symbol)[this.__ptr] = this; }
    else if (a2 === undefined) { this.__ptr = _mud_Symbol__construct_2(/*fill*/a0.__ptr, /*outline*/a1.__ptr); getCache(Symbol)[this.__ptr] = this; }
    else if (a3 === undefined) { this.__ptr = _mud_Symbol__construct_3(/*fill*/a0.__ptr, /*outline*/a1.__ptr, /*overlay*/a2); getCache(Symbol)[this.__ptr] = this; }
    else if (a4 === undefined) { this.__ptr = _mud_Symbol__construct_4(/*fill*/a0.__ptr, /*outline*/a1.__ptr, /*overlay*/a2, /*double_sided*/a3); getCache(Symbol)[this.__ptr] = this; }
    else { this.__ptr = _mud_Symbol__construct_5(/*fill*/a0.__ptr, /*outline*/a1.__ptr, /*overlay*/a2, /*double_sided*/a3, /*detail*/a4); getCache(Symbol)[this.__ptr] = this; }
};
Symbol.prototype = Object.create(WrapperObject.prototype);
Symbol.prototype.constructor = Symbol;
Symbol.prototype.__class = Symbol;
Symbol.__cache = {};
Module['Symbol'] = Symbol;
Object.defineProperty(Symbol.prototype, "outline", {
    get: function() {
        return wrapPointer(_mud_Symbol__get_outline(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('Symbol.outline: expected Colour');
        _mud_Symbol__set_outline(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Symbol.prototype, "fill", {
    get: function() {
        return wrapPointer(_mud_Symbol__get_fill(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('Symbol.fill: expected Colour');
        _mud_Symbol__set_fill(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Symbol.prototype, "overlay", {
    get: function() {
        return !!(_mud_Symbol__get_overlay(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Symbol.overlay: expected boolean');
        _mud_Symbol__set_overlay(this.__ptr, value);
    }
});
Object.defineProperty(Symbol.prototype, "double_sided", {
    get: function() {
        return !!(_mud_Symbol__get_double_sided(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Symbol.double_sided: expected boolean');
        _mud_Symbol__set_double_sided(this.__ptr, value);
    }
});
Object.defineProperty(Symbol.prototype, "detail", {
    get: function() {
        return _mud_Symbol__get_detail(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Symbol.detail: expected integer');
        _mud_Symbol__set_detail(this.__ptr, value);
    }
});
Object.defineProperty(Symbol.prototype, "subdiv", {
    get: function() {
        return wrapPointer(_mud_Symbol__get_subdiv(this.__ptr), v2_uint);
    },
    set: function(value) {
        if (!checkClass(value, v2_uint)) throw Error('Symbol.subdiv: expected v2<uint>');
        _mud_Symbol__set_subdiv(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Symbol.prototype, "image", {
    get: function() {
        return UTF8ToString(_mud_Symbol__get_image(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Symbol.image: expected string');
        _mud_Symbol__set_image(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Symbol.prototype, "image256", {
    get: function() {
        return wrapPointer(_mud_Symbol__get_image256(this.__ptr), Image256);
    },
    set: function(value) {
        if (!checkClass(value, Image256)) throw Error('Symbol.image256: expected Image256');
        _mud_Symbol__set_image256(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Symbol.prototype, "program", {
    get: function() {
        return UTF8ToString(_mud_Symbol__get_program(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Symbol.program: expected string');
        _mud_Symbol__set_program(this.__ptr, ensureString(value));
    }
});
Symbol.prototype["__destroy"] = Symbol.prototype.__destroy = function() {
    _mud_Symbol__destroy(this.__ptr);
};
// MarchingCubes
function MarchingCubes(a0) {
    if (typeof a0 !== 'number') throw Error('MarchingCubes(0:resolution): expected integer');
    this.__ptr = _mud_MarchingCubes__construct_1(/*resolution*/a0); getCache(MarchingCubes)[this.__ptr] = this;
};
MarchingCubes.prototype = Object.create(WrapperObject.prototype);
MarchingCubes.prototype.constructor = MarchingCubes;
MarchingCubes.prototype.__class = MarchingCubes;
MarchingCubes.__cache = {};
Module['MarchingCubes'] = MarchingCubes;
MarchingCubes.prototype["reset"] = MarchingCubes.prototype.reset = function() {
    
    _mud_MarchingCubes_reset_0(this.__ptr);
};
MarchingCubes.prototype["count"] = MarchingCubes.prototype.count = function() {
    
    return _mud_MarchingCubes_count_0(this.__ptr);
};
MarchingCubes.prototype["direct"] = MarchingCubes.prototype.direct = function(a0) {
    if (!checkClass(a0, MeshAdapter)) throw Error('direct(0:output): expected MeshAdapter');
    _mud_MarchingCubes_direct_1(this.__ptr, /*output*/a0.__ptr);
};
MarchingCubes.prototype["render"] = MarchingCubes.prototype.render = function(a0) {
    if (!checkClass(a0, MeshPacker)) throw Error('render(0:output): expected MeshPacker');
    _mud_MarchingCubes_render_1(this.__ptr, /*output*/a0.__ptr);
};
Object.defineProperty(MarchingCubes.prototype, "isolation", {
    get: function() {
        return _mud_MarchingCubes__get_isolation(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('MarchingCubes.isolation: expected number');
        _mud_MarchingCubes__set_isolation(this.__ptr, value);
    }
});
Object.defineProperty(MarchingCubes.prototype, "subdiv", {
    get: function() {
        return _mud_MarchingCubes__get_subdiv(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('MarchingCubes.subdiv: expected integer');
        _mud_MarchingCubes__set_subdiv(this.__ptr, value);
    }
});
MarchingCubes.prototype["__destroy"] = MarchingCubes.prototype.__destroy = function() {
    _mud_MarchingCubes__destroy(this.__ptr);
};
Module['to_ray'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, v3_float)) throw Error('to_ray(0:pos): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('to_ray(1:dir): expected v3<float>'); }
    else { if (!checkClass(a0, v3_float)) throw Error('to_ray(0:pos): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('to_ray(1:dir): expected v3<float>'); if (typeof a2 !== 'number') throw Error('to_ray(2:distance): expected number'); }
    if (a2 === undefined) { return wrapPointer(_mud_to_ray_2(/*pos*/a0.__ptr, /*dir*/a1.__ptr), Ray); }
    else { return wrapPointer(_mud_to_ray_3(/*pos*/a0.__ptr, /*dir*/a1.__ptr, /*distance*/a2), Ray); }
};
Module['to_segment'] = function(a0) {
    if (!checkClass(a0, Ray)) throw Error('to_segment(0:ray): expected Ray');
    return wrapPointer(_mud_to_segment_1(/*ray*/a0.__ptr), Segment);
};
Module['distribute_poisson'] = function(a0, a1) {
    if (!checkClass(a0, v2_float)) throw Error('distribute_poisson(0:size): expected v2<float>'); if (typeof a1 !== 'number') throw Error('distribute_poisson(1:radius): expected number');
    return _mud_distribute_poisson_2(/*size*/a0.__ptr, /*radius*/a1);
};
Module['add_ball'] = function(a0, a1, a2, a3, a4) {
    if (a4 === undefined) { if (!checkClass(a0, MarchingCubes)) throw Error('add_ball(0:cubes): expected MarchingCubes'); if (!checkClass(a1, v3_float)) throw Error('add_ball(1:ball): expected v3<float>'); if (typeof a2 !== 'number') throw Error('add_ball(2:strength): expected number'); if (typeof a3 !== 'number') throw Error('add_ball(3:subtract): expected number'); }
    else { if (!checkClass(a0, MarchingCubes)) throw Error('add_ball(0:cubes): expected MarchingCubes'); if (!checkClass(a1, v3_float)) throw Error('add_ball(1:ball): expected v3<float>'); if (typeof a2 !== 'number') throw Error('add_ball(2:strength): expected number'); if (typeof a3 !== 'number') throw Error('add_ball(3:subtract): expected number'); if (!checkClass(a4, Colour)) throw Error('add_ball(4:colour): expected Colour'); }
    if (a4 === undefined) { _mud_add_ball_4(/*cubes*/a0.__ptr, /*ball*/a1.__ptr, /*strength*/a2, /*subtract*/a3); }
    else { _mud_add_ball_5(/*cubes*/a0.__ptr, /*ball*/a1.__ptr, /*strength*/a2, /*subtract*/a3, /*colour*/a4.__ptr); }
};
Module['add_planeX'] = function(a0, a1, a2) {
    if (!checkClass(a0, MarchingCubes)) throw Error('add_planeX(0:cubes): expected MarchingCubes'); if (typeof a1 !== 'number') throw Error('add_planeX(1:strength): expected number'); if (typeof a2 !== 'number') throw Error('add_planeX(2:subtract): expected number');
    _mud_add_planeX_3(/*cubes*/a0.__ptr, /*strength*/a1, /*subtract*/a2);
};
Module['add_planeY'] = function(a0, a1, a2) {
    if (!checkClass(a0, MarchingCubes)) throw Error('add_planeY(0:cubes): expected MarchingCubes'); if (typeof a1 !== 'number') throw Error('add_planeY(1:strength): expected number'); if (typeof a2 !== 'number') throw Error('add_planeY(2:subtract): expected number');
    _mud_add_planeY_3(/*cubes*/a0.__ptr, /*strength*/a1, /*subtract*/a2);
};
Module['add_planeZ'] = function(a0, a1, a2) {
    if (!checkClass(a0, MarchingCubes)) throw Error('add_planeZ(0:cubes): expected MarchingCubes'); if (typeof a1 !== 'number') throw Error('add_planeZ(1:strength): expected number'); if (typeof a2 !== 'number') throw Error('add_planeZ(2:subtract): expected number');
    _mud_add_planeZ_3(/*cubes*/a0.__ptr, /*strength*/a1, /*subtract*/a2);
};

(function() {
    function setup() {
        Aabb.prototype.__type = _mud_Aabb__type();
        Curve2.prototype.__type = _mud_Curve2__type();
        Curve3.prototype.__type = _mud_Curve3__type();
        CurveSpline.prototype.__type = _mud_CurveSpline__type();
        CurveSpline3.prototype.__type = _mud_CurveSpline3__type();
        CurveBezierCubic.prototype.__type = _mud_CurveBezierCubic__type();
        CurveBezierCubic3.prototype.__type = _mud_CurveBezierCubic3__type();
        CurveLine.prototype.__type = _mud_CurveLine__type();
        CurveLine3.prototype.__type = _mud_CurveLine3__type();
        CurveBezierQuadratic.prototype.__type = _mud_CurveBezierQuadratic__type();
        CurveBezierQuadratic3.prototype.__type = _mud_CurveBezierQuadratic3__type();
        CurveCatmullRom3.prototype.__type = _mud_CurveCatmullRom3__type();
        Plane.prototype.__type = _mud_Plane__type();
        Plane3.prototype.__type = _mud_Plane3__type();
        Face3.prototype.__type = _mud_Face3__type();
        Segment.prototype.__type = _mud_Segment__type();
        Ray.prototype.__type = _mud_Ray__type();
        MeshAdapter.prototype.__type = _mud_MeshAdapter__type();
        Shape.prototype.__type = _mud_Shape__type();
        ShapeVar.prototype.__type = _mud_ShapeVar__type();
        Geometry.prototype.__type = _mud_Geometry__type();
        MeshPacker.prototype.__type = _mud_MeshPacker__type();
        Line.prototype.__type = _mud_Line__type();
        Rect.prototype.__type = _mud_Rect__type();
        Quad.prototype.__type = _mud_Quad__type();
        Grid2.prototype.__type = _mud_Grid2__type();
        Triangle.prototype.__type = _mud_Triangle__type();
        Circle.prototype.__type = _mud_Circle__type();
        Torus.prototype.__type = _mud_Torus__type();
        TorusKnot.prototype.__type = _mud_TorusKnot__type();
        Ring.prototype.__type = _mud_Ring__type();
        Ellipsis.prototype.__type = _mud_Ellipsis__type();
        Arc.prototype.__type = _mud_Arc__type();
        ArcLine.prototype.__type = _mud_ArcLine__type();
        Cylinder.prototype.__type = _mud_Cylinder__type();
        Capsule.prototype.__type = _mud_Capsule__type();
        Cube.prototype.__type = _mud_Cube__type();
        Tetraedr.prototype.__type = _mud_Tetraedr__type();
        Sphere.prototype.__type = _mud_Sphere__type();
        SphereRing.prototype.__type = _mud_SphereRing__type();
        Spheroid.prototype.__type = _mud_Spheroid__type();
        Icosaedr.prototype.__type = _mud_Icosaedr__type();
        Distribution.prototype.__type = _mud_Distribution__type();
        Poisson.prototype.__type = _mud_Poisson__type();
        Polygon.prototype.__type = _mud_Polygon__type();
        Box.prototype.__type = _mud_Box__type();
        Points.prototype.__type = _mud_Points__type();
        Grid3.prototype.__type = _mud_Grid3__type();
        ConvexHull.prototype.__type = _mud_ConvexHull__type();
        Symbol.prototype.__type = _mud_Symbol__type();
        MarchingCubes.prototype.__type = _mud_MarchingCubes__type();
        // CatmullType
        Module['CatmullType'] = Module['CatmullType'] || {};
        Module['CatmullType']['Centripetal'] = _mud_CatmullType_Centripetal();
        Module['CatmullType']['Chordal'] = _mud_CatmullType_Chordal();
        Module['CatmullType']['CatmullRom'] = _mud_CatmullType_CatmullRom();
        // DrawMode
        Module['OUTLINE'] = _mud_DrawMode_OUTLINE();
        Module['PLAIN'] = _mud_DrawMode_PLAIN();
        // PrimitiveType
        Module['PrimitiveType'] = Module['PrimitiveType'] || {};
        Module['PrimitiveType']['Points'] = _mud_PrimitiveType_Points();
        Module['PrimitiveType']['Lines'] = _mud_PrimitiveType_Lines();
        Module['PrimitiveType']['LineStrip'] = _mud_PrimitiveType_LineStrip();
        Module['PrimitiveType']['Triangles'] = _mud_PrimitiveType_Triangles();
        Module['PrimitiveType']['TriangleStrip'] = _mud_PrimitiveType_TriangleStrip();
        Module['PrimitiveType']['TriangleFan'] = _mud_PrimitiveType_TriangleFan();
        Module['PrimitiveType']['Count'] = _mud_PrimitiveType_Count();
        // SymbolDetail
        Module['SymbolDetail'] = Module['SymbolDetail'] || {};
        Module['SymbolDetail']['Lowest'] = _mud_SymbolDetail_Lowest();
        Module['SymbolDetail']['Low'] = _mud_SymbolDetail_Low();
        Module['SymbolDetail']['Medium'] = _mud_SymbolDetail_Medium();
        Module['SymbolDetail']['High'] = _mud_SymbolDetail_High();
        Module['SymbolDetail']['Highest'] = _mud_SymbolDetail_Highest();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
