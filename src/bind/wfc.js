// Tile
function Tile() {
    this.ptr = _mud_Tile__construct_0(); this.type = Tile; getCache(Tile)[this.ptr] = this;
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
    set: function(value) {
        var self = this.ptr;
        _mud_Tile__set_index(self, value);
    }
});
Object.defineProperty(Tile.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Tile__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Tile__set_name(self, ensureString(value));
    }
});
Object.defineProperty(Tile.prototype, "symmetry", {
    get: function() {
        var self = this.ptr;
        return _mud_Tile__get_symmetry(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Tile__set_symmetry(self, value);
    }
});
Object.defineProperty(Tile.prototype, "cardinality", {
    get: function() {
        var self = this.ptr;
        return _mud_Tile__get_cardinality(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Tile__set_cardinality(self, value);
    }
});
Object.defineProperty(Tile.prototype, "profile", {
    get: function() {
        var self = this.ptr;
        return _mud_Tile__get_profile(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Tile__set_profile(self, value);
    }
});
Tile.prototype["__destroy__"] = Tile.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Tile__destroy(self);
};
// Tileset
function Tileset() {
    this.ptr = _mud_Tileset__construct_0(); this.type = Tileset; getCache(Tileset)[this.ptr] = this;
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
    set: function(value) {
        var self = this.ptr;
        _mud_Tileset__set_name(self, ensureString(value));
    }
});
Object.defineProperty(Tileset.prototype, "tile_size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Tileset__get_tile_size(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Tileset__set_tile_size(self, value.ptr);
    }
});
Object.defineProperty(Tileset.prototype, "tile_scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Tileset__get_tile_scale(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Tileset__set_tile_scale(self, value.ptr);
    }
});
Object.defineProperty(Tileset.prototype, "nutiles", {
    get: function() {
        var self = this.ptr;
        return _mud_Tileset__get_nutiles(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Tileset__set_nutiles(self, value);
    }
});
Tileset.prototype["__destroy__"] = Tileset.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Tileset__destroy(self);
};
// Wave
function Wave() {
    this.ptr = _mud_Wave__construct_0(); this.type = Wave; getCache(Wave)[this.ptr] = this;
};
Wave.prototype = Object.create(WrapperObject.prototype);
Wave.prototype.constructor = Wave;
Wave.prototype.__class__ = Wave;
Wave.__cache__ = {};
Module['Wave'] = Wave;
Wave.prototype["solve"] = Wave.prototype.solve = function(self, a0) {
    var self = this.ptr;
    return _mud_Wave_solve_1(self, /*limit*/a0);
};
Wave.prototype["__destroy__"] = Wave.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Wave__destroy(self);
};
// TileWave
function TileWave(a0, a1, a2, a3, a4) {
    this.ptr = _mud_TileWave__construct_5(/*tileset*/a0.ptr, /*width*/a1, /*height*/a2, /*depth*/a3, /*periodic*/a4); this.type = TileWave; getCache(TileWave)[this.ptr] = this;
};
TileWave.prototype = Object.create(Wave.prototype);
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
    this.ptr = _mud_WaveTileset__construct_0(); this.type = WaveTileset; getCache(WaveTileset)[this.ptr] = this;
};
WaveTileset.prototype = Object.create(Tileset.prototype);
WaveTileset.prototype.constructor = WaveTileset;
WaveTileset.prototype.__class__ = WaveTileset;
WaveTileset.__cache__ = {};
Module['WaveTileset'] = WaveTileset;
WaveTileset.prototype["__destroy__"] = WaveTileset.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_WaveTileset__destroy(self);
};
Module['parse_json_tileset'] = function(a0, a1, a2) {
    var self = this.ptr;
    ensureCache.prepare();
    _mud_parse_json_tileset_3(ensureString(/*path*/a0), ensureString(/*subset*/a1), /*outputTileset*/a2.ptr);
};
Module['parse_json_wave_tileset'] = function(a0, a1, a2) {
    var self = this.ptr;
    ensureCache.prepare();
    _mud_parse_json_wave_tileset_3(ensureString(/*path*/a0), ensureString(/*subset*/a1), /*outputTileset*/a2.ptr);
};

(function() {
    function setup() {
        Tile.__type__ = _mud_Tile__type();
        Tileset.__type__ = _mud_Tileset__type();
        Wave.__type__ = _mud_Wave__type();
        TileWave.__type__ = _mud_TileWave__type();
        WaveTileset.__type__ = _mud_WaveTileset__type();
        // Result
        Module['kSuccess'] = _mud_Result_kSuccess();
        Module['kFail'] = _mud_Result_kFail();
        Module['kUnfinished'] = _mud_Result_kUnfinished();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
