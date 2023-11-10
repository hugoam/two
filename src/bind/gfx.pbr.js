Module['gfx'] = Module['gfx'] || {};
// BlockLight
function BlockLight() { throw "cannot construct a BlockLight, no constructor in IDL" }
BlockLight.prototype = Object.create(DrawBlock.prototype);
BlockLight.prototype.constructor = BlockLight;
BlockLight.prototype.__class = BlockLight;
BlockLight.__base = DrawBlock;
BlockLight.__cache = {};
Module['BlockLight'] = BlockLight;
BlockLight.prototype["__destroy"] = BlockLight.prototype.__destroy = function() {
    _two_BlockLight__destroy(this.__ptr);
};
// LightmapItem
function LightmapItem() { throw "cannot construct a LightmapItem, no constructor in IDL" }
LightmapItem.prototype = Object.create(WrapperObject.prototype);
LightmapItem.prototype.constructor = LightmapItem;
LightmapItem.prototype.__class = LightmapItem;
LightmapItem.__cache = {};
Module['LightmapItem'] = LightmapItem;
LightmapItem.prototype["__destroy"] = LightmapItem.prototype.__destroy = function() {
    _two_LightmapItem__destroy(this.__ptr);
};
// Lightmap
function Lightmap() { throw "cannot construct a Lightmap, no constructor in IDL" }
Lightmap.prototype = Object.create(WrapperObject.prototype);
Lightmap.prototype.constructor = Lightmap;
Lightmap.prototype.__class = Lightmap;
Lightmap.__cache = {};
Module['Lightmap'] = Lightmap;
Lightmap.prototype["__destroy"] = Lightmap.prototype.__destroy = function() {
    _two_Lightmap__destroy(this.__ptr);
};
// LightmapAtlas
function LightmapAtlas() { throw "cannot construct a LightmapAtlas, no constructor in IDL" }
LightmapAtlas.prototype = Object.create(WrapperObject.prototype);
LightmapAtlas.prototype.constructor = LightmapAtlas;
LightmapAtlas.prototype.__class = LightmapAtlas;
LightmapAtlas.__cache = {};
Module['LightmapAtlas'] = LightmapAtlas;
LightmapAtlas.prototype["__destroy"] = LightmapAtlas.prototype.__destroy = function() {
    _two_LightmapAtlas__destroy(this.__ptr);
};
// BlockLightmap
function BlockLightmap() { throw "cannot construct a BlockLightmap, no constructor in IDL" }
BlockLightmap.prototype = Object.create(DrawBlock.prototype);
BlockLightmap.prototype.constructor = BlockLightmap;
BlockLightmap.prototype.__class = BlockLightmap;
BlockLightmap.__base = DrawBlock;
BlockLightmap.__cache = {};
Module['BlockLightmap'] = BlockLightmap;
BlockLightmap.prototype["__destroy"] = BlockLightmap.prototype.__destroy = function() {
    _two_BlockLightmap__destroy(this.__ptr);
};
// PBRShot
function PBRShot() { throw "cannot construct a PBRShot, no constructor in IDL" }
PBRShot.prototype = Object.create(Shot.prototype);
PBRShot.prototype.constructor = PBRShot;
PBRShot.prototype.__class = PBRShot;
PBRShot.__base = Shot;
PBRShot.__cache = {};
Module['PBRShot'] = PBRShot;
PBRShot.prototype["__destroy"] = PBRShot.prototype.__destroy = function() {
    _two_PBRShot__destroy(this.__ptr);
};
// BlockGeometry
function BlockGeometry() { throw "cannot construct a BlockGeometry, no constructor in IDL" }
BlockGeometry.prototype = Object.create(DrawBlock.prototype);
BlockGeometry.prototype.constructor = BlockGeometry;
BlockGeometry.prototype.__class = BlockGeometry;
BlockGeometry.__base = DrawBlock;
BlockGeometry.__cache = {};
Module['BlockGeometry'] = BlockGeometry;
BlockGeometry.prototype["__destroy"] = BlockGeometry.prototype.__destroy = function() {
    _two_BlockGeometry__destroy(this.__ptr);
};
// BlockRadiance
function BlockRadiance() { throw "cannot construct a BlockRadiance, no constructor in IDL" }
BlockRadiance.prototype = Object.create(DrawBlock.prototype);
BlockRadiance.prototype.constructor = BlockRadiance;
BlockRadiance.prototype.__class = BlockRadiance;
BlockRadiance.__base = DrawBlock;
BlockRadiance.__cache = {};
Module['BlockRadiance'] = BlockRadiance;
BlockRadiance.prototype["__destroy"] = BlockRadiance.prototype.__destroy = function() {
    _two_BlockRadiance__destroy(this.__ptr);
};
// CubeTarget
function CubeTarget() {
    
    this.__ptr = _two_CubeTarget__construct_0(); getCache(CubeTarget)[this.__ptr] = this;
};
CubeTarget.prototype = Object.create(WrapperObject.prototype);
CubeTarget.prototype.constructor = CubeTarget;
CubeTarget.prototype.__class = CubeTarget;
CubeTarget.__cache = {};
Module['CubeTarget'] = CubeTarget;
CubeTarget.prototype["create"] = CubeTarget.prototype.create = function(a0) {
    if (typeof a0 !== 'number') throw Error('create(0:size): expected integer');
    _two_CubeTarget_create_1(this.__ptr, /*size*/a0);
};
CubeTarget.prototype["side"] = CubeTarget.prototype.side = function(a0) {
    if (typeof a0 !== 'number') throw Error('side(0:i): expected integer');
    return wrapPointer(_two_CubeTarget_side_1(this.__ptr, /*i*/a0), FrameBuffer);
};
Object.defineProperty(CubeTarget.prototype, "cubemap", {
    get: function() {
        return wrapPointer(_two_CubeTarget__get_cubemap(this.__ptr), Texture);
    }});
Object.defineProperty(CubeTarget.prototype, "depth", {
    get: function() {
        return wrapPointer(_two_CubeTarget__get_depth(this.__ptr), Texture);
    }});
Object.defineProperty(CubeTarget.prototype, "size", {
    get: function() {
        return _two_CubeTarget__get_size(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('CubeTarget.size: expected integer');
        _two_CubeTarget__set_size(this.__ptr, value);
    }
});
CubeTarget.prototype["__destroy"] = CubeTarget.prototype.__destroy = function() {
    _two_CubeTarget__destroy(this.__ptr);
};
// CubeCamera
function CubeCamera(a0, a1, a2, a3) {
    if (a0 === undefined) {  }
    else { if (!checkClass(a0, Scene)) throw Error('CubeCamera(0:scene): expected Scene'); if (typeof a1 !== 'number') throw Error('CubeCamera(1:near): expected number'); if (typeof a2 !== 'number') throw Error('CubeCamera(2:far): expected number'); if (typeof a3 !== 'number') throw Error('CubeCamera(3:size): expected integer'); }
    if (a0 === undefined) { this.__ptr = _two_CubeCamera__construct_0(); getCache(CubeCamera)[this.__ptr] = this; }
    else { this.__ptr = _two_CubeCamera__construct_4(/*scene*/a0.__ptr, /*near*/a1, /*far*/a2, /*size*/a3); getCache(CubeCamera)[this.__ptr] = this; }
};
CubeCamera.prototype = Object.create(WrapperObject.prototype);
CubeCamera.prototype.constructor = CubeCamera;
CubeCamera.prototype.__class = CubeCamera;
CubeCamera.__cache = {};
Module['CubeCamera'] = CubeCamera;
CubeCamera.prototype["render"] = CubeCamera.prototype.render = function(a0, a1, a2) {
    if (!checkClass(a0, GfxSystem)) throw Error('render(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('render(1:render): expected Render'); if (typeof a2 !== 'number') throw Error('render(2:axis): expected integer');
    return wrapPointer(_two_CubeCamera_render_3(this.__ptr, /*gfx*/a0.__ptr, /*render*/a1.__ptr, /*axis*/a2), Render);
};
Object.defineProperty(CubeCamera.prototype, "cubemap", {
    get: function() {
        return wrapPointer(_two_CubeCamera__get_cubemap(this.__ptr), CubeTarget);
    }});
Object.defineProperty(CubeCamera.prototype, "size", {
    get: function() {
        return wrapPointer(_two_CubeCamera__get_size(this.__ptr), v2_uint);
    },
    set: function(value) {
        if (!checkClass(value, v2_uint)) throw Error('CubeCamera.size: expected v2<uint>');
        _two_CubeCamera__set_size(this.__ptr, value.__ptr);
    }
});
CubeCamera.prototype["__destroy"] = CubeCamera.prototype.__destroy = function() {
    _two_CubeCamera__destroy(this.__ptr);
};
// ReflectionProbe
function ReflectionProbe() { throw "cannot construct a ReflectionProbe, no constructor in IDL" }
ReflectionProbe.prototype = Object.create(WrapperObject.prototype);
ReflectionProbe.prototype.constructor = ReflectionProbe;
ReflectionProbe.prototype.__class = ReflectionProbe;
ReflectionProbe.__cache = {};
Module['ReflectionProbe'] = ReflectionProbe;
Object.defineProperty(ReflectionProbe.prototype, "node", {
    get: function() {
        return wrapPointer(_two_ReflectionProbe__get_node(this.__ptr), Node3);
    }});
Object.defineProperty(ReflectionProbe.prototype, "visible", {
    get: function() {
        return !!(_two_ReflectionProbe__get_visible(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('ReflectionProbe.visible: expected boolean');
        _two_ReflectionProbe__set_visible(this.__ptr, value);
    }
});
Object.defineProperty(ReflectionProbe.prototype, "intensity", {
    get: function() {
        return _two_ReflectionProbe__get_intensity(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ReflectionProbe.intensity: expected number');
        _two_ReflectionProbe__set_intensity(this.__ptr, value);
    }
});
Object.defineProperty(ReflectionProbe.prototype, "extents", {
    get: function() {
        return wrapPointer(_two_ReflectionProbe__get_extents(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('ReflectionProbe.extents: expected v3<float>');
        _two_ReflectionProbe__set_extents(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ReflectionProbe.prototype, "shadows", {
    get: function() {
        return !!(_two_ReflectionProbe__get_shadows(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('ReflectionProbe.shadows: expected boolean');
        _two_ReflectionProbe__set_shadows(this.__ptr, value);
    }
});
Object.defineProperty(ReflectionProbe.prototype, "dirty", {
    get: function() {
        return !!(_two_ReflectionProbe__get_dirty(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('ReflectionProbe.dirty: expected boolean');
        _two_ReflectionProbe__set_dirty(this.__ptr, value);
    }
});
ReflectionProbe.prototype["__destroy"] = ReflectionProbe.prototype.__destroy = function() {
    _two_ReflectionProbe__destroy(this.__ptr);
};
// BlockReflection
function BlockReflection() { throw "cannot construct a BlockReflection, no constructor in IDL" }
BlockReflection.prototype = Object.create(DrawBlock.prototype);
BlockReflection.prototype.constructor = BlockReflection;
BlockReflection.prototype.__class = BlockReflection;
BlockReflection.__base = DrawBlock;
BlockReflection.__cache = {};
Module['BlockReflection'] = BlockReflection;
BlockReflection.prototype["__destroy"] = BlockReflection.prototype.__destroy = function() {
    _two_BlockReflection__destroy(this.__ptr);
};
// LightShadow
function LightShadow() {
    
    this.__ptr = _two_LightShadow__construct_0(); getCache(LightShadow)[this.__ptr] = this;
};
LightShadow.prototype = Object.create(WrapperObject.prototype);
LightShadow.prototype.constructor = LightShadow;
LightShadow.prototype.__class = LightShadow;
LightShadow.__cache = {};
Module['LightShadow'] = LightShadow;
LightShadow.prototype["__destroy"] = LightShadow.prototype.__destroy = function() {
    _two_LightShadow__destroy(this.__ptr);
};
// CSMSlice
function CSMSlice() {
    
    this.__ptr = _two_CSMSlice__construct_0(); getCache(CSMSlice)[this.__ptr] = this;
};
CSMSlice.prototype = Object.create(LightShadow.prototype);
CSMSlice.prototype.constructor = CSMSlice;
CSMSlice.prototype.__class = CSMSlice;
CSMSlice.__base = LightShadow;
CSMSlice.__cache = {};
Module['CSMSlice'] = CSMSlice;
CSMSlice.prototype["__destroy"] = CSMSlice.prototype.__destroy = function() {
    _two_CSMSlice__destroy(this.__ptr);
};
// CSMShadow
function CSMShadow() {
    
    this.__ptr = _two_CSMShadow__construct_0(); getCache(CSMShadow)[this.__ptr] = this;
};
CSMShadow.prototype = Object.create(WrapperObject.prototype);
CSMShadow.prototype.constructor = CSMShadow;
CSMShadow.prototype.__class = CSMShadow;
CSMShadow.__cache = {};
Module['CSMShadow'] = CSMShadow;
CSMShadow.prototype["__destroy"] = CSMShadow.prototype.__destroy = function() {
    _two_CSMShadow__destroy(this.__ptr);
};
// BlockShadow
function BlockShadow() { throw "cannot construct a BlockShadow, no constructor in IDL" }
BlockShadow.prototype = Object.create(DrawBlock.prototype);
BlockShadow.prototype.constructor = BlockShadow;
BlockShadow.prototype.__class = BlockShadow;
BlockShadow.__base = DrawBlock;
BlockShadow.__cache = {};
Module['BlockShadow'] = BlockShadow;
BlockShadow.prototype["__destroy"] = BlockShadow.prototype.__destroy = function() {
    _two_BlockShadow__destroy(this.__ptr);
};
// GIProbe
function GIProbe() { throw "cannot construct a GIProbe, no constructor in IDL" }
GIProbe.prototype = Object.create(WrapperObject.prototype);
GIProbe.prototype.constructor = GIProbe;
GIProbe.prototype.__class = GIProbe;
GIProbe.__cache = {};
Module['GIProbe'] = GIProbe;
GIProbe.prototype["__destroy"] = GIProbe.prototype.__destroy = function() {
    _two_GIProbe__destroy(this.__ptr);
};
// BlockGITrace
function BlockGITrace() { throw "cannot construct a BlockGITrace, no constructor in IDL" }
BlockGITrace.prototype = Object.create(DrawBlock.prototype);
BlockGITrace.prototype.constructor = BlockGITrace;
BlockGITrace.prototype.__class = BlockGITrace;
BlockGITrace.__base = DrawBlock;
BlockGITrace.__cache = {};
Module['BlockGITrace'] = BlockGITrace;
BlockGITrace.prototype["__destroy"] = BlockGITrace.prototype.__destroy = function() {
    _two_BlockGITrace__destroy(this.__ptr);
};
// BlockGIBake
function BlockGIBake() { throw "cannot construct a BlockGIBake, no constructor in IDL" }
BlockGIBake.prototype = Object.create(DrawBlock.prototype);
BlockGIBake.prototype.constructor = BlockGIBake;
BlockGIBake.prototype.__class = BlockGIBake;
BlockGIBake.__base = DrawBlock;
BlockGIBake.__cache = {};
Module['BlockGIBake'] = BlockGIBake;
BlockGIBake.prototype["__destroy"] = BlockGIBake.prototype.__destroy = function() {
    _two_BlockGIBake__destroy(this.__ptr);
};
// BlockBlur
function BlockBlur() { throw "cannot construct a BlockBlur, no constructor in IDL" }
BlockBlur.prototype = Object.create(GfxBlock.prototype);
BlockBlur.prototype.constructor = BlockBlur;
BlockBlur.prototype.__class = BlockBlur;
BlockBlur.__base = GfxBlock;
BlockBlur.__cache = {};
Module['BlockBlur'] = BlockBlur;
BlockBlur.prototype["__destroy"] = BlockBlur.prototype.__destroy = function() {
    _two_BlockBlur__destroy(this.__ptr);
};
// DofParams
function DofParams() {
    
    this.__ptr = _two_DofParams__construct_0(); getCache(DofParams)[this.__ptr] = this;
};
DofParams.prototype = Object.create(WrapperObject.prototype);
DofParams.prototype.constructor = DofParams;
DofParams.prototype.__class = DofParams;
DofParams.__cache = {};
Module['DofParams'] = DofParams;
Object.defineProperty(DofParams.prototype, "distance", {
    get: function() {
        return _two_DofParams__get_distance(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('DofParams.distance: expected number');
        _two_DofParams__set_distance(this.__ptr, value);
    }
});
Object.defineProperty(DofParams.prototype, "transition", {
    get: function() {
        return _two_DofParams__get_transition(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('DofParams.transition: expected number');
        _two_DofParams__set_transition(this.__ptr, value);
    }
});
Object.defineProperty(DofParams.prototype, "radius", {
    get: function() {
        return _two_DofParams__get_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('DofParams.radius: expected number');
        _two_DofParams__set_radius(this.__ptr, value);
    }
});
DofParams.prototype["__destroy"] = DofParams.prototype.__destroy = function() {
    _two_DofParams__destroy(this.__ptr);
};
// DofBlur
function DofBlur() {
    
    this.__ptr = _two_DofBlur__construct_0(); getCache(DofBlur)[this.__ptr] = this;
};
DofBlur.prototype = Object.create(WrapperObject.prototype);
DofBlur.prototype.constructor = DofBlur;
DofBlur.prototype.__class = DofBlur;
DofBlur.__cache = {};
Module['DofBlur'] = DofBlur;
Object.defineProperty(DofBlur.prototype, "enabled", {
    get: function() {
        return !!(_two_DofBlur__get_enabled(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('DofBlur.enabled: expected boolean');
        _two_DofBlur__set_enabled(this.__ptr, value);
    }
});
Object.defineProperty(DofBlur.prototype, "far", {
    get: function() {
        return wrapPointer(_two_DofBlur__get_far(this.__ptr), DofParams);
    },
    set: function(value) {
        if (!checkClass(value, DofParams)) throw Error('DofBlur.far: expected DofParams');
        _two_DofBlur__set_far(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(DofBlur.prototype, "near", {
    get: function() {
        return wrapPointer(_two_DofBlur__get_near(this.__ptr), DofParams);
    },
    set: function(value) {
        if (!checkClass(value, DofParams)) throw Error('DofBlur.near: expected DofParams');
        _two_DofBlur__set_near(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(DofBlur.prototype, "max_coc_radius", {
    get: function() {
        return _two_DofBlur__get_max_coc_radius(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('DofBlur.max_coc_radius: expected number');
        _two_DofBlur__set_max_coc_radius(this.__ptr, value);
    }
});
DofBlur.prototype["__destroy"] = DofBlur.prototype.__destroy = function() {
    _two_DofBlur__destroy(this.__ptr);
};
// BlockDofBlur
function BlockDofBlur() { throw "cannot construct a BlockDofBlur, no constructor in IDL" }
BlockDofBlur.prototype = Object.create(GfxBlock.prototype);
BlockDofBlur.prototype.constructor = BlockDofBlur;
BlockDofBlur.prototype.__class = BlockDofBlur;
BlockDofBlur.__base = GfxBlock;
BlockDofBlur.__cache = {};
Module['BlockDofBlur'] = BlockDofBlur;
BlockDofBlur.prototype["__destroy"] = BlockDofBlur.prototype.__destroy = function() {
    _two_BlockDofBlur__destroy(this.__ptr);
};
// Glow
function Glow() {
    
    this.__ptr = _two_Glow__construct_0(); getCache(Glow)[this.__ptr] = this;
};
Glow.prototype = Object.create(WrapperObject.prototype);
Glow.prototype.constructor = Glow;
Glow.prototype.__class = Glow;
Glow.__cache = {};
Module['Glow'] = Glow;
Object.defineProperty(Glow.prototype, "enabled", {
    get: function() {
        return !!(_two_Glow__get_enabled(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Glow.enabled: expected boolean');
        _two_Glow__set_enabled(this.__ptr, value);
    }
});
Object.defineProperty(Glow.prototype, "levels_1_4", {
    get: function() {
        return wrapPointer(_two_Glow__get_levels_1_4(this.__ptr), v4_float);
    },
    set: function(value) {
        if (!checkClass(value, v4_float)) throw Error('Glow.levels_1_4: expected v4<float>');
        _two_Glow__set_levels_1_4(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Glow.prototype, "levels_5_8", {
    get: function() {
        return wrapPointer(_two_Glow__get_levels_5_8(this.__ptr), v4_float);
    },
    set: function(value) {
        if (!checkClass(value, v4_float)) throw Error('Glow.levels_5_8: expected v4<float>');
        _two_Glow__set_levels_5_8(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Glow.prototype, "intensity", {
    get: function() {
        return _two_Glow__get_intensity(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Glow.intensity: expected number');
        _two_Glow__set_intensity(this.__ptr, value);
    }
});
Object.defineProperty(Glow.prototype, "bloom", {
    get: function() {
        return _two_Glow__get_bloom(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Glow.bloom: expected number');
        _two_Glow__set_bloom(this.__ptr, value);
    }
});
Object.defineProperty(Glow.prototype, "bleed_threshold", {
    get: function() {
        return _two_Glow__get_bleed_threshold(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Glow.bleed_threshold: expected number');
        _two_Glow__set_bleed_threshold(this.__ptr, value);
    }
});
Object.defineProperty(Glow.prototype, "bleed_scale", {
    get: function() {
        return _two_Glow__get_bleed_scale(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Glow.bleed_scale: expected number');
        _two_Glow__set_bleed_scale(this.__ptr, value);
    }
});
Object.defineProperty(Glow.prototype, "bicubic_filter", {
    get: function() {
        return !!(_two_Glow__get_bicubic_filter(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Glow.bicubic_filter: expected boolean');
        _two_Glow__set_bicubic_filter(this.__ptr, value);
    }
});
Glow.prototype["__destroy"] = Glow.prototype.__destroy = function() {
    _two_Glow__destroy(this.__ptr);
};
// BlockGlow
function BlockGlow() { throw "cannot construct a BlockGlow, no constructor in IDL" }
BlockGlow.prototype = Object.create(GfxBlock.prototype);
BlockGlow.prototype.constructor = BlockGlow;
BlockGlow.prototype.__class = BlockGlow;
BlockGlow.__base = GfxBlock;
BlockGlow.__cache = {};
Module['BlockGlow'] = BlockGlow;
BlockGlow.prototype["__destroy"] = BlockGlow.prototype.__destroy = function() {
    _two_BlockGlow__destroy(this.__ptr);
};
// BCS
function BCS() {
    
    this.__ptr = _two_BCS__construct_0(); getCache(BCS)[this.__ptr] = this;
};
BCS.prototype = Object.create(WrapperObject.prototype);
BCS.prototype.constructor = BCS;
BCS.prototype.__class = BCS;
BCS.__cache = {};
Module['BCS'] = BCS;
Object.defineProperty(BCS.prototype, "enabled", {
    get: function() {
        return !!(_two_BCS__get_enabled(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('BCS.enabled: expected boolean');
        _two_BCS__set_enabled(this.__ptr, value);
    }
});
Object.defineProperty(BCS.prototype, "brightness", {
    get: function() {
        return _two_BCS__get_brightness(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('BCS.brightness: expected number');
        _two_BCS__set_brightness(this.__ptr, value);
    }
});
Object.defineProperty(BCS.prototype, "contrast", {
    get: function() {
        return _two_BCS__get_contrast(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('BCS.contrast: expected number');
        _two_BCS__set_contrast(this.__ptr, value);
    }
});
Object.defineProperty(BCS.prototype, "saturation", {
    get: function() {
        return _two_BCS__get_saturation(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('BCS.saturation: expected number');
        _two_BCS__set_saturation(this.__ptr, value);
    }
});
BCS.prototype["__destroy"] = BCS.prototype.__destroy = function() {
    _two_BCS__destroy(this.__ptr);
};
// Tonemap
function Tonemap() {
    
    this.__ptr = _two_Tonemap__construct_0(); getCache(Tonemap)[this.__ptr] = this;
};
Tonemap.prototype = Object.create(WrapperObject.prototype);
Tonemap.prototype.constructor = Tonemap;
Tonemap.prototype.__class = Tonemap;
Tonemap.__cache = {};
Module['Tonemap'] = Tonemap;
Object.defineProperty(Tonemap.prototype, "mode", {
    get: function() {
        return _two_Tonemap__get_mode(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Tonemap.mode: expected integer');
        _two_Tonemap__set_mode(this.__ptr, value);
    }
});
Object.defineProperty(Tonemap.prototype, "enabled", {
    get: function() {
        return !!(_two_Tonemap__get_enabled(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Tonemap.enabled: expected boolean');
        _two_Tonemap__set_enabled(this.__ptr, value);
    }
});
Object.defineProperty(Tonemap.prototype, "exposure", {
    get: function() {
        return _two_Tonemap__get_exposure(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Tonemap.exposure: expected number');
        _two_Tonemap__set_exposure(this.__ptr, value);
    }
});
Object.defineProperty(Tonemap.prototype, "white_point", {
    get: function() {
        return _two_Tonemap__get_white_point(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Tonemap.white_point: expected number');
        _two_Tonemap__set_white_point(this.__ptr, value);
    }
});
Tonemap.prototype["__destroy"] = Tonemap.prototype.__destroy = function() {
    _two_Tonemap__destroy(this.__ptr);
};
// BlockTonemap
function BlockTonemap() { throw "cannot construct a BlockTonemap, no constructor in IDL" }
BlockTonemap.prototype = Object.create(GfxBlock.prototype);
BlockTonemap.prototype.constructor = BlockTonemap;
BlockTonemap.prototype.__class = BlockTonemap;
BlockTonemap.__base = GfxBlock;
BlockTonemap.__cache = {};
Module['BlockTonemap'] = BlockTonemap;
BlockTonemap.prototype["__destroy"] = BlockTonemap.prototype.__destroy = function() {
    _two_BlockTonemap__destroy(this.__ptr);
};
Module['begin_pbr_render'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('begin_pbr_render(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('begin_pbr_render(1:render): expected Render');
    _two_begin_pbr_render_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_gi_probes'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_gi_probes(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_gi_probes(1:render): expected Render');
    _two_pass_gi_probes_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_shadowmaps'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_shadowmaps(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_shadowmaps(1:render): expected Render');
    _two_pass_shadowmaps_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_shadow'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_shadow(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_shadow(1:render): expected Render');
    _two_pass_shadow_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_opaque'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_opaque(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_opaque(1:render): expected Render');
    _two_pass_opaque_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_alpha'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_alpha(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_alpha(1:render): expected Render');
    _two_pass_alpha_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_geometry'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_geometry(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_geometry(1:render): expected Render');
    _two_pass_geometry_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_lights'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_lights(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_lights(1:render): expected Render');
    _two_pass_lights_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_voxel_gi'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_voxel_gi(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_voxel_gi(1:render): expected Render');
    _two_pass_voxel_gi_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_lightmap'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_lightmap(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_lightmap(1:render): expected Render');
    _two_pass_lightmap_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_begin_post'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_begin_post(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_begin_post(1:render): expected Render');
    _two_pass_begin_post_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_post_auto'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_post_auto(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_post_auto(1:render): expected Render');
    _two_pass_post_auto_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_post_effects'] = function(a0, a1, a2, a3, a4, a5) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_post_effects(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_post_effects(1:render): expected Render'); if (!checkClass(a2, DofBlur)) throw Error('pass_post_effects(2:dof): expected DofBlur'); if (!checkClass(a3, Glow)) throw Error('pass_post_effects(3:glow): expected Glow'); if (!checkClass(a4, Tonemap)) throw Error('pass_post_effects(4:tonemap): expected Tonemap'); if (!checkClass(a5, BCS)) throw Error('pass_post_effects(5:bcs): expected BCS');
    _two_pass_post_effects_6(/*gfx*/a0.__ptr, /*render*/a1.__ptr, /*dof*/a2.__ptr, /*glow*/a3.__ptr, /*tonemap*/a4.__ptr, /*bcs*/a5.__ptr);
};
Module['render_pbr_forward'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('render_pbr_forward(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('render_pbr_forward(1:render): expected Render');
    _two_render_pbr_forward_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['render_pbr_deferred'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('render_pbr_deferred(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('render_pbr_deferred(1:render): expected Render');
    _two_render_pbr_deferred_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['render_shadow'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('render_shadow(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('render_shadow(1:render): expected Render');
    _two_render_shadow_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['render_voxel'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('render_voxel(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('render_voxel(1:render): expected Render');
    _two_render_voxel_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['render_lightmap'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('render_lightmap(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('render_lightmap(1:render): expected Render');
    _two_render_lightmap_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['render_reflection'] = function(a0, a1) {
    if (!checkClass(a0, GfxSystem)) throw Error('render_reflection(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('render_reflection(1:render): expected Render');
    _two_render_reflection_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pipeline_pbr'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, GfxSystem)) throw Error('pipeline_pbr(0:gfx): expected GfxSystem'); if (!checkClass(a1, Renderer)) throw Error('pipeline_pbr(1:pipeline): expected Renderer'); }
    else { if (!checkClass(a0, GfxSystem)) throw Error('pipeline_pbr(0:gfx): expected GfxSystem'); if (!checkClass(a1, Renderer)) throw Error('pipeline_pbr(1:pipeline): expected Renderer'); if (typeof a2 !== 'boolean') throw Error('pipeline_pbr(2:deferred): expected boolean'); }
    if (a2 === undefined) { _two_pipeline_pbr_2(/*gfx*/a0.__ptr, /*pipeline*/a1.__ptr); }
    else { _two_pipeline_pbr_3(/*gfx*/a0.__ptr, /*pipeline*/a1.__ptr, /*deferred*/a2); }
};
Module['gfx']['setup_pipeline_pbr'] = function(a0) {
    if (!checkClass(a0, GfxSystem)) throw Error('setup_pipeline_pbr(0:gfx): expected GfxSystem');
    _two_gfx_setup_pipeline_pbr_1(/*gfx*/a0.__ptr);
};
Module['gfx']['gi_probe'] = function(a0, a1, a2) {
    if (!checkClass(a0, Gnode)) throw Error('gi_probe(0:parent): expected Gnode'); if (typeof a1 !== 'number') throw Error('gi_probe(1:subdiv): expected integer'); if (!checkClass(a2, v3_float)) throw Error('gi_probe(2:extents): expected v3<float>');
    return wrapPointer(_two_gfx_gi_probe_3(/*parent*/a0.__ptr, /*subdiv*/a1, /*extents*/a2.__ptr), GIProbe);
};
Module['gfx']['lightmap'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a2 === undefined) { if (!checkClass(a0, Gnode)) throw Error('lightmap(0:parent): expected Gnode'); if (typeof a1 !== 'number') throw Error('lightmap(1:resolution): expected integer'); }
    else if (a3 === undefined) { if (!checkClass(a0, Gnode)) throw Error('lightmap(0:parent): expected Gnode'); if (typeof a1 !== 'number') throw Error('lightmap(1:resolution): expected integer'); if (typeof a2 !== 'number') throw Error('lightmap(2:density): expected number'); }
    else { if (!checkClass(a0, Gnode)) throw Error('lightmap(0:parent): expected Gnode'); if (typeof a1 !== 'number') throw Error('lightmap(1:resolution): expected integer'); if (typeof a2 !== 'number') throw Error('lightmap(2:density): expected number'); if (typeof a3 !== 'string') throw Error('lightmap(3:save_path): expected string'); }
    if (a2 === undefined) { return wrapPointer(_two_gfx_lightmap_2(/*parent*/a0.__ptr, /*resolution*/a1), LightmapAtlas); }
    else if (a3 === undefined) { return wrapPointer(_two_gfx_lightmap_3(/*parent*/a0.__ptr, /*resolution*/a1, /*density*/a2), LightmapAtlas); }
    else { return wrapPointer(_two_gfx_lightmap_4(/*parent*/a0.__ptr, /*resolution*/a1, /*density*/a2, ensureString(/*save_path*/a3)), LightmapAtlas); }
};
Module['pass_dofblur'] = function(a0, a1, a2) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_dofblur(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_dofblur(1:render): expected Render'); if (!checkClass(a2, DofBlur)) throw Error('pass_dofblur(2:blur): expected DofBlur');
    _two_pass_dofblur_3(/*gfx*/a0.__ptr, /*render*/a1.__ptr, /*blur*/a2.__ptr);
};
Module['pass_glow'] = function(a0, a1, a2) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_glow(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_glow(1:render): expected Render'); if (!checkClass(a2, Glow)) throw Error('pass_glow(2:glow): expected Glow');
    _two_pass_glow_3(/*gfx*/a0.__ptr, /*render*/a1.__ptr, /*glow*/a2.__ptr);
};
Module['pass_tonemap'] = function(a0, a1, a2, a3) {
    if (!checkClass(a0, GfxSystem)) throw Error('pass_tonemap(0:gfx): expected GfxSystem'); if (!checkClass(a1, Render)) throw Error('pass_tonemap(1:render): expected Render'); if (!checkClass(a2, Tonemap)) throw Error('pass_tonemap(2:tonemap): expected Tonemap'); if (!checkClass(a3, BCS)) throw Error('pass_tonemap(3:bcs): expected BCS');
    _two_pass_tonemap_4(/*gfx*/a0.__ptr, /*render*/a1.__ptr, /*tonemap*/a2.__ptr, /*bcs*/a3.__ptr);
};

(function() {
    function setup() {
        BlockLight.prototype.__type = _two_BlockLight__type();
        LightmapItem.prototype.__type = _two_LightmapItem__type();
        Lightmap.prototype.__type = _two_Lightmap__type();
        LightmapAtlas.prototype.__type = _two_LightmapAtlas__type();
        BlockLightmap.prototype.__type = _two_BlockLightmap__type();
        PBRShot.prototype.__type = _two_PBRShot__type();
        BlockGeometry.prototype.__type = _two_BlockGeometry__type();
        BlockRadiance.prototype.__type = _two_BlockRadiance__type();
        CubeTarget.prototype.__type = _two_CubeTarget__type();
        CubeCamera.prototype.__type = _two_CubeCamera__type();
        ReflectionProbe.prototype.__type = _two_ReflectionProbe__type();
        BlockReflection.prototype.__type = _two_BlockReflection__type();
        LightShadow.prototype.__type = _two_LightShadow__type();
        CSMSlice.prototype.__type = _two_CSMSlice__type();
        CSMShadow.prototype.__type = _two_CSMShadow__type();
        BlockShadow.prototype.__type = _two_BlockShadow__type();
        GIProbe.prototype.__type = _two_GIProbe__type();
        BlockGITrace.prototype.__type = _two_BlockGITrace__type();
        BlockGIBake.prototype.__type = _two_BlockGIBake__type();
        BlockBlur.prototype.__type = _two_BlockBlur__type();
        DofParams.prototype.__type = _two_DofParams__type();
        DofBlur.prototype.__type = _two_DofBlur__type();
        BlockDofBlur.prototype.__type = _two_BlockDofBlur__type();
        Glow.prototype.__type = _two_Glow__type();
        BlockGlow.prototype.__type = _two_BlockGlow__type();
        BCS.prototype.__type = _two_BCS__type();
        Tonemap.prototype.__type = _two_Tonemap__type();
        BlockTonemap.prototype.__type = _two_BlockTonemap__type();
        // TonemapMode
        Module['TonemapMode'] = Module['TonemapMode'] || {};
        Module['TonemapMode']['Linear'] = _two_TonemapMode_Linear();
        Module['TonemapMode']['Reinhardt'] = _two_TonemapMode_Reinhardt();
        Module['TonemapMode']['Filmic'] = _two_TonemapMode_Filmic();
        Module['TonemapMode']['ACES'] = _two_TonemapMode_ACES();
        Module['TonemapMode']['Cineon'] = _two_TonemapMode_Cineon();
        Module['TonemapMode']['Uncharted2'] = _two_TonemapMode_Uncharted2();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
