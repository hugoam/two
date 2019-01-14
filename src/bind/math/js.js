Module['glm'] = Module['glm'] || {};
// Colour
function Colour(r, g, b, a) {
    /* r <float> [] */
    /* g <float> [] */
    /* b <float> [] */
    /* a <float> [] */
    if (r === undefined) { this.ptr = _mud_Colour_Colour_0(); getCache(Colour)[this.ptr] = this; return; }
    if (g === undefined) { this.ptr = _mud_Colour_Colour_1(r); getCache(Colour)[this.ptr] = this; return; }
    if (b === undefined) { this.ptr = _mud_Colour_Colour_2(r, g); getCache(Colour)[this.ptr] = this; return; }
    if (a === undefined) { this.ptr = _mud_Colour_Colour_3(r, g, b); getCache(Colour)[this.ptr] = this; return; }
    this.ptr = _mud_Colour_Colour_4(r, g, b, a); getCache(Colour)[this.ptr] = this;
    this.type = Colour;
};
Colour.prototype = Object.create(WrapperObject.prototype);
Colour.prototype.constructor = Colour;
Colour.prototype.__class__ = Colour;
Colour.__cache__ = {};
Module['Colour'] = Colour;
Object.defineProperty(Colour.prototype, "r", {
    get: function() {
        var self = this.ptr;
        return _mud_Colour__get_r(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Colour__set_r(self, value);
    }
});
Object.defineProperty(Colour.prototype, "g", {
    get: function() {
        var self = this.ptr;
        return _mud_Colour__get_g(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Colour__set_g(self, value);
    }
});
Object.defineProperty(Colour.prototype, "b", {
    get: function() {
        var self = this.ptr;
        return _mud_Colour__get_b(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Colour__set_b(self, value);
    }
});
Object.defineProperty(Colour.prototype, "a", {
    get: function() {
        var self = this.ptr;
        return _mud_Colour__get_a(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Colour__set_a(self, value);
    }
});
Colour.prototype["__destroy__"] = Colour.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Colour__destroy(self);
};
// Gauge
function Gauge(value) {
    /* value <float> [] */
    if (value === undefined) { this.ptr = _mud_Gauge_Gauge_0(); getCache(Gauge)[this.ptr] = this; return; }
    this.ptr = _mud_Gauge_Gauge_1(value); getCache(Gauge)[this.ptr] = this;
    this.type = Gauge;
};
Gauge.prototype = Object.create(WrapperObject.prototype);
Gauge.prototype.constructor = Gauge;
Gauge.prototype.__class__ = Gauge;
Gauge.__cache__ = {};
Module['Gauge'] = Gauge;
Gauge.prototype["__destroy__"] = Gauge.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Gauge__destroy(self);
};
// Image
function Image() {
    this.ptr = _mud_Image_Image_0(); getCache(Image)[this.ptr] = this;
    this.type = Image;
};
Image.prototype = Object.create(WrapperObject.prototype);
Image.prototype.constructor = Image;
Image.prototype.__class__ = Image;
Image.__cache__ = {};
Module['Image'] = Image;
Image.prototype["__destroy__"] = Image.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Image__destroy(self);
};
// Image256
function Image256(width, height, palette) {
    /* width <uint16_t> [] */
    /* height <uint16_t> [] */
    /* palette <Palette> [] */
    if(typeof palette !== "undefined" && palette !== null) { palette = palette.ptr; }
    if (width === undefined) { this.ptr = _mud_Image256_Image256_0(); getCache(Image256)[this.ptr] = this; return; }
    if (height === undefined) { this.ptr = _mud_Image256_Image256_1(width); getCache(Image256)[this.ptr] = this; return; }
    if (palette === undefined) { this.ptr = _mud_Image256_Image256_2(width, height); getCache(Image256)[this.ptr] = this; return; }
    this.ptr = _mud_Image256_Image256_3(width, height, palette); getCache(Image256)[this.ptr] = this;
    this.type = Image256;
};
Image256.prototype = Object.create(WrapperObject.prototype);
Image256.prototype.constructor = Image256;
Image256.prototype.__class__ = Image256;
Image256.__cache__ = {};
Module['Image256'] = Image256;
Object.defineProperty(Image256.prototype, "width", {
    get: function() {
        var self = this.ptr;
        return _mud_Image256__get_width(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint16_t> [] */
        _mud_Image256__set_width(self, value);
    }
});
Object.defineProperty(Image256.prototype, "height", {
    get: function() {
        var self = this.ptr;
        return _mud_Image256__get_height(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint16_t> [] */
        _mud_Image256__set_height(self, value);
    }
});
Object.defineProperty(Image256.prototype, "palette", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Image256__get_palette(self), Palette);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Palette> [] */
        value = value.ptr;
        _mud_Image256__set_palette(self, value);
    }
});
Image256.prototype["__destroy__"] = Image256.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Image256__destroy(self);
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
    _mud_ImageAtlas__destroy(self);
};
// Palette
function Palette(spectrum, steps) {
    /* spectrum <Spectrum> [] */
    if (spectrum && typeof spectrum === "object") spectrum = spectrum.ptr;
    /* steps <size_t> [] */
    this.ptr = _mud_Palette_Palette_2(spectrum, steps); getCache(Palette)[this.ptr] = this;
    this.type = Palette;
};
Palette.prototype = Object.create(WrapperObject.prototype);
Palette.prototype.constructor = Palette;
Palette.prototype.__class__ = Palette;
Palette.__cache__ = {};
Module['Palette'] = Palette;
Palette.prototype["__destroy__"] = Palette.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Palette__destroy(self);
};
// Ratio
function Ratio(value) {
    /* value <float> [] */
    if (value === undefined) { this.ptr = _mud_Ratio_Ratio_0(); getCache(Ratio)[this.ptr] = this; return; }
    this.ptr = _mud_Ratio_Ratio_1(value); getCache(Ratio)[this.ptr] = this;
    this.type = Ratio;
};
Ratio.prototype = Object.create(WrapperObject.prototype);
Ratio.prototype.constructor = Ratio;
Ratio.prototype.__class__ = Ratio;
Ratio.__cache__ = {};
Module['Ratio'] = Ratio;
Ratio.prototype["__destroy__"] = Ratio.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ratio__destroy(self);
};
// Time
function Time(value) {
    /* value <double> [] */
    this.ptr = _mud_Time_Time_1(value); getCache(Time)[this.ptr] = this;
    this.type = Time;
};
Time.prototype = Object.create(WrapperObject.prototype);
Time.prototype.constructor = Time;
Time.prototype.__class__ = Time;
Time.__cache__ = {};
Module['Time'] = Time;
Object.defineProperty(Time.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return _mud_Time__get_value(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <double> [] */
        _mud_Time__set_value(self, value);
    }
});
Time.prototype["__destroy__"] = Time.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Time__destroy(self);
};
// TimeSpan
function TimeSpan(s, e) {
    /* s <Time> [] */
    s = s.ptr;
    /* e <Time> [] */
    e = e.ptr;
    this.ptr = _mud_TimeSpan_TimeSpan_2(s, e); getCache(TimeSpan)[this.ptr] = this;
    this.type = TimeSpan;
};
TimeSpan.prototype = Object.create(WrapperObject.prototype);
TimeSpan.prototype.constructor = TimeSpan;
TimeSpan.prototype.__class__ = TimeSpan;
TimeSpan.__cache__ = {};
Module['TimeSpan'] = TimeSpan;
Object.defineProperty(TimeSpan.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_TimeSpan__get_start(self), Time);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Time> [] */
        value = value.ptr;
        _mud_TimeSpan__set_start(self, value);
    }
});
Object.defineProperty(TimeSpan.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_TimeSpan__get_end(self), Time);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Time> [] */
        value = value.ptr;
        _mud_TimeSpan__set_end(self, value);
    }
});
TimeSpan.prototype["__destroy__"] = TimeSpan.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TimeSpan__destroy(self);
};
// Transform
function Transform(position, rotation, scale) {
    /* position <vec3> [] */
    position = position.ptr;
    /* rotation <quat> [] */
    rotation = rotation.ptr;
    /* scale <vec3> [] */
    scale = scale.ptr;
    if (position === undefined) { this.ptr = _mud_Transform_Transform_0(); getCache(Transform)[this.ptr] = this; return; }
    this.ptr = _mud_Transform_Transform_3(position, rotation, scale); getCache(Transform)[this.ptr] = this;
    this.type = Transform;
};
Transform.prototype = Object.create(WrapperObject.prototype);
Transform.prototype.constructor = Transform;
Transform.prototype.__class__ = Transform;
Transform.__cache__ = {};
Module['Transform'] = Transform;
Object.defineProperty(Transform.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Transform__get_position(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _mud_Transform__set_position(self, value);
    }
});
Object.defineProperty(Transform.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Transform__get_rotation(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <quat> [] */
        value = value.ptr;
        _mud_Transform__set_rotation(self, value);
    }
});
Object.defineProperty(Transform.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Transform__get_scale(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _mud_Transform__set_scale(self, value);
    }
});
Transform.prototype["__destroy__"] = Transform.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Transform__destroy(self);
};
// bvec3
function bvec3() {
    this.ptr = _mud_bvec3_bvec3_0(); getCache(bvec3)[this.ptr] = this;
    this.type = bvec3;
};
bvec3.prototype = Object.create(WrapperObject.prototype);
bvec3.prototype.constructor = bvec3;
bvec3.prototype.__class__ = bvec3;
bvec3.__cache__ = {};
Module['bvec3'] = bvec3;
bvec3.prototype["__destroy__"] = bvec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_bvec3__destroy(self);
};
// bvec4
function bvec4() {
    this.ptr = _mud_bvec4_bvec4_0(); getCache(bvec4)[this.ptr] = this;
    this.type = bvec4;
};
bvec4.prototype = Object.create(WrapperObject.prototype);
bvec4.prototype.constructor = bvec4;
bvec4.prototype.__class__ = bvec4;
bvec4.__cache__ = {};
Module['bvec4'] = bvec4;
bvec4.prototype["__destroy__"] = bvec4.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_bvec4__destroy(self);
};
// half2
function half2() {
    this.ptr = _mud_half2_half2_0(); getCache(half2)[this.ptr] = this;
    this.type = half2;
};
half2.prototype = Object.create(WrapperObject.prototype);
half2.prototype.constructor = half2;
half2.prototype.__class__ = half2;
half2.__cache__ = {};
Module['half2'] = half2;
half2.prototype["__destroy__"] = half2.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_half2__destroy(self);
};
// half3
function half3() {
    this.ptr = _mud_half3_half3_0(); getCache(half3)[this.ptr] = this;
    this.type = half3;
};
half3.prototype = Object.create(WrapperObject.prototype);
half3.prototype.constructor = half3;
half3.prototype.__class__ = half3;
half3.__cache__ = {};
Module['half3'] = half3;
half3.prototype["__destroy__"] = half3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_half3__destroy(self);
};
// ivec2
function ivec2() {
    this.ptr = _mud_ivec2_ivec2_0(); getCache(ivec2)[this.ptr] = this;
    this.type = ivec2;
};
ivec2.prototype = Object.create(WrapperObject.prototype);
ivec2.prototype.constructor = ivec2;
ivec2.prototype.__class__ = ivec2;
ivec2.__cache__ = {};
Module['ivec2'] = ivec2;
ivec2.prototype["__destroy__"] = ivec2.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ivec2__destroy(self);
};
// ivec3
function ivec3(x, y, z) {
    /* x <int> [] */
    /* y <int> [] */
    /* z <int> [] */
    if (x === undefined) { this.ptr = _mud_ivec3_ivec3_0(); getCache(ivec3)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_ivec3_ivec3_1(x); getCache(ivec3)[this.ptr] = this; return; }
    this.ptr = _mud_ivec3_ivec3_3(x, y, z); getCache(ivec3)[this.ptr] = this;
    this.type = ivec3;
};
ivec3.prototype = Object.create(WrapperObject.prototype);
ivec3.prototype.constructor = ivec3;
ivec3.prototype.__class__ = ivec3;
ivec3.__cache__ = {};
Module['ivec3'] = ivec3;
Object.defineProperty(ivec3.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_ivec3__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_ivec3__set_x(self, value);
    }
});
Object.defineProperty(ivec3.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_ivec3__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_ivec3__set_y(self, value);
    }
});
Object.defineProperty(ivec3.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_ivec3__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_ivec3__set_z(self, value);
    }
});
ivec3.prototype["__destroy__"] = ivec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ivec3__destroy(self);
};
// ivec4
function ivec4() {
    this.ptr = _mud_ivec4_ivec4_0(); getCache(ivec4)[this.ptr] = this;
    this.type = ivec4;
};
ivec4.prototype = Object.create(WrapperObject.prototype);
ivec4.prototype.constructor = ivec4;
ivec4.prototype.__class__ = ivec4;
ivec4.__cache__ = {};
Module['ivec4'] = ivec4;
ivec4.prototype["__destroy__"] = ivec4.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ivec4__destroy(self);
};
// mat4
function mat4() {
    this.ptr = _mud_mat4_mat4_0(); getCache(mat4)[this.ptr] = this;
    this.type = mat4;
};
mat4.prototype = Object.create(WrapperObject.prototype);
mat4.prototype.constructor = mat4;
mat4.prototype.__class__ = mat4;
mat4.__cache__ = {};
Module['mat4'] = mat4;
mat4.prototype["__destroy__"] = mat4.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_mat4__destroy(self);
};
// quat
function quat(w, x, y, z) {
    /* w <float> [] */
    /* x <float> [] */
    /* y <float> [] */
    /* z <float> [] */
    if (w === undefined) { this.ptr = _mud_quat_quat_0(); getCache(quat)[this.ptr] = this; return; }
    this.ptr = _mud_quat_quat_4(w, x, y, z); getCache(quat)[this.ptr] = this;
    this.type = quat;
};
quat.prototype = Object.create(WrapperObject.prototype);
quat.prototype.constructor = quat;
quat.prototype.__class__ = quat;
quat.__cache__ = {};
Module['quat'] = quat;
Object.defineProperty(quat.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_quat__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_quat__set_x(self, value);
    }
});
Object.defineProperty(quat.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_quat__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_quat__set_y(self, value);
    }
});
Object.defineProperty(quat.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_quat__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_quat__set_z(self, value);
    }
});
Object.defineProperty(quat.prototype, "w", {
    get: function() {
        var self = this.ptr;
        return _mud_quat__get_w(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_quat__set_w(self, value);
    }
});
quat.prototype["__destroy__"] = quat.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_quat__destroy(self);
};
// uvec2
function uvec2(x, y) {
    /* x <uint32_t> [] */
    /* y <uint32_t> [] */
    if (x === undefined) { this.ptr = _mud_uvec2_uvec2_0(); getCache(uvec2)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_uvec2_uvec2_1(x); getCache(uvec2)[this.ptr] = this; return; }
    this.ptr = _mud_uvec2_uvec2_2(x, y); getCache(uvec2)[this.ptr] = this;
    this.type = uvec2;
};
uvec2.prototype = Object.create(WrapperObject.prototype);
uvec2.prototype.constructor = uvec2;
uvec2.prototype.__class__ = uvec2;
uvec2.__cache__ = {};
Module['uvec2'] = uvec2;
Object.defineProperty(uvec2.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec2__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_uvec2__set_x(self, value);
    }
});
Object.defineProperty(uvec2.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec2__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_uvec2__set_y(self, value);
    }
});
uvec2.prototype["__destroy__"] = uvec2.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_uvec2__destroy(self);
};
// uvec3
function uvec3(x, y, z) {
    /* x <uint32_t> [] */
    /* y <uint32_t> [] */
    /* z <uint32_t> [] */
    if (x === undefined) { this.ptr = _mud_uvec3_uvec3_0(); getCache(uvec3)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_uvec3_uvec3_1(x); getCache(uvec3)[this.ptr] = this; return; }
    this.ptr = _mud_uvec3_uvec3_3(x, y, z); getCache(uvec3)[this.ptr] = this;
    this.type = uvec3;
};
uvec3.prototype = Object.create(WrapperObject.prototype);
uvec3.prototype.constructor = uvec3;
uvec3.prototype.__class__ = uvec3;
uvec3.__cache__ = {};
Module['uvec3'] = uvec3;
Object.defineProperty(uvec3.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec3__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_uvec3__set_x(self, value);
    }
});
Object.defineProperty(uvec3.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec3__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_uvec3__set_y(self, value);
    }
});
Object.defineProperty(uvec3.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec3__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_uvec3__set_z(self, value);
    }
});
uvec3.prototype["__destroy__"] = uvec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_uvec3__destroy(self);
};
// uvec4
function uvec4(w, x, y, z) {
    /* w <uint32_t> [] */
    /* x <uint32_t> [] */
    /* y <uint32_t> [] */
    /* z <uint32_t> [] */
    if (w === undefined) { this.ptr = _mud_uvec4_uvec4_0(); getCache(uvec4)[this.ptr] = this; return; }
    if (x === undefined) { this.ptr = _mud_uvec4_uvec4_1(w); getCache(uvec4)[this.ptr] = this; return; }
    this.ptr = _mud_uvec4_uvec4_4(w, x, y, z); getCache(uvec4)[this.ptr] = this;
    this.type = uvec4;
};
uvec4.prototype = Object.create(WrapperObject.prototype);
uvec4.prototype.constructor = uvec4;
uvec4.prototype.__class__ = uvec4;
uvec4.__cache__ = {};
Module['uvec4'] = uvec4;
Object.defineProperty(uvec4.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec4__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_uvec4__set_x(self, value);
    }
});
Object.defineProperty(uvec4.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec4__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_uvec4__set_y(self, value);
    }
});
Object.defineProperty(uvec4.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec4__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_uvec4__set_z(self, value);
    }
});
Object.defineProperty(uvec4.prototype, "w", {
    get: function() {
        var self = this.ptr;
        return _mud_uvec4__get_w(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_uvec4__set_w(self, value);
    }
});
uvec4.prototype["__destroy__"] = uvec4.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_uvec4__destroy(self);
};
// vec2
function vec2(x, y) {
    /* x <float> [] */
    /* y <float> [] */
    if (x === undefined) { this.ptr = _mud_vec2_vec2_0(); getCache(vec2)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_vec2_vec2_1(x); getCache(vec2)[this.ptr] = this; return; }
    this.ptr = _mud_vec2_vec2_2(x, y); getCache(vec2)[this.ptr] = this;
    this.type = vec2;
};
vec2.prototype = Object.create(WrapperObject.prototype);
vec2.prototype.constructor = vec2;
vec2.prototype.__class__ = vec2;
vec2.__cache__ = {};
Module['vec2'] = vec2;
Object.defineProperty(vec2.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_vec2__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_vec2__set_x(self, value);
    }
});
Object.defineProperty(vec2.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_vec2__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_vec2__set_y(self, value);
    }
});
vec2.prototype["__destroy__"] = vec2.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_vec2__destroy(self);
};
// vec3
function vec3(x, y, z) {
    /* x <float> [] */
    /* y <float> [] */
    /* z <float> [] */
    if (x === undefined) { this.ptr = _mud_vec3_vec3_0(); getCache(vec3)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_vec3_vec3_1(x); getCache(vec3)[this.ptr] = this; return; }
    this.ptr = _mud_vec3_vec3_3(x, y, z); getCache(vec3)[this.ptr] = this;
    this.type = vec3;
};
vec3.prototype = Object.create(WrapperObject.prototype);
vec3.prototype.constructor = vec3;
vec3.prototype.__class__ = vec3;
vec3.__cache__ = {};
Module['vec3'] = vec3;
Object.defineProperty(vec3.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_vec3__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_vec3__set_x(self, value);
    }
});
Object.defineProperty(vec3.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_vec3__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_vec3__set_y(self, value);
    }
});
Object.defineProperty(vec3.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_vec3__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_vec3__set_z(self, value);
    }
});
vec3.prototype["__destroy__"] = vec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_vec3__destroy(self);
};
// vec4
function vec4(w, x, y, z) {
    /* w <float> [] */
    /* x <float> [] */
    /* y <float> [] */
    /* z <float> [] */
    if (w === undefined) { this.ptr = _mud_vec4_vec4_0(); getCache(vec4)[this.ptr] = this; return; }
    if (x === undefined) { this.ptr = _mud_vec4_vec4_1(w); getCache(vec4)[this.ptr] = this; return; }
    this.ptr = _mud_vec4_vec4_4(w, x, y, z); getCache(vec4)[this.ptr] = this;
    this.type = vec4;
};
vec4.prototype = Object.create(WrapperObject.prototype);
vec4.prototype.constructor = vec4;
vec4.prototype.__class__ = vec4;
vec4.__cache__ = {};
Module['vec4'] = vec4;
Object.defineProperty(vec4.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_vec4__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_vec4__set_x(self, value);
    }
});
Object.defineProperty(vec4.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_vec4__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_vec4__set_y(self, value);
    }
});
Object.defineProperty(vec4.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_vec4__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_vec4__set_z(self, value);
    }
});
Object.defineProperty(vec4.prototype, "w", {
    get: function() {
        var self = this.ptr;
        return _mud_vec4__get_w(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_vec4__set_w(self, value);
    }
});
vec4.prototype["__destroy__"] = vec4.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_vec4__destroy(self);
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
    _mud_Sprite__destroy(self);
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
    _mud_SpriteAtlas__destroy(self);
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
    _mud_TextureAtlas__destroy(self);
};
Module['add<float>'] = function(a, b) {
    var self = this.ptr;
    /* a <float> [] */
    /* b <float> [] */
    return _mud_add_float__2(a, b);
};
Module['add<mud::vec3>'] = function(a, b) {
    var self = this.ptr;
    /* a <vec3> [] */
    a = a.ptr;
    /* b <vec3> [] */
    b = b.ptr;
    return wrapPointer(_mud_add_mud_vec3__2(a, b), vec3);
};
Module['angle_axis'] = function(angle, axis) {
    var self = this.ptr;
    /* angle <float> [] */
    /* axis <vec3> [] */
    axis = axis.ptr;
    return wrapPointer(_mud_angle_axis_2(angle, axis), quat);
};
Module['axis_angle'] = function(axis, angle) {
    var self = this.ptr;
    /* axis <vec3> [] */
    axis = axis.ptr;
    /* angle <float> [] */
    return wrapPointer(_mud_axis_angle_2(axis, angle), quat);
};
Module['cos'] = function(a) {
    var self = this.ptr;
    /* a <double> [] */
    return __cos_1(a);
};
Module['cosf'] = function(a) {
    var self = this.ptr;
    /* a <float> [] */
    return __cosf_1(a);
};
Module['glm']['distance'] = function(a, b) {
    var self = this.ptr;
    /* a <vec3> [] */
    a = a.ptr;
    /* b <vec3> [] */
    b = b.ptr;
    return _glm_distance_2(a, b);
};
Module['divide<float>'] = function(a, b) {
    var self = this.ptr;
    /* a <float> [] */
    /* b <float> [] */
    return _mud_divide_float__2(a, b);
};
Module['divide<mud::vec3>'] = function(a, b) {
    var self = this.ptr;
    /* a <vec3> [] */
    a = a.ptr;
    /* b <vec3> [] */
    b = b.ptr;
    return wrapPointer(_mud_divide_mud_vec3__2(a, b), vec3);
};
Module['from_abgr'] = function(colour) {
    var self = this.ptr;
    /* colour <uint32_t> [] */
    return wrapPointer(_mud_from_abgr_1(colour), Colour);
};
Module['from_rgba'] = function(colour) {
    var self = this.ptr;
    /* colour <uint32_t> [] */
    return wrapPointer(_mud_from_rgba_1(colour), Colour);
};
Module['grid_center'] = function(coord, cell_size) {
    var self = this.ptr;
    /* coord <uvec3> [] */
    coord = coord.ptr;
    /* cell_size <vec3> [] */
    cell_size = cell_size.ptr;
    return wrapPointer(_mud_grid_center_2(coord, cell_size), vec3);
};
Module['hsl_to_rgb'] = function(h, s, l) {
    var self = this.ptr;
    /* h <float> [] */
    /* s <float> [] */
    /* l <float> [] */
    return wrapPointer(_mud_hsl_to_rgb_3(h, s, l), Colour);
};
Module['hsla_to_rgba'] = function(colour) {
    var self = this.ptr;
    /* colour <Colour> [] */
    colour = colour.ptr;
    return wrapPointer(_mud_hsla_to_rgba_1(colour), Colour);
};
Module['glm']['length'] = function(v) {
    var self = this.ptr;
    /* v <vec3> [] */
    v = v.ptr;
    return _glm_length_1(v);
};
Module['glm']['length2'] = function(v) {
    var self = this.ptr;
    /* v <vec3> [] */
    v = v.ptr;
    return _glm_length2_1(v);
};
Module['look_at'] = function(eye, target, forward) {
    var self = this.ptr;
    /* eye <vec3> [] */
    eye = eye.ptr;
    /* target <vec3> [] */
    target = target.ptr;
    /* forward <vec3> [] */
    if(typeof forward !== "undefined" && forward !== null) { forward = forward.ptr; }
    if (forward === undefined) { return wrapPointer(_mud_look_at_2(eye, target), quat); }
    return wrapPointer(_mud_look_at_3(eye, target, forward), quat);
};
Module['look_dir'] = function(direction, forward) {
    var self = this.ptr;
    /* direction <vec3> [] */
    direction = direction.ptr;
    /* forward <vec3> [] */
    if(typeof forward !== "undefined" && forward !== null) { forward = forward.ptr; }
    if (forward === undefined) { return wrapPointer(_mud_look_dir_1(direction), quat); }
    return wrapPointer(_mud_look_dir_2(direction, forward), quat);
};
Module['multiply<float>'] = function(a, b) {
    var self = this.ptr;
    /* a <float> [] */
    /* b <float> [] */
    return _mud_multiply_float__2(a, b);
};
Module['multiply<mud::vec3>'] = function(a, b) {
    var self = this.ptr;
    /* a <vec3> [] */
    a = a.ptr;
    /* b <vec3> [] */
    b = b.ptr;
    return wrapPointer(_mud_multiply_mud_vec3__2(a, b), vec3);
};
Module['ncos'] = function(a) {
    var self = this.ptr;
    /* a <double> [] */
    return _mud_ncos_1(a);
};
Module['ncosf'] = function(a) {
    var self = this.ptr;
    /* a <float> [] */
    return _mud_ncosf_1(a);
};
Module['nsin'] = function(a) {
    var self = this.ptr;
    /* a <double> [] */
    return _mud_nsin_1(a);
};
Module['nsinf'] = function(a) {
    var self = this.ptr;
    /* a <float> [] */
    return _mud_nsinf_1(a);
};
Module['oriented_angle'] = function(lhs, rhs, ref) {
    var self = this.ptr;
    /* lhs <vec3> [] */
    lhs = lhs.ptr;
    /* rhs <vec3> [] */
    rhs = rhs.ptr;
    /* ref <vec3> [] */
    ref = ref.ptr;
    return _mud_oriented_angle_3(lhs, rhs, ref);
};
Module['oriented_angle_2d'] = function(lhs, rhs) {
    var self = this.ptr;
    /* lhs <vec2> [] */
    lhs = lhs.ptr;
    /* rhs <vec2> [] */
    rhs = rhs.ptr;
    return _mud_oriented_angle_2d_2(lhs, rhs);
};
Module['rgb_to_hsl'] = function(r, g, b) {
    var self = this.ptr;
    /* r <float> [] */
    /* g <float> [] */
    /* b <float> [] */
    return wrapPointer(_mud_rgb_to_hsl_3(r, g, b), Colour);
};
Module['rgba_to_hsla'] = function(colour) {
    var self = this.ptr;
    /* colour <Colour> [] */
    colour = colour.ptr;
    return wrapPointer(_mud_rgba_to_hsla_1(colour), Colour);
};
Module['rotate'] = function(q, axis, angle) {
    var self = this.ptr;
    /* q <quat> [] */
    q = q.ptr;
    /* axis <vec3> [] */
    axis = axis.ptr;
    /* angle <float> [] */
    return wrapPointer(_mud_rotate_3(q, axis, angle), quat);
};
Module['sin'] = function(a) {
    var self = this.ptr;
    /* a <double> [] */
    return __sin_1(a);
};
Module['sinf'] = function(a) {
    var self = this.ptr;
    /* a <float> [] */
    return __sinf_1(a);
};
Module['subtract<float>'] = function(a, b) {
    var self = this.ptr;
    /* a <float> [] */
    /* b <float> [] */
    return _mud_subtract_float__2(a, b);
};
Module['subtract<mud::vec3>'] = function(a, b) {
    var self = this.ptr;
    /* a <vec3> [] */
    a = a.ptr;
    /* b <vec3> [] */
    b = b.ptr;
    return wrapPointer(_mud_subtract_mud_vec3__2(a, b), vec3);
};
Module['to_abgr'] = function(colour) {
    var self = this.ptr;
    /* colour <Colour> [] */
    colour = colour.ptr;
    return _mud_to_abgr_1(colour);
};
Module['to_gamma'] = function(colour) {
    var self = this.ptr;
    /* colour <Colour> [] */
    colour = colour.ptr;
    return wrapPointer(_mud_to_gamma_1(colour), Colour);
};
Module['to_linear'] = function(colour) {
    var self = this.ptr;
    /* colour <Colour> [] */
    colour = colour.ptr;
    return wrapPointer(_mud_to_linear_1(colour), Colour);
};
Module['to_rgba'] = function(colour) {
    var self = this.ptr;
    /* colour <Colour> [] */
    colour = colour.ptr;
    return _mud_to_rgba_1(colour);
};
Module['to_srgb'] = function(colour) {
    var self = this.ptr;
    /* colour <Colour> [] */
    colour = colour.ptr;
    return wrapPointer(_mud_to_srgb_1(colour), Colour);
};

(function() {
    function setup() {
        Colour.__type__ = _mud_Colour__type();
        Gauge.__type__ = _mud_Gauge__type();
        Image.__type__ = _mud_Image__type();
        Image256.__type__ = _mud_Image256__type();
        ImageAtlas.__type__ = _mud_ImageAtlas__type();
        Palette.__type__ = _mud_Palette__type();
        Ratio.__type__ = _mud_Ratio__type();
        Time.__type__ = _mud_Time__type();
        TimeSpan.__type__ = _mud_TimeSpan__type();
        Transform.__type__ = _mud_Transform__type();
        bvec3.__type__ = _mud_bvec3__type();
        bvec4.__type__ = _mud_bvec4__type();
        half2.__type__ = _mud_half2__type();
        half3.__type__ = _mud_half3__type();
        ivec2.__type__ = _mud_ivec2__type();
        ivec3.__type__ = _mud_ivec3__type();
        ivec4.__type__ = _mud_ivec4__type();
        mat4.__type__ = _mud_mat4__type();
        quat.__type__ = _mud_quat__type();
        uvec2.__type__ = _mud_uvec2__type();
        uvec3.__type__ = _mud_uvec3__type();
        uvec4.__type__ = _mud_uvec4__type();
        vec2.__type__ = _mud_vec2__type();
        vec3.__type__ = _mud_vec3__type();
        vec4.__type__ = _mud_vec4__type();
        Sprite.__type__ = _mud_Sprite__type();
        SpriteAtlas.__type__ = _mud_SpriteAtlas__type();
        TextureAtlas.__type__ = _mud_TextureAtlas__type();
        // Axes
        Module['Axes'] = Module['Axes'] || {};
        Module['Axes']['None'] = _mud_Axes_None();
        Module['Axes']['X'] = _mud_Axes_X();
        Module['Axes']['Y'] = _mud_Axes_Y();
        Module['Axes']['Z'] = _mud_Axes_Z();
        // Axis
        Module['Axis'] = Module['Axis'] || {};
        Module['Axis']['X'] = _mud_Axis_X();
        Module['Axis']['Y'] = _mud_Axis_Y();
        Module['Axis']['Z'] = _mud_Axis_Z();
        // Clockwise
        Module['CLOCKWISE'] = _mud_Clockwise_CLOCKWISE();
        Module['ANTI_CLOCKWISE'] = _mud_Clockwise_ANTI_CLOCKWISE();
        // Side
        Module['Side'] = Module['Side'] || {};
        Module['Side']['Right'] = _mud_Side_Right();
        Module['Side']['Left'] = _mud_Side_Left();
        Module['Side']['Up'] = _mud_Side_Up();
        Module['Side']['Down'] = _mud_Side_Down();
        Module['Side']['Back'] = _mud_Side_Back();
        Module['Side']['Front'] = _mud_Side_Front();
        // SignedAxis
        Module['SignedAxis'] = Module['SignedAxis'] || {};
        Module['SignedAxis']['PlusX'] = _mud_SignedAxis_PlusX();
        Module['SignedAxis']['MinusX'] = _mud_SignedAxis_MinusX();
        Module['SignedAxis']['PlusY'] = _mud_SignedAxis_PlusY();
        Module['SignedAxis']['MinusY'] = _mud_SignedAxis_MinusY();
        Module['SignedAxis']['PlusZ'] = _mud_SignedAxis_PlusZ();
        Module['SignedAxis']['MinusZ'] = _mud_SignedAxis_MinusZ();
        // Spectrum
        Module['Spectrum'] = Module['Spectrum'] || {};
        Module['Spectrum']['Value'] = _mud_Spectrum_Value();
        Module['Spectrum']['Hue'] = _mud_Spectrum_Hue();
        // TrackMode
        Module['TrackMode'] = Module['TrackMode'] || {};
        Module['TrackMode']['Constant'] = _mud_TrackMode_Constant();
        Module['TrackMode']['ConstantRandom'] = _mud_TrackMode_ConstantRandom();
        Module['TrackMode']['Curve'] = _mud_TrackMode_Curve();
        Module['TrackMode']['CurveRandom'] = _mud_TrackMode_CurveRandom();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
