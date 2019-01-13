
// Bindings utilities
function WrapperObject() {
}
// Colour
function Colour(r, g, b, a) {
    var self = this.ptr;
    /* r <float> [] */
    /* g <float> [] */
    /* b <float> [] */
    /* a <float> [] */
    if (r === undefined) { this.ptr = _mud_Colour_Colour_0(self); getCache(Colour)[this.ptr] = this; return; }
    if (g === undefined) { this.ptr = _mud_Colour_Colour_1(self, r); getCache(Colour)[this.ptr] = this; return; }
    if (b === undefined) { this.ptr = _mud_Colour_Colour_2(self, r, g); getCache(Colour)[this.ptr] = this; return; }
    if (a === undefined) { this.ptr = _mud_Colour_Colour_3(self, r, g, b); getCache(Colour)[this.ptr] = this; return; }
    this.ptr = _mud_Colour_Colour_4(self, r, g, b, a); getCache(Colour)[this.ptr] = this;
};
Colour.prototype = Object.create(WrapperObject.prototype);
Colour.prototype.constructor = Colour;
Colour.prototype.__class__ = Colour;
Colour.__cache__ = {};
Module['Colour'] = Colour;
Object.defineProperty(Colour.prototype, "r", {
    get: function() {
        var self = this.ptr;
        return _mud_Colour_get_r(self);
    },
    set: function(r) {
        var self = this.ptr;
        /* r <float> [] */
        _mud_Colour_set_r(self, r);
    }
});
Object.defineProperty(Colour.prototype, "g", {
    get: function() {
        var self = this.ptr;
        return _mud_Colour_get_g(self);
    },
    set: function(g) {
        var self = this.ptr;
        /* g <float> [] */
        _mud_Colour_set_g(self, g);
    }
});
Object.defineProperty(Colour.prototype, "b", {
    get: function() {
        var self = this.ptr;
        return _mud_Colour_get_b(self);
    },
    set: function(b) {
        var self = this.ptr;
        /* b <float> [] */
        _mud_Colour_set_b(self, b);
    }
});
Object.defineProperty(Colour.prototype, "a", {
    get: function() {
        var self = this.ptr;
        return _mud_Colour_get_a(self);
    },
    set: function(a) {
        var self = this.ptr;
        /* a <float> [] */
        _mud_Colour_set_a(self, a);
    }
});
Colour.prototype["__destroy__"] = Colour.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Colour___destroy__(self);
};
// Gauge
function Gauge(value) {
    var self = this.ptr;
    /* value <float> [] */
    if (value === undefined) { this.ptr = _mud_Gauge_Gauge_0(self); getCache(Gauge)[this.ptr] = this; return; }
    this.ptr = _mud_Gauge_Gauge_1(self, value); getCache(Gauge)[this.ptr] = this;
};
Gauge.prototype = Object.create(WrapperObject.prototype);
Gauge.prototype.constructor = Gauge;
Gauge.prototype.__class__ = Gauge;
Gauge.__cache__ = {};
Module['Gauge'] = Gauge;
Gauge.prototype["__destroy__"] = Gauge.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Gauge___destroy__(self);
};
// Image
function Image() {
    var self = this.ptr;
    this.ptr = _mud_Image_Image_0(self); getCache(Image)[this.ptr] = this;
};
Image.prototype = Object.create(WrapperObject.prototype);
Image.prototype.constructor = Image;
Image.prototype.__class__ = Image;
Image.__cache__ = {};
Module['Image'] = Image;
Image.prototype["__destroy__"] = Image.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Image___destroy__(self);
};
// Image256
function Image256(width, height, palette) {
    var self = this.ptr;
    /* width <uint16_t> [] */
    /* height <uint16_t> [] */
    /* palette <Palette> [] */
    if(typeof palette !== "undefined" && palette !== null) {{ palette = palette.ptr }};
    if (width === undefined) { this.ptr = _mud_Image256_Image256_0(self); getCache(Image256)[this.ptr] = this; return; }
    if (height === undefined) { this.ptr = _mud_Image256_Image256_1(self, width); getCache(Image256)[this.ptr] = this; return; }
    if (palette === undefined) { this.ptr = _mud_Image256_Image256_2(self, width, height); getCache(Image256)[this.ptr] = this; return; }
    this.ptr = _mud_Image256_Image256_3(self, width, height, palette); getCache(Image256)[this.ptr] = this;
};
Image256.prototype = Object.create(WrapperObject.prototype);
Image256.prototype.constructor = Image256;
Image256.prototype.__class__ = Image256;
Image256.__cache__ = {};
Module['Image256'] = Image256;
Object.defineProperty(Image256.prototype, "width", {
    get: function() {
        var self = this.ptr;
        return _mud_Image256_get_width(self);
    },
    set: function(width) {
        var self = this.ptr;
        /* width <uint16_t> [] */
        _mud_Image256_set_width(self, width);
    }
});
Object.defineProperty(Image256.prototype, "height", {
    get: function() {
        var self = this.ptr;
        return _mud_Image256_get_height(self);
    },
    set: function(height) {
        var self = this.ptr;
        /* height <uint16_t> [] */
        _mud_Image256_set_height(self, height);
    }
});
Object.defineProperty(Image256.prototype, "palette", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Image256_get_palette(self), mud::Palette);
    },
    set: function(palette) {
        var self = this.ptr;
        /* palette <Palette> [] */
        palette = palette.ptr;
        _mud_Image256_set_palette(self, palette);
    }
});
Image256.prototype["__destroy__"] = Image256.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Image256___destroy__(self);
};
// ImageAtlas
function ImageAtlas() { throw "cannot construct a ImageAtlas, no constructor in IDL" }
ImageAtlas.prototype = Object.create(WrapperObject.prototype);
ImageAtlas.prototype.constructor = ImageAtlas;
ImageAtlas.prototype.__class__ = ImageAtlas;
ImageAtlas.__cache__ = {};
Module['ImageAtlas'] = ImageAtlas;
ImageAtlas.prototype["__destroy__"] = ImageAtlas.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ImageAtlas___destroy__(self);
};
// Palette
function Palette(spectrum, steps) {
    var self = this.ptr;
    /* spectrum <Spectrum> [] */
    if (spectrum && typeof spectrum === "object") spectrum = spectrum.ptr;
    /* steps <size_t> [] */
    this.ptr = _mud_Palette_Palette_2(self, spectrum, steps); getCache(Palette)[this.ptr] = this;
};
Palette.prototype = Object.create(WrapperObject.prototype);
Palette.prototype.constructor = Palette;
Palette.prototype.__class__ = Palette;
Palette.__cache__ = {};
Module['Palette'] = Palette;
Palette.prototype["__destroy__"] = Palette.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Palette___destroy__(self);
};
// Ratio
function Ratio(value) {
    var self = this.ptr;
    /* value <float> [] */
    if (value === undefined) { this.ptr = _mud_Ratio_Ratio_0(self); getCache(Ratio)[this.ptr] = this; return; }
    this.ptr = _mud_Ratio_Ratio_1(self, value); getCache(Ratio)[this.ptr] = this;
};
Ratio.prototype = Object.create(WrapperObject.prototype);
Ratio.prototype.constructor = Ratio;
Ratio.prototype.__class__ = Ratio;
Ratio.__cache__ = {};
Module['Ratio'] = Ratio;
Ratio.prototype["__destroy__"] = Ratio.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ratio___destroy__(self);
};
// Time
function Time(value) {
    var self = this.ptr;
    /* value <double> [] */
    this.ptr = _mud_Time_Time_1(self, value); getCache(Time)[this.ptr] = this;
};
Time.prototype = Object.create(WrapperObject.prototype);
Time.prototype.constructor = Time;
Time.prototype.__class__ = Time;
Time.__cache__ = {};
Module['Time'] = Time;
Object.defineProperty(Time.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return _mud_Time_get_value(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <double> [] */
        _mud_Time_set_value(self, value);
    }
});
Time.prototype["__destroy__"] = Time.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Time___destroy__(self);
};
// TimeSpan
function TimeSpan(s, e) {
    var self = this.ptr;
    /* s <Time> [] */
    s = s.ptr;
    /* e <Time> [] */
    e = e.ptr;
    this.ptr = _mud_TimeSpan_TimeSpan_2(self, s, e); getCache(TimeSpan)[this.ptr] = this;
};
TimeSpan.prototype = Object.create(WrapperObject.prototype);
TimeSpan.prototype.constructor = TimeSpan;
TimeSpan.prototype.__class__ = TimeSpan;
TimeSpan.__cache__ = {};
Module['TimeSpan'] = TimeSpan;
Object.defineProperty(TimeSpan.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_TimeSpan_get_start(self), mud::Time);
    },
    set: function(start) {
        var self = this.ptr;
        /* start <Time> [] */
        start = start.ptr;
        _mud_TimeSpan_set_start(self, start);
    }
});
Object.defineProperty(TimeSpan.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_TimeSpan_get_end(self), mud::Time);
    },
    set: function(end) {
        var self = this.ptr;
        /* end <Time> [] */
        end = end.ptr;
        _mud_TimeSpan_set_end(self, end);
    }
});
TimeSpan.prototype["__destroy__"] = TimeSpan.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TimeSpan___destroy__(self);
};
// Transform
function Transform(position, rotation, scale) {
    var self = this.ptr;
    /* position <vec3> [] */
    position = position.ptr;
    /* rotation <quat> [] */
    rotation = rotation.ptr;
    /* scale <vec3> [] */
    scale = scale.ptr;
    if (position === undefined) { this.ptr = _mud_Transform_Transform_0(self); getCache(Transform)[this.ptr] = this; return; }
    this.ptr = _mud_Transform_Transform_3(self, position, rotation, scale); getCache(Transform)[this.ptr] = this;
};
Transform.prototype = Object.create(WrapperObject.prototype);
Transform.prototype.constructor = Transform;
Transform.prototype.__class__ = Transform;
Transform.__cache__ = {};
Module['Transform'] = Transform;
Object.defineProperty(Transform.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Transform_get_position(self), mud::vec3);
    },
    set: function(position) {
        var self = this.ptr;
        /* position <vec3> [] */
        position = position.ptr;
        _mud_Transform_set_position(self, position);
    }
});
Object.defineProperty(Transform.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Transform_get_rotation(self), mud::quat);
    },
    set: function(rotation) {
        var self = this.ptr;
        /* rotation <quat> [] */
        rotation = rotation.ptr;
        _mud_Transform_set_rotation(self, rotation);
    }
});
Object.defineProperty(Transform.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Transform_get_scale(self), mud::vec3);
    },
    set: function(scale) {
        var self = this.ptr;
        /* scale <vec3> [] */
        scale = scale.ptr;
        _mud_Transform_set_scale(self, scale);
    }
});
Transform.prototype["__destroy__"] = Transform.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Transform___destroy__(self);
};
// bvec3
function bvec3() {
    var self = this.ptr;
    this.ptr = _mud_bvec3_bvec3_0(self); getCache(bvec3)[this.ptr] = this;
};
bvec3.prototype = Object.create(WrapperObject.prototype);
bvec3.prototype.constructor = bvec3;
bvec3.prototype.__class__ = bvec3;
bvec3.__cache__ = {};
Module['bvec3'] = bvec3;
bvec3.prototype["__destroy__"] = bvec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_bvec3___destroy__(self);
};
// bvec4
function bvec4() {
    var self = this.ptr;
    this.ptr = _mud_bvec4_bvec4_0(self); getCache(bvec4)[this.ptr] = this;
};
bvec4.prototype = Object.create(WrapperObject.prototype);
bvec4.prototype.constructor = bvec4;
bvec4.prototype.__class__ = bvec4;
bvec4.__cache__ = {};
Module['bvec4'] = bvec4;
bvec4.prototype["__destroy__"] = bvec4.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_bvec4___destroy__(self);
};
// half2
function half2() {
    var self = this.ptr;
    this.ptr = _mud_half2_half2_0(self); getCache(half2)[this.ptr] = this;
};
half2.prototype = Object.create(WrapperObject.prototype);
half2.prototype.constructor = half2;
half2.prototype.__class__ = half2;
half2.__cache__ = {};
Module['half2'] = half2;
half2.prototype["__destroy__"] = half2.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_half2___destroy__(self);
};
// half3
function half3() {
    var self = this.ptr;
    this.ptr = _mud_half3_half3_0(self); getCache(half3)[this.ptr] = this;
};
half3.prototype = Object.create(WrapperObject.prototype);
half3.prototype.constructor = half3;
half3.prototype.__class__ = half3;
half3.__cache__ = {};
Module['half3'] = half3;
half3.prototype["__destroy__"] = half3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_half3___destroy__(self);
};
// ivec2
function ivec2() {
    var self = this.ptr;
    this.ptr = _mud_ivec2_ivec2_0(self); getCache(ivec2)[this.ptr] = this;
};
ivec2.prototype = Object.create(WrapperObject.prototype);
ivec2.prototype.constructor = ivec2;
ivec2.prototype.__class__ = ivec2;
ivec2.__cache__ = {};
Module['ivec2'] = ivec2;
ivec2.prototype["__destroy__"] = ivec2.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ivec2___destroy__(self);
};
// ivec3
function ivec3(x, y, z) {
    var self = this.ptr;
    /* x <int> [] */
    /* y <int> [] */
    /* z <int> [] */
    if (x === undefined) { this.ptr = _mud_ivec3_ivec3_0(self); getCache(ivec3)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_ivec3_ivec3_1(self, x); getCache(ivec3)[this.ptr] = this; return; }
    this.ptr = _mud_ivec3_ivec3_3(self, x, y, z); getCache(ivec3)[this.ptr] = this;
};
ivec3.prototype = Object.create(WrapperObject.prototype);
ivec3.prototype.constructor = ivec3;
ivec3.prototype.__class__ = ivec3;
ivec3.__cache__ = {};
Module['ivec3'] = ivec3;
Object.defineProperty(ivec3.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_ivec3_get_x(self);
    },
    set: function(x) {
        var self = this.ptr;
        /* x <int> [] */
        _mud_ivec3_set_x(self, x);
    }
});
Object.defineProperty(ivec3.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_ivec3_get_y(self);
    },
    set: function(y) {
        var self = this.ptr;
        /* y <int> [] */
        _mud_ivec3_set_y(self, y);
    }
});
Object.defineProperty(ivec3.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_ivec3_get_z(self);
    },
    set: function(z) {
        var self = this.ptr;
        /* z <int> [] */
        _mud_ivec3_set_z(self, z);
    }
});
ivec3.prototype["__destroy__"] = ivec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ivec3___destroy__(self);
};
// ivec4
function ivec4() {
    var self = this.ptr;
    this.ptr = _mud_ivec4_ivec4_0(self); getCache(ivec4)[this.ptr] = this;
};
ivec4.prototype = Object.create(WrapperObject.prototype);
ivec4.prototype.constructor = ivec4;
ivec4.prototype.__class__ = ivec4;
ivec4.__cache__ = {};
Module['ivec4'] = ivec4;
ivec4.prototype["__destroy__"] = ivec4.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ivec4___destroy__(self);
};
// mat4
function mat4() {
    var self = this.ptr;
    this.ptr = _mud_mat4_mat4_0(self); getCache(mat4)[this.ptr] = this;
};
mat4.prototype = Object.create(WrapperObject.prototype);
mat4.prototype.constructor = mat4;
mat4.prototype.__class__ = mat4;
mat4.__cache__ = {};
Module['mat4'] = mat4;
mat4.prototype["__destroy__"] = mat4.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_mat4___destroy__(self);
};
// quat
function quat(w, x, y, z) {
    var self = this.ptr;
    /* w <float> [] */
    /* x <float> [] */
    /* y <float> [] */
    /* z <float> [] */
    if (w === undefined) { this.ptr = _mud_quat_quat_0(self); getCache(quat)[this.ptr] = this; return; }
    this.ptr = _mud_quat_quat_4(self, w, x, y, z); getCache(quat)[this.ptr] = this;
};
quat.prototype = Object.create(WrapperObject.prototype);
quat.prototype.constructor = quat;
quat.prototype.__class__ = quat;
quat.__cache__ = {};
Module['quat'] = quat;
Object.defineProperty(quat.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_quat_get_x(self);
    },
    set: function(x) {
        var self = this.ptr;
        /* x <float> [] */
        _mud_quat_set_x(self, x);
    }
});
Object.defineProperty(quat.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_quat_get_y(self);
    },
    set: function(y) {
        var self = this.ptr;
        /* y <float> [] */
        _mud_quat_set_y(self, y);
    }
});
Object.defineProperty(quat.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_quat_get_z(self);
    },
    set: function(z) {
        var self = this.ptr;
        /* z <float> [] */
        _mud_quat_set_z(self, z);
    }
});
Object.defineProperty(quat.prototype, "w", {
    get: function() {
        var self = this.ptr;
        return _mud_quat_get_w(self);
    },
    set: function(w) {
        var self = this.ptr;
        /* w <float> [] */
        _mud_quat_set_w(self, w);
    }
});
quat.prototype["__destroy__"] = quat.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_quat___destroy__(self);
};
// uvec2
function uvec2(x, y) {
    var self = this.ptr;
    /* x <uint32_t> [] */
    /* y <uint32_t> [] */
    if (x === undefined) { this.ptr = _mud_uvec2_uvec2_0(self); getCache(uvec2)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_uvec2_uvec2_1(self, x); getCache(uvec2)[this.ptr] = this; return; }
    this.ptr = _mud_uvec2_uvec2_2(self, x, y); getCache(uvec2)[this.ptr] = this;
};
uvec2.prototype = Object.create(WrapperObject.prototype);
uvec2.prototype.constructor = uvec2;
uvec2.prototype.__class__ = uvec2;
uvec2.__cache__ = {};
Module['uvec2'] = uvec2;
Object.defineProperty(uvec2.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec2_get_x(self);
    },
    set: function(x) {
        var self = this.ptr;
        /* x <uint32_t> [] */
        _mud_uvec2_set_x(self, x);
    }
});
Object.defineProperty(uvec2.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec2_get_y(self);
    },
    set: function(y) {
        var self = this.ptr;
        /* y <uint32_t> [] */
        _mud_uvec2_set_y(self, y);
    }
});
uvec2.prototype["__destroy__"] = uvec2.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_uvec2___destroy__(self);
};
// uvec3
function uvec3(x, y, z) {
    var self = this.ptr;
    /* x <uint32_t> [] */
    /* y <uint32_t> [] */
    /* z <uint32_t> [] */
    if (x === undefined) { this.ptr = _mud_uvec3_uvec3_0(self); getCache(uvec3)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_uvec3_uvec3_1(self, x); getCache(uvec3)[this.ptr] = this; return; }
    this.ptr = _mud_uvec3_uvec3_3(self, x, y, z); getCache(uvec3)[this.ptr] = this;
};
uvec3.prototype = Object.create(WrapperObject.prototype);
uvec3.prototype.constructor = uvec3;
uvec3.prototype.__class__ = uvec3;
uvec3.__cache__ = {};
Module['uvec3'] = uvec3;
Object.defineProperty(uvec3.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec3_get_x(self);
    },
    set: function(x) {
        var self = this.ptr;
        /* x <uint32_t> [] */
        _mud_uvec3_set_x(self, x);
    }
});
Object.defineProperty(uvec3.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec3_get_y(self);
    },
    set: function(y) {
        var self = this.ptr;
        /* y <uint32_t> [] */
        _mud_uvec3_set_y(self, y);
    }
});
Object.defineProperty(uvec3.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec3_get_z(self);
    },
    set: function(z) {
        var self = this.ptr;
        /* z <uint32_t> [] */
        _mud_uvec3_set_z(self, z);
    }
});
uvec3.prototype["__destroy__"] = uvec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_uvec3___destroy__(self);
};
// uvec4
function uvec4(w, x, y, z) {
    var self = this.ptr;
    /* w <uint32_t> [] */
    /* x <uint32_t> [] */
    /* y <uint32_t> [] */
    /* z <uint32_t> [] */
    if (w === undefined) { this.ptr = _mud_uvec4_uvec4_0(self); getCache(uvec4)[this.ptr] = this; return; }
    if (x === undefined) { this.ptr = _mud_uvec4_uvec4_1(self, w); getCache(uvec4)[this.ptr] = this; return; }
    this.ptr = _mud_uvec4_uvec4_4(self, w, x, y, z); getCache(uvec4)[this.ptr] = this;
};
uvec4.prototype = Object.create(WrapperObject.prototype);
uvec4.prototype.constructor = uvec4;
uvec4.prototype.__class__ = uvec4;
uvec4.__cache__ = {};
Module['uvec4'] = uvec4;
Object.defineProperty(uvec4.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec4_get_x(self);
    },
    set: function(x) {
        var self = this.ptr;
        /* x <uint32_t> [] */
        _mud_uvec4_set_x(self, x);
    }
});
Object.defineProperty(uvec4.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec4_get_y(self);
    },
    set: function(y) {
        var self = this.ptr;
        /* y <uint32_t> [] */
        _mud_uvec4_set_y(self, y);
    }
});
Object.defineProperty(uvec4.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec4_get_z(self);
    },
    set: function(z) {
        var self = this.ptr;
        /* z <uint32_t> [] */
        _mud_uvec4_set_z(self, z);
    }
});
Object.defineProperty(uvec4.prototype, "w", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec4_get_w(self);
    },
    set: function(w) {
        var self = this.ptr;
        /* w <uint32_t> [] */
        _mud_uvec4_set_w(self, w);
    }
});
uvec4.prototype["__destroy__"] = uvec4.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_uvec4___destroy__(self);
};
// vec2
function vec2(x, y) {
    var self = this.ptr;
    /* x <float> [] */
    /* y <float> [] */
    if (x === undefined) { this.ptr = _mud_vec2_vec2_0(self); getCache(vec2)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_vec2_vec2_1(self, x); getCache(vec2)[this.ptr] = this; return; }
    this.ptr = _mud_vec2_vec2_2(self, x, y); getCache(vec2)[this.ptr] = this;
};
vec2.prototype = Object.create(WrapperObject.prototype);
vec2.prototype.constructor = vec2;
vec2.prototype.__class__ = vec2;
vec2.__cache__ = {};
Module['vec2'] = vec2;
Object.defineProperty(vec2.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_vec2_get_x(self);
    },
    set: function(x) {
        var self = this.ptr;
        /* x <float> [] */
        _mud_vec2_set_x(self, x);
    }
});
Object.defineProperty(vec2.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_vec2_get_y(self);
    },
    set: function(y) {
        var self = this.ptr;
        /* y <float> [] */
        _mud_vec2_set_y(self, y);
    }
});
vec2.prototype["__destroy__"] = vec2.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_vec2___destroy__(self);
};
// vec3
function vec3(x, y, z) {
    var self = this.ptr;
    /* x <float> [] */
    /* y <float> [] */
    /* z <float> [] */
    if (x === undefined) { this.ptr = _mud_vec3_vec3_0(self); getCache(vec3)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_vec3_vec3_1(self, x); getCache(vec3)[this.ptr] = this; return; }
    this.ptr = _mud_vec3_vec3_3(self, x, y, z); getCache(vec3)[this.ptr] = this;
};
vec3.prototype = Object.create(WrapperObject.prototype);
vec3.prototype.constructor = vec3;
vec3.prototype.__class__ = vec3;
vec3.__cache__ = {};
Module['vec3'] = vec3;
Object.defineProperty(vec3.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_vec3_get_x(self);
    },
    set: function(x) {
        var self = this.ptr;
        /* x <float> [] */
        _mud_vec3_set_x(self, x);
    }
});
Object.defineProperty(vec3.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_vec3_get_y(self);
    },
    set: function(y) {
        var self = this.ptr;
        /* y <float> [] */
        _mud_vec3_set_y(self, y);
    }
});
Object.defineProperty(vec3.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_vec3_get_z(self);
    },
    set: function(z) {
        var self = this.ptr;
        /* z <float> [] */
        _mud_vec3_set_z(self, z);
    }
});
vec3.prototype["__destroy__"] = vec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_vec3___destroy__(self);
};
// vec4
function vec4(w, x, y, z) {
    var self = this.ptr;
    /* w <float> [] */
    /* x <float> [] */
    /* y <float> [] */
    /* z <float> [] */
    if (w === undefined) { this.ptr = _mud_vec4_vec4_0(self); getCache(vec4)[this.ptr] = this; return; }
    if (x === undefined) { this.ptr = _mud_vec4_vec4_1(self, w); getCache(vec4)[this.ptr] = this; return; }
    this.ptr = _mud_vec4_vec4_4(self, w, x, y, z); getCache(vec4)[this.ptr] = this;
};
vec4.prototype = Object.create(WrapperObject.prototype);
vec4.prototype.constructor = vec4;
vec4.prototype.__class__ = vec4;
vec4.__cache__ = {};
Module['vec4'] = vec4;
Object.defineProperty(vec4.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_vec4_get_x(self);
    },
    set: function(x) {
        var self = this.ptr;
        /* x <float> [] */
        _mud_vec4_set_x(self, x);
    }
});
Object.defineProperty(vec4.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_vec4_get_y(self);
    },
    set: function(y) {
        var self = this.ptr;
        /* y <float> [] */
        _mud_vec4_set_y(self, y);
    }
});
Object.defineProperty(vec4.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_vec4_get_z(self);
    },
    set: function(z) {
        var self = this.ptr;
        /* z <float> [] */
        _mud_vec4_set_z(self, z);
    }
});
Object.defineProperty(vec4.prototype, "w", {
    get: function() {
        var self = this.ptr;
        return _mud_vec4_get_w(self);
    },
    set: function(w) {
        var self = this.ptr;
        /* w <float> [] */
        _mud_vec4_set_w(self, w);
    }
});
vec4.prototype["__destroy__"] = vec4.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_vec4___destroy__(self);
};
// Sprite
function Sprite() { throw "cannot construct a Sprite, no constructor in IDL" }
Sprite.prototype = Object.create(WrapperObject.prototype);
Sprite.prototype.constructor = Sprite;
Sprite.prototype.__class__ = Sprite;
Sprite.__cache__ = {};
Module['Sprite'] = Sprite;
Sprite.prototype["__destroy__"] = Sprite.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Sprite___destroy__(self);
};
// SpriteAtlas
function SpriteAtlas() { throw "cannot construct a SpriteAtlas, no constructor in IDL" }
SpriteAtlas.prototype = Object.create(WrapperObject.prototype);
SpriteAtlas.prototype.constructor = SpriteAtlas;
SpriteAtlas.prototype.__class__ = SpriteAtlas;
SpriteAtlas.__cache__ = {};
Module['SpriteAtlas'] = SpriteAtlas;
SpriteAtlas.prototype["__destroy__"] = SpriteAtlas.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_SpriteAtlas___destroy__(self);
};
// TextureAtlas
function TextureAtlas() { throw "cannot construct a TextureAtlas, no constructor in IDL" }
TextureAtlas.prototype = Object.create(WrapperObject.prototype);
TextureAtlas.prototype.constructor = TextureAtlas;
TextureAtlas.prototype.__class__ = TextureAtlas;
TextureAtlas.__cache__ = {};
Module['TextureAtlas'] = TextureAtlas;
TextureAtlas.prototype["__destroy__"] = TextureAtlas.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TextureAtlas___destroy__(self);
};

(function() {
    function setupEnums() {
        // Axes
        Module['Axes']['None'] = _mud_Axes_None();
        Module['Axes']['X'] = _mud_Axes_X();
        Module['Axes']['Y'] = _mud_Axes_Y();
        Module['Axes']['Z'] = _mud_Axes_Z();
        // Axis
        Module['Axis']['X'] = _mud_Axis_X();
        Module['Axis']['Y'] = _mud_Axis_Y();
        Module['Axis']['Z'] = _mud_Axis_Z();
        // Clockwise
        Module['CLOCKWISE'] = _mud_Clockwise_CLOCKWISE();
        Module['ANTI_CLOCKWISE'] = _mud_Clockwise_ANTI_CLOCKWISE();
        // Side
        Module['Side']['Right'] = _mud_Side_Right();
        Module['Side']['Left'] = _mud_Side_Left();
        Module['Side']['Up'] = _mud_Side_Up();
        Module['Side']['Down'] = _mud_Side_Down();
        Module['Side']['Back'] = _mud_Side_Back();
        Module['Side']['Front'] = _mud_Side_Front();
        // SignedAxis
        Module['SignedAxis']['PlusX'] = _mud_SignedAxis_PlusX();
        Module['SignedAxis']['MinusX'] = _mud_SignedAxis_MinusX();
        Module['SignedAxis']['PlusY'] = _mud_SignedAxis_PlusY();
        Module['SignedAxis']['MinusY'] = _mud_SignedAxis_MinusY();
        Module['SignedAxis']['PlusZ'] = _mud_SignedAxis_PlusZ();
        Module['SignedAxis']['MinusZ'] = _mud_SignedAxis_MinusZ();
        // Spectrum
        Module['Spectrum']['Value'] = _mud_Spectrum_Value();
        Module['Spectrum']['Hue'] = _mud_Spectrum_Hue();
        // TrackMode
        Module['TrackMode']['Constant'] = _mud_TrackMode_Constant();
        Module['TrackMode']['ConstantRandom'] = _mud_TrackMode_ConstantRandom();
        Module['TrackMode']['Curve'] = _mud_TrackMode_Curve();
        Module['TrackMode']['CurveRandom'] = _mud_TrackMode_CurveRandom();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
