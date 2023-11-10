// Tile
function Tile() {
    
    this.__ptr = _two_Tile__construct_0(); getCache(Tile)[this.__ptr] = this;
};
Tile.prototype = Object.create(WrapperObject.prototype);
Tile.prototype.constructor = Tile;
Tile.prototype.__class = Tile;
Tile.__cache = {};
Module['Tile'] = Tile;
Object.defineProperty(Tile.prototype, "index", {
    get: function() {
        return _two_Tile__get_index(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Tile.index: expected integer');
        _two_Tile__set_index(this.__ptr, value);
    }
});
Object.defineProperty(Tile.prototype, "name", {
    get: function() {
        return UTF8ToString(_two_Tile__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Tile.name: expected string');
        _two_Tile__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Tile.prototype, "symmetry", {
    get: function() {
        return _two_Tile__get_symmetry(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Tile.symmetry: expected integer');
        _two_Tile__set_symmetry(this.__ptr, value);
    }
});
Object.defineProperty(Tile.prototype, "cardinality", {
    get: function() {
        return _two_Tile__get_cardinality(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Tile.cardinality: expected integer');
        _two_Tile__set_cardinality(this.__ptr, value);
    }
});
Object.defineProperty(Tile.prototype, "profile", {
    get: function() {
        return _two_Tile__get_profile(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Tile.profile: expected integer');
        _two_Tile__set_profile(this.__ptr, value);
    }
});
Tile.prototype["__destroy"] = Tile.prototype.__destroy = function() {
    _two_Tile__destroy(this.__ptr);
};
// Tileset
function Tileset() {
    
    this.__ptr = _two_Tileset__construct_0(); getCache(Tileset)[this.__ptr] = this;
};
Tileset.prototype = Object.create(WrapperObject.prototype);
Tileset.prototype.constructor = Tileset;
Tileset.prototype.__class = Tileset;
Tileset.__cache = {};
Module['Tileset'] = Tileset;
Object.defineProperty(Tileset.prototype, "name", {
    get: function() {
        return UTF8ToString(_two_Tileset__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Tileset.name: expected string');
        _two_Tileset__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Tileset.prototype, "tile_size", {
    get: function() {
        return wrapPointer(_two_Tileset__get_tile_size(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Tileset.tile_size: expected v3<float>');
        _two_Tileset__set_tile_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Tileset.prototype, "tile_scale", {
    get: function() {
        return wrapPointer(_two_Tileset__get_tile_scale(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('Tileset.tile_scale: expected v3<float>');
        _two_Tileset__set_tile_scale(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Tileset.prototype, "nutiles", {
    get: function() {
        return _two_Tileset__get_nutiles(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Tileset.nutiles: expected integer');
        _two_Tileset__set_nutiles(this.__ptr, value);
    }
});
Tileset.prototype["__destroy"] = Tileset.prototype.__destroy = function() {
    _two_Tileset__destroy(this.__ptr);
};
// Wave
function Wave() {
    
    this.__ptr = _two_Wave__construct_0(); getCache(Wave)[this.__ptr] = this;
};
Wave.prototype = Object.create(WrapperObject.prototype);
Wave.prototype.constructor = Wave;
Wave.prototype.__class = Wave;
Wave.__cache = {};
Module['Wave'] = Wave;
Wave.prototype["solve"] = Wave.prototype.solve = function(a0) {
    if (typeof a0 !== 'number') throw Error('solve(0:limit): expected integer');
    return _two_Wave_solve_1(this.__ptr, /*limit*/a0);
};
Wave.prototype["__destroy"] = Wave.prototype.__destroy = function() {
    _two_Wave__destroy(this.__ptr);
};
// WaveTileset
function WaveTileset() {
    
    this.__ptr = _two_WaveTileset__construct_0(); getCache(WaveTileset)[this.__ptr] = this;
};
WaveTileset.prototype = Object.create(Tileset.prototype);
WaveTileset.prototype.constructor = WaveTileset;
WaveTileset.prototype.__class = WaveTileset;
WaveTileset.__base = Tileset;
WaveTileset.__cache = {};
Module['WaveTileset'] = WaveTileset;
WaveTileset.prototype["__destroy"] = WaveTileset.prototype.__destroy = function() {
    _two_WaveTileset__destroy(this.__ptr);
};
// TileWave
function TileWave(a0, a1, a2, a3, a4) {
    if (!checkClass(a0, WaveTileset)) throw Error('TileWave(0:tileset): expected WaveTileset'); if (typeof a1 !== 'number') throw Error('TileWave(1:width): expected integer'); if (typeof a2 !== 'number') throw Error('TileWave(2:height): expected integer'); if (typeof a3 !== 'number') throw Error('TileWave(3:depth): expected integer'); if (typeof a4 !== 'boolean') throw Error('TileWave(4:periodic): expected boolean');
    this.__ptr = _two_TileWave__construct_5(/*tileset*/a0.__ptr, /*width*/a1, /*height*/a2, /*depth*/a3, /*periodic*/a4); getCache(TileWave)[this.__ptr] = this;
};
TileWave.prototype = Object.create(Wave.prototype);
TileWave.prototype.constructor = TileWave;
TileWave.prototype.__class = TileWave;
TileWave.__base = Wave;
TileWave.__cache = {};
Module['TileWave'] = TileWave;
TileWave.prototype["__destroy"] = TileWave.prototype.__destroy = function() {
    _two_TileWave__destroy(this.__ptr);
};
Module['parse_json_tileset'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (typeof a0 !== 'string') throw Error('parse_json_tileset(0:path): expected string'); if (typeof a1 !== 'string') throw Error('parse_json_tileset(1:subset): expected string'); if (!checkClass(a2, Tileset)) throw Error('parse_json_tileset(2:outputTileset): expected Tileset');
    _two_parse_json_tileset_3(ensureString(/*path*/a0), ensureString(/*subset*/a1), /*outputTileset*/a2.__ptr);
};
Module['parse_json_wave_tileset'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (typeof a0 !== 'string') throw Error('parse_json_wave_tileset(0:path): expected string'); if (typeof a1 !== 'string') throw Error('parse_json_wave_tileset(1:subset): expected string'); if (!checkClass(a2, WaveTileset)) throw Error('parse_json_wave_tileset(2:outputTileset): expected WaveTileset');
    _two_parse_json_wave_tileset_3(ensureString(/*path*/a0), ensureString(/*subset*/a1), /*outputTileset*/a2.__ptr);
};

(function() {
    function setup() {
        Tile.prototype.__type = _two_Tile__type();
        Tileset.prototype.__type = _two_Tileset__type();
        Wave.prototype.__type = _two_Wave__type();
        WaveTileset.prototype.__type = _two_WaveTileset__type();
        TileWave.prototype.__type = _two_TileWave__type();
        // Result
        Module['kSuccess'] = _two_Result_kSuccess();
        Module['kFail'] = _two_Result_kFail();
        Module['kUnfinished'] = _two_Result_kUnfinished();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
