
// Bindings utilities
function WrapperObject() {
}
// Tile
function Tile() {
    var self = this.ptr;
    this.ptr = _mud_Tile_Tile_0(self); getCache(Tile)[this.ptr] = this;
};
Tile.prototype = Object.create(WrapperObject.prototype);
Tile.prototype.constructor = Tile;
Tile.prototype.__class__ = Tile;
Tile.__cache__ = {};
Module['Tile'] = Tile;
Object.defineProperty(Tile.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Tile__get_index(self);
    },
    set: function(index) {
        var self = this.ptr;
        /* index <uint32_t> [] */
        _mud_Tile__set_index(self, index);
    }
});
Object.defineProperty(Tile.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Tile__get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _mud_Tile__set_name(self, name);
    }
});
Object.defineProperty(Tile.prototype, "symmetry", {
    get: function() {
        var self = this.ptr;
        return _mud_Tile__get_symmetry(self);
    },
    set: function(symmetry) {
        var self = this.ptr;
        /* symmetry <char> [] */
        _mud_Tile__set_symmetry(self, symmetry);
    }
});
Object.defineProperty(Tile.prototype, "cardinality", {
    get: function() {
        var self = this.ptr;
        return _mud_Tile__get_cardinality(self);
    },
    set: function(cardinality) {
        var self = this.ptr;
        /* cardinality <int> [] */
        _mud_Tile__set_cardinality(self, cardinality);
    }
});
Object.defineProperty(Tile.prototype, "profile", {
    get: function() {
        var self = this.ptr;
        return _mud_Tile__get_profile(self);
    },
    set: function(profile) {
        var self = this.ptr;
        /* profile <int> [] */
        _mud_Tile__set_profile(self, profile);
    }
});
Tile.prototype["__destroy__"] = Tile.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Tile__destroy(self);
};
// Tileset
function Tileset() {
    var self = this.ptr;
    this.ptr = _mud_Tileset_Tileset_0(self); getCache(Tileset)[this.ptr] = this;
};
Tileset.prototype = Object.create(WrapperObject.prototype);
Tileset.prototype.constructor = Tileset;
Tileset.prototype.__class__ = Tileset;
Tileset.__cache__ = {};
Module['Tileset'] = Tileset;
Object.defineProperty(Tileset.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Tileset__get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _mud_Tileset__set_name(self, name);
    }
});
Object.defineProperty(Tileset.prototype, "tile_size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Tileset__get_tile_size(self), mud::vec3);
    },
    set: function(tile_size) {
        var self = this.ptr;
        /* tile_size <vec3> [] */
        tile_size = tile_size.ptr;
        _mud_Tileset__set_tile_size(self, tile_size);
    }
});
Object.defineProperty(Tileset.prototype, "tile_scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Tileset__get_tile_scale(self), mud::vec3);
    },
    set: function(tile_scale) {
        var self = this.ptr;
        /* tile_scale <vec3> [] */
        tile_scale = tile_scale.ptr;
        _mud_Tileset__set_tile_scale(self, tile_scale);
    }
});
Object.defineProperty(Tileset.prototype, "nutiles", {
    get: function() {
        var self = this.ptr;
        return _mud_Tileset__get_nutiles(self);
    },
    set: function(nutiles) {
        var self = this.ptr;
        /* nutiles <uint16_t> [] */
        _mud_Tileset__set_nutiles(self, nutiles);
    }
});
Tileset.prototype["__destroy__"] = Tileset.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Tileset__destroy(self);
};
// Wave
function Wave() {
    var self = this.ptr;
    this.ptr = _mud_Wave_Wave_0(self); getCache(Wave)[this.ptr] = this;
};
Wave.prototype = Object.create(WrapperObject.prototype);
Wave.prototype.constructor = Wave;
Wave.prototype.__class__ = Wave;
Wave.__cache__ = {};
Module['Wave'] = Wave;
Wave.prototype["solve"] = Wave.prototype.solve = function(limit) {
    /* limit <size_t> [] */
    return _mud_Wave_solve_1(limit);
};
Wave.prototype["__destroy__"] = Wave.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Wave__destroy(self);
};
// TileWave
function TileWave(tileset, width, height, depth, periodic) {
    var self = this.ptr;
    /* tileset <WaveTileset> [] */
    tileset = tileset.ptr;
    /* width <uint16_t> [] */
    /* height <uint16_t> [] */
    /* depth <uint16_t> [] */
    /* periodic <bool> [] */
    this.ptr = _mud_TileWave_TileWave_5(self, tileset, width, height, depth, periodic); getCache(TileWave)[this.ptr] = this;
};
TileWave.prototype = Object.create(WrapperObject.prototype);
TileWave.prototype.constructor = TileWave;
TileWave.prototype.__class__ = TileWave;
TileWave.__cache__ = {};
Module['TileWave'] = TileWave;
TileWave.prototype["__destroy__"] = TileWave.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TileWave__destroy(self);
};
// WaveTileset
function WaveTileset() {
    var self = this.ptr;
    this.ptr = _mud_WaveTileset_WaveTileset_0(self); getCache(WaveTileset)[this.ptr] = this;
};
WaveTileset.prototype = Object.create(WrapperObject.prototype);
WaveTileset.prototype.constructor = WaveTileset;
WaveTileset.prototype.__class__ = WaveTileset;
WaveTileset.__cache__ = {};
Module['WaveTileset'] = WaveTileset;
WaveTileset.prototype["__destroy__"] = WaveTileset.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_WaveTileset__destroy(self);
};

(function() {
    function setupEnums() {
        // Result
        Module['kSuccess'] = _mud_Result_kSuccess();
        Module['kFail'] = _mud_Result_kFail();
        Module['kUnfinished'] = _mud_Result_kUnfinished();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
