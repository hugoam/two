
// Bindings utilities
function WrapperObject() {
}
// CanvasConnect
function CanvasConnect() {
    var self = this.ptr;
    this.ptr = _CanvasConnect_CanvasConnect_0(self); getCache(CanvasConnect)[this.ptr] = this;
};
CanvasConnect.prototype = Object.create(WrapperObject.prototype);
CanvasConnect.prototype.constructor = CanvasConnect;
CanvasConnect.prototype.__class__ = CanvasConnect;
CanvasConnect.__cache__ = {};
Module['CanvasConnect'] = CanvasConnect;
CanvasConnect.prototype["__destroy__"] = CanvasConnect.prototype.__destroy__ = function() {
    var self = this.ptr;
    _CanvasConnect___destroy__(self);
};
// Clipboard
function Clipboard() {
    var self = this.ptr;
    this.ptr = _Clipboard_Clipboard_0(self); getCache(Clipboard)[this.ptr] = this;
};
Clipboard.prototype = Object.create(WrapperObject.prototype);
Clipboard.prototype.constructor = Clipboard;
Clipboard.prototype.__class__ = Clipboard;
Clipboard.__cache__ = {};
Module['Clipboard'] = Clipboard;
Object.defineProperty(Clipboard.prototype, "text", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_Clipboard_get_text(self));
    },
    set: function(text) {
        var self = this.ptr;
        /* text <std::string> [] */
        if (text && typeof text === "object") text = text.ptr;
        else text = ensureString(text);
        _Clipboard_set_text(self, text);
    }
});
Object.defineProperty(Clipboard.prototype, "line_mode", {
    get: function() {
        var self = this.ptr;
        return !!(_Clipboard_get_line_mode(self));
    },
    set: function(line_mode) {
        var self = this.ptr;
        /* line_mode <bool> [] */
        _Clipboard_set_line_mode(self, line_mode);
    }
});
Object.defineProperty(Clipboard.prototype, "pasted", {
    get: function() {
        var self = this.ptr;
        return _Clipboard_get_pasted(self);
    },
    set: function(pasted) {
        var self = this.ptr;
        /* pasted <std::vector<std::string>> [] */
        _Clipboard_set_pasted(self, pasted);
    }
});
Clipboard.prototype["__destroy__"] = Clipboard.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Clipboard___destroy__(self);
};
// Dock
function Dock() {
    var self = this.ptr;
    this.ptr = _Dock_Dock_0(self); getCache(Dock)[this.ptr] = this;
};
Dock.prototype = Object.create(WrapperObject.prototype);
Dock.prototype.constructor = Dock;
Dock.prototype.__class__ = Dock;
Dock.__cache__ = {};
Module['Dock'] = Dock;
Dock.prototype["__destroy__"] = Dock.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Dock___destroy__(self);
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
    _Docksystem___destroy__(self);
};
// Gradient
function Gradient() {
    var self = this.ptr;
    this.ptr = _Gradient_Gradient_0(self); getCache(Gradient)[this.ptr] = this;
};
Gradient.prototype = Object.create(WrapperObject.prototype);
Gradient.prototype.constructor = Gradient;
Gradient.prototype.__class__ = Gradient;
Gradient.__cache__ = {};
Module['Gradient'] = Gradient;
Object.defineProperty(Gradient.prototype, "start", {
    get: function() {
        var self = this.ptr;
        return _Gradient_get_start(self);
    },
    set: function(start) {
        var self = this.ptr;
        /* start <Colour> [] */
        _Gradient_set_start(self, start);
    }
});
Object.defineProperty(Gradient.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return _Gradient_get_end(self);
    },
    set: function(end) {
        var self = this.ptr;
        /* end <Colour> [] */
        _Gradient_set_end(self, end);
    }
});
Gradient.prototype["__destroy__"] = Gradient.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Gradient___destroy__(self);
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
    _GridSolver___destroy__(self);
};
// ImageSkin
function ImageSkin(image, left, top, right, bottom, margin, stretch) {
    var self = this.ptr;
    /* image <Image> [] */
    /* left <int> [] */
    /* top <int> [] */
    /* right <int> [] */
    /* bottom <int> [] */
    /* margin <int> [] */
    /* stretch <Dim> [] */
    if (image === undefined) { this.ptr = _ImageSkin_ImageSkin_0(self); getCache(ImageSkin)[this.ptr] = this; return; }
    if (margin === undefined) { this.ptr = _ImageSkin_ImageSkin_5(self, image, left, top, right, bottom); getCache(ImageSkin)[this.ptr] = this; return; }
    if (stretch === undefined) { this.ptr = _ImageSkin_ImageSkin_6(self, image, left, top, right, bottom, margin); getCache(ImageSkin)[this.ptr] = this; return; }
    this.ptr = _ImageSkin_ImageSkin_7(self, image, left, top, right, bottom, margin, stretch); getCache(ImageSkin)[this.ptr] = this;
};
ImageSkin.prototype = Object.create(WrapperObject.prototype);
ImageSkin.prototype.constructor = ImageSkin;
ImageSkin.prototype.__class__ = ImageSkin;
ImageSkin.__cache__ = {};
Module['ImageSkin'] = ImageSkin;
Object.defineProperty(ImageSkin.prototype, "d_image", {
    get: function() {
        var self = this.ptr;
        return _ImageSkin_get_d_image(self);
    },
    set: function(d_image) {
        var self = this.ptr;
        /* d_image <Image> [] */
        _ImageSkin_set_d_image(self, d_image);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_left", {
    get: function() {
        var self = this.ptr;
        return _ImageSkin_get_d_left(self);
    },
    set: function(d_left) {
        var self = this.ptr;
        /* d_left <int> [] */
        _ImageSkin_set_d_left(self, d_left);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_top", {
    get: function() {
        var self = this.ptr;
        return _ImageSkin_get_d_top(self);
    },
    set: function(d_top) {
        var self = this.ptr;
        /* d_top <int> [] */
        _ImageSkin_set_d_top(self, d_top);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_right", {
    get: function() {
        var self = this.ptr;
        return _ImageSkin_get_d_right(self);
    },
    set: function(d_right) {
        var self = this.ptr;
        /* d_right <int> [] */
        _ImageSkin_set_d_right(self, d_right);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_bottom", {
    get: function() {
        var self = this.ptr;
        return _ImageSkin_get_d_bottom(self);
    },
    set: function(d_bottom) {
        var self = this.ptr;
        /* d_bottom <int> [] */
        _ImageSkin_set_d_bottom(self, d_bottom);
    }
});
Object.defineProperty(ImageSkin.prototype, "margin", {
    get: function() {
        var self = this.ptr;
        return _ImageSkin_get_margin(self);
    },
    set: function(margin) {
        var self = this.ptr;
        /* margin <int> [] */
        _ImageSkin_set_margin(self, margin);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_stretch", {
    get: function() {
        var self = this.ptr;
        return _ImageSkin_get_d_stretch(self);
    },
    set: function(d_stretch) {
        var self = this.ptr;
        /* d_stretch <Dim> [] */
        _ImageSkin_set_d_stretch(self, d_stretch);
    }
});
ImageSkin.prototype["__destroy__"] = ImageSkin.prototype.__destroy__ = function() {
    var self = this.ptr;
    _ImageSkin___destroy__(self);
};
// InkStyle
function InkStyle(name) {
    var self = this.ptr;
    ensureCache.prepare();
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    if (name === undefined) { this.ptr = _InkStyle_InkStyle_0(self); getCache(InkStyle)[this.ptr] = this; return; }
    this.ptr = _InkStyle_InkStyle_1(self, name); getCache(InkStyle)[this.ptr] = this;
};
InkStyle.prototype = Object.create(WrapperObject.prototype);
InkStyle.prototype.constructor = InkStyle;
InkStyle.prototype.__class__ = InkStyle;
InkStyle.__cache__ = {};
Module['InkStyle'] = InkStyle;
Object.defineProperty(InkStyle.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_InkStyle_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _InkStyle_set_name(self, name);
    }
});
Object.defineProperty(InkStyle.prototype, "empty", {
    get: function() {
        var self = this.ptr;
        return !!(_InkStyle_get_empty(self));
    },
    set: function(empty) {
        var self = this.ptr;
        /* empty <bool> [] */
        _InkStyle_set_empty(self, empty);
    }
});
Object.defineProperty(InkStyle.prototype, "background_colour", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_background_colour(self);
    },
    set: function(background_colour) {
        var self = this.ptr;
        /* background_colour <Colour> [] */
        _InkStyle_set_background_colour(self, background_colour);
    }
});
Object.defineProperty(InkStyle.prototype, "border_colour", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_border_colour(self);
    },
    set: function(border_colour) {
        var self = this.ptr;
        /* border_colour <Colour> [] */
        _InkStyle_set_border_colour(self, border_colour);
    }
});
Object.defineProperty(InkStyle.prototype, "image_colour", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_image_colour(self);
    },
    set: function(image_colour) {
        var self = this.ptr;
        /* image_colour <Colour> [] */
        _InkStyle_set_image_colour(self, image_colour);
    }
});
Object.defineProperty(InkStyle.prototype, "text_colour", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_text_colour(self);
    },
    set: function(text_colour) {
        var self = this.ptr;
        /* text_colour <Colour> [] */
        _InkStyle_set_text_colour(self, text_colour);
    }
});
Object.defineProperty(InkStyle.prototype, "text_font", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_InkStyle_get_text_font(self));
    },
    set: function(text_font) {
        var self = this.ptr;
        /* text_font <std::string> [] */
        if (text_font && typeof text_font === "object") text_font = text_font.ptr;
        else text_font = ensureString(text_font);
        _InkStyle_set_text_font(self, text_font);
    }
});
Object.defineProperty(InkStyle.prototype, "text_size", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_text_size(self);
    },
    set: function(text_size) {
        var self = this.ptr;
        /* text_size <float> [] */
        _InkStyle_set_text_size(self, text_size);
    }
});
Object.defineProperty(InkStyle.prototype, "text_break", {
    get: function() {
        var self = this.ptr;
        return !!(_InkStyle_get_text_break(self));
    },
    set: function(text_break) {
        var self = this.ptr;
        /* text_break <bool> [] */
        _InkStyle_set_text_break(self, text_break);
    }
});
Object.defineProperty(InkStyle.prototype, "text_wrap", {
    get: function() {
        var self = this.ptr;
        return !!(_InkStyle_get_text_wrap(self));
    },
    set: function(text_wrap) {
        var self = this.ptr;
        /* text_wrap <bool> [] */
        _InkStyle_set_text_wrap(self, text_wrap);
    }
});
Object.defineProperty(InkStyle.prototype, "border_width", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_border_width(self);
    },
    set: function(border_width) {
        var self = this.ptr;
        /* border_width <vec4> [] */
        _InkStyle_set_border_width(self, border_width);
    }
});
Object.defineProperty(InkStyle.prototype, "corner_radius", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_corner_radius(self);
    },
    set: function(corner_radius) {
        var self = this.ptr;
        /* corner_radius <vec4> [] */
        _InkStyle_set_corner_radius(self, corner_radius);
    }
});
Object.defineProperty(InkStyle.prototype, "weak_corners", {
    get: function() {
        var self = this.ptr;
        return !!(_InkStyle_get_weak_corners(self));
    },
    set: function(weak_corners) {
        var self = this.ptr;
        /* weak_corners <bool> [] */
        _InkStyle_set_weak_corners(self, weak_corners);
    }
});
Object.defineProperty(InkStyle.prototype, "padding", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_padding(self);
    },
    set: function(padding) {
        var self = this.ptr;
        /* padding <vec4> [] */
        _InkStyle_set_padding(self, padding);
    }
});
Object.defineProperty(InkStyle.prototype, "margin", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_margin(self);
    },
    set: function(margin) {
        var self = this.ptr;
        /* margin <vec4> [] */
        _InkStyle_set_margin(self, margin);
    }
});
Object.defineProperty(InkStyle.prototype, "linear_gradient", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_linear_gradient(self);
    },
    set: function(linear_gradient) {
        var self = this.ptr;
        /* linear_gradient <vec2> [] */
        _InkStyle_set_linear_gradient(self, linear_gradient);
    }
});
Object.defineProperty(InkStyle.prototype, "linear_gradient_dim", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_linear_gradient_dim(self);
    },
    set: function(linear_gradient_dim) {
        var self = this.ptr;
        /* linear_gradient_dim <Dim> [] */
        _InkStyle_set_linear_gradient_dim(self, linear_gradient_dim);
    }
});
Object.defineProperty(InkStyle.prototype, "image", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_image(self);
    },
    set: function(image) {
        var self = this.ptr;
        /* image <Image> [] */
        _InkStyle_set_image(self, image);
    }
});
Object.defineProperty(InkStyle.prototype, "overlay", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_overlay(self);
    },
    set: function(overlay) {
        var self = this.ptr;
        /* overlay <Image> [] */
        _InkStyle_set_overlay(self, overlay);
    }
});
Object.defineProperty(InkStyle.prototype, "tile", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_tile(self);
    },
    set: function(tile) {
        var self = this.ptr;
        /* tile <Image> [] */
        _InkStyle_set_tile(self, tile);
    }
});
Object.defineProperty(InkStyle.prototype, "image_skin", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_image_skin(self);
    },
    set: function(image_skin) {
        var self = this.ptr;
        /* image_skin <ImageSkin> [] */
        _InkStyle_set_image_skin(self, image_skin);
    }
});
Object.defineProperty(InkStyle.prototype, "shadow", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_shadow(self);
    },
    set: function(shadow) {
        var self = this.ptr;
        /* shadow <Shadow> [] */
        _InkStyle_set_shadow(self, shadow);
    }
});
Object.defineProperty(InkStyle.prototype, "shadow_colour", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_shadow_colour(self);
    },
    set: function(shadow_colour) {
        var self = this.ptr;
        /* shadow_colour <Colour> [] */
        _InkStyle_set_shadow_colour(self, shadow_colour);
    }
});
Object.defineProperty(InkStyle.prototype, "hover_cursor", {
    get: function() {
        var self = this.ptr;
        return _InkStyle_get_hover_cursor(self);
    },
    set: function(hover_cursor) {
        var self = this.ptr;
        /* hover_cursor <Style> [] */
        _InkStyle_set_hover_cursor(self, hover_cursor);
    }
});
InkStyle.prototype["__destroy__"] = InkStyle.prototype.__destroy__ = function() {
    var self = this.ptr;
    _InkStyle___destroy__(self);
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
    _Layer___destroy__(self);
};
// Layout
function Layout(name) {
    var self = this.ptr;
    ensureCache.prepare();
    /* name <const char*> [] */
    if (name && typeof name === "object") name = name.ptr;
    else name = ensureString(name);
    if (name === undefined) { this.ptr = _Layout_Layout_0(self); getCache(Layout)[this.ptr] = this; return; }
    this.ptr = _Layout_Layout_1(self, name); getCache(Layout)[this.ptr] = this;
};
Layout.prototype = Object.create(WrapperObject.prototype);
Layout.prototype.constructor = Layout;
Layout.prototype.__class__ = Layout;
Layout.__cache__ = {};
Module['Layout'] = Layout;
Object.defineProperty(Layout.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_Layout_get_name(self));
    },
    set: function(name) {
        var self = this.ptr;
        /* name <std::string> [] */
        if (name && typeof name === "object") name = name.ptr;
        else name = ensureString(name);
        _Layout_set_name(self, name);
    }
});
Object.defineProperty(Layout.prototype, "solver", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_solver(self);
    },
    set: function(solver) {
        var self = this.ptr;
        /* solver <LayoutSolver> [] */
        _Layout_set_solver(self, solver);
    }
});
Object.defineProperty(Layout.prototype, "flow", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_flow(self);
    },
    set: function(flow) {
        var self = this.ptr;
        /* flow <Flow> [] */
        _Layout_set_flow(self, flow);
    }
});
Object.defineProperty(Layout.prototype, "space", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_space(self);
    },
    set: function(space) {
        var self = this.ptr;
        /* space <Space> [] */
        _Layout_set_space(self, space);
    }
});
Object.defineProperty(Layout.prototype, "clipping", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_clipping(self);
    },
    set: function(clipping) {
        var self = this.ptr;
        /* clipping <Clipping> [] */
        _Layout_set_clipping(self, clipping);
    }
});
Object.defineProperty(Layout.prototype, "opacity", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_opacity(self);
    },
    set: function(opacity) {
        var self = this.ptr;
        /* opacity <Opacity> [] */
        _Layout_set_opacity(self, opacity);
    }
});
Object.defineProperty(Layout.prototype, "span", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_span(self);
    },
    set: function(span) {
        var self = this.ptr;
        /* span <vec2> [] */
        _Layout_set_span(self, span);
    }
});
Object.defineProperty(Layout.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_size(self);
    },
    set: function(size) {
        var self = this.ptr;
        /* size <vec2> [] */
        _Layout_set_size(self, size);
    }
});
Object.defineProperty(Layout.prototype, "padding", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_padding(self);
    },
    set: function(padding) {
        var self = this.ptr;
        /* padding <vec4> [] */
        _Layout_set_padding(self, padding);
    }
});
Object.defineProperty(Layout.prototype, "margin", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_margin(self);
    },
    set: function(margin) {
        var self = this.ptr;
        /* margin <vec2> [] */
        _Layout_set_margin(self, margin);
    }
});
Object.defineProperty(Layout.prototype, "spacing", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_spacing(self);
    },
    set: function(spacing) {
        var self = this.ptr;
        /* spacing <vec2> [] */
        _Layout_set_spacing(self, spacing);
    }
});
Object.defineProperty(Layout.prototype, "zorder", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_zorder(self);
    },
    set: function(zorder) {
        var self = this.ptr;
        /* zorder <int> [] */
        _Layout_set_zorder(self, zorder);
    }
});
Object.defineProperty(Layout.prototype, "no_grid", {
    get: function() {
        var self = this.ptr;
        return !!(_Layout_get_no_grid(self));
    },
    set: function(no_grid) {
        var self = this.ptr;
        /* no_grid <bool> [] */
        _Layout_set_no_grid(self, no_grid);
    }
});
Object.defineProperty(Layout.prototype, "grid_division", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_grid_division(self);
    },
    set: function(grid_division) {
        var self = this.ptr;
        /* grid_division <std::vector<mud::Space>> [] */
        _Layout_set_grid_division(self, grid_division);
    }
});
Object.defineProperty(Layout.prototype, "table_division", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_table_division(self);
    },
    set: function(table_division) {
        var self = this.ptr;
        /* table_division <std::vector<float>> [] */
        _Layout_set_table_division(self, table_division);
    }
});
Object.defineProperty(Layout.prototype, "updated", {
    get: function() {
        var self = this.ptr;
        return _Layout_get_updated(self);
    },
    set: function(updated) {
        var self = this.ptr;
        /* updated <size_t> [] */
        _Layout_set_updated(self, updated);
    }
});
Layout.prototype["__destroy__"] = Layout.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Layout___destroy__(self);
};
// NodeConnection
function NodeConnection() {
    var self = this.ptr;
    this.ptr = _NodeConnection_NodeConnection_0(self); getCache(NodeConnection)[this.ptr] = this;
};
NodeConnection.prototype = Object.create(WrapperObject.prototype);
NodeConnection.prototype.constructor = NodeConnection;
NodeConnection.prototype.__class__ = NodeConnection;
NodeConnection.__cache__ = {};
Module['NodeConnection'] = NodeConnection;
NodeConnection.prototype["__destroy__"] = NodeConnection.prototype.__destroy__ = function() {
    var self = this.ptr;
    _NodeConnection___destroy__(self);
};
// Paint
function Paint() {
    var self = this.ptr;
    this.ptr = _Paint_Paint_0(self); getCache(Paint)[this.ptr] = this;
};
Paint.prototype = Object.create(WrapperObject.prototype);
Paint.prototype.constructor = Paint;
Paint.prototype.__class__ = Paint;
Paint.__cache__ = {};
Module['Paint'] = Paint;
Object.defineProperty(Paint.prototype, "fill_colour", {
    get: function() {
        var self = this.ptr;
        return _Paint_get_fill_colour(self);
    },
    set: function(fill_colour) {
        var self = this.ptr;
        /* fill_colour <Colour> [] */
        _Paint_set_fill_colour(self, fill_colour);
    }
});
Object.defineProperty(Paint.prototype, "stroke_colour", {
    get: function() {
        var self = this.ptr;
        return _Paint_get_stroke_colour(self);
    },
    set: function(stroke_colour) {
        var self = this.ptr;
        /* stroke_colour <Colour> [] */
        _Paint_set_stroke_colour(self, stroke_colour);
    }
});
Object.defineProperty(Paint.prototype, "stroke_width", {
    get: function() {
        var self = this.ptr;
        return _Paint_get_stroke_width(self);
    },
    set: function(stroke_width) {
        var self = this.ptr;
        /* stroke_width <float> [] */
        _Paint_set_stroke_width(self, stroke_width);
    }
});
Paint.prototype["__destroy__"] = Paint.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Paint___destroy__(self);
};
// Shadow
function Shadow(xpos, ypos, blur, spread, colour) {
    var self = this.ptr;
    /* xpos <float> [] */
    /* ypos <float> [] */
    /* blur <float> [] */
    /* spread <float> [] */
    /* colour <Colour> [] */
    if (xpos === undefined) { this.ptr = _Shadow_Shadow_0(self); getCache(Shadow)[this.ptr] = this; return; }
    if (colour === undefined) { this.ptr = _Shadow_Shadow_4(self, xpos, ypos, blur, spread); getCache(Shadow)[this.ptr] = this; return; }
    this.ptr = _Shadow_Shadow_5(self, xpos, ypos, blur, spread, colour); getCache(Shadow)[this.ptr] = this;
};
Shadow.prototype = Object.create(WrapperObject.prototype);
Shadow.prototype.constructor = Shadow;
Shadow.prototype.__class__ = Shadow;
Shadow.__cache__ = {};
Module['Shadow'] = Shadow;
Object.defineProperty(Shadow.prototype, "d_xpos", {
    get: function() {
        var self = this.ptr;
        return _Shadow_get_d_xpos(self);
    },
    set: function(d_xpos) {
        var self = this.ptr;
        /* d_xpos <float> [] */
        _Shadow_set_d_xpos(self, d_xpos);
    }
});
Object.defineProperty(Shadow.prototype, "d_ypos", {
    get: function() {
        var self = this.ptr;
        return _Shadow_get_d_ypos(self);
    },
    set: function(d_ypos) {
        var self = this.ptr;
        /* d_ypos <float> [] */
        _Shadow_set_d_ypos(self, d_ypos);
    }
});
Object.defineProperty(Shadow.prototype, "d_blur", {
    get: function() {
        var self = this.ptr;
        return _Shadow_get_d_blur(self);
    },
    set: function(d_blur) {
        var self = this.ptr;
        /* d_blur <float> [] */
        _Shadow_set_d_blur(self, d_blur);
    }
});
Object.defineProperty(Shadow.prototype, "d_spread", {
    get: function() {
        var self = this.ptr;
        return _Shadow_get_d_spread(self);
    },
    set: function(d_spread) {
        var self = this.ptr;
        /* d_spread <float> [] */
        _Shadow_set_d_spread(self, d_spread);
    }
});
Object.defineProperty(Shadow.prototype, "d_colour", {
    get: function() {
        var self = this.ptr;
        return _Shadow_get_d_colour(self);
    },
    set: function(d_colour) {
        var self = this.ptr;
        /* d_colour <Colour> [] */
        _Shadow_set_d_colour(self, d_colour);
    }
});
Shadow.prototype["__destroy__"] = Shadow.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Shadow___destroy__(self);
};
// Space
function Space() {
    var self = this.ptr;
    this.ptr = _Space_Space_0(self); getCache(Space)[this.ptr] = this;
};
Space.prototype = Object.create(WrapperObject.prototype);
Space.prototype.constructor = Space;
Space.prototype.__class__ = Space;
Space.__cache__ = {};
Module['Space'] = Space;
Object.defineProperty(Space.prototype, "direction", {
    get: function() {
        var self = this.ptr;
        return _Space_get_direction(self);
    },
    set: function(direction) {
        var self = this.ptr;
        /* direction <FlowAxis> [] */
        _Space_set_direction(self, direction);
    }
});
Object.defineProperty(Space.prototype, "sizingLength", {
    get: function() {
        var self = this.ptr;
        return _Space_get_sizingLength(self);
    },
    set: function(sizingLength) {
        var self = this.ptr;
        /* sizingLength <Sizing> [] */
        _Space_set_sizingLength(self, sizingLength);
    }
});
Object.defineProperty(Space.prototype, "sizingDepth", {
    get: function() {
        var self = this.ptr;
        return _Space_get_sizingDepth(self);
    },
    set: function(sizingDepth) {
        var self = this.ptr;
        /* sizingDepth <Sizing> [] */
        _Space_set_sizingDepth(self, sizingDepth);
    }
});
Space.prototype["__destroy__"] = Space.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Space___destroy__(self);
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
        return _Style_get_base(self);
    },
    set: function(base) {
        var self = this.ptr;
        /* base <Style> [] */
        _Style_set_base(self, base);
    }
});
Object.defineProperty(Style.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_Style_get_name(self));
    }});
Object.defineProperty(Style.prototype, "layout", {
    get: function() {
        var self = this.ptr;
        return _Style_get_layout(self);
    },
    set: function(layout) {
        var self = this.ptr;
        /* layout <Layout> [] */
        _Style_set_layout(self, layout);
    }
});
Object.defineProperty(Style.prototype, "skin", {
    get: function() {
        var self = this.ptr;
        return _Style_get_skin(self);
    },
    set: function(skin) {
        var self = this.ptr;
        /* skin <InkStyle> [] */
        _Style_set_skin(self, skin);
    }
});
Style.prototype["__destroy__"] = Style.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Style___destroy__(self);
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
    _TableSolver___destroy__(self);
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
    _Text___destroy__(self);
};
// TextCursor
function TextCursor() {
    var self = this.ptr;
    this.ptr = _TextCursor_TextCursor_0(self); getCache(TextCursor)[this.ptr] = this;
};
TextCursor.prototype = Object.create(WrapperObject.prototype);
TextCursor.prototype.constructor = TextCursor;
TextCursor.prototype.__class__ = TextCursor;
TextCursor.__cache__ = {};
Module['TextCursor'] = TextCursor;
TextCursor.prototype["__destroy__"] = TextCursor.prototype.__destroy__ = function() {
    var self = this.ptr;
    _TextCursor___destroy__(self);
};
// TextMarker
function TextMarker() {
    var self = this.ptr;
    this.ptr = _TextMarker_TextMarker_0(self); getCache(TextMarker)[this.ptr] = this;
};
TextMarker.prototype = Object.create(WrapperObject.prototype);
TextMarker.prototype.constructor = TextMarker;
TextMarker.prototype.__class__ = TextMarker;
TextMarker.__cache__ = {};
Module['TextMarker'] = TextMarker;
TextMarker.prototype["__destroy__"] = TextMarker.prototype.__destroy__ = function() {
    var self = this.ptr;
    _TextMarker___destroy__(self);
};
// TextPaint
function TextPaint() {
    var self = this.ptr;
    this.ptr = _TextPaint_TextPaint_0(self); getCache(TextPaint)[this.ptr] = this;
};
TextPaint.prototype = Object.create(WrapperObject.prototype);
TextPaint.prototype.constructor = TextPaint;
TextPaint.prototype.__class__ = TextPaint;
TextPaint.__cache__ = {};
Module['TextPaint'] = TextPaint;
Object.defineProperty(TextPaint.prototype, "font", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_TextPaint_get_font(self));
    }});
Object.defineProperty(TextPaint.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return _TextPaint_get_colour(self);
    },
    set: function(colour) {
        var self = this.ptr;
        /* colour <Colour> [] */
        _TextPaint_set_colour(self, colour);
    }
});
Object.defineProperty(TextPaint.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return _TextPaint_get_size(self);
    },
    set: function(size) {
        var self = this.ptr;
        /* size <float> [] */
        _TextPaint_set_size(self, size);
    }
});
Object.defineProperty(TextPaint.prototype, "text_break", {
    get: function() {
        var self = this.ptr;
        return !!(_TextPaint_get_text_break(self));
    },
    set: function(text_break) {
        var self = this.ptr;
        /* text_break <bool> [] */
        _TextPaint_set_text_break(self, text_break);
    }
});
Object.defineProperty(TextPaint.prototype, "text_wrap", {
    get: function() {
        var self = this.ptr;
        return !!(_TextPaint_get_text_wrap(self));
    },
    set: function(text_wrap) {
        var self = this.ptr;
        /* text_wrap <bool> [] */
        _TextPaint_set_text_wrap(self, text_wrap);
    }
});
TextPaint.prototype["__destroy__"] = TextPaint.prototype.__destroy__ = function() {
    var self = this.ptr;
    _TextPaint___destroy__(self);
};
// TextSelection
function TextSelection() {
    var self = this.ptr;
    this.ptr = _TextSelection_TextSelection_0(self); getCache(TextSelection)[this.ptr] = this;
};
TextSelection.prototype = Object.create(WrapperObject.prototype);
TextSelection.prototype.constructor = TextSelection;
TextSelection.prototype.__class__ = TextSelection;
TextSelection.__cache__ = {};
Module['TextSelection'] = TextSelection;
TextSelection.prototype["__destroy__"] = TextSelection.prototype.__destroy__ = function() {
    var self = this.ptr;
    _TextSelection___destroy__(self);
};
// UiRect
function UiRect() {
    var self = this.ptr;
    this.ptr = _UiRect_UiRect_0(self); getCache(UiRect)[this.ptr] = this;
};
UiRect.prototype = Object.create(WrapperObject.prototype);
UiRect.prototype.constructor = UiRect;
UiRect.prototype.__class__ = UiRect;
UiRect.__cache__ = {};
Module['UiRect'] = UiRect;
Object.defineProperty(UiRect.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return _UiRect_get_position(self);
    },
    set: function(position) {
        var self = this.ptr;
        /* position <vec2> [] */
        _UiRect_set_position(self, position);
    }
});
Object.defineProperty(UiRect.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return _UiRect_get_size(self);
    },
    set: function(size) {
        var self = this.ptr;
        /* size <vec2> [] */
        _UiRect_set_size(self, size);
    }
});
Object.defineProperty(UiRect.prototype, "content", {
    get: function() {
        var self = this.ptr;
        return _UiRect_get_content(self);
    },
    set: function(content) {
        var self = this.ptr;
        /* content <vec2> [] */
        _UiRect_set_content(self, content);
    }
});
Object.defineProperty(UiRect.prototype, "span", {
    get: function() {
        var self = this.ptr;
        return _UiRect_get_span(self);
    },
    set: function(span) {
        var self = this.ptr;
        /* span <vec2> [] */
        _UiRect_set_span(self, span);
    }
});
Object.defineProperty(UiRect.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return _UiRect_get_scale(self);
    },
    set: function(scale) {
        var self = this.ptr;
        /* scale <float> [] */
        _UiRect_set_scale(self, scale);
    }
});
UiRect.prototype["__destroy__"] = UiRect.prototype.__destroy__ = function() {
    var self = this.ptr;
    _UiRect___destroy__(self);
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
    _UiWindow___destroy__(self);
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
    _User___destroy__(self);
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
    _Vg___destroy__(self);
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
    _Frame___destroy__(self);
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
    _FrameSolver___destroy__(self);
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
    _LineSolver___destroy__(self);
};
// Widget
function Widget() { throw "cannot construct a Widget, no constructor in IDL" }
Widget.prototype = Object.create(WrapperObject.prototype);
Widget.prototype.constructor = Widget;
Widget.prototype.__class__ = Widget;
Widget.__cache__ = {};
Module['Widget'] = Widget;
Widget.prototype["activated"] = Widget.prototype.activated = function() {
    return !!(_Widget_activated_0());
};
Widget.prototype["char_stroke"] = Widget.prototype.char_stroke = function(code, modifier) {
    /* code <Key> [] */
    /* modifier <InputMod> [] */
    if (modifier === undefined) { return _Widget_char_stroke_1(code); return; }
    return _Widget_char_stroke_2(code, modifier);
};
Widget.prototype["clear_focus"] = Widget.prototype.clear_focus = function() {
    _Widget_clear_focus_0();
};
Widget.prototype["closed"] = Widget.prototype.closed = function() {
    return !!(_Widget_closed_0());
};
Widget.prototype["disable_state"] = Widget.prototype.disable_state = function(state) {
    /* state <WidgetState> [] */
    _Widget_disable_state_1(state);
};
Widget.prototype["enable_state"] = Widget.prototype.enable_state = function(state) {
    /* state <WidgetState> [] */
    _Widget_enable_state_1(state);
};
Widget.prototype["focused"] = Widget.prototype.focused = function() {
    return !!(_Widget_focused_0());
};
Widget.prototype["hovered"] = Widget.prototype.hovered = function() {
    return !!(_Widget_hovered_0());
};
Widget.prototype["key_event"] = Widget.prototype.key_event = function(code, event_type, modifier) {
    /* code <Key> [] */
    /* event_type <EventType> [] */
    /* modifier <InputMod> [] */
    if (modifier === undefined) { return _Widget_key_event_2(code, event_type); return; }
    return _Widget_key_event_3(code, event_type, modifier);
};
Widget.prototype["key_stroke"] = Widget.prototype.key_stroke = function(code, modifier) {
    /* code <Key> [] */
    /* modifier <InputMod> [] */
    if (modifier === undefined) { return _Widget_key_stroke_1(code); return; }
    return _Widget_key_stroke_2(code, modifier);
};
Widget.prototype["modal"] = Widget.prototype.modal = function() {
    return !!(_Widget_modal_0());
};
Widget.prototype["mouse_event"] = Widget.prototype.mouse_event = function(device, event_type, modifier, consume) {
    /* device <DeviceType> [] */
    /* event_type <EventType> [] */
    /* modifier <InputMod> [] */
    /* consume <bool> [] */
    if (modifier === undefined) { return _Widget_mouse_event_2(device, event_type); return; }
    if (consume === undefined) { return _Widget_mouse_event_3(device, event_type, modifier); return; }
    return _Widget_mouse_event_4(device, event_type, modifier, consume);
};
Widget.prototype["parent_modal"] = Widget.prototype.parent_modal = function() {
    return _Widget_parent_modal_0();
};
Widget.prototype["pressed"] = Widget.prototype.pressed = function() {
    return !!(_Widget_pressed_0());
};
Widget.prototype["selected"] = Widget.prototype.selected = function() {
    return !!(_Widget_selected_0());
};
Widget.prototype["set_state"] = Widget.prototype.set_state = function(state, enabled) {
    /* state <WidgetState> [] */
    /* enabled <bool> [] */
    _Widget_set_state_2(state, enabled);
};
Widget.prototype["take_focus"] = Widget.prototype.take_focus = function() {
    _Widget_take_focus_0();
};
Widget.prototype["take_modal"] = Widget.prototype.take_modal = function(device_filter) {
    /* device_filter <uint32_t> [] */
    _Widget_take_modal_1(device_filter);
};
Widget.prototype["toggle_state"] = Widget.prototype.toggle_state = function(state) {
    /* state <WidgetState> [] */
    _Widget_toggle_state_1(state);
};
Widget.prototype["ui"] = Widget.prototype.ui = function() {
    return _Widget_ui_0();
};
Widget.prototype["ui_window"] = Widget.prototype.ui_window = function() {
    return _Widget_ui_window_0();
};
Widget.prototype["yield_focus"] = Widget.prototype.yield_focus = function() {
    _Widget_yield_focus_0();
};
Widget.prototype["yield_modal"] = Widget.prototype.yield_modal = function() {
    _Widget_yield_modal_0();
};
Object.defineProperty(Widget.prototype, "frame", {
    get: function() {
        var self = this.ptr;
        return _Widget_get_frame(self);
    },
    set: function(frame) {
        var self = this.ptr;
        /* frame <Frame> [] */
        _Widget_set_frame(self, frame);
    }
});
Object.defineProperty(Widget.prototype, "state", {
    get: function() {
        var self = this.ptr;
        return _Widget_get_state(self);
    },
    set: function(state) {
        var self = this.ptr;
        /* state <WidgetState> [] */
        _Widget_set_state(self, state);
    }
});
Object.defineProperty(Widget.prototype, "switch", {
    get: function() {
        var self = this.ptr;
        return _Widget_get_switch(self);
    },
    set: function(switch) {
        var self = this.ptr;
        /* switch <uint32_t> [] */
        _Widget_set_switch(self, switch);
    }
});
Object.defineProperty(Widget.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _Widget_get_index(self);
    },
    set: function(index) {
        var self = this.ptr;
        /* index <size_t> [] */
        _Widget_set_index(self, index);
    }
});
Object.defineProperty(Widget.prototype, "open", {
    get: function() {
        var self = this.ptr;
        return !!(_Widget_get_open(self));
    },
    set: function(open) {
        var self = this.ptr;
        /* open <bool> [] */
        _Widget_set_open(self, open);
    }
});
Object.defineProperty(Widget.prototype, "body", {
    get: function() {
        var self = this.ptr;
        return _Widget_get_body(self);
    },
    set: function(body) {
        var self = this.ptr;
        /* body <Widget> [] */
        _Widget_set_body(self, body);
    }
});
Widget.prototype["__destroy__"] = Widget.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Widget___destroy__(self);
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
    _Canvas___destroy__(self);
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
    _Dockable___destroy__(self);
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
    _Docker___destroy__(self);
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
    _Dockbar___destroy__(self);
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
    _Dockspace___destroy__(self);
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
    _Expandbox___destroy__(self);
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
    _Node___destroy__(self);
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
    _NodePlug___destroy__(self);
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
    _RowSolver___destroy__(self);
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
    _ScrollSheet___destroy__(self);
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
    _Sequence___destroy__(self);
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
    _Tabber___destroy__(self);
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
    _Table___destroy__(self);
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
    _TextEdit___destroy__(self);
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
    _TreeNode___destroy__(self);
};
// Ui
function Ui() { throw "cannot construct a Ui, no constructor in IDL" }
Ui.prototype = Object.create(WrapperObject.prototype);
Ui.prototype.constructor = Ui;
Ui.prototype.__class__ = Ui;
Ui.__cache__ = {};
Module['Ui'] = Ui;
Ui.prototype["begin"] = Ui.prototype.begin = function() {
    return _Ui_begin_0();
};
Ui.prototype["__destroy__"] = Ui.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Ui___destroy__(self);
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
    _Window___destroy__(self);
};

(function() {
    function setupEnums() {
        
        // 'Align'
        Module['Left'] = _emscripten_enum_Align_Left();
        Module['CENTER'] = _emscripten_enum_Align_CENTER();
        Module['Right'] = _emscripten_enum_Align_Right();
        Module['OUT_LEFT'] = _emscripten_enum_Align_OUT_LEFT();
        Module['OUT_RIGHT'] = _emscripten_enum_Align_OUT_RIGHT();
        
        // 'AutoLayout'
        Module['NO_LAYOUT'] = _emscripten_enum_AutoLayout_NO_LAYOUT();
        Module['AUTO_SIZE'] = _emscripten_enum_AutoLayout_AUTO_SIZE();
        Module['AUTO_LAYOUT'] = _emscripten_enum_AutoLayout_AUTO_LAYOUT();
        
        // 'Clipping'
        Module['NOCLIP'] = _emscripten_enum_Clipping_NOCLIP();
        Module['CLIP'] = _emscripten_enum_Clipping_CLIP();
        Module['UNCLIP'] = _emscripten_enum_Clipping_UNCLIP();
        
        // 'Dim'
        Module['DIM_X'] = _emscripten_enum_Dim_DIM_X();
        Module['DIM_Y'] = _emscripten_enum_Dim_DIM_Y();
        Module['DIM_NONE'] = _emscripten_enum_Dim_DIM_NONE();
        
        // 'Flow'
        Module['FLOW'] = _emscripten_enum_Flow_FLOW();
        Module['OVERLAY'] = _emscripten_enum_Flow_OVERLAY();
        Module['ALIGN'] = _emscripten_enum_Flow_ALIGN();
        Module['FREE'] = _emscripten_enum_Flow_FREE();
        
        // 'FlowAxis'
        Module['READING'] = _emscripten_enum_FlowAxis_READING();
        Module['PARAGRAPH'] = _emscripten_enum_FlowAxis_PARAGRAPH();
        Module['PARALLEL'] = _emscripten_enum_FlowAxis_PARALLEL();
        Module['ORTHOGONAL'] = _emscripten_enum_FlowAxis_ORTHOGONAL();
        Module['AXIS_NONE'] = _emscripten_enum_FlowAxis_AXIS_NONE();
        
        // 'LayoutSolver'
        Module['FRAME_SOLVER'] = _emscripten_enum_LayoutSolver_FRAME_SOLVER();
        Module['ROW_SOLVER'] = _emscripten_enum_LayoutSolver_ROW_SOLVER();
        Module['GRID_SOLVER'] = _emscripten_enum_LayoutSolver_GRID_SOLVER();
        Module['TABLE_SOLVER'] = _emscripten_enum_LayoutSolver_TABLE_SOLVER();
        
        // 'Opacity'
        Module['OPAQUE'] = _emscripten_enum_Opacity_OPAQUE();
        Module['CLEAR'] = _emscripten_enum_Opacity_CLEAR();
        Module['HOLLOW'] = _emscripten_enum_Opacity_HOLLOW();
        
        // 'Pivot'
        Module['FORWARD'] = _emscripten_enum_Pivot_FORWARD();
        Module['REVERSE'] = _emscripten_enum_Pivot_REVERSE();
        
        // 'PopupFlags'
        Module['PopupFlags']['None'] = _emscripten_enum_PopupFlags_None();
        Module['PopupFlags']['Modal'] = _emscripten_enum_PopupFlags_Modal();
        Module['PopupFlags']['Clamp'] = _emscripten_enum_PopupFlags_Clamp();
        Module['PopupFlags']['AutoClose'] = _emscripten_enum_PopupFlags_AutoClose();
        Module['PopupFlags']['AutoModal'] = _emscripten_enum_PopupFlags_AutoModal();
        
        // 'Sizing'
        Module['FIXED'] = _emscripten_enum_Sizing_FIXED();
        Module['SHRINK'] = _emscripten_enum_Sizing_SHRINK();
        Module['WRAP'] = _emscripten_enum_Sizing_WRAP();
        Module['EXPAND'] = _emscripten_enum_Sizing_EXPAND();
        
        // 'SpacePreset'
        Module['SHEET'] = _emscripten_enum_SpacePreset_SHEET();
        Module['FLEX'] = _emscripten_enum_SpacePreset_FLEX();
        Module['ITEM'] = _emscripten_enum_SpacePreset_ITEM();
        Module['UNIT'] = _emscripten_enum_SpacePreset_UNIT();
        Module['BLOCK'] = _emscripten_enum_SpacePreset_BLOCK();
        Module['LINE'] = _emscripten_enum_SpacePreset_LINE();
        Module['STACK'] = _emscripten_enum_SpacePreset_STACK();
        Module['DIV'] = _emscripten_enum_SpacePreset_DIV();
        Module['SPACER'] = _emscripten_enum_SpacePreset_SPACER();
        Module['BOARD'] = _emscripten_enum_SpacePreset_BOARD();
        Module['LAYOUT'] = _emscripten_enum_SpacePreset_LAYOUT();
        
        // 'WidgetState'
        Module['NOSTATE'] = _emscripten_enum_WidgetState_NOSTATE();
        Module['CREATED'] = _emscripten_enum_WidgetState_CREATED();
        Module['HOVERED'] = _emscripten_enum_WidgetState_HOVERED();
        Module['PRESSED'] = _emscripten_enum_WidgetState_PRESSED();
        Module['ACTIVATED'] = _emscripten_enum_WidgetState_ACTIVATED();
        Module['ACTIVE'] = _emscripten_enum_WidgetState_ACTIVE();
        Module['SELECTED'] = _emscripten_enum_WidgetState_SELECTED();
        Module['DISABLED'] = _emscripten_enum_WidgetState_DISABLED();
        Module['DRAGGED'] = _emscripten_enum_WidgetState_DRAGGED();
        Module['FOCUSED'] = _emscripten_enum_WidgetState_FOCUSED();
        Module['CLOSED'] = _emscripten_enum_WidgetState_CLOSED();
        
        // 'WindowState'
        Module['WINDOW_NOSTATE'] = _emscripten_enum_WindowState_WINDOW_NOSTATE();
        Module['WINDOW_HEADER'] = _emscripten_enum_WindowState_WINDOW_HEADER();
        Module['WINDOW_DOCKABLE'] = _emscripten_enum_WindowState_WINDOW_DOCKABLE();
        Module['WINDOW_CLOSABLE'] = _emscripten_enum_WindowState_WINDOW_CLOSABLE();
        Module['WINDOW_MOVABLE'] = _emscripten_enum_WindowState_WINDOW_MOVABLE();
        Module['WINDOW_SIZABLE'] = _emscripten_enum_WindowState_WINDOW_SIZABLE();
        Module['WINDOW_DEFAULT'] = _emscripten_enum_WindowState_WINDOW_DEFAULT();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
