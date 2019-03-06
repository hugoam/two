// Tile
function Tile() {
    this.__ptr = _mud_Tile__construct_0(); this.__type = Tile.__type; getCache(Tile)[this.__ptr] = this;
};
Tile.prototype = Object.create(WrapperObject.prototype);
Tile.prototype.constructor = Tile;
Tile.prototype.__class = Tile;
Tile.__cache = {};
Module['Tile'] = Tile;
Object.defineProperty(Tile.prototype, "index", {
    get: function() {
        return _mud_Tile__get_index(this.__ptr);
    },
    set: function(value) {
        _mud_Tile__set_index(this.__ptr, value);
    }
});
Object.defineProperty(Tile.prototype, "name", {
    get: function() {
        return Pointer_stringify(_mud_Tile__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Tile__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Tile.prototype, "symmetry", {
    get: function() {
        return _mud_Tile__get_symmetry(this.__ptr);
    },
    set: function(value) {
        _mud_Tile__set_symmetry(this.__ptr, value);
    }
});
Object.defineProperty(Tile.prototype, "cardinality", {
    get: function() {
        return _mud_Tile__get_cardinality(this.__ptr);
    },
    set: function(value) {
        _mud_Tile__set_cardinality(this.__ptr, value);
    }
});
Object.defineProperty(Tile.prototype, "profile", {
    get: function() {
        return _mud_Tile__get_profile(this.__ptr);
    },
    set: function(value) {
        _mud_Tile__set_profile(this.__ptr, value);
    }
});
Tile.prototype["__destroy"] = Tile.prototype.__destroy = function() {
    _mud_Tile__destroy(this.__ptr);
};
// Tileset
function Tileset() {
    this.__ptr = _mud_Tileset__construct_0(); this.__type = Tileset.__type; getCache(Tileset)[this.__ptr] = this;
};
Tileset.prototype = Object.create(WrapperObject.prototype);
Tileset.prototype.constructor = Tileset;
Tileset.prototype.__class = Tileset;
Tileset.__cache = {};
Module['Tileset'] = Tileset;
Object.defineProperty(Tileset.prototype, "name", {
    get: function() {
        return Pointer_stringify(_mud_Tileset__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Tileset__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Tileset.prototype, "tile_size", {
    get: function() {
        return wrapPointer(_mud_Tileset__get_tile_size(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Tileset__set_tile_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Tileset.prototype, "tile_scale", {
    get: function() {
        return wrapPointer(_mud_Tileset__get_tile_scale(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Tileset__set_tile_scale(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Tileset.prototype, "nutiles", {
    get: function() {
        return _mud_Tileset__get_nutiles(this.__ptr);
    },
    set: function(value) {
        _mud_Tileset__set_nutiles(this.__ptr, value);
    }
});
Tileset.prototype["__destroy"] = Tileset.prototype.__destroy = function() {
    _mud_Tileset__destroy(this.__ptr);
};
// Wave
function Wave() {
    this.__ptr = _mud_Wave__construct_0(); this.__type = Wave.__type; getCache(Wave)[this.__ptr] = this;
};
Wave.prototype = Object.create(WrapperObject.prototype);
Wave.prototype.constructor = Wave;
Wave.prototype.__class = Wave;
Wave.__cache = {};
Module['Wave'] = Wave;
Wave.prototype["solve"] = Wave.prototype.solve = function(a0) {
    return _mud_Wave_solve_1(this.__ptr, /*limit*/a0);
};
Wave.prototype["__destroy"] = Wave.prototype.__destroy = function() {
    _mud_Wave__destroy(this.__ptr);
};
// TileWave
function TileWave(a0, a1, a2, a3, a4) {
    this.__ptr = _mud_TileWave__construct_5(/*tileset*/a0.__ptr, /*width*/a1, /*height*/a2, /*depth*/a3, /*periodic*/a4); this.__type = TileWave.__type; getCache(TileWave)[this.__ptr] = this;
};
TileWave.prototype = Object.create(Wave.prototype);
TileWave.prototype.constructor = TileWave;
TileWave.prototype.__class = TileWave;
TileWave.__cache = {};
Module['TileWave'] = TileWave;
TileWave.prototype["__destroy"] = TileWave.prototype.__destroy = function() {
    _mud_TileWave__destroy(this.__ptr);
};
// WaveTileset
function WaveTileset() {
    this.__ptr = _mud_WaveTileset__construct_0(); this.__type = WaveTileset.__type; getCache(WaveTileset)[this.__ptr] = this;
};
WaveTileset.prototype = Object.create(Tileset.prototype);
WaveTileset.prototype.constructor = WaveTileset;
WaveTileset.prototype.__class = WaveTileset;
WaveTileset.__cache = {};
Module['WaveTileset'] = WaveTileset;
WaveTileset.prototype["__destroy"] = WaveTileset.prototype.__destroy = function() {
    _mud_WaveTileset__destroy(this.__ptr);
};
Module['parse_json_tileset'] = function(a0, a1, a2) {
    ensureCache.prepare();
    _mud_parse_json_tileset_3(ensureString(/*path*/a0), ensureString(/*subset*/a1), /*outputTileset*/a2.__ptr);
};
Module['parse_json_wave_tileset'] = function(a0, a1, a2) {
    ensureCache.prepare();
    _mud_parse_json_wave_tileset_3(ensureString(/*path*/a0), ensureString(/*subset*/a1), /*outputTileset*/a2.__ptr);
};

(function() {
    function setup() {
        Tile.__type = _mud_Tile__type();
        Tileset.__type = _mud_Tileset__type();
        Wave.__type = _mud_Wave__type();
        TileWave.__type = _mud_TileWave__type();
        WaveTileset.__type = _mud_WaveTileset__type();
        // Result
        Module['kSuccess'] = _mud_Result_kSuccess();
        Module['kFail'] = _mud_Result_kFail();
        Module['kUnfinished'] = _mud_Result_kUnfinished();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
