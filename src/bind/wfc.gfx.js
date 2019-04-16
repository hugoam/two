// TileModel
function TileModel() {
    
    this.__ptr = _mud_TileModel__construct_0(); getCache(TileModel)[this.__ptr] = this;
};
TileModel.prototype = Object.create(WrapperObject.prototype);
TileModel.prototype.constructor = TileModel;
TileModel.prototype.__class = TileModel;
TileModel.__cache = {};
Module['TileModel'] = TileModel;
TileModel.prototype["__destroy"] = TileModel.prototype.__destroy = function() {
    _mud_TileModel__destroy(this.__ptr);
};
// WfcBlock
function WfcBlock(a0, a1, a2, a3, a4) {
    if (a0 === undefined) {  }
    else if (a4 === undefined) { if (!checkClass(a0, v3_float)) throw Error('WfcBlock(0:position): expected v3<float>'); if (!checkClass(a1, v3_uint)) throw Error('WfcBlock(1:size): expected v3<uint>'); if (!checkClass(a2, v3_float)) throw Error('WfcBlock(2:scale): expected v3<float>'); if (!checkClass(a3, WaveTileset)) throw Error('WfcBlock(3:tileset): expected WaveTileset'); }
    else { if (!checkClass(a0, v3_float)) throw Error('WfcBlock(0:position): expected v3<float>'); if (!checkClass(a1, v3_uint)) throw Error('WfcBlock(1:size): expected v3<uint>'); if (!checkClass(a2, v3_float)) throw Error('WfcBlock(2:scale): expected v3<float>'); if (!checkClass(a3, WaveTileset)) throw Error('WfcBlock(3:tileset): expected WaveTileset'); if (typeof a4 !== 'boolean') throw Error('WfcBlock(4:auto_solve): expected boolean'); }
    if (a0 === undefined) { this.__ptr = _mud_WfcBlock__construct_0(); getCache(WfcBlock)[this.__ptr] = this; }
    else if (a4 === undefined) { this.__ptr = _mud_WfcBlock__construct_4(/*position*/a0.__ptr, /*size*/a1.__ptr, /*scale*/a2.__ptr, /*tileset*/a3.__ptr); getCache(WfcBlock)[this.__ptr] = this; }
    else { this.__ptr = _mud_WfcBlock__construct_5(/*position*/a0.__ptr, /*size*/a1.__ptr, /*scale*/a2.__ptr, /*tileset*/a3.__ptr, /*auto_solve*/a4); getCache(WfcBlock)[this.__ptr] = this; }
};
WfcBlock.prototype = Object.create(WrapperObject.prototype);
WfcBlock.prototype.constructor = WfcBlock;
WfcBlock.prototype.__class = WfcBlock;
WfcBlock.__cache = {};
Module['WfcBlock'] = WfcBlock;
WfcBlock.prototype["reset"] = WfcBlock.prototype.reset = function() {
    
    _mud_WfcBlock_reset_0(this.__ptr);
};
WfcBlock.prototype["observe"] = WfcBlock.prototype.observe = function() {
    
    _mud_WfcBlock_observe_0(this.__ptr);
};
WfcBlock.prototype["propagate"] = WfcBlock.prototype.propagate = function() {
    
    _mud_WfcBlock_propagate_0(this.__ptr);
};
WfcBlock.prototype["solve"] = WfcBlock.prototype.solve = function(a0) {
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'number') throw Error('solve(0:limit): expected integer'); }
    if (a0 === undefined) { _mud_WfcBlock_solve_0(this.__ptr); }
    else { _mud_WfcBlock_solve_1(this.__ptr, /*limit*/a0); }
};
WfcBlock.prototype["update"] = WfcBlock.prototype.update = function(a0) {
    if (!checkClass(a0, Wave)) throw Error('update(0:wave): expected Wave');
    _mud_WfcBlock_update_1(this.__ptr, /*wave*/a0.__ptr);
};
Object.defineProperty(WfcBlock.prototype, "position", {
    get: function() {
        return wrapPointer(_mud_WfcBlock__get_position(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('WfcBlock.position: expected v3<float>');
        _mud_WfcBlock__set_position(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(WfcBlock.prototype, "size", {
    get: function() {
        return wrapPointer(_mud_WfcBlock__get_size(this.__ptr), v3_uint);
    },
    set: function(value) {
        if (!checkClass(value, v3_uint)) throw Error('WfcBlock.size: expected v3<uint>');
        _mud_WfcBlock__set_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(WfcBlock.prototype, "scale", {
    get: function() {
        return wrapPointer(_mud_WfcBlock__get_scale(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('WfcBlock.scale: expected v3<float>');
        _mud_WfcBlock__set_scale(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(WfcBlock.prototype, "aabb", {
    get: function() {
        return wrapPointer(_mud_WfcBlock__get_aabb(this.__ptr), Aabb);
    },
    set: function(value) {
        if (!checkClass(value, Aabb)) throw Error('WfcBlock.aabb: expected Aabb');
        _mud_WfcBlock__set_aabb(this.__ptr, value.__ptr);
    }
});
WfcBlock.prototype["__destroy"] = WfcBlock.prototype.__destroy = function() {
    _mud_WfcBlock__destroy(this.__ptr);
};

(function() {
    function setup() {
        TileModel.prototype.__type = _mud_TileModel__type();
        WfcBlock.prototype.__type = _mud_WfcBlock__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
