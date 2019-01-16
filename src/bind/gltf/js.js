Module['glm'] = Module['glm'] || {};
Module['gfx'] = Module['gfx'] || {};
Module['ui'] = Module['ui'] || {};
// glTF
function glTF() {
    this.ptr = _glTF_glTF_0(); getCache(glTF)[this.ptr] = this;
    this.type = glTF;
};
glTF.prototype = Object.create(WrapperObject.prototype);
glTF.prototype.constructor = glTF;
glTF.prototype.__class__ = glTF;
glTF.__cache__ = {};
Module['glTF'] = glTF;
glTF.prototype["__destroy__"] = glTF.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTF__destroy(self);
};
// glTFAccessor
function glTFAccessor() {
    this.ptr = _glTFAccessor_glTFAccessor_0(); getCache(glTFAccessor)[this.ptr] = this;
    this.type = glTFAccessor;
};
glTFAccessor.prototype = Object.create(WrapperObject.prototype);
glTFAccessor.prototype.constructor = glTFAccessor;
glTFAccessor.prototype.__class__ = glTFAccessor;
glTFAccessor.__cache__ = {};
Module['glTFAccessor'] = glTFAccessor;
Object.defineProperty(glTFAccessor.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFAccessor__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFAccessor__set_name(self, value);
    }
});
Object.defineProperty(glTFAccessor.prototype, "buffer_view", {
    get: function() {
        var self = this.ptr;
        return _glTFAccessor__get_buffer_view(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAccessor__set_buffer_view(self, value);
    }
});
Object.defineProperty(glTFAccessor.prototype, "byte_offset", {
    get: function() {
        var self = this.ptr;
        return _glTFAccessor__get_byte_offset(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAccessor__set_byte_offset(self, value);
    }
});
Object.defineProperty(glTFAccessor.prototype, "component_type", {
    get: function() {
        var self = this.ptr;
        return _glTFAccessor__get_component_type(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFComponentType> [] */
        if (value && typeof value === "object") value = value.ptr;
        _glTFAccessor__set_component_type(self, value);
    }
});
Object.defineProperty(glTFAccessor.prototype, "normalized", {
    get: function() {
        var self = this.ptr;
        return !!(_glTFAccessor__get_normalized(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _glTFAccessor__set_normalized(self, value);
    }
});
Object.defineProperty(glTFAccessor.prototype, "count", {
    get: function() {
        var self = this.ptr;
        return _glTFAccessor__get_count(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAccessor__set_count(self, value);
    }
});
Object.defineProperty(glTFAccessor.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return _glTFAccessor__get_type(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFType> [] */
        if (value && typeof value === "object") value = value.ptr;
        _glTFAccessor__set_type(self, value);
    }
});
Object.defineProperty(glTFAccessor.prototype, "sparse", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFAccessor__get_sparse(self), glTFSparse);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFSparse> [] */
        value = value.ptr;
        _glTFAccessor__set_sparse(self, value);
    }
});
glTFAccessor.prototype["__destroy__"] = glTFAccessor.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFAccessor__destroy(self);
};
// glTFAnimation
function glTFAnimation() {
    this.ptr = _glTFAnimation_glTFAnimation_0(); getCache(glTFAnimation)[this.ptr] = this;
    this.type = glTFAnimation;
};
glTFAnimation.prototype = Object.create(WrapperObject.prototype);
glTFAnimation.prototype.constructor = glTFAnimation;
glTFAnimation.prototype.__class__ = glTFAnimation;
glTFAnimation.__cache__ = {};
Module['glTFAnimation'] = glTFAnimation;
Object.defineProperty(glTFAnimation.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFAnimation__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFAnimation__set_name(self, value);
    }
});
glTFAnimation.prototype["__destroy__"] = glTFAnimation.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFAnimation__destroy(self);
};
// glTFAnimationChannel
function glTFAnimationChannel() {
    this.ptr = _glTFAnimationChannel_glTFAnimationChannel_0(); getCache(glTFAnimationChannel)[this.ptr] = this;
    this.type = glTFAnimationChannel;
};
glTFAnimationChannel.prototype = Object.create(WrapperObject.prototype);
glTFAnimationChannel.prototype.constructor = glTFAnimationChannel;
glTFAnimationChannel.prototype.__class__ = glTFAnimationChannel;
glTFAnimationChannel.__cache__ = {};
Module['glTFAnimationChannel'] = glTFAnimationChannel;
Object.defineProperty(glTFAnimationChannel.prototype, "sampler", {
    get: function() {
        var self = this.ptr;
        return _glTFAnimationChannel__get_sampler(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAnimationChannel__set_sampler(self, value);
    }
});
Object.defineProperty(glTFAnimationChannel.prototype, "target", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFAnimationChannel__get_target(self), glTFAnimationTarget);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFAnimationTarget> [] */
        value = value.ptr;
        _glTFAnimationChannel__set_target(self, value);
    }
});
glTFAnimationChannel.prototype["__destroy__"] = glTFAnimationChannel.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFAnimationChannel__destroy(self);
};
// glTFAnimationSampler
function glTFAnimationSampler() {
    this.ptr = _glTFAnimationSampler_glTFAnimationSampler_0(); getCache(glTFAnimationSampler)[this.ptr] = this;
    this.type = glTFAnimationSampler;
};
glTFAnimationSampler.prototype = Object.create(WrapperObject.prototype);
glTFAnimationSampler.prototype.constructor = glTFAnimationSampler;
glTFAnimationSampler.prototype.__class__ = glTFAnimationSampler;
glTFAnimationSampler.__cache__ = {};
Module['glTFAnimationSampler'] = glTFAnimationSampler;
Object.defineProperty(glTFAnimationSampler.prototype, "interpolation", {
    get: function() {
        var self = this.ptr;
        return _glTFAnimationSampler__get_interpolation(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFInterpolation> [] */
        if (value && typeof value === "object") value = value.ptr;
        _glTFAnimationSampler__set_interpolation(self, value);
    }
});
Object.defineProperty(glTFAnimationSampler.prototype, "input", {
    get: function() {
        var self = this.ptr;
        return _glTFAnimationSampler__get_input(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAnimationSampler__set_input(self, value);
    }
});
Object.defineProperty(glTFAnimationSampler.prototype, "output", {
    get: function() {
        var self = this.ptr;
        return _glTFAnimationSampler__get_output(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAnimationSampler__set_output(self, value);
    }
});
glTFAnimationSampler.prototype["__destroy__"] = glTFAnimationSampler.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFAnimationSampler__destroy(self);
};
// glTFAnimationTarget
function glTFAnimationTarget() {
    this.ptr = _glTFAnimationTarget_glTFAnimationTarget_0(); getCache(glTFAnimationTarget)[this.ptr] = this;
    this.type = glTFAnimationTarget;
};
glTFAnimationTarget.prototype = Object.create(WrapperObject.prototype);
glTFAnimationTarget.prototype.constructor = glTFAnimationTarget;
glTFAnimationTarget.prototype.__class__ = glTFAnimationTarget;
glTFAnimationTarget.__cache__ = {};
Module['glTFAnimationTarget'] = glTFAnimationTarget;
Object.defineProperty(glTFAnimationTarget.prototype, "node", {
    get: function() {
        var self = this.ptr;
        return _glTFAnimationTarget__get_node(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAnimationTarget__set_node(self, value);
    }
});
Object.defineProperty(glTFAnimationTarget.prototype, "path", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFAnimationTarget__get_path(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFAnimationTarget__set_path(self, value);
    }
});
glTFAnimationTarget.prototype["__destroy__"] = glTFAnimationTarget.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFAnimationTarget__destroy(self);
};
// glTFAttributes
function glTFAttributes() {
    this.ptr = _glTFAttributes_glTFAttributes_0(); getCache(glTFAttributes)[this.ptr] = this;
    this.type = glTFAttributes;
};
glTFAttributes.prototype = Object.create(WrapperObject.prototype);
glTFAttributes.prototype.constructor = glTFAttributes;
glTFAttributes.prototype.__class__ = glTFAttributes;
glTFAttributes.__cache__ = {};
Module['glTFAttributes'] = glTFAttributes;
Object.defineProperty(glTFAttributes.prototype, "POSITION", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes__get_POSITION(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAttributes__set_POSITION(self, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "NORMAL", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes__get_NORMAL(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAttributes__set_NORMAL(self, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "TANGENT", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes__get_TANGENT(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAttributes__set_TANGENT(self, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "TEXCOORD_0", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes__get_TEXCOORD_0(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAttributes__set_TEXCOORD_0(self, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "TEXCOORD_1", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes__get_TEXCOORD_1(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAttributes__set_TEXCOORD_1(self, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "COLOR_0", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes__get_COLOR_0(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAttributes__set_COLOR_0(self, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "JOINTS_0", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes__get_JOINTS_0(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAttributes__set_JOINTS_0(self, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "WEIGHTS_0", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes__get_WEIGHTS_0(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFAttributes__set_WEIGHTS_0(self, value);
    }
});
glTFAttributes.prototype["__destroy__"] = glTFAttributes.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFAttributes__destroy(self);
};
// glTFBuffer
function glTFBuffer() {
    this.ptr = _glTFBuffer_glTFBuffer_0(); getCache(glTFBuffer)[this.ptr] = this;
    this.type = glTFBuffer;
};
glTFBuffer.prototype = Object.create(WrapperObject.prototype);
glTFBuffer.prototype.constructor = glTFBuffer;
glTFBuffer.prototype.__class__ = glTFBuffer;
glTFBuffer.__cache__ = {};
Module['glTFBuffer'] = glTFBuffer;
Object.defineProperty(glTFBuffer.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFBuffer__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFBuffer__set_name(self, value);
    }
});
Object.defineProperty(glTFBuffer.prototype, "mime_type", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFBuffer__get_mime_type(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFBuffer__set_mime_type(self, value);
    }
});
Object.defineProperty(glTFBuffer.prototype, "uri", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFBuffer__get_uri(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFBuffer__set_uri(self, value);
    }
});
Object.defineProperty(glTFBuffer.prototype, "byte_length", {
    get: function() {
        var self = this.ptr;
        return _glTFBuffer__get_byte_length(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFBuffer__set_byte_length(self, value);
    }
});
glTFBuffer.prototype["__destroy__"] = glTFBuffer.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFBuffer__destroy(self);
};
// glTFBufferView
function glTFBufferView() {
    this.ptr = _glTFBufferView_glTFBufferView_0(); getCache(glTFBufferView)[this.ptr] = this;
    this.type = glTFBufferView;
};
glTFBufferView.prototype = Object.create(WrapperObject.prototype);
glTFBufferView.prototype.constructor = glTFBufferView;
glTFBufferView.prototype.__class__ = glTFBufferView;
glTFBufferView.__cache__ = {};
Module['glTFBufferView'] = glTFBufferView;
Object.defineProperty(glTFBufferView.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFBufferView__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFBufferView__set_name(self, value);
    }
});
Object.defineProperty(glTFBufferView.prototype, "buffer", {
    get: function() {
        var self = this.ptr;
        return _glTFBufferView__get_buffer(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFBufferView__set_buffer(self, value);
    }
});
Object.defineProperty(glTFBufferView.prototype, "byte_offset", {
    get: function() {
        var self = this.ptr;
        return _glTFBufferView__get_byte_offset(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <size_t> [] */
        _glTFBufferView__set_byte_offset(self, value);
    }
});
Object.defineProperty(glTFBufferView.prototype, "byte_length", {
    get: function() {
        var self = this.ptr;
        return _glTFBufferView__get_byte_length(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <size_t> [] */
        _glTFBufferView__set_byte_length(self, value);
    }
});
Object.defineProperty(glTFBufferView.prototype, "byte_stride", {
    get: function() {
        var self = this.ptr;
        return _glTFBufferView__get_byte_stride(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <size_t> [] */
        _glTFBufferView__set_byte_stride(self, value);
    }
});
Object.defineProperty(glTFBufferView.prototype, "target", {
    get: function() {
        var self = this.ptr;
        return _glTFBufferView__get_target(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFBufferView__set_target(self, value);
    }
});
glTFBufferView.prototype["__destroy__"] = glTFBufferView.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFBufferView__destroy(self);
};
// glTFCamera
function glTFCamera() {
    this.ptr = _glTFCamera_glTFCamera_0(); getCache(glTFCamera)[this.ptr] = this;
    this.type = glTFCamera;
};
glTFCamera.prototype = Object.create(WrapperObject.prototype);
glTFCamera.prototype.constructor = glTFCamera;
glTFCamera.prototype.__class__ = glTFCamera;
glTFCamera.__cache__ = {};
Module['glTFCamera'] = glTFCamera;
Object.defineProperty(glTFCamera.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFCamera__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFCamera__set_name(self, value);
    }
});
Object.defineProperty(glTFCamera.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFCamera__get_type(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFCamera__set_type(self, value);
    }
});
Object.defineProperty(glTFCamera.prototype, "orthographic", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFCamera__get_orthographic(self), glTFOrthographic);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFOrthographic> [] */
        value = value.ptr;
        _glTFCamera__set_orthographic(self, value);
    }
});
Object.defineProperty(glTFCamera.prototype, "perspective", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFCamera__get_perspective(self), glTFPerspective);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFPerspective> [] */
        value = value.ptr;
        _glTFCamera__set_perspective(self, value);
    }
});
glTFCamera.prototype["__destroy__"] = glTFCamera.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFCamera__destroy(self);
};
// glTFImage
function glTFImage() {
    this.ptr = _glTFImage_glTFImage_0(); getCache(glTFImage)[this.ptr] = this;
    this.type = glTFImage;
};
glTFImage.prototype = Object.create(WrapperObject.prototype);
glTFImage.prototype.constructor = glTFImage;
glTFImage.prototype.__class__ = glTFImage;
glTFImage.__cache__ = {};
Module['glTFImage'] = glTFImage;
Object.defineProperty(glTFImage.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFImage__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFImage__set_name(self, value);
    }
});
Object.defineProperty(glTFImage.prototype, "mime_type", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFImage__get_mime_type(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFImage__set_mime_type(self, value);
    }
});
Object.defineProperty(glTFImage.prototype, "uri", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFImage__get_uri(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFImage__set_uri(self, value);
    }
});
Object.defineProperty(glTFImage.prototype, "buffer_view", {
    get: function() {
        var self = this.ptr;
        return _glTFImage__get_buffer_view(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFImage__set_buffer_view(self, value);
    }
});
glTFImage.prototype["__destroy__"] = glTFImage.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFImage__destroy(self);
};
// glTFMaterial
function glTFMaterial() {
    this.ptr = _glTFMaterial_glTFMaterial_0(); getCache(glTFMaterial)[this.ptr] = this;
    this.type = glTFMaterial;
};
glTFMaterial.prototype = Object.create(WrapperObject.prototype);
glTFMaterial.prototype.constructor = glTFMaterial;
glTFMaterial.prototype.__class__ = glTFMaterial;
glTFMaterial.__cache__ = {};
Module['glTFMaterial'] = glTFMaterial;
Object.defineProperty(glTFMaterial.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFMaterial__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFMaterial__set_name(self, value);
    }
});
Object.defineProperty(glTFMaterial.prototype, "normal_texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterial__get_normal_texture(self), glTFTextureInfo);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFTextureInfo> [] */
        value = value.ptr;
        _glTFMaterial__set_normal_texture(self, value);
    }
});
Object.defineProperty(glTFMaterial.prototype, "occlusion_texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterial__get_occlusion_texture(self), glTFTextureInfo);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFTextureInfo> [] */
        value = value.ptr;
        _glTFMaterial__set_occlusion_texture(self, value);
    }
});
Object.defineProperty(glTFMaterial.prototype, "emissive_factor", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterial__get_emissive_factor(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _glTFMaterial__set_emissive_factor(self, value);
    }
});
Object.defineProperty(glTFMaterial.prototype, "emissive_texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterial__get_emissive_texture(self), glTFTextureInfo);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFTextureInfo> [] */
        value = value.ptr;
        _glTFMaterial__set_emissive_texture(self, value);
    }
});
Object.defineProperty(glTFMaterial.prototype, "double_sided", {
    get: function() {
        var self = this.ptr;
        return !!(_glTFMaterial__get_double_sided(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _glTFMaterial__set_double_sided(self, value);
    }
});
Object.defineProperty(glTFMaterial.prototype, "alpha_mode", {
    get: function() {
        var self = this.ptr;
        return _glTFMaterial__get_alpha_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFAlphaMode> [] */
        if (value && typeof value === "object") value = value.ptr;
        _glTFMaterial__set_alpha_mode(self, value);
    }
});
Object.defineProperty(glTFMaterial.prototype, "pbr_metallic_roughness", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterial__get_pbr_metallic_roughness(self), glTFMaterialPBR);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFMaterialPBR> [] */
        value = value.ptr;
        _glTFMaterial__set_pbr_metallic_roughness(self, value);
    }
});
glTFMaterial.prototype["__destroy__"] = glTFMaterial.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFMaterial__destroy(self);
};
// glTFMaterialPBR
function glTFMaterialPBR() {
    this.ptr = _glTFMaterialPBR_glTFMaterialPBR_0(); getCache(glTFMaterialPBR)[this.ptr] = this;
    this.type = glTFMaterialPBR;
};
glTFMaterialPBR.prototype = Object.create(WrapperObject.prototype);
glTFMaterialPBR.prototype.constructor = glTFMaterialPBR;
glTFMaterialPBR.prototype.__class__ = glTFMaterialPBR;
glTFMaterialPBR.__cache__ = {};
Module['glTFMaterialPBR'] = glTFMaterialPBR;
Object.defineProperty(glTFMaterialPBR.prototype, "base_color_factor", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterialPBR__get_base_color_factor(self), vec4);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec4> [] */
        value = value.ptr;
        _glTFMaterialPBR__set_base_color_factor(self, value);
    }
});
Object.defineProperty(glTFMaterialPBR.prototype, "base_color_texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterialPBR__get_base_color_texture(self), glTFTextureInfo);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFTextureInfo> [] */
        value = value.ptr;
        _glTFMaterialPBR__set_base_color_texture(self, value);
    }
});
Object.defineProperty(glTFMaterialPBR.prototype, "metallic_factor", {
    get: function() {
        var self = this.ptr;
        return _glTFMaterialPBR__get_metallic_factor(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _glTFMaterialPBR__set_metallic_factor(self, value);
    }
});
Object.defineProperty(glTFMaterialPBR.prototype, "roughness_factor", {
    get: function() {
        var self = this.ptr;
        return _glTFMaterialPBR__get_roughness_factor(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _glTFMaterialPBR__set_roughness_factor(self, value);
    }
});
Object.defineProperty(glTFMaterialPBR.prototype, "metallic_roughness_texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterialPBR__get_metallic_roughness_texture(self), glTFTextureInfo);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFTextureInfo> [] */
        value = value.ptr;
        _glTFMaterialPBR__set_metallic_roughness_texture(self, value);
    }
});
glTFMaterialPBR.prototype["__destroy__"] = glTFMaterialPBR.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFMaterialPBR__destroy(self);
};
// glTFMesh
function glTFMesh() {
    this.ptr = _glTFMesh_glTFMesh_0(); getCache(glTFMesh)[this.ptr] = this;
    this.type = glTFMesh;
};
glTFMesh.prototype = Object.create(WrapperObject.prototype);
glTFMesh.prototype.constructor = glTFMesh;
glTFMesh.prototype.__class__ = glTFMesh;
glTFMesh.__cache__ = {};
Module['glTFMesh'] = glTFMesh;
Object.defineProperty(glTFMesh.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFMesh__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFMesh__set_name(self, value);
    }
});
glTFMesh.prototype["__destroy__"] = glTFMesh.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFMesh__destroy(self);
};
// glTFMorphTarget
function glTFMorphTarget() {
    this.ptr = _glTFMorphTarget_glTFMorphTarget_0(); getCache(glTFMorphTarget)[this.ptr] = this;
    this.type = glTFMorphTarget;
};
glTFMorphTarget.prototype = Object.create(WrapperObject.prototype);
glTFMorphTarget.prototype.constructor = glTFMorphTarget;
glTFMorphTarget.prototype.__class__ = glTFMorphTarget;
glTFMorphTarget.__cache__ = {};
Module['glTFMorphTarget'] = glTFMorphTarget;
Object.defineProperty(glTFMorphTarget.prototype, "POSITION", {
    get: function() {
        var self = this.ptr;
        return _glTFMorphTarget__get_POSITION(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFMorphTarget__set_POSITION(self, value);
    }
});
Object.defineProperty(glTFMorphTarget.prototype, "NORMAL", {
    get: function() {
        var self = this.ptr;
        return _glTFMorphTarget__get_NORMAL(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFMorphTarget__set_NORMAL(self, value);
    }
});
Object.defineProperty(glTFMorphTarget.prototype, "TANGENT", {
    get: function() {
        var self = this.ptr;
        return _glTFMorphTarget__get_TANGENT(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFMorphTarget__set_TANGENT(self, value);
    }
});
glTFMorphTarget.prototype["__destroy__"] = glTFMorphTarget.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFMorphTarget__destroy(self);
};
// glTFNode
function glTFNode() {
    this.ptr = _glTFNode_glTFNode_0(); getCache(glTFNode)[this.ptr] = this;
    this.type = glTFNode;
};
glTFNode.prototype = Object.create(WrapperObject.prototype);
glTFNode.prototype.constructor = glTFNode;
glTFNode.prototype.__class__ = glTFNode;
glTFNode.__cache__ = {};
Module['glTFNode'] = glTFNode;
Object.defineProperty(glTFNode.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFNode__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFNode__set_name(self, value);
    }
});
Object.defineProperty(glTFNode.prototype, "mesh", {
    get: function() {
        var self = this.ptr;
        return _glTFNode__get_mesh(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFNode__set_mesh(self, value);
    }
});
Object.defineProperty(glTFNode.prototype, "camera", {
    get: function() {
        var self = this.ptr;
        return _glTFNode__get_camera(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFNode__set_camera(self, value);
    }
});
Object.defineProperty(glTFNode.prototype, "skin", {
    get: function() {
        var self = this.ptr;
        return _glTFNode__get_skin(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFNode__set_skin(self, value);
    }
});
Object.defineProperty(glTFNode.prototype, "matrix", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFNode__get_matrix(self), mat4);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <mat4> [] */
        value = value.ptr;
        _glTFNode__set_matrix(self, value);
    }
});
Object.defineProperty(glTFNode.prototype, "translation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFNode__get_translation(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _glTFNode__set_translation(self, value);
    }
});
Object.defineProperty(glTFNode.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFNode__get_rotation(self), quat);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <quat> [] */
        value = value.ptr;
        _glTFNode__set_rotation(self, value);
    }
});
Object.defineProperty(glTFNode.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFNode__get_scale(self), vec3);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec3> [] */
        value = value.ptr;
        _glTFNode__set_scale(self, value);
    }
});
glTFNode.prototype["__destroy__"] = glTFNode.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFNode__destroy(self);
};
// glTFNodeExtras
function glTFNodeExtras() {
    this.ptr = _glTFNodeExtras_glTFNodeExtras_0(); getCache(glTFNodeExtras)[this.ptr] = this;
    this.type = glTFNodeExtras;
};
glTFNodeExtras.prototype = Object.create(WrapperObject.prototype);
glTFNodeExtras.prototype.constructor = glTFNodeExtras;
glTFNodeExtras.prototype.__class__ = glTFNodeExtras;
glTFNodeExtras.__cache__ = {};
Module['glTFNodeExtras'] = glTFNodeExtras;
glTFNodeExtras.prototype["__destroy__"] = glTFNodeExtras.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFNodeExtras__destroy(self);
};
// glTFOrthographic
function glTFOrthographic() {
    this.ptr = _glTFOrthographic_glTFOrthographic_0(); getCache(glTFOrthographic)[this.ptr] = this;
    this.type = glTFOrthographic;
};
glTFOrthographic.prototype = Object.create(WrapperObject.prototype);
glTFOrthographic.prototype.constructor = glTFOrthographic;
glTFOrthographic.prototype.__class__ = glTFOrthographic;
glTFOrthographic.__cache__ = {};
Module['glTFOrthographic'] = glTFOrthographic;
Object.defineProperty(glTFOrthographic.prototype, "xmag", {
    get: function() {
        var self = this.ptr;
        return _glTFOrthographic__get_xmag(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _glTFOrthographic__set_xmag(self, value);
    }
});
Object.defineProperty(glTFOrthographic.prototype, "ymag", {
    get: function() {
        var self = this.ptr;
        return _glTFOrthographic__get_ymag(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _glTFOrthographic__set_ymag(self, value);
    }
});
Object.defineProperty(glTFOrthographic.prototype, "zfar", {
    get: function() {
        var self = this.ptr;
        return _glTFOrthographic__get_zfar(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _glTFOrthographic__set_zfar(self, value);
    }
});
Object.defineProperty(glTFOrthographic.prototype, "znear", {
    get: function() {
        var self = this.ptr;
        return _glTFOrthographic__get_znear(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _glTFOrthographic__set_znear(self, value);
    }
});
glTFOrthographic.prototype["__destroy__"] = glTFOrthographic.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFOrthographic__destroy(self);
};
// glTFPerspective
function glTFPerspective() {
    this.ptr = _glTFPerspective_glTFPerspective_0(); getCache(glTFPerspective)[this.ptr] = this;
    this.type = glTFPerspective;
};
glTFPerspective.prototype = Object.create(WrapperObject.prototype);
glTFPerspective.prototype.constructor = glTFPerspective;
glTFPerspective.prototype.__class__ = glTFPerspective;
glTFPerspective.__cache__ = {};
Module['glTFPerspective'] = glTFPerspective;
Object.defineProperty(glTFPerspective.prototype, "yfov", {
    get: function() {
        var self = this.ptr;
        return _glTFPerspective__get_yfov(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _glTFPerspective__set_yfov(self, value);
    }
});
Object.defineProperty(glTFPerspective.prototype, "zfar", {
    get: function() {
        var self = this.ptr;
        return _glTFPerspective__get_zfar(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _glTFPerspective__set_zfar(self, value);
    }
});
Object.defineProperty(glTFPerspective.prototype, "znear", {
    get: function() {
        var self = this.ptr;
        return _glTFPerspective__get_znear(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _glTFPerspective__set_znear(self, value);
    }
});
Object.defineProperty(glTFPerspective.prototype, "aspect_ration", {
    get: function() {
        var self = this.ptr;
        return _glTFPerspective__get_aspect_ration(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _glTFPerspective__set_aspect_ration(self, value);
    }
});
glTFPerspective.prototype["__destroy__"] = glTFPerspective.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFPerspective__destroy(self);
};
// glTFPrimitive
function glTFPrimitive() {
    this.ptr = _glTFPrimitive_glTFPrimitive_0(); getCache(glTFPrimitive)[this.ptr] = this;
    this.type = glTFPrimitive;
};
glTFPrimitive.prototype = Object.create(WrapperObject.prototype);
glTFPrimitive.prototype.constructor = glTFPrimitive;
glTFPrimitive.prototype.__class__ = glTFPrimitive;
glTFPrimitive.__cache__ = {};
Module['glTFPrimitive'] = glTFPrimitive;
Object.defineProperty(glTFPrimitive.prototype, "attributes", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFPrimitive__get_attributes(self), glTFAttributes);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFAttributes> [] */
        value = value.ptr;
        _glTFPrimitive__set_attributes(self, value);
    }
});
Object.defineProperty(glTFPrimitive.prototype, "indices", {
    get: function() {
        var self = this.ptr;
        return _glTFPrimitive__get_indices(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFPrimitive__set_indices(self, value);
    }
});
Object.defineProperty(glTFPrimitive.prototype, "material", {
    get: function() {
        var self = this.ptr;
        return _glTFPrimitive__get_material(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFPrimitive__set_material(self, value);
    }
});
Object.defineProperty(glTFPrimitive.prototype, "mode", {
    get: function() {
        var self = this.ptr;
        return _glTFPrimitive__get_mode(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFPrimitiveType> [] */
        if (value && typeof value === "object") value = value.ptr;
        _glTFPrimitive__set_mode(self, value);
    }
});
glTFPrimitive.prototype["__destroy__"] = glTFPrimitive.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFPrimitive__destroy(self);
};
// glTFSampler
function glTFSampler() {
    this.ptr = _glTFSampler_glTFSampler_0(); getCache(glTFSampler)[this.ptr] = this;
    this.type = glTFSampler;
};
glTFSampler.prototype = Object.create(WrapperObject.prototype);
glTFSampler.prototype.constructor = glTFSampler;
glTFSampler.prototype.__class__ = glTFSampler;
glTFSampler.__cache__ = {};
Module['glTFSampler'] = glTFSampler;
Object.defineProperty(glTFSampler.prototype, "mag_filter", {
    get: function() {
        var self = this.ptr;
        return _glTFSampler__get_mag_filter(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFSampler__set_mag_filter(self, value);
    }
});
Object.defineProperty(glTFSampler.prototype, "min_filter", {
    get: function() {
        var self = this.ptr;
        return _glTFSampler__get_min_filter(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFSampler__set_min_filter(self, value);
    }
});
Object.defineProperty(glTFSampler.prototype, "wrap_s", {
    get: function() {
        var self = this.ptr;
        return _glTFSampler__get_wrap_s(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFSampler__set_wrap_s(self, value);
    }
});
Object.defineProperty(glTFSampler.prototype, "wrap_t", {
    get: function() {
        var self = this.ptr;
        return _glTFSampler__get_wrap_t(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFSampler__set_wrap_t(self, value);
    }
});
Object.defineProperty(glTFSampler.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFSampler__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFSampler__set_name(self, value);
    }
});
glTFSampler.prototype["__destroy__"] = glTFSampler.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFSampler__destroy(self);
};
// glTFScene
function glTFScene() {
    this.ptr = _glTFScene_glTFScene_0(); getCache(glTFScene)[this.ptr] = this;
    this.type = glTFScene;
};
glTFScene.prototype = Object.create(WrapperObject.prototype);
glTFScene.prototype.constructor = glTFScene;
glTFScene.prototype.__class__ = glTFScene;
glTFScene.__cache__ = {};
Module['glTFScene'] = glTFScene;
Object.defineProperty(glTFScene.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFScene__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFScene__set_name(self, value);
    }
});
glTFScene.prototype["__destroy__"] = glTFScene.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFScene__destroy(self);
};
// glTFSkin
function glTFSkin() {
    this.ptr = _glTFSkin_glTFSkin_0(); getCache(glTFSkin)[this.ptr] = this;
    this.type = glTFSkin;
};
glTFSkin.prototype = Object.create(WrapperObject.prototype);
glTFSkin.prototype.constructor = glTFSkin;
glTFSkin.prototype.__class__ = glTFSkin;
glTFSkin.__cache__ = {};
Module['glTFSkin'] = glTFSkin;
Object.defineProperty(glTFSkin.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFSkin__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFSkin__set_name(self, value);
    }
});
Object.defineProperty(glTFSkin.prototype, "skeleton", {
    get: function() {
        var self = this.ptr;
        return _glTFSkin__get_skeleton(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFSkin__set_skeleton(self, value);
    }
});
Object.defineProperty(glTFSkin.prototype, "inverse_bind_matrices", {
    get: function() {
        var self = this.ptr;
        return _glTFSkin__get_inverse_bind_matrices(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFSkin__set_inverse_bind_matrices(self, value);
    }
});
glTFSkin.prototype["__destroy__"] = glTFSkin.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFSkin__destroy(self);
};
// glTFSparse
function glTFSparse() {
    this.ptr = _glTFSparse_glTFSparse_0(); getCache(glTFSparse)[this.ptr] = this;
    this.type = glTFSparse;
};
glTFSparse.prototype = Object.create(WrapperObject.prototype);
glTFSparse.prototype.constructor = glTFSparse;
glTFSparse.prototype.__class__ = glTFSparse;
glTFSparse.__cache__ = {};
Module['glTFSparse'] = glTFSparse;
Object.defineProperty(glTFSparse.prototype, "count", {
    get: function() {
        var self = this.ptr;
        return _glTFSparse__get_count(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFSparse__set_count(self, value);
    }
});
Object.defineProperty(glTFSparse.prototype, "indices", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFSparse__get_indices(self), glTFSparseIndices);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFSparseIndices> [] */
        value = value.ptr;
        _glTFSparse__set_indices(self, value);
    }
});
Object.defineProperty(glTFSparse.prototype, "values", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFSparse__get_values(self), glTFSparseValues);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFSparseValues> [] */
        value = value.ptr;
        _glTFSparse__set_values(self, value);
    }
});
glTFSparse.prototype["__destroy__"] = glTFSparse.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFSparse__destroy(self);
};
// glTFSparseIndices
function glTFSparseIndices() {
    this.ptr = _glTFSparseIndices_glTFSparseIndices_0(); getCache(glTFSparseIndices)[this.ptr] = this;
    this.type = glTFSparseIndices;
};
glTFSparseIndices.prototype = Object.create(WrapperObject.prototype);
glTFSparseIndices.prototype.constructor = glTFSparseIndices;
glTFSparseIndices.prototype.__class__ = glTFSparseIndices;
glTFSparseIndices.__cache__ = {};
Module['glTFSparseIndices'] = glTFSparseIndices;
Object.defineProperty(glTFSparseIndices.prototype, "buffer_view", {
    get: function() {
        var self = this.ptr;
        return _glTFSparseIndices__get_buffer_view(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFSparseIndices__set_buffer_view(self, value);
    }
});
Object.defineProperty(glTFSparseIndices.prototype, "byte_offset", {
    get: function() {
        var self = this.ptr;
        return _glTFSparseIndices__get_byte_offset(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFSparseIndices__set_byte_offset(self, value);
    }
});
Object.defineProperty(glTFSparseIndices.prototype, "component_type", {
    get: function() {
        var self = this.ptr;
        return _glTFSparseIndices__get_component_type(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <glTFComponentType> [] */
        if (value && typeof value === "object") value = value.ptr;
        _glTFSparseIndices__set_component_type(self, value);
    }
});
glTFSparseIndices.prototype["__destroy__"] = glTFSparseIndices.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFSparseIndices__destroy(self);
};
// glTFSparseValues
function glTFSparseValues() {
    this.ptr = _glTFSparseValues_glTFSparseValues_0(); getCache(glTFSparseValues)[this.ptr] = this;
    this.type = glTFSparseValues;
};
glTFSparseValues.prototype = Object.create(WrapperObject.prototype);
glTFSparseValues.prototype.constructor = glTFSparseValues;
glTFSparseValues.prototype.__class__ = glTFSparseValues;
glTFSparseValues.__cache__ = {};
Module['glTFSparseValues'] = glTFSparseValues;
Object.defineProperty(glTFSparseValues.prototype, "buffer_view", {
    get: function() {
        var self = this.ptr;
        return _glTFSparseValues__get_buffer_view(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFSparseValues__set_buffer_view(self, value);
    }
});
Object.defineProperty(glTFSparseValues.prototype, "byte_offset", {
    get: function() {
        var self = this.ptr;
        return _glTFSparseValues__get_byte_offset(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFSparseValues__set_byte_offset(self, value);
    }
});
glTFSparseValues.prototype["__destroy__"] = glTFSparseValues.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFSparseValues__destroy(self);
};
// glTFTexture
function glTFTexture() {
    this.ptr = _glTFTexture_glTFTexture_0(); getCache(glTFTexture)[this.ptr] = this;
    this.type = glTFTexture;
};
glTFTexture.prototype = Object.create(WrapperObject.prototype);
glTFTexture.prototype.constructor = glTFTexture;
glTFTexture.prototype.__class__ = glTFTexture;
glTFTexture.__cache__ = {};
Module['glTFTexture'] = glTFTexture;
Object.defineProperty(glTFTexture.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFTexture__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _glTFTexture__set_name(self, value);
    }
});
Object.defineProperty(glTFTexture.prototype, "sampler", {
    get: function() {
        var self = this.ptr;
        return _glTFTexture__get_sampler(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFTexture__set_sampler(self, value);
    }
});
Object.defineProperty(glTFTexture.prototype, "source", {
    get: function() {
        var self = this.ptr;
        return _glTFTexture__get_source(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFTexture__set_source(self, value);
    }
});
glTFTexture.prototype["__destroy__"] = glTFTexture.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFTexture__destroy(self);
};
// glTFTextureInfo
function glTFTextureInfo() {
    this.ptr = _glTFTextureInfo_glTFTextureInfo_0(); getCache(glTFTextureInfo)[this.ptr] = this;
    this.type = glTFTextureInfo;
};
glTFTextureInfo.prototype = Object.create(WrapperObject.prototype);
glTFTextureInfo.prototype.constructor = glTFTextureInfo;
glTFTextureInfo.prototype.__class__ = glTFTextureInfo;
glTFTextureInfo.__cache__ = {};
Module['glTFTextureInfo'] = glTFTextureInfo;
Object.defineProperty(glTFTextureInfo.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _glTFTextureInfo__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _glTFTextureInfo__set_index(self, value);
    }
});
Object.defineProperty(glTFTextureInfo.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return _glTFTextureInfo__get_scale(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _glTFTextureInfo__set_scale(self, value);
    }
});
glTFTextureInfo.prototype["__destroy__"] = glTFTextureInfo.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFTextureInfo__destroy(self);
};

(function() {
    function setup() {
        glTF.__type__ = _glTF__type();
        glTFAccessor.__type__ = _glTFAccessor__type();
        glTFAnimation.__type__ = _glTFAnimation__type();
        glTFAnimationChannel.__type__ = _glTFAnimationChannel__type();
        glTFAnimationSampler.__type__ = _glTFAnimationSampler__type();
        glTFAnimationTarget.__type__ = _glTFAnimationTarget__type();
        glTFAttributes.__type__ = _glTFAttributes__type();
        glTFBuffer.__type__ = _glTFBuffer__type();
        glTFBufferView.__type__ = _glTFBufferView__type();
        glTFCamera.__type__ = _glTFCamera__type();
        glTFImage.__type__ = _glTFImage__type();
        glTFMaterial.__type__ = _glTFMaterial__type();
        glTFMaterialPBR.__type__ = _glTFMaterialPBR__type();
        glTFMesh.__type__ = _glTFMesh__type();
        glTFMorphTarget.__type__ = _glTFMorphTarget__type();
        glTFNode.__type__ = _glTFNode__type();
        glTFNodeExtras.__type__ = _glTFNodeExtras__type();
        glTFOrthographic.__type__ = _glTFOrthographic__type();
        glTFPerspective.__type__ = _glTFPerspective__type();
        glTFPrimitive.__type__ = _glTFPrimitive__type();
        glTFSampler.__type__ = _glTFSampler__type();
        glTFScene.__type__ = _glTFScene__type();
        glTFSkin.__type__ = _glTFSkin__type();
        glTFSparse.__type__ = _glTFSparse__type();
        glTFSparseIndices.__type__ = _glTFSparseIndices__type();
        glTFSparseValues.__type__ = _glTFSparseValues__type();
        glTFTexture.__type__ = _glTFTexture__type();
        glTFTextureInfo.__type__ = _glTFTextureInfo__type();
        // glTFAlphaMode
        Module['glTFAlphaMode'] = Module['glTFAlphaMode'] || {};
        Module['glTFAlphaMode']['OPAQUE'] = _glTFAlphaMode_OPAQUE();
        Module['glTFAlphaMode']['MASK'] = _glTFAlphaMode_MASK();
        Module['glTFAlphaMode']['BLEND'] = _glTFAlphaMode_BLEND();
        // glTFComponentType
        Module['glTFComponentType'] = Module['glTFComponentType'] || {};
        Module['glTFComponentType']['BYTE'] = _glTFComponentType_BYTE();
        Module['glTFComponentType']['UNSIGNED_BYTE'] = _glTFComponentType_UNSIGNED_BYTE();
        Module['glTFComponentType']['SHORT'] = _glTFComponentType_SHORT();
        Module['glTFComponentType']['UNSIGNED_SHORT'] = _glTFComponentType_UNSIGNED_SHORT();
        Module['glTFComponentType']['INT'] = _glTFComponentType_INT();
        Module['glTFComponentType']['FLOAT'] = _glTFComponentType_FLOAT();
        // glTFInterpolation
        Module['glTFInterpolation'] = Module['glTFInterpolation'] || {};
        Module['glTFInterpolation']['LINEAR'] = _glTFInterpolation_LINEAR();
        Module['glTFInterpolation']['STEP'] = _glTFInterpolation_STEP();
        Module['glTFInterpolation']['CATMULLROMSPLINE'] = _glTFInterpolation_CATMULLROMSPLINE();
        Module['glTFInterpolation']['CUBIC_SPLINE'] = _glTFInterpolation_CUBIC_SPLINE();
        // glTFPrimitiveType
        Module['glTFPrimitiveType'] = Module['glTFPrimitiveType'] || {};
        Module['glTFPrimitiveType']['POINTS'] = _glTFPrimitiveType_POINTS();
        Module['glTFPrimitiveType']['LINES'] = _glTFPrimitiveType_LINES();
        Module['glTFPrimitiveType']['LINE_LOOP'] = _glTFPrimitiveType_LINE_LOOP();
        Module['glTFPrimitiveType']['LINE_STRIP'] = _glTFPrimitiveType_LINE_STRIP();
        Module['glTFPrimitiveType']['TRIANGLES'] = _glTFPrimitiveType_TRIANGLES();
        Module['glTFPrimitiveType']['TRIANGLE_STRIP'] = _glTFPrimitiveType_TRIANGLE_STRIP();
        Module['glTFPrimitiveType']['TRIANGLE_FAN'] = _glTFPrimitiveType_TRIANGLE_FAN();
        // glTFType
        Module['glTFType'] = Module['glTFType'] || {};
        Module['glTFType']['SCALAR'] = _glTFType_SCALAR();
        Module['glTFType']['VEC2'] = _glTFType_VEC2();
        Module['glTFType']['VEC3'] = _glTFType_VEC3();
        Module['glTFType']['VEC4'] = _glTFType_VEC4();
        Module['glTFType']['MAT2'] = _glTFType_MAT2();
        Module['glTFType']['MAT3'] = _glTFType_MAT3();
        Module['glTFType']['MAT4'] = _glTFType_MAT4();
        Module['glTFType']['INVALID'] = _glTFType_INVALID();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
