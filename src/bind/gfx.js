Module['stl'] = Module['stl'] || {};
Module['gfx'] = Module['gfx'] || {};
// Animated
function Animated() { throw "cannot construct a Animated, no constructor in IDL" }
Animated.prototype = Object.create(WrapperObject.prototype);
Animated.prototype.constructor = Animated;
Animated.prototype.__class__ = Animated;
Animated.__cache__ = {};
Module['Animated'] = Animated;
Animated.prototype["start"] = Animated.prototype.start = function(self, a0, a1, a2, a3, a4) {
    var self = this.ptr;
    ensureCache.prepare();
    if (a2 === undefined) { _mud_Animated_start_2(self, ensureString(/*animation*/a0), /*loop*/a1); return; }
    if (a3 === undefined) { _mud_Animated_start_3(self, ensureString(/*animation*/a0), /*loop*/a1, /*blend*/a2); return; }
    if (a4 === undefined) { _mud_Animated_start_4(self, ensureString(/*animation*/a0), /*loop*/a1, /*blend*/a2, /*speed*/a3); return; }
    _mud_Animated_start_5(self, ensureString(/*animation*/a0), /*loop*/a1, /*blend*/a2, /*speed*/a3, /*transient*/a4);
};
Animated.prototype["play"] = Animated.prototype.play = function(self, a0, a1, a2, a3, a4) {
    var self = this.ptr;
    if (a2 === undefined) { _mud_Animated_play_2(self, /*animation*/a0.ptr, /*loop*/a1); return; }
    if (a3 === undefined) { _mud_Animated_play_3(self, /*animation*/a0.ptr, /*loop*/a1, /*blend*/a2); return; }
    if (a4 === undefined) { _mud_Animated_play_4(self, /*animation*/a0.ptr, /*loop*/a1, /*blend*/a2, /*speed*/a3); return; }
    _mud_Animated_play_5(self, /*animation*/a0.ptr, /*loop*/a1, /*blend*/a2, /*speed*/a3, /*transient*/a4);
};
Animated.prototype["seek"] = Animated.prototype.seek = function(self, a0) {
    var self = this.ptr;
    _mud_Animated_seek_1(self, /*time*/a0);
};
Animated.prototype["pause"] = Animated.prototype.pause = function(self) {
    var self = this.ptr;
    _mud_Animated_pause_0(self);
};
Animated.prototype["stop"] = Animated.prototype.stop = function(self) {
    var self = this.ptr;
    _mud_Animated_stop_0(self);
};
Animated.prototype["advance"] = Animated.prototype.advance = function(self, a0) {
    var self = this.ptr;
    _mud_Animated_advance_1(self, /*time*/a0);
};
Animated.prototype["next_animation"] = Animated.prototype.next_animation = function(self) {
    var self = this.ptr;
    _mud_Animated_next_animation_0(self);
};
Animated.prototype["playing"] = Animated.prototype.playing = function(self) {
    var self = this.ptr;
    return Pointer_stringify(_mud_Animated_playing_0(self));
};
Object.defineProperty(Animated.prototype, "active", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Animated__get_active(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Animated__set_active(self, value);
    }
});
Object.defineProperty(Animated.prototype, "speed_scale", {
    get: function() {
        var self = this.ptr;
        return _mud_Animated__get_speed_scale(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Animated__set_speed_scale(self, value);
    }
});
Object.defineProperty(Animated.prototype, "default_blend_time", {
    get: function() {
        var self = this.ptr;
        return _mud_Animated__get_default_blend_time(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Animated__set_default_blend_time(self, value);
    }
});
Animated.prototype["__destroy__"] = Animated.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Animated__destroy(self);
};
// AnimatedTrack
function AnimatedTrack() {
    this.ptr = _mud_AnimatedTrack__construct_0(); this.type = AnimatedTrack; getCache(AnimatedTrack)[this.ptr] = this;
};
AnimatedTrack.prototype = Object.create(WrapperObject.prototype);
AnimatedTrack.prototype.constructor = AnimatedTrack;
AnimatedTrack.prototype.__class__ = AnimatedTrack;
AnimatedTrack.__cache__ = {};
Module['AnimatedTrack'] = AnimatedTrack;
AnimatedTrack.prototype["__destroy__"] = AnimatedTrack.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AnimatedTrack__destroy(self);
};
// Animation
function Animation() { throw "cannot construct a Animation, no constructor in IDL" }
Animation.prototype = Object.create(WrapperObject.prototype);
Animation.prototype.constructor = Animation;
Animation.prototype.__class__ = Animation;
Animation.__cache__ = {};
Module['Animation'] = Animation;
Object.defineProperty(Animation.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Animation__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Animation__set_name(self, ensureString(value));
    }
});
Object.defineProperty(Animation.prototype, "length", {
    get: function() {
        var self = this.ptr;
        return _mud_Animation__get_length(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Animation__set_length(self, value);
    }
});
Object.defineProperty(Animation.prototype, "step", {
    get: function() {
        var self = this.ptr;
        return _mud_Animation__get_step(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Animation__set_step(self, value);
    }
});
Animation.prototype["__destroy__"] = Animation.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Animation__destroy(self);
};
// AnimationPlay
function AnimationPlay() {
    this.ptr = _mud_AnimationPlay__construct_0(); this.type = AnimationPlay; getCache(AnimationPlay)[this.ptr] = this;
};
AnimationPlay.prototype = Object.create(WrapperObject.prototype);
AnimationPlay.prototype.constructor = AnimationPlay;
AnimationPlay.prototype.__class__ = AnimationPlay;
AnimationPlay.__cache__ = {};
Module['AnimationPlay'] = AnimationPlay;
Object.defineProperty(AnimationPlay.prototype, "animation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_AnimationPlay__get_animation(self), Animation);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationPlay__set_animation(self, value.ptr);
    }
});
Object.defineProperty(AnimationPlay.prototype, "loop", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_AnimationPlay__get_loop(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationPlay__set_loop(self, value);
    }
});
Object.defineProperty(AnimationPlay.prototype, "speed", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationPlay__get_speed(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationPlay__set_speed(self, value);
    }
});
Object.defineProperty(AnimationPlay.prototype, "transient", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_AnimationPlay__get_transient(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationPlay__set_transient(self, value);
    }
});
Object.defineProperty(AnimationPlay.prototype, "fadeout", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationPlay__get_fadeout(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationPlay__set_fadeout(self, value);
    }
});
Object.defineProperty(AnimationPlay.prototype, "fadeout_left", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationPlay__get_fadeout_left(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationPlay__set_fadeout_left(self, value);
    }
});
Object.defineProperty(AnimationPlay.prototype, "cursor", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationPlay__get_cursor(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationPlay__set_cursor(self, value);
    }
});
Object.defineProperty(AnimationPlay.prototype, "ended", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_AnimationPlay__get_ended(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationPlay__set_ended(self, value);
    }
});
AnimationPlay.prototype["__destroy__"] = AnimationPlay.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AnimationPlay__destroy(self);
};
// AnimationTrack
function AnimationTrack() { throw "cannot construct a AnimationTrack, no constructor in IDL" }
AnimationTrack.prototype = Object.create(WrapperObject.prototype);
AnimationTrack.prototype.constructor = AnimationTrack;
AnimationTrack.prototype.__class__ = AnimationTrack;
AnimationTrack.__cache__ = {};
Module['AnimationTrack'] = AnimationTrack;
Object.defineProperty(AnimationTrack.prototype, "animation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_AnimationTrack__get_animation(self), Animation);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationTrack__set_animation(self, value.ptr);
    }
});
Object.defineProperty(AnimationTrack.prototype, "node", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationTrack__get_node(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationTrack__set_node(self, value);
    }
});
Object.defineProperty(AnimationTrack.prototype, "node_name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_AnimationTrack__get_node_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationTrack__set_node_name(self, ensureString(value));
    }
});
Object.defineProperty(AnimationTrack.prototype, "target", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationTrack__get_target(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationTrack__set_target(self, value);
    }
});
Object.defineProperty(AnimationTrack.prototype, "value_type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_AnimationTrack__get_value_type(self), Type);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationTrack__set_value_type(self, value.ptr);
    }
});
Object.defineProperty(AnimationTrack.prototype, "length", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationTrack__get_length(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationTrack__set_length(self, value);
    }
});
Object.defineProperty(AnimationTrack.prototype, "interpolation", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationTrack__get_interpolation(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_AnimationTrack__set_interpolation(self, value);
    }
});
AnimationTrack.prototype["__destroy__"] = AnimationTrack.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AnimationTrack__destroy(self);
};
// AssetStore<mud::Material>
function AssetStore_mud_Material() { throw "cannot construct a AssetStore<mud::Material>, no constructor in IDL" }
AssetStore_mud_Material.prototype = Object.create(WrapperObject.prototype);
AssetStore_mud_Material.prototype.constructor = AssetStore_mud_Material;
AssetStore_mud_Material.prototype.__class__ = AssetStore_mud_Material;
AssetStore_mud_Material.__cache__ = {};
Module['AssetStore_mud_Material'] = AssetStore_mud_Material;
AssetStore_mud_Material.prototype["get"] = AssetStore_mud_Material.prototype.get = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Material_get_1(self, ensureString(/*name*/a0)), Material);
};
AssetStore_mud_Material.prototype["create"] = AssetStore_mud_Material.prototype.create = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Material_create_1(self, ensureString(/*name*/a0)), Material);
};
AssetStore_mud_Material.prototype["fetch"] = AssetStore_mud_Material.prototype.fetch = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Material_fetch_1(self, ensureString(/*name*/a0)), Material);
};
AssetStore_mud_Material.prototype["file"] = AssetStore_mud_Material.prototype.file = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Material_file_1(self, ensureString(/*name*/a0)), Material);
};
AssetStore_mud_Material.prototype["file_at"] = AssetStore_mud_Material.prototype.file_at = function(self, a0, a1) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Material_file_at_2(self, ensureString(/*path*/a0), ensureString(/*name*/a1)), Material);
};
AssetStore_mud_Material.prototype["destroy"] = AssetStore_mud_Material.prototype.destroy = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    _mud_AssetStore_mud_Material_destroy_1(self, ensureString(/*name*/a0));
};
AssetStore_mud_Material.prototype["__destroy__"] = AssetStore_mud_Material.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AssetStore_mud_Material__destroy(self);
};
// AssetStore<mud::Model>
function AssetStore_mud_Model() { throw "cannot construct a AssetStore<mud::Model>, no constructor in IDL" }
AssetStore_mud_Model.prototype = Object.create(WrapperObject.prototype);
AssetStore_mud_Model.prototype.constructor = AssetStore_mud_Model;
AssetStore_mud_Model.prototype.__class__ = AssetStore_mud_Model;
AssetStore_mud_Model.__cache__ = {};
Module['AssetStore_mud_Model'] = AssetStore_mud_Model;
AssetStore_mud_Model.prototype["get"] = AssetStore_mud_Model.prototype.get = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Model_get_1(self, ensureString(/*name*/a0)), Model);
};
AssetStore_mud_Model.prototype["create"] = AssetStore_mud_Model.prototype.create = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Model_create_1(self, ensureString(/*name*/a0)), Model);
};
AssetStore_mud_Model.prototype["fetch"] = AssetStore_mud_Model.prototype.fetch = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Model_fetch_1(self, ensureString(/*name*/a0)), Model);
};
AssetStore_mud_Model.prototype["file"] = AssetStore_mud_Model.prototype.file = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Model_file_1(self, ensureString(/*name*/a0)), Model);
};
AssetStore_mud_Model.prototype["file_at"] = AssetStore_mud_Model.prototype.file_at = function(self, a0, a1) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Model_file_at_2(self, ensureString(/*path*/a0), ensureString(/*name*/a1)), Model);
};
AssetStore_mud_Model.prototype["destroy"] = AssetStore_mud_Model.prototype.destroy = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    _mud_AssetStore_mud_Model_destroy_1(self, ensureString(/*name*/a0));
};
AssetStore_mud_Model.prototype["__destroy__"] = AssetStore_mud_Model.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AssetStore_mud_Model__destroy(self);
};
// AssetStore<mud::ParticleFlow>
function AssetStore_mud_ParticleFlow() { throw "cannot construct a AssetStore<mud::ParticleFlow>, no constructor in IDL" }
AssetStore_mud_ParticleFlow.prototype = Object.create(WrapperObject.prototype);
AssetStore_mud_ParticleFlow.prototype.constructor = AssetStore_mud_ParticleFlow;
AssetStore_mud_ParticleFlow.prototype.__class__ = AssetStore_mud_ParticleFlow;
AssetStore_mud_ParticleFlow.__cache__ = {};
Module['AssetStore_mud_ParticleFlow'] = AssetStore_mud_ParticleFlow;
AssetStore_mud_ParticleFlow.prototype["get"] = AssetStore_mud_ParticleFlow.prototype.get = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_ParticleFlow_get_1(self, ensureString(/*name*/a0)), ParticleFlow);
};
AssetStore_mud_ParticleFlow.prototype["create"] = AssetStore_mud_ParticleFlow.prototype.create = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_ParticleFlow_create_1(self, ensureString(/*name*/a0)), ParticleFlow);
};
AssetStore_mud_ParticleFlow.prototype["fetch"] = AssetStore_mud_ParticleFlow.prototype.fetch = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_ParticleFlow_fetch_1(self, ensureString(/*name*/a0)), ParticleFlow);
};
AssetStore_mud_ParticleFlow.prototype["file"] = AssetStore_mud_ParticleFlow.prototype.file = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_ParticleFlow_file_1(self, ensureString(/*name*/a0)), ParticleFlow);
};
AssetStore_mud_ParticleFlow.prototype["file_at"] = AssetStore_mud_ParticleFlow.prototype.file_at = function(self, a0, a1) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_ParticleFlow_file_at_2(self, ensureString(/*path*/a0), ensureString(/*name*/a1)), ParticleFlow);
};
AssetStore_mud_ParticleFlow.prototype["destroy"] = AssetStore_mud_ParticleFlow.prototype.destroy = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    _mud_AssetStore_mud_ParticleFlow_destroy_1(self, ensureString(/*name*/a0));
};
AssetStore_mud_ParticleFlow.prototype["__destroy__"] = AssetStore_mud_ParticleFlow.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AssetStore_mud_ParticleFlow__destroy(self);
};
// AssetStore<mud::Prefab>
function AssetStore_mud_Prefab() { throw "cannot construct a AssetStore<mud::Prefab>, no constructor in IDL" }
AssetStore_mud_Prefab.prototype = Object.create(WrapperObject.prototype);
AssetStore_mud_Prefab.prototype.constructor = AssetStore_mud_Prefab;
AssetStore_mud_Prefab.prototype.__class__ = AssetStore_mud_Prefab;
AssetStore_mud_Prefab.__cache__ = {};
Module['AssetStore_mud_Prefab'] = AssetStore_mud_Prefab;
AssetStore_mud_Prefab.prototype["get"] = AssetStore_mud_Prefab.prototype.get = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Prefab_get_1(self, ensureString(/*name*/a0)), Prefab);
};
AssetStore_mud_Prefab.prototype["create"] = AssetStore_mud_Prefab.prototype.create = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Prefab_create_1(self, ensureString(/*name*/a0)), Prefab);
};
AssetStore_mud_Prefab.prototype["fetch"] = AssetStore_mud_Prefab.prototype.fetch = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Prefab_fetch_1(self, ensureString(/*name*/a0)), Prefab);
};
AssetStore_mud_Prefab.prototype["file"] = AssetStore_mud_Prefab.prototype.file = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Prefab_file_1(self, ensureString(/*name*/a0)), Prefab);
};
AssetStore_mud_Prefab.prototype["file_at"] = AssetStore_mud_Prefab.prototype.file_at = function(self, a0, a1) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Prefab_file_at_2(self, ensureString(/*path*/a0), ensureString(/*name*/a1)), Prefab);
};
AssetStore_mud_Prefab.prototype["destroy"] = AssetStore_mud_Prefab.prototype.destroy = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    _mud_AssetStore_mud_Prefab_destroy_1(self, ensureString(/*name*/a0));
};
AssetStore_mud_Prefab.prototype["__destroy__"] = AssetStore_mud_Prefab.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AssetStore_mud_Prefab__destroy(self);
};
// AssetStore<mud::Program>
function AssetStore_mud_Program() { throw "cannot construct a AssetStore<mud::Program>, no constructor in IDL" }
AssetStore_mud_Program.prototype = Object.create(WrapperObject.prototype);
AssetStore_mud_Program.prototype.constructor = AssetStore_mud_Program;
AssetStore_mud_Program.prototype.__class__ = AssetStore_mud_Program;
AssetStore_mud_Program.__cache__ = {};
Module['AssetStore_mud_Program'] = AssetStore_mud_Program;
AssetStore_mud_Program.prototype["get"] = AssetStore_mud_Program.prototype.get = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Program_get_1(self, ensureString(/*name*/a0)), Program);
};
AssetStore_mud_Program.prototype["create"] = AssetStore_mud_Program.prototype.create = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Program_create_1(self, ensureString(/*name*/a0)), Program);
};
AssetStore_mud_Program.prototype["fetch"] = AssetStore_mud_Program.prototype.fetch = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Program_fetch_1(self, ensureString(/*name*/a0)), Program);
};
AssetStore_mud_Program.prototype["file"] = AssetStore_mud_Program.prototype.file = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Program_file_1(self, ensureString(/*name*/a0)), Program);
};
AssetStore_mud_Program.prototype["file_at"] = AssetStore_mud_Program.prototype.file_at = function(self, a0, a1) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Program_file_at_2(self, ensureString(/*path*/a0), ensureString(/*name*/a1)), Program);
};
AssetStore_mud_Program.prototype["destroy"] = AssetStore_mud_Program.prototype.destroy = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    _mud_AssetStore_mud_Program_destroy_1(self, ensureString(/*name*/a0));
};
AssetStore_mud_Program.prototype["__destroy__"] = AssetStore_mud_Program.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AssetStore_mud_Program__destroy(self);
};
// AssetStore<mud::Texture>
function AssetStore_mud_Texture() { throw "cannot construct a AssetStore<mud::Texture>, no constructor in IDL" }
AssetStore_mud_Texture.prototype = Object.create(WrapperObject.prototype);
AssetStore_mud_Texture.prototype.constructor = AssetStore_mud_Texture;
AssetStore_mud_Texture.prototype.__class__ = AssetStore_mud_Texture;
AssetStore_mud_Texture.__cache__ = {};
Module['AssetStore_mud_Texture'] = AssetStore_mud_Texture;
AssetStore_mud_Texture.prototype["get"] = AssetStore_mud_Texture.prototype.get = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Texture_get_1(self, ensureString(/*name*/a0)), Texture);
};
AssetStore_mud_Texture.prototype["create"] = AssetStore_mud_Texture.prototype.create = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Texture_create_1(self, ensureString(/*name*/a0)), Texture);
};
AssetStore_mud_Texture.prototype["fetch"] = AssetStore_mud_Texture.prototype.fetch = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Texture_fetch_1(self, ensureString(/*name*/a0)), Texture);
};
AssetStore_mud_Texture.prototype["file"] = AssetStore_mud_Texture.prototype.file = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Texture_file_1(self, ensureString(/*name*/a0)), Texture);
};
AssetStore_mud_Texture.prototype["file_at"] = AssetStore_mud_Texture.prototype.file_at = function(self, a0, a1) {
    var self = this.ptr;
    ensureCache.prepare();
    return wrapPointer(_mud_AssetStore_mud_Texture_file_at_2(self, ensureString(/*path*/a0), ensureString(/*name*/a1)), Texture);
};
AssetStore_mud_Texture.prototype["destroy"] = AssetStore_mud_Texture.prototype.destroy = function(self, a0) {
    var self = this.ptr;
    ensureCache.prepare();
    _mud_AssetStore_mud_Texture_destroy_1(self, ensureString(/*name*/a0));
};
AssetStore_mud_Texture.prototype["__destroy__"] = AssetStore_mud_Texture.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AssetStore_mud_Texture__destroy(self);
};
// Background
function Background() {
    this.ptr = _mud_Background__construct_0(); this.type = Background; getCache(Background)[this.ptr] = this;
};
Background.prototype = Object.create(WrapperObject.prototype);
Background.prototype.constructor = Background;
Background.prototype.__class__ = Background;
Background.__cache__ = {};
Module['Background'] = Background;
Object.defineProperty(Background.prototype, "mode", {
    get: function() {
        var self = this.ptr;
        return _mud_Background__get_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Background__set_mode(self, value);
    }
});
Object.defineProperty(Background.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Background__get_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Background__set_colour(self, value.ptr);
    }
});
Object.defineProperty(Background.prototype, "custoprogram", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Background__get_custoprogram(self), Program);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Background__set_custoprogram(self, value.ptr);
    }
});
Background.prototype["__destroy__"] = Background.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Background__destroy(self);
};
// BaseMaterialBlock
function BaseMaterialBlock() {
    this.ptr = _mud_BaseMaterialBlock__construct_0(); this.type = BaseMaterialBlock; getCache(BaseMaterialBlock)[this.ptr] = this;
};
BaseMaterialBlock.prototype = Object.create(WrapperObject.prototype);
BaseMaterialBlock.prototype.constructor = BaseMaterialBlock;
BaseMaterialBlock.prototype.__class__ = BaseMaterialBlock;
BaseMaterialBlock.__cache__ = {};
Module['BaseMaterialBlock'] = BaseMaterialBlock;
Object.defineProperty(BaseMaterialBlock.prototype, "blend_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_BaseMaterialBlock__get_blend_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BaseMaterialBlock__set_blend_mode(self, value);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "cull_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_BaseMaterialBlock__get_cull_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BaseMaterialBlock__set_cull_mode(self, value);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "depth_draw_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_BaseMaterialBlock__get_depth_draw_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BaseMaterialBlock__set_depth_draw_mode(self, value);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "depth_test", {
    get: function() {
        var self = this.ptr;
        return _mud_BaseMaterialBlock__get_depth_test(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BaseMaterialBlock__set_depth_test(self, value);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "uv0_scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_BaseMaterialBlock__get_uv0_scale(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BaseMaterialBlock__set_uv0_scale(self, value.ptr);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "uv0_offset", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_BaseMaterialBlock__get_uv0_offset(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BaseMaterialBlock__set_uv0_offset(self, value.ptr);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "uv1_scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_BaseMaterialBlock__get_uv1_scale(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BaseMaterialBlock__set_uv1_scale(self, value.ptr);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "uv1_offset", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_BaseMaterialBlock__get_uv1_offset(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BaseMaterialBlock__set_uv1_offset(self, value.ptr);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "is_alpha", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_BaseMaterialBlock__get_is_alpha(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BaseMaterialBlock__set_is_alpha(self, value);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "screen_filter", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_BaseMaterialBlock__get_screen_filter(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_BaseMaterialBlock__set_screen_filter(self, value);
    }
});
BaseMaterialBlock.prototype["__destroy__"] = BaseMaterialBlock.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BaseMaterialBlock__destroy(self);
};
// Bone
function Bone() {
    this.ptr = _mud_Bone__construct_0(); this.type = Bone; getCache(Bone)[this.ptr] = this;
};
Bone.prototype = Object.create(WrapperObject.prototype);
Bone.prototype.constructor = Bone;
Bone.prototype.__class__ = Bone;
Bone.__cache__ = {};
Module['Bone'] = Bone;
Object.defineProperty(Bone.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Bone__get_position(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Bone__set_position(self, value.ptr);
    }
});
Object.defineProperty(Bone.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Bone__get_rotation(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Bone__set_rotation(self, value.ptr);
    }
});
Object.defineProperty(Bone.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Bone__get_scale(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Bone__set_scale(self, value.ptr);
    }
});
Bone.prototype["__destroy__"] = Bone.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Bone__destroy(self);
};
// Camera
function Camera() { throw "cannot construct a Camera, no constructor in IDL" }
Camera.prototype = Object.create(WrapperObject.prototype);
Camera.prototype.constructor = Camera;
Camera.prototype.__class__ = Camera;
Camera.__cache__ = {};
Module['Camera'] = Camera;
Object.defineProperty(Camera.prototype, "eye", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Camera__get_eye(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Camera__set_eye(self, value.ptr);
    }
});
Object.defineProperty(Camera.prototype, "target", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Camera__get_target(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Camera__set_target(self, value.ptr);
    }
});
Object.defineProperty(Camera.prototype, "transform", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Camera__get_transform(self), mat4);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Camera__set_transform(self, value.ptr);
    }
});
Object.defineProperty(Camera.prototype, "projection", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Camera__get_projection(self), mat4);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Camera__set_projection(self, value.ptr);
    }
});
Object.defineProperty(Camera.prototype, "fov", {
    get: function() {
        var self = this.ptr;
        return _mud_Camera__get_fov(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Camera__set_fov(self, value);
    }
});
Object.defineProperty(Camera.prototype, "aspect", {
    get: function() {
        var self = this.ptr;
        return _mud_Camera__get_aspect(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Camera__set_aspect(self, value);
    }
});
Object.defineProperty(Camera.prototype, "near", {
    get: function() {
        var self = this.ptr;
        return _mud_Camera__get_near(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Camera__set_near(self, value);
    }
});
Object.defineProperty(Camera.prototype, "far", {
    get: function() {
        var self = this.ptr;
        return _mud_Camera__get_far(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Camera__set_far(self, value);
    }
});
Object.defineProperty(Camera.prototype, "orthographic", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Camera__get_orthographic(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Camera__set_orthographic(self, value);
    }
});
Object.defineProperty(Camera.prototype, "height", {
    get: function() {
        var self = this.ptr;
        return _mud_Camera__get_height(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Camera__set_height(self, value);
    }
});
Object.defineProperty(Camera.prototype, "optimize_ends", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Camera__get_optimize_ends(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Camera__set_optimize_ends(self, value);
    }
});
Object.defineProperty(Camera.prototype, "clustered", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Camera__get_clustered(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Camera__set_clustered(self, value);
    }
});
Object.defineProperty(Camera.prototype, "lod_offsets", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Camera__get_lod_offsets(self), v4_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Camera__set_lod_offsets(self, value.ptr);
    }
});
Camera.prototype["__destroy__"] = Camera.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Camera__destroy(self);
};
// Culler
function Culler() { throw "cannot construct a Culler, no constructor in IDL" }
Culler.prototype = Object.create(WrapperObject.prototype);
Culler.prototype.constructor = Culler;
Culler.prototype.__class__ = Culler;
Culler.__cache__ = {};
Module['Culler'] = Culler;
Object.defineProperty(Culler.prototype, "viewport", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Culler__get_viewport(self), Viewport);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Culler__set_viewport(self, value.ptr);
    }
});
Culler.prototype["__destroy__"] = Culler.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Culler__destroy(self);
};
// DepthParams
function DepthParams() {
    this.ptr = _mud_DepthParams__construct_0(); this.type = DepthParams; getCache(DepthParams)[this.ptr] = this;
};
DepthParams.prototype = Object.create(WrapperObject.prototype);
DepthParams.prototype.constructor = DepthParams;
DepthParams.prototype.__class__ = DepthParams;
DepthParams.__cache__ = {};
Module['DepthParams'] = DepthParams;
DepthParams.prototype["__destroy__"] = DepthParams.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_DepthParams__destroy(self);
};
// Environment
function Environment() {
    this.ptr = _mud_Environment__construct_0(); this.type = Environment; getCache(Environment)[this.ptr] = this;
};
Environment.prototype = Object.create(WrapperObject.prototype);
Environment.prototype.constructor = Environment;
Environment.prototype.__class__ = Environment;
Environment.__cache__ = {};
Module['Environment'] = Environment;
Object.defineProperty(Environment.prototype, "background", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Environment__get_background(self), Background);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Environment__set_background(self, value.ptr);
    }
});
Object.defineProperty(Environment.prototype, "radiance", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Environment__get_radiance(self), Radiance);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Environment__set_radiance(self, value.ptr);
    }
});
Object.defineProperty(Environment.prototype, "sun", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Environment__get_sun(self), Sun);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Environment__set_sun(self, value.ptr);
    }
});
Object.defineProperty(Environment.prototype, "fog", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Environment__get_fog(self), Fog);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Environment__set_fog(self, value.ptr);
    }
});
Environment.prototype["__destroy__"] = Environment.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Environment__destroy(self);
};
// Filter
function Filter() { throw "cannot construct a Filter, no constructor in IDL" }
Filter.prototype = Object.create(WrapperObject.prototype);
Filter.prototype.constructor = Filter;
Filter.prototype.__class__ = Filter;
Filter.__cache__ = {};
Module['Filter'] = Filter;
Filter.prototype["__destroy__"] = Filter.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Filter__destroy(self);
};
// Fog
function Fog() {
    this.ptr = _mud_Fog__construct_0(); this.type = Fog; getCache(Fog)[this.ptr] = this;
};
Fog.prototype = Object.create(WrapperObject.prototype);
Fog.prototype.constructor = Fog;
Fog.prototype.__class__ = Fog;
Fog.__cache__ = {};
Module['Fog'] = Fog;
Object.defineProperty(Fog.prototype, "enabled", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Fog__get_enabled(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Fog__set_enabled(self, value);
    }
});
Object.defineProperty(Fog.prototype, "density", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_density(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Fog__set_density(self, value);
    }
});
Object.defineProperty(Fog.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Fog__get_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Fog__set_colour(self, value.ptr);
    }
});
Object.defineProperty(Fog.prototype, "depth", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Fog__get_depth(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Fog__set_depth(self, value);
    }
});
Object.defineProperty(Fog.prototype, "depth_begin", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_depth_begin(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Fog__set_depth_begin(self, value);
    }
});
Object.defineProperty(Fog.prototype, "depth_curve", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_depth_curve(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Fog__set_depth_curve(self, value);
    }
});
Object.defineProperty(Fog.prototype, "height", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Fog__get_height(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Fog__set_height(self, value);
    }
});
Object.defineProperty(Fog.prototype, "height_min", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_height_min(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Fog__set_height_min(self, value);
    }
});
Object.defineProperty(Fog.prototype, "height_max", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_height_max(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Fog__set_height_max(self, value);
    }
});
Object.defineProperty(Fog.prototype, "height_curve", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_height_curve(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Fog__set_height_curve(self, value);
    }
});
Object.defineProperty(Fog.prototype, "transmit", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Fog__get_transmit(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Fog__set_transmit(self, value);
    }
});
Object.defineProperty(Fog.prototype, "transmit_curve", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_transmit_curve(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Fog__set_transmit_curve(self, value);
    }
});
Fog.prototype["__destroy__"] = Fog.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Fog__destroy(self);
};
// FrameBuffer
function FrameBuffer() { throw "cannot construct a FrameBuffer, no constructor in IDL" }
FrameBuffer.prototype = Object.create(WrapperObject.prototype);
FrameBuffer.prototype.constructor = FrameBuffer;
FrameBuffer.prototype.__class__ = FrameBuffer;
FrameBuffer.__cache__ = {};
Module['FrameBuffer'] = FrameBuffer;
FrameBuffer.prototype["__destroy__"] = FrameBuffer.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FrameBuffer__destroy(self);
};
// FresnelMaterialBlock
function FresnelMaterialBlock() {
    this.ptr = _mud_FresnelMaterialBlock__construct_0(); this.type = FresnelMaterialBlock; getCache(FresnelMaterialBlock)[this.ptr] = this;
};
FresnelMaterialBlock.prototype = Object.create(WrapperObject.prototype);
FresnelMaterialBlock.prototype.constructor = FresnelMaterialBlock;
FresnelMaterialBlock.prototype.__class__ = FresnelMaterialBlock;
FresnelMaterialBlock.__cache__ = {};
Module['FresnelMaterialBlock'] = FresnelMaterialBlock;
Object.defineProperty(FresnelMaterialBlock.prototype, "enabled", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_FresnelMaterialBlock__get_enabled(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_FresnelMaterialBlock__set_enabled(self, value);
    }
});
Object.defineProperty(FresnelMaterialBlock.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_FresnelMaterialBlock__get_value(self), MaterialParam_mud_Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_FresnelMaterialBlock__set_value(self, value.ptr);
    }
});
Object.defineProperty(FresnelMaterialBlock.prototype, "fresnel_scale", {
    get: function() {
        var self = this.ptr;
        return _mud_FresnelMaterialBlock__get_fresnel_scale(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_FresnelMaterialBlock__set_fresnel_scale(self, value);
    }
});
Object.defineProperty(FresnelMaterialBlock.prototype, "fresnel_bias", {
    get: function() {
        var self = this.ptr;
        return _mud_FresnelMaterialBlock__get_fresnel_bias(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_FresnelMaterialBlock__set_fresnel_bias(self, value);
    }
});
Object.defineProperty(FresnelMaterialBlock.prototype, "fresnel_power", {
    get: function() {
        var self = this.ptr;
        return _mud_FresnelMaterialBlock__get_fresnel_power(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_FresnelMaterialBlock__set_fresnel_power(self, value);
    }
});
FresnelMaterialBlock.prototype["__destroy__"] = FresnelMaterialBlock.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FresnelMaterialBlock__destroy(self);
};
// Frustum
function Frustum() { throw "cannot construct a Frustum, no constructor in IDL" }
Frustum.prototype = Object.create(WrapperObject.prototype);
Frustum.prototype.constructor = Frustum;
Frustum.prototype.__class__ = Frustum;
Frustum.__cache__ = {};
Module['Frustum'] = Frustum;
Object.defineProperty(Frustum.prototype, "fov", {
    get: function() {
        var self = this.ptr;
        return _mud_Frustum__get_fov(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Frustum__set_fov(self, value);
    }
});
Object.defineProperty(Frustum.prototype, "aspect", {
    get: function() {
        var self = this.ptr;
        return _mud_Frustum__get_aspect(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Frustum__set_aspect(self, value);
    }
});
Object.defineProperty(Frustum.prototype, "near", {
    get: function() {
        var self = this.ptr;
        return _mud_Frustum__get_near(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Frustum__set_near(self, value);
    }
});
Object.defineProperty(Frustum.prototype, "far", {
    get: function() {
        var self = this.ptr;
        return _mud_Frustum__get_far(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Frustum__set_far(self, value);
    }
});
Object.defineProperty(Frustum.prototype, "center", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Frustum__get_center(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Frustum__set_center(self, value.ptr);
    }
});
Object.defineProperty(Frustum.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Frustum__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Frustum__set_radius(self, value);
    }
});
Frustum.prototype["__destroy__"] = Frustum.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Frustum__destroy(self);
};
// FrustumSlice
function FrustumSlice() {
    this.ptr = _mud_FrustumSlice__construct_0(); this.type = FrustumSlice; getCache(FrustumSlice)[this.ptr] = this;
};
FrustumSlice.prototype = Object.create(WrapperObject.prototype);
FrustumSlice.prototype.constructor = FrustumSlice;
FrustumSlice.prototype.__class__ = FrustumSlice;
FrustumSlice.__cache__ = {};
Module['FrustumSlice'] = FrustumSlice;
FrustumSlice.prototype["__destroy__"] = FrustumSlice.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FrustumSlice__destroy(self);
};
// GfxBlock
function GfxBlock() { throw "cannot construct a GfxBlock, no constructor in IDL" }
GfxBlock.prototype = Object.create(WrapperObject.prototype);
GfxBlock.prototype.constructor = GfxBlock;
GfxBlock.prototype.__class__ = GfxBlock;
GfxBlock.__cache__ = {};
Module['GfxBlock'] = GfxBlock;
Object.defineProperty(GfxBlock.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_GfxBlock__get_type(self), Type);
    }});
Object.defineProperty(GfxBlock.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_GfxBlock__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_GfxBlock__set_index(self, value);
    }
});
GfxBlock.prototype["__destroy__"] = GfxBlock.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_GfxBlock__destroy(self);
};
// GfxContext
function GfxContext() { throw "cannot construct a GfxContext, no constructor in IDL" }
GfxContext.prototype = Object.create(WrapperObject.prototype);
GfxContext.prototype.constructor = GfxContext;
GfxContext.prototype.__class__ = GfxContext;
GfxContext.__cache__ = {};
Module['GfxContext'] = GfxContext;
GfxContext.prototype["__destroy__"] = GfxContext.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_GfxContext__destroy(self);
};
// GfxSystem
function GfxSystem(a0) {
    ensureCache.prepare();
    this.ptr = _mud_GfxSystem__construct_1(ensureString(/*resource_path*/a0)); this.type = GfxSystem; getCache(GfxSystem)[this.ptr] = this;
};
GfxSystem.prototype = Object.create(WrapperObject.prototype);
GfxSystem.prototype.constructor = GfxSystem;
GfxSystem.prototype.__class__ = GfxSystem;
GfxSystem.__cache__ = {};
Module['GfxSystem'] = GfxSystem;
GfxSystem.prototype["default_pipeline"] = GfxSystem.prototype.default_pipeline = function(self) {
    var self = this.ptr;
    _mud_GfxSystem_default_pipeline_0(self);
};
GfxSystem.prototype["add_resource_path"] = GfxSystem.prototype.add_resource_path = function(self, a0, a1) {
    var self = this.ptr;
    ensureCache.prepare();
    if (a1 === undefined) { _mud_GfxSystem_add_resource_path_1(self, ensureString(/*path*/a0)); return; }
    _mud_GfxSystem_add_resource_path_2(self, ensureString(/*path*/a0), /*relative*/a1);
};
GfxSystem.prototype["debug_material"] = GfxSystem.prototype.debug_material = function(self) {
    var self = this.ptr;
    return wrapPointer(_mud_GfxSystem_debug_material_0(self), Material);
};
GfxSystem.prototype["fetch_material"] = GfxSystem.prototype.fetch_material = function(self, a0, a1, a2) {
    var self = this.ptr;
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_GfxSystem_fetch_material_2(self, ensureString(/*name*/a0), ensureString(/*shader*/a1)), Material); }
    return wrapPointer(_mud_GfxSystem_fetch_material_3(self, ensureString(/*name*/a0), ensureString(/*shader*/a1), /*builtin*/a2), Material);
};
GfxSystem.prototype["fetch_image256_material"] = GfxSystem.prototype.fetch_image256_material = function(self, a0) {
    var self = this.ptr;
    return wrapPointer(_mud_GfxSystem_fetch_image256_material_1(self, /*image*/a0.ptr), Material);
};
GfxSystem.prototype["fetch_symbol"] = GfxSystem.prototype.fetch_symbol = function(self, a0, a1, a2) {
    var self = this.ptr;
    return wrapPointer(_mud_GfxSystem_fetch_symbol_3(self, /*symbol*/a0.ptr, /*shape*/a1.ptr, /*draw_mode*/a2), Model);
};
GfxSystem.prototype["fetch_symbol_material"] = GfxSystem.prototype.fetch_symbol_material = function(self, a0, a1) {
    var self = this.ptr;
    return wrapPointer(_mud_GfxSystem_fetch_symbol_material_2(self, /*symbol*/a0.ptr, /*draw_mode*/a1), Material);
};
Object.defineProperty(GfxSystem.prototype, "textures", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_GfxSystem__get_textures(self), AssetStore_mud_Texture);
    }});
Object.defineProperty(GfxSystem.prototype, "programs", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_GfxSystem__get_programs(self), AssetStore_mud_Program);
    }});
Object.defineProperty(GfxSystem.prototype, "materials", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_GfxSystem__get_materials(self), AssetStore_mud_Material);
    }});
Object.defineProperty(GfxSystem.prototype, "models", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_GfxSystem__get_models(self), AssetStore_mud_Model);
    }});
Object.defineProperty(GfxSystem.prototype, "particles", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_GfxSystem__get_particles(self), AssetStore_mud_ParticleFlow);
    }});
Object.defineProperty(GfxSystem.prototype, "prefabs", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_GfxSystem__get_prefabs(self), AssetStore_mud_Prefab);
    }});
GfxSystem.prototype["__destroy__"] = GfxSystem.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_GfxSystem__destroy(self);
};
// Gnode
function Gnode() { throw "cannot construct a Gnode, no constructor in IDL" }
Gnode.prototype = Object.create(WrapperObject.prototype);
Gnode.prototype.constructor = Gnode;
Gnode.prototype.__class__ = Gnode;
Gnode.__cache__ = {};
Module['Gnode'] = Gnode;
Gnode.prototype["__destroy__"] = Gnode.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Gnode__destroy(self);
};
// ImmediateDraw
function ImmediateDraw() { throw "cannot construct a ImmediateDraw, no constructor in IDL" }
ImmediateDraw.prototype = Object.create(WrapperObject.prototype);
ImmediateDraw.prototype.constructor = ImmediateDraw;
ImmediateDraw.prototype.__class__ = ImmediateDraw;
ImmediateDraw.__cache__ = {};
Module['ImmediateDraw'] = ImmediateDraw;
ImmediateDraw.prototype["__destroy__"] = ImmediateDraw.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ImmediateDraw__destroy(self);
};
// ImportConfig
function ImportConfig() {
    this.ptr = _mud_ImportConfig__construct_0(); this.type = ImportConfig; getCache(ImportConfig)[this.ptr] = this;
};
ImportConfig.prototype = Object.create(WrapperObject.prototype);
ImportConfig.prototype.constructor = ImportConfig;
ImportConfig.prototype.__class__ = ImportConfig;
ImportConfig.__cache__ = {};
Module['ImportConfig'] = ImportConfig;
Object.defineProperty(ImportConfig.prototype, "format", {
    get: function() {
        var self = this.ptr;
        return _mud_ImportConfig__get_format(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ImportConfig__set_format(self, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ImportConfig__get_position(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ImportConfig__set_position(self, value.ptr);
    }
});
Object.defineProperty(ImportConfig.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ImportConfig__get_rotation(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ImportConfig__set_rotation(self, value.ptr);
    }
});
Object.defineProperty(ImportConfig.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ImportConfig__get_scale(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ImportConfig__set_scale(self, value.ptr);
    }
});
Object.defineProperty(ImportConfig.prototype, "transform", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ImportConfig__get_transform(self), mat4);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ImportConfig__set_transform(self, value.ptr);
    }
});
Object.defineProperty(ImportConfig.prototype, "suffix", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_ImportConfig__get_suffix(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ImportConfig__set_suffix(self, ensureString(value));
    }
});
Object.defineProperty(ImportConfig.prototype, "force_reimport", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ImportConfig__get_force_reimport(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ImportConfig__set_force_reimport(self, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "cache_geometry", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ImportConfig__get_cache_geometry(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ImportConfig__set_cache_geometry(self, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "optimize_geometry", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ImportConfig__get_optimize_geometry(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ImportConfig__set_optimize_geometry(self, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "flags", {
    get: function() {
        var self = this.ptr;
        return _mud_ImportConfig__get_flags(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ImportConfig__set_flags(self, value);
    }
});
ImportConfig.prototype["__destroy__"] = ImportConfig.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ImportConfig__destroy(self);
};
// Item
function Item() { throw "cannot construct a Item, no constructor in IDL" }
Item.prototype = Object.create(WrapperObject.prototype);
Item.prototype.constructor = Item;
Item.prototype.__class__ = Item;
Item.__cache__ = {};
Module['Item'] = Item;
Object.defineProperty(Item.prototype, "node", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Item__get_node(self), Node3);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Item__set_node(self, value.ptr);
    }
});
Object.defineProperty(Item.prototype, "model", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Item__get_model(self), Model);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Item__set_model(self, value.ptr);
    }
});
Object.defineProperty(Item.prototype, "flags", {
    get: function() {
        var self = this.ptr;
        return _mud_Item__get_flags(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Item__set_flags(self, value);
    }
});
Object.defineProperty(Item.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Item__get_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Item__set_colour(self, value.ptr);
    }
});
Object.defineProperty(Item.prototype, "material", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Item__get_material(self), Material);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Item__set_material(self, value.ptr);
    }
});
Object.defineProperty(Item.prototype, "visible", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Item__get_visible(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Item__set_visible(self, value);
    }
});
Object.defineProperty(Item.prototype, "shadow", {
    get: function() {
        var self = this.ptr;
        return _mud_Item__get_shadow(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Item__set_shadow(self, value);
    }
});
Object.defineProperty(Item.prototype, "rig", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Item__get_rig(self), Rig);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Item__set_rig(self, value.ptr);
    }
});
Item.prototype["__destroy__"] = Item.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Item__destroy(self);
};
// Joint
function Joint() {
    this.ptr = _mud_Joint__construct_0(); this.type = Joint; getCache(Joint)[this.ptr] = this;
};
Joint.prototype = Object.create(WrapperObject.prototype);
Joint.prototype.constructor = Joint;
Joint.prototype.__class__ = Joint;
Joint.__cache__ = {};
Module['Joint'] = Joint;
Joint.prototype["__destroy__"] = Joint.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Joint__destroy(self);
};
// Light
function Light() { throw "cannot construct a Light, no constructor in IDL" }
Light.prototype = Object.create(WrapperObject.prototype);
Light.prototype.constructor = Light;
Light.prototype.__class__ = Light;
Light.__cache__ = {};
Module['Light'] = Light;
Object.defineProperty(Light.prototype, "node", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Light__get_node(self), Node3);
    }});
Object.defineProperty(Light.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_type(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_type(self, value);
    }
});
Object.defineProperty(Light.prototype, "visible", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Light__get_visible(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_visible(self, value);
    }
});
Object.defineProperty(Light.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Light__get_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_colour(self, value.ptr);
    }
});
Object.defineProperty(Light.prototype, "range", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_range(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_range(self, value);
    }
});
Object.defineProperty(Light.prototype, "energy", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_energy(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_energy(self, value);
    }
});
Object.defineProperty(Light.prototype, "specular", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_specular(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_specular(self, value);
    }
});
Object.defineProperty(Light.prototype, "attenuation", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_attenuation(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_attenuation(self, value);
    }
});
Object.defineProperty(Light.prototype, "shadows", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Light__get_shadows(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_shadows(self, value);
    }
});
Object.defineProperty(Light.prototype, "shadow_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Light__get_shadow_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_shadow_colour(self, value.ptr);
    }
});
Object.defineProperty(Light.prototype, "shadow_range", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_shadow_range(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_shadow_range(self, value);
    }
});
Object.defineProperty(Light.prototype, "layers", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_layers(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_layers(self, value);
    }
});
Object.defineProperty(Light.prototype, "last_render", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_last_render(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_last_render(self, value);
    }
});
Object.defineProperty(Light.prototype, "last_update", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_last_update(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_last_update(self, value);
    }
});
Object.defineProperty(Light.prototype, "spot_angle", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_spot_angle(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_spot_angle(self, value);
    }
});
Object.defineProperty(Light.prototype, "spot_attenuation", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_spot_attenuation(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_spot_attenuation(self, value);
    }
});
Object.defineProperty(Light.prototype, "shadow_flags", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_shadow_flags(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_shadow_flags(self, value);
    }
});
Object.defineProperty(Light.prototype, "shadow_nusplits", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_shadow_nusplits(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_shadow_nusplits(self, value);
    }
});
Object.defineProperty(Light.prototype, "shadow_split_distribution", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_shadow_split_distribution(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_shadow_split_distribution(self, value);
    }
});
Object.defineProperty(Light.prototype, "shadow_normal_bias", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_shadow_normal_bias(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_shadow_normal_bias(self, value);
    }
});
Object.defineProperty(Light.prototype, "shadow_bias", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_shadow_bias(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Light__set_shadow_bias(self, value);
    }
});
Light.prototype["__destroy__"] = Light.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Light__destroy(self);
};
// Material
function Material() { throw "cannot construct a Material, no constructor in IDL" }
Material.prototype = Object.create(WrapperObject.prototype);
Material.prototype.constructor = Material;
Material.prototype.__class__ = Material;
Material.__cache__ = {};
Module['Material'] = Material;
Object.defineProperty(Material.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Material__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Material__set_index(self, value);
    }
});
Object.defineProperty(Material.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Material__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Material__set_name(self, ensureString(value));
    }
});
Object.defineProperty(Material.prototype, "builtin", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Material__get_builtin(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Material__set_builtin(self, value);
    }
});
Object.defineProperty(Material.prototype, "program", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_program(self), Program);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Material__set_program(self, value.ptr);
    }
});
Object.defineProperty(Material.prototype, "base_block", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_base_block(self), BaseMaterialBlock);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Material__set_base_block(self, value.ptr);
    }
});
Object.defineProperty(Material.prototype, "unshaded_block", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_unshaded_block(self), UnshadedMaterialBlock);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Material__set_unshaded_block(self, value.ptr);
    }
});
Object.defineProperty(Material.prototype, "pbr_block", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_pbr_block(self), PbrMaterialBlock);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Material__set_pbr_block(self, value.ptr);
    }
});
Object.defineProperty(Material.prototype, "fresnel_block", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_fresnel_block(self), FresnelMaterialBlock);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Material__set_fresnel_block(self, value.ptr);
    }
});
Material.prototype["__destroy__"] = Material.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Material__destroy(self);
};
// MaterialParam<float>
function MaterialParam_float() {
    this.ptr = _mud_MaterialParam_float__construct_0(); this.type = MaterialParam_float; getCache(MaterialParam_float)[this.ptr] = this;
};
MaterialParam_float.prototype = Object.create(WrapperObject.prototype);
MaterialParam_float.prototype.constructor = MaterialParam_float;
MaterialParam_float.prototype.__class__ = MaterialParam_float;
MaterialParam_float.__cache__ = {};
Module['MaterialParam_float'] = MaterialParam_float;
Object.defineProperty(MaterialParam_float.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return _mud_MaterialParam_float__get_value(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_MaterialParam_float__set_value(self, value);
    }
});
Object.defineProperty(MaterialParam_float.prototype, "texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_MaterialParam_float__get_texture(self), Texture);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_MaterialParam_float__set_texture(self, value.ptr);
    }
});
Object.defineProperty(MaterialParam_float.prototype, "channel", {
    get: function() {
        var self = this.ptr;
        return _mud_MaterialParam_float__get_channel(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_MaterialParam_float__set_channel(self, value);
    }
});
MaterialParam_float.prototype["__destroy__"] = MaterialParam_float.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_MaterialParam_float__destroy(self);
};
// MaterialParam<mud::Colour>
function MaterialParam_mud_Colour() {
    this.ptr = _mud_MaterialParam_mud_Colour__construct_0(); this.type = MaterialParam_mud_Colour; getCache(MaterialParam_mud_Colour)[this.ptr] = this;
};
MaterialParam_mud_Colour.prototype = Object.create(WrapperObject.prototype);
MaterialParam_mud_Colour.prototype.constructor = MaterialParam_mud_Colour;
MaterialParam_mud_Colour.prototype.__class__ = MaterialParam_mud_Colour;
MaterialParam_mud_Colour.__cache__ = {};
Module['MaterialParam_mud_Colour'] = MaterialParam_mud_Colour;
Object.defineProperty(MaterialParam_mud_Colour.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_MaterialParam_mud_Colour__get_value(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_MaterialParam_mud_Colour__set_value(self, value.ptr);
    }
});
Object.defineProperty(MaterialParam_mud_Colour.prototype, "texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_MaterialParam_mud_Colour__get_texture(self), Texture);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_MaterialParam_mud_Colour__set_texture(self, value.ptr);
    }
});
Object.defineProperty(MaterialParam_mud_Colour.prototype, "channel", {
    get: function() {
        var self = this.ptr;
        return _mud_MaterialParam_mud_Colour__get_channel(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_MaterialParam_mud_Colour__set_channel(self, value);
    }
});
MaterialParam_mud_Colour.prototype["__destroy__"] = MaterialParam_mud_Colour.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_MaterialParam_mud_Colour__destroy(self);
};
// Mesh
function Mesh() { throw "cannot construct a Mesh, no constructor in IDL" }
Mesh.prototype = Object.create(WrapperObject.prototype);
Mesh.prototype.constructor = Mesh;
Mesh.prototype.__class__ = Mesh;
Mesh.__cache__ = {};
Module['Mesh'] = Mesh;
Object.defineProperty(Mesh.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Mesh__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Mesh__set_name(self, ensureString(value));
    }
});
Object.defineProperty(Mesh.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Mesh__set_index(self, value);
    }
});
Object.defineProperty(Mesh.prototype, "draw_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_draw_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Mesh__set_draw_mode(self, value);
    }
});
Object.defineProperty(Mesh.prototype, "aabb", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Mesh__get_aabb(self), Aabb);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Mesh__set_aabb(self, value.ptr);
    }
});
Object.defineProperty(Mesh.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Mesh__set_radius(self, value);
    }
});
Object.defineProperty(Mesh.prototype, "origin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Mesh__get_origin(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Mesh__set_origin(self, value.ptr);
    }
});
Object.defineProperty(Mesh.prototype, "readback", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Mesh__get_readback(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Mesh__set_readback(self, value);
    }
});
Object.defineProperty(Mesh.prototype, "vertex_format", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_vertex_format(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Mesh__set_vertex_format(self, value);
    }
});
Object.defineProperty(Mesh.prototype, "qnormals", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Mesh__get_qnormals(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Mesh__set_qnormals(self, value);
    }
});
Object.defineProperty(Mesh.prototype, "vertex_count", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_vertex_count(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Mesh__set_vertex_count(self, value);
    }
});
Object.defineProperty(Mesh.prototype, "index_count", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_index_count(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Mesh__set_index_count(self, value);
    }
});
Object.defineProperty(Mesh.prototype, "index32", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Mesh__get_index32(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Mesh__set_index32(self, value);
    }
});
Object.defineProperty(Mesh.prototype, "material", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Mesh__get_material(self), Material);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Mesh__set_material(self, value.ptr);
    }
});
Mesh.prototype["__destroy__"] = Mesh.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Mesh__destroy(self);
};
// Model
function Model() { throw "cannot construct a Model, no constructor in IDL" }
Model.prototype = Object.create(WrapperObject.prototype);
Model.prototype.constructor = Model;
Model.prototype.__class__ = Model;
Model.__cache__ = {};
Module['Model'] = Model;
Object.defineProperty(Model.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Model__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Model__set_name(self, ensureString(value));
    }
});
Object.defineProperty(Model.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Model__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Model__set_index(self, value);
    }
});
Object.defineProperty(Model.prototype, "aabb", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Model__get_aabb(self), Aabb);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Model__set_aabb(self, value.ptr);
    }
});
Object.defineProperty(Model.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Model__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Model__set_radius(self, value);
    }
});
Object.defineProperty(Model.prototype, "origin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Model__get_origin(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Model__set_origin(self, value.ptr);
    }
});
Model.prototype["__destroy__"] = Model.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Model__destroy(self);
};
// ModelItem
function ModelItem() {
    this.ptr = _mud_ModelItem__construct_0(); this.type = ModelItem; getCache(ModelItem)[this.ptr] = this;
};
ModelItem.prototype = Object.create(WrapperObject.prototype);
ModelItem.prototype.constructor = ModelItem;
ModelItem.prototype.__class__ = ModelItem;
ModelItem.__cache__ = {};
Module['ModelItem'] = ModelItem;
Object.defineProperty(ModelItem.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_ModelItem__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ModelItem__set_index(self, value);
    }
});
Object.defineProperty(ModelItem.prototype, "mesh", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ModelItem__get_mesh(self), Mesh);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ModelItem__set_mesh(self, value.ptr);
    }
});
Object.defineProperty(ModelItem.prototype, "has_transform", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ModelItem__get_has_transform(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ModelItem__set_has_transform(self, value);
    }
});
Object.defineProperty(ModelItem.prototype, "transform", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ModelItem__get_transform(self), mat4);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ModelItem__set_transform(self, value.ptr);
    }
});
Object.defineProperty(ModelItem.prototype, "skin", {
    get: function() {
        var self = this.ptr;
        return _mud_ModelItem__get_skin(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ModelItem__set_skin(self, value);
    }
});
Object.defineProperty(ModelItem.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ModelItem__get_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ModelItem__set_colour(self, value.ptr);
    }
});
Object.defineProperty(ModelItem.prototype, "material", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ModelItem__get_material(self), Material);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ModelItem__set_material(self, value.ptr);
    }
});
ModelItem.prototype["__destroy__"] = ModelItem.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ModelItem__destroy(self);
};
// Node3
function Node3() { throw "cannot construct a Node3, no constructor in IDL" }
Node3.prototype = Object.create(WrapperObject.prototype);
Node3.prototype.constructor = Node3;
Node3.prototype.__class__ = Node3;
Node3.__cache__ = {};
Module['Node3'] = Node3;
Object.defineProperty(Node3.prototype, "scene", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Node3__get_scene(self), Scene);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Node3__set_scene(self, value.ptr);
    }
});
Object.defineProperty(Node3.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Node3__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Node3__set_index(self, value);
    }
});
Object.defineProperty(Node3.prototype, "transform", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Node3__get_transform(self), mat4);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Node3__set_transform(self, value.ptr);
    }
});
Object.defineProperty(Node3.prototype, "visible", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Node3__get_visible(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Node3__set_visible(self, value);
    }
});
Node3.prototype["__destroy__"] = Node3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Node3__destroy(self);
};
// ParticleFlow
function ParticleFlow() {
    this.ptr = _mud_ParticleFlow__construct_0(); this.type = ParticleFlow; getCache(ParticleFlow)[this.ptr] = this;
};
ParticleFlow.prototype = Object.create(WrapperObject.prototype);
ParticleFlow.prototype.constructor = ParticleFlow;
ParticleFlow.prototype.__class__ = ParticleFlow;
ParticleFlow.__cache__ = {};
Module['ParticleFlow'] = ParticleFlow;
Object.defineProperty(ParticleFlow.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_ParticleFlow__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_name(self, ensureString(value));
    }
});
Object.defineProperty(ParticleFlow.prototype, "duration", {
    get: function() {
        var self = this.ptr;
        return _mud_ParticleFlow__get_duration(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_duration(self, value);
    }
});
Object.defineProperty(ParticleFlow.prototype, "start_time", {
    get: function() {
        var self = this.ptr;
        return _mud_ParticleFlow__get_start_time(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_start_time(self, value);
    }
});
Object.defineProperty(ParticleFlow.prototype, "loop", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ParticleFlow__get_loop(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_loop(self, value);
    }
});
Object.defineProperty(ParticleFlow.prototype, "shape", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleFlow__get_shape(self), ShapeVar);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_shape(self, value.ptr);
    }
});
Object.defineProperty(ParticleFlow.prototype, "flow", {
    get: function() {
        var self = this.ptr;
        return _mud_ParticleFlow__get_flow(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_flow(self, value);
    }
});
Object.defineProperty(ParticleFlow.prototype, "billboard", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ParticleFlow__get_billboard(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_billboard(self, value);
    }
});
Object.defineProperty(ParticleFlow.prototype, "direction", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleFlow__get_direction(self), v3_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_direction(self, value.ptr);
    }
});
Object.defineProperty(ParticleFlow.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleFlow__get_rotation(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_rotation(self, value.ptr);
    }
});
Object.defineProperty(ParticleFlow.prototype, "blend_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_ParticleFlow__get_blend_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_blend_mode(self, value);
    }
});
Object.defineProperty(ParticleFlow.prototype, "volume", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleFlow__get_volume(self), ValueTrack_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_volume(self, value.ptr);
    }
});
Object.defineProperty(ParticleFlow.prototype, "rate", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleFlow__get_rate(self), ValueTrack_uint32_t);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_rate(self, value.ptr);
    }
});
Object.defineProperty(ParticleFlow.prototype, "lifetime", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleFlow__get_lifetime(self), ValueTrack_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_lifetime(self, value.ptr);
    }
});
Object.defineProperty(ParticleFlow.prototype, "gravity", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleFlow__get_gravity(self), ValueTrack_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_gravity(self, value.ptr);
    }
});
Object.defineProperty(ParticleFlow.prototype, "speed", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleFlow__get_speed(self), ValueTrack_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_speed(self, value.ptr);
    }
});
Object.defineProperty(ParticleFlow.prototype, "angle", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleFlow__get_angle(self), ValueTrack_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_angle(self, value.ptr);
    }
});
Object.defineProperty(ParticleFlow.prototype, "blend", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleFlow__get_blend(self), ValueTrack_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_blend(self, value.ptr);
    }
});
Object.defineProperty(ParticleFlow.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleFlow__get_colour(self), ValueTrack_mud_Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_colour(self, value.ptr);
    }
});
Object.defineProperty(ParticleFlow.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleFlow__get_scale(self), ValueTrack_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_scale(self, value.ptr);
    }
});
Object.defineProperty(ParticleFlow.prototype, "sprite_frame", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleFlow__get_sprite_frame(self), ValueTrack_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_sprite_frame(self, value.ptr);
    }
});
Object.defineProperty(ParticleFlow.prototype, "sprite_name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_ParticleFlow__get_sprite_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ParticleFlow__set_sprite_name(self, ensureString(value));
    }
});
ParticleFlow.prototype["__destroy__"] = ParticleFlow.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ParticleFlow__destroy(self);
};
// PbrMaterialBlock
function PbrMaterialBlock(a0, a1, a2) {
    if (a0 === undefined) { this.ptr = _mud_PbrMaterialBlock__construct_0(); this.type = PbrMaterialBlock; getCache(PbrMaterialBlock)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_PbrMaterialBlock__construct_1(/*albedo*/a0.ptr); this.type = PbrMaterialBlock; getCache(PbrMaterialBlock)[this.ptr] = this; return; }
    if (a2 === undefined) { this.ptr = _mud_PbrMaterialBlock__construct_2(/*albedo*/a0.ptr, /*metallic*/a1); this.type = PbrMaterialBlock; getCache(PbrMaterialBlock)[this.ptr] = this; return; }
    this.ptr = _mud_PbrMaterialBlock__construct_3(/*albedo*/a0.ptr, /*metallic*/a1, /*roughness*/a2); this.type = PbrMaterialBlock; getCache(PbrMaterialBlock)[this.ptr] = this;
};
PbrMaterialBlock.prototype = Object.create(WrapperObject.prototype);
PbrMaterialBlock.prototype.constructor = PbrMaterialBlock;
PbrMaterialBlock.prototype.__class__ = PbrMaterialBlock;
PbrMaterialBlock.__cache__ = {};
Module['PbrMaterialBlock'] = PbrMaterialBlock;
Object.defineProperty(PbrMaterialBlock.prototype, "enabled", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_PbrMaterialBlock__get_enabled(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_enabled(self, value);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "albedo", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PbrMaterialBlock__get_albedo(self), MaterialParam_mud_Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_albedo(self, value.ptr);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "specular", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_specular(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_specular(self, value);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "metallic", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PbrMaterialBlock__get_metallic(self), MaterialParam_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_metallic(self, value.ptr);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "roughness", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PbrMaterialBlock__get_roughness(self), MaterialParam_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_roughness(self, value.ptr);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "emissive", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PbrMaterialBlock__get_emissive(self), MaterialParam_mud_Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_emissive(self, value.ptr);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "emissive_energy", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_emissive_energy(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_emissive_energy(self, value);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "normal", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PbrMaterialBlock__get_normal(self), MaterialParam_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_normal(self, value.ptr);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "rim", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PbrMaterialBlock__get_rim(self), MaterialParam_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_rim(self, value.ptr);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "ritint", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_ritint(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_ritint(self, value);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "clearcoat", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PbrMaterialBlock__get_clearcoat(self), MaterialParam_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_clearcoat(self, value.ptr);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "clearcoat_gloss", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_clearcoat_gloss(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_clearcoat_gloss(self, value);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "anisotropy", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PbrMaterialBlock__get_anisotropy(self), MaterialParam_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_anisotropy(self, value.ptr);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "subsurface", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PbrMaterialBlock__get_subsurface(self), MaterialParam_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_subsurface(self, value.ptr);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "transmission", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PbrMaterialBlock__get_transmission(self), MaterialParam_mud_Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_transmission(self, value.ptr);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "refraction", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PbrMaterialBlock__get_refraction(self), MaterialParam_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_refraction(self, value.ptr);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "ambient_occlusion", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PbrMaterialBlock__get_ambient_occlusion(self), MaterialParam_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_ambient_occlusion(self, value.ptr);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "depth", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_PbrMaterialBlock__get_depth(self), MaterialParam_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_depth(self, value.ptr);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "deep_parallax", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_PbrMaterialBlock__get_deep_parallax(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_deep_parallax(self, value);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "diffuse_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_diffuse_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_diffuse_mode(self, value);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "specular_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_specular_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_PbrMaterialBlock__set_specular_mode(self, value);
    }
});
PbrMaterialBlock.prototype["__destroy__"] = PbrMaterialBlock.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_PbrMaterialBlock__destroy(self);
};
// Prefab
function Prefab() { throw "cannot construct a Prefab, no constructor in IDL" }
Prefab.prototype = Object.create(WrapperObject.prototype);
Prefab.prototype.constructor = Prefab;
Prefab.prototype.__class__ = Prefab;
Prefab.__cache__ = {};
Module['Prefab'] = Prefab;
Object.defineProperty(Prefab.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Prefab__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Prefab__set_name(self, ensureString(value));
    }
});
Prefab.prototype["__destroy__"] = Prefab.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Prefab__destroy(self);
};
// Program
function Program() { throw "cannot construct a Program, no constructor in IDL" }
Program.prototype = Object.create(WrapperObject.prototype);
Program.prototype.constructor = Program;
Program.prototype.__class__ = Program;
Program.__cache__ = {};
Module['Program'] = Program;
Object.defineProperty(Program.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Program__get_name(self));
    }});
Program.prototype["__destroy__"] = Program.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Program__destroy(self);
};
// Radiance
function Radiance() {
    this.ptr = _mud_Radiance__construct_0(); this.type = Radiance; getCache(Radiance)[this.ptr] = this;
};
Radiance.prototype = Object.create(WrapperObject.prototype);
Radiance.prototype.constructor = Radiance;
Radiance.prototype.__class__ = Radiance;
Radiance.__cache__ = {};
Module['Radiance'] = Radiance;
Object.defineProperty(Radiance.prototype, "energy", {
    get: function() {
        var self = this.ptr;
        return _mud_Radiance__get_energy(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Radiance__set_energy(self, value);
    }
});
Object.defineProperty(Radiance.prototype, "ambient", {
    get: function() {
        var self = this.ptr;
        return _mud_Radiance__get_ambient(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Radiance__set_ambient(self, value);
    }
});
Object.defineProperty(Radiance.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Radiance__get_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Radiance__set_colour(self, value.ptr);
    }
});
Object.defineProperty(Radiance.prototype, "texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Radiance__get_texture(self), Texture);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Radiance__set_texture(self, value.ptr);
    }
});
Radiance.prototype["__destroy__"] = Radiance.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Radiance__destroy(self);
};
// RenderFrame
function RenderFrame() {
    this.ptr = _mud_RenderFrame__construct_0(); this.type = RenderFrame; getCache(RenderFrame)[this.ptr] = this;
};
RenderFrame.prototype = Object.create(WrapperObject.prototype);
RenderFrame.prototype.constructor = RenderFrame;
RenderFrame.prototype.__class__ = RenderFrame;
RenderFrame.__cache__ = {};
Module['RenderFrame'] = RenderFrame;
RenderFrame.prototype["__destroy__"] = RenderFrame.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_RenderFrame__destroy(self);
};
// RenderQuad
function RenderQuad() {
    this.ptr = _mud_RenderQuad__construct_0(); this.type = RenderQuad; getCache(RenderQuad)[this.ptr] = this;
};
RenderQuad.prototype = Object.create(WrapperObject.prototype);
RenderQuad.prototype.constructor = RenderQuad;
RenderQuad.prototype.__class__ = RenderQuad;
RenderQuad.__cache__ = {};
Module['RenderQuad'] = RenderQuad;
RenderQuad.prototype["__destroy__"] = RenderQuad.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_RenderQuad__destroy(self);
};
// Rig
function Rig() { throw "cannot construct a Rig, no constructor in IDL" }
Rig.prototype = Object.create(WrapperObject.prototype);
Rig.prototype.constructor = Rig;
Rig.prototype.__class__ = Rig;
Rig.__cache__ = {};
Module['Rig'] = Rig;
Rig.prototype["__destroy__"] = Rig.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Rig__destroy(self);
};
// Scene
function Scene() { throw "cannot construct a Scene, no constructor in IDL" }
Scene.prototype = Object.create(WrapperObject.prototype);
Scene.prototype.constructor = Scene;
Scene.prototype.__class__ = Scene;
Scene.__cache__ = {};
Module['Scene'] = Scene;
Scene.prototype["begin"] = Scene.prototype.begin = function(self) {
    var self = this.ptr;
    return wrapPointer(_mud_Scene_begin_0(self), Gnode);
};
Object.defineProperty(Scene.prototype, "graph", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Scene__get_graph(self), Gnode);
    }});
Object.defineProperty(Scene.prototype, "root_node", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Scene__get_root_node(self), Node3);
    }});
Object.defineProperty(Scene.prototype, "environment", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Scene__get_environment(self), Environment);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Scene__set_environment(self, value.ptr);
    }
});
Object.defineProperty(Scene.prototype, "user", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Scene__get_user(self), Ref);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Scene__set_user(self, ensureRef(value), ensureRefType(value));
    }
});
Scene.prototype["__destroy__"] = Scene.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Scene__destroy(self);
};
// Shot
function Shot() { throw "cannot construct a Shot, no constructor in IDL" }
Shot.prototype = Object.create(WrapperObject.prototype);
Shot.prototype.constructor = Shot;
Shot.prototype.__class__ = Shot;
Shot.__cache__ = {};
Module['Shot'] = Shot;
Shot.prototype["__destroy__"] = Shot.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Shot__destroy(self);
};
// Skeleton
function Skeleton() { throw "cannot construct a Skeleton, no constructor in IDL" }
Skeleton.prototype = Object.create(WrapperObject.prototype);
Skeleton.prototype.constructor = Skeleton;
Skeleton.prototype.__class__ = Skeleton;
Skeleton.__cache__ = {};
Module['Skeleton'] = Skeleton;
Skeleton.prototype["__destroy__"] = Skeleton.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Skeleton__destroy(self);
};
// Skin
function Skin() { throw "cannot construct a Skin, no constructor in IDL" }
Skin.prototype = Object.create(WrapperObject.prototype);
Skin.prototype.constructor = Skin;
Skin.prototype.__class__ = Skin;
Skin.__cache__ = {};
Module['Skin'] = Skin;
Skin.prototype["__destroy__"] = Skin.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Skin__destroy(self);
};
// Sun
function Sun() {
    this.ptr = _mud_Sun__construct_0(); this.type = Sun; getCache(Sun)[this.ptr] = this;
};
Sun.prototype = Object.create(WrapperObject.prototype);
Sun.prototype.constructor = Sun;
Sun.prototype.__class__ = Sun;
Sun.__cache__ = {};
Module['Sun'] = Sun;
Object.defineProperty(Sun.prototype, "azimuth", {
    get: function() {
        var self = this.ptr;
        return _mud_Sun__get_azimuth(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Sun__set_azimuth(self, value);
    }
});
Object.defineProperty(Sun.prototype, "elevation", {
    get: function() {
        var self = this.ptr;
        return _mud_Sun__get_elevation(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Sun__set_elevation(self, value);
    }
});
Object.defineProperty(Sun.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Sun__get_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Sun__set_colour(self, value.ptr);
    }
});
Object.defineProperty(Sun.prototype, "intensity", {
    get: function() {
        var self = this.ptr;
        return _mud_Sun__get_intensity(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Sun__set_intensity(self, value);
    }
});
Sun.prototype["__destroy__"] = Sun.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Sun__destroy(self);
};
// SymbolIndex
function SymbolIndex() { throw "cannot construct a SymbolIndex, no constructor in IDL" }
SymbolIndex.prototype = Object.create(WrapperObject.prototype);
SymbolIndex.prototype.constructor = SymbolIndex;
SymbolIndex.prototype.__class__ = SymbolIndex;
SymbolIndex.__cache__ = {};
Module['SymbolIndex'] = SymbolIndex;
SymbolIndex.prototype["__destroy__"] = SymbolIndex.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_SymbolIndex__destroy(self);
};
// Texture
function Texture() { throw "cannot construct a Texture, no constructor in IDL" }
Texture.prototype = Object.create(WrapperObject.prototype);
Texture.prototype.constructor = Texture;
Texture.prototype.__class__ = Texture;
Texture.__cache__ = {};
Module['Texture'] = Texture;
Object.defineProperty(Texture.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Texture__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Texture__set_name(self, ensureString(value));
    }
});
Object.defineProperty(Texture.prototype, "width", {
    get: function() {
        var self = this.ptr;
        return _mud_Texture__get_width(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Texture__set_width(self, value);
    }
});
Object.defineProperty(Texture.prototype, "height", {
    get: function() {
        var self = this.ptr;
        return _mud_Texture__get_height(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Texture__set_height(self, value);
    }
});
Object.defineProperty(Texture.prototype, "bits_per_pixel", {
    get: function() {
        var self = this.ptr;
        return _mud_Texture__get_bits_per_pixel(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Texture__set_bits_per_pixel(self, value);
    }
});
Texture.prototype["__destroy__"] = Texture.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Texture__destroy(self);
};
// UnshadedMaterialBlock
function UnshadedMaterialBlock() {
    this.ptr = _mud_UnshadedMaterialBlock__construct_0(); this.type = UnshadedMaterialBlock; getCache(UnshadedMaterialBlock)[this.ptr] = this;
};
UnshadedMaterialBlock.prototype = Object.create(WrapperObject.prototype);
UnshadedMaterialBlock.prototype.constructor = UnshadedMaterialBlock;
UnshadedMaterialBlock.prototype.__class__ = UnshadedMaterialBlock;
UnshadedMaterialBlock.__cache__ = {};
Module['UnshadedMaterialBlock'] = UnshadedMaterialBlock;
Object.defineProperty(UnshadedMaterialBlock.prototype, "enabled", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_UnshadedMaterialBlock__get_enabled(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_UnshadedMaterialBlock__set_enabled(self, value);
    }
});
Object.defineProperty(UnshadedMaterialBlock.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_UnshadedMaterialBlock__get_colour(self), MaterialParam_mud_Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_UnshadedMaterialBlock__set_colour(self, value.ptr);
    }
});
UnshadedMaterialBlock.prototype["__destroy__"] = UnshadedMaterialBlock.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_UnshadedMaterialBlock__destroy(self);
};
// Viewport
function Viewport() { throw "cannot construct a Viewport, no constructor in IDL" }
Viewport.prototype = Object.create(WrapperObject.prototype);
Viewport.prototype.constructor = Viewport;
Viewport.prototype.__class__ = Viewport;
Viewport.__cache__ = {};
Module['Viewport'] = Viewport;
Object.defineProperty(Viewport.prototype, "camera", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewport__get_camera(self), Camera);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Viewport__set_camera(self, value.ptr);
    }
});
Object.defineProperty(Viewport.prototype, "scene", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewport__get_scene(self), Scene);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Viewport__set_scene(self, value.ptr);
    }
});
Object.defineProperty(Viewport.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Viewport__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Viewport__set_index(self, value);
    }
});
Object.defineProperty(Viewport.prototype, "active", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Viewport__get_active(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Viewport__set_active(self, value);
    }
});
Object.defineProperty(Viewport.prototype, "rect", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewport__get_rect(self), v4_uint);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Viewport__set_rect(self, value.ptr);
    }
});
Object.defineProperty(Viewport.prototype, "scissor", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Viewport__get_scissor(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Viewport__set_scissor(self, value);
    }
});
Object.defineProperty(Viewport.prototype, "clear_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewport__get_clear_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Viewport__set_clear_colour(self, value.ptr);
    }
});
Object.defineProperty(Viewport.prototype, "shading", {
    get: function() {
        var self = this.ptr;
        return _mud_Viewport__get_shading(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Viewport__set_shading(self, value);
    }
});
Object.defineProperty(Viewport.prototype, "lighting", {
    get: function() {
        var self = this.ptr;
        return _mud_Viewport__get_lighting(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Viewport__set_lighting(self, value);
    }
});
Viewport.prototype["__destroy__"] = Viewport.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Viewport__destroy(self);
};
// BlockCopy
function BlockCopy() { throw "cannot construct a BlockCopy, no constructor in IDL" }
BlockCopy.prototype = Object.create(GfxBlock.prototype);
BlockCopy.prototype.constructor = BlockCopy;
BlockCopy.prototype.__class__ = BlockCopy;
BlockCopy.__cache__ = {};
Module['BlockCopy'] = BlockCopy;
BlockCopy.prototype["__destroy__"] = BlockCopy.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockCopy__destroy(self);
};
// BlockFilter
function BlockFilter() { throw "cannot construct a BlockFilter, no constructor in IDL" }
BlockFilter.prototype = Object.create(GfxBlock.prototype);
BlockFilter.prototype.constructor = BlockFilter;
BlockFilter.prototype.__class__ = BlockFilter;
BlockFilter.__cache__ = {};
Module['BlockFilter'] = BlockFilter;
BlockFilter.prototype["__destroy__"] = BlockFilter.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockFilter__destroy(self);
};
// BlockParticles
function BlockParticles() { throw "cannot construct a BlockParticles, no constructor in IDL" }
BlockParticles.prototype = Object.create(GfxBlock.prototype);
BlockParticles.prototype.constructor = BlockParticles;
BlockParticles.prototype.__class__ = BlockParticles;
BlockParticles.__cache__ = {};
Module['BlockParticles'] = BlockParticles;
BlockParticles.prototype["__destroy__"] = BlockParticles.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockParticles__destroy(self);
};
// BlockResolve
function BlockResolve() { throw "cannot construct a BlockResolve, no constructor in IDL" }
BlockResolve.prototype = Object.create(GfxBlock.prototype);
BlockResolve.prototype.constructor = BlockResolve;
BlockResolve.prototype.__class__ = BlockResolve;
BlockResolve.__cache__ = {};
Module['BlockResolve'] = BlockResolve;
BlockResolve.prototype["__destroy__"] = BlockResolve.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockResolve__destroy(self);
};
// BlockSky
function BlockSky() { throw "cannot construct a BlockSky, no constructor in IDL" }
BlockSky.prototype = Object.create(GfxBlock.prototype);
BlockSky.prototype.constructor = BlockSky;
BlockSky.prototype.__class__ = BlockSky;
BlockSky.__cache__ = {};
Module['BlockSky'] = BlockSky;
BlockSky.prototype["__destroy__"] = BlockSky.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockSky__destroy(self);
};
// ClusteredFrustum
function ClusteredFrustum() {
    this.ptr = _mud_ClusteredFrustum__construct_0(); this.type = ClusteredFrustum; getCache(ClusteredFrustum)[this.ptr] = this;
};
ClusteredFrustum.prototype = Object.create(Frustum.prototype);
ClusteredFrustum.prototype.constructor = ClusteredFrustum;
ClusteredFrustum.prototype.__class__ = ClusteredFrustum;
ClusteredFrustum.__cache__ = {};
Module['ClusteredFrustum'] = ClusteredFrustum;
ClusteredFrustum.prototype["__destroy__"] = ClusteredFrustum.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ClusteredFrustum__destroy(self);
};
// DrawBlock
function DrawBlock() { throw "cannot construct a DrawBlock, no constructor in IDL" }
DrawBlock.prototype = Object.create(GfxBlock.prototype);
DrawBlock.prototype.constructor = DrawBlock;
DrawBlock.prototype.__class__ = DrawBlock;
DrawBlock.__cache__ = {};
Module['DrawBlock'] = DrawBlock;
DrawBlock.prototype["__destroy__"] = DrawBlock.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_DrawBlock__destroy(self);
};
// BlockDepth
function BlockDepth() { throw "cannot construct a BlockDepth, no constructor in IDL" }
BlockDepth.prototype = Object.create(DrawBlock.prototype);
BlockDepth.prototype.constructor = BlockDepth;
BlockDepth.prototype.__class__ = BlockDepth;
BlockDepth.__cache__ = {};
Module['BlockDepth'] = BlockDepth;
BlockDepth.prototype["__destroy__"] = BlockDepth.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockDepth__destroy(self);
};
// Particles
function Particles() {
    this.ptr = _mud_Particles__construct_0(); this.type = Particles; getCache(Particles)[this.ptr] = this;
};
Particles.prototype = Object.create(ParticleFlow.prototype);
Particles.prototype.constructor = Particles;
Particles.prototype.__class__ = Particles;
Particles.__cache__ = {};
Module['Particles'] = Particles;
Object.defineProperty(Particles.prototype, "node", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Particles__get_node(self), Node3);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Particles__set_node(self, value.ptr);
    }
});
Particles.prototype["__destroy__"] = Particles.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Particles__destroy(self);
};
// RenderTarget
function RenderTarget() { throw "cannot construct a RenderTarget, no constructor in IDL" }
RenderTarget.prototype = Object.create(FrameBuffer.prototype);
RenderTarget.prototype.constructor = RenderTarget;
RenderTarget.prototype.__class__ = RenderTarget;
RenderTarget.__cache__ = {};
Module['RenderTarget'] = RenderTarget;
RenderTarget.prototype["__destroy__"] = RenderTarget.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_RenderTarget__destroy(self);
};
Module['gfx']['update_item_lights'] = function(a0) {
    var self = this.ptr;
    _mud_gfx_update_item_lights_1(/*item*/a0.ptr);
};
Module['gfx']['update_item_aabb'] = function(a0) {
    var self = this.ptr;
    _mud_gfx_update_item_aabb_1(/*item*/a0.ptr);
};
Module['gfx']['node'] = function(a0, a1, a2, a3, a4) {
    var self = this.ptr;
    if (a1 === undefined) { return wrapPointer(_mud_gfx_node_1(/*parent*/a0.ptr), Gnode); }
    if (a2 === undefined) { return wrapPointer(_mud_gfx_node_2(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)), Gnode); }
    if (a3 === undefined) { return wrapPointer(_mud_gfx_node_3(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1), /*position*/a2.ptr), Gnode); }
    if (a4 === undefined) { return wrapPointer(_mud_gfx_node_4(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1), /*position*/a2.ptr, /*rotation*/a3.ptr), Gnode); }
    return wrapPointer(_mud_gfx_node_5(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1), /*position*/a2.ptr, /*rotation*/a3.ptr, /*scale*/a4.ptr), Gnode);
};
Module['gfx']['shape'] = function(a0, a1, a2, a3, a4, a5) {
    var self = this.ptr;
    if (a3 === undefined) { return wrapPointer(_mud_gfx_shape_3(/*parent*/a0.ptr, /*shape*/a1.ptr, /*symbol*/a2.ptr), Item); }
    if (a4 === undefined) { return wrapPointer(_mud_gfx_shape_4(/*parent*/a0.ptr, /*shape*/a1.ptr, /*symbol*/a2.ptr, /*flags*/a3), Item); }
    if (a5 === undefined) { return wrapPointer(_mud_gfx_shape_5(/*parent*/a0.ptr, /*shape*/a1.ptr, /*symbol*/a2.ptr, /*flags*/a3, /*material*/a4.ptr), Item); }
    return wrapPointer(_mud_gfx_shape_6(/*parent*/a0.ptr, /*shape*/a1.ptr, /*symbol*/a2.ptr, /*flags*/a3, /*material*/a4.ptr, /*instances*/a5), Item);
};
Module['gfx']['draw'] = function(a0, a1, a2, a3) {
    var self = this.ptr;
    if (a3 === undefined) { _mud_gfx_draw_3(/*parent*/a0.ptr, /*shape*/a1.ptr, /*symbol*/a2.ptr); return; }
    _mud_gfx_draw_4(/*parent*/a0.ptr, /*shape*/a1.ptr, /*symbol*/a2.ptr, /*flags*/a3);
};
Module['gfx']['sprite'] = function(a0, a1, a2, a3, a4, a5) {
    var self = this.ptr;
    if (a3 === undefined) { return wrapPointer(_mud_gfx_sprite_3(/*parent*/a0.ptr, /*image*/a1.ptr, /*size*/a2.ptr), Item); }
    if (a4 === undefined) { return wrapPointer(_mud_gfx_sprite_4(/*parent*/a0.ptr, /*image*/a1.ptr, /*size*/a2.ptr, /*flags*/a3), Item); }
    if (a5 === undefined) { return wrapPointer(_mud_gfx_sprite_5(/*parent*/a0.ptr, /*image*/a1.ptr, /*size*/a2.ptr, /*flags*/a3, /*material*/a4.ptr), Item); }
    return wrapPointer(_mud_gfx_sprite_6(/*parent*/a0.ptr, /*image*/a1.ptr, /*size*/a2.ptr, /*flags*/a3, /*material*/a4.ptr, /*instances*/a5), Item);
};
Module['gfx']['model'] = function(a0, a1, a2, a3, a4) {
    var self = this.ptr;
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_gfx_model_2(/*parent*/a0.ptr, ensureString(/*name*/a1)), Item); }
    if (a3 === undefined) { return wrapPointer(_mud_gfx_model_3(/*parent*/a0.ptr, ensureString(/*name*/a1), /*flags*/a2), Item); }
    if (a4 === undefined) { return wrapPointer(_mud_gfx_model_4(/*parent*/a0.ptr, ensureString(/*name*/a1), /*flags*/a2, /*material*/a3.ptr), Item); }
    return wrapPointer(_mud_gfx_model_5(/*parent*/a0.ptr, ensureString(/*name*/a1), /*flags*/a2, /*material*/a3.ptr, /*instances*/a4), Item);
};
Module['gfx']['animated'] = function(a0, a1) {
    var self = this.ptr;
    return wrapPointer(_mud_gfx_animated_2(/*parent*/a0.ptr, /*item*/a1.ptr), Animated);
};
Module['gfx']['particles'] = function(a0, a1, a2, a3) {
    var self = this.ptr;
    if (a2 === undefined) { return wrapPointer(_mud_gfx_particles_2(/*parent*/a0.ptr, /*emitter*/a1.ptr), Particles); }
    if (a3 === undefined) { return wrapPointer(_mud_gfx_particles_3(/*parent*/a0.ptr, /*emitter*/a1.ptr, /*flags*/a2), Particles); }
    return wrapPointer(_mud_gfx_particles_4(/*parent*/a0.ptr, /*emitter*/a1.ptr, /*flags*/a2, /*instances*/a3), Particles);
};
Module['gfx']['light'] = function(a0, a1, a2, a3, a4, a5) {
    var self = this.ptr;
    if (a4 === undefined) { return wrapPointer(_mud_gfx_light_4(/*parent*/a0.ptr, /*type*/a1, /*shadows*/a2, /*colour*/a3.ptr), Light); }
    if (a5 === undefined) { return wrapPointer(_mud_gfx_light_5(/*parent*/a0.ptr, /*type*/a1, /*shadows*/a2, /*colour*/a3.ptr, /*range*/a4), Light); }
    return wrapPointer(_mud_gfx_light_6(/*parent*/a0.ptr, /*type*/a1, /*shadows*/a2, /*colour*/a3.ptr, /*range*/a4, /*attenuation*/a5), Light);
};
Module['gfx']['sun_light'] = function(a0, a1, a2) {
    var self = this.ptr;
    return wrapPointer(_mud_gfx_sun_light_3(/*parent*/a0.ptr, /*azimuth*/a1, /*elevation*/a2), Light);
};
Module['gfx']['radiance'] = function(a0, a1, a2) {
    var self = this.ptr;
    ensureCache.prepare();
    _mud_gfx_radiance_3(/*parent*/a0.ptr, ensureString(/*texture*/a1), /*background*/a2);
};

(function() {
    function setup() {
        Animated.__type__ = _mud_Animated__type();
        AnimatedTrack.__type__ = _mud_AnimatedTrack__type();
        Animation.__type__ = _mud_Animation__type();
        AnimationPlay.__type__ = _mud_AnimationPlay__type();
        AnimationTrack.__type__ = _mud_AnimationTrack__type();
        Background.__type__ = _mud_Background__type();
        BaseMaterialBlock.__type__ = _mud_BaseMaterialBlock__type();
        Bone.__type__ = _mud_Bone__type();
        Camera.__type__ = _mud_Camera__type();
        Culler.__type__ = _mud_Culler__type();
        DepthParams.__type__ = _mud_DepthParams__type();
        Environment.__type__ = _mud_Environment__type();
        Filter.__type__ = _mud_Filter__type();
        Fog.__type__ = _mud_Fog__type();
        FrameBuffer.__type__ = _mud_FrameBuffer__type();
        FresnelMaterialBlock.__type__ = _mud_FresnelMaterialBlock__type();
        Frustum.__type__ = _mud_Frustum__type();
        FrustumSlice.__type__ = _mud_FrustumSlice__type();
        GfxBlock.__type__ = _mud_GfxBlock__type();
        GfxContext.__type__ = _mud_GfxContext__type();
        GfxSystem.__type__ = _mud_GfxSystem__type();
        Gnode.__type__ = _mud_Gnode__type();
        ImmediateDraw.__type__ = _mud_ImmediateDraw__type();
        ImportConfig.__type__ = _mud_ImportConfig__type();
        Item.__type__ = _mud_Item__type();
        Joint.__type__ = _mud_Joint__type();
        Light.__type__ = _mud_Light__type();
        Material.__type__ = _mud_Material__type();
        Mesh.__type__ = _mud_Mesh__type();
        Model.__type__ = _mud_Model__type();
        ModelItem.__type__ = _mud_ModelItem__type();
        Node3.__type__ = _mud_Node3__type();
        ParticleFlow.__type__ = _mud_ParticleFlow__type();
        PbrMaterialBlock.__type__ = _mud_PbrMaterialBlock__type();
        Prefab.__type__ = _mud_Prefab__type();
        Program.__type__ = _mud_Program__type();
        Radiance.__type__ = _mud_Radiance__type();
        RenderFrame.__type__ = _mud_RenderFrame__type();
        RenderQuad.__type__ = _mud_RenderQuad__type();
        Rig.__type__ = _mud_Rig__type();
        Scene.__type__ = _mud_Scene__type();
        Shot.__type__ = _mud_Shot__type();
        Skeleton.__type__ = _mud_Skeleton__type();
        Skin.__type__ = _mud_Skin__type();
        Sun.__type__ = _mud_Sun__type();
        SymbolIndex.__type__ = _mud_SymbolIndex__type();
        Texture.__type__ = _mud_Texture__type();
        UnshadedMaterialBlock.__type__ = _mud_UnshadedMaterialBlock__type();
        Viewport.__type__ = _mud_Viewport__type();
        BlockCopy.__type__ = _mud_BlockCopy__type();
        BlockFilter.__type__ = _mud_BlockFilter__type();
        BlockParticles.__type__ = _mud_BlockParticles__type();
        BlockResolve.__type__ = _mud_BlockResolve__type();
        BlockSky.__type__ = _mud_BlockSky__type();
        ClusteredFrustum.__type__ = _mud_ClusteredFrustum__type();
        DrawBlock.__type__ = _mud_DrawBlock__type();
        BlockDepth.__type__ = _mud_BlockDepth__type();
        Particles.__type__ = _mud_Particles__type();
        RenderTarget.__type__ = _mud_RenderTarget__type();
        // AnimationTarget
        Module['AnimationTarget'] = Module['AnimationTarget'] || {};
        Module['AnimationTarget']['Position'] = _mud_AnimationTarget_Position();
        Module['AnimationTarget']['Rotation'] = _mud_AnimationTarget_Rotation();
        Module['AnimationTarget']['Scale'] = _mud_AnimationTarget_Scale();
        // BackgroundMode
        Module['BackgroundMode'] = Module['BackgroundMode'] || {};
        Module['BackgroundMode']['None'] = _mud_BackgroundMode_None();
        Module['BackgroundMode']['Panorama'] = _mud_BackgroundMode_Panorama();
        Module['BackgroundMode']['Radiance'] = _mud_BackgroundMode_Radiance();
        Module['BackgroundMode']['Custom'] = _mud_BackgroundMode_Custom();
        // BlendMode
        Module['BlendMode'] = Module['BlendMode'] || {};
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
        // DepthDraw
        Module['DepthDraw'] = Module['DepthDraw'] || {};
        Module['DepthDraw']['Enabled'] = _mud_DepthDraw_Enabled();
        Module['DepthDraw']['Disabled'] = _mud_DepthDraw_Disabled();
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
        // MaterialFlag
        Module['MaterialFlag'] = Module['MaterialFlag'] || {};
        Module['MaterialFlag']['TriplanarUV1'] = _mud_MaterialFlag_TriplanarUV1();
        Module['MaterialFlag']['TriplanarUV2'] = _mud_MaterialFlag_TriplanarUV2();
        Module['MaterialFlag']['Count'] = _mud_MaterialFlag_Count();
        // ModelFormat
        Module['ModelFormat'] = Module['ModelFormat'] || {};
        Module['ModelFormat']['obj'] = _mud_ModelFormat_obj();
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
        Module['Shading']['Unshaded'] = _mud_Shading_Unshaded();
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
        Module['TextureSampler']['Metallic'] = _mud_TextureSampler_Metallic();
        Module['TextureSampler']['Roughness'] = _mud_TextureSampler_Roughness();
        Module['TextureSampler']['Emissive'] = _mud_TextureSampler_Emissive();
        Module['TextureSampler']['Normal'] = _mud_TextureSampler_Normal();
        Module['TextureSampler']['AO'] = _mud_TextureSampler_AO();
        Module['TextureSampler']['Depth'] = _mud_TextureSampler_Depth();
        Module['TextureSampler']['Skeleton'] = _mud_TextureSampler_Skeleton();
        Module['TextureSampler']['ShadowCSM'] = _mud_TextureSampler_ShadowCSM();
        Module['TextureSampler']['ShadowAtlas'] = _mud_TextureSampler_ShadowAtlas();
        Module['TextureSampler']['Radiance'] = _mud_TextureSampler_Radiance();
        Module['TextureSampler']['ReflectionProbe'] = _mud_TextureSampler_ReflectionProbe();
        Module['TextureSampler']['GIProbe'] = _mud_TextureSampler_GIProbe();
        Module['TextureSampler']['Lights'] = _mud_TextureSampler_Lights();
        Module['TextureSampler']['Clusters'] = _mud_TextureSampler_Clusters();
        Module['TextureSampler']['LightRecords'] = _mud_TextureSampler_LightRecords();
        Module['TextureSampler']['Lightmap'] = _mud_TextureSampler_Lightmap();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
