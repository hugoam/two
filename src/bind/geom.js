Module['stl'] = Module['stl'] || {};
// Aabb
function Aabb(center, extents) {
    /* center <mud::vec3> [] */
    if (typeof center !== "undefined" && center !== null) { center = center.ptr; }
    /* extents <mud::vec3> [] */
    if (typeof extents !== "undefined" && extents !== null) { extents = extents.ptr; }
    if (center === undefined) { this.ptr = _mud_Aabb__construct_0(); getCache(Aabb)[this.ptr] = this; return; }
    this.ptr = _mud_Aabb__construct_2(center, extents); getCache(Aabb)[this.ptr] = this;
    this.type = Aabb;
};
Aabb.prototype = Object.create(WrapperObject.prototype);
Aabb.prototype.constructor = Aabb;
Aabb.prototype.__class__ = Aabb;
Aabb.__cache__ = {};
Module['Aabb'] = Aabb;
Object.defineProperty(Aabb.prototype, "center", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Aabb__get_center(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Aabb__set_center(self, value);
    }
});
Object.defineProperty(Aabb.prototype, "extents", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Aabb__get_extents(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Aabb__set_extents(self, value);
    }
});
Object.defineProperty(Aabb.prototype, "empty", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Aabb__get_empty(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_Aabb__set_empty(self, value);
    }
});
Aabb.prototype["__destroy__"] = Aabb.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Aabb__destroy(self);
};
// Distribution
function Distribution() { throw "cannot construct a Distribution, no constructor in IDL" }
Distribution.prototype = Object.create(WrapperObject.prototype);
Distribution.prototype.constructor = Distribution;
Distribution.prototype.__class__ = Distribution;
Distribution.__cache__ = {};
Module['Distribution'] = Distribution;
Distribution.prototype["__destroy__"] = Distribution.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Distribution__destroy(self);
};
// Face3
function Face3() {
    this.ptr = _mud_Face3__construct_0(); getCache(Face3)[this.ptr] = this;
    this.type = Face3;
};
Face3.prototype = Object.create(WrapperObject.prototype);
Face3.prototype.constructor = Face3;
Face3.prototype.__class__ = Face3;
Face3.__cache__ = {};
Module['Face3'] = Face3;
Face3.prototype["__destroy__"] = Face3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Face3__destroy(self);
};
// MeshPacker
function MeshPacker() {
    this.ptr = _mud_MeshPacker__construct_0(); getCache(MeshPacker)[this.ptr] = this;
    this.type = MeshPacker;
};
MeshPacker.prototype = Object.create(WrapperObject.prototype);
MeshPacker.prototype.constructor = MeshPacker;
MeshPacker.prototype.__class__ = MeshPacker;
MeshPacker.__cache__ = {};
Module['MeshPacker'] = MeshPacker;
MeshPacker.prototype["__destroy__"] = MeshPacker.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_MeshPacker__destroy(self);
};
// Plane
function Plane() {
    this.ptr = _mud_Plane__construct_0(); getCache(Plane)[this.ptr] = this;
    this.type = Plane;
};
Plane.prototype = Object.create(WrapperObject.prototype);
Plane.prototype.constructor = Plane;
Plane.prototype.__class__ = Plane;
Plane.__cache__ = {};
Module['Plane'] = Plane;
Object.defineProperty(Plane.prototype, "normal", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Plane__get_normal(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Plane__set_normal(self, value);
    }
});
Object.defineProperty(Plane.prototype, "distance", {
    get: function() {
        var self = this.ptr;
        return _mud_Plane__get_distance(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Plane__set_distance(self, value);
    }
});
Plane.prototype["__destroy__"] = Plane.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Plane__destroy(self);
};
// Plane3
function Plane3() {
    this.ptr = _mud_Plane3__construct_0(); getCache(Plane3)[this.ptr] = this;
    this.type = Plane3;
};
Plane3.prototype = Object.create(WrapperObject.prototype);
Plane3.prototype.constructor = Plane3;
Plane3.prototype.__class__ = Plane3;
Plane3.__cache__ = {};
Module['Plane3'] = Plane3;
Object.defineProperty(Plane3.prototype, "origin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Plane3__get_origin(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Plane3__set_origin(self, value);
    }
});
Object.defineProperty(Plane3.prototype, "a", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Plane3__get_a(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Plane3__set_a(self, value);
    }
});
Object.defineProperty(Plane3.prototype, "b", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Plane3__get_b(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Plane3__set_b(self, value);
    }
});
Plane3.prototype["__destroy__"] = Plane3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Plane3__destroy(self);
};
// Ray
function Ray() {
    this.ptr = _mud_Ray__construct_0(); getCache(Ray)[this.ptr] = this;
    this.type = Ray;
};
Ray.prototype = Object.create(WrapperObject.prototype);
Ray.prototype.constructor = Ray;
Ray.prototype.__class__ = Ray;
Ray.__cache__ = {};
Module['Ray'] = Ray;
Object.defineProperty(Ray.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ray__get_start(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Ray__set_start(self, value);
    }
});
Object.defineProperty(Ray.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ray__get_end(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Ray__set_end(self, value);
    }
});
Object.defineProperty(Ray.prototype, "dir", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ray__get_dir(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Ray__set_dir(self, value);
    }
});
Object.defineProperty(Ray.prototype, "inv_dir", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ray__get_inv_dir(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Ray__set_inv_dir(self, value);
    }
});
Ray.prototype["__destroy__"] = Ray.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ray__destroy(self);
};
// Segment
function Segment() {
    this.ptr = _mud_Segment__construct_0(); getCache(Segment)[this.ptr] = this;
    this.type = Segment;
};
Segment.prototype = Object.create(WrapperObject.prototype);
Segment.prototype.constructor = Segment;
Segment.prototype.__class__ = Segment;
Segment.__cache__ = {};
Module['Segment'] = Segment;
Object.defineProperty(Segment.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Segment__get_start(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Segment__set_start(self, value);
    }
});
Object.defineProperty(Segment.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Segment__get_end(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Segment__set_end(self, value);
    }
});
Segment.prototype["__destroy__"] = Segment.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Segment__destroy(self);
};
// Shape
function Shape() { throw "cannot construct a Shape, no constructor in IDL" }
Shape.prototype = Object.create(WrapperObject.prototype);
Shape.prototype.constructor = Shape;
Shape.prototype.__class__ = Shape;
Shape.__cache__ = {};
Module['Shape'] = Shape;
Object.defineProperty(Shape.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shape__get_type(self), Type);
    }});
Shape.prototype["__destroy__"] = Shape.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Shape__destroy(self);
};
// ShapeVar
function ShapeVar(shape) {
    /* shape <mud::Shape> [] */
    if (typeof shape !== "undefined" && shape !== null) { shape = shape.ptr; }
    if (shape === undefined) { this.ptr = _mud_ShapeVar__construct_0(); getCache(ShapeVar)[this.ptr] = this; return; }
    this.ptr = _mud_ShapeVar__construct_1(shape); getCache(ShapeVar)[this.ptr] = this;
    this.type = ShapeVar;
};
ShapeVar.prototype = Object.create(WrapperObject.prototype);
ShapeVar.prototype.constructor = ShapeVar;
ShapeVar.prototype.__class__ = ShapeVar;
ShapeVar.__cache__ = {};
Module['ShapeVar'] = ShapeVar;
Object.defineProperty(ShapeVar.prototype, "shape", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ShapeVar__get_shape(self), Shape);
    }});
ShapeVar.prototype["__destroy__"] = ShapeVar.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ShapeVar__destroy(self);
};
// Symbol
function Symbol(fill, outline, overlay, double_sided, detail) {
    /* fill <mud::Colour> [] */
    if (typeof fill !== "undefined" && fill !== null) { fill = fill.ptr; }
    /* outline <mud::Colour> [] */
    if (typeof outline !== "undefined" && outline !== null) { outline = outline.ptr; }
    /* overlay <bool> [] */
    /* double_sided <bool> [] */
    /* detail <mud::SymbolDetail> [] */
    if (detail && typeof detail === "object") detail = detail.ptr;
    if (fill === undefined) { this.ptr = _mud_Symbol__construct_0(); getCache(Symbol)[this.ptr] = this; return; }
    if (outline === undefined) { this.ptr = _mud_Symbol__construct_1(fill); getCache(Symbol)[this.ptr] = this; return; }
    if (overlay === undefined) { this.ptr = _mud_Symbol__construct_2(fill, outline); getCache(Symbol)[this.ptr] = this; return; }
    if (double_sided === undefined) { this.ptr = _mud_Symbol__construct_3(fill, outline, overlay); getCache(Symbol)[this.ptr] = this; return; }
    if (detail === undefined) { this.ptr = _mud_Symbol__construct_4(fill, outline, overlay, double_sided); getCache(Symbol)[this.ptr] = this; return; }
    this.ptr = _mud_Symbol__construct_5(fill, outline, overlay, double_sided, detail); getCache(Symbol)[this.ptr] = this;
    this.type = Symbol;
};
Symbol.prototype = Object.create(WrapperObject.prototype);
Symbol.prototype.constructor = Symbol;
Symbol.prototype.__class__ = Symbol;
Symbol.__cache__ = {};
Module['Symbol'] = Symbol;
Object.defineProperty(Symbol.prototype, "outline", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Symbol__get_outline(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Colour> [] */
        value = value.ptr;
        _mud_Symbol__set_outline(self, value);
    }
});
Object.defineProperty(Symbol.prototype, "fill", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Symbol__get_fill(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Colour> [] */
        value = value.ptr;
        _mud_Symbol__set_fill(self, value);
    }
});
Object.defineProperty(Symbol.prototype, "overlay", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Symbol__get_overlay(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_Symbol__set_overlay(self, value);
    }
});
Object.defineProperty(Symbol.prototype, "double_sided", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Symbol__get_double_sided(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_Symbol__set_double_sided(self, value);
    }
});
Object.defineProperty(Symbol.prototype, "detail", {
    get: function() {
        var self = this.ptr;
        return _mud_Symbol__get_detail(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::SymbolDetail> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Symbol__set_detail(self, value);
    }
});
Object.defineProperty(Symbol.prototype, "image", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Symbol__get_image(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <const char*> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_Symbol__set_image(self, value);
    }
});
Object.defineProperty(Symbol.prototype, "image256", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Symbol__get_image256(self), Image256);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Image256> [] */
        value = value.ptr;
        _mud_Symbol__set_image256(self, value);
    }
});
Object.defineProperty(Symbol.prototype, "program", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Symbol__get_program(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <const char*> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_Symbol__set_program(self, value);
    }
});
Symbol.prototype["__destroy__"] = Symbol.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Symbol__destroy(self);
};
// Arc
function Arc(radius, start, end) {
    /* radius <float> [] */
    /* start <float> [] */
    /* end <float> [] */
    if (radius === undefined) { this.ptr = _mud_Arc__construct_0(); getCache(Arc)[this.ptr] = this; return; }
    this.ptr = _mud_Arc__construct_3(radius, start, end); getCache(Arc)[this.ptr] = this;
    this.type = Arc;
};
Arc.prototype = Object.create(Shape.prototype);
Arc.prototype.constructor = Arc;
Arc.prototype.__class__ = Arc;
Arc.__cache__ = {};
Module['Arc'] = Arc;
Object.defineProperty(Arc.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Arc__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Arc__set_radius(self, value);
    }
});
Object.defineProperty(Arc.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return _mud_Arc__get_start(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Arc__set_start(self, value);
    }
});
Object.defineProperty(Arc.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return _mud_Arc__get_end(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Arc__set_end(self, value);
    }
});
Arc.prototype["__destroy__"] = Arc.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Arc__destroy(self);
};
// ArcLine
function ArcLine(center, start, middle, end) {
    /* center <mud::vec3> [] */
    if (typeof center !== "undefined" && center !== null) { center = center.ptr; }
    /* start <mud::vec3> [] */
    if (typeof start !== "undefined" && start !== null) { start = start.ptr; }
    /* middle <mud::vec3> [] */
    if (typeof middle !== "undefined" && middle !== null) { middle = middle.ptr; }
    /* end <mud::vec3> [] */
    if (typeof end !== "undefined" && end !== null) { end = end.ptr; }
    if (center === undefined) { this.ptr = _mud_ArcLine__construct_0(); getCache(ArcLine)[this.ptr] = this; return; }
    if (end === undefined) { this.ptr = _mud_ArcLine__construct_3(center, start, middle); getCache(ArcLine)[this.ptr] = this; return; }
    this.ptr = _mud_ArcLine__construct_4(center, start, middle, end); getCache(ArcLine)[this.ptr] = this;
    this.type = ArcLine;
};
ArcLine.prototype = Object.create(Shape.prototype);
ArcLine.prototype.constructor = ArcLine;
ArcLine.prototype.__class__ = ArcLine;
ArcLine.__cache__ = {};
Module['ArcLine'] = ArcLine;
Object.defineProperty(ArcLine.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ArcLine__get_start(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_ArcLine__set_start(self, value);
    }
});
Object.defineProperty(ArcLine.prototype, "middle", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ArcLine__get_middle(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_ArcLine__set_middle(self, value);
    }
});
Object.defineProperty(ArcLine.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ArcLine__get_end(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_ArcLine__set_end(self, value);
    }
});
ArcLine.prototype["__destroy__"] = ArcLine.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ArcLine__destroy(self);
};
// Box
function Box() {
    this.ptr = _mud_Box__construct_0(); getCache(Box)[this.ptr] = this;
    this.type = Box;
};
Box.prototype = Object.create(Shape.prototype);
Box.prototype.constructor = Box;
Box.prototype.__class__ = Box;
Box.__cache__ = {};
Module['Box'] = Box;
Box.prototype["__destroy__"] = Box.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Box__destroy(self);
};
// Capsule
function Capsule(radius, height, axis) {
    /* radius <float> [] */
    /* height <float> [] */
    /* axis <mud::Axis> [] */
    if (axis && typeof axis === "object") axis = axis.ptr;
    if (radius === undefined) { this.ptr = _mud_Capsule__construct_0(); getCache(Capsule)[this.ptr] = this; return; }
    if (axis === undefined) { this.ptr = _mud_Capsule__construct_2(radius, height); getCache(Capsule)[this.ptr] = this; return; }
    this.ptr = _mud_Capsule__construct_3(radius, height, axis); getCache(Capsule)[this.ptr] = this;
    this.type = Capsule;
};
Capsule.prototype = Object.create(Shape.prototype);
Capsule.prototype.constructor = Capsule;
Capsule.prototype.__class__ = Capsule;
Capsule.__cache__ = {};
Module['Capsule'] = Capsule;
Object.defineProperty(Capsule.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Capsule__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Capsule__set_radius(self, value);
    }
});
Object.defineProperty(Capsule.prototype, "height", {
    get: function() {
        var self = this.ptr;
        return _mud_Capsule__get_height(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Capsule__set_height(self, value);
    }
});
Object.defineProperty(Capsule.prototype, "axis", {
    get: function() {
        var self = this.ptr;
        return _mud_Capsule__get_axis(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Axis> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Capsule__set_axis(self, value);
    }
});
Capsule.prototype["__destroy__"] = Capsule.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Capsule__destroy(self);
};
// Circle
function Circle(radius, axis) {
    /* radius <float> [] */
    /* axis <mud::Axis> [] */
    if (axis && typeof axis === "object") axis = axis.ptr;
    if (radius === undefined) { this.ptr = _mud_Circle__construct_0(); getCache(Circle)[this.ptr] = this; return; }
    if (axis === undefined) { this.ptr = _mud_Circle__construct_1(radius); getCache(Circle)[this.ptr] = this; return; }
    this.ptr = _mud_Circle__construct_2(radius, axis); getCache(Circle)[this.ptr] = this;
    this.type = Circle;
};
Circle.prototype = Object.create(Shape.prototype);
Circle.prototype.constructor = Circle;
Circle.prototype.__class__ = Circle;
Circle.__cache__ = {};
Module['Circle'] = Circle;
Object.defineProperty(Circle.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Circle__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Circle__set_radius(self, value);
    }
});
Object.defineProperty(Circle.prototype, "axis", {
    get: function() {
        var self = this.ptr;
        return _mud_Circle__get_axis(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Axis> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Circle__set_axis(self, value);
    }
});
Circle.prototype["__destroy__"] = Circle.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Circle__destroy(self);
};
// ConvexHull
function ConvexHull(vertices) {
    /* vertices <stl::vector<mud::vec3>> [] */
    if (typeof vertices !== "undefined" && vertices !== null) { vertices = vertices.ptr; }
    if (vertices === undefined) { this.ptr = _mud_ConvexHull__construct_0(); getCache(ConvexHull)[this.ptr] = this; return; }
    this.ptr = _mud_ConvexHull__construct_1(vertices); getCache(ConvexHull)[this.ptr] = this;
    this.type = ConvexHull;
};
ConvexHull.prototype = Object.create(Shape.prototype);
ConvexHull.prototype.constructor = ConvexHull;
ConvexHull.prototype.__class__ = ConvexHull;
ConvexHull.__cache__ = {};
Module['ConvexHull'] = ConvexHull;
ConvexHull.prototype["__destroy__"] = ConvexHull.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ConvexHull__destroy(self);
};
// Cube
function Cube(center, extents) {
    /* center <mud::vec3> [] */
    if (typeof center !== "undefined" && center !== null) { center = center.ptr; }
    /* extents <mud::vec3> [] */
    if (typeof extents !== "undefined" && extents !== null) { extents = extents.ptr; }
    if (center === undefined) { this.ptr = _mud_Cube__construct_0(); getCache(Cube)[this.ptr] = this; return; }
    if (extents === undefined) { this.ptr = _mud_Cube__construct_1(center); getCache(Cube)[this.ptr] = this; return; }
    this.ptr = _mud_Cube__construct_2(center, extents); getCache(Cube)[this.ptr] = this;
    this.type = Cube;
};
Cube.prototype = Object.create(Shape.prototype);
Cube.prototype.constructor = Cube;
Cube.prototype.__class__ = Cube;
Cube.__cache__ = {};
Module['Cube'] = Cube;
Object.defineProperty(Cube.prototype, "extents", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Cube__get_extents(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Cube__set_extents(self, value);
    }
});
Cube.prototype["__destroy__"] = Cube.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Cube__destroy(self);
};
// Cylinder
function Cylinder(radius, height, axis) {
    /* radius <float> [] */
    /* height <float> [] */
    /* axis <mud::Axis> [] */
    if (axis && typeof axis === "object") axis = axis.ptr;
    if (radius === undefined) { this.ptr = _mud_Cylinder__construct_0(); getCache(Cylinder)[this.ptr] = this; return; }
    if (axis === undefined) { this.ptr = _mud_Cylinder__construct_2(radius, height); getCache(Cylinder)[this.ptr] = this; return; }
    this.ptr = _mud_Cylinder__construct_3(radius, height, axis); getCache(Cylinder)[this.ptr] = this;
    this.type = Cylinder;
};
Cylinder.prototype = Object.create(Shape.prototype);
Cylinder.prototype.constructor = Cylinder;
Cylinder.prototype.__class__ = Cylinder;
Cylinder.__cache__ = {};
Module['Cylinder'] = Cylinder;
Object.defineProperty(Cylinder.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Cylinder__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Cylinder__set_radius(self, value);
    }
});
Object.defineProperty(Cylinder.prototype, "height", {
    get: function() {
        var self = this.ptr;
        return _mud_Cylinder__get_height(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Cylinder__set_height(self, value);
    }
});
Object.defineProperty(Cylinder.prototype, "axis", {
    get: function() {
        var self = this.ptr;
        return _mud_Cylinder__get_axis(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Axis> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Cylinder__set_axis(self, value);
    }
});
Cylinder.prototype["__destroy__"] = Cylinder.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Cylinder__destroy(self);
};
// Ellipsis
function Ellipsis(radius, axis) {
    /* radius <mud::vec2> [] */
    if (typeof radius !== "undefined" && radius !== null) { radius = radius.ptr; }
    /* axis <mud::Axis> [] */
    if (axis && typeof axis === "object") axis = axis.ptr;
    if (radius === undefined) { this.ptr = _mud_Ellipsis__construct_0(); getCache(Ellipsis)[this.ptr] = this; return; }
    if (axis === undefined) { this.ptr = _mud_Ellipsis__construct_1(radius); getCache(Ellipsis)[this.ptr] = this; return; }
    this.ptr = _mud_Ellipsis__construct_2(radius, axis); getCache(Ellipsis)[this.ptr] = this;
    this.type = Ellipsis;
};
Ellipsis.prototype = Object.create(Shape.prototype);
Ellipsis.prototype.constructor = Ellipsis;
Ellipsis.prototype.__class__ = Ellipsis;
Ellipsis.__cache__ = {};
Module['Ellipsis'] = Ellipsis;
Object.defineProperty(Ellipsis.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ellipsis__get_radius(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec2> [] */
        value = value.ptr;
        _mud_Ellipsis__set_radius(self, value);
    }
});
Object.defineProperty(Ellipsis.prototype, "axis", {
    get: function() {
        var self = this.ptr;
        return _mud_Ellipsis__get_axis(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Axis> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Ellipsis__set_axis(self, value);
    }
});
Ellipsis.prototype["__destroy__"] = Ellipsis.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ellipsis__destroy(self);
};
// Geometry
function Geometry() {
    this.ptr = _mud_Geometry__construct_0(); getCache(Geometry)[this.ptr] = this;
    this.type = Geometry;
};
Geometry.prototype = Object.create(Shape.prototype);
Geometry.prototype.constructor = Geometry;
Geometry.prototype.__class__ = Geometry;
Geometry.__cache__ = {};
Module['Geometry'] = Geometry;
Geometry.prototype["__destroy__"] = Geometry.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Geometry__destroy(self);
};
// Grid2
function Grid2(size, space) {
    /* size <mud::vec2> [] */
    if (typeof size !== "undefined" && size !== null) { size = size.ptr; }
    /* space <mud::vec2> [] */
    if (typeof space !== "undefined" && space !== null) { space = space.ptr; }
    if (size === undefined) { this.ptr = _mud_Grid2__construct_0(); getCache(Grid2)[this.ptr] = this; return; }
    if (space === undefined) { this.ptr = _mud_Grid2__construct_1(size); getCache(Grid2)[this.ptr] = this; return; }
    this.ptr = _mud_Grid2__construct_2(size, space); getCache(Grid2)[this.ptr] = this;
    this.type = Grid2;
};
Grid2.prototype = Object.create(Shape.prototype);
Grid2.prototype.constructor = Grid2;
Grid2.prototype.__class__ = Grid2;
Grid2.__cache__ = {};
Module['Grid2'] = Grid2;
Object.defineProperty(Grid2.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Grid2__get_size(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec2> [] */
        value = value.ptr;
        _mud_Grid2__set_size(self, value);
    }
});
Object.defineProperty(Grid2.prototype, "space", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Grid2__get_space(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec2> [] */
        value = value.ptr;
        _mud_Grid2__set_space(self, value);
    }
});
Grid2.prototype["__destroy__"] = Grid2.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Grid2__destroy(self);
};
// Grid3
function Grid3(size, points) {
    /* size <mud::uvec2> [] */
    if (typeof size !== "undefined" && size !== null) { size = size.ptr; }
    /* points <stl::vector<mud::vec3>> [] */
    if (typeof points !== "undefined" && points !== null) { points = points.ptr; }
    if (size === undefined) { this.ptr = _mud_Grid3__construct_0(); getCache(Grid3)[this.ptr] = this; return; }
    if (points === undefined) { this.ptr = _mud_Grid3__construct_1(size); getCache(Grid3)[this.ptr] = this; return; }
    this.ptr = _mud_Grid3__construct_2(size, points); getCache(Grid3)[this.ptr] = this;
    this.type = Grid3;
};
Grid3.prototype = Object.create(Shape.prototype);
Grid3.prototype.constructor = Grid3;
Grid3.prototype.__class__ = Grid3;
Grid3.__cache__ = {};
Module['Grid3'] = Grid3;
Object.defineProperty(Grid3.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Grid3__get_size(self), v2_stl_uint);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::uvec2> [] */
        value = value.ptr;
        _mud_Grid3__set_size(self, value);
    }
});
Grid3.prototype["__destroy__"] = Grid3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Grid3__destroy(self);
};
// Line
function Line(start, end) {
    /* start <mud::vec3> [] */
    if (typeof start !== "undefined" && start !== null) { start = start.ptr; }
    /* end <mud::vec3> [] */
    if (typeof end !== "undefined" && end !== null) { end = end.ptr; }
    if (start === undefined) { this.ptr = _mud_Line__construct_0(); getCache(Line)[this.ptr] = this; return; }
    this.ptr = _mud_Line__construct_2(start, end); getCache(Line)[this.ptr] = this;
    this.type = Line;
};
Line.prototype = Object.create(Shape.prototype);
Line.prototype.constructor = Line;
Line.prototype.__class__ = Line;
Line.__cache__ = {};
Module['Line'] = Line;
Object.defineProperty(Line.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Line__get_start(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Line__set_start(self, value);
    }
});
Object.defineProperty(Line.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Line__get_end(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Line__set_end(self, value);
    }
});
Line.prototype["__destroy__"] = Line.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Line__destroy(self);
};
// Points
function Points(points) {
    /* points <stl::vector<mud::vec3>> [] */
    if (typeof points !== "undefined" && points !== null) { points = points.ptr; }
    if (points === undefined) { this.ptr = _mud_Points__construct_0(); getCache(Points)[this.ptr] = this; return; }
    this.ptr = _mud_Points__construct_1(points); getCache(Points)[this.ptr] = this;
    this.type = Points;
};
Points.prototype = Object.create(Shape.prototype);
Points.prototype.constructor = Points;
Points.prototype.__class__ = Points;
Points.__cache__ = {};
Module['Points'] = Points;
Points.prototype["__destroy__"] = Points.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Points__destroy(self);
};
// Poisson
function Poisson(size, maxRadius) {
    /* size <mud::vec2> [] */
    size = size.ptr;
    /* maxRadius <float> [] */
    this.ptr = _mud_Poisson__construct_2(size, maxRadius); getCache(Poisson)[this.ptr] = this;
    this.type = Poisson;
};
Poisson.prototype = Object.create(Distribution.prototype);
Poisson.prototype.constructor = Poisson;
Poisson.prototype.__class__ = Poisson;
Poisson.__cache__ = {};
Module['Poisson'] = Poisson;
Poisson.prototype["addPoint"] = Poisson.prototype.addPoint = function(self, radius, point) {
    var self = this.ptr;
    /* radius <float> [] */
    /* point <mud::vec3> [] */
    point = point.ptr;
    return !!(_mud_Poisson_addPoint_2(self, radius, point));
};
Poisson.prototype["__destroy__"] = Poisson.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Poisson__destroy(self);
};
// Polygon
function Polygon(vertices) {
    /* vertices <stl::vector<mud::vec3>> [] */
    if (typeof vertices !== "undefined" && vertices !== null) { vertices = vertices.ptr; }
    if (vertices === undefined) { this.ptr = _mud_Polygon__construct_0(); getCache(Polygon)[this.ptr] = this; return; }
    this.ptr = _mud_Polygon__construct_1(vertices); getCache(Polygon)[this.ptr] = this;
    this.type = Polygon;
};
Polygon.prototype = Object.create(Shape.prototype);
Polygon.prototype.constructor = Polygon;
Polygon.prototype.__class__ = Polygon;
Polygon.__cache__ = {};
Module['Polygon'] = Polygon;
Polygon.prototype["__destroy__"] = Polygon.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Polygon__destroy(self);
};
// Quad
function Quad(a, b, c, d) {
    /* a <mud::vec3> [] */
    if (typeof a !== "undefined" && a !== null) { a = a.ptr; }
    /* b <mud::vec3> [] */
    if (typeof b !== "undefined" && b !== null) { b = b.ptr; }
    /* c <mud::vec3> [] */
    if (typeof c !== "undefined" && c !== null) { c = c.ptr; }
    /* d <mud::vec3> [] */
    if (typeof d !== "undefined" && d !== null) { d = d.ptr; }
    if (a === undefined) { this.ptr = _mud_Quad__construct_0(); getCache(Quad)[this.ptr] = this; return; }
    this.ptr = _mud_Quad__construct_4(a, b, c, d); getCache(Quad)[this.ptr] = this;
    this.type = Quad;
};
Quad.prototype = Object.create(Shape.prototype);
Quad.prototype.constructor = Quad;
Quad.prototype.__class__ = Quad;
Quad.__cache__ = {};
Module['Quad'] = Quad;
Quad.prototype["__destroy__"] = Quad.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Quad__destroy(self);
};
// Rect
function Rect(position, size) {
    /* position <mud::vec2> [] */
    if (typeof position !== "undefined" && position !== null) { position = position.ptr; }
    /* size <mud::vec2> [] */
    if (typeof size !== "undefined" && size !== null) { size = size.ptr; }
    if (position === undefined) { this.ptr = _mud_Rect__construct_0(); getCache(Rect)[this.ptr] = this; return; }
    this.ptr = _mud_Rect__construct_2(position, size); getCache(Rect)[this.ptr] = this;
    this.type = Rect;
};
Rect.prototype = Object.create(Shape.prototype);
Rect.prototype.constructor = Rect;
Rect.prototype.__class__ = Rect;
Rect.__cache__ = {};
Module['Rect'] = Rect;
Object.defineProperty(Rect.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Rect__get_position(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec2> [] */
        value = value.ptr;
        _mud_Rect__set_position(self, value);
    }
});
Object.defineProperty(Rect.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Rect__get_size(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec2> [] */
        value = value.ptr;
        _mud_Rect__set_size(self, value);
    }
});
Rect.prototype["__destroy__"] = Rect.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Rect__destroy(self);
};
// Ring
function Ring(radius, min, max) {
    /* radius <float> [] */
    /* min <float> [] */
    /* max <float> [] */
    if (radius === undefined) { this.ptr = _mud_Ring__construct_0(); getCache(Ring)[this.ptr] = this; return; }
    this.ptr = _mud_Ring__construct_3(radius, min, max); getCache(Ring)[this.ptr] = this;
    this.type = Ring;
};
Ring.prototype = Object.create(Shape.prototype);
Ring.prototype.constructor = Ring;
Ring.prototype.__class__ = Ring;
Ring.__cache__ = {};
Module['Ring'] = Ring;
Object.defineProperty(Ring.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Ring__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Ring__set_radius(self, value);
    }
});
Object.defineProperty(Ring.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return _mud_Ring__get_min(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Ring__set_min(self, value);
    }
});
Object.defineProperty(Ring.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return _mud_Ring__get_max(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Ring__set_max(self, value);
    }
});
Ring.prototype["__destroy__"] = Ring.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ring__destroy(self);
};
// Sphere
function Sphere(radius) {
    /* radius <float> [] */
    if (radius === undefined) { this.ptr = _mud_Sphere__construct_0(); getCache(Sphere)[this.ptr] = this; return; }
    this.ptr = _mud_Sphere__construct_1(radius); getCache(Sphere)[this.ptr] = this;
    this.type = Sphere;
};
Sphere.prototype = Object.create(Shape.prototype);
Sphere.prototype.constructor = Sphere;
Sphere.prototype.__class__ = Sphere;
Sphere.__cache__ = {};
Module['Sphere'] = Sphere;
Object.defineProperty(Sphere.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Sphere__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Sphere__set_radius(self, value);
    }
});
Sphere.prototype["__destroy__"] = Sphere.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Sphere__destroy(self);
};
// SphereRing
function SphereRing(radius, min, max) {
    /* radius <float> [] */
    /* min <float> [] */
    /* max <float> [] */
    if (radius === undefined) { this.ptr = _mud_SphereRing__construct_0(); getCache(SphereRing)[this.ptr] = this; return; }
    this.ptr = _mud_SphereRing__construct_3(radius, min, max); getCache(SphereRing)[this.ptr] = this;
    this.type = SphereRing;
};
SphereRing.prototype = Object.create(Shape.prototype);
SphereRing.prototype.constructor = SphereRing;
SphereRing.prototype.__class__ = SphereRing;
SphereRing.__cache__ = {};
Module['SphereRing'] = SphereRing;
Object.defineProperty(SphereRing.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_SphereRing__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_SphereRing__set_radius(self, value);
    }
});
Object.defineProperty(SphereRing.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return _mud_SphereRing__get_min(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_SphereRing__set_min(self, value);
    }
});
Object.defineProperty(SphereRing.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return _mud_SphereRing__get_max(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_SphereRing__set_max(self, value);
    }
});
SphereRing.prototype["__destroy__"] = SphereRing.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_SphereRing__destroy(self);
};
// Spheroid
function Spheroid(radius) {
    /* radius <float> [] */
    if (radius === undefined) { this.ptr = _mud_Spheroid__construct_0(); getCache(Spheroid)[this.ptr] = this; return; }
    this.ptr = _mud_Spheroid__construct_1(radius); getCache(Spheroid)[this.ptr] = this;
    this.type = Spheroid;
};
Spheroid.prototype = Object.create(Shape.prototype);
Spheroid.prototype.constructor = Spheroid;
Spheroid.prototype.__class__ = Spheroid;
Spheroid.__cache__ = {};
Module['Spheroid'] = Spheroid;
Object.defineProperty(Spheroid.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Spheroid__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Spheroid__set_radius(self, value);
    }
});
Spheroid.prototype["__destroy__"] = Spheroid.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Spheroid__destroy(self);
};
// Torus
function Torus(radius, solid_radius, axis) {
    /* radius <float> [] */
    /* solid_radius <float> [] */
    /* axis <mud::Axis> [] */
    if (axis && typeof axis === "object") axis = axis.ptr;
    if (radius === undefined) { this.ptr = _mud_Torus__construct_0(); getCache(Torus)[this.ptr] = this; return; }
    if (axis === undefined) { this.ptr = _mud_Torus__construct_2(radius, solid_radius); getCache(Torus)[this.ptr] = this; return; }
    this.ptr = _mud_Torus__construct_3(radius, solid_radius, axis); getCache(Torus)[this.ptr] = this;
    this.type = Torus;
};
Torus.prototype = Object.create(Shape.prototype);
Torus.prototype.constructor = Torus;
Torus.prototype.__class__ = Torus;
Torus.__cache__ = {};
Module['Torus'] = Torus;
Object.defineProperty(Torus.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Torus__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Torus__set_radius(self, value);
    }
});
Object.defineProperty(Torus.prototype, "solid_radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Torus__get_solid_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Torus__set_solid_radius(self, value);
    }
});
Object.defineProperty(Torus.prototype, "axis", {
    get: function() {
        var self = this.ptr;
        return _mud_Torus__get_axis(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Axis> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Torus__set_axis(self, value);
    }
});
Torus.prototype["__destroy__"] = Torus.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Torus__destroy(self);
};
// Triangle
function Triangle(size) {
    /* size <mud::vec2> [] */
    if (typeof size !== "undefined" && size !== null) { size = size.ptr; }
    if (size === undefined) { this.ptr = _mud_Triangle__construct_0(); getCache(Triangle)[this.ptr] = this; return; }
    this.ptr = _mud_Triangle__construct_1(size); getCache(Triangle)[this.ptr] = this;
    this.type = Triangle;
};
Triangle.prototype = Object.create(Shape.prototype);
Triangle.prototype.constructor = Triangle;
Triangle.prototype.__class__ = Triangle;
Triangle.__cache__ = {};
Module['Triangle'] = Triangle;
Object.defineProperty(Triangle.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Triangle__get_size(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec2> [] */
        value = value.ptr;
        _mud_Triangle__set_size(self, value);
    }
});
Triangle.prototype["__destroy__"] = Triangle.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Triangle__destroy(self);
};
Module['to_ray'] = function(pos, dir, distance) {
    var self = this.ptr;
    /* pos <mud::vec3> [] */
    pos = pos.ptr;
    /* dir <mud::vec3> [] */
    dir = dir.ptr;
    /* distance <float> [] */
    if (distance === undefined) { return wrapPointer(_mud_to_ray_2(pos, dir), Ray); }
    return wrapPointer(_mud_to_ray_3(pos, dir, distance), Ray);
};
Module['to_segment'] = function(ray) {
    var self = this.ptr;
    /* ray <mud::Ray> [] */
    ray = ray.ptr;
    return wrapPointer(_mud_to_segment_1(ray), Segment);
};

(function() {
    function setup() {
        Aabb.__type__ = _mud_Aabb__type();
        Distribution.__type__ = _mud_Distribution__type();
        Face3.__type__ = _mud_Face3__type();
        MeshPacker.__type__ = _mud_MeshPacker__type();
        Plane.__type__ = _mud_Plane__type();
        Plane3.__type__ = _mud_Plane3__type();
        Ray.__type__ = _mud_Ray__type();
        Segment.__type__ = _mud_Segment__type();
        Shape.__type__ = _mud_Shape__type();
        ShapeVar.__type__ = _mud_ShapeVar__type();
        Symbol.__type__ = _mud_Symbol__type();
        Arc.__type__ = _mud_Arc__type();
        ArcLine.__type__ = _mud_ArcLine__type();
        Box.__type__ = _mud_Box__type();
        Capsule.__type__ = _mud_Capsule__type();
        Circle.__type__ = _mud_Circle__type();
        ConvexHull.__type__ = _mud_ConvexHull__type();
        Cube.__type__ = _mud_Cube__type();
        Cylinder.__type__ = _mud_Cylinder__type();
        Ellipsis.__type__ = _mud_Ellipsis__type();
        Geometry.__type__ = _mud_Geometry__type();
        Grid2.__type__ = _mud_Grid2__type();
        Grid3.__type__ = _mud_Grid3__type();
        Line.__type__ = _mud_Line__type();
        Points.__type__ = _mud_Points__type();
        Poisson.__type__ = _mud_Poisson__type();
        Polygon.__type__ = _mud_Polygon__type();
        Quad.__type__ = _mud_Quad__type();
        Rect.__type__ = _mud_Rect__type();
        Ring.__type__ = _mud_Ring__type();
        Sphere.__type__ = _mud_Sphere__type();
        SphereRing.__type__ = _mud_SphereRing__type();
        Spheroid.__type__ = _mud_Spheroid__type();
        Torus.__type__ = _mud_Torus__type();
        Triangle.__type__ = _mud_Triangle__type();
        // DrawMode
        Module['OUTLINE'] = _mud_DrawMode_OUTLINE();
        Module['PLAIN'] = _mud_DrawMode_PLAIN();
        // PrimitiveType
        Module['PrimitiveType'] = Module['PrimitiveType'] || {};
        Module['PrimitiveType']['Points'] = _mud_PrimitiveType_Points();
        Module['PrimitiveType']['Lines'] = _mud_PrimitiveType_Lines();
        Module['PrimitiveType']['LineLoop'] = _mud_PrimitiveType_LineLoop();
        Module['PrimitiveType']['LineStrip'] = _mud_PrimitiveType_LineStrip();
        Module['PrimitiveType']['Triangles'] = _mud_PrimitiveType_Triangles();
        Module['PrimitiveType']['TriangleStrip'] = _mud_PrimitiveType_TriangleStrip();
        Module['PrimitiveType']['TriangleFan'] = _mud_PrimitiveType_TriangleFan();
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
