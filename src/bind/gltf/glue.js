
// Bindings utilities
function WrapperObject() {
}
// glTF
function glTF() {
    var self = this.ptr;
    this.ptr = _glTF_glTF_0(self); getCache(glTF)[this.ptr] = this;
};
glTF.prototype = Object.create(WrapperObject.prototype);
glTF.prototype.constructor = glTF;
glTF.prototype.__class__ = glTF;
glTF.__cache__ = {};
Module['glTF'] = glTF;
Object.defineProperty(glTF.prototype, "buffers", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTF_get_buffers(self), std::vector<glTFBuffer>);
    },
    set: function(buffers) {
        var self = this.ptr;
        /* buffers <std::vector<glTFBuffer>> [] */
        buffers = buffers.ptr;
        _glTF_set_buffers(self, buffers);
    }
});
Object.defineProperty(glTF.prototype, "buffer_views", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTF_get_buffer_views(self), std::vector<glTFBufferView>);
    },
    set: function(buffer_views) {
        var self = this.ptr;
        /* buffer_views <std::vector<glTFBufferView>> [] */
        buffer_views = buffer_views.ptr;
        _glTF_set_buffer_views(self, buffer_views);
    }
});
Object.defineProperty(glTF.prototype, "accessors", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTF_get_accessors(self), std::vector<glTFAccessor>);
    },
    set: function(accessors) {
        var self = this.ptr;
        /* accessors <std::vector<glTFAccessor>> [] */
        accessors = accessors.ptr;
        _glTF_set_accessors(self, accessors);
    }
});
Object.defineProperty(glTF.prototype, "images", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTF_get_images(self), std::vector<glTFImage>);
    },
    set: function(images) {
        var self = this.ptr;
        /* images <std::vector<glTFImage>> [] */
        images = images.ptr;
        _glTF_set_images(self, images);
    }
});
Object.defineProperty(glTF.prototype, "textures", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTF_get_textures(self), std::vector<glTFTexture>);
    },
    set: function(textures) {
        var self = this.ptr;
        /* textures <std::vector<glTFTexture>> [] */
        textures = textures.ptr;
        _glTF_set_textures(self, textures);
    }
});
Object.defineProperty(glTF.prototype, "materials", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTF_get_materials(self), std::vector<glTFMaterial>);
    },
    set: function(materials) {
        var self = this.ptr;
        /* materials <std::vector<glTFMaterial>> [] */
        materials = materials.ptr;
        _glTF_set_materials(self, materials);
    }
});
Object.defineProperty(glTF.prototype, "meshes", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTF_get_meshes(self), std::vector<glTFMesh>);
    },
    set: function(meshes) {
        var self = this.ptr;
        /* meshes <std::vector<glTFMesh>> [] */
        meshes = meshes.ptr;
        _glTF_set_meshes(self, meshes);
    }
});
Object.defineProperty(glTF.prototype, "nodes", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTF_get_nodes(self), std::vector<glTFNode>);
    },
    set: function(nodes) {
        var self = this.ptr;
        /* nodes <std::vector<glTFNode>> [] */
        nodes = nodes.ptr;
        _glTF_set_nodes(self, nodes);
    }
});
Object.defineProperty(glTF.prototype, "skins", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTF_get_skins(self), std::vector<glTFSkin>);
    },
    set: function(skins) {
        var self = this.ptr;
        /* skins <std::vector<glTFSkin>> [] */
        skins = skins.ptr;
        _glTF_set_skins(self, skins);
    }
});
Object.defineProperty(glTF.prototype, "animations", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTF_get_animations(self), std::vector<glTFAnimation>);
    },
    set: function(animations) {
        var self = this.ptr;
        /* animations <std::vector<glTFAnimation>> [] */
        animations = animations.ptr;
        _glTF_set_animations(self, animations);
    }
});
Object.defineProperty(glTF.prototype, "cameras", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTF_get_cameras(self), std::vector<glTFCamera>);
    },
    set: function(cameras) {
        var self = this.ptr;
        /* cameras <std::vector<glTFCamera>> [] */
        cameras = cameras.ptr;
        _glTF_set_cameras(self, cameras);
    }
});
Object.defineProperty(glTF.prototype, "samplers", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTF_get_samplers(self), std::vector<glTFSampler>);
    },
    set: function(samplers) {
        var self = this.ptr;
        /* samplers <std::vector<glTFSampler>> [] */
        samplers = samplers.ptr;
        _glTF_set_samplers(self, samplers);
    }
});
Object.defineProperty(glTF.prototype, "scenes", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTF_get_scenes(self), std::vector<glTFScene>);
    },
    set: function(scenes) {
        var self = this.ptr;
        /* scenes <std::vector<glTFScene>> [] */
        scenes = scenes.ptr;
        _glTF_set_scenes(self, scenes);
    }
});
glTF.prototype["__destroy__"] = glTF.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTF___destroy__(self);
};
// glTFAccessor
function glTFAccessor() {
    var self = this.ptr;
    this.ptr = _glTFAccessor_glTFAccessor_0(self); getCache(glTFAccessor)[this.ptr] = this;
};
glTFAccessor.prototype = Object.create(WrapperObject.prototype);
glTFAccessor.prototype.constructor = glTFAccessor;
glTFAccessor.prototype.__class__ = glTFAccessor;
glTFAccessor.__cache__ = {};
Module['glTFAccessor'] = glTFAccessor;
Object.defineProperty(glTFAccessor.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFAccessor_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _glTFAccessor_set_name(self, name);
    }
});
Object.defineProperty(glTFAccessor.prototype, "buffer_view", {
    get: function() {
        var self = this.ptr;
        return _glTFAccessor_get_buffer_view(self);
    },
    set: function(buffer_view) {
        var self = this.ptr;
        /* buffer_view <int> [] */
        _glTFAccessor_set_buffer_view(self, buffer_view);
    }
});
Object.defineProperty(glTFAccessor.prototype, "byte_offset", {
    get: function() {
        var self = this.ptr;
        return _glTFAccessor_get_byte_offset(self);
    },
    set: function(byte_offset) {
        var self = this.ptr;
        /* byte_offset <int> [] */
        _glTFAccessor_set_byte_offset(self, byte_offset);
    }
});
Object.defineProperty(glTFAccessor.prototype, "component_type", {
    get: function() {
        var self = this.ptr;
        return _glTFAccessor_get_component_type(self);
    },
    set: function(component_type) {
        var self = this.ptr;
        /* component_type <glTFComponentType> [] */
        if (component_type && typeof component_type === "object") component_type = component_type.ptr;
        _glTFAccessor_set_component_type(self, component_type);
    }
});
Object.defineProperty(glTFAccessor.prototype, "normalized", {
    get: function() {
        var self = this.ptr;
        return !!(_glTFAccessor_get_normalized(self));
    },
    set: function(normalized) {
        var self = this.ptr;
        /* normalized <bool> [] */
        _glTFAccessor_set_normalized(self, normalized);
    }
});
Object.defineProperty(glTFAccessor.prototype, "count", {
    get: function() {
        var self = this.ptr;
        return _glTFAccessor_get_count(self);
    },
    set: function(count) {
        var self = this.ptr;
        /* count <int> [] */
        _glTFAccessor_set_count(self, count);
    }
});
Object.defineProperty(glTFAccessor.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return _glTFAccessor_get_type(self);
    },
    set: function(type) {
        var self = this.ptr;
        /* type <glTFType> [] */
        if (type && typeof type === "object") type = type.ptr;
        _glTFAccessor_set_type(self, type);
    }
});
Object.defineProperty(glTFAccessor.prototype, "sparse", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFAccessor_get_sparse(self), glTFSparse);
    },
    set: function(sparse) {
        var self = this.ptr;
        /* sparse <glTFSparse> [] */
        sparse = sparse.ptr;
        _glTFAccessor_set_sparse(self, sparse);
    }
});
glTFAccessor.prototype["__destroy__"] = glTFAccessor.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFAccessor___destroy__(self);
};
// glTFAnimation
function glTFAnimation() {
    var self = this.ptr;
    this.ptr = _glTFAnimation_glTFAnimation_0(self); getCache(glTFAnimation)[this.ptr] = this;
};
glTFAnimation.prototype = Object.create(WrapperObject.prototype);
glTFAnimation.prototype.constructor = glTFAnimation;
glTFAnimation.prototype.__class__ = glTFAnimation;
glTFAnimation.__cache__ = {};
Module['glTFAnimation'] = glTFAnimation;
Object.defineProperty(glTFAnimation.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFAnimation_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _glTFAnimation_set_name(self, name);
    }
});
Object.defineProperty(glTFAnimation.prototype, "samplers", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFAnimation_get_samplers(self), std::vector<glTFAnimationSampler>);
    },
    set: function(samplers) {
        var self = this.ptr;
        /* samplers <std::vector<glTFAnimationSampler>> [] */
        samplers = samplers.ptr;
        _glTFAnimation_set_samplers(self, samplers);
    }
});
Object.defineProperty(glTFAnimation.prototype, "channels", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFAnimation_get_channels(self), std::vector<glTFAnimationChannel>);
    },
    set: function(channels) {
        var self = this.ptr;
        /* channels <std::vector<glTFAnimationChannel>> [] */
        channels = channels.ptr;
        _glTFAnimation_set_channels(self, channels);
    }
});
glTFAnimation.prototype["__destroy__"] = glTFAnimation.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFAnimation___destroy__(self);
};
// glTFAnimationChannel
function glTFAnimationChannel() {
    var self = this.ptr;
    this.ptr = _glTFAnimationChannel_glTFAnimationChannel_0(self); getCache(glTFAnimationChannel)[this.ptr] = this;
};
glTFAnimationChannel.prototype = Object.create(WrapperObject.prototype);
glTFAnimationChannel.prototype.constructor = glTFAnimationChannel;
glTFAnimationChannel.prototype.__class__ = glTFAnimationChannel;
glTFAnimationChannel.__cache__ = {};
Module['glTFAnimationChannel'] = glTFAnimationChannel;
Object.defineProperty(glTFAnimationChannel.prototype, "sampler", {
    get: function() {
        var self = this.ptr;
        return _glTFAnimationChannel_get_sampler(self);
    },
    set: function(sampler) {
        var self = this.ptr;
        /* sampler <int> [] */
        _glTFAnimationChannel_set_sampler(self, sampler);
    }
});
Object.defineProperty(glTFAnimationChannel.prototype, "target", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFAnimationChannel_get_target(self), glTFAnimationTarget);
    },
    set: function(target) {
        var self = this.ptr;
        /* target <glTFAnimationTarget> [] */
        target = target.ptr;
        _glTFAnimationChannel_set_target(self, target);
    }
});
glTFAnimationChannel.prototype["__destroy__"] = glTFAnimationChannel.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFAnimationChannel___destroy__(self);
};
// glTFAnimationSampler
function glTFAnimationSampler() {
    var self = this.ptr;
    this.ptr = _glTFAnimationSampler_glTFAnimationSampler_0(self); getCache(glTFAnimationSampler)[this.ptr] = this;
};
glTFAnimationSampler.prototype = Object.create(WrapperObject.prototype);
glTFAnimationSampler.prototype.constructor = glTFAnimationSampler;
glTFAnimationSampler.prototype.__class__ = glTFAnimationSampler;
glTFAnimationSampler.__cache__ = {};
Module['glTFAnimationSampler'] = glTFAnimationSampler;
Object.defineProperty(glTFAnimationSampler.prototype, "interpolation", {
    get: function() {
        var self = this.ptr;
        return _glTFAnimationSampler_get_interpolation(self);
    },
    set: function(interpolation) {
        var self = this.ptr;
        /* interpolation <glTFInterpolation> [] */
        if (interpolation && typeof interpolation === "object") interpolation = interpolation.ptr;
        _glTFAnimationSampler_set_interpolation(self, interpolation);
    }
});
Object.defineProperty(glTFAnimationSampler.prototype, "input", {
    get: function() {
        var self = this.ptr;
        return _glTFAnimationSampler_get_input(self);
    },
    set: function(input) {
        var self = this.ptr;
        /* input <int> [] */
        _glTFAnimationSampler_set_input(self, input);
    }
});
Object.defineProperty(glTFAnimationSampler.prototype, "output", {
    get: function() {
        var self = this.ptr;
        return _glTFAnimationSampler_get_output(self);
    },
    set: function(output) {
        var self = this.ptr;
        /* output <int> [] */
        _glTFAnimationSampler_set_output(self, output);
    }
});
glTFAnimationSampler.prototype["__destroy__"] = glTFAnimationSampler.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFAnimationSampler___destroy__(self);
};
// glTFAnimationTarget
function glTFAnimationTarget() {
    var self = this.ptr;
    this.ptr = _glTFAnimationTarget_glTFAnimationTarget_0(self); getCache(glTFAnimationTarget)[this.ptr] = this;
};
glTFAnimationTarget.prototype = Object.create(WrapperObject.prototype);
glTFAnimationTarget.prototype.constructor = glTFAnimationTarget;
glTFAnimationTarget.prototype.__class__ = glTFAnimationTarget;
glTFAnimationTarget.__cache__ = {};
Module['glTFAnimationTarget'] = glTFAnimationTarget;
Object.defineProperty(glTFAnimationTarget.prototype, "node", {
    get: function() {
        var self = this.ptr;
        return _glTFAnimationTarget_get_node(self);
    },
    set: function(node) {
        var self = this.ptr;
        /* node <int> [] */
        _glTFAnimationTarget_set_node(self, node);
    }
});
Object.defineProperty(glTFAnimationTarget.prototype, "path", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFAnimationTarget_get_path(self));
    },
    set: function(path) {
        var self = this.ptr;
        /* path <std::string> [] */
        if (path && typeof path === "object") path = path.ptr;
        else path = ensureString(path);
        _glTFAnimationTarget_set_path(self, path);
    }
});
glTFAnimationTarget.prototype["__destroy__"] = glTFAnimationTarget.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFAnimationTarget___destroy__(self);
};
// glTFAttributes
function glTFAttributes() {
    var self = this.ptr;
    this.ptr = _glTFAttributes_glTFAttributes_0(self); getCache(glTFAttributes)[this.ptr] = this;
};
glTFAttributes.prototype = Object.create(WrapperObject.prototype);
glTFAttributes.prototype.constructor = glTFAttributes;
glTFAttributes.prototype.__class__ = glTFAttributes;
glTFAttributes.__cache__ = {};
Module['glTFAttributes'] = glTFAttributes;
Object.defineProperty(glTFAttributes.prototype, "POSITION", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes_get_POSITION(self);
    },
    set: function(POSITION) {
        var self = this.ptr;
        /* POSITION <int> [] */
        _glTFAttributes_set_POSITION(self, POSITION);
    }
});
Object.defineProperty(glTFAttributes.prototype, "NORMAL", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes_get_NORMAL(self);
    },
    set: function(NORMAL) {
        var self = this.ptr;
        /* NORMAL <int> [] */
        _glTFAttributes_set_NORMAL(self, NORMAL);
    }
});
Object.defineProperty(glTFAttributes.prototype, "TANGENT", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes_get_TANGENT(self);
    },
    set: function(TANGENT) {
        var self = this.ptr;
        /* TANGENT <int> [] */
        _glTFAttributes_set_TANGENT(self, TANGENT);
    }
});
Object.defineProperty(glTFAttributes.prototype, "TEXCOORD_0", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes_get_TEXCOORD_0(self);
    },
    set: function(TEXCOORD_0) {
        var self = this.ptr;
        /* TEXCOORD_0 <int> [] */
        _glTFAttributes_set_TEXCOORD_0(self, TEXCOORD_0);
    }
});
Object.defineProperty(glTFAttributes.prototype, "TEXCOORD_1", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes_get_TEXCOORD_1(self);
    },
    set: function(TEXCOORD_1) {
        var self = this.ptr;
        /* TEXCOORD_1 <int> [] */
        _glTFAttributes_set_TEXCOORD_1(self, TEXCOORD_1);
    }
});
Object.defineProperty(glTFAttributes.prototype, "COLOR_0", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes_get_COLOR_0(self);
    },
    set: function(COLOR_0) {
        var self = this.ptr;
        /* COLOR_0 <int> [] */
        _glTFAttributes_set_COLOR_0(self, COLOR_0);
    }
});
Object.defineProperty(glTFAttributes.prototype, "JOINTS_0", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes_get_JOINTS_0(self);
    },
    set: function(JOINTS_0) {
        var self = this.ptr;
        /* JOINTS_0 <int> [] */
        _glTFAttributes_set_JOINTS_0(self, JOINTS_0);
    }
});
Object.defineProperty(glTFAttributes.prototype, "WEIGHTS_0", {
    get: function() {
        var self = this.ptr;
        return _glTFAttributes_get_WEIGHTS_0(self);
    },
    set: function(WEIGHTS_0) {
        var self = this.ptr;
        /* WEIGHTS_0 <int> [] */
        _glTFAttributes_set_WEIGHTS_0(self, WEIGHTS_0);
    }
});
glTFAttributes.prototype["__destroy__"] = glTFAttributes.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFAttributes___destroy__(self);
};
// glTFBuffer
function glTFBuffer() {
    var self = this.ptr;
    this.ptr = _glTFBuffer_glTFBuffer_0(self); getCache(glTFBuffer)[this.ptr] = this;
};
glTFBuffer.prototype = Object.create(WrapperObject.prototype);
glTFBuffer.prototype.constructor = glTFBuffer;
glTFBuffer.prototype.__class__ = glTFBuffer;
glTFBuffer.__cache__ = {};
Module['glTFBuffer'] = glTFBuffer;
Object.defineProperty(glTFBuffer.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFBuffer_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _glTFBuffer_set_name(self, name);
    }
});
Object.defineProperty(glTFBuffer.prototype, "mime_type", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFBuffer_get_mime_type(self));
    },
    set: function(mime_type) {
        var self = this.ptr;
        /* mime_type <std::string> [] */
        if (mime_type && typeof mime_type === "object") mime_type = mime_type.ptr;
        else mime_type = ensureString(mime_type);
        _glTFBuffer_set_mime_type(self, mime_type);
    }
});
Object.defineProperty(glTFBuffer.prototype, "uri", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFBuffer_get_uri(self));
    },
    set: function(uri) {
        var self = this.ptr;
        /* uri <std::string> [] */
        if (uri && typeof uri === "object") uri = uri.ptr;
        else uri = ensureString(uri);
        _glTFBuffer_set_uri(self, uri);
    }
});
Object.defineProperty(glTFBuffer.prototype, "byte_length", {
    get: function() {
        var self = this.ptr;
        return _glTFBuffer_get_byte_length(self);
    },
    set: function(byte_length) {
        var self = this.ptr;
        /* byte_length <int> [] */
        _glTFBuffer_set_byte_length(self, byte_length);
    }
});
glTFBuffer.prototype["__destroy__"] = glTFBuffer.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFBuffer___destroy__(self);
};
// glTFBufferView
function glTFBufferView() {
    var self = this.ptr;
    this.ptr = _glTFBufferView_glTFBufferView_0(self); getCache(glTFBufferView)[this.ptr] = this;
};
glTFBufferView.prototype = Object.create(WrapperObject.prototype);
glTFBufferView.prototype.constructor = glTFBufferView;
glTFBufferView.prototype.__class__ = glTFBufferView;
glTFBufferView.__cache__ = {};
Module['glTFBufferView'] = glTFBufferView;
Object.defineProperty(glTFBufferView.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFBufferView_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _glTFBufferView_set_name(self, name);
    }
});
Object.defineProperty(glTFBufferView.prototype, "buffer", {
    get: function() {
        var self = this.ptr;
        return _glTFBufferView_get_buffer(self);
    },
    set: function(buffer) {
        var self = this.ptr;
        /* buffer <int> [] */
        _glTFBufferView_set_buffer(self, buffer);
    }
});
Object.defineProperty(glTFBufferView.prototype, "byte_offset", {
    get: function() {
        var self = this.ptr;
        return _glTFBufferView_get_byte_offset(self);
    },
    set: function(byte_offset) {
        var self = this.ptr;
        /* byte_offset <size_t> [] */
        _glTFBufferView_set_byte_offset(self, byte_offset);
    }
});
Object.defineProperty(glTFBufferView.prototype, "byte_length", {
    get: function() {
        var self = this.ptr;
        return _glTFBufferView_get_byte_length(self);
    },
    set: function(byte_length) {
        var self = this.ptr;
        /* byte_length <size_t> [] */
        _glTFBufferView_set_byte_length(self, byte_length);
    }
});
Object.defineProperty(glTFBufferView.prototype, "byte_stride", {
    get: function() {
        var self = this.ptr;
        return _glTFBufferView_get_byte_stride(self);
    },
    set: function(byte_stride) {
        var self = this.ptr;
        /* byte_stride <size_t> [] */
        _glTFBufferView_set_byte_stride(self, byte_stride);
    }
});
Object.defineProperty(glTFBufferView.prototype, "target", {
    get: function() {
        var self = this.ptr;
        return _glTFBufferView_get_target(self);
    },
    set: function(target) {
        var self = this.ptr;
        /* target <int> [] */
        _glTFBufferView_set_target(self, target);
    }
});
glTFBufferView.prototype["__destroy__"] = glTFBufferView.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFBufferView___destroy__(self);
};
// glTFCamera
function glTFCamera() {
    var self = this.ptr;
    this.ptr = _glTFCamera_glTFCamera_0(self); getCache(glTFCamera)[this.ptr] = this;
};
glTFCamera.prototype = Object.create(WrapperObject.prototype);
glTFCamera.prototype.constructor = glTFCamera;
glTFCamera.prototype.__class__ = glTFCamera;
glTFCamera.__cache__ = {};
Module['glTFCamera'] = glTFCamera;
Object.defineProperty(glTFCamera.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFCamera_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _glTFCamera_set_name(self, name);
    }
});
Object.defineProperty(glTFCamera.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFCamera_get_type(self));
    },
    set: function(type) {
        var self = this.ptr;
        /* type <std::string> [] */
        if (type && typeof type === "object") type = type.ptr;
        else type = ensureString(type);
        _glTFCamera_set_type(self, type);
    }
});
Object.defineProperty(glTFCamera.prototype, "orthographic", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFCamera_get_orthographic(self), glTFOrthographic);
    },
    set: function(orthographic) {
        var self = this.ptr;
        /* orthographic <glTFOrthographic> [] */
        orthographic = orthographic.ptr;
        _glTFCamera_set_orthographic(self, orthographic);
    }
});
Object.defineProperty(glTFCamera.prototype, "perspective", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFCamera_get_perspective(self), glTFPerspective);
    },
    set: function(perspective) {
        var self = this.ptr;
        /* perspective <glTFPerspective> [] */
        perspective = perspective.ptr;
        _glTFCamera_set_perspective(self, perspective);
    }
});
glTFCamera.prototype["__destroy__"] = glTFCamera.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFCamera___destroy__(self);
};
// glTFImage
function glTFImage() {
    var self = this.ptr;
    this.ptr = _glTFImage_glTFImage_0(self); getCache(glTFImage)[this.ptr] = this;
};
glTFImage.prototype = Object.create(WrapperObject.prototype);
glTFImage.prototype.constructor = glTFImage;
glTFImage.prototype.__class__ = glTFImage;
glTFImage.__cache__ = {};
Module['glTFImage'] = glTFImage;
Object.defineProperty(glTFImage.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFImage_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _glTFImage_set_name(self, name);
    }
});
Object.defineProperty(glTFImage.prototype, "mime_type", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFImage_get_mime_type(self));
    },
    set: function(mime_type) {
        var self = this.ptr;
        /* mime_type <std::string> [] */
        if (mime_type && typeof mime_type === "object") mime_type = mime_type.ptr;
        else mime_type = ensureString(mime_type);
        _glTFImage_set_mime_type(self, mime_type);
    }
});
Object.defineProperty(glTFImage.prototype, "uri", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFImage_get_uri(self));
    },
    set: function(uri) {
        var self = this.ptr;
        /* uri <std::string> [] */
        if (uri && typeof uri === "object") uri = uri.ptr;
        else uri = ensureString(uri);
        _glTFImage_set_uri(self, uri);
    }
});
Object.defineProperty(glTFImage.prototype, "buffer_view", {
    get: function() {
        var self = this.ptr;
        return _glTFImage_get_buffer_view(self);
    },
    set: function(buffer_view) {
        var self = this.ptr;
        /* buffer_view <int> [] */
        _glTFImage_set_buffer_view(self, buffer_view);
    }
});
glTFImage.prototype["__destroy__"] = glTFImage.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFImage___destroy__(self);
};
// glTFMaterial
function glTFMaterial() {
    var self = this.ptr;
    this.ptr = _glTFMaterial_glTFMaterial_0(self); getCache(glTFMaterial)[this.ptr] = this;
};
glTFMaterial.prototype = Object.create(WrapperObject.prototype);
glTFMaterial.prototype.constructor = glTFMaterial;
glTFMaterial.prototype.__class__ = glTFMaterial;
glTFMaterial.__cache__ = {};
Module['glTFMaterial'] = glTFMaterial;
Object.defineProperty(glTFMaterial.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFMaterial_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _glTFMaterial_set_name(self, name);
    }
});
Object.defineProperty(glTFMaterial.prototype, "normal_texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterial_get_normal_texture(self), glTFTextureInfo);
    },
    set: function(normal_texture) {
        var self = this.ptr;
        /* normal_texture <glTFTextureInfo> [] */
        normal_texture = normal_texture.ptr;
        _glTFMaterial_set_normal_texture(self, normal_texture);
    }
});
Object.defineProperty(glTFMaterial.prototype, "occlusion_texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterial_get_occlusion_texture(self), glTFTextureInfo);
    },
    set: function(occlusion_texture) {
        var self = this.ptr;
        /* occlusion_texture <glTFTextureInfo> [] */
        occlusion_texture = occlusion_texture.ptr;
        _glTFMaterial_set_occlusion_texture(self, occlusion_texture);
    }
});
Object.defineProperty(glTFMaterial.prototype, "emissive_factor", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterial_get_emissive_factor(self), mud::vec3);
    },
    set: function(emissive_factor) {
        var self = this.ptr;
        /* emissive_factor <vec3> [] */
        emissive_factor = emissive_factor.ptr;
        _glTFMaterial_set_emissive_factor(self, emissive_factor);
    }
});
Object.defineProperty(glTFMaterial.prototype, "emissive_texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterial_get_emissive_texture(self), glTFTextureInfo);
    },
    set: function(emissive_texture) {
        var self = this.ptr;
        /* emissive_texture <glTFTextureInfo> [] */
        emissive_texture = emissive_texture.ptr;
        _glTFMaterial_set_emissive_texture(self, emissive_texture);
    }
});
Object.defineProperty(glTFMaterial.prototype, "double_sided", {
    get: function() {
        var self = this.ptr;
        return !!(_glTFMaterial_get_double_sided(self));
    },
    set: function(double_sided) {
        var self = this.ptr;
        /* double_sided <bool> [] */
        _glTFMaterial_set_double_sided(self, double_sided);
    }
});
Object.defineProperty(glTFMaterial.prototype, "alpha_mode", {
    get: function() {
        var self = this.ptr;
        return _glTFMaterial_get_alpha_mode(self);
    },
    set: function(alpha_mode) {
        var self = this.ptr;
        /* alpha_mode <glTFAlphaMode> [] */
        if (alpha_mode && typeof alpha_mode === "object") alpha_mode = alpha_mode.ptr;
        _glTFMaterial_set_alpha_mode(self, alpha_mode);
    }
});
Object.defineProperty(glTFMaterial.prototype, "pbr_metallic_roughness", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterial_get_pbr_metallic_roughness(self), glTFMaterialPBR);
    },
    set: function(pbr_metallic_roughness) {
        var self = this.ptr;
        /* pbr_metallic_roughness <glTFMaterialPBR> [] */
        pbr_metallic_roughness = pbr_metallic_roughness.ptr;
        _glTFMaterial_set_pbr_metallic_roughness(self, pbr_metallic_roughness);
    }
});
glTFMaterial.prototype["__destroy__"] = glTFMaterial.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFMaterial___destroy__(self);
};
// glTFMaterialPBR
function glTFMaterialPBR() {
    var self = this.ptr;
    this.ptr = _glTFMaterialPBR_glTFMaterialPBR_0(self); getCache(glTFMaterialPBR)[this.ptr] = this;
};
glTFMaterialPBR.prototype = Object.create(WrapperObject.prototype);
glTFMaterialPBR.prototype.constructor = glTFMaterialPBR;
glTFMaterialPBR.prototype.__class__ = glTFMaterialPBR;
glTFMaterialPBR.__cache__ = {};
Module['glTFMaterialPBR'] = glTFMaterialPBR;
Object.defineProperty(glTFMaterialPBR.prototype, "base_color_factor", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterialPBR_get_base_color_factor(self), mud::vec4);
    },
    set: function(base_color_factor) {
        var self = this.ptr;
        /* base_color_factor <vec4> [] */
        base_color_factor = base_color_factor.ptr;
        _glTFMaterialPBR_set_base_color_factor(self, base_color_factor);
    }
});
Object.defineProperty(glTFMaterialPBR.prototype, "base_color_texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterialPBR_get_base_color_texture(self), glTFTextureInfo);
    },
    set: function(base_color_texture) {
        var self = this.ptr;
        /* base_color_texture <glTFTextureInfo> [] */
        base_color_texture = base_color_texture.ptr;
        _glTFMaterialPBR_set_base_color_texture(self, base_color_texture);
    }
});
Object.defineProperty(glTFMaterialPBR.prototype, "metallic_factor", {
    get: function() {
        var self = this.ptr;
        return _glTFMaterialPBR_get_metallic_factor(self);
    },
    set: function(metallic_factor) {
        var self = this.ptr;
        /* metallic_factor <float> [] */
        _glTFMaterialPBR_set_metallic_factor(self, metallic_factor);
    }
});
Object.defineProperty(glTFMaterialPBR.prototype, "roughness_factor", {
    get: function() {
        var self = this.ptr;
        return _glTFMaterialPBR_get_roughness_factor(self);
    },
    set: function(roughness_factor) {
        var self = this.ptr;
        /* roughness_factor <float> [] */
        _glTFMaterialPBR_set_roughness_factor(self, roughness_factor);
    }
});
Object.defineProperty(glTFMaterialPBR.prototype, "metallic_roughness_texture", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMaterialPBR_get_metallic_roughness_texture(self), glTFTextureInfo);
    },
    set: function(metallic_roughness_texture) {
        var self = this.ptr;
        /* metallic_roughness_texture <glTFTextureInfo> [] */
        metallic_roughness_texture = metallic_roughness_texture.ptr;
        _glTFMaterialPBR_set_metallic_roughness_texture(self, metallic_roughness_texture);
    }
});
glTFMaterialPBR.prototype["__destroy__"] = glTFMaterialPBR.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFMaterialPBR___destroy__(self);
};
// glTFMesh
function glTFMesh() {
    var self = this.ptr;
    this.ptr = _glTFMesh_glTFMesh_0(self); getCache(glTFMesh)[this.ptr] = this;
};
glTFMesh.prototype = Object.create(WrapperObject.prototype);
glTFMesh.prototype.constructor = glTFMesh;
glTFMesh.prototype.__class__ = glTFMesh;
glTFMesh.__cache__ = {};
Module['glTFMesh'] = glTFMesh;
Object.defineProperty(glTFMesh.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFMesh_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _glTFMesh_set_name(self, name);
    }
});
Object.defineProperty(glTFMesh.prototype, "primitives", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMesh_get_primitives(self), std::vector<glTFPrimitive>);
    },
    set: function(primitives) {
        var self = this.ptr;
        /* primitives <std::vector<glTFPrimitive>> [] */
        primitives = primitives.ptr;
        _glTFMesh_set_primitives(self, primitives);
    }
});
Object.defineProperty(glTFMesh.prototype, "weights", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFMesh_get_weights(self), std::vector<float>);
    },
    set: function(weights) {
        var self = this.ptr;
        /* weights <std::vector<float>> [] */
        weights = weights.ptr;
        _glTFMesh_set_weights(self, weights);
    }
});
glTFMesh.prototype["__destroy__"] = glTFMesh.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFMesh___destroy__(self);
};
// glTFMorphTarget
function glTFMorphTarget() {
    var self = this.ptr;
    this.ptr = _glTFMorphTarget_glTFMorphTarget_0(self); getCache(glTFMorphTarget)[this.ptr] = this;
};
glTFMorphTarget.prototype = Object.create(WrapperObject.prototype);
glTFMorphTarget.prototype.constructor = glTFMorphTarget;
glTFMorphTarget.prototype.__class__ = glTFMorphTarget;
glTFMorphTarget.__cache__ = {};
Module['glTFMorphTarget'] = glTFMorphTarget;
Object.defineProperty(glTFMorphTarget.prototype, "POSITION", {
    get: function() {
        var self = this.ptr;
        return _glTFMorphTarget_get_POSITION(self);
    },
    set: function(POSITION) {
        var self = this.ptr;
        /* POSITION <int> [] */
        _glTFMorphTarget_set_POSITION(self, POSITION);
    }
});
Object.defineProperty(glTFMorphTarget.prototype, "NORMAL", {
    get: function() {
        var self = this.ptr;
        return _glTFMorphTarget_get_NORMAL(self);
    },
    set: function(NORMAL) {
        var self = this.ptr;
        /* NORMAL <int> [] */
        _glTFMorphTarget_set_NORMAL(self, NORMAL);
    }
});
Object.defineProperty(glTFMorphTarget.prototype, "TANGENT", {
    get: function() {
        var self = this.ptr;
        return _glTFMorphTarget_get_TANGENT(self);
    },
    set: function(TANGENT) {
        var self = this.ptr;
        /* TANGENT <int> [] */
        _glTFMorphTarget_set_TANGENT(self, TANGENT);
    }
});
glTFMorphTarget.prototype["__destroy__"] = glTFMorphTarget.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFMorphTarget___destroy__(self);
};
// glTFNode
function glTFNode() {
    var self = this.ptr;
    this.ptr = _glTFNode_glTFNode_0(self); getCache(glTFNode)[this.ptr] = this;
};
glTFNode.prototype = Object.create(WrapperObject.prototype);
glTFNode.prototype.constructor = glTFNode;
glTFNode.prototype.__class__ = glTFNode;
glTFNode.__cache__ = {};
Module['glTFNode'] = glTFNode;
Object.defineProperty(glTFNode.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFNode_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _glTFNode_set_name(self, name);
    }
});
Object.defineProperty(glTFNode.prototype, "mesh", {
    get: function() {
        var self = this.ptr;
        return _glTFNode_get_mesh(self);
    },
    set: function(mesh) {
        var self = this.ptr;
        /* mesh <int> [] */
        _glTFNode_set_mesh(self, mesh);
    }
});
Object.defineProperty(glTFNode.prototype, "camera", {
    get: function() {
        var self = this.ptr;
        return _glTFNode_get_camera(self);
    },
    set: function(camera) {
        var self = this.ptr;
        /* camera <int> [] */
        _glTFNode_set_camera(self, camera);
    }
});
Object.defineProperty(glTFNode.prototype, "skin", {
    get: function() {
        var self = this.ptr;
        return _glTFNode_get_skin(self);
    },
    set: function(skin) {
        var self = this.ptr;
        /* skin <int> [] */
        _glTFNode_set_skin(self, skin);
    }
});
Object.defineProperty(glTFNode.prototype, "matrix", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFNode_get_matrix(self), mud::mat4);
    },
    set: function(matrix) {
        var self = this.ptr;
        /* matrix <mat4> [] */
        matrix = matrix.ptr;
        _glTFNode_set_matrix(self, matrix);
    }
});
Object.defineProperty(glTFNode.prototype, "translation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFNode_get_translation(self), mud::vec3);
    },
    set: function(translation) {
        var self = this.ptr;
        /* translation <vec3> [] */
        translation = translation.ptr;
        _glTFNode_set_translation(self, translation);
    }
});
Object.defineProperty(glTFNode.prototype, "rotation", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFNode_get_rotation(self), mud::quat);
    },
    set: function(rotation) {
        var self = this.ptr;
        /* rotation <quat> [] */
        rotation = rotation.ptr;
        _glTFNode_set_rotation(self, rotation);
    }
});
Object.defineProperty(glTFNode.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFNode_get_scale(self), mud::vec3);
    },
    set: function(scale) {
        var self = this.ptr;
        /* scale <vec3> [] */
        scale = scale.ptr;
        _glTFNode_set_scale(self, scale);
    }
});
Object.defineProperty(glTFNode.prototype, "children", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFNode_get_children(self), std::vector<int>);
    },
    set: function(children) {
        var self = this.ptr;
        /* children <std::vector<int>> [] */
        children = children.ptr;
        _glTFNode_set_children(self, children);
    }
});
glTFNode.prototype["__destroy__"] = glTFNode.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFNode___destroy__(self);
};
// glTFNodeExtras
function glTFNodeExtras() {
    var self = this.ptr;
    this.ptr = _glTFNodeExtras_glTFNodeExtras_0(self); getCache(glTFNodeExtras)[this.ptr] = this;
};
glTFNodeExtras.prototype = Object.create(WrapperObject.prototype);
glTFNodeExtras.prototype.constructor = glTFNodeExtras;
glTFNodeExtras.prototype.__class__ = glTFNodeExtras;
glTFNodeExtras.__cache__ = {};
Module['glTFNodeExtras'] = glTFNodeExtras;
glTFNodeExtras.prototype["__destroy__"] = glTFNodeExtras.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFNodeExtras___destroy__(self);
};
// glTFOrthographic
function glTFOrthographic() {
    var self = this.ptr;
    this.ptr = _glTFOrthographic_glTFOrthographic_0(self); getCache(glTFOrthographic)[this.ptr] = this;
};
glTFOrthographic.prototype = Object.create(WrapperObject.prototype);
glTFOrthographic.prototype.constructor = glTFOrthographic;
glTFOrthographic.prototype.__class__ = glTFOrthographic;
glTFOrthographic.__cache__ = {};
Module['glTFOrthographic'] = glTFOrthographic;
Object.defineProperty(glTFOrthographic.prototype, "xmag", {
    get: function() {
        var self = this.ptr;
        return _glTFOrthographic_get_xmag(self);
    },
    set: function(xmag) {
        var self = this.ptr;
        /* xmag <float> [] */
        _glTFOrthographic_set_xmag(self, xmag);
    }
});
Object.defineProperty(glTFOrthographic.prototype, "ymag", {
    get: function() {
        var self = this.ptr;
        return _glTFOrthographic_get_ymag(self);
    },
    set: function(ymag) {
        var self = this.ptr;
        /* ymag <float> [] */
        _glTFOrthographic_set_ymag(self, ymag);
    }
});
Object.defineProperty(glTFOrthographic.prototype, "zfar", {
    get: function() {
        var self = this.ptr;
        return _glTFOrthographic_get_zfar(self);
    },
    set: function(zfar) {
        var self = this.ptr;
        /* zfar <float> [] */
        _glTFOrthographic_set_zfar(self, zfar);
    }
});
Object.defineProperty(glTFOrthographic.prototype, "znear", {
    get: function() {
        var self = this.ptr;
        return _glTFOrthographic_get_znear(self);
    },
    set: function(znear) {
        var self = this.ptr;
        /* znear <float> [] */
        _glTFOrthographic_set_znear(self, znear);
    }
});
glTFOrthographic.prototype["__destroy__"] = glTFOrthographic.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFOrthographic___destroy__(self);
};
// glTFPerspective
function glTFPerspective() {
    var self = this.ptr;
    this.ptr = _glTFPerspective_glTFPerspective_0(self); getCache(glTFPerspective)[this.ptr] = this;
};
glTFPerspective.prototype = Object.create(WrapperObject.prototype);
glTFPerspective.prototype.constructor = glTFPerspective;
glTFPerspective.prototype.__class__ = glTFPerspective;
glTFPerspective.__cache__ = {};
Module['glTFPerspective'] = glTFPerspective;
Object.defineProperty(glTFPerspective.prototype, "yfov", {
    get: function() {
        var self = this.ptr;
        return _glTFPerspective_get_yfov(self);
    },
    set: function(yfov) {
        var self = this.ptr;
        /* yfov <float> [] */
        _glTFPerspective_set_yfov(self, yfov);
    }
});
Object.defineProperty(glTFPerspective.prototype, "zfar", {
    get: function() {
        var self = this.ptr;
        return _glTFPerspective_get_zfar(self);
    },
    set: function(zfar) {
        var self = this.ptr;
        /* zfar <float> [] */
        _glTFPerspective_set_zfar(self, zfar);
    }
});
Object.defineProperty(glTFPerspective.prototype, "znear", {
    get: function() {
        var self = this.ptr;
        return _glTFPerspective_get_znear(self);
    },
    set: function(znear) {
        var self = this.ptr;
        /* znear <float> [] */
        _glTFPerspective_set_znear(self, znear);
    }
});
Object.defineProperty(glTFPerspective.prototype, "aspect_ration", {
    get: function() {
        var self = this.ptr;
        return _glTFPerspective_get_aspect_ration(self);
    },
    set: function(aspect_ration) {
        var self = this.ptr;
        /* aspect_ration <float> [] */
        _glTFPerspective_set_aspect_ration(self, aspect_ration);
    }
});
glTFPerspective.prototype["__destroy__"] = glTFPerspective.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFPerspective___destroy__(self);
};
// glTFPrimitive
function glTFPrimitive() {
    var self = this.ptr;
    this.ptr = _glTFPrimitive_glTFPrimitive_0(self); getCache(glTFPrimitive)[this.ptr] = this;
};
glTFPrimitive.prototype = Object.create(WrapperObject.prototype);
glTFPrimitive.prototype.constructor = glTFPrimitive;
glTFPrimitive.prototype.__class__ = glTFPrimitive;
glTFPrimitive.__cache__ = {};
Module['glTFPrimitive'] = glTFPrimitive;
Object.defineProperty(glTFPrimitive.prototype, "attributes", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFPrimitive_get_attributes(self), glTFAttributes);
    },
    set: function(attributes) {
        var self = this.ptr;
        /* attributes <glTFAttributes> [] */
        attributes = attributes.ptr;
        _glTFPrimitive_set_attributes(self, attributes);
    }
});
Object.defineProperty(glTFPrimitive.prototype, "indices", {
    get: function() {
        var self = this.ptr;
        return _glTFPrimitive_get_indices(self);
    },
    set: function(indices) {
        var self = this.ptr;
        /* indices <int> [] */
        _glTFPrimitive_set_indices(self, indices);
    }
});
Object.defineProperty(glTFPrimitive.prototype, "material", {
    get: function() {
        var self = this.ptr;
        return _glTFPrimitive_get_material(self);
    },
    set: function(material) {
        var self = this.ptr;
        /* material <int> [] */
        _glTFPrimitive_set_material(self, material);
    }
});
Object.defineProperty(glTFPrimitive.prototype, "mode", {
    get: function() {
        var self = this.ptr;
        return _glTFPrimitive_get_mode(self);
    },
    set: function(mode) {
        var self = this.ptr;
        /* mode <glTFPrimitiveType> [] */
        if (mode && typeof mode === "object") mode = mode.ptr;
        _glTFPrimitive_set_mode(self, mode);
    }
});
Object.defineProperty(glTFPrimitive.prototype, "targets", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFPrimitive_get_targets(self), std::vector<glTFMorphTarget>);
    },
    set: function(targets) {
        var self = this.ptr;
        /* targets <std::vector<glTFMorphTarget>> [] */
        targets = targets.ptr;
        _glTFPrimitive_set_targets(self, targets);
    }
});
glTFPrimitive.prototype["__destroy__"] = glTFPrimitive.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFPrimitive___destroy__(self);
};
// glTFSampler
function glTFSampler() {
    var self = this.ptr;
    this.ptr = _glTFSampler_glTFSampler_0(self); getCache(glTFSampler)[this.ptr] = this;
};
glTFSampler.prototype = Object.create(WrapperObject.prototype);
glTFSampler.prototype.constructor = glTFSampler;
glTFSampler.prototype.__class__ = glTFSampler;
glTFSampler.__cache__ = {};
Module['glTFSampler'] = glTFSampler;
Object.defineProperty(glTFSampler.prototype, "mag_filter", {
    get: function() {
        var self = this.ptr;
        return _glTFSampler_get_mag_filter(self);
    },
    set: function(mag_filter) {
        var self = this.ptr;
        /* mag_filter <int> [] */
        _glTFSampler_set_mag_filter(self, mag_filter);
    }
});
Object.defineProperty(glTFSampler.prototype, "min_filter", {
    get: function() {
        var self = this.ptr;
        return _glTFSampler_get_min_filter(self);
    },
    set: function(min_filter) {
        var self = this.ptr;
        /* min_filter <int> [] */
        _glTFSampler_set_min_filter(self, min_filter);
    }
});
Object.defineProperty(glTFSampler.prototype, "wrap_s", {
    get: function() {
        var self = this.ptr;
        return _glTFSampler_get_wrap_s(self);
    },
    set: function(wrap_s) {
        var self = this.ptr;
        /* wrap_s <int> [] */
        _glTFSampler_set_wrap_s(self, wrap_s);
    }
});
Object.defineProperty(glTFSampler.prototype, "wrap_t", {
    get: function() {
        var self = this.ptr;
        return _glTFSampler_get_wrap_t(self);
    },
    set: function(wrap_t) {
        var self = this.ptr;
        /* wrap_t <int> [] */
        _glTFSampler_set_wrap_t(self, wrap_t);
    }
});
Object.defineProperty(glTFSampler.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFSampler_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _glTFSampler_set_name(self, name);
    }
});
glTFSampler.prototype["__destroy__"] = glTFSampler.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFSampler___destroy__(self);
};
// glTFScene
function glTFScene() {
    var self = this.ptr;
    this.ptr = _glTFScene_glTFScene_0(self); getCache(glTFScene)[this.ptr] = this;
};
glTFScene.prototype = Object.create(WrapperObject.prototype);
glTFScene.prototype.constructor = glTFScene;
glTFScene.prototype.__class__ = glTFScene;
glTFScene.__cache__ = {};
Module['glTFScene'] = glTFScene;
Object.defineProperty(glTFScene.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFScene_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _glTFScene_set_name(self, name);
    }
});
Object.defineProperty(glTFScene.prototype, "nodes", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFScene_get_nodes(self), std::vector<int>);
    },
    set: function(nodes) {
        var self = this.ptr;
        /* nodes <std::vector<int>> [] */
        nodes = nodes.ptr;
        _glTFScene_set_nodes(self, nodes);
    }
});
glTFScene.prototype["__destroy__"] = glTFScene.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFScene___destroy__(self);
};
// glTFSkin
function glTFSkin() {
    var self = this.ptr;
    this.ptr = _glTFSkin_glTFSkin_0(self); getCache(glTFSkin)[this.ptr] = this;
};
glTFSkin.prototype = Object.create(WrapperObject.prototype);
glTFSkin.prototype.constructor = glTFSkin;
glTFSkin.prototype.__class__ = glTFSkin;
glTFSkin.__cache__ = {};
Module['glTFSkin'] = glTFSkin;
Object.defineProperty(glTFSkin.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFSkin_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _glTFSkin_set_name(self, name);
    }
});
Object.defineProperty(glTFSkin.prototype, "skeleton", {
    get: function() {
        var self = this.ptr;
        return _glTFSkin_get_skeleton(self);
    },
    set: function(skeleton) {
        var self = this.ptr;
        /* skeleton <int> [] */
        _glTFSkin_set_skeleton(self, skeleton);
    }
});
Object.defineProperty(glTFSkin.prototype, "joints", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFSkin_get_joints(self), std::vector<int>);
    },
    set: function(joints) {
        var self = this.ptr;
        /* joints <std::vector<int>> [] */
        joints = joints.ptr;
        _glTFSkin_set_joints(self, joints);
    }
});
Object.defineProperty(glTFSkin.prototype, "inverse_bind_matrices", {
    get: function() {
        var self = this.ptr;
        return _glTFSkin_get_inverse_bind_matrices(self);
    },
    set: function(inverse_bind_matrices) {
        var self = this.ptr;
        /* inverse_bind_matrices <int> [] */
        _glTFSkin_set_inverse_bind_matrices(self, inverse_bind_matrices);
    }
});
glTFSkin.prototype["__destroy__"] = glTFSkin.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFSkin___destroy__(self);
};
// glTFSparse
function glTFSparse() {
    var self = this.ptr;
    this.ptr = _glTFSparse_glTFSparse_0(self); getCache(glTFSparse)[this.ptr] = this;
};
glTFSparse.prototype = Object.create(WrapperObject.prototype);
glTFSparse.prototype.constructor = glTFSparse;
glTFSparse.prototype.__class__ = glTFSparse;
glTFSparse.__cache__ = {};
Module['glTFSparse'] = glTFSparse;
Object.defineProperty(glTFSparse.prototype, "count", {
    get: function() {
        var self = this.ptr;
        return _glTFSparse_get_count(self);
    },
    set: function(count) {
        var self = this.ptr;
        /* count <int> [] */
        _glTFSparse_set_count(self, count);
    }
});
Object.defineProperty(glTFSparse.prototype, "indices", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFSparse_get_indices(self), glTFSparseIndices);
    },
    set: function(indices) {
        var self = this.ptr;
        /* indices <glTFSparseIndices> [] */
        indices = indices.ptr;
        _glTFSparse_set_indices(self, indices);
    }
});
Object.defineProperty(glTFSparse.prototype, "values", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_glTFSparse_get_values(self), glTFSparseValues);
    },
    set: function(values) {
        var self = this.ptr;
        /* values <glTFSparseValues> [] */
        values = values.ptr;
        _glTFSparse_set_values(self, values);
    }
});
glTFSparse.prototype["__destroy__"] = glTFSparse.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFSparse___destroy__(self);
};
// glTFSparseIndices
function glTFSparseIndices() {
    var self = this.ptr;
    this.ptr = _glTFSparseIndices_glTFSparseIndices_0(self); getCache(glTFSparseIndices)[this.ptr] = this;
};
glTFSparseIndices.prototype = Object.create(WrapperObject.prototype);
glTFSparseIndices.prototype.constructor = glTFSparseIndices;
glTFSparseIndices.prototype.__class__ = glTFSparseIndices;
glTFSparseIndices.__cache__ = {};
Module['glTFSparseIndices'] = glTFSparseIndices;
Object.defineProperty(glTFSparseIndices.prototype, "buffer_view", {
    get: function() {
        var self = this.ptr;
        return _glTFSparseIndices_get_buffer_view(self);
    },
    set: function(buffer_view) {
        var self = this.ptr;
        /* buffer_view <int> [] */
        _glTFSparseIndices_set_buffer_view(self, buffer_view);
    }
});
Object.defineProperty(glTFSparseIndices.prototype, "byte_offset", {
    get: function() {
        var self = this.ptr;
        return _glTFSparseIndices_get_byte_offset(self);
    },
    set: function(byte_offset) {
        var self = this.ptr;
        /* byte_offset <int> [] */
        _glTFSparseIndices_set_byte_offset(self, byte_offset);
    }
});
Object.defineProperty(glTFSparseIndices.prototype, "component_type", {
    get: function() {
        var self = this.ptr;
        return _glTFSparseIndices_get_component_type(self);
    },
    set: function(component_type) {
        var self = this.ptr;
        /* component_type <glTFComponentType> [] */
        if (component_type && typeof component_type === "object") component_type = component_type.ptr;
        _glTFSparseIndices_set_component_type(self, component_type);
    }
});
glTFSparseIndices.prototype["__destroy__"] = glTFSparseIndices.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFSparseIndices___destroy__(self);
};
// glTFSparseValues
function glTFSparseValues() {
    var self = this.ptr;
    this.ptr = _glTFSparseValues_glTFSparseValues_0(self); getCache(glTFSparseValues)[this.ptr] = this;
};
glTFSparseValues.prototype = Object.create(WrapperObject.prototype);
glTFSparseValues.prototype.constructor = glTFSparseValues;
glTFSparseValues.prototype.__class__ = glTFSparseValues;
glTFSparseValues.__cache__ = {};
Module['glTFSparseValues'] = glTFSparseValues;
Object.defineProperty(glTFSparseValues.prototype, "buffer_view", {
    get: function() {
        var self = this.ptr;
        return _glTFSparseValues_get_buffer_view(self);
    },
    set: function(buffer_view) {
        var self = this.ptr;
        /* buffer_view <int> [] */
        _glTFSparseValues_set_buffer_view(self, buffer_view);
    }
});
Object.defineProperty(glTFSparseValues.prototype, "byte_offset", {
    get: function() {
        var self = this.ptr;
        return _glTFSparseValues_get_byte_offset(self);
    },
    set: function(byte_offset) {
        var self = this.ptr;
        /* byte_offset <int> [] */
        _glTFSparseValues_set_byte_offset(self, byte_offset);
    }
});
glTFSparseValues.prototype["__destroy__"] = glTFSparseValues.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFSparseValues___destroy__(self);
};
// glTFTexture
function glTFTexture() {
    var self = this.ptr;
    this.ptr = _glTFTexture_glTFTexture_0(self); getCache(glTFTexture)[this.ptr] = this;
};
glTFTexture.prototype = Object.create(WrapperObject.prototype);
glTFTexture.prototype.constructor = glTFTexture;
glTFTexture.prototype.__class__ = glTFTexture;
glTFTexture.__cache__ = {};
Module['glTFTexture'] = glTFTexture;
Object.defineProperty(glTFTexture.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_glTFTexture_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _glTFTexture_set_name(self, name);
    }
});
Object.defineProperty(glTFTexture.prototype, "sampler", {
    get: function() {
        var self = this.ptr;
        return _glTFTexture_get_sampler(self);
    },
    set: function(sampler) {
        var self = this.ptr;
        /* sampler <int> [] */
        _glTFTexture_set_sampler(self, sampler);
    }
});
Object.defineProperty(glTFTexture.prototype, "source", {
    get: function() {
        var self = this.ptr;
        return _glTFTexture_get_source(self);
    },
    set: function(source) {
        var self = this.ptr;
        /* source <int> [] */
        _glTFTexture_set_source(self, source);
    }
});
glTFTexture.prototype["__destroy__"] = glTFTexture.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFTexture___destroy__(self);
};
// glTFTextureInfo
function glTFTextureInfo() {
    var self = this.ptr;
    this.ptr = _glTFTextureInfo_glTFTextureInfo_0(self); getCache(glTFTextureInfo)[this.ptr] = this;
};
glTFTextureInfo.prototype = Object.create(WrapperObject.prototype);
glTFTextureInfo.prototype.constructor = glTFTextureInfo;
glTFTextureInfo.prototype.__class__ = glTFTextureInfo;
glTFTextureInfo.__cache__ = {};
Module['glTFTextureInfo'] = glTFTextureInfo;
Object.defineProperty(glTFTextureInfo.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _glTFTextureInfo_get_index(self);
    },
    set: function(index) {
        var self = this.ptr;
        /* index <int> [] */
        _glTFTextureInfo_set_index(self, index);
    }
});
Object.defineProperty(glTFTextureInfo.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return _glTFTextureInfo_get_scale(self);
    },
    set: function(scale) {
        var self = this.ptr;
        /* scale <float> [] */
        _glTFTextureInfo_set_scale(self, scale);
    }
});
glTFTextureInfo.prototype["__destroy__"] = glTFTextureInfo.prototype.__destroy__ = function() {
    var self = this.ptr;
    _glTFTextureInfo___destroy__(self);
};

(function() {
    function setupEnums() {
        // glTFAlphaMode
        Module['glTFAlphaMode']['OPAQUE'] = _emscripten_enum_glTFAlphaMode_OPAQUE();
        Module['glTFAlphaMode']['MASK'] = _emscripten_enum_glTFAlphaMode_MASK();
        Module['glTFAlphaMode']['BLEND'] = _emscripten_enum_glTFAlphaMode_BLEND();
        // glTFComponentType
        Module['glTFComponentType']['BYTE'] = _emscripten_enum_glTFComponentType_BYTE();
        Module['glTFComponentType']['UNSIGNED_BYTE'] = _emscripten_enum_glTFComponentType_UNSIGNED_BYTE();
        Module['glTFComponentType']['SHORT'] = _emscripten_enum_glTFComponentType_SHORT();
        Module['glTFComponentType']['UNSIGNED_SHORT'] = _emscripten_enum_glTFComponentType_UNSIGNED_SHORT();
        Module['glTFComponentType']['INT'] = _emscripten_enum_glTFComponentType_INT();
        Module['glTFComponentType']['FLOAT'] = _emscripten_enum_glTFComponentType_FLOAT();
        // glTFInterpolation
        Module['glTFInterpolation']['LINEAR'] = _emscripten_enum_glTFInterpolation_LINEAR();
        Module['glTFInterpolation']['STEP'] = _emscripten_enum_glTFInterpolation_STEP();
        Module['glTFInterpolation']['CATMULLROMSPLINE'] = _emscripten_enum_glTFInterpolation_CATMULLROMSPLINE();
        Module['glTFInterpolation']['CUBIC_SPLINE'] = _emscripten_enum_glTFInterpolation_CUBIC_SPLINE();
        // glTFPrimitiveType
        Module['glTFPrimitiveType']['POINTS'] = _emscripten_enum_glTFPrimitiveType_POINTS();
        Module['glTFPrimitiveType']['LINES'] = _emscripten_enum_glTFPrimitiveType_LINES();
        Module['glTFPrimitiveType']['LINE_LOOP'] = _emscripten_enum_glTFPrimitiveType_LINE_LOOP();
        Module['glTFPrimitiveType']['LINE_STRIP'] = _emscripten_enum_glTFPrimitiveType_LINE_STRIP();
        Module['glTFPrimitiveType']['TRIANGLES'] = _emscripten_enum_glTFPrimitiveType_TRIANGLES();
        Module['glTFPrimitiveType']['TRIANGLE_STRIP'] = _emscripten_enum_glTFPrimitiveType_TRIANGLE_STRIP();
        Module['glTFPrimitiveType']['TRIANGLE_FAN'] = _emscripten_enum_glTFPrimitiveType_TRIANGLE_FAN();
        // glTFType
        Module['glTFType']['SCALAR'] = _emscripten_enum_glTFType_SCALAR();
        Module['glTFType']['VEC2'] = _emscripten_enum_glTFType_VEC2();
        Module['glTFType']['VEC3'] = _emscripten_enum_glTFType_VEC3();
        Module['glTFType']['VEC4'] = _emscripten_enum_glTFType_VEC4();
        Module['glTFType']['MAT2'] = _emscripten_enum_glTFType_MAT2();
        Module['glTFType']['MAT3'] = _emscripten_enum_glTFType_MAT3();
        Module['glTFType']['MAT4'] = _emscripten_enum_glTFType_MAT4();
        Module['glTFType']['INVALID'] = _emscripten_enum_glTFType_INVALID();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
