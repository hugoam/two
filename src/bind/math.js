Module['stl'] = Module['stl'] || {};
// AutoStat<float>
function AutoStat_float() {
    this.ptr = _mud_AutoStat_float__construct_0(); getCache(AutoStat_float)[this.ptr] = this;
    this.type = AutoStat_float;
};
AutoStat_float.prototype = Object.create(WrapperObject.prototype);
AutoStat_float.prototype.constructor = AutoStat_float;
AutoStat_float.prototype.__class__ = AutoStat_float;
AutoStat_float.__cache__ = {};
Module['AutoStat_float'] = AutoStat_float;
Object.defineProperty(AutoStat_float.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return _mud_AutoStat_float__get_value(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_AutoStat_float__set_value(self, value);
    }
});
AutoStat_float.prototype["__destroy__"] = AutoStat_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AutoStat_float__destroy(self);
};
// AutoStat<int>
function AutoStat_int() {
    this.ptr = _mud_AutoStat_int__construct_0(); getCache(AutoStat_int)[this.ptr] = this;
    this.type = AutoStat_int;
};
AutoStat_int.prototype = Object.create(WrapperObject.prototype);
AutoStat_int.prototype.constructor = AutoStat_int;
AutoStat_int.prototype.__class__ = AutoStat_int;
AutoStat_int.__cache__ = {};
Module['AutoStat_int'] = AutoStat_int;
Object.defineProperty(AutoStat_int.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return _mud_AutoStat_int__get_value(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_AutoStat_int__set_value(self, value);
    }
});
AutoStat_int.prototype["__destroy__"] = AutoStat_int.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AutoStat_int__destroy(self);
};
// Colour
function Colour(r, g, b, a) {
    /* r <float> [] */
    /* g <float> [] */
    /* b <float> [] */
    /* a <float> [] */
    if (r === undefined) { this.ptr = _mud_Colour__construct_0(); getCache(Colour)[this.ptr] = this; return; }
    if (g === undefined) { this.ptr = _mud_Colour__construct_1(r); getCache(Colour)[this.ptr] = this; return; }
    if (b === undefined) { this.ptr = _mud_Colour__construct_2(r, g); getCache(Colour)[this.ptr] = this; return; }
    if (a === undefined) { this.ptr = _mud_Colour__construct_3(r, g, b); getCache(Colour)[this.ptr] = this; return; }
    this.ptr = _mud_Colour__construct_4(r, g, b, a); getCache(Colour)[this.ptr] = this;
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
// Image
function Image() {
    this.ptr = _mud_Image__construct_0(); getCache(Image)[this.ptr] = this;
    this.type = Image;
};
Image.prototype = Object.create(WrapperObject.prototype);
Image.prototype.constructor = Image;
Image.prototype.__class__ = Image;
Image.__cache__ = {};
Module['Image'] = Image;
Object.defineProperty(Image.prototype, "d_name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Image__get_d_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <stl::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_Image__set_d_name(self, value);
    }
});
Object.defineProperty(Image.prototype, "d_path", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Image__get_d_path(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <stl::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_Image__set_d_path(self, value);
    }
});
Image.prototype["__destroy__"] = Image.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Image__destroy(self);
};
// Image256
function Image256(width, height, palette) {
    /* width <uint16_t> [] */
    /* height <uint16_t> [] */
    /* palette <mud::Palette> [] */
    if (typeof palette !== "undefined" && palette !== null) { palette = palette.ptr; }
    if (width === undefined) { this.ptr = _mud_Image256__construct_0(); getCache(Image256)[this.ptr] = this; return; }
    if (height === undefined) { this.ptr = _mud_Image256__construct_1(width); getCache(Image256)[this.ptr] = this; return; }
    if (palette === undefined) { this.ptr = _mud_Image256__construct_2(width, height); getCache(Image256)[this.ptr] = this; return; }
    this.ptr = _mud_Image256__construct_3(width, height, palette); getCache(Image256)[this.ptr] = this;
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
        /* value <mud::Palette> [] */
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
    /* spectrum <mud::Spectrum> [] */
    if (spectrum && typeof spectrum === "object") spectrum = spectrum.ptr;
    /* steps <size_t> [] */
    this.ptr = _mud_Palette__construct_2(spectrum, steps); getCache(Palette)[this.ptr] = this;
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
// Range<float>
function Range_float() {
    this.ptr = _mud_Range_float__construct_0(); getCache(Range_float)[this.ptr] = this;
    this.type = Range_float;
};
Range_float.prototype = Object.create(WrapperObject.prototype);
Range_float.prototype.constructor = Range_float;
Range_float.prototype.__class__ = Range_float;
Range_float.__cache__ = {};
Module['Range_float'] = Range_float;
Object.defineProperty(Range_float.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return _mud_Range_float__get_min(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Range_float__set_min(self, value);
    }
});
Object.defineProperty(Range_float.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return _mud_Range_float__get_max(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Range_float__set_max(self, value);
    }
});
Range_float.prototype["__destroy__"] = Range_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Range_float__destroy(self);
};
// Range<mud::Colour>
function Range_mud_Colour() {
    this.ptr = _mud_Range_mud_Colour__construct_0(); getCache(Range_mud_Colour)[this.ptr] = this;
    this.type = Range_mud_Colour;
};
Range_mud_Colour.prototype = Object.create(WrapperObject.prototype);
Range_mud_Colour.prototype.constructor = Range_mud_Colour;
Range_mud_Colour.prototype.__class__ = Range_mud_Colour;
Range_mud_Colour.__cache__ = {};
Module['Range_mud_Colour'] = Range_mud_Colour;
Object.defineProperty(Range_mud_Colour.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Range_mud_Colour__get_min(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Colour> [] */
        value = value.ptr;
        _mud_Range_mud_Colour__set_min(self, value);
    }
});
Object.defineProperty(Range_mud_Colour.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Range_mud_Colour__get_max(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Colour> [] */
        value = value.ptr;
        _mud_Range_mud_Colour__set_max(self, value);
    }
});
Range_mud_Colour.prototype["__destroy__"] = Range_mud_Colour.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Range_mud_Colour__destroy(self);
};
// Range<mud::quat>
function Range_mud_quat() {
    this.ptr = _mud_Range_mud_quat__construct_0(); getCache(Range_mud_quat)[this.ptr] = this;
    this.type = Range_mud_quat;
};
Range_mud_quat.prototype = Object.create(WrapperObject.prototype);
Range_mud_quat.prototype.constructor = Range_mud_quat;
Range_mud_quat.prototype.__class__ = Range_mud_quat;
Range_mud_quat.__cache__ = {};
Module['Range_mud_quat'] = Range_mud_quat;
Object.defineProperty(Range_mud_quat.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Range_mud_quat__get_min(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::quat> [] */
        value = value.ptr;
        _mud_Range_mud_quat__set_min(self, value);
    }
});
Object.defineProperty(Range_mud_quat.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Range_mud_quat__get_max(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::quat> [] */
        value = value.ptr;
        _mud_Range_mud_quat__set_max(self, value);
    }
});
Range_mud_quat.prototype["__destroy__"] = Range_mud_quat.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Range_mud_quat__destroy(self);
};
// Range<mud::vec3>
function Range_mud_vec3() {
    this.ptr = _mud_Range_mud_vec3__construct_0(); getCache(Range_mud_vec3)[this.ptr] = this;
    this.type = Range_mud_vec3;
};
Range_mud_vec3.prototype = Object.create(WrapperObject.prototype);
Range_mud_vec3.prototype.constructor = Range_mud_vec3;
Range_mud_vec3.prototype.__class__ = Range_mud_vec3;
Range_mud_vec3.__cache__ = {};
Module['Range_mud_vec3'] = Range_mud_vec3;
Object.defineProperty(Range_mud_vec3.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Range_mud_vec3__get_min(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Range_mud_vec3__set_min(self, value);
    }
});
Object.defineProperty(Range_mud_vec3.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Range_mud_vec3__get_max(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Range_mud_vec3__set_max(self, value);
    }
});
Range_mud_vec3.prototype["__destroy__"] = Range_mud_vec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Range_mud_vec3__destroy(self);
};
// Range<uint32_t>
function Range_uint32_t() {
    this.ptr = _mud_Range_uint32_t__construct_0(); getCache(Range_uint32_t)[this.ptr] = this;
    this.type = Range_uint32_t;
};
Range_uint32_t.prototype = Object.create(WrapperObject.prototype);
Range_uint32_t.prototype.constructor = Range_uint32_t;
Range_uint32_t.prototype.__class__ = Range_uint32_t;
Range_uint32_t.__cache__ = {};
Module['Range_uint32_t'] = Range_uint32_t;
Object.defineProperty(Range_uint32_t.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return _mud_Range_uint32_t__get_min(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_Range_uint32_t__set_min(self, value);
    }
});
Object.defineProperty(Range_uint32_t.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return _mud_Range_uint32_t__get_max(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_Range_uint32_t__set_max(self, value);
    }
});
Range_uint32_t.prototype["__destroy__"] = Range_uint32_t.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Range_uint32_t__destroy(self);
};
// Time
function Time(value) {
    /* value <double> [] */
    this.ptr = _mud_Time__construct_1(value); getCache(Time)[this.ptr] = this;
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
    /* s <mud::Time> [] */
    s = s.ptr;
    /* e <mud::Time> [] */
    e = e.ptr;
    this.ptr = _mud_TimeSpan__construct_2(s, e); getCache(TimeSpan)[this.ptr] = this;
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
        /* value <mud::Time> [] */
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
        /* value <mud::Time> [] */
        value = value.ptr;
        _mud_TimeSpan__set_end(self, value);
    }
});
TimeSpan.prototype["__destroy__"] = TimeSpan.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TimeSpan__destroy(self);
};
// Transform
function Transform() {
    this.ptr = _mud_Transform__construct_0(); getCache(Transform)[this.ptr] = this;
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
        return wrapPointer(_mud_Transform__get_position(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
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
        /* value <mud::quat> [] */
        value = value.ptr;
        _mud_Transform__set_rotation(self, value);
    }
});
Object.defineProperty(Transform.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Transform__get_scale(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_Transform__set_scale(self, value);
    }
});
Transform.prototype["__destroy__"] = Transform.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Transform__destroy(self);
};
// ValueCurve<float>
function ValueCurve_float(keys) {
    /* keys <stl::vector<float>> [] */
    if (typeof keys !== "undefined" && keys !== null) { keys = keys.ptr; }
    if (keys === undefined) { this.ptr = _mud_ValueCurve_float__construct_0(); getCache(ValueCurve_float)[this.ptr] = this; return; }
    this.ptr = _mud_ValueCurve_float__construct_1(keys); getCache(ValueCurve_float)[this.ptr] = this;
    this.type = ValueCurve_float;
};
ValueCurve_float.prototype = Object.create(WrapperObject.prototype);
ValueCurve_float.prototype.constructor = ValueCurve_float;
ValueCurve_float.prototype.__class__ = ValueCurve_float;
ValueCurve_float.__cache__ = {};
Module['ValueCurve_float'] = ValueCurve_float;
ValueCurve_float.prototype["__destroy__"] = ValueCurve_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueCurve_float__destroy(self);
};
// ValueCurve<mud::Colour>
function ValueCurve_mud_Colour(keys) {
    /* keys <stl::vector<mud::Colour>> [] */
    if (typeof keys !== "undefined" && keys !== null) { keys = keys.ptr; }
    if (keys === undefined) { this.ptr = _mud_ValueCurve_mud_Colour__construct_0(); getCache(ValueCurve_mud_Colour)[this.ptr] = this; return; }
    this.ptr = _mud_ValueCurve_mud_Colour__construct_1(keys); getCache(ValueCurve_mud_Colour)[this.ptr] = this;
    this.type = ValueCurve_mud_Colour;
};
ValueCurve_mud_Colour.prototype = Object.create(WrapperObject.prototype);
ValueCurve_mud_Colour.prototype.constructor = ValueCurve_mud_Colour;
ValueCurve_mud_Colour.prototype.__class__ = ValueCurve_mud_Colour;
ValueCurve_mud_Colour.__cache__ = {};
Module['ValueCurve_mud_Colour'] = ValueCurve_mud_Colour;
ValueCurve_mud_Colour.prototype["__destroy__"] = ValueCurve_mud_Colour.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueCurve_mud_Colour__destroy(self);
};
// ValueCurve<mud::quat>
function ValueCurve_mud_quat(keys) {
    /* keys <stl::vector<mud::quat>> [] */
    if (typeof keys !== "undefined" && keys !== null) { keys = keys.ptr; }
    if (keys === undefined) { this.ptr = _mud_ValueCurve_mud_quat__construct_0(); getCache(ValueCurve_mud_quat)[this.ptr] = this; return; }
    this.ptr = _mud_ValueCurve_mud_quat__construct_1(keys); getCache(ValueCurve_mud_quat)[this.ptr] = this;
    this.type = ValueCurve_mud_quat;
};
ValueCurve_mud_quat.prototype = Object.create(WrapperObject.prototype);
ValueCurve_mud_quat.prototype.constructor = ValueCurve_mud_quat;
ValueCurve_mud_quat.prototype.__class__ = ValueCurve_mud_quat;
ValueCurve_mud_quat.__cache__ = {};
Module['ValueCurve_mud_quat'] = ValueCurve_mud_quat;
ValueCurve_mud_quat.prototype["__destroy__"] = ValueCurve_mud_quat.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueCurve_mud_quat__destroy(self);
};
// ValueCurve<mud::vec3>
function ValueCurve_mud_vec3(keys) {
    /* keys <stl::vector<mud::vec3>> [] */
    if (typeof keys !== "undefined" && keys !== null) { keys = keys.ptr; }
    if (keys === undefined) { this.ptr = _mud_ValueCurve_mud_vec3__construct_0(); getCache(ValueCurve_mud_vec3)[this.ptr] = this; return; }
    this.ptr = _mud_ValueCurve_mud_vec3__construct_1(keys); getCache(ValueCurve_mud_vec3)[this.ptr] = this;
    this.type = ValueCurve_mud_vec3;
};
ValueCurve_mud_vec3.prototype = Object.create(WrapperObject.prototype);
ValueCurve_mud_vec3.prototype.constructor = ValueCurve_mud_vec3;
ValueCurve_mud_vec3.prototype.__class__ = ValueCurve_mud_vec3;
ValueCurve_mud_vec3.__cache__ = {};
Module['ValueCurve_mud_vec3'] = ValueCurve_mud_vec3;
ValueCurve_mud_vec3.prototype["__destroy__"] = ValueCurve_mud_vec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueCurve_mud_vec3__destroy(self);
};
// ValueCurve<uint32_t>
function ValueCurve_uint32_t(keys) {
    /* keys <stl::vector<uint32_t>> [] */
    if (typeof keys !== "undefined" && keys !== null) { keys = keys.ptr; }
    if (keys === undefined) { this.ptr = _mud_ValueCurve_uint32_t__construct_0(); getCache(ValueCurve_uint32_t)[this.ptr] = this; return; }
    this.ptr = _mud_ValueCurve_uint32_t__construct_1(keys); getCache(ValueCurve_uint32_t)[this.ptr] = this;
    this.type = ValueCurve_uint32_t;
};
ValueCurve_uint32_t.prototype = Object.create(WrapperObject.prototype);
ValueCurve_uint32_t.prototype.constructor = ValueCurve_uint32_t;
ValueCurve_uint32_t.prototype.__class__ = ValueCurve_uint32_t;
ValueCurve_uint32_t.__cache__ = {};
Module['ValueCurve_uint32_t'] = ValueCurve_uint32_t;
ValueCurve_uint32_t.prototype["__destroy__"] = ValueCurve_uint32_t.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueCurve_uint32_t__destroy(self);
};
// ValueTrack<float>
function ValueTrack_float(mode, curve, min_curve, max_curve) {
    /* mode <mud::TrackMode> [] */
    if (mode && typeof mode === "object") mode = mode.ptr;
    /* curve <mud::ValueCurve<float>> [] */
    if (typeof curve !== "undefined" && curve !== null) { curve = curve.ptr; }
    /* min_curve <mud::ValueCurve<float>> [] */
    if (typeof min_curve !== "undefined" && min_curve !== null) { min_curve = min_curve.ptr; }
    /* max_curve <mud::ValueCurve<float>> [] */
    if (typeof max_curve !== "undefined" && max_curve !== null) { max_curve = max_curve.ptr; }
    if (mode === undefined) { this.ptr = _mud_ValueTrack_float__construct_0(); getCache(ValueTrack_float)[this.ptr] = this; return; }
    this.ptr = _mud_ValueTrack_float__construct_4(mode, curve, min_curve, max_curve); getCache(ValueTrack_float)[this.ptr] = this;
    this.type = ValueTrack_float;
};
ValueTrack_float.prototype = Object.create(WrapperObject.prototype);
ValueTrack_float.prototype.constructor = ValueTrack_float;
ValueTrack_float.prototype.__class__ = ValueTrack_float;
ValueTrack_float.__cache__ = {};
Module['ValueTrack_float'] = ValueTrack_float;
Object.defineProperty(ValueTrack_float.prototype, "mode", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueTrack_float__get_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::TrackMode> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_ValueTrack_float__set_mode(self, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueTrack_float__get_value(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_ValueTrack_float__set_value(self, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueTrack_float__get_min(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_ValueTrack_float__set_min(self, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueTrack_float__get_max(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_ValueTrack_float__set_max(self, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_float__get_curve(self), ValueCurve_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<float>> [] */
        value = value.ptr;
        _mud_ValueTrack_float__set_curve(self, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "min_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_float__get_min_curve(self), ValueCurve_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<float>> [] */
        value = value.ptr;
        _mud_ValueTrack_float__set_min_curve(self, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "max_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_float__get_max_curve(self), ValueCurve_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<float>> [] */
        value = value.ptr;
        _mud_ValueTrack_float__set_max_curve(self, value);
    }
});
ValueTrack_float.prototype["__destroy__"] = ValueTrack_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueTrack_float__destroy(self);
};
// ValueTrack<mud::Colour>
function ValueTrack_mud_Colour(mode, curve, min_curve, max_curve) {
    /* mode <mud::TrackMode> [] */
    if (mode && typeof mode === "object") mode = mode.ptr;
    /* curve <mud::ValueCurve<mud::Colour>> [] */
    if (typeof curve !== "undefined" && curve !== null) { curve = curve.ptr; }
    /* min_curve <mud::ValueCurve<mud::Colour>> [] */
    if (typeof min_curve !== "undefined" && min_curve !== null) { min_curve = min_curve.ptr; }
    /* max_curve <mud::ValueCurve<mud::Colour>> [] */
    if (typeof max_curve !== "undefined" && max_curve !== null) { max_curve = max_curve.ptr; }
    if (mode === undefined) { this.ptr = _mud_ValueTrack_mud_Colour__construct_0(); getCache(ValueTrack_mud_Colour)[this.ptr] = this; return; }
    this.ptr = _mud_ValueTrack_mud_Colour__construct_4(mode, curve, min_curve, max_curve); getCache(ValueTrack_mud_Colour)[this.ptr] = this;
    this.type = ValueTrack_mud_Colour;
};
ValueTrack_mud_Colour.prototype = Object.create(WrapperObject.prototype);
ValueTrack_mud_Colour.prototype.constructor = ValueTrack_mud_Colour;
ValueTrack_mud_Colour.prototype.__class__ = ValueTrack_mud_Colour;
ValueTrack_mud_Colour.__cache__ = {};
Module['ValueTrack_mud_Colour'] = ValueTrack_mud_Colour;
Object.defineProperty(ValueTrack_mud_Colour.prototype, "mode", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueTrack_mud_Colour__get_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::TrackMode> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_ValueTrack_mud_Colour__set_mode(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_value(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Colour> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_Colour__set_value(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_min(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Colour> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_Colour__set_min(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_max(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Colour> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_Colour__set_max(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_curve(self), ValueCurve_mud_Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<mud::Colour>> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_Colour__set_curve(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "min_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_min_curve(self), ValueCurve_mud_Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<mud::Colour>> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_Colour__set_min_curve(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "max_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_max_curve(self), ValueCurve_mud_Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<mud::Colour>> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_Colour__set_max_curve(self, value);
    }
});
ValueTrack_mud_Colour.prototype["__destroy__"] = ValueTrack_mud_Colour.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueTrack_mud_Colour__destroy(self);
};
// ValueTrack<mud::quat>
function ValueTrack_mud_quat(mode, curve, min_curve, max_curve) {
    /* mode <mud::TrackMode> [] */
    if (mode && typeof mode === "object") mode = mode.ptr;
    /* curve <mud::ValueCurve<mud::quat>> [] */
    if (typeof curve !== "undefined" && curve !== null) { curve = curve.ptr; }
    /* min_curve <mud::ValueCurve<mud::quat>> [] */
    if (typeof min_curve !== "undefined" && min_curve !== null) { min_curve = min_curve.ptr; }
    /* max_curve <mud::ValueCurve<mud::quat>> [] */
    if (typeof max_curve !== "undefined" && max_curve !== null) { max_curve = max_curve.ptr; }
    if (mode === undefined) { this.ptr = _mud_ValueTrack_mud_quat__construct_0(); getCache(ValueTrack_mud_quat)[this.ptr] = this; return; }
    this.ptr = _mud_ValueTrack_mud_quat__construct_4(mode, curve, min_curve, max_curve); getCache(ValueTrack_mud_quat)[this.ptr] = this;
    this.type = ValueTrack_mud_quat;
};
ValueTrack_mud_quat.prototype = Object.create(WrapperObject.prototype);
ValueTrack_mud_quat.prototype.constructor = ValueTrack_mud_quat;
ValueTrack_mud_quat.prototype.__class__ = ValueTrack_mud_quat;
ValueTrack_mud_quat.__cache__ = {};
Module['ValueTrack_mud_quat'] = ValueTrack_mud_quat;
Object.defineProperty(ValueTrack_mud_quat.prototype, "mode", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueTrack_mud_quat__get_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::TrackMode> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_ValueTrack_mud_quat__set_mode(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_quat__get_value(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::quat> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_quat__set_value(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_quat__get_min(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::quat> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_quat__set_min(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_quat__get_max(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::quat> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_quat__set_max(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_quat__get_curve(self), ValueCurve_mud_quat);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<mud::quat>> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_quat__set_curve(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "min_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_quat__get_min_curve(self), ValueCurve_mud_quat);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<mud::quat>> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_quat__set_min_curve(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "max_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_quat__get_max_curve(self), ValueCurve_mud_quat);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<mud::quat>> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_quat__set_max_curve(self, value);
    }
});
ValueTrack_mud_quat.prototype["__destroy__"] = ValueTrack_mud_quat.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueTrack_mud_quat__destroy(self);
};
// ValueTrack<mud::vec3>
function ValueTrack_mud_vec3(mode, curve, min_curve, max_curve) {
    /* mode <mud::TrackMode> [] */
    if (mode && typeof mode === "object") mode = mode.ptr;
    /* curve <mud::ValueCurve<mud::vec3>> [] */
    if (typeof curve !== "undefined" && curve !== null) { curve = curve.ptr; }
    /* min_curve <mud::ValueCurve<mud::vec3>> [] */
    if (typeof min_curve !== "undefined" && min_curve !== null) { min_curve = min_curve.ptr; }
    /* max_curve <mud::ValueCurve<mud::vec3>> [] */
    if (typeof max_curve !== "undefined" && max_curve !== null) { max_curve = max_curve.ptr; }
    if (mode === undefined) { this.ptr = _mud_ValueTrack_mud_vec3__construct_0(); getCache(ValueTrack_mud_vec3)[this.ptr] = this; return; }
    this.ptr = _mud_ValueTrack_mud_vec3__construct_4(mode, curve, min_curve, max_curve); getCache(ValueTrack_mud_vec3)[this.ptr] = this;
    this.type = ValueTrack_mud_vec3;
};
ValueTrack_mud_vec3.prototype = Object.create(WrapperObject.prototype);
ValueTrack_mud_vec3.prototype.constructor = ValueTrack_mud_vec3;
ValueTrack_mud_vec3.prototype.__class__ = ValueTrack_mud_vec3;
ValueTrack_mud_vec3.__cache__ = {};
Module['ValueTrack_mud_vec3'] = ValueTrack_mud_vec3;
Object.defineProperty(ValueTrack_mud_vec3.prototype, "mode", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueTrack_mud_vec3__get_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::TrackMode> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_ValueTrack_mud_vec3__set_mode(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_value(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_vec3__set_value(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_min(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_vec3__set_min(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_max(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_vec3__set_max(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_curve(self), ValueCurve_mud_vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<mud::vec3>> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_vec3__set_curve(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "min_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_min_curve(self), ValueCurve_mud_vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<mud::vec3>> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_vec3__set_min_curve(self, value);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "max_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_max_curve(self), ValueCurve_mud_vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<mud::vec3>> [] */
        value = value.ptr;
        _mud_ValueTrack_mud_vec3__set_max_curve(self, value);
    }
});
ValueTrack_mud_vec3.prototype["__destroy__"] = ValueTrack_mud_vec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueTrack_mud_vec3__destroy(self);
};
// ValueTrack<uint32_t>
function ValueTrack_uint32_t(mode, curve, min_curve, max_curve) {
    /* mode <mud::TrackMode> [] */
    if (mode && typeof mode === "object") mode = mode.ptr;
    /* curve <mud::ValueCurve<uint32_t>> [] */
    if (typeof curve !== "undefined" && curve !== null) { curve = curve.ptr; }
    /* min_curve <mud::ValueCurve<uint32_t>> [] */
    if (typeof min_curve !== "undefined" && min_curve !== null) { min_curve = min_curve.ptr; }
    /* max_curve <mud::ValueCurve<uint32_t>> [] */
    if (typeof max_curve !== "undefined" && max_curve !== null) { max_curve = max_curve.ptr; }
    if (mode === undefined) { this.ptr = _mud_ValueTrack_uint32_t__construct_0(); getCache(ValueTrack_uint32_t)[this.ptr] = this; return; }
    this.ptr = _mud_ValueTrack_uint32_t__construct_4(mode, curve, min_curve, max_curve); getCache(ValueTrack_uint32_t)[this.ptr] = this;
    this.type = ValueTrack_uint32_t;
};
ValueTrack_uint32_t.prototype = Object.create(WrapperObject.prototype);
ValueTrack_uint32_t.prototype.constructor = ValueTrack_uint32_t;
ValueTrack_uint32_t.prototype.__class__ = ValueTrack_uint32_t;
ValueTrack_uint32_t.__cache__ = {};
Module['ValueTrack_uint32_t'] = ValueTrack_uint32_t;
Object.defineProperty(ValueTrack_uint32_t.prototype, "mode", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueTrack_uint32_t__get_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::TrackMode> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_ValueTrack_uint32_t__set_mode(self, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueTrack_uint32_t__get_value(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_ValueTrack_uint32_t__set_value(self, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueTrack_uint32_t__get_min(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_ValueTrack_uint32_t__set_min(self, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueTrack_uint32_t__get_max(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_ValueTrack_uint32_t__set_max(self, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_uint32_t__get_curve(self), ValueCurve_uint32_t);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<uint32_t>> [] */
        value = value.ptr;
        _mud_ValueTrack_uint32_t__set_curve(self, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "min_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_uint32_t__get_min_curve(self), ValueCurve_uint32_t);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<uint32_t>> [] */
        value = value.ptr;
        _mud_ValueTrack_uint32_t__set_min_curve(self, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "max_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_uint32_t__get_max_curve(self), ValueCurve_uint32_t);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::ValueCurve<uint32_t>> [] */
        value = value.ptr;
        _mud_ValueTrack_uint32_t__set_max_curve(self, value);
    }
});
ValueTrack_uint32_t.prototype["__destroy__"] = ValueTrack_uint32_t.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueTrack_uint32_t__destroy(self);
};
// mat3
function mat3(x, y, z) {
    /* x <mud::float3> [] */
    if (typeof x !== "undefined" && x !== null) { x = x.ptr; }
    /* y <mud::float3> [] */
    if (typeof y !== "undefined" && y !== null) { y = y.ptr; }
    /* z <mud::float3> [] */
    if (typeof z !== "undefined" && z !== null) { z = z.ptr; }
    if (x === undefined) { this.ptr = _mud_mat3__construct_0(); getCache(mat3)[this.ptr] = this; return; }
    this.ptr = _mud_mat3__construct_3(x, y, z); getCache(mat3)[this.ptr] = this;
    this.type = mat3;
};
mat3.prototype = Object.create(WrapperObject.prototype);
mat3.prototype.constructor = mat3;
mat3.prototype.__class__ = mat3;
mat3.__cache__ = {};
Module['mat3'] = mat3;
Object.defineProperty(mat3.prototype, "f", {
    get: function() {
        var self = this.ptr;
        return _mud_mat3__get_f(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_mat3__set_f(self, value);
    }
});
mat3.prototype["__destroy__"] = mat3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_mat3__destroy(self);
};
// mat4
function mat4(x, y, z, w) {
    /* x <mud::float4> [] */
    if (typeof x !== "undefined" && x !== null) { x = x.ptr; }
    /* y <mud::float4> [] */
    if (typeof y !== "undefined" && y !== null) { y = y.ptr; }
    /* z <mud::float4> [] */
    if (typeof z !== "undefined" && z !== null) { z = z.ptr; }
    /* w <mud::float4> [] */
    if (typeof w !== "undefined" && w !== null) { w = w.ptr; }
    if (x === undefined) { this.ptr = _mud_mat4__construct_0(); getCache(mat4)[this.ptr] = this; return; }
    this.ptr = _mud_mat4__construct_4(x, y, z, w); getCache(mat4)[this.ptr] = this;
    this.type = mat4;
};
mat4.prototype = Object.create(WrapperObject.prototype);
mat4.prototype.constructor = mat4;
mat4.prototype.__class__ = mat4;
mat4.__cache__ = {};
Module['mat4'] = mat4;
Object.defineProperty(mat4.prototype, "f", {
    get: function() {
        var self = this.ptr;
        return _mud_mat4__get_f(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_mat4__set_f(self, value);
    }
});
mat4.prototype["__destroy__"] = mat4.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_mat4__destroy(self);
};
// v2<bool>
function v2_bool(x, y) {
    /* x <bool> [] */
    /* y <bool> [] */
    if (x === undefined) { this.ptr = _mud_v2_bool__construct_0(); getCache(v2_bool)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_v2_bool__construct_1(x); getCache(v2_bool)[this.ptr] = this; return; }
    this.ptr = _mud_v2_bool__construct_2(x, y); getCache(v2_bool)[this.ptr] = this;
    this.type = v2_bool;
};
v2_bool.prototype = Object.create(WrapperObject.prototype);
v2_bool.prototype.constructor = v2_bool;
v2_bool.prototype.__class__ = v2_bool;
v2_bool.__cache__ = {};
Module['v2_bool'] = v2_bool;
Object.defineProperty(v2_bool.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_v2_bool__get_x(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_v2_bool__set_x(self, value);
    }
});
Object.defineProperty(v2_bool.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_v2_bool__get_y(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_v2_bool__set_y(self, value);
    }
});
v2_bool.prototype["__destroy__"] = v2_bool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v2_bool__destroy(self);
};
// v2<float>
function v2_float(x, y) {
    /* x <float> [] */
    /* y <float> [] */
    if (x === undefined) { this.ptr = _mud_v2_float__construct_0(); getCache(v2_float)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_v2_float__construct_1(x); getCache(v2_float)[this.ptr] = this; return; }
    this.ptr = _mud_v2_float__construct_2(x, y); getCache(v2_float)[this.ptr] = this;
    this.type = v2_float;
};
v2_float.prototype = Object.create(WrapperObject.prototype);
v2_float.prototype.constructor = v2_float;
v2_float.prototype.__class__ = v2_float;
v2_float.__cache__ = {};
Module['v2_float'] = v2_float;
Object.defineProperty(v2_float.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_float__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_v2_float__set_x(self, value);
    }
});
Object.defineProperty(v2_float.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_float__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_v2_float__set_y(self, value);
    }
});
v2_float.prototype["__destroy__"] = v2_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v2_float__destroy(self);
};
// v2<int>
function v2_int(x, y) {
    /* x <int> [] */
    /* y <int> [] */
    if (x === undefined) { this.ptr = _mud_v2_int__construct_0(); getCache(v2_int)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_v2_int__construct_1(x); getCache(v2_int)[this.ptr] = this; return; }
    this.ptr = _mud_v2_int__construct_2(x, y); getCache(v2_int)[this.ptr] = this;
    this.type = v2_int;
};
v2_int.prototype = Object.create(WrapperObject.prototype);
v2_int.prototype.constructor = v2_int;
v2_int.prototype.__class__ = v2_int;
v2_int.__cache__ = {};
Module['v2_int'] = v2_int;
Object.defineProperty(v2_int.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_int__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_v2_int__set_x(self, value);
    }
});
Object.defineProperty(v2_int.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_int__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_v2_int__set_y(self, value);
    }
});
v2_int.prototype["__destroy__"] = v2_int.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v2_int__destroy(self);
};
// v2<stl::uint>
function v2_stl_uint(x, y) {
    /* x <stl::uint> [] */
    /* y <stl::uint> [] */
    if (x === undefined) { this.ptr = _mud_v2_stl_uint__construct_0(); getCache(v2_stl_uint)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_v2_stl_uint__construct_1(x); getCache(v2_stl_uint)[this.ptr] = this; return; }
    this.ptr = _mud_v2_stl_uint__construct_2(x, y); getCache(v2_stl_uint)[this.ptr] = this;
    this.type = v2_stl_uint;
};
v2_stl_uint.prototype = Object.create(WrapperObject.prototype);
v2_stl_uint.prototype.constructor = v2_stl_uint;
v2_stl_uint.prototype.__class__ = v2_stl_uint;
v2_stl_uint.__cache__ = {};
Module['v2_stl_uint'] = v2_stl_uint;
Object.defineProperty(v2_stl_uint.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_stl_uint__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <stl::uint> [] */
        _mud_v2_stl_uint__set_x(self, value);
    }
});
Object.defineProperty(v2_stl_uint.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_stl_uint__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <stl::uint> [] */
        _mud_v2_stl_uint__set_y(self, value);
    }
});
v2_stl_uint.prototype["__destroy__"] = v2_stl_uint.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v2_stl_uint__destroy(self);
};
// v3<bool>
function v3_bool(x, y, z) {
    /* x <bool> [] */
    /* y <bool> [] */
    /* z <bool> [] */
    if (x === undefined) { this.ptr = _mud_v3_bool__construct_0(); getCache(v3_bool)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_v3_bool__construct_1(x); getCache(v3_bool)[this.ptr] = this; return; }
    this.ptr = _mud_v3_bool__construct_3(x, y, z); getCache(v3_bool)[this.ptr] = this;
    this.type = v3_bool;
};
v3_bool.prototype = Object.create(WrapperObject.prototype);
v3_bool.prototype.constructor = v3_bool;
v3_bool.prototype.__class__ = v3_bool;
v3_bool.__cache__ = {};
Module['v3_bool'] = v3_bool;
Object.defineProperty(v3_bool.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_v3_bool__get_x(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_v3_bool__set_x(self, value);
    }
});
Object.defineProperty(v3_bool.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_v3_bool__get_y(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_v3_bool__set_y(self, value);
    }
});
Object.defineProperty(v3_bool.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_v3_bool__get_z(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_v3_bool__set_z(self, value);
    }
});
v3_bool.prototype["__destroy__"] = v3_bool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v3_bool__destroy(self);
};
// v3<float>
function v3_float(x, y, z) {
    /* x <float> [] */
    /* y <float> [] */
    /* z <float> [] */
    if (x === undefined) { this.ptr = _mud_v3_float__construct_0(); getCache(v3_float)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_v3_float__construct_1(x); getCache(v3_float)[this.ptr] = this; return; }
    this.ptr = _mud_v3_float__construct_3(x, y, z); getCache(v3_float)[this.ptr] = this;
    this.type = v3_float;
};
v3_float.prototype = Object.create(WrapperObject.prototype);
v3_float.prototype.constructor = v3_float;
v3_float.prototype.__class__ = v3_float;
v3_float.__cache__ = {};
Module['v3_float'] = v3_float;
Object.defineProperty(v3_float.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v3_float__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_v3_float__set_x(self, value);
    }
});
Object.defineProperty(v3_float.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v3_float__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_v3_float__set_y(self, value);
    }
});
Object.defineProperty(v3_float.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_v3_float__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_v3_float__set_z(self, value);
    }
});
v3_float.prototype["__destroy__"] = v3_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v3_float__destroy(self);
};
// v3<int>
function v3_int(x, y, z) {
    /* x <int> [] */
    /* y <int> [] */
    /* z <int> [] */
    if (x === undefined) { this.ptr = _mud_v3_int__construct_0(); getCache(v3_int)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_v3_int__construct_1(x); getCache(v3_int)[this.ptr] = this; return; }
    this.ptr = _mud_v3_int__construct_3(x, y, z); getCache(v3_int)[this.ptr] = this;
    this.type = v3_int;
};
v3_int.prototype = Object.create(WrapperObject.prototype);
v3_int.prototype.constructor = v3_int;
v3_int.prototype.__class__ = v3_int;
v3_int.__cache__ = {};
Module['v3_int'] = v3_int;
Object.defineProperty(v3_int.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v3_int__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_v3_int__set_x(self, value);
    }
});
Object.defineProperty(v3_int.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v3_int__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_v3_int__set_y(self, value);
    }
});
Object.defineProperty(v3_int.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_v3_int__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_v3_int__set_z(self, value);
    }
});
v3_int.prototype["__destroy__"] = v3_int.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v3_int__destroy(self);
};
// v3<stl::uint>
function v3_stl_uint(x, y, z) {
    /* x <stl::uint> [] */
    /* y <stl::uint> [] */
    /* z <stl::uint> [] */
    if (x === undefined) { this.ptr = _mud_v3_stl_uint__construct_0(); getCache(v3_stl_uint)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_v3_stl_uint__construct_1(x); getCache(v3_stl_uint)[this.ptr] = this; return; }
    this.ptr = _mud_v3_stl_uint__construct_3(x, y, z); getCache(v3_stl_uint)[this.ptr] = this;
    this.type = v3_stl_uint;
};
v3_stl_uint.prototype = Object.create(WrapperObject.prototype);
v3_stl_uint.prototype.constructor = v3_stl_uint;
v3_stl_uint.prototype.__class__ = v3_stl_uint;
v3_stl_uint.__cache__ = {};
Module['v3_stl_uint'] = v3_stl_uint;
Object.defineProperty(v3_stl_uint.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v3_stl_uint__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <stl::uint> [] */
        _mud_v3_stl_uint__set_x(self, value);
    }
});
Object.defineProperty(v3_stl_uint.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v3_stl_uint__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <stl::uint> [] */
        _mud_v3_stl_uint__set_y(self, value);
    }
});
Object.defineProperty(v3_stl_uint.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_v3_stl_uint__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <stl::uint> [] */
        _mud_v3_stl_uint__set_z(self, value);
    }
});
v3_stl_uint.prototype["__destroy__"] = v3_stl_uint.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v3_stl_uint__destroy(self);
};
// v4<bool>
function v4_bool(x, y, z, w) {
    /* x <bool> [] */
    /* y <bool> [] */
    /* z <bool> [] */
    /* w <bool> [] */
    if (x === undefined) { this.ptr = _mud_v4_bool__construct_0(); getCache(v4_bool)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_v4_bool__construct_1(x); getCache(v4_bool)[this.ptr] = this; return; }
    this.ptr = _mud_v4_bool__construct_4(x, y, z, w); getCache(v4_bool)[this.ptr] = this;
    this.type = v4_bool;
};
v4_bool.prototype = Object.create(WrapperObject.prototype);
v4_bool.prototype.constructor = v4_bool;
v4_bool.prototype.__class__ = v4_bool;
v4_bool.__cache__ = {};
Module['v4_bool'] = v4_bool;
Object.defineProperty(v4_bool.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_v4_bool__get_x(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_v4_bool__set_x(self, value);
    }
});
Object.defineProperty(v4_bool.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_v4_bool__get_y(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_v4_bool__set_y(self, value);
    }
});
Object.defineProperty(v4_bool.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_v4_bool__get_z(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_v4_bool__set_z(self, value);
    }
});
Object.defineProperty(v4_bool.prototype, "w", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_v4_bool__get_w(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_v4_bool__set_w(self, value);
    }
});
v4_bool.prototype["__destroy__"] = v4_bool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v4_bool__destroy(self);
};
// v4<float>
function v4_float(x, y, z, w) {
    /* x <float> [] */
    /* y <float> [] */
    /* z <float> [] */
    /* w <float> [] */
    if (x === undefined) { this.ptr = _mud_v4_float__construct_0(); getCache(v4_float)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_v4_float__construct_1(x); getCache(v4_float)[this.ptr] = this; return; }
    this.ptr = _mud_v4_float__construct_4(x, y, z, w); getCache(v4_float)[this.ptr] = this;
    this.type = v4_float;
};
v4_float.prototype = Object.create(WrapperObject.prototype);
v4_float.prototype.constructor = v4_float;
v4_float.prototype.__class__ = v4_float;
v4_float.__cache__ = {};
Module['v4_float'] = v4_float;
Object.defineProperty(v4_float.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_float__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_v4_float__set_x(self, value);
    }
});
Object.defineProperty(v4_float.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_float__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_v4_float__set_y(self, value);
    }
});
Object.defineProperty(v4_float.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_float__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_v4_float__set_z(self, value);
    }
});
Object.defineProperty(v4_float.prototype, "w", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_float__get_w(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_v4_float__set_w(self, value);
    }
});
v4_float.prototype["__destroy__"] = v4_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v4_float__destroy(self);
};
// v4<int>
function v4_int(x, y, z, w) {
    /* x <int> [] */
    /* y <int> [] */
    /* z <int> [] */
    /* w <int> [] */
    if (x === undefined) { this.ptr = _mud_v4_int__construct_0(); getCache(v4_int)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_v4_int__construct_1(x); getCache(v4_int)[this.ptr] = this; return; }
    this.ptr = _mud_v4_int__construct_4(x, y, z, w); getCache(v4_int)[this.ptr] = this;
    this.type = v4_int;
};
v4_int.prototype = Object.create(WrapperObject.prototype);
v4_int.prototype.constructor = v4_int;
v4_int.prototype.__class__ = v4_int;
v4_int.__cache__ = {};
Module['v4_int'] = v4_int;
Object.defineProperty(v4_int.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_int__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_v4_int__set_x(self, value);
    }
});
Object.defineProperty(v4_int.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_int__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_v4_int__set_y(self, value);
    }
});
Object.defineProperty(v4_int.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_int__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_v4_int__set_z(self, value);
    }
});
Object.defineProperty(v4_int.prototype, "w", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_int__get_w(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_v4_int__set_w(self, value);
    }
});
v4_int.prototype["__destroy__"] = v4_int.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v4_int__destroy(self);
};
// v4<stl::uint>
function v4_stl_uint(x, y, z, w) {
    /* x <stl::uint> [] */
    /* y <stl::uint> [] */
    /* z <stl::uint> [] */
    /* w <stl::uint> [] */
    if (x === undefined) { this.ptr = _mud_v4_stl_uint__construct_0(); getCache(v4_stl_uint)[this.ptr] = this; return; }
    if (y === undefined) { this.ptr = _mud_v4_stl_uint__construct_1(x); getCache(v4_stl_uint)[this.ptr] = this; return; }
    this.ptr = _mud_v4_stl_uint__construct_4(x, y, z, w); getCache(v4_stl_uint)[this.ptr] = this;
    this.type = v4_stl_uint;
};
v4_stl_uint.prototype = Object.create(WrapperObject.prototype);
v4_stl_uint.prototype.constructor = v4_stl_uint;
v4_stl_uint.prototype.__class__ = v4_stl_uint;
v4_stl_uint.__cache__ = {};
Module['v4_stl_uint'] = v4_stl_uint;
Object.defineProperty(v4_stl_uint.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_stl_uint__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <stl::uint> [] */
        _mud_v4_stl_uint__set_x(self, value);
    }
});
Object.defineProperty(v4_stl_uint.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_stl_uint__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <stl::uint> [] */
        _mud_v4_stl_uint__set_y(self, value);
    }
});
Object.defineProperty(v4_stl_uint.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_stl_uint__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <stl::uint> [] */
        _mud_v4_stl_uint__set_z(self, value);
    }
});
Object.defineProperty(v4_stl_uint.prototype, "w", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_stl_uint__get_w(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <stl::uint> [] */
        _mud_v4_stl_uint__set_w(self, value);
    }
});
v4_stl_uint.prototype["__destroy__"] = v4_stl_uint.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v4_stl_uint__destroy(self);
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
// quat
function quat(x, y, z, w) {
    /* x <float> [] */
    /* y <float> [] */
    /* z <float> [] */
    /* w <float> [] */
    if (x === undefined) { this.ptr = _mud_quat__construct_0(); getCache(quat)[this.ptr] = this; return; }
    this.ptr = _mud_quat__construct_4(x, y, z, w); getCache(quat)[this.ptr] = this;
    this.type = quat;
};
quat.prototype = Object.create(WrapperObject.prototype);
quat.prototype.constructor = quat;
quat.prototype.__class__ = quat;
quat.__cache__ = {};
Module['quat'] = quat;
quat.prototype["__destroy__"] = quat.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_quat__destroy(self);
};
Module['to_rgba'] = function(colour) {
    var self = this.ptr;
    /* colour <mud::Colour> [] */
    colour = colour.ptr;
    return _mud_to_rgba_1(colour);
};
Module['to_abgr'] = function(colour) {
    var self = this.ptr;
    /* colour <mud::Colour> [] */
    colour = colour.ptr;
    return _mud_to_abgr_1(colour);
};
Module['from_rgba'] = function(colour) {
    var self = this.ptr;
    /* colour <uint32_t> [] */
    return wrapPointer(_mud_from_rgba_1(colour), Colour);
};
Module['from_abgr'] = function(colour) {
    var self = this.ptr;
    /* colour <uint32_t> [] */
    return wrapPointer(_mud_from_abgr_1(colour), Colour);
};
Module['to_linear'] = function(colour) {
    var self = this.ptr;
    /* colour <mud::Colour> [] */
    colour = colour.ptr;
    return wrapPointer(_mud_to_linear_1(colour), Colour);
};
Module['to_gamma'] = function(colour) {
    var self = this.ptr;
    /* colour <mud::Colour> [] */
    colour = colour.ptr;
    return wrapPointer(_mud_to_gamma_1(colour), Colour);
};
Module['to_srgb'] = function(colour) {
    var self = this.ptr;
    /* colour <mud::Colour> [] */
    colour = colour.ptr;
    return wrapPointer(_mud_to_srgb_1(colour), Colour);
};
Module['hsl_to_rgb'] = function(h, s, l) {
    var self = this.ptr;
    /* h <float> [] */
    /* s <float> [] */
    /* l <float> [] */
    return wrapPointer(_mud_hsl_to_rgb_3(h, s, l), Colour);
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
    /* colour <mud::Colour> [] */
    colour = colour.ptr;
    return wrapPointer(_mud_rgba_to_hsla_1(colour), Colour);
};
Module['hsla_to_rgba'] = function(colour) {
    var self = this.ptr;
    /* colour <mud::Colour> [] */
    colour = colour.ptr;
    return wrapPointer(_mud_hsla_to_rgba_1(colour), Colour);
};
Module['sinf'] = function(a) {
    var self = this.ptr;
    /* a <float> [] */
    return _sinf_1(a);
};
Module['cosf'] = function(a) {
    var self = this.ptr;
    /* a <float> [] */
    return _cosf_1(a);
};
Module['sin'] = function(a) {
    var self = this.ptr;
    /* a <double> [] */
    return _sin_1(a);
};
Module['cos'] = function(a) {
    var self = this.ptr;
    /* a <double> [] */
    return _cos_1(a);
};
Module['add'] = function(a, b) {
    var self = this.ptr;
    /* a <float> [] */
    /* b <float> [] */
    return _mud_add_2(a, b);
};
Module['subtract'] = function(a, b) {
    var self = this.ptr;
    /* a <float> [] */
    /* b <float> [] */
    return _mud_subtract_2(a, b);
};
Module['multiply'] = function(a, b) {
    var self = this.ptr;
    /* a <float> [] */
    /* b <float> [] */
    return _mud_multiply_2(a, b);
};
Module['divide'] = function(a, b) {
    var self = this.ptr;
    /* a <float> [] */
    /* b <float> [] */
    return _mud_divide_2(a, b);
};
Module['nsinf'] = function(a) {
    var self = this.ptr;
    /* a <float> [] */
    return _mud_nsinf_1(a);
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
Module['ncos'] = function(a) {
    var self = this.ptr;
    /* a <double> [] */
    return _mud_ncos_1(a);
};
Module['look_dir'] = function(direction, forward) {
    var self = this.ptr;
    /* direction <mud::vec3> [] */
    direction = direction.ptr;
    /* forward <mud::vec3> [] */
    if (typeof forward !== "undefined" && forward !== null) { forward = forward.ptr; }
    if (forward === undefined) { return wrapPointer(_mud_look_dir_1(direction), quat); }
    return wrapPointer(_mud_look_dir_2(direction, forward), quat);
};
Module['look_at'] = function(eye, target, forward) {
    var self = this.ptr;
    /* eye <mud::vec3> [] */
    eye = eye.ptr;
    /* target <mud::vec3> [] */
    target = target.ptr;
    /* forward <mud::vec3> [] */
    if (typeof forward !== "undefined" && forward !== null) { forward = forward.ptr; }
    if (forward === undefined) { return wrapPointer(_mud_look_at_2(eye, target), quat); }
    return wrapPointer(_mud_look_at_3(eye, target, forward), quat);
};
Module['grid_center'] = function(coord, cell_size) {
    var self = this.ptr;
    /* coord <mud::uvec3> [] */
    coord = coord.ptr;
    /* cell_size <mud::vec3> [] */
    cell_size = cell_size.ptr;
    return wrapPointer(_mud_grid_center_2(coord, cell_size), v3_float);
};

(function() {
    function setup() {
        Colour.__type__ = _mud_Colour__type();
        Image.__type__ = _mud_Image__type();
        Image256.__type__ = _mud_Image256__type();
        ImageAtlas.__type__ = _mud_ImageAtlas__type();
        Palette.__type__ = _mud_Palette__type();
        Time.__type__ = _mud_Time__type();
        TimeSpan.__type__ = _mud_TimeSpan__type();
        Transform.__type__ = _mud_Transform__type();
        mat3.__type__ = _mud_mat3__type();
        mat4.__type__ = _mud_mat4__type();
        Sprite.__type__ = _mud_Sprite__type();
        SpriteAtlas.__type__ = _mud_SpriteAtlas__type();
        TextureAtlas.__type__ = _mud_TextureAtlas__type();
        quat.__type__ = _mud_quat__type();
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
