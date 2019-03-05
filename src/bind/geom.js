Module['stl'] = Module['stl'] || {};
// Aabb
function Aabb(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_Aabb__construct_0(); this.type = Aabb; getCache(Aabb)[this.ptr] = this; return; }
    this.ptr = _mud_Aabb__construct_2(/*center*/a0.ptr, /*extents*/a1.ptr); this.type = Aabb; getCache(Aabb)[this.ptr] = this;
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
        _mud_Aabb__set_center(self, value.ptr);
    }
});
Object.defineProperty(Aabb.prototype, "extents", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Aabb__get_extents(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Aabb__set_extents(self, value.ptr);
    }
});
Object.defineProperty(Aabb.prototype, "empty", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Aabb__get_empty(self));
    },
    set: function(value) {
        var self = this.ptr;
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
    this.ptr = _mud_Face3__construct_0(); this.type = Face3; getCache(Face3)[this.ptr] = this;
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
    this.ptr = _mud_MeshPacker__construct_0(); this.type = MeshPacker; getCache(MeshPacker)[this.ptr] = this;
};
MeshPacker.prototype = Object.create(WrapperObject.prototype);
MeshPacker.prototype.constructor = MeshPacker;
MeshPacker.prototype.__class__ = MeshPacker;
MeshPacker.__cache__ = {};
Module['MeshPacker'] = MeshPacker;
Object.defineProperty(MeshPacker.prototype, "primitive", {
    get: function() {
        var self = this.ptr;
        return _mud_MeshPacker__get_primitive(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_MeshPacker__set_primitive(self, value);
    }
});
MeshPacker.prototype["__destroy__"] = MeshPacker.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_MeshPacker__destroy(self);
};
// Plane
function Plane() {
    this.ptr = _mud_Plane__construct_0(); this.type = Plane; getCache(Plane)[this.ptr] = this;
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
        _mud_Plane__set_normal(self, value.ptr);
    }
});
Object.defineProperty(Plane.prototype, "distance", {
    get: function() {
        var self = this.ptr;
        return _mud_Plane__get_distance(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Plane__set_distance(self, value);
    }
});
Plane.prototype["__destroy__"] = Plane.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Plane__destroy(self);
};
// Plane3
function Plane3() {
    this.ptr = _mud_Plane3__construct_0(); this.type = Plane3; getCache(Plane3)[this.ptr] = this;
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
        _mud_Plane3__set_origin(self, value.ptr);
    }
});
Object.defineProperty(Plane3.prototype, "a", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Plane3__get_a(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Plane3__set_a(self, value.ptr);
    }
});
Object.defineProperty(Plane3.prototype, "b", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Plane3__get_b(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Plane3__set_b(self, value.ptr);
    }
});
Plane3.prototype["__destroy__"] = Plane3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Plane3__destroy(self);
};
// Ray
function Ray() {
    this.ptr = _mud_Ray__construct_0(); this.type = Ray; getCache(Ray)[this.ptr] = this;
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
        _mud_Ray__set_start(self, value.ptr);
    }
});
Object.defineProperty(Ray.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ray__get_end(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Ray__set_end(self, value.ptr);
    }
});
Object.defineProperty(Ray.prototype, "dir", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ray__get_dir(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Ray__set_dir(self, value.ptr);
    }
});
Object.defineProperty(Ray.prototype, "inv_dir", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ray__get_inv_dir(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Ray__set_inv_dir(self, value.ptr);
    }
});
Ray.prototype["__destroy__"] = Ray.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ray__destroy(self);
};
// Segment
function Segment() {
    this.ptr = _mud_Segment__construct_0(); this.type = Segment; getCache(Segment)[this.ptr] = this;
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
        _mud_Segment__set_start(self, value.ptr);
    }
});
Object.defineProperty(Segment.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Segment__get_end(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Segment__set_end(self, value.ptr);
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
function ShapeVar(a0) {
    if (a0 === undefined) { this.ptr = _mud_ShapeVar__construct_0(); this.type = ShapeVar; getCache(ShapeVar)[this.ptr] = this; return; }
    this.ptr = _mud_ShapeVar__construct_1(/*shape*/a0.ptr); this.type = ShapeVar; getCache(ShapeVar)[this.ptr] = this;
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
function Symbol(a0, a1, a2, a3, a4) {
    if (a0 === undefined) { this.ptr = _mud_Symbol__construct_0(); this.type = Symbol; getCache(Symbol)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_Symbol__construct_1(/*fill*/a0.ptr); this.type = Symbol; getCache(Symbol)[this.ptr] = this; return; }
    if (a2 === undefined) { this.ptr = _mud_Symbol__construct_2(/*fill*/a0.ptr, /*outline*/a1.ptr); this.type = Symbol; getCache(Symbol)[this.ptr] = this; return; }
    if (a3 === undefined) { this.ptr = _mud_Symbol__construct_3(/*fill*/a0.ptr, /*outline*/a1.ptr, /*overlay*/a2); this.type = Symbol; getCache(Symbol)[this.ptr] = this; return; }
    if (a4 === undefined) { this.ptr = _mud_Symbol__construct_4(/*fill*/a0.ptr, /*outline*/a1.ptr, /*overlay*/a2, /*double_sided*/a3); this.type = Symbol; getCache(Symbol)[this.ptr] = this; return; }
    this.ptr = _mud_Symbol__construct_5(/*fill*/a0.ptr, /*outline*/a1.ptr, /*overlay*/a2, /*double_sided*/a3, /*detail*/a4); this.type = Symbol; getCache(Symbol)[this.ptr] = this;
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
        _mud_Symbol__set_outline(self, value.ptr);
    }
});
Object.defineProperty(Symbol.prototype, "fill", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Symbol__get_fill(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Symbol__set_fill(self, value.ptr);
    }
});
Object.defineProperty(Symbol.prototype, "overlay", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Symbol__get_overlay(self));
    },
    set: function(value) {
        var self = this.ptr;
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
        _mud_Symbol__set_image(self, ensureString(value));
    }
});
Object.defineProperty(Symbol.prototype, "image256", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Symbol__get_image256(self), Image256);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Symbol__set_image256(self, value.ptr);
    }
});
Object.defineProperty(Symbol.prototype, "program", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Symbol__get_program(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Symbol__set_program(self, ensureString(value));
    }
});
Symbol.prototype["__destroy__"] = Symbol.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Symbol__destroy(self);
};
// Arc
function Arc(a0, a1, a2) {
    if (a0 === undefined) { this.ptr = _mud_Arc__construct_0(); this.type = Arc; getCache(Arc)[this.ptr] = this; return; }
    this.ptr = _mud_Arc__construct_3(/*radius*/a0, /*start*/a1, /*end*/a2); this.type = Arc; getCache(Arc)[this.ptr] = this;
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
        _mud_Arc__set_end(self, value);
    }
});
Arc.prototype["__destroy__"] = Arc.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Arc__destroy(self);
};
// ArcLine
function ArcLine(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_ArcLine__construct_0(); this.type = ArcLine; getCache(ArcLine)[this.ptr] = this; return; }
    if (a3 === undefined) { this.ptr = _mud_ArcLine__construct_3(/*start*/a0.ptr, /*middle*/a1.ptr, /*end*/a2.ptr); this.type = ArcLine; getCache(ArcLine)[this.ptr] = this; return; }
    this.ptr = _mud_ArcLine__construct_4(/*center*/a0.ptr, /*start*/a1.ptr, /*middle*/a2.ptr, /*end*/a3.ptr); this.type = ArcLine; getCache(ArcLine)[this.ptr] = this;
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
        _mud_ArcLine__set_start(self, value.ptr);
    }
});
Object.defineProperty(ArcLine.prototype, "middle", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ArcLine__get_middle(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ArcLine__set_middle(self, value.ptr);
    }
});
Object.defineProperty(ArcLine.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ArcLine__get_end(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ArcLine__set_end(self, value.ptr);
    }
});
ArcLine.prototype["__destroy__"] = ArcLine.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ArcLine__destroy(self);
};
// Box
function Box() {
    this.ptr = _mud_Box__construct_0(); this.type = Box; getCache(Box)[this.ptr] = this;
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
function Capsule(a0, a1, a2) {
    if (a0 === undefined) { this.ptr = _mud_Capsule__construct_0(); this.type = Capsule; getCache(Capsule)[this.ptr] = this; return; }
    if (a2 === undefined) { this.ptr = _mud_Capsule__construct_2(/*radius*/a0, /*height*/a1); this.type = Capsule; getCache(Capsule)[this.ptr] = this; return; }
    this.ptr = _mud_Capsule__construct_3(/*radius*/a0, /*height*/a1, /*axis*/a2); this.type = Capsule; getCache(Capsule)[this.ptr] = this;
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
        _mud_Capsule__set_axis(self, value);
    }
});
Capsule.prototype["__destroy__"] = Capsule.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Capsule__destroy(self);
};
// Circle
function Circle(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_Circle__construct_0(); this.type = Circle; getCache(Circle)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_Circle__construct_1(/*radius*/a0); this.type = Circle; getCache(Circle)[this.ptr] = this; return; }
    this.ptr = _mud_Circle__construct_2(/*radius*/a0, /*axis*/a1); this.type = Circle; getCache(Circle)[this.ptr] = this;
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
        _mud_Circle__set_axis(self, value);
    }
});
Circle.prototype["__destroy__"] = Circle.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Circle__destroy(self);
};
// ConvexHull
function ConvexHull(a0) {
    if (a0 === undefined) { this.ptr = _mud_ConvexHull__construct_0(); this.type = ConvexHull; getCache(ConvexHull)[this.ptr] = this; return; }
    this.ptr = _mud_ConvexHull__construct_1(/*vertices*/a0.ptr); this.type = ConvexHull; getCache(ConvexHull)[this.ptr] = this;
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
function Cube(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_Cube__construct_0(); this.type = Cube; getCache(Cube)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_Cube__construct_1(/*extents*/a0.ptr); this.type = Cube; getCache(Cube)[this.ptr] = this; return; }
    this.ptr = _mud_Cube__construct_2(/*center*/a0.ptr, /*extents*/a1.ptr); this.type = Cube; getCache(Cube)[this.ptr] = this;
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
        _mud_Cube__set_extents(self, value.ptr);
    }
});
Cube.prototype["__destroy__"] = Cube.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Cube__destroy(self);
};
// Cylinder
function Cylinder(a0, a1, a2) {
    if (a0 === undefined) { this.ptr = _mud_Cylinder__construct_0(); this.type = Cylinder; getCache(Cylinder)[this.ptr] = this; return; }
    if (a2 === undefined) { this.ptr = _mud_Cylinder__construct_2(/*radius*/a0, /*height*/a1); this.type = Cylinder; getCache(Cylinder)[this.ptr] = this; return; }
    this.ptr = _mud_Cylinder__construct_3(/*radius*/a0, /*height*/a1, /*axis*/a2); this.type = Cylinder; getCache(Cylinder)[this.ptr] = this;
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
        _mud_Cylinder__set_axis(self, value);
    }
});
Cylinder.prototype["__destroy__"] = Cylinder.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Cylinder__destroy(self);
};
// Ellipsis
function Ellipsis(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_Ellipsis__construct_0(); this.type = Ellipsis; getCache(Ellipsis)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_Ellipsis__construct_1(/*radius*/a0.ptr); this.type = Ellipsis; getCache(Ellipsis)[this.ptr] = this; return; }
    this.ptr = _mud_Ellipsis__construct_2(/*radius*/a0.ptr, /*axis*/a1); this.type = Ellipsis; getCache(Ellipsis)[this.ptr] = this;
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
        _mud_Ellipsis__set_radius(self, value.ptr);
    }
});
Object.defineProperty(Ellipsis.prototype, "axis", {
    get: function() {
        var self = this.ptr;
        return _mud_Ellipsis__get_axis(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Ellipsis__set_axis(self, value);
    }
});
Ellipsis.prototype["__destroy__"] = Ellipsis.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ellipsis__destroy(self);
};
// Geometry
function Geometry() {
    this.ptr = _mud_Geometry__construct_0(); this.type = Geometry; getCache(Geometry)[this.ptr] = this;
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
function Grid2(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_Grid2__construct_0(); this.type = Grid2; getCache(Grid2)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_Grid2__construct_1(/*size*/a0.ptr); this.type = Grid2; getCache(Grid2)[this.ptr] = this; return; }
    this.ptr = _mud_Grid2__construct_2(/*size*/a0.ptr, /*space*/a1.ptr); this.type = Grid2; getCache(Grid2)[this.ptr] = this;
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
        _mud_Grid2__set_size(self, value.ptr);
    }
});
Object.defineProperty(Grid2.prototype, "space", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Grid2__get_space(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Grid2__set_space(self, value.ptr);
    }
});
Grid2.prototype["__destroy__"] = Grid2.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Grid2__destroy(self);
};
// Grid3
function Grid3(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_Grid3__construct_0(); this.type = Grid3; getCache(Grid3)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_Grid3__construct_1(/*size*/a0.ptr); this.type = Grid3; getCache(Grid3)[this.ptr] = this; return; }
    this.ptr = _mud_Grid3__construct_2(/*size*/a0.ptr, /*points*/a1.ptr); this.type = Grid3; getCache(Grid3)[this.ptr] = this;
};
Grid3.prototype = Object.create(Shape.prototype);
Grid3.prototype.constructor = Grid3;
Grid3.prototype.__class__ = Grid3;
Grid3.__cache__ = {};
Module['Grid3'] = Grid3;
Object.defineProperty(Grid3.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Grid3__get_size(self), v2_uint);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Grid3__set_size(self, value.ptr);
    }
});
Grid3.prototype["__destroy__"] = Grid3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Grid3__destroy(self);
};
// Icosahedron
function Icosahedron(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_Icosahedron__construct_0(); this.type = Icosahedron; getCache(Icosahedron)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_Icosahedron__construct_1(/*radius*/a0); this.type = Icosahedron; getCache(Icosahedron)[this.ptr] = this; return; }
    this.ptr = _mud_Icosahedron__construct_2(/*center*/a0.ptr, /*radius*/a1); this.type = Icosahedron; getCache(Icosahedron)[this.ptr] = this;
};
Icosahedron.prototype = Object.create(Shape.prototype);
Icosahedron.prototype.constructor = Icosahedron;
Icosahedron.prototype.__class__ = Icosahedron;
Icosahedron.__cache__ = {};
Module['Icosahedron'] = Icosahedron;
Object.defineProperty(Icosahedron.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Icosahedron__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Icosahedron__set_radius(self, value);
    }
});
Icosahedron.prototype["__destroy__"] = Icosahedron.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Icosahedron__destroy(self);
};
// Line
function Line(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_Line__construct_0(); this.type = Line; getCache(Line)[this.ptr] = this; return; }
    this.ptr = _mud_Line__construct_2(/*start*/a0.ptr, /*end*/a1.ptr); this.type = Line; getCache(Line)[this.ptr] = this;
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
        _mud_Line__set_start(self, value.ptr);
    }
});
Object.defineProperty(Line.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Line__get_end(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Line__set_end(self, value.ptr);
    }
});
Line.prototype["__destroy__"] = Line.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Line__destroy(self);
};
// Points
function Points(a0) {
    if (a0 === undefined) { this.ptr = _mud_Points__construct_0(); this.type = Points; getCache(Points)[this.ptr] = this; return; }
    this.ptr = _mud_Points__construct_1(/*points*/a0.ptr); this.type = Points; getCache(Points)[this.ptr] = this;
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
function Poisson(a0, a1) {
    this.ptr = _mud_Poisson__construct_2(/*size*/a0.ptr, /*maxRadius*/a1); this.type = Poisson; getCache(Poisson)[this.ptr] = this;
};
Poisson.prototype = Object.create(Distribution.prototype);
Poisson.prototype.constructor = Poisson;
Poisson.prototype.__class__ = Poisson;
Poisson.__cache__ = {};
Module['Poisson'] = Poisson;
Poisson.prototype["addPoint"] = Poisson.prototype.addPoint = function(a0, a1) {
    var self = this.ptr;
    return !!(_mud_Poisson_addPoint_2(self, /*radius*/a0, /*point*/a1.ptr));
};
Poisson.prototype["__destroy__"] = Poisson.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Poisson__destroy(self);
};
// Polygon
function Polygon(a0) {
    if (a0 === undefined) { this.ptr = _mud_Polygon__construct_0(); this.type = Polygon; getCache(Polygon)[this.ptr] = this; return; }
    this.ptr = _mud_Polygon__construct_1(/*vertices*/a0.ptr); this.type = Polygon; getCache(Polygon)[this.ptr] = this;
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
function Quad(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_Quad__construct_0(); this.type = Quad; getCache(Quad)[this.ptr] = this; return; }
    this.ptr = _mud_Quad__construct_4(/*a*/a0.ptr, /*b*/a1.ptr, /*c*/a2.ptr, /*d*/a3.ptr); this.type = Quad; getCache(Quad)[this.ptr] = this;
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
function Rect(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_Rect__construct_0(); this.type = Rect; getCache(Rect)[this.ptr] = this; return; }
    if (a2 === undefined) { this.ptr = _mud_Rect__construct_2(/*position*/a0.ptr, /*size*/a1.ptr); this.type = Rect; getCache(Rect)[this.ptr] = this; return; }
    this.ptr = _mud_Rect__construct_4(/*x*/a0, /*y*/a1, /*w*/a2, /*h*/a3); this.type = Rect; getCache(Rect)[this.ptr] = this;
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
        _mud_Rect__set_position(self, value.ptr);
    }
});
Object.defineProperty(Rect.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Rect__get_size(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Rect__set_size(self, value.ptr);
    }
});
Rect.prototype["__destroy__"] = Rect.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Rect__destroy(self);
};
// Ring
function Ring(a0, a1, a2) {
    if (a0 === undefined) { this.ptr = _mud_Ring__construct_0(); this.type = Ring; getCache(Ring)[this.ptr] = this; return; }
    this.ptr = _mud_Ring__construct_3(/*radius*/a0, /*min*/a1, /*max*/a2); this.type = Ring; getCache(Ring)[this.ptr] = this;
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
        _mud_Ring__set_max(self, value);
    }
});
Ring.prototype["__destroy__"] = Ring.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ring__destroy(self);
};
// Sphere
function Sphere(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_Sphere__construct_0(); this.type = Sphere; getCache(Sphere)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_Sphere__construct_1(/*radius*/a0); this.type = Sphere; getCache(Sphere)[this.ptr] = this; return; }
    this.ptr = _mud_Sphere__construct_2(/*center*/a0.ptr, /*radius*/a1); this.type = Sphere; getCache(Sphere)[this.ptr] = this;
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
        _mud_Sphere__set_radius(self, value);
    }
});
Sphere.prototype["__destroy__"] = Sphere.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Sphere__destroy(self);
};
// SphereRing
function SphereRing(a0, a1, a2) {
    if (a0 === undefined) { this.ptr = _mud_SphereRing__construct_0(); this.type = SphereRing; getCache(SphereRing)[this.ptr] = this; return; }
    this.ptr = _mud_SphereRing__construct_3(/*radius*/a0, /*min*/a1, /*max*/a2); this.type = SphereRing; getCache(SphereRing)[this.ptr] = this;
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
        _mud_SphereRing__set_max(self, value);
    }
});
SphereRing.prototype["__destroy__"] = SphereRing.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_SphereRing__destroy(self);
};
// Spheroid
function Spheroid(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_Spheroid__construct_0(); this.type = Spheroid; getCache(Spheroid)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_Spheroid__construct_1(/*radius*/a0); this.type = Spheroid; getCache(Spheroid)[this.ptr] = this; return; }
    this.ptr = _mud_Spheroid__construct_2(/*center*/a0.ptr, /*radius*/a1); this.type = Spheroid; getCache(Spheroid)[this.ptr] = this;
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
        _mud_Spheroid__set_radius(self, value);
    }
});
Spheroid.prototype["__destroy__"] = Spheroid.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Spheroid__destroy(self);
};
// Torus
function Torus(a0, a1, a2) {
    if (a0 === undefined) { this.ptr = _mud_Torus__construct_0(); this.type = Torus; getCache(Torus)[this.ptr] = this; return; }
    if (a2 === undefined) { this.ptr = _mud_Torus__construct_2(/*radius*/a0, /*solid_radius*/a1); this.type = Torus; getCache(Torus)[this.ptr] = this; return; }
    this.ptr = _mud_Torus__construct_3(/*radius*/a0, /*solid_radius*/a1, /*axis*/a2); this.type = Torus; getCache(Torus)[this.ptr] = this;
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
        _mud_Torus__set_axis(self, value);
    }
});
Torus.prototype["__destroy__"] = Torus.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Torus__destroy(self);
};
// TorusKnot
function TorusKnot(a0, a1, a2) {
    if (a0 === undefined) { this.ptr = _mud_TorusKnot__construct_0(); this.type = TorusKnot; getCache(TorusKnot)[this.ptr] = this; return; }
    if (a2 === undefined) { this.ptr = _mud_TorusKnot__construct_2(/*radius*/a0, /*solid_radius*/a1); this.type = TorusKnot; getCache(TorusKnot)[this.ptr] = this; return; }
    this.ptr = _mud_TorusKnot__construct_3(/*center*/a0.ptr, /*radius*/a1, /*solid_radius*/a2); this.type = TorusKnot; getCache(TorusKnot)[this.ptr] = this;
};
TorusKnot.prototype = Object.create(Shape.prototype);
TorusKnot.prototype.constructor = TorusKnot;
TorusKnot.prototype.__class__ = TorusKnot;
TorusKnot.__cache__ = {};
Module['TorusKnot'] = TorusKnot;
Object.defineProperty(TorusKnot.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_TorusKnot__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_TorusKnot__set_radius(self, value);
    }
});
Object.defineProperty(TorusKnot.prototype, "solid_radius", {
    get: function() {
        var self = this.ptr;
        return _mud_TorusKnot__get_solid_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_TorusKnot__set_solid_radius(self, value);
    }
});
TorusKnot.prototype["__destroy__"] = TorusKnot.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TorusKnot__destroy(self);
};
// Triangle
function Triangle(a0) {
    if (a0 === undefined) { this.ptr = _mud_Triangle__construct_0(); this.type = Triangle; getCache(Triangle)[this.ptr] = this; return; }
    this.ptr = _mud_Triangle__construct_1(/*size*/a0.ptr); this.type = Triangle; getCache(Triangle)[this.ptr] = this;
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
        _mud_Triangle__set_size(self, value.ptr);
    }
});
Triangle.prototype["__destroy__"] = Triangle.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Triangle__destroy(self);
};
Module['to_ray'] = function(a0, a1, a2) {
    if (a2 === undefined) { return wrapPointer(_mud_to_ray_2(/*pos*/a0.ptr, /*dir*/a1.ptr), Ray); }
    return wrapPointer(_mud_to_ray_3(/*pos*/a0.ptr, /*dir*/a1.ptr, /*distance*/a2), Ray);
};
Module['to_segment'] = function(a0) {
    return wrapPointer(_mud_to_segment_1(/*ray*/a0.ptr), Segment);
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
        Icosahedron.__type__ = _mud_Icosahedron__type();
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
        TorusKnot.__type__ = _mud_TorusKnot__type();
        Triangle.__type__ = _mud_Triangle__type();
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
