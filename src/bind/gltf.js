Module['stl'] = Module['stl'] || {};
// glTF
function glTF() {
    
    this.__ptr = _glTF__construct_0(); getCache(glTF)[this.__ptr] = this;
};
glTF.prototype = Object.create(WrapperObject.prototype);
glTF.prototype.constructor = glTF;
glTF.prototype.__class = glTF;
glTF.__cache = {};
Module['glTF'] = glTF;
glTF.prototype["__destroy"] = glTF.prototype.__destroy = function() {
    _glTF__destroy(this.__ptr);
};
// glTFAccessor
function glTFAccessor() {
    
    this.__ptr = _glTFAccessor__construct_0(); getCache(glTFAccessor)[this.__ptr] = this;
};
glTFAccessor.prototype = Object.create(WrapperObject.prototype);
glTFAccessor.prototype.constructor = glTFAccessor;
glTFAccessor.prototype.__class = glTFAccessor;
glTFAccessor.__cache = {};
Module['glTFAccessor'] = glTFAccessor;
Object.defineProperty(glTFAccessor.prototype, "name", {
    get: function() {
        return UTF8ToString(_glTFAccessor__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFAccessor.name: expected string');
        _glTFAccessor__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFAccessor.prototype, "buffer_view", {
    get: function() {
        return _glTFAccessor__get_buffer_view(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAccessor.buffer_view: expected integer');
        _glTFAccessor__set_buffer_view(this.__ptr, value);
    }
});
Object.defineProperty(glTFAccessor.prototype, "byte_offset", {
    get: function() {
        return _glTFAccessor__get_byte_offset(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAccessor.byte_offset: expected integer');
        _glTFAccessor__set_byte_offset(this.__ptr, value);
    }
});
Object.defineProperty(glTFAccessor.prototype, "component_type", {
    get: function() {
        return _glTFAccessor__get_component_type(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAccessor.component_type: expected integer');
        _glTFAccessor__set_component_type(this.__ptr, value);
    }
});
Object.defineProperty(glTFAccessor.prototype, "normalized", {
    get: function() {
        return !!(_glTFAccessor__get_normalized(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('glTFAccessor.normalized: expected boolean');
        _glTFAccessor__set_normalized(this.__ptr, value);
    }
});
Object.defineProperty(glTFAccessor.prototype, "count", {
    get: function() {
        return _glTFAccessor__get_count(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAccessor.count: expected integer');
        _glTFAccessor__set_count(this.__ptr, value);
    }
});
Object.defineProperty(glTFAccessor.prototype, "type", {
    get: function() {
        return _glTFAccessor__get_type(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAccessor.type: expected integer');
        _glTFAccessor__set_type(this.__ptr, value);
    }
});
Object.defineProperty(glTFAccessor.prototype, "sparse", {
    get: function() {
        return wrapPointer(_glTFAccessor__get_sparse(this.__ptr), glTFSparse);
    },
    set: function(value) {
        if (!checkClass(value, glTFSparse)) throw Error('glTFAccessor.sparse: expected glTFSparse');
        _glTFAccessor__set_sparse(this.__ptr, value.__ptr);
    }
});
glTFAccessor.prototype["__destroy"] = glTFAccessor.prototype.__destroy = function() {
    _glTFAccessor__destroy(this.__ptr);
};
// glTFAnimation
function glTFAnimation() {
    
    this.__ptr = _glTFAnimation__construct_0(); getCache(glTFAnimation)[this.__ptr] = this;
};
glTFAnimation.prototype = Object.create(WrapperObject.prototype);
glTFAnimation.prototype.constructor = glTFAnimation;
glTFAnimation.prototype.__class = glTFAnimation;
glTFAnimation.__cache = {};
Module['glTFAnimation'] = glTFAnimation;
Object.defineProperty(glTFAnimation.prototype, "name", {
    get: function() {
        return UTF8ToString(_glTFAnimation__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFAnimation.name: expected string');
        _glTFAnimation__set_name(this.__ptr, ensureString(value));
    }
});
glTFAnimation.prototype["__destroy"] = glTFAnimation.prototype.__destroy = function() {
    _glTFAnimation__destroy(this.__ptr);
};
// glTFAnimationChannel
function glTFAnimationChannel() {
    
    this.__ptr = _glTFAnimationChannel__construct_0(); getCache(glTFAnimationChannel)[this.__ptr] = this;
};
glTFAnimationChannel.prototype = Object.create(WrapperObject.prototype);
glTFAnimationChannel.prototype.constructor = glTFAnimationChannel;
glTFAnimationChannel.prototype.__class = glTFAnimationChannel;
glTFAnimationChannel.__cache = {};
Module['glTFAnimationChannel'] = glTFAnimationChannel;
Object.defineProperty(glTFAnimationChannel.prototype, "sampler", {
    get: function() {
        return _glTFAnimationChannel__get_sampler(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAnimationChannel.sampler: expected integer');
        _glTFAnimationChannel__set_sampler(this.__ptr, value);
    }
});
Object.defineProperty(glTFAnimationChannel.prototype, "target", {
    get: function() {
        return wrapPointer(_glTFAnimationChannel__get_target(this.__ptr), glTFAnimationTarget);
    },
    set: function(value) {
        if (!checkClass(value, glTFAnimationTarget)) throw Error('glTFAnimationChannel.target: expected glTFAnimationTarget');
        _glTFAnimationChannel__set_target(this.__ptr, value.__ptr);
    }
});
glTFAnimationChannel.prototype["__destroy"] = glTFAnimationChannel.prototype.__destroy = function() {
    _glTFAnimationChannel__destroy(this.__ptr);
};
// glTFAnimationSampler
function glTFAnimationSampler() {
    
    this.__ptr = _glTFAnimationSampler__construct_0(); getCache(glTFAnimationSampler)[this.__ptr] = this;
};
glTFAnimationSampler.prototype = Object.create(WrapperObject.prototype);
glTFAnimationSampler.prototype.constructor = glTFAnimationSampler;
glTFAnimationSampler.prototype.__class = glTFAnimationSampler;
glTFAnimationSampler.__cache = {};
Module['glTFAnimationSampler'] = glTFAnimationSampler;
Object.defineProperty(glTFAnimationSampler.prototype, "interpolation", {
    get: function() {
        return _glTFAnimationSampler__get_interpolation(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAnimationSampler.interpolation: expected integer');
        _glTFAnimationSampler__set_interpolation(this.__ptr, value);
    }
});
Object.defineProperty(glTFAnimationSampler.prototype, "input", {
    get: function() {
        return _glTFAnimationSampler__get_input(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAnimationSampler.input: expected integer');
        _glTFAnimationSampler__set_input(this.__ptr, value);
    }
});
Object.defineProperty(glTFAnimationSampler.prototype, "output", {
    get: function() {
        return _glTFAnimationSampler__get_output(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAnimationSampler.output: expected integer');
        _glTFAnimationSampler__set_output(this.__ptr, value);
    }
});
glTFAnimationSampler.prototype["__destroy"] = glTFAnimationSampler.prototype.__destroy = function() {
    _glTFAnimationSampler__destroy(this.__ptr);
};
// glTFAnimationTarget
function glTFAnimationTarget() {
    
    this.__ptr = _glTFAnimationTarget__construct_0(); getCache(glTFAnimationTarget)[this.__ptr] = this;
};
glTFAnimationTarget.prototype = Object.create(WrapperObject.prototype);
glTFAnimationTarget.prototype.constructor = glTFAnimationTarget;
glTFAnimationTarget.prototype.__class = glTFAnimationTarget;
glTFAnimationTarget.__cache = {};
Module['glTFAnimationTarget'] = glTFAnimationTarget;
Object.defineProperty(glTFAnimationTarget.prototype, "node", {
    get: function() {
        return _glTFAnimationTarget__get_node(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAnimationTarget.node: expected integer');
        _glTFAnimationTarget__set_node(this.__ptr, value);
    }
});
Object.defineProperty(glTFAnimationTarget.prototype, "path", {
    get: function() {
        return UTF8ToString(_glTFAnimationTarget__get_path(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFAnimationTarget.path: expected string');
        _glTFAnimationTarget__set_path(this.__ptr, ensureString(value));
    }
});
glTFAnimationTarget.prototype["__destroy"] = glTFAnimationTarget.prototype.__destroy = function() {
    _glTFAnimationTarget__destroy(this.__ptr);
};
// glTFAttributes
function glTFAttributes() {
    
    this.__ptr = _glTFAttributes__construct_0(); getCache(glTFAttributes)[this.__ptr] = this;
};
glTFAttributes.prototype = Object.create(WrapperObject.prototype);
glTFAttributes.prototype.constructor = glTFAttributes;
glTFAttributes.prototype.__class = glTFAttributes;
glTFAttributes.__cache = {};
Module['glTFAttributes'] = glTFAttributes;
Object.defineProperty(glTFAttributes.prototype, "POSITION", {
    get: function() {
        return _glTFAttributes__get_POSITION(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAttributes.POSITION: expected integer');
        _glTFAttributes__set_POSITION(this.__ptr, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "NORMAL", {
    get: function() {
        return _glTFAttributes__get_NORMAL(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAttributes.NORMAL: expected integer');
        _glTFAttributes__set_NORMAL(this.__ptr, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "TANGENT", {
    get: function() {
        return _glTFAttributes__get_TANGENT(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAttributes.TANGENT: expected integer');
        _glTFAttributes__set_TANGENT(this.__ptr, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "TEXCOORD_0", {
    get: function() {
        return _glTFAttributes__get_TEXCOORD_0(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAttributes.TEXCOORD_0: expected integer');
        _glTFAttributes__set_TEXCOORD_0(this.__ptr, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "TEXCOORD_1", {
    get: function() {
        return _glTFAttributes__get_TEXCOORD_1(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAttributes.TEXCOORD_1: expected integer');
        _glTFAttributes__set_TEXCOORD_1(this.__ptr, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "COLOR_0", {
    get: function() {
        return _glTFAttributes__get_COLOR_0(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAttributes.COLOR_0: expected integer');
        _glTFAttributes__set_COLOR_0(this.__ptr, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "JOINTS_0", {
    get: function() {
        return _glTFAttributes__get_JOINTS_0(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAttributes.JOINTS_0: expected integer');
        _glTFAttributes__set_JOINTS_0(this.__ptr, value);
    }
});
Object.defineProperty(glTFAttributes.prototype, "WEIGHTS_0", {
    get: function() {
        return _glTFAttributes__get_WEIGHTS_0(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFAttributes.WEIGHTS_0: expected integer');
        _glTFAttributes__set_WEIGHTS_0(this.__ptr, value);
    }
});
glTFAttributes.prototype["__destroy"] = glTFAttributes.prototype.__destroy = function() {
    _glTFAttributes__destroy(this.__ptr);
};
// glTFBuffer
function glTFBuffer() {
    
    this.__ptr = _glTFBuffer__construct_0(); getCache(glTFBuffer)[this.__ptr] = this;
};
glTFBuffer.prototype = Object.create(WrapperObject.prototype);
glTFBuffer.prototype.constructor = glTFBuffer;
glTFBuffer.prototype.__class = glTFBuffer;
glTFBuffer.__cache = {};
Module['glTFBuffer'] = glTFBuffer;
Object.defineProperty(glTFBuffer.prototype, "name", {
    get: function() {
        return UTF8ToString(_glTFBuffer__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFBuffer.name: expected string');
        _glTFBuffer__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFBuffer.prototype, "mime_type", {
    get: function() {
        return UTF8ToString(_glTFBuffer__get_mime_type(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFBuffer.mime_type: expected string');
        _glTFBuffer__set_mime_type(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFBuffer.prototype, "uri", {
    get: function() {
        return UTF8ToString(_glTFBuffer__get_uri(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFBuffer.uri: expected string');
        _glTFBuffer__set_uri(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFBuffer.prototype, "byte_length", {
    get: function() {
        return _glTFBuffer__get_byte_length(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFBuffer.byte_length: expected integer');
        _glTFBuffer__set_byte_length(this.__ptr, value);
    }
});
glTFBuffer.prototype["__destroy"] = glTFBuffer.prototype.__destroy = function() {
    _glTFBuffer__destroy(this.__ptr);
};
// glTFBufferView
function glTFBufferView() {
    
    this.__ptr = _glTFBufferView__construct_0(); getCache(glTFBufferView)[this.__ptr] = this;
};
glTFBufferView.prototype = Object.create(WrapperObject.prototype);
glTFBufferView.prototype.constructor = glTFBufferView;
glTFBufferView.prototype.__class = glTFBufferView;
glTFBufferView.__cache = {};
Module['glTFBufferView'] = glTFBufferView;
Object.defineProperty(glTFBufferView.prototype, "name", {
    get: function() {
        return UTF8ToString(_glTFBufferView__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFBufferView.name: expected string');
        _glTFBufferView__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFBufferView.prototype, "buffer", {
    get: function() {
        return _glTFBufferView__get_buffer(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFBufferView.buffer: expected integer');
        _glTFBufferView__set_buffer(this.__ptr, value);
    }
});
Object.defineProperty(glTFBufferView.prototype, "byte_offset", {
    get: function() {
        return _glTFBufferView__get_byte_offset(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFBufferView.byte_offset: expected integer');
        _glTFBufferView__set_byte_offset(this.__ptr, value);
    }
});
Object.defineProperty(glTFBufferView.prototype, "byte_length", {
    get: function() {
        return _glTFBufferView__get_byte_length(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFBufferView.byte_length: expected integer');
        _glTFBufferView__set_byte_length(this.__ptr, value);
    }
});
Object.defineProperty(glTFBufferView.prototype, "byte_stride", {
    get: function() {
        return _glTFBufferView__get_byte_stride(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFBufferView.byte_stride: expected integer');
        _glTFBufferView__set_byte_stride(this.__ptr, value);
    }
});
Object.defineProperty(glTFBufferView.prototype, "target", {
    get: function() {
        return _glTFBufferView__get_target(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFBufferView.target: expected integer');
        _glTFBufferView__set_target(this.__ptr, value);
    }
});
glTFBufferView.prototype["__destroy"] = glTFBufferView.prototype.__destroy = function() {
    _glTFBufferView__destroy(this.__ptr);
};
// glTFCamera
function glTFCamera() {
    
    this.__ptr = _glTFCamera__construct_0(); getCache(glTFCamera)[this.__ptr] = this;
};
glTFCamera.prototype = Object.create(WrapperObject.prototype);
glTFCamera.prototype.constructor = glTFCamera;
glTFCamera.prototype.__class = glTFCamera;
glTFCamera.__cache = {};
Module['glTFCamera'] = glTFCamera;
Object.defineProperty(glTFCamera.prototype, "name", {
    get: function() {
        return UTF8ToString(_glTFCamera__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFCamera.name: expected string');
        _glTFCamera__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFCamera.prototype, "type", {
    get: function() {
        return UTF8ToString(_glTFCamera__get_type(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFCamera.type: expected string');
        _glTFCamera__set_type(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFCamera.prototype, "orthographic", {
    get: function() {
        return wrapPointer(_glTFCamera__get_orthographic(this.__ptr), glTFOrthographic);
    },
    set: function(value) {
        if (!checkClass(value, glTFOrthographic)) throw Error('glTFCamera.orthographic: expected glTFOrthographic');
        _glTFCamera__set_orthographic(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(glTFCamera.prototype, "perspective", {
    get: function() {
        return wrapPointer(_glTFCamera__get_perspective(this.__ptr), glTFPerspective);
    },
    set: function(value) {
        if (!checkClass(value, glTFPerspective)) throw Error('glTFCamera.perspective: expected glTFPerspective');
        _glTFCamera__set_perspective(this.__ptr, value.__ptr);
    }
});
glTFCamera.prototype["__destroy"] = glTFCamera.prototype.__destroy = function() {
    _glTFCamera__destroy(this.__ptr);
};
// glTFImage
function glTFImage() {
    
    this.__ptr = _glTFImage__construct_0(); getCache(glTFImage)[this.__ptr] = this;
};
glTFImage.prototype = Object.create(WrapperObject.prototype);
glTFImage.prototype.constructor = glTFImage;
glTFImage.prototype.__class = glTFImage;
glTFImage.__cache = {};
Module['glTFImage'] = glTFImage;
Object.defineProperty(glTFImage.prototype, "name", {
    get: function() {
        return UTF8ToString(_glTFImage__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFImage.name: expected string');
        _glTFImage__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFImage.prototype, "mime_type", {
    get: function() {
        return UTF8ToString(_glTFImage__get_mime_type(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFImage.mime_type: expected string');
        _glTFImage__set_mime_type(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFImage.prototype, "uri", {
    get: function() {
        return UTF8ToString(_glTFImage__get_uri(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFImage.uri: expected string');
        _glTFImage__set_uri(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFImage.prototype, "buffer_view", {
    get: function() {
        return _glTFImage__get_buffer_view(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFImage.buffer_view: expected integer');
        _glTFImage__set_buffer_view(this.__ptr, value);
    }
});
glTFImage.prototype["__destroy"] = glTFImage.prototype.__destroy = function() {
    _glTFImage__destroy(this.__ptr);
};
// glTFMaterial
function glTFMaterial() {
    
    this.__ptr = _glTFMaterial__construct_0(); getCache(glTFMaterial)[this.__ptr] = this;
};
glTFMaterial.prototype = Object.create(WrapperObject.prototype);
glTFMaterial.prototype.constructor = glTFMaterial;
glTFMaterial.prototype.__class = glTFMaterial;
glTFMaterial.__cache = {};
Module['glTFMaterial'] = glTFMaterial;
Object.defineProperty(glTFMaterial.prototype, "name", {
    get: function() {
        return UTF8ToString(_glTFMaterial__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFMaterial.name: expected string');
        _glTFMaterial__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFMaterial.prototype, "normal_texture", {
    get: function() {
        return wrapPointer(_glTFMaterial__get_normal_texture(this.__ptr), glTFTextureInfo);
    },
    set: function(value) {
        if (!checkClass(value, glTFTextureInfo)) throw Error('glTFMaterial.normal_texture: expected glTFTextureInfo');
        _glTFMaterial__set_normal_texture(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(glTFMaterial.prototype, "occlusion_texture", {
    get: function() {
        return wrapPointer(_glTFMaterial__get_occlusion_texture(this.__ptr), glTFTextureInfo);
    },
    set: function(value) {
        if (!checkClass(value, glTFTextureInfo)) throw Error('glTFMaterial.occlusion_texture: expected glTFTextureInfo');
        _glTFMaterial__set_occlusion_texture(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(glTFMaterial.prototype, "emissive_factor", {
    get: function() {
        return wrapPointer(_glTFMaterial__get_emissive_factor(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('glTFMaterial.emissive_factor: expected v3<float>');
        _glTFMaterial__set_emissive_factor(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(glTFMaterial.prototype, "emissive_texture", {
    get: function() {
        return wrapPointer(_glTFMaterial__get_emissive_texture(this.__ptr), glTFTextureInfo);
    },
    set: function(value) {
        if (!checkClass(value, glTFTextureInfo)) throw Error('glTFMaterial.emissive_texture: expected glTFTextureInfo');
        _glTFMaterial__set_emissive_texture(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(glTFMaterial.prototype, "double_sided", {
    get: function() {
        return !!(_glTFMaterial__get_double_sided(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('glTFMaterial.double_sided: expected boolean');
        _glTFMaterial__set_double_sided(this.__ptr, value);
    }
});
Object.defineProperty(glTFMaterial.prototype, "alpha_mode", {
    get: function() {
        return _glTFMaterial__get_alpha_mode(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFMaterial.alpha_mode: expected integer');
        _glTFMaterial__set_alpha_mode(this.__ptr, value);
    }
});
Object.defineProperty(glTFMaterial.prototype, "pbr_metallic_roughness", {
    get: function() {
        return wrapPointer(_glTFMaterial__get_pbr_metallic_roughness(this.__ptr), glTFMaterialPBR);
    },
    set: function(value) {
        if (!checkClass(value, glTFMaterialPBR)) throw Error('glTFMaterial.pbr_metallic_roughness: expected glTFMaterialPBR');
        _glTFMaterial__set_pbr_metallic_roughness(this.__ptr, value.__ptr);
    }
});
glTFMaterial.prototype["__destroy"] = glTFMaterial.prototype.__destroy = function() {
    _glTFMaterial__destroy(this.__ptr);
};
// glTFMaterialPBR
function glTFMaterialPBR() {
    
    this.__ptr = _glTFMaterialPBR__construct_0(); getCache(glTFMaterialPBR)[this.__ptr] = this;
};
glTFMaterialPBR.prototype = Object.create(WrapperObject.prototype);
glTFMaterialPBR.prototype.constructor = glTFMaterialPBR;
glTFMaterialPBR.prototype.__class = glTFMaterialPBR;
glTFMaterialPBR.__cache = {};
Module['glTFMaterialPBR'] = glTFMaterialPBR;
Object.defineProperty(glTFMaterialPBR.prototype, "base_color_factor", {
    get: function() {
        return wrapPointer(_glTFMaterialPBR__get_base_color_factor(this.__ptr), v4_float);
    },
    set: function(value) {
        if (!checkClass(value, v4_float)) throw Error('glTFMaterialPBR.base_color_factor: expected v4<float>');
        _glTFMaterialPBR__set_base_color_factor(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(glTFMaterialPBR.prototype, "base_color_texture", {
    get: function() {
        return wrapPointer(_glTFMaterialPBR__get_base_color_texture(this.__ptr), glTFTextureInfo);
    },
    set: function(value) {
        if (!checkClass(value, glTFTextureInfo)) throw Error('glTFMaterialPBR.base_color_texture: expected glTFTextureInfo');
        _glTFMaterialPBR__set_base_color_texture(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(glTFMaterialPBR.prototype, "metallic_factor", {
    get: function() {
        return _glTFMaterialPBR__get_metallic_factor(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFMaterialPBR.metallic_factor: expected number');
        _glTFMaterialPBR__set_metallic_factor(this.__ptr, value);
    }
});
Object.defineProperty(glTFMaterialPBR.prototype, "roughness_factor", {
    get: function() {
        return _glTFMaterialPBR__get_roughness_factor(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFMaterialPBR.roughness_factor: expected number');
        _glTFMaterialPBR__set_roughness_factor(this.__ptr, value);
    }
});
Object.defineProperty(glTFMaterialPBR.prototype, "metallic_roughness_texture", {
    get: function() {
        return wrapPointer(_glTFMaterialPBR__get_metallic_roughness_texture(this.__ptr), glTFTextureInfo);
    },
    set: function(value) {
        if (!checkClass(value, glTFTextureInfo)) throw Error('glTFMaterialPBR.metallic_roughness_texture: expected glTFTextureInfo');
        _glTFMaterialPBR__set_metallic_roughness_texture(this.__ptr, value.__ptr);
    }
});
glTFMaterialPBR.prototype["__destroy"] = glTFMaterialPBR.prototype.__destroy = function() {
    _glTFMaterialPBR__destroy(this.__ptr);
};
// glTFMesh
function glTFMesh() {
    
    this.__ptr = _glTFMesh__construct_0(); getCache(glTFMesh)[this.__ptr] = this;
};
glTFMesh.prototype = Object.create(WrapperObject.prototype);
glTFMesh.prototype.constructor = glTFMesh;
glTFMesh.prototype.__class = glTFMesh;
glTFMesh.__cache = {};
Module['glTFMesh'] = glTFMesh;
Object.defineProperty(glTFMesh.prototype, "name", {
    get: function() {
        return UTF8ToString(_glTFMesh__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFMesh.name: expected string');
        _glTFMesh__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFMesh.prototype, "weights", {
    get: function() {
        return _glTFMesh__get_weights(this.__ptr);
    }});
glTFMesh.prototype["__destroy"] = glTFMesh.prototype.__destroy = function() {
    _glTFMesh__destroy(this.__ptr);
};
// glTFMorphTarget
function glTFMorphTarget() {
    
    this.__ptr = _glTFMorphTarget__construct_0(); getCache(glTFMorphTarget)[this.__ptr] = this;
};
glTFMorphTarget.prototype = Object.create(WrapperObject.prototype);
glTFMorphTarget.prototype.constructor = glTFMorphTarget;
glTFMorphTarget.prototype.__class = glTFMorphTarget;
glTFMorphTarget.__cache = {};
Module['glTFMorphTarget'] = glTFMorphTarget;
Object.defineProperty(glTFMorphTarget.prototype, "POSITION", {
    get: function() {
        return _glTFMorphTarget__get_POSITION(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFMorphTarget.POSITION: expected integer');
        _glTFMorphTarget__set_POSITION(this.__ptr, value);
    }
});
Object.defineProperty(glTFMorphTarget.prototype, "NORMAL", {
    get: function() {
        return _glTFMorphTarget__get_NORMAL(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFMorphTarget.NORMAL: expected integer');
        _glTFMorphTarget__set_NORMAL(this.__ptr, value);
    }
});
Object.defineProperty(glTFMorphTarget.prototype, "TANGENT", {
    get: function() {
        return _glTFMorphTarget__get_TANGENT(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFMorphTarget.TANGENT: expected integer');
        _glTFMorphTarget__set_TANGENT(this.__ptr, value);
    }
});
glTFMorphTarget.prototype["__destroy"] = glTFMorphTarget.prototype.__destroy = function() {
    _glTFMorphTarget__destroy(this.__ptr);
};
// glTFNode
function glTFNode() {
    
    this.__ptr = _glTFNode__construct_0(); getCache(glTFNode)[this.__ptr] = this;
};
glTFNode.prototype = Object.create(WrapperObject.prototype);
glTFNode.prototype.constructor = glTFNode;
glTFNode.prototype.__class = glTFNode;
glTFNode.__cache = {};
Module['glTFNode'] = glTFNode;
Object.defineProperty(glTFNode.prototype, "name", {
    get: function() {
        return UTF8ToString(_glTFNode__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFNode.name: expected string');
        _glTFNode__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFNode.prototype, "mesh", {
    get: function() {
        return _glTFNode__get_mesh(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFNode.mesh: expected integer');
        _glTFNode__set_mesh(this.__ptr, value);
    }
});
Object.defineProperty(glTFNode.prototype, "camera", {
    get: function() {
        return _glTFNode__get_camera(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFNode.camera: expected integer');
        _glTFNode__set_camera(this.__ptr, value);
    }
});
Object.defineProperty(glTFNode.prototype, "skin", {
    get: function() {
        return _glTFNode__get_skin(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFNode.skin: expected integer');
        _glTFNode__set_skin(this.__ptr, value);
    }
});
Object.defineProperty(glTFNode.prototype, "matrix", {
    get: function() {
        return wrapPointer(_glTFNode__get_matrix(this.__ptr), mat4);
    },
    set: function(value) {
        if (!checkClass(value, mat4)) throw Error('glTFNode.matrix: expected mat4');
        _glTFNode__set_matrix(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(glTFNode.prototype, "translation", {
    get: function() {
        return wrapPointer(_glTFNode__get_translation(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('glTFNode.translation: expected v3<float>');
        _glTFNode__set_translation(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(glTFNode.prototype, "rotation", {
    get: function() {
        return wrapPointer(_glTFNode__get_rotation(this.__ptr), quat);
    },
    set: function(value) {
        if (!checkClass(value, quat)) throw Error('glTFNode.rotation: expected quat');
        _glTFNode__set_rotation(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(glTFNode.prototype, "scale", {
    get: function() {
        return wrapPointer(_glTFNode__get_scale(this.__ptr), v3_float);
    },
    set: function(value) {
        if (!checkClass(value, v3_float)) throw Error('glTFNode.scale: expected v3<float>');
        _glTFNode__set_scale(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(glTFNode.prototype, "children", {
    get: function() {
        return _glTFNode__get_children(this.__ptr);
    }});
glTFNode.prototype["__destroy"] = glTFNode.prototype.__destroy = function() {
    _glTFNode__destroy(this.__ptr);
};
// glTFNodeExtras
function glTFNodeExtras() {
    
    this.__ptr = _glTFNodeExtras__construct_0(); getCache(glTFNodeExtras)[this.__ptr] = this;
};
glTFNodeExtras.prototype = Object.create(WrapperObject.prototype);
glTFNodeExtras.prototype.constructor = glTFNodeExtras;
glTFNodeExtras.prototype.__class = glTFNodeExtras;
glTFNodeExtras.__cache = {};
Module['glTFNodeExtras'] = glTFNodeExtras;
glTFNodeExtras.prototype["__destroy"] = glTFNodeExtras.prototype.__destroy = function() {
    _glTFNodeExtras__destroy(this.__ptr);
};
// glTFOrthographic
function glTFOrthographic() {
    
    this.__ptr = _glTFOrthographic__construct_0(); getCache(glTFOrthographic)[this.__ptr] = this;
};
glTFOrthographic.prototype = Object.create(WrapperObject.prototype);
glTFOrthographic.prototype.constructor = glTFOrthographic;
glTFOrthographic.prototype.__class = glTFOrthographic;
glTFOrthographic.__cache = {};
Module['glTFOrthographic'] = glTFOrthographic;
Object.defineProperty(glTFOrthographic.prototype, "xmag", {
    get: function() {
        return _glTFOrthographic__get_xmag(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFOrthographic.xmag: expected number');
        _glTFOrthographic__set_xmag(this.__ptr, value);
    }
});
Object.defineProperty(glTFOrthographic.prototype, "ymag", {
    get: function() {
        return _glTFOrthographic__get_ymag(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFOrthographic.ymag: expected number');
        _glTFOrthographic__set_ymag(this.__ptr, value);
    }
});
Object.defineProperty(glTFOrthographic.prototype, "zfar", {
    get: function() {
        return _glTFOrthographic__get_zfar(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFOrthographic.zfar: expected number');
        _glTFOrthographic__set_zfar(this.__ptr, value);
    }
});
Object.defineProperty(glTFOrthographic.prototype, "znear", {
    get: function() {
        return _glTFOrthographic__get_znear(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFOrthographic.znear: expected number');
        _glTFOrthographic__set_znear(this.__ptr, value);
    }
});
glTFOrthographic.prototype["__destroy"] = glTFOrthographic.prototype.__destroy = function() {
    _glTFOrthographic__destroy(this.__ptr);
};
// glTFPerspective
function glTFPerspective() {
    
    this.__ptr = _glTFPerspective__construct_0(); getCache(glTFPerspective)[this.__ptr] = this;
};
glTFPerspective.prototype = Object.create(WrapperObject.prototype);
glTFPerspective.prototype.constructor = glTFPerspective;
glTFPerspective.prototype.__class = glTFPerspective;
glTFPerspective.__cache = {};
Module['glTFPerspective'] = glTFPerspective;
Object.defineProperty(glTFPerspective.prototype, "yfov", {
    get: function() {
        return _glTFPerspective__get_yfov(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFPerspective.yfov: expected number');
        _glTFPerspective__set_yfov(this.__ptr, value);
    }
});
Object.defineProperty(glTFPerspective.prototype, "zfar", {
    get: function() {
        return _glTFPerspective__get_zfar(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFPerspective.zfar: expected number');
        _glTFPerspective__set_zfar(this.__ptr, value);
    }
});
Object.defineProperty(glTFPerspective.prototype, "znear", {
    get: function() {
        return _glTFPerspective__get_znear(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFPerspective.znear: expected number');
        _glTFPerspective__set_znear(this.__ptr, value);
    }
});
Object.defineProperty(glTFPerspective.prototype, "aspect_ratio", {
    get: function() {
        return _glTFPerspective__get_aspect_ratio(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFPerspective.aspect_ratio: expected number');
        _glTFPerspective__set_aspect_ratio(this.__ptr, value);
    }
});
glTFPerspective.prototype["__destroy"] = glTFPerspective.prototype.__destroy = function() {
    _glTFPerspective__destroy(this.__ptr);
};
// glTFPrimitive
function glTFPrimitive() {
    
    this.__ptr = _glTFPrimitive__construct_0(); getCache(glTFPrimitive)[this.__ptr] = this;
};
glTFPrimitive.prototype = Object.create(WrapperObject.prototype);
glTFPrimitive.prototype.constructor = glTFPrimitive;
glTFPrimitive.prototype.__class = glTFPrimitive;
glTFPrimitive.__cache = {};
Module['glTFPrimitive'] = glTFPrimitive;
Object.defineProperty(glTFPrimitive.prototype, "attributes", {
    get: function() {
        return wrapPointer(_glTFPrimitive__get_attributes(this.__ptr), glTFAttributes);
    },
    set: function(value) {
        if (!checkClass(value, glTFAttributes)) throw Error('glTFPrimitive.attributes: expected glTFAttributes');
        _glTFPrimitive__set_attributes(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(glTFPrimitive.prototype, "indices", {
    get: function() {
        return _glTFPrimitive__get_indices(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFPrimitive.indices: expected integer');
        _glTFPrimitive__set_indices(this.__ptr, value);
    }
});
Object.defineProperty(glTFPrimitive.prototype, "material", {
    get: function() {
        return _glTFPrimitive__get_material(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFPrimitive.material: expected integer');
        _glTFPrimitive__set_material(this.__ptr, value);
    }
});
Object.defineProperty(glTFPrimitive.prototype, "mode", {
    get: function() {
        return _glTFPrimitive__get_mode(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFPrimitive.mode: expected integer');
        _glTFPrimitive__set_mode(this.__ptr, value);
    }
});
glTFPrimitive.prototype["__destroy"] = glTFPrimitive.prototype.__destroy = function() {
    _glTFPrimitive__destroy(this.__ptr);
};
// glTFSampler
function glTFSampler() {
    
    this.__ptr = _glTFSampler__construct_0(); getCache(glTFSampler)[this.__ptr] = this;
};
glTFSampler.prototype = Object.create(WrapperObject.prototype);
glTFSampler.prototype.constructor = glTFSampler;
glTFSampler.prototype.__class = glTFSampler;
glTFSampler.__cache = {};
Module['glTFSampler'] = glTFSampler;
Object.defineProperty(glTFSampler.prototype, "mag_filter", {
    get: function() {
        return _glTFSampler__get_mag_filter(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFSampler.mag_filter: expected integer');
        _glTFSampler__set_mag_filter(this.__ptr, value);
    }
});
Object.defineProperty(glTFSampler.prototype, "min_filter", {
    get: function() {
        return _glTFSampler__get_min_filter(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFSampler.min_filter: expected integer');
        _glTFSampler__set_min_filter(this.__ptr, value);
    }
});
Object.defineProperty(glTFSampler.prototype, "wrap_s", {
    get: function() {
        return _glTFSampler__get_wrap_s(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFSampler.wrap_s: expected integer');
        _glTFSampler__set_wrap_s(this.__ptr, value);
    }
});
Object.defineProperty(glTFSampler.prototype, "wrap_t", {
    get: function() {
        return _glTFSampler__get_wrap_t(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFSampler.wrap_t: expected integer');
        _glTFSampler__set_wrap_t(this.__ptr, value);
    }
});
Object.defineProperty(glTFSampler.prototype, "name", {
    get: function() {
        return UTF8ToString(_glTFSampler__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFSampler.name: expected string');
        _glTFSampler__set_name(this.__ptr, ensureString(value));
    }
});
glTFSampler.prototype["__destroy"] = glTFSampler.prototype.__destroy = function() {
    _glTFSampler__destroy(this.__ptr);
};
// glTFScene
function glTFScene() {
    
    this.__ptr = _glTFScene__construct_0(); getCache(glTFScene)[this.__ptr] = this;
};
glTFScene.prototype = Object.create(WrapperObject.prototype);
glTFScene.prototype.constructor = glTFScene;
glTFScene.prototype.__class = glTFScene;
glTFScene.__cache = {};
Module['glTFScene'] = glTFScene;
Object.defineProperty(glTFScene.prototype, "name", {
    get: function() {
        return UTF8ToString(_glTFScene__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFScene.name: expected string');
        _glTFScene__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFScene.prototype, "nodes", {
    get: function() {
        return _glTFScene__get_nodes(this.__ptr);
    }});
glTFScene.prototype["__destroy"] = glTFScene.prototype.__destroy = function() {
    _glTFScene__destroy(this.__ptr);
};
// glTFSkin
function glTFSkin() {
    
    this.__ptr = _glTFSkin__construct_0(); getCache(glTFSkin)[this.__ptr] = this;
};
glTFSkin.prototype = Object.create(WrapperObject.prototype);
glTFSkin.prototype.constructor = glTFSkin;
glTFSkin.prototype.__class = glTFSkin;
glTFSkin.__cache = {};
Module['glTFSkin'] = glTFSkin;
Object.defineProperty(glTFSkin.prototype, "name", {
    get: function() {
        return UTF8ToString(_glTFSkin__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFSkin.name: expected string');
        _glTFSkin__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFSkin.prototype, "skeleton", {
    get: function() {
        return _glTFSkin__get_skeleton(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFSkin.skeleton: expected integer');
        _glTFSkin__set_skeleton(this.__ptr, value);
    }
});
Object.defineProperty(glTFSkin.prototype, "joints", {
    get: function() {
        return _glTFSkin__get_joints(this.__ptr);
    }});
Object.defineProperty(glTFSkin.prototype, "inverse_bind_matrices", {
    get: function() {
        return _glTFSkin__get_inverse_bind_matrices(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFSkin.inverse_bind_matrices: expected integer');
        _glTFSkin__set_inverse_bind_matrices(this.__ptr, value);
    }
});
glTFSkin.prototype["__destroy"] = glTFSkin.prototype.__destroy = function() {
    _glTFSkin__destroy(this.__ptr);
};
// glTFSparse
function glTFSparse() {
    
    this.__ptr = _glTFSparse__construct_0(); getCache(glTFSparse)[this.__ptr] = this;
};
glTFSparse.prototype = Object.create(WrapperObject.prototype);
glTFSparse.prototype.constructor = glTFSparse;
glTFSparse.prototype.__class = glTFSparse;
glTFSparse.__cache = {};
Module['glTFSparse'] = glTFSparse;
Object.defineProperty(glTFSparse.prototype, "count", {
    get: function() {
        return _glTFSparse__get_count(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFSparse.count: expected integer');
        _glTFSparse__set_count(this.__ptr, value);
    }
});
Object.defineProperty(glTFSparse.prototype, "indices", {
    get: function() {
        return wrapPointer(_glTFSparse__get_indices(this.__ptr), glTFSparseIndices);
    },
    set: function(value) {
        if (!checkClass(value, glTFSparseIndices)) throw Error('glTFSparse.indices: expected glTFSparseIndices');
        _glTFSparse__set_indices(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(glTFSparse.prototype, "values", {
    get: function() {
        return wrapPointer(_glTFSparse__get_values(this.__ptr), glTFSparseValues);
    },
    set: function(value) {
        if (!checkClass(value, glTFSparseValues)) throw Error('glTFSparse.values: expected glTFSparseValues');
        _glTFSparse__set_values(this.__ptr, value.__ptr);
    }
});
glTFSparse.prototype["__destroy"] = glTFSparse.prototype.__destroy = function() {
    _glTFSparse__destroy(this.__ptr);
};
// glTFSparseIndices
function glTFSparseIndices() {
    
    this.__ptr = _glTFSparseIndices__construct_0(); getCache(glTFSparseIndices)[this.__ptr] = this;
};
glTFSparseIndices.prototype = Object.create(WrapperObject.prototype);
glTFSparseIndices.prototype.constructor = glTFSparseIndices;
glTFSparseIndices.prototype.__class = glTFSparseIndices;
glTFSparseIndices.__cache = {};
Module['glTFSparseIndices'] = glTFSparseIndices;
Object.defineProperty(glTFSparseIndices.prototype, "buffer_view", {
    get: function() {
        return _glTFSparseIndices__get_buffer_view(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFSparseIndices.buffer_view: expected integer');
        _glTFSparseIndices__set_buffer_view(this.__ptr, value);
    }
});
Object.defineProperty(glTFSparseIndices.prototype, "byte_offset", {
    get: function() {
        return _glTFSparseIndices__get_byte_offset(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFSparseIndices.byte_offset: expected integer');
        _glTFSparseIndices__set_byte_offset(this.__ptr, value);
    }
});
Object.defineProperty(glTFSparseIndices.prototype, "component_type", {
    get: function() {
        return _glTFSparseIndices__get_component_type(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFSparseIndices.component_type: expected integer');
        _glTFSparseIndices__set_component_type(this.__ptr, value);
    }
});
glTFSparseIndices.prototype["__destroy"] = glTFSparseIndices.prototype.__destroy = function() {
    _glTFSparseIndices__destroy(this.__ptr);
};
// glTFSparseValues
function glTFSparseValues() {
    
    this.__ptr = _glTFSparseValues__construct_0(); getCache(glTFSparseValues)[this.__ptr] = this;
};
glTFSparseValues.prototype = Object.create(WrapperObject.prototype);
glTFSparseValues.prototype.constructor = glTFSparseValues;
glTFSparseValues.prototype.__class = glTFSparseValues;
glTFSparseValues.__cache = {};
Module['glTFSparseValues'] = glTFSparseValues;
Object.defineProperty(glTFSparseValues.prototype, "buffer_view", {
    get: function() {
        return _glTFSparseValues__get_buffer_view(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFSparseValues.buffer_view: expected integer');
        _glTFSparseValues__set_buffer_view(this.__ptr, value);
    }
});
Object.defineProperty(glTFSparseValues.prototype, "byte_offset", {
    get: function() {
        return _glTFSparseValues__get_byte_offset(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFSparseValues.byte_offset: expected integer');
        _glTFSparseValues__set_byte_offset(this.__ptr, value);
    }
});
glTFSparseValues.prototype["__destroy"] = glTFSparseValues.prototype.__destroy = function() {
    _glTFSparseValues__destroy(this.__ptr);
};
// glTFTexture
function glTFTexture() {
    
    this.__ptr = _glTFTexture__construct_0(); getCache(glTFTexture)[this.__ptr] = this;
};
glTFTexture.prototype = Object.create(WrapperObject.prototype);
glTFTexture.prototype.constructor = glTFTexture;
glTFTexture.prototype.__class = glTFTexture;
glTFTexture.__cache = {};
Module['glTFTexture'] = glTFTexture;
Object.defineProperty(glTFTexture.prototype, "name", {
    get: function() {
        return UTF8ToString(_glTFTexture__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('glTFTexture.name: expected string');
        _glTFTexture__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(glTFTexture.prototype, "sampler", {
    get: function() {
        return _glTFTexture__get_sampler(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFTexture.sampler: expected integer');
        _glTFTexture__set_sampler(this.__ptr, value);
    }
});
Object.defineProperty(glTFTexture.prototype, "source", {
    get: function() {
        return _glTFTexture__get_source(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFTexture.source: expected integer');
        _glTFTexture__set_source(this.__ptr, value);
    }
});
glTFTexture.prototype["__destroy"] = glTFTexture.prototype.__destroy = function() {
    _glTFTexture__destroy(this.__ptr);
};
// glTFTextureInfo
function glTFTextureInfo() {
    
    this.__ptr = _glTFTextureInfo__construct_0(); getCache(glTFTextureInfo)[this.__ptr] = this;
};
glTFTextureInfo.prototype = Object.create(WrapperObject.prototype);
glTFTextureInfo.prototype.constructor = glTFTextureInfo;
glTFTextureInfo.prototype.__class = glTFTextureInfo;
glTFTextureInfo.__cache = {};
Module['glTFTextureInfo'] = glTFTextureInfo;
Object.defineProperty(glTFTextureInfo.prototype, "index", {
    get: function() {
        return _glTFTextureInfo__get_index(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFTextureInfo.index: expected integer');
        _glTFTextureInfo__set_index(this.__ptr, value);
    }
});
Object.defineProperty(glTFTextureInfo.prototype, "scale", {
    get: function() {
        return _glTFTextureInfo__get_scale(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('glTFTextureInfo.scale: expected number');
        _glTFTextureInfo__set_scale(this.__ptr, value);
    }
});
glTFTextureInfo.prototype["__destroy"] = glTFTextureInfo.prototype.__destroy = function() {
    _glTFTextureInfo__destroy(this.__ptr);
};

(function() {
    function setup() {
        glTF.prototype.__type = _glTF__type();
        glTFAccessor.prototype.__type = _glTFAccessor__type();
        glTFAnimation.prototype.__type = _glTFAnimation__type();
        glTFAnimationChannel.prototype.__type = _glTFAnimationChannel__type();
        glTFAnimationSampler.prototype.__type = _glTFAnimationSampler__type();
        glTFAnimationTarget.prototype.__type = _glTFAnimationTarget__type();
        glTFAttributes.prototype.__type = _glTFAttributes__type();
        glTFBuffer.prototype.__type = _glTFBuffer__type();
        glTFBufferView.prototype.__type = _glTFBufferView__type();
        glTFCamera.prototype.__type = _glTFCamera__type();
        glTFImage.prototype.__type = _glTFImage__type();
        glTFMaterial.prototype.__type = _glTFMaterial__type();
        glTFMaterialPBR.prototype.__type = _glTFMaterialPBR__type();
        glTFMesh.prototype.__type = _glTFMesh__type();
        glTFMorphTarget.prototype.__type = _glTFMorphTarget__type();
        glTFNode.prototype.__type = _glTFNode__type();
        glTFNodeExtras.prototype.__type = _glTFNodeExtras__type();
        glTFOrthographic.prototype.__type = _glTFOrthographic__type();
        glTFPerspective.prototype.__type = _glTFPerspective__type();
        glTFPrimitive.prototype.__type = _glTFPrimitive__type();
        glTFSampler.prototype.__type = _glTFSampler__type();
        glTFScene.prototype.__type = _glTFScene__type();
        glTFSkin.prototype.__type = _glTFSkin__type();
        glTFSparse.prototype.__type = _glTFSparse__type();
        glTFSparseIndices.prototype.__type = _glTFSparseIndices__type();
        glTFSparseValues.prototype.__type = _glTFSparseValues__type();
        glTFTexture.prototype.__type = _glTFTexture__type();
        glTFTextureInfo.prototype.__type = _glTFTextureInfo__type();
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
