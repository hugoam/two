Module['ui'] = Module['ui'] || {};
Module['stl'] = Module['stl'] || {};
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
Object.defineProperty(Layout.prototype, "solver", {
    get: function() {
        return _two_Layout__get_solver(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Layout.solver: expected integer');
        _two_Layout__set_solver(this.__ptr, value);
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
Object.defineProperty(Widget.prototype, "index", {
    get: function() {
        return _two_Widget__get_index(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Widget.index: expected integer');
        _two_Widget__set_index(this.__ptr, value);
    }
});
Object.defineProperty(Widget.prototype, "open", {
    get: function() {
        return !!(_two_Widget__get_open(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Widget.open: expected boolean');
        _two_Widget__set_open(this.__ptr, value);
    }
});
Object.defineProperty(Widget.prototype, "body", {
    get: function() {
        return wrapPointer(_two_Widget__get_body(this.__ptr), Widget);
    },
    set: function(value) {
        if (!checkClass(value, Widget)) throw Error('Widget.body: expected Widget');
        _two_Widget__set_body(this.__ptr, value.__ptr);
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
TextEdit.prototype = Object.create(Widget.prototype);
TextEdit.prototype.constructor = TextEdit;
TextEdit.prototype.__class = TextEdit;
TextEdit.__base = Widget;
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
// FrameSolver
function FrameSolver() { throw "cannot construct a FrameSolver, no constructor in IDL" }
FrameSolver.prototype = Object.create(UiRect.prototype);
FrameSolver.prototype.constructor = FrameSolver;
FrameSolver.prototype.__class = FrameSolver;
FrameSolver.__base = UiRect;
FrameSolver.__cache = {};
Module['FrameSolver'] = FrameSolver;
FrameSolver.prototype["__destroy"] = FrameSolver.prototype.__destroy = function() {
    _two_FrameSolver__destroy(this.__ptr);
};
// RowSolver
function RowSolver() { throw "cannot construct a RowSolver, no constructor in IDL" }
RowSolver.prototype = Object.create(FrameSolver.prototype);
RowSolver.prototype.constructor = RowSolver;
RowSolver.prototype.__class = RowSolver;
RowSolver.__base = FrameSolver;
RowSolver.__cache = {};
Module['RowSolver'] = RowSolver;
RowSolver.prototype["__destroy"] = RowSolver.prototype.__destroy = function() {
    _two_RowSolver__destroy(this.__ptr);
};
// TableSolver
function TableSolver() { throw "cannot construct a TableSolver, no constructor in IDL" }
TableSolver.prototype = Object.create(WrapperObject.prototype);
TableSolver.prototype.constructor = TableSolver;
TableSolver.prototype.__class = TableSolver;
TableSolver.__cache = {};
Module['TableSolver'] = TableSolver;
TableSolver.prototype["__destroy"] = TableSolver.prototype.__destroy = function() {
    _two_TableSolver__destroy(this.__ptr);
};
// LineSolver
function LineSolver() { throw "cannot construct a LineSolver, no constructor in IDL" }
LineSolver.prototype = Object.create(RowSolver.prototype);
LineSolver.prototype.constructor = LineSolver;
LineSolver.prototype.__class = LineSolver;
LineSolver.__base = RowSolver;
LineSolver.__cache = {};
Module['LineSolver'] = LineSolver;
LineSolver.prototype["__destroy"] = LineSolver.prototype.__destroy = function() {
    _two_LineSolver__destroy(this.__ptr);
};
// GridSolver
function GridSolver() { throw "cannot construct a GridSolver, no constructor in IDL" }
GridSolver.prototype = Object.create(WrapperObject.prototype);
GridSolver.prototype.constructor = GridSolver;
GridSolver.prototype.__class = GridSolver;
GridSolver.__cache = {};
Module['GridSolver'] = GridSolver;
GridSolver.prototype["__destroy"] = GridSolver.prototype.__destroy = function() {
    _two_GridSolver__destroy(this.__ptr);
};
// ScrollSheet
function ScrollSheet() { throw "cannot construct a ScrollSheet, no constructor in IDL" }
ScrollSheet.prototype = Object.create(Widget.prototype);
ScrollSheet.prototype.constructor = ScrollSheet;
ScrollSheet.prototype.__class = ScrollSheet;
ScrollSheet.__base = Widget;
ScrollSheet.__cache = {};
Module['ScrollSheet'] = ScrollSheet;
ScrollSheet.prototype["__destroy"] = ScrollSheet.prototype.__destroy = function() {
    _two_ScrollSheet__destroy(this.__ptr);
};
// Sequence
function Sequence() { throw "cannot construct a Sequence, no constructor in IDL" }
Sequence.prototype = Object.create(Widget.prototype);
Sequence.prototype.constructor = Sequence;
Sequence.prototype.__class = Sequence;
Sequence.__base = Widget;
Sequence.__cache = {};
Module['ui']['Sequence'] = Sequence;
Sequence.prototype["__destroy"] = Sequence.prototype.__destroy = function() {
    _two_ui_Sequence__destroy(this.__ptr);
};
// Tabber
function Tabber() { throw "cannot construct a Tabber, no constructor in IDL" }
Tabber.prototype = Object.create(Widget.prototype);
Tabber.prototype.constructor = Tabber;
Tabber.prototype.__class = Tabber;
Tabber.__base = Widget;
Tabber.__cache = {};
Module['Tabber'] = Tabber;
Tabber.prototype["__destroy"] = Tabber.prototype.__destroy = function() {
    _two_Tabber__destroy(this.__ptr);
};
// Expandbox
function Expandbox() { throw "cannot construct a Expandbox, no constructor in IDL" }
Expandbox.prototype = Object.create(Widget.prototype);
Expandbox.prototype.constructor = Expandbox;
Expandbox.prototype.__class = Expandbox;
Expandbox.__base = Widget;
Expandbox.__cache = {};
Module['Expandbox'] = Expandbox;
Expandbox.prototype["__destroy"] = Expandbox.prototype.__destroy = function() {
    _two_Expandbox__destroy(this.__ptr);
};
// TreeNode
function TreeNode() { throw "cannot construct a TreeNode, no constructor in IDL" }
TreeNode.prototype = Object.create(Widget.prototype);
TreeNode.prototype.constructor = TreeNode;
TreeNode.prototype.__class = TreeNode;
TreeNode.__base = Widget;
TreeNode.__cache = {};
Module['TreeNode'] = TreeNode;
TreeNode.prototype["__destroy"] = TreeNode.prototype.__destroy = function() {
    _two_TreeNode__destroy(this.__ptr);
};
// Table
function Table() { throw "cannot construct a Table, no constructor in IDL" }
Table.prototype = Object.create(Widget.prototype);
Table.prototype.constructor = Table;
Table.prototype.__class = Table;
Table.__base = Widget;
Table.__cache = {};
Module['Table'] = Table;
Table.prototype["__destroy"] = Table.prototype.__destroy = function() {
    _two_Table__destroy(this.__ptr);
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
// Dockable
function Dockable() { throw "cannot construct a Dockable, no constructor in IDL" }
Dockable.prototype = Object.create(Widget.prototype);
Dockable.prototype.constructor = Dockable;
Dockable.prototype.__class = Dockable;
Dockable.__base = Widget;
Dockable.__cache = {};
Module['Dockable'] = Dockable;
Dockable.prototype["__destroy"] = Dockable.prototype.__destroy = function() {
    _two_Dockable__destroy(this.__ptr);
};
// Docker
function Docker() { throw "cannot construct a Docker, no constructor in IDL" }
Docker.prototype = Object.create(Widget.prototype);
Docker.prototype.constructor = Docker;
Docker.prototype.__class = Docker;
Docker.__base = Widget;
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
NodePlug.prototype = Object.create(Widget.prototype);
NodePlug.prototype.constructor = NodePlug;
NodePlug.prototype.__class = NodePlug;
NodePlug.__base = Widget;
NodePlug.__cache = {};
Module['NodePlug'] = NodePlug;
NodePlug.prototype["__destroy"] = NodePlug.prototype.__destroy = function() {
    _two_NodePlug__destroy(this.__ptr);
};
// Node
function Node() { throw "cannot construct a Node, no constructor in IDL" }
Node.prototype = Object.create(Widget.prototype);
Node.prototype.constructor = Node;
Node.prototype.__class = Node;
Node.__base = Widget;
Node.__cache = {};
Module['Node'] = Node;
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
Canvas.prototype = Object.create(Widget.prototype);
Canvas.prototype.constructor = Canvas;
Canvas.prototype.__class = Canvas;
Canvas.__base = Widget;
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
// Window
function Window() { throw "cannot construct a Window, no constructor in IDL" }
Window.prototype = Object.create(Dockable.prototype);
Window.prototype.constructor = Window;
Window.prototype.__class = Window;
Window.__base = Dockable;
Window.__cache = {};
Module['Window'] = Window;
Object.defineProperty(Window.prototype, "window_state", {
    get: function() {
        return _two_Window__get_window_state(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Window.window_state: expected integer');
        _two_Window__set_window_state(this.__ptr, value);
    }
});
Object.defineProperty(Window.prototype, "menu", {
    get: function() {
        return wrapPointer(_two_Window__get_menu(this.__ptr), Widget);
    },
    set: function(value) {
        if (!checkClass(value, Widget)) throw Error('Window.menu: expected Widget');
        _two_Window__set_menu(this.__ptr, value.__ptr);
    }
});
Window.prototype["__destroy"] = Window.prototype.__destroy = function() {
    _two_Window__destroy(this.__ptr);
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
Module['ui']['widget'] = function(a0, a1, a2, a3, a4) {
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('widget(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('widget(1:style): expected Style'); }
    else if (a3 === undefined) { if (!checkClass(a0, Widget)) throw Error('widget(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('widget(1:style): expected Style'); if (typeof a2 !== 'boolean') throw Error('widget(2:open): expected boolean'); }
    else if (a4 === undefined) { if (!checkClass(a0, Widget)) throw Error('widget(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('widget(1:style): expected Style'); if (typeof a2 !== 'boolean') throw Error('widget(2:open): expected boolean'); if (typeof a3 !== 'number') throw Error('widget(3:length): expected integer'); }
    else { if (!checkClass(a0, Widget)) throw Error('widget(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('widget(1:style): expected Style'); if (typeof a2 !== 'boolean') throw Error('widget(2:open): expected boolean'); if (typeof a3 !== 'number') throw Error('widget(3:length): expected integer'); if (!checkClass(a4, v2_uint)) throw Error('widget(4:index): expected v2<uint>'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_widget_2(/*parent*/a0.__ptr, /*style*/a1.__ptr), Widget); }
    else if (a3 === undefined) { return wrapPointer(_two_ui_widget_3(/*parent*/a0.__ptr, /*style*/a1.__ptr, /*open*/a2), Widget); }
    else if (a4 === undefined) { return wrapPointer(_two_ui_widget_4(/*parent*/a0.__ptr, /*style*/a1.__ptr, /*open*/a2, /*length*/a3), Widget); }
    else { return wrapPointer(_two_ui_widget_5(/*parent*/a0.__ptr, /*style*/a1.__ptr, /*open*/a2, /*length*/a3, /*index*/a4.__ptr), Widget); }
};
Module['ui']['item'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('item(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('item(1:style): expected Style'); }
    else { if (!checkClass(a0, Widget)) throw Error('item(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('item(1:style): expected Style'); if (typeof a2 !== 'string') throw Error('item(2:content): expected string'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_item_2(/*parent*/a0.__ptr, /*style*/a1.__ptr), Widget); }
    else { return wrapPointer(_two_ui_item_3(/*parent*/a0.__ptr, /*style*/a1.__ptr, ensureString(/*content*/a2)), Widget); }
};
Module['ui']['multi_item'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { if (!checkClass(a0, Widget)) throw Error('multi_item(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('multi_item(1:style): expected Style');  }
    else { if (!checkClass(a0, Widget)) throw Error('multi_item(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('multi_item(1:style): expected Style');  if (!checkClass(a3, Style)) throw Error('multi_item(3:element_style): expected Style'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_multi_item_3(/*parent*/a0.__ptr, /*style*/a1.__ptr, ensureInt8(/*elements*/a2), /*elements*/a2.length), Widget); }
    else { return wrapPointer(_two_ui_multi_item_4(/*parent*/a0.__ptr, /*style*/a1.__ptr, ensureInt8(/*elements*/a2), /*elements*/a2.length, /*element_style*/a3.__ptr), Widget); }
};
Module['ui']['spanner'] = function(a0, a1, a2, a3) {
    if (!checkClass(a0, Widget)) throw Error('spanner(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('spanner(1:style): expected Style'); if (typeof a2 !== 'number') throw Error('spanner(2:dim): expected integer'); if (typeof a3 !== 'number') throw Error('spanner(3:span): expected number');
    return wrapPointer(_two_ui_spanner_4(/*parent*/a0.__ptr, /*style*/a1.__ptr, /*dim*/a2, /*span*/a3), Widget);
};
Module['ui']['spacer'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('spacer(0:parent): expected Widget');
    return wrapPointer(_two_ui_spacer_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['separator'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('separator(0:parent): expected Widget');
    return wrapPointer(_two_ui_separator_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['icon'] = function(a0, a1) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('icon(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('icon(1:image): expected string');
    return wrapPointer(_two_ui_icon_2(/*parent*/a0.__ptr, ensureString(/*image*/a1)), Widget);
};
Module['ui']['label'] = function(a0, a1) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('label(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('label(1:label): expected string');
    return wrapPointer(_two_ui_label_2(/*parent*/a0.__ptr, ensureString(/*label*/a1)), Widget);
};
Module['ui']['title'] = function(a0, a1) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('title(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('title(1:label): expected string');
    return wrapPointer(_two_ui_title_2(/*parent*/a0.__ptr, ensureString(/*label*/a1)), Widget);
};
Module['ui']['message'] = function(a0, a1) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('message(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('message(1:label): expected string');
    return wrapPointer(_two_ui_message_2(/*parent*/a0.__ptr, ensureString(/*label*/a1)), Widget);
};
Module['ui']['text'] = function(a0, a1) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('text(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('text(1:label): expected string');
    return wrapPointer(_two_ui_text_2(/*parent*/a0.__ptr, ensureString(/*label*/a1)), Widget);
};
Module['ui']['bullet'] = function(a0, a1) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('bullet(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('bullet(1:label): expected string');
    return wrapPointer(_two_ui_bullet_2(/*parent*/a0.__ptr, ensureString(/*label*/a1)), Widget);
};
Module['ui']['selectable'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('selectable(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('selectable(1:label): expected string'); if (typeof a2 !== 'boolean') throw Error('selectable(2:selected): expected boolean');
    return wrapPointer(_two_ui_selectable_3(/*parent*/a0.__ptr, ensureString(/*label*/a1), /*selected*/a2), Widget);
};
Module['ui']['button'] = function(a0, a1) {
    ensureCache.prepare();
    if (a1 === undefined) { if (!checkClass(a0, Widget)) throw Error('button(0:parent): expected Widget'); }
    else { if (!checkClass(a0, Widget)) throw Error('button(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('button(1:content): expected string'); }
    if (a1 === undefined) { return wrapPointer(_two_ui_button_1(/*parent*/a0.__ptr), Widget); }
    else { return wrapPointer(_two_ui_button_2(/*parent*/a0.__ptr, ensureString(/*content*/a1)), Widget); }
};
Module['ui']['toggle'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('toggle(0:parent): expected Widget'); if (typeof a1 !== 'boolean') throw Error('toggle(1:on): expected boolean'); }
    else { if (!checkClass(a0, Widget)) throw Error('toggle(0:parent): expected Widget'); if (typeof a1 !== 'boolean') throw Error('toggle(1:on): expected boolean'); if (typeof a2 !== 'string') throw Error('toggle(2:content): expected string'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_toggle_2(/*parent*/a0.__ptr, /*on*/a1), Widget); }
    else { return wrapPointer(_two_ui_toggle_3(/*parent*/a0.__ptr, /*on*/a1, ensureString(/*content*/a2)), Widget); }
};
Module['ui']['multi_button'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('multi_button(0:parent): expected Widget');  }
    else { if (!checkClass(a0, Widget)) throw Error('multi_button(0:parent): expected Widget');  if (!checkClass(a2, Style)) throw Error('multi_button(2:element_style): expected Style'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_multi_button_2(/*parent*/a0.__ptr, ensureInt8(/*elements*/a1), /*elements*/a1.length), Widget); }
    else { return wrapPointer(_two_ui_multi_button_3(/*parent*/a0.__ptr, ensureInt8(/*elements*/a1), /*elements*/a1.length, /*element_style*/a2.__ptr), Widget); }
};
Module['ui']['multi_toggle'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { if (!checkClass(a0, Widget)) throw Error('multi_toggle(0:parent): expected Widget'); if (typeof a1 !== 'boolean') throw Error('multi_toggle(1:on): expected boolean');  }
    else { if (!checkClass(a0, Widget)) throw Error('multi_toggle(0:parent): expected Widget'); if (typeof a1 !== 'boolean') throw Error('multi_toggle(1:on): expected boolean');  if (!checkClass(a3, Style)) throw Error('multi_toggle(3:element_style): expected Style'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_multi_toggle_3(/*parent*/a0.__ptr, /*on*/a1, ensureInt8(/*elements*/a2), /*elements*/a2.length), Widget); }
    else { return wrapPointer(_two_ui_multi_toggle_4(/*parent*/a0.__ptr, /*on*/a1, ensureInt8(/*elements*/a2), /*elements*/a2.length, /*element_style*/a3.__ptr), Widget); }
};
Module['ui']['modal_button'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('modal_button(0:screen): expected Widget'); if (!checkClass(a1, Widget)) throw Error('modal_button(1:parent): expected Widget'); if (typeof a2 !== 'string') throw Error('modal_button(2:content): expected string'); if (typeof a3 !== 'number') throw Error('modal_button(3:mode): expected integer');
    return !!(_two_ui_modal_button_4(/*screen*/a0.__ptr, /*parent*/a1.__ptr, ensureString(/*content*/a2), /*mode*/a3));
};
Module['ui']['modal_multi_button'] = function(a0, a1, a2, a3) {
    if (!checkClass(a0, Widget)) throw Error('modal_multi_button(0:screen): expected Widget'); if (!checkClass(a1, Widget)) throw Error('modal_multi_button(1:parent): expected Widget');  if (typeof a3 !== 'number') throw Error('modal_multi_button(3:mode): expected integer');
    return !!(_two_ui_modal_multi_button_4(/*screen*/a0.__ptr, /*parent*/a1.__ptr, ensureInt8(/*elements*/a2), /*elements*/a2.length, /*mode*/a3));
};
Module['ui']['checkbox'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('checkbox(0:parent): expected Widget'); if (typeof a1 !== 'boolean') throw Error('checkbox(1:on): expected boolean');
    return wrapPointer(_two_ui_checkbox_2(/*parent*/a0.__ptr, /*on*/a1), Widget);
};
Module['ui']['fill_bar'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('fill_bar(0:parent): expected Widget'); if (typeof a1 !== 'number') throw Error('fill_bar(1:percentage): expected number'); }
    else { if (!checkClass(a0, Widget)) throw Error('fill_bar(0:parent): expected Widget'); if (typeof a1 !== 'number') throw Error('fill_bar(1:percentage): expected number'); if (typeof a2 !== 'number') throw Error('fill_bar(2:dim): expected integer'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_fill_bar_2(/*parent*/a0.__ptr, /*percentage*/a1), Widget); }
    else { return wrapPointer(_two_ui_fill_bar_3(/*parent*/a0.__ptr, /*percentage*/a1, /*dim*/a2), Widget); }
};
Module['ui']['image256'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a3 === undefined) { if (!checkClass(a0, Widget)) throw Error('image256(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('image256(1:name): expected string'); if (!checkClass(a2, Image256)) throw Error('image256(2:source): expected Image256'); }
    else { if (!checkClass(a0, Widget)) throw Error('image256(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('image256(1:name): expected string'); if (!checkClass(a2, Image256)) throw Error('image256(2:source): expected Image256'); if (!checkClass(a3, v2_float)) throw Error('image256(3:size): expected v2<float>'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_image256_3(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*source*/a2.__ptr), Widget); }
    else { return wrapPointer(_two_ui_image256_4(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*source*/a2.__ptr, /*size*/a3.__ptr), Widget); }
};
Module['ui']['radio_choice'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('radio_choice(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('radio_choice(1:label): expected string'); if (typeof a2 !== 'boolean') throw Error('radio_choice(2:active): expected boolean');
    return wrapPointer(_two_ui_radio_choice_3(/*parent*/a0.__ptr, ensureString(/*label*/a1), /*active*/a2), Widget);
};
Module['ui']['radio_button'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('radio_button(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('radio_button(1:label): expected string'); if (typeof a2 !== 'number') throw Error('radio_button(2:value): expected integer'); if (typeof a3 !== 'number') throw Error('radio_button(3:index): expected integer');
    return wrapPointer(_two_ui_radio_button_4(/*parent*/a0.__ptr, ensureString(/*label*/a1), /*value*/a2, /*index*/a3), Widget);
};
Module['ui']['radio_switch'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { if (!checkClass(a0, Widget)) throw Error('radio_switch(0:parent): expected Widget');  if (typeof a2 !== 'number') throw Error('radio_switch(2:value): expected integer'); }
    else { if (!checkClass(a0, Widget)) throw Error('radio_switch(0:parent): expected Widget');  if (typeof a2 !== 'number') throw Error('radio_switch(2:value): expected integer'); if (typeof a3 !== 'number') throw Error('radio_switch(3:dim): expected integer'); }
    if (a3 === undefined) { return !!(_two_ui_radio_switch_3(/*parent*/a0.__ptr, ensureInt8(/*labels*/a1), /*labels*/a1.length, /*value*/a2)); }
    else { return !!(_two_ui_radio_switch_4(/*parent*/a0.__ptr, ensureInt8(/*labels*/a1), /*labels*/a1.length, /*value*/a2, /*dim*/a3)); }
};
Module['ui']['popdown'] = function(a0, a1, a2, a3, a4) {
    if (!checkClass(a0, Widget)) throw Error('popdown(0:parent): expected Widget');  if (typeof a2 !== 'number') throw Error('popdown(2:value): expected integer'); if (!checkClass(a3, v2_float)) throw Error('popdown(3:position): expected v2<float>'); if (typeof a4 !== 'number') throw Error('popdown(4:flags): expected integer');
    return !!(_two_ui_popdown_5(/*parent*/a0.__ptr, ensureInt8(/*choices*/a1), /*choices*/a1.length, /*value*/a2, /*position*/a3.__ptr, /*flags*/a4));
};
Module['ui']['dropdown'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (a4 === undefined) { if (!checkClass(a0, Widget)) throw Error('dropdown(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('dropdown(1:style): expected Style'); if (typeof a2 !== 'string') throw Error('dropdown(2:value): expected string'); if (typeof a3 !== 'number') throw Error('dropdown(3:flags): expected integer'); }
    else if (a5 === undefined) { if (!checkClass(a0, Widget)) throw Error('dropdown(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('dropdown(1:style): expected Style'); if (typeof a2 !== 'string') throw Error('dropdown(2:value): expected string'); if (typeof a3 !== 'number') throw Error('dropdown(3:flags): expected integer'); if (typeof a4 !== 'boolean') throw Error('dropdown(4:no_toggle): expected boolean'); }
    else { if (!checkClass(a0, Widget)) throw Error('dropdown(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('dropdown(1:style): expected Style'); if (typeof a2 !== 'string') throw Error('dropdown(2:value): expected string'); if (typeof a3 !== 'number') throw Error('dropdown(3:flags): expected integer'); if (typeof a4 !== 'boolean') throw Error('dropdown(4:no_toggle): expected boolean'); if (!checkClass(a5, Style)) throw Error('dropdown(5:list_style): expected Style'); }
    if (a4 === undefined) { return wrapPointer(_two_ui_dropdown_4(/*parent*/a0.__ptr, /*style*/a1.__ptr, ensureString(/*value*/a2), /*flags*/a3), Widget); }
    else if (a5 === undefined) { return wrapPointer(_two_ui_dropdown_5(/*parent*/a0.__ptr, /*style*/a1.__ptr, ensureString(/*value*/a2), /*flags*/a3, /*no_toggle*/a4), Widget); }
    else { return wrapPointer(_two_ui_dropdown_6(/*parent*/a0.__ptr, /*style*/a1.__ptr, ensureString(/*value*/a2), /*flags*/a3, /*no_toggle*/a4, /*list_style*/a5.__ptr), Widget); }
};
Module['ui']['dropdown_input'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { if (!checkClass(a0, Widget)) throw Error('dropdown_input(0:parent): expected Widget');  if (typeof a2 !== 'number') throw Error('dropdown_input(2:value): expected integer'); }
    else { if (!checkClass(a0, Widget)) throw Error('dropdown_input(0:parent): expected Widget');  if (typeof a2 !== 'number') throw Error('dropdown_input(2:value): expected integer'); if (typeof a3 !== 'boolean') throw Error('dropdown_input(3:compact): expected boolean'); }
    if (a3 === undefined) { return !!(_two_ui_dropdown_input_3(/*parent*/a0.__ptr, ensureInt8(/*choices*/a1), /*choices*/a1.length, /*value*/a2)); }
    else { return !!(_two_ui_dropdown_input_4(/*parent*/a0.__ptr, ensureInt8(/*choices*/a1), /*choices*/a1.length, /*value*/a2, /*compact*/a3)); }
};
Module['ui']['typedown_input'] = function(a0, a1, a2) {
    if (!checkClass(a0, Widget)) throw Error('typedown_input(0:parent): expected Widget');  if (typeof a2 !== 'number') throw Error('typedown_input(2:value): expected integer');
    return !!(_two_ui_typedown_input_3(/*parent*/a0.__ptr, ensureInt8(/*choices*/a1), /*choices*/a1.length, /*value*/a2));
};
Module['ui']['menu_choice'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('menu_choice(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('menu_choice(1:content): expected string'); }
    else { if (!checkClass(a0, Widget)) throw Error('menu_choice(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('menu_choice(1:content): expected string'); if (typeof a2 !== 'string') throw Error('menu_choice(2:shortcut): expected string'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_menu_choice_2(/*parent*/a0.__ptr, ensureString(/*content*/a1)), Widget); }
    else { return wrapPointer(_two_ui_menu_choice_3(/*parent*/a0.__ptr, ensureString(/*content*/a1), ensureString(/*shortcut*/a2)), Widget); }
};
Module['ui']['menu_option'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('menu_option(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('menu_option(1:content): expected string'); if (typeof a2 !== 'string') throw Error('menu_option(2:shortcut): expected string'); if (typeof a3 !== 'boolean') throw Error('menu_option(3:enabled): expected boolean');
    return wrapPointer(_two_ui_menu_option_4(/*parent*/a0.__ptr, ensureString(/*content*/a1), ensureString(/*shortcut*/a2), /*enabled*/a3), Widget);
};
Module['ui']['menu'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('menu(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('menu(1:label): expected string'); }
    else { if (!checkClass(a0, Widget)) throw Error('menu(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('menu(1:label): expected string'); if (typeof a2 !== 'boolean') throw Error('menu(2:submenu): expected boolean'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_menu_2(/*parent*/a0.__ptr, ensureString(/*label*/a1)), Widget); }
    else { return wrapPointer(_two_ui_menu_3(/*parent*/a0.__ptr, ensureString(/*label*/a1), /*submenu*/a2), Widget); }
};
Module['ui']['menubar'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('menubar(0:parent): expected Widget');
    return wrapPointer(_two_ui_menubar_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['toolbutton'] = function(a0, a1) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('toolbutton(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('toolbutton(1:icon): expected string');
    return wrapPointer(_two_ui_toolbutton_2(/*parent*/a0.__ptr, ensureString(/*icon*/a1)), Widget);
};
Module['ui']['tooldock'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('tooldock(0:parent): expected Widget');
    return wrapPointer(_two_ui_tooldock_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['toolbar'] = function(a0, a1) {
    if (a1 === undefined) { if (!checkClass(a0, Widget)) throw Error('toolbar(0:parent): expected Widget'); }
    else { if (!checkClass(a0, Widget)) throw Error('toolbar(0:parent): expected Widget'); if (typeof a1 !== 'boolean') throw Error('toolbar(1:wrap): expected boolean'); }
    if (a1 === undefined) { return wrapPointer(_two_ui_toolbar_1(/*parent*/a0.__ptr), Widget); }
    else { return wrapPointer(_two_ui_toolbar_2(/*parent*/a0.__ptr, /*wrap*/a1), Widget); }
};
Module['ui']['select_list'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('select_list(0:parent): expected Widget');
    return wrapPointer(_two_ui_select_list_1(/*parent*/a0.__ptr), ScrollSheet);
};
Module['ui']['columns'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('columns(0:parent): expected Widget'); 
    return wrapPointer(_two_ui_columns_2(/*parent*/a0.__ptr, ensureFloat32(/*weights*/a1), /*weights*/a1.length), Table);
};
Module['ui']['table'] = function(a0, a1, a2) {
    if (!checkClass(a0, Widget)) throw Error('table(0:parent): expected Widget');  
    return wrapPointer(_two_ui_table_3(/*parent*/a0.__ptr, ensureInt8(/*columns*/a1), /*columns*/a1.length, ensureFloat32(/*weights*/a2), /*weights*/a2.length), Table);
};
Module['ui']['table_row'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('table_row(0:parent): expected Widget');
    return wrapPointer(_two_ui_table_row_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['table_separator'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('table_separator(0:parent): expected Widget');
    return wrapPointer(_two_ui_table_separator_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['expandbox'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('expandbox(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('expandbox(1:name): expected string'); }
    else { if (!checkClass(a0, Widget)) throw Error('expandbox(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('expandbox(1:name): expected string'); if (typeof a2 !== 'boolean') throw Error('expandbox(2:open): expected boolean'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_expandbox_2(/*parent*/a0.__ptr, ensureString(/*name*/a1)), Expandbox); }
    else { return wrapPointer(_two_ui_expandbox_3(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*open*/a2), Expandbox); }
};
Module['ui']['tree_node'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('tree_node(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('tree_node(1:name): expected string'); }
    else if (a3 === undefined) { if (!checkClass(a0, Widget)) throw Error('tree_node(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('tree_node(1:name): expected string'); if (typeof a2 !== 'boolean') throw Error('tree_node(2:leaf): expected boolean'); }
    else { if (!checkClass(a0, Widget)) throw Error('tree_node(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('tree_node(1:name): expected string'); if (typeof a2 !== 'boolean') throw Error('tree_node(2:leaf): expected boolean'); if (typeof a3 !== 'boolean') throw Error('tree_node(3:open): expected boolean'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_tree_node_2(/*parent*/a0.__ptr, ensureString(/*name*/a1)), TreeNode); }
    else if (a3 === undefined) { return wrapPointer(_two_ui_tree_node_3(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*leaf*/a2), TreeNode); }
    else { return wrapPointer(_two_ui_tree_node_4(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*leaf*/a2, /*open*/a3), TreeNode); }
};
Module['ui']['tree'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('tree(0:parent): expected Widget');
    return wrapPointer(_two_ui_tree_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['tab'] = function(a0, a1) {
    ensureCache.prepare();
    if (!checkClass(a0, Tabber)) throw Error('tab(0:tabber): expected Tabber'); if (typeof a1 !== 'string') throw Error('tab(1:name): expected string');
    return wrapPointer(_two_ui_tab_2(/*tabber*/a0.__ptr, ensureString(/*name*/a1)), Widget);
};
Module['ui']['tabber'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('tabber(0:parent): expected Widget');
    return wrapPointer(_two_ui_tabber_1(/*parent*/a0.__ptr), Tabber);
};
Module['ui']['row'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('row(0:parent): expected Widget');
    return wrapPointer(_two_ui_row_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['header'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('header(0:parent): expected Widget');
    return wrapPointer(_two_ui_header_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['div'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('div(0:parent): expected Widget');
    return wrapPointer(_two_ui_div_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['stack'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('stack(0:parent): expected Widget');
    return wrapPointer(_two_ui_stack_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['sheet'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('sheet(0:parent): expected Widget');
    return wrapPointer(_two_ui_sheet_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['board'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('board(0:parent): expected Widget');
    return wrapPointer(_two_ui_board_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['layout'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('layout(0:parent): expected Widget');
    return wrapPointer(_two_ui_layout_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['indent'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('indent(0:parent): expected Widget');
    return wrapPointer(_two_ui_indent_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['screen'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('screen(0:parent): expected Widget');
    return wrapPointer(_two_ui_screen_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['decal'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('decal(0:parent): expected Widget');
    return wrapPointer(_two_ui_decal_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['overlay'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('overlay(0:parent): expected Widget');
    return wrapPointer(_two_ui_overlay_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['title_header'] = function(a0, a1) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('title_header(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('title_header(1:title): expected string');
    return wrapPointer(_two_ui_title_header_2(/*parent*/a0.__ptr, ensureString(/*title*/a1)), Widget);
};
Module['ui']['dummy'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('dummy(0:parent): expected Widget'); if (!checkClass(a1, v2_float)) throw Error('dummy(1:size): expected v2<float>');
    return wrapPointer(_two_ui_dummy_2(/*parent*/a0.__ptr, /*size*/a1.__ptr), Widget);
};
Module['ui']['popup'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('popup(0:parent): expected Widget'); if (typeof a1 !== 'number') throw Error('popup(1:flags): expected integer'); }
    else { if (!checkClass(a0, Widget)) throw Error('popup(0:parent): expected Widget'); if (!checkClass(a1, v2_float)) throw Error('popup(1:size): expected v2<float>'); if (typeof a2 !== 'number') throw Error('popup(2:flags): expected integer'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_popup_2(/*parent*/a0.__ptr, /*flags*/a1), Widget); }
    else { return wrapPointer(_two_ui_popup_3(/*parent*/a0.__ptr, /*size*/a1.__ptr, /*flags*/a2), Widget); }
};
Module['ui']['popup_at'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('popup_at(0:parent): expected Widget'); if (!checkClass(a1, v2_float)) throw Error('popup_at(1:position): expected v2<float>'); }
    else { if (!checkClass(a0, Widget)) throw Error('popup_at(0:parent): expected Widget'); if (!checkClass(a1, v2_float)) throw Error('popup_at(1:position): expected v2<float>'); if (typeof a2 !== 'number') throw Error('popup_at(2:flags): expected integer'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_popup_at_2(/*parent*/a0.__ptr, /*position*/a1.__ptr), Widget); }
    else { return wrapPointer(_two_ui_popup_at_3(/*parent*/a0.__ptr, /*position*/a1.__ptr, /*flags*/a2), Widget); }
};
Module['ui']['modal'] = function(a0, a1) {
    if (a1 === undefined) { if (!checkClass(a0, Widget)) throw Error('modal(0:parent): expected Widget'); }
    else { if (!checkClass(a0, Widget)) throw Error('modal(0:parent): expected Widget'); if (!checkClass(a1, v2_float)) throw Error('modal(1:size): expected v2<float>'); }
    if (a1 === undefined) { return wrapPointer(_two_ui_modal_1(/*parent*/a0.__ptr), Widget); }
    else { return wrapPointer(_two_ui_modal_2(/*parent*/a0.__ptr, /*size*/a1.__ptr), Widget); }
};
Module['ui']['auto_modal'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('auto_modal(0:parent): expected Widget'); if (typeof a1 !== 'number') throw Error('auto_modal(1:mode): expected integer'); }
    else { if (!checkClass(a0, Widget)) throw Error('auto_modal(0:parent): expected Widget'); if (typeof a1 !== 'number') throw Error('auto_modal(1:mode): expected integer'); if (!checkClass(a2, v2_float)) throw Error('auto_modal(2:size): expected v2<float>'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_auto_modal_2(/*parent*/a0.__ptr, /*mode*/a1), Widget); }
    else { return wrapPointer(_two_ui_auto_modal_3(/*parent*/a0.__ptr, /*mode*/a1, /*size*/a2.__ptr), Widget); }
};
Module['ui']['context'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('context(0:parent): expected Widget'); if (typeof a1 !== 'number') throw Error('context(1:mode): expected integer'); }
    else { if (!checkClass(a0, Widget)) throw Error('context(0:parent): expected Widget'); if (typeof a1 !== 'number') throw Error('context(1:mode): expected integer'); if (typeof a2 !== 'number') throw Error('context(2:flags): expected integer'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_context_2(/*parent*/a0.__ptr, /*mode*/a1), Widget); }
    else { return wrapPointer(_two_ui_context_3(/*parent*/a0.__ptr, /*mode*/a1, /*flags*/a2), Widget); }
};
Module['ui']['hoverbox'] = function(a0, a1) {
    if (a1 === undefined) { if (!checkClass(a0, Widget)) throw Error('hoverbox(0:parent): expected Widget'); }
    else { if (!checkClass(a0, Widget)) throw Error('hoverbox(0:parent): expected Widget'); if (typeof a1 !== 'number') throw Error('hoverbox(1:delay): expected number'); }
    if (a1 === undefined) { return wrapPointer(_two_ui_hoverbox_1(/*parent*/a0.__ptr), Widget); }
    else { return wrapPointer(_two_ui_hoverbox_2(/*parent*/a0.__ptr, /*delay*/a1), Widget); }
};
Module['ui']['cursor'] = function(a0, a1, a2, a3) {
    if (a3 === undefined) { if (!checkClass(a0, Widget)) throw Error('cursor(0:parent): expected Widget'); if (!checkClass(a1, v2_float)) throw Error('cursor(1:position): expected v2<float>'); if (!checkClass(a2, Widget)) throw Error('cursor(2:hovered): expected Widget'); }
    else { if (!checkClass(a0, Widget)) throw Error('cursor(0:parent): expected Widget'); if (!checkClass(a1, v2_float)) throw Error('cursor(1:position): expected v2<float>'); if (!checkClass(a2, Widget)) throw Error('cursor(2:hovered): expected Widget'); if (typeof a3 !== 'boolean') throw Error('cursor(3:locked): expected boolean'); }
    if (a3 === undefined) { return wrapPointer(_two_ui_cursor_3(/*parent*/a0.__ptr, /*position*/a1.__ptr, /*hovered*/a2.__ptr), Widget); }
    else { return wrapPointer(_two_ui_cursor_4(/*parent*/a0.__ptr, /*position*/a1.__ptr, /*hovered*/a2.__ptr, /*locked*/a3), Widget); }
};
Module['ui']['rectangle'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('rectangle(0:parent): expected Widget'); if (!checkClass(a1, v4_float)) throw Error('rectangle(1:rect): expected v4<float>');
    return wrapPointer(_two_ui_rectangle_2(/*parent*/a0.__ptr, /*rect*/a1.__ptr), Widget);
};
Module['ui']['viewport'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('viewport(0:parent): expected Widget'); if (!checkClass(a1, v4_float)) throw Error('viewport(1:rect): expected v4<float>');
    return wrapPointer(_two_ui_viewport_2(/*parent*/a0.__ptr, /*rect*/a1.__ptr), Widget);
};
Module['ui']['dockspace'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('dockspace(0:parent): expected Widget'); if (!checkClass(a1, Docksystem)) throw Error('dockspace(1:docksystem): expected Docksystem');
    return wrapPointer(_two_ui_dockspace_2(/*parent*/a0.__ptr, /*docksystem*/a1.__ptr), Dockspace);
};
Module['ui']['dockbar'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('dockbar(0:parent): expected Widget'); if (!checkClass(a1, Docksystem)) throw Error('dockbar(1:docksystem): expected Docksystem');
    return wrapPointer(_two_ui_dockbar_2(/*parent*/a0.__ptr, /*docksystem*/a1.__ptr), Dockbar);
};
Module['ui']['dockitem'] = function(a0, a1, a2) {
    if (!checkClass(a0, Widget)) throw Error('dockitem(0:parent): expected Widget'); if (!checkClass(a1, Docksystem)) throw Error('dockitem(1:docksystem): expected Docksystem'); if (!checkClass(a2, Dock)) throw Error('dockitem(2:dock): expected Dock');
    return wrapPointer(_two_ui_dockitem_3(/*parent*/a0.__ptr, /*docksystem*/a1.__ptr, /*dock*/a2.__ptr), Widget);
};
Module['ui']['drag_float'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('drag_float(0:parent): expected Widget'); if (typeof a1 !== 'number') throw Error('drag_float(1:value): expected number'); }
    else { if (!checkClass(a0, Widget)) throw Error('drag_float(0:parent): expected Widget'); if (typeof a1 !== 'number') throw Error('drag_float(1:value): expected number'); if (typeof a2 !== 'number') throw Error('drag_float(2:step): expected number'); }
    if (a2 === undefined) { return !!(_two_ui_drag_float_2(/*parent*/a0.__ptr, /*value*/a1)); }
    else { return !!(_two_ui_drag_float_3(/*parent*/a0.__ptr, /*value*/a1, /*step*/a2)); }
};
Module['ui']['float2_input'] = function(a0, a1, a2, a3) {
    if (!checkClass(a0, Widget)) throw Error('float2_input(0:parent): expected Widget');   if (!checkClass(a3, StatDef_float)) throw Error('float2_input(3:def): expected StatDef<float>');
    return !!(_two_ui_float2_input_4(/*parent*/a0.__ptr, ensureInt8(/*labels*/a1), /*labels*/a1.length, ensureFloat32(/*vals*/a2), /*vals*/a2.length, /*def*/a3.__ptr));
};
Module['ui']['float3_input'] = function(a0, a1, a2, a3) {
    if (!checkClass(a0, Widget)) throw Error('float3_input(0:parent): expected Widget');   if (!checkClass(a3, StatDef_float)) throw Error('float3_input(3:def): expected StatDef<float>');
    return !!(_two_ui_float3_input_4(/*parent*/a0.__ptr, ensureInt8(/*labels*/a1), /*labels*/a1.length, ensureFloat32(/*vals*/a2), /*vals*/a2.length, /*def*/a3.__ptr));
};
Module['ui']['float4_input'] = function(a0, a1, a2, a3) {
    if (!checkClass(a0, Widget)) throw Error('float4_input(0:parent): expected Widget');   if (!checkClass(a3, StatDef_float)) throw Error('float4_input(3:def): expected StatDef<float>');
    return !!(_two_ui_float4_input_4(/*parent*/a0.__ptr, ensureInt8(/*labels*/a1), /*labels*/a1.length, ensureFloat32(/*vals*/a2), /*vals*/a2.length, /*def*/a3.__ptr));
};
Module['ui']['float2_slider'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('float2_slider(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('float2_slider(1:label): expected string');   if (!checkClass(a4, StatDef_float)) throw Error('float2_slider(4:def): expected StatDef<float>');
    return !!(_two_ui_float2_slider_5(/*parent*/a0.__ptr, ensureString(/*label*/a1), ensureInt8(/*labels*/a2), /*labels*/a2.length, ensureFloat32(/*vals*/a3), /*vals*/a3.length, /*def*/a4.__ptr));
};
Module['ui']['float3_slider'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('float3_slider(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('float3_slider(1:label): expected string');   if (!checkClass(a4, StatDef_float)) throw Error('float3_slider(4:def): expected StatDef<float>');
    return !!(_two_ui_float3_slider_5(/*parent*/a0.__ptr, ensureString(/*label*/a1), ensureInt8(/*labels*/a2), /*labels*/a2.length, ensureFloat32(/*vals*/a3), /*vals*/a3.length, /*def*/a4.__ptr));
};
Module['ui']['float4_slider'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('float4_slider(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('float4_slider(1:label): expected string');   if (!checkClass(a4, StatDef_float)) throw Error('float4_slider(4:def): expected StatDef<float>');
    return !!(_two_ui_float4_slider_5(/*parent*/a0.__ptr, ensureString(/*label*/a1), ensureInt8(/*labels*/a2), /*labels*/a2.length, ensureFloat32(/*vals*/a3), /*vals*/a3.length, /*def*/a4.__ptr));
};
Module['ui']['vec2_edit'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('vec2_edit(0:parent): expected Widget'); if (!checkClass(a1, v2_float)) throw Error('vec2_edit(1:vec): expected v2<float>');
    return !!(_two_ui_vec2_edit_2(/*parent*/a0.__ptr, /*vec*/a1.__ptr));
};
Module['ui']['vec3_edit'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('vec3_edit(0:parent): expected Widget'); if (!checkClass(a1, v3_float)) throw Error('vec3_edit(1:vec): expected v3<float>');
    return !!(_two_ui_vec3_edit_2(/*parent*/a0.__ptr, /*vec*/a1.__ptr));
};
Module['ui']['quat_edit'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('quat_edit(0:parent): expected Widget'); if (!checkClass(a1, quat)) throw Error('quat_edit(1:quat): expected quat');
    return !!(_two_ui_quat_edit_2(/*parent*/a0.__ptr, /*quat*/a1.__ptr));
};
Module['ui']['color_display'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('color_display(0:parent): expected Widget'); if (!checkClass(a1, Colour)) throw Error('color_display(1:value): expected Colour');
    return wrapPointer(_two_ui_color_display_2(/*parent*/a0.__ptr, /*value*/a1.__ptr), Widget);
};
Module['ui']['color_edit'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('color_edit(0:parent): expected Widget'); if (!checkClass(a1, Colour)) throw Error('color_edit(1:value): expected Colour');
    return !!(_two_ui_color_edit_2(/*parent*/a0.__ptr, /*value*/a1.__ptr));
};
Module['ui']['color_edit_simple'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('color_edit_simple(0:parent): expected Widget'); if (!checkClass(a1, Colour)) throw Error('color_edit_simple(1:value): expected Colour');
    return !!(_two_ui_color_edit_simple_2(/*parent*/a0.__ptr, /*value*/a1.__ptr));
};
Module['ui']['color_toggle_edit'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('color_toggle_edit(0:parent): expected Widget'); if (!checkClass(a1, Colour)) throw Error('color_toggle_edit(1:value): expected Colour');
    return !!(_two_ui_color_toggle_edit_2(/*parent*/a0.__ptr, /*value*/a1.__ptr));
};
Module['ui']['curve_graph'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('curve_graph(0:parent): expected Widget');  }
    else { if (!checkClass(a0, Widget)) throw Error('curve_graph(0:parent): expected Widget');   }
    if (a2 === undefined) { return !!(_two_ui_curve_graph_2(/*parent*/a0.__ptr, ensureFloat32(/*values*/a1), /*values*/a1.length)); }
    else { return !!(_two_ui_curve_graph_3(/*parent*/a0.__ptr, ensureFloat32(/*values*/a1), /*values*/a1.length, ensureFloat32(/*points*/a2), /*points*/a2.length)); }
};
Module['ui']['curve_edit'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('curve_edit(0:parent): expected Widget');  }
    else { if (!checkClass(a0, Widget)) throw Error('curve_edit(0:parent): expected Widget');   }
    if (a2 === undefined) { return !!(_two_ui_curve_edit_2(/*parent*/a0.__ptr, ensureFloat32(/*values*/a1), /*values*/a1.length)); }
    else { return !!(_two_ui_curve_edit_3(/*parent*/a0.__ptr, ensureFloat32(/*values*/a1), /*values*/a1.length, ensureFloat32(/*points*/a2), /*points*/a2.length)); }
};
Module['ui']['flag_field'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a4 === undefined) { if (!checkClass(a0, Widget)) throw Error('flag_field(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('flag_field(1:name): expected string'); if (typeof a2 !== 'number') throw Error('flag_field(2:value): expected integer'); if (typeof a3 !== 'number') throw Error('flag_field(3:shift): expected integer'); }
    else { if (!checkClass(a0, Widget)) throw Error('flag_field(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('flag_field(1:name): expected string'); if (typeof a2 !== 'number') throw Error('flag_field(2:value): expected integer'); if (typeof a3 !== 'number') throw Error('flag_field(3:shift): expected integer'); if (typeof a4 !== 'boolean') throw Error('flag_field(4:reverse): expected boolean'); }
    if (a4 === undefined) { return !!(_two_ui_flag_field_4(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*value*/a2, /*shift*/a3)); }
    else { return !!(_two_ui_flag_field_5(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*value*/a2, /*shift*/a3, /*reverse*/a4)); }
};
Module['ui']['radio_field'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (a4 === undefined) { if (!checkClass(a0, Widget)) throw Error('radio_field(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('radio_field(1:name): expected string');  if (typeof a3 !== 'number') throw Error('radio_field(3:value): expected integer'); }
    else if (a5 === undefined) { if (!checkClass(a0, Widget)) throw Error('radio_field(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('radio_field(1:name): expected string');  if (typeof a3 !== 'number') throw Error('radio_field(3:value): expected integer'); if (typeof a4 !== 'number') throw Error('radio_field(4:dim): expected integer'); }
    else { if (!checkClass(a0, Widget)) throw Error('radio_field(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('radio_field(1:name): expected string');  if (typeof a3 !== 'number') throw Error('radio_field(3:value): expected integer'); if (typeof a4 !== 'number') throw Error('radio_field(4:dim): expected integer'); if (typeof a5 !== 'boolean') throw Error('radio_field(5:reverse): expected boolean'); }
    if (a4 === undefined) { return !!(_two_ui_radio_field_4(/*parent*/a0.__ptr, ensureString(/*name*/a1), ensureInt8(/*choices*/a2), /*choices*/a2.length, /*value*/a3)); }
    else if (a5 === undefined) { return !!(_two_ui_radio_field_5(/*parent*/a0.__ptr, ensureString(/*name*/a1), ensureInt8(/*choices*/a2), /*choices*/a2.length, /*value*/a3, /*dim*/a4)); }
    else { return !!(_two_ui_radio_field_6(/*parent*/a0.__ptr, ensureString(/*name*/a1), ensureInt8(/*choices*/a2), /*choices*/a2.length, /*value*/a3, /*dim*/a4, /*reverse*/a5)); }
};
Module['ui']['dropdown_field'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a4 === undefined) { if (!checkClass(a0, Widget)) throw Error('dropdown_field(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('dropdown_field(1:name): expected string');  if (typeof a3 !== 'number') throw Error('dropdown_field(3:value): expected integer'); }
    else { if (!checkClass(a0, Widget)) throw Error('dropdown_field(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('dropdown_field(1:name): expected string');  if (typeof a3 !== 'number') throw Error('dropdown_field(3:value): expected integer'); if (typeof a4 !== 'boolean') throw Error('dropdown_field(4:reverse): expected boolean'); }
    if (a4 === undefined) { return !!(_two_ui_dropdown_field_4(/*parent*/a0.__ptr, ensureString(/*name*/a1), ensureInt8(/*choices*/a2), /*choices*/a2.length, /*value*/a3)); }
    else { return !!(_two_ui_dropdown_field_5(/*parent*/a0.__ptr, ensureString(/*name*/a1), ensureInt8(/*choices*/a2), /*choices*/a2.length, /*value*/a3, /*reverse*/a4)); }
};
Module['ui']['typedown_field'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a4 === undefined) { if (!checkClass(a0, Widget)) throw Error('typedown_field(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('typedown_field(1:name): expected string');  if (typeof a3 !== 'number') throw Error('typedown_field(3:value): expected integer'); }
    else { if (!checkClass(a0, Widget)) throw Error('typedown_field(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('typedown_field(1:name): expected string');  if (typeof a3 !== 'number') throw Error('typedown_field(3:value): expected integer'); if (typeof a4 !== 'boolean') throw Error('typedown_field(4:reverse): expected boolean'); }
    if (a4 === undefined) { return !!(_two_ui_typedown_field_4(/*parent*/a0.__ptr, ensureString(/*name*/a1), ensureInt8(/*choices*/a2), /*choices*/a2.length, /*value*/a3)); }
    else { return !!(_two_ui_typedown_field_5(/*parent*/a0.__ptr, ensureString(/*name*/a1), ensureInt8(/*choices*/a2), /*choices*/a2.length, /*value*/a3, /*reverse*/a4)); }
};
Module['ui']['color_field'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a3 === undefined) { if (!checkClass(a0, Widget)) throw Error('color_field(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('color_field(1:name): expected string'); if (!checkClass(a2, Colour)) throw Error('color_field(2:value): expected Colour'); }
    else { if (!checkClass(a0, Widget)) throw Error('color_field(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('color_field(1:name): expected string'); if (!checkClass(a2, Colour)) throw Error('color_field(2:value): expected Colour'); if (typeof a3 !== 'boolean') throw Error('color_field(3:reverse): expected boolean'); }
    if (a3 === undefined) { return !!(_two_ui_color_field_3(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*value*/a2.__ptr)); }
    else { return !!(_two_ui_color_field_4(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*value*/a2.__ptr, /*reverse*/a3)); }
};
Module['ui']['color_display_field'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a3 === undefined) { if (!checkClass(a0, Widget)) throw Error('color_display_field(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('color_display_field(1:name): expected string'); if (!checkClass(a2, Colour)) throw Error('color_display_field(2:value): expected Colour'); }
    else { if (!checkClass(a0, Widget)) throw Error('color_display_field(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('color_display_field(1:name): expected string'); if (!checkClass(a2, Colour)) throw Error('color_display_field(2:value): expected Colour'); if (typeof a3 !== 'boolean') throw Error('color_display_field(3:reverse): expected boolean'); }
    if (a3 === undefined) { _two_ui_color_display_field_3(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*value*/a2.__ptr); }
    else { _two_ui_color_display_field_4(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*value*/a2.__ptr, /*reverse*/a3); }
};
Module['ui']['input_bool'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('input<bool>(0:parent): expected Widget'); if (typeof a1 !== 'boolean') throw Error('input<bool>(1:value): expected boolean');
    return !!(_two_ui_input_bool_2(/*parent*/a0.__ptr, /*value*/a1));
};
Module['ui']['input_int'] = function(a0, a1, a2) {
    if (!checkClass(a0, Widget)) throw Error('input<int>(0:parent): expected Widget'); if (typeof a1 !== 'number') throw Error('input<int>(1:value): expected integer'); if (!checkClass(a2, StatDef_int)) throw Error('input<int>(2:def): expected StatDef<int>');
    return !!(_two_ui_input_int_3(/*parent*/a0.__ptr, /*value*/a1, /*def*/a2.__ptr));
};
Module['ui']['input_float'] = function(a0, a1, a2) {
    if (!checkClass(a0, Widget)) throw Error('input<float>(0:parent): expected Widget'); if (typeof a1 !== 'number') throw Error('input<float>(1:value): expected number'); if (!checkClass(a2, StatDef_float)) throw Error('input<float>(2:def): expected StatDef<float>');
    return !!(_two_ui_input_float_3(/*parent*/a0.__ptr, /*value*/a1, /*def*/a2.__ptr));
};
Module['ui']['field_bool'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (a3 === undefined) { if (!checkClass(a0, Widget)) throw Error('field<bool>(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('field<bool>(1:name): expected string'); if (typeof a2 !== 'boolean') throw Error('field<bool>(2:value): expected boolean'); }
    else { if (!checkClass(a0, Widget)) throw Error('field<bool>(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('field<bool>(1:name): expected string'); if (typeof a2 !== 'boolean') throw Error('field<bool>(2:value): expected boolean'); if (typeof a3 !== 'boolean') throw Error('field<bool>(3:reverse): expected boolean'); }
    if (a3 === undefined) { return !!(_two_ui_field_bool_3(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*value*/a2)); }
    else { return !!(_two_ui_field_bool_4(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*value*/a2, /*reverse*/a3)); }
};
Module['ui']['field_int'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a4 === undefined) { if (!checkClass(a0, Widget)) throw Error('field<int>(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('field<int>(1:name): expected string'); if (typeof a2 !== 'number') throw Error('field<int>(2:value): expected integer'); if (!checkClass(a3, StatDef_int)) throw Error('field<int>(3:def): expected StatDef<int>'); }
    else { if (!checkClass(a0, Widget)) throw Error('field<int>(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('field<int>(1:name): expected string'); if (typeof a2 !== 'number') throw Error('field<int>(2:value): expected integer'); if (!checkClass(a3, StatDef_int)) throw Error('field<int>(3:def): expected StatDef<int>'); if (typeof a4 !== 'boolean') throw Error('field<int>(4:reverse): expected boolean'); }
    if (a4 === undefined) { return !!(_two_ui_field_int_4(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*value*/a2, /*def*/a3.__ptr)); }
    else { return !!(_two_ui_field_int_5(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*value*/a2, /*def*/a3.__ptr, /*reverse*/a4)); }
};
Module['ui']['field_float'] = function(a0, a1, a2, a3, a4) {
    ensureCache.prepare();
    if (a4 === undefined) { if (!checkClass(a0, Widget)) throw Error('field<float>(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('field<float>(1:name): expected string'); if (typeof a2 !== 'number') throw Error('field<float>(2:value): expected number'); if (!checkClass(a3, StatDef_float)) throw Error('field<float>(3:def): expected StatDef<float>'); }
    else { if (!checkClass(a0, Widget)) throw Error('field<float>(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('field<float>(1:name): expected string'); if (typeof a2 !== 'number') throw Error('field<float>(2:value): expected number'); if (!checkClass(a3, StatDef_float)) throw Error('field<float>(3:def): expected StatDef<float>'); if (typeof a4 !== 'boolean') throw Error('field<float>(4:reverse): expected boolean'); }
    if (a4 === undefined) { return !!(_two_ui_field_float_4(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*value*/a2, /*def*/a3.__ptr)); }
    else { return !!(_two_ui_field_float_5(/*parent*/a0.__ptr, ensureString(/*name*/a1), /*value*/a2, /*def*/a3.__ptr, /*reverse*/a4)); }
};
Module['ui']['node_input'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (a2 === undefined) { if (!checkClass(a0, Node)) throw Error('node_input(0:node): expected Node'); if (typeof a1 !== 'string') throw Error('node_input(1:name): expected string'); }
    else if (a3 === undefined) { if (!checkClass(a0, Node)) throw Error('node_input(0:node): expected Node'); if (typeof a1 !== 'string') throw Error('node_input(1:name): expected string'); if (typeof a2 !== 'string') throw Error('node_input(2:icon): expected string'); }
    else if (a4 === undefined) { if (!checkClass(a0, Node)) throw Error('node_input(0:node): expected Node'); if (typeof a1 !== 'string') throw Error('node_input(1:name): expected string'); if (typeof a2 !== 'string') throw Error('node_input(2:icon): expected string'); if (!checkClass(a3, Colour)) throw Error('node_input(3:colour): expected Colour'); }
    else if (a5 === undefined) { if (!checkClass(a0, Node)) throw Error('node_input(0:node): expected Node'); if (typeof a1 !== 'string') throw Error('node_input(1:name): expected string'); if (typeof a2 !== 'string') throw Error('node_input(2:icon): expected string'); if (!checkClass(a3, Colour)) throw Error('node_input(3:colour): expected Colour'); if (typeof a4 !== 'boolean') throw Error('node_input(4:active): expected boolean'); }
    else { if (!checkClass(a0, Node)) throw Error('node_input(0:node): expected Node'); if (typeof a1 !== 'string') throw Error('node_input(1:name): expected string'); if (typeof a2 !== 'string') throw Error('node_input(2:icon): expected string'); if (!checkClass(a3, Colour)) throw Error('node_input(3:colour): expected Colour'); if (typeof a4 !== 'boolean') throw Error('node_input(4:active): expected boolean'); if (typeof a5 !== 'boolean') throw Error('node_input(5:connected): expected boolean'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_node_input_2(/*node*/a0.__ptr, ensureString(/*name*/a1)), NodePlug); }
    else if (a3 === undefined) { return wrapPointer(_two_ui_node_input_3(/*node*/a0.__ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2)), NodePlug); }
    else if (a4 === undefined) { return wrapPointer(_two_ui_node_input_4(/*node*/a0.__ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2), /*colour*/a3.__ptr), NodePlug); }
    else if (a5 === undefined) { return wrapPointer(_two_ui_node_input_5(/*node*/a0.__ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2), /*colour*/a3.__ptr, /*active*/a4), NodePlug); }
    else { return wrapPointer(_two_ui_node_input_6(/*node*/a0.__ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2), /*colour*/a3.__ptr, /*active*/a4, /*connected*/a5), NodePlug); }
};
Module['ui']['node_output'] = function(a0, a1, a2, a3, a4, a5) {
    ensureCache.prepare();
    if (a2 === undefined) { if (!checkClass(a0, Node)) throw Error('node_output(0:node): expected Node'); if (typeof a1 !== 'string') throw Error('node_output(1:name): expected string'); }
    else if (a3 === undefined) { if (!checkClass(a0, Node)) throw Error('node_output(0:node): expected Node'); if (typeof a1 !== 'string') throw Error('node_output(1:name): expected string'); if (typeof a2 !== 'string') throw Error('node_output(2:icon): expected string'); }
    else if (a4 === undefined) { if (!checkClass(a0, Node)) throw Error('node_output(0:node): expected Node'); if (typeof a1 !== 'string') throw Error('node_output(1:name): expected string'); if (typeof a2 !== 'string') throw Error('node_output(2:icon): expected string'); if (!checkClass(a3, Colour)) throw Error('node_output(3:colour): expected Colour'); }
    else if (a5 === undefined) { if (!checkClass(a0, Node)) throw Error('node_output(0:node): expected Node'); if (typeof a1 !== 'string') throw Error('node_output(1:name): expected string'); if (typeof a2 !== 'string') throw Error('node_output(2:icon): expected string'); if (!checkClass(a3, Colour)) throw Error('node_output(3:colour): expected Colour'); if (typeof a4 !== 'boolean') throw Error('node_output(4:active): expected boolean'); }
    else { if (!checkClass(a0, Node)) throw Error('node_output(0:node): expected Node'); if (typeof a1 !== 'string') throw Error('node_output(1:name): expected string'); if (typeof a2 !== 'string') throw Error('node_output(2:icon): expected string'); if (!checkClass(a3, Colour)) throw Error('node_output(3:colour): expected Colour'); if (typeof a4 !== 'boolean') throw Error('node_output(4:active): expected boolean'); if (typeof a5 !== 'boolean') throw Error('node_output(5:connected): expected boolean'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_node_output_2(/*node*/a0.__ptr, ensureString(/*name*/a1)), NodePlug); }
    else if (a3 === undefined) { return wrapPointer(_two_ui_node_output_3(/*node*/a0.__ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2)), NodePlug); }
    else if (a4 === undefined) { return wrapPointer(_two_ui_node_output_4(/*node*/a0.__ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2), /*colour*/a3.__ptr), NodePlug); }
    else if (a5 === undefined) { return wrapPointer(_two_ui_node_output_5(/*node*/a0.__ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2), /*colour*/a3.__ptr, /*active*/a4), NodePlug); }
    else { return wrapPointer(_two_ui_node_output_6(/*node*/a0.__ptr, ensureString(/*name*/a1), ensureString(/*icon*/a2), /*colour*/a3.__ptr, /*active*/a4, /*connected*/a5), NodePlug); }
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
Module['ui']['node_cable'] = function(a0, a1, a2) {
    if (!checkClass(a0, Canvas)) throw Error('node_cable(0:canvas): expected Canvas'); if (!checkClass(a1, NodePlug)) throw Error('node_cable(1:plug_out): expected NodePlug'); if (!checkClass(a2, NodePlug)) throw Error('node_cable(2:plug_in): expected NodePlug');
    return wrapPointer(_two_ui_node_cable_3(/*canvas*/a0.__ptr, /*plug_out*/a1.__ptr, /*plug_in*/a2.__ptr), Widget);
};
Module['ui']['canvas'] = function(a0, a1) {
    if (a1 === undefined) { if (!checkClass(a0, Widget)) throw Error('canvas(0:parent): expected Widget'); }
    else { if (!checkClass(a0, Widget)) throw Error('canvas(0:parent): expected Widget'); if (typeof a1 !== 'number') throw Error('canvas(1:num_nodes): expected integer'); }
    if (a1 === undefined) { return wrapPointer(_two_ui_canvas_1(/*parent*/a0.__ptr), Canvas); }
    else { return wrapPointer(_two_ui_canvas_2(/*parent*/a0.__ptr, /*num_nodes*/a1), Canvas); }
};
Module['ui']['scroll_sheet'] = function(a0, a1, a2) {
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('scroll_sheet(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('scroll_sheet(1:style): expected Style'); }
    else { if (!checkClass(a0, Widget)) throw Error('scroll_sheet(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('scroll_sheet(1:style): expected Style'); if (!checkClass(a2, Style)) throw Error('scroll_sheet(2:surface_style): expected Style'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_scroll_sheet_2(/*parent*/a0.__ptr, /*style*/a1.__ptr), ScrollSheet); }
    else { return wrapPointer(_two_ui_scroll_sheet_3(/*parent*/a0.__ptr, /*style*/a1.__ptr, /*surface_style*/a2.__ptr), ScrollSheet); }
};
Module['ui']['scroll_plan'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('scroll_plan(0:parent): expected Widget'); if (!checkClass(a1, Style)) throw Error('scroll_plan(1:style): expected Style');
    return wrapPointer(_two_ui_scroll_plan_2(/*parent*/a0.__ptr, /*style*/a1.__ptr), ScrollSheet);
};
Module['ui']['scrollable'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('scrollable(0:parent): expected Widget');
    return wrapPointer(_two_ui_scrollable_1(/*parent*/a0.__ptr), Widget);
};
Module['ui']['sequence'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('sequence(0:parent): expected Widget');
    return wrapPointer(_two_ui_sequence_1(/*parent*/a0.__ptr), Sequence);
};
Module['ui']['scroll_sequence'] = function(a0) {
    if (!checkClass(a0, Widget)) throw Error('scroll_sequence(0:parent): expected Widget');
    return wrapPointer(_two_ui_scroll_sequence_1(/*parent*/a0.__ptr), Sequence);
};
Module['ui']['select_logic'] = function(a0, a1, a2) {
    if (!checkClass(a0, Widget)) throw Error('select_logic(0:element): expected Widget'); if (!checkClass(a1, Ref)) throw Error('select_logic(1:object): expected Ref'); if (!checkClass(a2, Ref)) throw Error('select_logic(2:selection): expected Ref');
    return !!(_two_ui_select_logic_3(/*element*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1), ensureRef(/*selection*/a2), ensureRefType(/*selection*/a2)));
};
Module['ui']['element'] = function(a0, a1) {
    if (!checkClass(a0, Widget)) throw Error('element(0:parent): expected Widget'); if (!checkClass(a1, Ref)) throw Error('element(1:object): expected Ref');
    return wrapPointer(_two_ui_element_2(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)), Widget);
};
Module['ui']['sequence_element'] = function(a0, a1) {
    if (!checkClass(a0, Sequence)) throw Error('sequence_element(0:parent): expected Sequence'); if (!checkClass(a1, Ref)) throw Error('sequence_element(1:object): expected Ref');
    return wrapPointer(_two_ui_sequence_element_2(/*parent*/a0.__ptr, ensureRef(/*object*/a1), ensureRefType(/*object*/a1)), Widget);
};
Module['ui']['window'] = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { if (!checkClass(a0, Widget)) throw Error('window(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('window(1:title): expected string'); }
    else { if (!checkClass(a0, Widget)) throw Error('window(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('window(1:title): expected string'); if (typeof a2 !== 'number') throw Error('window(2:state): expected integer'); }
    if (a2 === undefined) { return wrapPointer(_two_ui_window_2(/*parent*/a0.__ptr, ensureString(/*title*/a1)), Window); }
    else { return wrapPointer(_two_ui_window_3(/*parent*/a0.__ptr, ensureString(/*title*/a1), /*state*/a2), Window); }
};
Module['ui']['dir_item'] = function(a0, a1) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('dir_item(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('dir_item(1:name): expected string');
    return wrapPointer(_two_ui_dir_item_2(/*parent*/a0.__ptr, ensureString(/*name*/a1)), Widget);
};
Module['ui']['file_item'] = function(a0, a1) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('file_item(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('file_item(1:name): expected string');
    return wrapPointer(_two_ui_file_item_2(/*parent*/a0.__ptr, ensureString(/*name*/a1)), Widget);
};
Module['ui']['dir_node'] = function(a0, a1, a2, a3) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('dir_node(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('dir_node(1:path): expected string'); if (typeof a2 !== 'string') throw Error('dir_node(2:name): expected string'); if (typeof a3 !== 'boolean') throw Error('dir_node(3:collapsed): expected boolean');
    return wrapPointer(_two_ui_dir_node_4(/*parent*/a0.__ptr, ensureString(/*path*/a1), ensureString(/*name*/a2), /*collapsed*/a3), Widget);
};
Module['ui']['file_node'] = function(a0, a1) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('file_node(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('file_node(1:name): expected string');
    return wrapPointer(_two_ui_file_node_2(/*parent*/a0.__ptr, ensureString(/*name*/a1)), Widget);
};
Module['ui']['file_tree'] = function(a0, a1) {
    ensureCache.prepare();
    if (!checkClass(a0, Widget)) throw Error('file_tree(0:parent): expected Widget'); if (typeof a1 !== 'string') throw Error('file_tree(1:path): expected string');
    return wrapPointer(_two_ui_file_tree_2(/*parent*/a0.__ptr, ensureString(/*path*/a1)), Widget);
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
        FrameSolver.prototype.__type = _two_FrameSolver__type();
        RowSolver.prototype.__type = _two_RowSolver__type();
        TableSolver.prototype.__type = _two_TableSolver__type();
        LineSolver.prototype.__type = _two_LineSolver__type();
        GridSolver.prototype.__type = _two_GridSolver__type();
        ScrollSheet.prototype.__type = _two_ScrollSheet__type();
        Sequence.prototype.__type = _two_ui_Sequence__type();
        Tabber.prototype.__type = _two_Tabber__type();
        Expandbox.prototype.__type = _two_Expandbox__type();
        TreeNode.prototype.__type = _two_TreeNode__type();
        Table.prototype.__type = _two_Table__type();
        Dock.prototype.__type = _two_Dock__type();
        Docksystem.prototype.__type = _two_Docksystem__type();
        Dockable.prototype.__type = _two_Dockable__type();
        Docker.prototype.__type = _two_Docker__type();
        Dockspace.prototype.__type = _two_Dockspace__type();
        Dockbar.prototype.__type = _two_Dockbar__type();
        NodePlug.prototype.__type = _two_NodePlug__type();
        Node.prototype.__type = _two_Node__type();
        CanvasConnect.prototype.__type = _two_CanvasConnect__type();
        Canvas.prototype.__type = _two_Canvas__type();
        Ui.prototype.__type = _two_Ui__type();
        Window.prototype.__type = _two_Window__type();
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
        // Solver
        Module['Solver'] = Module['Solver'] || {};
        Module['Solver']['Frame'] = _two_Solver_Frame();
        Module['Solver']['Row'] = _two_Solver_Row();
        Module['Solver']['Grid'] = _two_Solver_Grid();
        Module['Solver']['Table'] = _two_Solver_Table();
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
