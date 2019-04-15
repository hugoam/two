// BgfxSystem
function BgfxSystem() { throw "cannot construct a BgfxSystem, no constructor in IDL" }
BgfxSystem.prototype = Object.create(RenderSystem.prototype);
BgfxSystem.prototype.constructor = BgfxSystem;
BgfxSystem.prototype.__class = BgfxSystem;
BgfxSystem.prototype.__base = RenderSystem;
BgfxSystem.__cache = {};
Module['BgfxSystem'] = BgfxSystem;
Object.defineProperty(BgfxSystem.prototype, "frame", {
    get: function() {
        return _mud_BgfxSystem__get_frame(this.__ptr);
    },
    set: function(value) {
        _mud_BgfxSystem__set_frame(this.__ptr, value);
    }
});
Object.defineProperty(BgfxSystem.prototype, "time", {
    get: function() {
        return _mud_BgfxSystem__get_time(this.__ptr);
    },
    set: function(value) {
        _mud_BgfxSystem__set_time(this.__ptr, value);
    }
});
Object.defineProperty(BgfxSystem.prototype, "frame_time", {
    get: function() {
        return _mud_BgfxSystem__get_frame_time(this.__ptr);
    },
    set: function(value) {
        _mud_BgfxSystem__set_frame_time(this.__ptr, value);
    }
});
Object.defineProperty(BgfxSystem.prototype, "delta_time", {
    get: function() {
        return _mud_BgfxSystem__get_delta_time(this.__ptr);
    },
    set: function(value) {
        _mud_BgfxSystem__set_delta_time(this.__ptr, value);
    }
});
BgfxSystem.prototype["__destroy"] = BgfxSystem.prototype.__destroy = function() {
    _mud_BgfxSystem__destroy(this.__ptr);
};

(function() {
    function setup() {
        BgfxSystem.__type = _mud_BgfxSystem__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
