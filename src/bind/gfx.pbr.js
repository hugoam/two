Module['gfx'] = Module['gfx'] || {};
// BCS
function BCS() {
    this.__ptr = _mud_BCS__construct_0(); this.__type = BCS.__type; getCache(BCS)[this.__ptr] = this;
};
BCS.prototype = Object.create(WrapperObject.prototype);
BCS.prototype.constructor = BCS;
BCS.prototype.__class = BCS;
BCS.__cache = {};
Module['BCS'] = BCS;
Object.defineProperty(BCS.prototype, "enabled", {
    get: function() {
        return !!(_mud_BCS__get_enabled(this.__ptr));
    },
    set: function(value) {
        _mud_BCS__set_enabled(this.__ptr, value);
    }
});
Object.defineProperty(BCS.prototype, "brightness", {
    get: function() {
        return _mud_BCS__get_brightness(this.__ptr);
    },
    set: function(value) {
        _mud_BCS__set_brightness(this.__ptr, value);
    }
});
Object.defineProperty(BCS.prototype, "contrast", {
    get: function() {
        return _mud_BCS__get_contrast(this.__ptr);
    },
    set: function(value) {
        _mud_BCS__set_contrast(this.__ptr, value);
    }
});
Object.defineProperty(BCS.prototype, "saturation", {
    get: function() {
        return _mud_BCS__get_saturation(this.__ptr);
    },
    set: function(value) {
        _mud_BCS__set_saturation(this.__ptr, value);
    }
});
BCS.prototype["__destroy"] = BCS.prototype.__destroy = function() {
    _mud_BCS__destroy(this.__ptr);
};
// CSMShadow
function CSMShadow() {
    this.__ptr = _mud_CSMShadow__construct_0(); this.__type = CSMShadow.__type; getCache(CSMShadow)[this.__ptr] = this;
};
CSMShadow.prototype = Object.create(WrapperObject.prototype);
CSMShadow.prototype.constructor = CSMShadow;
CSMShadow.prototype.__class = CSMShadow;
CSMShadow.__cache = {};
Module['CSMShadow'] = CSMShadow;
CSMShadow.prototype["__destroy"] = CSMShadow.prototype.__destroy = function() {
    _mud_CSMShadow__destroy(this.__ptr);
};
// CubeCamera
function CubeCamera(a0, a1, a2, a3) {
    if (a0 === undefined) { this.__ptr = _mud_CubeCamera__construct_0(); this.__type = CubeCamera.__type; getCache(CubeCamera)[this.__ptr] = this; return; }
    this.__ptr = _mud_CubeCamera__construct_4(/*scene*/a0.__ptr, /*near*/a1, /*far*/a2, /*size*/a3); this.__type = CubeCamera.__type; getCache(CubeCamera)[this.__ptr] = this;
};
CubeCamera.prototype = Object.create(WrapperObject.prototype);
CubeCamera.prototype.constructor = CubeCamera;
CubeCamera.prototype.__class = CubeCamera;
CubeCamera.__cache = {};
Module['CubeCamera'] = CubeCamera;
CubeCamera.prototype["render"] = CubeCamera.prototype.render = function(a0, a1, a2) {
    return wrapPointer(_mud_CubeCamera_render_3(this.__ptr, /*gfx*/a0.__ptr, /*render*/a1.__ptr, /*axis*/a2), Render);
};
Object.defineProperty(CubeCamera.prototype, "cubemap", {
    get: function() {
        return wrapPointer(_mud_CubeCamera__get_cubemap(this.__ptr), CubeTarget);
    }});
Object.defineProperty(CubeCamera.prototype, "size", {
    get: function() {
        return wrapPointer(_mud_CubeCamera__get_size(this.__ptr), v2_uint);
    },
    set: function(value) {
        _mud_CubeCamera__set_size(this.__ptr, value.__ptr);
    }
});
CubeCamera.prototype["__destroy"] = CubeCamera.prototype.__destroy = function() {
    _mud_CubeCamera__destroy(this.__ptr);
};
// CubeTarget
function CubeTarget() {
    this.__ptr = _mud_CubeTarget__construct_0(); this.__type = CubeTarget.__type; getCache(CubeTarget)[this.__ptr] = this;
};
CubeTarget.prototype = Object.create(WrapperObject.prototype);
CubeTarget.prototype.constructor = CubeTarget;
CubeTarget.prototype.__class = CubeTarget;
CubeTarget.__cache = {};
Module['CubeTarget'] = CubeTarget;
CubeTarget.prototype["create"] = CubeTarget.prototype.create = function(a0) {
    _mud_CubeTarget_create_1(this.__ptr, /*size*/a0);
};
CubeTarget.prototype["side"] = CubeTarget.prototype.side = function(a0) {
    return wrapPointer(_mud_CubeTarget_side_1(this.__ptr, /*i*/a0), FrameBuffer);
};
Object.defineProperty(CubeTarget.prototype, "cubemap", {
    get: function() {
        return wrapPointer(_mud_CubeTarget__get_cubemap(this.__ptr), Texture);
    }});
Object.defineProperty(CubeTarget.prototype, "depth", {
    get: function() {
        return wrapPointer(_mud_CubeTarget__get_depth(this.__ptr), Texture);
    }});
Object.defineProperty(CubeTarget.prototype, "size", {
    get: function() {
        return _mud_CubeTarget__get_size(this.__ptr);
    },
    set: function(value) {
        _mud_CubeTarget__set_size(this.__ptr, value);
    }
});
CubeTarget.prototype["__destroy"] = CubeTarget.prototype.__destroy = function() {
    _mud_CubeTarget__destroy(this.__ptr);
};
// DofBlur
function DofBlur() {
    this.__ptr = _mud_DofBlur__construct_0(); this.__type = DofBlur.__type; getCache(DofBlur)[this.__ptr] = this;
};
DofBlur.prototype = Object.create(WrapperObject.prototype);
DofBlur.prototype.constructor = DofBlur;
DofBlur.prototype.__class = DofBlur;
DofBlur.__cache = {};
Module['DofBlur'] = DofBlur;
Object.defineProperty(DofBlur.prototype, "enabled", {
    get: function() {
        return !!(_mud_DofBlur__get_enabled(this.__ptr));
    },
    set: function(value) {
        _mud_DofBlur__set_enabled(this.__ptr, value);
    }
});
Object.defineProperty(DofBlur.prototype, "far", {
    get: function() {
        return wrapPointer(_mud_DofBlur__get_far(this.__ptr), DofParams);
    },
    set: function(value) {
        _mud_DofBlur__set_far(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(DofBlur.prototype, "near", {
    get: function() {
        return wrapPointer(_mud_DofBlur__get_near(this.__ptr), DofParams);
    },
    set: function(value) {
        _mud_DofBlur__set_near(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(DofBlur.prototype, "max_coc_radius", {
    get: function() {
        return _mud_DofBlur__get_max_coc_radius(this.__ptr);
    },
    set: function(value) {
        _mud_DofBlur__set_max_coc_radius(this.__ptr, value);
    }
});
DofBlur.prototype["__destroy"] = DofBlur.prototype.__destroy = function() {
    _mud_DofBlur__destroy(this.__ptr);
};
// DofParams
function DofParams() {
    this.__ptr = _mud_DofParams__construct_0(); this.__type = DofParams.__type; getCache(DofParams)[this.__ptr] = this;
};
DofParams.prototype = Object.create(WrapperObject.prototype);
DofParams.prototype.constructor = DofParams;
DofParams.prototype.__class = DofParams;
DofParams.__cache = {};
Module['DofParams'] = DofParams;
Object.defineProperty(DofParams.prototype, "distance", {
    get: function() {
        return _mud_DofParams__get_distance(this.__ptr);
    },
    set: function(value) {
        _mud_DofParams__set_distance(this.__ptr, value);
    }
});
Object.defineProperty(DofParams.prototype, "transition", {
    get: function() {
        return _mud_DofParams__get_transition(this.__ptr);
    },
    set: function(value) {
        _mud_DofParams__set_transition(this.__ptr, value);
    }
});
Object.defineProperty(DofParams.prototype, "radius", {
    get: function() {
        return _mud_DofParams__get_radius(this.__ptr);
    },
    set: function(value) {
        _mud_DofParams__set_radius(this.__ptr, value);
    }
});
DofParams.prototype["__destroy"] = DofParams.prototype.__destroy = function() {
    _mud_DofParams__destroy(this.__ptr);
};
// GIProbe
function GIProbe() { throw "cannot construct a GIProbe, no constructor in IDL" }
GIProbe.prototype = Object.create(WrapperObject.prototype);
GIProbe.prototype.constructor = GIProbe;
GIProbe.prototype.__class = GIProbe;
GIProbe.__cache = {};
Module['GIProbe'] = GIProbe;
GIProbe.prototype["__destroy"] = GIProbe.prototype.__destroy = function() {
    _mud_GIProbe__destroy(this.__ptr);
};
// Glow
function Glow() {
    this.__ptr = _mud_Glow__construct_0(); this.__type = Glow.__type; getCache(Glow)[this.__ptr] = this;
};
Glow.prototype = Object.create(WrapperObject.prototype);
Glow.prototype.constructor = Glow;
Glow.prototype.__class = Glow;
Glow.__cache = {};
Module['Glow'] = Glow;
Object.defineProperty(Glow.prototype, "enabled", {
    get: function() {
        return !!(_mud_Glow__get_enabled(this.__ptr));
    },
    set: function(value) {
        _mud_Glow__set_enabled(this.__ptr, value);
    }
});
Object.defineProperty(Glow.prototype, "levels_1_4", {
    get: function() {
        return wrapPointer(_mud_Glow__get_levels_1_4(this.__ptr), v4_float);
    },
    set: function(value) {
        _mud_Glow__set_levels_1_4(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Glow.prototype, "levels_5_8", {
    get: function() {
        return wrapPointer(_mud_Glow__get_levels_5_8(this.__ptr), v4_float);
    },
    set: function(value) {
        _mud_Glow__set_levels_5_8(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Glow.prototype, "intensity", {
    get: function() {
        return _mud_Glow__get_intensity(this.__ptr);
    },
    set: function(value) {
        _mud_Glow__set_intensity(this.__ptr, value);
    }
});
Object.defineProperty(Glow.prototype, "bloom", {
    get: function() {
        return _mud_Glow__get_bloom(this.__ptr);
    },
    set: function(value) {
        _mud_Glow__set_bloom(this.__ptr, value);
    }
});
Object.defineProperty(Glow.prototype, "bleed_threshold", {
    get: function() {
        return _mud_Glow__get_bleed_threshold(this.__ptr);
    },
    set: function(value) {
        _mud_Glow__set_bleed_threshold(this.__ptr, value);
    }
});
Object.defineProperty(Glow.prototype, "bleed_scale", {
    get: function() {
        return _mud_Glow__get_bleed_scale(this.__ptr);
    },
    set: function(value) {
        _mud_Glow__set_bleed_scale(this.__ptr, value);
    }
});
Object.defineProperty(Glow.prototype, "bicubic_filter", {
    get: function() {
        return !!(_mud_Glow__get_bicubic_filter(this.__ptr));
    },
    set: function(value) {
        _mud_Glow__set_bicubic_filter(this.__ptr, value);
    }
});
Glow.prototype["__destroy"] = Glow.prototype.__destroy = function() {
    _mud_Glow__destroy(this.__ptr);
};
// LightShadow
function LightShadow() {
    this.__ptr = _mud_LightShadow__construct_0(); this.__type = LightShadow.__type; getCache(LightShadow)[this.__ptr] = this;
};
LightShadow.prototype = Object.create(WrapperObject.prototype);
LightShadow.prototype.constructor = LightShadow;
LightShadow.prototype.__class = LightShadow;
LightShadow.__cache = {};
Module['LightShadow'] = LightShadow;
LightShadow.prototype["__destroy"] = LightShadow.prototype.__destroy = function() {
    _mud_LightShadow__destroy(this.__ptr);
};
// Lightmap
function Lightmap() { throw "cannot construct a Lightmap, no constructor in IDL" }
Lightmap.prototype = Object.create(WrapperObject.prototype);
Lightmap.prototype.constructor = Lightmap;
Lightmap.prototype.__class = Lightmap;
Lightmap.__cache = {};
Module['Lightmap'] = Lightmap;
Lightmap.prototype["__destroy"] = Lightmap.prototype.__destroy = function() {
    _mud_Lightmap__destroy(this.__ptr);
};
// LightmapAtlas
function LightmapAtlas() { throw "cannot construct a LightmapAtlas, no constructor in IDL" }
LightmapAtlas.prototype = Object.create(WrapperObject.prototype);
LightmapAtlas.prototype.constructor = LightmapAtlas;
LightmapAtlas.prototype.__class = LightmapAtlas;
LightmapAtlas.__cache = {};
Module['LightmapAtlas'] = LightmapAtlas;
LightmapAtlas.prototype["__destroy"] = LightmapAtlas.prototype.__destroy = function() {
    _mud_LightmapAtlas__destroy(this.__ptr);
};
// LightmapItem
function LightmapItem() { throw "cannot construct a LightmapItem, no constructor in IDL" }
LightmapItem.prototype = Object.create(WrapperObject.prototype);
LightmapItem.prototype.constructor = LightmapItem;
LightmapItem.prototype.__class = LightmapItem;
LightmapItem.__cache = {};
Module['LightmapItem'] = LightmapItem;
LightmapItem.prototype["__destroy"] = LightmapItem.prototype.__destroy = function() {
    _mud_LightmapItem__destroy(this.__ptr);
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
        return wrapPointer(_mud_ReflectionProbe__get_node(this.__ptr), Node3);
    }});
Object.defineProperty(ReflectionProbe.prototype, "visible", {
    get: function() {
        return !!(_mud_ReflectionProbe__get_visible(this.__ptr));
    },
    set: function(value) {
        _mud_ReflectionProbe__set_visible(this.__ptr, value);
    }
});
Object.defineProperty(ReflectionProbe.prototype, "intensity", {
    get: function() {
        return _mud_ReflectionProbe__get_intensity(this.__ptr);
    },
    set: function(value) {
        _mud_ReflectionProbe__set_intensity(this.__ptr, value);
    }
});
Object.defineProperty(ReflectionProbe.prototype, "extents", {
    get: function() {
        return wrapPointer(_mud_ReflectionProbe__get_extents(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_ReflectionProbe__set_extents(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ReflectionProbe.prototype, "shadows", {
    get: function() {
        return !!(_mud_ReflectionProbe__get_shadows(this.__ptr));
    },
    set: function(value) {
        _mud_ReflectionProbe__set_shadows(this.__ptr, value);
    }
});
Object.defineProperty(ReflectionProbe.prototype, "dirty", {
    get: function() {
        return !!(_mud_ReflectionProbe__get_dirty(this.__ptr));
    },
    set: function(value) {
        _mud_ReflectionProbe__set_dirty(this.__ptr, value);
    }
});
ReflectionProbe.prototype["__destroy"] = ReflectionProbe.prototype.__destroy = function() {
    _mud_ReflectionProbe__destroy(this.__ptr);
};
// Tonemap
function Tonemap() {
    this.__ptr = _mud_Tonemap__construct_0(); this.__type = Tonemap.__type; getCache(Tonemap)[this.__ptr] = this;
};
Tonemap.prototype = Object.create(WrapperObject.prototype);
Tonemap.prototype.constructor = Tonemap;
Tonemap.prototype.__class = Tonemap;
Tonemap.__cache = {};
Module['Tonemap'] = Tonemap;
Object.defineProperty(Tonemap.prototype, "mode", {
    get: function() {
        return _mud_Tonemap__get_mode(this.__ptr);
    },
    set: function(value) {
        _mud_Tonemap__set_mode(this.__ptr, value);
    }
});
Object.defineProperty(Tonemap.prototype, "enabled", {
    get: function() {
        return !!(_mud_Tonemap__get_enabled(this.__ptr));
    },
    set: function(value) {
        _mud_Tonemap__set_enabled(this.__ptr, value);
    }
});
Object.defineProperty(Tonemap.prototype, "exposure", {
    get: function() {
        return _mud_Tonemap__get_exposure(this.__ptr);
    },
    set: function(value) {
        _mud_Tonemap__set_exposure(this.__ptr, value);
    }
});
Object.defineProperty(Tonemap.prototype, "white_point", {
    get: function() {
        return _mud_Tonemap__get_white_point(this.__ptr);
    },
    set: function(value) {
        _mud_Tonemap__set_white_point(this.__ptr, value);
    }
});
Tonemap.prototype["__destroy"] = Tonemap.prototype.__destroy = function() {
    _mud_Tonemap__destroy(this.__ptr);
};
// BlockBlur
function BlockBlur() { throw "cannot construct a BlockBlur, no constructor in IDL" }
BlockBlur.prototype = Object.create(GfxBlock.prototype);
BlockBlur.prototype.constructor = BlockBlur;
BlockBlur.prototype.__class = BlockBlur;
BlockBlur.__cache = {};
Module['BlockBlur'] = BlockBlur;
BlockBlur.prototype["__destroy"] = BlockBlur.prototype.__destroy = function() {
    _mud_BlockBlur__destroy(this.__ptr);
};
// BlockDofBlur
function BlockDofBlur() { throw "cannot construct a BlockDofBlur, no constructor in IDL" }
BlockDofBlur.prototype = Object.create(GfxBlock.prototype);
BlockDofBlur.prototype.constructor = BlockDofBlur;
BlockDofBlur.prototype.__class = BlockDofBlur;
BlockDofBlur.__cache = {};
Module['BlockDofBlur'] = BlockDofBlur;
BlockDofBlur.prototype["__destroy"] = BlockDofBlur.prototype.__destroy = function() {
    _mud_BlockDofBlur__destroy(this.__ptr);
};
// BlockGIBake
function BlockGIBake() { throw "cannot construct a BlockGIBake, no constructor in IDL" }
BlockGIBake.prototype = Object.create(DrawBlock.prototype);
BlockGIBake.prototype.constructor = BlockGIBake;
BlockGIBake.prototype.__class = BlockGIBake;
BlockGIBake.__cache = {};
Module['BlockGIBake'] = BlockGIBake;
BlockGIBake.prototype["__destroy"] = BlockGIBake.prototype.__destroy = function() {
    _mud_BlockGIBake__destroy(this.__ptr);
};
// BlockGITrace
function BlockGITrace() { throw "cannot construct a BlockGITrace, no constructor in IDL" }
BlockGITrace.prototype = Object.create(DrawBlock.prototype);
BlockGITrace.prototype.constructor = BlockGITrace;
BlockGITrace.prototype.__class = BlockGITrace;
BlockGITrace.__cache = {};
Module['BlockGITrace'] = BlockGITrace;
BlockGITrace.prototype["__destroy"] = BlockGITrace.prototype.__destroy = function() {
    _mud_BlockGITrace__destroy(this.__ptr);
};
// BlockGeometry
function BlockGeometry() { throw "cannot construct a BlockGeometry, no constructor in IDL" }
BlockGeometry.prototype = Object.create(DrawBlock.prototype);
BlockGeometry.prototype.constructor = BlockGeometry;
BlockGeometry.prototype.__class = BlockGeometry;
BlockGeometry.__cache = {};
Module['BlockGeometry'] = BlockGeometry;
BlockGeometry.prototype["__destroy"] = BlockGeometry.prototype.__destroy = function() {
    _mud_BlockGeometry__destroy(this.__ptr);
};
// BlockGlow
function BlockGlow() { throw "cannot construct a BlockGlow, no constructor in IDL" }
BlockGlow.prototype = Object.create(GfxBlock.prototype);
BlockGlow.prototype.constructor = BlockGlow;
BlockGlow.prototype.__class = BlockGlow;
BlockGlow.__cache = {};
Module['BlockGlow'] = BlockGlow;
BlockGlow.prototype["__destroy"] = BlockGlow.prototype.__destroy = function() {
    _mud_BlockGlow__destroy(this.__ptr);
};
// BlockLight
function BlockLight() { throw "cannot construct a BlockLight, no constructor in IDL" }
BlockLight.prototype = Object.create(DrawBlock.prototype);
BlockLight.prototype.constructor = BlockLight;
BlockLight.prototype.__class = BlockLight;
BlockLight.__cache = {};
Module['BlockLight'] = BlockLight;
BlockLight.prototype["__destroy"] = BlockLight.prototype.__destroy = function() {
    _mud_BlockLight__destroy(this.__ptr);
};
// BlockLightmap
function BlockLightmap() { throw "cannot construct a BlockLightmap, no constructor in IDL" }
BlockLightmap.prototype = Object.create(DrawBlock.prototype);
BlockLightmap.prototype.constructor = BlockLightmap;
BlockLightmap.prototype.__class = BlockLightmap;
BlockLightmap.__cache = {};
Module['BlockLightmap'] = BlockLightmap;
BlockLightmap.prototype["__destroy"] = BlockLightmap.prototype.__destroy = function() {
    _mud_BlockLightmap__destroy(this.__ptr);
};
// BlockRadiance
function BlockRadiance() { throw "cannot construct a BlockRadiance, no constructor in IDL" }
BlockRadiance.prototype = Object.create(DrawBlock.prototype);
BlockRadiance.prototype.constructor = BlockRadiance;
BlockRadiance.prototype.__class = BlockRadiance;
BlockRadiance.__cache = {};
Module['BlockRadiance'] = BlockRadiance;
BlockRadiance.prototype["__destroy"] = BlockRadiance.prototype.__destroy = function() {
    _mud_BlockRadiance__destroy(this.__ptr);
};
// BlockReflection
function BlockReflection() { throw "cannot construct a BlockReflection, no constructor in IDL" }
BlockReflection.prototype = Object.create(DrawBlock.prototype);
BlockReflection.prototype.constructor = BlockReflection;
BlockReflection.prototype.__class = BlockReflection;
BlockReflection.__cache = {};
Module['BlockReflection'] = BlockReflection;
BlockReflection.prototype["__destroy"] = BlockReflection.prototype.__destroy = function() {
    _mud_BlockReflection__destroy(this.__ptr);
};
// BlockShadow
function BlockShadow() { throw "cannot construct a BlockShadow, no constructor in IDL" }
BlockShadow.prototype = Object.create(DrawBlock.prototype);
BlockShadow.prototype.constructor = BlockShadow;
BlockShadow.prototype.__class = BlockShadow;
BlockShadow.__cache = {};
Module['BlockShadow'] = BlockShadow;
BlockShadow.prototype["__destroy"] = BlockShadow.prototype.__destroy = function() {
    _mud_BlockShadow__destroy(this.__ptr);
};
// BlockTonemap
function BlockTonemap() { throw "cannot construct a BlockTonemap, no constructor in IDL" }
BlockTonemap.prototype = Object.create(GfxBlock.prototype);
BlockTonemap.prototype.constructor = BlockTonemap;
BlockTonemap.prototype.__class = BlockTonemap;
BlockTonemap.__cache = {};
Module['BlockTonemap'] = BlockTonemap;
BlockTonemap.prototype["__destroy"] = BlockTonemap.prototype.__destroy = function() {
    _mud_BlockTonemap__destroy(this.__ptr);
};
// CSMSlice
function CSMSlice() {
    this.__ptr = _mud_CSMSlice__construct_0(); this.__type = CSMSlice.__type; getCache(CSMSlice)[this.__ptr] = this;
};
CSMSlice.prototype = Object.create(LightShadow.prototype);
CSMSlice.prototype.constructor = CSMSlice;
CSMSlice.prototype.__class = CSMSlice;
CSMSlice.__cache = {};
Module['CSMSlice'] = CSMSlice;
CSMSlice.prototype["__destroy"] = CSMSlice.prototype.__destroy = function() {
    _mud_CSMSlice__destroy(this.__ptr);
};
Module['begin_pbr_render'] = function(a0, a1) {
    _mud_begin_pbr_render_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_gi_probes'] = function(a0, a1) {
    _mud_pass_gi_probes_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_shadowmaps'] = function(a0, a1) {
    _mud_pass_shadowmaps_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_shadow'] = function(a0, a1) {
    _mud_pass_shadow_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_opaque'] = function(a0, a1) {
    _mud_pass_opaque_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_alpha'] = function(a0, a1) {
    _mud_pass_alpha_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_geometry'] = function(a0, a1) {
    _mud_pass_geometry_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_lights'] = function(a0, a1) {
    _mud_pass_lights_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_voxel_gi'] = function(a0, a1) {
    _mud_pass_voxel_gi_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_lightmap'] = function(a0, a1) {
    _mud_pass_lightmap_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_begin_post'] = function(a0, a1) {
    _mud_pass_begin_post_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_post_auto'] = function(a0, a1) {
    _mud_pass_post_auto_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_post_effects'] = function(a0, a1, a2, a3, a4, a5) {
    _mud_pass_post_effects_6(/*gfx*/a0.__ptr, /*render*/a1.__ptr, /*dof*/a2.__ptr, /*glow*/a3.__ptr, /*tonemap*/a4.__ptr, /*bcs*/a5.__ptr);
};
Module['render_pbr_forward'] = function(a0, a1) {
    _mud_render_pbr_forward_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['render_pbr_deferred'] = function(a0, a1) {
    _mud_render_pbr_deferred_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['render_shadow'] = function(a0, a1) {
    _mud_render_shadow_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['render_voxel'] = function(a0, a1) {
    _mud_render_voxel_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['render_lightmap'] = function(a0, a1) {
    _mud_render_lightmap_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['render_reflection'] = function(a0, a1) {
    _mud_render_reflection_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pipeline_pbr'] = function(a0, a1, a2) {
    if (a2 === undefined) { _mud_pipeline_pbr_2(/*gfx*/a0.__ptr, /*pipeline*/a1.__ptr); return; }
    _mud_pipeline_pbr_3(/*gfx*/a0.__ptr, /*pipeline*/a1.__ptr, /*deferred*/a2);
};
Module['gfx']['setup_pipeline_pbr'] = function(a0) {
    _mud_gfx_setup_pipeline_pbr_1(/*gfx*/a0.__ptr);
};
Module['gfx']['gi_probe'] = function(a0, a1, a2) {
    return wrapPointer(_mud_gfx_gi_probe_3(/*parent*/a0.__ptr, /*subdiv*/a1, /*extents*/a2.__ptr), GIProbe);
};
Module['gfx']['lightmap'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_gfx_lightmap_2(/*parent*/a0.__ptr, /*resolution*/a1), LightmapAtlas); }
    if (a3 === undefined) { return wrapPointer(_mud_gfx_lightmap_3(/*parent*/a0.__ptr, /*resolution*/a1, /*density*/a2), LightmapAtlas); }
    return wrapPointer(_mud_gfx_lightmap_4(/*parent*/a0.__ptr, /*resolution*/a1, /*density*/a2, ensureString(/*save_path*/a3)), LightmapAtlas);
};
Module['pass_dofblur'] = function(a0, a1, a2) {
    _mud_pass_dofblur_3(/*gfx*/a0.__ptr, /*render*/a1.__ptr, /*blur*/a2.__ptr);
};
Module['pass_glow'] = function(a0, a1, a2) {
    _mud_pass_glow_3(/*gfx*/a0.__ptr, /*render*/a1.__ptr, /*glow*/a2.__ptr);
};
Module['pass_tonemap'] = function(a0, a1, a2, a3) {
    _mud_pass_tonemap_4(/*gfx*/a0.__ptr, /*render*/a1.__ptr, /*tonemap*/a2.__ptr, /*bcs*/a3.__ptr);
};

(function() {
    function setup() {
        BCS.__type = _mud_BCS__type();
        CSMShadow.__type = _mud_CSMShadow__type();
        CubeCamera.__type = _mud_CubeCamera__type();
        CubeTarget.__type = _mud_CubeTarget__type();
        DofBlur.__type = _mud_DofBlur__type();
        DofParams.__type = _mud_DofParams__type();
        GIProbe.__type = _mud_GIProbe__type();
        Glow.__type = _mud_Glow__type();
        LightShadow.__type = _mud_LightShadow__type();
        Lightmap.__type = _mud_Lightmap__type();
        LightmapAtlas.__type = _mud_LightmapAtlas__type();
        LightmapItem.__type = _mud_LightmapItem__type();
        ReflectionProbe.__type = _mud_ReflectionProbe__type();
        Tonemap.__type = _mud_Tonemap__type();
        BlockBlur.__type = _mud_BlockBlur__type();
        BlockDofBlur.__type = _mud_BlockDofBlur__type();
        BlockGIBake.__type = _mud_BlockGIBake__type();
        BlockGITrace.__type = _mud_BlockGITrace__type();
        BlockGeometry.__type = _mud_BlockGeometry__type();
        BlockGlow.__type = _mud_BlockGlow__type();
        BlockLight.__type = _mud_BlockLight__type();
        BlockLightmap.__type = _mud_BlockLightmap__type();
        BlockRadiance.__type = _mud_BlockRadiance__type();
        BlockReflection.__type = _mud_BlockReflection__type();
        BlockShadow.__type = _mud_BlockShadow__type();
        BlockTonemap.__type = _mud_BlockTonemap__type();
        CSMSlice.__type = _mud_CSMSlice__type();
        // TonemapMode
        Module['TonemapMode'] = Module['TonemapMode'] || {};
        Module['TonemapMode']['Linear'] = _mud_TonemapMode_Linear();
        Module['TonemapMode']['Reinhardt'] = _mud_TonemapMode_Reinhardt();
        Module['TonemapMode']['Filmic'] = _mud_TonemapMode_Filmic();
        Module['TonemapMode']['ACES'] = _mud_TonemapMode_ACES();
        Module['TonemapMode']['Cineon'] = _mud_TonemapMode_Cineon();
        Module['TonemapMode']['Uncharted2'] = _mud_TonemapMode_Uncharted2();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
