Module['stl'] = Module['stl'] || {};
// AutoStat<float>
function AutoStat_float() {
    this.ptr = _mud_AutoStat_float__construct_0(); this.type = AutoStat_float; getCache(AutoStat_float)[this.ptr] = this;
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
        _mud_AutoStat_float__set_value(self, value);
    }
});
AutoStat_float.prototype["__destroy__"] = AutoStat_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AutoStat_float__destroy(self);
};
// AutoStat<int>
function AutoStat_int() {
    this.ptr = _mud_AutoStat_int__construct_0(); this.type = AutoStat_int; getCache(AutoStat_int)[this.ptr] = this;
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
        _mud_AutoStat_int__set_value(self, value);
    }
});
AutoStat_int.prototype["__destroy__"] = AutoStat_int.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AutoStat_int__destroy(self);
};
// Colour
function Colour(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_Colour__construct_0(); this.type = Colour; getCache(Colour)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_Colour__construct_1(/*v*/a0); this.type = Colour; getCache(Colour)[this.ptr] = this; return; }
    if (a2 === undefined) { this.ptr = _mud_Colour__construct_2(/*v*/a0, /*a*/a1); this.type = Colour; getCache(Colour)[this.ptr] = this; return; }
    if (a3 === undefined) { this.ptr = _mud_Colour__construct_3(/*r*/a0, /*g*/a1, /*b*/a2); this.type = Colour; getCache(Colour)[this.ptr] = this; return; }
    this.ptr = _mud_Colour__construct_4(/*r*/a0, /*g*/a1, /*b*/a2, /*a*/a3); this.type = Colour; getCache(Colour)[this.ptr] = this;
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
        _mud_Colour__set_a(self, value);
    }
});
Colour.prototype["__destroy__"] = Colour.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Colour__destroy(self);
};
// ColourHSL
function ColourHSL() {
    this.ptr = _mud_ColourHSL__construct_0(); this.type = ColourHSL; getCache(ColourHSL)[this.ptr] = this;
};
ColourHSL.prototype = Object.create(WrapperObject.prototype);
ColourHSL.prototype.constructor = ColourHSL;
ColourHSL.prototype.__class__ = ColourHSL;
ColourHSL.__cache__ = {};
Module['ColourHSL'] = ColourHSL;
Object.defineProperty(ColourHSL.prototype, "h", {
    get: function() {
        var self = this.ptr;
        return _mud_ColourHSL__get_h(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ColourHSL__set_h(self, value);
    }
});
Object.defineProperty(ColourHSL.prototype, "s", {
    get: function() {
        var self = this.ptr;
        return _mud_ColourHSL__get_s(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ColourHSL__set_s(self, value);
    }
});
Object.defineProperty(ColourHSL.prototype, "l", {
    get: function() {
        var self = this.ptr;
        return _mud_ColourHSL__get_l(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ColourHSL__set_l(self, value);
    }
});
Object.defineProperty(ColourHSL.prototype, "a", {
    get: function() {
        var self = this.ptr;
        return _mud_ColourHSL__get_a(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ColourHSL__set_a(self, value);
    }
});
ColourHSL.prototype["__destroy__"] = ColourHSL.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ColourHSL__destroy(self);
};
// Image
function Image() {
    this.ptr = _mud_Image__construct_0(); this.type = Image; getCache(Image)[this.ptr] = this;
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
        _mud_Image__set_d_name(self, ensureString(value));
    }
});
Object.defineProperty(Image.prototype, "d_path", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Image__get_d_path(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Image__set_d_path(self, ensureString(value));
    }
});
Image.prototype["__destroy__"] = Image.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Image__destroy(self);
};
// Image256
function Image256(a0, a1, a2) {
    if (a0 === undefined) { this.ptr = _mud_Image256__construct_0(); this.type = Image256; getCache(Image256)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_Image256__construct_1(/*width*/a0); this.type = Image256; getCache(Image256)[this.ptr] = this; return; }
    if (a2 === undefined) { this.ptr = _mud_Image256__construct_2(/*width*/a0, /*height*/a1); this.type = Image256; getCache(Image256)[this.ptr] = this; return; }
    this.ptr = _mud_Image256__construct_3(/*width*/a0, /*height*/a1, /*palette*/a2.ptr); this.type = Image256; getCache(Image256)[this.ptr] = this;
};
Image256.prototype = Object.create(WrapperObject.prototype);
Image256.prototype.constructor = Image256;
Image256.prototype.__class__ = Image256;
Image256.__cache__ = {};
Module['Image256'] = Image256;
Object.defineProperty(Image256.prototype, "pixels", {
    get: function() {
        var self = this.ptr;
        return _mud_Image256__get_pixels(self);
    }});
Object.defineProperty(Image256.prototype, "width", {
    get: function() {
        var self = this.ptr;
        return _mud_Image256__get_width(self);
    },
    set: function(value) {
        var self = this.ptr;
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
        _mud_Image256__set_palette(self, value.ptr);
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
function Palette(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_Palette__construct_0(); this.type = Palette; getCache(Palette)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_Palette__construct_1(/*colours*/a0.ptr); this.type = Palette; getCache(Palette)[this.ptr] = this; return; }
    this.ptr = _mud_Palette__construct_2(/*spectrum*/a0, /*steps*/a1); this.type = Palette; getCache(Palette)[this.ptr] = this;
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
    this.ptr = _mud_Range_float__construct_0(); this.type = Range_float; getCache(Range_float)[this.ptr] = this;
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
        _mud_Range_float__set_max(self, value);
    }
});
Range_float.prototype["__destroy__"] = Range_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Range_float__destroy(self);
};
// Range<mud::Colour>
function Range_mud_Colour() {
    this.ptr = _mud_Range_mud_Colour__construct_0(); this.type = Range_mud_Colour; getCache(Range_mud_Colour)[this.ptr] = this;
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
        _mud_Range_mud_Colour__set_min(self, value.ptr);
    }
});
Object.defineProperty(Range_mud_Colour.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Range_mud_Colour__get_max(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Range_mud_Colour__set_max(self, value.ptr);
    }
});
Range_mud_Colour.prototype["__destroy__"] = Range_mud_Colour.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Range_mud_Colour__destroy(self);
};
// Range<mud::quat>
function Range_mud_quat() {
    this.ptr = _mud_Range_mud_quat__construct_0(); this.type = Range_mud_quat; getCache(Range_mud_quat)[this.ptr] = this;
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
        _mud_Range_mud_quat__set_min(self, value.ptr);
    }
});
Object.defineProperty(Range_mud_quat.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Range_mud_quat__get_max(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Range_mud_quat__set_max(self, value.ptr);
    }
});
Range_mud_quat.prototype["__destroy__"] = Range_mud_quat.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Range_mud_quat__destroy(self);
};
// Range<mud::vec3>
function Range_mud_vec3() {
    this.ptr = _mud_Range_mud_vec3__construct_0(); this.type = Range_mud_vec3; getCache(Range_mud_vec3)[this.ptr] = this;
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
        _mud_Range_mud_vec3__set_min(self, value.ptr);
    }
});
Object.defineProperty(Range_mud_vec3.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Range_mud_vec3__get_max(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Range_mud_vec3__set_max(self, value.ptr);
    }
});
Range_mud_vec3.prototype["__destroy__"] = Range_mud_vec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Range_mud_vec3__destroy(self);
};
// Range<uint32_t>
function Range_uint32_t() {
    this.ptr = _mud_Range_uint32_t__construct_0(); this.type = Range_uint32_t; getCache(Range_uint32_t)[this.ptr] = this;
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
        _mud_Range_uint32_t__set_max(self, value);
    }
});
Range_uint32_t.prototype["__destroy__"] = Range_uint32_t.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Range_uint32_t__destroy(self);
};
// Time
function Time(a0) {
    this.ptr = _mud_Time__construct_1(/*value*/a0); this.type = Time; getCache(Time)[this.ptr] = this;
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
        _mud_Time__set_value(self, value);
    }
});
Time.prototype["__destroy__"] = Time.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Time__destroy(self);
};
// TimeSpan
function TimeSpan(a0, a1) {
    this.ptr = _mud_TimeSpan__construct_2(/*s*/a0.ptr, /*e*/a1.ptr); this.type = TimeSpan; getCache(TimeSpan)[this.ptr] = this;
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
        _mud_TimeSpan__set_start(self, value.ptr);
    }
});
Object.defineProperty(TimeSpan.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_TimeSpan__get_end(self), Time);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_TimeSpan__set_end(self, value.ptr);
    }
});
TimeSpan.prototype["__destroy__"] = TimeSpan.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TimeSpan__destroy(self);
};
// Transform
function Transform() {
    this.ptr = _mud_Transform__construct_0(); this.type = Transform; getCache(Transform)[this.ptr] = this;
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
        _mud_Transform__set_position(self, value.ptr);
    }
});
Object.defineProperty(Transform.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Transform__get_rotation(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Transform__set_rotation(self, value.ptr);
    }
});
Object.defineProperty(Transform.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Transform__get_scale(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Transform__set_scale(self, value.ptr);
    }
});
Transform.prototype["__destroy__"] = Transform.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Transform__destroy(self);
};
// ValueCurve<float>
function ValueCurve_float(a0) {
    if (a0 === undefined) { this.ptr = _mud_ValueCurve_float__construct_0(); this.type = ValueCurve_float; getCache(ValueCurve_float)[this.ptr] = this; return; }
    this.ptr = _mud_ValueCurve_float__construct_1(/*keys*/a0.ptr); this.type = ValueCurve_float; getCache(ValueCurve_float)[this.ptr] = this;
};
ValueCurve_float.prototype = Object.create(WrapperObject.prototype);
ValueCurve_float.prototype.constructor = ValueCurve_float;
ValueCurve_float.prototype.__class__ = ValueCurve_float;
ValueCurve_float.__cache__ = {};
Module['ValueCurve_float'] = ValueCurve_float;
Object.defineProperty(ValueCurve_float.prototype, "keys", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueCurve_float__get_keys(self);
    }});
ValueCurve_float.prototype["__destroy__"] = ValueCurve_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueCurve_float__destroy(self);
};
// ValueCurve<mud::Colour>
function ValueCurve_mud_Colour(a0) {
    if (a0 === undefined) { this.ptr = _mud_ValueCurve_mud_Colour__construct_0(); this.type = ValueCurve_mud_Colour; getCache(ValueCurve_mud_Colour)[this.ptr] = this; return; }
    this.ptr = _mud_ValueCurve_mud_Colour__construct_1(/*keys*/a0.ptr); this.type = ValueCurve_mud_Colour; getCache(ValueCurve_mud_Colour)[this.ptr] = this;
};
ValueCurve_mud_Colour.prototype = Object.create(WrapperObject.prototype);
ValueCurve_mud_Colour.prototype.constructor = ValueCurve_mud_Colour;
ValueCurve_mud_Colour.prototype.__class__ = ValueCurve_mud_Colour;
ValueCurve_mud_Colour.__cache__ = {};
Module['ValueCurve_mud_Colour'] = ValueCurve_mud_Colour;
Object.defineProperty(ValueCurve_mud_Colour.prototype, "keys", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueCurve_mud_Colour__get_keys(self);
    }});
ValueCurve_mud_Colour.prototype["__destroy__"] = ValueCurve_mud_Colour.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueCurve_mud_Colour__destroy(self);
};
// ValueCurve<mud::quat>
function ValueCurve_mud_quat() {
    this.ptr = _mud_ValueCurve_mud_quat__construct_0(); this.type = ValueCurve_mud_quat; getCache(ValueCurve_mud_quat)[this.ptr] = this;
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
function ValueCurve_mud_vec3(a0) {
    if (a0 === undefined) { this.ptr = _mud_ValueCurve_mud_vec3__construct_0(); this.type = ValueCurve_mud_vec3; getCache(ValueCurve_mud_vec3)[this.ptr] = this; return; }
    this.ptr = _mud_ValueCurve_mud_vec3__construct_1(/*keys*/a0.ptr); this.type = ValueCurve_mud_vec3; getCache(ValueCurve_mud_vec3)[this.ptr] = this;
};
ValueCurve_mud_vec3.prototype = Object.create(WrapperObject.prototype);
ValueCurve_mud_vec3.prototype.constructor = ValueCurve_mud_vec3;
ValueCurve_mud_vec3.prototype.__class__ = ValueCurve_mud_vec3;
ValueCurve_mud_vec3.__cache__ = {};
Module['ValueCurve_mud_vec3'] = ValueCurve_mud_vec3;
Object.defineProperty(ValueCurve_mud_vec3.prototype, "keys", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueCurve_mud_vec3__get_keys(self);
    }});
ValueCurve_mud_vec3.prototype["__destroy__"] = ValueCurve_mud_vec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueCurve_mud_vec3__destroy(self);
};
// ValueCurve<uint32_t>
function ValueCurve_uint32_t(a0) {
    if (a0 === undefined) { this.ptr = _mud_ValueCurve_uint32_t__construct_0(); this.type = ValueCurve_uint32_t; getCache(ValueCurve_uint32_t)[this.ptr] = this; return; }
    this.ptr = _mud_ValueCurve_uint32_t__construct_1(/*keys*/a0.ptr); this.type = ValueCurve_uint32_t; getCache(ValueCurve_uint32_t)[this.ptr] = this;
};
ValueCurve_uint32_t.prototype = Object.create(WrapperObject.prototype);
ValueCurve_uint32_t.prototype.constructor = ValueCurve_uint32_t;
ValueCurve_uint32_t.prototype.__class__ = ValueCurve_uint32_t;
ValueCurve_uint32_t.__cache__ = {};
Module['ValueCurve_uint32_t'] = ValueCurve_uint32_t;
Object.defineProperty(ValueCurve_uint32_t.prototype, "keys", {
    get: function() {
        var self = this.ptr;
        return _mud_ValueCurve_uint32_t__get_keys(self);
    }});
ValueCurve_uint32_t.prototype["__destroy__"] = ValueCurve_uint32_t.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueCurve_uint32_t__destroy(self);
};
// ValueTrack<float>
function ValueTrack_float(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_ValueTrack_float__construct_0(); this.type = ValueTrack_float; getCache(ValueTrack_float)[this.ptr] = this; return; }
    this.ptr = _mud_ValueTrack_float__construct_4(/*mode*/a0, /*curve*/a1.ptr, /*min_curve*/a2.ptr, /*max_curve*/a3.ptr); this.type = ValueTrack_float; getCache(ValueTrack_float)[this.ptr] = this;
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
        _mud_ValueTrack_float__set_curve(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "min_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_float__get_min_curve(self), ValueCurve_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_float__set_min_curve(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "max_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_float__get_max_curve(self), ValueCurve_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_float__set_max_curve(self, value.ptr);
    }
});
ValueTrack_float.prototype["__destroy__"] = ValueTrack_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueTrack_float__destroy(self);
};
// ValueTrack<mud::Colour>
function ValueTrack_mud_Colour(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_ValueTrack_mud_Colour__construct_0(); this.type = ValueTrack_mud_Colour; getCache(ValueTrack_mud_Colour)[this.ptr] = this; return; }
    this.ptr = _mud_ValueTrack_mud_Colour__construct_4(/*mode*/a0, /*curve*/a1.ptr, /*min_curve*/a2.ptr, /*max_curve*/a3.ptr); this.type = ValueTrack_mud_Colour; getCache(ValueTrack_mud_Colour)[this.ptr] = this;
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
        _mud_ValueTrack_mud_Colour__set_value(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_min(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_Colour__set_min(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_max(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_Colour__set_max(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_curve(self), ValueCurve_mud_Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_Colour__set_curve(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "min_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_min_curve(self), ValueCurve_mud_Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_Colour__set_min_curve(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_Colour.prototype, "max_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_Colour__get_max_curve(self), ValueCurve_mud_Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_Colour__set_max_curve(self, value.ptr);
    }
});
ValueTrack_mud_Colour.prototype["__destroy__"] = ValueTrack_mud_Colour.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueTrack_mud_Colour__destroy(self);
};
// ValueTrack<mud::quat>
function ValueTrack_mud_quat(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_ValueTrack_mud_quat__construct_0(); this.type = ValueTrack_mud_quat; getCache(ValueTrack_mud_quat)[this.ptr] = this; return; }
    this.ptr = _mud_ValueTrack_mud_quat__construct_4(/*mode*/a0, /*curve*/a1.ptr, /*min_curve*/a2.ptr, /*max_curve*/a3.ptr); this.type = ValueTrack_mud_quat; getCache(ValueTrack_mud_quat)[this.ptr] = this;
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
        _mud_ValueTrack_mud_quat__set_value(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_quat__get_min(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_quat__set_min(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_quat__get_max(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_quat__set_max(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_quat__get_curve(self), ValueCurve_mud_quat);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_quat__set_curve(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "min_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_quat__get_min_curve(self), ValueCurve_mud_quat);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_quat__set_min_curve(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_quat.prototype, "max_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_quat__get_max_curve(self), ValueCurve_mud_quat);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_quat__set_max_curve(self, value.ptr);
    }
});
ValueTrack_mud_quat.prototype["__destroy__"] = ValueTrack_mud_quat.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueTrack_mud_quat__destroy(self);
};
// ValueTrack<mud::vec3>
function ValueTrack_mud_vec3(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_ValueTrack_mud_vec3__construct_0(); this.type = ValueTrack_mud_vec3; getCache(ValueTrack_mud_vec3)[this.ptr] = this; return; }
    this.ptr = _mud_ValueTrack_mud_vec3__construct_4(/*mode*/a0, /*curve*/a1.ptr, /*min_curve*/a2.ptr, /*max_curve*/a3.ptr); this.type = ValueTrack_mud_vec3; getCache(ValueTrack_mud_vec3)[this.ptr] = this;
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
        _mud_ValueTrack_mud_vec3__set_value(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "min", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_min(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_vec3__set_min(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "max", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_max(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_vec3__set_max(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_curve(self), ValueCurve_mud_vec3);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_vec3__set_curve(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "min_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_min_curve(self), ValueCurve_mud_vec3);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_vec3__set_min_curve(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_mud_vec3.prototype, "max_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_mud_vec3__get_max_curve(self), ValueCurve_mud_vec3);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_mud_vec3__set_max_curve(self, value.ptr);
    }
});
ValueTrack_mud_vec3.prototype["__destroy__"] = ValueTrack_mud_vec3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueTrack_mud_vec3__destroy(self);
};
// ValueTrack<uint32_t>
function ValueTrack_uint32_t(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_ValueTrack_uint32_t__construct_0(); this.type = ValueTrack_uint32_t; getCache(ValueTrack_uint32_t)[this.ptr] = this; return; }
    this.ptr = _mud_ValueTrack_uint32_t__construct_4(/*mode*/a0, /*curve*/a1.ptr, /*min_curve*/a2.ptr, /*max_curve*/a3.ptr); this.type = ValueTrack_uint32_t; getCache(ValueTrack_uint32_t)[this.ptr] = this;
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
        _mud_ValueTrack_uint32_t__set_curve(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "min_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_uint32_t__get_min_curve(self), ValueCurve_uint32_t);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_uint32_t__set_min_curve(self, value.ptr);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "max_curve", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ValueTrack_uint32_t__get_max_curve(self), ValueCurve_uint32_t);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ValueTrack_uint32_t__set_max_curve(self, value.ptr);
    }
});
ValueTrack_uint32_t.prototype["__destroy__"] = ValueTrack_uint32_t.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ValueTrack_uint32_t__destroy(self);
};
// mat3
function mat3(a0, a1, a2, a3, a4, a5, a6, a7, a8) {
    if (a0 === undefined) { this.ptr = _mud_mat3__construct_0(); this.type = mat3; getCache(mat3)[this.ptr] = this; return; }
    if (a3 === undefined) { this.ptr = _mud_mat3__construct_3(/*x*/a0.ptr, /*y*/a1.ptr, /*z*/a2.ptr); this.type = mat3; getCache(mat3)[this.ptr] = this; return; }
    this.ptr = _mud_mat3__construct_9(/*f0*/a0, /*f1*/a1, /*f2*/a2, /*f3*/a3, /*f4*/a4, /*f5*/a5, /*f6*/a6, /*f7*/a7, /*f8*/a8); this.type = mat3; getCache(mat3)[this.ptr] = this;
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
        _mud_mat3__set_f(self, ensureFloat32(value));
    }
});
mat3.prototype["__destroy__"] = mat3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_mat3__destroy(self);
};
// mat4
function mat4(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) {
    if (a0 === undefined) { this.ptr = _mud_mat4__construct_0(); this.type = mat4; getCache(mat4)[this.ptr] = this; return; }
    if (a4 === undefined) { this.ptr = _mud_mat4__construct_4(/*x*/a0.ptr, /*y*/a1.ptr, /*z*/a2.ptr, /*w*/a3.ptr); this.type = mat4; getCache(mat4)[this.ptr] = this; return; }
    this.ptr = _mud_mat4__construct_16(/*f0*/a0, /*f1*/a1, /*f2*/a2, /*f3*/a3, /*f4*/a4, /*f5*/a5, /*f6*/a6, /*f7*/a7, /*f8*/a8, /*f9*/a9, /*f10*/a10, /*f11*/a11, /*f12*/a12, /*f13*/a13, /*f14*/a14, /*f15*/a15); this.type = mat4; getCache(mat4)[this.ptr] = this;
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
        _mud_mat4__set_f(self, ensureFloat32(value));
    }
});
mat4.prototype["__destroy__"] = mat4.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_mat4__destroy(self);
};
// v2<bool>
function v2_bool(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_v2_bool__construct_0(); this.type = v2_bool; getCache(v2_bool)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v2_bool__construct_1(/*v*/a0); this.type = v2_bool; getCache(v2_bool)[this.ptr] = this; return; }
    this.ptr = _mud_v2_bool__construct_2(/*x*/a0, /*y*/a1); this.type = v2_bool; getCache(v2_bool)[this.ptr] = this;
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
        _mud_v2_bool__set_y(self, value);
    }
});
v2_bool.prototype["__destroy__"] = v2_bool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v2_bool__destroy(self);
};
// v2<float>
function v2_float(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_v2_float__construct_0(); this.type = v2_float; getCache(v2_float)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v2_float__construct_1(/*v*/a0); this.type = v2_float; getCache(v2_float)[this.ptr] = this; return; }
    this.ptr = _mud_v2_float__construct_2(/*x*/a0, /*y*/a1); this.type = v2_float; getCache(v2_float)[this.ptr] = this;
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
        _mud_v2_float__set_y(self, value);
    }
});
v2_float.prototype["__destroy__"] = v2_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v2_float__destroy(self);
};
// v2<int>
function v2_int(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_v2_int__construct_0(); this.type = v2_int; getCache(v2_int)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v2_int__construct_1(/*v*/a0); this.type = v2_int; getCache(v2_int)[this.ptr] = this; return; }
    this.ptr = _mud_v2_int__construct_2(/*x*/a0, /*y*/a1); this.type = v2_int; getCache(v2_int)[this.ptr] = this;
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
        _mud_v2_int__set_y(self, value);
    }
});
v2_int.prototype["__destroy__"] = v2_int.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v2_int__destroy(self);
};
// v2<uint>
function v2_uint(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_v2_uint__construct_0(); this.type = v2_uint; getCache(v2_uint)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v2_uint__construct_1(/*v*/a0); this.type = v2_uint; getCache(v2_uint)[this.ptr] = this; return; }
    this.ptr = _mud_v2_uint__construct_2(/*x*/a0, /*y*/a1); this.type = v2_uint; getCache(v2_uint)[this.ptr] = this;
};
v2_uint.prototype = Object.create(WrapperObject.prototype);
v2_uint.prototype.constructor = v2_uint;
v2_uint.prototype.__class__ = v2_uint;
v2_uint.__cache__ = {};
Module['v2_uint'] = v2_uint;
Object.defineProperty(v2_uint.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_uint__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v2_uint__set_x(self, value);
    }
});
Object.defineProperty(v2_uint.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_uint__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v2_uint__set_y(self, value);
    }
});
v2_uint.prototype["__destroy__"] = v2_uint.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v2_uint__destroy(self);
};
// v3<bool>
function v3_bool(a0, a1, a2) {
    if (a0 === undefined) { this.ptr = _mud_v3_bool__construct_0(); this.type = v3_bool; getCache(v3_bool)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v3_bool__construct_1(/*v*/a0); this.type = v3_bool; getCache(v3_bool)[this.ptr] = this; return; }
    this.ptr = _mud_v3_bool__construct_3(/*x*/a0, /*y*/a1, /*z*/a2); this.type = v3_bool; getCache(v3_bool)[this.ptr] = this;
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
        _mud_v3_bool__set_z(self, value);
    }
});
v3_bool.prototype["__destroy__"] = v3_bool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v3_bool__destroy(self);
};
// v3<float>
function v3_float(a0, a1, a2) {
    if (a0 === undefined) { this.ptr = _mud_v3_float__construct_0(); this.type = v3_float; getCache(v3_float)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v3_float__construct_1(/*v*/a0); this.type = v3_float; getCache(v3_float)[this.ptr] = this; return; }
    this.ptr = _mud_v3_float__construct_3(/*x*/a0, /*y*/a1, /*z*/a2); this.type = v3_float; getCache(v3_float)[this.ptr] = this;
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
        _mud_v3_float__set_z(self, value);
    }
});
v3_float.prototype["__destroy__"] = v3_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v3_float__destroy(self);
};
// v3<int>
function v3_int(a0, a1, a2) {
    if (a0 === undefined) { this.ptr = _mud_v3_int__construct_0(); this.type = v3_int; getCache(v3_int)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v3_int__construct_1(/*v*/a0); this.type = v3_int; getCache(v3_int)[this.ptr] = this; return; }
    this.ptr = _mud_v3_int__construct_3(/*x*/a0, /*y*/a1, /*z*/a2); this.type = v3_int; getCache(v3_int)[this.ptr] = this;
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
        _mud_v3_int__set_z(self, value);
    }
});
v3_int.prototype["__destroy__"] = v3_int.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v3_int__destroy(self);
};
// v3<uint>
function v3_uint(a0, a1, a2) {
    if (a0 === undefined) { this.ptr = _mud_v3_uint__construct_0(); this.type = v3_uint; getCache(v3_uint)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v3_uint__construct_1(/*v*/a0); this.type = v3_uint; getCache(v3_uint)[this.ptr] = this; return; }
    this.ptr = _mud_v3_uint__construct_3(/*x*/a0, /*y*/a1, /*z*/a2); this.type = v3_uint; getCache(v3_uint)[this.ptr] = this;
};
v3_uint.prototype = Object.create(WrapperObject.prototype);
v3_uint.prototype.constructor = v3_uint;
v3_uint.prototype.__class__ = v3_uint;
v3_uint.__cache__ = {};
Module['v3_uint'] = v3_uint;
Object.defineProperty(v3_uint.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v3_uint__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v3_uint__set_x(self, value);
    }
});
Object.defineProperty(v3_uint.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v3_uint__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v3_uint__set_y(self, value);
    }
});
Object.defineProperty(v3_uint.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_v3_uint__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v3_uint__set_z(self, value);
    }
});
v3_uint.prototype["__destroy__"] = v3_uint.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v3_uint__destroy(self);
};
// v4<bool>
function v4_bool(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_v4_bool__construct_0(); this.type = v4_bool; getCache(v4_bool)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v4_bool__construct_1(/*v*/a0); this.type = v4_bool; getCache(v4_bool)[this.ptr] = this; return; }
    this.ptr = _mud_v4_bool__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); this.type = v4_bool; getCache(v4_bool)[this.ptr] = this;
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
        _mud_v4_bool__set_w(self, value);
    }
});
v4_bool.prototype["__destroy__"] = v4_bool.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v4_bool__destroy(self);
};
// v4<float>
function v4_float(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_v4_float__construct_0(); this.type = v4_float; getCache(v4_float)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v4_float__construct_1(/*v*/a0); this.type = v4_float; getCache(v4_float)[this.ptr] = this; return; }
    this.ptr = _mud_v4_float__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); this.type = v4_float; getCache(v4_float)[this.ptr] = this;
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
        _mud_v4_float__set_w(self, value);
    }
});
v4_float.prototype["__destroy__"] = v4_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v4_float__destroy(self);
};
// v4<int>
function v4_int(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_v4_int__construct_0(); this.type = v4_int; getCache(v4_int)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v4_int__construct_1(/*v*/a0); this.type = v4_int; getCache(v4_int)[this.ptr] = this; return; }
    this.ptr = _mud_v4_int__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); this.type = v4_int; getCache(v4_int)[this.ptr] = this;
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
        _mud_v4_int__set_w(self, value);
    }
});
v4_int.prototype["__destroy__"] = v4_int.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v4_int__destroy(self);
};
// v4<uint>
function v4_uint(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_v4_uint__construct_0(); this.type = v4_uint; getCache(v4_uint)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v4_uint__construct_1(/*v*/a0); this.type = v4_uint; getCache(v4_uint)[this.ptr] = this; return; }
    this.ptr = _mud_v4_uint__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); this.type = v4_uint; getCache(v4_uint)[this.ptr] = this;
};
v4_uint.prototype = Object.create(WrapperObject.prototype);
v4_uint.prototype.constructor = v4_uint;
v4_uint.prototype.__class__ = v4_uint;
v4_uint.__cache__ = {};
Module['v4_uint'] = v4_uint;
Object.defineProperty(v4_uint.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_uint__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v4_uint__set_x(self, value);
    }
});
Object.defineProperty(v4_uint.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_uint__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v4_uint__set_y(self, value);
    }
});
Object.defineProperty(v4_uint.prototype, "z", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_uint__get_z(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v4_uint__set_z(self, value);
    }
});
Object.defineProperty(v4_uint.prototype, "w", {
    get: function() {
        var self = this.ptr;
        return _mud_v4_uint__get_w(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v4_uint__set_w(self, value);
    }
});
v4_uint.prototype["__destroy__"] = v4_uint.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v4_uint__destroy(self);
};
// Sprite
function Sprite() { throw "cannot construct a Sprite, no constructor in IDL" }
Sprite.prototype = Object.create(Image.prototype);
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
SpriteAtlas.prototype = Object.create(ImageAtlas.prototype);
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
TextureAtlas.prototype = Object.create(ImageAtlas.prototype);
TextureAtlas.prototype.constructor = TextureAtlas;
TextureAtlas.prototype.__class__ = TextureAtlas;
TextureAtlas.__cache__ = {};
Module['TextureAtlas'] = TextureAtlas;
TextureAtlas.prototype["__destroy__"] = TextureAtlas.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TextureAtlas__destroy(self);
};
// quat
function quat(a0, a1, a2, a3) {
    if (a0 === undefined) { this.ptr = _mud_quat__construct_0(); this.type = quat; getCache(quat)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_quat__construct_1(/*euler_angles*/a0.ptr); this.type = quat; getCache(quat)[this.ptr] = this; return; }
    this.ptr = _mud_quat__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); this.type = quat; getCache(quat)[this.ptr] = this;
};
quat.prototype = Object.create(v4_float.prototype);
quat.prototype.constructor = quat;
quat.prototype.__class__ = quat;
quat.__cache__ = {};
Module['quat'] = quat;
quat.prototype["__destroy__"] = quat.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_quat__destroy(self);
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
    return _mud_to_rgba_1(/*colour*/a0.ptr);
};
Module['to_abgr'] = function(a0) {
    return _mud_to_abgr_1(/*colour*/a0.ptr);
};
Module['to_linear'] = function(a0) {
    return wrapPointer(_mud_to_linear_1(/*colour*/a0.ptr), Colour);
};
Module['to_gamma'] = function(a0) {
    return wrapPointer(_mud_to_gamma_1(/*colour*/a0.ptr), Colour);
};
Module['to_srgb'] = function(a0) {
    return wrapPointer(_mud_to_srgb_1(/*colour*/a0.ptr), Colour);
};
Module['to_hsl'] = function(a0, a1, a2) {
    if (a1 === undefined) { return wrapPointer(_mud_to_hsl_1(/*colour*/a0.ptr), ColourHSL); }
    return wrapPointer(_mud_to_hsl_3(/*r*/a0, /*g*/a1, /*b*/a2), ColourHSL);
};
Module['to_hsla'] = function(a0) {
    return wrapPointer(_mud_to_hsla_1(/*colour*/a0.ptr), ColourHSL);
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
    if (a1 === undefined) { return wrapPointer(_mud_look_dir_1(/*direction*/a0.ptr), quat); }
    return wrapPointer(_mud_look_dir_2(/*direction*/a0.ptr, /*forward*/a1.ptr), quat);
};
Module['look_at'] = function(a0, a1, a2) {
    if (a2 === undefined) { return wrapPointer(_mud_look_at_2(/*eye*/a0.ptr, /*target*/a1.ptr), quat); }
    return wrapPointer(_mud_look_at_3(/*eye*/a0.ptr, /*target*/a1.ptr, /*forward*/a2.ptr), quat);
};
Module['grid'] = function(a0, a1) {
    _mud_grid_2(/*size*/a0.ptr, /*output_coords*/a1.ptr);
};
Module['grid_center'] = function(a0, a1) {
    return wrapPointer(_mud_grid_center_2(/*coord*/a0.ptr, /*cell_size*/a1.ptr), v3_float);
};
Module['index_list'] = function(a0, a1) {
    _mud_index_list_2(/*size*/a0, /*output_indices*/a1.ptr);
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
        Colour.__type__ = _mud_Colour__type();
        ColourHSL.__type__ = _mud_ColourHSL__type();
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
