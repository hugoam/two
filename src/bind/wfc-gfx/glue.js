
// Bindings utilities
function WrapperObject() {
}
// TileModel
function TileModel() {
    var self = this.ptr;
    this.ptr = _TileModel_TileModel_0(self); getCache(TileModel)[this.ptr] = this;
};
TileModel.prototype = Object.create(WrapperObject.prototype);
TileModel.prototype.constructor = TileModel;
TileModel.prototype.__class__ = TileModel;
TileModel.__cache__ = {};
Module['TileModel'] = TileModel;
TileModel.prototype["__destroy__"] = TileModel.prototype.__destroy__ = function() {
    var self = this.ptr;
    _TileModel___destroy__(self);
};
// WfcBlock
function WfcBlock(position, size, scale, tileset, auto_solve) {
    var self = this.ptr;
    /* position <vec3> [] */
    /* size <uvec3> [] */
    /* scale <vec3> [] */
    /* tileset <WaveTileset> [] */
    /* auto_solve <bool> [] */
    if (position === undefined) { this.ptr = _WfcBlock_WfcBlock_0(self); getCache(WfcBlock)[this.ptr] = this; return; }
    if (auto_solve === undefined) { this.ptr = _WfcBlock_WfcBlock_4(self, position, size, scale, tileset); getCache(WfcBlock)[this.ptr] = this; return; }
    this.ptr = _WfcBlock_WfcBlock_5(self, position, size, scale, tileset, auto_solve); getCache(WfcBlock)[this.ptr] = this;
};
WfcBlock.prototype = Object.create(WrapperObject.prototype);
WfcBlock.prototype.constructor = WfcBlock;
WfcBlock.prototype.__class__ = WfcBlock;
WfcBlock.__cache__ = {};
Module['WfcBlock'] = WfcBlock;
WfcBlock.prototype["observe"] = WfcBlock.prototype.observe = function() {
    _WfcBlock_observe_0();
};
WfcBlock.prototype["propagate"] = WfcBlock.prototype.propagate = function() {
    _WfcBlock_propagate_0();
};
WfcBlock.prototype["reset"] = WfcBlock.prototype.reset = function() {
    _WfcBlock_reset_0();
};
WfcBlock.prototype["solve"] = WfcBlock.prototype.solve = function(limit) {
    /* limit <size_t> [] */
    if (limit === undefined) { _WfcBlock_solve_0(); return; }
    _WfcBlock_solve_1(limit);
};
WfcBlock.prototype["update"] = WfcBlock.prototype.update = function(wave) {
    /* wave <Wave> [] */
    _WfcBlock_update_1(wave);
};
Object.defineProperty(WfcBlock.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return _WfcBlock_get_position(self);
    },
    set: function(position) {
        var self = this.ptr;
        /* position <vec3> [] */
        _WfcBlock_set_position(self, position);
    }
});
Object.defineProperty(WfcBlock.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return _WfcBlock_get_size(self);
    },
    set: function(size) {
        var self = this.ptr;
        /* size <uvec3> [] */
        _WfcBlock_set_size(self, size);
    }
});
Object.defineProperty(WfcBlock.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return _WfcBlock_get_scale(self);
    },
    set: function(scale) {
        var self = this.ptr;
        /* scale <vec3> [] */
        _WfcBlock_set_scale(self, scale);
    }
});
Object.defineProperty(WfcBlock.prototype, "aabb", {
    get: function() {
        var self = this.ptr;
        return _WfcBlock_get_aabb(self);
    },
    set: function(aabb) {
        var self = this.ptr;
        /* aabb <Aabb> [] */
        _WfcBlock_set_aabb(self, aabb);
    }
});
WfcBlock.prototype["__destroy__"] = WfcBlock.prototype.__destroy__ = function() {
    var self = this.ptr;
    _WfcBlock___destroy__(self);
};

(function() {
    function setupEnums() {
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
