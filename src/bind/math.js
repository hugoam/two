Module['stl'] = Module['stl'] || {};
// v2<float>
function v2_float(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('v2<T>(0:v): expected number'); }
    else { if (typeof a0 !== 'number') throw Error('v2<T>(0:x): expected number'); if (typeof a1 !== 'number') throw Error('v2<T>(1:y): expected number'); }
    if (a0 === undefined) { this.__ptr = _two_v2_float__construct_0(); getCache(v2_float)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v2_float__construct_1(/*v*/a0); getCache(v2_float)[this.__ptr] = this; }
    else { this.__ptr = _two_v2_float__construct_2(/*x*/a0, /*y*/a1); getCache(v2_float)[this.__ptr] = this; }
};
v2_float.prototype = Object.create(WrapperObject.prototype);
v2_float.prototype.constructor = v2_float;
v2_float.prototype.__class = v2_float;
v2_float.__cache = {};
Module['v2_float'] = v2_float;
Object.defineProperty(v2_float.prototype, "x", {
    get: function() {
        return _two_v2_float__get_x(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<float>.x: expected number');
        _two_v2_float__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v2_float.prototype, "y", {
    get: function() {
        return _two_v2_float__get_y(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<float>.y: expected number');
        _two_v2_float__set_y(this.__ptr, value);
    }
});
v2_float.prototype["__destroy"] = v2_float.prototype.__destroy = function() {
    _two_v2_float__destroy(this.__ptr);
};
// v3<float>
function v3_float(a0, a1, a2) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('v3<T>(0:v): expected number'); }
    else { if (typeof a0 !== 'number') throw Error('v3<T>(0:x): expected number'); if (typeof a1 !== 'number') throw Error('v3<T>(1:y): expected number'); if (typeof a2 !== 'number') throw Error('v3<T>(2:z): expected number'); }
    if (a0 === undefined) { this.__ptr = _two_v3_float__construct_0(); getCache(v3_float)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v3_float__construct_1(/*v*/a0); getCache(v3_float)[this.__ptr] = this; }
    else { this.__ptr = _two_v3_float__construct_3(/*x*/a0, /*y*/a1, /*z*/a2); getCache(v3_float)[this.__ptr] = this; }
};
v3_float.prototype = Object.create(WrapperObject.prototype);
v3_float.prototype.constructor = v3_float;
v3_float.prototype.__class = v3_float;
v3_float.__cache = {};
Module['v3_float'] = v3_float;
Object.defineProperty(v3_float.prototype, "x", {
    get: function() {
        return _two_v3_float__get_x(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v3<float>.x: expected number');
        _two_v3_float__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v3_float.prototype, "y", {
    get: function() {
        return _two_v3_float__get_y(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v3<float>.y: expected number');
        _two_v3_float__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v3_float.prototype, "z", {
    get: function() {
        return _two_v3_float__get_z(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v3<float>.z: expected number');
        _two_v3_float__set_z(this.__ptr, value);
    }
});
v3_float.prototype["__destroy"] = v3_float.prototype.__destroy = function() {
    _two_v3_float__destroy(this.__ptr);
};
// v4<float>
function v4_float(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('v4<T>(0:v): expected number'); }
    else { if (typeof a0 !== 'number') throw Error('v4<T>(0:x): expected number'); if (typeof a1 !== 'number') throw Error('v4<T>(1:y): expected number'); if (typeof a2 !== 'number') throw Error('v4<T>(2:z): expected number'); if (typeof a3 !== 'number') throw Error('v4<T>(3:w): expected number'); }
    if (a0 === undefined) { this.__ptr = _two_v4_float__construct_0(); getCache(v4_float)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v4_float__construct_1(/*v*/a0); getCache(v4_float)[this.__ptr] = this; }
    else { this.__ptr = _two_v4_float__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); getCache(v4_float)[this.__ptr] = this; }
};
v4_float.prototype = Object.create(WrapperObject.prototype);
v4_float.prototype.constructor = v4_float;
v4_float.prototype.__class = v4_float;
v4_float.__cache = {};
Module['v4_float'] = v4_float;
Object.defineProperty(v4_float.prototype, "x", {
    get: function() {
        return _two_v4_float__get_x(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v4<float>.x: expected number');
        _two_v4_float__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v4_float.prototype, "y", {
    get: function() {
        return _two_v4_float__get_y(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v4<float>.y: expected number');
        _two_v4_float__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v4_float.prototype, "z", {
    get: function() {
        return _two_v4_float__get_z(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v4<float>.z: expected number');
        _two_v4_float__set_z(this.__ptr, value);
    }
});
Object.defineProperty(v4_float.prototype, "w", {
    get: function() {
        return _two_v4_float__get_w(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v4<float>.w: expected number');
        _two_v4_float__set_w(this.__ptr, value);
    }
});
v4_float.prototype["__destroy"] = v4_float.prototype.__destroy = function() {
    _two_v4_float__destroy(this.__ptr);
};
// v2<int>
function v2_int(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('v2<T>(0:v): expected integer'); }
    else { if (typeof a0 !== 'number') throw Error('v2<T>(0:x): expected integer'); if (typeof a1 !== 'number') throw Error('v2<T>(1:y): expected integer'); }
    if (a0 === undefined) { this.__ptr = _two_v2_int__construct_0(); getCache(v2_int)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v2_int__construct_1(/*v*/a0); getCache(v2_int)[this.__ptr] = this; }
    else { this.__ptr = _two_v2_int__construct_2(/*x*/a0, /*y*/a1); getCache(v2_int)[this.__ptr] = this; }
};
v2_int.prototype = Object.create(WrapperObject.prototype);
v2_int.prototype.constructor = v2_int;
v2_int.prototype.__class = v2_int;
v2_int.__cache = {};
Module['v2_int'] = v2_int;
Object.defineProperty(v2_int.prototype, "x", {
    get: function() {
        return _two_v2_int__get_x(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<int>.x: expected integer');
        _two_v2_int__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v2_int.prototype, "y", {
    get: function() {
        return _two_v2_int__get_y(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<int>.y: expected integer');
        _two_v2_int__set_y(this.__ptr, value);
    }
});
v2_int.prototype["__destroy"] = v2_int.prototype.__destroy = function() {
    _two_v2_int__destroy(this.__ptr);
};
// v3<int>
function v3_int(a0, a1, a2) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('v3<T>(0:v): expected integer'); }
    else { if (typeof a0 !== 'number') throw Error('v3<T>(0:x): expected integer'); if (typeof a1 !== 'number') throw Error('v3<T>(1:y): expected integer'); if (typeof a2 !== 'number') throw Error('v3<T>(2:z): expected integer'); }
    if (a0 === undefined) { this.__ptr = _two_v3_int__construct_0(); getCache(v3_int)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v3_int__construct_1(/*v*/a0); getCache(v3_int)[this.__ptr] = this; }
    else { this.__ptr = _two_v3_int__construct_3(/*x*/a0, /*y*/a1, /*z*/a2); getCache(v3_int)[this.__ptr] = this; }
};
v3_int.prototype = Object.create(WrapperObject.prototype);
v3_int.prototype.constructor = v3_int;
v3_int.prototype.__class = v3_int;
v3_int.__cache = {};
Module['v3_int'] = v3_int;
Object.defineProperty(v3_int.prototype, "x", {
    get: function() {
        return _two_v3_int__get_x(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v3<int>.x: expected integer');
        _two_v3_int__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v3_int.prototype, "y", {
    get: function() {
        return _two_v3_int__get_y(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v3<int>.y: expected integer');
        _two_v3_int__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v3_int.prototype, "z", {
    get: function() {
        return _two_v3_int__get_z(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v3<int>.z: expected integer');
        _two_v3_int__set_z(this.__ptr, value);
    }
});
v3_int.prototype["__destroy"] = v3_int.prototype.__destroy = function() {
    _two_v3_int__destroy(this.__ptr);
};
// v4<int>
function v4_int(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('v4<T>(0:v): expected integer'); }
    else { if (typeof a0 !== 'number') throw Error('v4<T>(0:x): expected integer'); if (typeof a1 !== 'number') throw Error('v4<T>(1:y): expected integer'); if (typeof a2 !== 'number') throw Error('v4<T>(2:z): expected integer'); if (typeof a3 !== 'number') throw Error('v4<T>(3:w): expected integer'); }
    if (a0 === undefined) { this.__ptr = _two_v4_int__construct_0(); getCache(v4_int)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v4_int__construct_1(/*v*/a0); getCache(v4_int)[this.__ptr] = this; }
    else { this.__ptr = _two_v4_int__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); getCache(v4_int)[this.__ptr] = this; }
};
v4_int.prototype = Object.create(WrapperObject.prototype);
v4_int.prototype.constructor = v4_int;
v4_int.prototype.__class = v4_int;
v4_int.__cache = {};
Module['v4_int'] = v4_int;
Object.defineProperty(v4_int.prototype, "x", {
    get: function() {
        return _two_v4_int__get_x(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v4<int>.x: expected integer');
        _two_v4_int__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v4_int.prototype, "y", {
    get: function() {
        return _two_v4_int__get_y(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v4<int>.y: expected integer');
        _two_v4_int__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v4_int.prototype, "z", {
    get: function() {
        return _two_v4_int__get_z(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v4<int>.z: expected integer');
        _two_v4_int__set_z(this.__ptr, value);
    }
});
Object.defineProperty(v4_int.prototype, "w", {
    get: function() {
        return _two_v4_int__get_w(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v4<int>.w: expected integer');
        _two_v4_int__set_w(this.__ptr, value);
    }
});
v4_int.prototype["__destroy"] = v4_int.prototype.__destroy = function() {
    _two_v4_int__destroy(this.__ptr);
};
// v2<uint>
function v2_uint(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('v2<T>(0:v): expected integer'); }
    else { if (typeof a0 !== 'number') throw Error('v2<T>(0:x): expected integer'); if (typeof a1 !== 'number') throw Error('v2<T>(1:y): expected integer'); }
    if (a0 === undefined) { this.__ptr = _two_v2_uint__construct_0(); getCache(v2_uint)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v2_uint__construct_1(/*v*/a0); getCache(v2_uint)[this.__ptr] = this; }
    else { this.__ptr = _two_v2_uint__construct_2(/*x*/a0, /*y*/a1); getCache(v2_uint)[this.__ptr] = this; }
};
v2_uint.prototype = Object.create(WrapperObject.prototype);
v2_uint.prototype.constructor = v2_uint;
v2_uint.prototype.__class = v2_uint;
v2_uint.__cache = {};
Module['v2_uint'] = v2_uint;
Object.defineProperty(v2_uint.prototype, "x", {
    get: function() {
        return _two_v2_uint__get_x(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<uint>.x: expected integer');
        _two_v2_uint__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v2_uint.prototype, "y", {
    get: function() {
        return _two_v2_uint__get_y(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<uint>.y: expected integer');
        _two_v2_uint__set_y(this.__ptr, value);
    }
});
v2_uint.prototype["__destroy"] = v2_uint.prototype.__destroy = function() {
    _two_v2_uint__destroy(this.__ptr);
};
// v3<uint>
function v3_uint(a0, a1, a2) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('v3<T>(0:v): expected integer'); }
    else { if (typeof a0 !== 'number') throw Error('v3<T>(0:x): expected integer'); if (typeof a1 !== 'number') throw Error('v3<T>(1:y): expected integer'); if (typeof a2 !== 'number') throw Error('v3<T>(2:z): expected integer'); }
    if (a0 === undefined) { this.__ptr = _two_v3_uint__construct_0(); getCache(v3_uint)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v3_uint__construct_1(/*v*/a0); getCache(v3_uint)[this.__ptr] = this; }
    else { this.__ptr = _two_v3_uint__construct_3(/*x*/a0, /*y*/a1, /*z*/a2); getCache(v3_uint)[this.__ptr] = this; }
};
v3_uint.prototype = Object.create(WrapperObject.prototype);
v3_uint.prototype.constructor = v3_uint;
v3_uint.prototype.__class = v3_uint;
v3_uint.__cache = {};
Module['v3_uint'] = v3_uint;
Object.defineProperty(v3_uint.prototype, "x", {
    get: function() {
        return _two_v3_uint__get_x(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v3<uint>.x: expected integer');
        _two_v3_uint__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v3_uint.prototype, "y", {
    get: function() {
        return _two_v3_uint__get_y(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v3<uint>.y: expected integer');
        _two_v3_uint__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v3_uint.prototype, "z", {
    get: function() {
        return _two_v3_uint__get_z(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v3<uint>.z: expected integer');
        _two_v3_uint__set_z(this.__ptr, value);
    }
});
v3_uint.prototype["__destroy"] = v3_uint.prototype.__destroy = function() {
    _two_v3_uint__destroy(this.__ptr);
};
// v4<uint>
function v4_uint(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('v4<T>(0:v): expected integer'); }
    else { if (typeof a0 !== 'number') throw Error('v4<T>(0:x): expected integer'); if (typeof a1 !== 'number') throw Error('v4<T>(1:y): expected integer'); if (typeof a2 !== 'number') throw Error('v4<T>(2:z): expected integer'); if (typeof a3 !== 'number') throw Error('v4<T>(3:w): expected integer'); }
    if (a0 === undefined) { this.__ptr = _two_v4_uint__construct_0(); getCache(v4_uint)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v4_uint__construct_1(/*v*/a0); getCache(v4_uint)[this.__ptr] = this; }
    else { this.__ptr = _two_v4_uint__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); getCache(v4_uint)[this.__ptr] = this; }
};
v4_uint.prototype = Object.create(WrapperObject.prototype);
v4_uint.prototype.constructor = v4_uint;
v4_uint.prototype.__class = v4_uint;
v4_uint.__cache = {};
Module['v4_uint'] = v4_uint;
Object.defineProperty(v4_uint.prototype, "x", {
    get: function() {
        return _two_v4_uint__get_x(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v4<uint>.x: expected integer');
        _two_v4_uint__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v4_uint.prototype, "y", {
    get: function() {
        return _two_v4_uint__get_y(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v4<uint>.y: expected integer');
        _two_v4_uint__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v4_uint.prototype, "z", {
    get: function() {
        return _two_v4_uint__get_z(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v4<uint>.z: expected integer');
        _two_v4_uint__set_z(this.__ptr, value);
    }
});
Object.defineProperty(v4_uint.prototype, "w", {
    get: function() {
        return _two_v4_uint__get_w(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v4<uint>.w: expected integer');
        _two_v4_uint__set_w(this.__ptr, value);
    }
});
v4_uint.prototype["__destroy"] = v4_uint.prototype.__destroy = function() {
    _two_v4_uint__destroy(this.__ptr);
};
// v2<bool>
function v2_bool(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'boolean') throw Error('v2<T>(0:v): expected boolean'); }
    else { if (typeof a0 !== 'boolean') throw Error('v2<T>(0:x): expected boolean'); if (typeof a1 !== 'boolean') throw Error('v2<T>(1:y): expected boolean'); }
    if (a0 === undefined) { this.__ptr = _two_v2_bool__construct_0(); getCache(v2_bool)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v2_bool__construct_1(/*v*/a0); getCache(v2_bool)[this.__ptr] = this; }
    else { this.__ptr = _two_v2_bool__construct_2(/*x*/a0, /*y*/a1); getCache(v2_bool)[this.__ptr] = this; }
};
v2_bool.prototype = Object.create(WrapperObject.prototype);
v2_bool.prototype.constructor = v2_bool;
v2_bool.prototype.__class = v2_bool;
v2_bool.__cache = {};
Module['v2_bool'] = v2_bool;
Object.defineProperty(v2_bool.prototype, "x", {
    get: function() {
        return !!(_two_v2_bool__get_x(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('v2<bool>.x: expected boolean');
        _two_v2_bool__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v2_bool.prototype, "y", {
    get: function() {
        return !!(_two_v2_bool__get_y(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('v2<bool>.y: expected boolean');
        _two_v2_bool__set_y(this.__ptr, value);
    }
});
v2_bool.prototype["__destroy"] = v2_bool.prototype.__destroy = function() {
    _two_v2_bool__destroy(this.__ptr);
};
// v3<bool>
function v3_bool(a0, a1, a2) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'boolean') throw Error('v3<T>(0:v): expected boolean'); }
    else { if (typeof a0 !== 'boolean') throw Error('v3<T>(0:x): expected boolean'); if (typeof a1 !== 'boolean') throw Error('v3<T>(1:y): expected boolean'); if (typeof a2 !== 'boolean') throw Error('v3<T>(2:z): expected boolean'); }
    if (a0 === undefined) { this.__ptr = _two_v3_bool__construct_0(); getCache(v3_bool)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v3_bool__construct_1(/*v*/a0); getCache(v3_bool)[this.__ptr] = this; }
    else { this.__ptr = _two_v3_bool__construct_3(/*x*/a0, /*y*/a1, /*z*/a2); getCache(v3_bool)[this.__ptr] = this; }
};
v3_bool.prototype = Object.create(WrapperObject.prototype);
v3_bool.prototype.constructor = v3_bool;
v3_bool.prototype.__class = v3_bool;
v3_bool.__cache = {};
Module['v3_bool'] = v3_bool;
Object.defineProperty(v3_bool.prototype, "x", {
    get: function() {
        return !!(_two_v3_bool__get_x(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('v3<bool>.x: expected boolean');
        _two_v3_bool__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v3_bool.prototype, "y", {
    get: function() {
        return !!(_two_v3_bool__get_y(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('v3<bool>.y: expected boolean');
        _two_v3_bool__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v3_bool.prototype, "z", {
    get: function() {
        return !!(_two_v3_bool__get_z(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('v3<bool>.z: expected boolean');
        _two_v3_bool__set_z(this.__ptr, value);
    }
});
v3_bool.prototype["__destroy"] = v3_bool.prototype.__destroy = function() {
    _two_v3_bool__destroy(this.__ptr);
};
// v4<bool>
function v4_bool(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'boolean') throw Error('v4<T>(0:v): expected boolean'); }
    else { if (typeof a0 !== 'boolean') throw Error('v4<T>(0:x): expected boolean'); if (typeof a1 !== 'boolean') throw Error('v4<T>(1:y): expected boolean'); if (typeof a2 !== 'boolean') throw Error('v4<T>(2:z): expected boolean'); if (typeof a3 !== 'boolean') throw Error('v4<T>(3:w): expected boolean'); }
    if (a0 === undefined) { this.__ptr = _two_v4_bool__construct_0(); getCache(v4_bool)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v4_bool__construct_1(/*v*/a0); getCache(v4_bool)[this.__ptr] = this; }
    else { this.__ptr = _two_v4_bool__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); getCache(v4_bool)[this.__ptr] = this; }
};
v4_bool.prototype = Object.create(WrapperObject.prototype);
v4_bool.prototype.constructor = v4_bool;
v4_bool.prototype.__class = v4_bool;
v4_bool.__cache = {};
Module['v4_bool'] = v4_bool;
Object.defineProperty(v4_bool.prototype, "x", {
    get: function() {
        return !!(_two_v4_bool__get_x(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('v4<bool>.x: expected boolean');
        _two_v4_bool__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v4_bool.prototype, "y", {
    get: function() {
        return !!(_two_v4_bool__get_y(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('v4<bool>.y: expected boolean');
        _two_v4_bool__set_y(this.__ptr, value);
    }
});
Object.defineProperty(v4_bool.prototype, "z", {
    get: function() {
        return !!(_two_v4_bool__get_z(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('v4<bool>.z: expected boolean');
        _two_v4_bool__set_z(this.__ptr, value);
    }
});
Object.defineProperty(v4_bool.prototype, "w", {
    get: function() {
        return !!(_two_v4_bool__get_w(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('v4<bool>.w: expected boolean');
        _two_v4_bool__set_w(this.__ptr, value);
    }
});
v4_bool.prototype["__destroy"] = v4_bool.prototype.__destroy = function() {
    _two_v4_bool__destroy(this.__ptr);
};
// mat3
function mat3(a0, a1, a2, a3, a4, a5, a6, a7, a8) {
    if (a0 === undefined) {  }
    else if (a3 === undefined) { if (!checkClass(a0, v3_float)) throw Error('mat3(0:x): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('mat3(1:y): expected v3<float>'); if (!checkClass(a2, v3_float)) throw Error('mat3(2:z): expected v3<float>'); }
    else { if (typeof a0 !== 'number') throw Error('mat3(0:f0): expected number'); if (typeof a1 !== 'number') throw Error('mat3(1:f1): expected number'); if (typeof a2 !== 'number') throw Error('mat3(2:f2): expected number'); if (typeof a3 !== 'number') throw Error('mat3(3:f3): expected number'); if (typeof a4 !== 'number') throw Error('mat3(4:f4): expected number'); if (typeof a5 !== 'number') throw Error('mat3(5:f5): expected number'); if (typeof a6 !== 'number') throw Error('mat3(6:f6): expected number'); if (typeof a7 !== 'number') throw Error('mat3(7:f7): expected number'); if (typeof a8 !== 'number') throw Error('mat3(8:f8): expected number'); }
    if (a0 === undefined) { this.__ptr = _two_mat3__construct_0(); getCache(mat3)[this.__ptr] = this; }
    else if (a3 === undefined) { this.__ptr = _two_mat3__construct_3(/*x*/a0.__ptr, /*y*/a1.__ptr, /*z*/a2.__ptr); getCache(mat3)[this.__ptr] = this; }
    else { this.__ptr = _two_mat3__construct_9(/*f0*/a0, /*f1*/a1, /*f2*/a2, /*f3*/a3, /*f4*/a4, /*f5*/a5, /*f6*/a6, /*f7*/a7, /*f8*/a8); getCache(mat3)[this.__ptr] = this; }
};
mat3.prototype = Object.create(WrapperObject.prototype);
mat3.prototype.constructor = mat3;
mat3.prototype.__class = mat3;
mat3.__cache = {};
Module['mat3'] = mat3;
Object.defineProperty(mat3.prototype, "f", {
    get: function() {
        return _two_mat3__get_f(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('mat3.f: expected number');
        _two_mat3__set_f(this.__ptr, ensureFloat32(value));
    }
});
mat3.prototype["__destroy"] = mat3.prototype.__destroy = function() {
    _two_mat3__destroy(this.__ptr);
};
// mat4
function mat4(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15) {
    if (a0 === undefined) {  }
    else if (a4 === undefined) { if (!checkClass(a0, v4_float)) throw Error('mat4(0:x): expected v4<float>'); if (!checkClass(a1, v4_float)) throw Error('mat4(1:y): expected v4<float>'); if (!checkClass(a2, v4_float)) throw Error('mat4(2:z): expected v4<float>'); if (!checkClass(a3, v4_float)) throw Error('mat4(3:w): expected v4<float>'); }
    else { if (typeof a0 !== 'number') throw Error('mat4(0:f0): expected number'); if (typeof a1 !== 'number') throw Error('mat4(1:f1): expected number'); if (typeof a2 !== 'number') throw Error('mat4(2:f2): expected number'); if (typeof a3 !== 'number') throw Error('mat4(3:f3): expected number'); if (typeof a4 !== 'number') throw Error('mat4(4:f4): expected number'); if (typeof a5 !== 'number') throw Error('mat4(5:f5): expected number'); if (typeof a6 !== 'number') throw Error('mat4(6:f6): expected number'); if (typeof a7 !== 'number') throw Error('mat4(7:f7): expected number'); if (typeof a8 !== 'number') throw Error('mat4(8:f8): expected number'); if (typeof a9 !== 'number') throw Error('mat4(9:f9): expected number'); if (typeof a10 !== 'number') throw Error('mat4(10:f10): expected number'); if (typeof a11 !== 'number') throw Error('mat4(11:f11): expected number'); if (typeof a12 !== 'number') throw Error('mat4(12:f12): expected number'); if (typeof a13 !== 'number') throw Error('mat4(13:f13): expected number'); if (typeof a14 !== 'number') throw Error('mat4(14:f14): expected number'); if (typeof a15 !== 'number') throw Error('mat4(15:f15): expected number'); }
    if (a0 === undefined) { this.__ptr = _two_mat4__construct_0(); getCache(mat4)[this.__ptr] = this; }
    else if (a4 === undefined) { this.__ptr = _two_mat4__construct_4(/*x*/a0.__ptr, /*y*/a1.__ptr, /*z*/a2.__ptr, /*w*/a3.__ptr); getCache(mat4)[this.__ptr] = this; }
    else { this.__ptr = _two_mat4__construct_16(/*f0*/a0, /*f1*/a1, /*f2*/a2, /*f3*/a3, /*f4*/a4, /*f5*/a5, /*f6*/a6, /*f7*/a7, /*f8*/a8, /*f9*/a9, /*f10*/a10, /*f11*/a11, /*f12*/a12, /*f13*/a13, /*f14*/a14, /*f15*/a15); getCache(mat4)[this.__ptr] = this; }
};
mat4.prototype = Object.create(WrapperObject.prototype);
mat4.prototype.constructor = mat4;
mat4.prototype.__class = mat4;
mat4.__cache = {};
Module['mat4'] = mat4;
Object.defineProperty(mat4.prototype, "f", {
    get: function() {
        return _two_mat4__get_f(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('mat4.f: expected number');
        _two_mat4__set_f(this.__ptr, ensureFloat32(value));
    }
});
mat4.prototype["__destroy"] = mat4.prototype.__destroy = function() {
    _two_mat4__destroy(this.__ptr);
};
// quat
function quat(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (!checkClass(a0, v3_float)) throw Error('quat(0:euler_angles): expected v3<float>'); }
    else { if (typeof a0 !== 'number') throw Error('quat(0:x): expected number'); if (typeof a1 !== 'number') throw Error('quat(1:y): expected number'); if (typeof a2 !== 'number') throw Error('quat(2:z): expected number'); if (typeof a3 !== 'number') throw Error('quat(3:w): expected number'); }
    if (a0 === undefined) { this.__ptr = _two_quat__construct_0(); getCache(quat)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_quat__construct_1(/*euler_angles*/a0.__ptr); getCache(quat)[this.__ptr] = this; }
    else { this.__ptr = _two_quat__construct_4(/*x*/a0, /*y*/a1, /*z*/a2, /*w*/a3); getCache(quat)[this.__ptr] = this; }
};
quat.prototype = Object.create(v4_float.prototype);
quat.prototype.constructor = quat;
quat.prototype.__class = quat;
quat.__base = v4_float;
quat.__cache = {};
Module['quat'] = quat;
quat.prototype["__destroy"] = quat.prototype.__destroy = function() {
    _two_quat__destroy(this.__ptr);
};
// Transform
function Transform() {
    
    this.__ptr = _two_Transform__construct_0(); getCache(Transform)[this.__ptr] = this;
};
Transform.prototype = Object.create(WrapperObject.prototype);
Transform.prototype.constructor = Transform;
Transform.prototype.__class = Transform;
Transform.__cache = {};
Module['Transform'] = Transform;
Object.defineProperty(Transform.prototype, "position", {
    get: function() {
        return wrapPointer(_two_Transform__get_position(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Transform.position: expected v3<float>');
        _two_Transform__set_position(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Transform.prototype, "rotation", {
    get: function() {
        return wrapPointer(_two_Transform__get_rotation(this.__ptr), quat);
    },
    set: function(value) {
        if (!checkClass(value, quat)) throw Error('Transform.rotation: expected quat');
        _two_Transform__set_rotation(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Transform.prototype, "scale", {
    get: function() {
        return wrapPointer(_two_Transform__get_scale(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Transform.scale: expected v3<float>');
        _two_Transform__set_scale(this.__ptr, value.__ptr);
    }
});
Transform.prototype["__destroy"] = Transform.prototype.__destroy = function() {
    _two_Transform__destroy(this.__ptr);
};
// ColourHSL
function ColourHSL() {
    
    this.__ptr = _two_ColourHSL__construct_0(); getCache(ColourHSL)[this.__ptr] = this;
};
ColourHSL.prototype = Object.create(WrapperObject.prototype);
ColourHSL.prototype.constructor = ColourHSL;
ColourHSL.prototype.__class = ColourHSL;
ColourHSL.__cache = {};
Module['ColourHSL'] = ColourHSL;
Object.defineProperty(ColourHSL.prototype, "h", {
    get: function() {
        return _two_ColourHSL__get_h(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ColourHSL.h: expected number');
        _two_ColourHSL__set_h(this.__ptr, value);
    }
});
Object.defineProperty(ColourHSL.prototype, "s", {
    get: function() {
        return _two_ColourHSL__get_s(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ColourHSL.s: expected number');
        _two_ColourHSL__set_s(this.__ptr, value);
    }
});
Object.defineProperty(ColourHSL.prototype, "l", {
    get: function() {
        return _two_ColourHSL__get_l(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ColourHSL.l: expected number');
        _two_ColourHSL__set_l(this.__ptr, value);
    }
});
Object.defineProperty(ColourHSL.prototype, "a", {
    get: function() {
        return _two_ColourHSL__get_a(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ColourHSL.a: expected number');
        _two_ColourHSL__set_a(this.__ptr, value);
    }
});
ColourHSL.prototype["__destroy"] = ColourHSL.prototype.__destroy = function() {
    _two_ColourHSL__destroy(this.__ptr);
};
// Colour
function Colour(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('Colour(0:v): expected number'); }
    else if (a2 === undefined) { if (typeof a0 !== 'number') throw Error('Colour(0:v): expected number'); if (typeof a1 !== 'number') throw Error('Colour(1:a): expected number'); }
    else if (a3 === undefined) { if (typeof a0 !== 'number') throw Error('Colour(0:r): expected number'); if (typeof a1 !== 'number') throw Error('Colour(1:g): expected number'); if (typeof a2 !== 'number') throw Error('Colour(2:b): expected number'); }
    else { if (typeof a0 !== 'number') throw Error('Colour(0:r): expected number'); if (typeof a1 !== 'number') throw Error('Colour(1:g): expected number'); if (typeof a2 !== 'number') throw Error('Colour(2:b): expected number'); if (typeof a3 !== 'number') throw Error('Colour(3:a): expected number'); }
    if (a0 === undefined) { this.__ptr = _two_Colour__construct_0(); getCache(Colour)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_Colour__construct_1(/*v*/a0); getCache(Colour)[this.__ptr] = this; }
    else if (a2 === undefined) { this.__ptr = _two_Colour__construct_2(/*v*/a0, /*a*/a1); getCache(Colour)[this.__ptr] = this; }
    else if (a3 === undefined) { this.__ptr = _two_Colour__construct_3(/*r*/a0, /*g*/a1, /*b*/a2); getCache(Colour)[this.__ptr] = this; }
    else { this.__ptr = _two_Colour__construct_4(/*r*/a0, /*g*/a1, /*b*/a2, /*a*/a3); getCache(Colour)[this.__ptr] = this; }
};
Colour.prototype = Object.create(WrapperObject.prototype);
Colour.prototype.constructor = Colour;
Colour.prototype.__class = Colour;
Colour.__cache = {};
Module['Colour'] = Colour;
Object.defineProperty(Colour.prototype, "r", {
    get: function() {
        return _two_Colour__get_r(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Colour.r: expected number');
        _two_Colour__set_r(this.__ptr, value);
    }
});
Object.defineProperty(Colour.prototype, "g", {
    get: function() {
        return _two_Colour__get_g(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Colour.g: expected number');
        _two_Colour__set_g(this.__ptr, value);
    }
});
Object.defineProperty(Colour.prototype, "b", {
    get: function() {
        return _two_Colour__get_b(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Colour.b: expected number');
        _two_Colour__set_b(this.__ptr, value);
    }
});
Object.defineProperty(Colour.prototype, "a", {
    get: function() {
        return _two_Colour__get_a(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Colour.a: expected number');
        _two_Colour__set_a(this.__ptr, value);
    }
});
Colour.prototype["__destroy"] = Colour.prototype.__destroy = function() {
    _two_Colour__destroy(this.__ptr);
};
// ValueCurve<float>
function ValueCurve_float(a0) {
    if (a0 === undefined) {  }
    else {  }
    if (a0 === undefined) { this.__ptr = _two_ValueCurve_float__construct_0(); getCache(ValueCurve_float)[this.__ptr] = this; }
    else { this.__ptr = _two_ValueCurve_float__construct_1(ensureFloat32(/*keys*/a0), /*keys*/a0.length); getCache(ValueCurve_float)[this.__ptr] = this; }
};
ValueCurve_float.prototype = Object.create(WrapperObject.prototype);
ValueCurve_float.prototype.constructor = ValueCurve_float;
ValueCurve_float.prototype.__class = ValueCurve_float;
ValueCurve_float.__cache = {};
Module['ValueCurve_float'] = ValueCurve_float;
Object.defineProperty(ValueCurve_float.prototype, "keys", {
    get: function() {
        return _two_ValueCurve_float__get_keys(this.__ptr);
    }});
ValueCurve_float.prototype["__destroy"] = ValueCurve_float.prototype.__destroy = function() {
    _two_ValueCurve_float__destroy(this.__ptr);
};
// ValueCurve<uint32_t>
function ValueCurve_uint32_t(a0) {
    if (a0 === undefined) {  }
    else {  }
    if (a0 === undefined) { this.__ptr = _two_ValueCurve_uint32_t__construct_0(); getCache(ValueCurve_uint32_t)[this.__ptr] = this; }
    else { this.__ptr = _two_ValueCurve_uint32_t__construct_1(ensureInt32(/*keys*/a0), /*keys*/a0.length); getCache(ValueCurve_uint32_t)[this.__ptr] = this; }
};
ValueCurve_uint32_t.prototype = Object.create(WrapperObject.prototype);
ValueCurve_uint32_t.prototype.constructor = ValueCurve_uint32_t;
ValueCurve_uint32_t.prototype.__class = ValueCurve_uint32_t;
ValueCurve_uint32_t.__cache = {};
Module['ValueCurve_uint32_t'] = ValueCurve_uint32_t;
Object.defineProperty(ValueCurve_uint32_t.prototype, "keys", {
    get: function() {
        return _two_ValueCurve_uint32_t__get_keys(this.__ptr);
    }});
ValueCurve_uint32_t.prototype["__destroy"] = ValueCurve_uint32_t.prototype.__destroy = function() {
    _two_ValueCurve_uint32_t__destroy(this.__ptr);
};
// ValueCurve<two::vec3>
function ValueCurve_two_vec3(a0) {
    if (a0 === undefined) {  }
    else {  }
    if (a0 === undefined) { this.__ptr = _two_ValueCurve_two_vec3__construct_0(); getCache(ValueCurve_two_vec3)[this.__ptr] = this; }
    else { this.__ptr = _two_ValueCurve_two_vec3__construct_1(ensureFloat32(/*keys*/a0), /*keys*/a0.length); getCache(ValueCurve_two_vec3)[this.__ptr] = this; }
};
ValueCurve_two_vec3.prototype = Object.create(WrapperObject.prototype);
ValueCurve_two_vec3.prototype.constructor = ValueCurve_two_vec3;
ValueCurve_two_vec3.prototype.__class = ValueCurve_two_vec3;
ValueCurve_two_vec3.__cache = {};
Module['ValueCurve_two_vec3'] = ValueCurve_two_vec3;
Object.defineProperty(ValueCurve_two_vec3.prototype, "keys", {
    get: function() {
        return _two_ValueCurve_two_vec3__get_keys(this.__ptr);
    }});
ValueCurve_two_vec3.prototype["__destroy"] = ValueCurve_two_vec3.prototype.__destroy = function() {
    _two_ValueCurve_two_vec3__destroy(this.__ptr);
};
// ValueCurve<two::quat>
function ValueCurve_two_quat() {
    
    this.__ptr = _two_ValueCurve_two_quat__construct_0(); getCache(ValueCurve_two_quat)[this.__ptr] = this;
};
ValueCurve_two_quat.prototype = Object.create(WrapperObject.prototype);
ValueCurve_two_quat.prototype.constructor = ValueCurve_two_quat;
ValueCurve_two_quat.prototype.__class = ValueCurve_two_quat;
ValueCurve_two_quat.__cache = {};
Module['ValueCurve_two_quat'] = ValueCurve_two_quat;
ValueCurve_two_quat.prototype["__destroy"] = ValueCurve_two_quat.prototype.__destroy = function() {
    _two_ValueCurve_two_quat__destroy(this.__ptr);
};
// ValueCurve<two::Colour>
function ValueCurve_two_Colour(a0) {
    if (a0 === undefined) {  }
    else {  }
    if (a0 === undefined) { this.__ptr = _two_ValueCurve_two_Colour__construct_0(); getCache(ValueCurve_two_Colour)[this.__ptr] = this; }
    else { this.__ptr = _two_ValueCurve_two_Colour__construct_1(ensureFloat32(/*keys*/a0), /*keys*/a0.length); getCache(ValueCurve_two_Colour)[this.__ptr] = this; }
};
ValueCurve_two_Colour.prototype = Object.create(WrapperObject.prototype);
ValueCurve_two_Colour.prototype.constructor = ValueCurve_two_Colour;
ValueCurve_two_Colour.prototype.__class = ValueCurve_two_Colour;
ValueCurve_two_Colour.__cache = {};
Module['ValueCurve_two_Colour'] = ValueCurve_two_Colour;
Object.defineProperty(ValueCurve_two_Colour.prototype, "keys", {
    get: function() {
        return _two_ValueCurve_two_Colour__get_keys(this.__ptr);
    }});
ValueCurve_two_Colour.prototype["__destroy"] = ValueCurve_two_Colour.prototype.__destroy = function() {
    _two_ValueCurve_two_Colour__destroy(this.__ptr);
};
// ValueTrack<two::vec3>
function ValueTrack_two_vec3(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'number') throw Error('ValueTrack<T>(0:mode): expected integer'); if (!checkClass(a1, ValueCurve_two_vec3)) throw Error('ValueTrack<T>(1:curve): expected ValueCurve<two::vec3>'); if (!checkClass(a2, ValueCurve_two_vec3)) throw Error('ValueTrack<T>(2:min_curve): expected ValueCurve<two::vec3>'); if (!checkClass(a3, ValueCurve_two_vec3)) throw Error('ValueTrack<T>(3:max_curve): expected ValueCurve<two::vec3>'); }
    if (a0 === undefined) { this.__ptr = _two_ValueTrack_two_vec3__construct_0(); getCache(ValueTrack_two_vec3)[this.__ptr] = this; }
    else { this.__ptr = _two_ValueTrack_two_vec3__construct_4(/*mode*/a0, /*curve*/a1.__ptr, /*min_curve*/a2.__ptr, /*max_curve*/a3.__ptr); getCache(ValueTrack_two_vec3)[this.__ptr] = this; }
};
ValueTrack_two_vec3.prototype = Object.create(WrapperObject.prototype);
ValueTrack_two_vec3.prototype.constructor = ValueTrack_two_vec3;
ValueTrack_two_vec3.prototype.__class = ValueTrack_two_vec3;
ValueTrack_two_vec3.__cache = {};
Module['ValueTrack_two_vec3'] = ValueTrack_two_vec3;
Object.defineProperty(ValueTrack_two_vec3.prototype, "mode", {
    get: function() {
        return _two_ValueTrack_two_vec3__get_mode(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ValueTrack<two::vec3>.mode: expected integer');
        _two_ValueTrack_two_vec3__set_mode(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_two_vec3.prototype, "value", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_vec3__get_value(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('ValueTrack<two::vec3>.value: expected v3<float>');
        _two_ValueTrack_two_vec3__set_value(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_vec3.prototype, "min", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_vec3__get_min(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('ValueTrack<two::vec3>.min: expected v3<float>');
        _two_ValueTrack_two_vec3__set_min(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_vec3.prototype, "max", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_vec3__get_max(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('ValueTrack<two::vec3>.max: expected v3<float>');
        _two_ValueTrack_two_vec3__set_max(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_vec3.prototype, "curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_vec3__get_curve(this.__ptr), ValueCurve_two_vec3);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_two_vec3)) throw Error('ValueTrack<two::vec3>.curve: expected ValueCurve<two::vec3>');
        _two_ValueTrack_two_vec3__set_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_vec3.prototype, "min_curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_vec3__get_min_curve(this.__ptr), ValueCurve_two_vec3);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_two_vec3)) throw Error('ValueTrack<two::vec3>.min_curve: expected ValueCurve<two::vec3>');
        _two_ValueTrack_two_vec3__set_min_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_vec3.prototype, "max_curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_vec3__get_max_curve(this.__ptr), ValueCurve_two_vec3);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_two_vec3)) throw Error('ValueTrack<two::vec3>.max_curve: expected ValueCurve<two::vec3>');
        _two_ValueTrack_two_vec3__set_max_curve(this.__ptr, value.__ptr);
    }
});
ValueTrack_two_vec3.prototype["__destroy"] = ValueTrack_two_vec3.prototype.__destroy = function() {
    _two_ValueTrack_two_vec3__destroy(this.__ptr);
};
// ValueTrack<two::quat>
function ValueTrack_two_quat(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'number') throw Error('ValueTrack<T>(0:mode): expected integer'); if (!checkClass(a1, ValueCurve_two_quat)) throw Error('ValueTrack<T>(1:curve): expected ValueCurve<two::quat>'); if (!checkClass(a2, ValueCurve_two_quat)) throw Error('ValueTrack<T>(2:min_curve): expected ValueCurve<two::quat>'); if (!checkClass(a3, ValueCurve_two_quat)) throw Error('ValueTrack<T>(3:max_curve): expected ValueCurve<two::quat>'); }
    if (a0 === undefined) { this.__ptr = _two_ValueTrack_two_quat__construct_0(); getCache(ValueTrack_two_quat)[this.__ptr] = this; }
    else { this.__ptr = _two_ValueTrack_two_quat__construct_4(/*mode*/a0, /*curve*/a1.__ptr, /*min_curve*/a2.__ptr, /*max_curve*/a3.__ptr); getCache(ValueTrack_two_quat)[this.__ptr] = this; }
};
ValueTrack_two_quat.prototype = Object.create(WrapperObject.prototype);
ValueTrack_two_quat.prototype.constructor = ValueTrack_two_quat;
ValueTrack_two_quat.prototype.__class = ValueTrack_two_quat;
ValueTrack_two_quat.__cache = {};
Module['ValueTrack_two_quat'] = ValueTrack_two_quat;
Object.defineProperty(ValueTrack_two_quat.prototype, "mode", {
    get: function() {
        return _two_ValueTrack_two_quat__get_mode(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ValueTrack<two::quat>.mode: expected integer');
        _two_ValueTrack_two_quat__set_mode(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_two_quat.prototype, "value", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_quat__get_value(this.__ptr), quat);
    },
    set: function(value) {
        if (!checkClass(value, quat)) throw Error('ValueTrack<two::quat>.value: expected quat');
        _two_ValueTrack_two_quat__set_value(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_quat.prototype, "min", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_quat__get_min(this.__ptr), quat);
    },
    set: function(value) {
        if (!checkClass(value, quat)) throw Error('ValueTrack<two::quat>.min: expected quat');
        _two_ValueTrack_two_quat__set_min(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_quat.prototype, "max", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_quat__get_max(this.__ptr), quat);
    },
    set: function(value) {
        if (!checkClass(value, quat)) throw Error('ValueTrack<two::quat>.max: expected quat');
        _two_ValueTrack_two_quat__set_max(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_quat.prototype, "curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_quat__get_curve(this.__ptr), ValueCurve_two_quat);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_two_quat)) throw Error('ValueTrack<two::quat>.curve: expected ValueCurve<two::quat>');
        _two_ValueTrack_two_quat__set_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_quat.prototype, "min_curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_quat__get_min_curve(this.__ptr), ValueCurve_two_quat);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_two_quat)) throw Error('ValueTrack<two::quat>.min_curve: expected ValueCurve<two::quat>');
        _two_ValueTrack_two_quat__set_min_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_quat.prototype, "max_curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_quat__get_max_curve(this.__ptr), ValueCurve_two_quat);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_two_quat)) throw Error('ValueTrack<two::quat>.max_curve: expected ValueCurve<two::quat>');
        _two_ValueTrack_two_quat__set_max_curve(this.__ptr, value.__ptr);
    }
});
ValueTrack_two_quat.prototype["__destroy"] = ValueTrack_two_quat.prototype.__destroy = function() {
    _two_ValueTrack_two_quat__destroy(this.__ptr);
};
// ValueTrack<float>
function ValueTrack_float(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'number') throw Error('ValueTrack<T>(0:mode): expected integer'); if (!checkClass(a1, ValueCurve_float)) throw Error('ValueTrack<T>(1:curve): expected ValueCurve<float>'); if (!checkClass(a2, ValueCurve_float)) throw Error('ValueTrack<T>(2:min_curve): expected ValueCurve<float>'); if (!checkClass(a3, ValueCurve_float)) throw Error('ValueTrack<T>(3:max_curve): expected ValueCurve<float>'); }
    if (a0 === undefined) { this.__ptr = _two_ValueTrack_float__construct_0(); getCache(ValueTrack_float)[this.__ptr] = this; }
    else { this.__ptr = _two_ValueTrack_float__construct_4(/*mode*/a0, /*curve*/a1.__ptr, /*min_curve*/a2.__ptr, /*max_curve*/a3.__ptr); getCache(ValueTrack_float)[this.__ptr] = this; }
};
ValueTrack_float.prototype = Object.create(WrapperObject.prototype);
ValueTrack_float.prototype.constructor = ValueTrack_float;
ValueTrack_float.prototype.__class = ValueTrack_float;
ValueTrack_float.__cache = {};
Module['ValueTrack_float'] = ValueTrack_float;
Object.defineProperty(ValueTrack_float.prototype, "mode", {
    get: function() {
        return _two_ValueTrack_float__get_mode(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ValueTrack<float>.mode: expected integer');
        _two_ValueTrack_float__set_mode(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "value", {
    get: function() {
        return _two_ValueTrack_float__get_value(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ValueTrack<float>.value: expected number');
        _two_ValueTrack_float__set_value(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "min", {
    get: function() {
        return _two_ValueTrack_float__get_min(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ValueTrack<float>.min: expected number');
        _two_ValueTrack_float__set_min(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "max", {
    get: function() {
        return _two_ValueTrack_float__get_max(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ValueTrack<float>.max: expected number');
        _two_ValueTrack_float__set_max(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_float__get_curve(this.__ptr), ValueCurve_float);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_float)) throw Error('ValueTrack<float>.curve: expected ValueCurve<float>');
        _two_ValueTrack_float__set_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "min_curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_float__get_min_curve(this.__ptr), ValueCurve_float);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_float)) throw Error('ValueTrack<float>.min_curve: expected ValueCurve<float>');
        _two_ValueTrack_float__set_min_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_float.prototype, "max_curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_float__get_max_curve(this.__ptr), ValueCurve_float);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_float)) throw Error('ValueTrack<float>.max_curve: expected ValueCurve<float>');
        _two_ValueTrack_float__set_max_curve(this.__ptr, value.__ptr);
    }
});
ValueTrack_float.prototype["__destroy"] = ValueTrack_float.prototype.__destroy = function() {
    _two_ValueTrack_float__destroy(this.__ptr);
};
// ValueTrack<uint32_t>
function ValueTrack_uint32_t(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'number') throw Error('ValueTrack<T>(0:mode): expected integer'); if (!checkClass(a1, ValueCurve_uint32_t)) throw Error('ValueTrack<T>(1:curve): expected ValueCurve<uint32_t>'); if (!checkClass(a2, ValueCurve_uint32_t)) throw Error('ValueTrack<T>(2:min_curve): expected ValueCurve<uint32_t>'); if (!checkClass(a3, ValueCurve_uint32_t)) throw Error('ValueTrack<T>(3:max_curve): expected ValueCurve<uint32_t>'); }
    if (a0 === undefined) { this.__ptr = _two_ValueTrack_uint32_t__construct_0(); getCache(ValueTrack_uint32_t)[this.__ptr] = this; }
    else { this.__ptr = _two_ValueTrack_uint32_t__construct_4(/*mode*/a0, /*curve*/a1.__ptr, /*min_curve*/a2.__ptr, /*max_curve*/a3.__ptr); getCache(ValueTrack_uint32_t)[this.__ptr] = this; }
};
ValueTrack_uint32_t.prototype = Object.create(WrapperObject.prototype);
ValueTrack_uint32_t.prototype.constructor = ValueTrack_uint32_t;
ValueTrack_uint32_t.prototype.__class = ValueTrack_uint32_t;
ValueTrack_uint32_t.__cache = {};
Module['ValueTrack_uint32_t'] = ValueTrack_uint32_t;
Object.defineProperty(ValueTrack_uint32_t.prototype, "mode", {
    get: function() {
        return _two_ValueTrack_uint32_t__get_mode(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ValueTrack<uint32_t>.mode: expected integer');
        _two_ValueTrack_uint32_t__set_mode(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "value", {
    get: function() {
        return _two_ValueTrack_uint32_t__get_value(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ValueTrack<uint32_t>.value: expected integer');
        _two_ValueTrack_uint32_t__set_value(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "min", {
    get: function() {
        return _two_ValueTrack_uint32_t__get_min(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ValueTrack<uint32_t>.min: expected integer');
        _two_ValueTrack_uint32_t__set_min(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "max", {
    get: function() {
        return _two_ValueTrack_uint32_t__get_max(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ValueTrack<uint32_t>.max: expected integer');
        _two_ValueTrack_uint32_t__set_max(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_uint32_t__get_curve(this.__ptr), ValueCurve_uint32_t);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_uint32_t)) throw Error('ValueTrack<uint32_t>.curve: expected ValueCurve<uint32_t>');
        _two_ValueTrack_uint32_t__set_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "min_curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_uint32_t__get_min_curve(this.__ptr), ValueCurve_uint32_t);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_uint32_t)) throw Error('ValueTrack<uint32_t>.min_curve: expected ValueCurve<uint32_t>');
        _two_ValueTrack_uint32_t__set_min_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_uint32_t.prototype, "max_curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_uint32_t__get_max_curve(this.__ptr), ValueCurve_uint32_t);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_uint32_t)) throw Error('ValueTrack<uint32_t>.max_curve: expected ValueCurve<uint32_t>');
        _two_ValueTrack_uint32_t__set_max_curve(this.__ptr, value.__ptr);
    }
});
ValueTrack_uint32_t.prototype["__destroy"] = ValueTrack_uint32_t.prototype.__destroy = function() {
    _two_ValueTrack_uint32_t__destroy(this.__ptr);
};
// ValueTrack<two::Colour>
function ValueTrack_two_Colour(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'number') throw Error('ValueTrack<T>(0:mode): expected integer'); if (!checkClass(a1, ValueCurve_two_Colour)) throw Error('ValueTrack<T>(1:curve): expected ValueCurve<two::Colour>'); if (!checkClass(a2, ValueCurve_two_Colour)) throw Error('ValueTrack<T>(2:min_curve): expected ValueCurve<two::Colour>'); if (!checkClass(a3, ValueCurve_two_Colour)) throw Error('ValueTrack<T>(3:max_curve): expected ValueCurve<two::Colour>'); }
    if (a0 === undefined) { this.__ptr = _two_ValueTrack_two_Colour__construct_0(); getCache(ValueTrack_two_Colour)[this.__ptr] = this; }
    else { this.__ptr = _two_ValueTrack_two_Colour__construct_4(/*mode*/a0, /*curve*/a1.__ptr, /*min_curve*/a2.__ptr, /*max_curve*/a3.__ptr); getCache(ValueTrack_two_Colour)[this.__ptr] = this; }
};
ValueTrack_two_Colour.prototype = Object.create(WrapperObject.prototype);
ValueTrack_two_Colour.prototype.constructor = ValueTrack_two_Colour;
ValueTrack_two_Colour.prototype.__class = ValueTrack_two_Colour;
ValueTrack_two_Colour.__cache = {};
Module['ValueTrack_two_Colour'] = ValueTrack_two_Colour;
Object.defineProperty(ValueTrack_two_Colour.prototype, "mode", {
    get: function() {
        return _two_ValueTrack_two_Colour__get_mode(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ValueTrack<two::Colour>.mode: expected integer');
        _two_ValueTrack_two_Colour__set_mode(this.__ptr, value);
    }
});
Object.defineProperty(ValueTrack_two_Colour.prototype, "value", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_Colour__get_value(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('ValueTrack<two::Colour>.value: expected Colour');
        _two_ValueTrack_two_Colour__set_value(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_Colour.prototype, "min", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_Colour__get_min(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('ValueTrack<two::Colour>.min: expected Colour');
        _two_ValueTrack_two_Colour__set_min(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_Colour.prototype, "max", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_Colour__get_max(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('ValueTrack<two::Colour>.max: expected Colour');
        _two_ValueTrack_two_Colour__set_max(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_Colour.prototype, "curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_Colour__get_curve(this.__ptr), ValueCurve_two_Colour);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_two_Colour)) throw Error('ValueTrack<two::Colour>.curve: expected ValueCurve<two::Colour>');
        _two_ValueTrack_two_Colour__set_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_Colour.prototype, "min_curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_Colour__get_min_curve(this.__ptr), ValueCurve_two_Colour);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_two_Colour)) throw Error('ValueTrack<two::Colour>.min_curve: expected ValueCurve<two::Colour>');
        _two_ValueTrack_two_Colour__set_min_curve(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ValueTrack_two_Colour.prototype, "max_curve", {
    get: function() {
        return wrapPointer(_two_ValueTrack_two_Colour__get_max_curve(this.__ptr), ValueCurve_two_Colour);
    },
    set: function(value) {
        if (!checkClass(value, ValueCurve_two_Colour)) throw Error('ValueTrack<two::Colour>.max_curve: expected ValueCurve<two::Colour>');
        _two_ValueTrack_two_Colour__set_max_curve(this.__ptr, value.__ptr);
    }
});
ValueTrack_two_Colour.prototype["__destroy"] = ValueTrack_two_Colour.prototype.__destroy = function() {
    _two_ValueTrack_two_Colour__destroy(this.__ptr);
};
// Image
function Image() {
    
    this.__ptr = _two_Image__construct_0(); getCache(Image)[this.__ptr] = this;
};
Image.prototype = Object.create(WrapperObject.prototype);
Image.prototype.constructor = Image;
Image.prototype.__class = Image;
Image.__cache = {};
Module['Image'] = Image;
Object.defineProperty(Image.prototype, "d_name", {
    get: function() {
        return UTF8ToString(_two_Image__get_d_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Image.d_name: expected string');
        _two_Image__set_d_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Image.prototype, "d_path", {
    get: function() {
        return UTF8ToString(_two_Image__get_d_path(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Image.d_path: expected string');
        _two_Image__set_d_path(this.__ptr, ensureString(value));
    }
});
Image.prototype["__destroy"] = Image.prototype.__destroy = function() {
    _two_Image__destroy(this.__ptr);
};
// Palette
function Palette(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) {  }
    else { if (typeof a0 !== 'number') throw Error('Palette(0:spectrum): expected integer'); if (typeof a1 !== 'number') throw Error('Palette(1:steps): expected integer'); }
    if (a0 === undefined) { this.__ptr = _two_Palette__construct_0(); getCache(Palette)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_Palette__construct_1(ensureFloat32(/*colours*/a0), /*colours*/a0.length); getCache(Palette)[this.__ptr] = this; }
    else { this.__ptr = _two_Palette__construct_2(/*spectrum*/a0, /*steps*/a1); getCache(Palette)[this.__ptr] = this; }
};
Palette.prototype = Object.create(WrapperObject.prototype);
Palette.prototype.constructor = Palette;
Palette.prototype.__class = Palette;
Palette.__cache = {};
Module['Palette'] = Palette;
Palette.prototype["__destroy"] = Palette.prototype.__destroy = function() {
    _two_Palette__destroy(this.__ptr);
};
// Image256
function Image256(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (!checkClass(a0, v2_uint)) throw Error('Image256(0:size): expected v2<uint>'); }
    else { if (!checkClass(a0, v2_uint)) throw Error('Image256(0:size): expected v2<uint>'); if (!checkClass(a1, Palette)) throw Error('Image256(1:palette): expected Palette'); }
    if (a0 === undefined) { this.__ptr = _two_Image256__construct_0(); getCache(Image256)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_Image256__construct_1(/*size*/a0.__ptr); getCache(Image256)[this.__ptr] = this; }
    else { this.__ptr = _two_Image256__construct_2(/*size*/a0.__ptr, /*palette*/a1.__ptr); getCache(Image256)[this.__ptr] = this; }
};
Image256.prototype = Object.create(WrapperObject.prototype);
Image256.prototype.constructor = Image256;
Image256.prototype.__class = Image256;
Image256.__cache = {};
Module['Image256'] = Image256;
Object.defineProperty(Image256.prototype, "pixels", {
    get: function() {
        return _two_Image256__get_pixels(this.__ptr);
    }});
Object.defineProperty(Image256.prototype, "size", {
    get: function() {
        return wrapPointer(_two_Image256__get_size(this.__ptr), v2_uint);
    },
    set: function(value) {
        if (!checkClass(value, v2_uint)) throw Error('Image256.size: expected v2<uint>');
        _two_Image256__set_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Image256.prototype, "palette", {
    get: function() {
        return wrapPointer(_two_Image256__get_palette(this.__ptr), Palette);
    },
    set: function(value) {
        if (!checkClass(value, Palette)) throw Error('Image256.palette: expected Palette');
        _two_Image256__set_palette(this.__ptr, value.__ptr);
    }
});
Image256.prototype["__destroy"] = Image256.prototype.__destroy = function() {
    _two_Image256__destroy(this.__ptr);
};
// ImageAtlas
function ImageAtlas() { throw "cannot construct a ImageAtlas, no constructor in IDL" }
ImageAtlas.prototype = Object.create(WrapperObject.prototype);
ImageAtlas.prototype.constructor = ImageAtlas;
ImageAtlas.prototype.__class = ImageAtlas;
ImageAtlas.__cache = {};
Module['ImageAtlas'] = ImageAtlas;
ImageAtlas.prototype["__destroy"] = ImageAtlas.prototype.__destroy = function() {
    _two_ImageAtlas__destroy(this.__ptr);
};
// TextureAtlas
function TextureAtlas() { throw "cannot construct a TextureAtlas, no constructor in IDL" }
TextureAtlas.prototype = Object.create(ImageAtlas.prototype);
TextureAtlas.prototype.constructor = TextureAtlas;
TextureAtlas.prototype.__class = TextureAtlas;
TextureAtlas.__base = ImageAtlas;
TextureAtlas.__cache = {};
Module['TextureAtlas'] = TextureAtlas;
TextureAtlas.prototype["__destroy"] = TextureAtlas.prototype.__destroy = function() {
    _two_TextureAtlas__destroy(this.__ptr);
};
// Sprite
function Sprite() { throw "cannot construct a Sprite, no constructor in IDL" }
Sprite.prototype = Object.create(Image.prototype);
Sprite.prototype.constructor = Sprite;
Sprite.prototype.__class = Sprite;
Sprite.__base = Image;
Sprite.__cache = {};
Module['Sprite'] = Sprite;
Sprite.prototype["__destroy"] = Sprite.prototype.__destroy = function() {
    _two_Sprite__destroy(this.__ptr);
};
// SpriteAtlas
function SpriteAtlas() { throw "cannot construct a SpriteAtlas, no constructor in IDL" }
SpriteAtlas.prototype = Object.create(ImageAtlas.prototype);
SpriteAtlas.prototype.constructor = SpriteAtlas;
SpriteAtlas.prototype.__class = SpriteAtlas;
SpriteAtlas.__base = ImageAtlas;
SpriteAtlas.__cache = {};
Module['SpriteAtlas'] = SpriteAtlas;
SpriteAtlas.prototype["__destroy"] = SpriteAtlas.prototype.__destroy = function() {
    _two_SpriteAtlas__destroy(this.__ptr);
};
// Range<two::vec3>
function Range_two_vec3() {
    
    this.__ptr = _two_Range_two_vec3__construct_0(); getCache(Range_two_vec3)[this.__ptr] = this;
};
Range_two_vec3.prototype = Object.create(WrapperObject.prototype);
Range_two_vec3.prototype.constructor = Range_two_vec3;
Range_two_vec3.prototype.__class = Range_two_vec3;
Range_two_vec3.__cache = {};
Module['Range_two_vec3'] = Range_two_vec3;
Object.defineProperty(Range_two_vec3.prototype, "min", {
    get: function() {
        return wrapPointer(_two_Range_two_vec3__get_min(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Range<two::vec3>.min: expected v3<float>');
        _two_Range_two_vec3__set_min(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Range_two_vec3.prototype, "max", {
    get: function() {
        return wrapPointer(_two_Range_two_vec3__get_max(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Range<two::vec3>.max: expected v3<float>');
        _two_Range_two_vec3__set_max(this.__ptr, value.__ptr);
    }
});
Range_two_vec3.prototype["__destroy"] = Range_two_vec3.prototype.__destroy = function() {
    _two_Range_two_vec3__destroy(this.__ptr);
};
// Range<two::quat>
function Range_two_quat() {
    
    this.__ptr = _two_Range_two_quat__construct_0(); getCache(Range_two_quat)[this.__ptr] = this;
};
Range_two_quat.prototype = Object.create(WrapperObject.prototype);
Range_two_quat.prototype.constructor = Range_two_quat;
Range_two_quat.prototype.__class = Range_two_quat;
Range_two_quat.__cache = {};
Module['Range_two_quat'] = Range_two_quat;
Object.defineProperty(Range_two_quat.prototype, "min", {
    get: function() {
        return wrapPointer(_two_Range_two_quat__get_min(this.__ptr), quat);
    },
    set: function(value) {
        if (!checkClass(value, quat)) throw Error('Range<two::quat>.min: expected quat');
        _two_Range_two_quat__set_min(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Range_two_quat.prototype, "max", {
    get: function() {
        return wrapPointer(_two_Range_two_quat__get_max(this.__ptr), quat);
    },
    set: function(value) {
        if (!checkClass(value, quat)) throw Error('Range<two::quat>.max: expected quat');
        _two_Range_two_quat__set_max(this.__ptr, value.__ptr);
    }
});
Range_two_quat.prototype["__destroy"] = Range_two_quat.prototype.__destroy = function() {
    _two_Range_two_quat__destroy(this.__ptr);
};
// Range<float>
function Range_float() {
    
    this.__ptr = _two_Range_float__construct_0(); getCache(Range_float)[this.__ptr] = this;
};
Range_float.prototype = Object.create(WrapperObject.prototype);
Range_float.prototype.constructor = Range_float;
Range_float.prototype.__class = Range_float;
Range_float.__cache = {};
Module['Range_float'] = Range_float;
Object.defineProperty(Range_float.prototype, "min", {
    get: function() {
        return _two_Range_float__get_min(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Range<float>.min: expected number');
        _two_Range_float__set_min(this.__ptr, value);
    }
});
Object.defineProperty(Range_float.prototype, "max", {
    get: function() {
        return _two_Range_float__get_max(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Range<float>.max: expected number');
        _two_Range_float__set_max(this.__ptr, value);
    }
});
Range_float.prototype["__destroy"] = Range_float.prototype.__destroy = function() {
    _two_Range_float__destroy(this.__ptr);
};
// Range<uint32_t>
function Range_uint32_t() {
    
    this.__ptr = _two_Range_uint32_t__construct_0(); getCache(Range_uint32_t)[this.__ptr] = this;
};
Range_uint32_t.prototype = Object.create(WrapperObject.prototype);
Range_uint32_t.prototype.constructor = Range_uint32_t;
Range_uint32_t.prototype.__class = Range_uint32_t;
Range_uint32_t.__cache = {};
Module['Range_uint32_t'] = Range_uint32_t;
Object.defineProperty(Range_uint32_t.prototype, "min", {
    get: function() {
        return _two_Range_uint32_t__get_min(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Range<uint32_t>.min: expected integer');
        _two_Range_uint32_t__set_min(this.__ptr, value);
    }
});
Object.defineProperty(Range_uint32_t.prototype, "max", {
    get: function() {
        return _two_Range_uint32_t__get_max(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Range<uint32_t>.max: expected integer');
        _two_Range_uint32_t__set_max(this.__ptr, value);
    }
});
Range_uint32_t.prototype["__destroy"] = Range_uint32_t.prototype.__destroy = function() {
    _two_Range_uint32_t__destroy(this.__ptr);
};
// Range<two::Colour>
function Range_two_Colour() {
    
    this.__ptr = _two_Range_two_Colour__construct_0(); getCache(Range_two_Colour)[this.__ptr] = this;
};
Range_two_Colour.prototype = Object.create(WrapperObject.prototype);
Range_two_Colour.prototype.constructor = Range_two_Colour;
Range_two_Colour.prototype.__class = Range_two_Colour;
Range_two_Colour.__cache = {};
Module['Range_two_Colour'] = Range_two_Colour;
Object.defineProperty(Range_two_Colour.prototype, "min", {
    get: function() {
        return wrapPointer(_two_Range_two_Colour__get_min(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('Range<two::Colour>.min: expected Colour');
        _two_Range_two_Colour__set_min(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Range_two_Colour.prototype, "max", {
    get: function() {
        return wrapPointer(_two_Range_two_Colour__get_max(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('Range<two::Colour>.max: expected Colour');
        _two_Range_two_Colour__set_max(this.__ptr, value.__ptr);
    }
});
Range_two_Colour.prototype["__destroy"] = Range_two_Colour.prototype.__destroy = function() {
    _two_Range_two_Colour__destroy(this.__ptr);
};
// StatDef<int>
function StatDef_int() {
    
    this.__ptr = _two_StatDef_int__construct_0(); getCache(StatDef_int)[this.__ptr] = this;
};
StatDef_int.prototype = Object.create(WrapperObject.prototype);
StatDef_int.prototype.constructor = StatDef_int;
StatDef_int.prototype.__class = StatDef_int;
StatDef_int.__cache = {};
Module['StatDef_int'] = StatDef_int;
Object.defineProperty(StatDef_int.prototype, "min", {
    get: function() {
        return _two_StatDef_int__get_min(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('StatDef<int>.min: expected integer');
        _two_StatDef_int__set_min(this.__ptr, value);
    }
});
Object.defineProperty(StatDef_int.prototype, "max", {
    get: function() {
        return _two_StatDef_int__get_max(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('StatDef<int>.max: expected integer');
        _two_StatDef_int__set_max(this.__ptr, value);
    }
});
Object.defineProperty(StatDef_int.prototype, "step", {
    get: function() {
        return _two_StatDef_int__get_step(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('StatDef<int>.step: expected integer');
        _two_StatDef_int__set_step(this.__ptr, value);
    }
});
StatDef_int.prototype["__destroy"] = StatDef_int.prototype.__destroy = function() {
    _two_StatDef_int__destroy(this.__ptr);
};
// StatDef<float>
function StatDef_float() {
    
    this.__ptr = _two_StatDef_float__construct_0(); getCache(StatDef_float)[this.__ptr] = this;
};
StatDef_float.prototype = Object.create(WrapperObject.prototype);
StatDef_float.prototype.constructor = StatDef_float;
StatDef_float.prototype.__class = StatDef_float;
StatDef_float.__cache = {};
Module['StatDef_float'] = StatDef_float;
Object.defineProperty(StatDef_float.prototype, "min", {
    get: function() {
        return _two_StatDef_float__get_min(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('StatDef<float>.min: expected number');
        _two_StatDef_float__set_min(this.__ptr, value);
    }
});
Object.defineProperty(StatDef_float.prototype, "max", {
    get: function() {
        return _two_StatDef_float__get_max(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('StatDef<float>.max: expected number');
        _two_StatDef_float__set_max(this.__ptr, value);
    }
});
Object.defineProperty(StatDef_float.prototype, "step", {
    get: function() {
        return _two_StatDef_float__get_step(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('StatDef<float>.step: expected number');
        _two_StatDef_float__set_step(this.__ptr, value);
    }
});
StatDef_float.prototype["__destroy"] = StatDef_float.prototype.__destroy = function() {
    _two_StatDef_float__destroy(this.__ptr);
};
// Time
function Time(a0) {
    if (typeof a0 !== 'number') throw Error('Time(0:value): expected number');
    this.__ptr = _two_Time__construct_1(/*value*/a0); getCache(Time)[this.__ptr] = this;
};
Time.prototype = Object.create(WrapperObject.prototype);
Time.prototype.constructor = Time;
Time.prototype.__class = Time;
Time.__cache = {};
Module['Time'] = Time;
Object.defineProperty(Time.prototype, "value", {
    get: function() {
        return _two_Time__get_value(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Time.value: expected number');
        _two_Time__set_value(this.__ptr, value);
    }
});
Time.prototype["__destroy"] = Time.prototype.__destroy = function() {
    _two_Time__destroy(this.__ptr);
};
// TimeSpan
function TimeSpan(a0, a1) {
    if (!checkClass(a0, Time)) throw Error('TimeSpan(0:s): expected Time'); if (!checkClass(a1, Time)) throw Error('TimeSpan(1:e): expected Time');
    this.__ptr = _two_TimeSpan__construct_2(/*s*/a0.__ptr, /*e*/a1.__ptr); getCache(TimeSpan)[this.__ptr] = this;
};
TimeSpan.prototype = Object.create(WrapperObject.prototype);
TimeSpan.prototype.constructor = TimeSpan;
TimeSpan.prototype.__class = TimeSpan;
TimeSpan.__cache = {};
Module['TimeSpan'] = TimeSpan;
Object.defineProperty(TimeSpan.prototype, "start", {
    get: function() {
        return wrapPointer(_two_TimeSpan__get_start(this.__ptr), Time);
    },
    set: function(value) {
        if (!checkClass(value, Time)) throw Error('TimeSpan.start: expected Time');
        _two_TimeSpan__set_start(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(TimeSpan.prototype, "end", {
    get: function() {
        return wrapPointer(_two_TimeSpan__get_end(this.__ptr), Time);
    },
    set: function(value) {
        if (!checkClass(value, Time)) throw Error('TimeSpan.end: expected Time');
        _two_TimeSpan__set_end(this.__ptr, value.__ptr);
    }
});
TimeSpan.prototype["__destroy"] = TimeSpan.prototype.__destroy = function() {
    _two_TimeSpan__destroy(this.__ptr);
};
Module['rgb'] = function(a0) {
    if (typeof a0 !== 'number') throw Error('rgb(0:colour): expected integer');
    return wrapPointer(_two_rgb_1(/*colour*/a0), Colour);
};
Module['rgba'] = function(a0) {
    if (typeof a0 !== 'number') throw Error('rgba(0:colour): expected integer');
    return wrapPointer(_two_rgba_1(/*colour*/a0), Colour);
};
Module['abgr'] = function(a0) {
    if (typeof a0 !== 'number') throw Error('abgr(0:colour): expected integer');
    return wrapPointer(_two_abgr_1(/*colour*/a0), Colour);
};
Module['hsv'] = function(a0, a1, a2) {
    if (typeof a0 !== 'number') throw Error('hsv(0:h): expected number'); if (typeof a1 !== 'number') throw Error('hsv(1:s): expected number'); if (typeof a2 !== 'number') throw Error('hsv(2:v): expected number');
    return wrapPointer(_two_hsv_3(/*h*/a0, /*s*/a1, /*v*/a2), Colour);
};
Module['hsl'] = function(a0, a1, a2) {
    if (typeof a0 !== 'number') throw Error('hsl(0:h): expected number'); if (typeof a1 !== 'number') throw Error('hsl(1:s): expected number'); if (typeof a2 !== 'number') throw Error('hsl(2:l): expected number');
    return wrapPointer(_two_hsl_3(/*h*/a0, /*s*/a1, /*l*/a2), Colour);
};
Module['to_rgba'] = function(a0) {
    if (!checkClass(a0, Colour)) throw Error('to_rgba(0:colour): expected Colour');
    return _two_to_rgba_1(/*colour*/a0.__ptr);
};
Module['to_abgr'] = function(a0, a1, a2, a3) {
    if (a1 === undefined) { if (!checkClass(a0, Colour)) throw Error('to_abgr(0:colour): expected Colour'); }
    else if (a3 === undefined) { if (typeof a0 !== 'number') throw Error('to_abgr(0:r): expected number'); if (typeof a1 !== 'number') throw Error('to_abgr(1:g): expected number'); if (typeof a2 !== 'number') throw Error('to_abgr(2:b): expected number'); }
    else { if (typeof a0 !== 'number') throw Error('to_abgr(0:r): expected number'); if (typeof a1 !== 'number') throw Error('to_abgr(1:g): expected number'); if (typeof a2 !== 'number') throw Error('to_abgr(2:b): expected number'); if (typeof a3 !== 'number') throw Error('to_abgr(3:a): expected number'); }
    if (a1 === undefined) { return _two_to_abgr_1(/*colour*/a0.__ptr); }
    else if (a3 === undefined) { return _two_to_abgr_3(/*r*/a0, /*g*/a1, /*b*/a2); }
    else { return _two_to_abgr_4(/*r*/a0, /*g*/a1, /*b*/a2, /*a*/a3); }
};
Module['to_linear'] = function(a0) {
    if (!checkClass(a0, Colour)) throw Error('to_linear(0:colour): expected Colour');
    return wrapPointer(_two_to_linear_1(/*colour*/a0.__ptr), Colour);
};
Module['to_gamma'] = function(a0) {
    if (!checkClass(a0, Colour)) throw Error('to_gamma(0:colour): expected Colour');
    return wrapPointer(_two_to_gamma_1(/*colour*/a0.__ptr), Colour);
};
Module['to_srgb'] = function(a0) {
    if (!checkClass(a0, Colour)) throw Error('to_srgb(0:colour): expected Colour');
    return wrapPointer(_two_to_srgb_1(/*colour*/a0.__ptr), Colour);
};
Module['to_hsl'] = function(a0, a1, a2) {
    if (a1 === undefined) { if (!checkClass(a0, Colour)) throw Error('to_hsl(0:colour): expected Colour'); }
    else { if (typeof a0 !== 'number') throw Error('to_hsl(0:r): expected number'); if (typeof a1 !== 'number') throw Error('to_hsl(1:g): expected number'); if (typeof a2 !== 'number') throw Error('to_hsl(2:b): expected number'); }
    if (a1 === undefined) { return wrapPointer(_two_to_hsl_1(/*colour*/a0.__ptr), ColourHSL); }
    else { return wrapPointer(_two_to_hsl_3(/*r*/a0, /*g*/a1, /*b*/a2), ColourHSL); }
};
Module['to_hsla'] = function(a0) {
    if (!checkClass(a0, Colour)) throw Error('to_hsla(0:colour): expected Colour');
    return wrapPointer(_two_to_hsla_1(/*colour*/a0.__ptr), ColourHSL);
};
Module['sinf'] = function(a0) {
    if (typeof a0 !== 'number') throw Error('sinf(0:a): expected number');
    return _sinf_1(/*a*/a0);
};
Module['cosf'] = function(a0) {
    if (typeof a0 !== 'number') throw Error('cosf(0:a): expected number');
    return _cosf_1(/*a*/a0);
};
Module['sin'] = function(a0) {
    if (typeof a0 !== 'number') throw Error('sin(0:a): expected number');
    return _sin_1(/*a*/a0);
};
Module['cos'] = function(a0) {
    if (typeof a0 !== 'number') throw Error('cos(0:a): expected number');
    return _cos_1(/*a*/a0);
};
Module['add_float'] = function(a0, a1) {
    if (typeof a0 !== 'number') throw Error('add<float>(0:a): expected number'); if (typeof a1 !== 'number') throw Error('add<float>(1:b): expected number');
    return _two_add_float_2(/*a*/a0, /*b*/a1);
};
Module['subtract_float'] = function(a0, a1) {
    if (typeof a0 !== 'number') throw Error('subtract<float>(0:a): expected number'); if (typeof a1 !== 'number') throw Error('subtract<float>(1:b): expected number');
    return _two_subtract_float_2(/*a*/a0, /*b*/a1);
};
Module['multiply_float'] = function(a0, a1) {
    if (typeof a0 !== 'number') throw Error('multiply<float>(0:a): expected number'); if (typeof a1 !== 'number') throw Error('multiply<float>(1:b): expected number');
    return _two_multiply_float_2(/*a*/a0, /*b*/a1);
};
Module['divide_float'] = function(a0, a1) {
    if (typeof a0 !== 'number') throw Error('divide<float>(0:a): expected number'); if (typeof a1 !== 'number') throw Error('divide<float>(1:b): expected number');
    return _two_divide_float_2(/*a*/a0, /*b*/a1);
};
Module['nsinf'] = function(a0) {
    if (typeof a0 !== 'number') throw Error('nsinf(0:a): expected number');
    return _two_nsinf_1(/*a*/a0);
};
Module['ncosf'] = function(a0) {
    if (typeof a0 !== 'number') throw Error('ncosf(0:a): expected number');
    return _two_ncosf_1(/*a*/a0);
};
Module['nsin'] = function(a0) {
    if (typeof a0 !== 'number') throw Error('nsin(0:a): expected number');
    return _two_nsin_1(/*a*/a0);
};
Module['ncos'] = function(a0) {
    if (typeof a0 !== 'number') throw Error('ncos(0:a): expected number');
    return _two_ncos_1(/*a*/a0);
};
Module['add_two_v3_float'] = function(a0, a1) {
    if (!checkClass(a0, v3_float)) throw Error('add<two::v3<float>>(0:a): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('add<two::v3<float>>(1:b): expected v3<float>');
    return wrapPointer(_two_add_two_v3_float_2(/*a*/a0.__ptr, /*b*/a1.__ptr), v3_float);
};
Module['subtract_two_v3_float'] = function(a0, a1) {
    if (!checkClass(a0, v3_float)) throw Error('subtract<two::v3<float>>(0:a): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('subtract<two::v3<float>>(1:b): expected v3<float>');
    return wrapPointer(_two_subtract_two_v3_float_2(/*a*/a0.__ptr, /*b*/a1.__ptr), v3_float);
};
Module['multiply_two_v3_float'] = function(a0, a1) {
    if (!checkClass(a0, v3_float)) throw Error('multiply<two::v3<float>>(0:a): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('multiply<two::v3<float>>(1:b): expected v3<float>');
    return wrapPointer(_two_multiply_two_v3_float_2(/*a*/a0.__ptr, /*b*/a1.__ptr), v3_float);
};
Module['divide_two_v3_float'] = function(a0, a1) {
    if (!checkClass(a0, v3_float)) throw Error('divide<two::v3<float>>(0:a): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('divide<two::v3<float>>(1:b): expected v3<float>');
    return wrapPointer(_two_divide_two_v3_float_2(/*a*/a0.__ptr, /*b*/a1.__ptr), v3_float);
};
Module['look_dir'] = function(a0, a1) {
    if (a1 === undefined) { if (!checkClass(a0, v3_float)) throw Error('look_dir(0:direction): expected v3<float>'); }
    else { if (!checkClass(a0, v3_float)) throw Error('look_dir(0:direction): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('look_dir(1:forward): expected v3<float>'); }
    if (a1 === undefined) { return wrapPointer(_two_look_dir_1(/*direction*/a0.__ptr), quat); }
    else { return wrapPointer(_two_look_dir_2(/*direction*/a0.__ptr, /*forward*/a1.__ptr), quat); }
};
Module['look_at'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, v3_float)) throw Error('look_at(0:eye): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('look_at(1:target): expected v3<float>'); }
    else { if (!checkClass(a0, v3_float)) throw Error('look_at(0:eye): expected v3<float>'); if (!checkClass(a1, v3_float)) throw Error('look_at(1:target): expected v3<float>'); if (!checkClass(a2, v3_float)) throw Error('look_at(2:forward): expected v3<float>'); }
    if (a2 === undefined) { return wrapPointer(_two_look_at_2(/*eye*/a0.__ptr, /*target*/a1.__ptr), quat); }
    else { return wrapPointer(_two_look_at_3(/*eye*/a0.__ptr, /*target*/a1.__ptr, /*forward*/a2.__ptr), quat); }
};
Module['grid_center'] = function(a0, a1) {
    if (!checkClass(a0, v3_uint)) throw Error('grid_center(0:coord): expected v3<uint>'); if (!checkClass(a1, v3_float)) throw Error('grid_center(1:cell_size): expected v3<float>');
    return wrapPointer(_two_grid_center_2(/*coord*/a0.__ptr, /*cell_size*/a1.__ptr), v3_float);
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
        mat3.prototype.__type = _two_mat3__type();
        mat4.prototype.__type = _two_mat4__type();
        quat.prototype.__type = _two_quat__type();
        Transform.prototype.__type = _two_Transform__type();
        ColourHSL.prototype.__type = _two_ColourHSL__type();
        Colour.prototype.__type = _two_Colour__type();
        Image.prototype.__type = _two_Image__type();
        Palette.prototype.__type = _two_Palette__type();
        Image256.prototype.__type = _two_Image256__type();
        ImageAtlas.prototype.__type = _two_ImageAtlas__type();
        TextureAtlas.prototype.__type = _two_TextureAtlas__type();
        Sprite.prototype.__type = _two_Sprite__type();
        SpriteAtlas.prototype.__type = _two_SpriteAtlas__type();
        Time.prototype.__type = _two_Time__type();
        TimeSpan.prototype.__type = _two_TimeSpan__type();
        // Axis
        Module['Axis'] = Module['Axis'] || {};
        Module['Axis']['X'] = _two_Axis_X();
        Module['Axis']['Y'] = _two_Axis_Y();
        Module['Axis']['Z'] = _two_Axis_Z();
        Module['Axis']['None'] = _two_Axis_None();
        Module['Axis']['Count'] = _two_Axis_Count();
        // Axes
        Module['Axes'] = Module['Axes'] || {};
        Module['Axes']['None'] = _two_Axes_None();
        Module['Axes']['X'] = _two_Axes_X();
        Module['Axes']['Y'] = _two_Axes_Y();
        Module['Axes']['Z'] = _two_Axes_Z();
        // SignedAxis
        Module['SignedAxis'] = Module['SignedAxis'] || {};
        Module['SignedAxis']['PlusX'] = _two_SignedAxis_PlusX();
        Module['SignedAxis']['MinusX'] = _two_SignedAxis_MinusX();
        Module['SignedAxis']['PlusY'] = _two_SignedAxis_PlusY();
        Module['SignedAxis']['MinusY'] = _two_SignedAxis_MinusY();
        Module['SignedAxis']['PlusZ'] = _two_SignedAxis_PlusZ();
        Module['SignedAxis']['MinusZ'] = _two_SignedAxis_MinusZ();
        Module['SignedAxis']['Count'] = _two_SignedAxis_Count();
        // Side
        Module['Side'] = Module['Side'] || {};
        Module['Side']['Right'] = _two_Side_Right();
        Module['Side']['Left'] = _two_Side_Left();
        Module['Side']['Up'] = _two_Side_Up();
        Module['Side']['Down'] = _two_Side_Down();
        Module['Side']['Back'] = _two_Side_Back();
        Module['Side']['Front'] = _two_Side_Front();
        Module['Side']['Count'] = _two_Side_Count();
        // Clockwise
        Module['CLOCKWISE'] = _two_Clockwise_CLOCKWISE();
        Module['ANTI_CLOCKWISE'] = _two_Clockwise_ANTI_CLOCKWISE();
        // TrackMode
        Module['TrackMode'] = Module['TrackMode'] || {};
        Module['TrackMode']['Constant'] = _two_TrackMode_Constant();
        Module['TrackMode']['ConstantRandom'] = _two_TrackMode_ConstantRandom();
        Module['TrackMode']['Curve'] = _two_TrackMode_Curve();
        Module['TrackMode']['CurveRandom'] = _two_TrackMode_CurveRandom();
        // Spectrum
        Module['Spectrum'] = Module['Spectrum'] || {};
        Module['Spectrum']['Value'] = _two_Spectrum_Value();
        Module['Spectrum']['Hue'] = _two_Spectrum_Hue();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
