
// Bindings utilities
function WrapperObject() {
}
// Animated
function Animated() { throw "cannot construct a Animated, no constructor in IDL" }
Animated.prototype = Object.create(WrapperObject.prototype);
Animated.prototype.constructor = Animated;
Animated.prototype.__class__ = Animated;
Animated.__cache__ = {};
Module['Animated'] = Animated;
Animated.prototype["advance"] = Animated.prototype.advance = function(time) {
    /* time <float> [] */
    _mud_Animated_advance_1(time);
};
Animated.prototype["next_animation"] = Animated.prototype.next_animation = function() {
    _mud_Animated_next_animation_0();
};
Animated.prototype["pause"] = Animated.prototype.pause = function() {
    _mud_Animated_pause_0();
};
Animated.prototype["play"] = Animated.prototype.play = function(animation, loop, blend, speed, transient) {
    /* animation <Animation> [] */
    animation = animation.ptr;
    /* loop <bool> [] */
    /* blend <float> [] */
    /* speed <float> [] */
    /* transient <bool> [] */
    if (blend === undefined) { _mud_Animated_play_2(animation, loop); return; }
    if (speed === undefined) { _mud_Animated_play_3(animation, loop, blend); return; }
    if (transient === undefined) { _mud_Animated_play_4(animation, loop, blend, speed); return; }
    _mud_Animated_play_5(animation, loop, blend, speed, transient);
};
Animated.prototype["playing"] = Animated.prototype.playing = function() {
    return Pointer_stringify(_mud_Animated_playing_0());
};
Animated.prototype["seek"] = Animated.prototype.seek = function(time) {
    /* time <float> [] */
    _mud_Animated_seek_1(time);
};
Animated.prototype["start"] = Animated.prototype.start = function(animation, loop, blend, speed, transient) {
    /* animation <const char*> [] */
    /* loop <bool> [] */
    /* blend <float> [] */
    /* speed <float> [] */
    /* transient <bool> [] */
    if (blend === undefined) { _mud_Animated_start_2(animation, loop); return; }
    if (speed === undefined) { _mud_Animated_start_3(animation, loop, blend); return; }
    if (transient === undefined) { _mud_Animated_start_4(animation, loop, blend, speed); return; }
    _mud_Animated_start_5(animation, loop, blend, speed, transient);
};
Animated.prototype["stop"] = Animated.prototype.stop = function() {
    _mud_Animated_stop_0();
};
Object.defineProperty(Animated.prototype, "active", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Animated__get_active(self));
    },
    set: function(active) {
        var self = this.ptr;
        /* active <bool> [] */
        _mud_Animated__set_active(self, active);
    }
});
Object.defineProperty(Animated.prototype, "speed_scale", {
    get: function() {
        var self = this.ptr;
        return _mud_Animated__get_speed_scale(self);
    },
    set: function(speed_scale) {
        var self = this.ptr;
        /* speed_scale <float> [] */
        _mud_Animated__set_speed_scale(self, speed_scale);
    }
});
Object.defineProperty(Animated.prototype, "default_blend_time", {
    get: function() {
        var self = this.ptr;
        return _mud_Animated__get_default_blend_time(self);
    },
    set: function(default_blend_time) {
        var self = this.ptr;
        /* default_blend_time <float> [] */
        _mud_Animated__set_default_blend_time(self, default_blend_time);
    }
});
Animated.prototype["__destroy__"] = Animated.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Animated__destroy(self);
};
// AnimatedTrack
function AnimatedTrack() {
    var self = this.ptr;
    this.ptr = _mud_AnimatedTrack_AnimatedTrack_0(self); getCache(AnimatedTrack)[this.ptr] = this;
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
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _mud_Animation__set_name(self, name);
    }
});
Object.defineProperty(Animation.prototype, "length", {
    get: function() {
        var self = this.ptr;
        return _mud_Animation__get_length(self);
    },
    set: function(length) {
        var self = this.ptr;
        /* length <float> [] */
        _mud_Animation__set_length(self, length);
    }
});
Object.defineProperty(Animation.prototype, "step", {
    get: function() {
        var self = this.ptr;
        return _mud_Animation__get_step(self);
    },
    set: function(step) {
        var self = this.ptr;
        /* step <float> [] */
        _mud_Animation__set_step(self, step);
    }
});
Animation.prototype["__destroy__"] = Animation.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Animation__destroy(self);
};
// AnimationPlay
function AnimationPlay() {
    var self = this.ptr;
    this.ptr = _mud_AnimationPlay_AnimationPlay_0(self); getCache(AnimationPlay)[this.ptr] = this;
};
AnimationPlay.prototype = Object.create(WrapperObject.prototype);
AnimationPlay.prototype.constructor = AnimationPlay;
AnimationPlay.prototype.__class__ = AnimationPlay;
AnimationPlay.__cache__ = {};
Module['AnimationPlay'] = AnimationPlay;
Object.defineProperty(AnimationPlay.prototype, "animation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_AnimationPlay__get_animation(self), mud::Animation);
    },
    set: function(animation) {
        var self = this.ptr;
        /* animation <Animation> [] */
        animation = animation.ptr;
        _mud_AnimationPlay__set_animation(self, animation);
    }
});
Object.defineProperty(AnimationPlay.prototype, "loop", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_AnimationPlay__get_loop(self));
    },
    set: function(loop) {
        var self = this.ptr;
        /* loop <bool> [] */
        _mud_AnimationPlay__set_loop(self, loop);
    }
});
Object.defineProperty(AnimationPlay.prototype, "speed", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationPlay__get_speed(self);
    },
    set: function(speed) {
        var self = this.ptr;
        /* speed <float> [] */
        _mud_AnimationPlay__set_speed(self, speed);
    }
});
Object.defineProperty(AnimationPlay.prototype, "transient", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_AnimationPlay__get_transient(self));
    },
    set: function(transient) {
        var self = this.ptr;
        /* transient <bool> [] */
        _mud_AnimationPlay__set_transient(self, transient);
    }
});
Object.defineProperty(AnimationPlay.prototype, "fadeout", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationPlay__get_fadeout(self);
    },
    set: function(fadeout) {
        var self = this.ptr;
        /* fadeout <float> [] */
        _mud_AnimationPlay__set_fadeout(self, fadeout);
    }
});
Object.defineProperty(AnimationPlay.prototype, "fadeout_left", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationPlay__get_fadeout_left(self);
    },
    set: function(fadeout_left) {
        var self = this.ptr;
        /* fadeout_left <float> [] */
        _mud_AnimationPlay__set_fadeout_left(self, fadeout_left);
    }
});
Object.defineProperty(AnimationPlay.prototype, "cursor", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationPlay__get_cursor(self);
    },
    set: function(cursor) {
        var self = this.ptr;
        /* cursor <float> [] */
        _mud_AnimationPlay__set_cursor(self, cursor);
    }
});
Object.defineProperty(AnimationPlay.prototype, "ended", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_AnimationPlay__get_ended(self));
    },
    set: function(ended) {
        var self = this.ptr;
        /* ended <bool> [] */
        _mud_AnimationPlay__set_ended(self, ended);
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
        return wrapPointer(_mud_AnimationTrack__get_animation(self), mud::Animation);
    },
    set: function(animation) {
        var self = this.ptr;
        /* animation <Animation> [] */
        animation = animation.ptr;
        _mud_AnimationTrack__set_animation(self, animation);
    }
});
Object.defineProperty(AnimationTrack.prototype, "node", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationTrack__get_node(self);
    },
    set: function(node) {
        var self = this.ptr;
        /* node <size_t> [] */
        _mud_AnimationTrack__set_node(self, node);
    }
});
Object.defineProperty(AnimationTrack.prototype, "node_name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_AnimationTrack__get_node_name(self));
    },
    set: function(node_name) {
        var self = this.ptr;
        /* node_name <std::string> [] */
        if (node_name && typeof node_name === "object") node_name = node_name.ptr;
        else node_name = ensureString(node_name);
        _mud_AnimationTrack__set_node_name(self, node_name);
    }
});
Object.defineProperty(AnimationTrack.prototype, "target", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationTrack__get_target(self);
    },
    set: function(target) {
        var self = this.ptr;
        /* target <AnimationTarget> [] */
        if (target && typeof target === "object") target = target.ptr;
        _mud_AnimationTrack__set_target(self, target);
    }
});
Object.defineProperty(AnimationTrack.prototype, "value_type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_AnimationTrack__get_value_type(self), mud::Type);
    },
    set: function(value_type) {
        var self = this.ptr;
        /* value_type <Type> [] */
        value_type = value_type.ptr;
        _mud_AnimationTrack__set_value_type(self, value_type);
    }
});
Object.defineProperty(AnimationTrack.prototype, "length", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationTrack__get_length(self);
    },
    set: function(length) {
        var self = this.ptr;
        /* length <float> [] */
        _mud_AnimationTrack__set_length(self, length);
    }
});
Object.defineProperty(AnimationTrack.prototype, "interpolation", {
    get: function() {
        var self = this.ptr;
        return _mud_AnimationTrack__get_interpolation(self);
    },
    set: function(interpolation) {
        var self = this.ptr;
        /* interpolation <Interpolation> [] */
        if (interpolation && typeof interpolation === "object") interpolation = interpolation.ptr;
        _mud_AnimationTrack__set_interpolation(self, interpolation);
    }
});
AnimationTrack.prototype["__destroy__"] = AnimationTrack.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_AnimationTrack__destroy(self);
};
// Background
function Background() {
    var self = this.ptr;
    this.ptr = _mud_Background_Background_0(self); getCache(Background)[this.ptr] = this;
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
    set: function(mode) {
        var self = this.ptr;
        /* mode <BackgroundMode> [] */
        if (mode && typeof mode === "object") mode = mode.ptr;
        _mud_Background__set_mode(self, mode);
    }
});
Object.defineProperty(Background.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Background__get_colour(self), mud::Colour);
    },
    set: function(colour) {
        var self = this.ptr;
        /* colour <Colour> [] */
        colour = colour.ptr;
        _mud_Background__set_colour(self, colour);
    }
});
Object.defineProperty(Background.prototype, "custoprogram", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Background__get_custoprogram(self), mud::Program);
    },
    set: function(custoprogram) {
        var self = this.ptr;
        /* custoprogram <Program> [] */
        custoprogram = custoprogram.ptr;
        _mud_Background__set_custoprogram(self, custoprogram);
    }
});
Background.prototype["__destroy__"] = Background.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Background__destroy(self);
};
// BaseMaterialBlock
function BaseMaterialBlock() {
    var self = this.ptr;
    this.ptr = _mud_BaseMaterialBlock_BaseMaterialBlock_0(self); getCache(BaseMaterialBlock)[this.ptr] = this;
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
    set: function(blend_mode) {
        var self = this.ptr;
        /* blend_mode <BlendMode> [] */
        if (blend_mode && typeof blend_mode === "object") blend_mode = blend_mode.ptr;
        _mud_BaseMaterialBlock__set_blend_mode(self, blend_mode);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "cull_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_BaseMaterialBlock__get_cull_mode(self);
    },
    set: function(cull_mode) {
        var self = this.ptr;
        /* cull_mode <CullMode> [] */
        if (cull_mode && typeof cull_mode === "object") cull_mode = cull_mode.ptr;
        _mud_BaseMaterialBlock__set_cull_mode(self, cull_mode);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "depth_draw_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_BaseMaterialBlock__get_depth_draw_mode(self);
    },
    set: function(depth_draw_mode) {
        var self = this.ptr;
        /* depth_draw_mode <DepthDraw> [] */
        if (depth_draw_mode && typeof depth_draw_mode === "object") depth_draw_mode = depth_draw_mode.ptr;
        _mud_BaseMaterialBlock__set_depth_draw_mode(self, depth_draw_mode);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "depth_test", {
    get: function() {
        var self = this.ptr;
        return _mud_BaseMaterialBlock__get_depth_test(self);
    },
    set: function(depth_test) {
        var self = this.ptr;
        /* depth_test <DepthTest> [] */
        if (depth_test && typeof depth_test === "object") depth_test = depth_test.ptr;
        _mud_BaseMaterialBlock__set_depth_test(self, depth_test);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "uv0_scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_BaseMaterialBlock__get_uv0_scale(self), mud::vec2);
    },
    set: function(uv0_scale) {
        var self = this.ptr;
        /* uv0_scale <vec2> [] */
        uv0_scale = uv0_scale.ptr;
        _mud_BaseMaterialBlock__set_uv0_scale(self, uv0_scale);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "uv0_offset", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_BaseMaterialBlock__get_uv0_offset(self), mud::vec2);
    },
    set: function(uv0_offset) {
        var self = this.ptr;
        /* uv0_offset <vec2> [] */
        uv0_offset = uv0_offset.ptr;
        _mud_BaseMaterialBlock__set_uv0_offset(self, uv0_offset);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "uv1_scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_BaseMaterialBlock__get_uv1_scale(self), mud::vec2);
    },
    set: function(uv1_scale) {
        var self = this.ptr;
        /* uv1_scale <vec2> [] */
        uv1_scale = uv1_scale.ptr;
        _mud_BaseMaterialBlock__set_uv1_scale(self, uv1_scale);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "uv1_offset", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_BaseMaterialBlock__get_uv1_offset(self), mud::vec2);
    },
    set: function(uv1_offset) {
        var self = this.ptr;
        /* uv1_offset <vec2> [] */
        uv1_offset = uv1_offset.ptr;
        _mud_BaseMaterialBlock__set_uv1_offset(self, uv1_offset);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "is_alpha", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_BaseMaterialBlock__get_is_alpha(self));
    },
    set: function(is_alpha) {
        var self = this.ptr;
        /* is_alpha <bool> [] */
        _mud_BaseMaterialBlock__set_is_alpha(self, is_alpha);
    }
});
Object.defineProperty(BaseMaterialBlock.prototype, "screen_filter", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_BaseMaterialBlock__get_screen_filter(self));
    },
    set: function(screen_filter) {
        var self = this.ptr;
        /* screen_filter <bool> [] */
        _mud_BaseMaterialBlock__set_screen_filter(self, screen_filter);
    }
});
BaseMaterialBlock.prototype["__destroy__"] = BaseMaterialBlock.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_BaseMaterialBlock__destroy(self);
};
// Bone
function Bone() {
    var self = this.ptr;
    this.ptr = _mud_Bone_Bone_0(self); getCache(Bone)[this.ptr] = this;
};
Bone.prototype = Object.create(WrapperObject.prototype);
Bone.prototype.constructor = Bone;
Bone.prototype.__class__ = Bone;
Bone.__cache__ = {};
Module['Bone'] = Bone;
Object.defineProperty(Bone.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Bone__get_position(self), mud::vec3);
    },
    set: function(position) {
        var self = this.ptr;
        /* position <vec3> [] */
        position = position.ptr;
        _mud_Bone__set_position(self, position);
    }
});
Object.defineProperty(Bone.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Bone__get_rotation(self), mud::quat);
    },
    set: function(rotation) {
        var self = this.ptr;
        /* rotation <quat> [] */
        rotation = rotation.ptr;
        _mud_Bone__set_rotation(self, rotation);
    }
});
Object.defineProperty(Bone.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Bone__get_scale(self), mud::vec3);
    },
    set: function(scale) {
        var self = this.ptr;
        /* scale <vec3> [] */
        scale = scale.ptr;
        _mud_Bone__set_scale(self, scale);
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
        return wrapPointer(_mud_Camera__get_eye(self), mud::vec3);
    },
    set: function(eye) {
        var self = this.ptr;
        /* eye <vec3> [] */
        eye = eye.ptr;
        _mud_Camera__set_eye(self, eye);
    }
});
Object.defineProperty(Camera.prototype, "target", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Camera__get_target(self), mud::vec3);
    },
    set: function(target) {
        var self = this.ptr;
        /* target <vec3> [] */
        target = target.ptr;
        _mud_Camera__set_target(self, target);
    }
});
Object.defineProperty(Camera.prototype, "transform", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Camera__get_transform(self), mud::mat4);
    },
    set: function(transform) {
        var self = this.ptr;
        /* transform <mat4> [] */
        transform = transform.ptr;
        _mud_Camera__set_transform(self, transform);
    }
});
Object.defineProperty(Camera.prototype, "projection", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Camera__get_projection(self), mud::mat4);
    },
    set: function(projection) {
        var self = this.ptr;
        /* projection <mat4> [] */
        projection = projection.ptr;
        _mud_Camera__set_projection(self, projection);
    }
});
Object.defineProperty(Camera.prototype, "fov", {
    get: function() {
        var self = this.ptr;
        return _mud_Camera__get_fov(self);
    },
    set: function(fov) {
        var self = this.ptr;
        /* fov <float> [] */
        _mud_Camera__set_fov(self, fov);
    }
});
Object.defineProperty(Camera.prototype, "aspect", {
    get: function() {
        var self = this.ptr;
        return _mud_Camera__get_aspect(self);
    },
    set: function(aspect) {
        var self = this.ptr;
        /* aspect <float> [] */
        _mud_Camera__set_aspect(self, aspect);
    }
});
Object.defineProperty(Camera.prototype, "near", {
    get: function() {
        var self = this.ptr;
        return _mud_Camera__get_near(self);
    },
    set: function(near) {
        var self = this.ptr;
        /* near <float> [] */
        _mud_Camera__set_near(self, near);
    }
});
Object.defineProperty(Camera.prototype, "far", {
    get: function() {
        var self = this.ptr;
        return _mud_Camera__get_far(self);
    },
    set: function(far) {
        var self = this.ptr;
        /* far <float> [] */
        _mud_Camera__set_far(self, far);
    }
});
Object.defineProperty(Camera.prototype, "orthographic", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Camera__get_orthographic(self));
    },
    set: function(orthographic) {
        var self = this.ptr;
        /* orthographic <bool> [] */
        _mud_Camera__set_orthographic(self, orthographic);
    }
});
Object.defineProperty(Camera.prototype, "height", {
    get: function() {
        var self = this.ptr;
        return _mud_Camera__get_height(self);
    },
    set: function(height) {
        var self = this.ptr;
        /* height <float> [] */
        _mud_Camera__set_height(self, height);
    }
});
Object.defineProperty(Camera.prototype, "optimize_ends", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Camera__get_optimize_ends(self));
    },
    set: function(optimize_ends) {
        var self = this.ptr;
        /* optimize_ends <bool> [] */
        _mud_Camera__set_optimize_ends(self, optimize_ends);
    }
});
Object.defineProperty(Camera.prototype, "clustered", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Camera__get_clustered(self));
    },
    set: function(clustered) {
        var self = this.ptr;
        /* clustered <bool> [] */
        _mud_Camera__set_clustered(self, clustered);
    }
});
Object.defineProperty(Camera.prototype, "lod_offsets", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Camera__get_lod_offsets(self), mud::vec4);
    },
    set: function(lod_offsets) {
        var self = this.ptr;
        /* lod_offsets <vec4> [] */
        lod_offsets = lod_offsets.ptr;
        _mud_Camera__set_lod_offsets(self, lod_offsets);
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
        return wrapPointer(_mud_Culler__get_viewport(self), mud::Viewport);
    },
    set: function(viewport) {
        var self = this.ptr;
        /* viewport <Viewport> [] */
        viewport = viewport.ptr;
        _mud_Culler__set_viewport(self, viewport);
    }
});
Culler.prototype["__destroy__"] = Culler.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Culler__destroy(self);
};
// DepthParams
function DepthParams() {
    var self = this.ptr;
    this.ptr = _mud_DepthParams_DepthParams_0(self); getCache(DepthParams)[this.ptr] = this;
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
    var self = this.ptr;
    this.ptr = _mud_Environment_Environment_0(self); getCache(Environment)[this.ptr] = this;
};
Environment.prototype = Object.create(WrapperObject.prototype);
Environment.prototype.constructor = Environment;
Environment.prototype.__class__ = Environment;
Environment.__cache__ = {};
Module['Environment'] = Environment;
Object.defineProperty(Environment.prototype, "background", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Environment__get_background(self), mud::Background);
    },
    set: function(background) {
        var self = this.ptr;
        /* background <Background> [] */
        background = background.ptr;
        _mud_Environment__set_background(self, background);
    }
});
Object.defineProperty(Environment.prototype, "radiance", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Environment__get_radiance(self), mud::Radiance);
    },
    set: function(radiance) {
        var self = this.ptr;
        /* radiance <Radiance> [] */
        radiance = radiance.ptr;
        _mud_Environment__set_radiance(self, radiance);
    }
});
Object.defineProperty(Environment.prototype, "sun", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Environment__get_sun(self), mud::Sun);
    },
    set: function(sun) {
        var self = this.ptr;
        /* sun <Sun> [] */
        sun = sun.ptr;
        _mud_Environment__set_sun(self, sun);
    }
});
Object.defineProperty(Environment.prototype, "fog", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Environment__get_fog(self), mud::Fog);
    },
    set: function(fog) {
        var self = this.ptr;
        /* fog <Fog> [] */
        fog = fog.ptr;
        _mud_Environment__set_fog(self, fog);
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
    var self = this.ptr;
    this.ptr = _mud_Fog_Fog_0(self); getCache(Fog)[this.ptr] = this;
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
    set: function(enabled) {
        var self = this.ptr;
        /* enabled <bool> [] */
        _mud_Fog__set_enabled(self, enabled);
    }
});
Object.defineProperty(Fog.prototype, "density", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_density(self);
    },
    set: function(density) {
        var self = this.ptr;
        /* density <float> [] */
        _mud_Fog__set_density(self, density);
    }
});
Object.defineProperty(Fog.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Fog__get_colour(self), mud::Colour);
    },
    set: function(colour) {
        var self = this.ptr;
        /* colour <Colour> [] */
        colour = colour.ptr;
        _mud_Fog__set_colour(self, colour);
    }
});
Object.defineProperty(Fog.prototype, "depth", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Fog__get_depth(self));
    },
    set: function(depth) {
        var self = this.ptr;
        /* depth <bool> [] */
        _mud_Fog__set_depth(self, depth);
    }
});
Object.defineProperty(Fog.prototype, "depth_begin", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_depth_begin(self);
    },
    set: function(depth_begin) {
        var self = this.ptr;
        /* depth_begin <float> [] */
        _mud_Fog__set_depth_begin(self, depth_begin);
    }
});
Object.defineProperty(Fog.prototype, "depth_curve", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_depth_curve(self);
    },
    set: function(depth_curve) {
        var self = this.ptr;
        /* depth_curve <float> [] */
        _mud_Fog__set_depth_curve(self, depth_curve);
    }
});
Object.defineProperty(Fog.prototype, "height", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Fog__get_height(self));
    },
    set: function(height) {
        var self = this.ptr;
        /* height <bool> [] */
        _mud_Fog__set_height(self, height);
    }
});
Object.defineProperty(Fog.prototype, "height_min", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_height_min(self);
    },
    set: function(height_min) {
        var self = this.ptr;
        /* height_min <float> [] */
        _mud_Fog__set_height_min(self, height_min);
    }
});
Object.defineProperty(Fog.prototype, "height_max", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_height_max(self);
    },
    set: function(height_max) {
        var self = this.ptr;
        /* height_max <float> [] */
        _mud_Fog__set_height_max(self, height_max);
    }
});
Object.defineProperty(Fog.prototype, "height_curve", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_height_curve(self);
    },
    set: function(height_curve) {
        var self = this.ptr;
        /* height_curve <float> [] */
        _mud_Fog__set_height_curve(self, height_curve);
    }
});
Object.defineProperty(Fog.prototype, "transmit", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Fog__get_transmit(self));
    },
    set: function(transmit) {
        var self = this.ptr;
        /* transmit <bool> [] */
        _mud_Fog__set_transmit(self, transmit);
    }
});
Object.defineProperty(Fog.prototype, "transmit_curve", {
    get: function() {
        var self = this.ptr;
        return _mud_Fog__get_transmit_curve(self);
    },
    set: function(transmit_curve) {
        var self = this.ptr;
        /* transmit_curve <float> [] */
        _mud_Fog__set_transmit_curve(self, transmit_curve);
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
    var self = this.ptr;
    this.ptr = _mud_FresnelMaterialBlock_FresnelMaterialBlock_0(self); getCache(FresnelMaterialBlock)[this.ptr] = this;
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
    set: function(enabled) {
        var self = this.ptr;
        /* enabled <bool> [] */
        _mud_FresnelMaterialBlock__set_enabled(self, enabled);
    }
});
Object.defineProperty(FresnelMaterialBlock.prototype, "fresnel_scale", {
    get: function() {
        var self = this.ptr;
        return _mud_FresnelMaterialBlock__get_fresnel_scale(self);
    },
    set: function(fresnel_scale) {
        var self = this.ptr;
        /* fresnel_scale <float> [] */
        _mud_FresnelMaterialBlock__set_fresnel_scale(self, fresnel_scale);
    }
});
Object.defineProperty(FresnelMaterialBlock.prototype, "fresnel_bias", {
    get: function() {
        var self = this.ptr;
        return _mud_FresnelMaterialBlock__get_fresnel_bias(self);
    },
    set: function(fresnel_bias) {
        var self = this.ptr;
        /* fresnel_bias <float> [] */
        _mud_FresnelMaterialBlock__set_fresnel_bias(self, fresnel_bias);
    }
});
Object.defineProperty(FresnelMaterialBlock.prototype, "fresnel_power", {
    get: function() {
        var self = this.ptr;
        return _mud_FresnelMaterialBlock__get_fresnel_power(self);
    },
    set: function(fresnel_power) {
        var self = this.ptr;
        /* fresnel_power <float> [] */
        _mud_FresnelMaterialBlock__set_fresnel_power(self, fresnel_power);
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
    set: function(fov) {
        var self = this.ptr;
        /* fov <float> [] */
        _mud_Frustum__set_fov(self, fov);
    }
});
Object.defineProperty(Frustum.prototype, "aspect", {
    get: function() {
        var self = this.ptr;
        return _mud_Frustum__get_aspect(self);
    },
    set: function(aspect) {
        var self = this.ptr;
        /* aspect <float> [] */
        _mud_Frustum__set_aspect(self, aspect);
    }
});
Object.defineProperty(Frustum.prototype, "near", {
    get: function() {
        var self = this.ptr;
        return _mud_Frustum__get_near(self);
    },
    set: function(near) {
        var self = this.ptr;
        /* near <float> [] */
        _mud_Frustum__set_near(self, near);
    }
});
Object.defineProperty(Frustum.prototype, "far", {
    get: function() {
        var self = this.ptr;
        return _mud_Frustum__get_far(self);
    },
    set: function(far) {
        var self = this.ptr;
        /* far <float> [] */
        _mud_Frustum__set_far(self, far);
    }
});
Object.defineProperty(Frustum.prototype, "center", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Frustum__get_center(self), mud::vec3);
    },
    set: function(center) {
        var self = this.ptr;
        /* center <vec3> [] */
        center = center.ptr;
        _mud_Frustum__set_center(self, center);
    }
});
Object.defineProperty(Frustum.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Frustum__get_radius(self);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <float> [] */
        _mud_Frustum__set_radius(self, radius);
    }
});
Frustum.prototype["__destroy__"] = Frustum.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Frustum__destroy(self);
};
// FrustumSlice
function FrustumSlice() {
    var self = this.ptr;
    this.ptr = _mud_FrustumSlice_FrustumSlice_0(self); getCache(FrustumSlice)[this.ptr] = this;
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
        return wrapPointer(_mud_GfxBlock__get_type(self), mud::Type);
    }});
Object.defineProperty(GfxBlock.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_GfxBlock__get_index(self);
    },
    set: function(index) {
        var self = this.ptr;
        /* index <uint8_t> [] */
        _mud_GfxBlock__set_index(self, index);
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
function GfxSystem() { throw "cannot construct a GfxSystem, no constructor in IDL" }
GfxSystem.prototype = Object.create(WrapperObject.prototype);
GfxSystem.prototype.constructor = GfxSystem;
GfxSystem.prototype.__class__ = GfxSystem;
GfxSystem.__cache__ = {};
Module['GfxSystem'] = GfxSystem;
GfxSystem.prototype["add_resource_path"] = GfxSystem.prototype.add_resource_path = function(path) {
    /* path <const char*> [] */
    _mud_GfxSystem_add_resource_path_1(path);
};
GfxSystem.prototype["debug_material"] = GfxSystem.prototype.debug_material = function() {
    return wrapPointer(_mud_GfxSystem_debug_material_0(), mud::Material);
};
GfxSystem.prototype["fetch_image256_material"] = GfxSystem.prototype.fetch_image256_material = function(image) {
    /* image <Image256> [] */
    image = image.ptr;
    return wrapPointer(_mud_GfxSystem_fetch_image256_material_1(image), mud::Material);
};
GfxSystem.prototype["fetch_material"] = GfxSystem.prototype.fetch_material = function(name, shader, builtin) {
    /* name <const char*> [] */
    /* shader <const char*> [] */
    /* builtin <bool> [] */
    if (builtin === undefined) { return wrapPointer(_mud_GfxSystem_fetch_material_2(name, shader), mud::Material); return; }
    return wrapPointer(_mud_GfxSystem_fetch_material_3(name, shader, builtin), mud::Material);
};
GfxSystem.prototype["fetch_symbol"] = GfxSystem.prototype.fetch_symbol = function(symbol, shape, draw_mode) {
    /* symbol <Symbol> [] */
    symbol = symbol.ptr;
    /* shape <Shape> [] */
    shape = shape.ptr;
    /* draw_mode <DrawMode> [] */
    if (draw_mode && typeof draw_mode === "object") draw_mode = draw_mode.ptr;
    return wrapPointer(_mud_GfxSystem_fetch_symbol_3(symbol, shape, draw_mode), mud::Model);
};
GfxSystem.prototype["fetch_symbol_material"] = GfxSystem.prototype.fetch_symbol_material = function(symbol, draw_mode) {
    /* symbol <Symbol> [] */
    symbol = symbol.ptr;
    /* draw_mode <DrawMode> [] */
    if (draw_mode && typeof draw_mode === "object") draw_mode = draw_mode.ptr;
    return wrapPointer(_mud_GfxSystem_fetch_symbol_material_2(symbol, draw_mode), mud::Material);
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
    var self = this.ptr;
    this.ptr = _mud_ImportConfig_ImportConfig_0(self); getCache(ImportConfig)[this.ptr] = this;
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
    set: function(format) {
        var self = this.ptr;
        /* format <ModelFormat> [] */
        if (format && typeof format === "object") format = format.ptr;
        _mud_ImportConfig__set_format(self, format);
    }
});
Object.defineProperty(ImportConfig.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ImportConfig__get_position(self), mud::vec3);
    },
    set: function(position) {
        var self = this.ptr;
        /* position <vec3> [] */
        position = position.ptr;
        _mud_ImportConfig__set_position(self, position);
    }
});
Object.defineProperty(ImportConfig.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ImportConfig__get_rotation(self), mud::quat);
    },
    set: function(rotation) {
        var self = this.ptr;
        /* rotation <quat> [] */
        rotation = rotation.ptr;
        _mud_ImportConfig__set_rotation(self, rotation);
    }
});
Object.defineProperty(ImportConfig.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ImportConfig__get_scale(self), mud::vec3);
    },
    set: function(scale) {
        var self = this.ptr;
        /* scale <vec3> [] */
        scale = scale.ptr;
        _mud_ImportConfig__set_scale(self, scale);
    }
});
Object.defineProperty(ImportConfig.prototype, "transform", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ImportConfig__get_transform(self), mud::mat4);
    },
    set: function(transform) {
        var self = this.ptr;
        /* transform <mat4> [] */
        transform = transform.ptr;
        _mud_ImportConfig__set_transform(self, transform);
    }
});
Object.defineProperty(ImportConfig.prototype, "suffix", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_ImportConfig__get_suffix(self));
    },
    set: function(suffix) {
        var self = this.ptr;
        /* suffix <std::string> [] */
        if (suffix && typeof suffix === "object") suffix = suffix.ptr;
        else suffix = ensureString(suffix);
        _mud_ImportConfig__set_suffix(self, suffix);
    }
});
Object.defineProperty(ImportConfig.prototype, "force_reimport", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ImportConfig__get_force_reimport(self));
    },
    set: function(force_reimport) {
        var self = this.ptr;
        /* force_reimport <bool> [] */
        _mud_ImportConfig__set_force_reimport(self, force_reimport);
    }
});
Object.defineProperty(ImportConfig.prototype, "cache_geometry", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ImportConfig__get_cache_geometry(self));
    },
    set: function(cache_geometry) {
        var self = this.ptr;
        /* cache_geometry <bool> [] */
        _mud_ImportConfig__set_cache_geometry(self, cache_geometry);
    }
});
Object.defineProperty(ImportConfig.prototype, "optimize_geometry", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ImportConfig__get_optimize_geometry(self));
    },
    set: function(optimize_geometry) {
        var self = this.ptr;
        /* optimize_geometry <bool> [] */
        _mud_ImportConfig__set_optimize_geometry(self, optimize_geometry);
    }
});
Object.defineProperty(ImportConfig.prototype, "flags", {
    get: function() {
        var self = this.ptr;
        return _mud_ImportConfig__get_flags(self);
    },
    set: function(flags) {
        var self = this.ptr;
        /* flags <uint32_t> [] */
        _mud_ImportConfig__set_flags(self, flags);
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
        return wrapPointer(_mud_Item__get_node(self), mud::Node3);
    },
    set: function(node) {
        var self = this.ptr;
        /* node <Node3> [] */
        node = node.ptr;
        _mud_Item__set_node(self, node);
    }
});
Object.defineProperty(Item.prototype, "model", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Item__get_model(self), mud::Model);
    },
    set: function(model) {
        var self = this.ptr;
        /* model <Model> [] */
        model = model.ptr;
        _mud_Item__set_model(self, model);
    }
});
Object.defineProperty(Item.prototype, "flags", {
    get: function() {
        var self = this.ptr;
        return _mud_Item__get_flags(self);
    },
    set: function(flags) {
        var self = this.ptr;
        /* flags <uint32_t> [] */
        _mud_Item__set_flags(self, flags);
    }
});
Object.defineProperty(Item.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Item__get_colour(self), mud::Colour);
    },
    set: function(colour) {
        var self = this.ptr;
        /* colour <Colour> [] */
        colour = colour.ptr;
        _mud_Item__set_colour(self, colour);
    }
});
Object.defineProperty(Item.prototype, "material", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Item__get_material(self), mud::Material);
    },
    set: function(material) {
        var self = this.ptr;
        /* material <Material> [] */
        material = material.ptr;
        _mud_Item__set_material(self, material);
    }
});
Object.defineProperty(Item.prototype, "visible", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Item__get_visible(self));
    },
    set: function(visible) {
        var self = this.ptr;
        /* visible <bool> [] */
        _mud_Item__set_visible(self, visible);
    }
});
Object.defineProperty(Item.prototype, "shadow", {
    get: function() {
        var self = this.ptr;
        return _mud_Item__get_shadow(self);
    },
    set: function(shadow) {
        var self = this.ptr;
        /* shadow <ItemShadow> [] */
        if (shadow && typeof shadow === "object") shadow = shadow.ptr;
        _mud_Item__set_shadow(self, shadow);
    }
});
Object.defineProperty(Item.prototype, "rig", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Item__get_rig(self), mud::Rig);
    },
    set: function(rig) {
        var self = this.ptr;
        /* rig <Rig> [] */
        rig = rig.ptr;
        _mud_Item__set_rig(self, rig);
    }
});
Item.prototype["__destroy__"] = Item.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Item__destroy(self);
};
// Joint
function Joint() {
    var self = this.ptr;
    this.ptr = _mud_Joint_Joint_0(self); getCache(Joint)[this.ptr] = this;
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
        return wrapPointer(_mud_Light__get_node(self), mud::Node3);
    }});
Object.defineProperty(Light.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_type(self);
    },
    set: function(type) {
        var self = this.ptr;
        /* type <LightType> [] */
        if (type && typeof type === "object") type = type.ptr;
        _mud_Light__set_type(self, type);
    }
});
Object.defineProperty(Light.prototype, "visible", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Light__get_visible(self));
    },
    set: function(visible) {
        var self = this.ptr;
        /* visible <bool> [] */
        _mud_Light__set_visible(self, visible);
    }
});
Object.defineProperty(Light.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Light__get_colour(self), mud::Colour);
    },
    set: function(colour) {
        var self = this.ptr;
        /* colour <Colour> [] */
        colour = colour.ptr;
        _mud_Light__set_colour(self, colour);
    }
});
Object.defineProperty(Light.prototype, "range", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_range(self);
    },
    set: function(range) {
        var self = this.ptr;
        /* range <float> [] */
        _mud_Light__set_range(self, range);
    }
});
Object.defineProperty(Light.prototype, "energy", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_energy(self);
    },
    set: function(energy) {
        var self = this.ptr;
        /* energy <float> [] */
        _mud_Light__set_energy(self, energy);
    }
});
Object.defineProperty(Light.prototype, "specular", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_specular(self);
    },
    set: function(specular) {
        var self = this.ptr;
        /* specular <float> [] */
        _mud_Light__set_specular(self, specular);
    }
});
Object.defineProperty(Light.prototype, "attenuation", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_attenuation(self);
    },
    set: function(attenuation) {
        var self = this.ptr;
        /* attenuation <float> [] */
        _mud_Light__set_attenuation(self, attenuation);
    }
});
Object.defineProperty(Light.prototype, "shadows", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Light__get_shadows(self));
    },
    set: function(shadows) {
        var self = this.ptr;
        /* shadows <bool> [] */
        _mud_Light__set_shadows(self, shadows);
    }
});
Object.defineProperty(Light.prototype, "shadow_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Light__get_shadow_colour(self), mud::Colour);
    },
    set: function(shadow_colour) {
        var self = this.ptr;
        /* shadow_colour <Colour> [] */
        shadow_colour = shadow_colour.ptr;
        _mud_Light__set_shadow_colour(self, shadow_colour);
    }
});
Object.defineProperty(Light.prototype, "shadow_range", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_shadow_range(self);
    },
    set: function(shadow_range) {
        var self = this.ptr;
        /* shadow_range <float> [] */
        _mud_Light__set_shadow_range(self, shadow_range);
    }
});
Object.defineProperty(Light.prototype, "layers", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_layers(self);
    },
    set: function(layers) {
        var self = this.ptr;
        /* layers <uint32_t> [] */
        _mud_Light__set_layers(self, layers);
    }
});
Object.defineProperty(Light.prototype, "last_render", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_last_render(self);
    },
    set: function(last_render) {
        var self = this.ptr;
        /* last_render <uint32_t> [] */
        _mud_Light__set_last_render(self, last_render);
    }
});
Object.defineProperty(Light.prototype, "last_update", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_last_update(self);
    },
    set: function(last_update) {
        var self = this.ptr;
        /* last_update <uint32_t> [] */
        _mud_Light__set_last_update(self, last_update);
    }
});
Object.defineProperty(Light.prototype, "spot_angle", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_spot_angle(self);
    },
    set: function(spot_angle) {
        var self = this.ptr;
        /* spot_angle <float> [] */
        _mud_Light__set_spot_angle(self, spot_angle);
    }
});
Object.defineProperty(Light.prototype, "spot_attenuation", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_spot_attenuation(self);
    },
    set: function(spot_attenuation) {
        var self = this.ptr;
        /* spot_attenuation <float> [] */
        _mud_Light__set_spot_attenuation(self, spot_attenuation);
    }
});
Object.defineProperty(Light.prototype, "shadow_flags", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_shadow_flags(self);
    },
    set: function(shadow_flags) {
        var self = this.ptr;
        /* shadow_flags <ShadowFlags> [] */
        if (shadow_flags && typeof shadow_flags === "object") shadow_flags = shadow_flags.ptr;
        _mud_Light__set_shadow_flags(self, shadow_flags);
    }
});
Object.defineProperty(Light.prototype, "shadow_nusplits", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_shadow_nusplits(self);
    },
    set: function(shadow_nusplits) {
        var self = this.ptr;
        /* shadow_nusplits <uint8_t> [] */
        _mud_Light__set_shadow_nusplits(self, shadow_nusplits);
    }
});
Object.defineProperty(Light.prototype, "shadow_split_distribution", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_shadow_split_distribution(self);
    },
    set: function(shadow_split_distribution) {
        var self = this.ptr;
        /* shadow_split_distribution <float> [] */
        _mud_Light__set_shadow_split_distribution(self, shadow_split_distribution);
    }
});
Object.defineProperty(Light.prototype, "shadow_normal_bias", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_shadow_normal_bias(self);
    },
    set: function(shadow_normal_bias) {
        var self = this.ptr;
        /* shadow_normal_bias <float> [] */
        _mud_Light__set_shadow_normal_bias(self, shadow_normal_bias);
    }
});
Object.defineProperty(Light.prototype, "shadow_bias", {
    get: function() {
        var self = this.ptr;
        return _mud_Light__get_shadow_bias(self);
    },
    set: function(shadow_bias) {
        var self = this.ptr;
        /* shadow_bias <float> [] */
        _mud_Light__set_shadow_bias(self, shadow_bias);
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
    set: function(index) {
        var self = this.ptr;
        /* index <uint16_t> [] */
        _mud_Material__set_index(self, index);
    }
});
Object.defineProperty(Material.prototype, "builtin", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Material__get_builtin(self));
    },
    set: function(builtin) {
        var self = this.ptr;
        /* builtin <bool> [] */
        _mud_Material__set_builtin(self, builtin);
    }
});
Object.defineProperty(Material.prototype, "program", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_program(self), mud::Program);
    },
    set: function(program) {
        var self = this.ptr;
        /* program <Program> [] */
        program = program.ptr;
        _mud_Material__set_program(self, program);
    }
});
Object.defineProperty(Material.prototype, "base_block", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_base_block(self), mud::BaseMaterialBlock);
    },
    set: function(base_block) {
        var self = this.ptr;
        /* base_block <BaseMaterialBlock> [] */
        base_block = base_block.ptr;
        _mud_Material__set_base_block(self, base_block);
    }
});
Object.defineProperty(Material.prototype, "unshaded_block", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_unshaded_block(self), mud::UnshadedMaterialBlock);
    },
    set: function(unshaded_block) {
        var self = this.ptr;
        /* unshaded_block <UnshadedMaterialBlock> [] */
        unshaded_block = unshaded_block.ptr;
        _mud_Material__set_unshaded_block(self, unshaded_block);
    }
});
Object.defineProperty(Material.prototype, "pbr_block", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_pbr_block(self), mud::PbrMaterialBlock);
    },
    set: function(pbr_block) {
        var self = this.ptr;
        /* pbr_block <PbrMaterialBlock> [] */
        pbr_block = pbr_block.ptr;
        _mud_Material__set_pbr_block(self, pbr_block);
    }
});
Object.defineProperty(Material.prototype, "fresnel_block", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Material__get_fresnel_block(self), mud::FresnelMaterialBlock);
    },
    set: function(fresnel_block) {
        var self = this.ptr;
        /* fresnel_block <FresnelMaterialBlock> [] */
        fresnel_block = fresnel_block.ptr;
        _mud_Material__set_fresnel_block(self, fresnel_block);
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
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _mud_Mesh__set_name(self, name);
    }
});
Object.defineProperty(Mesh.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_index(self);
    },
    set: function(index) {
        var self = this.ptr;
        /* index <uint16_t> [] */
        _mud_Mesh__set_index(self, index);
    }
});
Object.defineProperty(Mesh.prototype, "draw_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_draw_mode(self);
    },
    set: function(draw_mode) {
        var self = this.ptr;
        /* draw_mode <DrawMode> [] */
        if (draw_mode && typeof draw_mode === "object") draw_mode = draw_mode.ptr;
        _mud_Mesh__set_draw_mode(self, draw_mode);
    }
});
Object.defineProperty(Mesh.prototype, "aabb", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Mesh__get_aabb(self), mud::Aabb);
    },
    set: function(aabb) {
        var self = this.ptr;
        /* aabb <Aabb> [] */
        aabb = aabb.ptr;
        _mud_Mesh__set_aabb(self, aabb);
    }
});
Object.defineProperty(Mesh.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_radius(self);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <float> [] */
        _mud_Mesh__set_radius(self, radius);
    }
});
Object.defineProperty(Mesh.prototype, "origin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Mesh__get_origin(self), mud::vec3);
    },
    set: function(origin) {
        var self = this.ptr;
        /* origin <vec3> [] */
        origin = origin.ptr;
        _mud_Mesh__set_origin(self, origin);
    }
});
Object.defineProperty(Mesh.prototype, "readback", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Mesh__get_readback(self));
    },
    set: function(readback) {
        var self = this.ptr;
        /* readback <bool> [] */
        _mud_Mesh__set_readback(self, readback);
    }
});
Object.defineProperty(Mesh.prototype, "vertex_format", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_vertex_format(self);
    },
    set: function(vertex_format) {
        var self = this.ptr;
        /* vertex_format <uint32_t> [] */
        _mud_Mesh__set_vertex_format(self, vertex_format);
    }
});
Object.defineProperty(Mesh.prototype, "qnormals", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Mesh__get_qnormals(self));
    },
    set: function(qnormals) {
        var self = this.ptr;
        /* qnormals <bool> [] */
        _mud_Mesh__set_qnormals(self, qnormals);
    }
});
Object.defineProperty(Mesh.prototype, "vertex_count", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_vertex_count(self);
    },
    set: function(vertex_count) {
        var self = this.ptr;
        /* vertex_count <uint32_t> [] */
        _mud_Mesh__set_vertex_count(self, vertex_count);
    }
});
Object.defineProperty(Mesh.prototype, "index_count", {
    get: function() {
        var self = this.ptr;
        return _mud_Mesh__get_index_count(self);
    },
    set: function(index_count) {
        var self = this.ptr;
        /* index_count <uint32_t> [] */
        _mud_Mesh__set_index_count(self, index_count);
    }
});
Object.defineProperty(Mesh.prototype, "index32", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Mesh__get_index32(self));
    },
    set: function(index32) {
        var self = this.ptr;
        /* index32 <bool> [] */
        _mud_Mesh__set_index32(self, index32);
    }
});
Object.defineProperty(Mesh.prototype, "material", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Mesh__get_material(self), mud::Material);
    },
    set: function(material) {
        var self = this.ptr;
        /* material <Material> [] */
        material = material.ptr;
        _mud_Mesh__set_material(self, material);
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
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _mud_Model__set_name(self, name);
    }
});
Object.defineProperty(Model.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Model__get_index(self);
    },
    set: function(index) {
        var self = this.ptr;
        /* index <uint16_t> [] */
        _mud_Model__set_index(self, index);
    }
});
Object.defineProperty(Model.prototype, "aabb", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Model__get_aabb(self), mud::Aabb);
    },
    set: function(aabb) {
        var self = this.ptr;
        /* aabb <Aabb> [] */
        aabb = aabb.ptr;
        _mud_Model__set_aabb(self, aabb);
    }
});
Object.defineProperty(Model.prototype, "radius", {
    get: function() {
        var self = this.ptr;
        return _mud_Model__get_radius(self);
    },
    set: function(radius) {
        var self = this.ptr;
        /* radius <float> [] */
        _mud_Model__set_radius(self, radius);
    }
});
Object.defineProperty(Model.prototype, "origin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Model__get_origin(self), mud::vec3);
    },
    set: function(origin) {
        var self = this.ptr;
        /* origin <vec3> [] */
        origin = origin.ptr;
        _mud_Model__set_origin(self, origin);
    }
});
Model.prototype["__destroy__"] = Model.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Model__destroy(self);
};
// ModelItem
function ModelItem() {
    var self = this.ptr;
    this.ptr = _mud_ModelItem_ModelItem_0(self); getCache(ModelItem)[this.ptr] = this;
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
    set: function(index) {
        var self = this.ptr;
        /* index <size_t> [] */
        _mud_ModelItem__set_index(self, index);
    }
});
Object.defineProperty(ModelItem.prototype, "mesh", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ModelItem__get_mesh(self), mud::Mesh);
    },
    set: function(mesh) {
        var self = this.ptr;
        /* mesh <Mesh> [] */
        mesh = mesh.ptr;
        _mud_ModelItem__set_mesh(self, mesh);
    }
});
Object.defineProperty(ModelItem.prototype, "has_transform", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ModelItem__get_has_transform(self));
    },
    set: function(has_transform) {
        var self = this.ptr;
        /* has_transform <bool> [] */
        _mud_ModelItem__set_has_transform(self, has_transform);
    }
});
Object.defineProperty(ModelItem.prototype, "transform", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ModelItem__get_transform(self), mud::mat4);
    },
    set: function(transform) {
        var self = this.ptr;
        /* transform <mat4> [] */
        transform = transform.ptr;
        _mud_ModelItem__set_transform(self, transform);
    }
});
Object.defineProperty(ModelItem.prototype, "skin", {
    get: function() {
        var self = this.ptr;
        return _mud_ModelItem__get_skin(self);
    },
    set: function(skin) {
        var self = this.ptr;
        /* skin <int> [] */
        _mud_ModelItem__set_skin(self, skin);
    }
});
Object.defineProperty(ModelItem.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ModelItem__get_colour(self), mud::Colour);
    },
    set: function(colour) {
        var self = this.ptr;
        /* colour <Colour> [] */
        colour = colour.ptr;
        _mud_ModelItem__set_colour(self, colour);
    }
});
Object.defineProperty(ModelItem.prototype, "material", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ModelItem__get_material(self), mud::Material);
    },
    set: function(material) {
        var self = this.ptr;
        /* material <Material> [] */
        material = material.ptr;
        _mud_ModelItem__set_material(self, material);
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
        return wrapPointer(_mud_Node3__get_scene(self), mud::Scene);
    },
    set: function(scene) {
        var self = this.ptr;
        /* scene <Scene> [] */
        scene = scene.ptr;
        _mud_Node3__set_scene(self, scene);
    }
});
Object.defineProperty(Node3.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Node3__get_index(self);
    },
    set: function(index) {
        var self = this.ptr;
        /* index <uint16_t> [] */
        _mud_Node3__set_index(self, index);
    }
});
Object.defineProperty(Node3.prototype, "transform", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Node3__get_transform(self), mud::mat4);
    },
    set: function(transform) {
        var self = this.ptr;
        /* transform <mat4> [] */
        transform = transform.ptr;
        _mud_Node3__set_transform(self, transform);
    }
});
Object.defineProperty(Node3.prototype, "visible", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Node3__get_visible(self));
    },
    set: function(visible) {
        var self = this.ptr;
        /* visible <bool> [] */
        _mud_Node3__set_visible(self, visible);
    }
});
Node3.prototype["__destroy__"] = Node3.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Node3__destroy(self);
};
// ParticleGenerator
function ParticleGenerator() {
    var self = this.ptr;
    this.ptr = _mud_ParticleGenerator_ParticleGenerator_0(self); getCache(ParticleGenerator)[this.ptr] = this;
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
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _mud_ParticleGenerator__set_name(self, name);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "duration", {
    get: function() {
        var self = this.ptr;
        return _mud_ParticleGenerator__get_duration(self);
    },
    set: function(duration) {
        var self = this.ptr;
        /* duration <float> [] */
        _mud_ParticleGenerator__set_duration(self, duration);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "start_time", {
    get: function() {
        var self = this.ptr;
        return _mud_ParticleGenerator__get_start_time(self);
    },
    set: function(start_time) {
        var self = this.ptr;
        /* start_time <float> [] */
        _mud_ParticleGenerator__set_start_time(self, start_time);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "loop", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ParticleGenerator__get_loop(self));
    },
    set: function(loop) {
        var self = this.ptr;
        /* loop <bool> [] */
        _mud_ParticleGenerator__set_loop(self, loop);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "shape", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleGenerator__get_shape(self), mud::ShapeVar);
    },
    set: function(shape) {
        var self = this.ptr;
        /* shape <ShapeVar> [] */
        shape = shape.ptr;
        _mud_ParticleGenerator__set_shape(self, shape);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "flow", {
    get: function() {
        var self = this.ptr;
        return _mud_ParticleGenerator__get_flow(self);
    },
    set: function(flow) {
        var self = this.ptr;
        /* flow <EmitterFlow> [] */
        if (flow && typeof flow === "object") flow = flow.ptr;
        _mud_ParticleGenerator__set_flow(self, flow);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "billboard", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_ParticleGenerator__get_billboard(self));
    },
    set: function(billboard) {
        var self = this.ptr;
        /* billboard <bool> [] */
        _mud_ParticleGenerator__set_billboard(self, billboard);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "direction", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleGenerator__get_direction(self), mud::vec3);
    },
    set: function(direction) {
        var self = this.ptr;
        /* direction <vec3> [] */
        direction = direction.ptr;
        _mud_ParticleGenerator__set_direction(self, direction);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ParticleGenerator__get_rotation(self), mud::quat);
    },
    set: function(rotation) {
        var self = this.ptr;
        /* rotation <quat> [] */
        rotation = rotation.ptr;
        _mud_ParticleGenerator__set_rotation(self, rotation);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "blend_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_ParticleGenerator__get_blend_mode(self);
    },
    set: function(blend_mode) {
        var self = this.ptr;
        /* blend_mode <BlendMode> [] */
        if (blend_mode && typeof blend_mode === "object") blend_mode = blend_mode.ptr;
        _mud_ParticleGenerator__set_blend_mode(self, blend_mode);
    }
});
Object.defineProperty(ParticleGenerator.prototype, "sprite_name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_ParticleGenerator__get_sprite_name(self));
    },
    set: function(sprite_name) {
        var self = this.ptr;
        /* sprite_name <std::string> [] */
        if (sprite_name && typeof sprite_name === "object") sprite_name = sprite_name.ptr;
        else sprite_name = ensureString(sprite_name);
        _mud_ParticleGenerator__set_sprite_name(self, sprite_name);
    }
});
ParticleGenerator.prototype["__destroy__"] = ParticleGenerator.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ParticleGenerator__destroy(self);
};
// PbrMaterialBlock
function PbrMaterialBlock(albedo, metallic, roughness) {
    var self = this.ptr;
    /* albedo <Colour> [] */
    albedo = albedo.ptr;
    /* metallic <float> [] */
    /* roughness <float> [] */
    if (albedo === undefined) { this.ptr = _mud_PbrMaterialBlock_PbrMaterialBlock_0(self); getCache(PbrMaterialBlock)[this.ptr] = this; return; }
    if (metallic === undefined) { this.ptr = _mud_PbrMaterialBlock_PbrMaterialBlock_1(self, albedo); getCache(PbrMaterialBlock)[this.ptr] = this; return; }
    if (roughness === undefined) { this.ptr = _mud_PbrMaterialBlock_PbrMaterialBlock_2(self, albedo, metallic); getCache(PbrMaterialBlock)[this.ptr] = this; return; }
    this.ptr = _mud_PbrMaterialBlock_PbrMaterialBlock_3(self, albedo, metallic, roughness); getCache(PbrMaterialBlock)[this.ptr] = this;
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
    set: function(enabled) {
        var self = this.ptr;
        /* enabled <bool> [] */
        _mud_PbrMaterialBlock__set_enabled(self, enabled);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "specular", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_specular(self);
    },
    set: function(specular) {
        var self = this.ptr;
        /* specular <float> [] */
        _mud_PbrMaterialBlock__set_specular(self, specular);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "emissive_energy", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_emissive_energy(self);
    },
    set: function(emissive_energy) {
        var self = this.ptr;
        /* emissive_energy <float> [] */
        _mud_PbrMaterialBlock__set_emissive_energy(self, emissive_energy);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "ritint", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_ritint(self);
    },
    set: function(ritint) {
        var self = this.ptr;
        /* ritint <float> [] */
        _mud_PbrMaterialBlock__set_ritint(self, ritint);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "clearcoat_gloss", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_clearcoat_gloss(self);
    },
    set: function(clearcoat_gloss) {
        var self = this.ptr;
        /* clearcoat_gloss <float> [] */
        _mud_PbrMaterialBlock__set_clearcoat_gloss(self, clearcoat_gloss);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "deep_parallax", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_PbrMaterialBlock__get_deep_parallax(self));
    },
    set: function(deep_parallax) {
        var self = this.ptr;
        /* deep_parallax <bool> [] */
        _mud_PbrMaterialBlock__set_deep_parallax(self, deep_parallax);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "diffuse_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_diffuse_mode(self);
    },
    set: function(diffuse_mode) {
        var self = this.ptr;
        /* diffuse_mode <PbrDiffuseMode> [] */
        if (diffuse_mode && typeof diffuse_mode === "object") diffuse_mode = diffuse_mode.ptr;
        _mud_PbrMaterialBlock__set_diffuse_mode(self, diffuse_mode);
    }
});
Object.defineProperty(PbrMaterialBlock.prototype, "specular_mode", {
    get: function() {
        var self = this.ptr;
        return _mud_PbrMaterialBlock__get_specular_mode(self);
    },
    set: function(specular_mode) {
        var self = this.ptr;
        /* specular_mode <PbrSpecularMode> [] */
        if (specular_mode && typeof specular_mode === "object") specular_mode = specular_mode.ptr;
        _mud_PbrMaterialBlock__set_specular_mode(self, specular_mode);
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
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _mud_Prefab__set_name(self, name);
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
        return _mud_Program__get_name(self);
    }});
Program.prototype["__destroy__"] = Program.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Program__destroy(self);
};
// Radiance
function Radiance() {
    var self = this.ptr;
    this.ptr = _mud_Radiance_Radiance_0(self); getCache(Radiance)[this.ptr] = this;
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
    set: function(energy) {
        var self = this.ptr;
        /* energy <float> [] */
        _mud_Radiance__set_energy(self, energy);
    }
});
Object.defineProperty(Radiance.prototype, "ambient", {
    get: function() {
        var self = this.ptr;
        return _mud_Radiance__get_ambient(self);
    },
    set: function(ambient) {
        var self = this.ptr;
        /* ambient <float> [] */
        _mud_Radiance__set_ambient(self, ambient);
    }
});
Object.defineProperty(Radiance.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Radiance__get_colour(self), mud::Colour);
    },
    set: function(colour) {
        var self = this.ptr;
        /* colour <Colour> [] */
        colour = colour.ptr;
        _mud_Radiance__set_colour(self, colour);
    }
});
Object.defineProperty(Radiance.prototype, "texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Radiance__get_texture(self), mud::Texture);
    },
    set: function(texture) {
        var self = this.ptr;
        /* texture <Texture> [] */
        texture = texture.ptr;
        _mud_Radiance__set_texture(self, texture);
    }
});
Radiance.prototype["__destroy__"] = Radiance.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Radiance__destroy(self);
};
// RenderFrame
function RenderFrame() {
    var self = this.ptr;
    this.ptr = _mud_RenderFrame_RenderFrame_0(self); getCache(RenderFrame)[this.ptr] = this;
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
    var self = this.ptr;
    this.ptr = _mud_RenderQuad_RenderQuad_0(self); getCache(RenderQuad)[this.ptr] = this;
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
Scene.prototype["begin"] = Scene.prototype.begin = function() {
    return wrapPointer(_mud_Scene_begin_0(), mud::Gnode);
};
Object.defineProperty(Scene.prototype, "graph", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Scene__get_graph(self), mud::Gnode);
    }});
Object.defineProperty(Scene.prototype, "root_node", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Scene__get_root_node(self), mud::Node3);
    }});
Object.defineProperty(Scene.prototype, "environment", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Scene__get_environment(self), mud::Environment);
    },
    set: function(environment) {
        var self = this.ptr;
        /* environment <Environment> [] */
        environment = environment.ptr;
        _mud_Scene__set_environment(self, environment);
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
    var self = this.ptr;
    this.ptr = _mud_Sun_Sun_0(self); getCache(Sun)[this.ptr] = this;
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
    set: function(azimuth) {
        var self = this.ptr;
        /* azimuth <float> [] */
        _mud_Sun__set_azimuth(self, azimuth);
    }
});
Object.defineProperty(Sun.prototype, "elevation", {
    get: function() {
        var self = this.ptr;
        return _mud_Sun__get_elevation(self);
    },
    set: function(elevation) {
        var self = this.ptr;
        /* elevation <float> [] */
        _mud_Sun__set_elevation(self, elevation);
    }
});
Object.defineProperty(Sun.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Sun__get_colour(self), mud::Colour);
    },
    set: function(colour) {
        var self = this.ptr;
        /* colour <Colour> [] */
        colour = colour.ptr;
        _mud_Sun__set_colour(self, colour);
    }
});
Object.defineProperty(Sun.prototype, "intensity", {
    get: function() {
        var self = this.ptr;
        return _mud_Sun__get_intensity(self);
    },
    set: function(intensity) {
        var self = this.ptr;
        /* intensity <float> [] */
        _mud_Sun__set_intensity(self, intensity);
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
    set: function(width) {
        var self = this.ptr;
        /* width <uint16_t> [] */
        _mud_Texture__set_width(self, width);
    }
});
Object.defineProperty(Texture.prototype, "height", {
    get: function() {
        var self = this.ptr;
        return _mud_Texture__get_height(self);
    },
    set: function(height) {
        var self = this.ptr;
        /* height <uint16_t> [] */
        _mud_Texture__set_height(self, height);
    }
});
Object.defineProperty(Texture.prototype, "bits_per_pixel", {
    get: function() {
        var self = this.ptr;
        return _mud_Texture__get_bits_per_pixel(self);
    },
    set: function(bits_per_pixel) {
        var self = this.ptr;
        /* bits_per_pixel <uint32_t> [] */
        _mud_Texture__set_bits_per_pixel(self, bits_per_pixel);
    }
});
Texture.prototype["__destroy__"] = Texture.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Texture__destroy(self);
};
// UnshadedMaterialBlock
function UnshadedMaterialBlock() {
    var self = this.ptr;
    this.ptr = _mud_UnshadedMaterialBlock_UnshadedMaterialBlock_0(self); getCache(UnshadedMaterialBlock)[this.ptr] = this;
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
    set: function(enabled) {
        var self = this.ptr;
        /* enabled <bool> [] */
        _mud_UnshadedMaterialBlock__set_enabled(self, enabled);
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
        return wrapPointer(_mud_Viewport__get_camera(self), mud::Camera);
    },
    set: function(camera) {
        var self = this.ptr;
        /* camera <Camera> [] */
        camera = camera.ptr;
        _mud_Viewport__set_camera(self, camera);
    }
});
Object.defineProperty(Viewport.prototype, "scene", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewport__get_scene(self), mud::Scene);
    },
    set: function(scene) {
        var self = this.ptr;
        /* scene <Scene> [] */
        scene = scene.ptr;
        _mud_Viewport__set_scene(self, scene);
    }
});
Object.defineProperty(Viewport.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Viewport__get_index(self);
    },
    set: function(index) {
        var self = this.ptr;
        /* index <uint16_t> [] */
        _mud_Viewport__set_index(self, index);
    }
});
Object.defineProperty(Viewport.prototype, "active", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Viewport__get_active(self));
    },
    set: function(active) {
        var self = this.ptr;
        /* active <bool> [] */
        _mud_Viewport__set_active(self, active);
    }
});
Object.defineProperty(Viewport.prototype, "rect", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewport__get_rect(self), mud::uvec4);
    },
    set: function(rect) {
        var self = this.ptr;
        /* rect <uvec4> [] */
        rect = rect.ptr;
        _mud_Viewport__set_rect(self, rect);
    }
});
Object.defineProperty(Viewport.prototype, "scissor", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Viewport__get_scissor(self));
    },
    set: function(scissor) {
        var self = this.ptr;
        /* scissor <bool> [] */
        _mud_Viewport__set_scissor(self, scissor);
    }
});
Object.defineProperty(Viewport.prototype, "clear_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Viewport__get_clear_colour(self), mud::Colour);
    },
    set: function(clear_colour) {
        var self = this.ptr;
        /* clear_colour <Colour> [] */
        clear_colour = clear_colour.ptr;
        _mud_Viewport__set_clear_colour(self, clear_colour);
    }
});
Object.defineProperty(Viewport.prototype, "shading", {
    get: function() {
        var self = this.ptr;
        return _mud_Viewport__get_shading(self);
    },
    set: function(shading) {
        var self = this.ptr;
        /* shading <Shading> [] */
        if (shading && typeof shading === "object") shading = shading.ptr;
        _mud_Viewport__set_shading(self, shading);
    }
});
Object.defineProperty(Viewport.prototype, "lighting", {
    get: function() {
        var self = this.ptr;
        return _mud_Viewport__get_lighting(self);
    },
    set: function(lighting) {
        var self = this.ptr;
        /* lighting <Lighting> [] */
        if (lighting && typeof lighting === "object") lighting = lighting.ptr;
        _mud_Viewport__set_lighting(self, lighting);
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
    var self = this.ptr;
    this.ptr = _mud_ClusteredFrustum_ClusteredFrustum_0(self); getCache(ClusteredFrustum)[this.ptr] = this;
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
    var self = this.ptr;
    this.ptr = _mud_Particles_Particles_0(self); getCache(Particles)[this.ptr] = this;
};
Particles.prototype = Object.create(WrapperObject.prototype);
Particles.prototype.constructor = Particles;
Particles.prototype.__class__ = Particles;
Particles.__cache__ = {};
Module['Particles'] = Particles;
Object.defineProperty(Particles.prototype, "node", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Particles__get_node(self), mud::Node3);
    },
    set: function(node) {
        var self = this.ptr;
        /* node <Node3> [] */
        node = node.ptr;
        _mud_Particles__set_node(self, node);
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

(function() {
    function setupEnums() {
        // AnimationTarget
        Module['AnimationTarget']['Position'] = _mud_AnimationTarget_Position();
        Module['AnimationTarget']['Rotation'] = _mud_AnimationTarget_Rotation();
        Module['AnimationTarget']['Scale'] = _mud_AnimationTarget_Scale();
        // BackgroundMode
        Module['BackgroundMode']['None'] = _mud_BackgroundMode_None();
        Module['BackgroundMode']['Panorama'] = _mud_BackgroundMode_Panorama();
        Module['BackgroundMode']['Radiance'] = _mud_BackgroundMode_Radiance();
        Module['BackgroundMode']['Custom'] = _mud_BackgroundMode_Custom();
        // BlendMode
        Module['BlendMode']['Mix'] = _mud_BlendMode_Mix();
        Module['BlendMode']['Add'] = _mud_BlendMode_Add();
        Module['BlendMode']['Sub'] = _mud_BlendMode_Sub();
        Module['BlendMode']['Mul'] = _mud_BlendMode_Mul();
        Module['BlendMode']['Normal'] = _mud_BlendMode_Normal();
        Module['BlendMode']['Alpha'] = _mud_BlendMode_Alpha();
        // CullMode
        Module['CullMode']['None'] = _mud_CullMode_None();
        Module['CullMode']['Front'] = _mud_CullMode_Front();
        Module['CullMode']['Back'] = _mud_CullMode_Back();
        // DepthDraw
        Module['DepthDraw']['Enabled'] = _mud_DepthDraw_Enabled();
        Module['DepthDraw']['Disabled'] = _mud_DepthDraw_Disabled();
        // DepthTest
        Module['DepthTest']['Enabled'] = _mud_DepthTest_Enabled();
        Module['DepthTest']['Disabled'] = _mud_DepthTest_Disabled();
        // EmitterFlow
        Module['EmitterFlow']['Outward'] = _mud_EmitterFlow_Outward();
        Module['EmitterFlow']['Absolute'] = _mud_EmitterFlow_Absolute();
        // Interpolation
        Module['Interpolation']['Nearest'] = _mud_Interpolation_Nearest();
        Module['Interpolation']['Linear'] = _mud_Interpolation_Linear();
        Module['Interpolation']['Cubic'] = _mud_Interpolation_Cubic();
        // IsometricAngle
        Module['NORTH'] = _mud_IsometricAngle_NORTH();
        Module['SOUTH'] = _mud_IsometricAngle_SOUTH();
        Module['EAST'] = _mud_IsometricAngle_EAST();
        Module['WEST'] = _mud_IsometricAngle_WEST();
        // ItemShadow
        Module['ItemShadow']['Default'] = _mud_ItemShadow_Default();
        Module['ItemShadow']['DoubleSided'] = _mud_ItemShadow_DoubleSided();
        // LightType
        Module['LightType']['Direct'] = _mud_LightType_Direct();
        Module['LightType']['Point'] = _mud_LightType_Point();
        Module['LightType']['Spot'] = _mud_LightType_Spot();
        Module['LightType']['Count'] = _mud_LightType_Count();
        // Lighting
        Module['Lighting']['None'] = _mud_Lighting_None();
        Module['Lighting']['Clustered'] = _mud_Lighting_Clustered();
        Module['Lighting']['Deferred'] = _mud_Lighting_Deferred();
        Module['Lighting']['VoxelGI'] = _mud_Lighting_VoxelGI();
        // MSAA
        Module['MSAA']['Disabled'] = _mud_MSAA_Disabled();
        Module['MSAA']['X2'] = _mud_MSAA_X2();
        Module['MSAA']['X4'] = _mud_MSAA_X4();
        Module['MSAA']['X8'] = _mud_MSAA_X8();
        Module['MSAA']['X16'] = _mud_MSAA_X16();
        // MaterialFlag
        Module['MaterialFlag']['TriplanarUV1'] = _mud_MaterialFlag_TriplanarUV1();
        Module['MaterialFlag']['TriplanarUV2'] = _mud_MaterialFlag_TriplanarUV2();
        Module['MaterialFlag']['Count'] = _mud_MaterialFlag_Count();
        // ModelFormat
        Module['ModelFormat']['obj'] = _mud_ModelFormat_obj();
        Module['ModelFormat']['gltf'] = _mud_ModelFormat_gltf();
        Module['ModelFormat']['Count'] = _mud_ModelFormat_Count();
        // Month
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
        Module['PbrDiffuseMode']['Lambert'] = _mud_PbrDiffuseMode_Lambert();
        Module['PbrDiffuseMode']['LambertHalf'] = _mud_PbrDiffuseMode_LambertHalf();
        Module['PbrDiffuseMode']['OrenNayar'] = _mud_PbrDiffuseMode_OrenNayar();
        Module['PbrDiffuseMode']['Burley'] = _mud_PbrDiffuseMode_Burley();
        Module['PbrDiffuseMode']['Toon'] = _mud_PbrDiffuseMode_Toon();
        // PbrSpecularMode
        Module['PbrSpecularMode']['SchlickGGX'] = _mud_PbrSpecularMode_SchlickGGX();
        Module['PbrSpecularMode']['Blinn'] = _mud_PbrSpecularMode_Blinn();
        Module['PbrSpecularMode']['Phong'] = _mud_PbrSpecularMode_Phong();
        Module['PbrSpecularMode']['Toon'] = _mud_PbrSpecularMode_Toon();
        Module['PbrSpecularMode']['Disabled'] = _mud_PbrSpecularMode_Disabled();
        // ShaderType
        Module['ShaderType']['Compute'] = _mud_ShaderType_Compute();
        Module['ShaderType']['Fragment'] = _mud_ShaderType_Fragment();
        Module['ShaderType']['Geometry'] = _mud_ShaderType_Geometry();
        Module['ShaderType']['Vertex'] = _mud_ShaderType_Vertex();
        Module['ShaderType']['Count'] = _mud_ShaderType_Count();
        // Shading
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
        Module['TextureChannel']['Red'] = _mud_TextureChannel_Red();
        Module['TextureChannel']['Green'] = _mud_TextureChannel_Green();
        Module['TextureChannel']['Blue'] = _mud_TextureChannel_Blue();
        Module['TextureChannel']['Alpha'] = _mud_TextureChannel_Alpha();
        Module['TextureChannel']['All'] = _mud_TextureChannel_All();
        // TextureHint
        Module['TextureHint']['Black'] = _mud_TextureHint_Black();
        Module['TextureHint']['White'] = _mud_TextureHint_White();
        Module['TextureHint']['Normal'] = _mud_TextureHint_Normal();
        // TextureSampler
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
