// TileModel
function TileModel() {
    this.ptr = _mud_TileModel__construct_0(); this.type = TileModel; getCache(TileModel)[this.ptr] = this;
};
TileModel.prototype = Object.create(WrapperObject.prototype);
TileModel.prototype.constructor = TileModel;
TileModel.prototype.__class__ = TileModel;
TileModel.__cache__ = {};
Module['TileModel'] = TileModel;
TileModel.prototype["__destroy__"] = TileModel.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TileModel__destroy(self);
};
// WfcBlock
function WfcBlock(a0, a1, a2, a3, a4) {
    if (a0 === undefined) { this.ptr = _mud_WfcBlock__construct_0(); this.type = WfcBlock; getCache(WfcBlock)[this.ptr] = this; return; }
    if (a4 === undefined) { this.ptr = _mud_WfcBlock__construct_4(/*position*/a0.ptr, /*size*/a1.ptr, /*scale*/a2.ptr, /*tileset*/a3.ptr); this.type = WfcBlock; getCache(WfcBlock)[this.ptr] = this; return; }
    this.ptr = _mud_WfcBlock__construct_5(/*position*/a0.ptr, /*size*/a1.ptr, /*scale*/a2.ptr, /*tileset*/a3.ptr, /*auto_solve*/a4); this.type = WfcBlock; getCache(WfcBlock)[this.ptr] = this;
};
WfcBlock.prototype = Object.create(WrapperObject.prototype);
WfcBlock.prototype.constructor = WfcBlock;
WfcBlock.prototype.__class__ = WfcBlock;
WfcBlock.__cache__ = {};
Module['WfcBlock'] = WfcBlock;
WfcBlock.prototype["reset"] = WfcBlock.prototype.reset = function(self) {
    var self = this.ptr;
    _mud_WfcBlock_reset_0(self);
};
WfcBlock.prototype["observe"] = WfcBlock.prototype.observe = function(self) {
    var self = this.ptr;
    _mud_WfcBlock_observe_0(self);
};
WfcBlock.prototype["propagate"] = WfcBlock.prototype.propagate = function(self) {
    var self = this.ptr;
    _mud_WfcBlock_propagate_0(self);
};
WfcBlock.prototype["solve"] = WfcBlock.prototype.solve = function(self, a0) {
    var self = this.ptr;
    if (a0 === undefined) { _mud_WfcBlock_solve_0(self); return; }
    _mud_WfcBlock_solve_1(self, /*limit*/a0);
};
WfcBlock.prototype["update"] = WfcBlock.prototype.update = function(self, a0) {
    var self = this.ptr;
    _mud_WfcBlock_update_1(self, /*wave*/a0.ptr);
};
Object.defineProperty(WfcBlock.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_WfcBlock__get_position(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_WfcBlock__set_position(self, value.ptr);
    }
});
Object.defineProperty(WfcBlock.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_WfcBlock__get_size(self), v3_uint);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_WfcBlock__set_size(self, value.ptr);
    }
});
Object.defineProperty(WfcBlock.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_WfcBlock__get_scale(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_WfcBlock__set_scale(self, value.ptr);
    }
});
Object.defineProperty(WfcBlock.prototype, "aabb", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_WfcBlock__get_aabb(self), Aabb);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_WfcBlock__set_aabb(self, value.ptr);
    }
});
WfcBlock.prototype["__destroy__"] = WfcBlock.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_WfcBlock__destroy(self);
};

(function() {
    function setup() {
        TileModel.__type__ = _mud_TileModel__type();
        WfcBlock.__type__ = _mud_WfcBlock__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
