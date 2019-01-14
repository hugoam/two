Module['glm'] = Module['glm'] || {};
Module['ui'] = Module['ui'] || {};
// CanvasConnect
function CanvasConnect() {
    this.ptr = _mud_CanvasConnect_CanvasConnect_0(); getCache(CanvasConnect)[this.ptr] = this;
    this.type = CanvasConnect;
};
CanvasConnect.prototype = Object.create(WrapperObject.prototype);
CanvasConnect.prototype.constructor = CanvasConnect;
CanvasConnect.prototype.__class__ = CanvasConnect;
CanvasConnect.__cache__ = {};
CanvasConnect.__type__ = _mud_CanvasConnect__type();
Module['CanvasConnect'] = CanvasConnect;
CanvasConnect.prototype["__destroy__"] = CanvasConnect.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_CanvasConnect__destroy(self);
};
// Clipboard
function Clipboard() {
    this.ptr = _mud_Clipboard_Clipboard_0(); getCache(Clipboard)[this.ptr] = this;
    this.type = Clipboard;
};
Clipboard.prototype = Object.create(WrapperObject.prototype);
Clipboard.prototype.constructor = Clipboard;
Clipboard.prototype.__class__ = Clipboard;
Clipboard.__cache__ = {};
Clipboard.__type__ = _mud_Clipboard__type();
Module['Clipboard'] = Clipboard;
Object.defineProperty(Clipboard.prototype, "text", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Clipboard__get_text(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <std::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_Clipboard__set_text(self, value);
    }
});
Object.defineProperty(Clipboard.prototype, "line_mode", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Clipboard__get_line_mode(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_Clipboard__set_line_mode(self, value);
    }
});
Clipboard.prototype["__destroy__"] = Clipboard.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Clipboard__destroy(self);
};
// Dock
function Dock() {
    this.ptr = _mud_Dock_Dock_0(); getCache(Dock)[this.ptr] = this;
    this.type = Dock;
};
Dock.prototype = Object.create(WrapperObject.prototype);
Dock.prototype.constructor = Dock;
Dock.prototype.__class__ = Dock;
Dock.__cache__ = {};
Dock.__type__ = _mud_Dock__type();
Module['Dock'] = Dock;
Dock.prototype["__destroy__"] = Dock.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Dock__destroy(self);
};
// Docksystem
function Docksystem() { throw "cannot construct a Docksystem, no constructor in IDL" }
Docksystem.prototype = Object.create(WrapperObject.prototype);
Docksystem.prototype.constructor = Docksystem;
Docksystem.prototype.__class__ = Docksystem;
Docksystem.__cache__ = {};
Docksystem.__type__ = _mud_Docksystem__type();
Module['Docksystem'] = Docksystem;
Docksystem.prototype["__destroy__"] = Docksystem.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Docksystem__destroy(self);
};
// Gradient
function Gradient() {
    this.ptr = _mud_Gradient_Gradient_0(); getCache(Gradient)[this.ptr] = this;
    this.type = Gradient;
};
Gradient.prototype = Object.create(WrapperObject.prototype);
Gradient.prototype.constructor = Gradient;
Gradient.prototype.__class__ = Gradient;
Gradient.__cache__ = {};
Gradient.__type__ = _mud_Gradient__type();
Module['Gradient'] = Gradient;
Object.defineProperty(Gradient.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Gradient__get_start(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Colour> [] */
        value = value.ptr;
        _mud_Gradient__set_start(self, value);
    }
});
Object.defineProperty(Gradient.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Gradient__get_end(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Colour> [] */
        value = value.ptr;
        _mud_Gradient__set_end(self, value);
    }
});
Gradient.prototype["__destroy__"] = Gradient.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Gradient__destroy(self);
};
// GridSolver
function GridSolver() { throw "cannot construct a GridSolver, no constructor in IDL" }
GridSolver.prototype = Object.create(WrapperObject.prototype);
GridSolver.prototype.constructor = GridSolver;
GridSolver.prototype.__class__ = GridSolver;
GridSolver.__cache__ = {};
GridSolver.__type__ = _mud_GridSolver__type();
Module['GridSolver'] = GridSolver;
GridSolver.prototype["__destroy__"] = GridSolver.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_GridSolver__destroy(self);
};
// ImageSkin
function ImageSkin(image, left, top, right, bottom, margin, stretch) {
    /* image <Image> [] */
    image = image.ptr;
    /* left <int> [] */
    /* top <int> [] */
    /* right <int> [] */
    /* bottom <int> [] */
    /* margin <int> [] */
    /* stretch <Dim> [] */
    if (stretch && typeof stretch === "object") stretch = stretch.ptr;
    if (margin === undefined) { this.ptr = _mud_ImageSkin_ImageSkin_5(image, left, top, right, bottom); getCache(ImageSkin)[this.ptr] = this; return; }
    if (stretch === undefined) { this.ptr = _mud_ImageSkin_ImageSkin_6(image, left, top, right, bottom, margin); getCache(ImageSkin)[this.ptr] = this; return; }
    this.ptr = _mud_ImageSkin_ImageSkin_7(image, left, top, right, bottom, margin, stretch); getCache(ImageSkin)[this.ptr] = this;
    this.type = ImageSkin;
};
ImageSkin.prototype = Object.create(WrapperObject.prototype);
ImageSkin.prototype.constructor = ImageSkin;
ImageSkin.prototype.__class__ = ImageSkin;
ImageSkin.__cache__ = {};
ImageSkin.__type__ = _mud_ImageSkin__type();
Module['ImageSkin'] = ImageSkin;
Object.defineProperty(ImageSkin.prototype, "d_image", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ImageSkin__get_d_image(self), Image);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Image> [] */
        value = value.ptr;
        _mud_ImageSkin__set_d_image(self, value);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_left", {
    get: function() {
        var self = this.ptr;
        return _mud_ImageSkin__get_d_left(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_ImageSkin__set_d_left(self, value);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_top", {
    get: function() {
        var self = this.ptr;
        return _mud_ImageSkin__get_d_top(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_ImageSkin__set_d_top(self, value);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_right", {
    get: function() {
        var self = this.ptr;
        return _mud_ImageSkin__get_d_right(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_ImageSkin__set_d_right(self, value);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_bottom", {
    get: function() {
        var self = this.ptr;
        return _mud_ImageSkin__get_d_bottom(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_ImageSkin__set_d_bottom(self, value);
    }
});
Object.defineProperty(ImageSkin.prototype, "margin", {
    get: function() {
        var self = this.ptr;
        return _mud_ImageSkin__get_margin(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_ImageSkin__set_margin(self, value);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_stretch", {
    get: function() {
        var self = this.ptr;
        return _mud_ImageSkin__get_d_stretch(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Dim> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_ImageSkin__set_d_stretch(self, value);
    }
});
ImageSkin.prototype["__destroy__"] = ImageSkin.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ImageSkin__destroy(self);
};
// InkStyle
function InkStyle(name) {
    ensureCache.prepare();
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    if (name === undefined) { this.ptr = _mud_InkStyle_InkStyle_0(); getCache(InkStyle)[this.ptr] = this; return; }
    this.ptr = _mud_InkStyle_InkStyle_1(name); getCache(InkStyle)[this.ptr] = this;
    this.type = InkStyle;
};
InkStyle.prototype = Object.create(WrapperObject.prototype);
InkStyle.prototype.constructor = InkStyle;
InkStyle.prototype.__class__ = InkStyle;
InkStyle.__cache__ = {};
InkStyle.__type__ = _mud_InkStyle__type();
Module['InkStyle'] = InkStyle;
Object.defineProperty(InkStyle.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_InkStyle__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <std::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_InkStyle__set_name(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "empty", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_InkStyle__get_empty(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_InkStyle__set_empty(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "background_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_background_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Colour> [] */
        value = value.ptr;
        _mud_InkStyle__set_background_colour(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "border_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_border_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Colour> [] */
        value = value.ptr;
        _mud_InkStyle__set_border_colour(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "image_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_image_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Colour> [] */
        value = value.ptr;
        _mud_InkStyle__set_image_colour(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "text_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_text_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Colour> [] */
        value = value.ptr;
        _mud_InkStyle__set_text_colour(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "text_font", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_InkStyle__get_text_font(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <std::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_InkStyle__set_text_font(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "text_size", {
    get: function() {
        var self = this.ptr;
        return _mud_InkStyle__get_text_size(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_InkStyle__set_text_size(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "text_break", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_InkStyle__get_text_break(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_InkStyle__set_text_break(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "text_wrap", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_InkStyle__get_text_wrap(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_InkStyle__set_text_wrap(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "border_width", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_border_width(self), vec4);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec4> [] */
        value = value.ptr;
        _mud_InkStyle__set_border_width(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "corner_radius", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_corner_radius(self), vec4);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec4> [] */
        value = value.ptr;
        _mud_InkStyle__set_corner_radius(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "weak_corners", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_InkStyle__get_weak_corners(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_InkStyle__set_weak_corners(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "padding", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_padding(self), vec4);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec4> [] */
        value = value.ptr;
        _mud_InkStyle__set_padding(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "margin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_margin(self), vec4);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec4> [] */
        value = value.ptr;
        _mud_InkStyle__set_margin(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "linear_gradient", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_linear_gradient(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_InkStyle__set_linear_gradient(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "linear_gradient_dim", {
    get: function() {
        var self = this.ptr;
        return _mud_InkStyle__get_linear_gradient_dim(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Dim> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_InkStyle__set_linear_gradient_dim(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "image", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_image(self), Image);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Image> [] */
        value = value.ptr;
        _mud_InkStyle__set_image(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "overlay", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_overlay(self), Image);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Image> [] */
        value = value.ptr;
        _mud_InkStyle__set_overlay(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "tile", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_tile(self), Image);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Image> [] */
        value = value.ptr;
        _mud_InkStyle__set_tile(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "image_skin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_image_skin(self), ImageSkin);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <ImageSkin> [] */
        value = value.ptr;
        _mud_InkStyle__set_image_skin(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "shadow", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_shadow(self), Shadow);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Shadow> [] */
        value = value.ptr;
        _mud_InkStyle__set_shadow(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "shadow_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_shadow_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Colour> [] */
        value = value.ptr;
        _mud_InkStyle__set_shadow_colour(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "hover_cursor", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_hover_cursor(self), Style);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Style> [] */
        value = value.ptr;
        _mud_InkStyle__set_hover_cursor(self, value);
    }
});
InkStyle.prototype["__destroy__"] = InkStyle.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_InkStyle__destroy(self);
};
// Layer
function Layer() { throw "cannot construct a Layer, no constructor in IDL" }
Layer.prototype = Object.create(WrapperObject.prototype);
Layer.prototype.constructor = Layer;
Layer.prototype.__class__ = Layer;
Layer.__cache__ = {};
Layer.__type__ = _mud_Layer__type();
Module['Layer'] = Layer;
Layer.prototype["__destroy__"] = Layer.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Layer__destroy(self);
};
// Layout
function Layout(name) {
    ensureCache.prepare();
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    if (name === undefined) { this.ptr = _mud_Layout_Layout_0(); getCache(Layout)[this.ptr] = this; return; }
    this.ptr = _mud_Layout_Layout_1(name); getCache(Layout)[this.ptr] = this;
    this.type = Layout;
};
Layout.prototype = Object.create(WrapperObject.prototype);
Layout.prototype.constructor = Layout;
Layout.prototype.__class__ = Layout;
Layout.__cache__ = {};
Layout.__type__ = _mud_Layout__type();
Module['Layout'] = Layout;
Object.defineProperty(Layout.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Layout__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <std::string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_Layout__set_name(self, value);
    }
});
Object.defineProperty(Layout.prototype, "solver", {
    get: function() {
        var self = this.ptr;
        return _mud_Layout__get_solver(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <LayoutSolver> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Layout__set_solver(self, value);
    }
});
Object.defineProperty(Layout.prototype, "flow", {
    get: function() {
        var self = this.ptr;
        return _mud_Layout__get_flow(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Flow> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Layout__set_flow(self, value);
    }
});
Object.defineProperty(Layout.prototype, "space", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_space(self), Space);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Space> [] */
        value = value.ptr;
        _mud_Layout__set_space(self, value);
    }
});
Object.defineProperty(Layout.prototype, "clipping", {
    get: function() {
        var self = this.ptr;
        return _mud_Layout__get_clipping(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Clipping> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Layout__set_clipping(self, value);
    }
});
Object.defineProperty(Layout.prototype, "opacity", {
    get: function() {
        var self = this.ptr;
        return _mud_Layout__get_opacity(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Opacity> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Layout__set_opacity(self, value);
    }
});
Object.defineProperty(Layout.prototype, "span", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_span(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_Layout__set_span(self, value);
    }
});
Object.defineProperty(Layout.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_size(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_Layout__set_size(self, value);
    }
});
Object.defineProperty(Layout.prototype, "padding", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_padding(self), vec4);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec4> [] */
        value = value.ptr;
        _mud_Layout__set_padding(self, value);
    }
});
Object.defineProperty(Layout.prototype, "margin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_margin(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_Layout__set_margin(self, value);
    }
});
Object.defineProperty(Layout.prototype, "spacing", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_spacing(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_Layout__set_spacing(self, value);
    }
});
Object.defineProperty(Layout.prototype, "zorder", {
    get: function() {
        var self = this.ptr;
        return _mud_Layout__get_zorder(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <int> [] */
        _mud_Layout__set_zorder(self, value);
    }
});
Object.defineProperty(Layout.prototype, "no_grid", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Layout__get_no_grid(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_Layout__set_no_grid(self, value);
    }
});
Object.defineProperty(Layout.prototype, "updated", {
    get: function() {
        var self = this.ptr;
        return _mud_Layout__get_updated(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <size_t> [] */
        _mud_Layout__set_updated(self, value);
    }
});
Layout.prototype["__destroy__"] = Layout.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Layout__destroy(self);
};
// NodeConnection
function NodeConnection() {
    this.ptr = _mud_NodeConnection_NodeConnection_0(); getCache(NodeConnection)[this.ptr] = this;
    this.type = NodeConnection;
};
NodeConnection.prototype = Object.create(WrapperObject.prototype);
NodeConnection.prototype.constructor = NodeConnection;
NodeConnection.prototype.__class__ = NodeConnection;
NodeConnection.__cache__ = {};
NodeConnection.__type__ = _mud_NodeConnection__type();
Module['NodeConnection'] = NodeConnection;
NodeConnection.prototype["__destroy__"] = NodeConnection.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_NodeConnection__destroy(self);
};
// Paint
function Paint() {
    this.ptr = _mud_Paint_Paint_0(); getCache(Paint)[this.ptr] = this;
    this.type = Paint;
};
Paint.prototype = Object.create(WrapperObject.prototype);
Paint.prototype.constructor = Paint;
Paint.prototype.__class__ = Paint;
Paint.__cache__ = {};
Paint.__type__ = _mud_Paint__type();
Module['Paint'] = Paint;
Object.defineProperty(Paint.prototype, "fill_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Paint__get_fill_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Colour> [] */
        value = value.ptr;
        _mud_Paint__set_fill_colour(self, value);
    }
});
Object.defineProperty(Paint.prototype, "stroke_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Paint__get_stroke_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Colour> [] */
        value = value.ptr;
        _mud_Paint__set_stroke_colour(self, value);
    }
});
Object.defineProperty(Paint.prototype, "stroke_width", {
    get: function() {
        var self = this.ptr;
        return _mud_Paint__get_stroke_width(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Paint__set_stroke_width(self, value);
    }
});
Paint.prototype["__destroy__"] = Paint.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Paint__destroy(self);
};
// Shadow
function Shadow(xpos, ypos, blur, spread, colour) {
    /* xpos <float> [] */
    /* ypos <float> [] */
    /* blur <float> [] */
    /* spread <float> [] */
    /* colour <Colour> [] */
    if(typeof colour !== "undefined" && colour !== null) { colour = colour.ptr; }
    if (colour === undefined) { this.ptr = _mud_Shadow_Shadow_4(xpos, ypos, blur, spread); getCache(Shadow)[this.ptr] = this; return; }
    this.ptr = _mud_Shadow_Shadow_5(xpos, ypos, blur, spread, colour); getCache(Shadow)[this.ptr] = this;
    this.type = Shadow;
};
Shadow.prototype = Object.create(WrapperObject.prototype);
Shadow.prototype.constructor = Shadow;
Shadow.prototype.__class__ = Shadow;
Shadow.__cache__ = {};
Shadow.__type__ = _mud_Shadow__type();
Module['Shadow'] = Shadow;
Object.defineProperty(Shadow.prototype, "d_xpos", {
    get: function() {
        var self = this.ptr;
        return _mud_Shadow__get_d_xpos(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Shadow__set_d_xpos(self, value);
    }
});
Object.defineProperty(Shadow.prototype, "d_ypos", {
    get: function() {
        var self = this.ptr;
        return _mud_Shadow__get_d_ypos(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Shadow__set_d_ypos(self, value);
    }
});
Object.defineProperty(Shadow.prototype, "d_blur", {
    get: function() {
        var self = this.ptr;
        return _mud_Shadow__get_d_blur(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Shadow__set_d_blur(self, value);
    }
});
Object.defineProperty(Shadow.prototype, "d_spread", {
    get: function() {
        var self = this.ptr;
        return _mud_Shadow__get_d_spread(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_Shadow__set_d_spread(self, value);
    }
});
Object.defineProperty(Shadow.prototype, "d_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shadow__get_d_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Colour> [] */
        value = value.ptr;
        _mud_Shadow__set_d_colour(self, value);
    }
});
Shadow.prototype["__destroy__"] = Shadow.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Shadow__destroy(self);
};
// Space
function Space() {
    this.ptr = _mud_Space_Space_0(); getCache(Space)[this.ptr] = this;
    this.type = Space;
};
Space.prototype = Object.create(WrapperObject.prototype);
Space.prototype.constructor = Space;
Space.prototype.__class__ = Space;
Space.__cache__ = {};
Space.__type__ = _mud_Space__type();
Module['Space'] = Space;
Object.defineProperty(Space.prototype, "direction", {
    get: function() {
        var self = this.ptr;
        return _mud_Space__get_direction(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <FlowAxis> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Space__set_direction(self, value);
    }
});
Object.defineProperty(Space.prototype, "sizingLength", {
    get: function() {
        var self = this.ptr;
        return _mud_Space__get_sizingLength(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Sizing> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Space__set_sizingLength(self, value);
    }
});
Object.defineProperty(Space.prototype, "sizingDepth", {
    get: function() {
        var self = this.ptr;
        return _mud_Space__get_sizingDepth(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Sizing> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Space__set_sizingDepth(self, value);
    }
});
Space.prototype["__destroy__"] = Space.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Space__destroy(self);
};
// Style
function Style() { throw "cannot construct a Style, no constructor in IDL" }
Style.prototype = Object.create(WrapperObject.prototype);
Style.prototype.constructor = Style;
Style.prototype.__class__ = Style;
Style.__cache__ = {};
Style.__type__ = _mud_Style__type();
Module['Style'] = Style;
Object.defineProperty(Style.prototype, "base", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Style__get_base(self), Style);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Style> [] */
        value = value.ptr;
        _mud_Style__set_base(self, value);
    }
});
Object.defineProperty(Style.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Style__get_name(self));
    }});
Object.defineProperty(Style.prototype, "layout", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Style__get_layout(self), Layout);
    }});
Object.defineProperty(Style.prototype, "skin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Style__get_skin(self), InkStyle);
    }});
Style.prototype["__destroy__"] = Style.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Style__destroy(self);
};
// TableSolver
function TableSolver() { throw "cannot construct a TableSolver, no constructor in IDL" }
TableSolver.prototype = Object.create(WrapperObject.prototype);
TableSolver.prototype.constructor = TableSolver;
TableSolver.prototype.__class__ = TableSolver;
TableSolver.__cache__ = {};
TableSolver.__type__ = _mud_TableSolver__type();
Module['TableSolver'] = TableSolver;
TableSolver.prototype["__destroy__"] = TableSolver.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TableSolver__destroy(self);
};
// Text
function Text() { throw "cannot construct a Text, no constructor in IDL" }
Text.prototype = Object.create(WrapperObject.prototype);
Text.prototype.constructor = Text;
Text.prototype.__class__ = Text;
Text.__cache__ = {};
Text.__type__ = _mud_Text__type();
Module['Text'] = Text;
Text.prototype["__destroy__"] = Text.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Text__destroy(self);
};
// TextCursor
function TextCursor() {
    this.ptr = _mud_TextCursor_TextCursor_0(); getCache(TextCursor)[this.ptr] = this;
    this.type = TextCursor;
};
TextCursor.prototype = Object.create(WrapperObject.prototype);
TextCursor.prototype.constructor = TextCursor;
TextCursor.prototype.__class__ = TextCursor;
TextCursor.__cache__ = {};
TextCursor.__type__ = _mud_TextCursor__type();
Module['TextCursor'] = TextCursor;
TextCursor.prototype["__destroy__"] = TextCursor.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TextCursor__destroy(self);
};
// TextMarker
function TextMarker() {
    this.ptr = _mud_TextMarker_TextMarker_0(); getCache(TextMarker)[this.ptr] = this;
    this.type = TextMarker;
};
TextMarker.prototype = Object.create(WrapperObject.prototype);
TextMarker.prototype.constructor = TextMarker;
TextMarker.prototype.__class__ = TextMarker;
TextMarker.__cache__ = {};
TextMarker.__type__ = _mud_TextMarker__type();
Module['TextMarker'] = TextMarker;
TextMarker.prototype["__destroy__"] = TextMarker.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TextMarker__destroy(self);
};
// TextPaint
function TextPaint() {
    this.ptr = _mud_TextPaint_TextPaint_0(); getCache(TextPaint)[this.ptr] = this;
    this.type = TextPaint;
};
TextPaint.prototype = Object.create(WrapperObject.prototype);
TextPaint.prototype.constructor = TextPaint;
TextPaint.prototype.__class__ = TextPaint;
TextPaint.__cache__ = {};
TextPaint.__type__ = _mud_TextPaint__type();
Module['TextPaint'] = TextPaint;
Object.defineProperty(TextPaint.prototype, "font", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_TextPaint__get_font(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <const char*> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_TextPaint__set_font(self, value);
    }
});
Object.defineProperty(TextPaint.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_TextPaint__get_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Colour> [] */
        value = value.ptr;
        _mud_TextPaint__set_colour(self, value);
    }
});
Object.defineProperty(TextPaint.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return _mud_TextPaint__get_size(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_TextPaint__set_size(self, value);
    }
});
Object.defineProperty(TextPaint.prototype, "text_break", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_TextPaint__get_text_break(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_TextPaint__set_text_break(self, value);
    }
});
Object.defineProperty(TextPaint.prototype, "text_wrap", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_TextPaint__get_text_wrap(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_TextPaint__set_text_wrap(self, value);
    }
});
TextPaint.prototype["__destroy__"] = TextPaint.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TextPaint__destroy(self);
};
// TextSelection
function TextSelection() {
    this.ptr = _mud_TextSelection_TextSelection_0(); getCache(TextSelection)[this.ptr] = this;
    this.type = TextSelection;
};
TextSelection.prototype = Object.create(WrapperObject.prototype);
TextSelection.prototype.constructor = TextSelection;
TextSelection.prototype.__class__ = TextSelection;
TextSelection.__cache__ = {};
TextSelection.__type__ = _mud_TextSelection__type();
Module['TextSelection'] = TextSelection;
TextSelection.prototype["__destroy__"] = TextSelection.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TextSelection__destroy(self);
};
// UiRect
function UiRect() {
    this.ptr = _mud_UiRect_UiRect_0(); getCache(UiRect)[this.ptr] = this;
    this.type = UiRect;
};
UiRect.prototype = Object.create(WrapperObject.prototype);
UiRect.prototype.constructor = UiRect;
UiRect.prototype.__class__ = UiRect;
UiRect.__cache__ = {};
UiRect.__type__ = _mud_UiRect__type();
Module['UiRect'] = UiRect;
Object.defineProperty(UiRect.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_UiRect__get_position(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_UiRect__set_position(self, value);
    }
});
Object.defineProperty(UiRect.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_UiRect__get_size(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_UiRect__set_size(self, value);
    }
});
Object.defineProperty(UiRect.prototype, "content", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_UiRect__get_content(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_UiRect__set_content(self, value);
    }
});
Object.defineProperty(UiRect.prototype, "span", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_UiRect__get_span(self), vec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <vec2> [] */
        value = value.ptr;
        _mud_UiRect__set_span(self, value);
    }
});
Object.defineProperty(UiRect.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return _mud_UiRect__get_scale(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <float> [] */
        _mud_UiRect__set_scale(self, value);
    }
});
UiRect.prototype["__destroy__"] = UiRect.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_UiRect__destroy(self);
};
// UiWindow
function UiWindow() { throw "cannot construct a UiWindow, no constructor in IDL" }
UiWindow.prototype = Object.create(WrapperObject.prototype);
UiWindow.prototype.constructor = UiWindow;
UiWindow.prototype.__class__ = UiWindow;
UiWindow.__cache__ = {};
UiWindow.__type__ = _mud_UiWindow__type();
Module['UiWindow'] = UiWindow;
UiWindow.prototype["__destroy__"] = UiWindow.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_UiWindow__destroy(self);
};
// User
function User() { throw "cannot construct a User, no constructor in IDL" }
User.prototype = Object.create(WrapperObject.prototype);
User.prototype.constructor = User;
User.prototype.__class__ = User;
User.__cache__ = {};
User.__type__ = _mud_User__type();
Module['User'] = User;
User.prototype["__destroy__"] = User.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_User__destroy(self);
};
// Vg
function Vg() { throw "cannot construct a Vg, no constructor in IDL" }
Vg.prototype = Object.create(WrapperObject.prototype);
Vg.prototype.constructor = Vg;
Vg.prototype.__class__ = Vg;
Vg.__cache__ = {};
Vg.__type__ = _mud_Vg__type();
Module['Vg'] = Vg;
Vg.prototype["__destroy__"] = Vg.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Vg__destroy(self);
};
// Frame
function Frame() { throw "cannot construct a Frame, no constructor in IDL" }
Frame.prototype = Object.create(WrapperObject.prototype);
Frame.prototype.constructor = Frame;
Frame.prototype.__class__ = Frame;
Frame.__cache__ = {};
Frame.__type__ = _mud_Frame__type();
Module['Frame'] = Frame;
Frame.prototype["__destroy__"] = Frame.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Frame__destroy(self);
};
// FrameSolver
function FrameSolver() { throw "cannot construct a FrameSolver, no constructor in IDL" }
FrameSolver.prototype = Object.create(WrapperObject.prototype);
FrameSolver.prototype.constructor = FrameSolver;
FrameSolver.prototype.__class__ = FrameSolver;
FrameSolver.__cache__ = {};
FrameSolver.__type__ = _mud_FrameSolver__type();
Module['FrameSolver'] = FrameSolver;
FrameSolver.prototype["__destroy__"] = FrameSolver.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FrameSolver__destroy(self);
};
// LineSolver
function LineSolver() { throw "cannot construct a LineSolver, no constructor in IDL" }
LineSolver.prototype = Object.create(WrapperObject.prototype);
LineSolver.prototype.constructor = LineSolver;
LineSolver.prototype.__class__ = LineSolver;
LineSolver.__cache__ = {};
LineSolver.__type__ = _mud_LineSolver__type();
Module['LineSolver'] = LineSolver;
LineSolver.prototype["__destroy__"] = LineSolver.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_LineSolver__destroy(self);
};
// Widget
function Widget() { throw "cannot construct a Widget, no constructor in IDL" }
Widget.prototype = Object.create(WrapperObject.prototype);
Widget.prototype.constructor = Widget;
Widget.prototype.__class__ = Widget;
Widget.__cache__ = {};
Widget.__type__ = _mud_Widget__type();
Module['Widget'] = Widget;
Widget.prototype["activated"] = Widget.prototype.activated = function(self) {
    var self = this.ptr;
    return !!(_mud_Widget_activated_0(self));
};
Widget.prototype["char_stroke"] = Widget.prototype.char_stroke = function(self, code, modifier) {
    var self = this.ptr;
    /* code <Key> [] */
    if (code && typeof code === "object") code = code.ptr;
    /* modifier <InputMod> [] */
    if (modifier && typeof modifier === "object") modifier = modifier.ptr;
    if (modifier === undefined) { return wrapPointer(_mud_Widget_char_stroke_1(self, code), KeyEvent); }
    return wrapPointer(_mud_Widget_char_stroke_2(self, code, modifier), KeyEvent);
};
Widget.prototype["clear_focus"] = Widget.prototype.clear_focus = function(self) {
    var self = this.ptr;
    _mud_Widget_clear_focus_0(self);
};
Widget.prototype["closed"] = Widget.prototype.closed = function(self) {
    var self = this.ptr;
    return !!(_mud_Widget_closed_0(self));
};
Widget.prototype["disable_state"] = Widget.prototype.disable_state = function(self, state) {
    var self = this.ptr;
    /* state <WidgetState> [] */
    if (state && typeof state === "object") state = state.ptr;
    _mud_Widget_disable_state_1(self, state);
};
Widget.prototype["enable_state"] = Widget.prototype.enable_state = function(self, state) {
    var self = this.ptr;
    /* state <WidgetState> [] */
    if (state && typeof state === "object") state = state.ptr;
    _mud_Widget_enable_state_1(self, state);
};
Widget.prototype["focused"] = Widget.prototype.focused = function(self) {
    var self = this.ptr;
    return !!(_mud_Widget_focused_0(self));
};
Widget.prototype["hovered"] = Widget.prototype.hovered = function(self) {
    var self = this.ptr;
    return !!(_mud_Widget_hovered_0(self));
};
Widget.prototype["key_event"] = Widget.prototype.key_event = function(self, code, event_type, modifier) {
    var self = this.ptr;
    /* code <Key> [] */
    if (code && typeof code === "object") code = code.ptr;
    /* event_type <EventType> [] */
    if (event_type && typeof event_type === "object") event_type = event_type.ptr;
    /* modifier <InputMod> [] */
    if (modifier && typeof modifier === "object") modifier = modifier.ptr;
    if (modifier === undefined) { return wrapPointer(_mud_Widget_key_event_2(self, code, event_type), KeyEvent); }
    return wrapPointer(_mud_Widget_key_event_3(self, code, event_type, modifier), KeyEvent);
};
Widget.prototype["key_stroke"] = Widget.prototype.key_stroke = function(self, code, modifier) {
    var self = this.ptr;
    /* code <Key> [] */
    if (code && typeof code === "object") code = code.ptr;
    /* modifier <InputMod> [] */
    if (modifier && typeof modifier === "object") modifier = modifier.ptr;
    if (modifier === undefined) { return wrapPointer(_mud_Widget_key_stroke_1(self, code), KeyEvent); }
    return wrapPointer(_mud_Widget_key_stroke_2(self, code, modifier), KeyEvent);
};
Widget.prototype["modal"] = Widget.prototype.modal = function(self) {
    var self = this.ptr;
    return !!(_mud_Widget_modal_0(self));
};
Widget.prototype["mouse_event"] = Widget.prototype.mouse_event = function(self, device, event_type, modifier, consume) {
    var self = this.ptr;
    /* device <DeviceType> [] */
    if (device && typeof device === "object") device = device.ptr;
    /* event_type <EventType> [] */
    if (event_type && typeof event_type === "object") event_type = event_type.ptr;
    /* modifier <InputMod> [] */
    if (modifier && typeof modifier === "object") modifier = modifier.ptr;
    /* consume <bool> [] */
    if (modifier === undefined) { return wrapPointer(_mud_Widget_mouse_event_2(self, device, event_type), MouseEvent); }
    if (consume === undefined) { return wrapPointer(_mud_Widget_mouse_event_3(self, device, event_type, modifier), MouseEvent); }
    return wrapPointer(_mud_Widget_mouse_event_4(self, device, event_type, modifier, consume), MouseEvent);
};
Widget.prototype["parent_modal"] = Widget.prototype.parent_modal = function(self) {
    var self = this.ptr;
    return wrapPointer(_mud_Widget_parent_modal_0(self), Widget);
};
Widget.prototype["pressed"] = Widget.prototype.pressed = function(self) {
    var self = this.ptr;
    return !!(_mud_Widget_pressed_0(self));
};
Widget.prototype["selected"] = Widget.prototype.selected = function(self) {
    var self = this.ptr;
    return !!(_mud_Widget_selected_0(self));
};
Widget.prototype["set_state"] = Widget.prototype.set_state = function(self, state, enabled) {
    var self = this.ptr;
    /* state <WidgetState> [] */
    if (state && typeof state === "object") state = state.ptr;
    /* enabled <bool> [] */
    _mud_Widget_set_state_2(self, state, enabled);
};
Widget.prototype["take_focus"] = Widget.prototype.take_focus = function(self) {
    var self = this.ptr;
    _mud_Widget_take_focus_0(self);
};
Widget.prototype["take_modal"] = Widget.prototype.take_modal = function(self, device_filter) {
    var self = this.ptr;
    /* device_filter <uint32_t> [] */
    _mud_Widget_take_modal_1(self, device_filter);
};
Widget.prototype["toggle_state"] = Widget.prototype.toggle_state = function(self, state) {
    var self = this.ptr;
    /* state <WidgetState> [] */
    if (state && typeof state === "object") state = state.ptr;
    _mud_Widget_toggle_state_1(self, state);
};
Widget.prototype["ui"] = Widget.prototype.ui = function(self) {
    var self = this.ptr;
    return wrapPointer(_mud_Widget_ui_0(self), Ui);
};
Widget.prototype["ui_window"] = Widget.prototype.ui_window = function(self) {
    var self = this.ptr;
    return wrapPointer(_mud_Widget_ui_window_0(self), UiWindow);
};
Widget.prototype["yield_focus"] = Widget.prototype.yield_focus = function(self) {
    var self = this.ptr;
    _mud_Widget_yield_focus_0(self);
};
Widget.prototype["yield_modal"] = Widget.prototype.yield_modal = function(self) {
    var self = this.ptr;
    _mud_Widget_yield_modal_0(self);
};
Object.defineProperty(Widget.prototype, "frame", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Widget__get_frame(self), Frame);
    }});
Object.defineProperty(Widget.prototype, "state", {
    get: function() {
        var self = this.ptr;
        return _mud_Widget__get_state(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <WidgetState> [] */
        if (value && typeof value === "object") value = value.ptr;
        _mud_Widget__set_state(self, value);
    }
});
Object.defineProperty(Widget.prototype, "switch", {
    get: function() {
        var self = this.ptr;
        return _mud_Widget__get_switch(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uint32_t> [] */
        _mud_Widget__set_switch(self, value);
    }
});
Object.defineProperty(Widget.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Widget__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <size_t> [] */
        _mud_Widget__set_index(self, value);
    }
});
Object.defineProperty(Widget.prototype, "open", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Widget__get_open(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <bool> [] */
        _mud_Widget__set_open(self, value);
    }
});
Object.defineProperty(Widget.prototype, "body", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Widget__get_body(self), Widget);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Widget> [] */
        value = value.ptr;
        _mud_Widget__set_body(self, value);
    }
});
Widget.prototype["__destroy__"] = Widget.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Widget__destroy(self);
};
// Canvas
function Canvas() { throw "cannot construct a Canvas, no constructor in IDL" }
Canvas.prototype = Object.create(WrapperObject.prototype);
Canvas.prototype.constructor = Canvas;
Canvas.prototype.__class__ = Canvas;
Canvas.__cache__ = {};
Canvas.__type__ = _mud_Canvas__type();
Module['Canvas'] = Canvas;
Canvas.prototype["__destroy__"] = Canvas.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Canvas__destroy(self);
};
// Dockable
function Dockable() { throw "cannot construct a Dockable, no constructor in IDL" }
Dockable.prototype = Object.create(WrapperObject.prototype);
Dockable.prototype.constructor = Dockable;
Dockable.prototype.__class__ = Dockable;
Dockable.__cache__ = {};
Dockable.__type__ = _mud_Dockable__type();
Module['Dockable'] = Dockable;
Dockable.prototype["__destroy__"] = Dockable.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Dockable__destroy(self);
};
// Docker
function Docker() { throw "cannot construct a Docker, no constructor in IDL" }
Docker.prototype = Object.create(WrapperObject.prototype);
Docker.prototype.constructor = Docker;
Docker.prototype.__class__ = Docker;
Docker.__cache__ = {};
Docker.__type__ = _mud_Docker__type();
Module['Docker'] = Docker;
Docker.prototype["__destroy__"] = Docker.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Docker__destroy(self);
};
// Dockbar
function Dockbar() { throw "cannot construct a Dockbar, no constructor in IDL" }
Dockbar.prototype = Object.create(WrapperObject.prototype);
Dockbar.prototype.constructor = Dockbar;
Dockbar.prototype.__class__ = Dockbar;
Dockbar.__cache__ = {};
Dockbar.__type__ = _mud_Dockbar__type();
Module['Dockbar'] = Dockbar;
Dockbar.prototype["__destroy__"] = Dockbar.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Dockbar__destroy(self);
};
// Dockspace
function Dockspace() { throw "cannot construct a Dockspace, no constructor in IDL" }
Dockspace.prototype = Object.create(WrapperObject.prototype);
Dockspace.prototype.constructor = Dockspace;
Dockspace.prototype.__class__ = Dockspace;
Dockspace.__cache__ = {};
Dockspace.__type__ = _mud_Dockspace__type();
Module['Dockspace'] = Dockspace;
Dockspace.prototype["__destroy__"] = Dockspace.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Dockspace__destroy(self);
};
// Expandbox
function Expandbox() { throw "cannot construct a Expandbox, no constructor in IDL" }
Expandbox.prototype = Object.create(WrapperObject.prototype);
Expandbox.prototype.constructor = Expandbox;
Expandbox.prototype.__class__ = Expandbox;
Expandbox.__cache__ = {};
Expandbox.__type__ = _mud_Expandbox__type();
Module['Expandbox'] = Expandbox;
Expandbox.prototype["__destroy__"] = Expandbox.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Expandbox__destroy(self);
};
// Node
function Node() { throw "cannot construct a Node, no constructor in IDL" }
Node.prototype = Object.create(WrapperObject.prototype);
Node.prototype.constructor = Node;
Node.prototype.__class__ = Node;
Node.__cache__ = {};
Node.__type__ = _mud_Node__type();
Module['Node'] = Node;
Node.prototype["__destroy__"] = Node.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Node__destroy(self);
};
// NodePlug
function NodePlug() { throw "cannot construct a NodePlug, no constructor in IDL" }
NodePlug.prototype = Object.create(WrapperObject.prototype);
NodePlug.prototype.constructor = NodePlug;
NodePlug.prototype.__class__ = NodePlug;
NodePlug.__cache__ = {};
NodePlug.__type__ = _mud_NodePlug__type();
Module['NodePlug'] = NodePlug;
NodePlug.prototype["__destroy__"] = NodePlug.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_NodePlug__destroy(self);
};
// RowSolver
function RowSolver() { throw "cannot construct a RowSolver, no constructor in IDL" }
RowSolver.prototype = Object.create(WrapperObject.prototype);
RowSolver.prototype.constructor = RowSolver;
RowSolver.prototype.__class__ = RowSolver;
RowSolver.__cache__ = {};
RowSolver.__type__ = _mud_RowSolver__type();
Module['RowSolver'] = RowSolver;
RowSolver.prototype["__destroy__"] = RowSolver.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_RowSolver__destroy(self);
};
// ScrollSheet
function ScrollSheet() { throw "cannot construct a ScrollSheet, no constructor in IDL" }
ScrollSheet.prototype = Object.create(WrapperObject.prototype);
ScrollSheet.prototype.constructor = ScrollSheet;
ScrollSheet.prototype.__class__ = ScrollSheet;
ScrollSheet.__cache__ = {};
ScrollSheet.__type__ = _mud_ScrollSheet__type();
Module['ScrollSheet'] = ScrollSheet;
ScrollSheet.prototype["__destroy__"] = ScrollSheet.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ScrollSheet__destroy(self);
};
// Sequence
function Sequence() { throw "cannot construct a Sequence, no constructor in IDL" }
Sequence.prototype = Object.create(WrapperObject.prototype);
Sequence.prototype.constructor = Sequence;
Sequence.prototype.__class__ = Sequence;
Sequence.__cache__ = {};
Sequence.__type__ = _mud_ui_Sequence__type();
Module['ui']['Sequence'] = Sequence;
Sequence.prototype["__destroy__"] = Sequence.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ui_Sequence__destroy(self);
};
// Tabber
function Tabber() { throw "cannot construct a Tabber, no constructor in IDL" }
Tabber.prototype = Object.create(WrapperObject.prototype);
Tabber.prototype.constructor = Tabber;
Tabber.prototype.__class__ = Tabber;
Tabber.__cache__ = {};
Tabber.__type__ = _mud_Tabber__type();
Module['Tabber'] = Tabber;
Tabber.prototype["__destroy__"] = Tabber.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Tabber__destroy(self);
};
// Table
function Table() { throw "cannot construct a Table, no constructor in IDL" }
Table.prototype = Object.create(WrapperObject.prototype);
Table.prototype.constructor = Table;
Table.prototype.__class__ = Table;
Table.__cache__ = {};
Table.__type__ = _mud_Table__type();
Module['Table'] = Table;
Table.prototype["__destroy__"] = Table.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Table__destroy(self);
};
// TextEdit
function TextEdit() { throw "cannot construct a TextEdit, no constructor in IDL" }
TextEdit.prototype = Object.create(WrapperObject.prototype);
TextEdit.prototype.constructor = TextEdit;
TextEdit.prototype.__class__ = TextEdit;
TextEdit.__cache__ = {};
TextEdit.__type__ = _mud_TextEdit__type();
Module['TextEdit'] = TextEdit;
TextEdit.prototype["__destroy__"] = TextEdit.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TextEdit__destroy(self);
};
// TreeNode
function TreeNode() { throw "cannot construct a TreeNode, no constructor in IDL" }
TreeNode.prototype = Object.create(WrapperObject.prototype);
TreeNode.prototype.constructor = TreeNode;
TreeNode.prototype.__class__ = TreeNode;
TreeNode.__cache__ = {};
TreeNode.__type__ = _mud_TreeNode__type();
Module['TreeNode'] = TreeNode;
TreeNode.prototype["__destroy__"] = TreeNode.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TreeNode__destroy(self);
};
// Ui
function Ui() { throw "cannot construct a Ui, no constructor in IDL" }
Ui.prototype = Object.create(WrapperObject.prototype);
Ui.prototype.constructor = Ui;
Ui.prototype.__class__ = Ui;
Ui.__cache__ = {};
Ui.__type__ = _mud_Ui__type();
Module['Ui'] = Ui;
Ui.prototype["begin"] = Ui.prototype.begin = function(self) {
    var self = this.ptr;
    return wrapPointer(_mud_Ui_begin_0(self), Widget);
};
Ui.prototype["__destroy__"] = Ui.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ui__destroy(self);
};
// Window
function Window() { throw "cannot construct a Window, no constructor in IDL" }
Window.prototype = Object.create(WrapperObject.prototype);
Window.prototype.constructor = Window;
Window.prototype.__class__ = Window;
Window.__cache__ = {};
Window.__type__ = _mud_Window__type();
Module['Window'] = Window;
Window.prototype["__destroy__"] = Window.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Window__destroy(self);
};
Module['ui']['auto_modal'] = function(parent, mode, size) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* mode <uint32_t> [] */
    /* size <vec2> [] */
    size = size.ptr;
    if (size === undefined) { return wrapPointer(_mud_ui_auto_modal_2(parent, mode), Widget); }
    return wrapPointer(_mud_ui_auto_modal_3(parent, mode, size), Widget);
};
Module['ui']['board'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_board_1(parent), Widget);
};
Module['ui']['button'] = function(parent, content) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* content <const char*> [] */
    if (content && typeof content === "object") content = content.ptr;
    else content = ensureString(content);
    if (content === undefined) { return wrapPointer(_mud_ui_button_1(parent), Widget); }
    return wrapPointer(_mud_ui_button_2(parent, content), Widget);
};
Module['ui']['canvas'] = function(parent, num_nodes) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* num_nodes <size_t> [] */
    if (num_nodes === undefined) { return wrapPointer(_mud_ui_canvas_1(parent), Canvas); }
    return wrapPointer(_mud_ui_canvas_2(parent, num_nodes), Canvas);
};
Module['ui']['checkbox'] = function(parent, on) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* on <bool> [] */
    return wrapPointer(_mud_ui_checkbox_2(parent, on), Widget);
};
Module['ui']['color_display'] = function(parent, value) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* value <Colour> [] */
    value = value.ptr;
    return wrapPointer(_mud_ui_color_display_2(parent, value), Widget);
};
Module['ui']['color_display_field'] = function(parent, name, value, reverse) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    /* value <Colour> [] */
    value = value.ptr;
    /* reverse <bool> [] */
    if (reverse === undefined) { _mud_ui_color_display_field_3(parent, name, value); return; }
    _mud_ui_color_display_field_4(parent, name, value, reverse);
};
Module['ui']['color_edit'] = function(parent, value) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* value <Colour> [] */
    value = value.ptr;
    return !!(_mud_ui_color_edit_2(parent, value));
};
Module['ui']['color_edit_hsl'] = function(parent, colour, value) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* colour <Colour> [] */
    colour = colour.ptr;
    /* value <Colour> [] */
    value = value.ptr;
    return !!(_mud_ui_color_edit_hsl_3(parent, colour, value));
};
Module['ui']['color_edit_simple'] = function(parent, value) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* value <Colour> [] */
    value = value.ptr;
    return !!(_mud_ui_color_edit_simple_2(parent, value));
};
Module['ui']['color_field'] = function(parent, name, value, reverse) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    /* value <Colour> [] */
    value = value.ptr;
    /* reverse <bool> [] */
    if (reverse === undefined) { return !!(_mud_ui_color_field_3(parent, name, value)); }
    return !!(_mud_ui_color_field_4(parent, name, value, reverse));
};
Module['ui']['color_toggle_edit'] = function(parent, value) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* value <Colour> [] */
    value = value.ptr;
    return !!(_mud_ui_color_toggle_edit_2(parent, value));
};
Module['ui']['context'] = function(parent, mode, flags) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* mode <uint32_t> [] */
    /* flags <PopupFlags> [] */
    if (flags && typeof flags === "object") flags = flags.ptr;
    if (flags === undefined) { return wrapPointer(_mud_ui_context_2(parent, mode), Widget); }
    return wrapPointer(_mud_ui_context_3(parent, mode, flags), Widget);
};
Module['ui']['cursor'] = function(parent, position, hovered, locked) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* position <vec2> [] */
    position = position.ptr;
    /* hovered <Widget> [] */
    hovered = hovered.ptr;
    /* locked <bool> [] */
    if (locked === undefined) { return wrapPointer(_mud_ui_cursor_3(parent, position, hovered), Widget); }
    return wrapPointer(_mud_ui_cursor_4(parent, position, hovered, locked), Widget);
};
Module['ui']['decal'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_decal_1(parent), Widget);
};
Module['ui']['dir_item'] = function(parent, name) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    return wrapPointer(_mud_ui_dir_item_2(parent, name), Widget);
};
Module['ui']['dir_node'] = function(parent, path, name, collapsed) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* path <const char*> [] */
    if (path && typeof path === "object") path = path.ptr;
    else path = ensureString(path);
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    /* collapsed <bool> [] */
    return wrapPointer(_mud_ui_dir_node_4(parent, path, name, collapsed), Widget);
};
Module['ui']['div'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_div_1(parent), Widget);
};
Module['ui']['dockbar'] = function(parent, docksystem) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* docksystem <Docksystem> [] */
    docksystem = docksystem.ptr;
    return wrapPointer(_mud_ui_dockbar_2(parent, docksystem), Dockbar);
};
Module['ui']['dockitem'] = function(parent, docksystem, dock) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* docksystem <Docksystem> [] */
    docksystem = docksystem.ptr;
    /* dock <Dock> [] */
    dock = dock.ptr;
    return wrapPointer(_mud_ui_dockitem_3(parent, docksystem, dock), Widget);
};
Module['ui']['dockspace'] = function(parent, docksystem) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* docksystem <Docksystem> [] */
    docksystem = docksystem.ptr;
    return wrapPointer(_mud_ui_dockspace_2(parent, docksystem), Dockspace);
};
Module['ui']['drag_float'] = function(parent, value, step) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* value <float> [] */
    /* step <float> [] */
    if (step === undefined) { return !!(_mud_ui_drag_float_2(parent, value)); }
    return !!(_mud_ui_drag_float_3(parent, value, step));
};
Module['ui']['dropdown'] = function(parent, style, value, flags, list_style) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* style <Style> [] */
    style = style.ptr;
    /* value <const char*> [] */
    if (value && typeof value === "object") value = value.ptr;
    else value = ensureString(value);
    /* flags <PopupFlags> [] */
    if (flags && typeof flags === "object") flags = flags.ptr;
    /* list_style <Style> [] */
    if(typeof list_style !== "undefined" && list_style !== null) { list_style = list_style.ptr; }
    if (list_style === undefined) { return wrapPointer(_mud_ui_dropdown_4(parent, style, value, flags), Widget); }
    return wrapPointer(_mud_ui_dropdown_5(parent, style, value, flags, list_style), Widget);
};
Module['ui']['dummy'] = function(parent, size) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* size <vec2> [] */
    size = size.ptr;
    return wrapPointer(_mud_ui_dummy_2(parent, size), Widget);
};
Module['ui']['element'] = function(parent, object) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* object <Ref> [] */
    var object_type;
    if(typeof object !== "undefined" && object !== null) { object = object.ptr; object_type = object.type.__type__; }
    else { object = 0; object_type = 0; }
    return wrapPointer(_mud_ui_element_2(parent, object, object_type), Widget);
};
Module['ui']['expandbox'] = function(parent, name, open) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    /* open <bool> [] */
    if (open === undefined) { return wrapPointer(_mud_ui_expandbox_2(parent, name), Expandbox); }
    return wrapPointer(_mud_ui_expandbox_3(parent, name, open), Expandbox);
};
Module['ui']['file_item'] = function(parent, name) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    return wrapPointer(_mud_ui_file_item_2(parent, name), Widget);
};
Module['ui']['file_node'] = function(parent, name) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    return wrapPointer(_mud_ui_file_node_2(parent, name), Widget);
};
Module['ui']['file_tree'] = function(parent, path) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* path <const char*> [] */
    if (path && typeof path === "object") path = path.ptr;
    else path = ensureString(path);
    return wrapPointer(_mud_ui_file_tree_2(parent, path), Widget);
};
Module['ui']['fill_bar'] = function(parent, percentage, dim) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* percentage <float> [] */
    /* dim <Dim> [] */
    if (dim && typeof dim === "object") dim = dim.ptr;
    if (dim === undefined) { return wrapPointer(_mud_ui_fill_bar_2(parent, percentage), Widget); }
    return wrapPointer(_mud_ui_fill_bar_3(parent, percentage, dim), Widget);
};
Module['ui']['flag_field'] = function(parent, name, value, shift, reverse) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    /* value <uint32_t> [] */
    /* shift <uint8_t> [] */
    /* reverse <bool> [] */
    if (reverse === undefined) { return !!(_mud_ui_flag_field_4(parent, name, value, shift)); }
    return !!(_mud_ui_flag_field_5(parent, name, value, shift, reverse));
};
Module['ui']['header'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_header_1(parent), Widget);
};
Module['ui']['hoverbox'] = function(parent, delay) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* delay <float> [] */
    if (delay === undefined) { return wrapPointer(_mud_ui_hoverbox_1(parent), Widget); }
    return wrapPointer(_mud_ui_hoverbox_2(parent, delay), Widget);
};
Module['ui']['icon'] = function(parent, icon) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* icon <const char*> [] */
    if (icon && typeof icon === "object") icon = icon.ptr;
    else icon = ensureString(icon);
    return wrapPointer(_mud_ui_icon_2(parent, icon), Widget);
};
Module['ui']['image256'] = function(parent, name, source, size) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    /* source <Image256> [] */
    source = source.ptr;
    /* size <vec2> [] */
    size = size.ptr;
    if (size === undefined) { return wrapPointer(_mud_ui_image256_3(parent, name, source), Widget); }
    return wrapPointer(_mud_ui_image256_4(parent, name, source, size), Widget);
};
Module['ui']['item'] = function(parent, style, content) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* style <Style> [] */
    style = style.ptr;
    /* content <const char*> [] */
    if (content && typeof content === "object") content = content.ptr;
    else content = ensureString(content);
    if (content === undefined) { return wrapPointer(_mud_ui_item_2(parent, style), Widget); }
    return wrapPointer(_mud_ui_item_3(parent, style, content), Widget);
};
Module['ui']['label'] = function(parent, label) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* label <const char*> [] */
    if (label && typeof label === "object") label = label.ptr;
    else label = ensureString(label);
    return wrapPointer(_mud_ui_label_2(parent, label), Widget);
};
Module['ui']['layout'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_layout_1(parent), Widget);
};
Module['ui']['menu'] = function(parent, label, submenu) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* label <const char*> [] */
    if (label && typeof label === "object") label = label.ptr;
    else label = ensureString(label);
    /* submenu <bool> [] */
    if (submenu === undefined) { return wrapPointer(_mud_ui_menu_2(parent, label), Widget); }
    return wrapPointer(_mud_ui_menu_3(parent, label, submenu), Widget);
};
Module['ui']['menu_choice'] = function(parent, content) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* content <const char*> [] */
    if (content && typeof content === "object") content = content.ptr;
    else content = ensureString(content);
    return wrapPointer(_mud_ui_menu_choice_2(parent, content), Widget);
};
Module['ui']['menubar'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_menubar_1(parent), Widget);
};
Module['ui']['message'] = function(parent, label) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* label <const char*> [] */
    if (label && typeof label === "object") label = label.ptr;
    else label = ensureString(label);
    return wrapPointer(_mud_ui_message_2(parent, label), Widget);
};
Module['ui']['modal'] = function(parent, size) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* size <vec2> [] */
    size = size.ptr;
    if (size === undefined) { return wrapPointer(_mud_ui_modal_1(parent), Widget); }
    return wrapPointer(_mud_ui_modal_2(parent, size), Widget);
};
Module['ui']['modal_button'] = function(screen, parent, content, mode) {
    var self = this.ptr;
    ensureCache.prepare();
    /* screen <Widget> [] */
    screen = screen.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* content <const char*> [] */
    if (content && typeof content === "object") content = content.ptr;
    else content = ensureString(content);
    /* mode <uint32_t> [] */
    return !!(_mud_ui_modal_button_4(screen, parent, content, mode));
};
Module['ui']['node'] = function(parent, title, position, order, identity) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Canvas> [] */
    parent = parent.ptr;
    /* title <const char*> [] */
    if (title && typeof title === "object") title = title.ptr;
    else title = ensureString(title);
    /* position <vec2> [] */
    position = position.ptr;
    /* order <int> [] */
    /* identity <Ref> [] */
    var identity_type;
    if(typeof identity !== "undefined" && identity !== null) { identity = identity.ptr; identity_type = identity.type.__type__; }
    else { identity = 0; identity_type = 0; }
    if (order === undefined) { return wrapPointer(_mud_ui_node_3(parent, title, position), Node); }
    if (identity === undefined) { return wrapPointer(_mud_ui_node_4(parent, title, position, order), Node); }
    return wrapPointer(_mud_ui_node_5(parent, title, position, order, identity, identity_type), Node);
};
Module['ui']['node_cable'] = function(canvas, plug_out, plug_in) {
    var self = this.ptr;
    /* canvas <Canvas> [] */
    canvas = canvas.ptr;
    /* plug_out <NodePlug> [] */
    plug_out = plug_out.ptr;
    /* plug_in <NodePlug> [] */
    plug_in = plug_in.ptr;
    return wrapPointer(_mud_ui_node_cable_3(canvas, plug_out, plug_in), Widget);
};
Module['ui']['node_input'] = function(node, name, icon, colour, active, connected) {
    var self = this.ptr;
    ensureCache.prepare();
    /* node <Node> [] */
    node = node.ptr;
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    /* icon <const char*> [] */
    if (icon && typeof icon === "object") icon = icon.ptr;
    else icon = ensureString(icon);
    /* colour <Colour> [] */
    if(typeof colour !== "undefined" && colour !== null) { colour = colour.ptr; }
    /* active <bool> [] */
    /* connected <bool> [] */
    if (icon === undefined) { return wrapPointer(_mud_ui_node_input_2(node, name), NodePlug); }
    if (colour === undefined) { return wrapPointer(_mud_ui_node_input_3(node, name, icon), NodePlug); }
    if (active === undefined) { return wrapPointer(_mud_ui_node_input_4(node, name, icon, colour), NodePlug); }
    if (connected === undefined) { return wrapPointer(_mud_ui_node_input_5(node, name, icon, colour, active), NodePlug); }
    return wrapPointer(_mud_ui_node_input_6(node, name, icon, colour, active, connected), NodePlug);
};
Module['ui']['node_output'] = function(node, name, icon, colour, active, connected) {
    var self = this.ptr;
    ensureCache.prepare();
    /* node <Node> [] */
    node = node.ptr;
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    /* icon <const char*> [] */
    if (icon && typeof icon === "object") icon = icon.ptr;
    else icon = ensureString(icon);
    /* colour <Colour> [] */
    if(typeof colour !== "undefined" && colour !== null) { colour = colour.ptr; }
    /* active <bool> [] */
    /* connected <bool> [] */
    if (icon === undefined) { return wrapPointer(_mud_ui_node_output_2(node, name), NodePlug); }
    if (colour === undefined) { return wrapPointer(_mud_ui_node_output_3(node, name, icon), NodePlug); }
    if (active === undefined) { return wrapPointer(_mud_ui_node_output_4(node, name, icon, colour), NodePlug); }
    if (connected === undefined) { return wrapPointer(_mud_ui_node_output_5(node, name, icon, colour, active), NodePlug); }
    return wrapPointer(_mud_ui_node_output_6(node, name, icon, colour, active, connected), NodePlug);
};
Module['ui']['overlay'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_overlay_1(parent), Widget);
};
Module['ui']['popup'] = function(parent, flags) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* flags <PopupFlags> [] */
    if (flags && typeof flags === "object") flags = flags.ptr;
    return wrapPointer(_mud_ui_popup_2(parent, flags), Widget);
};
Module['ui']['popup_at'] = function(parent, position, flags) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* position <vec2> [] */
    position = position.ptr;
    /* flags <PopupFlags> [] */
    if (flags && typeof flags === "object") flags = flags.ptr;
    if (flags === undefined) { return wrapPointer(_mud_ui_popup_at_2(parent, position), Widget); }
    return wrapPointer(_mud_ui_popup_at_3(parent, position, flags), Widget);
};
Module['ui']['quat_edit'] = function(parent, quat) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* quat <quat> [] */
    quat = quat.ptr;
    return !!(_mud_ui_quat_edit_2(parent, quat));
};
Module['ui']['radio_choice'] = function(parent, value, active) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* value <const char*> [] */
    if (value && typeof value === "object") value = value.ptr;
    else value = ensureString(value);
    /* active <bool> [] */
    return wrapPointer(_mud_ui_radio_choice_3(parent, value, active), Widget);
};
Module['ui']['rectangle'] = function(parent, rect) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* rect <vec4> [] */
    rect = rect.ptr;
    return wrapPointer(_mud_ui_rectangle_2(parent, rect), Widget);
};
Module['ui']['row'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_row_1(parent), Widget);
};
Module['ui']['screen'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_screen_1(parent), Widget);
};
Module['ui']['scroll_sequence'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_scroll_sequence_1(parent), Sequence);
};
Module['ui']['scrollable'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_scrollable_1(parent), Widget);
};
Module['ui']['select_list'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_select_list_1(parent), ScrollSheet);
};
Module['ui']['select_logic'] = function(element, object, selection) {
    var self = this.ptr;
    /* element <Widget> [] */
    element = element.ptr;
    /* object <Ref> [] */
    var object_type;
    if(typeof object !== "undefined" && object !== null) { object = object.ptr; object_type = object.type.__type__; }
    else { object = 0; object_type = 0; }
    /* selection <Ref> [] */
    var selection_type;
    if(typeof selection !== "undefined" && selection !== null) { selection = selection.ptr; selection_type = selection.type.__type__; }
    else { selection = 0; selection_type = 0; }
    return !!(_mud_ui_select_logic_3(element, object, object_type, selection, selection_type));
};
Module['ui']['sequence'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_sequence_1(parent), Sequence);
};
Module['ui']['sequence_element'] = function(parent, object) {
    var self = this.ptr;
    /* parent <Sequence> [] */
    parent = parent.ptr;
    /* object <Ref> [] */
    var object_type;
    if(typeof object !== "undefined" && object !== null) { object = object.ptr; object_type = object.type.__type__; }
    else { object = 0; object_type = 0; }
    return wrapPointer(_mud_ui_sequence_element_2(parent, object, object_type), Widget);
};
Module['ui']['sheet'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_sheet_1(parent), Widget);
};
Module['ui']['spacer'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_spacer_1(parent), Widget);
};
Module['ui']['spanner'] = function(parent, style, dim, span) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* style <Style> [] */
    style = style.ptr;
    /* dim <Dim> [] */
    if (dim && typeof dim === "object") dim = dim.ptr;
    /* span <float> [] */
    return wrapPointer(_mud_ui_spanner_4(parent, style, dim, span), Widget);
};
Module['ui']['stack'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_stack_1(parent), Widget);
};
Module['ui']['tab'] = function(tabber, name) {
    var self = this.ptr;
    ensureCache.prepare();
    /* tabber <Tabber> [] */
    tabber = tabber.ptr;
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    return wrapPointer(_mud_ui_tab_2(tabber, name), Widget);
};
Module['ui']['tabber'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_tabber_1(parent), Tabber);
};
Module['ui']['table_row'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_table_row_1(parent), Widget);
};
Module['ui']['table_separator'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_table_separator_1(parent), Widget);
};
Module['ui']['text'] = function(parent, label) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* label <const char*> [] */
    if (label && typeof label === "object") label = label.ptr;
    else label = ensureString(label);
    return wrapPointer(_mud_ui_text_2(parent, label), Widget);
};
Module['ui']['title'] = function(parent, label) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* label <const char*> [] */
    if (label && typeof label === "object") label = label.ptr;
    else label = ensureString(label);
    return wrapPointer(_mud_ui_title_2(parent, label), Widget);
};
Module['ui']['title_header'] = function(parent, title) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* title <const char*> [] */
    if (title && typeof title === "object") title = title.ptr;
    else title = ensureString(title);
    return wrapPointer(_mud_ui_title_header_2(parent, title), Widget);
};
Module['ui']['toggle'] = function(parent, on, content) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* on <bool> [] */
    /* content <const char*> [] */
    if (content && typeof content === "object") content = content.ptr;
    else content = ensureString(content);
    if (content === undefined) { return wrapPointer(_mud_ui_toggle_2(parent, on), Widget); }
    return wrapPointer(_mud_ui_toggle_3(parent, on, content), Widget);
};
Module['ui']['toolbar'] = function(parent, wrap) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* wrap <bool> [] */
    if (wrap === undefined) { return wrapPointer(_mud_ui_toolbar_1(parent), Widget); }
    return wrapPointer(_mud_ui_toolbar_2(parent, wrap), Widget);
};
Module['ui']['toolbutton'] = function(parent, icon) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* icon <const char*> [] */
    if (icon && typeof icon === "object") icon = icon.ptr;
    else icon = ensureString(icon);
    return wrapPointer(_mud_ui_toolbutton_2(parent, icon), Widget);
};
Module['ui']['tooldock'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_tooldock_1(parent), Widget);
};
Module['ui']['tooltip'] = function(parent, position, content) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* position <vec2> [] */
    position = position.ptr;
    /* content <const char*> [] */
    if (content && typeof content === "object") content = content.ptr;
    else content = ensureString(content);
    return wrapPointer(_mud_ui_tooltip_3(parent, position, content), Widget);
};
Module['ui']['tree'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_tree_1(parent), Widget);
};
Module['ui']['tree_node'] = function(parent, name, leaf, open) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    /* leaf <bool> [] */
    /* open <bool> [] */
    if (leaf === undefined) { return wrapPointer(_mud_ui_tree_node_2(parent, name), TreeNode); }
    if (open === undefined) { return wrapPointer(_mud_ui_tree_node_3(parent, name, leaf), TreeNode); }
    return wrapPointer(_mud_ui_tree_node_4(parent, name, leaf, open), TreeNode);
};
Module['ui']['vec2_edit'] = function(parent, vec) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* vec <vec2> [] */
    vec = vec.ptr;
    return !!(_mud_ui_vec2_edit_2(parent, vec));
};
Module['ui']['vec3_edit'] = function(parent, vec) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* vec <vec3> [] */
    vec = vec.ptr;
    return !!(_mud_ui_vec3_edit_2(parent, vec));
};
Module['ui']['widget'] = function(parent, style, open, length, index) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* style <Style> [] */
    style = style.ptr;
    /* open <bool> [] */
    /* length <Dim> [] */
    if (length && typeof length === "object") length = length.ptr;
    /* index <Dim2<size_t>> [] */
    if(typeof index !== "undefined" && index !== null) { index = index.ptr; }
    if (open === undefined) { return wrapPointer(_mud_ui_widget_2(parent, style), Widget); }
    if (length === undefined) { return wrapPointer(_mud_ui_widget_3(parent, style, open), Widget); }
    if (index === undefined) { return wrapPointer(_mud_ui_widget_4(parent, style, open, length), Widget); }
    return wrapPointer(_mud_ui_widget_5(parent, style, open, length, index), Widget);
};
Module['ui']['window'] = function(parent, title, state) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* title <const char*> [] */
    if (title && typeof title === "object") title = title.ptr;
    else title = ensureString(title);
    /* state <WindowState> [] */
    if (state && typeof state === "object") state = state.ptr;
    if (state === undefined) { return wrapPointer(_mud_ui_window_2(parent, title), Window); }
    return wrapPointer(_mud_ui_window_3(parent, title, state), Window);
};

(function() {
    function setupEnums() {
        // Align
        Module['Left'] = _mud_Align_Left();
        Module['CENTER'] = _mud_Align_CENTER();
        Module['Right'] = _mud_Align_Right();
        Module['OUT_LEFT'] = _mud_Align_OUT_LEFT();
        Module['OUT_RIGHT'] = _mud_Align_OUT_RIGHT();
        // AutoLayout
        Module['NO_LAYOUT'] = _mud_AutoLayout_NO_LAYOUT();
        Module['AUTO_SIZE'] = _mud_AutoLayout_AUTO_SIZE();
        Module['AUTO_LAYOUT'] = _mud_AutoLayout_AUTO_LAYOUT();
        // Clipping
        Module['NOCLIP'] = _mud_Clipping_NOCLIP();
        Module['CLIP'] = _mud_Clipping_CLIP();
        Module['UNCLIP'] = _mud_Clipping_UNCLIP();
        // Dim
        Module['DIM_X'] = _mud_Dim_DIM_X();
        Module['DIM_Y'] = _mud_Dim_DIM_Y();
        Module['DIM_NONE'] = _mud_Dim_DIM_NONE();
        // Flow
        Module['FLOW'] = _mud_Flow_FLOW();
        Module['OVERLAY'] = _mud_Flow_OVERLAY();
        Module['ALIGN'] = _mud_Flow_ALIGN();
        Module['FREE'] = _mud_Flow_FREE();
        // FlowAxis
        Module['READING'] = _mud_FlowAxis_READING();
        Module['PARAGRAPH'] = _mud_FlowAxis_PARAGRAPH();
        Module['PARALLEL'] = _mud_FlowAxis_PARALLEL();
        Module['ORTHOGONAL'] = _mud_FlowAxis_ORTHOGONAL();
        Module['AXIS_NONE'] = _mud_FlowAxis_AXIS_NONE();
        // LayoutSolver
        Module['FRAME_SOLVER'] = _mud_LayoutSolver_FRAME_SOLVER();
        Module['ROW_SOLVER'] = _mud_LayoutSolver_ROW_SOLVER();
        Module['GRID_SOLVER'] = _mud_LayoutSolver_GRID_SOLVER();
        Module['TABLE_SOLVER'] = _mud_LayoutSolver_TABLE_SOLVER();
        // Opacity
        Module['OPAQUE'] = _mud_Opacity_OPAQUE();
        Module['CLEAR'] = _mud_Opacity_CLEAR();
        Module['HOLLOW'] = _mud_Opacity_HOLLOW();
        // Pivot
        Module['FORWARD'] = _mud_Pivot_FORWARD();
        Module['REVERSE'] = _mud_Pivot_REVERSE();
        // PopupFlags
        Module['ui']['PopupFlags'] = Module['ui']['PopupFlags'] || {};
        Module['ui']['PopupFlags']['None'] = _mud_ui_PopupFlags_None();
        Module['ui']['PopupFlags']['Modal'] = _mud_ui_PopupFlags_Modal();
        Module['ui']['PopupFlags']['Clamp'] = _mud_ui_PopupFlags_Clamp();
        Module['ui']['PopupFlags']['AutoClose'] = _mud_ui_PopupFlags_AutoClose();
        Module['ui']['PopupFlags']['AutoModal'] = _mud_ui_PopupFlags_AutoModal();
        // Sizing
        Module['FIXED'] = _mud_Sizing_FIXED();
        Module['SHRINK'] = _mud_Sizing_SHRINK();
        Module['WRAP'] = _mud_Sizing_WRAP();
        Module['EXPAND'] = _mud_Sizing_EXPAND();
        // SpacePreset
        Module['SHEET'] = _mud_SpacePreset_SHEET();
        Module['FLEX'] = _mud_SpacePreset_FLEX();
        Module['ITEM'] = _mud_SpacePreset_ITEM();
        Module['UNIT'] = _mud_SpacePreset_UNIT();
        Module['BLOCK'] = _mud_SpacePreset_BLOCK();
        Module['LINE'] = _mud_SpacePreset_LINE();
        Module['STACK'] = _mud_SpacePreset_STACK();
        Module['DIV'] = _mud_SpacePreset_DIV();
        Module['SPACER'] = _mud_SpacePreset_SPACER();
        Module['BOARD'] = _mud_SpacePreset_BOARD();
        Module['LAYOUT'] = _mud_SpacePreset_LAYOUT();
        // WidgetState
        Module['NOSTATE'] = _mud_WidgetState_NOSTATE();
        Module['CREATED'] = _mud_WidgetState_CREATED();
        Module['HOVERED'] = _mud_WidgetState_HOVERED();
        Module['PRESSED'] = _mud_WidgetState_PRESSED();
        Module['ACTIVATED'] = _mud_WidgetState_ACTIVATED();
        Module['ACTIVE'] = _mud_WidgetState_ACTIVE();
        Module['SELECTED'] = _mud_WidgetState_SELECTED();
        Module['DISABLED'] = _mud_WidgetState_DISABLED();
        Module['DRAGGED'] = _mud_WidgetState_DRAGGED();
        Module['FOCUSED'] = _mud_WidgetState_FOCUSED();
        Module['CLOSED'] = _mud_WidgetState_CLOSED();
        // WindowState
        Module['WINDOW_NOSTATE'] = _mud_WindowState_WINDOW_NOSTATE();
        Module['WINDOW_HEADER'] = _mud_WindowState_WINDOW_HEADER();
        Module['WINDOW_DOCKABLE'] = _mud_WindowState_WINDOW_DOCKABLE();
        Module['WINDOW_CLOSABLE'] = _mud_WindowState_WINDOW_CLOSABLE();
        Module['WINDOW_MOVABLE'] = _mud_WindowState_WINDOW_MOVABLE();
        Module['WINDOW_SIZABLE'] = _mud_WindowState_WINDOW_SIZABLE();
        Module['WINDOW_DEFAULT'] = _mud_WindowState_WINDOW_DEFAULT();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
