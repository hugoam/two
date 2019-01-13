
// Bindings utilities
function WrapperObject() {
}
// Circlifier
function Circlifier(image) {
    var self = this.ptr;
    /* image <Image256> [] */
    if (image === undefined) { this.ptr = _Circlifier_Circlifier_0(self); getCache(Circlifier)[this.ptr] = this; return; }
    this.ptr = _Circlifier_Circlifier_1(self, image); getCache(Circlifier)[this.ptr] = this;
};
Circlifier.prototype = Object.create(WrapperObject.prototype);
Circlifier.prototype.constructor = Circlifier;
Circlifier.prototype.__class__ = Circlifier;
Circlifier.__cache__ = {};
Module['Circlifier'] = Circlifier;
Circlifier.prototype["compute"] = Circlifier.prototype.compute = function(colour, scale) {
    /* colour <Colour> [] */
    /* scale <float> [] */
    if (scale === undefined) { return _Circlifier_compute_1(colour); return; }
    return _Circlifier_compute_2(colour, scale);
};
Circlifier.prototype["__destroy__"] = Circlifier.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Circlifier___destroy__(self);
};
// Fract
function Fract(num_tabs) {
    var self = this.ptr;
    /* num_tabs <size_t> [] */
    if (num_tabs === undefined) { this.ptr = _Fract_Fract_0(self); getCache(Fract)[this.ptr] = this; return; }
    this.ptr = _Fract_Fract_1(self, num_tabs); getCache(Fract)[this.ptr] = this;
};
Fract.prototype = Object.create(WrapperObject.prototype);
Fract.prototype.constructor = Fract;
Fract.prototype.__class__ = Fract;
Fract.__cache__ = {};
Module['Fract'] = Fract;
Fract.prototype["generate"] = Fract.prototype.generate = function(num_tabs) {
    /* num_tabs <size_t> [] */
    if (num_tabs === undefined) { _Fract_generate_0(); return; }
    _Fract_generate_1(num_tabs);
};
Fract.prototype["regen"] = Fract.prototype.regen = function() {
    _Fract_regen_0();
};
Fract.prototype["render"] = Fract.prototype.render = function(rect, pattern, resolution, output_image) {
    /* rect <Rect> [] */
    /* pattern <Pattern> [] */
    /* resolution <uvec2> [] */
    /* output_image <Image256> [] */
    _Fract_render_4(rect, pattern, resolution, output_image);
};
Fract.prototype["render_grid"] = Fract.prototype.render_grid = function(size, pattern, resolution, output_images) {
    /* size <uvec2> [] */
    /* pattern <Pattern> [] */
    /* resolution <uvec2> [] */
    /* output_images <std::vector<mud::Image256>> [] */
    _Fract_render_grid_4(size, pattern, resolution, output_images);
};
Fract.prototype["render_whole"] = Fract.prototype.render_whole = function(pattern, resolution, output_image) {
    /* pattern <Pattern> [] */
    /* resolution <uvec2> [] */
    /* output_image <Image256> [] */
    _Fract_render_whole_3(pattern, resolution, output_image);
};
Object.defineProperty(Fract.prototype, "nutabs", {
    get: function() {
        var self = this.ptr;
        return _Fract_get_nutabs(self);
    },
    set: function(nutabs) {
        var self = this.ptr;
        /* nutabs <size_t> [] */
        _Fract_set_nutabs(self, nutabs);
    }
});
Fract.prototype["__destroy__"] = Fract.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Fract___destroy__(self);
};
// FractSample
function FractSample(fract, rect, resolution) {
    var self = this.ptr;
    /* fract <Fract> [] */
    /* rect <Rect> [] */
    /* resolution <uvec2> [] */
    this.ptr = _FractSample_FractSample_3(self, fract, rect, resolution); getCache(FractSample)[this.ptr] = this;
};
FractSample.prototype = Object.create(WrapperObject.prototype);
FractSample.prototype.constructor = FractSample;
FractSample.prototype.__class__ = FractSample;
FractSample.__cache__ = {};
Module['FractSample'] = FractSample;
FractSample.prototype["render"] = FractSample.prototype.render = function(pattern, outputImage) {
    /* pattern <Pattern> [] */
    /* outputImage <Image256> [] */
    _FractSample_render_2(pattern, outputImage);
};
Object.defineProperty(FractSample.prototype, "fract", {
    get: function() {
        var self = this.ptr;
        return _FractSample_get_fract(self);
    },
    set: function(fract) {
        var self = this.ptr;
        /* fract <Fract> [] */
        _FractSample_set_fract(self, fract);
    }
});
Object.defineProperty(FractSample.prototype, "rect", {
    get: function() {
        var self = this.ptr;
        return _FractSample_get_rect(self);
    },
    set: function(rect) {
        var self = this.ptr;
        /* rect <Rect> [] */
        _FractSample_set_rect(self, rect);
    }
});
Object.defineProperty(FractSample.prototype, "resolution", {
    get: function() {
        var self = this.ptr;
        return _FractSample_get_resolution(self);
    },
    set: function(resolution) {
        var self = this.ptr;
        /* resolution <uvec2> [] */
        _FractSample_set_resolution(self, resolution);
    }
});
FractSample.prototype["__destroy__"] = FractSample.prototype.__destroy__ = function() {
    var self = this.ptr;
    _FractSample___destroy__(self);
};
// FractTab
function FractTab() {
    var self = this.ptr;
    this.ptr = _FractTab_FractTab_0(self); getCache(FractTab)[this.ptr] = this;
};
FractTab.prototype = Object.create(WrapperObject.prototype);
FractTab.prototype.constructor = FractTab;
FractTab.prototype.__class__ = FractTab;
FractTab.__cache__ = {};
Module['FractTab'] = FractTab;
FractTab.prototype["__destroy__"] = FractTab.prototype.__destroy__ = function() {
    var self = this.ptr;
    _FractTab___destroy__(self);
};
// Pattern
function Pattern(palette, sampling, precision, step) {
    var self = this.ptr;
    /* palette <Palette> [] */
    /* sampling <PatternSampling> [] */
    /* precision <float> [] */
    /* step <size_t> [] */
    if (palette === undefined) { this.ptr = _Pattern_Pattern_0(self); getCache(Pattern)[this.ptr] = this; return; }
    if (precision === undefined) { this.ptr = _Pattern_Pattern_2(self, palette, sampling); getCache(Pattern)[this.ptr] = this; return; }
    if (step === undefined) { this.ptr = _Pattern_Pattern_3(self, palette, sampling, precision); getCache(Pattern)[this.ptr] = this; return; }
    this.ptr = _Pattern_Pattern_4(self, palette, sampling, precision, step); getCache(Pattern)[this.ptr] = this;
};
Pattern.prototype = Object.create(WrapperObject.prototype);
Pattern.prototype.constructor = Pattern;
Pattern.prototype.__class__ = Pattern;
Pattern.__cache__ = {};
Module['Pattern'] = Pattern;
Pattern.prototype["__destroy__"] = Pattern.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Pattern___destroy__(self);
};

(function() {
    function setupEnums() {
        // PatternSampling
        Module['PatternSampling']['X'] = _emscripten_enum_PatternSampling_X();
        Module['PatternSampling']['XY'] = _emscripten_enum_PatternSampling_XY();
        Module['PatternSampling']['Depth'] = _emscripten_enum_PatternSampling_Depth();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
