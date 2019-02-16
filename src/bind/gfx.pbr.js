Module['gfx'] = Module['gfx'] || {};
// BCS
function BCS() {
    this.ptr = _mud_BCS__construct_0(); this.type = BCS; getCache(BCS)[this.ptr] = this;
};
BCS.prototype = Object.create(WrapperObject.prototype);
BCS.prototype.constructor = BCS;
BCS.prototype.__class__ = BCS;
BCS.__cache__ = {};
Module['BCS'] = BCS;
Object.defineProperty(BCS.prototype, "enabled", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_BCS__get_enabled(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BCS__set_enabled(self, value);
    }
});
Object.defineProperty(BCS.prototype, "brightness", {
    get: function() {
        var self = this.ptr;
        return _mud_BCS__get_brightness(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BCS__set_brightness(self, value);
    }
});
Object.defineProperty(BCS.prototype, "contrast", {
    get: function() {
        var self = this.ptr;
        return _mud_BCS__get_contrast(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BCS__set_contrast(self, value);
    }
});
Object.defineProperty(BCS.prototype, "saturation", {
    get: function() {
        var self = this.ptr;
        return _mud_BCS__get_saturation(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BCS__set_saturation(self, value);
    }
});
BCS.prototype["__destroy__"] = BCS.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BCS__destroy(self);
};
// BlockBlur
function BlockBlur() { throw "cannot construct a BlockBlur, no constructor in IDL" }
BlockBlur.prototype = Object.create(WrapperObject.prototype);
BlockBlur.prototype.constructor = BlockBlur;
BlockBlur.prototype.__class__ = BlockBlur;
BlockBlur.__cache__ = {};
Module['BlockBlur'] = BlockBlur;
BlockBlur.prototype["__destroy__"] = BlockBlur.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockBlur__destroy(self);
};
// BlockDofBlur
function BlockDofBlur() { throw "cannot construct a BlockDofBlur, no constructor in IDL" }
BlockDofBlur.prototype = Object.create(WrapperObject.prototype);
BlockDofBlur.prototype.constructor = BlockDofBlur;
BlockDofBlur.prototype.__class__ = BlockDofBlur;
BlockDofBlur.__cache__ = {};
Module['BlockDofBlur'] = BlockDofBlur;
BlockDofBlur.prototype["__destroy__"] = BlockDofBlur.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockDofBlur__destroy(self);
};
// BlockGIBake
function BlockGIBake() { throw "cannot construct a BlockGIBake, no constructor in IDL" }
BlockGIBake.prototype = Object.create(WrapperObject.prototype);
BlockGIBake.prototype.constructor = BlockGIBake;
BlockGIBake.prototype.__class__ = BlockGIBake;
BlockGIBake.__cache__ = {};
Module['BlockGIBake'] = BlockGIBake;
BlockGIBake.prototype["__destroy__"] = BlockGIBake.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockGIBake__destroy(self);
};
// BlockGITrace
function BlockGITrace() { throw "cannot construct a BlockGITrace, no constructor in IDL" }
BlockGITrace.prototype = Object.create(WrapperObject.prototype);
BlockGITrace.prototype.constructor = BlockGITrace;
BlockGITrace.prototype.__class__ = BlockGITrace;
BlockGITrace.__cache__ = {};
Module['BlockGITrace'] = BlockGITrace;
BlockGITrace.prototype["__destroy__"] = BlockGITrace.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockGITrace__destroy(self);
};
// BlockGeometry
function BlockGeometry() { throw "cannot construct a BlockGeometry, no constructor in IDL" }
BlockGeometry.prototype = Object.create(WrapperObject.prototype);
BlockGeometry.prototype.constructor = BlockGeometry;
BlockGeometry.prototype.__class__ = BlockGeometry;
BlockGeometry.__cache__ = {};
Module['BlockGeometry'] = BlockGeometry;
BlockGeometry.prototype["__destroy__"] = BlockGeometry.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockGeometry__destroy(self);
};
// BlockGlow
function BlockGlow() { throw "cannot construct a BlockGlow, no constructor in IDL" }
BlockGlow.prototype = Object.create(WrapperObject.prototype);
BlockGlow.prototype.constructor = BlockGlow;
BlockGlow.prototype.__class__ = BlockGlow;
BlockGlow.__cache__ = {};
Module['BlockGlow'] = BlockGlow;
BlockGlow.prototype["__destroy__"] = BlockGlow.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockGlow__destroy(self);
};
// BlockLight
function BlockLight() { throw "cannot construct a BlockLight, no constructor in IDL" }
BlockLight.prototype = Object.create(WrapperObject.prototype);
BlockLight.prototype.constructor = BlockLight;
BlockLight.prototype.__class__ = BlockLight;
BlockLight.__cache__ = {};
Module['BlockLight'] = BlockLight;
BlockLight.prototype["__destroy__"] = BlockLight.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockLight__destroy(self);
};
// BlockLightmap
function BlockLightmap() { throw "cannot construct a BlockLightmap, no constructor in IDL" }
BlockLightmap.prototype = Object.create(WrapperObject.prototype);
BlockLightmap.prototype.constructor = BlockLightmap;
BlockLightmap.prototype.__class__ = BlockLightmap;
BlockLightmap.__cache__ = {};
Module['BlockLightmap'] = BlockLightmap;
BlockLightmap.prototype["__destroy__"] = BlockLightmap.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockLightmap__destroy(self);
};
// BlockRadiance
function BlockRadiance() { throw "cannot construct a BlockRadiance, no constructor in IDL" }
BlockRadiance.prototype = Object.create(WrapperObject.prototype);
BlockRadiance.prototype.constructor = BlockRadiance;
BlockRadiance.prototype.__class__ = BlockRadiance;
BlockRadiance.__cache__ = {};
Module['BlockRadiance'] = BlockRadiance;
BlockRadiance.prototype["__destroy__"] = BlockRadiance.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockRadiance__destroy(self);
};
// BlockReflection
function BlockReflection() { throw "cannot construct a BlockReflection, no constructor in IDL" }
BlockReflection.prototype = Object.create(WrapperObject.prototype);
BlockReflection.prototype.constructor = BlockReflection;
BlockReflection.prototype.__class__ = BlockReflection;
BlockReflection.__cache__ = {};
Module['BlockReflection'] = BlockReflection;
BlockReflection.prototype["__destroy__"] = BlockReflection.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockReflection__destroy(self);
};
// BlockShadow
function BlockShadow() { throw "cannot construct a BlockShadow, no constructor in IDL" }
BlockShadow.prototype = Object.create(WrapperObject.prototype);
BlockShadow.prototype.constructor = BlockShadow;
BlockShadow.prototype.__class__ = BlockShadow;
BlockShadow.__cache__ = {};
Module['BlockShadow'] = BlockShadow;
BlockShadow.prototype["__destroy__"] = BlockShadow.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockShadow__destroy(self);
};
// BlockTonemap
function BlockTonemap() { throw "cannot construct a BlockTonemap, no constructor in IDL" }
BlockTonemap.prototype = Object.create(WrapperObject.prototype);
BlockTonemap.prototype.constructor = BlockTonemap;
BlockTonemap.prototype.__class__ = BlockTonemap;
BlockTonemap.__cache__ = {};
Module['BlockTonemap'] = BlockTonemap;
BlockTonemap.prototype["__destroy__"] = BlockTonemap.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockTonemap__destroy(self);
};
// DofBlur
function DofBlur() {
    this.ptr = _mud_DofBlur__construct_0(); this.type = DofBlur; getCache(DofBlur)[this.ptr] = this;
};
DofBlur.prototype = Object.create(WrapperObject.prototype);
DofBlur.prototype.constructor = DofBlur;
DofBlur.prototype.__class__ = DofBlur;
DofBlur.__cache__ = {};
Module['DofBlur'] = DofBlur;
Object.defineProperty(DofBlur.prototype, "enabled", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_DofBlur__get_enabled(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_DofBlur__set_enabled(self, value);
    }
});
Object.defineProperty(DofBlur.prototype, "far", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_DofBlur__get_far(self), DofParams);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_DofBlur__set_far(self, value.ptr);
    }
});
Object.defineProperty(DofBlur.prototype, "near", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_DofBlur__get_near(self), DofParams);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_DofBlur__set_near(self, value.ptr);
    }
});
Object.defineProperty(DofBlur.prototype, "max_coc_radius", {
    get: function() {
        var self = this.ptr;
        return _mud_DofBlur__get_max_coc_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_DofBlur__set_max_coc_radius(self, value);
    }
});
DofBlur.prototype["__destroy__"] = DofBlur.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_DofBlur__destroy(self);
};
// DofParams
function DofParams() {
    this.ptr = _mud_DofParams__construct_0(); this.type = DofParams; getCache(DofParams)[this.ptr] = this;
};
DofParams.prototype = Object.create(WrapperObject.prototype);
DofParams.prototype.constructor = DofParams;
DofParams.prototype.__class__ = DofParams;
DofParams.__cache__ = {};
Module['DofParams'] = DofParams;
Object.defineProperty(DofParams.prototype, "distance", {
    get: function() {
        var self = this.ptr;
        return _mud_DofParams__get_distance(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_DofParams__set_distance(self, value);
    }
});
Object.defineProperty(DofParams.prototype, "transition", {
    get: function() {
        var self = this.ptr;
        return _mud_DofParams__get_transition(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_DofParams__set_transition(self, value);
    }
});
Object.defineProperty(DofParams.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_DofParams__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_DofParams__set_radius(self, value);
    }
});
DofParams.prototype["__destroy__"] = DofParams.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_DofParams__destroy(self);
};
// GIProbe
function GIProbe() { throw "cannot construct a GIProbe, no constructor in IDL" }
GIProbe.prototype = Object.create(WrapperObject.prototype);
GIProbe.prototype.constructor = GIProbe;
GIProbe.prototype.__class__ = GIProbe;
GIProbe.__cache__ = {};
Module['GIProbe'] = GIProbe;
GIProbe.prototype["__destroy__"] = GIProbe.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_GIProbe__destroy(self);
};
// Glow
function Glow() {
    this.ptr = _mud_Glow__construct_0(); this.type = Glow; getCache(Glow)[this.ptr] = this;
};
Glow.prototype = Object.create(WrapperObject.prototype);
Glow.prototype.constructor = Glow;
Glow.prototype.__class__ = Glow;
Glow.__cache__ = {};
Module['Glow'] = Glow;
Object.defineProperty(Glow.prototype, "enabled", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Glow__get_enabled(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Glow__set_enabled(self, value);
    }
});
Object.defineProperty(Glow.prototype, "levels_1_4", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Glow__get_levels_1_4(self), v4_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Glow__set_levels_1_4(self, value.ptr);
    }
});
Object.defineProperty(Glow.prototype, "levels_5_8", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Glow__get_levels_5_8(self), v4_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Glow__set_levels_5_8(self, value.ptr);
    }
});
Object.defineProperty(Glow.prototype, "intensity", {
    get: function() {
        var self = this.ptr;
        return _mud_Glow__get_intensity(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Glow__set_intensity(self, value);
    }
});
Object.defineProperty(Glow.prototype, "bloom", {
    get: function() {
        var self = this.ptr;
        return _mud_Glow__get_bloom(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Glow__set_bloom(self, value);
    }
});
Object.defineProperty(Glow.prototype, "bleed_threshold", {
    get: function() {
        var self = this.ptr;
        return _mud_Glow__get_bleed_threshold(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Glow__set_bleed_threshold(self, value);
    }
});
Object.defineProperty(Glow.prototype, "bleed_scale", {
    get: function() {
        var self = this.ptr;
        return _mud_Glow__get_bleed_scale(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Glow__set_bleed_scale(self, value);
    }
});
Object.defineProperty(Glow.prototype, "bicubic_filter", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Glow__get_bicubic_filter(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Glow__set_bicubic_filter(self, value);
    }
});
Glow.prototype["__destroy__"] = Glow.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Glow__destroy(self);
};
// LightShadow
function LightShadow() {
    this.ptr = _mud_LightShadow__construct_0(); this.type = LightShadow; getCache(LightShadow)[this.ptr] = this;
};
LightShadow.prototype = Object.create(WrapperObject.prototype);
LightShadow.prototype.constructor = LightShadow;
LightShadow.prototype.__class__ = LightShadow;
LightShadow.__cache__ = {};
Module['LightShadow'] = LightShadow;
LightShadow.prototype["__destroy__"] = LightShadow.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_LightShadow__destroy(self);
};
// Lightmap
function Lightmap() { throw "cannot construct a Lightmap, no constructor in IDL" }
Lightmap.prototype = Object.create(WrapperObject.prototype);
Lightmap.prototype.constructor = Lightmap;
Lightmap.prototype.__class__ = Lightmap;
Lightmap.__cache__ = {};
Module['Lightmap'] = Lightmap;
Lightmap.prototype["__destroy__"] = Lightmap.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Lightmap__destroy(self);
};
// LightmapAtlas
function LightmapAtlas() { throw "cannot construct a LightmapAtlas, no constructor in IDL" }
LightmapAtlas.prototype = Object.create(WrapperObject.prototype);
LightmapAtlas.prototype.constructor = LightmapAtlas;
LightmapAtlas.prototype.__class__ = LightmapAtlas;
LightmapAtlas.__cache__ = {};
Module['LightmapAtlas'] = LightmapAtlas;
LightmapAtlas.prototype["__destroy__"] = LightmapAtlas.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_LightmapAtlas__destroy(self);
};
// LightmapItem
function LightmapItem() { throw "cannot construct a LightmapItem, no constructor in IDL" }
LightmapItem.prototype = Object.create(WrapperObject.prototype);
LightmapItem.prototype.constructor = LightmapItem;
LightmapItem.prototype.__class__ = LightmapItem;
LightmapItem.__cache__ = {};
Module['LightmapItem'] = LightmapItem;
LightmapItem.prototype["__destroy__"] = LightmapItem.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_LightmapItem__destroy(self);
};
// ReflectionProbe
function ReflectionProbe() { throw "cannot construct a ReflectionProbe, no constructor in IDL" }
ReflectionProbe.prototype = Object.create(WrapperObject.prototype);
ReflectionProbe.prototype.constructor = ReflectionProbe;
ReflectionProbe.prototype.__class__ = ReflectionProbe;
ReflectionProbe.__cache__ = {};
Module['ReflectionProbe'] = ReflectionProbe;
Object.defineProperty(ReflectionProbe.prototype, "node", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ReflectionProbe__get_node(self), Node3);
    }});
Object.defineProperty(ReflectionProbe.prototype, "visible", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ReflectionProbe__get_visible(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ReflectionProbe__set_visible(self, value);
    }
});
Object.defineProperty(ReflectionProbe.prototype, "intensity", {
    get: function() {
        var self = this.ptr;
        return _mud_ReflectionProbe__get_intensity(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ReflectionProbe__set_intensity(self, value);
    }
});
Object.defineProperty(ReflectionProbe.prototype, "extents", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ReflectionProbe__get_extents(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ReflectionProbe__set_extents(self, value.ptr);
    }
});
Object.defineProperty(ReflectionProbe.prototype, "shadows", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ReflectionProbe__get_shadows(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ReflectionProbe__set_shadows(self, value);
    }
});
Object.defineProperty(ReflectionProbe.prototype, "dirty", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ReflectionProbe__get_dirty(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ReflectionProbe__set_dirty(self, value);
    }
});
ReflectionProbe.prototype["__destroy__"] = ReflectionProbe.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ReflectionProbe__destroy(self);
};
// Tonemap
function Tonemap() {
    this.ptr = _mud_Tonemap__construct_0(); this.type = Tonemap; getCache(Tonemap)[this.ptr] = this;
};
Tonemap.prototype = Object.create(WrapperObject.prototype);
Tonemap.prototype.constructor = Tonemap;
Tonemap.prototype.__class__ = Tonemap;
Tonemap.__cache__ = {};
Module['Tonemap'] = Tonemap;
Object.defineProperty(Tonemap.prototype, "mode", {
    get: function() {
        var self = this.ptr;
        return _mud_Tonemap__get_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Tonemap__set_mode(self, value);
    }
});
Object.defineProperty(Tonemap.prototype, "enabled", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Tonemap__get_enabled(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Tonemap__set_enabled(self, value);
    }
});
Object.defineProperty(Tonemap.prototype, "exposure", {
    get: function() {
        var self = this.ptr;
        return _mud_Tonemap__get_exposure(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Tonemap__set_exposure(self, value);
    }
});
Object.defineProperty(Tonemap.prototype, "white_point", {
    get: function() {
        var self = this.ptr;
        return _mud_Tonemap__get_white_point(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Tonemap__set_white_point(self, value);
    }
});
Tonemap.prototype["__destroy__"] = Tonemap.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Tonemap__destroy(self);
};
Module['gfx']['setup_pipeline_pbr'] = function(a0) {
    _mud_gfx_setup_pipeline_pbr_1(/*gfx*/a0.ptr);
};
Module['gfx']['gi_probe'] = function(a0, a1, a2) {
    return wrapPointer(_mud_gfx_gi_probe_3(/*parent*/a0.ptr, /*subdiv*/a1, /*extents*/a2.ptr), GIProbe);
};
Module['gfx']['lightmap'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_gfx_lightmap_2(/*parent*/a0.ptr, /*resolution*/a1), LightmapAtlas); }
    if (a3 === undefined) { return wrapPointer(_mud_gfx_lightmap_3(/*parent*/a0.ptr, /*resolution*/a1, /*density*/a2), LightmapAtlas); }
    return wrapPointer(_mud_gfx_lightmap_4(/*parent*/a0.ptr, /*resolution*/a1, /*density*/a2, ensureString(/*save_path*/a3)), LightmapAtlas);
};

(function() {
    function setup() {
        BCS.__type__ = _mud_BCS__type();
        BlockBlur.__type__ = _mud_BlockBlur__type();
        BlockDofBlur.__type__ = _mud_BlockDofBlur__type();
        BlockGIBake.__type__ = _mud_BlockGIBake__type();
        BlockGITrace.__type__ = _mud_BlockGITrace__type();
        BlockGeometry.__type__ = _mud_BlockGeometry__type();
        BlockGlow.__type__ = _mud_BlockGlow__type();
        BlockLight.__type__ = _mud_BlockLight__type();
        BlockLightmap.__type__ = _mud_BlockLightmap__type();
        BlockRadiance.__type__ = _mud_BlockRadiance__type();
        BlockReflection.__type__ = _mud_BlockReflection__type();
        BlockShadow.__type__ = _mud_BlockShadow__type();
        BlockTonemap.__type__ = _mud_BlockTonemap__type();
        DofBlur.__type__ = _mud_DofBlur__type();
        DofParams.__type__ = _mud_DofParams__type();
        GIProbe.__type__ = _mud_GIProbe__type();
        Glow.__type__ = _mud_Glow__type();
        LightShadow.__type__ = _mud_LightShadow__type();
        Lightmap.__type__ = _mud_Lightmap__type();
        LightmapAtlas.__type__ = _mud_LightmapAtlas__type();
        LightmapItem.__type__ = _mud_LightmapItem__type();
        ReflectionProbe.__type__ = _mud_ReflectionProbe__type();
        Tonemap.__type__ = _mud_Tonemap__type();
        // TonemapMode
        Module['TonemapMode'] = Module['TonemapMode'] || {};
        Module['TonemapMode']['Linear'] = _mud_TonemapMode_Linear();
        Module['TonemapMode']['Reinhardt'] = _mud_TonemapMode_Reinhardt();
        Module['TonemapMode']['Filmic'] = _mud_TonemapMode_Filmic();
        Module['TonemapMode']['ACES'] = _mud_TonemapMode_ACES();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
