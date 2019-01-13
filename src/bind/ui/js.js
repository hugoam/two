
// Bindings utilities
function WrapperObject() {
}
// CanvasConnect
function CanvasConnect() {
    this.ptr = _mud_CanvasConnect_CanvasConnect_0(); getCache(CanvasConnect)[this.ptr] = this;
};
CanvasConnect.prototype = Object.create(WrapperObject.prototype);
CanvasConnect.prototype.constructor = CanvasConnect;
CanvasConnect.prototype.__class__ = CanvasConnect;
CanvasConnect.__cache__ = {};
Module['CanvasConnect'] = CanvasConnect;
CanvasConnect.prototype["__destroy__"] = CanvasConnect.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_CanvasConnect__destroy(self);
};
// Clipboard
function Clipboard() {
    this.ptr = _mud_Clipboard_Clipboard_0(); getCache(Clipboard)[this.ptr] = this;
};
Clipboard.prototype = Object.create(WrapperObject.prototype);
Clipboard.prototype.constructor = Clipboard;
Clipboard.prototype.__class__ = Clipboard;
Clipboard.__cache__ = {};
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
};
Dock.prototype = Object.create(WrapperObject.prototype);
Dock.prototype.constructor = Dock;
Dock.prototype.__class__ = Dock;
Dock.__cache__ = {};
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
Module['Docksystem'] = Docksystem;
Docksystem.prototype["__destroy__"] = Docksystem.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Docksystem__destroy(self);
};
// Gradient
function Gradient() {
    this.ptr = _mud_Gradient_Gradient_0(); getCache(Gradient)[this.ptr] = this;
};
Gradient.prototype = Object.create(WrapperObject.prototype);
Gradient.prototype.constructor = Gradient;
Gradient.prototype.__class__ = Gradient;
Gradient.__cache__ = {};
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
};
ImageSkin.prototype = Object.create(WrapperObject.prototype);
ImageSkin.prototype.constructor = ImageSkin;
ImageSkin.prototype.__class__ = ImageSkin;
ImageSkin.__cache__ = {};
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
    /* name <const char*> [] */
    if (name === undefined) { this.ptr = _mud_InkStyle_InkStyle_0(); getCache(InkStyle)[this.ptr] = this; return; }
    this.ptr = _mud_InkStyle_InkStyle_1(name); getCache(InkStyle)[this.ptr] = this;
};
InkStyle.prototype = Object.create(WrapperObject.prototype);
InkStyle.prototype.constructor = InkStyle;
InkStyle.prototype.__class__ = InkStyle;
InkStyle.__cache__ = {};
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
Module['Layer'] = Layer;
Layer.prototype["__destroy__"] = Layer.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Layer__destroy(self);
};
// Layout
function Layout(name) {
    /* name <const char*> [] */
    if (name === undefined) { this.ptr = _mud_Layout_Layout_0(); getCache(Layout)[this.ptr] = this; return; }
    this.ptr = _mud_Layout_Layout_1(name); getCache(Layout)[this.ptr] = this;
};
Layout.prototype = Object.create(WrapperObject.prototype);
Layout.prototype.constructor = Layout;
Layout.prototype.__class__ = Layout;
Layout.__cache__ = {};
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
};
NodeConnection.prototype = Object.create(WrapperObject.prototype);
NodeConnection.prototype.constructor = NodeConnection;
NodeConnection.prototype.__class__ = NodeConnection;
NodeConnection.__cache__ = {};
Module['NodeConnection'] = NodeConnection;
NodeConnection.prototype["__destroy__"] = NodeConnection.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_NodeConnection__destroy(self);
};
// Paint
function Paint() {
    this.ptr = _mud_Paint_Paint_0(); getCache(Paint)[this.ptr] = this;
};
Paint.prototype = Object.create(WrapperObject.prototype);
Paint.prototype.constructor = Paint;
Paint.prototype.__class__ = Paint;
Paint.__cache__ = {};
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
    colour = colour.ptr;
    if (colour === undefined) { this.ptr = _mud_Shadow_Shadow_4(xpos, ypos, blur, spread); getCache(Shadow)[this.ptr] = this; return; }
    this.ptr = _mud_Shadow_Shadow_5(xpos, ypos, blur, spread, colour); getCache(Shadow)[this.ptr] = this;
};
Shadow.prototype = Object.create(WrapperObject.prototype);
Shadow.prototype.constructor = Shadow;
Shadow.prototype.__class__ = Shadow;
Shadow.__cache__ = {};
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
};
Space.prototype = Object.create(WrapperObject.prototype);
Space.prototype.constructor = Space;
Space.prototype.__class__ = Space;
Space.__cache__ = {};
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
        return _mud_Style__get_name(self);
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
Module['Text'] = Text;
Text.prototype["__destroy__"] = Text.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Text__destroy(self);
};
// TextCursor
function TextCursor() {
    this.ptr = _mud_TextCursor_TextCursor_0(); getCache(TextCursor)[this.ptr] = this;
};
TextCursor.prototype = Object.create(WrapperObject.prototype);
TextCursor.prototype.constructor = TextCursor;
TextCursor.prototype.__class__ = TextCursor;
TextCursor.__cache__ = {};
Module['TextCursor'] = TextCursor;
TextCursor.prototype["__destroy__"] = TextCursor.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TextCursor__destroy(self);
};
// TextMarker
function TextMarker() {
    this.ptr = _mud_TextMarker_TextMarker_0(); getCache(TextMarker)[this.ptr] = this;
};
TextMarker.prototype = Object.create(WrapperObject.prototype);
TextMarker.prototype.constructor = TextMarker;
TextMarker.prototype.__class__ = TextMarker;
TextMarker.__cache__ = {};
Module['TextMarker'] = TextMarker;
TextMarker.prototype["__destroy__"] = TextMarker.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TextMarker__destroy(self);
};
// TextPaint
function TextPaint() {
    this.ptr = _mud_TextPaint_TextPaint_0(); getCache(TextPaint)[this.ptr] = this;
};
TextPaint.prototype = Object.create(WrapperObject.prototype);
TextPaint.prototype.constructor = TextPaint;
TextPaint.prototype.__class__ = TextPaint;
TextPaint.__cache__ = {};
Module['TextPaint'] = TextPaint;
Object.defineProperty(TextPaint.prototype, "font", {
    get: function() {
        var self = this.ptr;
        return _mud_TextPaint__get_font(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <const char*> [] */
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
};
TextSelection.prototype = Object.create(WrapperObject.prototype);
TextSelection.prototype.constructor = TextSelection;
TextSelection.prototype.__class__ = TextSelection;
TextSelection.__cache__ = {};
Module['TextSelection'] = TextSelection;
TextSelection.prototype["__destroy__"] = TextSelection.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TextSelection__destroy(self);
};
// UiRect
function UiRect() {
    this.ptr = _mud_UiRect_UiRect_0(); getCache(UiRect)[this.ptr] = this;
};
UiRect.prototype = Object.create(WrapperObject.prototype);
UiRect.prototype.constructor = UiRect;
UiRect.prototype.__class__ = UiRect;
UiRect.__cache__ = {};
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
    if (modifier === undefined) { return wrapPointer(_mud_Widget_char_stroke_1(self, code), KeyEvent); return; }
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
    if (modifier === undefined) { return wrapPointer(_mud_Widget_key_event_2(self, code, event_type), KeyEvent); return; }
    return wrapPointer(_mud_Widget_key_event_3(self, code, event_type, modifier), KeyEvent);
};
Widget.prototype["key_stroke"] = Widget.prototype.key_stroke = function(self, code, modifier) {
    var self = this.ptr;
    /* code <Key> [] */
    if (code && typeof code === "object") code = code.ptr;
    /* modifier <InputMod> [] */
    if (modifier && typeof modifier === "object") modifier = modifier.ptr;
    if (modifier === undefined) { return wrapPointer(_mud_Widget_key_stroke_1(self, code), KeyEvent); return; }
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
    if (modifier === undefined) { return wrapPointer(_mud_Widget_mouse_event_2(self, device, event_type), MouseEvent); return; }
    if (consume === undefined) { return wrapPointer(_mud_Widget_mouse_event_3(self, device, event_type, modifier), MouseEvent); return; }
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
Module['Sequence'] = Sequence;
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
Module['Window'] = Window;
Window.prototype["__destroy__"] = Window.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Window__destroy(self);
};
Module['auto_modal'] = function(parent, mode, size) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* mode <uint32_t> [] */
    /* size <vec2> [] */
    size = size.ptr;
    if (size === undefined) { return wrapPointer(_mud_ui_auto_modal_2(parent, mode), Widget); return; }
    return wrapPointer(_mud_ui_auto_modal_3(parent, mode, size), Widget);
};
Module['board'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_board_1(parent), Widget);
};
Module['button'] = function(parent, content) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* content <const char*> [] */
    if (content === undefined) { return wrapPointer(_mud_ui_button_1(parent), Widget); return; }
    return wrapPointer(_mud_ui_button_2(parent, content), Widget);
};
Module['canvas'] = function(parent, num_nodes) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* num_nodes <size_t> [] */
    if (num_nodes === undefined) { return wrapPointer(_mud_ui_canvas_1(parent), Canvas); return; }
    return wrapPointer(_mud_ui_canvas_2(parent, num_nodes), Canvas);
};
Module['checkbox'] = function(parent, on) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* on <bool> [] */
    return wrapPointer(_mud_ui_checkbox_2(parent, on), Widget);
};
Module['color_display'] = function(parent, value) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* value <Colour> [] */
    value = value.ptr;
    return wrapPointer(_mud_ui_color_display_2(parent, value), Widget);
};
Module['color_display_field'] = function(parent, name, value, reverse) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    /* value <Colour> [] */
    value = value.ptr;
    /* reverse <bool> [] */
    if (reverse === undefined) { _mud_ui_color_display_field_3(parent, name, value); return; }
    _mud_ui_color_display_field_4(parent, name, value, reverse);
};
Module['color_edit'] = function(parent, value) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* value <Colour> [] */
    value = value.ptr;
    return !!(_mud_ui_color_edit_2(parent, value));
};
Module['color_edit_hsl'] = function(parent, colour, value) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* colour <Colour> [] */
    colour = colour.ptr;
    /* value <Colour> [] */
    value = value.ptr;
    return !!(_mud_ui_color_edit_hsl_3(parent, colour, value));
};
Module['color_edit_simple'] = function(parent, value) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* value <Colour> [] */
    value = value.ptr;
    return !!(_mud_ui_color_edit_simple_2(parent, value));
};
Module['color_field'] = function(parent, name, value, reverse) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    /* value <Colour> [] */
    value = value.ptr;
    /* reverse <bool> [] */
    if (reverse === undefined) { return !!(_mud_ui_color_field_3(parent, name, value)); return; }
    return !!(_mud_ui_color_field_4(parent, name, value, reverse));
};
Module['color_toggle_edit'] = function(parent, value) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* value <Colour> [] */
    value = value.ptr;
    return !!(_mud_ui_color_toggle_edit_2(parent, value));
};
Module['command_line'] = function(parent, text, command) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* text <std::string> [] */
    if (text && typeof text === "object") text = text.ptr;
    else text = ensureString(text);
    /* command <std::string> [] */
    if (command && typeof command === "object") command = command.ptr;
    else command = ensureString(command);
    return wrapPointer(_mud_ui_command_line_3(parent, text, command), Widget);
};
Module['console'] = function(parent, feed, line, command, num_lines) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* feed <std::string> [] */
    if (feed && typeof feed === "object") feed = feed.ptr;
    else feed = ensureString(feed);
    /* line <std::string> [] */
    if (line && typeof line === "object") line = line.ptr;
    else line = ensureString(line);
    /* command <std::string> [] */
    if (command && typeof command === "object") command = command.ptr;
    else command = ensureString(command);
    /* num_lines <size_t> [] */
    if (num_lines === undefined) { return wrapPointer(_mud_ui_console_4(parent, feed, line, command), Widget); return; }
    return wrapPointer(_mud_ui_console_5(parent, feed, line, command, num_lines), Widget);
};
Module['context'] = function(parent, mode, flags) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* mode <uint32_t> [] */
    /* flags <PopupFlags> [] */
    if (flags && typeof flags === "object") flags = flags.ptr;
    if (flags === undefined) { return wrapPointer(_mud_ui_context_2(parent, mode), Widget); return; }
    return wrapPointer(_mud_ui_context_3(parent, mode, flags), Widget);
};
Module['cursor'] = function(parent, position, hovered, locked) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* position <vec2> [] */
    position = position.ptr;
    /* hovered <Widget> [] */
    hovered = hovered.ptr;
    /* locked <bool> [] */
    if (locked === undefined) { return wrapPointer(_mud_ui_cursor_3(parent, position, hovered), Widget); return; }
    return wrapPointer(_mud_ui_cursor_4(parent, position, hovered, locked), Widget);
};
Module['decal'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_decal_1(parent), Widget);
};
Module['dir_item'] = function(parent, name) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    return wrapPointer(_mud_ui_dir_item_2(parent, name), Widget);
};
Module['dir_node'] = function(parent, path, name, collapsed) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* path <const char*> [] */
    /* name <const char*> [] */
    /* collapsed <bool> [] */
    return wrapPointer(_mud_ui_dir_node_4(parent, path, name, collapsed), Widget);
};
Module['div'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_div_1(parent), Widget);
};
Module['dockbar'] = function(parent, docksystem) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* docksystem <Docksystem> [] */
    docksystem = docksystem.ptr;
    return wrapPointer(_mud_ui_dockbar_2(parent, docksystem), Dockbar);
};
Module['dockitem'] = function(parent, docksystem, dock) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* docksystem <Docksystem> [] */
    docksystem = docksystem.ptr;
    /* dock <Dock> [] */
    dock = dock.ptr;
    return wrapPointer(_mud_ui_dockitem_3(parent, docksystem, dock), Widget);
};
Module['dockspace'] = function(parent, docksystem) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* docksystem <Docksystem> [] */
    docksystem = docksystem.ptr;
    return wrapPointer(_mud_ui_dockspace_2(parent, docksystem), Dockspace);
};
Module['drag_float'] = function(parent, value, step) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* value <float> [] */
    /* step <float> [] */
    if (step === undefined) { return !!(_mud_ui_drag_float_2(parent, value)); return; }
    return !!(_mud_ui_drag_float_3(parent, value, step));
};
Module['dropdown'] = function(parent, style, value, flags, list_style) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* style <Style> [] */
    style = style.ptr;
    /* value <const char*> [] */
    /* flags <PopupFlags> [] */
    if (flags && typeof flags === "object") flags = flags.ptr;
    /* list_style <Style> [] */
    list_style = list_style.ptr;
    if (list_style === undefined) { return wrapPointer(_mud_ui_dropdown_4(parent, style, value, flags), Widget); return; }
    return wrapPointer(_mud_ui_dropdown_5(parent, style, value, flags, list_style), Widget);
};
Module['dummy'] = function(parent, size) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* size <vec2> [] */
    size = size.ptr;
    return wrapPointer(_mud_ui_dummy_2(parent, size), Widget);
};
Module['expandbox'] = function(parent, name, open) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    /* open <bool> [] */
    if (open === undefined) { return wrapPointer(_mud_ui_expandbox_2(parent, name), Expandbox); return; }
    return wrapPointer(_mud_ui_expandbox_3(parent, name, open), Expandbox);
};
Module['file_browser'] = function(parent, path) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* path <std::string> [] */
    if (path && typeof path === "object") path = path.ptr;
    else path = ensureString(path);
    return wrapPointer(_mud_ui_file_browser_2(parent, path), Widget);
};
Module['file_item'] = function(parent, name) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    return wrapPointer(_mud_ui_file_item_2(parent, name), Widget);
};
Module['file_list'] = function(parent, path) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* path <std::string> [] */
    if (path && typeof path === "object") path = path.ptr;
    else path = ensureString(path);
    return wrapPointer(_mud_ui_file_list_2(parent, path), Widget);
};
Module['file_node'] = function(parent, name) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    return wrapPointer(_mud_ui_file_node_2(parent, name), Widget);
};
Module['file_tree'] = function(parent, path) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* path <const char*> [] */
    return wrapPointer(_mud_ui_file_tree_2(parent, path), Widget);
};
Module['fill_bar'] = function(parent, percentage, dim) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* percentage <float> [] */
    /* dim <Dim> [] */
    if (dim && typeof dim === "object") dim = dim.ptr;
    if (dim === undefined) { return wrapPointer(_mud_ui_fill_bar_2(parent, percentage), Widget); return; }
    return wrapPointer(_mud_ui_fill_bar_3(parent, percentage, dim), Widget);
};
Module['flag_field'] = function(parent, name, value, shift, reverse) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    /* value <uint32_t> [] */
    /* shift <uint8_t> [] */
    /* reverse <bool> [] */
    if (reverse === undefined) { return !!(_mud_ui_flag_field_4(parent, name, value, shift)); return; }
    return !!(_mud_ui_flag_field_5(parent, name, value, shift, reverse));
};
Module['header'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_header_1(parent), Widget);
};
Module['hoverbox'] = function(parent, delay) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* delay <float> [] */
    if (delay === undefined) { return wrapPointer(_mud_ui_hoverbox_1(parent), Widget); return; }
    return wrapPointer(_mud_ui_hoverbox_2(parent, delay), Widget);
};
Module['icon'] = function(parent, icon) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* icon <const char*> [] */
    return wrapPointer(_mud_ui_icon_2(parent, icon), Widget);
};
Module['image256'] = function(parent, name, source, size) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    /* source <Image256> [] */
    source = source.ptr;
    /* size <vec2> [] */
    size = size.ptr;
    if (size === undefined) { return wrapPointer(_mud_ui_image256_3(parent, name, source), Widget); return; }
    return wrapPointer(_mud_ui_image256_4(parent, name, source, size), Widget);
};
Module['item'] = function(parent, style, content) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* style <Style> [] */
    style = style.ptr;
    /* content <const char*> [] */
    if (content === undefined) { return wrapPointer(_mud_ui_item_2(parent, style), Widget); return; }
    return wrapPointer(_mud_ui_item_3(parent, style, content), Widget);
};
Module['label'] = function(parent, label) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* label <const char*> [] */
    return wrapPointer(_mud_ui_label_2(parent, label), Widget);
};
Module['layout'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_layout_1(parent), Widget);
};
Module['menu'] = function(parent, label, submenu) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* label <const char*> [] */
    /* submenu <bool> [] */
    if (submenu === undefined) { return wrapPointer(_mud_ui_menu_2(parent, label), Widget); return; }
    return wrapPointer(_mud_ui_menu_3(parent, label, submenu), Widget);
};
Module['menu_choice'] = function(parent, content) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* content <const char*> [] */
    return wrapPointer(_mud_ui_menu_choice_2(parent, content), Widget);
};
Module['menubar'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_menubar_1(parent), Widget);
};
Module['message'] = function(parent, label) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* label <const char*> [] */
    return wrapPointer(_mud_ui_message_2(parent, label), Widget);
};
Module['modal'] = function(parent, size) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* size <vec2> [] */
    size = size.ptr;
    if (size === undefined) { return wrapPointer(_mud_ui_modal_1(parent), Widget); return; }
    return wrapPointer(_mud_ui_modal_2(parent, size), Widget);
};
Module['modal_button'] = function(screen, parent, content, mode) {
    var self = this.ptr;
    /* screen <Widget> [] */
    screen = screen.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* content <const char*> [] */
    /* mode <uint32_t> [] */
    return !!(_mud_ui_modal_button_4(screen, parent, content, mode));
};
Module['node_cable'] = function(canvas, plug_out, plug_in) {
    var self = this.ptr;
    /* canvas <Canvas> [] */
    canvas = canvas.ptr;
    /* plug_out <NodePlug> [] */
    plug_out = plug_out.ptr;
    /* plug_in <NodePlug> [] */
    plug_in = plug_in.ptr;
    return wrapPointer(_mud_ui_node_cable_3(canvas, plug_out, plug_in), Widget);
};
Module['node_input'] = function(node, name, icon, colour, active, connected) {
    var self = this.ptr;
    /* node <Node> [] */
    node = node.ptr;
    /* name <const char*> [] */
    /* icon <const char*> [] */
    /* colour <Colour> [] */
    if(typeof colour !== "undefined" && colour !== null) {{ colour = colour.ptr }};
    /* active <bool> [] */
    /* connected <bool> [] */
    if (icon === undefined) { return wrapPointer(_mud_ui_node_input_2(node, name), NodePlug); return; }
    if (colour === undefined) { return wrapPointer(_mud_ui_node_input_3(node, name, icon), NodePlug); return; }
    if (active === undefined) { return wrapPointer(_mud_ui_node_input_4(node, name, icon, colour), NodePlug); return; }
    if (connected === undefined) { return wrapPointer(_mud_ui_node_input_5(node, name, icon, colour, active), NodePlug); return; }
    return wrapPointer(_mud_ui_node_input_6(node, name, icon, colour, active, connected), NodePlug);
};
Module['node_output'] = function(node, name, icon, colour, active, connected) {
    var self = this.ptr;
    /* node <Node> [] */
    node = node.ptr;
    /* name <const char*> [] */
    /* icon <const char*> [] */
    /* colour <Colour> [] */
    if(typeof colour !== "undefined" && colour !== null) {{ colour = colour.ptr }};
    /* active <bool> [] */
    /* connected <bool> [] */
    if (icon === undefined) { return wrapPointer(_mud_ui_node_output_2(node, name), NodePlug); return; }
    if (colour === undefined) { return wrapPointer(_mud_ui_node_output_3(node, name, icon), NodePlug); return; }
    if (active === undefined) { return wrapPointer(_mud_ui_node_output_4(node, name, icon, colour), NodePlug); return; }
    if (connected === undefined) { return wrapPointer(_mud_ui_node_output_5(node, name, icon, colour, active), NodePlug); return; }
    return wrapPointer(_mud_ui_node_output_6(node, name, icon, colour, active, connected), NodePlug);
};
Module['overlay'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_overlay_1(parent), Widget);
};
Module['popup'] = function(parent, flags) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* flags <PopupFlags> [] */
    if (flags && typeof flags === "object") flags = flags.ptr;
    return wrapPointer(_mud_ui_popup_2(parent, flags), Widget);
};
Module['popup_at'] = function(parent, position, flags) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* position <vec2> [] */
    position = position.ptr;
    /* flags <PopupFlags> [] */
    if (flags && typeof flags === "object") flags = flags.ptr;
    if (flags === undefined) { return wrapPointer(_mud_ui_popup_at_2(parent, position), Widget); return; }
    return wrapPointer(_mud_ui_popup_at_3(parent, position, flags), Widget);
};
Module['quat_edit'] = function(parent, quat) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* quat <quat> [] */
    quat = quat.ptr;
    return !!(_mud_ui_quat_edit_2(parent, quat));
};
Module['radio_choice'] = function(parent, value, active) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* value <const char*> [] */
    /* active <bool> [] */
    return wrapPointer(_mud_ui_radio_choice_3(parent, value, active), Widget);
};
Module['rectangle'] = function(parent, rect) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* rect <vec4> [] */
    rect = rect.ptr;
    return wrapPointer(_mud_ui_rectangle_2(parent, rect), Widget);
};
Module['row'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_row_1(parent), Widget);
};
Module['screen'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_screen_1(parent), Widget);
};
Module['scroll_sequence'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_scroll_sequence_1(parent), Sequence);
};
Module['scrollable'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_scrollable_1(parent), Widget);
};
Module['select_list'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_select_list_1(parent), ScrollSheet);
};
Module['sequence'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_sequence_1(parent), Sequence);
};
Module['sheet'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_sheet_1(parent), Widget);
};
Module['spacer'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_spacer_1(parent), Widget);
};
Module['spanner'] = function(parent, style, dim, span) {
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
Module['stack'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_stack_1(parent), Widget);
};
Module['tab'] = function(tabber, name) {
    var self = this.ptr;
    /* tabber <Tabber> [] */
    tabber = tabber.ptr;
    /* name <const char*> [] */
    return wrapPointer(_mud_ui_tab_2(tabber, name), Widget);
};
Module['tabber'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_tabber_1(parent), Tabber);
};
Module['table_row'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_table_row_1(parent), Widget);
};
Module['table_separator'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_table_separator_1(parent), Widget);
};
Module['text'] = function(parent, label) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* label <const char*> [] */
    return wrapPointer(_mud_ui_text_2(parent, label), Widget);
};
Module['text_box'] = function(parent, style, text, editor, lines, allowed_chars) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* style <Style> [] */
    style = style.ptr;
    /* text <std::string> [] */
    if (text && typeof text === "object") text = text.ptr;
    else text = ensureString(text);
    /* editor <bool> [] */
    /* lines <size_t> [] */
    /* allowed_chars <std::string> [] */
    if (allowed_chars && typeof allowed_chars === "object") allowed_chars = allowed_chars.ptr;
    else allowed_chars = ensureString(allowed_chars);
    if (editor === undefined) { return wrapPointer(_mud_ui_text_box_3(parent, style, text), TextEdit); return; }
    if (lines === undefined) { return wrapPointer(_mud_ui_text_box_4(parent, style, text, editor), TextEdit); return; }
    if (allowed_chars === undefined) { return wrapPointer(_mud_ui_text_box_5(parent, style, text, editor, lines), TextEdit); return; }
    return wrapPointer(_mud_ui_text_box_6(parent, style, text, editor, lines, allowed_chars), TextEdit);
};
Module['title'] = function(parent, label) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* label <const char*> [] */
    return wrapPointer(_mud_ui_title_2(parent, label), Widget);
};
Module['title_header'] = function(parent, title) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* title <const char*> [] */
    return wrapPointer(_mud_ui_title_header_2(parent, title), Widget);
};
Module['toggle'] = function(parent, on, content) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* on <bool> [] */
    /* content <const char*> [] */
    if (content === undefined) { return wrapPointer(_mud_ui_toggle_2(parent, on), Widget); return; }
    return wrapPointer(_mud_ui_toggle_3(parent, on, content), Widget);
};
Module['toolbar'] = function(parent, wrap) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* wrap <bool> [] */
    if (wrap === undefined) { return wrapPointer(_mud_ui_toolbar_1(parent), Widget); return; }
    return wrapPointer(_mud_ui_toolbar_2(parent, wrap), Widget);
};
Module['toolbutton'] = function(parent, icon) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* icon <const char*> [] */
    return wrapPointer(_mud_ui_toolbutton_2(parent, icon), Widget);
};
Module['tooldock'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_tooldock_1(parent), Widget);
};
Module['tooltip'] = function(parent, position, content) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* position <vec2> [] */
    position = position.ptr;
    /* content <const char*> [] */
    return wrapPointer(_mud_ui_tooltip_3(parent, position, content), Widget);
};
Module['tree'] = function(parent) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    return wrapPointer(_mud_ui_tree_1(parent), Widget);
};
Module['tree_node'] = function(parent, name, leaf, open) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* name <const char*> [] */
    /* leaf <bool> [] */
    /* open <bool> [] */
    if (leaf === undefined) { return wrapPointer(_mud_ui_tree_node_2(parent, name), TreeNode); return; }
    if (open === undefined) { return wrapPointer(_mud_ui_tree_node_3(parent, name, leaf), TreeNode); return; }
    return wrapPointer(_mud_ui_tree_node_4(parent, name, leaf, open), TreeNode);
};
Module['type_in'] = function(parent, text, lines, allowed_chars) {
    var self = this.ptr;
    ensureCache.prepare();
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* text <std::string> [] */
    if (text && typeof text === "object") text = text.ptr;
    else text = ensureString(text);
    /* lines <size_t> [] */
    /* allowed_chars <std::string> [] */
    if (allowed_chars && typeof allowed_chars === "object") allowed_chars = allowed_chars.ptr;
    else allowed_chars = ensureString(allowed_chars);
    if (lines === undefined) { return wrapPointer(_mud_ui_type_in_2(parent, text), TextEdit); return; }
    if (allowed_chars === undefined) { return wrapPointer(_mud_ui_type_in_3(parent, text, lines), TextEdit); return; }
    return wrapPointer(_mud_ui_type_in_4(parent, text, lines, allowed_chars), TextEdit);
};
Module['vec2_edit'] = function(parent, vec) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* vec <vec2> [] */
    vec = vec.ptr;
    return !!(_mud_ui_vec2_edit_2(parent, vec));
};
Module['vec3_edit'] = function(parent, vec) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* vec <vec3> [] */
    vec = vec.ptr;
    return !!(_mud_ui_vec3_edit_2(parent, vec));
};
Module['widget'] = function(parent, style, open, length, index) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* style <Style> [] */
    style = style.ptr;
    /* open <bool> [] */
    /* length <Dim> [] */
    if (length && typeof length === "object") length = length.ptr;
    /* index <Dim2<size_t>> [] */
    if(typeof index !== "undefined" && index !== null) {{ index = index.ptr }};
    if (open === undefined) { return wrapPointer(_mud_ui_widget_2(parent, style), Widget); return; }
    if (length === undefined) { return wrapPointer(_mud_ui_widget_3(parent, style, open), Widget); return; }
    if (index === undefined) { return wrapPointer(_mud_ui_widget_4(parent, style, open, length), Widget); return; }
    return wrapPointer(_mud_ui_widget_5(parent, style, open, length, index), Widget);
};
Module['window'] = function(parent, title, state) {
    var self = this.ptr;
    /* parent <Widget> [] */
    parent = parent.ptr;
    /* title <const char*> [] */
    /* state <WindowState> [] */
    if (state && typeof state === "object") state = state.ptr;
    if (state === undefined) { return wrapPointer(_mud_ui_window_2(parent, title), Window); return; }
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
        Module['PopupFlags']['None'] = _mud_ui_PopupFlags_None();
        Module['PopupFlags']['Modal'] = _mud_ui_PopupFlags_Modal();
        Module['PopupFlags']['Clamp'] = _mud_ui_PopupFlags_Clamp();
        Module['PopupFlags']['AutoClose'] = _mud_ui_PopupFlags_AutoClose();
        Module['PopupFlags']['AutoModal'] = _mud_ui_PopupFlags_AutoModal();
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
