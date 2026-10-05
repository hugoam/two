Module['stl'] = Module['stl'] || {};
Module['ui'] = Module['ui'] || {};
// Space
function Space() {
    this.__ptr = _two_Space__construct_0(); getCache(Space)[this.__ptr] = this;
};
Space.prototype = Object.create(WrapperObject.prototype);
Space.prototype.constructor = Space;
Space.prototype.__class = Space;
Space.__cache = {};
Module['Space'] = Space;
Object.defineProperty(Space.prototype, "direction", {
    get: function() {
        return _two_Space__get_direction(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Space.direction: expected integer');
        _two_Space__set_direction(this.__ptr, value);
    }
});
Object.defineProperty(Space.prototype, "sizingLength", {
    get: function() {
        return _two_Space__get_sizingLength(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Space.sizingLength: expected integer');
        _two_Space__set_sizingLength(this.__ptr, value);
    }
});
Object.defineProperty(Space.prototype, "sizingDepth", {
    get: function() {
        return _two_Space__get_sizingDepth(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Space.sizingDepth: expected integer');
        _two_Space__set_sizingDepth(this.__ptr, value);
    }
});
Space.prototype["__destroy"] = Space.prototype.__destroy = function() {
    _two_Space__destroy(this.__ptr);
};
// v2<two::AutoLayout>
function v2_two_AutoLayout(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('v2<T>(0:v): expected integer'); }
    else { if (typeof a0 !== 'number') throw Error('v2<T>(0:x): expected integer'); if (typeof a1 !== 'number') throw Error('v2<T>(1:y): expected integer'); }
    if (a0 === undefined) { this.__ptr = _two_v2_two_AutoLayout__construct_0(); getCache(v2_two_AutoLayout)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v2_two_AutoLayout__construct_1(/*v*/a0); getCache(v2_two_AutoLayout)[this.__ptr] = this; }
    else { this.__ptr = _two_v2_two_AutoLayout__construct_2(/*x*/a0, /*y*/a1); getCache(v2_two_AutoLayout)[this.__ptr] = this; }
};
v2_two_AutoLayout.prototype = Object.create(WrapperObject.prototype);
v2_two_AutoLayout.prototype.constructor = v2_two_AutoLayout;
v2_two_AutoLayout.prototype.__class = v2_two_AutoLayout;
v2_two_AutoLayout.__cache = {};
Module['v2_two_AutoLayout'] = v2_two_AutoLayout;
Object.defineProperty(v2_two_AutoLayout.prototype, "x", {
    get: function() {
        return _two_v2_two_AutoLayout__get_x(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<two::AutoLayout>.x: expected integer');
        _two_v2_two_AutoLayout__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v2_two_AutoLayout.prototype, "y", {
    get: function() {
        return _two_v2_two_AutoLayout__get_y(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<two::AutoLayout>.y: expected integer');
        _two_v2_two_AutoLayout__set_y(this.__ptr, value);
    }
});
v2_two_AutoLayout.prototype["__destroy"] = v2_two_AutoLayout.prototype.__destroy = function() {
    _two_v2_two_AutoLayout__destroy(this.__ptr);
};
// v2<two::Sizing>
function v2_two_Sizing(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('v2<T>(0:v): expected integer'); }
    else { if (typeof a0 !== 'number') throw Error('v2<T>(0:x): expected integer'); if (typeof a1 !== 'number') throw Error('v2<T>(1:y): expected integer'); }
    if (a0 === undefined) { this.__ptr = _two_v2_two_Sizing__construct_0(); getCache(v2_two_Sizing)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v2_two_Sizing__construct_1(/*v*/a0); getCache(v2_two_Sizing)[this.__ptr] = this; }
    else { this.__ptr = _two_v2_two_Sizing__construct_2(/*x*/a0, /*y*/a1); getCache(v2_two_Sizing)[this.__ptr] = this; }
};
v2_two_Sizing.prototype = Object.create(WrapperObject.prototype);
v2_two_Sizing.prototype.constructor = v2_two_Sizing;
v2_two_Sizing.prototype.__class = v2_two_Sizing;
v2_two_Sizing.__cache = {};
Module['v2_two_Sizing'] = v2_two_Sizing;
Object.defineProperty(v2_two_Sizing.prototype, "x", {
    get: function() {
        return _two_v2_two_Sizing__get_x(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<two::Sizing>.x: expected integer');
        _two_v2_two_Sizing__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v2_two_Sizing.prototype, "y", {
    get: function() {
        return _two_v2_two_Sizing__get_y(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<two::Sizing>.y: expected integer');
        _two_v2_two_Sizing__set_y(this.__ptr, value);
    }
});
v2_two_Sizing.prototype["__destroy"] = v2_two_Sizing.prototype.__destroy = function() {
    _two_v2_two_Sizing__destroy(this.__ptr);
};
// v2<two::Align>
function v2_two_Align(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('v2<T>(0:v): expected integer'); }
    else { if (typeof a0 !== 'number') throw Error('v2<T>(0:x): expected integer'); if (typeof a1 !== 'number') throw Error('v2<T>(1:y): expected integer'); }
    if (a0 === undefined) { this.__ptr = _two_v2_two_Align__construct_0(); getCache(v2_two_Align)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v2_two_Align__construct_1(/*v*/a0); getCache(v2_two_Align)[this.__ptr] = this; }
    else { this.__ptr = _two_v2_two_Align__construct_2(/*x*/a0, /*y*/a1); getCache(v2_two_Align)[this.__ptr] = this; }
};
v2_two_Align.prototype = Object.create(WrapperObject.prototype);
v2_two_Align.prototype.constructor = v2_two_Align;
v2_two_Align.prototype.__class = v2_two_Align;
v2_two_Align.__cache = {};
Module['v2_two_Align'] = v2_two_Align;
Object.defineProperty(v2_two_Align.prototype, "x", {
    get: function() {
        return _two_v2_two_Align__get_x(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<two::Align>.x: expected integer');
        _two_v2_two_Align__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v2_two_Align.prototype, "y", {
    get: function() {
        return _two_v2_two_Align__get_y(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<two::Align>.y: expected integer');
        _two_v2_two_Align__set_y(this.__ptr, value);
    }
});
v2_two_Align.prototype["__destroy"] = v2_two_Align.prototype.__destroy = function() {
    _two_v2_two_Align__destroy(this.__ptr);
};
// v2<two::Pivot>
function v2_two_Pivot(a0, a1) {
    if (a0 === undefined) {  }
    else if (a1 === undefined) { if (typeof a0 !== 'number') throw Error('v2<T>(0:v): expected integer'); }
    else { if (typeof a0 !== 'number') throw Error('v2<T>(0:x): expected integer'); if (typeof a1 !== 'number') throw Error('v2<T>(1:y): expected integer'); }
    if (a0 === undefined) { this.__ptr = _two_v2_two_Pivot__construct_0(); getCache(v2_two_Pivot)[this.__ptr] = this; }
    else if (a1 === undefined) { this.__ptr = _two_v2_two_Pivot__construct_1(/*v*/a0); getCache(v2_two_Pivot)[this.__ptr] = this; }
    else { this.__ptr = _two_v2_two_Pivot__construct_2(/*x*/a0, /*y*/a1); getCache(v2_two_Pivot)[this.__ptr] = this; }
};
v2_two_Pivot.prototype = Object.create(WrapperObject.prototype);
v2_two_Pivot.prototype.constructor = v2_two_Pivot;
v2_two_Pivot.prototype.__class = v2_two_Pivot;
v2_two_Pivot.__cache = {};
Module['v2_two_Pivot'] = v2_two_Pivot;
Object.defineProperty(v2_two_Pivot.prototype, "x", {
    get: function() {
        return _two_v2_two_Pivot__get_x(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<two::Pivot>.x: expected integer');
        _two_v2_two_Pivot__set_x(this.__ptr, value);
    }
});
Object.defineProperty(v2_two_Pivot.prototype, "y", {
    get: function() {
        return _two_v2_two_Pivot__get_y(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('v2<two::Pivot>.y: expected integer');
        _two_v2_two_Pivot__set_y(this.__ptr, value);
    }
});
v2_two_Pivot.prototype["__destroy"] = v2_two_Pivot.prototype.__destroy = function() {
    _two_v2_two_Pivot__destroy(this.__ptr);
};
// ImageSkin
function ImageSkin(a0, a1, a2, a3, a4, a5, a6) {
    if (a5 === undefined) { if (!checkClass(a0, Image)) throw Error('ImageSkin(0:image): expected Image'); if (typeof a1 !== 'number') throw Error('ImageSkin(1:left): expected integer'); if (typeof a2 !== 'number') throw Error('ImageSkin(2:top): expected integer'); if (typeof a3 !== 'number') throw Error('ImageSkin(3:right): expected integer'); if (typeof a4 !== 'number') throw Error('ImageSkin(4:bottom): expected integer'); }
    else if (a6 === undefined) { if (!checkClass(a0, Image)) throw Error('ImageSkin(0:image): expected Image'); if (typeof a1 !== 'number') throw Error('ImageSkin(1:left): expected integer'); if (typeof a2 !== 'number') throw Error('ImageSkin(2:top): expected integer'); if (typeof a3 !== 'number') throw Error('ImageSkin(3:right): expected integer'); if (typeof a4 !== 'number') throw Error('ImageSkin(4:bottom): expected integer'); if (typeof a5 !== 'number') throw Error('ImageSkin(5:margin): expected integer'); }
    else { if (!checkClass(a0, Image)) throw Error('ImageSkin(0:image): expected Image'); if (typeof a1 !== 'number') throw Error('ImageSkin(1:left): expected integer'); if (typeof a2 !== 'number') throw Error('ImageSkin(2:top): expected integer'); if (typeof a3 !== 'number') throw Error('ImageSkin(3:right): expected integer'); if (typeof a4 !== 'number') throw Error('ImageSkin(4:bottom): expected integer'); if (typeof a5 !== 'number') throw Error('ImageSkin(5:margin): expected integer'); if (typeof a6 !== 'number') throw Error('ImageSkin(6:stretch): expected integer'); }
    if (a5 === undefined) { this.__ptr = _two_ImageSkin__construct_5(/*image*/a0.__ptr, /*left*/a1, /*top*/a2, /*right*/a3, /*bottom*/a4); getCache(ImageSkin)[this.__ptr] = this; }
    else if (a6 === undefined) { this.__ptr = _two_ImageSkin__construct_6(/*image*/a0.__ptr, /*left*/a1, /*top*/a2, /*right*/a3, /*bottom*/a4, /*margin*/a5); getCache(ImageSkin)[this.__ptr] = this; }
    else { this.__ptr = _two_ImageSkin__construct_7(/*image*/a0.__ptr, /*left*/a1, /*top*/a2, /*right*/a3, /*bottom*/a4, /*margin*/a5, /*stretch*/a6); getCache(ImageSkin)[this.__ptr] = this; }
};
ImageSkin.prototype = Object.create(WrapperObject.prototype);
ImageSkin.prototype.constructor = ImageSkin;
ImageSkin.prototype.__class = ImageSkin;
ImageSkin.__cache = {};
Module['ImageSkin'] = ImageSkin;
Object.defineProperty(ImageSkin.prototype, "d_image", {
    get: function() {
        return wrapPointer(_two_ImageSkin__get_d_image(this.__ptr), Image);
    },
    set: function(value) {
        if (!checkClass(value, Image)) throw Error('ImageSkin.d_image: expected Image');
        _two_ImageSkin__set_d_image(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_left", {
    get: function() {
        return _two_ImageSkin__get_d_left(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ImageSkin.d_left: expected integer');
        _two_ImageSkin__set_d_left(this.__ptr, value);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_top", {
    get: function() {
        return _two_ImageSkin__get_d_top(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ImageSkin.d_top: expected integer');
        _two_ImageSkin__set_d_top(this.__ptr, value);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_right", {
    get: function() {
        return _two_ImageSkin__get_d_right(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ImageSkin.d_right: expected integer');
        _two_ImageSkin__set_d_right(this.__ptr, value);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_bottom", {
    get: function() {
        return _two_ImageSkin__get_d_bottom(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ImageSkin.d_bottom: expected integer');
        _two_ImageSkin__set_d_bottom(this.__ptr, value);
    }
});
Object.defineProperty(ImageSkin.prototype, "margin", {
    get: function() {
        return _two_ImageSkin__get_margin(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ImageSkin.margin: expected integer');
        _two_ImageSkin__set_margin(this.__ptr, value);
    }
});
Object.defineProperty(ImageSkin.prototype, "d_stretch", {
    get: function() {
        return _two_ImageSkin__get_d_stretch(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ImageSkin.d_stretch: expected integer');
        _two_ImageSkin__set_d_stretch(this.__ptr, value);
    }
});
ImageSkin.prototype["__destroy"] = ImageSkin.prototype.__destroy = function() {
    _two_ImageSkin__destroy(this.__ptr);
};
// Shadow
function Shadow(a0, a1, a2, a3, a4) {
    if (a0 === undefined) {  }
    else if (a4 === undefined) { if (typeof a0 !== 'number') throw Error('Shadow(0:xpos): expected number'); if (typeof a1 !== 'number') throw Error('Shadow(1:ypos): expected number'); if (typeof a2 !== 'number') throw Error('Shadow(2:blur): expected number'); if (typeof a3 !== 'number') throw Error('Shadow(3:spread): expected number'); }
    else { if (typeof a0 !== 'number') throw Error('Shadow(0:xpos): expected number'); if (typeof a1 !== 'number') throw Error('Shadow(1:ypos): expected number'); if (typeof a2 !== 'number') throw Error('Shadow(2:blur): expected number'); if (typeof a3 !== 'number') throw Error('Shadow(3:spread): expected number'); if (!checkClass(a4, Colour)) throw Error('Shadow(4:colour): expected Colour'); }
    if (a0 === undefined) { this.__ptr = _two_Shadow__construct_0(); getCache(Shadow)[this.__ptr] = this; }
    else if (a4 === undefined) { this.__ptr = _two_Shadow__construct_4(/*xpos*/a0, /*ypos*/a1, /*blur*/a2, /*spread*/a3); getCache(Shadow)[this.__ptr] = this; }
    else { this.__ptr = _two_Shadow__construct_5(/*xpos*/a0, /*ypos*/a1, /*blur*/a2, /*spread*/a3, /*colour*/a4.__ptr); getCache(Shadow)[this.__ptr] = this; }
};
Shadow.prototype = Object.create(WrapperObject.prototype);
Shadow.prototype.constructor = Shadow;
Shadow.prototype.__class = Shadow;
Shadow.__cache = {};
Module['Shadow'] = Shadow;
Object.defineProperty(Shadow.prototype, "d_xpos", {
    get: function() {
        return _two_Shadow__get_d_xpos(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Shadow.d_xpos: expected number');
        _two_Shadow__set_d_xpos(this.__ptr, value);
    }
});
Object.defineProperty(Shadow.prototype, "d_ypos", {
    get: function() {
        return _two_Shadow__get_d_ypos(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Shadow.d_ypos: expected number');
        _two_Shadow__set_d_ypos(this.__ptr, value);
    }
});
Object.defineProperty(Shadow.prototype, "d_blur", {
    get: function() {
        return _two_Shadow__get_d_blur(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Shadow.d_blur: expected number');
        _two_Shadow__set_d_blur(this.__ptr, value);
    }
});
Object.defineProperty(Shadow.prototype, "d_spread", {
    get: function() {
        return _two_Shadow__get_d_spread(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Shadow.d_spread: expected number');
        _two_Shadow__set_d_spread(this.__ptr, value);
    }
});
Object.defineProperty(Shadow.prototype, "d_colour", {
    get: function() {
        return wrapPointer(_two_Shadow__get_d_colour(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('Shadow.d_colour: expected Colour');
        _two_Shadow__set_d_colour(this.__ptr, value.__ptr);
    }
});
Shadow.prototype["__destroy"] = Shadow.prototype.__destroy = function() {
    _two_Shadow__destroy(this.__ptr);
};
// Paint
function Paint() {
    this.__ptr = _two_Paint__construct_0(); getCache(Paint)[this.__ptr] = this;
};
Paint.prototype = Object.create(WrapperObject.prototype);
Paint.prototype.constructor = Paint;
Paint.prototype.__class = Paint;
Paint.__cache = {};
Module['Paint'] = Paint;
Object.defineProperty(Paint.prototype, "fill_colour", {
    get: function() {
        return wrapPointer(_two_Paint__get_fill_colour(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('Paint.fill_colour: expected Colour');
        _two_Paint__set_fill_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Paint.prototype, "stroke_colour", {
    get: function() {
        return wrapPointer(_two_Paint__get_stroke_colour(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('Paint.stroke_colour: expected Colour');
        _two_Paint__set_stroke_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Paint.prototype, "stroke_width", {
    get: function() {
        return _two_Paint__get_stroke_width(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Paint.stroke_width: expected number');
        _two_Paint__set_stroke_width(this.__ptr, value);
    }
});
Paint.prototype["__destroy"] = Paint.prototype.__destroy = function() {
    _two_Paint__destroy(this.__ptr);
};
// TextPaint
function TextPaint() {
    this.__ptr = _two_TextPaint__construct_0(); getCache(TextPaint)[this.__ptr] = this;
};
TextPaint.prototype = Object.create(WrapperObject.prototype);
TextPaint.prototype.constructor = TextPaint;
TextPaint.prototype.__class = TextPaint;
TextPaint.__cache = {};
Module['TextPaint'] = TextPaint;
Object.defineProperty(TextPaint.prototype, "font", {
    get: function() {
        return UTF8ToString(_two_TextPaint__get_font(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('TextPaint.font: expected string');
        _two_TextPaint__set_font(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(TextPaint.prototype, "colour", {
    get: function() {
        return wrapPointer(_two_TextPaint__get_colour(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('TextPaint.colour: expected Colour');
        _two_TextPaint__set_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(TextPaint.prototype, "size", {
    get: function() {
        return _two_TextPaint__get_size(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('TextPaint.size: expected number');
        _two_TextPaint__set_size(this.__ptr, value);
    }
});
Object.defineProperty(TextPaint.prototype, "align", {
    get: function() {
        return wrapPointer(_two_TextPaint__get_align(this.__ptr), v2_two_Align);
    },
    set: function(value) {
        if (!checkClass(value, v2_two_Align)) throw Error('TextPaint.align: expected v2<two::Align>');
        _two_TextPaint__set_align(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(TextPaint.prototype, "text_break", {
    get: function() {
        return !!(_two_TextPaint__get_text_break(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('TextPaint.text_break: expected boolean');
        _two_TextPaint__set_text_break(this.__ptr, value);
    }
});
Object.defineProperty(TextPaint.prototype, "text_wrap", {
    get: function() {
        return !!(_two_TextPaint__get_text_wrap(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('TextPaint.text_wrap: expected boolean');
        _two_TextPaint__set_text_wrap(this.__ptr, value);
    }
});
TextPaint.prototype["__destroy"] = TextPaint.prototype.__destroy = function() {
    _two_TextPaint__destroy(this.__ptr);
};
// Gradient
function Gradient() {
    this.__ptr = _two_Gradient__construct_0(); getCache(Gradient)[this.__ptr] = this;
};
Gradient.prototype = Object.create(WrapperObject.prototype);
Gradient.prototype.constructor = Gradient;
Gradient.prototype.__class = Gradient;
Gradient.__cache = {};
Module['Gradient'] = Gradient;
Object.defineProperty(Gradient.prototype, "start", {
    get: function() {
        return wrapPointer(_two_Gradient__get_start(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('Gradient.start: expected Colour');
        _two_Gradient__set_start(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Gradient.prototype, "end", {
    get: function() {
        return wrapPointer(_two_Gradient__get_end(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('Gradient.end: expected Colour');
        _two_Gradient__set_end(this.__ptr, value.__ptr);
    }
});
Gradient.prototype["__destroy"] = Gradient.prototype.__destroy = function() {
    _two_Gradient__destroy(this.__ptr);
};
// InkStyle
function InkStyle(a0) {
    ensureCache.prepare();
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'string') throw Error('InkStyle(0:name): expected string'); }
    if (a0 === undefined) { this.__ptr = _two_InkStyle__construct_0(); getCache(InkStyle)[this.__ptr] = this; }
    else { this.__ptr = _two_InkStyle__construct_1(ensureString(/*name*/a0)); getCache(InkStyle)[this.__ptr] = this; }
};
InkStyle.prototype = Object.create(WrapperObject.prototype);
InkStyle.prototype.constructor = InkStyle;
InkStyle.prototype.__class = InkStyle;
InkStyle.__cache = {};
Module['InkStyle'] = InkStyle;
Object.defineProperty(InkStyle.prototype, "name", {
    get: function() {
        return UTF8ToString(_two_InkStyle__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('InkStyle.name: expected string');
        _two_InkStyle__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(InkStyle.prototype, "empty", {
    get: function() {
        return !!(_two_InkStyle__get_empty(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('InkStyle.empty: expected boolean');
        _two_InkStyle__set_empty(this.__ptr, value);
    }
});
Object.defineProperty(InkStyle.prototype, "background_colour", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_background_colour(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('InkStyle.background_colour: expected Colour');
        _two_InkStyle__set_background_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "border_colour", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_border_colour(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('InkStyle.border_colour: expected Colour');
        _two_InkStyle__set_border_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "image_colour", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_image_colour(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('InkStyle.image_colour: expected Colour');
        _two_InkStyle__set_image_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "text_colour", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_text_colour(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('InkStyle.text_colour: expected Colour');
        _two_InkStyle__set_text_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "text_font", {
    get: function() {
        return UTF8ToString(_two_InkStyle__get_text_font(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('InkStyle.text_font: expected string');
        _two_InkStyle__set_text_font(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(InkStyle.prototype, "text_size", {
    get: function() {
        return _two_InkStyle__get_text_size(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('InkStyle.text_size: expected number');
        _two_InkStyle__set_text_size(this.__ptr, value);
    }
});
Object.defineProperty(InkStyle.prototype, "text_break", {
    get: function() {
        return !!(_two_InkStyle__get_text_break(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('InkStyle.text_break: expected boolean');
        _two_InkStyle__set_text_break(this.__ptr, value);
    }
});
Object.defineProperty(InkStyle.prototype, "text_wrap", {
    get: function() {
        return !!(_two_InkStyle__get_text_wrap(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('InkStyle.text_wrap: expected boolean');
        _two_InkStyle__set_text_wrap(this.__ptr, value);
    }
});
Object.defineProperty(InkStyle.prototype, "border_width", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_border_width(this.__ptr), v4_float);
    },
    set: function(value) {
        if (!checkClass(value, v4_float)) throw Error('InkStyle.border_width: expected v4<float>');
        _two_InkStyle__set_border_width(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "corner_radius", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_corner_radius(this.__ptr), v4_float);
    },
    set: function(value) {
        if (!checkClass(value, v4_float)) throw Error('InkStyle.corner_radius: expected v4<float>');
        _two_InkStyle__set_corner_radius(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "weak_corners", {
    get: function() {
        return !!(_two_InkStyle__get_weak_corners(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('InkStyle.weak_corners: expected boolean');
        _two_InkStyle__set_weak_corners(this.__ptr, value);
    }
});
Object.defineProperty(InkStyle.prototype, "padding", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_padding(this.__ptr), v4_float);
    },
    set: function(value) {
        if (!checkClass(value, v4_float)) throw Error('InkStyle.padding: expected v4<float>');
        _two_InkStyle__set_padding(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "margin", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_margin(this.__ptr), v4_float);
    },
    set: function(value) {
        if (!checkClass(value, v4_float)) throw Error('InkStyle.margin: expected v4<float>');
        _two_InkStyle__set_margin(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "align", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_align(this.__ptr), v2_two_Align);
    },
    set: function(value) {
        if (!checkClass(value, v2_two_Align)) throw Error('InkStyle.align: expected v2<two::Align>');
        _two_InkStyle__set_align(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "linear_gradient", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_linear_gradient(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('InkStyle.linear_gradient: expected v2<float>');
        _two_InkStyle__set_linear_gradient(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "linear_gradient_dim", {
    get: function() {
        return _two_InkStyle__get_linear_gradient_dim(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('InkStyle.linear_gradient_dim: expected integer');
        _two_InkStyle__set_linear_gradient_dim(this.__ptr, value);
    }
});
Object.defineProperty(InkStyle.prototype, "stretch", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_stretch(this.__ptr), v2_bool);
    },
    set: function(value) {
        if (!checkClass(value, v2_bool)) throw Error('InkStyle.stretch: expected v2<bool>');
        _two_InkStyle__set_stretch(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "image", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_image(this.__ptr), Image);
    },
    set: function(value) {
        if (!checkClass(value, Image)) throw Error('InkStyle.image: expected Image');
        _two_InkStyle__set_image(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "overlay", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_overlay(this.__ptr), Image);
    },
    set: function(value) {
        if (!checkClass(value, Image)) throw Error('InkStyle.overlay: expected Image');
        _two_InkStyle__set_overlay(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "tile", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_tile(this.__ptr), Image);
    },
    set: function(value) {
        if (!checkClass(value, Image)) throw Error('InkStyle.tile: expected Image');
        _two_InkStyle__set_tile(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "image_skin", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_image_skin(this.__ptr), ImageSkin);
    },
    set: function(value) {
        if (!checkClass(value, ImageSkin)) throw Error('InkStyle.image_skin: expected ImageSkin');
        _two_InkStyle__set_image_skin(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "shadow", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_shadow(this.__ptr), Shadow);
    },
    set: function(value) {
        if (!checkClass(value, Shadow)) throw Error('InkStyle.shadow: expected Shadow');
        _two_InkStyle__set_shadow(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "shadow_colour", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_shadow_colour(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('InkStyle.shadow_colour: expected Colour');
        _two_InkStyle__set_shadow_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InkStyle.prototype, "hover_cursor", {
    get: function() {
        return wrapPointer(_two_InkStyle__get_hover_cursor(this.__ptr), Style);
    },
    set: function(value) {
        if (!checkClass(value, Style)) throw Error('InkStyle.hover_cursor: expected Style');
        _two_InkStyle__set_hover_cursor(this.__ptr, value.__ptr);
    }
});
InkStyle.prototype["__destroy"] = InkStyle.prototype.__destroy = function() {
    _two_InkStyle__destroy(this.__ptr);
};
// Layout
function Layout(a0) {
    ensureCache.prepare();
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'string') throw Error('Layout(0:name): expected string'); }
    if (a0 === undefined) { this.__ptr = _two_Layout__construct_0(); getCache(Layout)[this.__ptr] = this; }
    else { this.__ptr = _two_Layout__construct_1(ensureString(/*name*/a0)); getCache(Layout)[this.__ptr] = this; }
};
Layout.prototype = Object.create(WrapperObject.prototype);
Layout.prototype.constructor = Layout;
Layout.prototype.__class = Layout;
Layout.__cache = {};
Module['Layout'] = Layout;
Object.defineProperty(Layout.prototype, "name", {
    get: function() {
        return UTF8ToString(_two_Layout__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Layout.name: expected string');
        _two_Layout__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Layout.prototype, "layout", {
    get: function() {
        return wrapPointer(_two_Layout__get_layout(this.__ptr), v2_two_AutoLayout);
    },
    set: function(value) {
        if (!checkClass(value, v2_two_AutoLayout)) throw Error('Layout.layout: expected v2<two::AutoLayout>');
        _two_Layout__set_layout(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Layout.prototype, "flow", {
    get: function() {
        return _two_Layout__get_flow(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Layout.flow: expected integer');
        _two_Layout__set_flow(this.__ptr, value);
    }
});
Object.defineProperty(Layout.prototype, "space", {
    get: function() {
        return wrapPointer(_two_Layout__get_space(this.__ptr), Space);
    },
    set: function(value) {
        if (!checkClass(value, Space)) throw Error('Layout.space: expected Space');
        _two_Layout__set_space(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Layout.prototype, "clipping", {
    get: function() {
        return _two_Layout__get_clipping(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Layout.clipping: expected integer');
        _two_Layout__set_clipping(this.__ptr, value);
    }
});
Object.defineProperty(Layout.prototype, "opacity", {
    get: function() {
        return _two_Layout__get_opacity(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Layout.opacity: expected integer');
        _two_Layout__set_opacity(this.__ptr, value);
    }
});
Object.defineProperty(Layout.prototype, "align", {
    get: function() {
        return wrapPointer(_two_Layout__get_align(this.__ptr), v2_two_Align);
    },
    set: function(value) {
        if (!checkClass(value, v2_two_Align)) throw Error('Layout.align: expected v2<two::Align>');
        _two_Layout__set_align(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Layout.prototype, "span", {
    get: function() {
        return wrapPointer(_two_Layout__get_span(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('Layout.span: expected v2<float>');
        _two_Layout__set_span(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Layout.prototype, "size", {
    get: function() {
        return wrapPointer(_two_Layout__get_size(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('Layout.size: expected v2<float>');
        _two_Layout__set_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Layout.prototype, "padding", {
    get: function() {
        return wrapPointer(_two_Layout__get_padding(this.__ptr), v4_float);
    },
    set: function(value) {
        if (!checkClass(value, v4_float)) throw Error('Layout.padding: expected v4<float>');
        _two_Layout__set_padding(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Layout.prototype, "margin", {
    get: function() {
        return wrapPointer(_two_Layout__get_margin(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('Layout.margin: expected v2<float>');
        _two_Layout__set_margin(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Layout.prototype, "spacing", {
    get: function() {
        return wrapPointer(_two_Layout__get_spacing(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('Layout.spacing: expected v2<float>');
        _two_Layout__set_spacing(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Layout.prototype, "pivot", {
    get: function() {
        return wrapPointer(_two_Layout__get_pivot(this.__ptr), v2_two_Pivot);
    },
    set: function(value) {
        if (!checkClass(value, v2_two_Pivot)) throw Error('Layout.pivot: expected v2<two::Pivot>');
        _two_Layout__set_pivot(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Layout.prototype, "zorder", {
    get: function() {
        return _two_Layout__get_zorder(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Layout.zorder: expected integer');
        _two_Layout__set_zorder(this.__ptr, value);
    }
});
Object.defineProperty(Layout.prototype, "no_grid", {
    get: function() {
        return !!(_two_Layout__get_no_grid(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Layout.no_grid: expected boolean');
        _two_Layout__set_no_grid(this.__ptr, value);
    }
});
Object.defineProperty(Layout.prototype, "table_division", {
    get: function() {
        return _two_Layout__get_table_division(this.__ptr);
    }});
Object.defineProperty(Layout.prototype, "updated", {
    get: function() {
        return _two_Layout__get_updated(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Layout.updated: expected integer');
        _two_Layout__set_updated(this.__ptr, value);
    }
});
Layout.prototype["__destroy"] = Layout.prototype.__destroy = function() {
    _two_Layout__destroy(this.__ptr);
};
// Subskin
function Subskin() {
    this.__ptr = _two_Subskin__construct_0(); getCache(Subskin)[this.__ptr] = this;
};
Subskin.prototype = Object.create(WrapperObject.prototype);
Subskin.prototype.constructor = Subskin;
Subskin.prototype.__class = Subskin;
Subskin.__cache = {};
Module['Subskin'] = Subskin;
Object.defineProperty(Subskin.prototype, "skin", {
    get: function() {
        return wrapPointer(_two_Subskin__get_skin(this.__ptr), InkStyle);
    },
    set: function(value) {
        if (!checkClass(value, InkStyle)) throw Error('Subskin.skin: expected InkStyle');
        _two_Subskin__set_skin(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Subskin.prototype, "state", {
    get: function() {
        return _two_Subskin__get_state(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Subskin.state: expected integer');
        _two_Subskin__set_state(this.__ptr, value);
    }
});
Subskin.prototype["__destroy"] = Subskin.prototype.__destroy = function() {
    _two_Subskin__destroy(this.__ptr);
};
// Style
function Style() { throw "cannot construct a Style, no constructor in IDL" }
Style.prototype = Object.create(WrapperObject.prototype);
Style.prototype.constructor = Style;
Style.prototype.__class = Style;
Style.__cache = {};
Module['Style'] = Style;
Object.defineProperty(Style.prototype, "base", {
    get: function() {
        return wrapPointer(_two_Style__get_base(this.__ptr), Style);
    },
    set: function(value) {
        if (!checkClass(value, Style)) throw Error('Style.base: expected Style');
        _two_Style__set_base(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Style.prototype, "name", {
    get: function() {
        return UTF8ToString(_two_Style__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Style.name: expected string');
        _two_Style__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Style.prototype, "layout", {
    get: function() {
        return wrapPointer(_two_Style__get_layout(this.__ptr), Layout);
    },
    set: function(value) {
        if (!checkClass(value, Layout)) throw Error('Style.layout: expected Layout');
        _two_Style__set_layout(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Style.prototype, "skin", {
    get: function() {
        return wrapPointer(_two_Style__get_skin(this.__ptr), InkStyle);
    },
    set: function(value) {
        if (!checkClass(value, InkStyle)) throw Error('Style.skin: expected InkStyle');
        _two_Style__set_skin(this.__ptr, value.__ptr);
    }
});
Style.prototype["__destroy"] = Style.prototype.__destroy = function() {
    _two_Style__destroy(this.__ptr);
};
// UiRect
function UiRect() {
    this.__ptr = _two_UiRect__construct_0(); getCache(UiRect)[this.__ptr] = this;
};
UiRect.prototype = Object.create(WrapperObject.prototype);
UiRect.prototype.constructor = UiRect;
UiRect.prototype.__class = UiRect;
UiRect.__cache = {};
Module['UiRect'] = UiRect;
Object.defineProperty(UiRect.prototype, "position", {
    get: function() {
        return wrapPointer(_two_UiRect__get_position(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('UiRect.position: expected v2<float>');
        _two_UiRect__set_position(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(UiRect.prototype, "size", {
    get: function() {
        return wrapPointer(_two_UiRect__get_size(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('UiRect.size: expected v2<float>');
        _two_UiRect__set_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(UiRect.prototype, "content", {
    get: function() {
        return wrapPointer(_two_UiRect__get_content(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('UiRect.content: expected v2<float>');
        _two_UiRect__set_content(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(UiRect.prototype, "span", {
    get: function() {
        return wrapPointer(_two_UiRect__get_span(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('UiRect.span: expected v2<float>');
        _two_UiRect__set_span(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(UiRect.prototype, "scale", {
    get: function() {
        return _two_UiRect__get_scale(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('UiRect.scale: expected number');
        _two_UiRect__set_scale(this.__ptr, value);
    }
});
UiRect.prototype["__destroy"] = UiRect.prototype.__destroy = function() {
    _two_UiRect__destroy(this.__ptr);
};
// Frame
function Frame() { throw "cannot construct a Frame, no constructor in IDL" }
Frame.prototype = Object.create(UiRect.prototype);
Frame.prototype.constructor = Frame;
Frame.prototype.__class = Frame;
Frame.__base = UiRect;
Frame.__cache = {};
Module['Frame'] = Frame;
Frame.prototype["__destroy"] = Frame.prototype.__destroy = function() {
    _two_Frame__destroy(this.__ptr);
};
// Widget
function Widget() { throw "cannot construct a Widget, no constructor in IDL" }
Widget.prototype = Object.create(ControlNode.prototype);
Widget.prototype.constructor = Widget;
Widget.prototype.__class = Widget;
Widget.__base = ControlNode;
Widget.__cache = {};
Module['Widget'] = Widget;
Widget.prototype["focused"] = Widget.prototype.focused = function() {
    return !!(_two_Widget_focused_0(this.__ptr));
};
Widget.prototype["hovered"] = Widget.prototype.hovered = function() {
    return !!(_two_Widget_hovered_0(this.__ptr));
};
Widget.prototype["pressed"] = Widget.prototype.pressed = function() {
    return !!(_two_Widget_pressed_0(this.__ptr));
};
Widget.prototype["activated"] = Widget.prototype.activated = function() {
    return !!(_two_Widget_activated_0(this.__ptr));
};
Widget.prototype["active"] = Widget.prototype.active = function() {
    return !!(_two_Widget_active_0(this.__ptr));
};
Widget.prototype["selected"] = Widget.prototype.selected = function() {
    return !!(_two_Widget_selected_0(this.__ptr));
};
Widget.prototype["modal"] = Widget.prototype.modal = function() {
    return !!(_two_Widget_modal_0(this.__ptr));
};
Widget.prototype["closed"] = Widget.prototype.closed = function() {
    return !!(_two_Widget_closed_0(this.__ptr));
};
Widget.prototype["open"] = Widget.prototype.open = function() {
    return !!(_two_Widget_open_0(this.__ptr));
};
Widget.prototype["ui_window"] = Widget.prototype.ui_window = function() {
    return wrapPointer(_two_Widget_ui_window_0(this.__ptr), UiWindow);
};
Widget.prototype["ui"] = Widget.prototype.ui = function() {
    return wrapPointer(_two_Widget_ui_0(this.__ptr), Ui);
};
Widget.prototype["parent_modal"] = Widget.prototype.parent_modal = function() {
    return wrapPointer(_two_Widget_parent_modal_0(this.__ptr), Widget);
};
Widget.prototype["clear"] = Widget.prototype.clear = function() {
    _two_Widget_clear_0(this.__ptr);
};
Widget.prototype["toggle_state"] = Widget.prototype.toggle_state = function(a0) {
    if (typeof a0 !== 'number') throw Error('toggle_state(0:state): expected integer');
    _two_Widget_toggle_state_1(this.__ptr, /*state*/a0);
};
Widget.prototype["disable_state"] = Widget.prototype.disable_state = function(a0) {
    if (typeof a0 !== 'number') throw Error('disable_state(0:state): expected integer');
    _two_Widget_disable_state_1(this.__ptr, /*state*/a0);
};
Widget.prototype["set_state"] = Widget.prototype.set_state = function(a0, a1) {
    if (typeof a0 !== 'number') throw Error('set_state(0:state): expected integer'); if (typeof a1 !== 'boolean') throw Error('set_state(1:enabled): expected boolean');
    _two_Widget_set_state_2(this.__ptr, /*state*/a0, /*enabled*/a1);
};
Widget.prototype["enable_state"] = Widget.prototype.enable_state = function(a0) {
    if (typeof a0 !== 'number') throw Error('enable_state(0:state): expected integer');
    _two_Widget_enable_state_1(this.__ptr, /*state*/a0);
};
Widget.prototype["set_open"] = Widget.prototype.set_open = function(a0) {
    if (typeof a0 !== 'boolean') throw Error('set_open(0:open): expected boolean');
    _two_Widget_set_open_1(this.__ptr, /*open*/a0);
};
Widget.prototype["clear_focus"] = Widget.prototype.clear_focus = function() {
    _two_Widget_clear_focus_0(this.__ptr);
};
Widget.prototype["take_focus"] = Widget.prototype.take_focus = function() {
    _two_Widget_take_focus_0(this.__ptr);
};
Widget.prototype["yield_focus"] = Widget.prototype.yield_focus = function() {
    _two_Widget_yield_focus_0(this.__ptr);
};
Widget.prototype["take_modal"] = Widget.prototype.take_modal = function(a0) {
    if (typeof a0 !== 'number') throw Error('take_modal(0:device_filter): expected integer');
    _two_Widget_take_modal_1(this.__ptr, /*device_filter*/a0);
};
Widget.prototype["yield_modal"] = Widget.prototype.yield_modal = function() {
    _two_Widget_yield_modal_0(this.__ptr);
};
Object.defineProperty(Widget.prototype, "frame", {
    get: function() {
        return wrapPointer(_two_Widget__get_frame(this.__ptr), Frame);
    }});
Object.defineProperty(Widget.prototype, "state", {
    get: function() {
        return _two_Widget__get_state(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Widget.state: expected integer');
        _two_Widget__set_state(this.__ptr, value);
    }
});
Object.defineProperty(Widget.prototype, "switch", {
    get: function() {
        return _two_Widget__get_switch(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Widget.switch: expected integer');
        _two_Widget__set_switch(this.__ptr, value);
    }
});
Widget.prototype["__destroy"] = Widget.prototype.__destroy = function() {
    _two_Widget__destroy(this.__ptr);
};
// TextCursor
function TextCursor() {
    this.__ptr = _two_TextCursor__construct_0(); getCache(TextCursor)[this.__ptr] = this;
};
TextCursor.prototype = Object.create(WrapperObject.prototype);
TextCursor.prototype.constructor = TextCursor;
TextCursor.prototype.__class = TextCursor;
TextCursor.__cache = {};
Module['TextCursor'] = TextCursor;
TextCursor.prototype["__destroy"] = TextCursor.prototype.__destroy = function() {
    _two_TextCursor__destroy(this.__ptr);
};
// TextSelection
function TextSelection() {
    this.__ptr = _two_TextSelection__construct_0(); getCache(TextSelection)[this.__ptr] = this;
};
TextSelection.prototype = Object.create(WrapperObject.prototype);
TextSelection.prototype.constructor = TextSelection;
TextSelection.prototype.__class = TextSelection;
TextSelection.__cache = {};
Module['TextSelection'] = TextSelection;
TextSelection.prototype["__destroy"] = TextSelection.prototype.__destroy = function() {
    _two_TextSelection__destroy(this.__ptr);
};
// TextMarker
function TextMarker() {
    this.__ptr = _two_TextMarker__construct_0(); getCache(TextMarker)[this.__ptr] = this;
};
TextMarker.prototype = Object.create(WrapperObject.prototype);
TextMarker.prototype.constructor = TextMarker;
TextMarker.prototype.__class = TextMarker;
TextMarker.__cache = {};
Module['TextMarker'] = TextMarker;
TextMarker.prototype["__destroy"] = TextMarker.prototype.__destroy = function() {
    _two_TextMarker__destroy(this.__ptr);
};
// Text
function Text() { throw "cannot construct a Text, no constructor in IDL" }
Text.prototype = Object.create(WrapperObject.prototype);
Text.prototype.constructor = Text;
Text.prototype.__class = Text;
Text.__cache = {};
Module['Text'] = Text;
Text.prototype["__destroy"] = Text.prototype.__destroy = function() {
    _two_Text__destroy(this.__ptr);
};
// TextEdit
function TextEdit() { throw "cannot construct a TextEdit, no constructor in IDL" }
TextEdit.prototype = Object.create(WrapperObject.prototype);
TextEdit.prototype.constructor = TextEdit;
TextEdit.prototype.__class = TextEdit;
TextEdit.__cache = {};
Module['TextEdit'] = TextEdit;
TextEdit.prototype["__destroy"] = TextEdit.prototype.__destroy = function() {
    _two_TextEdit__destroy(this.__ptr);
};
// NodeConnection
function NodeConnection() {
    this.__ptr = _two_NodeConnection__construct_0(); getCache(NodeConnection)[this.__ptr] = this;
};
NodeConnection.prototype = Object.create(WrapperObject.prototype);
NodeConnection.prototype.constructor = NodeConnection;
NodeConnection.prototype.__class = NodeConnection;
NodeConnection.__cache = {};
Module['NodeConnection'] = NodeConnection;
NodeConnection.prototype["__destroy"] = NodeConnection.prototype.__destroy = function() {
    _two_NodeConnection__destroy(this.__ptr);
};
// Vg
function Vg() { throw "cannot construct a Vg, no constructor in IDL" }
Vg.prototype = Object.create(WrapperObject.prototype);
Vg.prototype.constructor = Vg;
Vg.prototype.__class = Vg;
Vg.__cache = {};
Module['Vg'] = Vg;
Vg.prototype["__destroy"] = Vg.prototype.__destroy = function() {
    _two_Vg__destroy(this.__ptr);
};
// Clipboard
function Clipboard() {
    this.__ptr = _two_Clipboard__construct_0(); getCache(Clipboard)[this.__ptr] = this;
};
Clipboard.prototype = Object.create(WrapperObject.prototype);
Clipboard.prototype.constructor = Clipboard;
Clipboard.prototype.__class = Clipboard;
Clipboard.__cache = {};
Module['Clipboard'] = Clipboard;
Object.defineProperty(Clipboard.prototype, "text", {
    get: function() {
        return UTF8ToString(_two_Clipboard__get_text(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Clipboard.text: expected string');
        _two_Clipboard__set_text(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Clipboard.prototype, "line_mode", {
    get: function() {
        return !!(_two_Clipboard__get_line_mode(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Clipboard.line_mode: expected boolean');
        _two_Clipboard__set_line_mode(this.__ptr, value);
    }
});
Clipboard.prototype["__destroy"] = Clipboard.prototype.__destroy = function() {
    _two_Clipboard__destroy(this.__ptr);
};
// UiWindow
function UiWindow() { throw "cannot construct a UiWindow, no constructor in IDL" }
UiWindow.prototype = Object.create(WrapperObject.prototype);
UiWindow.prototype.constructor = UiWindow;
UiWindow.prototype.__class = UiWindow;
UiWindow.__cache = {};
Module['UiWindow'] = UiWindow;
UiWindow.prototype["reset_styles"] = UiWindow.prototype.reset_styles = function() {
    _two_UiWindow_reset_styles_0(this.__ptr);
};
Object.defineProperty(UiWindow.prototype, "resource_path", {
    get: function() {
        return UTF8ToString(_two_UiWindow__get_resource_path(this.__ptr));
    }});
Object.defineProperty(UiWindow.prototype, "context", {
    get: function() {
        return wrapPointer(_two_UiWindow__get_context(this.__ptr), Context);
    }});
Object.defineProperty(UiWindow.prototype, "vg", {
    get: function() {
        return wrapPointer(_two_UiWindow__get_vg(this.__ptr), Vg);
    }});
Object.defineProperty(UiWindow.prototype, "size", {
    get: function() {
        return wrapPointer(_two_UiWindow__get_size(this.__ptr), v2_uint);
    },
    set: function(value) {
        if (!checkClass(value, v2_uint)) throw Error('UiWindow.size: expected v2<uint>');
        _two_UiWindow__set_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(UiWindow.prototype, "colour", {
    get: function() {
        return wrapPointer(_two_UiWindow__get_colour(this.__ptr), Colour);
    },
    set: function(value) {
        if (!checkClass(value, Colour)) throw Error('UiWindow.colour: expected Colour');
        _two_UiWindow__set_colour(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(UiWindow.prototype, "shutdown", {
    get: function() {
        return !!(_two_UiWindow__get_shutdown(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('UiWindow.shutdown: expected boolean');
        _two_UiWindow__set_shutdown(this.__ptr, value);
    }
});
UiWindow.prototype["__destroy"] = UiWindow.prototype.__destroy = function() {
    _two_UiWindow__destroy(this.__ptr);
};
// User
function User() { throw "cannot construct a User, no constructor in IDL" }
User.prototype = Object.create(WrapperObject.prototype);
User.prototype.constructor = User;
User.prototype.__class = User;
User.__cache = {};
Module['User'] = User;
User.prototype["__destroy"] = User.prototype.__destroy = function() {
    _two_User__destroy(this.__ptr);
};
// Layer
function Layer() { throw "cannot construct a Layer, no constructor in IDL" }
Layer.prototype = Object.create(WrapperObject.prototype);
Layer.prototype.constructor = Layer;
Layer.prototype.__class = Layer;
Layer.__cache = {};
Module['Layer'] = Layer;
Layer.prototype["__destroy"] = Layer.prototype.__destroy = function() {
    _two_Layer__destroy(this.__ptr);
};
// Dock
function Dock() {
    this.__ptr = _two_Dock__construct_0(); getCache(Dock)[this.__ptr] = this;
};
Dock.prototype = Object.create(WrapperObject.prototype);
Dock.prototype.constructor = Dock;
Dock.prototype.__class = Dock;
Dock.__cache = {};
Module['Dock'] = Dock;
Dock.prototype["__destroy"] = Dock.prototype.__destroy = function() {
    _two_Dock__destroy(this.__ptr);
};
// Docksystem
function Docksystem() { throw "cannot construct a Docksystem, no constructor in IDL" }
Docksystem.prototype = Object.create(WrapperObject.prototype);
Docksystem.prototype.constructor = Docksystem;
Docksystem.prototype.__class = Docksystem;
Docksystem.__cache = {};
Module['Docksystem'] = Docksystem;
Docksystem.prototype["__destroy"] = Docksystem.prototype.__destroy = function() {
    _two_Docksystem__destroy(this.__ptr);
};
// Docker
function Docker() { throw "cannot construct a Docker, no constructor in IDL" }
Docker.prototype = Object.create(WrapperObject.prototype);
Docker.prototype.constructor = Docker;
Docker.prototype.__class = Docker;
Docker.__cache = {};
Module['Docker'] = Docker;
Docker.prototype["__destroy"] = Docker.prototype.__destroy = function() {
    _two_Docker__destroy(this.__ptr);
};
// Dockspace
function Dockspace() { throw "cannot construct a Dockspace, no constructor in IDL" }
Dockspace.prototype = Object.create(Docker.prototype);
Dockspace.prototype.constructor = Dockspace;
Dockspace.prototype.__class = Dockspace;
Dockspace.__base = Docker;
Dockspace.__cache = {};
Module['Dockspace'] = Dockspace;
Dockspace.prototype["__destroy"] = Dockspace.prototype.__destroy = function() {
    _two_Dockspace__destroy(this.__ptr);
};
// Dockbar
function Dockbar() { throw "cannot construct a Dockbar, no constructor in IDL" }
Dockbar.prototype = Object.create(Docker.prototype);
Dockbar.prototype.constructor = Dockbar;
Dockbar.prototype.__class = Dockbar;
Dockbar.__base = Docker;
Dockbar.__cache = {};
Module['Dockbar'] = Dockbar;
Dockbar.prototype["__destroy"] = Dockbar.prototype.__destroy = function() {
    _two_Dockbar__destroy(this.__ptr);
};
// NodePlug
function NodePlug() { throw "cannot construct a NodePlug, no constructor in IDL" }
NodePlug.prototype = Object.create(WrapperObject.prototype);
NodePlug.prototype.constructor = NodePlug;
NodePlug.prototype.__class = NodePlug;
NodePlug.__cache = {};
Module['NodePlug'] = NodePlug;
NodePlug.prototype["__destroy"] = NodePlug.prototype.__destroy = function() {
    _two_NodePlug__destroy(this.__ptr);
};
// Node
function Node() { throw "cannot construct a Node, no constructor in IDL" }
Node.prototype = Object.create(WrapperObject.prototype);
Node.prototype.constructor = Node;
Node.prototype.__class = Node;
Node.__cache = {};
Module['Node'] = Node;
Object.defineProperty(Node.prototype, "header", {
    get: function() {
        return wrapPointer(_two_Node__get_header(this.__ptr), Widget);
    },
    set: function(value) {
        if (!checkClass(value, Widget)) throw Error('Node.header: expected Widget');
        _two_Node__set_header(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Node.prototype, "inputs", {
    get: function() {
        return wrapPointer(_two_Node__get_inputs(this.__ptr), Widget);
    },
    set: function(value) {
        if (!checkClass(value, Widget)) throw Error('Node.inputs: expected Widget');
        _two_Node__set_inputs(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Node.prototype, "outputs", {
    get: function() {
        return wrapPointer(_two_Node__get_outputs(this.__ptr), Widget);
    },
    set: function(value) {
        if (!checkClass(value, Widget)) throw Error('Node.outputs: expected Widget');
        _two_Node__set_outputs(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Node.prototype, "body", {
    get: function() {
        return wrapPointer(_two_Node__get_body(this.__ptr), Widget);
    },
    set: function(value) {
        if (!checkClass(value, Widget)) throw Error('Node.body: expected Widget');
        _two_Node__set_body(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Node.prototype, "order", {
    get: function() {
        return _two_Node__get_order(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Node.order: expected integer');
        _two_Node__set_order(this.__ptr, value);
    }
});
Node.prototype["__destroy"] = Node.prototype.__destroy = function() {
    _two_Node__destroy(this.__ptr);
};
// CanvasConnect
function CanvasConnect() {
    this.__ptr = _two_CanvasConnect__construct_0(); getCache(CanvasConnect)[this.__ptr] = this;
};
CanvasConnect.prototype = Object.create(WrapperObject.prototype);
CanvasConnect.prototype.constructor = CanvasConnect;
CanvasConnect.prototype.__class = CanvasConnect;
CanvasConnect.__cache = {};
Module['CanvasConnect'] = CanvasConnect;
CanvasConnect.prototype["__destroy"] = CanvasConnect.prototype.__destroy = function() {
    _two_CanvasConnect__destroy(this.__ptr);
};
// Canvas
function Canvas() { throw "cannot construct a Canvas, no constructor in IDL" }
Canvas.prototype = Object.create(WrapperObject.prototype);
Canvas.prototype.constructor = Canvas;
Canvas.prototype.__class = Canvas;
Canvas.__cache = {};
Module['Canvas'] = Canvas;
Canvas.prototype["__destroy"] = Canvas.prototype.__destroy = function() {
    _two_Canvas__destroy(this.__ptr);
};
// Ui
function Ui() { throw "cannot construct a Ui, no constructor in IDL" }
Ui.prototype = Object.create(Widget.prototype);
Ui.prototype.constructor = Ui;
Ui.prototype.__class = Ui;
Ui.__base = Widget;
Ui.__cache = {};
Module['Ui'] = Ui;
Ui.prototype["begin"] = Ui.prototype.begin = function() {
    return wrapPointer(_two_Ui_begin_0(this.__ptr), Widget);
};
Ui.prototype["reset_styles"] = Ui.prototype.reset_styles = function() {
    _two_Ui_reset_styles_0(this.__ptr);
};
Ui.prototype["__destroy"] = Ui.prototype.__destroy = function() {
    _two_Ui__destroy(this.__ptr);
};
Module['layout_minimal'] = function(a0) {
    if (!checkClass(a0, UiWindow)) throw Error('layout_minimal(0:ui_window): expected UiWindow');
    _two_layout_minimal_1(/*ui_window*/a0.__ptr);
};
Module['style_minimal'] = function(a0) {
    if (!checkClass(a0, UiWindow)) throw Error('style_minimal(0:ui_window): expected UiWindow');
    _two_style_minimal_1(/*ui_window*/a0.__ptr);
};
Module['style_vector'] = function(a0) {
    if (!checkClass(a0, UiWindow)) throw Error('style_vector(0:ui_window): expected UiWindow');
    _two_style_vector_1(/*ui_window*/a0.__ptr);
};
Module['style_blendish'] = function(a0) {
    if (!checkClass(a0, UiWindow)) throw Error('style_blendish(0:ui_window): expected UiWindow');
    _two_style_blendish_1(/*ui_window*/a0.__ptr);
};
Module['style_blendish_light'] = function(a0) {
    if (!checkClass(a0, UiWindow)) throw Error('style_blendish_light(0:ui_window): expected UiWindow');
    _two_style_blendish_light_1(/*ui_window*/a0.__ptr);
};
Module['style_blendish_dark'] = function(a0) {
    if (!checkClass(a0, UiWindow)) throw Error('style_blendish_dark(0:ui_window): expected UiWindow');
    _two_style_blendish_dark_1(/*ui_window*/a0.__ptr);
};
Module['style_imgui_dark'] = function(a0) {
    if (!checkClass(a0, UiWindow)) throw Error('style_imgui_dark(0:ui_window): expected UiWindow');
    _two_style_imgui_dark_1(/*ui_window*/a0.__ptr);
};
Module['style_imgui_light'] = function(a0) {
    if (!checkClass(a0, UiWindow)) throw Error('style_imgui_light(0:ui_window): expected UiWindow');
    _two_style_imgui_light_1(/*ui_window*/a0.__ptr);
};
Module['style_imgui_classic'] = function(a0) {
    if (!checkClass(a0, UiWindow)) throw Error('style_imgui_classic(0:ui_window): expected UiWindow');
    _two_style_imgui_classic_1(/*ui_window*/a0.__ptr);
};
Module['ui']['widget'] = function(a0, a1, a2, a3, a4, a5) {
    if (a3 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('widget(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('widget(1:parent): expected Widget'); if (!checkClass(a2, Style)) throw Error('widget(2:style): expected Style'); }
    else if (a4 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('widget(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('widget(1:parent): expected Widget'); if (!checkClass(a2, Style)) throw Error('widget(2:style): expected Style'); if (typeof a3 !== 'boolean') throw Error('widget(3:open): expected boolean'); }
    else if (a5 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('widget(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('widget(1:parent): expected Widget'); if (!checkClass(a2, Style)) throw Error('widget(2:style): expected Style'); if (typeof a3 !== 'boolean') throw Error('widget(3:open): expected boolean'); if (typeof a4 !== 'number') throw Error('widget(4:length): expected integer'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('widget(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('widget(1:parent): expected Widget'); if (!checkClass(a2, Style)) throw Error('widget(2:style): expected Style'); if (typeof a3 !== 'boolean') throw Error('widget(3:open): expected boolean'); if (typeof a4 !== 'number') throw Error('widget(4:length): expected integer'); if (!checkClass(a5, v2_uint)) throw Error('widget(5:index): expected v2<uint>'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_widget_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*style*/a2.__ptr), Widget); }
    else if (a4 === undefined) { return wrapPointer(_two_ui_widget_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*style*/a2.__ptr, /*open*/a3), Widget); }
    else if (a5 === undefined) { return wrapPointer(_two_ui_widget_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*style*/a2.__ptr, /*open*/a3, /*length*/a4), Widget); }
    else { return wrapPointer(_two_ui_widget_6(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*style*/a2.__ptr, /*open*/a3, /*length*/a4, /*index*/a5.__ptr), Widget); }
};
Module['ui']['item'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a3 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('item(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('item(1:parent): expected Widget'); if (!checkClass(a2, Style)) throw Error('item(2:style): expected Style'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('item(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('item(1:parent): expected Widget'); if (!checkClass(a2, Style)) throw Error('item(2:style): expected Style'); if (typeof a3 !== 'string') throw Error('item(3:content): expected string'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_item_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*style*/a2.__ptr), Widget); }
    else { return wrapPointer(_two_ui_item_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*style*/a2.__ptr, ensureString(/*content*/a3)), Widget); }
};
Module['ui']['multi_item'] = function(a0, a1, a2, a3, a4) {
    if (a4 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('multi_item(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('multi_item(1:parent): expected Widget'); if (!checkClass(a2, Style)) throw Error('multi_item(2:style): expected Style');  }
    else { if (!checkClass(a0, NodeKey)) throw Error('multi_item(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('multi_item(1:parent): expected Widget'); if (!checkClass(a2, Style)) throw Error('multi_item(2:style): expected Style');  if (!checkClass(a4, Style)) throw Error('multi_item(4:element_style): expected Style'); }
    if (a4 === undefined) { return wrapPointer(_two_ui_multi_item_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*style*/a2.__ptr, ensureInt8(/*elements*/a3), /*elements*/a3.length), Widget); }
    else { return wrapPointer(_two_ui_multi_item_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*style*/a2.__ptr, ensureInt8(/*elements*/a3), /*elements*/a3.length, /*element_style*/a4.__ptr), Widget); }
};
Module['ui']['spanner'] = function(a0, a1, a2, a3, a4) {
    if (!checkClass(a0, NodeKey)) throw Error('spanner(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('spanner(1:parent): expected Widget'); if (!checkClass(a2, Style)) throw Error('spanner(2:style): expected Style'); if (typeof a3 !== 'number') throw Error('spanner(3:dim): expected integer'); if (typeof a4 !== 'number') throw Error('spanner(4:span): expected number');
    return wrapPointer(_two_ui_spanner_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*style*/a2.__ptr, /*dim*/a3, /*span*/a4), Widget);
};
Module['ui']['spacer'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('spacer(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('spacer(1:parent): expected Widget');
    return wrapPointer(_two_ui_spacer_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['separator'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('separator(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('separator(1:parent): expected Widget');
    return wrapPointer(_two_ui_separator_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['icon'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('icon(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('icon(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('icon(2:image): expected string');
    return wrapPointer(_two_ui_icon_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*image*/a2)), Widget);
};
Module['ui']['label'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('label(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('label(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('label(2:label): expected string');
    return wrapPointer(_two_ui_label_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*label*/a2)), Widget);
};
Module['ui']['title'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('title(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('title(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('title(2:label): expected string');
    return wrapPointer(_two_ui_title_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*label*/a2)), Widget);
};
Module['ui']['message'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('message(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('message(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('message(2:label): expected string');
    return wrapPointer(_two_ui_message_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*label*/a2)), Widget);
};
Module['ui']['text'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('text(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('text(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('text(2:label): expected string');
    return wrapPointer(_two_ui_text_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*label*/a2)), Widget);
};
Module['ui']['bullet'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('bullet(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('bullet(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('bullet(2:label): expected string');
    return wrapPointer(_two_ui_bullet_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*label*/a2)), Widget);
};
Module['ui']['selectable'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('selectable(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('selectable(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('selectable(2:label): expected string'); if (typeof a3 !== 'boolean') throw Error('selectable(3:selected): expected boolean');
    return wrapPointer(_two_ui_selectable_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*label*/a2), /*selected*/a3), Widget);
};
Module['ui']['button'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('button(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('button(1:parent): expected Widget'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('button(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('button(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('button(2:content): expected string'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_button_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget); }
    else { return wrapPointer(_two_ui_button_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*content*/a2)), Widget); }
};
Module['ui']['toggle'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a3 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('toggle(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('toggle(1:parent): expected Widget'); if (typeof a2 !== 'boolean') throw Error('toggle(2:on): expected boolean'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('toggle(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('toggle(1:parent): expected Widget'); if (typeof a2 !== 'boolean') throw Error('toggle(2:on): expected boolean'); if (typeof a3 !== 'string') throw Error('toggle(3:content): expected string'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_toggle_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*on*/a2), Widget); }
    else { return wrapPointer(_two_ui_toggle_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*on*/a2, ensureString(/*content*/a3)), Widget); }
};
Module['ui']['multi_button'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('multi_button(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('multi_button(1:parent): expected Widget');  }
    else { if (!checkClass(a0, NodeKey)) throw Error('multi_button(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('multi_button(1:parent): expected Widget');  if (!checkClass(a3, Style)) throw Error('multi_button(3:element_style): expected Style'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_multi_button_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureInt8(/*elements*/a2), /*elements*/a2.length), Widget); }
    else { return wrapPointer(_two_ui_multi_button_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureInt8(/*elements*/a2), /*elements*/a2.length, /*element_style*/a3.__ptr), Widget); }
};
Module['ui']['multi_toggle'] = function(a0, a1, a2, a3, a4) {
    if (a4 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('multi_toggle(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('multi_toggle(1:parent): expected Widget'); if (typeof a2 !== 'boolean') throw Error('multi_toggle(2:on): expected boolean');  }
    else { if (!checkClass(a0, NodeKey)) throw Error('multi_toggle(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('multi_toggle(1:parent): expected Widget'); if (typeof a2 !== 'boolean') throw Error('multi_toggle(2:on): expected boolean');  if (!checkClass(a4, Style)) throw Error('multi_toggle(4:element_style): expected Style'); }
    if (a4 === undefined) { return wrapPointer(_two_ui_multi_toggle_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*on*/a2, ensureInt8(/*elements*/a3), /*elements*/a3.length), Widget); }
    else { return wrapPointer(_two_ui_multi_toggle_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*on*/a2, ensureInt8(/*elements*/a3), /*elements*/a3.length, /*element_style*/a4.__ptr), Widget); }
};
Module['ui']['modal_button'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('modal_button(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('modal_button(1:screen): expected Widget'); if (!checkClass(a2, Widget)) throw Error('modal_button(2:parent): expected Widget'); if (typeof a3 !== 'string') throw Error('modal_button(3:content): expected string'); if (typeof a4 !== 'number') throw Error('modal_button(4:mode): expected integer');
    return !!(_two_ui_modal_button_5(/*id*/a0.__ptr, /*screen*/a1.__ptr, /*parent*/a2.__ptr, ensureString(/*content*/a3), /*mode*/a4));
};
Module['ui']['modal_multi_button'] = function(a0, a1, a2, a3, a4) {
    if (!checkClass(a0, NodeKey)) throw Error('modal_multi_button(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('modal_multi_button(1:screen): expected Widget'); if (!checkClass(a2, Widget)) throw Error('modal_multi_button(2:parent): expected Widget');  if (typeof a4 !== 'number') throw Error('modal_multi_button(4:mode): expected integer');
    return !!(_two_ui_modal_multi_button_5(/*id*/a0.__ptr, /*screen*/a1.__ptr, /*parent*/a2.__ptr, ensureInt8(/*elements*/a3), /*elements*/a3.length, /*mode*/a4));
};
Module['ui']['checkbox'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('checkbox(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('checkbox(1:parent): expected Widget'); if (typeof a2 !== 'boolean') throw Error('checkbox(2:on): expected boolean');
    return wrapPointer(_two_ui_checkbox_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*on*/a2), Widget);
};
Module['ui']['fill_bar'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('fill_bar(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('fill_bar(1:parent): expected Widget'); if (typeof a2 !== 'number') throw Error('fill_bar(2:percentage): expected number'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('fill_bar(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('fill_bar(1:parent): expected Widget'); if (typeof a2 !== 'number') throw Error('fill_bar(2:percentage): expected number'); if (typeof a3 !== 'number') throw Error('fill_bar(3:dim): expected integer'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_fill_bar_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*percentage*/a2), Widget); }
    else { return wrapPointer(_two_ui_fill_bar_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*percentage*/a2, /*dim*/a3), Widget); }
};
Module['ui']['image256'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a4 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('image256(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('image256(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('image256(2:name): expected string'); if (!checkClass(a3, Image256)) throw Error('image256(3:source): expected Image256'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('image256(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('image256(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('image256(2:name): expected string'); if (!checkClass(a3, Image256)) throw Error('image256(3:source): expected Image256'); if (!checkClass(a4, v2_float)) throw Error('image256(4:size): expected v2<float>'); }
    if (a4 === undefined) { return wrapPointer(_two_ui_image256_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*source*/a3.__ptr), Widget); }
    else { return wrapPointer(_two_ui_image256_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*source*/a3.__ptr, /*size*/a4.__ptr), Widget); }
};
Module['ui']['radio_choice'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('radio_choice(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('radio_choice(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('radio_choice(2:label): expected string'); if (typeof a3 !== 'boolean') throw Error('radio_choice(3:active): expected boolean');
    return wrapPointer(_two_ui_radio_choice_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*label*/a2), /*active*/a3), Widget);
};
Module['ui']['radio_button'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('radio_button(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('radio_button(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('radio_button(2:label): expected string'); if (typeof a3 !== 'number') throw Error('radio_button(3:value): expected integer'); if (typeof a4 !== 'number') throw Error('radio_button(4:index): expected integer');
    return wrapPointer(_two_ui_radio_button_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*label*/a2), /*value*/a3, /*index*/a4), Widget);
};
Module['ui']['radio_switch'] = function(a0, a1, a2, a3, a4) {
    if (a4 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('radio_switch(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('radio_switch(1:parent): expected Widget');  if (typeof a3 !== 'number') throw Error('radio_switch(3:value): expected integer'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('radio_switch(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('radio_switch(1:parent): expected Widget');  if (typeof a3 !== 'number') throw Error('radio_switch(3:value): expected integer'); if (typeof a4 !== 'number') throw Error('radio_switch(4:dim): expected integer'); }
    if (a4 === undefined) { return !!(_two_ui_radio_switch_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureInt8(/*labels*/a2), /*labels*/a2.length, /*value*/a3)); }
    else { return !!(_two_ui_radio_switch_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureInt8(/*labels*/a2), /*labels*/a2.length, /*value*/a3, /*dim*/a4)); }
};
Module['ui']['popdown'] = function(a0, a1, a2, a3, a4, a5) {
    if (!checkClass(a0, NodeKey)) throw Error('popdown(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('popdown(1:parent): expected Widget');  if (typeof a3 !== 'number') throw Error('popdown(3:value): expected integer'); if (!checkClass(a4, v2_float)) throw Error('popdown(4:position): expected v2<float>'); if (typeof a5 !== 'number') throw Error('popdown(5:flags): expected integer');
    return !!(_two_ui_popdown_6(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureInt8(/*choices*/a2), /*choices*/a2.length, /*value*/a3, /*position*/a4.__ptr, /*flags*/a5));
};
Module['ui']['dropdown_input'] = function(a0, a1, a2, a3, a4) {
    if (a4 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('dropdown_input(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('dropdown_input(1:parent): expected Widget');  if (typeof a3 !== 'number') throw Error('dropdown_input(3:value): expected integer'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('dropdown_input(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('dropdown_input(1:parent): expected Widget');  if (typeof a3 !== 'number') throw Error('dropdown_input(3:value): expected integer'); if (typeof a4 !== 'boolean') throw Error('dropdown_input(4:compact): expected boolean'); }
    if (a4 === undefined) { return !!(_two_ui_dropdown_input_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureInt8(/*choices*/a2), /*choices*/a2.length, /*value*/a3)); }
    else { return !!(_two_ui_dropdown_input_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureInt8(/*choices*/a2), /*choices*/a2.length, /*value*/a3, /*compact*/a4)); }
};
Module['ui']['typedown_input'] = function(a0, a1, a2, a3) {
    if (!checkClass(a0, NodeKey)) throw Error('typedown_input(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('typedown_input(1:parent): expected Widget');  if (typeof a3 !== 'number') throw Error('typedown_input(3:value): expected integer');
    return !!(_two_ui_typedown_input_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureInt8(/*choices*/a2), /*choices*/a2.length, /*value*/a3));
};
Module['ui']['menu_choice'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a3 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('menu_choice(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('menu_choice(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('menu_choice(2:content): expected string'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('menu_choice(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('menu_choice(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('menu_choice(2:content): expected string'); if (typeof a3 !== 'string') throw Error('menu_choice(3:shortcut): expected string'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_menu_choice_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*content*/a2)), Widget); }
    else { return wrapPointer(_two_ui_menu_choice_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*content*/a2), ensureString(/*shortcut*/a3)), Widget); }
};
Module['ui']['menu_option'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('menu_option(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('menu_option(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('menu_option(2:content): expected string'); if (typeof a3 !== 'string') throw Error('menu_option(3:shortcut): expected string'); if (typeof a4 !== 'boolean') throw Error('menu_option(4:enabled): expected boolean');
    return wrapPointer(_two_ui_menu_option_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*content*/a2), ensureString(/*shortcut*/a3), /*enabled*/a4), Widget);
};
Module['ui']['menubar'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('menubar(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('menubar(1:parent): expected Widget');
    return wrapPointer(_two_ui_menubar_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['toolbutton'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('toolbutton(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('toolbutton(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('toolbutton(2:icon): expected string');
    return wrapPointer(_two_ui_toolbutton_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*icon*/a2)), Widget);
};
Module['ui']['tooldock'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('tooldock(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('tooldock(1:parent): expected Widget');
    return wrapPointer(_two_ui_tooldock_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['toolbar'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('toolbar(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('toolbar(1:parent): expected Widget'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('toolbar(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('toolbar(1:parent): expected Widget'); if (typeof a2 !== 'boolean') throw Error('toolbar(2:wrap): expected boolean'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_toolbar_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget); }
    else { return wrapPointer(_two_ui_toolbar_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*wrap*/a2), Widget); }
};
Module['ui']['columns'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('columns(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('columns(1:parent): expected Widget'); 
    return wrapPointer(_two_ui_columns_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureFloat32(/*weights*/a2), /*weights*/a2.length), Widget);
};
Module['ui']['table'] = function(a0, a1, a2, a3) {
    if (!checkClass(a0, NodeKey)) throw Error('table(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('table(1:parent): expected Widget');  
    return wrapPointer(_two_ui_table_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureInt8(/*columns*/a2), /*columns*/a2.length, ensureFloat32(/*weights*/a3), /*weights*/a3.length), Widget);
};
Module['ui']['table_row'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('table_row(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('table_row(1:parent): expected Widget');
    return wrapPointer(_two_ui_table_row_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['table_separator'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('table_separator(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('table_separator(1:parent): expected Widget');
    return wrapPointer(_two_ui_table_separator_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['tree'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('tree(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('tree(1:parent): expected Widget');
    return wrapPointer(_two_ui_tree_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['row'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('row(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('row(1:parent): expected Widget');
    return wrapPointer(_two_ui_row_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['header'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('header(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('header(1:parent): expected Widget');
    return wrapPointer(_two_ui_header_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['div'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('div(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('div(1:parent): expected Widget');
    return wrapPointer(_two_ui_div_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['stack'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('stack(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('stack(1:parent): expected Widget');
    return wrapPointer(_two_ui_stack_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['sheet'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('sheet(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('sheet(1:parent): expected Widget');
    return wrapPointer(_two_ui_sheet_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['board'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('board(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('board(1:parent): expected Widget');
    return wrapPointer(_two_ui_board_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['layout'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('layout(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('layout(1:parent): expected Widget');
    return wrapPointer(_two_ui_layout_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['indent'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('indent(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('indent(1:parent): expected Widget');
    return wrapPointer(_two_ui_indent_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['screen'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('screen(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('screen(1:parent): expected Widget');
    return wrapPointer(_two_ui_screen_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['decal'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('decal(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('decal(1:parent): expected Widget');
    return wrapPointer(_two_ui_decal_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['overlay'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('overlay(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('overlay(1:parent): expected Widget');
    return wrapPointer(_two_ui_overlay_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['title_header'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('title_header(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('title_header(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('title_header(2:title): expected string');
    return wrapPointer(_two_ui_title_header_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*title*/a2)), Widget);
};
Module['ui']['dummy'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('dummy(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('dummy(1:parent): expected Widget'); if (!checkClass(a2, v2_float)) throw Error('dummy(2:size): expected v2<float>');
    return wrapPointer(_two_ui_dummy_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*size*/a2.__ptr), Widget);
};
Module['ui']['popup'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('popup(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('popup(1:parent): expected Widget'); if (typeof a2 !== 'number') throw Error('popup(2:flags): expected integer');
    return wrapPointer(_two_ui_popup_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*flags*/a2), Widget);
};
Module['ui']['popup_at'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('popup_at(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('popup_at(1:parent): expected Widget'); if (!checkClass(a2, v2_float)) throw Error('popup_at(2:position): expected v2<float>'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('popup_at(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('popup_at(1:parent): expected Widget'); if (!checkClass(a2, v2_float)) throw Error('popup_at(2:position): expected v2<float>'); if (typeof a3 !== 'number') throw Error('popup_at(3:flags): expected integer'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_popup_at_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*position*/a2.__ptr), Widget); }
    else { return wrapPointer(_two_ui_popup_at_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*position*/a2.__ptr, /*flags*/a3), Widget); }
};
Module['ui']['modal'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('modal(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('modal(1:parent): expected Widget');
    return wrapPointer(_two_ui_modal_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['auto_modal'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('auto_modal(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('auto_modal(1:parent): expected Widget'); if (typeof a2 !== 'number') throw Error('auto_modal(2:mode): expected integer');
    return wrapPointer(_two_ui_auto_modal_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*mode*/a2), Widget);
};
Module['ui']['context'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('context(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('context(1:parent): expected Widget'); if (typeof a2 !== 'number') throw Error('context(2:mode): expected integer'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('context(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('context(1:parent): expected Widget'); if (typeof a2 !== 'number') throw Error('context(2:mode): expected integer'); if (typeof a3 !== 'number') throw Error('context(3:flags): expected integer'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_context_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*mode*/a2), Widget); }
    else { return wrapPointer(_two_ui_context_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*mode*/a2, /*flags*/a3), Widget); }
};
Module['ui']['hoverbox'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('hoverbox(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('hoverbox(1:parent): expected Widget'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('hoverbox(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('hoverbox(1:parent): expected Widget'); if (typeof a2 !== 'number') throw Error('hoverbox(2:delay): expected number'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_hoverbox_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget); }
    else { return wrapPointer(_two_ui_hoverbox_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*delay*/a2), Widget); }
};
Module['ui']['cursor'] = function(a0, a1, a2, a3, a4) {
    if (a4 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('cursor(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('cursor(1:parent): expected Widget'); if (!checkClass(a2, v2_float)) throw Error('cursor(2:position): expected v2<float>'); if (!checkClass(a3, Widget)) throw Error('cursor(3:hovered): expected Widget'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('cursor(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('cursor(1:parent): expected Widget'); if (!checkClass(a2, v2_float)) throw Error('cursor(2:position): expected v2<float>'); if (!checkClass(a3, Widget)) throw Error('cursor(3:hovered): expected Widget'); if (typeof a4 !== 'boolean') throw Error('cursor(4:locked): expected boolean'); }
    if (a4 === undefined) { return wrapPointer(_two_ui_cursor_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*position*/a2.__ptr, /*hovered*/a3.__ptr), Widget); }
    else { return wrapPointer(_two_ui_cursor_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*position*/a2.__ptr, /*hovered*/a3.__ptr, /*locked*/a4), Widget); }
};
Module['ui']['rectangle'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('rectangle(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('rectangle(1:parent): expected Widget'); if (!checkClass(a2, v4_float)) throw Error('rectangle(2:rect): expected v4<float>');
    return wrapPointer(_two_ui_rectangle_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*rect*/a2.__ptr), Widget);
};
Module['ui']['viewport'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('viewport(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('viewport(1:parent): expected Widget'); if (!checkClass(a2, v4_float)) throw Error('viewport(2:rect): expected v4<float>');
    return wrapPointer(_two_ui_viewport_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*rect*/a2.__ptr), Widget);
};
Module['ui']['dockspace'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('dockspace(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('dockspace(1:parent): expected Widget'); if (!checkClass(a2, Docksystem)) throw Error('dockspace(2:docksystem): expected Docksystem');
    return wrapPointer(_two_ui_dockspace_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*docksystem*/a2.__ptr), Dockspace);
};
Module['ui']['dockbar'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('dockbar(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('dockbar(1:parent): expected Widget'); if (!checkClass(a2, Docksystem)) throw Error('dockbar(2:docksystem): expected Docksystem');
    return wrapPointer(_two_ui_dockbar_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*docksystem*/a2.__ptr), Dockbar);
};
Module['ui']['dockitem'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('dockitem(0:parent): expected Widget'); if (!checkClass(a1, Docksystem)) throw Error('dockitem(1:docksystem): expected Docksystem'); if (typeof a2 !== 'string') throw Error('dockitem(2:name): expected string');
    return wrapPointer(_two_ui_dockitem_3(/*parent*/a0.__ptr, /*docksystem*/a1.__ptr, ensureString(/*name*/a2)), Widget);
};
Module['ui']['drag_float'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('drag_float(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('drag_float(1:parent): expected Widget'); if (typeof a2 !== 'number') throw Error('drag_float(2:value): expected number'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('drag_float(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('drag_float(1:parent): expected Widget'); if (typeof a2 !== 'number') throw Error('drag_float(2:value): expected number'); if (typeof a3 !== 'number') throw Error('drag_float(3:step): expected number'); }
    if (a3 === undefined) { return !!(_two_ui_drag_float_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*value*/a2)); }
    else { return !!(_two_ui_drag_float_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*value*/a2, /*step*/a3)); }
};
Module['ui']['float2_input'] = function(a0, a1, a2, a3, a4) {
    if (!checkClass(a0, NodeKey)) throw Error('float2_input(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('float2_input(1:parent): expected Widget');   if (!checkClass(a4, StatDef_float)) throw Error('float2_input(4:def): expected StatDef<float>');
    return !!(_two_ui_float2_input_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureInt8(/*labels*/a2), /*labels*/a2.length, ensureFloat32(/*vals*/a3), /*vals*/a3.length, /*def*/a4.__ptr));
};
Module['ui']['float3_input'] = function(a0, a1, a2, a3, a4) {
    if (!checkClass(a0, NodeKey)) throw Error('float3_input(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('float3_input(1:parent): expected Widget');   if (!checkClass(a4, StatDef_float)) throw Error('float3_input(4:def): expected StatDef<float>');
    return !!(_two_ui_float3_input_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureInt8(/*labels*/a2), /*labels*/a2.length, ensureFloat32(/*vals*/a3), /*vals*/a3.length, /*def*/a4.__ptr));
};
Module['ui']['float4_input'] = function(a0, a1, a2, a3, a4) {
    if (!checkClass(a0, NodeKey)) throw Error('float4_input(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('float4_input(1:parent): expected Widget');   if (!checkClass(a4, StatDef_float)) throw Error('float4_input(4:def): expected StatDef<float>');
    return !!(_two_ui_float4_input_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureInt8(/*labels*/a2), /*labels*/a2.length, ensureFloat32(/*vals*/a3), /*vals*/a3.length, /*def*/a4.__ptr));
};
Module['ui']['float2_slider'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('float2_slider(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('float2_slider(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('float2_slider(2:label): expected string');   if (!checkClass(a5, StatDef_float)) throw Error('float2_slider(5:def): expected StatDef<float>');
    return !!(_two_ui_float2_slider_6(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*label*/a2), ensureInt8(/*labels*/a3), /*labels*/a3.length, ensureFloat32(/*vals*/a4), /*vals*/a4.length, /*def*/a5.__ptr));
};
Module['ui']['float3_slider'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('float3_slider(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('float3_slider(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('float3_slider(2:label): expected string');   if (!checkClass(a5, StatDef_float)) throw Error('float3_slider(5:def): expected StatDef<float>');
    return !!(_two_ui_float3_slider_6(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*label*/a2), ensureInt8(/*labels*/a3), /*labels*/a3.length, ensureFloat32(/*vals*/a4), /*vals*/a4.length, /*def*/a5.__ptr));
};
Module['ui']['float4_slider'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('float4_slider(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('float4_slider(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('float4_slider(2:label): expected string');   if (!checkClass(a5, StatDef_float)) throw Error('float4_slider(5:def): expected StatDef<float>');
    return !!(_two_ui_float4_slider_6(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*label*/a2), ensureInt8(/*labels*/a3), /*labels*/a3.length, ensureFloat32(/*vals*/a4), /*vals*/a4.length, /*def*/a5.__ptr));
};
Module['ui']['vec2_edit'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('vec2_edit(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('vec2_edit(1:parent): expected Widget'); if (!checkClass(a2, v2_float)) throw Error('vec2_edit(2:vec): expected v2<float>');
    return !!(_two_ui_vec2_edit_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*vec*/a2.__ptr));
};
Module['ui']['vec3_edit'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('vec3_edit(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('vec3_edit(1:parent): expected Widget'); if (!checkClass(a2, v3_float)) throw Error('vec3_edit(2:vec): expected v3<float>');
    return !!(_two_ui_vec3_edit_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*vec*/a2.__ptr));
};
Module['ui']['quat_edit'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('quat_edit(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('quat_edit(1:parent): expected Widget'); if (!checkClass(a2, quat)) throw Error('quat_edit(2:quat): expected quat');
    return !!(_two_ui_quat_edit_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*quat*/a2.__ptr));
};
Module['ui']['color_display'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('color_display(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('color_display(1:parent): expected Widget'); if (!checkClass(a2, Colour)) throw Error('color_display(2:value): expected Colour');
    return wrapPointer(_two_ui_color_display_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*value*/a2.__ptr), Widget);
};
Module['ui']['color_edit'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('color_edit(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('color_edit(1:parent): expected Widget'); if (!checkClass(a2, Colour)) throw Error('color_edit(2:value): expected Colour');
    return !!(_two_ui_color_edit_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*value*/a2.__ptr));
};
Module['ui']['color_edit_simple'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('color_edit_simple(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('color_edit_simple(1:parent): expected Widget'); if (!checkClass(a2, Colour)) throw Error('color_edit_simple(2:value): expected Colour');
    return !!(_two_ui_color_edit_simple_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*value*/a2.__ptr));
};
Module['ui']['color_toggle_edit'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('color_toggle_edit(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('color_toggle_edit(1:parent): expected Widget'); if (!checkClass(a2, Colour)) throw Error('color_toggle_edit(2:value): expected Colour');
    return !!(_two_ui_color_toggle_edit_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*value*/a2.__ptr));
};
Module['ui']['curve_graph'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('curve_graph(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('curve_graph(1:parent): expected Widget');  }
    else { if (!checkClass(a0, NodeKey)) throw Error('curve_graph(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('curve_graph(1:parent): expected Widget');   }
    if (a3 === undefined) { return !!(_two_ui_curve_graph_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureFloat32(/*values*/a2), /*values*/a2.length)); }
    else { return !!(_two_ui_curve_graph_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureFloat32(/*values*/a2), /*values*/a2.length, ensureFloat32(/*points*/a3), /*points*/a3.length)); }
};
Module['ui']['curve_edit'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('curve_edit(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('curve_edit(1:parent): expected Widget');  }
    else { if (!checkClass(a0, NodeKey)) throw Error('curve_edit(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('curve_edit(1:parent): expected Widget');   }
    if (a3 === undefined) { return !!(_two_ui_curve_edit_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureFloat32(/*values*/a2), /*values*/a2.length)); }
    else { return !!(_two_ui_curve_edit_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureFloat32(/*values*/a2), /*values*/a2.length, ensureFloat32(/*points*/a3), /*points*/a3.length)); }
};
Module['ui']['flag_field'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (a5 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('flag_field(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('flag_field(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('flag_field(2:name): expected string'); if (typeof a3 !== 'number') throw Error('flag_field(3:value): expected integer'); if (typeof a4 !== 'number') throw Error('flag_field(4:shift): expected integer'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('flag_field(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('flag_field(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('flag_field(2:name): expected string'); if (typeof a3 !== 'number') throw Error('flag_field(3:value): expected integer'); if (typeof a4 !== 'number') throw Error('flag_field(4:shift): expected integer'); if (typeof a5 !== 'boolean') throw Error('flag_field(5:reverse): expected boolean'); }
    if (a5 === undefined) { return !!(_two_ui_flag_field_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*value*/a3, /*shift*/a4)); }
    else { return !!(_two_ui_flag_field_6(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*value*/a3, /*shift*/a4, /*reverse*/a5)); }
};
Module['ui']['radio_field'] = function(a0, a1, a2, a3, a4, a5, a6) {
    ensureCache.prepare();
    if (a5 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('radio_field(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('radio_field(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('radio_field(2:name): expected string');  if (typeof a4 !== 'number') throw Error('radio_field(4:value): expected integer'); }
    else if (a6 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('radio_field(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('radio_field(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('radio_field(2:name): expected string');  if (typeof a4 !== 'number') throw Error('radio_field(4:value): expected integer'); if (typeof a5 !== 'number') throw Error('radio_field(5:dim): expected integer'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('radio_field(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('radio_field(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('radio_field(2:name): expected string');  if (typeof a4 !== 'number') throw Error('radio_field(4:value): expected integer'); if (typeof a5 !== 'number') throw Error('radio_field(5:dim): expected integer'); if (typeof a6 !== 'boolean') throw Error('radio_field(6:reverse): expected boolean'); }
    if (a5 === undefined) { return !!(_two_ui_radio_field_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), ensureInt8(/*choices*/a3), /*choices*/a3.length, /*value*/a4)); }
    else if (a6 === undefined) { return !!(_two_ui_radio_field_6(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), ensureInt8(/*choices*/a3), /*choices*/a3.length, /*value*/a4, /*dim*/a5)); }
    else { return !!(_two_ui_radio_field_7(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), ensureInt8(/*choices*/a3), /*choices*/a3.length, /*value*/a4, /*dim*/a5, /*reverse*/a6)); }
};
Module['ui']['dropdown_field'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (a5 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('dropdown_field(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('dropdown_field(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('dropdown_field(2:name): expected string');  if (typeof a4 !== 'number') throw Error('dropdown_field(4:value): expected integer'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('dropdown_field(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('dropdown_field(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('dropdown_field(2:name): expected string');  if (typeof a4 !== 'number') throw Error('dropdown_field(4:value): expected integer'); if (typeof a5 !== 'boolean') throw Error('dropdown_field(5:reverse): expected boolean'); }
    if (a5 === undefined) { return !!(_two_ui_dropdown_field_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), ensureInt8(/*choices*/a3), /*choices*/a3.length, /*value*/a4)); }
    else { return !!(_two_ui_dropdown_field_6(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), ensureInt8(/*choices*/a3), /*choices*/a3.length, /*value*/a4, /*reverse*/a5)); }
};
Module['ui']['typedown_field'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (a5 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('typedown_field(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('typedown_field(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('typedown_field(2:name): expected string');  if (typeof a4 !== 'number') throw Error('typedown_field(4:value): expected integer'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('typedown_field(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('typedown_field(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('typedown_field(2:name): expected string');  if (typeof a4 !== 'number') throw Error('typedown_field(4:value): expected integer'); if (typeof a5 !== 'boolean') throw Error('typedown_field(5:reverse): expected boolean'); }
    if (a5 === undefined) { return !!(_two_ui_typedown_field_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), ensureInt8(/*choices*/a3), /*choices*/a3.length, /*value*/a4)); }
    else { return !!(_two_ui_typedown_field_6(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), ensureInt8(/*choices*/a3), /*choices*/a3.length, /*value*/a4, /*reverse*/a5)); }
};
Module['ui']['color_field'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a4 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('color_field(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('color_field(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('color_field(2:name): expected string'); if (!checkClass(a3, Colour)) throw Error('color_field(3:value): expected Colour'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('color_field(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('color_field(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('color_field(2:name): expected string'); if (!checkClass(a3, Colour)) throw Error('color_field(3:value): expected Colour'); if (typeof a4 !== 'boolean') throw Error('color_field(4:reverse): expected boolean'); }
    if (a4 === undefined) { return !!(_two_ui_color_field_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*value*/a3.__ptr)); }
    else { return !!(_two_ui_color_field_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*value*/a3.__ptr, /*reverse*/a4)); }
};
Module['ui']['color_display_field'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a4 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('color_display_field(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('color_display_field(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('color_display_field(2:name): expected string'); if (!checkClass(a3, Colour)) throw Error('color_display_field(3:value): expected Colour'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('color_display_field(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('color_display_field(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('color_display_field(2:name): expected string'); if (!checkClass(a3, Colour)) throw Error('color_display_field(3:value): expected Colour'); if (typeof a4 !== 'boolean') throw Error('color_display_field(4:reverse): expected boolean'); }
    if (a4 === undefined) { _two_ui_color_display_field_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*value*/a3.__ptr); }
    else { _two_ui_color_display_field_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*value*/a3.__ptr, /*reverse*/a4); }
};
Module['ui']['input_bool'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('input<bool>(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('input<bool>(1:parent): expected Widget'); if (typeof a2 !== 'boolean') throw Error('input<bool>(2:value): expected boolean');
    return !!(_two_ui_input_bool_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*value*/a2));
};
Module['ui']['input_int'] = function(a0, a1, a2, a3) {
    if (!checkClass(a0, NodeKey)) throw Error('input<int>(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('input<int>(1:parent): expected Widget'); if (typeof a2 !== 'number') throw Error('input<int>(2:value): expected integer'); if (!checkClass(a3, StatDef_int)) throw Error('input<int>(3:def): expected StatDef<int>');
    return !!(_two_ui_input_int_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*value*/a2, /*def*/a3.__ptr));
};
Module['ui']['input_float'] = function(a0, a1, a2, a3) {
    if (!checkClass(a0, NodeKey)) throw Error('input<float>(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('input<float>(1:parent): expected Widget'); if (typeof a2 !== 'number') throw Error('input<float>(2:value): expected number'); if (!checkClass(a3, StatDef_float)) throw Error('input<float>(3:def): expected StatDef<float>');
    return !!(_two_ui_input_float_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*value*/a2, /*def*/a3.__ptr));
};
Module['ui']['field_bool'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a4 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('field<bool>(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('field<bool>(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('field<bool>(2:name): expected string'); if (typeof a3 !== 'boolean') throw Error('field<bool>(3:value): expected boolean'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('field<bool>(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('field<bool>(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('field<bool>(2:name): expected string'); if (typeof a3 !== 'boolean') throw Error('field<bool>(3:value): expected boolean'); if (typeof a4 !== 'boolean') throw Error('field<bool>(4:reverse): expected boolean'); }
    if (a4 === undefined) { return !!(_two_ui_field_bool_4(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*value*/a3)); }
    else { return !!(_two_ui_field_bool_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*value*/a3, /*reverse*/a4)); }
};
Module['ui']['field_int'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (a5 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('field<int>(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('field<int>(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('field<int>(2:name): expected string'); if (typeof a3 !== 'number') throw Error('field<int>(3:value): expected integer'); if (!checkClass(a4, StatDef_int)) throw Error('field<int>(4:def): expected StatDef<int>'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('field<int>(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('field<int>(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('field<int>(2:name): expected string'); if (typeof a3 !== 'number') throw Error('field<int>(3:value): expected integer'); if (!checkClass(a4, StatDef_int)) throw Error('field<int>(4:def): expected StatDef<int>'); if (typeof a5 !== 'boolean') throw Error('field<int>(5:reverse): expected boolean'); }
    if (a5 === undefined) { return !!(_two_ui_field_int_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*value*/a3, /*def*/a4.__ptr)); }
    else { return !!(_two_ui_field_int_6(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*value*/a3, /*def*/a4.__ptr, /*reverse*/a5)); }
};
Module['ui']['field_float'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (a5 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('field<float>(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('field<float>(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('field<float>(2:name): expected string'); if (typeof a3 !== 'number') throw Error('field<float>(3:value): expected number'); if (!checkClass(a4, StatDef_float)) throw Error('field<float>(4:def): expected StatDef<float>'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('field<float>(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('field<float>(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('field<float>(2:name): expected string'); if (typeof a3 !== 'number') throw Error('field<float>(3:value): expected number'); if (!checkClass(a4, StatDef_float)) throw Error('field<float>(4:def): expected StatDef<float>'); if (typeof a5 !== 'boolean') throw Error('field<float>(5:reverse): expected boolean'); }
    if (a5 === undefined) { return !!(_two_ui_field_float_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*value*/a3, /*def*/a4.__ptr)); }
    else { return !!(_two_ui_field_float_6(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2), /*value*/a3, /*def*/a4.__ptr, /*reverse*/a5)); }
};
Module['ui']['node_input'] = function(a0, a1, a2, a3, a4, a5, a6) {
    ensureCache.prepare();
    if (a3 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('node_input(0:id): expected NodeKey'); if (!checkClass(a1, Node)) throw Error('node_input(1:node): expected Node'); if (typeof a2 !== 'string') throw Error('node_input(2:name): expected string'); }
    else if (a4 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('node_input(0:id): expected NodeKey'); if (!checkClass(a1, Node)) throw Error('node_input(1:node): expected Node'); if (typeof a2 !== 'string') throw Error('node_input(2:name): expected string'); if (typeof a3 !== 'string') throw Error('node_input(3:icon): expected string'); }
    else if (a5 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('node_input(0:id): expected NodeKey'); if (!checkClass(a1, Node)) throw Error('node_input(1:node): expected Node'); if (typeof a2 !== 'string') throw Error('node_input(2:name): expected string'); if (typeof a3 !== 'string') throw Error('node_input(3:icon): expected string'); if (!checkClass(a4, Colour)) throw Error('node_input(4:colour): expected Colour'); }
    else if (a6 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('node_input(0:id): expected NodeKey'); if (!checkClass(a1, Node)) throw Error('node_input(1:node): expected Node'); if (typeof a2 !== 'string') throw Error('node_input(2:name): expected string'); if (typeof a3 !== 'string') throw Error('node_input(3:icon): expected string'); if (!checkClass(a4, Colour)) throw Error('node_input(4:colour): expected Colour'); if (typeof a5 !== 'boolean') throw Error('node_input(5:active): expected boolean'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('node_input(0:id): expected NodeKey'); if (!checkClass(a1, Node)) throw Error('node_input(1:node): expected Node'); if (typeof a2 !== 'string') throw Error('node_input(2:name): expected string'); if (typeof a3 !== 'string') throw Error('node_input(3:icon): expected string'); if (!checkClass(a4, Colour)) throw Error('node_input(4:colour): expected Colour'); if (typeof a5 !== 'boolean') throw Error('node_input(5:active): expected boolean'); if (typeof a6 !== 'boolean') throw Error('node_input(6:connected): expected boolean'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_node_input_3(/*id*/a0.__ptr, /*node*/a1.__ptr, ensureString(/*name*/a2)), NodePlug); }
    else if (a4 === undefined) { return wrapPointer(_two_ui_node_input_4(/*id*/a0.__ptr, /*node*/a1.__ptr, ensureString(/*name*/a2), ensureString(/*icon*/a3)), NodePlug); }
    else if (a5 === undefined) { return wrapPointer(_two_ui_node_input_5(/*id*/a0.__ptr, /*node*/a1.__ptr, ensureString(/*name*/a2), ensureString(/*icon*/a3), /*colour*/a4.__ptr), NodePlug); }
    else if (a6 === undefined) { return wrapPointer(_two_ui_node_input_6(/*id*/a0.__ptr, /*node*/a1.__ptr, ensureString(/*name*/a2), ensureString(/*icon*/a3), /*colour*/a4.__ptr, /*active*/a5), NodePlug); }
    else { return wrapPointer(_two_ui_node_input_7(/*id*/a0.__ptr, /*node*/a1.__ptr, ensureString(/*name*/a2), ensureString(/*icon*/a3), /*colour*/a4.__ptr, /*active*/a5, /*connected*/a6), NodePlug); }
};
Module['ui']['node_output'] = function(a0, a1, a2, a3, a4, a5, a6) {
    ensureCache.prepare();
    if (a3 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('node_output(0:id): expected NodeKey'); if (!checkClass(a1, Node)) throw Error('node_output(1:node): expected Node'); if (typeof a2 !== 'string') throw Error('node_output(2:name): expected string'); }
    else if (a4 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('node_output(0:id): expected NodeKey'); if (!checkClass(a1, Node)) throw Error('node_output(1:node): expected Node'); if (typeof a2 !== 'string') throw Error('node_output(2:name): expected string'); if (typeof a3 !== 'string') throw Error('node_output(3:icon): expected string'); }
    else if (a5 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('node_output(0:id): expected NodeKey'); if (!checkClass(a1, Node)) throw Error('node_output(1:node): expected Node'); if (typeof a2 !== 'string') throw Error('node_output(2:name): expected string'); if (typeof a3 !== 'string') throw Error('node_output(3:icon): expected string'); if (!checkClass(a4, Colour)) throw Error('node_output(4:colour): expected Colour'); }
    else if (a6 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('node_output(0:id): expected NodeKey'); if (!checkClass(a1, Node)) throw Error('node_output(1:node): expected Node'); if (typeof a2 !== 'string') throw Error('node_output(2:name): expected string'); if (typeof a3 !== 'string') throw Error('node_output(3:icon): expected string'); if (!checkClass(a4, Colour)) throw Error('node_output(4:colour): expected Colour'); if (typeof a5 !== 'boolean') throw Error('node_output(5:active): expected boolean'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('node_output(0:id): expected NodeKey'); if (!checkClass(a1, Node)) throw Error('node_output(1:node): expected Node'); if (typeof a2 !== 'string') throw Error('node_output(2:name): expected string'); if (typeof a3 !== 'string') throw Error('node_output(3:icon): expected string'); if (!checkClass(a4, Colour)) throw Error('node_output(4:colour): expected Colour'); if (typeof a5 !== 'boolean') throw Error('node_output(5:active): expected boolean'); if (typeof a6 !== 'boolean') throw Error('node_output(6:connected): expected boolean'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_node_output_3(/*id*/a0.__ptr, /*node*/a1.__ptr, ensureString(/*name*/a2)), NodePlug); }
    else if (a4 === undefined) { return wrapPointer(_two_ui_node_output_4(/*id*/a0.__ptr, /*node*/a1.__ptr, ensureString(/*name*/a2), ensureString(/*icon*/a3)), NodePlug); }
    else if (a5 === undefined) { return wrapPointer(_two_ui_node_output_5(/*id*/a0.__ptr, /*node*/a1.__ptr, ensureString(/*name*/a2), ensureString(/*icon*/a3), /*colour*/a4.__ptr), NodePlug); }
    else if (a6 === undefined) { return wrapPointer(_two_ui_node_output_6(/*id*/a0.__ptr, /*node*/a1.__ptr, ensureString(/*name*/a2), ensureString(/*icon*/a3), /*colour*/a4.__ptr, /*active*/a5), NodePlug); }
    else { return wrapPointer(_two_ui_node_output_7(/*id*/a0.__ptr, /*node*/a1.__ptr, ensureString(/*name*/a2), ensureString(/*icon*/a3), /*colour*/a4.__ptr, /*active*/a5, /*connected*/a6), NodePlug); }
};
Module['ui']['node'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a3 === undefined) { if (!checkClass(a0, Canvas)) throw Error('node(0:parent): expected Canvas'); if (typeof a1 !== 'string') throw Error('node(1:title): expected string'); if (!checkClass(a2, v2_float)) throw Error('node(2:position): expected v2<float>'); }
    else if (a4 === undefined) { if (!checkClass(a0, Canvas)) throw Error('node(0:parent): expected Canvas'); if (typeof a1 !== 'string') throw Error('node(1:title): expected string'); if (!checkClass(a2, v2_float)) throw Error('node(2:position): expected v2<float>'); if (typeof a3 !== 'number') throw Error('node(3:order): expected integer'); }
    else { if (!checkClass(a0, Canvas)) throw Error('node(0:parent): expected Canvas'); if (typeof a1 !== 'string') throw Error('node(1:title): expected string'); if (!checkClass(a2, v2_float)) throw Error('node(2:position): expected v2<float>'); if (typeof a3 !== 'number') throw Error('node(3:order): expected integer'); if (!checkClass(a4, Ref)) throw Error('node(4:identity): expected Ref'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_node_3(/*parent*/a0.__ptr, ensureString(/*title*/a1), /*position*/a2.__ptr), Node); }
    else if (a4 === undefined) { return wrapPointer(_two_ui_node_4(/*parent*/a0.__ptr, ensureString(/*title*/a1), /*position*/a2.__ptr, /*order*/a3), Node); }
    else { return wrapPointer(_two_ui_node_5(/*parent*/a0.__ptr, ensureString(/*title*/a1), /*position*/a2.__ptr, /*order*/a3, ensureRef(/*identity*/a4), ensureRefType(/*identity*/a4)), Node); }
};
Module['ui']['node_cable'] = function(a0, a1, a2, a3) {
    if (!checkClass(a0, NodeKey)) throw Error('node_cable(0:id): expected NodeKey'); if (!checkClass(a1, Canvas)) throw Error('node_cable(1:canvas): expected Canvas'); if (!checkClass(a2, NodePlug)) throw Error('node_cable(2:plug_out): expected NodePlug'); if (!checkClass(a3, NodePlug)) throw Error('node_cable(3:plug_in): expected NodePlug');
    return wrapPointer(_two_ui_node_cable_4(/*id*/a0.__ptr, /*canvas*/a1.__ptr, /*plug_out*/a2.__ptr, /*plug_in*/a3.__ptr), Widget);
};
Module['ui']['canvas'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, NodeKey)) throw Error('canvas(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('canvas(1:parent): expected Widget'); }
    else { if (!checkClass(a0, NodeKey)) throw Error('canvas(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('canvas(1:parent): expected Widget'); if (typeof a2 !== 'number') throw Error('canvas(2:num_nodes): expected integer'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_canvas_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Canvas); }
    else { return wrapPointer(_two_ui_canvas_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, /*num_nodes*/a2), Canvas); }
};
Module['ui']['scrollable'] = function(a0, a1) {
    if (!checkClass(a0, NodeKey)) throw Error('scrollable(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('scrollable(1:parent): expected Widget');
    return wrapPointer(_two_ui_scrollable_2(/*id*/a0.__ptr, /*parent*/a1.__ptr), Widget);
};
Module['ui']['select_logic'] = function(a0, a1, a2) {
    if (!checkClass(a0, Widget)) throw Error('select_logic(0:element): expected Widget'); if (!checkClass(a1, Ref)) throw Error('select_logic(1:object): expected Ref'); if (!checkClass(a2, Ref)) throw Error('select_logic(2:selection): expected Ref');
    return !!(_two_ui_select_logic_3(/*element*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1), ensureRef(/*selection*/a2), ensureRefType(/*selection*/a2)));
};
Module['ui']['element'] = function(a0, a1, a2) {
    if (!checkClass(a0, NodeKey)) throw Error('element(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('element(1:parent): expected Widget'); if (!checkClass(a2, Ref)) throw Error('element(2:object): expected Ref');
    return wrapPointer(_two_ui_element_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureRef(/*object*/a2), ensureRefType(/*object*/a2)), Widget);
};
Module['ui']['dir_item'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('dir_item(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('dir_item(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('dir_item(2:name): expected string');
    return wrapPointer(_two_ui_dir_item_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2)), Widget);
};
Module['ui']['file_item'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('file_item(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('file_item(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('file_item(2:name): expected string');
    return wrapPointer(_two_ui_file_item_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2)), Widget);
};
Module['ui']['dir_node'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('dir_node(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('dir_node(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('dir_node(2:path): expected string'); if (typeof a3 !== 'string') throw Error('dir_node(3:name): expected string'); if (typeof a4 !== 'boolean') throw Error('dir_node(4:collapsed): expected boolean');
    return wrapPointer(_two_ui_dir_node_5(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*path*/a2), ensureString(/*name*/a3), /*collapsed*/a4), Widget);
};
Module['ui']['file_node'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('file_node(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('file_node(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('file_node(2:name): expected string');
    return wrapPointer(_two_ui_file_node_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*name*/a2)), Widget);
};
Module['ui']['file_tree'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, NodeKey)) throw Error('file_tree(0:id): expected NodeKey'); if (!checkClass(a1, Widget)) throw Error('file_tree(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('file_tree(2:path): expected string');
    return wrapPointer(_two_ui_file_tree_3(/*id*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*path*/a2)), Widget);
};

(function() {
    function setup() {
        Space.prototype.__type = _two_Space__type();
        ImageSkin.prototype.__type = _two_ImageSkin__type();
        Shadow.prototype.__type = _two_Shadow__type();
        Paint.prototype.__type = _two_Paint__type();
        TextPaint.prototype.__type = _two_TextPaint__type();
        Gradient.prototype.__type = _two_Gradient__type();
        InkStyle.prototype.__type = _two_InkStyle__type();
        Layout.prototype.__type = _two_Layout__type();
        Subskin.prototype.__type = _two_Subskin__type();
        Style.prototype.__type = _two_Style__type();
        UiRect.prototype.__type = _two_UiRect__type();
        Frame.prototype.__type = _two_Frame__type();
        Widget.prototype.__type = _two_Widget__type();
        TextCursor.prototype.__type = _two_TextCursor__type();
        TextSelection.prototype.__type = _two_TextSelection__type();
        TextMarker.prototype.__type = _two_TextMarker__type();
        Text.prototype.__type = _two_Text__type();
        TextEdit.prototype.__type = _two_TextEdit__type();
        NodeConnection.prototype.__type = _two_NodeConnection__type();
        Vg.prototype.__type = _two_Vg__type();
        Clipboard.prototype.__type = _two_Clipboard__type();
        UiWindow.prototype.__type = _two_UiWindow__type();
        User.prototype.__type = _two_User__type();
        Layer.prototype.__type = _two_Layer__type();
        Dock.prototype.__type = _two_Dock__type();
        Docksystem.prototype.__type = _two_Docksystem__type();
        Docker.prototype.__type = _two_Docker__type();
        Dockspace.prototype.__type = _two_Dockspace__type();
        Dockbar.prototype.__type = _two_Dockbar__type();
        NodePlug.prototype.__type = _two_NodePlug__type();
        Node.prototype.__type = _two_Node__type();
        CanvasConnect.prototype.__type = _two_CanvasConnect__type();
        Canvas.prototype.__type = _two_Canvas__type();
        Ui.prototype.__type = _two_Ui__type();
        // FlowAxis
        Module['FlowAxis'] = Module['FlowAxis'] || {};
        Module['FlowAxis']['Reading'] = _two_FlowAxis_Reading();
        Module['FlowAxis']['Paragraph'] = _two_FlowAxis_Paragraph();
        Module['FlowAxis']['Same'] = _two_FlowAxis_Same();
        Module['FlowAxis']['Flip'] = _two_FlowAxis_Flip();
        Module['FlowAxis']['None'] = _two_FlowAxis_None();
        // Pivot
        Module['Pivot'] = Module['Pivot'] || {};
        Module['Pivot']['Forward'] = _two_Pivot_Forward();
        Module['Pivot']['Reverse'] = _two_Pivot_Reverse();
        // Align
        Module['Align'] = Module['Align'] || {};
        Module['Align']['Left'] = _two_Align_Left();
        Module['Align']['Center'] = _two_Align_Center();
        Module['Align']['Right'] = _two_Align_Right();
        Module['Align']['OutLeft'] = _two_Align_OutLeft();
        Module['Align']['OutRight'] = _two_Align_OutRight();
        Module['Align']['Count'] = _two_Align_Count();
        // AutoLayout
        Module['AutoLayout'] = Module['AutoLayout'] || {};
        Module['AutoLayout']['None'] = _two_AutoLayout_None();
        Module['AutoLayout']['Size'] = _two_AutoLayout_Size();
        Module['AutoLayout']['Layout'] = _two_AutoLayout_Layout();
        // LayoutFlow
        Module['LayoutFlow'] = Module['LayoutFlow'] || {};
        Module['LayoutFlow']['Flow'] = _two_LayoutFlow_Flow();
        Module['LayoutFlow']['Overlay'] = _two_LayoutFlow_Overlay();
        Module['LayoutFlow']['Align'] = _two_LayoutFlow_Align();
        Module['LayoutFlow']['Free'] = _two_LayoutFlow_Free();
        // Sizing
        Module['Sizing'] = Module['Sizing'] || {};
        Module['Sizing']['Fixed'] = _two_Sizing_Fixed();
        Module['Sizing']['Shrink'] = _two_Sizing_Shrink();
        Module['Sizing']['Wrap'] = _two_Sizing_Wrap();
        Module['Sizing']['Expand'] = _two_Sizing_Expand();
        // Preset
        Module['Preset'] = Module['Preset'] || {};
        Module['Preset']['Sheet'] = _two_Preset_Sheet();
        Module['Preset']['Flex'] = _two_Preset_Flex();
        Module['Preset']['Item'] = _two_Preset_Item();
        Module['Preset']['Unit'] = _two_Preset_Unit();
        Module['Preset']['Block'] = _two_Preset_Block();
        Module['Preset']['Line'] = _two_Preset_Line();
        Module['Preset']['Stack'] = _two_Preset_Stack();
        Module['Preset']['Div'] = _two_Preset_Div();
        Module['Preset']['Spacer'] = _two_Preset_Spacer();
        Module['Preset']['Board'] = _two_Preset_Board();
        Module['Preset']['Layout'] = _two_Preset_Layout();
        // Clip
        Module['Clip'] = Module['Clip'] || {};
        Module['Clip']['None'] = _two_Clip_None();
        Module['Clip']['Clip'] = _two_Clip_Clip();
        Module['Clip']['Unclip'] = _two_Clip_Unclip();
        // Opacity
        Module['Opacity'] = Module['Opacity'] || {};
        Module['Opacity']['Opaque'] = _two_Opacity_Opaque();
        Module['Opacity']['Clear'] = _two_Opacity_Clear();
        Module['Opacity']['Hollow'] = _two_Opacity_Hollow();
        // WidgetState
        Module['NOSTATE'] = _two_WidgetState_NOSTATE();
        Module['CREATED'] = _two_WidgetState_CREATED();
        Module['HOVERED'] = _two_WidgetState_HOVERED();
        Module['PRESSED'] = _two_WidgetState_PRESSED();
        Module['ACTIVATED'] = _two_WidgetState_ACTIVATED();
        Module['ACTIVE'] = _two_WidgetState_ACTIVE();
        Module['SELECTED'] = _two_WidgetState_SELECTED();
        Module['DISABLED'] = _two_WidgetState_DISABLED();
        Module['DRAGGED'] = _two_WidgetState_DRAGGED();
        Module['FOCUSED'] = _two_WidgetState_FOCUSED();
        Module['CLOSED'] = _two_WidgetState_CLOSED();
        Module['OPEN'] = _two_WidgetState_OPEN();
        // PopupFlags
        Module['ui']['PopupFlags'] = Module['ui']['PopupFlags'] || {};
        Module['ui']['PopupFlags']['None'] = _two_ui_PopupFlags_None();
        Module['ui']['PopupFlags']['Modal'] = _two_ui_PopupFlags_Modal();
        Module['ui']['PopupFlags']['Clamp'] = _two_ui_PopupFlags_Clamp();
        Module['ui']['PopupFlags']['AutoClose'] = _two_ui_PopupFlags_AutoClose();
        Module['ui']['PopupFlags']['AutoModal'] = _two_ui_PopupFlags_AutoModal();
        // WindowState
        Module['WindowState'] = Module['WindowState'] || {};
        Module['WindowState']['None'] = _two_WindowState_None();
        Module['WindowState']['Header'] = _two_WindowState_Header();
        Module['WindowState']['Dockable'] = _two_WindowState_Dockable();
        Module['WindowState']['Closable'] = _two_WindowState_Closable();
        Module['WindowState']['Movable'] = _two_WindowState_Movable();
        Module['WindowState']['Sizable'] = _two_WindowState_Sizable();
        Module['WindowState']['Scrollable'] = _two_WindowState_Scrollable();
        Module['WindowState']['Menu'] = _two_WindowState_Menu();
        Module['WindowState']['Default'] = _two_WindowState_Default();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
