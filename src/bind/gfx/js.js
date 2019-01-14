Module['glm'] = Module['glm'] || {};
Module['gfx'] = Module['gfx'] || {};
Module['ui'] = Module['ui'] || {};
// Animated
function Animated() { throw "cannot construct a Animated, no constructor in IDL" }
Animated.prototype = Object.create(WrapperObject.prototype);
Animated.prototype.constructor = Animated;
Animated.prototype.__class__ = Animated;
Animated.__cache__ = {};
Module['Animated'] = Animated;
Animated.prototype["advance"] = Animated.prototype.advance = function(self, time) {
    var self = this.ptr;
    /* time <float> [] */
    _mud_Animated_advance_1(self, time);
};
Animated.prototype["next_animation"] = Animated.prototype.next_animation = function(self) {
    var self = this.ptr;
    _mud_Animated_next_animation_0(self);
};
Animated.prototype["pause"] = Animated.prototype.pause = function(self) {
    var self = this.ptr;
    _mud_Animated_pause_0(self);
};
Animated.prototype["play"] = Animated.prototype.play = function(self, animation, loop, blend, speed, transient) {
    var self = this.ptr;
    /* animation <Animation> [] */
    animation = animation.ptr;
    /* loop <bool> [] */
    /* blend <float> [] */
    /* speed <float> [] */
    /* transient <bool> [] */
    if (blend === undefined) { _mud_Animated_play_2(self, animation, loop); return; }
    if (speed === undefined) { _mud_Animated_play_3(self, animation, loop, blend); return; }
    if (transient === undefined) { _mud_Animated_play_4(self, animation, loop, blend, speed); return; }
    _mud_Animated_play_5(self, animation, loop, blend, speed, transient);
};
Animated.prototype["playing"] = Animated.prototype.playing = function(self) {
    var self = this.ptr;
    return Pointer_stringify(_mud_Animated_playing_0(self));
};
Animated.prototype["seek"] = Animated.prototype.seek = function(self, time) {
    var self = this.ptr;
    /* time <float> [] */
    _mud_Animated_seek_1(self, time);
};
Animated.prototype["start"] = Animated.prototype.start = function(self, animation, loop, blend, speed, transient) {
    var self = this.ptr;
    /* animation <const char*> [] */
    if (animation && typeof animation === "object") animation = animation.ptr;
    else animation = ensureString(animation);
    /* loop <bool> [] */
    /* blend <float> [] */
    /* speed <float> [] */
    /* transient <bool> [] */
    if (blend === undefined) { _mud_Animated_start_2(self, animation, loop); return; }
    if (speed === undefined) { _mud_Animated_start_3(self, animation, loop, blend); return; }
    if (transient === undefined) { _mud_Animated_start_4(self, animation, loop, blend, speed); return; }
    _mud_Animated_start_5(self, animation, loop, blend, speed, transient);
};
Animated.prototype["stop"] = Animated.prototype.stop = function(self) {
    var self = this.ptr;
    _mud_Animated_stop_0(self);
};
Object.defineProperty(Animated.prototype, "active", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Animated__get_active(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
        _mud_Animated__set_default_blend_time(self, value);
    }
});
Animated.prototype["__destroy__"] = Animated.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Animated__destroy(self);
};
// AnimatedTrack
function AnimatedTrack() {
    this.ptr = _mud_AnimatedTrack_AnimatedTrack_0(); getCache(AnimatedTrack)[this.ptr] = this;
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
        /* value <std::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_Animation__set_name(self, value);
    }
});
Object.defineProperty(Animation.prototype, "length", {
    get: function() {
        var self = this.ptr;
        return _mud_Animation__get_length(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
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
        /* value <float> [] */
        _mud_Animation__set_step(self, value);
    }
});
Animation.prototype["__destroy__"] = Animation.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Animation__destroy(self);
};
// AnimationPlay
function AnimationPlay() {
    this.ptr = _mud_AnimationPlay_AnimationPlay_0(); getCache(AnimationPlay)[this.ptr] = this;
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
        /* value <Animation> [] */
        value = value.ptr;
        _mud_AnimationPlay__set_animation(self, value);
    }
});
Object.defineProperty(AnimationPlay.prototype, "loop", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_AnimationPlay__get_loop(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
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
        /* value <float> [] */
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
        /* value <bool> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <bool> [] */
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
        /* value <Animation> [] */
        value = value.ptr;
        _mud_AnimationTrack__set_animation(self, value);
    }
});
Object.defineProperty(AnimationTrack.prototype, "node", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationTrack__get_node(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <size_t> [] */
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
        /* value <std::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_AnimationTrack__set_node_name(self, value);
    }
});
Object.defineProperty(AnimationTrack.prototype, "target", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationTrack__get_target(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <AnimationTarget> [] */
        if (value && typeof value === "object") value = value.ptr;
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
        /* value <Type> [] */
        value = value.ptr;
        _mud_AnimationTrack__set_value_type(self, value);
    }
});
Object.defineProperty(AnimationTrack.prototype, "length", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationTrack__get_length(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
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
        /* value <Interpolation> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_AnimationTrack__set_interpolation(self, value);
    }
});
AnimationTrack.prototype["__destroy__"] = AnimationTrack.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AnimationTrack__destroy(self);
};
// Background
function Background() {
    this.ptr = _mud_Background_Background_0(); getCache(Background)[this.ptr] = this;
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
        /* value <BackgroundMode> [] */
        if (value && typeof value === "object") value = value.ptr;
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
        /* value <Colour> [] */
        value = value.ptr;
        _mud_Background__set_colour(self, value);
    }
});
Object.defineProperty(Background.prototype, "custoprogram", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Background__get_custoprogram(self), Program);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Program> [] */
        value = value.ptr;
        _mud_Background__set_custoprogram(self, value);
    }
});
Background.prototype["__destroy__"] = Background.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Background__destroy(self);
};
// BaseMaterialBlock
function BaseMaterialBlock() {
    this.ptr = _mud_BaseMaterialBlock_BaseMaterialBlock_0(); getCache(BaseMaterialBlock)[this.ptr] = this;
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
        /* value <BlendMode> [] */
        if (value && typeof value === "object") value = value.ptr;
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
        /* value <CullMode> [] */
        if (value && typeof value === "object") value = value.ptr;
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
        /* value <DepthDraw> [] */
        if (value && typeof value === "object") value = value.ptr;
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
        /* value <DepthTest> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_BaseMaterialBlock__set_depth_test(self, value);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "uv0_scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_BaseMaterialBlock__get_uv0_scale(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_BaseMaterialBlock__set_uv0_scale(self, value);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "uv0_offset", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_BaseMaterialBlock__get_uv0_offset(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_BaseMaterialBlock__set_uv0_offset(self, value);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "uv1_scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_BaseMaterialBlock__get_uv1_scale(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_BaseMaterialBlock__set_uv1_scale(self, value);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "uv1_offset", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_BaseMaterialBlock__get_uv1_offset(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_BaseMaterialBlock__set_uv1_offset(self, value);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "is_alpha", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_BaseMaterialBlock__get_is_alpha(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
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
        /* value <bool> [] */
        _mud_BaseMaterialBlock__set_screen_filter(self, value);
    }
});
BaseMaterialBlock.prototype["__destroy__"] = BaseMaterialBlock.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BaseMaterialBlock__destroy(self);
};
// Bone
function Bone() {
    this.ptr = _mud_Bone_Bone_0(); getCache(Bone)[this.ptr] = this;
};
Bone.prototype = Object.create(WrapperObject.prototype);
Bone.prototype.constructor = Bone;
Bone.prototype.__class__ = Bone;
Bone.__cache__ = {};
Module['Bone'] = Bone;
Object.defineProperty(Bone.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Bone__get_position(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _mud_Bone__set_position(self, value);
    }
});
Object.defineProperty(Bone.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Bone__get_rotation(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <quat> [] */
        value = value.ptr;
        _mud_Bone__set_rotation(self, value);
    }
});
Object.defineProperty(Bone.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Bone__get_scale(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _mud_Bone__set_scale(self, value);
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
        return wrapPointer(_mud_Camera__get_eye(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _mud_Camera__set_eye(self, value);
    }
});
Object.defineProperty(Camera.prototype, "target", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Camera__get_target(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _mud_Camera__set_target(self, value);
    }
});
Object.defineProperty(Camera.prototype, "transform", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Camera__get_transform(self), mat4);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mat4> [] */
        value = value.ptr;
        _mud_Camera__set_transform(self, value);
    }
});
Object.defineProperty(Camera.prototype, "projection", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Camera__get_projection(self), mat4);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mat4> [] */
        value = value.ptr;
        _mud_Camera__set_projection(self, value);
    }
});
Object.defineProperty(Camera.prototype, "fov", {
    get: function() {
        var self = this.ptr;
        return _mud_Camera__get_fov(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <bool> [] */
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
        /* value <float> [] */
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
        /* value <bool> [] */
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
        /* value <bool> [] */
        _mud_Camera__set_clustered(self, value);
    }
});
Object.defineProperty(Camera.prototype, "lod_offsets", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Camera__get_lod_offsets(self), vec4);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec4> [] */
        value = value.ptr;
        _mud_Camera__set_lod_offsets(self, value);
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
        /* value <Viewport> [] */
        value = value.ptr;
        _mud_Culler__set_viewport(self, value);
    }
});
Culler.prototype["__destroy__"] = Culler.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Culler__destroy(self);
};
// DepthParams
function DepthParams() {
    this.ptr = _mud_DepthParams_DepthParams_0(); getCache(DepthParams)[this.ptr] = this;
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
    this.ptr = _mud_Environment_Environment_0(); getCache(Environment)[this.ptr] = this;
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
        /* value <Background> [] */
        value = value.ptr;
        _mud_Environment__set_background(self, value);
    }
});
Object.defineProperty(Environment.prototype, "radiance", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Environment__get_radiance(self), Radiance);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Radiance> [] */
        value = value.ptr;
        _mud_Environment__set_radiance(self, value);
    }
});
Object.defineProperty(Environment.prototype, "sun", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Environment__get_sun(self), Sun);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Sun> [] */
        value = value.ptr;
        _mud_Environment__set_sun(self, value);
    }
});
Object.defineProperty(Environment.prototype, "fog", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Environment__get_fog(self), Fog);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Fog> [] */
        value = value.ptr;
        _mud_Environment__set_fog(self, value);
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
    this.ptr = _mud_Fog_Fog_0(); getCache(Fog)[this.ptr] = this;
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
        /* value <bool> [] */
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
        /* value <float> [] */
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
        /* value <Colour> [] */
        value = value.ptr;
        _mud_Fog__set_colour(self, value);
    }
});
Object.defineProperty(Fog.prototype, "depth", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Fog__get_depth(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <bool> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <bool> [] */
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
        /* value <float> [] */
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
    this.ptr = _mud_FresnelMaterialBlock_FresnelMaterialBlock_0(); getCache(FresnelMaterialBlock)[this.ptr] = this;
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
        /* value <bool> [] */
        _mud_FresnelMaterialBlock__set_enabled(self, value);
    }
});
Object.defineProperty(FresnelMaterialBlock.prototype, "fresnel_scale", {
    get: function() {
        var self = this.ptr;
        return _mud_FresnelMaterialBlock__get_fresnel_scale(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
        _mud_Frustum__set_far(self, value);
    }
});
Object.defineProperty(Frustum.prototype, "center", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Frustum__get_center(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _mud_Frustum__set_center(self, value);
    }
});
Object.defineProperty(Frustum.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Frustum__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Frustum__set_radius(self, value);
    }
});
Frustum.prototype["__destroy__"] = Frustum.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Frustum__destroy(self);
};
// FrustumSlice
function FrustumSlice() {
    this.ptr = _mud_FrustumSlice_FrustumSlice_0(); getCache(FrustumSlice)[this.ptr] = this;
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
        /* value <uint8_t> [] */
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
function GfxSystem(resource_path) {
    /* resource_path <const char*> [] */
    if (resource_path && typeof resource_path === "object") resource_path = resource_path.ptr;
    else resource_path = ensureString(resource_path);
    this.ptr = _mud_GfxSystem_GfxSystem_1(resource_path); getCache(GfxSystem)[this.ptr] = this;
};
GfxSystem.prototype = Object.create(WrapperObject.prototype);
GfxSystem.prototype.constructor = GfxSystem;
GfxSystem.prototype.__class__ = GfxSystem;
GfxSystem.__cache__ = {};
Module['GfxSystem'] = GfxSystem;
GfxSystem.prototype["add_resource_path"] = GfxSystem.prototype.add_resource_path = function(self, path, relative) {
    var self = this.ptr;
    /* path <const char*> [] */
    if (path && typeof path === "object") path = path.ptr;
    else path = ensureString(path);
    /* relative <bool> [] */
    if (relative === undefined) { _mud_GfxSystem_add_resource_path_1(self, path); return; }
    _mud_GfxSystem_add_resource_path_2(self, path, relative);
};
GfxSystem.prototype["debug_material"] = GfxSystem.prototype.debug_material = function(self) {
    var self = this.ptr;
    return wrapPointer(_mud_GfxSystem_debug_material_0(self), Material);
};
GfxSystem.prototype["default_pipeline"] = GfxSystem.prototype.default_pipeline = function(self) {
    var self = this.ptr;
    _mud_GfxSystem_default_pipeline_0(self);
};
GfxSystem.prototype["fetch_image256_material"] = GfxSystem.prototype.fetch_image256_material = function(self, image) {
    var self = this.ptr;
    /* image <Image256> [] */
    image = image.ptr;
    return wrapPointer(_mud_GfxSystem_fetch_image256_material_1(self, image), Material);
};
GfxSystem.prototype["fetch_material"] = GfxSystem.prototype.fetch_material = function(self, name, shader, builtin) {
    var self = this.ptr;
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    /* shader <const char*> [] */
    if (shader && typeof shader === "object") shader = shader.ptr;
    else shader = ensureString(shader);
    /* builtin <bool> [] */
    if (builtin === undefined) { return wrapPointer(_mud_GfxSystem_fetch_material_2(self, name, shader), Material); }
    return wrapPointer(_mud_GfxSystem_fetch_material_3(self, name, shader, builtin), Material);
};
GfxSystem.prototype["fetch_symbol"] = GfxSystem.prototype.fetch_symbol = function(self, symbol, shape, draw_mode) {
    var self = this.ptr;
    /* symbol <Symbol> [] */
    symbol = symbol.ptr;
    /* shape <Shape> [] */
    shape = shape.ptr;
    /* draw_mode <DrawMode> [] */
    if (draw_mode && typeof draw_mode === "object") draw_mode = draw_mode.ptr;
    return wrapPointer(_mud_GfxSystem_fetch_symbol_3(self, symbol, shape, draw_mode), Model);
};
GfxSystem.prototype["fetch_symbol_material"] = GfxSystem.prototype.fetch_symbol_material = function(self, symbol, draw_mode) {
    var self = this.ptr;
    /* symbol <Symbol> [] */
    symbol = symbol.ptr;
    /* draw_mode <DrawMode> [] */
    if (draw_mode && typeof draw_mode === "object") draw_mode = draw_mode.ptr;
    return wrapPointer(_mud_GfxSystem_fetch_symbol_material_2(self, symbol, draw_mode), Material);
};
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
    this.ptr = _mud_ImportConfig_ImportConfig_0(); getCache(ImportConfig)[this.ptr] = this;
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
        /* value <ModelFormat> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_ImportConfig__set_format(self, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ImportConfig__get_position(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _mud_ImportConfig__set_position(self, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ImportConfig__get_rotation(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <quat> [] */
        value = value.ptr;
        _mud_ImportConfig__set_rotation(self, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ImportConfig__get_scale(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _mud_ImportConfig__set_scale(self, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "transform", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ImportConfig__get_transform(self), mat4);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mat4> [] */
        value = value.ptr;
        _mud_ImportConfig__set_transform(self, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "suffix", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_ImportConfig__get_suffix(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <std::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_ImportConfig__set_suffix(self, value);
    }
});
Object.defineProperty(ImportConfig.prototype, "force_reimport", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ImportConfig__get_force_reimport(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
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
        /* value <bool> [] */
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
        /* value <bool> [] */
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
        /* value <uint32_t> [] */
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
        /* value <Node3> [] */
        value = value.ptr;
        _mud_Item__set_node(self, value);
    }
});
Object.defineProperty(Item.prototype, "model", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Item__get_model(self), Model);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Model> [] */
        value = value.ptr;
        _mud_Item__set_model(self, value);
    }
});
Object.defineProperty(Item.prototype, "flags", {
    get: function() {
        var self = this.ptr;
        return _mud_Item__get_flags(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
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
        /* value <Colour> [] */
        value = value.ptr;
        _mud_Item__set_colour(self, value);
    }
});
Object.defineProperty(Item.prototype, "material", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Item__get_material(self), Material);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Material> [] */
        value = value.ptr;
        _mud_Item__set_material(self, value);
    }
});
Object.defineProperty(Item.prototype, "visible", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Item__get_visible(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
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
        /* value <ItemShadow> [] */
        if (value && typeof value === "object") value = value.ptr;
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
        /* value <Rig> [] */
        value = value.ptr;
        _mud_Item__set_rig(self, value);
    }
});
Item.prototype["__destroy__"] = Item.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Item__destroy(self);
};
// Joint
function Joint() {
    this.ptr = _mud_Joint_Joint_0(); getCache(Joint)[this.ptr] = this;
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
        /* value <LightType> [] */
        if (value && typeof value === "object") value = value.ptr;
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
        /* value <bool> [] */
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
        /* value <Colour> [] */
        value = value.ptr;
        _mud_Light__set_colour(self, value);
    }
});
Object.defineProperty(Light.prototype, "range", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_range(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <bool> [] */
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
        /* value <Colour> [] */
        value = value.ptr;
        _mud_Light__set_shadow_colour(self, value);
    }
});
Object.defineProperty(Light.prototype, "shadow_range", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_shadow_range(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
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
        /* value <uint32_t> [] */
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
        /* value <uint32_t> [] */
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
        /* value <uint32_t> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <ShadowFlags> [] */
        if (value && typeof value === "object") value = value.ptr;
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
        /* value <uint8_t> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <uint16_t> [] */
        _mud_Material__set_index(self, value);
    }
});
Object.defineProperty(Material.prototype, "builtin", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Material__get_builtin(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
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
        /* value <Program> [] */
        value = value.ptr;
        _mud_Material__set_program(self, value);
    }
});
Object.defineProperty(Material.prototype, "base_block", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_base_block(self), BaseMaterialBlock);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <BaseMaterialBlock> [] */
        value = value.ptr;
        _mud_Material__set_base_block(self, value);
    }
});
Object.defineProperty(Material.prototype, "unshaded_block", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_unshaded_block(self), UnshadedMaterialBlock);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <UnshadedMaterialBlock> [] */
        value = value.ptr;
        _mud_Material__set_unshaded_block(self, value);
    }
});
Object.defineProperty(Material.prototype, "pbr_block", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_pbr_block(self), PbrMaterialBlock);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <PbrMaterialBlock> [] */
        value = value.ptr;
        _mud_Material__set_pbr_block(self, value);
    }
});
Object.defineProperty(Material.prototype, "fresnel_block", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_fresnel_block(self), FresnelMaterialBlock);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <FresnelMaterialBlock> [] */
        value = value.ptr;
        _mud_Material__set_fresnel_block(self, value);
    }
});
Material.prototype["__destroy__"] = Material.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Material__destroy(self);
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
        /* value <std::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_Mesh__set_name(self, value);
    }
});
Object.defineProperty(Mesh.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint16_t> [] */
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
        /* value <DrawMode> [] */
        if (value && typeof value === "object") value = value.ptr;
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
        /* value <Aabb> [] */
        value = value.ptr;
        _mud_Mesh__set_aabb(self, value);
    }
});
Object.defineProperty(Mesh.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Mesh__set_radius(self, value);
    }
});
Object.defineProperty(Mesh.prototype, "origin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Mesh__get_origin(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _mud_Mesh__set_origin(self, value);
    }
});
Object.defineProperty(Mesh.prototype, "readback", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Mesh__get_readback(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
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
        /* value <uint32_t> [] */
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
        /* value <bool> [] */
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
        /* value <uint32_t> [] */
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
        /* value <uint32_t> [] */
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
        /* value <bool> [] */
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
        /* value <Material> [] */
        value = value.ptr;
        _mud_Mesh__set_material(self, value);
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
        /* value <std::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_Model__set_name(self, value);
    }
});
Object.defineProperty(Model.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Model__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint16_t> [] */
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
        /* value <Aabb> [] */
        value = value.ptr;
        _mud_Model__set_aabb(self, value);
    }
});
Object.defineProperty(Model.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Model__get_radius(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Model__set_radius(self, value);
    }
});
Object.defineProperty(Model.prototype, "origin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Model__get_origin(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _mud_Model__set_origin(self, value);
    }
});
Model.prototype["__destroy__"] = Model.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Model__destroy(self);
};
// ModelItem
function ModelItem() {
    this.ptr = _mud_ModelItem_ModelItem_0(); getCache(ModelItem)[this.ptr] = this;
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
        /* value <size_t> [] */
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
        /* value <Mesh> [] */
        value = value.ptr;
        _mud_ModelItem__set_mesh(self, value);
    }
});
Object.defineProperty(ModelItem.prototype, "has_transform", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ModelItem__get_has_transform(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
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
        /* value <mat4> [] */
        value = value.ptr;
        _mud_ModelItem__set_transform(self, value);
    }
});
Object.defineProperty(ModelItem.prototype, "skin", {
    get: function() {
        var self = this.ptr;
        return _mud_ModelItem__get_skin(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
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
        /* value <Colour> [] */
        value = value.ptr;
        _mud_ModelItem__set_colour(self, value);
    }
});
Object.defineProperty(ModelItem.prototype, "material", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ModelItem__get_material(self), Material);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Material> [] */
        value = value.ptr;
        _mud_ModelItem__set_material(self, value);
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
        /* value <Scene> [] */
        value = value.ptr;
        _mud_Node3__set_scene(self, value);
    }
});
Object.defineProperty(Node3.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Node3__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint16_t> [] */
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
        /* value <mat4> [] */
        value = value.ptr;
        _mud_Node3__set_transform(self, value);
    }
});
Object.defineProperty(Node3.prototype, "visible", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Node3__get_visible(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_Node3__set_visible(self, value);
    }
});
Node3.prototype["__destroy__"] = Node3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Node3__destroy(self);
};
// ParticleGenerator
function ParticleGenerator() {
    this.ptr = _mud_ParticleGenerator_ParticleGenerator_0(); getCache(ParticleGenerator)[this.ptr] = this;
};
ParticleGenerator.prototype = Object.create(WrapperObject.prototype);
ParticleGenerator.prototype.constructor = ParticleGenerator;
ParticleGenerator.prototype.__class__ = ParticleGenerator;
ParticleGenerator.__cache__ = {};
Module['ParticleGenerator'] = ParticleGenerator;
Object.defineProperty(ParticleGenerator.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_ParticleGenerator__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <std::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_ParticleGenerator__set_name(self, value);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "duration", {
    get: function() {
        var self = this.ptr;
        return _mud_ParticleGenerator__get_duration(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_ParticleGenerator__set_duration(self, value);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "start_time", {
    get: function() {
        var self = this.ptr;
        return _mud_ParticleGenerator__get_start_time(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_ParticleGenerator__set_start_time(self, value);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "loop", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ParticleGenerator__get_loop(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_ParticleGenerator__set_loop(self, value);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "shape", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleGenerator__get_shape(self), ShapeVar);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <ShapeVar> [] */
        value = value.ptr;
        _mud_ParticleGenerator__set_shape(self, value);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "flow", {
    get: function() {
        var self = this.ptr;
        return _mud_ParticleGenerator__get_flow(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <EmitterFlow> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_ParticleGenerator__set_flow(self, value);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "billboard", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ParticleGenerator__get_billboard(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_ParticleGenerator__set_billboard(self, value);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "direction", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleGenerator__get_direction(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _mud_ParticleGenerator__set_direction(self, value);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleGenerator__get_rotation(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <quat> [] */
        value = value.ptr;
        _mud_ParticleGenerator__set_rotation(self, value);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "blend_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_ParticleGenerator__get_blend_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <BlendMode> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_ParticleGenerator__set_blend_mode(self, value);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "sprite_name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_ParticleGenerator__get_sprite_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <std::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_ParticleGenerator__set_sprite_name(self, value);
    }
});
ParticleGenerator.prototype["__destroy__"] = ParticleGenerator.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ParticleGenerator__destroy(self);
};
// PbrMaterialBlock
function PbrMaterialBlock(albedo, metallic, roughness) {
    /* albedo <Colour> [] */
    albedo = albedo.ptr;
    /* metallic <float> [] */
    /* roughness <float> [] */
    if (albedo === undefined) { this.ptr = _mud_PbrMaterialBlock_PbrMaterialBlock_0(); getCache(PbrMaterialBlock)[this.ptr] = this; return; }
    if (metallic === undefined) { this.ptr = _mud_PbrMaterialBlock_PbrMaterialBlock_1(albedo); getCache(PbrMaterialBlock)[this.ptr] = this; return; }
    if (roughness === undefined) { this.ptr = _mud_PbrMaterialBlock_PbrMaterialBlock_2(albedo, metallic); getCache(PbrMaterialBlock)[this.ptr] = this; return; }
    this.ptr = _mud_PbrMaterialBlock_PbrMaterialBlock_3(albedo, metallic, roughness); getCache(PbrMaterialBlock)[this.ptr] = this;
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
        /* value <bool> [] */
        _mud_PbrMaterialBlock__set_enabled(self, value);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "specular", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_specular(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_PbrMaterialBlock__set_specular(self, value);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "emissive_energy", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_emissive_energy(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_PbrMaterialBlock__set_emissive_energy(self, value);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "ritint", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_ritint(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_PbrMaterialBlock__set_ritint(self, value);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "clearcoat_gloss", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_clearcoat_gloss(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_PbrMaterialBlock__set_clearcoat_gloss(self, value);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "deep_parallax", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_PbrMaterialBlock__get_deep_parallax(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
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
        /* value <PbrDiffuseMode> [] */
        if (value && typeof value === "object") value = value.ptr;
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
        /* value <PbrSpecularMode> [] */
        if (value && typeof value === "object") value = value.ptr;
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
        /* value <std::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_Prefab__set_name(self, value);
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
    this.ptr = _mud_Radiance_Radiance_0(); getCache(Radiance)[this.ptr] = this;
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <Colour> [] */
        value = value.ptr;
        _mud_Radiance__set_colour(self, value);
    }
});
Object.defineProperty(Radiance.prototype, "texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Radiance__get_texture(self), Texture);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Texture> [] */
        value = value.ptr;
        _mud_Radiance__set_texture(self, value);
    }
});
Radiance.prototype["__destroy__"] = Radiance.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Radiance__destroy(self);
};
// RenderFrame
function RenderFrame() {
    this.ptr = _mud_RenderFrame_RenderFrame_0(); getCache(RenderFrame)[this.ptr] = this;
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
    this.ptr = _mud_RenderQuad_RenderQuad_0(); getCache(RenderQuad)[this.ptr] = this;
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
        /* value <Environment> [] */
        value = value.ptr;
        _mud_Scene__set_environment(self, value);
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
    this.ptr = _mud_Sun_Sun_0(); getCache(Sun)[this.ptr] = this;
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
        /* value <float> [] */
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
        /* value <float> [] */
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
        /* value <Colour> [] */
        value = value.ptr;
        _mud_Sun__set_colour(self, value);
    }
});
Object.defineProperty(Sun.prototype, "intensity", {
    get: function() {
        var self = this.ptr;
        return _mud_Sun__get_intensity(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
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
Object.defineProperty(Texture.prototype, "width", {
    get: function() {
        var self = this.ptr;
        return _mud_Texture__get_width(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint16_t> [] */
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
        /* value <uint16_t> [] */
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
        /* value <uint32_t> [] */
        _mud_Texture__set_bits_per_pixel(self, value);
    }
});
Texture.prototype["__destroy__"] = Texture.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Texture__destroy(self);
};
// UnshadedMaterialBlock
function UnshadedMaterialBlock() {
    this.ptr = _mud_UnshadedMaterialBlock_UnshadedMaterialBlock_0(); getCache(UnshadedMaterialBlock)[this.ptr] = this;
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
        /* value <bool> [] */
        _mud_UnshadedMaterialBlock__set_enabled(self, value);
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
        /* value <Camera> [] */
        value = value.ptr;
        _mud_Viewport__set_camera(self, value);
    }
});
Object.defineProperty(Viewport.prototype, "scene", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewport__get_scene(self), Scene);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Scene> [] */
        value = value.ptr;
        _mud_Viewport__set_scene(self, value);
    }
});
Object.defineProperty(Viewport.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Viewport__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint16_t> [] */
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
        /* value <bool> [] */
        _mud_Viewport__set_active(self, value);
    }
});
Object.defineProperty(Viewport.prototype, "rect", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewport__get_rect(self), uvec4);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uvec4> [] */
        value = value.ptr;
        _mud_Viewport__set_rect(self, value);
    }
});
Object.defineProperty(Viewport.prototype, "scissor", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Viewport__get_scissor(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
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
        /* value <Colour> [] */
        value = value.ptr;
        _mud_Viewport__set_clear_colour(self, value);
    }
});
Object.defineProperty(Viewport.prototype, "shading", {
    get: function() {
        var self = this.ptr;
        return _mud_Viewport__get_shading(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Shading> [] */
        if (value && typeof value === "object") value = value.ptr;
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
        /* value <Lighting> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Viewport__set_lighting(self, value);
    }
});
Viewport.prototype["__destroy__"] = Viewport.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Viewport__destroy(self);
};
// BlockCopy
function BlockCopy() { throw "cannot construct a BlockCopy, no constructor in IDL" }
BlockCopy.prototype = Object.create(WrapperObject.prototype);
BlockCopy.prototype.constructor = BlockCopy;
BlockCopy.prototype.__class__ = BlockCopy;
BlockCopy.__cache__ = {};
Module['BlockCopy'] = BlockCopy;
BlockCopy.prototype["__destroy__"] = BlockCopy.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockCopy__destroy(self);
};
// DrawBlock
function DrawBlock() { throw "cannot construct a DrawBlock, no constructor in IDL" }
DrawBlock.prototype = Object.create(WrapperObject.prototype);
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
BlockDepth.prototype = Object.create(WrapperObject.prototype);
BlockDepth.prototype.constructor = BlockDepth;
BlockDepth.prototype.__class__ = BlockDepth;
BlockDepth.__cache__ = {};
Module['BlockDepth'] = BlockDepth;
BlockDepth.prototype["__destroy__"] = BlockDepth.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BlockDepth__destroy(self);
};
// BlockFilter
function BlockFilter() { throw "cannot construct a BlockFilter, no constructor in IDL" }
BlockFilter.prototype = Object.create(WrapperObject.prototype);
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
BlockParticles.prototype = Object.create(WrapperObject.prototype);
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
BlockResolve.prototype = Object.create(WrapperObject.prototype);
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
BlockSky.prototype = Object.create(WrapperObject.prototype);
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
    this.ptr = _mud_ClusteredFrustum_ClusteredFrustum_0(); getCache(ClusteredFrustum)[this.ptr] = this;
};
ClusteredFrustum.prototype = Object.create(WrapperObject.prototype);
ClusteredFrustum.prototype.constructor = ClusteredFrustum;
ClusteredFrustum.prototype.__class__ = ClusteredFrustum;
ClusteredFrustum.__cache__ = {};
Module['ClusteredFrustum'] = ClusteredFrustum;
ClusteredFrustum.prototype["__destroy__"] = ClusteredFrustum.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ClusteredFrustum__destroy(self);
};
// Particles
function Particles() {
    this.ptr = _mud_Particles_Particles_0(); getCache(Particles)[this.ptr] = this;
};
Particles.prototype = Object.create(WrapperObject.prototype);
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
        /* value <Node3> [] */
        value = value.ptr;
        _mud_Particles__set_node(self, value);
    }
});
Particles.prototype["__destroy__"] = Particles.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Particles__destroy(self);
};
// RenderTarget
function RenderTarget() { throw "cannot construct a RenderTarget, no constructor in IDL" }
RenderTarget.prototype = Object.create(WrapperObject.prototype);
RenderTarget.prototype.constructor = RenderTarget;
RenderTarget.prototype.__class__ = RenderTarget;
RenderTarget.__cache__ = {};
Module['RenderTarget'] = RenderTarget;
RenderTarget.prototype["__destroy__"] = RenderTarget.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_RenderTarget__destroy(self);
};
Module['gfx']['animated'] = function(parent, item) {
    var self = this.ptr;
    /* parent <Gnode> [] */
    parent = parent.ptr;
    /* item <Item> [] */
    item = item.ptr;
    return wrapPointer(_mud_gfx_animated_2(parent, item), Animated);
};
Module['gfx']['draw'] = function(parent, shape, symbol, flags) {
    var self = this.ptr;
    /* parent <Gnode> [] */
    parent = parent.ptr;
    /* shape <Shape> [] */
    shape = shape.ptr;
    /* symbol <Symbol> [] */
    symbol = symbol.ptr;
    /* flags <uint32_t> [] */
    if (flags === undefined) { _mud_gfx_draw_3(parent, shape, symbol); return; }
    _mud_gfx_draw_4(parent, shape, symbol, flags);
};
Module['gfx']['light'] = function(parent, type, shadows, colour, range, attenuation) {
    var self = this.ptr;
    /* parent <Gnode> [] */
    parent = parent.ptr;
    /* type <LightType> [] */
    if (type && typeof type === "object") type = type.ptr;
    /* shadows <bool> [] */
    /* colour <Colour> [] */
    colour = colour.ptr;
    /* range <float> [] */
    /* attenuation <float> [] */
    if (range === undefined) { return wrapPointer(_mud_gfx_light_4(parent, type, shadows, colour), Light); }
    if (attenuation === undefined) { return wrapPointer(_mud_gfx_light_5(parent, type, shadows, colour, range), Light); }
    return wrapPointer(_mud_gfx_light_6(parent, type, shadows, colour, range, attenuation), Light);
};
Module['gfx']['model'] = function(parent, name, flags, material, instances) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Gnode> [] */
    parent = parent.ptr;
    /* name <std::string> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    /* flags <uint32_t> [] */
    /* material <Material> [] */
    if(typeof material !== "undefined" && material !== null) {{ material = material.ptr }};
    /* instances <size_t> [] */
    if (flags === undefined) { return wrapPointer(_mud_gfx_model_2(parent, name), Item); }
    if (material === undefined) { return wrapPointer(_mud_gfx_model_3(parent, name, flags), Item); }
    if (instances === undefined) { return wrapPointer(_mud_gfx_model_4(parent, name, flags, material), Item); }
    return wrapPointer(_mud_gfx_model_5(parent, name, flags, material, instances), Item);
};
Module['gfx']['particles'] = function(parent, emitter, flags, instances) {
    var self = this.ptr;
    /* parent <Gnode> [] */
    parent = parent.ptr;
    /* emitter <ParticleGenerator> [] */
    emitter = emitter.ptr;
    /* flags <uint32_t> [] */
    /* instances <size_t> [] */
    if (flags === undefined) { return wrapPointer(_mud_gfx_particles_2(parent, emitter), Particles); }
    if (instances === undefined) { return wrapPointer(_mud_gfx_particles_3(parent, emitter, flags), Particles); }
    return wrapPointer(_mud_gfx_particles_4(parent, emitter, flags, instances), Particles);
};
Module['gfx']['radiance'] = function(parent, texture, background) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Gnode> [] */
    parent = parent.ptr;
    /* texture <std::string> [] */
    if (texture && typeof texture === "object") texture = texture.ptr;
    else texture = ensureString(texture);
    /* background <BackgroundMode> [] */
    if (background && typeof background === "object") background = background.ptr;
    _mud_gfx_radiance_3(parent, texture, background);
};
Module['gfx']['shape'] = function(parent, shape, symbol, flags, material, instances) {
    var self = this.ptr;
    /* parent <Gnode> [] */
    parent = parent.ptr;
    /* shape <Shape> [] */
    shape = shape.ptr;
    /* symbol <Symbol> [] */
    symbol = symbol.ptr;
    /* flags <uint32_t> [] */
    /* material <Material> [] */
    if(typeof material !== "undefined" && material !== null) {{ material = material.ptr }};
    /* instances <size_t> [] */
    if (flags === undefined) { return wrapPointer(_mud_gfx_shape_3(parent, shape, symbol), Item); }
    if (material === undefined) { return wrapPointer(_mud_gfx_shape_4(parent, shape, symbol, flags), Item); }
    if (instances === undefined) { return wrapPointer(_mud_gfx_shape_5(parent, shape, symbol, flags, material), Item); }
    return wrapPointer(_mud_gfx_shape_6(parent, shape, symbol, flags, material, instances), Item);
};
Module['gfx']['sprite'] = function(parent, image, size, flags, material, instances) {
    var self = this.ptr;
    /* parent <Gnode> [] */
    parent = parent.ptr;
    /* image <Image256> [] */
    image = image.ptr;
    /* size <vec2> [] */
    size = size.ptr;
    /* flags <uint32_t> [] */
    /* material <Material> [] */
    if(typeof material !== "undefined" && material !== null) {{ material = material.ptr }};
    /* instances <size_t> [] */
    if (flags === undefined) { return wrapPointer(_mud_gfx_sprite_3(parent, image, size), Item); }
    if (material === undefined) { return wrapPointer(_mud_gfx_sprite_4(parent, image, size, flags), Item); }
    if (instances === undefined) { return wrapPointer(_mud_gfx_sprite_5(parent, image, size, flags, material), Item); }
    return wrapPointer(_mud_gfx_sprite_6(parent, image, size, flags, material, instances), Item);
};
Module['gfx']['sun_light'] = function(parent, azimuth, elevation) {
    var self = this.ptr;
    /* parent <Gnode> [] */
    parent = parent.ptr;
    /* azimuth <float> [] */
    /* elevation <float> [] */
    return wrapPointer(_mud_gfx_sun_light_3(parent, azimuth, elevation), Light);
};
Module['gfx']['update_item_aabb'] = function(item) {
    var self = this.ptr;
    /* item <Item> [] */
    item = item.ptr;
    _mud_gfx_update_item_aabb_1(item);
};
Module['gfx']['update_item_lights'] = function(item) {
    var self = this.ptr;
    /* item <Item> [] */
    item = item.ptr;
    _mud_gfx_update_item_lights_1(item);
};

(function() {
    function setupEnums() {
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
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
