// TileModel
function TileModel() {
    this.ptr = _mud_TileModel__construct_0(); getCache(TileModel)[this.ptr] = this;
    this.type = TileModel;
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
function WfcBlock(position, size, scale, tileset, auto_solve) {
    /* position <mud::vec3> [] */
    if (typeof position !== "undefined" && position !== null) { position = position.ptr; }
    /* size <mud::uvec3> [] */
    if (typeof size !== "undefined" && size !== null) { size = size.ptr; }
    /* scale <mud::vec3> [] */
    if (typeof scale !== "undefined" && scale !== null) { scale = scale.ptr; }
    /* tileset <mud::WaveTileset> [] */
    if (typeof tileset !== "undefined" && tileset !== null) { tileset = tileset.ptr; }
    /* auto_solve <bool> [] */
    if (position === undefined) { this.ptr = _mud_WfcBlock__construct_0(); getCache(WfcBlock)[this.ptr] = this; return; }
    if (auto_solve === undefined) { this.ptr = _mud_WfcBlock__construct_4(position, size, scale, tileset); getCache(WfcBlock)[this.ptr] = this; return; }
    this.ptr = _mud_WfcBlock__construct_5(position, size, scale, tileset, auto_solve); getCache(WfcBlock)[this.ptr] = this;
    this.type = WfcBlock;
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
WfcBlock.prototype["solve"] = WfcBlock.prototype.solve = function(self, limit) {
    var self = this.ptr;
    /* limit <size_t> [] */
    if (limit === undefined) { _mud_WfcBlock_solve_0(self); return; }
    _mud_WfcBlock_solve_1(self, limit);
};
WfcBlock.prototype["update"] = WfcBlock.prototype.update = function(self, wave) {
    var self = this.ptr;
    /* wave <mud::Wave> [] */
    wave = wave.ptr;
    _mud_WfcBlock_update_1(self, wave);
};
Object.defineProperty(WfcBlock.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_WfcBlock__get_position(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_WfcBlock__set_position(self, value);
    }
});
Object.defineProperty(WfcBlock.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_WfcBlock__get_size(self), v3_stl_uint);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::uvec3> [] */
        value = value.ptr;
        _mud_WfcBlock__set_size(self, value);
    }
});
Object.defineProperty(WfcBlock.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_WfcBlock__get_scale(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::vec3> [] */
        value = value.ptr;
        _mud_WfcBlock__set_scale(self, value);
    }
});
Object.defineProperty(WfcBlock.prototype, "aabb", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_WfcBlock__get_aabb(self), Aabb);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mud::Aabb> [] */
        value = value.ptr;
        _mud_WfcBlock__set_aabb(self, value);
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
