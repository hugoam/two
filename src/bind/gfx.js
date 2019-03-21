Module['stl'] = Module['stl'] || {};
Module['gfx'] = Module['gfx'] || {};
// AnimatedTrack
function AnimatedTrack() {
    this.__ptr = _mud_AnimatedTrack__construct_0(); this.__type = AnimatedTrack.__type; getCache(AnimatedTrack)[this.__ptr] = this;
};
AnimatedTrack.prototype = Object.create(WrapperObject.prototype);
AnimatedTrack.prototype.constructor = AnimatedTrack;
AnimatedTrack.prototype.__class = AnimatedTrack;
AnimatedTrack.__cache = {};
Module['AnimatedTrack'] = AnimatedTrack;
AnimatedTrack.prototype["__destroy"] = AnimatedTrack.prototype.__destroy = function() {
    _mud_AnimatedTrack__destroy(this.__ptr);
};
// Animation
function Animation() { throw "cannot construct a Animation, no constructor in IDL" }
Animation.prototype = Object.create(WrapperObject.prototype);
Animation.prototype.constructor = Animation;
Animation.prototype.__class = Animation;
Animation.__cache = {};
Module['Animation'] = Animation;
Object.defineProperty(Animation.prototype, "name", {
    get: function() {
        return Pointer_stringify(_mud_Animation__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Animation__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Animation.prototype, "length", {
    get: function() {
        return _mud_Animation__get_length(this.__ptr);
    },
    set: function(value) {
        _mud_Animation__set_length(this.__ptr, value);
    }
});
Object.defineProperty(Animation.prototype, "step", {
    get: function() {
        return _mud_Animation__get_step(this.__ptr);
    },
    set: function(value) {
        _mud_Animation__set_step(this.__ptr, value);
    }
});
Animation.prototype["__destroy"] = Animation.prototype.__destroy = function() {
    _mud_Animation__destroy(this.__ptr);
};
// AnimationPlay
function AnimationPlay() {
    this.__ptr = _mud_AnimationPlay__construct_0(); this.__type = AnimationPlay.__type; getCache(AnimationPlay)[this.__ptr] = this;
};
AnimationPlay.prototype = Object.create(WrapperObject.prototype);
AnimationPlay.prototype.constructor = AnimationPlay;
AnimationPlay.prototype.__class = AnimationPlay;
AnimationPlay.__cache = {};
Module['AnimationPlay'] = AnimationPlay;
Object.defineProperty(AnimationPlay.prototype, "animation", {
    get: function() {
        return wrapPointer(_mud_AnimationPlay__get_animation(this.__ptr), Animation);
    },
    set: function(value) {
        _mud_AnimationPlay__set_animation(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(AnimationPlay.prototype, "loop", {
    get: function() {
        return !!(_mud_AnimationPlay__get_loop(this.__ptr));
    },
    set: function(value) {
        _mud_AnimationPlay__set_loop(this.__ptr, value);
    }
});
Object.defineProperty(AnimationPlay.prototype, "speed", {
    get: function() {
        return _mud_AnimationPlay__get_speed(this.__ptr);
    },
    set: function(value) {
        _mud_AnimationPlay__set_speed(this.__ptr, value);
    }
});
Object.defineProperty(AnimationPlay.prototype, "transient", {
    get: function() {
        return !!(_mud_AnimationPlay__get_transient(this.__ptr));
    },
    set: function(value) {
        _mud_AnimationPlay__set_transient(this.__ptr, value);
    }
});
Object.defineProperty(AnimationPlay.prototype, "fadeout", {
    get: function() {
        return _mud_AnimationPlay__get_fadeout(this.__ptr);
    },
    set: function(value) {
        _mud_AnimationPlay__set_fadeout(this.__ptr, value);
    }
});
Object.defineProperty(AnimationPlay.prototype, "fadeout_left", {
    get: function() {
        return _mud_AnimationPlay__get_fadeout_left(this.__ptr);
    },
    set: function(value) {
        _mud_AnimationPlay__set_fadeout_left(this.__ptr, value);
    }
});
Object.defineProperty(AnimationPlay.prototype, "cursor", {
    get: function() {
        return _mud_AnimationPlay__get_cursor(this.__ptr);
    },
    set: function(value) {
        _mud_AnimationPlay__set_cursor(this.__ptr, value);
    }
});
Object.defineProperty(AnimationPlay.prototype, "ended", {
    get: function() {
        return !!(_mud_AnimationPlay__get_ended(this.__ptr));
    },
    set: function(value) {
        _mud_AnimationPlay__set_ended(this.__ptr, value);
    }
});
AnimationPlay.prototype["__destroy"] = AnimationPlay.prototype.__destroy = function() {
    _mud_AnimationPlay__destroy(this.__ptr);
};
// AnimationTrack
function AnimationTrack() { throw "cannot construct a AnimationTrack, no constructor in IDL" }
AnimationTrack.prototype = Object.create(WrapperObject.prototype);
AnimationTrack.prototype.constructor = AnimationTrack;
AnimationTrack.prototype.__class = AnimationTrack;
AnimationTrack.__cache = {};
Module['AnimationTrack'] = AnimationTrack;
Object.defineProperty(AnimationTrack.prototype, "animation", {
    get: function() {
        return wrapPointer(_mud_AnimationTrack__get_animation(this.__ptr), Animation);
    },
    set: function(value) {
        _mud_AnimationTrack__set_animation(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(AnimationTrack.prototype, "node", {
    get: function() {
        return _mud_AnimationTrack__get_node(this.__ptr);
    },
    set: function(value) {
        _mud_AnimationTrack__set_node(this.__ptr, value);
    }
});
Object.defineProperty(AnimationTrack.prototype, "node_name", {
    get: function() {
        return Pointer_stringify(_mud_AnimationTrack__get_node_name(this.__ptr));
    },
    set: function(value) {
        _mud_AnimationTrack__set_node_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(AnimationTrack.prototype, "target", {
    get: function() {
        return _mud_AnimationTrack__get_target(this.__ptr);
    },
    set: function(value) {
        _mud_AnimationTrack__set_target(this.__ptr, value);
    }
});
Object.defineProperty(AnimationTrack.prototype, "value_type", {
    get: function() {
        return wrapPointer(_mud_AnimationTrack__get_value_type(this.__ptr), Type);
    },
    set: function(value) {
        _mud_AnimationTrack__set_value_type(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(AnimationTrack.prototype, "length", {
    get: function() {
        return _mud_AnimationTrack__get_length(this.__ptr);
    },
    set: function(value) {
        _mud_AnimationTrack__set_length(this.__ptr, value);
    }
});
Object.defineProperty(AnimationTrack.prototype, "interpolation", {
    get: function() {
        return _mud_AnimationTrack__get_interpolation(this.__ptr);
    },
    set: function(value) {
        _mud_AnimationTrack__set_interpolation(this.__ptr, value);
    }
});
AnimationTrack.prototype["__destroy"] = AnimationTrack.prototype.__destroy = function() {
    _mud_AnimationTrack__destroy(this.__ptr);
};
// AssetStore<mud::Flow>
function AssetStore_mud_Flow() { throw "cannot construct a AssetStore<mud::Flow>, no constructor in IDL" }
AssetStore_mud_Flow.prototype = Object.create(WrapperObject.prototype);
AssetStore_mud_Flow.prototype.constructor = AssetStore_mud_Flow;
AssetStore_mud_Flow.prototype.__class = AssetStore_mud_Flow;
AssetStore_mud_Flow.__cache = {};
Module['AssetStore_mud_Flow'] = AssetStore_mud_Flow;
AssetStore_mud_Flow.prototype["get"] = AssetStore_mud_Flow.prototype.get = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Flow_get_1(this.__ptr, ensureString(/*name*/a0)), Flow);
};
AssetStore_mud_Flow.prototype["create"] = AssetStore_mud_Flow.prototype.create = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Flow_create_1(this.__ptr, ensureString(/*name*/a0)), Flow);
};
AssetStore_mud_Flow.prototype["fetch"] = AssetStore_mud_Flow.prototype.fetch = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Flow_fetch_1(this.__ptr, ensureString(/*name*/a0)), Flow);
};
AssetStore_mud_Flow.prototype["file"] = AssetStore_mud_Flow.prototype.file = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Flow_file_1(this.__ptr, ensureString(/*name*/a0)), Flow);
};
AssetStore_mud_Flow.prototype["file_at"] = AssetStore_mud_Flow.prototype.file_at = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Flow_file_at_2(this.__ptr, ensureString(/*path*/a0), ensureString(/*name*/a1)), Flow);
};
AssetStore_mud_Flow.prototype["destroy"] = AssetStore_mud_Flow.prototype.destroy = function(a0) {
    ensureCache.prepare();
    _mud_AssetStore_mud_Flow_destroy_1(this.__ptr, ensureString(/*name*/a0));
};
AssetStore_mud_Flow.prototype["clear"] = AssetStore_mud_Flow.prototype.clear = function() {
    _mud_AssetStore_mud_Flow_clear_0(this.__ptr);
};
AssetStore_mud_Flow.prototype["__destroy"] = AssetStore_mud_Flow.prototype.__destroy = function() {
    _mud_AssetStore_mud_Flow__destroy(this.__ptr);
};
// AssetStore<mud::Material>
function AssetStore_mud_Material() { throw "cannot construct a AssetStore<mud::Material>, no constructor in IDL" }
AssetStore_mud_Material.prototype = Object.create(WrapperObject.prototype);
AssetStore_mud_Material.prototype.constructor = AssetStore_mud_Material;
AssetStore_mud_Material.prototype.__class = AssetStore_mud_Material;
AssetStore_mud_Material.__cache = {};
Module['AssetStore_mud_Material'] = AssetStore_mud_Material;
AssetStore_mud_Material.prototype["get"] = AssetStore_mud_Material.prototype.get = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Material_get_1(this.__ptr, ensureString(/*name*/a0)), Material);
};
AssetStore_mud_Material.prototype["create"] = AssetStore_mud_Material.prototype.create = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Material_create_1(this.__ptr, ensureString(/*name*/a0)), Material);
};
AssetStore_mud_Material.prototype["fetch"] = AssetStore_mud_Material.prototype.fetch = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Material_fetch_1(this.__ptr, ensureString(/*name*/a0)), Material);
};
AssetStore_mud_Material.prototype["file"] = AssetStore_mud_Material.prototype.file = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Material_file_1(this.__ptr, ensureString(/*name*/a0)), Material);
};
AssetStore_mud_Material.prototype["file_at"] = AssetStore_mud_Material.prototype.file_at = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Material_file_at_2(this.__ptr, ensureString(/*path*/a0), ensureString(/*name*/a1)), Material);
};
AssetStore_mud_Material.prototype["destroy"] = AssetStore_mud_Material.prototype.destroy = function(a0) {
    ensureCache.prepare();
    _mud_AssetStore_mud_Material_destroy_1(this.__ptr, ensureString(/*name*/a0));
};
AssetStore_mud_Material.prototype["clear"] = AssetStore_mud_Material.prototype.clear = function() {
    _mud_AssetStore_mud_Material_clear_0(this.__ptr);
};
AssetStore_mud_Material.prototype["__destroy"] = AssetStore_mud_Material.prototype.__destroy = function() {
    _mud_AssetStore_mud_Material__destroy(this.__ptr);
};
// AssetStore<mud::Model>
function AssetStore_mud_Model() { throw "cannot construct a AssetStore<mud::Model>, no constructor in IDL" }
AssetStore_mud_Model.prototype = Object.create(WrapperObject.prototype);
AssetStore_mud_Model.prototype.constructor = AssetStore_mud_Model;
AssetStore_mud_Model.prototype.__class = AssetStore_mud_Model;
AssetStore_mud_Model.__cache = {};
Module['AssetStore_mud_Model'] = AssetStore_mud_Model;
AssetStore_mud_Model.prototype["get"] = AssetStore_mud_Model.prototype.get = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Model_get_1(this.__ptr, ensureString(/*name*/a0)), Model);
};
AssetStore_mud_Model.prototype["create"] = AssetStore_mud_Model.prototype.create = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Model_create_1(this.__ptr, ensureString(/*name*/a0)), Model);
};
AssetStore_mud_Model.prototype["fetch"] = AssetStore_mud_Model.prototype.fetch = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Model_fetch_1(this.__ptr, ensureString(/*name*/a0)), Model);
};
AssetStore_mud_Model.prototype["file"] = AssetStore_mud_Model.prototype.file = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Model_file_1(this.__ptr, ensureString(/*name*/a0)), Model);
};
AssetStore_mud_Model.prototype["file_at"] = AssetStore_mud_Model.prototype.file_at = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Model_file_at_2(this.__ptr, ensureString(/*path*/a0), ensureString(/*name*/a1)), Model);
};
AssetStore_mud_Model.prototype["destroy"] = AssetStore_mud_Model.prototype.destroy = function(a0) {
    ensureCache.prepare();
    _mud_AssetStore_mud_Model_destroy_1(this.__ptr, ensureString(/*name*/a0));
};
AssetStore_mud_Model.prototype["clear"] = AssetStore_mud_Model.prototype.clear = function() {
    _mud_AssetStore_mud_Model_clear_0(this.__ptr);
};
AssetStore_mud_Model.prototype["__destroy"] = AssetStore_mud_Model.prototype.__destroy = function() {
    _mud_AssetStore_mud_Model__destroy(this.__ptr);
};
// AssetStore<mud::Prefab>
function AssetStore_mud_Prefab() { throw "cannot construct a AssetStore<mud::Prefab>, no constructor in IDL" }
AssetStore_mud_Prefab.prototype = Object.create(WrapperObject.prototype);
AssetStore_mud_Prefab.prototype.constructor = AssetStore_mud_Prefab;
AssetStore_mud_Prefab.prototype.__class = AssetStore_mud_Prefab;
AssetStore_mud_Prefab.__cache = {};
Module['AssetStore_mud_Prefab'] = AssetStore_mud_Prefab;
AssetStore_mud_Prefab.prototype["get"] = AssetStore_mud_Prefab.prototype.get = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Prefab_get_1(this.__ptr, ensureString(/*name*/a0)), Prefab);
};
AssetStore_mud_Prefab.prototype["create"] = AssetStore_mud_Prefab.prototype.create = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Prefab_create_1(this.__ptr, ensureString(/*name*/a0)), Prefab);
};
AssetStore_mud_Prefab.prototype["fetch"] = AssetStore_mud_Prefab.prototype.fetch = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Prefab_fetch_1(this.__ptr, ensureString(/*name*/a0)), Prefab);
};
AssetStore_mud_Prefab.prototype["file"] = AssetStore_mud_Prefab.prototype.file = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Prefab_file_1(this.__ptr, ensureString(/*name*/a0)), Prefab);
};
AssetStore_mud_Prefab.prototype["file_at"] = AssetStore_mud_Prefab.prototype.file_at = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Prefab_file_at_2(this.__ptr, ensureString(/*path*/a0), ensureString(/*name*/a1)), Prefab);
};
AssetStore_mud_Prefab.prototype["destroy"] = AssetStore_mud_Prefab.prototype.destroy = function(a0) {
    ensureCache.prepare();
    _mud_AssetStore_mud_Prefab_destroy_1(this.__ptr, ensureString(/*name*/a0));
};
AssetStore_mud_Prefab.prototype["clear"] = AssetStore_mud_Prefab.prototype.clear = function() {
    _mud_AssetStore_mud_Prefab_clear_0(this.__ptr);
};
AssetStore_mud_Prefab.prototype["__destroy"] = AssetStore_mud_Prefab.prototype.__destroy = function() {
    _mud_AssetStore_mud_Prefab__destroy(this.__ptr);
};
// AssetStore<mud::Program>
function AssetStore_mud_Program() { throw "cannot construct a AssetStore<mud::Program>, no constructor in IDL" }
AssetStore_mud_Program.prototype = Object.create(WrapperObject.prototype);
AssetStore_mud_Program.prototype.constructor = AssetStore_mud_Program;
AssetStore_mud_Program.prototype.__class = AssetStore_mud_Program;
AssetStore_mud_Program.__cache = {};
Module['AssetStore_mud_Program'] = AssetStore_mud_Program;
AssetStore_mud_Program.prototype["get"] = AssetStore_mud_Program.prototype.get = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Program_get_1(this.__ptr, ensureString(/*name*/a0)), Program);
};
AssetStore_mud_Program.prototype["create"] = AssetStore_mud_Program.prototype.create = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Program_create_1(this.__ptr, ensureString(/*name*/a0)), Program);
};
AssetStore_mud_Program.prototype["fetch"] = AssetStore_mud_Program.prototype.fetch = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Program_fetch_1(this.__ptr, ensureString(/*name*/a0)), Program);
};
AssetStore_mud_Program.prototype["file"] = AssetStore_mud_Program.prototype.file = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Program_file_1(this.__ptr, ensureString(/*name*/a0)), Program);
};
AssetStore_mud_Program.prototype["file_at"] = AssetStore_mud_Program.prototype.file_at = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Program_file_at_2(this.__ptr, ensureString(/*path*/a0), ensureString(/*name*/a1)), Program);
};
AssetStore_mud_Program.prototype["destroy"] = AssetStore_mud_Program.prototype.destroy = function(a0) {
    ensureCache.prepare();
    _mud_AssetStore_mud_Program_destroy_1(this.__ptr, ensureString(/*name*/a0));
};
AssetStore_mud_Program.prototype["clear"] = AssetStore_mud_Program.prototype.clear = function() {
    _mud_AssetStore_mud_Program_clear_0(this.__ptr);
};
AssetStore_mud_Program.prototype["__destroy"] = AssetStore_mud_Program.prototype.__destroy = function() {
    _mud_AssetStore_mud_Program__destroy(this.__ptr);
};
// AssetStore<mud::Texture>
function AssetStore_mud_Texture() { throw "cannot construct a AssetStore<mud::Texture>, no constructor in IDL" }
AssetStore_mud_Texture.prototype = Object.create(WrapperObject.prototype);
AssetStore_mud_Texture.prototype.constructor = AssetStore_mud_Texture;
AssetStore_mud_Texture.prototype.__class = AssetStore_mud_Texture;
AssetStore_mud_Texture.__cache = {};
Module['AssetStore_mud_Texture'] = AssetStore_mud_Texture;
AssetStore_mud_Texture.prototype["get"] = AssetStore_mud_Texture.prototype.get = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Texture_get_1(this.__ptr, ensureString(/*name*/a0)), Texture);
};
AssetStore_mud_Texture.prototype["create"] = AssetStore_mud_Texture.prototype.create = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Texture_create_1(this.__ptr, ensureString(/*name*/a0)), Texture);
};
AssetStore_mud_Texture.prototype["fetch"] = AssetStore_mud_Texture.prototype.fetch = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Texture_fetch_1(this.__ptr, ensureString(/*name*/a0)), Texture);
};
AssetStore_mud_Texture.prototype["file"] = AssetStore_mud_Texture.prototype.file = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Texture_file_1(this.__ptr, ensureString(/*name*/a0)), Texture);
};
AssetStore_mud_Texture.prototype["file_at"] = AssetStore_mud_Texture.prototype.file_at = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Texture_file_at_2(this.__ptr, ensureString(/*path*/a0), ensureString(/*name*/a1)), Texture);
};
AssetStore_mud_Texture.prototype["destroy"] = AssetStore_mud_Texture.prototype.destroy = function(a0) {
    ensureCache.prepare();
    _mud_AssetStore_mud_Texture_destroy_1(this.__ptr, ensureString(/*name*/a0));
};
AssetStore_mud_Texture.prototype["clear"] = AssetStore_mud_Texture.prototype.clear = function() {
    _mud_AssetStore_mud_Texture_clear_0(this.__ptr);
};
AssetStore_mud_Texture.prototype["__destroy"] = AssetStore_mud_Texture.prototype.__destroy = function() {
    _mud_AssetStore_mud_Texture__destroy(this.__ptr);
};
// Background
function Background() {
    this.__ptr = _mud_Background__construct_0(); this.__type = Background.__type; getCache(Background)[this.__ptr] = this;
};
Background.prototype = Object.create(WrapperObject.prototype);
Background.prototype.constructor = Background;
Background.prototype.__class = Background;
Background.__cache = {};
Module['Background'] = Background;
Object.defineProperty(Background.prototype, "mode", {
    get: function() {
        return _mud_Background__get_mode(this.__ptr);
    },
    set: function(value) {
        _mud_Background__set_mode(this.__ptr, value);
    }
});
Object.defineProperty(Background.prototype, "colour", {
    get: function() {
        return wrapPointer(_mud_Background__get_colour(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_Background__set_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Background.prototype, "custoprogram", {
    get: function() {
        return wrapPointer(_mud_Background__get_custoprogram(this.__ptr), Program);
    },
    set: function(value) {
        _mud_Background__set_custoprogram(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Background.prototype, "texture", {
    get: function() {
        return wrapPointer(_mud_Background__get_texture(this.__ptr), Texture);
    },
    set: function(value) {
        _mud_Background__set_texture(this.__ptr, value.__ptr);
    }
});
Background.prototype["__destroy"] = Background.prototype.__destroy = function() {
    _mud_Background__destroy(this.__ptr);
};
// Batch
function Batch(a0, a1) {
    if (a0 === undefined) { this.__ptr = _mud_Batch__construct_0(); this.__type = Batch.__type; getCache(Batch)[this.__ptr] = this; return; }
    this.__ptr = _mud_Batch__construct_2(/*item*/a0.__ptr, /*stride*/a1); this.__type = Batch.__type; getCache(Batch)[this.__ptr] = this;
};
Batch.prototype = Object.create(WrapperObject.prototype);
Batch.prototype.constructor = Batch;
Batch.prototype.__class = Batch;
Batch.__cache = {};
Module['Batch'] = Batch;
Batch.prototype["update_aabb"] = Batch.prototype.update_aabb = function(a0) {
    _mud_Batch_update_aabb_1(this.__ptr, ensureFloat32(/*instances*/a0), /*instances*/a0.length);
};
Batch.prototype["transforms"] = Batch.prototype.transforms = function(a0) {
    _mud_Batch_transforms_1(this.__ptr, ensureFloat32(/*instances*/a0), /*instances*/a0.length);
};
Batch.prototype["begin"] = Batch.prototype.begin = function(a0) {
    return _mud_Batch_begin_1(this.__ptr, /*count*/a0);
};
Batch.prototype["commit"] = Batch.prototype.commit = function(a0) {
    _mud_Batch_commit_1(this.__ptr, ensureFloat32(/*data*/a0), /*data*/a0.length);
};
Batch.prototype["cache"] = Batch.prototype.cache = function(a0) {
    _mud_Batch_cache_1(this.__ptr, ensureFloat32(/*data*/a0), /*data*/a0.length);
};
Object.defineProperty(Batch.prototype, "item", {
    get: function() {
        return wrapPointer(_mud_Batch__get_item(this.__ptr), Item);
    },
    set: function(value) {
        _mud_Batch__set_item(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Batch.prototype, "stride", {
    get: function() {
        return _mud_Batch__get_stride(this.__ptr);
    },
    set: function(value) {
        _mud_Batch__set_stride(this.__ptr, value);
    }
});
Batch.prototype["__destroy"] = Batch.prototype.__destroy = function() {
    _mud_Batch__destroy(this.__ptr);
};
// Bone
function Bone() {
    this.__ptr = _mud_Bone__construct_0(); this.__type = Bone.__type; getCache(Bone)[this.__ptr] = this;
};
Bone.prototype = Object.create(WrapperObject.prototype);
Bone.prototype.constructor = Bone;
Bone.prototype.__class = Bone;
Bone.__cache = {};
Module['Bone'] = Bone;
Object.defineProperty(Bone.prototype, "position", {
    get: function() {
        return wrapPointer(_mud_Bone__get_position(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Bone__set_position(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Bone.prototype, "rotation", {
    get: function() {
        return wrapPointer(_mud_Bone__get_rotation(this.__ptr), quat);
    },
    set: function(value) {
        _mud_Bone__set_rotation(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Bone.prototype, "scale", {
    get: function() {
        return wrapPointer(_mud_Bone__get_scale(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Bone__set_scale(this.__ptr, value.__ptr);
    }
});
Bone.prototype["__destroy"] = Bone.prototype.__destroy = function() {
    _mud_Bone__destroy(this.__ptr);
};
// Camera
function Camera() { throw "cannot construct a Camera, no constructor in IDL" }
Camera.prototype = Object.create(WrapperObject.prototype);
Camera.prototype.constructor = Camera;
Camera.prototype.__class = Camera;
Camera.__cache = {};
Module['Camera'] = Camera;
Camera.prototype["set_look_at"] = Camera.prototype.set_look_at = function(a0, a1) {
    _mud_Camera_set_look_at_2(this.__ptr, /*eye*/a0.__ptr, /*target*/a1.__ptr);
};
Camera.prototype["set_isometric"] = Camera.prototype.set_isometric = function(a0, a1) {
    _mud_Camera_set_isometric_2(this.__ptr, /*angle*/a0, /*position*/a1.__ptr);
};
Object.defineProperty(Camera.prototype, "eye", {
    get: function() {
        return wrapPointer(_mud_Camera__get_eye(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Camera__set_eye(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Camera.prototype, "target", {
    get: function() {
        return wrapPointer(_mud_Camera__get_target(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Camera__set_target(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Camera.prototype, "up", {
    get: function() {
        return wrapPointer(_mud_Camera__get_up(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Camera__set_up(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Camera.prototype, "transform", {
    get: function() {
        return wrapPointer(_mud_Camera__get_transform(this.__ptr), mat4);
    },
    set: function(value) {
        _mud_Camera__set_transform(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Camera.prototype, "projection", {
    get: function() {
        return wrapPointer(_mud_Camera__get_projection(this.__ptr), mat4);
    },
    set: function(value) {
        _mud_Camera__set_projection(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Camera.prototype, "fov", {
    get: function() {
        return _mud_Camera__get_fov(this.__ptr);
    },
    set: function(value) {
        _mud_Camera__set_fov(this.__ptr, value);
    }
});
Object.defineProperty(Camera.prototype, "aspect", {
    get: function() {
        return _mud_Camera__get_aspect(this.__ptr);
    },
    set: function(value) {
        _mud_Camera__set_aspect(this.__ptr, value);
    }
});
Object.defineProperty(Camera.prototype, "near", {
    get: function() {
        return _mud_Camera__get_near(this.__ptr);
    },
    set: function(value) {
        _mud_Camera__set_near(this.__ptr, value);
    }
});
Object.defineProperty(Camera.prototype, "far", {
    get: function() {
        return _mud_Camera__get_far(this.__ptr);
    },
    set: function(value) {
        _mud_Camera__set_far(this.__ptr, value);
    }
});
Object.defineProperty(Camera.prototype, "orthographic", {
    get: function() {
        return !!(_mud_Camera__get_orthographic(this.__ptr));
    },
    set: function(value) {
        _mud_Camera__set_orthographic(this.__ptr, value);
    }
});
Object.defineProperty(Camera.prototype, "height", {
    get: function() {
        return _mud_Camera__get_height(this.__ptr);
    },
    set: function(value) {
        _mud_Camera__set_height(this.__ptr, value);
    }
});
Object.defineProperty(Camera.prototype, "optimize_ends", {
    get: function() {
        return !!(_mud_Camera__get_optimize_ends(this.__ptr));
    },
    set: function(value) {
        _mud_Camera__set_optimize_ends(this.__ptr, value);
    }
});
Object.defineProperty(Camera.prototype, "lod_offsets", {
    get: function() {
        return wrapPointer(_mud_Camera__get_lod_offsets(this.__ptr), v4_float);
    },
    set: function(value) {
        _mud_Camera__set_lod_offsets(this.__ptr, value.__ptr);
    }
});
Camera.prototype["__destroy"] = Camera.prototype.__destroy = function() {
    _mud_Camera__destroy(this.__ptr);
};
// Cascade
function Cascade() { throw "cannot construct a Cascade, no constructor in IDL" }
Cascade.prototype = Object.create(WrapperObject.prototype);
Cascade.prototype.constructor = Cascade;
Cascade.prototype.__class = Cascade;
Cascade.__cache = {};
Module['Cascade'] = Cascade;
Object.defineProperty(Cascade.prototype, "texture", {
    get: function() {
        return wrapPointer(_mud_Cascade__get_texture(this.__ptr), Texture);
    }});
Object.defineProperty(Cascade.prototype, "numips", {
    get: function() {
        return _mud_Cascade__get_numips(this.__ptr);
    },
    set: function(value) {
        _mud_Cascade__set_numips(this.__ptr, value);
    }
});
Cascade.prototype["__destroy"] = Cascade.prototype.__destroy = function() {
    _mud_Cascade__destroy(this.__ptr);
};
// Culler
function Culler() { throw "cannot construct a Culler, no constructor in IDL" }
Culler.prototype = Object.create(WrapperObject.prototype);
Culler.prototype.constructor = Culler;
Culler.prototype.__class = Culler;
Culler.__cache = {};
Module['Culler'] = Culler;
Object.defineProperty(Culler.prototype, "viewport", {
    get: function() {
        return wrapPointer(_mud_Culler__get_viewport(this.__ptr), Viewport);
    },
    set: function(value) {
        _mud_Culler__set_viewport(this.__ptr, value.__ptr);
    }
});
Culler.prototype["__destroy"] = Culler.prototype.__destroy = function() {
    _mud_Culler__destroy(this.__ptr);
};
// DepthParams
function DepthParams() {
    this.__ptr = _mud_DepthParams__construct_0(); this.__type = DepthParams.__type; getCache(DepthParams)[this.__ptr] = this;
};
DepthParams.prototype = Object.create(WrapperObject.prototype);
DepthParams.prototype.constructor = DepthParams;
DepthParams.prototype.__class = DepthParams;
DepthParams.__cache = {};
Module['DepthParams'] = DepthParams;
Object.defineProperty(DepthParams.prototype, "depth_bias", {
    get: function() {
        return _mud_DepthParams__get_depth_bias(this.__ptr);
    },
    set: function(value) {
        _mud_DepthParams__set_depth_bias(this.__ptr, value);
    }
});
Object.defineProperty(DepthParams.prototype, "depth_normal_bias", {
    get: function() {
        return _mud_DepthParams__get_depth_normal_bias(this.__ptr);
    },
    set: function(value) {
        _mud_DepthParams__set_depth_normal_bias(this.__ptr, value);
    }
});
Object.defineProperty(DepthParams.prototype, "depth_z_far", {
    get: function() {
        return _mud_DepthParams__get_depth_z_far(this.__ptr);
    },
    set: function(value) {
        _mud_DepthParams__set_depth_z_far(this.__ptr, value);
    }
});
DepthParams.prototype["__destroy"] = DepthParams.prototype.__destroy = function() {
    _mud_DepthParams__destroy(this.__ptr);
};
// Direct
function Direct(a0) {
    if (a0 === undefined) { this.__ptr = _mud_Direct__construct_0(); this.__type = Direct.__type; getCache(Direct)[this.__ptr] = this; return; }
    this.__ptr = _mud_Direct__construct_1(/*item*/a0.__ptr); this.__type = Direct.__type; getCache(Direct)[this.__ptr] = this;
};
Direct.prototype = Object.create(WrapperObject.prototype);
Direct.prototype.constructor = Direct;
Direct.prototype.__class = Direct;
Direct.__cache = {};
Module['Direct'] = Direct;
Object.defineProperty(Direct.prototype, "item", {
    get: function() {
        return wrapPointer(_mud_Direct__get_item(this.__ptr), Item);
    },
    set: function(value) {
        _mud_Direct__set_item(this.__ptr, value.__ptr);
    }
});
Direct.prototype["__destroy"] = Direct.prototype.__destroy = function() {
    _mud_Direct__destroy(this.__ptr);
};
// DistanceParams
function DistanceParams() {
    this.__ptr = _mud_DistanceParams__construct_0(); this.__type = DistanceParams.__type; getCache(DistanceParams)[this.__ptr] = this;
};
DistanceParams.prototype = Object.create(WrapperObject.prototype);
DistanceParams.prototype.constructor = DistanceParams;
DistanceParams.prototype.__class = DistanceParams;
DistanceParams.__cache = {};
Module['DistanceParams'] = DistanceParams;
Object.defineProperty(DistanceParams.prototype, "eye", {
    get: function() {
        return wrapPointer(_mud_DistanceParams__get_eye(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_DistanceParams__set_eye(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(DistanceParams.prototype, "near", {
    get: function() {
        return _mud_DistanceParams__get_near(this.__ptr);
    },
    set: function(value) {
        _mud_DistanceParams__set_near(this.__ptr, value);
    }
});
Object.defineProperty(DistanceParams.prototype, "far", {
    get: function() {
        return _mud_DistanceParams__get_far(this.__ptr);
    },
    set: function(value) {
        _mud_DistanceParams__set_far(this.__ptr, value);
    }
});
DistanceParams.prototype["__destroy"] = DistanceParams.prototype.__destroy = function() {
    _mud_DistanceParams__destroy(this.__ptr);
};
// Flow
function Flow() {
    this.__ptr = _mud_Flow__construct_0(); this.__type = Flow.__type; getCache(Flow)[this.__ptr] = this;
};
Flow.prototype = Object.create(WrapperObject.prototype);
Flow.prototype.constructor = Flow;
Flow.prototype.__class = Flow;
Flow.__cache = {};
Module['Flow'] = Flow;
Object.defineProperty(Flow.prototype, "name", {
    get: function() {
        return Pointer_stringify(_mud_Flow__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Flow__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Flow.prototype, "duration", {
    get: function() {
        return _mud_Flow__get_duration(this.__ptr);
    },
    set: function(value) {
        _mud_Flow__set_duration(this.__ptr, value);
    }
});
Object.defineProperty(Flow.prototype, "start_time", {
    get: function() {
        return _mud_Flow__get_start_time(this.__ptr);
    },
    set: function(value) {
        _mud_Flow__set_start_time(this.__ptr, value);
    }
});
Object.defineProperty(Flow.prototype, "loop", {
    get: function() {
        return !!(_mud_Flow__get_loop(this.__ptr));
    },
    set: function(value) {
        _mud_Flow__set_loop(this.__ptr, value);
    }
});
Object.defineProperty(Flow.prototype, "shape", {
    get: function() {
        return wrapPointer(_mud_Flow__get_shape(this.__ptr), ShapeVar);
    }});
Object.defineProperty(Flow.prototype, "flow", {
    get: function() {
        return _mud_Flow__get_flow(this.__ptr);
    },
    set: function(value) {
        _mud_Flow__set_flow(this.__ptr, value);
    }
});
Object.defineProperty(Flow.prototype, "billboard", {
    get: function() {
        return !!(_mud_Flow__get_billboard(this.__ptr));
    },
    set: function(value) {
        _mud_Flow__set_billboard(this.__ptr, value);
    }
});
Object.defineProperty(Flow.prototype, "direction", {
    get: function() {
        return wrapPointer(_mud_Flow__get_direction(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Flow__set_direction(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Flow.prototype, "rotation", {
    get: function() {
        return wrapPointer(_mud_Flow__get_rotation(this.__ptr), quat);
    },
    set: function(value) {
        _mud_Flow__set_rotation(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Flow.prototype, "blend_mode", {
    get: function() {
        return _mud_Flow__get_blend_mode(this.__ptr);
    },
    set: function(value) {
        _mud_Flow__set_blend_mode(this.__ptr, value);
    }
});
Object.defineProperty(Flow.prototype, "volume", {
    get: function() {
        return wrapPointer(_mud_Flow__get_volume(this.__ptr), ValueTrack_float);
    },
    set: function(value) {
        _mud_Flow__set_volume(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Flow.prototype, "rate", {
    get: function() {
        return wrapPointer(_mud_Flow__get_rate(this.__ptr), ValueTrack_uint32_t);
    },
    set: function(value) {
        _mud_Flow__set_rate(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Flow.prototype, "lifetime", {
    get: function() {
        return wrapPointer(_mud_Flow__get_lifetime(this.__ptr), ValueTrack_float);
    },
    set: function(value) {
        _mud_Flow__set_lifetime(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Flow.prototype, "gravity", {
    get: function() {
        return wrapPointer(_mud_Flow__get_gravity(this.__ptr), ValueTrack_float);
    },
    set: function(value) {
        _mud_Flow__set_gravity(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Flow.prototype, "speed", {
    get: function() {
        return wrapPointer(_mud_Flow__get_speed(this.__ptr), ValueTrack_float);
    },
    set: function(value) {
        _mud_Flow__set_speed(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Flow.prototype, "angle", {
    get: function() {
        return wrapPointer(_mud_Flow__get_angle(this.__ptr), ValueTrack_float);
    },
    set: function(value) {
        _mud_Flow__set_angle(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Flow.prototype, "blend", {
    get: function() {
        return wrapPointer(_mud_Flow__get_blend(this.__ptr), ValueTrack_float);
    },
    set: function(value) {
        _mud_Flow__set_blend(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Flow.prototype, "colour", {
    get: function() {
        return wrapPointer(_mud_Flow__get_colour(this.__ptr), ValueTrack_mud_Colour);
    },
    set: function(value) {
        _mud_Flow__set_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Flow.prototype, "scale", {
    get: function() {
        return wrapPointer(_mud_Flow__get_scale(this.__ptr), ValueTrack_float);
    },
    set: function(value) {
        _mud_Flow__set_scale(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Flow.prototype, "sprite_frame", {
    get: function() {
        return wrapPointer(_mud_Flow__get_sprite_frame(this.__ptr), ValueTrack_float);
    },
    set: function(value) {
        _mud_Flow__set_sprite_frame(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Flow.prototype, "sprite_name", {
    get: function() {
        return Pointer_stringify(_mud_Flow__get_sprite_name(this.__ptr));
    },
    set: function(value) {
        _mud_Flow__set_sprite_name(this.__ptr, ensureString(value));
    }
});
Flow.prototype["__destroy"] = Flow.prototype.__destroy = function() {
    _mud_Flow__destroy(this.__ptr);
};
// Fog
function Fog() {
    this.__ptr = _mud_Fog__construct_0(); this.__type = Fog.__type; getCache(Fog)[this.__ptr] = this;
};
Fog.prototype = Object.create(WrapperObject.prototype);
Fog.prototype.constructor = Fog;
Fog.prototype.__class = Fog;
Fog.__cache = {};
Module['Fog'] = Fog;
Object.defineProperty(Fog.prototype, "enabled", {
    get: function() {
        return !!(_mud_Fog__get_enabled(this.__ptr));
    },
    set: function(value) {
        _mud_Fog__set_enabled(this.__ptr, value);
    }
});
Object.defineProperty(Fog.prototype, "density", {
    get: function() {
        return _mud_Fog__get_density(this.__ptr);
    },
    set: function(value) {
        _mud_Fog__set_density(this.__ptr, value);
    }
});
Object.defineProperty(Fog.prototype, "colour", {
    get: function() {
        return wrapPointer(_mud_Fog__get_colour(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_Fog__set_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Fog.prototype, "depth", {
    get: function() {
        return !!(_mud_Fog__get_depth(this.__ptr));
    },
    set: function(value) {
        _mud_Fog__set_depth(this.__ptr, value);
    }
});
Object.defineProperty(Fog.prototype, "depth_begin", {
    get: function() {
        return _mud_Fog__get_depth_begin(this.__ptr);
    },
    set: function(value) {
        _mud_Fog__set_depth_begin(this.__ptr, value);
    }
});
Object.defineProperty(Fog.prototype, "depth_curve", {
    get: function() {
        return _mud_Fog__get_depth_curve(this.__ptr);
    },
    set: function(value) {
        _mud_Fog__set_depth_curve(this.__ptr, value);
    }
});
Object.defineProperty(Fog.prototype, "height", {
    get: function() {
        return !!(_mud_Fog__get_height(this.__ptr));
    },
    set: function(value) {
        _mud_Fog__set_height(this.__ptr, value);
    }
});
Object.defineProperty(Fog.prototype, "height_min", {
    get: function() {
        return _mud_Fog__get_height_min(this.__ptr);
    },
    set: function(value) {
        _mud_Fog__set_height_min(this.__ptr, value);
    }
});
Object.defineProperty(Fog.prototype, "height_max", {
    get: function() {
        return _mud_Fog__get_height_max(this.__ptr);
    },
    set: function(value) {
        _mud_Fog__set_height_max(this.__ptr, value);
    }
});
Object.defineProperty(Fog.prototype, "height_curve", {
    get: function() {
        return _mud_Fog__get_height_curve(this.__ptr);
    },
    set: function(value) {
        _mud_Fog__set_height_curve(this.__ptr, value);
    }
});
Object.defineProperty(Fog.prototype, "transmit", {
    get: function() {
        return !!(_mud_Fog__get_transmit(this.__ptr));
    },
    set: function(value) {
        _mud_Fog__set_transmit(this.__ptr, value);
    }
});
Object.defineProperty(Fog.prototype, "transmit_curve", {
    get: function() {
        return _mud_Fog__get_transmit_curve(this.__ptr);
    },
    set: function(value) {
        _mud_Fog__set_transmit_curve(this.__ptr, value);
    }
});
Fog.prototype["__destroy"] = Fog.prototype.__destroy = function() {
    _mud_Fog__destroy(this.__ptr);
};
// FrameBuffer
function FrameBuffer() { throw "cannot construct a FrameBuffer, no constructor in IDL" }
FrameBuffer.prototype = Object.create(WrapperObject.prototype);
FrameBuffer.prototype.constructor = FrameBuffer;
FrameBuffer.prototype.__class = FrameBuffer;
FrameBuffer.__cache = {};
Module['FrameBuffer'] = FrameBuffer;
Object.defineProperty(FrameBuffer.prototype, "size", {
    get: function() {
        return wrapPointer(_mud_FrameBuffer__get_size(this.__ptr), v2_uint);
    },
    set: function(value) {
        _mud_FrameBuffer__set_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(FrameBuffer.prototype, "tex", {
    get: function() {
        return wrapPointer(_mud_FrameBuffer__get_tex(this.__ptr), Texture);
    }});
FrameBuffer.prototype["__destroy"] = FrameBuffer.prototype.__destroy = function() {
    _mud_FrameBuffer__destroy(this.__ptr);
};
// Frustum
function Frustum() { throw "cannot construct a Frustum, no constructor in IDL" }
Frustum.prototype = Object.create(WrapperObject.prototype);
Frustum.prototype.constructor = Frustum;
Frustum.prototype.__class = Frustum;
Frustum.__cache = {};
Module['Frustum'] = Frustum;
Object.defineProperty(Frustum.prototype, "fov", {
    get: function() {
        return _mud_Frustum__get_fov(this.__ptr);
    },
    set: function(value) {
        _mud_Frustum__set_fov(this.__ptr, value);
    }
});
Object.defineProperty(Frustum.prototype, "aspect", {
    get: function() {
        return _mud_Frustum__get_aspect(this.__ptr);
    },
    set: function(value) {
        _mud_Frustum__set_aspect(this.__ptr, value);
    }
});
Object.defineProperty(Frustum.prototype, "near", {
    get: function() {
        return _mud_Frustum__get_near(this.__ptr);
    },
    set: function(value) {
        _mud_Frustum__set_near(this.__ptr, value);
    }
});
Object.defineProperty(Frustum.prototype, "far", {
    get: function() {
        return _mud_Frustum__get_far(this.__ptr);
    },
    set: function(value) {
        _mud_Frustum__set_far(this.__ptr, value);
    }
});
Object.defineProperty(Frustum.prototype, "center", {
    get: function() {
        return wrapPointer(_mud_Frustum__get_center(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Frustum__set_center(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Frustum.prototype, "radius", {
    get: function() {
        return _mud_Frustum__get_radius(this.__ptr);
    },
    set: function(value) {
        _mud_Frustum__set_radius(this.__ptr, value);
    }
});
Frustum.prototype["__destroy"] = Frustum.prototype.__destroy = function() {
    _mud_Frustum__destroy(this.__ptr);
};
// FrustumSlice
function FrustumSlice() {
    this.__ptr = _mud_FrustumSlice__construct_0(); this.__type = FrustumSlice.__type; getCache(FrustumSlice)[this.__ptr] = this;
};
FrustumSlice.prototype = Object.create(WrapperObject.prototype);
FrustumSlice.prototype.constructor = FrustumSlice;
FrustumSlice.prototype.__class = FrustumSlice;
FrustumSlice.__cache = {};
Module['FrustumSlice'] = FrustumSlice;
FrustumSlice.prototype["__destroy"] = FrustumSlice.prototype.__destroy = function() {
    _mud_FrustumSlice__destroy(this.__ptr);
};
// GfxBlock
function GfxBlock() { throw "cannot construct a GfxBlock, no constructor in IDL" }
GfxBlock.prototype = Object.create(WrapperObject.prototype);
GfxBlock.prototype.constructor = GfxBlock;
GfxBlock.prototype.__class = GfxBlock;
GfxBlock.__cache = {};
Module['GfxBlock'] = GfxBlock;
Object.defineProperty(GfxBlock.prototype, "type", {
    get: function() {
        return wrapPointer(_mud_GfxBlock__get_type(this.__ptr), Type);
    }});
Object.defineProperty(GfxBlock.prototype, "index", {
    get: function() {
        return _mud_GfxBlock__get_index(this.__ptr);
    },
    set: function(value) {
        _mud_GfxBlock__set_index(this.__ptr, value);
    }
});
GfxBlock.prototype["__destroy"] = GfxBlock.prototype.__destroy = function() {
    _mud_GfxBlock__destroy(this.__ptr);
};
// GfxWindow
function GfxWindow() { throw "cannot construct a GfxWindow, no constructor in IDL" }
GfxWindow.prototype = Object.create(WrapperObject.prototype);
GfxWindow.prototype.constructor = GfxWindow;
GfxWindow.prototype.__class = GfxWindow;
GfxWindow.__cache = {};
Module['GfxWindow'] = GfxWindow;
GfxWindow.prototype["__destroy"] = GfxWindow.prototype.__destroy = function() {
    _mud_GfxWindow__destroy(this.__ptr);
};
// Gnode
function Gnode() { throw "cannot construct a Gnode, no constructor in IDL" }
Gnode.prototype = Object.create(WrapperObject.prototype);
Gnode.prototype.constructor = Gnode;
Gnode.prototype.__class = Gnode;
Gnode.__cache = {};
Module['Gnode'] = Gnode;
Gnode.prototype["__destroy"] = Gnode.prototype.__destroy = function() {
    _mud_Gnode__destroy(this.__ptr);
};
// GpuMesh
function GpuMesh() {
    this.__ptr = _mud_GpuMesh__construct_0(); this.__type = GpuMesh.__type; getCache(GpuMesh)[this.__ptr] = this;
};
GpuMesh.prototype = Object.create(WrapperObject.prototype);
GpuMesh.prototype.constructor = GpuMesh;
GpuMesh.prototype.__class = GpuMesh;
GpuMesh.__cache = {};
Module['GpuMesh'] = GpuMesh;
GpuMesh.prototype["__destroy"] = GpuMesh.prototype.__destroy = function() {
    _mud_GpuMesh__destroy(this.__ptr);
};
// ImmediateDraw
function ImmediateDraw() { throw "cannot construct a ImmediateDraw, no constructor in IDL" }
ImmediateDraw.prototype = Object.create(WrapperObject.prototype);
ImmediateDraw.prototype.constructor = ImmediateDraw;
ImmediateDraw.prototype.__class = ImmediateDraw;
ImmediateDraw.__cache = {};
Module['ImmediateDraw'] = ImmediateDraw;
ImmediateDraw.prototype["__destroy"] = ImmediateDraw.prototype.__destroy = function() {
    _mud_ImmediateDraw__destroy(this.__ptr);
};
// Import
function Import() { throw "cannot construct a Import, no constructor in IDL" }
Import.prototype = Object.create(WrapperObject.prototype);
Import.prototype.constructor = Import;
Import.prototype.__class = Import;
Import.__cache = {};
Module['Import'] = Import;
Object.defineProperty(Import.prototype, "name", {
    get: function() {
        return Pointer_stringify(_mud_Import__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Import__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Import.prototype, "file", {
    get: function() {
        return Pointer_stringify(_mud_Import__get_file(this.__ptr));
    },
    set: function(value) {
        _mud_Import__set_file(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Import.prototype, "path", {
    get: function() {
        return Pointer_stringify(_mud_Import__get_path(this.__ptr));
    },
    set: function(value) {
        _mud_Import__set_path(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Import.prototype, "config", {
    get: function() {
        return wrapPointer(_mud_Import__get_config(this.__ptr), ImportConfig);
    },
    set: function(value) {
        _mud_Import__set_config(this.__ptr, value.__ptr);
    }
});
Import.prototype["__destroy"] = Import.prototype.__destroy = function() {
    _mud_Import__destroy(this.__ptr);
};
// ImportConfig
function ImportConfig() {
    this.__ptr = _mud_ImportConfig__construct_0(); this.__type = ImportConfig.__type; getCache(ImportConfig)[this.__ptr] = this;
};
ImportConfig.prototype = Object.create(WrapperObject.prototype);
ImportConfig.prototype.constructor = ImportConfig;
ImportConfig.prototype.__class = ImportConfig;
ImportConfig.__cache = {};
Module['ImportConfig'] = ImportConfig;
Object.defineProperty(ImportConfig.prototype, "format", {
    get: function() {
        return _mud_ImportConfig__get_format(this.__ptr);
    },
    set: function(value) {
        _mud_ImportConfig__set_format(this.__ptr, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "position", {
    get: function() {
        return wrapPointer(_mud_ImportConfig__get_position(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_ImportConfig__set_position(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ImportConfig.prototype, "rotation", {
    get: function() {
        return wrapPointer(_mud_ImportConfig__get_rotation(this.__ptr), quat);
    },
    set: function(value) {
        _mud_ImportConfig__set_rotation(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ImportConfig.prototype, "scale", {
    get: function() {
        return wrapPointer(_mud_ImportConfig__get_scale(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_ImportConfig__set_scale(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ImportConfig.prototype, "transform", {
    get: function() {
        return wrapPointer(_mud_ImportConfig__get_transform(this.__ptr), mat4);
    },
    set: function(value) {
        _mud_ImportConfig__set_transform(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ImportConfig.prototype, "suffix", {
    get: function() {
        return Pointer_stringify(_mud_ImportConfig__get_suffix(this.__ptr));
    },
    set: function(value) {
        _mud_ImportConfig__set_suffix(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(ImportConfig.prototype, "force_reimport", {
    get: function() {
        return !!(_mud_ImportConfig__get_force_reimport(this.__ptr));
    },
    set: function(value) {
        _mud_ImportConfig__set_force_reimport(this.__ptr, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "cache_geometry", {
    get: function() {
        return !!(_mud_ImportConfig__get_cache_geometry(this.__ptr));
    },
    set: function(value) {
        _mud_ImportConfig__set_cache_geometry(this.__ptr, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "optimize_geometry", {
    get: function() {
        return !!(_mud_ImportConfig__get_optimize_geometry(this.__ptr));
    },
    set: function(value) {
        _mud_ImportConfig__set_optimize_geometry(this.__ptr, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "need_normals", {
    get: function() {
        return !!(_mud_ImportConfig__get_need_normals(this.__ptr));
    },
    set: function(value) {
        _mud_ImportConfig__set_need_normals(this.__ptr, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "need_uvs", {
    get: function() {
        return !!(_mud_ImportConfig__get_need_uvs(this.__ptr));
    },
    set: function(value) {
        _mud_ImportConfig__set_need_uvs(this.__ptr, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "flags", {
    get: function() {
        return _mud_ImportConfig__get_flags(this.__ptr);
    },
    set: function(value) {
        _mud_ImportConfig__set_flags(this.__ptr, value);
    }
});
ImportConfig.prototype["__destroy"] = ImportConfig.prototype.__destroy = function() {
    _mud_ImportConfig__destroy(this.__ptr);
};
// Item
function Item(a0, a1, a2, a3) {
    if (a0 === undefined) { this.__ptr = _mud_Item__construct_0(); this.__type = Item.__type; getCache(Item)[this.__ptr] = this; return; }
    if (a2 === undefined) { this.__ptr = _mud_Item__construct_2(/*node*/a0.__ptr, /*model*/a1.__ptr); this.__type = Item.__type; getCache(Item)[this.__ptr] = this; return; }
    if (a3 === undefined) { this.__ptr = _mud_Item__construct_3(/*node*/a0.__ptr, /*model*/a1.__ptr, /*flags*/a2); this.__type = Item.__type; getCache(Item)[this.__ptr] = this; return; }
    this.__ptr = _mud_Item__construct_4(/*node*/a0.__ptr, /*model*/a1.__ptr, /*flags*/a2, /*material*/a3.__ptr); this.__type = Item.__type; getCache(Item)[this.__ptr] = this;
};
Item.prototype = Object.create(WrapperObject.prototype);
Item.prototype.constructor = Item;
Item.prototype.__class = Item;
Item.__cache = {};
Module['Item'] = Item;
Item.prototype["update_aabb"] = Item.prototype.update_aabb = function() {
    _mud_Item_update_aabb_0(this.__ptr);
};
Object.defineProperty(Item.prototype, "node", {
    get: function() {
        return wrapPointer(_mud_Item__get_node(this.__ptr), Node3);
    },
    set: function(value) {
        _mud_Item__set_node(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Item.prototype, "model", {
    get: function() {
        return wrapPointer(_mud_Item__get_model(this.__ptr), Model);
    },
    set: function(value) {
        _mud_Item__set_model(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Item.prototype, "flags", {
    get: function() {
        return _mud_Item__get_flags(this.__ptr);
    },
    set: function(value) {
        _mud_Item__set_flags(this.__ptr, value);
    }
});
Object.defineProperty(Item.prototype, "colour", {
    get: function() {
        return wrapPointer(_mud_Item__get_colour(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_Item__set_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Item.prototype, "material", {
    get: function() {
        return wrapPointer(_mud_Item__get_material(this.__ptr), Material);
    },
    set: function(value) {
        _mud_Item__set_material(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Item.prototype, "visible", {
    get: function() {
        return !!(_mud_Item__get_visible(this.__ptr));
    },
    set: function(value) {
        _mud_Item__set_visible(this.__ptr, value);
    }
});
Object.defineProperty(Item.prototype, "shadow", {
    get: function() {
        return _mud_Item__get_shadow(this.__ptr);
    },
    set: function(value) {
        _mud_Item__set_shadow(this.__ptr, value);
    }
});
Object.defineProperty(Item.prototype, "rig", {
    get: function() {
        return wrapPointer(_mud_Item__get_rig(this.__ptr), Rig);
    },
    set: function(value) {
        _mud_Item__set_rig(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Item.prototype, "aabb", {
    get: function() {
        return wrapPointer(_mud_Item__get_aabb(this.__ptr), Aabb);
    },
    set: function(value) {
        _mud_Item__set_aabb(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Item.prototype, "batch", {
    get: function() {
        return wrapPointer(_mud_Item__get_batch(this.__ptr), Batch);
    },
    set: function(value) {
        _mud_Item__set_batch(this.__ptr, value.__ptr);
    }
});
Item.prototype["__destroy"] = Item.prototype.__destroy = function() {
    _mud_Item__destroy(this.__ptr);
};
// Joint
function Joint() {
    this.__ptr = _mud_Joint__construct_0(); this.__type = Joint.__type; getCache(Joint)[this.__ptr] = this;
};
Joint.prototype = Object.create(WrapperObject.prototype);
Joint.prototype.constructor = Joint;
Joint.prototype.__class = Joint;
Joint.__cache = {};
Module['Joint'] = Joint;
Joint.prototype["__destroy"] = Joint.prototype.__destroy = function() {
    _mud_Joint__destroy(this.__ptr);
};
// Light
function Light(a0, a1, a2, a3, a4, a5) {
    if (a1 === undefined) { this.__ptr = _mud_Light__construct_1(/*node*/a0.__ptr); this.__type = Light.__type; getCache(Light)[this.__ptr] = this; return; }
    if (a2 === undefined) { this.__ptr = _mud_Light__construct_2(/*node*/a0.__ptr, /*type*/a1); this.__type = Light.__type; getCache(Light)[this.__ptr] = this; return; }
    if (a3 === undefined) { this.__ptr = _mud_Light__construct_3(/*node*/a0.__ptr, /*type*/a1, /*shadows*/a2); this.__type = Light.__type; getCache(Light)[this.__ptr] = this; return; }
    if (a4 === undefined) { this.__ptr = _mud_Light__construct_4(/*node*/a0.__ptr, /*type*/a1, /*shadows*/a2, /*colour*/a3.__ptr); this.__type = Light.__type; getCache(Light)[this.__ptr] = this; return; }
    if (a5 === undefined) { this.__ptr = _mud_Light__construct_5(/*node*/a0.__ptr, /*type*/a1, /*shadows*/a2, /*colour*/a3.__ptr, /*energy*/a4); this.__type = Light.__type; getCache(Light)[this.__ptr] = this; return; }
    this.__ptr = _mud_Light__construct_6(/*node*/a0.__ptr, /*type*/a1, /*shadows*/a2, /*colour*/a3.__ptr, /*energy*/a4, /*range*/a5); this.__type = Light.__type; getCache(Light)[this.__ptr] = this;
};
Light.prototype = Object.create(WrapperObject.prototype);
Light.prototype.constructor = Light;
Light.prototype.__class = Light;
Light.__cache = {};
Module['Light'] = Light;
Object.defineProperty(Light.prototype, "node", {
    get: function() {
        return wrapPointer(_mud_Light__get_node(this.__ptr), Node3);
    },
    set: function(value) {
        _mud_Light__set_node(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Light.prototype, "type", {
    get: function() {
        return _mud_Light__get_type(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_type(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "visible", {
    get: function() {
        return !!(_mud_Light__get_visible(this.__ptr));
    },
    set: function(value) {
        _mud_Light__set_visible(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "colour", {
    get: function() {
        return wrapPointer(_mud_Light__get_colour(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_Light__set_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Light.prototype, "range", {
    get: function() {
        return _mud_Light__get_range(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_range(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "energy", {
    get: function() {
        return _mud_Light__get_energy(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_energy(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "specular", {
    get: function() {
        return _mud_Light__get_specular(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_specular(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "attenuation", {
    get: function() {
        return _mud_Light__get_attenuation(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_attenuation(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "shadows", {
    get: function() {
        return !!(_mud_Light__get_shadows(this.__ptr));
    },
    set: function(value) {
        _mud_Light__set_shadows(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "shadow_range", {
    get: function() {
        return _mud_Light__get_shadow_range(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_shadow_range(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "layers", {
    get: function() {
        return _mud_Light__get_layers(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_layers(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "last_render", {
    get: function() {
        return _mud_Light__get_last_render(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_last_render(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "last_update", {
    get: function() {
        return _mud_Light__get_last_update(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_last_update(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "spot_angle", {
    get: function() {
        return _mud_Light__get_spot_angle(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_spot_angle(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "spot_attenuation", {
    get: function() {
        return _mud_Light__get_spot_attenuation(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_spot_attenuation(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "shadow_flags", {
    get: function() {
        return _mud_Light__get_shadow_flags(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_shadow_flags(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "shadow_nusplits", {
    get: function() {
        return _mud_Light__get_shadow_nusplits(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_shadow_nusplits(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "shadow_split_distribution", {
    get: function() {
        return _mud_Light__get_shadow_split_distribution(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_shadow_split_distribution(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "shadow_normal_bias", {
    get: function() {
        return _mud_Light__get_shadow_normal_bias(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_shadow_normal_bias(this.__ptr, value);
    }
});
Object.defineProperty(Light.prototype, "shadow_bias", {
    get: function() {
        return _mud_Light__get_shadow_bias(this.__ptr);
    },
    set: function(value) {
        _mud_Light__set_shadow_bias(this.__ptr, value);
    }
});
Light.prototype["__destroy"] = Light.prototype.__destroy = function() {
    _mud_Light__destroy(this.__ptr);
};
// Lines
function Lines(a0, a1) {
    if (a0 === undefined) { this.__ptr = _mud_Lines__construct_0(); this.__type = Lines.__type; getCache(Lines)[this.__ptr] = this; return; }
    this.__ptr = _mud_Lines__construct_2(/*curve*/a0.__ptr, /*subdiv*/a1); this.__type = Lines.__type; getCache(Lines)[this.__ptr] = this;
};
Lines.prototype = Object.create(WrapperObject.prototype);
Lines.prototype.constructor = Lines;
Lines.prototype.__class = Lines;
Lines.__cache = {};
Module['Lines'] = Lines;
Lines.prototype["add"] = Lines.prototype.add = function(a0, a1, a2, a3) {
    if (a2 === undefined) { _mud_Lines_add_2(this.__ptr, /*start*/a0.__ptr, /*end*/a1.__ptr); return; }
    if (a3 === undefined) { _mud_Lines_add_3(this.__ptr, /*start*/a0.__ptr, /*end*/a1.__ptr, /*start_colour*/a2.__ptr); return; }
    _mud_Lines_add_4(this.__ptr, /*start*/a0.__ptr, /*end*/a1.__ptr, /*start_colour*/a2.__ptr, /*end_colour*/a3.__ptr);
};
Lines.prototype["start"] = Lines.prototype.start = function(a0, a1) {
    if (a1 === undefined) { _mud_Lines_start_1(this.__ptr, /*position*/a0.__ptr); return; }
    _mud_Lines_start_2(this.__ptr, /*position*/a0.__ptr, /*colour*/a1.__ptr);
};
Lines.prototype["next"] = Lines.prototype.next = function(a0, a1) {
    if (a1 === undefined) { _mud_Lines_next_1(this.__ptr, /*position*/a0.__ptr); return; }
    _mud_Lines_next_2(this.__ptr, /*position*/a0.__ptr, /*colour*/a1.__ptr);
};
Lines.prototype["setup"] = Lines.prototype.setup = function() {
    _mud_Lines_setup_0(this.__ptr);
};
Lines.prototype["write"] = Lines.prototype.write = function(a0) {
    _mud_Lines_write_1(this.__ptr, /*mesh*/a0.__ptr);
};
Lines.prototype["commit"] = Lines.prototype.commit = function(a0) {
    _mud_Lines_commit_1(this.__ptr, /*batch*/a0.__ptr);
};
Lines.prototype["__destroy"] = Lines.prototype.__destroy = function() {
    _mud_Lines__destroy(this.__ptr);
};
// Material
function Material() { throw "cannot construct a Material, no constructor in IDL" }
Material.prototype = Object.create(WrapperObject.prototype);
Material.prototype.constructor = Material;
Material.prototype.__class = Material;
Material.__cache = {};
Module['Material'] = Material;
Object.defineProperty(Material.prototype, "index", {
    get: function() {
        return _mud_Material__get_index(this.__ptr);
    },
    set: function(value) {
        _mud_Material__set_index(this.__ptr, value);
    }
});
Object.defineProperty(Material.prototype, "name", {
    get: function() {
        return Pointer_stringify(_mud_Material__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Material__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Material.prototype, "builtin", {
    get: function() {
        return !!(_mud_Material__get_builtin(this.__ptr));
    },
    set: function(value) {
        _mud_Material__set_builtin(this.__ptr, value);
    }
});
Object.defineProperty(Material.prototype, "program", {
    get: function() {
        return wrapPointer(_mud_Material__get_program(this.__ptr), Program);
    },
    set: function(value) {
        _mud_Material__set_program(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Material.prototype, "base", {
    get: function() {
        return wrapPointer(_mud_Material__get_base(this.__ptr), MaterialBase);
    },
    set: function(value) {
        _mud_Material__set_base(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Material.prototype, "alpha", {
    get: function() {
        return wrapPointer(_mud_Material__get_alpha(this.__ptr), MaterialAlpha);
    },
    set: function(value) {
        _mud_Material__set_alpha(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Material.prototype, "solid", {
    get: function() {
        return wrapPointer(_mud_Material__get_solid(this.__ptr), MaterialSolid);
    },
    set: function(value) {
        _mud_Material__set_solid(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Material.prototype, "point", {
    get: function() {
        return wrapPointer(_mud_Material__get_point(this.__ptr), MaterialPoint);
    },
    set: function(value) {
        _mud_Material__set_point(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Material.prototype, "line", {
    get: function() {
        return wrapPointer(_mud_Material__get_line(this.__ptr), MaterialLine);
    },
    set: function(value) {
        _mud_Material__set_line(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Material.prototype, "pbr", {
    get: function() {
        return wrapPointer(_mud_Material__get_pbr(this.__ptr), MaterialPbr);
    },
    set: function(value) {
        _mud_Material__set_pbr(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Material.prototype, "fresnel", {
    get: function() {
        return wrapPointer(_mud_Material__get_fresnel(this.__ptr), MaterialFresnel);
    },
    set: function(value) {
        _mud_Material__set_fresnel(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Material.prototype, "user", {
    get: function() {
        return wrapPointer(_mud_Material__get_user(this.__ptr), MaterialUser);
    },
    set: function(value) {
        _mud_Material__set_user(this.__ptr, value.__ptr);
    }
});
Material.prototype["__destroy"] = Material.prototype.__destroy = function() {
    _mud_Material__destroy(this.__ptr);
};
// MaterialAlpha
function MaterialAlpha() {
    this.__ptr = _mud_MaterialAlpha__construct_0(); this.__type = MaterialAlpha.__type; getCache(MaterialAlpha)[this.__ptr] = this;
};
MaterialAlpha.prototype = Object.create(WrapperObject.prototype);
MaterialAlpha.prototype.constructor = MaterialAlpha;
MaterialAlpha.prototype.__class = MaterialAlpha;
MaterialAlpha.__cache = {};
Module['MaterialAlpha'] = MaterialAlpha;
Object.defineProperty(MaterialAlpha.prototype, "alpha", {
    get: function() {
        return wrapPointer(_mud_MaterialAlpha__get_alpha(this.__ptr), MaterialParam_float);
    },
    set: function(value) {
        _mud_MaterialAlpha__set_alpha(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialAlpha.prototype, "alpha_scissor", {
    get: function() {
        return _mud_MaterialAlpha__get_alpha_scissor(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialAlpha__set_alpha_scissor(this.__ptr, value);
    }
});
Object.defineProperty(MaterialAlpha.prototype, "alpha_test", {
    get: function() {
        return !!(_mud_MaterialAlpha__get_alpha_test(this.__ptr));
    },
    set: function(value) {
        _mud_MaterialAlpha__set_alpha_test(this.__ptr, value);
    }
});
Object.defineProperty(MaterialAlpha.prototype, "is_alpha", {
    get: function() {
        return !!(_mud_MaterialAlpha__get_is_alpha(this.__ptr));
    },
    set: function(value) {
        _mud_MaterialAlpha__set_is_alpha(this.__ptr, value);
    }
});
MaterialAlpha.prototype["__destroy"] = MaterialAlpha.prototype.__destroy = function() {
    _mud_MaterialAlpha__destroy(this.__ptr);
};
// MaterialBase
function MaterialBase() {
    this.__ptr = _mud_MaterialBase__construct_0(); this.__type = MaterialBase.__type; getCache(MaterialBase)[this.__ptr] = this;
};
MaterialBase.prototype = Object.create(WrapperObject.prototype);
MaterialBase.prototype.constructor = MaterialBase;
MaterialBase.prototype.__class = MaterialBase;
MaterialBase.__cache = {};
Module['MaterialBase'] = MaterialBase;
Object.defineProperty(MaterialBase.prototype, "blend_mode", {
    get: function() {
        return _mud_MaterialBase__get_blend_mode(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialBase__set_blend_mode(this.__ptr, value);
    }
});
Object.defineProperty(MaterialBase.prototype, "cull_mode", {
    get: function() {
        return _mud_MaterialBase__get_cull_mode(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialBase__set_cull_mode(this.__ptr, value);
    }
});
Object.defineProperty(MaterialBase.prototype, "depth_draw", {
    get: function() {
        return _mud_MaterialBase__get_depth_draw(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialBase__set_depth_draw(this.__ptr, value);
    }
});
Object.defineProperty(MaterialBase.prototype, "depth_test", {
    get: function() {
        return _mud_MaterialBase__get_depth_test(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialBase__set_depth_test(this.__ptr, value);
    }
});
Object.defineProperty(MaterialBase.prototype, "uv0_scale", {
    get: function() {
        return wrapPointer(_mud_MaterialBase__get_uv0_scale(this.__ptr), v2_float);
    },
    set: function(value) {
        _mud_MaterialBase__set_uv0_scale(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialBase.prototype, "uv0_offset", {
    get: function() {
        return wrapPointer(_mud_MaterialBase__get_uv0_offset(this.__ptr), v2_float);
    },
    set: function(value) {
        _mud_MaterialBase__set_uv0_offset(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialBase.prototype, "uv1_scale", {
    get: function() {
        return wrapPointer(_mud_MaterialBase__get_uv1_scale(this.__ptr), v2_float);
    },
    set: function(value) {
        _mud_MaterialBase__set_uv1_scale(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialBase.prototype, "uv1_offset", {
    get: function() {
        return wrapPointer(_mud_MaterialBase__get_uv1_offset(this.__ptr), v2_float);
    },
    set: function(value) {
        _mud_MaterialBase__set_uv1_offset(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialBase.prototype, "shader_color", {
    get: function() {
        return _mud_MaterialBase__get_shader_color(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialBase__set_shader_color(this.__ptr, value);
    }
});
Object.defineProperty(MaterialBase.prototype, "screen_filter", {
    get: function() {
        return !!(_mud_MaterialBase__get_screen_filter(this.__ptr));
    },
    set: function(value) {
        _mud_MaterialBase__set_screen_filter(this.__ptr, value);
    }
});
Object.defineProperty(MaterialBase.prototype, "anisotropy", {
    get: function() {
        return _mud_MaterialBase__get_anisotropy(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialBase__set_anisotropy(this.__ptr, value);
    }
});
MaterialBase.prototype["__destroy"] = MaterialBase.prototype.__destroy = function() {
    _mud_MaterialBase__destroy(this.__ptr);
};
// MaterialFresnel
function MaterialFresnel() {
    this.__ptr = _mud_MaterialFresnel__construct_0(); this.__type = MaterialFresnel.__type; getCache(MaterialFresnel)[this.__ptr] = this;
};
MaterialFresnel.prototype = Object.create(WrapperObject.prototype);
MaterialFresnel.prototype.constructor = MaterialFresnel;
MaterialFresnel.prototype.__class = MaterialFresnel;
MaterialFresnel.__cache = {};
Module['MaterialFresnel'] = MaterialFresnel;
Object.defineProperty(MaterialFresnel.prototype, "value", {
    get: function() {
        return wrapPointer(_mud_MaterialFresnel__get_value(this.__ptr), MaterialParam_mud_Colour);
    },
    set: function(value) {
        _mud_MaterialFresnel__set_value(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialFresnel.prototype, "fresnel_scale", {
    get: function() {
        return _mud_MaterialFresnel__get_fresnel_scale(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialFresnel__set_fresnel_scale(this.__ptr, value);
    }
});
Object.defineProperty(MaterialFresnel.prototype, "fresnel_bias", {
    get: function() {
        return _mud_MaterialFresnel__get_fresnel_bias(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialFresnel__set_fresnel_bias(this.__ptr, value);
    }
});
Object.defineProperty(MaterialFresnel.prototype, "fresnel_power", {
    get: function() {
        return _mud_MaterialFresnel__get_fresnel_power(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialFresnel__set_fresnel_power(this.__ptr, value);
    }
});
MaterialFresnel.prototype["__destroy"] = MaterialFresnel.prototype.__destroy = function() {
    _mud_MaterialFresnel__destroy(this.__ptr);
};
// MaterialLine
function MaterialLine() {
    this.__ptr = _mud_MaterialLine__construct_0(); this.__type = MaterialLine.__type; getCache(MaterialLine)[this.__ptr] = this;
};
MaterialLine.prototype = Object.create(WrapperObject.prototype);
MaterialLine.prototype.constructor = MaterialLine;
MaterialLine.prototype.__class = MaterialLine;
MaterialLine.__cache = {};
Module['MaterialLine'] = MaterialLine;
Object.defineProperty(MaterialLine.prototype, "line_width", {
    get: function() {
        return _mud_MaterialLine__get_line_width(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialLine__set_line_width(this.__ptr, value);
    }
});
Object.defineProperty(MaterialLine.prototype, "dashed", {
    get: function() {
        return !!(_mud_MaterialLine__get_dashed(this.__ptr));
    },
    set: function(value) {
        _mud_MaterialLine__set_dashed(this.__ptr, value);
    }
});
Object.defineProperty(MaterialLine.prototype, "dash_scale", {
    get: function() {
        return _mud_MaterialLine__get_dash_scale(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialLine__set_dash_scale(this.__ptr, value);
    }
});
Object.defineProperty(MaterialLine.prototype, "dash_size", {
    get: function() {
        return _mud_MaterialLine__get_dash_size(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialLine__set_dash_size(this.__ptr, value);
    }
});
Object.defineProperty(MaterialLine.prototype, "dash_gap", {
    get: function() {
        return _mud_MaterialLine__get_dash_gap(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialLine__set_dash_gap(this.__ptr, value);
    }
});
MaterialLine.prototype["__destroy"] = MaterialLine.prototype.__destroy = function() {
    _mud_MaterialLine__destroy(this.__ptr);
};
// MaterialParam<float>
function MaterialParam_float() {
    this.__ptr = _mud_MaterialParam_float__construct_0(); this.__type = MaterialParam_float.__type; getCache(MaterialParam_float)[this.__ptr] = this;
};
MaterialParam_float.prototype = Object.create(WrapperObject.prototype);
MaterialParam_float.prototype.constructor = MaterialParam_float;
MaterialParam_float.prototype.__class = MaterialParam_float;
MaterialParam_float.__cache = {};
Module['MaterialParam_float'] = MaterialParam_float;
Object.defineProperty(MaterialParam_float.prototype, "value", {
    get: function() {
        return _mud_MaterialParam_float__get_value(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialParam_float__set_value(this.__ptr, value);
    }
});
Object.defineProperty(MaterialParam_float.prototype, "texture", {
    get: function() {
        return wrapPointer(_mud_MaterialParam_float__get_texture(this.__ptr), Texture);
    },
    set: function(value) {
        _mud_MaterialParam_float__set_texture(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialParam_float.prototype, "channel", {
    get: function() {
        return _mud_MaterialParam_float__get_channel(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialParam_float__set_channel(this.__ptr, value);
    }
});
MaterialParam_float.prototype["__destroy"] = MaterialParam_float.prototype.__destroy = function() {
    _mud_MaterialParam_float__destroy(this.__ptr);
};
// MaterialParam<mud::Colour>
function MaterialParam_mud_Colour() {
    this.__ptr = _mud_MaterialParam_mud_Colour__construct_0(); this.__type = MaterialParam_mud_Colour.__type; getCache(MaterialParam_mud_Colour)[this.__ptr] = this;
};
MaterialParam_mud_Colour.prototype = Object.create(WrapperObject.prototype);
MaterialParam_mud_Colour.prototype.constructor = MaterialParam_mud_Colour;
MaterialParam_mud_Colour.prototype.__class = MaterialParam_mud_Colour;
MaterialParam_mud_Colour.__cache = {};
Module['MaterialParam_mud_Colour'] = MaterialParam_mud_Colour;
Object.defineProperty(MaterialParam_mud_Colour.prototype, "value", {
    get: function() {
        return wrapPointer(_mud_MaterialParam_mud_Colour__get_value(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_MaterialParam_mud_Colour__set_value(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialParam_mud_Colour.prototype, "texture", {
    get: function() {
        return wrapPointer(_mud_MaterialParam_mud_Colour__get_texture(this.__ptr), Texture);
    },
    set: function(value) {
        _mud_MaterialParam_mud_Colour__set_texture(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialParam_mud_Colour.prototype, "channel", {
    get: function() {
        return _mud_MaterialParam_mud_Colour__get_channel(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialParam_mud_Colour__set_channel(this.__ptr, value);
    }
});
MaterialParam_mud_Colour.prototype["__destroy"] = MaterialParam_mud_Colour.prototype.__destroy = function() {
    _mud_MaterialParam_mud_Colour__destroy(this.__ptr);
};
// MaterialParam<mud::vec4>
function MaterialParam_mud_vec4() {
    this.__ptr = _mud_MaterialParam_mud_vec4__construct_0(); this.__type = MaterialParam_mud_vec4.__type; getCache(MaterialParam_mud_vec4)[this.__ptr] = this;
};
MaterialParam_mud_vec4.prototype = Object.create(WrapperObject.prototype);
MaterialParam_mud_vec4.prototype.constructor = MaterialParam_mud_vec4;
MaterialParam_mud_vec4.prototype.__class = MaterialParam_mud_vec4;
MaterialParam_mud_vec4.__cache = {};
Module['MaterialParam_mud_vec4'] = MaterialParam_mud_vec4;
Object.defineProperty(MaterialParam_mud_vec4.prototype, "value", {
    get: function() {
        return wrapPointer(_mud_MaterialParam_mud_vec4__get_value(this.__ptr), v4_float);
    },
    set: function(value) {
        _mud_MaterialParam_mud_vec4__set_value(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialParam_mud_vec4.prototype, "texture", {
    get: function() {
        return wrapPointer(_mud_MaterialParam_mud_vec4__get_texture(this.__ptr), Texture);
    },
    set: function(value) {
        _mud_MaterialParam_mud_vec4__set_texture(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialParam_mud_vec4.prototype, "channel", {
    get: function() {
        return _mud_MaterialParam_mud_vec4__get_channel(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialParam_mud_vec4__set_channel(this.__ptr, value);
    }
});
MaterialParam_mud_vec4.prototype["__destroy"] = MaterialParam_mud_vec4.prototype.__destroy = function() {
    _mud_MaterialParam_mud_vec4__destroy(this.__ptr);
};
// MaterialPbr
function MaterialPbr(a0, a1, a2) {
    if (a0 === undefined) { this.__ptr = _mud_MaterialPbr__construct_0(); this.__type = MaterialPbr.__type; getCache(MaterialPbr)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_MaterialPbr__construct_1(/*albedo*/a0.__ptr); this.__type = MaterialPbr.__type; getCache(MaterialPbr)[this.__ptr] = this; return; }
    if (a2 === undefined) { this.__ptr = _mud_MaterialPbr__construct_2(/*albedo*/a0.__ptr, /*metallic*/a1); this.__type = MaterialPbr.__type; getCache(MaterialPbr)[this.__ptr] = this; return; }
    this.__ptr = _mud_MaterialPbr__construct_3(/*albedo*/a0.__ptr, /*metallic*/a1, /*roughness*/a2); this.__type = MaterialPbr.__type; getCache(MaterialPbr)[this.__ptr] = this;
};
MaterialPbr.prototype = Object.create(WrapperObject.prototype);
MaterialPbr.prototype.constructor = MaterialPbr;
MaterialPbr.prototype.__class = MaterialPbr;
MaterialPbr.__cache = {};
Module['MaterialPbr'] = MaterialPbr;
Object.defineProperty(MaterialPbr.prototype, "albedo", {
    get: function() {
        return wrapPointer(_mud_MaterialPbr__get_albedo(this.__ptr), MaterialParam_mud_Colour);
    },
    set: function(value) {
        _mud_MaterialPbr__set_albedo(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialPbr.prototype, "specular", {
    get: function() {
        return _mud_MaterialPbr__get_specular(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialPbr__set_specular(this.__ptr, value);
    }
});
Object.defineProperty(MaterialPbr.prototype, "metallic", {
    get: function() {
        return wrapPointer(_mud_MaterialPbr__get_metallic(this.__ptr), MaterialParam_float);
    },
    set: function(value) {
        _mud_MaterialPbr__set_metallic(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialPbr.prototype, "roughness", {
    get: function() {
        return wrapPointer(_mud_MaterialPbr__get_roughness(this.__ptr), MaterialParam_float);
    },
    set: function(value) {
        _mud_MaterialPbr__set_roughness(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialPbr.prototype, "normal", {
    get: function() {
        return wrapPointer(_mud_MaterialPbr__get_normal(this.__ptr), MaterialParam_float);
    },
    set: function(value) {
        _mud_MaterialPbr__set_normal(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialPbr.prototype, "emissive", {
    get: function() {
        return wrapPointer(_mud_MaterialPbr__get_emissive(this.__ptr), MaterialParam_mud_Colour);
    },
    set: function(value) {
        _mud_MaterialPbr__set_emissive(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialPbr.prototype, "emissive_energy", {
    get: function() {
        return _mud_MaterialPbr__get_emissive_energy(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialPbr__set_emissive_energy(this.__ptr, value);
    }
});
Object.defineProperty(MaterialPbr.prototype, "rim", {
    get: function() {
        return wrapPointer(_mud_MaterialPbr__get_rim(this.__ptr), MaterialParam_float);
    },
    set: function(value) {
        _mud_MaterialPbr__set_rim(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialPbr.prototype, "ritint", {
    get: function() {
        return _mud_MaterialPbr__get_ritint(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialPbr__set_ritint(this.__ptr, value);
    }
});
Object.defineProperty(MaterialPbr.prototype, "clearcoat", {
    get: function() {
        return wrapPointer(_mud_MaterialPbr__get_clearcoat(this.__ptr), MaterialParam_float);
    },
    set: function(value) {
        _mud_MaterialPbr__set_clearcoat(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialPbr.prototype, "clearcoat_gloss", {
    get: function() {
        return _mud_MaterialPbr__get_clearcoat_gloss(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialPbr__set_clearcoat_gloss(this.__ptr, value);
    }
});
Object.defineProperty(MaterialPbr.prototype, "anisotropy", {
    get: function() {
        return wrapPointer(_mud_MaterialPbr__get_anisotropy(this.__ptr), MaterialParam_float);
    },
    set: function(value) {
        _mud_MaterialPbr__set_anisotropy(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialPbr.prototype, "subsurface", {
    get: function() {
        return wrapPointer(_mud_MaterialPbr__get_subsurface(this.__ptr), MaterialParam_float);
    },
    set: function(value) {
        _mud_MaterialPbr__set_subsurface(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialPbr.prototype, "refraction", {
    get: function() {
        return wrapPointer(_mud_MaterialPbr__get_refraction(this.__ptr), MaterialParam_float);
    },
    set: function(value) {
        _mud_MaterialPbr__set_refraction(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialPbr.prototype, "depth", {
    get: function() {
        return wrapPointer(_mud_MaterialPbr__get_depth(this.__ptr), MaterialParam_float);
    },
    set: function(value) {
        _mud_MaterialPbr__set_depth(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialPbr.prototype, "ambient_occlusion", {
    get: function() {
        return wrapPointer(_mud_MaterialPbr__get_ambient_occlusion(this.__ptr), MaterialParam_float);
    },
    set: function(value) {
        _mud_MaterialPbr__set_ambient_occlusion(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialPbr.prototype, "transmission", {
    get: function() {
        return wrapPointer(_mud_MaterialPbr__get_transmission(this.__ptr), MaterialParam_mud_Colour);
    },
    set: function(value) {
        _mud_MaterialPbr__set_transmission(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialPbr.prototype, "deep_parallax", {
    get: function() {
        return !!(_mud_MaterialPbr__get_deep_parallax(this.__ptr));
    },
    set: function(value) {
        _mud_MaterialPbr__set_deep_parallax(this.__ptr, value);
    }
});
Object.defineProperty(MaterialPbr.prototype, "scene_environment", {
    get: function() {
        return !!(_mud_MaterialPbr__get_scene_environment(this.__ptr));
    },
    set: function(value) {
        _mud_MaterialPbr__set_scene_environment(this.__ptr, value);
    }
});
Object.defineProperty(MaterialPbr.prototype, "diffuse_mode", {
    get: function() {
        return _mud_MaterialPbr__get_diffuse_mode(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialPbr__set_diffuse_mode(this.__ptr, value);
    }
});
Object.defineProperty(MaterialPbr.prototype, "specular_mode", {
    get: function() {
        return _mud_MaterialPbr__get_specular_mode(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialPbr__set_specular_mode(this.__ptr, value);
    }
});
MaterialPbr.prototype["__destroy"] = MaterialPbr.prototype.__destroy = function() {
    _mud_MaterialPbr__destroy(this.__ptr);
};
// MaterialPoint
function MaterialPoint() {
    this.__ptr = _mud_MaterialPoint__construct_0(); this.__type = MaterialPoint.__type; getCache(MaterialPoint)[this.__ptr] = this;
};
MaterialPoint.prototype = Object.create(WrapperObject.prototype);
MaterialPoint.prototype.constructor = MaterialPoint;
MaterialPoint.prototype.__class = MaterialPoint;
MaterialPoint.__cache = {};
Module['MaterialPoint'] = MaterialPoint;
Object.defineProperty(MaterialPoint.prototype, "point_size", {
    get: function() {
        return _mud_MaterialPoint__get_point_size(this.__ptr);
    },
    set: function(value) {
        _mud_MaterialPoint__set_point_size(this.__ptr, value);
    }
});
Object.defineProperty(MaterialPoint.prototype, "project", {
    get: function() {
        return !!(_mud_MaterialPoint__get_project(this.__ptr));
    },
    set: function(value) {
        _mud_MaterialPoint__set_project(this.__ptr, value);
    }
});
MaterialPoint.prototype["__destroy"] = MaterialPoint.prototype.__destroy = function() {
    _mud_MaterialPoint__destroy(this.__ptr);
};
// MaterialSolid
function MaterialSolid() {
    this.__ptr = _mud_MaterialSolid__construct_0(); this.__type = MaterialSolid.__type; getCache(MaterialSolid)[this.__ptr] = this;
};
MaterialSolid.prototype = Object.create(WrapperObject.prototype);
MaterialSolid.prototype.constructor = MaterialSolid;
MaterialSolid.prototype.__class = MaterialSolid;
MaterialSolid.__cache = {};
Module['MaterialSolid'] = MaterialSolid;
Object.defineProperty(MaterialSolid.prototype, "colour", {
    get: function() {
        return wrapPointer(_mud_MaterialSolid__get_colour(this.__ptr), MaterialParam_mud_Colour);
    },
    set: function(value) {
        _mud_MaterialSolid__set_colour(this.__ptr, value.__ptr);
    }
});
MaterialSolid.prototype["__destroy"] = MaterialSolid.prototype.__destroy = function() {
    _mud_MaterialSolid__destroy(this.__ptr);
};
// MaterialUser
function MaterialUser() {
    this.__ptr = _mud_MaterialUser__construct_0(); this.__type = MaterialUser.__type; getCache(MaterialUser)[this.__ptr] = this;
};
MaterialUser.prototype = Object.create(WrapperObject.prototype);
MaterialUser.prototype.constructor = MaterialUser;
MaterialUser.prototype.__class = MaterialUser;
MaterialUser.__cache = {};
Module['MaterialUser'] = MaterialUser;
Object.defineProperty(MaterialUser.prototype, "tex0", {
    get: function() {
        return wrapPointer(_mud_MaterialUser__get_tex0(this.__ptr), Texture);
    },
    set: function(value) {
        _mud_MaterialUser__set_tex0(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialUser.prototype, "tex1", {
    get: function() {
        return wrapPointer(_mud_MaterialUser__get_tex1(this.__ptr), Texture);
    },
    set: function(value) {
        _mud_MaterialUser__set_tex1(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialUser.prototype, "tex2", {
    get: function() {
        return wrapPointer(_mud_MaterialUser__get_tex2(this.__ptr), Texture);
    },
    set: function(value) {
        _mud_MaterialUser__set_tex2(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialUser.prototype, "tex3", {
    get: function() {
        return wrapPointer(_mud_MaterialUser__get_tex3(this.__ptr), Texture);
    },
    set: function(value) {
        _mud_MaterialUser__set_tex3(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialUser.prototype, "attr0", {
    get: function() {
        return wrapPointer(_mud_MaterialUser__get_attr0(this.__ptr), v4_float);
    },
    set: function(value) {
        _mud_MaterialUser__set_attr0(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialUser.prototype, "attr1", {
    get: function() {
        return wrapPointer(_mud_MaterialUser__get_attr1(this.__ptr), v4_float);
    },
    set: function(value) {
        _mud_MaterialUser__set_attr1(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialUser.prototype, "attr2", {
    get: function() {
        return wrapPointer(_mud_MaterialUser__get_attr2(this.__ptr), v4_float);
    },
    set: function(value) {
        _mud_MaterialUser__set_attr2(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialUser.prototype, "attr3", {
    get: function() {
        return wrapPointer(_mud_MaterialUser__get_attr3(this.__ptr), v4_float);
    },
    set: function(value) {
        _mud_MaterialUser__set_attr3(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialUser.prototype, "attr4", {
    get: function() {
        return wrapPointer(_mud_MaterialUser__get_attr4(this.__ptr), v4_float);
    },
    set: function(value) {
        _mud_MaterialUser__set_attr4(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MaterialUser.prototype, "attr5", {
    get: function() {
        return wrapPointer(_mud_MaterialUser__get_attr5(this.__ptr), v4_float);
    },
    set: function(value) {
        _mud_MaterialUser__set_attr5(this.__ptr, value.__ptr);
    }
});
MaterialUser.prototype["__destroy"] = MaterialUser.prototype.__destroy = function() {
    _mud_MaterialUser__destroy(this.__ptr);
};
// Mesh
function Mesh() { throw "cannot construct a Mesh, no constructor in IDL" }
Mesh.prototype = Object.create(WrapperObject.prototype);
Mesh.prototype.constructor = Mesh;
Mesh.prototype.__class = Mesh;
Mesh.__cache = {};
Module['Mesh'] = Mesh;
Mesh.prototype["clear"] = Mesh.prototype.clear = function() {
    _mud_Mesh_clear_0(this.__ptr);
};
Mesh.prototype["write"] = Mesh.prototype.write = function(a0, a1, a2) {
    if (a1 === undefined) { _mud_Mesh_write_1(this.__ptr, /*packer*/a0.__ptr); return; }
    if (a2 === undefined) { _mud_Mesh_write_2(this.__ptr, /*packer*/a0.__ptr, /*optimize*/a1); return; }
    _mud_Mesh_write_3(this.__ptr, /*packer*/a0.__ptr, /*optimize*/a1, /*dynamic*/a2);
};
Mesh.prototype["upload"] = Mesh.prototype.upload = function(a0, a1) {
    if (a1 === undefined) { _mud_Mesh_upload_1(this.__ptr, /*gpu_mesh*/a0.__ptr); return; }
    _mud_Mesh_upload_2(this.__ptr, /*gpu_mesh*/a0.__ptr, /*optimize*/a1);
};
Mesh.prototype["cache"] = Mesh.prototype.cache = function(a0) {
    _mud_Mesh_cache_1(this.__ptr, /*gpu_mesh*/a0.__ptr);
};
Mesh.prototype["direct"] = Mesh.prototype.direct = function(a0, a1, a2) {
    if (a2 === undefined) { return wrapPointer(_mud_Mesh_direct_2(this.__ptr, /*vertex_format*/a0, /*vertex_count*/a1), MeshAdapter); }
    return wrapPointer(_mud_Mesh_direct_3(this.__ptr, /*vertex_format*/a0, /*vertex_count*/a1, /*index_count*/a2), MeshAdapter);
};
Object.defineProperty(Mesh.prototype, "name", {
    get: function() {
        return Pointer_stringify(_mud_Mesh__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Mesh__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Mesh.prototype, "index", {
    get: function() {
        return _mud_Mesh__get_index(this.__ptr);
    },
    set: function(value) {
        _mud_Mesh__set_index(this.__ptr, value);
    }
});
Object.defineProperty(Mesh.prototype, "primitive", {
    get: function() {
        return _mud_Mesh__get_primitive(this.__ptr);
    },
    set: function(value) {
        _mud_Mesh__set_primitive(this.__ptr, value);
    }
});
Object.defineProperty(Mesh.prototype, "aabb", {
    get: function() {
        return wrapPointer(_mud_Mesh__get_aabb(this.__ptr), Aabb);
    },
    set: function(value) {
        _mud_Mesh__set_aabb(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Mesh.prototype, "radius", {
    get: function() {
        return _mud_Mesh__get_radius(this.__ptr);
    },
    set: function(value) {
        _mud_Mesh__set_radius(this.__ptr, value);
    }
});
Object.defineProperty(Mesh.prototype, "origin", {
    get: function() {
        return wrapPointer(_mud_Mesh__get_origin(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Mesh__set_origin(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Mesh.prototype, "readback", {
    get: function() {
        return !!(_mud_Mesh__get_readback(this.__ptr));
    },
    set: function(value) {
        _mud_Mesh__set_readback(this.__ptr, value);
    }
});
Object.defineProperty(Mesh.prototype, "vertex_format", {
    get: function() {
        return _mud_Mesh__get_vertex_format(this.__ptr);
    },
    set: function(value) {
        _mud_Mesh__set_vertex_format(this.__ptr, value);
    }
});
Object.defineProperty(Mesh.prototype, "qnormals", {
    get: function() {
        return !!(_mud_Mesh__get_qnormals(this.__ptr));
    },
    set: function(value) {
        _mud_Mesh__set_qnormals(this.__ptr, value);
    }
});
Object.defineProperty(Mesh.prototype, "vertex_count", {
    get: function() {
        return _mud_Mesh__get_vertex_count(this.__ptr);
    },
    set: function(value) {
        _mud_Mesh__set_vertex_count(this.__ptr, value);
    }
});
Object.defineProperty(Mesh.prototype, "index_count", {
    get: function() {
        return _mud_Mesh__get_index_count(this.__ptr);
    },
    set: function(value) {
        _mud_Mesh__set_index_count(this.__ptr, value);
    }
});
Object.defineProperty(Mesh.prototype, "index32", {
    get: function() {
        return !!(_mud_Mesh__get_index32(this.__ptr));
    },
    set: function(value) {
        _mud_Mesh__set_index32(this.__ptr, value);
    }
});
Object.defineProperty(Mesh.prototype, "material", {
    get: function() {
        return wrapPointer(_mud_Mesh__get_material(this.__ptr), Material);
    },
    set: function(value) {
        _mud_Mesh__set_material(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Mesh.prototype, "is_dynamic", {
    get: function() {
        return !!(_mud_Mesh__get_is_dynamic(this.__ptr));
    },
    set: function(value) {
        _mud_Mesh__set_is_dynamic(this.__ptr, value);
    }
});
Object.defineProperty(Mesh.prototype, "is_direct", {
    get: function() {
        return !!(_mud_Mesh__get_is_direct(this.__ptr));
    },
    set: function(value) {
        _mud_Mesh__set_is_direct(this.__ptr, value);
    }
});
Object.defineProperty(Mesh.prototype, "cache", {
    get: function() {
        return wrapPointer(_mud_Mesh__get_cache(this.__ptr), MeshAdapter);
    },
    set: function(value) {
        _mud_Mesh__set_cache(this.__ptr, value.__ptr);
    }
});
Mesh.prototype["__destroy"] = Mesh.prototype.__destroy = function() {
    _mud_Mesh__destroy(this.__ptr);
};
// Mime
function Mime() { throw "cannot construct a Mime, no constructor in IDL" }
Mime.prototype = Object.create(WrapperObject.prototype);
Mime.prototype.constructor = Mime;
Mime.prototype.__class = Mime;
Mime.__cache = {};
Module['Mime'] = Mime;
Mime.prototype["start"] = Mime.prototype.start = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a2 === undefined) { _mud_Mime_start_2(this.__ptr, ensureString(/*animation*/a0), /*loop*/a1); return; }
    if (a3 === undefined) { _mud_Mime_start_3(this.__ptr, ensureString(/*animation*/a0), /*loop*/a1, /*blend*/a2); return; }
    if (a4 === undefined) { _mud_Mime_start_4(this.__ptr, ensureString(/*animation*/a0), /*loop*/a1, /*blend*/a2, /*speed*/a3); return; }
    _mud_Mime_start_5(this.__ptr, ensureString(/*animation*/a0), /*loop*/a1, /*blend*/a2, /*speed*/a3, /*transient*/a4);
};
Mime.prototype["play"] = Mime.prototype.play = function(a0, a1, a2, a3, a4) {
    if (a2 === undefined) { _mud_Mime_play_2(this.__ptr, /*animation*/a0.__ptr, /*loop*/a1); return; }
    if (a3 === undefined) { _mud_Mime_play_3(this.__ptr, /*animation*/a0.__ptr, /*loop*/a1, /*blend*/a2); return; }
    if (a4 === undefined) { _mud_Mime_play_4(this.__ptr, /*animation*/a0.__ptr, /*loop*/a1, /*blend*/a2, /*speed*/a3); return; }
    _mud_Mime_play_5(this.__ptr, /*animation*/a0.__ptr, /*loop*/a1, /*blend*/a2, /*speed*/a3, /*transient*/a4);
};
Mime.prototype["seek"] = Mime.prototype.seek = function(a0) {
    _mud_Mime_seek_1(this.__ptr, /*time*/a0);
};
Mime.prototype["pause"] = Mime.prototype.pause = function() {
    _mud_Mime_pause_0(this.__ptr);
};
Mime.prototype["stop"] = Mime.prototype.stop = function() {
    _mud_Mime_stop_0(this.__ptr);
};
Mime.prototype["advance"] = Mime.prototype.advance = function(a0) {
    _mud_Mime_advance_1(this.__ptr, /*time*/a0);
};
Mime.prototype["next_animation"] = Mime.prototype.next_animation = function() {
    _mud_Mime_next_animation_0(this.__ptr);
};
Mime.prototype["playing"] = Mime.prototype.playing = function() {
    return Pointer_stringify(_mud_Mime_playing_0(this.__ptr));
};
Object.defineProperty(Mime.prototype, "active", {
    get: function() {
        return !!(_mud_Mime__get_active(this.__ptr));
    },
    set: function(value) {
        _mud_Mime__set_active(this.__ptr, value);
    }
});
Object.defineProperty(Mime.prototype, "speed_scale", {
    get: function() {
        return _mud_Mime__get_speed_scale(this.__ptr);
    },
    set: function(value) {
        _mud_Mime__set_speed_scale(this.__ptr, value);
    }
});
Object.defineProperty(Mime.prototype, "default_blend_time", {
    get: function() {
        return _mud_Mime__get_default_blend_time(this.__ptr);
    },
    set: function(value) {
        _mud_Mime__set_default_blend_time(this.__ptr, value);
    }
});
Mime.prototype["__destroy"] = Mime.prototype.__destroy = function() {
    _mud_Mime__destroy(this.__ptr);
};
// Model
function Model() { throw "cannot construct a Model, no constructor in IDL" }
Model.prototype = Object.create(WrapperObject.prototype);
Model.prototype.constructor = Model;
Model.prototype.__class = Model;
Model.__cache = {};
Module['Model'] = Model;
Model.prototype["get_mesh"] = Model.prototype.get_mesh = function(a0) {
    return wrapPointer(_mud_Model_get_mesh_1(this.__ptr, /*index*/a0), Mesh);
};
Model.prototype["add_mesh"] = Model.prototype.add_mesh = function(a0, a1) {
    ensureCache.prepare();
    if (a1 === undefined) { return wrapPointer(_mud_Model_add_mesh_1(this.__ptr, ensureString(/*name*/a0)), Mesh); }
    return wrapPointer(_mud_Model_add_mesh_2(this.__ptr, ensureString(/*name*/a0), /*readback*/a1), Mesh);
};
Model.prototype["add_rig"] = Model.prototype.add_rig = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_Model_add_rig_1(this.__ptr, ensureString(/*name*/a0)), Rig);
};
Model.prototype["add_item"] = Model.prototype.add_item = function(a0, a1, a2, a3, a4) {
    if (a2 === undefined) { return wrapPointer(_mud_Model_add_item_2(this.__ptr, /*mesh*/a0.__ptr, /*transform*/a1.__ptr), ModelItem); }
    if (a3 === undefined) { return wrapPointer(_mud_Model_add_item_3(this.__ptr, /*mesh*/a0.__ptr, /*transform*/a1.__ptr, /*skin*/a2), ModelItem); }
    if (a4 === undefined) { return wrapPointer(_mud_Model_add_item_4(this.__ptr, /*mesh*/a0.__ptr, /*transform*/a1.__ptr, /*skin*/a2, /*colour*/a3.__ptr), ModelItem); }
    return wrapPointer(_mud_Model_add_item_5(this.__ptr, /*mesh*/a0.__ptr, /*transform*/a1.__ptr, /*skin*/a2, /*colour*/a3.__ptr, /*material*/a4.__ptr), ModelItem);
};
Model.prototype["prepare"] = Model.prototype.prepare = function() {
    _mud_Model_prepare_0(this.__ptr);
};
Object.defineProperty(Model.prototype, "name", {
    get: function() {
        return Pointer_stringify(_mud_Model__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Model__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Model.prototype, "index", {
    get: function() {
        return _mud_Model__get_index(this.__ptr);
    },
    set: function(value) {
        _mud_Model__set_index(this.__ptr, value);
    }
});
Object.defineProperty(Model.prototype, "aabb", {
    get: function() {
        return wrapPointer(_mud_Model__get_aabb(this.__ptr), Aabb);
    },
    set: function(value) {
        _mud_Model__set_aabb(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Model.prototype, "radius", {
    get: function() {
        return _mud_Model__get_radius(this.__ptr);
    },
    set: function(value) {
        _mud_Model__set_radius(this.__ptr, value);
    }
});
Object.defineProperty(Model.prototype, "origin", {
    get: function() {
        return wrapPointer(_mud_Model__get_origin(this.__ptr), v3_float);
    },
    set: function(value) {
        _mud_Model__set_origin(this.__ptr, value.__ptr);
    }
});
Model.prototype["__destroy"] = Model.prototype.__destroy = function() {
    _mud_Model__destroy(this.__ptr);
};
// ModelItem
function ModelItem() {
    this.__ptr = _mud_ModelItem__construct_0(); this.__type = ModelItem.__type; getCache(ModelItem)[this.__ptr] = this;
};
ModelItem.prototype = Object.create(WrapperObject.prototype);
ModelItem.prototype.constructor = ModelItem;
ModelItem.prototype.__class = ModelItem;
ModelItem.__cache = {};
Module['ModelItem'] = ModelItem;
Object.defineProperty(ModelItem.prototype, "index", {
    get: function() {
        return _mud_ModelItem__get_index(this.__ptr);
    },
    set: function(value) {
        _mud_ModelItem__set_index(this.__ptr, value);
    }
});
Object.defineProperty(ModelItem.prototype, "mesh", {
    get: function() {
        return wrapPointer(_mud_ModelItem__get_mesh(this.__ptr), Mesh);
    },
    set: function(value) {
        _mud_ModelItem__set_mesh(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ModelItem.prototype, "has_transform", {
    get: function() {
        return !!(_mud_ModelItem__get_has_transform(this.__ptr));
    },
    set: function(value) {
        _mud_ModelItem__set_has_transform(this.__ptr, value);
    }
});
Object.defineProperty(ModelItem.prototype, "transform", {
    get: function() {
        return wrapPointer(_mud_ModelItem__get_transform(this.__ptr), mat4);
    },
    set: function(value) {
        _mud_ModelItem__set_transform(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ModelItem.prototype, "skin", {
    get: function() {
        return _mud_ModelItem__get_skin(this.__ptr);
    },
    set: function(value) {
        _mud_ModelItem__set_skin(this.__ptr, value);
    }
});
Object.defineProperty(ModelItem.prototype, "colour", {
    get: function() {
        return wrapPointer(_mud_ModelItem__get_colour(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_ModelItem__set_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ModelItem.prototype, "material", {
    get: function() {
        return wrapPointer(_mud_ModelItem__get_material(this.__ptr), Material);
    },
    set: function(value) {
        _mud_ModelItem__set_material(this.__ptr, value.__ptr);
    }
});
ModelItem.prototype["__destroy"] = ModelItem.prototype.__destroy = function() {
    _mud_ModelItem__destroy(this.__ptr);
};
// Node3
function Node3(a0, a1, a2) {
    if (a0 === undefined) { this.__ptr = _mud_Node3__construct_0(); this.__type = Node3.__type; getCache(Node3)[this.__ptr] = this; return; }
    if (a1 === undefined) { this.__ptr = _mud_Node3__construct_1(/*transform*/a0.__ptr); this.__type = Node3.__type; getCache(Node3)[this.__ptr] = this; return; }
    if (a2 === undefined) { this.__ptr = _mud_Node3__construct_2(/*position*/a0.__ptr, /*rotation*/a1.__ptr); this.__type = Node3.__type; getCache(Node3)[this.__ptr] = this; return; }
    this.__ptr = _mud_Node3__construct_3(/*position*/a0.__ptr, /*rotation*/a1.__ptr, /*scale*/a2.__ptr); this.__type = Node3.__type; getCache(Node3)[this.__ptr] = this;
};
Node3.prototype = Object.create(WrapperObject.prototype);
Node3.prototype.constructor = Node3;
Node3.prototype.__class = Node3;
Node3.__cache = {};
Module['Node3'] = Node3;
Node3.prototype["apply"] = Node3.prototype.apply = function(a0, a1, a2) {
    if (a1 === undefined) { _mud_Node3_apply_1(this.__ptr, /*position*/a0.__ptr); return; }
    if (a2 === undefined) { _mud_Node3_apply_2(this.__ptr, /*position*/a0.__ptr, /*rotation*/a1.__ptr); return; }
    _mud_Node3_apply_3(this.__ptr, /*position*/a0.__ptr, /*rotation*/a1.__ptr, /*scale*/a2.__ptr);
};
Node3.prototype["derive"] = Node3.prototype.derive = function(a0, a1, a2, a3) {
    if (a2 === undefined) { _mud_Node3_derive_2(this.__ptr, /*parent*/a0.__ptr, /*position*/a1.__ptr); return; }
    if (a3 === undefined) { _mud_Node3_derive_3(this.__ptr, /*parent*/a0.__ptr, /*position*/a1.__ptr, /*rotation*/a2.__ptr); return; }
    _mud_Node3_derive_4(this.__ptr, /*parent*/a0.__ptr, /*position*/a1.__ptr, /*rotation*/a2.__ptr, /*scale*/a3.__ptr);
};
Node3.prototype["position"] = Node3.prototype.position = function() {
    return wrapPointer(_mud_Node3_position_0(this.__ptr), v3_float);
};
Node3.prototype["axis"] = Node3.prototype.axis = function(a0) {
    return wrapPointer(_mud_Node3_axis_1(this.__ptr, /*dir*/a0.__ptr), v3_float);
};
Node3.prototype["direction"] = Node3.prototype.direction = function() {
    return wrapPointer(_mud_Node3_direction_0(this.__ptr), v3_float);
};
Object.defineProperty(Node3.prototype, "transform", {
    get: function() {
        return wrapPointer(_mud_Node3__get_transform(this.__ptr), mat4);
    },
    set: function(value) {
        _mud_Node3__set_transform(this.__ptr, value.__ptr);
    }
});
Node3.prototype["__destroy"] = Node3.prototype.__destroy = function() {
    _mud_Node3__destroy(this.__ptr);
};
// Pass
function Pass() {
    this.__ptr = _mud_Pass__construct_0(); this.__type = Pass.__type; getCache(Pass)[this.__ptr] = this;
};
Pass.prototype = Object.create(WrapperObject.prototype);
Pass.prototype.constructor = Pass;
Pass.prototype.__class = Pass;
Pass.__cache = {};
Module['Pass'] = Pass;
Object.defineProperty(Pass.prototype, "target", {
    get: function() {
        return wrapPointer(_mud_Pass__get_target(this.__ptr), RenderTarget);
    },
    set: function(value) {
        _mud_Pass__set_target(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Pass.prototype, "fbo", {
    get: function() {
        return wrapPointer(_mud_Pass__get_fbo(this.__ptr), FrameBuffer);
    },
    set: function(value) {
        _mud_Pass__set_fbo(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Pass.prototype, "viewport", {
    get: function() {
        return wrapPointer(_mud_Pass__get_viewport(this.__ptr), Viewport);
    },
    set: function(value) {
        _mud_Pass__set_viewport(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Pass.prototype, "rect", {
    get: function() {
        return wrapPointer(_mud_Pass__get_rect(this.__ptr), v4_uint);
    },
    set: function(value) {
        _mud_Pass__set_rect(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Pass.prototype, "bgfx_state", {
    get: function() {
        return _mud_Pass__get_bgfx_state(this.__ptr);
    },
    set: function(value) {
        _mud_Pass__set_bgfx_state(this.__ptr, value);
    }
});
Object.defineProperty(Pass.prototype, "pass_type", {
    get: function() {
        return _mud_Pass__get_pass_type(this.__ptr);
    },
    set: function(value) {
        _mud_Pass__set_pass_type(this.__ptr, value);
    }
});
Object.defineProperty(Pass.prototype, "use_mrt", {
    get: function() {
        return !!(_mud_Pass__get_use_mrt(this.__ptr));
    },
    set: function(value) {
        _mud_Pass__set_use_mrt(this.__ptr, value);
    }
});
Object.defineProperty(Pass.prototype, "index", {
    get: function() {
        return _mud_Pass__get_index(this.__ptr);
    },
    set: function(value) {
        _mud_Pass__set_index(this.__ptr, value);
    }
});
Object.defineProperty(Pass.prototype, "sub_pass", {
    get: function() {
        return _mud_Pass__get_sub_pass(this.__ptr);
    },
    set: function(value) {
        _mud_Pass__set_sub_pass(this.__ptr, value);
    }
});
Pass.prototype["__destroy"] = Pass.prototype.__destroy = function() {
    _mud_Pass__destroy(this.__ptr);
};
// Prefab
function Prefab() { throw "cannot construct a Prefab, no constructor in IDL" }
Prefab.prototype = Object.create(WrapperObject.prototype);
Prefab.prototype.constructor = Prefab;
Prefab.prototype.__class = Prefab;
Prefab.__cache = {};
Module['Prefab'] = Prefab;
Object.defineProperty(Prefab.prototype, "name", {
    get: function() {
        return Pointer_stringify(_mud_Prefab__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Prefab__set_name(this.__ptr, ensureString(value));
    }
});
Prefab.prototype["__destroy"] = Prefab.prototype.__destroy = function() {
    _mud_Prefab__destroy(this.__ptr);
};
// Program
function Program() { throw "cannot construct a Program, no constructor in IDL" }
Program.prototype = Object.create(WrapperObject.prototype);
Program.prototype.constructor = Program;
Program.prototype.__class = Program;
Program.__cache = {};
Module['Program'] = Program;
Program.prototype["set_block"] = Program.prototype.set_block = function(a0, a1) {
    if (a1 === undefined) { _mud_Program_set_block_1(this.__ptr, /*block*/a0); return; }
    _mud_Program_set_block_2(this.__ptr, /*block*/a0, /*enabled*/a1);
};
Program.prototype["set_pass"] = Program.prototype.set_pass = function(a0, a1) {
    if (a1 === undefined) { _mud_Program_set_pass_1(this.__ptr, /*type*/a0); return; }
    _mud_Program_set_pass_2(this.__ptr, /*type*/a0, /*enabled*/a1);
};
Program.prototype["set_source"] = Program.prototype.set_source = function(a0, a1) {
    ensureCache.prepare();
    _mud_Program_set_source_2(this.__ptr, /*type*/a0, ensureString(/*source*/a1));
};
Object.defineProperty(Program.prototype, "name", {
    get: function() {
        return Pointer_stringify(_mud_Program__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Program__set_name(this.__ptr, ensureString(value));
    }
});
Program.prototype["__destroy"] = Program.prototype.__destroy = function() {
    _mud_Program__destroy(this.__ptr);
};
// Radiance
function Radiance() {
    this.__ptr = _mud_Radiance__construct_0(); this.__type = Radiance.__type; getCache(Radiance)[this.__ptr] = this;
};
Radiance.prototype = Object.create(WrapperObject.prototype);
Radiance.prototype.constructor = Radiance;
Radiance.prototype.__class = Radiance;
Radiance.__cache = {};
Module['Radiance'] = Radiance;
Object.defineProperty(Radiance.prototype, "colour", {
    get: function() {
        return wrapPointer(_mud_Radiance__get_colour(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_Radiance__set_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Radiance.prototype, "energy", {
    get: function() {
        return _mud_Radiance__get_energy(this.__ptr);
    },
    set: function(value) {
        _mud_Radiance__set_energy(this.__ptr, value);
    }
});
Object.defineProperty(Radiance.prototype, "ambient", {
    get: function() {
        return _mud_Radiance__get_ambient(this.__ptr);
    },
    set: function(value) {
        _mud_Radiance__set_ambient(this.__ptr, value);
    }
});
Object.defineProperty(Radiance.prototype, "texture", {
    get: function() {
        return wrapPointer(_mud_Radiance__get_texture(this.__ptr), Texture);
    },
    set: function(value) {
        _mud_Radiance__set_texture(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Radiance.prototype, "filtered", {
    get: function() {
        return wrapPointer(_mud_Radiance__get_filtered(this.__ptr), Texture);
    },
    set: function(value) {
        _mud_Radiance__set_filtered(this.__ptr, value.__ptr);
    }
});
Radiance.prototype["__destroy"] = Radiance.prototype.__destroy = function() {
    _mud_Radiance__destroy(this.__ptr);
};
// Render
function Render(a0, a1, a2, a3, a4) {
    if (a4 === undefined) { this.__ptr = _mud_Render__construct_4(/*shading*/a0, /*viewport*/a1.__ptr, /*target*/a2.__ptr, /*frame*/a3.__ptr); this.__type = Render.__type; getCache(Render)[this.__ptr] = this; return; }
    this.__ptr = _mud_Render__construct_5(/*shading*/a0, /*viewport*/a1.__ptr, /*target*/a2.__ptr, /*target_fbo*/a3.__ptr, /*frame*/a4.__ptr); this.__type = Render.__type; getCache(Render)[this.__ptr] = this;
};
Render.prototype = Object.create(WrapperObject.prototype);
Render.prototype.constructor = Render;
Render.prototype.__class = Render;
Render.__cache = {};
Module['Render'] = Render;
Render.prototype["next_pass"] = Render.prototype.next_pass = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_Render_next_pass_2(this.__ptr, ensureString(/*name*/a0), /*type*/a1), Pass); }
    return wrapPointer(_mud_Render_next_pass_3(this.__ptr, ensureString(/*name*/a0), /*type*/a1, /*subpass*/a2), Pass);
};
Render.prototype["composite_pass"] = Render.prototype.composite_pass = function(a0, a1, a2) {
    ensureCache.prepare();
    return wrapPointer(_mud_Render_composite_pass_3(this.__ptr, ensureString(/*name*/a0), /*fbo*/a1.__ptr, /*rect*/a2.__ptr), Pass);
};
Object.defineProperty(Render.prototype, "shading", {
    get: function() {
        return _mud_Render__get_shading(this.__ptr);
    },
    set: function(value) {
        _mud_Render__set_shading(this.__ptr, value);
    }
});
Object.defineProperty(Render.prototype, "scene", {
    get: function() {
        return wrapPointer(_mud_Render__get_scene(this.__ptr), Scene);
    },
    set: function(value) {
        _mud_Render__set_scene(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Render.prototype, "target", {
    get: function() {
        return wrapPointer(_mud_Render__get_target(this.__ptr), RenderTarget);
    },
    set: function(value) {
        _mud_Render__set_target(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Render.prototype, "target_fbo", {
    get: function() {
        return wrapPointer(_mud_Render__get_target_fbo(this.__ptr), FrameBuffer);
    },
    set: function(value) {
        _mud_Render__set_target_fbo(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Render.prototype, "viewport", {
    get: function() {
        return wrapPointer(_mud_Render__get_viewport(this.__ptr), Viewport);
    },
    set: function(value) {
        _mud_Render__set_viewport(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Render.prototype, "rect", {
    get: function() {
        return wrapPointer(_mud_Render__get_rect(this.__ptr), v4_uint);
    },
    set: function(value) {
        _mud_Render__set_rect(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Render.prototype, "camera", {
    get: function() {
        return wrapPointer(_mud_Render__get_camera(this.__ptr), Camera);
    },
    set: function(value) {
        _mud_Render__set_camera(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Render.prototype, "frame", {
    get: function() {
        return wrapPointer(_mud_Render__get_frame(this.__ptr), RenderFrame);
    },
    set: function(value) {
        _mud_Render__set_frame(this.__ptr, value.__ptr);
    }
});
Render.prototype["__destroy"] = Render.prototype.__destroy = function() {
    _mud_Render__destroy(this.__ptr);
};
// RenderFrame
function RenderFrame() {
    this.__ptr = _mud_RenderFrame__construct_0(); this.__type = RenderFrame.__type; getCache(RenderFrame)[this.__ptr] = this;
};
RenderFrame.prototype = Object.create(WrapperObject.prototype);
RenderFrame.prototype.constructor = RenderFrame;
RenderFrame.prototype.__class = RenderFrame;
RenderFrame.__cache = {};
Module['RenderFrame'] = RenderFrame;
Object.defineProperty(RenderFrame.prototype, "frame", {
    get: function() {
        return _mud_RenderFrame__get_frame(this.__ptr);
    },
    set: function(value) {
        _mud_RenderFrame__set_frame(this.__ptr, value);
    }
});
Object.defineProperty(RenderFrame.prototype, "time", {
    get: function() {
        return _mud_RenderFrame__get_time(this.__ptr);
    },
    set: function(value) {
        _mud_RenderFrame__set_time(this.__ptr, value);
    }
});
Object.defineProperty(RenderFrame.prototype, "delta_time", {
    get: function() {
        return _mud_RenderFrame__get_delta_time(this.__ptr);
    },
    set: function(value) {
        _mud_RenderFrame__set_delta_time(this.__ptr, value);
    }
});
Object.defineProperty(RenderFrame.prototype, "render_pass", {
    get: function() {
        return _mud_RenderFrame__get_render_pass(this.__ptr);
    },
    set: function(value) {
        _mud_RenderFrame__set_render_pass(this.__ptr, value);
    }
});
Object.defineProperty(RenderFrame.prototype, "nudraw_calls", {
    get: function() {
        return _mud_RenderFrame__get_nudraw_calls(this.__ptr);
    },
    set: function(value) {
        _mud_RenderFrame__set_nudraw_calls(this.__ptr, value);
    }
});
Object.defineProperty(RenderFrame.prototype, "nuvertices", {
    get: function() {
        return _mud_RenderFrame__get_nuvertices(this.__ptr);
    },
    set: function(value) {
        _mud_RenderFrame__set_nuvertices(this.__ptr, value);
    }
});
Object.defineProperty(RenderFrame.prototype, "nutriangles", {
    get: function() {
        return _mud_RenderFrame__get_nutriangles(this.__ptr);
    },
    set: function(value) {
        _mud_RenderFrame__set_nutriangles(this.__ptr, value);
    }
});
RenderFrame.prototype["__destroy"] = RenderFrame.prototype.__destroy = function() {
    _mud_RenderFrame__destroy(this.__ptr);
};
// RenderQuad
function RenderQuad(a0, a1, a2) {
    if (a0 === undefined) { this.__ptr = _mud_RenderQuad__construct_0(); this.__type = RenderQuad.__type; getCache(RenderQuad)[this.__ptr] = this; return; }
    if (a2 === undefined) { this.__ptr = _mud_RenderQuad__construct_2(/*crop*/a0.__ptr, /*dest*/a1.__ptr); this.__type = RenderQuad.__type; getCache(RenderQuad)[this.__ptr] = this; return; }
    this.__ptr = _mud_RenderQuad__construct_3(/*crop*/a0.__ptr, /*dest*/a1.__ptr, /*fbo_flip*/a2); this.__type = RenderQuad.__type; getCache(RenderQuad)[this.__ptr] = this;
};
RenderQuad.prototype = Object.create(WrapperObject.prototype);
RenderQuad.prototype.constructor = RenderQuad;
RenderQuad.prototype.__class = RenderQuad;
RenderQuad.__cache = {};
Module['RenderQuad'] = RenderQuad;
Object.defineProperty(RenderQuad.prototype, "source", {
    get: function() {
        return wrapPointer(_mud_RenderQuad__get_source(this.__ptr), v4_float);
    },
    set: function(value) {
        _mud_RenderQuad__set_source(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(RenderQuad.prototype, "dest", {
    get: function() {
        return wrapPointer(_mud_RenderQuad__get_dest(this.__ptr), v4_float);
    },
    set: function(value) {
        _mud_RenderQuad__set_dest(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(RenderQuad.prototype, "fbo_flip", {
    get: function() {
        return !!(_mud_RenderQuad__get_fbo_flip(this.__ptr));
    },
    set: function(value) {
        _mud_RenderQuad__set_fbo_flip(this.__ptr, value);
    }
});
RenderQuad.prototype["__destroy"] = RenderQuad.prototype.__destroy = function() {
    _mud_RenderQuad__destroy(this.__ptr);
};
// Renderer
function Renderer() { throw "cannot construct a Renderer, no constructor in IDL" }
Renderer.prototype = Object.create(WrapperObject.prototype);
Renderer.prototype.constructor = Renderer;
Renderer.prototype.__class = Renderer;
Renderer.__cache = {};
Module['Renderer'] = Renderer;
Renderer.prototype["gather"] = Renderer.prototype.gather = function(a0) {
    _mud_Renderer_gather_1(this.__ptr, /*render*/a0.__ptr);
};
Renderer.prototype["begin"] = Renderer.prototype.begin = function(a0) {
    _mud_Renderer_begin_1(this.__ptr, /*render*/a0.__ptr);
};
Renderer.prototype["end"] = Renderer.prototype.end = function(a0) {
    _mud_Renderer_end_1(this.__ptr, /*render*/a0.__ptr);
};
Renderer.prototype["__destroy"] = Renderer.prototype.__destroy = function() {
    _mud_Renderer__destroy(this.__ptr);
};
// Rig
function Rig() { throw "cannot construct a Rig, no constructor in IDL" }
Rig.prototype = Object.create(WrapperObject.prototype);
Rig.prototype.constructor = Rig;
Rig.prototype.__class = Rig;
Rig.__cache = {};
Module['Rig'] = Rig;
Rig.prototype["__destroy"] = Rig.prototype.__destroy = function() {
    _mud_Rig__destroy(this.__ptr);
};
// Scene
function Scene(a0) {
    this.__ptr = _mud_Scene__construct_1(/*gfx*/a0.__ptr); this.__type = Scene.__type; getCache(Scene)[this.__ptr] = this;
};
Scene.prototype = Object.create(WrapperObject.prototype);
Scene.prototype.constructor = Scene;
Scene.prototype.__class = Scene;
Scene.__cache = {};
Module['Scene'] = Scene;
Scene.prototype["begin"] = Scene.prototype.begin = function() {
    return wrapPointer(_mud_Scene_begin_0(this.__ptr), Gnode);
};
Scene.prototype["nodes"] = Scene.prototype.nodes = function() {
    return wrapPointer(_mud_Scene_nodes_0(this.__ptr), TPool_mud_Node3);
};
Scene.prototype["items"] = Scene.prototype.items = function() {
    return wrapPointer(_mud_Scene_items_0(this.__ptr), TPool_mud_Item);
};
Scene.prototype["batches"] = Scene.prototype.batches = function() {
    return wrapPointer(_mud_Scene_batches_0(this.__ptr), TPool_mud_Batch);
};
Scene.prototype["directs"] = Scene.prototype.directs = function() {
    return wrapPointer(_mud_Scene_directs_0(this.__ptr), TPool_mud_Direct);
};
Scene.prototype["mimes"] = Scene.prototype.mimes = function() {
    return wrapPointer(_mud_Scene_mimes_0(this.__ptr), TPool_mud_Mime);
};
Scene.prototype["lights"] = Scene.prototype.lights = function() {
    return wrapPointer(_mud_Scene_lights_0(this.__ptr), TPool_mud_Light);
};
Scene.prototype["flares"] = Scene.prototype.flares = function() {
    return wrapPointer(_mud_Scene_flares_0(this.__ptr), TPool_mud_Flare);
};
Object.defineProperty(Scene.prototype, "index", {
    get: function() {
        return _mud_Scene__get_index(this.__ptr);
    },
    set: function(value) {
        _mud_Scene__set_index(this.__ptr, value);
    }
});
Object.defineProperty(Scene.prototype, "graph", {
    get: function() {
        return wrapPointer(_mud_Scene__get_graph(this.__ptr), Gnode);
    }});
Object.defineProperty(Scene.prototype, "root_node", {
    get: function() {
        return wrapPointer(_mud_Scene__get_root_node(this.__ptr), Node3);
    }});
Object.defineProperty(Scene.prototype, "env", {
    get: function() {
        return wrapPointer(_mud_Scene__get_env(this.__ptr), Zone);
    },
    set: function(value) {
        _mud_Scene__set_env(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Scene.prototype, "user", {
    get: function() {
        return wrapPointer(_mud_Scene__get_user(this.__ptr), Ref);
    },
    set: function(value) {
        _mud_Scene__set_user(this.__ptr, ensureRef(value), ensureRefType(value));
    }
});
Scene.prototype["__destroy"] = Scene.prototype.__destroy = function() {
    _mud_Scene__destroy(this.__ptr);
};
// Shot
function Shot() { throw "cannot construct a Shot, no constructor in IDL" }
Shot.prototype = Object.create(WrapperObject.prototype);
Shot.prototype.constructor = Shot;
Shot.prototype.__class = Shot;
Shot.__cache = {};
Module['Shot'] = Shot;
Shot.prototype["__destroy"] = Shot.prototype.__destroy = function() {
    _mud_Shot__destroy(this.__ptr);
};
// Skeleton
function Skeleton() { throw "cannot construct a Skeleton, no constructor in IDL" }
Skeleton.prototype = Object.create(WrapperObject.prototype);
Skeleton.prototype.constructor = Skeleton;
Skeleton.prototype.__class = Skeleton;
Skeleton.__cache = {};
Module['Skeleton'] = Skeleton;
Skeleton.prototype["__destroy"] = Skeleton.prototype.__destroy = function() {
    _mud_Skeleton__destroy(this.__ptr);
};
// Skin
function Skin() { throw "cannot construct a Skin, no constructor in IDL" }
Skin.prototype = Object.create(WrapperObject.prototype);
Skin.prototype.constructor = Skin;
Skin.prototype.__class = Skin;
Skin.__cache = {};
Module['Skin'] = Skin;
Skin.prototype["__destroy"] = Skin.prototype.__destroy = function() {
    _mud_Skin__destroy(this.__ptr);
};
// Sun
function Sun() {
    this.__ptr = _mud_Sun__construct_0(); this.__type = Sun.__type; getCache(Sun)[this.__ptr] = this;
};
Sun.prototype = Object.create(WrapperObject.prototype);
Sun.prototype.constructor = Sun;
Sun.prototype.__class = Sun;
Sun.__cache = {};
Module['Sun'] = Sun;
Object.defineProperty(Sun.prototype, "azimuth", {
    get: function() {
        return _mud_Sun__get_azimuth(this.__ptr);
    },
    set: function(value) {
        _mud_Sun__set_azimuth(this.__ptr, value);
    }
});
Object.defineProperty(Sun.prototype, "elevation", {
    get: function() {
        return _mud_Sun__get_elevation(this.__ptr);
    },
    set: function(value) {
        _mud_Sun__set_elevation(this.__ptr, value);
    }
});
Object.defineProperty(Sun.prototype, "colour", {
    get: function() {
        return wrapPointer(_mud_Sun__get_colour(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_Sun__set_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Sun.prototype, "intensity", {
    get: function() {
        return _mud_Sun__get_intensity(this.__ptr);
    },
    set: function(value) {
        _mud_Sun__set_intensity(this.__ptr, value);
    }
});
Sun.prototype["__destroy"] = Sun.prototype.__destroy = function() {
    _mud_Sun__destroy(this.__ptr);
};
// SwapBuffer
function SwapBuffer() { throw "cannot construct a SwapBuffer, no constructor in IDL" }
SwapBuffer.prototype = Object.create(WrapperObject.prototype);
SwapBuffer.prototype.constructor = SwapBuffer;
SwapBuffer.prototype.__class = SwapBuffer;
SwapBuffer.__cache = {};
Module['SwapBuffer'] = SwapBuffer;
SwapBuffer.prototype["swap"] = SwapBuffer.prototype.swap = function() {
    return wrapPointer(_mud_SwapBuffer_swap_0(this.__ptr), FrameBuffer);
};
SwapBuffer.prototype["last"] = SwapBuffer.prototype.last = function() {
    return wrapPointer(_mud_SwapBuffer_last_0(this.__ptr), Texture);
};
Object.defineProperty(SwapBuffer.prototype, "one", {
    get: function() {
        return wrapPointer(_mud_SwapBuffer__get_one(this.__ptr), FrameBuffer);
    }});
Object.defineProperty(SwapBuffer.prototype, "two", {
    get: function() {
        return wrapPointer(_mud_SwapBuffer__get_two(this.__ptr), FrameBuffer);
    }});
SwapBuffer.prototype["__destroy"] = SwapBuffer.prototype.__destroy = function() {
    _mud_SwapBuffer__destroy(this.__ptr);
};
// SwapCascade
function SwapCascade() { throw "cannot construct a SwapCascade, no constructor in IDL" }
SwapCascade.prototype = Object.create(WrapperObject.prototype);
SwapCascade.prototype.constructor = SwapCascade;
SwapCascade.prototype.__class = SwapCascade;
SwapCascade.__cache = {};
Module['SwapCascade'] = SwapCascade;
SwapCascade.prototype["swap"] = SwapCascade.prototype.swap = function() {
    return wrapPointer(_mud_SwapCascade_swap_0(this.__ptr), Cascade);
};
SwapCascade.prototype["last"] = SwapCascade.prototype.last = function() {
    return wrapPointer(_mud_SwapCascade_last_0(this.__ptr), Cascade);
};
Object.defineProperty(SwapCascade.prototype, "one", {
    get: function() {
        return wrapPointer(_mud_SwapCascade__get_one(this.__ptr), Cascade);
    }});
Object.defineProperty(SwapCascade.prototype, "two", {
    get: function() {
        return wrapPointer(_mud_SwapCascade__get_two(this.__ptr), Cascade);
    }});
SwapCascade.prototype["__destroy"] = SwapCascade.prototype.__destroy = function() {
    _mud_SwapCascade__destroy(this.__ptr);
};
// SymbolIndex
function SymbolIndex() { throw "cannot construct a SymbolIndex, no constructor in IDL" }
SymbolIndex.prototype = Object.create(WrapperObject.prototype);
SymbolIndex.prototype.constructor = SymbolIndex;
SymbolIndex.prototype.__class = SymbolIndex;
SymbolIndex.__cache = {};
Module['SymbolIndex'] = SymbolIndex;
SymbolIndex.prototype["__destroy"] = SymbolIndex.prototype.__destroy = function() {
    _mud_SymbolIndex__destroy(this.__ptr);
};
// TPool<mud::Batch>
function TPool_mud_Batch() { throw "cannot construct a TPool<mud::Batch>, no constructor in IDL" }
TPool_mud_Batch.prototype = Object.create(WrapperObject.prototype);
TPool_mud_Batch.prototype.constructor = TPool_mud_Batch;
TPool_mud_Batch.prototype.__class = TPool_mud_Batch;
TPool_mud_Batch.__cache = {};
Module['TPool_mud_Batch'] = TPool_mud_Batch;
TPool_mud_Batch.prototype["add"] = TPool_mud_Batch.prototype.add = function(a0) {
    return wrapPointer(_mud_TPool_mud_Batch_add_1(this.__ptr, /*value*/a0.__ptr), Batch);
};
TPool_mud_Batch.prototype["talloc"] = TPool_mud_Batch.prototype.talloc = function() {
    return wrapPointer(_mud_TPool_mud_Batch_talloc_0(this.__ptr), Batch);
};
TPool_mud_Batch.prototype["tdestroy"] = TPool_mud_Batch.prototype.tdestroy = function(a0) {
    _mud_TPool_mud_Batch_tdestroy_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Batch.prototype["tfree"] = TPool_mud_Batch.prototype.tfree = function(a0) {
    _mud_TPool_mud_Batch_tfree_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Batch.prototype["__destroy"] = TPool_mud_Batch.prototype.__destroy = function() {
    _mud_TPool_mud_Batch__destroy(this.__ptr);
};
// TPool<mud::Direct>
function TPool_mud_Direct() { throw "cannot construct a TPool<mud::Direct>, no constructor in IDL" }
TPool_mud_Direct.prototype = Object.create(WrapperObject.prototype);
TPool_mud_Direct.prototype.constructor = TPool_mud_Direct;
TPool_mud_Direct.prototype.__class = TPool_mud_Direct;
TPool_mud_Direct.__cache = {};
Module['TPool_mud_Direct'] = TPool_mud_Direct;
TPool_mud_Direct.prototype["add"] = TPool_mud_Direct.prototype.add = function(a0) {
    return wrapPointer(_mud_TPool_mud_Direct_add_1(this.__ptr, /*value*/a0.__ptr), Direct);
};
TPool_mud_Direct.prototype["talloc"] = TPool_mud_Direct.prototype.talloc = function() {
    return wrapPointer(_mud_TPool_mud_Direct_talloc_0(this.__ptr), Direct);
};
TPool_mud_Direct.prototype["tdestroy"] = TPool_mud_Direct.prototype.tdestroy = function(a0) {
    _mud_TPool_mud_Direct_tdestroy_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Direct.prototype["tfree"] = TPool_mud_Direct.prototype.tfree = function(a0) {
    _mud_TPool_mud_Direct_tfree_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Direct.prototype["__destroy"] = TPool_mud_Direct.prototype.__destroy = function() {
    _mud_TPool_mud_Direct__destroy(this.__ptr);
};
// TPool<mud::Flare>
function TPool_mud_Flare() { throw "cannot construct a TPool<mud::Flare>, no constructor in IDL" }
TPool_mud_Flare.prototype = Object.create(WrapperObject.prototype);
TPool_mud_Flare.prototype.constructor = TPool_mud_Flare;
TPool_mud_Flare.prototype.__class = TPool_mud_Flare;
TPool_mud_Flare.__cache = {};
Module['TPool_mud_Flare'] = TPool_mud_Flare;
TPool_mud_Flare.prototype["add"] = TPool_mud_Flare.prototype.add = function(a0) {
    return wrapPointer(_mud_TPool_mud_Flare_add_1(this.__ptr, /*value*/a0.__ptr), Flare);
};
TPool_mud_Flare.prototype["talloc"] = TPool_mud_Flare.prototype.talloc = function() {
    return wrapPointer(_mud_TPool_mud_Flare_talloc_0(this.__ptr), Flare);
};
TPool_mud_Flare.prototype["tdestroy"] = TPool_mud_Flare.prototype.tdestroy = function(a0) {
    _mud_TPool_mud_Flare_tdestroy_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Flare.prototype["tfree"] = TPool_mud_Flare.prototype.tfree = function(a0) {
    _mud_TPool_mud_Flare_tfree_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Flare.prototype["__destroy"] = TPool_mud_Flare.prototype.__destroy = function() {
    _mud_TPool_mud_Flare__destroy(this.__ptr);
};
// TPool<mud::Item>
function TPool_mud_Item() { throw "cannot construct a TPool<mud::Item>, no constructor in IDL" }
TPool_mud_Item.prototype = Object.create(WrapperObject.prototype);
TPool_mud_Item.prototype.constructor = TPool_mud_Item;
TPool_mud_Item.prototype.__class = TPool_mud_Item;
TPool_mud_Item.__cache = {};
Module['TPool_mud_Item'] = TPool_mud_Item;
TPool_mud_Item.prototype["add"] = TPool_mud_Item.prototype.add = function(a0) {
    return wrapPointer(_mud_TPool_mud_Item_add_1(this.__ptr, /*value*/a0.__ptr), Item);
};
TPool_mud_Item.prototype["talloc"] = TPool_mud_Item.prototype.talloc = function() {
    return wrapPointer(_mud_TPool_mud_Item_talloc_0(this.__ptr), Item);
};
TPool_mud_Item.prototype["tdestroy"] = TPool_mud_Item.prototype.tdestroy = function(a0) {
    _mud_TPool_mud_Item_tdestroy_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Item.prototype["tfree"] = TPool_mud_Item.prototype.tfree = function(a0) {
    _mud_TPool_mud_Item_tfree_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Item.prototype["__destroy"] = TPool_mud_Item.prototype.__destroy = function() {
    _mud_TPool_mud_Item__destroy(this.__ptr);
};
// TPool<mud::Light>
function TPool_mud_Light() { throw "cannot construct a TPool<mud::Light>, no constructor in IDL" }
TPool_mud_Light.prototype = Object.create(WrapperObject.prototype);
TPool_mud_Light.prototype.constructor = TPool_mud_Light;
TPool_mud_Light.prototype.__class = TPool_mud_Light;
TPool_mud_Light.__cache = {};
Module['TPool_mud_Light'] = TPool_mud_Light;
TPool_mud_Light.prototype["add"] = TPool_mud_Light.prototype.add = function(a0) {
    return wrapPointer(_mud_TPool_mud_Light_add_1(this.__ptr, /*value*/a0.__ptr), Light);
};
TPool_mud_Light.prototype["talloc"] = TPool_mud_Light.prototype.talloc = function() {
    return wrapPointer(_mud_TPool_mud_Light_talloc_0(this.__ptr), Light);
};
TPool_mud_Light.prototype["tdestroy"] = TPool_mud_Light.prototype.tdestroy = function(a0) {
    _mud_TPool_mud_Light_tdestroy_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Light.prototype["tfree"] = TPool_mud_Light.prototype.tfree = function(a0) {
    _mud_TPool_mud_Light_tfree_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Light.prototype["__destroy"] = TPool_mud_Light.prototype.__destroy = function() {
    _mud_TPool_mud_Light__destroy(this.__ptr);
};
// TPool<mud::Mime>
function TPool_mud_Mime() { throw "cannot construct a TPool<mud::Mime>, no constructor in IDL" }
TPool_mud_Mime.prototype = Object.create(WrapperObject.prototype);
TPool_mud_Mime.prototype.constructor = TPool_mud_Mime;
TPool_mud_Mime.prototype.__class = TPool_mud_Mime;
TPool_mud_Mime.__cache = {};
Module['TPool_mud_Mime'] = TPool_mud_Mime;
TPool_mud_Mime.prototype["add"] = TPool_mud_Mime.prototype.add = function(a0) {
    return wrapPointer(_mud_TPool_mud_Mime_add_1(this.__ptr, /*value*/a0.__ptr), Mime);
};
TPool_mud_Mime.prototype["talloc"] = TPool_mud_Mime.prototype.talloc = function() {
    return wrapPointer(_mud_TPool_mud_Mime_talloc_0(this.__ptr), Mime);
};
TPool_mud_Mime.prototype["tdestroy"] = TPool_mud_Mime.prototype.tdestroy = function(a0) {
    _mud_TPool_mud_Mime_tdestroy_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Mime.prototype["tfree"] = TPool_mud_Mime.prototype.tfree = function(a0) {
    _mud_TPool_mud_Mime_tfree_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Mime.prototype["__destroy"] = TPool_mud_Mime.prototype.__destroy = function() {
    _mud_TPool_mud_Mime__destroy(this.__ptr);
};
// TPool<mud::Node3>
function TPool_mud_Node3() { throw "cannot construct a TPool<mud::Node3>, no constructor in IDL" }
TPool_mud_Node3.prototype = Object.create(WrapperObject.prototype);
TPool_mud_Node3.prototype.constructor = TPool_mud_Node3;
TPool_mud_Node3.prototype.__class = TPool_mud_Node3;
TPool_mud_Node3.__cache = {};
Module['TPool_mud_Node3'] = TPool_mud_Node3;
TPool_mud_Node3.prototype["add"] = TPool_mud_Node3.prototype.add = function(a0) {
    return wrapPointer(_mud_TPool_mud_Node3_add_1(this.__ptr, /*value*/a0.__ptr), Node3);
};
TPool_mud_Node3.prototype["talloc"] = TPool_mud_Node3.prototype.talloc = function() {
    return wrapPointer(_mud_TPool_mud_Node3_talloc_0(this.__ptr), Node3);
};
TPool_mud_Node3.prototype["tdestroy"] = TPool_mud_Node3.prototype.tdestroy = function(a0) {
    _mud_TPool_mud_Node3_tdestroy_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Node3.prototype["tfree"] = TPool_mud_Node3.prototype.tfree = function(a0) {
    _mud_TPool_mud_Node3_tfree_1(this.__ptr, /*object*/a0.__ptr);
};
TPool_mud_Node3.prototype["__destroy"] = TPool_mud_Node3.prototype.__destroy = function() {
    _mud_TPool_mud_Node3__destroy(this.__ptr);
};
// Texture
function Texture() { throw "cannot construct a Texture, no constructor in IDL" }
Texture.prototype = Object.create(WrapperObject.prototype);
Texture.prototype.constructor = Texture;
Texture.prototype.__class = Texture;
Texture.__cache = {};
Module['Texture'] = Texture;
Texture.prototype["valid"] = Texture.prototype.valid = function() {
    return !!(_mud_Texture_valid_0(this.__ptr));
};
Object.defineProperty(Texture.prototype, "name", {
    get: function() {
        return Pointer_stringify(_mud_Texture__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Texture__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Texture.prototype, "size", {
    get: function() {
        return wrapPointer(_mud_Texture__get_size(this.__ptr), v2_uint);
    },
    set: function(value) {
        _mud_Texture__set_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Texture.prototype, "depth", {
    get: function() {
        return _mud_Texture__get_depth(this.__ptr);
    },
    set: function(value) {
        _mud_Texture__set_depth(this.__ptr, value);
    }
});
Object.defineProperty(Texture.prototype, "memsize", {
    get: function() {
        return _mud_Texture__get_memsize(this.__ptr);
    },
    set: function(value) {
        _mud_Texture__set_memsize(this.__ptr, value);
    }
});
Object.defineProperty(Texture.prototype, "bits_per_pixel", {
    get: function() {
        return _mud_Texture__get_bits_per_pixel(this.__ptr);
    },
    set: function(value) {
        _mud_Texture__set_bits_per_pixel(this.__ptr, value);
    }
});
Object.defineProperty(Texture.prototype, "is_depth", {
    get: function() {
        return !!(_mud_Texture__get_is_depth(this.__ptr));
    },
    set: function(value) {
        _mud_Texture__set_is_depth(this.__ptr, value);
    }
});
Object.defineProperty(Texture.prototype, "is_depth_packed", {
    get: function() {
        return !!(_mud_Texture__get_is_depth_packed(this.__ptr));
    },
    set: function(value) {
        _mud_Texture__set_is_depth_packed(this.__ptr, value);
    }
});
Object.defineProperty(Texture.prototype, "is_array", {
    get: function() {
        return !!(_mud_Texture__get_is_array(this.__ptr));
    },
    set: function(value) {
        _mud_Texture__set_is_array(this.__ptr, value);
    }
});
Object.defineProperty(Texture.prototype, "is_cube", {
    get: function() {
        return !!(_mud_Texture__get_is_cube(this.__ptr));
    },
    set: function(value) {
        _mud_Texture__set_is_cube(this.__ptr, value);
    }
});
Object.defineProperty(Texture.prototype, "is_fbo", {
    get: function() {
        return !!(_mud_Texture__get_is_fbo(this.__ptr));
    },
    set: function(value) {
        _mud_Texture__set_is_fbo(this.__ptr, value);
    }
});
Object.defineProperty(Texture.prototype, "mips", {
    get: function() {
        return !!(_mud_Texture__get_mips(this.__ptr));
    },
    set: function(value) {
        _mud_Texture__set_mips(this.__ptr, value);
    }
});
Texture.prototype["__destroy"] = Texture.prototype.__destroy = function() {
    _mud_Texture__destroy(this.__ptr);
};
// Zone
function Zone() {
    this.__ptr = _mud_Zone__construct_0(); this.__type = Zone.__type; getCache(Zone)[this.__ptr] = this;
};
Zone.prototype = Object.create(WrapperObject.prototype);
Zone.prototype.constructor = Zone;
Zone.prototype.__class = Zone;
Zone.__cache = {};
Module['Zone'] = Zone;
Object.defineProperty(Zone.prototype, "background", {
    get: function() {
        return wrapPointer(_mud_Zone__get_background(this.__ptr), Background);
    },
    set: function(value) {
        _mud_Zone__set_background(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Zone.prototype, "radiance", {
    get: function() {
        return wrapPointer(_mud_Zone__get_radiance(this.__ptr), Radiance);
    },
    set: function(value) {
        _mud_Zone__set_radiance(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Zone.prototype, "sun", {
    get: function() {
        return wrapPointer(_mud_Zone__get_sun(this.__ptr), Sun);
    },
    set: function(value) {
        _mud_Zone__set_sun(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Zone.prototype, "fog", {
    get: function() {
        return wrapPointer(_mud_Zone__get_fog(this.__ptr), Fog);
    },
    set: function(value) {
        _mud_Zone__set_fog(this.__ptr, value.__ptr);
    }
});
Zone.prototype["__destroy"] = Zone.prototype.__destroy = function() {
    _mud_Zone__destroy(this.__ptr);
};
// BlockCopy
function BlockCopy() { throw "cannot construct a BlockCopy, no constructor in IDL" }
BlockCopy.prototype = Object.create(GfxBlock.prototype);
BlockCopy.prototype.constructor = BlockCopy;
BlockCopy.prototype.__class = BlockCopy;
BlockCopy.__cache = {};
Module['BlockCopy'] = BlockCopy;
BlockCopy.prototype["quad"] = BlockCopy.prototype.quad = function(a0, a1, a2, a3, a4) {
    if (a4 === undefined) { _mud_BlockCopy_quad_4(this.__ptr, /*view*/a0, /*fbo*/a1.__ptr, /*texture*/a2.__ptr, /*rect*/a3.__ptr); return; }
    _mud_BlockCopy_quad_5(this.__ptr, /*view*/a0, /*fbo*/a1.__ptr, /*texture*/a2.__ptr, /*rect*/a3.__ptr, /*flags*/a4);
};
BlockCopy.prototype["__destroy"] = BlockCopy.prototype.__destroy = function() {
    _mud_BlockCopy__destroy(this.__ptr);
};
// BlockDepth
function BlockDepth() { throw "cannot construct a BlockDepth, no constructor in IDL" }
BlockDepth.prototype = Object.create(DrawBlock.prototype);
BlockDepth.prototype.constructor = BlockDepth;
BlockDepth.prototype.__class = BlockDepth;
BlockDepth.__cache = {};
Module['BlockDepth'] = BlockDepth;
BlockDepth.prototype["__destroy"] = BlockDepth.prototype.__destroy = function() {
    _mud_BlockDepth__destroy(this.__ptr);
};
// BlockFilter
function BlockFilter() { throw "cannot construct a BlockFilter, no constructor in IDL" }
BlockFilter.prototype = Object.create(GfxBlock.prototype);
BlockFilter.prototype.constructor = BlockFilter;
BlockFilter.prototype.__class = BlockFilter;
BlockFilter.__cache = {};
Module['BlockFilter'] = BlockFilter;
BlockFilter.prototype["quad"] = BlockFilter.prototype.quad = function(a0, a1, a2, a3, a4, a5) {
    if (a4 === undefined) { _mud_BlockFilter_quad_4(this.__ptr, /*view*/a0, /*fbo*/a1.__ptr, /*program*/a2.__ptr, /*rect*/a3.__ptr); return; }
    if (a5 === undefined) { _mud_BlockFilter_quad_5(this.__ptr, /*view*/a0, /*fbo*/a1.__ptr, /*program*/a2.__ptr, /*rect*/a3.__ptr, /*flags*/a4); return; }
    _mud_BlockFilter_quad_6(this.__ptr, /*view*/a0, /*fbo*/a1.__ptr, /*program*/a2.__ptr, /*rect*/a3.__ptr, /*flags*/a4, /*render*/a5);
};
BlockFilter.prototype["source0"] = BlockFilter.prototype.source0 = function(a0, a1) {
    if (a1 === undefined) { _mud_BlockFilter_source0_1(this.__ptr, /*texture*/a0.__ptr); return; }
    _mud_BlockFilter_source0_2(this.__ptr, /*texture*/a0.__ptr, /*flags*/a1);
};
BlockFilter.prototype["source1"] = BlockFilter.prototype.source1 = function(a0, a1) {
    if (a1 === undefined) { _mud_BlockFilter_source1_1(this.__ptr, /*texture*/a0.__ptr); return; }
    _mud_BlockFilter_source1_2(this.__ptr, /*texture*/a0.__ptr, /*flags*/a1);
};
BlockFilter.prototype["source2"] = BlockFilter.prototype.source2 = function(a0, a1) {
    if (a1 === undefined) { _mud_BlockFilter_source2_1(this.__ptr, /*texture*/a0.__ptr); return; }
    _mud_BlockFilter_source2_2(this.__ptr, /*texture*/a0.__ptr, /*flags*/a1);
};
BlockFilter.prototype["source3"] = BlockFilter.prototype.source3 = function(a0, a1) {
    if (a1 === undefined) { _mud_BlockFilter_source3_1(this.__ptr, /*texture*/a0.__ptr); return; }
    _mud_BlockFilter_source3_2(this.__ptr, /*texture*/a0.__ptr, /*flags*/a1);
};
BlockFilter.prototype["sourcedepth"] = BlockFilter.prototype.sourcedepth = function(a0, a1) {
    if (a1 === undefined) { _mud_BlockFilter_sourcedepth_1(this.__ptr, /*texture*/a0.__ptr); return; }
    _mud_BlockFilter_sourcedepth_2(this.__ptr, /*texture*/a0.__ptr, /*flags*/a1);
};
BlockFilter.prototype["uniform"] = BlockFilter.prototype.uniform = function(a0, a1, a2) {
    ensureCache.prepare();
    _mud_BlockFilter_uniform_3(this.__ptr, /*view*/a0, ensureString(/*name*/a1), /*value*/a2.__ptr);
};
BlockFilter.prototype["uniforms"] = BlockFilter.prototype.uniforms = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    _mud_BlockFilter_uniforms_4(this.__ptr, /*view*/a0, ensureString(/*name*/a1), /*value*/a2.__ptr, /*num*/a3);
};
BlockFilter.prototype["__destroy"] = BlockFilter.prototype.__destroy = function() {
    _mud_BlockFilter__destroy(this.__ptr);
};
// BlockMaterial
function BlockMaterial() { throw "cannot construct a BlockMaterial, no constructor in IDL" }
BlockMaterial.prototype = Object.create(GfxBlock.prototype);
BlockMaterial.prototype.constructor = BlockMaterial;
BlockMaterial.prototype.__class = BlockMaterial;
BlockMaterial.__cache = {};
Module['BlockMaterial'] = BlockMaterial;
BlockMaterial.prototype["__destroy"] = BlockMaterial.prototype.__destroy = function() {
    _mud_BlockMaterial__destroy(this.__ptr);
};
// BlockParticles
function BlockParticles() { throw "cannot construct a BlockParticles, no constructor in IDL" }
BlockParticles.prototype = Object.create(GfxBlock.prototype);
BlockParticles.prototype.constructor = BlockParticles;
BlockParticles.prototype.__class = BlockParticles;
BlockParticles.__cache = {};
Module['BlockParticles'] = BlockParticles;
BlockParticles.prototype["__destroy"] = BlockParticles.prototype.__destroy = function() {
    _mud_BlockParticles__destroy(this.__ptr);
};
// BlockPbr
function BlockPbr() { throw "cannot construct a BlockPbr, no constructor in IDL" }
BlockPbr.prototype = Object.create(GfxBlock.prototype);
BlockPbr.prototype.constructor = BlockPbr;
BlockPbr.prototype.__class = BlockPbr;
BlockPbr.__cache = {};
Module['BlockPbr'] = BlockPbr;
BlockPbr.prototype["__destroy"] = BlockPbr.prototype.__destroy = function() {
    _mud_BlockPbr__destroy(this.__ptr);
};
// BlockSky
function BlockSky() { throw "cannot construct a BlockSky, no constructor in IDL" }
BlockSky.prototype = Object.create(GfxBlock.prototype);
BlockSky.prototype.constructor = BlockSky;
BlockSky.prototype.__class = BlockSky;
BlockSky.__cache = {};
Module['BlockSky'] = BlockSky;
BlockSky.prototype["__destroy"] = BlockSky.prototype.__destroy = function() {
    _mud_BlockSky__destroy(this.__ptr);
};
// ClusteredFrustum
function ClusteredFrustum() {
    this.__ptr = _mud_ClusteredFrustum__construct_0(); this.__type = ClusteredFrustum.__type; getCache(ClusteredFrustum)[this.__ptr] = this;
};
ClusteredFrustum.prototype = Object.create(Frustum.prototype);
ClusteredFrustum.prototype.constructor = ClusteredFrustum;
ClusteredFrustum.prototype.__class = ClusteredFrustum;
ClusteredFrustum.__cache = {};
Module['ClusteredFrustum'] = ClusteredFrustum;
ClusteredFrustum.prototype["__destroy"] = ClusteredFrustum.prototype.__destroy = function() {
    _mud_ClusteredFrustum__destroy(this.__ptr);
};
// DrawBlock
function DrawBlock() { throw "cannot construct a DrawBlock, no constructor in IDL" }
DrawBlock.prototype = Object.create(GfxBlock.prototype);
DrawBlock.prototype.constructor = DrawBlock;
DrawBlock.prototype.__class = DrawBlock;
DrawBlock.__cache = {};
Module['DrawBlock'] = DrawBlock;
DrawBlock.prototype["__destroy"] = DrawBlock.prototype.__destroy = function() {
    _mud_DrawBlock__destroy(this.__ptr);
};
// Flare
function Flare() {
    this.__ptr = _mud_Flare__construct_0(); this.__type = Flare.__type; getCache(Flare)[this.__ptr] = this;
};
Flare.prototype = Object.create(Flow.prototype);
Flare.prototype.constructor = Flare;
Flare.prototype.__class = Flare;
Flare.__cache = {};
Module['Flare'] = Flare;
Object.defineProperty(Flare.prototype, "node", {
    get: function() {
        return wrapPointer(_mud_Flare__get_node(this.__ptr), Node3);
    },
    set: function(value) {
        _mud_Flare__set_node(this.__ptr, value.__ptr);
    }
});
Flare.prototype["__destroy"] = Flare.prototype.__destroy = function() {
    _mud_Flare__destroy(this.__ptr);
};
// GfxSystem
function GfxSystem(a0) {
    ensureCache.prepare();
    this.__ptr = _mud_GfxSystem__construct_1(ensureString(/*resource_path*/a0)); this.__type = GfxSystem.__type; getCache(GfxSystem)[this.__ptr] = this;
};
GfxSystem.prototype = Object.create(BgfxSystem.prototype);
GfxSystem.prototype.constructor = GfxSystem;
GfxSystem.prototype.__class = GfxSystem;
GfxSystem.__cache = {};
Module['GfxSystem'] = GfxSystem;
GfxSystem.prototype["main_target"] = GfxSystem.prototype.main_target = function() {
    return wrapPointer(_mud_GfxSystem_main_target_0(this.__ptr), RenderTarget);
};
GfxSystem.prototype["default_pipeline"] = GfxSystem.prototype.default_pipeline = function() {
    _mud_GfxSystem_default_pipeline_0(this.__ptr);
};
GfxSystem.prototype["add_resource_path"] = GfxSystem.prototype.add_resource_path = function(a0, a1) {
    ensureCache.prepare();
    if (a1 === undefined) { _mud_GfxSystem_add_resource_path_1(this.__ptr, ensureString(/*path*/a0)); return; }
    _mud_GfxSystem_add_resource_path_2(this.__ptr, ensureString(/*path*/a0), /*relative*/a1);
};
GfxSystem.prototype["debug_material"] = GfxSystem.prototype.debug_material = function() {
    return wrapPointer(_mud_GfxSystem_debug_material_0(this.__ptr), Material);
};
GfxSystem.prototype["create_model"] = GfxSystem.prototype.create_model = function(a0) {
    ensureCache.prepare();
    return wrapPointer(_mud_GfxSystem_create_model_1(this.__ptr, ensureString(/*name*/a0)), Model);
};
GfxSystem.prototype["create_model_geo"] = GfxSystem.prototype.create_model_geo = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_GfxSystem_create_model_geo_2(this.__ptr, ensureString(/*name*/a0), /*geometry*/a1.__ptr), Model); }
    if (a3 === undefined) { return wrapPointer(_mud_GfxSystem_create_model_geo_3(this.__ptr, ensureString(/*name*/a0), /*geometry*/a1.__ptr, /*readback*/a2), Model); }
    return wrapPointer(_mud_GfxSystem_create_model_geo_4(this.__ptr, ensureString(/*name*/a0), /*geometry*/a1.__ptr, /*readback*/a2, /*optimize*/a3), Model);
};
GfxSystem.prototype["create_model_gpu"] = GfxSystem.prototype.create_model_gpu = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_GfxSystem_create_model_gpu_2(this.__ptr, ensureString(/*name*/a0), /*gpu_mesh*/a1.__ptr), Model); }
    if (a3 === undefined) { return wrapPointer(_mud_GfxSystem_create_model_gpu_3(this.__ptr, ensureString(/*name*/a0), /*gpu_mesh*/a1.__ptr, /*readback*/a2), Model); }
    return wrapPointer(_mud_GfxSystem_create_model_gpu_4(this.__ptr, ensureString(/*name*/a0), /*gpu_mesh*/a1.__ptr, /*readback*/a2, /*optimize*/a3), Model);
};
GfxSystem.prototype["fetch_material"] = GfxSystem.prototype.fetch_material = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_GfxSystem_fetch_material_2(this.__ptr, ensureString(/*name*/a0), ensureString(/*shader*/a1)), Material); }
    return wrapPointer(_mud_GfxSystem_fetch_material_3(this.__ptr, ensureString(/*name*/a0), ensureString(/*shader*/a1), /*builtin*/a2), Material);
};
GfxSystem.prototype["fetch_image256_material"] = GfxSystem.prototype.fetch_image256_material = function(a0) {
    return wrapPointer(_mud_GfxSystem_fetch_image256_material_1(this.__ptr, /*image*/a0.__ptr), Material);
};
GfxSystem.prototype["shape"] = GfxSystem.prototype.shape = function(a0, a1, a2) {
    if (a1 === undefined) { return wrapPointer(_mud_GfxSystem_shape_1(this.__ptr, /*shape*/a0.__ptr), Model); }
    if (a2 === undefined) { return wrapPointer(_mud_GfxSystem_shape_2(this.__ptr, /*shape*/a0.__ptr, /*symbol*/a1.__ptr), Model); }
    return wrapPointer(_mud_GfxSystem_shape_3(this.__ptr, /*shape*/a0.__ptr, /*symbol*/a1.__ptr, /*draw_mode*/a2), Model);
};
GfxSystem.prototype["symbol_material"] = GfxSystem.prototype.symbol_material = function(a0, a1) {
    if (a1 === undefined) { return wrapPointer(_mud_GfxSystem_symbol_material_1(this.__ptr, /*symbol*/a0.__ptr), Material); }
    return wrapPointer(_mud_GfxSystem_symbol_material_2(this.__ptr, /*symbol*/a0.__ptr, /*draw_mode*/a1), Material);
};
Object.defineProperty(GfxSystem.prototype, "renderer", {
    get: function() {
        return wrapPointer(_mud_GfxSystem__get_renderer(this.__ptr), Renderer);
    }});
Object.defineProperty(GfxSystem.prototype, "copy", {
    get: function() {
        return wrapPointer(_mud_GfxSystem__get_copy(this.__ptr), BlockCopy);
    },
    set: function(value) {
        _mud_GfxSystem__set_copy(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(GfxSystem.prototype, "filter", {
    get: function() {
        return wrapPointer(_mud_GfxSystem__get_filter(this.__ptr), BlockFilter);
    },
    set: function(value) {
        _mud_GfxSystem__set_filter(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(GfxSystem.prototype, "render_frame", {
    get: function() {
        return wrapPointer(_mud_GfxSystem__get_render_frame(this.__ptr), RenderFrame);
    },
    set: function(value) {
        _mud_GfxSystem__set_render_frame(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(GfxSystem.prototype, "textures", {
    get: function() {
        return wrapPointer(_mud_GfxSystem__get_textures(this.__ptr), AssetStore_mud_Texture);
    }});
Object.defineProperty(GfxSystem.prototype, "programs", {
    get: function() {
        return wrapPointer(_mud_GfxSystem__get_programs(this.__ptr), AssetStore_mud_Program);
    }});
Object.defineProperty(GfxSystem.prototype, "materials", {
    get: function() {
        return wrapPointer(_mud_GfxSystem__get_materials(this.__ptr), AssetStore_mud_Material);
    }});
Object.defineProperty(GfxSystem.prototype, "models", {
    get: function() {
        return wrapPointer(_mud_GfxSystem__get_models(this.__ptr), AssetStore_mud_Model);
    }});
Object.defineProperty(GfxSystem.prototype, "flows", {
    get: function() {
        return wrapPointer(_mud_GfxSystem__get_flows(this.__ptr), AssetStore_mud_Flow);
    }});
Object.defineProperty(GfxSystem.prototype, "prefabs", {
    get: function() {
        return wrapPointer(_mud_GfxSystem__get_prefabs(this.__ptr), AssetStore_mud_Prefab);
    }});
GfxSystem.prototype["__destroy"] = GfxSystem.prototype.__destroy = function() {
    _mud_GfxSystem__destroy(this.__ptr);
};
// RenderTarget
function RenderTarget() { throw "cannot construct a RenderTarget, no constructor in IDL" }
RenderTarget.prototype = Object.create(FrameBuffer.prototype);
RenderTarget.prototype.constructor = RenderTarget;
RenderTarget.prototype.__class = RenderTarget;
RenderTarget.__cache = {};
Module['RenderTarget'] = RenderTarget;
Object.defineProperty(RenderTarget.prototype, "backbuffer", {
    get: function() {
        return wrapPointer(_mud_RenderTarget__get_backbuffer(this.__ptr), FrameBuffer);
    }});
Object.defineProperty(RenderTarget.prototype, "msaa", {
    get: function() {
        return _mud_RenderTarget__get_msaa(this.__ptr);
    },
    set: function(value) {
        _mud_RenderTarget__set_msaa(this.__ptr, value);
    }
});
Object.defineProperty(RenderTarget.prototype, "mrt", {
    get: function() {
        return !!(_mud_RenderTarget__get_mrt(this.__ptr));
    },
    set: function(value) {
        _mud_RenderTarget__set_mrt(this.__ptr, value);
    }
});
Object.defineProperty(RenderTarget.prototype, "depth", {
    get: function() {
        return wrapPointer(_mud_RenderTarget__get_depth(this.__ptr), Texture);
    }});
Object.defineProperty(RenderTarget.prototype, "diffuse", {
    get: function() {
        return wrapPointer(_mud_RenderTarget__get_diffuse(this.__ptr), Texture);
    }});
Object.defineProperty(RenderTarget.prototype, "specular", {
    get: function() {
        return wrapPointer(_mud_RenderTarget__get_specular(this.__ptr), Texture);
    }});
Object.defineProperty(RenderTarget.prototype, "normal_rough", {
    get: function() {
        return wrapPointer(_mud_RenderTarget__get_normal_rough(this.__ptr), Texture);
    }});
Object.defineProperty(RenderTarget.prototype, "sss", {
    get: function() {
        return wrapPointer(_mud_RenderTarget__get_sss(this.__ptr), Texture);
    }});
Object.defineProperty(RenderTarget.prototype, "ping_pong", {
    get: function() {
        return wrapPointer(_mud_RenderTarget__get_ping_pong(this.__ptr), SwapBuffer);
    }});
Object.defineProperty(RenderTarget.prototype, "post_process", {
    get: function() {
        return wrapPointer(_mud_RenderTarget__get_post_process(this.__ptr), SwapBuffer);
    }});
Object.defineProperty(RenderTarget.prototype, "cascade", {
    get: function() {
        return wrapPointer(_mud_RenderTarget__get_cascade(this.__ptr), Cascade);
    }});
Object.defineProperty(RenderTarget.prototype, "swap_cascade", {
    get: function() {
        return wrapPointer(_mud_RenderTarget__get_swap_cascade(this.__ptr), SwapCascade);
    }});
Object.defineProperty(RenderTarget.prototype, "deferred", {
    get: function() {
        return !!(_mud_RenderTarget__get_deferred(this.__ptr));
    },
    set: function(value) {
        _mud_RenderTarget__set_deferred(this.__ptr, value);
    }
});
RenderTarget.prototype["__destroy"] = RenderTarget.prototype.__destroy = function() {
    _mud_RenderTarget__destroy(this.__ptr);
};
// Viewport
function Viewport() { throw "cannot construct a Viewport, no constructor in IDL" }
Viewport.prototype = Object.create(OEntt.prototype);
Viewport.prototype.constructor = Viewport;
Viewport.prototype.__class = Viewport;
Viewport.__cache = {};
Module['Viewport'] = Viewport;
Viewport.prototype["cull"] = Viewport.prototype.cull = function(a0) {
    _mud_Viewport_cull_1(this.__ptr, /*render*/a0.__ptr);
};
Viewport.prototype["render"] = Viewport.prototype.render = function(a0) {
    _mud_Viewport_render_1(this.__ptr, /*render*/a0.__ptr);
};
Viewport.prototype["set_clustered"] = Viewport.prototype.set_clustered = function(a0) {
    _mud_Viewport_set_clustered_1(this.__ptr, /*gfx*/a0.__ptr);
};
Object.defineProperty(Viewport.prototype, "camera", {
    get: function() {
        return wrapPointer(_mud_Viewport__get_camera(this.__ptr), Camera);
    },
    set: function(value) {
        _mud_Viewport__set_camera(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Viewport.prototype, "scene", {
    get: function() {
        return wrapPointer(_mud_Viewport__get_scene(this.__ptr), Scene);
    },
    set: function(value) {
        _mud_Viewport__set_scene(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Viewport.prototype, "index", {
    get: function() {
        return _mud_Viewport__get_index(this.__ptr);
    },
    set: function(value) {
        _mud_Viewport__set_index(this.__ptr, value);
    }
});
Object.defineProperty(Viewport.prototype, "active", {
    get: function() {
        return !!(_mud_Viewport__get_active(this.__ptr));
    },
    set: function(value) {
        _mud_Viewport__set_active(this.__ptr, value);
    }
});
Object.defineProperty(Viewport.prototype, "rect", {
    get: function() {
        return wrapPointer(_mud_Viewport__get_rect(this.__ptr), v4_uint);
    },
    set: function(value) {
        _mud_Viewport__set_rect(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Viewport.prototype, "scissor", {
    get: function() {
        return !!(_mud_Viewport__get_scissor(this.__ptr));
    },
    set: function(value) {
        _mud_Viewport__set_scissor(this.__ptr, value);
    }
});
Object.defineProperty(Viewport.prototype, "clear_colour", {
    get: function() {
        return wrapPointer(_mud_Viewport__get_clear_colour(this.__ptr), Colour);
    },
    set: function(value) {
        _mud_Viewport__set_clear_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Viewport.prototype, "shading", {
    get: function() {
        return _mud_Viewport__get_shading(this.__ptr);
    },
    set: function(value) {
        _mud_Viewport__set_shading(this.__ptr, value);
    }
});
Object.defineProperty(Viewport.prototype, "lighting", {
    get: function() {
        return _mud_Viewport__get_lighting(this.__ptr);
    },
    set: function(value) {
        _mud_Viewport__set_lighting(this.__ptr, value);
    }
});
Object.defineProperty(Viewport.prototype, "clustered", {
    get: function() {
        return !!(_mud_Viewport__get_clustered(this.__ptr));
    },
    set: function(value) {
        _mud_Viewport__set_clustered(this.__ptr, value);
    }
});
Viewport.prototype["__destroy"] = Viewport.prototype.__destroy = function() {
    _mud_Viewport__destroy(this.__ptr);
};
Module['bxidentity'] = function() {
    return wrapPointer(_mud_bxidentity_0(), mat4);
};
Module['bxinverse'] = function(a0) {
    return wrapPointer(_mud_bxinverse_1(/*mat*/a0.__ptr), mat4);
};
Module['bxSRT'] = function(a0, a1, a2) {
    return wrapPointer(_mud_bxSRT_3(/*scale*/a0.__ptr, /*rot*/a1.__ptr, /*trans*/a2.__ptr), mat4);
};
Module['bxscale'] = function(a0) {
    return wrapPointer(_mud_bxscale_1(/*scale*/a0.__ptr), mat4);
};
Module['bxrotation'] = function(a0) {
    return wrapPointer(_mud_bxrotation_1(/*rot*/a0.__ptr), mat4);
};
Module['bxtranslation'] = function(a0) {
    return wrapPointer(_mud_bxtranslation_1(/*vec*/a0.__ptr), mat4);
};
Module['bxmul'] = function(a0, a1) {
    return wrapPointer(_mud_bxmul_2(/*lhs*/a0.__ptr, /*rhs*/a1.__ptr), mat4);
};
Module['bxmulh'] = function(a0, a1) {
    return wrapPointer(_mud_bxmulh_2(/*mat*/a0.__ptr, /*vec*/a1.__ptr), v3_float);
};
Module['bxlookat'] = function(a0, a1, a2, a3) {
    if (a2 === undefined) { return wrapPointer(_mud_bxlookat_2(/*eye*/a0.__ptr, /*at*/a1.__ptr), mat4); }
    if (a3 === undefined) { return wrapPointer(_mud_bxlookat_3(/*eye*/a0.__ptr, /*at*/a1.__ptr, /*up*/a2.__ptr), mat4); }
    _mud_bxlookat_4(/*result*/a0.__ptr, /*eye*/a1.__ptr, /*at*/a2.__ptr, /*up*/a3.__ptr);
};
Module['bxproj'] = function(a0, a1, a2, a3, a4) {
    return wrapPointer(_mud_bxproj_5(/*fov*/a0, /*aspect*/a1, /*near*/a2, /*far*/a3, /*oglNdc*/a4), mat4);
};
Module['bxortho'] = function(a0, a1, a2, a3, a4, a5, a6, a7) {
    if (a5 === undefined) { return wrapPointer(_mud_bxortho_5(/*rect*/a0.__ptr, /*near*/a1, /*far*/a2, /*offset*/a3, /*oglNdc*/a4), mat4); }
    return wrapPointer(_mud_bxortho_8(/*left*/a0, /*right*/a1, /*bottom*/a2, /*top*/a3, /*near*/a4, /*far*/a5, /*offset*/a6, /*oglNdc*/a7), mat4);
};
Module['bxTRS'] = function(a0, a1, a2) {
    return wrapPointer(_mud_bxTRS_3(/*scale*/a0.__ptr, /*rot*/a1.__ptr, /*trans*/a2.__ptr), mat4);
};
Module['load_texture_rgba'] = function(a0, a1, a2) {
    _mud_load_texture_rgba_3(/*texture*/a0.__ptr, /*size*/a1.__ptr, ensureInt32(/*data*/a2), /*data*/a2.length);
};
Module['gfx']['setup_pipeline_minimal'] = function(a0) {
    _mud_gfx_setup_pipeline_minimal_1(/*gfx*/a0.__ptr);
};
Module['gfx']['node'] = function(a0, a1, a2, a3, a4) {
    if (a1 === undefined) { return wrapPointer(_mud_gfx_node_1(/*parent*/a0.__ptr), Gnode); }
    if (a2 === undefined) { return wrapPointer(_mud_gfx_node_2(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)), Gnode); }
    if (a3 === undefined) { return wrapPointer(_mud_gfx_node_3(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1), /*position*/a2.__ptr), Gnode); }
    if (a4 === undefined) { return wrapPointer(_mud_gfx_node_4(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1), /*position*/a2.__ptr, /*rotation*/a3.__ptr), Gnode); }
    return wrapPointer(_mud_gfx_node_5(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1), /*position*/a2.__ptr, /*rotation*/a3.__ptr, /*scale*/a4.__ptr), Gnode);
};
Module['gfx']['shape'] = function(a0, a1, a2, a3, a4) {
    if (a3 === undefined) { return wrapPointer(_mud_gfx_shape_3(/*parent*/a0.__ptr, /*shape*/a1.__ptr, /*symbol*/a2.__ptr), Item); }
    if (a4 === undefined) { return wrapPointer(_mud_gfx_shape_4(/*parent*/a0.__ptr, /*shape*/a1.__ptr, /*symbol*/a2.__ptr, /*flags*/a3), Item); }
    return wrapPointer(_mud_gfx_shape_5(/*parent*/a0.__ptr, /*shape*/a1.__ptr, /*symbol*/a2.__ptr, /*flags*/a3, /*material*/a4.__ptr), Item);
};
Module['gfx']['draw'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { _mud_gfx_draw_3(/*parent*/a0.__ptr, /*shape*/a1.__ptr, /*symbol*/a2.__ptr); return; }
    _mud_gfx_draw_4(/*parent*/a0.__ptr, /*shape*/a1.__ptr, /*symbol*/a2.__ptr, /*flags*/a3);
};
Module['gfx']['sprite'] = function(a0, a1, a2, a3, a4) {
    if (a3 === undefined) { return wrapPointer(_mud_gfx_sprite_3(/*parent*/a0.__ptr, /*image*/a1.__ptr, /*size*/a2.__ptr), Item); }
    if (a4 === undefined) { return wrapPointer(_mud_gfx_sprite_4(/*parent*/a0.__ptr, /*image*/a1.__ptr, /*size*/a2.__ptr, /*flags*/a3), Item); }
    return wrapPointer(_mud_gfx_sprite_5(/*parent*/a0.__ptr, /*image*/a1.__ptr, /*size*/a2.__ptr, /*flags*/a3, /*material*/a4.__ptr), Item);
};
Module['gfx']['item'] = function(a0, a1, a2, a3) {
    if (a2 === undefined) { return wrapPointer(_mud_gfx_item_2(/*parent*/a0.__ptr, /*model*/a1.__ptr), Item); }
    if (a3 === undefined) { return wrapPointer(_mud_gfx_item_3(/*parent*/a0.__ptr, /*model*/a1.__ptr, /*flags*/a2), Item); }
    return wrapPointer(_mud_gfx_item_4(/*parent*/a0.__ptr, /*model*/a1.__ptr, /*flags*/a2, /*material*/a3.__ptr), Item);
};
Module['gfx']['batch'] = function(a0, a1, a2) {
    return wrapPointer(_mud_gfx_batch_3(/*parent*/a0.__ptr, /*item*/a1.__ptr, /*stride*/a2), Batch);
};
Module['gfx']['instances'] = function(a0, a1, a2) {
    if (a2 === undefined) { return wrapPointer(_mud_gfx_instances_2(/*parent*/a0.__ptr, /*item*/a1.__ptr), Batch); }
    return wrapPointer(_mud_gfx_instances_3(/*parent*/a0.__ptr, /*item*/a1.__ptr, ensureFloat32(/*transforms*/a2), /*transforms*/a2.length), Batch);
};
Module['gfx']['prefab'] = function(a0, a1, a2, a3, a4) {
    if (a2 === undefined) { _mud_gfx_prefab_2(/*parent*/a0.__ptr, /*prefab*/a1.__ptr); return; }
    if (a3 === undefined) { _mud_gfx_prefab_3(/*parent*/a0.__ptr, /*prefab*/a1.__ptr, /*transform*/a2); return; }
    if (a4 === undefined) { _mud_gfx_prefab_4(/*parent*/a0.__ptr, /*prefab*/a1.__ptr, /*transform*/a2, /*flags*/a3); return; }
    _mud_gfx_prefab_5(/*parent*/a0.__ptr, /*prefab*/a1.__ptr, /*transform*/a2, /*flags*/a3, /*material*/a4.__ptr);
};
Module['gfx']['model'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_gfx_model_2(/*parent*/a0.__ptr, ensureString(/*name*/a1)), Item); }
    if (a3 === undefined) { return wrapPointer(_mud_gfx_model_3(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*flags*/a2), Item); }
    return wrapPointer(_mud_gfx_model_4(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*flags*/a2, /*material*/a3.__ptr), Item);
};
Module['gfx']['animated'] = function(a0, a1) {
    return wrapPointer(_mud_gfx_animated_2(/*parent*/a0.__ptr, /*item*/a1.__ptr), Mime);
};
Module['gfx']['flows'] = function(a0, a1, a2) {
    if (a2 === undefined) { return wrapPointer(_mud_gfx_flows_2(/*parent*/a0.__ptr, /*emitter*/a1.__ptr), Flare); }
    return wrapPointer(_mud_gfx_flows_3(/*parent*/a0.__ptr, /*emitter*/a1.__ptr, /*flags*/a2), Flare);
};
Module['gfx']['light'] = function(a0, a1, a2, a3, a4, a5) {
    if (a4 === undefined) { return wrapPointer(_mud_gfx_light_4(/*parent*/a0.__ptr, /*type*/a1, /*shadows*/a2, /*colour*/a3.__ptr), Light); }
    if (a5 === undefined) { return wrapPointer(_mud_gfx_light_5(/*parent*/a0.__ptr, /*type*/a1, /*shadows*/a2, /*colour*/a3.__ptr, /*range*/a4), Light); }
    return wrapPointer(_mud_gfx_light_6(/*parent*/a0.__ptr, /*type*/a1, /*shadows*/a2, /*colour*/a3.__ptr, /*range*/a4, /*attenuation*/a5), Light);
};
Module['gfx']['sun_light'] = function(a0, a1, a2) {
    return wrapPointer(_mud_gfx_sun_light_3(/*parent*/a0.__ptr, /*azimuth*/a1, /*elevation*/a2), Light);
};
Module['gfx']['radiance'] = function(a0, a1, a2) {
    ensureCache.prepare();
    _mud_gfx_radiance_3(/*parent*/a0.__ptr, ensureString(/*texture*/a1), /*background*/a2);
};
Module['gfx']['direct_light_node'] = function(a0, a1) {
    return wrapPointer(_mud_gfx_direct_light_node_2(/*parent*/a0.__ptr, /*direction*/a1.__ptr), Light);
};
Module['gfx']['solid_material'] = function(a0, a1, a2) {
    ensureCache.prepare();
    return wrapPointer(_mud_gfx_solid_material_3(/*gfx*/a0.__ptr, ensureString(/*name*/a1), /*colour*/a2.__ptr), Material);
};
Module['gfx']['pbr_material'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a3 === undefined) { return wrapPointer(_mud_gfx_pbr_material_3(/*gfx*/a0.__ptr, ensureString(/*name*/a1), /*albedo*/a2.__ptr), Material); }
    if (a4 === undefined) { return wrapPointer(_mud_gfx_pbr_material_4(/*gfx*/a0.__ptr, ensureString(/*name*/a1), /*albedo*/a2.__ptr, /*metallic*/a3), Material); }
    return wrapPointer(_mud_gfx_pbr_material_5(/*gfx*/a0.__ptr, ensureString(/*name*/a1), /*albedo*/a2.__ptr, /*metallic*/a3, /*roughness*/a4), Material);
};
Module['gfx']['model_suzanne'] = function(a0) {
    return wrapPointer(_mud_gfx_model_suzanne_1(/*gfx*/a0.__ptr), Model);
};
Module['pass_clear_fbo'] = function(a0, a1, a2, a3) {
    _mud_pass_clear_fbo_4(/*gfx*/a0.__ptr, /*render*/a1.__ptr, /*fbo*/a2.__ptr, /*colour*/a3.__ptr);
};
Module['pass_clear'] = function(a0, a1) {
    _mud_pass_clear_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_gclear'] = function(a0, a1) {
    _mud_pass_gclear_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_depth'] = function(a0, a1) {
    _mud_pass_depth_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_background'] = function(a0, a1) {
    _mud_pass_background_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_solid'] = function(a0, a1) {
    _mud_pass_solid_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['pass_flip'] = function(a0, a1) {
    _mud_pass_flip_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['render_minimal'] = function(a0, a1) {
    _mud_render_minimal_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['render_solid'] = function(a0, a1) {
    _mud_render_solid_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};
Module['render_clear'] = function(a0, a1) {
    _mud_render_clear_2(/*gfx*/a0.__ptr, /*render*/a1.__ptr);
};

(function() {
    function setup() {
        AnimatedTrack.__type = _mud_AnimatedTrack__type();
        Animation.__type = _mud_Animation__type();
        AnimationPlay.__type = _mud_AnimationPlay__type();
        AnimationTrack.__type = _mud_AnimationTrack__type();
        Background.__type = _mud_Background__type();
        Batch.__type = _mud_Batch__type();
        Bone.__type = _mud_Bone__type();
        Camera.__type = _mud_Camera__type();
        Cascade.__type = _mud_Cascade__type();
        Culler.__type = _mud_Culler__type();
        DepthParams.__type = _mud_DepthParams__type();
        Direct.__type = _mud_Direct__type();
        DistanceParams.__type = _mud_DistanceParams__type();
        Flow.__type = _mud_Flow__type();
        Fog.__type = _mud_Fog__type();
        FrameBuffer.__type = _mud_FrameBuffer__type();
        Frustum.__type = _mud_Frustum__type();
        FrustumSlice.__type = _mud_FrustumSlice__type();
        GfxBlock.__type = _mud_GfxBlock__type();
        GfxWindow.__type = _mud_GfxWindow__type();
        Gnode.__type = _mud_Gnode__type();
        GpuMesh.__type = _mud_GpuMesh__type();
        ImmediateDraw.__type = _mud_ImmediateDraw__type();
        Import.__type = _mud_Import__type();
        ImportConfig.__type = _mud_ImportConfig__type();
        Item.__type = _mud_Item__type();
        Joint.__type = _mud_Joint__type();
        Light.__type = _mud_Light__type();
        Lines.__type = _mud_Lines__type();
        Material.__type = _mud_Material__type();
        MaterialAlpha.__type = _mud_MaterialAlpha__type();
        MaterialBase.__type = _mud_MaterialBase__type();
        MaterialFresnel.__type = _mud_MaterialFresnel__type();
        MaterialLine.__type = _mud_MaterialLine__type();
        MaterialPbr.__type = _mud_MaterialPbr__type();
        MaterialPoint.__type = _mud_MaterialPoint__type();
        MaterialSolid.__type = _mud_MaterialSolid__type();
        MaterialUser.__type = _mud_MaterialUser__type();
        Mesh.__type = _mud_Mesh__type();
        Mime.__type = _mud_Mime__type();
        Model.__type = _mud_Model__type();
        ModelItem.__type = _mud_ModelItem__type();
        Node3.__type = _mud_Node3__type();
        Pass.__type = _mud_Pass__type();
        Prefab.__type = _mud_Prefab__type();
        Program.__type = _mud_Program__type();
        Radiance.__type = _mud_Radiance__type();
        Render.__type = _mud_Render__type();
        RenderFrame.__type = _mud_RenderFrame__type();
        RenderQuad.__type = _mud_RenderQuad__type();
        Renderer.__type = _mud_Renderer__type();
        Rig.__type = _mud_Rig__type();
        Scene.__type = _mud_Scene__type();
        Shot.__type = _mud_Shot__type();
        Skeleton.__type = _mud_Skeleton__type();
        Skin.__type = _mud_Skin__type();
        Sun.__type = _mud_Sun__type();
        SwapBuffer.__type = _mud_SwapBuffer__type();
        SwapCascade.__type = _mud_SwapCascade__type();
        SymbolIndex.__type = _mud_SymbolIndex__type();
        Texture.__type = _mud_Texture__type();
        Zone.__type = _mud_Zone__type();
        BlockCopy.__type = _mud_BlockCopy__type();
        BlockDepth.__type = _mud_BlockDepth__type();
        BlockFilter.__type = _mud_BlockFilter__type();
        BlockMaterial.__type = _mud_BlockMaterial__type();
        BlockParticles.__type = _mud_BlockParticles__type();
        BlockPbr.__type = _mud_BlockPbr__type();
        BlockSky.__type = _mud_BlockSky__type();
        ClusteredFrustum.__type = _mud_ClusteredFrustum__type();
        DrawBlock.__type = _mud_DrawBlock__type();
        Flare.__type = _mud_Flare__type();
        GfxSystem.__type = _mud_GfxSystem__type();
        RenderTarget.__type = _mud_RenderTarget__type();
        Viewport.__type = _mud_Viewport__type();
        // AnimationTarget
        Module['AnimationTarget'] = Module['AnimationTarget'] || {};
        Module['AnimationTarget']['Position'] = _mud_AnimationTarget_Position();
        Module['AnimationTarget']['Rotation'] = _mud_AnimationTarget_Rotation();
        Module['AnimationTarget']['Scale'] = _mud_AnimationTarget_Scale();
        Module['AnimationTarget']['Count'] = _mud_AnimationTarget_Count();
        // BackgroundMode
        Module['BackgroundMode'] = Module['BackgroundMode'] || {};
        Module['BackgroundMode']['None'] = _mud_BackgroundMode_None();
        Module['BackgroundMode']['Panorama'] = _mud_BackgroundMode_Panorama();
        Module['BackgroundMode']['Radiance'] = _mud_BackgroundMode_Radiance();
        Module['BackgroundMode']['Custom'] = _mud_BackgroundMode_Custom();
        // BlendMode
        Module['BlendMode'] = Module['BlendMode'] || {};
        Module['BlendMode']['None'] = _mud_BlendMode_None();
        Module['BlendMode']['Mix'] = _mud_BlendMode_Mix();
        Module['BlendMode']['Add'] = _mud_BlendMode_Add();
        Module['BlendMode']['Sub'] = _mud_BlendMode_Sub();
        Module['BlendMode']['Mul'] = _mud_BlendMode_Mul();
        Module['BlendMode']['Normal'] = _mud_BlendMode_Normal();
        Module['BlendMode']['Alpha'] = _mud_BlendMode_Alpha();
        // CullMode
        Module['CullMode'] = Module['CullMode'] || {};
        Module['CullMode']['None'] = _mud_CullMode_None();
        Module['CullMode']['Front'] = _mud_CullMode_Front();
        Module['CullMode']['Back'] = _mud_CullMode_Back();
        Module['CullMode']['Count'] = _mud_CullMode_Count();
        // DepthDraw
        Module['DepthDraw'] = Module['DepthDraw'] || {};
        Module['DepthDraw']['Enabled'] = _mud_DepthDraw_Enabled();
        Module['DepthDraw']['Disabled'] = _mud_DepthDraw_Disabled();
        // DepthMethod
        Module['DepthMethod'] = Module['DepthMethod'] || {};
        Module['DepthMethod']['Depth'] = _mud_DepthMethod_Depth();
        Module['DepthMethod']['DepthPacked'] = _mud_DepthMethod_DepthPacked();
        Module['DepthMethod']['Distance'] = _mud_DepthMethod_Distance();
        Module['DepthMethod']['Count'] = _mud_DepthMethod_Count();
        // DepthTest
        Module['DepthTest'] = Module['DepthTest'] || {};
        Module['DepthTest']['Enabled'] = _mud_DepthTest_Enabled();
        Module['DepthTest']['Disabled'] = _mud_DepthTest_Disabled();
        // EmitterFlow
        Module['EmitterFlow'] = Module['EmitterFlow'] || {};
        Module['EmitterFlow']['Outward'] = _mud_EmitterFlow_Outward();
        Module['EmitterFlow']['Absolute'] = _mud_EmitterFlow_Absolute();
        // Interpolation
        Module['Interpolation'] = Module['Interpolation'] || {};
        Module['Interpolation']['Nearest'] = _mud_Interpolation_Nearest();
        Module['Interpolation']['Linear'] = _mud_Interpolation_Linear();
        Module['Interpolation']['Cubic'] = _mud_Interpolation_Cubic();
        // IsometricAngle
        Module['NORTH'] = _mud_IsometricAngle_NORTH();
        Module['SOUTH'] = _mud_IsometricAngle_SOUTH();
        Module['EAST'] = _mud_IsometricAngle_EAST();
        Module['WEST'] = _mud_IsometricAngle_WEST();
        // ItemShadow
        Module['ItemShadow'] = Module['ItemShadow'] || {};
        Module['ItemShadow']['Default'] = _mud_ItemShadow_Default();
        Module['ItemShadow']['DoubleSided'] = _mud_ItemShadow_DoubleSided();
        // LightType
        Module['LightType'] = Module['LightType'] || {};
        Module['LightType']['Direct'] = _mud_LightType_Direct();
        Module['LightType']['Point'] = _mud_LightType_Point();
        Module['LightType']['Spot'] = _mud_LightType_Spot();
        Module['LightType']['Count'] = _mud_LightType_Count();
        // Lighting
        Module['Lighting'] = Module['Lighting'] || {};
        Module['Lighting']['None'] = _mud_Lighting_None();
        Module['Lighting']['Clustered'] = _mud_Lighting_Clustered();
        Module['Lighting']['Deferred'] = _mud_Lighting_Deferred();
        Module['Lighting']['VoxelGI'] = _mud_Lighting_VoxelGI();
        // MSAA
        Module['MSAA'] = Module['MSAA'] || {};
        Module['MSAA']['Disabled'] = _mud_MSAA_Disabled();
        Module['MSAA']['X2'] = _mud_MSAA_X2();
        Module['MSAA']['X4'] = _mud_MSAA_X4();
        Module['MSAA']['X8'] = _mud_MSAA_X8();
        Module['MSAA']['X16'] = _mud_MSAA_X16();
        Module['MSAA']['Count'] = _mud_MSAA_Count();
        // MaterialBlock
        Module['MaterialBlock'] = Module['MaterialBlock'] || {};
        Module['MaterialBlock']['Base'] = _mud_MaterialBlock_Base();
        Module['MaterialBlock']['Alpha'] = _mud_MaterialBlock_Alpha();
        Module['MaterialBlock']['Solid'] = _mud_MaterialBlock_Solid();
        Module['MaterialBlock']['Point'] = _mud_MaterialBlock_Point();
        Module['MaterialBlock']['Line'] = _mud_MaterialBlock_Line();
        Module['MaterialBlock']['Pbr'] = _mud_MaterialBlock_Pbr();
        Module['MaterialBlock']['Fresnel'] = _mud_MaterialBlock_Fresnel();
        Module['MaterialBlock']['User'] = _mud_MaterialBlock_User();
        Module['MaterialBlock']['Count'] = _mud_MaterialBlock_Count();
        // MaterialFlag
        Module['MaterialFlag'] = Module['MaterialFlag'] || {};
        Module['MaterialFlag']['TriplanarUV1'] = _mud_MaterialFlag_TriplanarUV1();
        Module['MaterialFlag']['TriplanarUV2'] = _mud_MaterialFlag_TriplanarUV2();
        Module['MaterialFlag']['Count'] = _mud_MaterialFlag_Count();
        // ModelFormat
        Module['ModelFormat'] = Module['ModelFormat'] || {};
        Module['ModelFormat']['obj'] = _mud_ModelFormat_obj();
        Module['ModelFormat']['ply'] = _mud_ModelFormat_ply();
        Module['ModelFormat']['gltf'] = _mud_ModelFormat_gltf();
        Module['ModelFormat']['Count'] = _mud_ModelFormat_Count();
        // Month
        Module['Month'] = Module['Month'] || {};
        Module['Month']['January'] = _mud_Month_January();
        Module['Month']['February'] = _mud_Month_February();
        Module['Month']['March'] = _mud_Month_March();
        Module['Month']['April'] = _mud_Month_April();
        Module['Month']['May'] = _mud_Month_May();
        Module['Month']['June'] = _mud_Month_June();
        Module['Month']['July'] = _mud_Month_July();
        Module['Month']['August'] = _mud_Month_August();
        Module['Month']['September'] = _mud_Month_September();
        Module['Month']['October'] = _mud_Month_October();
        Module['Month']['November'] = _mud_Month_November();
        Module['Month']['December'] = _mud_Month_December();
        // PassType
        Module['PassType'] = Module['PassType'] || {};
        Module['PassType']['VoxelGI'] = _mud_PassType_VoxelGI();
        Module['PassType']['Lightmap'] = _mud_PassType_Lightmap();
        Module['PassType']['Shadowmap'] = _mud_PassType_Shadowmap();
        Module['PassType']['Probes'] = _mud_PassType_Probes();
        Module['PassType']['Clear'] = _mud_PassType_Clear();
        Module['PassType']['Depth'] = _mud_PassType_Depth();
        Module['PassType']['Normals'] = _mud_PassType_Normals();
        Module['PassType']['Shadow'] = _mud_PassType_Shadow();
        Module['PassType']['Geometry'] = _mud_PassType_Geometry();
        Module['PassType']['Lights'] = _mud_PassType_Lights();
        Module['PassType']['Opaque'] = _mud_PassType_Opaque();
        Module['PassType']['Background'] = _mud_PassType_Background();
        Module['PassType']['Particles'] = _mud_PassType_Particles();
        Module['PassType']['Alpha'] = _mud_PassType_Alpha();
        Module['PassType']['Solid'] = _mud_PassType_Solid();
        Module['PassType']['Effects'] = _mud_PassType_Effects();
        Module['PassType']['PostProcess'] = _mud_PassType_PostProcess();
        Module['PassType']['Flip'] = _mud_PassType_Flip();
        Module['PassType']['Count'] = _mud_PassType_Count();
        // PbrDiffuseMode
        Module['PbrDiffuseMode'] = Module['PbrDiffuseMode'] || {};
        Module['PbrDiffuseMode']['Lambert'] = _mud_PbrDiffuseMode_Lambert();
        Module['PbrDiffuseMode']['LambertHalf'] = _mud_PbrDiffuseMode_LambertHalf();
        Module['PbrDiffuseMode']['OrenNayar'] = _mud_PbrDiffuseMode_OrenNayar();
        Module['PbrDiffuseMode']['Burley'] = _mud_PbrDiffuseMode_Burley();
        Module['PbrDiffuseMode']['Toon'] = _mud_PbrDiffuseMode_Toon();
        // PbrSpecularMode
        Module['PbrSpecularMode'] = Module['PbrSpecularMode'] || {};
        Module['PbrSpecularMode']['SchlickGGX'] = _mud_PbrSpecularMode_SchlickGGX();
        Module['PbrSpecularMode']['Blinn'] = _mud_PbrSpecularMode_Blinn();
        Module['PbrSpecularMode']['Phong'] = _mud_PbrSpecularMode_Phong();
        Module['PbrSpecularMode']['Toon'] = _mud_PbrSpecularMode_Toon();
        Module['PbrSpecularMode']['Disabled'] = _mud_PbrSpecularMode_Disabled();
        // ShaderColor
        Module['ShaderColor'] = Module['ShaderColor'] || {};
        Module['ShaderColor']['Shader'] = _mud_ShaderColor_Shader();
        Module['ShaderColor']['Vertex'] = _mud_ShaderColor_Vertex();
        Module['ShaderColor']['Face'] = _mud_ShaderColor_Face();
        // ShaderType
        Module['ShaderType'] = Module['ShaderType'] || {};
        Module['ShaderType']['Compute'] = _mud_ShaderType_Compute();
        Module['ShaderType']['Fragment'] = _mud_ShaderType_Fragment();
        Module['ShaderType']['Geometry'] = _mud_ShaderType_Geometry();
        Module['ShaderType']['Vertex'] = _mud_ShaderType_Vertex();
        Module['ShaderType']['Count'] = _mud_ShaderType_Count();
        // Shading
        Module['Shading'] = Module['Shading'] || {};
        Module['Shading']['Wireframe'] = _mud_Shading_Wireframe();
        Module['Shading']['Solid'] = _mud_Shading_Solid();
        Module['Shading']['Shaded'] = _mud_Shading_Shaded();
        Module['Shading']['Volume'] = _mud_Shading_Volume();
        Module['Shading']['Voxels'] = _mud_Shading_Voxels();
        Module['Shading']['Lightmap'] = _mud_Shading_Lightmap();
        Module['Shading']['Clear'] = _mud_Shading_Clear();
        Module['Shading']['Count'] = _mud_Shading_Count();
        // ShadowFlags
        Module['CSM_Stabilize'] = _mud_ShadowFlags_CSM_Stabilize();
        Module['CSM_Optimize'] = _mud_ShadowFlags_CSM_Optimize();
        Module['CSM_BlendSplits'] = _mud_ShadowFlags_CSM_BlendSplits();
        // TextureChannel
        Module['TextureChannel'] = Module['TextureChannel'] || {};
        Module['TextureChannel']['Red'] = _mud_TextureChannel_Red();
        Module['TextureChannel']['Green'] = _mud_TextureChannel_Green();
        Module['TextureChannel']['Blue'] = _mud_TextureChannel_Blue();
        Module['TextureChannel']['Alpha'] = _mud_TextureChannel_Alpha();
        Module['TextureChannel']['All'] = _mud_TextureChannel_All();
        // TextureHint
        Module['TextureHint'] = Module['TextureHint'] || {};
        Module['TextureHint']['Black'] = _mud_TextureHint_Black();
        Module['TextureHint']['White'] = _mud_TextureHint_White();
        Module['TextureHint']['Normal'] = _mud_TextureHint_Normal();
        // TextureSampler
        Module['TextureSampler'] = Module['TextureSampler'] || {};
        Module['TextureSampler']['Source0'] = _mud_TextureSampler_Source0();
        Module['TextureSampler']['Source1'] = _mud_TextureSampler_Source1();
        Module['TextureSampler']['Source2'] = _mud_TextureSampler_Source2();
        Module['TextureSampler']['Source3'] = _mud_TextureSampler_Source3();
        Module['TextureSampler']['SourceDepth'] = _mud_TextureSampler_SourceDepth();
        Module['TextureSampler']['Color'] = _mud_TextureSampler_Color();
        Module['TextureSampler']['Albedo'] = _mud_TextureSampler_Albedo();
        Module['TextureSampler']['Alpha'] = _mud_TextureSampler_Alpha();
        Module['TextureSampler']['Metallic'] = _mud_TextureSampler_Metallic();
        Module['TextureSampler']['User0'] = _mud_TextureSampler_User0();
        Module['TextureSampler']['Roughness'] = _mud_TextureSampler_Roughness();
        Module['TextureSampler']['User1'] = _mud_TextureSampler_User1();
        Module['TextureSampler']['Emissive'] = _mud_TextureSampler_Emissive();
        Module['TextureSampler']['User2'] = _mud_TextureSampler_User2();
        Module['TextureSampler']['Normal'] = _mud_TextureSampler_Normal();
        Module['TextureSampler']['User3'] = _mud_TextureSampler_User3();
        Module['TextureSampler']['AO'] = _mud_TextureSampler_AO();
        Module['TextureSampler']['User4'] = _mud_TextureSampler_User4();
        Module['TextureSampler']['Depth'] = _mud_TextureSampler_Depth();
        Module['TextureSampler']['User5'] = _mud_TextureSampler_User5();
        Module['TextureSampler']['Radiance'] = _mud_TextureSampler_Radiance();
        Module['TextureSampler']['ShadowAtlas'] = _mud_TextureSampler_ShadowAtlas();
        Module['TextureSampler']['ShadowCSM'] = _mud_TextureSampler_ShadowCSM();
        Module['TextureSampler']['Lightmap'] = _mud_TextureSampler_Lightmap();
        Module['TextureSampler']['ReflectionProbe'] = _mud_TextureSampler_ReflectionProbe();
        Module['TextureSampler']['GIProbe'] = _mud_TextureSampler_GIProbe();
        Module['TextureSampler']['Skeleton'] = _mud_TextureSampler_Skeleton();
        Module['TextureSampler']['Zones'] = _mud_TextureSampler_Zones();
        Module['TextureSampler']['Materials'] = _mud_TextureSampler_Materials();
        Module['TextureSampler']['Lights'] = _mud_TextureSampler_Lights();
        Module['TextureSampler']['Clusters'] = _mud_TextureSampler_Clusters();
        Module['TextureSampler']['LightRecords'] = _mud_TextureSampler_LightRecords();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
