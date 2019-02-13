Module['ui'] = Module['ui'] || {};
Module['stl'] = Module['stl'] || {};
// CanvasConnect
function CanvasConnect() {
    this.ptr = _mud_CanvasConnect__construct_0(); this.type = CanvasConnect; getCache(CanvasConnect)[this.ptr] = this;
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
    this.ptr = _mud_Clipboard__construct_0(); this.type = Clipboard; getCache(Clipboard)[this.ptr] = this;
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
        _mud_Clipboard__set_text(self, ensureString(value));
    }
});
Object.defineProperty(Clipboard.prototype, "line_mode", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Clipboard__get_line_mode(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Clipboard__set_line_mode(self, value);
    }
});
Clipboard.prototype["__destroy__"] = Clipboard.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Clipboard__destroy(self);
};
// Dock
function Dock() {
    this.ptr = _mud_Dock__construct_0(); this.type = Dock; getCache(Dock)[this.ptr] = this;
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
    this.ptr = _mud_Gradient__construct_0(); this.type = Gradient; getCache(Gradient)[this.ptr] = this;
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
        _mud_Gradient__set_start(self, value.ptr);
    }
});
Object.defineProperty(Gradient.prototype, "end", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Gradient__get_end(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Gradient__set_end(self, value.ptr);
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
function ImageSkin(a0, a1, a2, a3, a4, a5, a6) {
    if (a5 === undefined) { this.ptr = _mud_ImageSkin__construct_5(/*image*/a0.ptr, /*left*/a1, /*top*/a2, /*right*/a3, /*bottom*/a4); this.type = ImageSkin; getCache(ImageSkin)[this.ptr] = this; return; }
    if (a6 === undefined) { this.ptr = _mud_ImageSkin__construct_6(/*image*/a0.ptr, /*left*/a1, /*top*/a2, /*right*/a3, /*bottom*/a4, /*margin*/a5); this.type = ImageSkin; getCache(ImageSkin)[this.ptr] = this; return; }
    this.ptr = _mud_ImageSkin__construct_7(/*image*/a0.ptr, /*left*/a1, /*top*/a2, /*right*/a3, /*bottom*/a4, /*margin*/a5, /*stretch*/a6); this.type = ImageSkin; getCache(ImageSkin)[this.ptr] = this;
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
        _mud_ImageSkin__set_d_image(self, value.ptr);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_left", {
    get: function() {
        var self = this.ptr;
        return _mud_ImageSkin__get_d_left(self);
    },
    set: function(value) {
        var self = this.ptr;
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
        _mud_ImageSkin__set_d_stretch(self, value);
    }
});
ImageSkin.prototype["__destroy__"] = ImageSkin.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ImageSkin__destroy(self);
};
// InkStyle
function InkStyle(a0) {
    ensureCache.prepare();
    if (a0 === undefined) { this.ptr = _mud_InkStyle__construct_0(); this.type = InkStyle; getCache(InkStyle)[this.ptr] = this; return; }
    this.ptr = _mud_InkStyle__construct_1(ensureString(/*name*/a0)); this.type = InkStyle; getCache(InkStyle)[this.ptr] = this;
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
        _mud_InkStyle__set_name(self, ensureString(value));
    }
});
Object.defineProperty(InkStyle.prototype, "empty", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_InkStyle__get_empty(self));
    },
    set: function(value) {
        var self = this.ptr;
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
        _mud_InkStyle__set_background_colour(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "border_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_border_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_border_colour(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "image_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_image_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_image_colour(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "text_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_text_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_text_colour(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "text_font", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_InkStyle__get_text_font(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_text_font(self, ensureString(value));
    }
});
Object.defineProperty(InkStyle.prototype, "text_size", {
    get: function() {
        var self = this.ptr;
        return _mud_InkStyle__get_text_size(self);
    },
    set: function(value) {
        var self = this.ptr;
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
        _mud_InkStyle__set_text_wrap(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "border_width", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_border_width(self), v4_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_border_width(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "corner_radius", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_corner_radius(self), v4_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_corner_radius(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "weak_corners", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_InkStyle__get_weak_corners(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_weak_corners(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "padding", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_padding(self), v4_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_padding(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "margin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_margin(self), v4_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_margin(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "align", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_align(self), v2_mud_Align);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_align(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "linear_gradient", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_linear_gradient(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_linear_gradient(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "linear_gradient_dim", {
    get: function() {
        var self = this.ptr;
        return _mud_InkStyle__get_linear_gradient_dim(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_linear_gradient_dim(self, value);
    }
});
Object.defineProperty(InkStyle.prototype, "stretch", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_stretch(self), v2_bool);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_stretch(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "image", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_image(self), Image);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_image(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "overlay", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_overlay(self), Image);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_overlay(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "tile", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_tile(self), Image);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_tile(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "image_skin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_image_skin(self), ImageSkin);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_image_skin(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "shadow", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_shadow(self), Shadow);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_shadow(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "shadow_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_shadow_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_shadow_colour(self, value.ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "hover_cursor", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InkStyle__get_hover_cursor(self), Style);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InkStyle__set_hover_cursor(self, value.ptr);
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
function Layout(a0) {
    ensureCache.prepare();
    if (a0 === undefined) { this.ptr = _mud_Layout__construct_0(); this.type = Layout; getCache(Layout)[this.ptr] = this; return; }
    this.ptr = _mud_Layout__construct_1(ensureString(/*name*/a0)); this.type = Layout; getCache(Layout)[this.ptr] = this;
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
        _mud_Layout__set_name(self, ensureString(value));
    }
});
Object.defineProperty(Layout.prototype, "solver", {
    get: function() {
        var self = this.ptr;
        return _mud_Layout__get_solver(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Layout__set_solver(self, value);
    }
});
Object.defineProperty(Layout.prototype, "layout", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_layout(self), v2_mud_AutoLayout);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Layout__set_layout(self, value.ptr);
    }
});
Object.defineProperty(Layout.prototype, "flow", {
    get: function() {
        var self = this.ptr;
        return _mud_Layout__get_flow(self);
    },
    set: function(value) {
        var self = this.ptr;
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
        _mud_Layout__set_space(self, value.ptr);
    }
});
Object.defineProperty(Layout.prototype, "clipping", {
    get: function() {
        var self = this.ptr;
        return _mud_Layout__get_clipping(self);
    },
    set: function(value) {
        var self = this.ptr;
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
        _mud_Layout__set_opacity(self, value);
    }
});
Object.defineProperty(Layout.prototype, "align", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_align(self), v2_mud_Align);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Layout__set_align(self, value.ptr);
    }
});
Object.defineProperty(Layout.prototype, "span", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_span(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Layout__set_span(self, value.ptr);
    }
});
Object.defineProperty(Layout.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_size(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Layout__set_size(self, value.ptr);
    }
});
Object.defineProperty(Layout.prototype, "padding", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_padding(self), v4_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Layout__set_padding(self, value.ptr);
    }
});
Object.defineProperty(Layout.prototype, "margin", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_margin(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Layout__set_margin(self, value.ptr);
    }
});
Object.defineProperty(Layout.prototype, "spacing", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_spacing(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Layout__set_spacing(self, value.ptr);
    }
});
Object.defineProperty(Layout.prototype, "pivot", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Layout__get_pivot(self), v2_mud_Pivot);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Layout__set_pivot(self, value.ptr);
    }
});
Object.defineProperty(Layout.prototype, "zorder", {
    get: function() {
        var self = this.ptr;
        return _mud_Layout__get_zorder(self);
    },
    set: function(value) {
        var self = this.ptr;
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
        _mud_Layout__set_updated(self, value);
    }
});
Layout.prototype["__destroy__"] = Layout.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Layout__destroy(self);
};
// NodeConnection
function NodeConnection() {
    this.ptr = _mud_NodeConnection__construct_0(); this.type = NodeConnection; getCache(NodeConnection)[this.ptr] = this;
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
    this.ptr = _mud_Paint__construct_0(); this.type = Paint; getCache(Paint)[this.ptr] = this;
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
        _mud_Paint__set_fill_colour(self, value.ptr);
    }
});
Object.defineProperty(Paint.prototype, "stroke_colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Paint__get_stroke_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Paint__set_stroke_colour(self, value.ptr);
    }
});
Object.defineProperty(Paint.prototype, "stroke_width", {
    get: function() {
        var self = this.ptr;
        return _mud_Paint__get_stroke_width(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Paint__set_stroke_width(self, value);
    }
});
Paint.prototype["__destroy__"] = Paint.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Paint__destroy(self);
};
// Shadow
function Shadow(a0, a1, a2, a3, a4) {
    if (a0 === undefined) { this.ptr = _mud_Shadow__construct_0(); this.type = Shadow; getCache(Shadow)[this.ptr] = this; return; }
    if (a4 === undefined) { this.ptr = _mud_Shadow__construct_4(/*xpos*/a0, /*ypos*/a1, /*blur*/a2, /*spread*/a3); this.type = Shadow; getCache(Shadow)[this.ptr] = this; return; }
    this.ptr = _mud_Shadow__construct_5(/*xpos*/a0, /*ypos*/a1, /*blur*/a2, /*spread*/a3, /*colour*/a4.ptr); this.type = Shadow; getCache(Shadow)[this.ptr] = this;
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
        _mud_Shadow__set_d_colour(self, value.ptr);
    }
});
Shadow.prototype["__destroy__"] = Shadow.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Shadow__destroy(self);
};
// Space
function Space() {
    this.ptr = _mud_Space__construct_0(); this.type = Space; getCache(Space)[this.ptr] = this;
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
        _mud_Style__set_base(self, value.ptr);
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
    this.ptr = _mud_TextCursor__construct_0(); this.type = TextCursor; getCache(TextCursor)[this.ptr] = this;
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
    this.ptr = _mud_TextMarker__construct_0(); this.type = TextMarker; getCache(TextMarker)[this.ptr] = this;
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
    this.ptr = _mud_TextPaint__construct_0(); this.type = TextPaint; getCache(TextPaint)[this.ptr] = this;
};
TextPaint.prototype = Object.create(WrapperObject.prototype);
TextPaint.prototype.constructor = TextPaint;
TextPaint.prototype.__class__ = TextPaint;
TextPaint.__cache__ = {};
Module['TextPaint'] = TextPaint;
Object.defineProperty(TextPaint.prototype, "font", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_TextPaint__get_font(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_TextPaint__set_font(self, ensureString(value));
    }
});
Object.defineProperty(TextPaint.prototype, "colour", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_TextPaint__get_colour(self), Colour);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_TextPaint__set_colour(self, value.ptr);
    }
});
Object.defineProperty(TextPaint.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return _mud_TextPaint__get_size(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_TextPaint__set_size(self, value);
    }
});
Object.defineProperty(TextPaint.prototype, "align", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_TextPaint__get_align(self), v2_mud_Align);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_TextPaint__set_align(self, value.ptr);
    }
});
Object.defineProperty(TextPaint.prototype, "text_break", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_TextPaint__get_text_break(self));
    },
    set: function(value) {
        var self = this.ptr;
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
        _mud_TextPaint__set_text_wrap(self, value);
    }
});
TextPaint.prototype["__destroy__"] = TextPaint.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TextPaint__destroy(self);
};
// TextSelection
function TextSelection() {
    this.ptr = _mud_TextSelection__construct_0(); this.type = TextSelection; getCache(TextSelection)[this.ptr] = this;
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
    this.ptr = _mud_UiRect__construct_0(); this.type = UiRect; getCache(UiRect)[this.ptr] = this;
};
UiRect.prototype = Object.create(WrapperObject.prototype);
UiRect.prototype.constructor = UiRect;
UiRect.prototype.__class__ = UiRect;
UiRect.__cache__ = {};
Module['UiRect'] = UiRect;
Object.defineProperty(UiRect.prototype, "position", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_UiRect__get_position(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_UiRect__set_position(self, value.ptr);
    }
});
Object.defineProperty(UiRect.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_UiRect__get_size(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_UiRect__set_size(self, value.ptr);
    }
});
Object.defineProperty(UiRect.prototype, "content", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_UiRect__get_content(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_UiRect__set_content(self, value.ptr);
    }
});
Object.defineProperty(UiRect.prototype, "span", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_UiRect__get_span(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_UiRect__set_span(self, value.ptr);
    }
});
Object.defineProperty(UiRect.prototype, "scale", {
    get: function() {
        var self = this.ptr;
        return _mud_UiRect__get_scale(self);
    },
    set: function(value) {
        var self = this.ptr;
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
// Widget
function Widget() { throw "cannot construct a Widget, no constructor in IDL" }
Widget.prototype = Object.create(WrapperObject.prototype);
Widget.prototype.constructor = Widget;
Widget.prototype.__class__ = Widget;
Widget.__cache__ = {};
Module['Widget'] = Widget;
Widget.prototype["focused"] = Widget.prototype.focused = function() {
    var self = this.ptr;
    return !!(_mud_Widget_focused_0(self));
};
Widget.prototype["hovered"] = Widget.prototype.hovered = function() {
    var self = this.ptr;
    return !!(_mud_Widget_hovered_0(self));
};
Widget.prototype["pressed"] = Widget.prototype.pressed = function() {
    var self = this.ptr;
    return !!(_mud_Widget_pressed_0(self));
};
Widget.prototype["activated"] = Widget.prototype.activated = function() {
    var self = this.ptr;
    return !!(_mud_Widget_activated_0(self));
};
Widget.prototype["selected"] = Widget.prototype.selected = function() {
    var self = this.ptr;
    return !!(_mud_Widget_selected_0(self));
};
Widget.prototype["modal"] = Widget.prototype.modal = function() {
    var self = this.ptr;
    return !!(_mud_Widget_modal_0(self));
};
Widget.prototype["closed"] = Widget.prototype.closed = function() {
    var self = this.ptr;
    return !!(_mud_Widget_closed_0(self));
};
Widget.prototype["ui_window"] = Widget.prototype.ui_window = function() {
    var self = this.ptr;
    return wrapPointer(_mud_Widget_ui_window_0(self), UiWindow);
};
Widget.prototype["ui"] = Widget.prototype.ui = function() {
    var self = this.ptr;
    return wrapPointer(_mud_Widget_ui_0(self), Ui);
};
Widget.prototype["parent_modal"] = Widget.prototype.parent_modal = function() {
    var self = this.ptr;
    return wrapPointer(_mud_Widget_parent_modal_0(self), Widget);
};
Widget.prototype["toggle_state"] = Widget.prototype.toggle_state = function(a0) {
    var self = this.ptr;
    _mud_Widget_toggle_state_1(self, /*state*/a0);
};
Widget.prototype["disable_state"] = Widget.prototype.disable_state = function(a0) {
    var self = this.ptr;
    _mud_Widget_disable_state_1(self, /*state*/a0);
};
Widget.prototype["set_state"] = Widget.prototype.set_state = function(a0, a1) {
    var self = this.ptr;
    _mud_Widget_set_state_2(self, /*state*/a0, /*enabled*/a1);
};
Widget.prototype["enable_state"] = Widget.prototype.enable_state = function(a0) {
    var self = this.ptr;
    _mud_Widget_enable_state_1(self, /*state*/a0);
};
Widget.prototype["clear_focus"] = Widget.prototype.clear_focus = function() {
    var self = this.ptr;
    _mud_Widget_clear_focus_0(self);
};
Widget.prototype["take_focus"] = Widget.prototype.take_focus = function() {
    var self = this.ptr;
    _mud_Widget_take_focus_0(self);
};
Widget.prototype["yield_focus"] = Widget.prototype.yield_focus = function() {
    var self = this.ptr;
    _mud_Widget_yield_focus_0(self);
};
Widget.prototype["take_modal"] = Widget.prototype.take_modal = function(a0) {
    var self = this.ptr;
    _mud_Widget_take_modal_1(self, /*device_filter*/a0);
};
Widget.prototype["yield_modal"] = Widget.prototype.yield_modal = function() {
    var self = this.ptr;
    _mud_Widget_yield_modal_0(self);
};
Widget.prototype["key_event"] = Widget.prototype.key_event = function(a0, a1, a2) {
    var self = this.ptr;
    if (a2 === undefined) { return wrapPointer(_mud_Widget_key_event_2(self, /*code*/a0, /*event_type*/a1), KeyEvent); }
    return wrapPointer(_mud_Widget_key_event_3(self, /*code*/a0, /*event_type*/a1, /*modifier*/a2), KeyEvent);
};
Widget.prototype["key_stroke"] = Widget.prototype.key_stroke = function(a0, a1) {
    var self = this.ptr;
    if (a1 === undefined) { return wrapPointer(_mud_Widget_key_stroke_1(self, /*code*/a0), KeyEvent); }
    return wrapPointer(_mud_Widget_key_stroke_2(self, /*code*/a0, /*modifier*/a1), KeyEvent);
};
Widget.prototype["char_stroke"] = Widget.prototype.char_stroke = function(a0, a1) {
    var self = this.ptr;
    if (a1 === undefined) { return wrapPointer(_mud_Widget_char_stroke_1(self, /*code*/a0), KeyEvent); }
    return wrapPointer(_mud_Widget_char_stroke_2(self, /*code*/a0, /*modifier*/a1), KeyEvent);
};
Widget.prototype["mouse_event"] = Widget.prototype.mouse_event = function(a0, a1, a2, a3) {
    var self = this.ptr;
    if (a2 === undefined) { return wrapPointer(_mud_Widget_mouse_event_2(self, /*device*/a0, /*event_type*/a1), MouseEvent); }
    if (a3 === undefined) { return wrapPointer(_mud_Widget_mouse_event_3(self, /*device*/a0, /*event_type*/a1, /*modifier*/a2), MouseEvent); }
    return wrapPointer(_mud_Widget_mouse_event_4(self, /*device*/a0, /*event_type*/a1, /*modifier*/a2, /*consume*/a3), MouseEvent);
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
        _mud_Widget__set_body(self, value.ptr);
    }
});
Widget.prototype["__destroy__"] = Widget.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Widget__destroy(self);
};
// v2<mud::Align>
function v2_mud_Align(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_v2_mud_Align__construct_0(); this.type = v2_mud_Align; getCache(v2_mud_Align)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v2_mud_Align__construct_1(/*v*/a0); this.type = v2_mud_Align; getCache(v2_mud_Align)[this.ptr] = this; return; }
    this.ptr = _mud_v2_mud_Align__construct_2(/*x*/a0, /*y*/a1); this.type = v2_mud_Align; getCache(v2_mud_Align)[this.ptr] = this;
};
v2_mud_Align.prototype = Object.create(WrapperObject.prototype);
v2_mud_Align.prototype.constructor = v2_mud_Align;
v2_mud_Align.prototype.__class__ = v2_mud_Align;
v2_mud_Align.__cache__ = {};
Module['v2_mud_Align'] = v2_mud_Align;
Object.defineProperty(v2_mud_Align.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_mud_Align__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v2_mud_Align__set_x(self, value);
    }
});
Object.defineProperty(v2_mud_Align.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_mud_Align__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v2_mud_Align__set_y(self, value);
    }
});
v2_mud_Align.prototype["__destroy__"] = v2_mud_Align.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v2_mud_Align__destroy(self);
};
// v2<mud::AutoLayout>
function v2_mud_AutoLayout(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_v2_mud_AutoLayout__construct_0(); this.type = v2_mud_AutoLayout; getCache(v2_mud_AutoLayout)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v2_mud_AutoLayout__construct_1(/*v*/a0); this.type = v2_mud_AutoLayout; getCache(v2_mud_AutoLayout)[this.ptr] = this; return; }
    this.ptr = _mud_v2_mud_AutoLayout__construct_2(/*x*/a0, /*y*/a1); this.type = v2_mud_AutoLayout; getCache(v2_mud_AutoLayout)[this.ptr] = this;
};
v2_mud_AutoLayout.prototype = Object.create(WrapperObject.prototype);
v2_mud_AutoLayout.prototype.constructor = v2_mud_AutoLayout;
v2_mud_AutoLayout.prototype.__class__ = v2_mud_AutoLayout;
v2_mud_AutoLayout.__cache__ = {};
Module['v2_mud_AutoLayout'] = v2_mud_AutoLayout;
Object.defineProperty(v2_mud_AutoLayout.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_mud_AutoLayout__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v2_mud_AutoLayout__set_x(self, value);
    }
});
Object.defineProperty(v2_mud_AutoLayout.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_mud_AutoLayout__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v2_mud_AutoLayout__set_y(self, value);
    }
});
v2_mud_AutoLayout.prototype["__destroy__"] = v2_mud_AutoLayout.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v2_mud_AutoLayout__destroy(self);
};
// v2<mud::Pivot>
function v2_mud_Pivot(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_v2_mud_Pivot__construct_0(); this.type = v2_mud_Pivot; getCache(v2_mud_Pivot)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v2_mud_Pivot__construct_1(/*v*/a0); this.type = v2_mud_Pivot; getCache(v2_mud_Pivot)[this.ptr] = this; return; }
    this.ptr = _mud_v2_mud_Pivot__construct_2(/*x*/a0, /*y*/a1); this.type = v2_mud_Pivot; getCache(v2_mud_Pivot)[this.ptr] = this;
};
v2_mud_Pivot.prototype = Object.create(WrapperObject.prototype);
v2_mud_Pivot.prototype.constructor = v2_mud_Pivot;
v2_mud_Pivot.prototype.__class__ = v2_mud_Pivot;
v2_mud_Pivot.__cache__ = {};
Module['v2_mud_Pivot'] = v2_mud_Pivot;
Object.defineProperty(v2_mud_Pivot.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_mud_Pivot__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v2_mud_Pivot__set_x(self, value);
    }
});
Object.defineProperty(v2_mud_Pivot.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_mud_Pivot__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v2_mud_Pivot__set_y(self, value);
    }
});
v2_mud_Pivot.prototype["__destroy__"] = v2_mud_Pivot.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v2_mud_Pivot__destroy(self);
};
// v2<mud::Sizing>
function v2_mud_Sizing(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_v2_mud_Sizing__construct_0(); this.type = v2_mud_Sizing; getCache(v2_mud_Sizing)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v2_mud_Sizing__construct_1(/*v*/a0); this.type = v2_mud_Sizing; getCache(v2_mud_Sizing)[this.ptr] = this; return; }
    this.ptr = _mud_v2_mud_Sizing__construct_2(/*x*/a0, /*y*/a1); this.type = v2_mud_Sizing; getCache(v2_mud_Sizing)[this.ptr] = this;
};
v2_mud_Sizing.prototype = Object.create(WrapperObject.prototype);
v2_mud_Sizing.prototype.constructor = v2_mud_Sizing;
v2_mud_Sizing.prototype.__class__ = v2_mud_Sizing;
v2_mud_Sizing.__cache__ = {};
Module['v2_mud_Sizing'] = v2_mud_Sizing;
Object.defineProperty(v2_mud_Sizing.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_mud_Sizing__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v2_mud_Sizing__set_x(self, value);
    }
});
Object.defineProperty(v2_mud_Sizing.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_mud_Sizing__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v2_mud_Sizing__set_y(self, value);
    }
});
v2_mud_Sizing.prototype["__destroy__"] = v2_mud_Sizing.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v2_mud_Sizing__destroy(self);
};
// v2<size_t>
function v2_size_t(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_v2_size_t__construct_0(); this.type = v2_size_t; getCache(v2_size_t)[this.ptr] = this; return; }
    if (a1 === undefined) { this.ptr = _mud_v2_size_t__construct_1(/*v*/a0); this.type = v2_size_t; getCache(v2_size_t)[this.ptr] = this; return; }
    this.ptr = _mud_v2_size_t__construct_2(/*x*/a0, /*y*/a1); this.type = v2_size_t; getCache(v2_size_t)[this.ptr] = this;
};
v2_size_t.prototype = Object.create(WrapperObject.prototype);
v2_size_t.prototype.constructor = v2_size_t;
v2_size_t.prototype.__class__ = v2_size_t;
v2_size_t.__cache__ = {};
Module['v2_size_t'] = v2_size_t;
Object.defineProperty(v2_size_t.prototype, "x", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_size_t__get_x(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v2_size_t__set_x(self, value);
    }
});
Object.defineProperty(v2_size_t.prototype, "y", {
    get: function() {
        var self = this.ptr;
        return _mud_v2_size_t__get_y(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_v2_size_t__set_y(self, value);
    }
});
v2_size_t.prototype["__destroy__"] = v2_size_t.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_v2_size_t__destroy(self);
};
// Canvas
function Canvas() { throw "cannot construct a Canvas, no constructor in IDL" }
Canvas.prototype = Object.create(Widget.prototype);
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
Dockable.prototype = Object.create(Widget.prototype);
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
Docker.prototype = Object.create(Widget.prototype);
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
Dockbar.prototype = Object.create(Docker.prototype);
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
Dockspace.prototype = Object.create(Docker.prototype);
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
Expandbox.prototype = Object.create(Widget.prototype);
Expandbox.prototype.constructor = Expandbox;
Expandbox.prototype.__class__ = Expandbox;
Expandbox.__cache__ = {};
Module['Expandbox'] = Expandbox;
Expandbox.prototype["__destroy__"] = Expandbox.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Expandbox__destroy(self);
};
// Frame
function Frame() { throw "cannot construct a Frame, no constructor in IDL" }
Frame.prototype = Object.create(UiRect.prototype);
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
FrameSolver.prototype = Object.create(UiRect.prototype);
FrameSolver.prototype.constructor = FrameSolver;
FrameSolver.prototype.__class__ = FrameSolver;
FrameSolver.__cache__ = {};
Module['FrameSolver'] = FrameSolver;
FrameSolver.prototype["__destroy__"] = FrameSolver.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FrameSolver__destroy(self);
};
// RowSolver
function RowSolver() { throw "cannot construct a RowSolver, no constructor in IDL" }
RowSolver.prototype = Object.create(FrameSolver.prototype);
RowSolver.prototype.constructor = RowSolver;
RowSolver.prototype.__class__ = RowSolver;
RowSolver.__cache__ = {};
Module['RowSolver'] = RowSolver;
RowSolver.prototype["__destroy__"] = RowSolver.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_RowSolver__destroy(self);
};
// LineSolver
function LineSolver() { throw "cannot construct a LineSolver, no constructor in IDL" }
LineSolver.prototype = Object.create(RowSolver.prototype);
LineSolver.prototype.constructor = LineSolver;
LineSolver.prototype.__class__ = LineSolver;
LineSolver.__cache__ = {};
Module['LineSolver'] = LineSolver;
LineSolver.prototype["__destroy__"] = LineSolver.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_LineSolver__destroy(self);
};
// Node
function Node() { throw "cannot construct a Node, no constructor in IDL" }
Node.prototype = Object.create(Widget.prototype);
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
NodePlug.prototype = Object.create(Widget.prototype);
NodePlug.prototype.constructor = NodePlug;
NodePlug.prototype.__class__ = NodePlug;
NodePlug.__cache__ = {};
Module['NodePlug'] = NodePlug;
NodePlug.prototype["__destroy__"] = NodePlug.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_NodePlug__destroy(self);
};
// ScrollSheet
function ScrollSheet() { throw "cannot construct a ScrollSheet, no constructor in IDL" }
ScrollSheet.prototype = Object.create(Widget.prototype);
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
Sequence.prototype = Object.create(Widget.prototype);
Sequence.prototype.constructor = Sequence;
Sequence.prototype.__class__ = Sequence;
Sequence.__cache__ = {};
Module['ui']['Sequence'] = Sequence;
Sequence.prototype["__destroy__"] = Sequence.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ui_Sequence__destroy(self);
};
// Tabber
function Tabber() { throw "cannot construct a Tabber, no constructor in IDL" }
Tabber.prototype = Object.create(Widget.prototype);
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
Table.prototype = Object.create(Widget.prototype);
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
TextEdit.prototype = Object.create(Widget.prototype);
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
TreeNode.prototype = Object.create(Widget.prototype);
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
Ui.prototype = Object.create(Widget.prototype);
Ui.prototype.constructor = Ui;
Ui.prototype.__class__ = Ui;
Ui.__cache__ = {};
Module['Ui'] = Ui;
Ui.prototype["begin"] = Ui.prototype.begin = function() {
    var self = this.ptr;
    return wrapPointer(_mud_Ui_begin_0(self), Widget);
};
Ui.prototype["__destroy__"] = Ui.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ui__destroy(self);
};
// Window
function Window() { throw "cannot construct a Window, no constructor in IDL" }
Window.prototype = Object.create(Dockable.prototype);
Window.prototype.constructor = Window;
Window.prototype.__class__ = Window;
Window.__cache__ = {};
Module['Window'] = Window;
Window.prototype["__destroy__"] = Window.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Window__destroy(self);
};
Module['ui']['widget'] = function(a0, a1, a2, a3, a4) {
    if (a2 === undefined) { return wrapPointer(_mud_ui_widget_2(/*parent*/a0.ptr, /*style*/a1.ptr), Widget); }
    if (a3 === undefined) { return wrapPointer(_mud_ui_widget_3(/*parent*/a0.ptr, /*style*/a1.ptr, /*open*/a2), Widget); }
    if (a4 === undefined) { return wrapPointer(_mud_ui_widget_4(/*parent*/a0.ptr, /*style*/a1.ptr, /*open*/a2, /*length*/a3), Widget); }
    return wrapPointer(_mud_ui_widget_5(/*parent*/a0.ptr, /*style*/a1.ptr, /*open*/a2, /*length*/a3, /*index*/a4.ptr), Widget);
};
Module['ui']['item'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_ui_item_2(/*parent*/a0.ptr, /*style*/a1.ptr), Widget); }
    return wrapPointer(_mud_ui_item_3(/*parent*/a0.ptr, /*style*/a1.ptr, ensureString(/*content*/a2)), Widget);
};
Module['ui']['spanner'] = function(a0, a1, a2, a3) {
    return wrapPointer(_mud_ui_spanner_4(/*parent*/a0.ptr, /*style*/a1.ptr, /*dim*/a2, /*span*/a3), Widget);
};
Module['ui']['spacer'] = function(a0) {
    return wrapPointer(_mud_ui_spacer_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['icon'] = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_icon_2(/*parent*/a0.ptr, ensureString(/*image*/a1)), Widget);
};
Module['ui']['label'] = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_label_2(/*parent*/a0.ptr, ensureString(/*label*/a1)), Widget);
};
Module['ui']['title'] = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_title_2(/*parent*/a0.ptr, ensureString(/*label*/a1)), Widget);
};
Module['ui']['message'] = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_message_2(/*parent*/a0.ptr, ensureString(/*label*/a1)), Widget);
};
Module['ui']['text'] = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_text_2(/*parent*/a0.ptr, ensureString(/*label*/a1)), Widget);
};
Module['ui']['button'] = function(a0, a1) {
    ensureCache.prepare();
    if (a1 === undefined) { return wrapPointer(_mud_ui_button_1(/*parent*/a0.ptr), Widget); }
    return wrapPointer(_mud_ui_button_2(/*parent*/a0.ptr, ensureString(/*content*/a1)), Widget);
};
Module['ui']['toggle'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_ui_toggle_2(/*parent*/a0.ptr, /*on*/a1), Widget); }
    return wrapPointer(_mud_ui_toggle_3(/*parent*/a0.ptr, /*on*/a1, ensureString(/*content*/a2)), Widget);
};
Module['ui']['modal_button'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    return !!(_mud_ui_modal_button_4(/*screen*/a0.ptr, /*parent*/a1.ptr, ensureString(/*content*/a2), /*mode*/a3));
};
Module['ui']['checkbox'] = function(a0, a1) {
    return wrapPointer(_mud_ui_checkbox_2(/*parent*/a0.ptr, /*on*/a1), Widget);
};
Module['ui']['fill_bar'] = function(a0, a1, a2) {
    if (a2 === undefined) { return wrapPointer(_mud_ui_fill_bar_2(/*parent*/a0.ptr, /*percentage*/a1), Widget); }
    return wrapPointer(_mud_ui_fill_bar_3(/*parent*/a0.ptr, /*percentage*/a1, /*dim*/a2), Widget);
};
Module['ui']['image256'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a3 === undefined) { return wrapPointer(_mud_ui_image256_3(/*parent*/a0.ptr, ensureString(/*name*/a1), /*source*/a2.ptr), Widget); }
    return wrapPointer(_mud_ui_image256_4(/*parent*/a0.ptr, ensureString(/*name*/a1), /*source*/a2.ptr, /*size*/a3.ptr), Widget);
};
Module['ui']['radio_choice'] = function(a0, a1, a2) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_radio_choice_3(/*parent*/a0.ptr, ensureString(/*value*/a1), /*active*/a2), Widget);
};
Module['ui']['dropdown'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a4 === undefined) { return wrapPointer(_mud_ui_dropdown_4(/*parent*/a0.ptr, /*style*/a1.ptr, ensureString(/*value*/a2), /*flags*/a3), Widget); }
    return wrapPointer(_mud_ui_dropdown_5(/*parent*/a0.ptr, /*style*/a1.ptr, ensureString(/*value*/a2), /*flags*/a3, /*list_style*/a4.ptr), Widget);
};
Module['ui']['menu_choice'] = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_menu_choice_2(/*parent*/a0.ptr, ensureString(/*content*/a1)), Widget);
};
Module['ui']['menu'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_ui_menu_2(/*parent*/a0.ptr, ensureString(/*label*/a1)), Widget); }
    return wrapPointer(_mud_ui_menu_3(/*parent*/a0.ptr, ensureString(/*label*/a1), /*submenu*/a2), Widget);
};
Module['ui']['menubar'] = function(a0) {
    return wrapPointer(_mud_ui_menubar_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['toolbutton'] = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_toolbutton_2(/*parent*/a0.ptr, ensureString(/*icon*/a1)), Widget);
};
Module['ui']['tooldock'] = function(a0) {
    return wrapPointer(_mud_ui_tooldock_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['toolbar'] = function(a0, a1) {
    if (a1 === undefined) { return wrapPointer(_mud_ui_toolbar_1(/*parent*/a0.ptr), Widget); }
    return wrapPointer(_mud_ui_toolbar_2(/*parent*/a0.ptr, /*wrap*/a1), Widget);
};
Module['ui']['select_list'] = function(a0) {
    return wrapPointer(_mud_ui_select_list_1(/*parent*/a0.ptr), ScrollSheet);
};
Module['ui']['table_row'] = function(a0) {
    return wrapPointer(_mud_ui_table_row_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['table_separator'] = function(a0) {
    return wrapPointer(_mud_ui_table_separator_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['expandbox'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_ui_expandbox_2(/*parent*/a0.ptr, ensureString(/*name*/a1)), Expandbox); }
    return wrapPointer(_mud_ui_expandbox_3(/*parent*/a0.ptr, ensureString(/*name*/a1), /*open*/a2), Expandbox);
};
Module['ui']['tree_node'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_ui_tree_node_2(/*parent*/a0.ptr, ensureString(/*name*/a1)), TreeNode); }
    if (a3 === undefined) { return wrapPointer(_mud_ui_tree_node_3(/*parent*/a0.ptr, ensureString(/*name*/a1), /*leaf*/a2), TreeNode); }
    return wrapPointer(_mud_ui_tree_node_4(/*parent*/a0.ptr, ensureString(/*name*/a1), /*leaf*/a2, /*open*/a3), TreeNode);
};
Module['ui']['tree'] = function(a0) {
    return wrapPointer(_mud_ui_tree_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['tab'] = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_tab_2(/*tabber*/a0.ptr, ensureString(/*name*/a1)), Widget);
};
Module['ui']['tabber'] = function(a0) {
    return wrapPointer(_mud_ui_tabber_1(/*parent*/a0.ptr), Tabber);
};
Module['ui']['row'] = function(a0) {
    return wrapPointer(_mud_ui_row_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['header'] = function(a0) {
    return wrapPointer(_mud_ui_header_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['div'] = function(a0) {
    return wrapPointer(_mud_ui_div_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['stack'] = function(a0) {
    return wrapPointer(_mud_ui_stack_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['sheet'] = function(a0) {
    return wrapPointer(_mud_ui_sheet_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['board'] = function(a0) {
    return wrapPointer(_mud_ui_board_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['layout'] = function(a0) {
    return wrapPointer(_mud_ui_layout_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['screen'] = function(a0) {
    return wrapPointer(_mud_ui_screen_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['decal'] = function(a0) {
    return wrapPointer(_mud_ui_decal_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['overlay'] = function(a0) {
    return wrapPointer(_mud_ui_overlay_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['title_header'] = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_title_header_2(/*parent*/a0.ptr, ensureString(/*title*/a1)), Widget);
};
Module['ui']['dummy'] = function(a0, a1) {
    return wrapPointer(_mud_ui_dummy_2(/*parent*/a0.ptr, /*size*/a1.ptr), Widget);
};
Module['ui']['popup'] = function(a0, a1) {
    return wrapPointer(_mud_ui_popup_2(/*parent*/a0.ptr, /*flags*/a1), Widget);
};
Module['ui']['popup_at'] = function(a0, a1, a2) {
    if (a2 === undefined) { return wrapPointer(_mud_ui_popup_at_2(/*parent*/a0.ptr, /*position*/a1.ptr), Widget); }
    return wrapPointer(_mud_ui_popup_at_3(/*parent*/a0.ptr, /*position*/a1.ptr, /*flags*/a2), Widget);
};
Module['ui']['modal'] = function(a0, a1) {
    if (a1 === undefined) { return wrapPointer(_mud_ui_modal_1(/*parent*/a0.ptr), Widget); }
    return wrapPointer(_mud_ui_modal_2(/*parent*/a0.ptr, /*size*/a1.ptr), Widget);
};
Module['ui']['auto_modal'] = function(a0, a1, a2) {
    if (a2 === undefined) { return wrapPointer(_mud_ui_auto_modal_2(/*parent*/a0.ptr, /*mode*/a1), Widget); }
    return wrapPointer(_mud_ui_auto_modal_3(/*parent*/a0.ptr, /*mode*/a1, /*size*/a2.ptr), Widget);
};
Module['ui']['context'] = function(a0, a1, a2) {
    if (a2 === undefined) { return wrapPointer(_mud_ui_context_2(/*parent*/a0.ptr, /*mode*/a1), Widget); }
    return wrapPointer(_mud_ui_context_3(/*parent*/a0.ptr, /*mode*/a1, /*flags*/a2), Widget);
};
Module['ui']['hoverbox'] = function(a0, a1) {
    if (a1 === undefined) { return wrapPointer(_mud_ui_hoverbox_1(/*parent*/a0.ptr), Widget); }
    return wrapPointer(_mud_ui_hoverbox_2(/*parent*/a0.ptr, /*delay*/a1), Widget);
};
Module['ui']['tooltip'] = function(a0, a1, a2) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_tooltip_3(/*parent*/a0.ptr, /*position*/a1.ptr, ensureString(/*content*/a2)), Widget);
};
Module['ui']['cursor'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { return wrapPointer(_mud_ui_cursor_3(/*parent*/a0.ptr, /*position*/a1.ptr, /*hovered*/a2.ptr), Widget); }
    return wrapPointer(_mud_ui_cursor_4(/*parent*/a0.ptr, /*position*/a1.ptr, /*hovered*/a2.ptr, /*locked*/a3), Widget);
};
Module['ui']['rectangle'] = function(a0, a1) {
    return wrapPointer(_mud_ui_rectangle_2(/*parent*/a0.ptr, /*rect*/a1.ptr), Widget);
};
Module['ui']['dockspace'] = function(a0, a1) {
    return wrapPointer(_mud_ui_dockspace_2(/*parent*/a0.ptr, /*docksystem*/a1.ptr), Dockspace);
};
Module['ui']['dockbar'] = function(a0, a1) {
    return wrapPointer(_mud_ui_dockbar_2(/*parent*/a0.ptr, /*docksystem*/a1.ptr), Dockbar);
};
Module['ui']['dockitem'] = function(a0, a1, a2) {
    return wrapPointer(_mud_ui_dockitem_3(/*parent*/a0.ptr, /*docksystem*/a1.ptr, /*dock*/a2.ptr), Widget);
};
Module['ui']['drag_float'] = function(a0, a1, a2) {
    if (a2 === undefined) { return !!(_mud_ui_drag_float_2(/*parent*/a0.ptr, /*value*/a1)); }
    return !!(_mud_ui_drag_float_3(/*parent*/a0.ptr, /*value*/a1, /*step*/a2));
};
Module['ui']['vec2_edit'] = function(a0, a1) {
    return !!(_mud_ui_vec2_edit_2(/*parent*/a0.ptr, /*vec*/a1.ptr));
};
Module['ui']['vec3_edit'] = function(a0, a1) {
    return !!(_mud_ui_vec3_edit_2(/*parent*/a0.ptr, /*vec*/a1.ptr));
};
Module['ui']['quat_edit'] = function(a0, a1) {
    return !!(_mud_ui_quat_edit_2(/*parent*/a0.ptr, /*quat*/a1.ptr));
};
Module['ui']['color_edit_hsl'] = function(a0, a1, a2) {
    return !!(_mud_ui_color_edit_hsl_3(/*parent*/a0.ptr, /*colour*/a1.ptr, /*value*/a2.ptr));
};
Module['ui']['color_display'] = function(a0, a1) {
    return wrapPointer(_mud_ui_color_display_2(/*parent*/a0.ptr, /*value*/a1.ptr), Widget);
};
Module['ui']['color_edit'] = function(a0, a1) {
    return !!(_mud_ui_color_edit_2(/*parent*/a0.ptr, /*value*/a1.ptr));
};
Module['ui']['color_edit_simple'] = function(a0, a1) {
    return !!(_mud_ui_color_edit_simple_2(/*parent*/a0.ptr, /*value*/a1.ptr));
};
Module['ui']['color_toggle_edit'] = function(a0, a1) {
    return !!(_mud_ui_color_toggle_edit_2(/*parent*/a0.ptr, /*value*/a1.ptr));
};
Module['ui']['flag_field'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a4 === undefined) { return !!(_mud_ui_flag_field_4(/*parent*/a0.ptr, ensureString(/*name*/a1), /*value*/a2, /*shift*/a3)); }
    return !!(_mud_ui_flag_field_5(/*parent*/a0.ptr, ensureString(/*name*/a1), /*value*/a2, /*shift*/a3, /*reverse*/a4));
};
Module['ui']['color_field'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a3 === undefined) { return !!(_mud_ui_color_field_3(/*parent*/a0.ptr, ensureString(/*name*/a1), /*value*/a2.ptr)); }
    return !!(_mud_ui_color_field_4(/*parent*/a0.ptr, ensureString(/*name*/a1), /*value*/a2.ptr, /*reverse*/a3));
};
Module['ui']['color_display_field'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a3 === undefined) { _mud_ui_color_display_field_3(/*parent*/a0.ptr, ensureString(/*name*/a1), /*value*/a2.ptr); return; }
    _mud_ui_color_display_field_4(/*parent*/a0.ptr, ensureString(/*name*/a1), /*value*/a2.ptr, /*reverse*/a3);
};
Module['ui']['node_input'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_ui_node_input_2(/*node*/a0.ptr, ensureString(/*name*/a1)), NodePlug); }
    if (a3 === undefined) { return wrapPointer(_mud_ui_node_input_3(/*node*/a0.ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2)), NodePlug); }
    if (a4 === undefined) { return wrapPointer(_mud_ui_node_input_4(/*node*/a0.ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2), /*colour*/a3.ptr), NodePlug); }
    if (a5 === undefined) { return wrapPointer(_mud_ui_node_input_5(/*node*/a0.ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2), /*colour*/a3.ptr, /*active*/a4), NodePlug); }
    return wrapPointer(_mud_ui_node_input_6(/*node*/a0.ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2), /*colour*/a3.ptr, /*active*/a4, /*connected*/a5), NodePlug);
};
Module['ui']['node_output'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_ui_node_output_2(/*node*/a0.ptr, ensureString(/*name*/a1)), NodePlug); }
    if (a3 === undefined) { return wrapPointer(_mud_ui_node_output_3(/*node*/a0.ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2)), NodePlug); }
    if (a4 === undefined) { return wrapPointer(_mud_ui_node_output_4(/*node*/a0.ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2), /*colour*/a3.ptr), NodePlug); }
    if (a5 === undefined) { return wrapPointer(_mud_ui_node_output_5(/*node*/a0.ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2), /*colour*/a3.ptr, /*active*/a4), NodePlug); }
    return wrapPointer(_mud_ui_node_output_6(/*node*/a0.ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2), /*colour*/a3.ptr, /*active*/a4, /*connected*/a5), NodePlug);
};
Module['ui']['node'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a3 === undefined) { return wrapPointer(_mud_ui_node_3(/*parent*/a0.ptr, ensureString(/*title*/a1), /*position*/a2.ptr), Node); }
    if (a4 === undefined) { return wrapPointer(_mud_ui_node_4(/*parent*/a0.ptr, ensureString(/*title*/a1), /*position*/a2.ptr, /*order*/a3), Node); }
    return wrapPointer(_mud_ui_node_5(/*parent*/a0.ptr, ensureString(/*title*/a1), /*position*/a2.ptr, /*order*/a3, ensureRef(/*identity*/a4), ensureRefType(/*identity*/a4)), Node);
};
Module['ui']['node_cable'] = function(a0, a1, a2) {
    return wrapPointer(_mud_ui_node_cable_3(/*canvas*/a0.ptr, /*plug_out*/a1.ptr, /*plug_in*/a2.ptr), Widget);
};
Module['ui']['canvas'] = function(a0, a1) {
    if (a1 === undefined) { return wrapPointer(_mud_ui_canvas_1(/*parent*/a0.ptr), Canvas); }
    return wrapPointer(_mud_ui_canvas_2(/*parent*/a0.ptr, /*num_nodes*/a1), Canvas);
};
Module['ui']['scrollable'] = function(a0) {
    return wrapPointer(_mud_ui_scrollable_1(/*parent*/a0.ptr), Widget);
};
Module['ui']['sequence'] = function(a0) {
    return wrapPointer(_mud_ui_sequence_1(/*parent*/a0.ptr), Sequence);
};
Module['ui']['scroll_sequence'] = function(a0) {
    return wrapPointer(_mud_ui_scroll_sequence_1(/*parent*/a0.ptr), Sequence);
};
Module['ui']['select_logic'] = function(a0, a1, a2) {
    return !!(_mud_ui_select_logic_3(/*element*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1), ensureRef(/*selection*/a2), ensureRefType(/*selection*/a2)));
};
Module['ui']['element'] = function(a0, a1) {
    return wrapPointer(_mud_ui_element_2(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)), Widget);
};
Module['ui']['sequence_element'] = function(a0, a1) {
    return wrapPointer(_mud_ui_sequence_element_2(/*parent*/a0.ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)), Widget);
};
Module['ui']['window'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { return wrapPointer(_mud_ui_window_2(/*parent*/a0.ptr, ensureString(/*title*/a1)), Window); }
    return wrapPointer(_mud_ui_window_3(/*parent*/a0.ptr, ensureString(/*title*/a1), /*state*/a2), Window);
};
Module['ui']['dir_item'] = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_dir_item_2(/*parent*/a0.ptr, ensureString(/*name*/a1)), Widget);
};
Module['ui']['file_item'] = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_file_item_2(/*parent*/a0.ptr, ensureString(/*name*/a1)), Widget);
};
Module['ui']['dir_node'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_dir_node_4(/*parent*/a0.ptr, ensureString(/*path*/a1), ensureString(/*name*/a2), /*collapsed*/a3), Widget);
};
Module['ui']['file_node'] = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_file_node_2(/*parent*/a0.ptr, ensureString(/*name*/a1)), Widget);
};
Module['ui']['file_tree'] = function(a0, a1) {
    ensureCache.prepare();
    return wrapPointer(_mud_ui_file_tree_2(/*parent*/a0.ptr, ensureString(/*path*/a1)), Widget);
};

(function() {
    function setup() {
        CanvasConnect.__type__ = _mud_CanvasConnect__type();
        Clipboard.__type__ = _mud_Clipboard__type();
        Dock.__type__ = _mud_Dock__type();
        Docksystem.__type__ = _mud_Docksystem__type();
        Gradient.__type__ = _mud_Gradient__type();
        GridSolver.__type__ = _mud_GridSolver__type();
        ImageSkin.__type__ = _mud_ImageSkin__type();
        InkStyle.__type__ = _mud_InkStyle__type();
        Layer.__type__ = _mud_Layer__type();
        Layout.__type__ = _mud_Layout__type();
        NodeConnection.__type__ = _mud_NodeConnection__type();
        Paint.__type__ = _mud_Paint__type();
        Shadow.__type__ = _mud_Shadow__type();
        Space.__type__ = _mud_Space__type();
        Style.__type__ = _mud_Style__type();
        TableSolver.__type__ = _mud_TableSolver__type();
        Text.__type__ = _mud_Text__type();
        TextCursor.__type__ = _mud_TextCursor__type();
        TextMarker.__type__ = _mud_TextMarker__type();
        TextPaint.__type__ = _mud_TextPaint__type();
        TextSelection.__type__ = _mud_TextSelection__type();
        UiRect.__type__ = _mud_UiRect__type();
        UiWindow.__type__ = _mud_UiWindow__type();
        User.__type__ = _mud_User__type();
        Vg.__type__ = _mud_Vg__type();
        Widget.__type__ = _mud_Widget__type();
        Canvas.__type__ = _mud_Canvas__type();
        Dockable.__type__ = _mud_Dockable__type();
        Docker.__type__ = _mud_Docker__type();
        Dockbar.__type__ = _mud_Dockbar__type();
        Dockspace.__type__ = _mud_Dockspace__type();
        Expandbox.__type__ = _mud_Expandbox__type();
        Frame.__type__ = _mud_Frame__type();
        FrameSolver.__type__ = _mud_FrameSolver__type();
        RowSolver.__type__ = _mud_RowSolver__type();
        LineSolver.__type__ = _mud_LineSolver__type();
        Node.__type__ = _mud_Node__type();
        NodePlug.__type__ = _mud_NodePlug__type();
        ScrollSheet.__type__ = _mud_ScrollSheet__type();
        Sequence.__type__ = _mud_ui_Sequence__type();
        Tabber.__type__ = _mud_Tabber__type();
        Table.__type__ = _mud_Table__type();
        TextEdit.__type__ = _mud_TextEdit__type();
        TreeNode.__type__ = _mud_TreeNode__type();
        Ui.__type__ = _mud_Ui__type();
        Window.__type__ = _mud_Window__type();
        // Align
        Module['Align'] = Module['Align'] || {};
        Module['Align']['Left'] = _mud_Align_Left();
        Module['Align']['Center'] = _mud_Align_Center();
        Module['Align']['Right'] = _mud_Align_Right();
        Module['Align']['OutLeft'] = _mud_Align_OutLeft();
        Module['Align']['OutRight'] = _mud_Align_OutRight();
        Module['Align']['Count'] = _mud_Align_Count();
        // AutoLayout
        Module['AutoLayout'] = Module['AutoLayout'] || {};
        Module['AutoLayout']['None'] = _mud_AutoLayout_None();
        Module['AutoLayout']['Size'] = _mud_AutoLayout_Size();
        Module['AutoLayout']['Layout'] = _mud_AutoLayout_Layout();
        // Clip
        Module['Clip'] = Module['Clip'] || {};
        Module['Clip']['None'] = _mud_Clip_None();
        Module['Clip']['Clip'] = _mud_Clip_Clip();
        Module['Clip']['Unclip'] = _mud_Clip_Unclip();
        // FlowAxis
        Module['FlowAxis'] = Module['FlowAxis'] || {};
        Module['FlowAxis']['Reading'] = _mud_FlowAxis_Reading();
        Module['FlowAxis']['Paragraph'] = _mud_FlowAxis_Paragraph();
        Module['FlowAxis']['Same'] = _mud_FlowAxis_Same();
        Module['FlowAxis']['Flip'] = _mud_FlowAxis_Flip();
        Module['FlowAxis']['None'] = _mud_FlowAxis_None();
        // LayoutFlow
        Module['LayoutFlow'] = Module['LayoutFlow'] || {};
        Module['LayoutFlow']['Flow'] = _mud_LayoutFlow_Flow();
        Module['LayoutFlow']['Overlay'] = _mud_LayoutFlow_Overlay();
        Module['LayoutFlow']['Align'] = _mud_LayoutFlow_Align();
        Module['LayoutFlow']['Free'] = _mud_LayoutFlow_Free();
        // Opacity
        Module['Opacity'] = Module['Opacity'] || {};
        Module['Opacity']['Opaque'] = _mud_Opacity_Opaque();
        Module['Opacity']['Clear'] = _mud_Opacity_Clear();
        Module['Opacity']['Hollow'] = _mud_Opacity_Hollow();
        // Pivot
        Module['Pivot'] = Module['Pivot'] || {};
        Module['Pivot']['Forward'] = _mud_Pivot_Forward();
        Module['Pivot']['Reverse'] = _mud_Pivot_Reverse();
        // PopupFlags
        Module['ui']['PopupFlags'] = Module['ui']['PopupFlags'] || {};
        Module['ui']['PopupFlags']['None'] = _mud_ui_PopupFlags_None();
        Module['ui']['PopupFlags']['Modal'] = _mud_ui_PopupFlags_Modal();
        Module['ui']['PopupFlags']['Clamp'] = _mud_ui_PopupFlags_Clamp();
        Module['ui']['PopupFlags']['AutoClose'] = _mud_ui_PopupFlags_AutoClose();
        Module['ui']['PopupFlags']['AutoModal'] = _mud_ui_PopupFlags_AutoModal();
        // Preset
        Module['Preset'] = Module['Preset'] || {};
        Module['Preset']['Sheet'] = _mud_Preset_Sheet();
        Module['Preset']['Flex'] = _mud_Preset_Flex();
        Module['Preset']['Item'] = _mud_Preset_Item();
        Module['Preset']['Unit'] = _mud_Preset_Unit();
        Module['Preset']['Block'] = _mud_Preset_Block();
        Module['Preset']['Line'] = _mud_Preset_Line();
        Module['Preset']['Stack'] = _mud_Preset_Stack();
        Module['Preset']['Div'] = _mud_Preset_Div();
        Module['Preset']['Spacer'] = _mud_Preset_Spacer();
        Module['Preset']['Board'] = _mud_Preset_Board();
        Module['Preset']['Layout'] = _mud_Preset_Layout();
        // Sizing
        Module['Sizing'] = Module['Sizing'] || {};
        Module['Sizing']['Fixed'] = _mud_Sizing_Fixed();
        Module['Sizing']['Shrink'] = _mud_Sizing_Shrink();
        Module['Sizing']['Wrap'] = _mud_Sizing_Wrap();
        Module['Sizing']['Expand'] = _mud_Sizing_Expand();
        // Solver
        Module['Solver'] = Module['Solver'] || {};
        Module['Solver']['Frame'] = _mud_Solver_Frame();
        Module['Solver']['Row'] = _mud_Solver_Row();
        Module['Solver']['Grid'] = _mud_Solver_Grid();
        Module['Solver']['Table'] = _mud_Solver_Table();
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
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
