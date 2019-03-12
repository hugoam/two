Module['stl'] = Module['stl'] || {};
// AutoStat<float>
function AutoStat_float() {
    this.__ptr = _mud_AutoStat_float__construct_0(); this.__type = AutoStat_float.__type; getCache(AutoStat_float)[this.__ptr] = this;
};
AutoStat_float.prototype = Object.create(WrapperObject.prototype);
AutoStat_float.prototype.constructor = AutoStat_float;
AutoStat_float.prototype.__class = AutoStat_float;
AutoStat_float.__cache = {};
Module['AutoStat_float'] = AutoStat_float;
Object.defineProperty(AutoStat_float.prototype, "value", {
    get: function() {
        return _mud_AutoStat_float__get_value(this.__ptr);
    },
    set: function(value) {
        _mud_AutoStat_float__set_value(this.__ptr, value);
    }
});
AutoStat_float.prototype["__destroy"] = AutoStat_float.prototype.__destroy = function() {
    _mud_AutoStat_float__destroy(this.__ptr);
};
// AutoStat<int>
function AutoStat_int() {
    this.__ptr = _mud_AutoStat_int__construct_0(); this.__type = AutoStat_int.__type; getCache(AutoStat_int)[this.__ptr] = this;
};
AutoStat_int.prototype = Object.create(WrapperObject.prototype);
AutoStat_int.prototype.constructor = AutoStat_int;
AutoStat_int.prototype.__class = AutoStat_int;
AutoStat_int.__cache = {};
Module['AutoStat_int'] = AutoStat_int;
Object.defineProperty(AutoStat_int.prototype, "value", {
    get: function() {
        return _mud_AutoStat_int__get_value(this.__ptr);
    },
    set: function(value) {
        _mud_AutoStat_int__set_value(this.__ptr, value);
    }
});
AutoStat_int.prototype["__destroy"] = AutoStat_int.prototype.__destroy = function() {
    _mud_AutoStat_int__destroy(this.__ptr);
};
// Colour
function Colour(a0, a1, a2, a3) {
    if (a0 === undefined) { this.__ptr = _mud_Colour__construct_0(); this.__type = Colour.__type; getCache(Colour)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_Colour__construct_1(/*v*/a0); this.__type = Colour.__type; getCache(Colour)[this.__ptr] = this; return; }
    if (a2 === undefined) { this.__ptr = _mud_Colour__construct_2(/*v*/a0, /*a*/a1); this.__type = Colour.__type; getCache(Colour)[this.__ptr] = this; return; }
    if (a3 === undefined) { this.__ptr = _mud_Colour__construct_3(/*r*/a0, /*g*/a1, /*b*/a2); this.__type = Colour.__type; getCache(Colour)[this.__ptr] = this; return; }
    this.__ptr = _mud_Colour__construct_4(/*r*/a0, /*g*/a1, /*b*/a2, /*a*/a3); this.__type = Colour.__type; getCache(Colour)[this.__ptr] = this;
};
Colour.prototype = Object.create(WrapperObject.prototype);
Colour.prototype.constructor = Colour;
Colour.prototype.__class = Colour;
Colour.__cache = {};
Module['Colour'] = Colour;
Object.defineProperty(Colour.prototype, "r", {
    get: function() {
        return _mud_Colour__get_r(this.__ptr);
    },
    set: function(value) {
        _mud_Colour__set_r(this.__ptr, value);
    }
});
Object.defineProperty(Colour.prototype, "g", {
    get: function() {
        return _mud_Colour__get_g(this.__ptr);
    },
    set: function(value) {
        _mud_Colour__set_g(this.__ptr, value);
    }
});
Object.defineProperty(Colour.prototype, "b", {
    get: function() {
        return _mud_Colour__get_b(this.__ptr);
    },
    set: function(value) {
        _mud_Colour__set_b(this.__ptr, value);
    }
});
Object.defineProperty(Colour.prototype, "a", {
    get: function() {
        return _mud_Colour__get_a(this.__ptr);
    },
    set: function(value) {
        _mud_Colour__set_a(this.__ptr, value);
    }
});
Colour.prototype["__destroy"] = Colour.prototype.__destroy = function() {
    _mud_Colour__destroy(this.__ptr);
};
// ColourHSL
function ColourHSL() {
    this.__ptr = _mud_ColourHSL__construct_0(); this.__type = ColourHSL.__type; getCache(ColourHSL)[this.__ptr] = this;
};
ColourHSL.prototype = Object.create(WrapperObject.prototype);
ColourHSL.prototype.constructor = ColourHSL;
ColourHSL.prototype.__class = ColourHSL;
ColourHSL.__cache = {};
Module['ColourHSL'] = ColourHSL;
Object.defineProperty(ColourHSL.prototype, "h", {
    get: function() {
        return _mud_ColourHSL__get_h(this.__ptr);
    },
    set: function(value) {
        _mud_ColourHSL__set_h(this.__ptr, value);
    }
});
Object.defineProperty(ColourHSL.prototype, "s", {
    get: function() {
        return _mud_ColourHSL__get_s(this.__ptr);
    },
    set: function(value) {
        _mud_ColourHSL__set_s(this.__ptr, value);
    }
});
Object.defineProperty(ColourHSL.prototype, "l", {
    get: function() {
        return _mud_ColourHSL__get_l(this.__ptr);
    },
    set: function(value) {
        _mud_ColourHSL__set_l(this.__ptr, value);
    }
});
Object.defineProperty(ColourHSL.prototype, "a", {
    get: function() {
        return _mud_ColourHSL__get_a(this.__ptr);
    },
    set: function(value) {
        _mud_ColourHSL__set_a(this.__ptr, value);
    }
});
ColourHSL.prototype["__destroy"] = ColourHSL.prototype.__destroy = function() {
    _mud_ColourHSL__destroy(this.__ptr);
};
// Image
function Image() {
    this.__ptr = _mud_Image__construct_0(); this.__type = Image.__type; getCache(Image)[this.__ptr] = this;
};
Image.prototype = Object.create(WrapperObject.prototype);
Image.prototype.constructor = Image;
Image.prototype.__class = Image;
Image.__cache = {};
Module['Image'] = Image;
Object.defineProperty(Image.prototype, "d_name", {
    get: function() {
        return Pointer_stringify(_mud_Image__get_d_name(this.__ptr));
    },
    set: function(value) {
        _mud_Image__set_d_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Image.prototype, "d_path", {
    get: function() {
        return Pointer_stringify(_mud_Image__get_d_path(this.__ptr));
    },
    set: function(value) {
        _mud_Image__set_d_path(this.__ptr, ensureString(value));
    }
});
Image.prototype["__destroy"] = Image.prototype.__destroy = function() {
    _mud_Image__destroy(this.__ptr);
};
// Image256
function Image256(a0, a1) {
    if (a0 === undefined) { this.__ptr = _mud_Image256__construct_0(); this.__type = Image256.__type; getCache(Image256)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_Image256__construct_1(/*size*/a0.__ptr); this.__type = Image256.__type; getCache(Image256)[this.__ptr] = this; return; }
    this.__ptr = _mud_Image256__construct_2(/*size*/a0.__ptr, /*palette*/a1.__ptr); this.__type = Image256.__type; getCache(Image256)[this.__ptr] = this;
};
Image256.prototype = Object.create(WrapperObject.prototype);
Image256.prototype.constructor = Image256;
Image256.prototype.__class = Image256;
Image256.__cache = {};
Module['Image256'] = Image256;
Object.defineProperty(Image256.prototype, "pixels", {
    get: function() {
        return _mud_Image256__get_pixels(this.__ptr);
    }});
Object.defineProperty(Image256.prototype, "size", {
    get: function() {
        return wrapPointer(_mud_Image256__get_size(this.__ptr), v2_uint);
    },
    set: function(value) {
        _mud_Image256__set_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Image256.prototype, "palette", {
    get: function() {
        return wrapPointer(_mud_Image256__get_palette(this.__ptr), Palette);
    },
    set: function(value) {
        _mud_Image256__set_palette(this.__ptr, value.__ptr);
    }
});
Image256.prototype["__destroy"] = Image256.prototype.__destroy = function() {
    _mud_Image256__destroy(this.__ptr);
};
// ImageAtlas
function ImageAtlas() { throw "cannot construct a ImageAtlas, no constructor in IDL" }
ImageAtlas.prototype = Object.create(WrapperObject.prototype);
ImageAtlas.prototype.constructor = ImageAtlas;
ImageAtlas.prototype.__class = ImageAtlas;
ImageAtlas.__cache = {};
Module['ImageAtlas'] = ImageAtlas;
ImageAtlas.prototype["__destroy"] = ImageAtlas.prototype.__destroy = function() {
    _mud_ImageAtlas__destroy(this.__ptr);
};
// Palette
function Palette(a0, a1) {
    if (a0 === undefined) { this.__ptr = _mud_Palette__construct_0(); this.__type = Palette.__type; getCache(Palette)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_Palette__construct_1(ensureFloat32(/*colours*/a0), /*colours*/a0.length); this.__type = Palette.__type; getCache(Palette)[this.__ptr] = this; return; }
    this.__ptr = _mud_Palette__construct_2(/*spectrum*/a0, /*steps*/a1); this.__type = Palette.__type; getCache(Palette)[this.__ptr] = this;
};
Palette.prototype = Object.create(WrapperObject.prototype);
Palette.prototype.constructor = Palette;
Palette.prototype.__class = Palette;
Palette.__cache = {};
Module['Palette'] = Palette;
Palette.prototype["__destroy"] = Palette.prototype.__destroy = function() {
    _mud_Palette__destroy(this.__ptr);
};
// Range<float>
function Range_float() {
    this.__ptr = _mud_Range_float__construct_0(); this.__type = Range_float.__type; getCache(Range_float)[this.__ptr] = this;
};
Range_float.prototype = Object.create(WrapperObject.prototype);
Range_float.prototype.constructor = Range_float;
Range_float.prototype.__class = Range_float;
Range_float.__cache = {};
Module['Range_float'] = Range_float;
Object.defineProperty(Range_float.prototype, "min", {
    get: function() {
        return _mud_Range_float__get_min(this.__ptr);
    },
    set: function(value) {
        _mud_Range_float__set_min(this.__ptr, value);
    }
});
Object.defineProperty(Range_float.prototype, "max", {
    get: function() {
        return _mud_Range_float__get_max(this.__ptr);
    },
    set: function(value) {
        _mud_Range_float__set_max(this.__ptr, value);
    }
});
Range_float.prototype["__destroy"] = Range_float.prototype.__destroy = function() {
    _mud_Range_float__destroy(this.__ptr);
};
// Range<mud::Colour>
function Range_mud_Colour() {
    this.__ptr = _mud_Range_mud_Colour__construct_0(); this.__type = Range_mud_Colour.__type; getCache(Range_mud_Colour)[this.__ptr] = this;
};
Range_mud_Colour.prototype = Object.create(WrapperObject.prototype);
Range_mud_Colour.prototype.constructor = Range_mud_Colour;
Range_mud_Colour.prototype.__class = Range_mud_Colour;
Range_mud_Colour.__cache = {};
Module['Range_mud_Colour'] = Range_mud_Colour;
Object.defineProperty(Range_mud_Colour.prototype, "min", {
    get: function() {
        return wrapPointer(_mud_Range_mud_Colour__get_min(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_Range_mud_Colour__set_min(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Range_mud_Colour.prototype, "max", {
    get: function() {
        return wrapPointer(_mud_Range_mud_Colour__get_max(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_Range_mud_Colour__set_max(this.__ptr, value.__ptr);
    }
});
Range_mud_Colour.prototype["__destroy"] = Range_mud_Colour.prototype.__destroy = function() {
    _mud_Range_mud_Colour__destroy(this.__ptr);
};
// Range<mud::quat>
function Range_mud_quat() {
    this.__ptr = _mud_Range_mud_quat__construct_0(); this.__type = Range_mud_quat.__type; getCache(Range_mud_quat)[this.__ptr] = this;
};
Range_mud_quat.prototype = Object.create(WrapperObject.prototype);
Range_mud_quat.prototype.constructor = Range_mud_quat;
Range_mud_quat.prototype.__class = Range_mud_quat;
Range_mud_quat.__cache = {};
Module['Range_mud_quat'] = Range_mud_quat;
Object.defineProperty(Range_mud_quat.prototype, "min", {
    get: function() {
        return wrapPointer(_mud_Range_mud_quat__get_min(this.__ptr), quat);
    },
    set: function(value) {
        _mud_Range_mud_quat__set_min(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Range_mud_quat.prototype, "max", {
    get: function() {
        return wrapPointer(_mud_Range_mud_quat__get_max(this.__ptr), quat);
    },
    set: function(value) {
        _mud_Range_mud_quat__set_max(this.__ptr, value.__ptr);
    }
});
Range_mud_quat.prototype["__destroy"] = Range_mud_quat.prototype.__destroy = function() {
    _mud_Range_mud_quat__destroy(this.__ptr);
};
// Range<mud::vec3>
function Range_mud_vec3() {
    this.__ptr = _mud_Range_mud_vec3__construct_0(); this.__type = Range_mud_vec3.__type; getCache(Range_mud_vec3)[this.__ptr] = this;
};
Range_mud_vec3.prototype = Object.create(WrapperObject.prototype);
Range_mud_vec3.prototype.constructor = Range_mud_vec3;
Range_mud_vec3.prototype.__class = Range_mud_vec3;
Range_mud_vec3.__cache = {};
Module['Range_mud_vec3'] = Range_mud_vec3;
Object.defineProperty(Range_mud_vec3.prototype, "min", {
    get: function() {
        return wrapPointer(_mud_Range_mud_vec3__get_min(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Range_mud_vec3__set_min(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Range_mud_vec3.prototype, "max", {
    get: function() {
        return wrapPointer(_mud_Range_mud_vec3__get_max(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Range_mud_vec3__set_max(this.__ptr, value.__ptr);
    }
});
Range_mud_vec3.prototype["__destroy"] = Range_mud_vec3.prototype.__destroy = function() {
    _mud_Range_mud_vec3__destroy(this.__ptr);
};
// Range<uint32_t>
function Range_uint32_t() {
    this.__ptr = _mud_Range_uint32_t__construct_0(); this.__type = Range_uint32_t.__type; getCache(Range_uint32_t)[this.__ptr] = this;
};
Range_uint32_t.prototype = Object.create(WrapperObject.prototype);
Range_uint32_t.prototype.constructor = Range_uint32_t;
Range_uint32_t.prototype.__class = Range_uint32_t;
Range_uint32_t.__cache = {};
Module['Range_uint32_t'] = Range_uint32_t;
Object.defineProperty(Range_uint32_t.prototype, "min", {
    get: function() {
        return _mud_Range_uint32_t__get_min(this.__ptr);
    },
    set: function(value) {
        _mud_Range_uint32_t__set_min(this.__ptr, value);
    }
});
Object.defineProperty(Range_uint32_t.prototype, "max", {
    get: function() {
        return _mud_Range_uint32_t__get_max(this.__ptr);
    },
    set: function(value) {
        _mud_Range_uint32_t__set_max(this.__ptr, value);
    }
});
Range_uint32_t.prototype["__destroy"] = Range_uint32_t.prototype.__destroy = function() {
    _mud_Range_uint32_t__destroy(this.__ptr);
};
// Time
function Time(a0) {
    this.__ptr = _mud_Time__construct_1(/*value*/a0); this.__type = Time.__type; getCache(Time)[this.__ptr] = this;
};
Time.prototype = Object.create(WrapperObject.prototype);
Time.prototype.constructor = Time;
Time.prototype.__class = Time;
Time.__cache = {};
Module['Time'] = Time;
Object.defineProperty(Time.prototype, "value", {
    get: function() {
        return _mud_Time__get_value(this.__ptr);
    },
    set: function(value) {
        _mud_Time__set_value(this.__ptr, value);
    }
});
Time.prototype["__destroy"] = Time.prototype.__destroy = function() {
    _mud_Time__destroy(this.__ptr);
};
// TimeSpan
function TimeSpan(a0, a1) {
    this.__ptr = _mud_TimeSpan__construct_2(/*s*/a0.__ptr, /*e*/a1.__ptr); this.__type = TimeSpan.__type; getCache(TimeSpan)[this.__ptr] = this;
};
TimeSpan.prototype = Object.create(WrapperObject.prototype);
TimeSpan.prototype.constructor = TimeSpan;
TimeSpan.prototype.__class = TimeSpan;
TimeSpan.__cache = {};
Module['TimeSpan'] = TimeSpan;
Object.defineProperty(TimeSpan.prototype, "start", {
    get: function() {
        return wrapPointer(_mud_TimeSpan__get_start(this.__ptr), Time);
    },
    set: function(value) {
        _mud_TimeSpan__set_start(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(TimeSpan.prototype, "end", {
    get: function() {
        return wrapPointer(_mud_TimeSpan__get_end(this.__ptr), Time);
    },
    set: function(value) {
        _mud_TimeSpan__set_end(this.__ptr, value.__ptr);
    }
});
TimeSpan.prototype["__destroy"] = TimeSpan.prototype.__destroy = function() {
    _mud_TimeSpan__destroy(this.__ptr);
};
// Transform
function Transform() {
    this.__ptr = _mud_Transform__construct_0(); this.__type = Transform.__type; getCache(Transform)[this.__ptr] = this;
};
Transform.prototype = Object.create(WrapperObject.prototype);
Transform.prototype.constructor = Transform;
Transform.prototype.__class = Transform;
Transform.__cache = {};
Module['Transform'] = Transform;
Object.defineProperty(Transform.prototype, "position", {
    get: function() {
        return wrapPointer(_mud_Transform__get_position(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Transform__set_position(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Transform.prototype, "rotation", {
    get: function() {
        return wrapPointer(_mud_Transform__get_rotation(this.__ptr), quat);
    },
    set: function(value) {
        _mud_Transform__set_rotation(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Transform.prototype, "scale", {
    get: function() {
        return wrapPointer(_mud_Transform__get_scale(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Transform__set_scale(this.__ptr, value.__ptr);
    }
});
Transform.prototype["__destroy"] = Transform.prototype.__destroy = function() {
    _mud_Transform__destroy(this.__ptr);
};
// ValueCurve<float>
function ValueCurve_float(a0) {
    if (a0 === undefined) { this.__ptr = _mud_ValueCurve_float__construct_0(); this.__type = ValueCurve_float.__type; getCache(ValueCurve_float)[this.__ptr] = this; return; }
    this.__ptr = _mud_ValueCurve_float__construct_1(ensureFloat32(/*keys*/a0), /*keys*/a0.length); this.__type = ValueCurve_float.__type; getCache(ValueCurve_float)[this.__ptr] = this;
};
ValueCurve_float.prototype = Object.create(WrapperObject.prototype);
ValueCurve_float.prototype.constructor = ValueCurve_float;
ValueCurve_float.prototype.__class = ValueCurve_float;
ValueCurve_float.__cache = {};
Module['ValueCurve_float'] = ValueCurve_float;
Object.defineProperty(ValueCurve_float.prototype, "keys", {
    get: function() {
        return _mud_ValueCurve_float__get_keys(this.__ptr);
    }});
ValueCurve_float.prototype["__destroy"] = ValueCurve_float.prototype.__destroy = function() {
    _mud_ValueCurve_float__destroy(this.__ptr);
};
// ValueCurve<mud::Colour>
function ValueCurve_mud_Colour(a0) {
    if (a0 === undefined) { this.__ptr = _mud_ValueCurve_mud_Colour__construct_0(); this.__type = ValueCurve_mud_Colour.__type; getCache(ValueCurve_mud_Colour)[this.__ptr] = this; return; }
    this.__ptr = _mud_ValueCurve_mud_Colour__construct_1(ensureFloat32(/*keys*/a0), /*keys*/a0.length); this.__type = ValueCurve_mud_Colour.__type; getCache(ValueCurve_mud_Colour)[this.__ptr] = this;
};
ValueCurve_mud_Colour.prototype = Object.create(WrapperObject.prototype);
ValueCurve_mud_Colour.prototype.constructor = ValueCurve_mud_Colour;
ValueCurve_mud_Colour.prototype.__class = ValueCurve_mud_Colour;
ValueCurve_mud_Colour.__cache = {};
Module['ValueCurve_mud_Colour'] = ValueCurve_mud_Colour;
Object.defineProperty(ValueCurve_mud_Colour.prototype, "keys", {
    get: function() {
        return _mud_ValueCurve_mud_Colour__get_keys(this.__ptr);
    }});
ValueCurve_mud_Colour.prototype["__destroy"] = ValueCurve_mud_Colour.prototype.__destroy = function() {
    _mud_ValueCurve_mud_Colour__destroy(this.__ptr);
};
// ValueCurve<mud::quat>
function ValueCurve_mud_quat() {
    this.__ptr = _mud_ValueCurve_mud_quat__construct_0(); this.__type = ValueCurve_mud_quat.__type; getCache(ValueCurve_mud_quat)[this.__ptr] = this;
};
ValueCurve_mud_quat.prototype = Object.create(WrapperObject.prototype);
ValueCurve_mud_quat.prototype.constructor = ValueCurve_mud_quat;
ValueCurve_mud_quat.prototype.__class = ValueCurve_mud_quat;
ValueCurve_mud_quat.__cache = {};
Module['ValueCurve_mud_quat'] = ValueCurve_mud_quat;
ValueCurve_mud_quat.prototype["__destroy"] = ValueCurve_mud_quat.prototype.__destroy = function() {
    _mud_ValueCurve_mud_quat__destroy(this.__ptr);
};
// ValueCurve<mud::vec3>
function ValueCurve_mud_vec3(a0) {
    if (a0 === undefined) { this.__ptr = _mud_ValueCurve_mud_vec3__construct_0(); this.__type = ValueCurve_mud_vec3.__type; getCache(ValueCurve_mud_vec3)[this.__ptr] = this; return; }
    this.__ptr = _mud_ValueCurve_mud_vec3__construct_1(ensureFloat32(/*keys*/a0), /*keys*/a0.length); this.__type = ValueCurve_mud_vec3.__type; getCache(ValueCurve_mud_vec3)[this.__ptr] = this;
};
ValueCurve_mud_vec3.prototype = Object.create(WrapperObject.prototype);
ValueCurve_mud_vec3.prototype.constructor = ValueCurve_mud_vec3;
ValueCurve_mud_vec3.prototype.__class = ValueCurve_mud_vec3;
ValueCurve_mud_vec3.__cache = {};
Module['ValueCurve_mud_vec3'] = ValueCurve_mud_vec3;
Object.defineProperty(ValueCurve_mud_vec3.prototype, "keys", {
    get: function() {
        return _mud_ValueCurve_mud_vec3__get_keys(this.__ptr);
    }});
ValueCurve_mud_vec3.prototype["__destroy"] = ValueCurve_mud_vec3.prototype.__destroy = function() {
    _mud_ValueCurve_mud_vec3__destroy(this.__ptr);
};
// ValueCurve<uint32_t>
function ValueCurve_uint32_t(a0) {
    if (a0 === undefined) { this.__ptr = _mud_ValueCurve_uint32_t__construct_0(); this.__type = ValueCurve_uint32_t.__type; getCache(ValueCurve_uint32_t)[this.__ptr] = this; return; }
    this.__ptr = _mud_ValueCurve_uint32_t__construct_1(ensureInt32(/*keys*/a0), /*keys*/a0.length); this.__type = ValueCurve_uint32_t.__type; getCache(ValueCurve_uint32_t)[this.__ptr] = this;
};
ValueCurve_uint32_t.prototype = Object.create(WrapperObject.prototype);
ValueCurve_uint32_t.prototype.constructor = ValueCurve_uint32_t;
ValueCurve_uint32_t.prototype.__class = ValueCurve_uint32_t;
ValueCurve_uint32_t.__cache = {};
Module['ValueCurve_uint32_t'] = ValueCurve_uint32_t;
Object.defineProperty(ValueCurve_uint32_t.prototype, "keys", {
    get: function() {
        return _mud_ValueCurve_uint32_t__get_keys(this.__ptr);
    }});
ValueCurve_uint32_t.prototype["__destroy"] = ValueCurve_uint32_t.prototype.__destroy = function() {
    _mud_ValueCurve_uint32_t__destroy(this.__ptr);
};
// ValueTrack<float>
function ValueTrack_float(a0, a1, a2, a3) {
    if (a0 === undefined) { this.__ptr = _mud_ValueTrack_float__construct_0(); this.__type = ValueTrack_float.__type; getCache(ValueTrack_float)[this.__ptr] = this; return; }
    this.__ptr = _mud_ValueTrack_float__construct_4(/*mode*/a0, /*curve*/a1.__ptr, /*min_curve*/a2.__ptr, /*max_curve*/a3.__ptr); this.__type = ValueTrack_float.__type; getCache(ValueTrack_float)[this.__ptr] = this;
};
ValueTrack_float.prototype = Object.create(WrapperObject.prototype);
ValueTrack_float.prototype.constructor = ValueTrack_float;
ValueTrack_float.prototype.__class = ValueTrack_float;
ValueTrack_float.__cache = {};
Module['ValueTrack_float'] = ValueTrack_float;
Object.defineProperty(ValueTrack_float.prototype, "mode", {
    get: function() {
        return _mud_ValueTrack_float__get_mode(this.__ptr);
    },
    set: function(value) {
        _mud_ValueTrack_float__set_mode(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "value", {
    get: function() {
        return _mud_ValueTrack_float__get_value(this.__ptr);
    },
    set: function(value) {
        _mud_ValueTrack_float__set_value(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "min", {
    get: function() {
        return _mud_ValueTrack_float__get_min(this.__ptr);
    },
    set: function(value) {
        _mud_ValueTrack_float__set_min(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "max", {
    get: function() {
        return _mud_ValueTrack_float__get_max(this.__ptr);
    },
    set: function(value) {
        _mud_ValueTrack_float__set_max(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_float__get_curve(this.__ptr), ValueCurve_float);
    },
    set: function(value) {
        _mud_ValueTrack_float__set_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "min_curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_float__get_min_curve(this.__ptr), ValueCurve_float);
    },
    set: function(value) {
        _mud_ValueTrack_float__set_min_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "max_curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_float__get_max_curve(this.__ptr), ValueCurve_float);
    },
    set: function(value) {
        _mud_ValueTrack_float__set_max_curve(this.__ptr, value.__ptr);
    }
});
ValueTrack_float.prototype["__destroy"] = ValueTrack_float.prototype.__destroy = function() {
    _mud_ValueTrack_float__destroy(this.__ptr);
};
// ValueTrack<mud::Colour>
function ValueTrack_mud_Colour(a0, a1, a2, a3) {
    if (a0 === undefined) { this.__ptr = _mud_ValueTrack_mud_Colour__construct_0(); this.__type = ValueTrack_mud_Colour.__type; getCache(ValueTrack_mud_Colour)[this.__ptr] = this; return; }
    this.__ptr = _mud_ValueTrack_mud_Colour__construct_4(/*mode*/a0, /*curve*/a1.__ptr, /*min_curve*/a2.__ptr, /*max_curve*/a3.__ptr); this.__type = ValueTrack_mud_Colour.__type; getCache(ValueTrack_mud_Colour)[this.__ptr] = this;
};
ValueTrack_mud_Colour.prototype = Object.create(WrapperObject.prototype);
ValueTrack_mud_Colour.prototype.constructor = ValueTrack_mud_Colour;
ValueTrack_mud_Colour.prototype.__class = ValueTrack_mud_Colour;
ValueTrack_mud_Colour.__cache = {};
Module['ValueTrack_mud_Colour'] = ValueTrack_mud_Colour;
Object.defineProperty(ValueTrack_mud_Colour.prototype, "mode", {
    get: function() {
        return _mud_ValueTrack_mud_Colour__get_mode(this.__ptr);
    },
    set: function(value) {
        _mud_ValueTrack_mud_Colour__set_mode(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "value", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_value(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_ValueTrack_mud_Colour__set_value(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "min", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_min(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_ValueTrack_mud_Colour__set_min(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "max", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_max(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_ValueTrack_mud_Colour__set_max(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_curve(this.__ptr), ValueCurve_mud_Colour);
    },
    set: function(value) {
        _mud_ValueTrack_mud_Colour__set_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "min_curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_min_curve(this.__ptr), ValueCurve_mud_Colour);
    },
    set: function(value) {
        _mud_ValueTrack_mud_Colour__set_min_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "max_curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_max_curve(this.__ptr), ValueCurve_mud_Colour);
    },
    set: function(value) {
        _mud_ValueTrack_mud_Colour__set_max_curve(this.__ptr, value.__ptr);
    }
});
ValueTrack_mud_Colour.prototype["__destroy"] = ValueTrack_mud_Colour.prototype.__destroy = function() {
    _mud_ValueTrack_mud_Colour__destroy(this.__ptr);
};
// ValueTrack<mud::quat>
function ValueTrack_mud_quat(a0, a1, a2, a3) {
    if (a0 === undefined) { this.__ptr = _mud_ValueTrack_mud_quat__construct_0(); this.__type = ValueTrack_mud_quat.__type; getCache(ValueTrack_mud_quat)[this.__ptr] = this; return; }
    this.__ptr = _mud_ValueTrack_mud_quat__construct_4(/*mode*/a0, /*curve*/a1.__ptr, /*min_curve*/a2.__ptr, /*max_curve*/a3.__ptr); this.__type = ValueTrack_mud_quat.__type; getCache(ValueTrack_mud_quat)[this.__ptr] = this;
};
ValueTrack_mud_quat.prototype = Object.create(WrapperObject.prototype);
ValueTrack_mud_quat.prototype.constructor = ValueTrack_mud_quat;
ValueTrack_mud_quat.prototype.__class = ValueTrack_mud_quat;
ValueTrack_mud_quat.__cache = {};
Module['ValueTrack_mud_quat'] = ValueTrack_mud_quat;
Object.defineProperty(ValueTrack_mud_quat.prototype, "mode", {
    get: function() {
        return _mud_ValueTrack_mud_quat__get_mode(this.__ptr);
    },
    set: function(value) {
        _mud_ValueTrack_mud_quat__set_mode(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "value", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_quat__get_value(this.__ptr), quat);
    },
    set: function(value) {
        _mud_ValueTrack_mud_quat__set_value(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "min", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_quat__get_min(this.__ptr), quat);
    },
    set: function(value) {
        _mud_ValueTrack_mud_quat__set_min(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "max", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_quat__get_max(this.__ptr), quat);
    },
    set: function(value) {
        _mud_ValueTrack_mud_quat__set_max(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_quat__get_curve(this.__ptr), ValueCurve_mud_quat);
    },
    set: function(value) {
        _mud_ValueTrack_mud_quat__set_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "min_curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_quat__get_min_curve(this.__ptr), ValueCurve_mud_quat);
    },
    set: function(value) {
        _mud_ValueTrack_mud_quat__set_min_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "max_curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_quat__get_max_curve(this.__ptr), ValueCurve_mud_quat);
    },
    set: function(value) {
        _mud_ValueTrack_mud_quat__set_max_curve(this.__ptr, value.__ptr);
    }
});
ValueTrack_mud_quat.prototype["__destroy"] = ValueTrack_mud_quat.prototype.__destroy = function() {
    _mud_ValueTrack_mud_quat__destroy(this.__ptr);
};
// ValueTrack<mud::vec3>
function ValueTrack_mud_vec3(a0, a1, a2, a3) {
    if (a0 === undefined) { this.__ptr = _mud_ValueTrack_mud_vec3__construct_0(); this.__type = ValueTrack_mud_vec3.__type; getCache(ValueTrack_mud_vec3)[this.__ptr] = this; return; }
    this.__ptr = _mud_ValueTrack_mud_vec3__construct_4(/*mode*/a0, /*curve*/a1.__ptr, /*min_curve*/a2.__ptr, /*max_curve*/a3.__ptr); this.__type = ValueTrack_mud_vec3.__type; getCache(ValueTrack_mud_vec3)[this.__ptr] = this;
};
ValueTrack_mud_vec3.prototype = Object.create(WrapperObject.prototype);
ValueTrack_mud_vec3.prototype.constructor = ValueTrack_mud_vec3;
ValueTrack_mud_vec3.prototype.__class = ValueTrack_mud_vec3;
ValueTrack_mud_vec3.__cache = {};
Module['ValueTrack_mud_vec3'] = ValueTrack_mud_vec3;
Object.defineProperty(ValueTrack_mud_vec3.prototype, "mode", {
    get: function() {
        return _mud_ValueTrack_mud_vec3__get_mode(this.__ptr);
    },
    set: function(value) {
        _mud_ValueTrack_mud_vec3__set_mode(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "value", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_value(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_ValueTrack_mud_vec3__set_value(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "min", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_min(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_ValueTrack_mud_vec3__set_min(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "max", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_max(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_ValueTrack_mud_vec3__set_max(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_curve(this.__ptr), ValueCurve_mud_vec3);
    },
    set: function(value) {
        _mud_ValueTrack_mud_vec3__set_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "min_curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_min_curve(this.__ptr), ValueCurve_mud_vec3);
    },
    set: function(value) {
        _mud_ValueTrack_mud_vec3__set_min_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "max_curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_max_curve(this.__ptr), ValueCurve_mud_vec3);
    },
    set: function(value) {
        _mud_ValueTrack_mud_vec3__set_max_curve(this.__ptr, value.__ptr);
    }
});
ValueTrack_mud_vec3.prototype["__destroy"] = ValueTrack_mud_vec3.prototype.__destroy = function() {
    _mud_ValueTrack_mud_vec3__destroy(this.__ptr);
};
// ValueTrack<uint32_t>
function ValueTrack_uint32_t(a0, a1, a2, a3) {
    if (a0 === undefined) { this.__ptr = _mud_ValueTrack_uint32_t__construct_0(); this.__type = ValueTrack_uint32_t.__type; getCache(ValueTrack_uint32_t)[this.__ptr] = this; return; }
    this.__ptr = _mud_ValueTrack_uint32_t__construct_4(/*mode*/a0, /*curve*/a1.__ptr, /*min_curve*/a2.__ptr, /*max_curve*/a3.__ptr); this.__type = ValueTrack_uint32_t.__type; getCache(ValueTrack_uint32_t)[this.__ptr] = this;
};
ValueTrack_uint32_t.prototype = Object.create(WrapperObject.prototype);
ValueTrack_uint32_t.prototype.constructor = ValueTrack_uint32_t;
ValueTrack_uint32_t.prototype.__class = ValueTrack_uint32_t;
ValueTrack_uint32_t.__cache = {};
Module['ValueTrack_uint32_t'] = ValueTrack_uint32_t;
Object.defineProperty(ValueTrack_uint32_t.prototype, "mode", {
    get: function() {
        return _mud_ValueTrack_uint32_t__get_mode(this.__ptr);
    },
    set: function(value) {
        _mud_ValueTrack_uint32_t__set_mode(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "value", {
    get: function() {
        return _mud_ValueTrack_uint32_t__get_value(this.__ptr);
    },
    set: function(value) {
        _mud_ValueTrack_uint32_t__set_value(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "min", {
    get: function() {
        return _mud_ValueTrack_uint32_t__get_min(this.__ptr);
    },
    set: function(value) {
        _mud_ValueTrack_uint32_t__set_min(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "max", {
    get: function() {
        return _mud_ValueTrack_uint32_t__get_max(this.__ptr);
    },
    set: function(value) {
        _mud_ValueTrack_uint32_t__set_max(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_uint32_t__get_curve(this.__ptr), ValueCurve_uint32_t);
    },
    set: function(value) {
        _mud_ValueTrack_uint32_t__set_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "min_curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_uint32_t__get_min_curve(this.__ptr), ValueCurve_uint32_t);
    },
    set: function(value) {
        _mud_ValueTrack_uint32_t__set_min_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "max_curve", {
    get: function() {
        return wrapPointer(_mud_ValueTrack_uint32_t__get_max_curve(this.__ptr), ValueCurve_uint32_t);
    },
    set: function(value) {
        _mud_ValueTrack_uint32_t__set_max_curve(this.__ptr, value.__ptr);
    }
});
ValueTrack_uint32_t.prototype["__destroy"] = ValueTrack_uint32_t.prototype.__destroy = function() {
    _mud_ValueTrack_uint32_t__destroy(this.__ptr);
};
// mat3
function mat3(a0, a1, a2, a3, a4, a5, a6, a7, a8) {
    if (a0 === undefined) { this.__ptr = _mud_mat3__construct_0(); this.__type = mat3.__type; getCache(mat3)[this.__ptr] = this; return; }
    if (a3 === undefined) { this.__ptr = _mud_mat3__construct_3(/*x*/a0.__ptr, /*y*/a1.__ptr, /*z*/a2.__ptr); this.__type = mat3.__type; getCache(mat3)[this.__ptr] = this; return; }
    this.__ptr = _mud_mat3__construct_9(/*f0*/a0, /*f1*/a1, /*f2*/a2, /*f3*/a3, /*f4*/a4, /*f5*/a5, /*f6*/a6, /*f7*/a7, /*f8*/a8); this.__type = mat3.__type; getCache(mat3)[this.__ptr] = this;
};
mat3.prototype = Object.create(WrapperObject.prototype);
mat3.prototype.constructor = mat3;
mat3.prototype.__class = mat3;
mat3.__cache = {};
Module['mat3'] = mat3;
Object.defineProperty(mat3.prototype, "f", {
    get: function() {
        return _mud_mat3__get_f(this.__ptr);
    },
    set: function(value) {
        _mud_mat3__set_f(this.__ptr, ensureFloat32(value));
    }
});
mat3.prototype["__destroy"] = mat3.prototype.__destroy = function() {
    _mud_mat3__destroy(this.__ptr);
};
// mat4
function mat4(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) {
    if (a0 === undefined) { this.__ptr = _mud_mat4__construct_0(); this.__type = mat4.__type; getCache(mat4)[this.__ptr] = this; return; }
    if (a4 === undefined) { this.__ptr = _mud_mat4__construct_4(/*x*/a0.__ptr, /*y*/a1.__ptr, /*z*/a2.__ptr, /*w*/a3.__ptr); this.__type = mat4.__type; getCache(mat4)[this.__ptr] = this; return; }
    this.__ptr = _mud_mat4__construct_16(/*f0*/a0, /*f1*/a1, /*f2*/a2, /*f3*/a3, /*f4*/a4, /*f5*/a5, /*f6*/a6, /*f7*/a7, /*f8*/a8, /*f9*/a9, /*f10*/a10, /*f11*/a11, /*f12*/a12, /*f13*/a13, /*f14*/a14, /*f15*/a15); this.__type = mat4.__type; getCache(mat4)[this.__ptr] = this;
};
mat4.prototype = Object.create(WrapperObject.prototype);
mat4.prototype.constructor = mat4;
mat4.prototype.__class = mat4;
mat4.__cache = {};
Module['mat4'] = mat4;
Object.defineProperty(mat4.prototype, "f", {
    get: function() {
        return _mud_mat4__get_f(this.__ptr);
    },
    set: function(value) {
        _mud_mat4__set_f(this.__ptr, ensureFloat32(value));
    }
});
mat4.prototype["__destroy"] = mat4.prototype.__destroy = function() {
    _mud_mat4__destroy(this.__ptr);
};
// v2<bool>
function v2_bool(a0, a1) {
    if (a0 === undefined) { this.__ptr = _mud_v2_bool__construct_0(); this.__type = v2_bool.__type; getCache(v2_bool)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_v2_bool__construct_1(/*v*/a0); this.__type = v2_bool.__type; getCache(v2_bool)[this.__ptr] = this; return; }
    this.__ptr = _mud_v2_bool__construct_2(/*x*/a0, /*y*/a1); this.__type = v2_bool.__type; getCache(v2_bool)[this.__ptr] = this;
};
v2_bool.prototype = Object.create(WrapperObject.prototype);
v2_bool.prototype.constructor = v2_bool;
v2_bool.prototype.__class = v2_bool;
v2_bool.__cache = {};
Module['v2_bool'] = v2_bool;
Object.defineProperty(v2_bool.prototype, "x", {
    get: function() {
        return !!(_mud_v2_bool__get_x(this.__ptr));
    },
    set: function(value) {
        _mud_v2_bool__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v2_bool.prototype, "y", {
    get: function() {
        return !!(_mud_v2_bool__get_y(this.__ptr));
    },
    set: function(value) {
        _mud_v2_bool__set_y(this.__ptr, value);
    }
});
v2_bool.prototype["__destroy"] = v2_bool.prototype.__destroy = function() {
    _mud_v2_bool__destroy(this.__ptr);
};
// v2<float>
function v2_float(a0, a1) {
    if (a0 === undefined) { this.__ptr = _mud_v2_float__construct_0(); this.__type = v2_float.__type; getCache(v2_float)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_v2_float__construct_1(/*v*/a0); this.__type = v2_float.__type; getCache(v2_float)[this.__ptr] = this; return; }
    this.__ptr = _mud_v2_float__construct_2(/*x*/a0, /*y*/a1); this.__type = v2_float.__type; getCache(v2_float)[this.__ptr] = this;
};
v2_float.prototype = Object.create(WrapperObject.prototype);
v2_float.prototype.constructor = v2_float;
v2_float.prototype.__class = v2_float;
v2_float.__cache = {};
Module['v2_float'] = v2_float;
Object.defineProperty(v2_float.prototype, "x", {
    get: function() {
        return _mud_v2_float__get_x(this.__ptr);
    },
    set: function(value) {
        _mud_v2_float__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v2_float.prototype, "y", {
    get: function() {
        return _mud_v2_float__get_y(this.__ptr);
    },
    set: function(value) {
        _mud_v2_float__set_y(this.__ptr, value);
    }
});
v2_float.prototype["__destroy"] = v2_float.prototype.__destroy = function() {
    _mud_v2_float__destroy(this.__ptr);
};
// v2<int>
function v2_int(a0, a1) {
    if (a0 === undefined) { this.__ptr = _mud_v2_int__construct_0(); this.__type = v2_int.__type; getCache(v2_int)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_v2_int__construct_1(/*v*/a0); this.__type = v2_int.__type; getCache(v2_int)[this.__ptr] = this; return; }
    this.__ptr = _mud_v2_int__construct_2(/*x*/a0, /*y*/a1); this.__type = v2_int.__type; getCache(v2_int)[this.__ptr] = this;
};
v2_int.prototype = Object.create(WrapperObject.prototype);
v2_int.prototype.constructor = v2_int;
v2_int.prototype.__class = v2_int;
v2_int.__cache = {};
Module['v2_int'] = v2_int;
Object.defineProperty(v2_int.prototype, "x", {
    get: function() {
        return _mud_v2_int__get_x(this.__ptr);
    },
    set: function(value) {
        _mud_v2_int__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v2_int.prototype, "y", {
    get: function() {
        return _mud_v2_int__get_y(this.__ptr);
    },
    set: function(value) {
        _mud_v2_int__set_y(this.__ptr, value);
    }
});
v2_int.prototype["__destroy"] = v2_int.prototype.__destroy = function() {
    _mud_v2_int__destroy(this.__ptr);
};
// v2<uint>
function v2_uint(a0, a1) {
    if (a0 === undefined) { this.__ptr = _mud_v2_uint__construct_0(); this.__type = v2_uint.__type; getCache(v2_uint)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_v2_uint__construct_1(/*v*/a0); this.__type = v2_uint.__type; getCache(v2_uint)[this.__ptr] = this; return; }
    this.__ptr = _mud_v2_uint__construct_2(/*x*/a0, /*y*/a1); this.__type = v2_uint.__type; getCache(v2_uint)[this.__ptr] = this;
};
v2_uint.prototype = Object.create(WrapperObject.prototype);
v2_uint.prototype.constructor = v2_uint;
v2_uint.prototype.__class = v2_uint;
v2_uint.__cache = {};
Module['v2_uint'] = v2_uint;
Object.defineProperty(v2_uint.prototype, "x", {
    get: function() {
        return _mud_v2_uint__get_x(this.__ptr);
    },
    set: function(value) {
        _mud_v2_uint__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v2_uint.prototype, "y", {
    get: function() {
        return _mud_v2_uint__get_y(this.__ptr);
    },
    set: function(value) {
        _mud_v2_uint__set_y(this.__ptr, value);
    }
});
v2_uint.prototype["__destroy"] = v2_uint.prototype.__destroy = function() {
    _mud_v2_uint__destroy(this.__ptr);
};
// v3<bool>
function v3_bool(a0, a1, a2) {
    if (a0 === undefined) { this.__ptr = _mud_v3_bool__construct_0(); this.__type = v3_bool.__type; getCache(v3_bool)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_v3_bool__construct_1(/*v*/a0); this.__type = v3_bool.__type; getCache(v3_bool)[this.__ptr] = this; return; }
    this.__ptr = _mud_v3_bool__construct_3(/*x*/a0, /*y*/a1, /*z*/a2); this.__type = v3_bool.__type; getCache(v3_bool)[this.__ptr] = this;
};
v3_bool.prototype = Object.create(WrapperObject.prototype);
v3_bool.prototype.constructor = v3_bool;
v3_bool.prototype.__class = v3_bool;
v3_bool.__cache = {};
Module['v3_bool'] = v3_bool;
Object.defineProperty(v3_bool.prototype, "x", {
    get: function() {
        return !!(_mud_v3_bool__get_x(this.__ptr));
    },
    set: function(value) {
        _mud_v3_bool__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v3_bool.prototype, "y", {
    get: function() {
        return !!(_mud_v3_bool__get_y(this.__ptr));
    },
    set: function(value) {
        _mud_v3_bool__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v3_bool.prototype, "z", {
    get: function() {
        return !!(_mud_v3_bool__get_z(this.__ptr));
    },
    set: function(value) {
        _mud_v3_bool__set_z(this.__ptr, value);
    }
});
v3_bool.prototype["__destroy"] = v3_bool.prototype.__destroy = function() {
    _mud_v3_bool__destroy(this.__ptr);
};
// v3<float>
function v3_float(a0, a1, a2) {
    if (a0 === undefined) { this.__ptr = _mud_v3_float__construct_0(); this.__type = v3_float.__type; getCache(v3_float)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_v3_float__construct_1(/*v*/a0); this.__type = v3_float.__type; getCache(v3_float)[this.__ptr] = this; return; }
    this.__ptr = _mud_v3_float__construct_3(/*x*/a0, /*y*/a1, /*z*/a2); this.__type = v3_float.__type; getCache(v3_float)[this.__ptr] = this;
};
v3_float.prototype = Object.create(WrapperObject.prototype);
v3_float.prototype.constructor = v3_float;
v3_float.prototype.__class = v3_float;
v3_float.__cache = {};
Module['v3_float'] = v3_float;
Object.defineProperty(v3_float.prototype, "x", {
    get: function() {
        return _mud_v3_float__get_x(this.__ptr);
    },
    set: function(value) {
        _mud_v3_float__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v3_float.prototype, "y", {
    get: function() {
        return _mud_v3_float__get_y(this.__ptr);
    },
    set: function(value) {
        _mud_v3_float__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v3_float.prototype, "z", {
    get: function() {
        return _mud_v3_float__get_z(this.__ptr);
    },
    set: function(value) {
        _mud_v3_float__set_z(this.__ptr, value);
    }
});
v3_float.prototype["__destroy"] = v3_float.prototype.__destroy = function() {
    _mud_v3_float__destroy(this.__ptr);
};
// v3<int>
function v3_int(a0, a1, a2) {
    if (a0 === undefined) { this.__ptr = _mud_v3_int__construct_0(); this.__type = v3_int.__type; getCache(v3_int)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_v3_int__construct_1(/*v*/a0); this.__type = v3_int.__type; getCache(v3_int)[this.__ptr] = this; return; }
    this.__ptr = _mud_v3_int__construct_3(/*x*/a0, /*y*/a1, /*z*/a2); this.__type = v3_int.__type; getCache(v3_int)[this.__ptr] = this;
};
v3_int.prototype = Object.create(WrapperObject.prototype);
v3_int.prototype.constructor = v3_int;
v3_int.prototype.__class = v3_int;
v3_int.__cache = {};
Module['v3_int'] = v3_int;
Object.defineProperty(v3_int.prototype, "x", {
    get: function() {
        return _mud_v3_int__get_x(this.__ptr);
    },
    set: function(value) {
        _mud_v3_int__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v3_int.prototype, "y", {
    get: function() {
        return _mud_v3_int__get_y(this.__ptr);
    },
    set: function(value) {
        _mud_v3_int__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v3_int.prototype, "z", {
    get: function() {
        return _mud_v3_int__get_z(this.__ptr);
    },
    set: function(value) {
        _mud_v3_int__set_z(this.__ptr, value);
    }
});
v3_int.prototype["__destroy"] = v3_int.prototype.__destroy = function() {
    _mud_v3_int__destroy(this.__ptr);
};
// v3<uint>
function v3_uint(a0, a1, a2) {
    if (a0 === undefined) { this.__ptr = _mud_v3_uint__construct_0(); this.__type = v3_uint.__type; getCache(v3_uint)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_v3_uint__construct_1(/*v*/a0); this.__type = v3_uint.__type; getCache(v3_uint)[this.__ptr] = this; return; }
    this.__ptr = _mud_v3_uint__construct_3(/*x*/a0, /*y*/a1, /*z*/a2); this.__type = v3_uint.__type; getCache(v3_uint)[this.__ptr] = this;
};
v3_uint.prototype = Object.create(WrapperObject.prototype);
v3_uint.prototype.constructor = v3_uint;
v3_uint.prototype.__class = v3_uint;
v3_uint.__cache = {};
Module['v3_uint'] = v3_uint;
Object.defineProperty(v3_uint.prototype, "x", {
    get: function() {
        return _mud_v3_uint__get_x(this.__ptr);
    },
    set: function(value) {
        _mud_v3_uint__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v3_uint.prototype, "y", {
    get: function() {
        return _mud_v3_uint__get_y(this.__ptr);
    },
    set: function(value) {
        _mud_v3_uint__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v3_uint.prototype, "z", {
    get: function() {
        return _mud_v3_uint__get_z(this.__ptr);
    },
    set: function(value) {
        _mud_v3_uint__set_z(this.__ptr, value);
    }
});
v3_uint.prototype["__destroy"] = v3_uint.prototype.__destroy = function() {
    _mud_v3_uint__destroy(this.__ptr);
};
// v4<bool>
function v4_bool(a0, a1, a2, a3) {
    if (a0 === undefined) { this.__ptr = _mud_v4_bool__construct_0(); this.__type = v4_bool.__type; getCache(v4_bool)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_v4_bool__construct_1(/*v*/a0); this.__type = v4_bool.__type; getCache(v4_bool)[this.__ptr] = this; return; }
    this.__ptr = _mud_v4_bool__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); this.__type = v4_bool.__type; getCache(v4_bool)[this.__ptr] = this;
};
v4_bool.prototype = Object.create(WrapperObject.prototype);
v4_bool.prototype.constructor = v4_bool;
v4_bool.prototype.__class = v4_bool;
v4_bool.__cache = {};
Module['v4_bool'] = v4_bool;
Object.defineProperty(v4_bool.prototype, "x", {
    get: function() {
        return !!(_mud_v4_bool__get_x(this.__ptr));
    },
    set: function(value) {
        _mud_v4_bool__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v4_bool.prototype, "y", {
    get: function() {
        return !!(_mud_v4_bool__get_y(this.__ptr));
    },
    set: function(value) {
        _mud_v4_bool__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v4_bool.prototype, "z", {
    get: function() {
        return !!(_mud_v4_bool__get_z(this.__ptr));
    },
    set: function(value) {
        _mud_v4_bool__set_z(this.__ptr, value);
    }
});
Object.defineProperty(v4_bool.prototype, "w", {
    get: function() {
        return !!(_mud_v4_bool__get_w(this.__ptr));
    },
    set: function(value) {
        _mud_v4_bool__set_w(this.__ptr, value);
    }
});
v4_bool.prototype["__destroy"] = v4_bool.prototype.__destroy = function() {
    _mud_v4_bool__destroy(this.__ptr);
};
// v4<float>
function v4_float(a0, a1, a2, a3) {
    if (a0 === undefined) { this.__ptr = _mud_v4_float__construct_0(); this.__type = v4_float.__type; getCache(v4_float)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_v4_float__construct_1(/*v*/a0); this.__type = v4_float.__type; getCache(v4_float)[this.__ptr] = this; return; }
    this.__ptr = _mud_v4_float__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); this.__type = v4_float.__type; getCache(v4_float)[this.__ptr] = this;
};
v4_float.prototype = Object.create(WrapperObject.prototype);
v4_float.prototype.constructor = v4_float;
v4_float.prototype.__class = v4_float;
v4_float.__cache = {};
Module['v4_float'] = v4_float;
Object.defineProperty(v4_float.prototype, "x", {
    get: function() {
        return _mud_v4_float__get_x(this.__ptr);
    },
    set: function(value) {
        _mud_v4_float__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v4_float.prototype, "y", {
    get: function() {
        return _mud_v4_float__get_y(this.__ptr);
    },
    set: function(value) {
        _mud_v4_float__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v4_float.prototype, "z", {
    get: function() {
        return _mud_v4_float__get_z(this.__ptr);
    },
    set: function(value) {
        _mud_v4_float__set_z(this.__ptr, value);
    }
});
Object.defineProperty(v4_float.prototype, "w", {
    get: function() {
        return _mud_v4_float__get_w(this.__ptr);
    },
    set: function(value) {
        _mud_v4_float__set_w(this.__ptr, value);
    }
});
v4_float.prototype["__destroy"] = v4_float.prototype.__destroy = function() {
    _mud_v4_float__destroy(this.__ptr);
};
// v4<int>
function v4_int(a0, a1, a2, a3) {
    if (a0 === undefined) { this.__ptr = _mud_v4_int__construct_0(); this.__type = v4_int.__type; getCache(v4_int)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_v4_int__construct_1(/*v*/a0); this.__type = v4_int.__type; getCache(v4_int)[this.__ptr] = this; return; }
    this.__ptr = _mud_v4_int__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); this.__type = v4_int.__type; getCache(v4_int)[this.__ptr] = this;
};
v4_int.prototype = Object.create(WrapperObject.prototype);
v4_int.prototype.constructor = v4_int;
v4_int.prototype.__class = v4_int;
v4_int.__cache = {};
Module['v4_int'] = v4_int;
Object.defineProperty(v4_int.prototype, "x", {
    get: function() {
        return _mud_v4_int__get_x(this.__ptr);
    },
    set: function(value) {
        _mud_v4_int__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v4_int.prototype, "y", {
    get: function() {
        return _mud_v4_int__get_y(this.__ptr);
    },
    set: function(value) {
        _mud_v4_int__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v4_int.prototype, "z", {
    get: function() {
        return _mud_v4_int__get_z(this.__ptr);
    },
    set: function(value) {
        _mud_v4_int__set_z(this.__ptr, value);
    }
});
Object.defineProperty(v4_int.prototype, "w", {
    get: function() {
        return _mud_v4_int__get_w(this.__ptr);
    },
    set: function(value) {
        _mud_v4_int__set_w(this.__ptr, value);
    }
});
v4_int.prototype["__destroy"] = v4_int.prototype.__destroy = function() {
    _mud_v4_int__destroy(this.__ptr);
};
// v4<uint>
function v4_uint(a0, a1, a2, a3) {
    if (a0 === undefined) { this.__ptr = _mud_v4_uint__construct_0(); this.__type = v4_uint.__type; getCache(v4_uint)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_v4_uint__construct_1(/*v*/a0); this.__type = v4_uint.__type; getCache(v4_uint)[this.__ptr] = this; return; }
    this.__ptr = _mud_v4_uint__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); this.__type = v4_uint.__type; getCache(v4_uint)[this.__ptr] = this;
};
v4_uint.prototype = Object.create(WrapperObject.prototype);
v4_uint.prototype.constructor = v4_uint;
v4_uint.prototype.__class = v4_uint;
v4_uint.__cache = {};
Module['v4_uint'] = v4_uint;
Object.defineProperty(v4_uint.prototype, "x", {
    get: function() {
        return _mud_v4_uint__get_x(this.__ptr);
    },
    set: function(value) {
        _mud_v4_uint__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v4_uint.prototype, "y", {
    get: function() {
        return _mud_v4_uint__get_y(this.__ptr);
    },
    set: function(value) {
        _mud_v4_uint__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v4_uint.prototype, "z", {
    get: function() {
        return _mud_v4_uint__get_z(this.__ptr);
    },
    set: function(value) {
        _mud_v4_uint__set_z(this.__ptr, value);
    }
});
Object.defineProperty(v4_uint.prototype, "w", {
    get: function() {
        return _mud_v4_uint__get_w(this.__ptr);
    },
    set: function(value) {
        _mud_v4_uint__set_w(this.__ptr, value);
    }
});
v4_uint.prototype["__destroy"] = v4_uint.prototype.__destroy = function() {
    _mud_v4_uint__destroy(this.__ptr);
};
// Sprite
function Sprite() { throw "cannot construct a Sprite, no constructor in IDL" }
Sprite.prototype = Object.create(Image.prototype);
Sprite.prototype.constructor = Sprite;
Sprite.prototype.__class = Sprite;
Sprite.__cache = {};
Module['Sprite'] = Sprite;
Sprite.prototype["__destroy"] = Sprite.prototype.__destroy = function() {
    _mud_Sprite__destroy(this.__ptr);
};
// SpriteAtlas
function SpriteAtlas() { throw "cannot construct a SpriteAtlas, no constructor in IDL" }
SpriteAtlas.prototype = Object.create(ImageAtlas.prototype);
SpriteAtlas.prototype.constructor = SpriteAtlas;
SpriteAtlas.prototype.__class = SpriteAtlas;
SpriteAtlas.__cache = {};
Module['SpriteAtlas'] = SpriteAtlas;
SpriteAtlas.prototype["__destroy"] = SpriteAtlas.prototype.__destroy = function() {
    _mud_SpriteAtlas__destroy(this.__ptr);
};
// TextureAtlas
function TextureAtlas() { throw "cannot construct a TextureAtlas, no constructor in IDL" }
TextureAtlas.prototype = Object.create(ImageAtlas.prototype);
TextureAtlas.prototype.constructor = TextureAtlas;
TextureAtlas.prototype.__class = TextureAtlas;
TextureAtlas.__cache = {};
Module['TextureAtlas'] = TextureAtlas;
TextureAtlas.prototype["__destroy"] = TextureAtlas.prototype.__destroy = function() {
    _mud_TextureAtlas__destroy(this.__ptr);
};
// quat
function quat(a0, a1, a2, a3) {
    if (a0 === undefined) { this.__ptr = _mud_quat__construct_0(); this.__type = quat.__type; getCache(quat)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_quat__construct_1(/*euler_angles*/a0.__ptr); this.__type = quat.__type; getCache(quat)[this.__ptr] = this; return; }
    this.__ptr = _mud_quat__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); this.__type = quat.__type; getCache(quat)[this.__ptr] = this;
};
quat.prototype = Object.create(v4_float.prototype);
quat.prototype.constructor = quat;
quat.prototype.__class = quat;
quat.__cache = {};
Module['quat'] = quat;
quat.prototype["__destroy"] = quat.prototype.__destroy = function() {
    _mud_quat__destroy(this.__ptr);
};
Module['rgb'] = function(a0) {
    return wrapPointer(_mud_rgb_1(/*colour*/a0), Colour);
};
Module['rgba'] = function(a0) {
    return wrapPointer(_mud_rgba_1(/*colour*/a0), Colour);
};
Module['abgr'] = function(a0) {
    return wrapPointer(_mud_abgr_1(/*colour*/a0), Colour);
};
Module['hsl'] = function(a0, a1, a2) {
    return wrapPointer(_mud_hsl_3(/*h*/a0, /*s*/a1, /*l*/a2), Colour);
};
Module['to_rgba'] = function(a0) {
    return _mud_to_rgba_1(/*colour*/a0.__ptr);
};
Module['to_abgr'] = function(a0) {
    return _mud_to_abgr_1(/*colour*/a0.__ptr);
};
Module['to_linear'] = function(a0) {
    return wrapPointer(_mud_to_linear_1(/*colour*/a0.__ptr), Colour);
};
Module['to_gamma'] = function(a0) {
    return wrapPointer(_mud_to_gamma_1(/*colour*/a0.__ptr), Colour);
};
Module['to_srgb'] = function(a0) {
    return wrapPointer(_mud_to_srgb_1(/*colour*/a0.__ptr), Colour);
};
Module['to_hsl'] = function(a0, a1, a2) {
    if (a1 === undefined) { return wrapPointer(_mud_to_hsl_1(/*colour*/a0.__ptr), ColourHSL); }
    return wrapPointer(_mud_to_hsl_3(/*r*/a0, /*g*/a1, /*b*/a2), ColourHSL);
};
Module['to_hsla'] = function(a0) {
    return wrapPointer(_mud_to_hsla_1(/*colour*/a0.__ptr), ColourHSL);
};
Module['sinf'] = function(a0) {
    return _sinf_1(/*a*/a0);
};
Module['cosf'] = function(a0) {
    return _cosf_1(/*a*/a0);
};
Module['sin'] = function(a0) {
    return _sin_1(/*a*/a0);
};
Module['cos'] = function(a0) {
    return _cos_1(/*a*/a0);
};
Module['add'] = function(a0, a1) {
    return _mud_add_2(/*a*/a0, /*b*/a1);
};
Module['subtract'] = function(a0, a1) {
    return _mud_subtract_2(/*a*/a0, /*b*/a1);
};
Module['multiply'] = function(a0, a1) {
    return _mud_multiply_2(/*a*/a0, /*b*/a1);
};
Module['divide'] = function(a0, a1) {
    return _mud_divide_2(/*a*/a0, /*b*/a1);
};
Module['nsinf'] = function(a0) {
    return _mud_nsinf_1(/*a*/a0);
};
Module['ncosf'] = function(a0) {
    return _mud_ncosf_1(/*a*/a0);
};
Module['nsin'] = function(a0) {
    return _mud_nsin_1(/*a*/a0);
};
Module['ncos'] = function(a0) {
    return _mud_ncos_1(/*a*/a0);
};
Module['look_dir'] = function(a0, a1) {
    if (a1 === undefined) { return wrapPointer(_mud_look_dir_1(/*direction*/a0.__ptr), quat); }
    return wrapPointer(_mud_look_dir_2(/*direction*/a0.__ptr, /*forward*/a1.__ptr), quat);
};
Module['look_at'] = function(a0, a1, a2) {
    if (a2 === undefined) { return wrapPointer(_mud_look_at_2(/*eye*/a0.__ptr, /*target*/a1.__ptr), quat); }
    return wrapPointer(_mud_look_at_3(/*eye*/a0.__ptr, /*target*/a1.__ptr, /*forward*/a2.__ptr), quat);
};
Module['grid_center'] = function(a0, a1) {
    return wrapPointer(_mud_grid_center_2(/*coord*/a0.__ptr, /*cell_size*/a1.__ptr), v3_float);
};
Module['float2'] = v2_float;
Module['float3'] = v3_float;
Module['float4'] = v4_float;
Module['int2'] = v2_int;
Module['int3'] = v3_int;
Module['int4'] = v4_int;
Module['uint2'] = v2_uint;
Module['uint3'] = v3_uint;
Module['uint4'] = v4_uint;
Module['bool2'] = v2_bool;
Module['bool3'] = v3_bool;
Module['bool4'] = v4_bool;
Module['vec2'] = v2_float;
Module['vec3'] = v3_float;
Module['vec4'] = v4_float;
Module['uvec2'] = v2_uint;
Module['uvec3'] = v3_uint;
Module['uvec4'] = v4_uint;
Module['ivec2'] = v2_int;
Module['ivec3'] = v3_int;
Module['ivec4'] = v4_int;
Module['bvec3'] = v3_bool;
Module['bvec4'] = v4_bool;

(function() {
    function setup() {
        Colour.__type = _mud_Colour__type();
        ColourHSL.__type = _mud_ColourHSL__type();
        Image.__type = _mud_Image__type();
        Image256.__type = _mud_Image256__type();
        ImageAtlas.__type = _mud_ImageAtlas__type();
        Palette.__type = _mud_Palette__type();
        Time.__type = _mud_Time__type();
        TimeSpan.__type = _mud_TimeSpan__type();
        Transform.__type = _mud_Transform__type();
        mat3.__type = _mud_mat3__type();
        mat4.__type = _mud_mat4__type();
        Sprite.__type = _mud_Sprite__type();
        SpriteAtlas.__type = _mud_SpriteAtlas__type();
        TextureAtlas.__type = _mud_TextureAtlas__type();
        quat.__type = _mud_quat__type();
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
        Module['Axis']['None'] = _mud_Axis_None();
        Module['Axis']['Count'] = _mud_Axis_Count();
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
        Module['Side']['Count'] = _mud_Side_Count();
        // SignedAxis
        Module['SignedAxis'] = Module['SignedAxis'] || {};
        Module['SignedAxis']['PlusX'] = _mud_SignedAxis_PlusX();
        Module['SignedAxis']['MinusX'] = _mud_SignedAxis_MinusX();
        Module['SignedAxis']['PlusY'] = _mud_SignedAxis_PlusY();
        Module['SignedAxis']['MinusY'] = _mud_SignedAxis_MinusY();
        Module['SignedAxis']['PlusZ'] = _mud_SignedAxis_PlusZ();
        Module['SignedAxis']['MinusZ'] = _mud_SignedAxis_MinusZ();
        Module['SignedAxis']['Count'] = _mud_SignedAxis_Count();
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
