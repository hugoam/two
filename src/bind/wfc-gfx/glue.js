
// Bindings utilities
function WrapperObject() {
}
// TileModel
function TileModel() {
    var self = this.ptr;
    this.ptr = _mud_TileModel_TileModel_0(self); getCache(TileModel)[this.ptr] = this;
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
    var self = this.ptr;
    /* position <vec3> [] */
    position = position.ptr;
    /* size <uvec3> [] */
    size = size.ptr;
    /* scale <vec3> [] */
    scale = scale.ptr;
    /* tileset <WaveTileset> [] */
    tileset = tileset.ptr;
    /* auto_solve <bool> [] */
    if (position === undefined) { this.ptr = _mud_WfcBlock_WfcBlock_0(self); getCache(WfcBlock)[this.ptr] = this; return; }
    if (auto_solve === undefined) { this.ptr = _mud_WfcBlock_WfcBlock_4(self, position, size, scale, tileset); getCache(WfcBlock)[this.ptr] = this; return; }
    this.ptr = _mud_WfcBlock_WfcBlock_5(self, position, size, scale, tileset, auto_solve); getCache(WfcBlock)[this.ptr] = this;
};
WfcBlock.prototype = Object.create(WrapperObject.prototype);
WfcBlock.prototype.constructor = WfcBlock;
WfcBlock.prototype.__class__ = WfcBlock;
WfcBlock.__cache__ = {};
Module['WfcBlock'] = WfcBlock;
WfcBlock.prototype["observe"] = WfcBlock.prototype.observe = function() {
    _mud_WfcBlock_observe_0();
};
WfcBlock.prototype["propagate"] = WfcBlock.prototype.propagate = function() {
    _mud_WfcBlock_propagate_0();
};
WfcBlock.prototype["reset"] = WfcBlock.prototype.reset = function() {
    _mud_WfcBlock_reset_0();
};
WfcBlock.prototype["solve"] = WfcBlock.prototype.solve = function(limit) {
    /* limit <size_t> [] */
    if (limit === undefined) { _mud_WfcBlock_solve_0(); return; }
    _mud_WfcBlock_solve_1(limit);
};
WfcBlock.prototype["update"] = WfcBlock.prototype.update = function(wave) {
    /* wave <Wave> [] */
    wave = wave.ptr;
    _mud_WfcBlock_update_1(wave);
};
Object.defineProperty(WfcBlock.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_WfcBlock__get_position(self), mud::vec3);
    },
    set: function(position) {
        var self = this.ptr;
        /* position <vec3> [] */
        position = position.ptr;
        _mud_WfcBlock__set_position(self, position);
    }
});
Object.defineProperty(WfcBlock.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_WfcBlock__get_size(self), mud::uvec3);
    },
    set: function(size) {
        var self = this.ptr;
        /* size <uvec3> [] */
        size = size.ptr;
        _mud_WfcBlock__set_size(self, size);
    }
});
Object.defineProperty(WfcBlock.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_WfcBlock__get_scale(self), mud::vec3);
    },
    set: function(scale) {
        var self = this.ptr;
        /* scale <vec3> [] */
        scale = scale.ptr;
        _mud_WfcBlock__set_scale(self, scale);
    }
});
Object.defineProperty(WfcBlock.prototype, "aabb", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_WfcBlock__get_aabb(self), mud::Aabb);
    },
    set: function(aabb) {
        var self = this.ptr;
        /* aabb <Aabb> [] */
        aabb = aabb.ptr;
        _mud_WfcBlock__set_aabb(self, aabb);
    }
});
WfcBlock.prototype["__destroy__"] = WfcBlock.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_WfcBlock__destroy(self);
};

(function() {
    function setupEnums() {
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
