// Circlifier
function Circlifier(image) {
    /* image <Image256> [] */
    image = image.ptr;
    this.ptr = _mud_Circlifier_Circlifier_1(image); getCache(Circlifier)[this.ptr] = this;
    this.type = Circlifier;
};
Circlifier.prototype = Object.create(WrapperObject.prototype);
Circlifier.prototype.constructor = Circlifier;
Circlifier.prototype.__class__ = Circlifier;
Circlifier.__cache__ = {};
Module['Circlifier'] = Circlifier;
Circlifier.prototype["__destroy__"] = Circlifier.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Circlifier__destroy(self);
};
// Fract
function Fract(num_tabs) {
    /* num_tabs <size_t> [] */
    if (num_tabs === undefined) { this.ptr = _mud_Fract_Fract_0(); getCache(Fract)[this.ptr] = this; return; }
    this.ptr = _mud_Fract_Fract_1(num_tabs); getCache(Fract)[this.ptr] = this;
    this.type = Fract;
};
Fract.prototype = Object.create(WrapperObject.prototype);
Fract.prototype.constructor = Fract;
Fract.prototype.__class__ = Fract;
Fract.__cache__ = {};
Module['Fract'] = Fract;
Fract.prototype["generate"] = Fract.prototype.generate = function(self, num_tabs) {
    var self = this.ptr;
    /* num_tabs <size_t> [] */
    if (num_tabs === undefined) { _mud_Fract_generate_0(self); return; }
    _mud_Fract_generate_1(self, num_tabs);
};
Fract.prototype["regen"] = Fract.prototype.regen = function(self) {
    var self = this.ptr;
    _mud_Fract_regen_0(self);
};
Fract.prototype["render"] = Fract.prototype.render = function(self, rect, pattern, resolution, output_image) {
    var self = this.ptr;
    /* rect <Rect> [] */
    rect = rect.ptr;
    /* pattern <Pattern> [] */
    pattern = pattern.ptr;
    /* resolution <uvec2> [] */
    resolution = resolution.ptr;
    /* output_image <Image256> [] */
    output_image = output_image.ptr;
    _mud_Fract_render_4(self, rect, pattern, resolution, output_image);
};
Fract.prototype["render_whole"] = Fract.prototype.render_whole = function(self, pattern, resolution, output_image) {
    var self = this.ptr;
    /* pattern <Pattern> [] */
    pattern = pattern.ptr;
    /* resolution <uvec2> [] */
    resolution = resolution.ptr;
    /* output_image <Image256> [] */
    output_image = output_image.ptr;
    _mud_Fract_render_whole_3(self, pattern, resolution, output_image);
};
Object.defineProperty(Fract.prototype, "nutabs", {
    get: function() {
        var self = this.ptr;
        return _mud_Fract__get_nutabs(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <size_t> [] */
        _mud_Fract__set_nutabs(self, value);
    }
});
Fract.prototype["__destroy__"] = Fract.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Fract__destroy(self);
};
// FractSample
function FractSample(fract, rect, resolution) {
    /* fract <Fract> [] */
    fract = fract.ptr;
    /* rect <Rect> [] */
    rect = rect.ptr;
    /* resolution <uvec2> [] */
    resolution = resolution.ptr;
    this.ptr = _mud_FractSample_FractSample_3(fract, rect, resolution); getCache(FractSample)[this.ptr] = this;
    this.type = FractSample;
};
FractSample.prototype = Object.create(WrapperObject.prototype);
FractSample.prototype.constructor = FractSample;
FractSample.prototype.__class__ = FractSample;
FractSample.__cache__ = {};
Module['FractSample'] = FractSample;
FractSample.prototype["render"] = FractSample.prototype.render = function(self, pattern, outputImage) {
    var self = this.ptr;
    /* pattern <Pattern> [] */
    pattern = pattern.ptr;
    /* outputImage <Image256> [] */
    outputImage = outputImage.ptr;
    _mud_FractSample_render_2(self, pattern, outputImage);
};
Object.defineProperty(FractSample.prototype, "fract", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_FractSample__get_fract(self), Fract);
    }});
Object.defineProperty(FractSample.prototype, "rect", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_FractSample__get_rect(self), Rect);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Rect> [] */
        value = value.ptr;
        _mud_FractSample__set_rect(self, value);
    }
});
Object.defineProperty(FractSample.prototype, "resolution", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_FractSample__get_resolution(self), uvec2);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <uvec2> [] */
        value = value.ptr;
        _mud_FractSample__set_resolution(self, value);
    }
});
FractSample.prototype["__destroy__"] = FractSample.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FractSample__destroy(self);
};
// FractTab
function FractTab() {
    this.ptr = _mud_FractTab_FractTab_0(); getCache(FractTab)[this.ptr] = this;
    this.type = FractTab;
};
FractTab.prototype = Object.create(WrapperObject.prototype);
FractTab.prototype.constructor = FractTab;
FractTab.prototype.__class__ = FractTab;
FractTab.__cache__ = {};
Module['FractTab'] = FractTab;
FractTab.prototype["__destroy__"] = FractTab.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_FractTab__destroy(self);
};
// Pattern
function Pattern(palette, sampling, precision, step) {
    /* palette <Palette> [] */
    palette = palette.ptr;
    /* sampling <PatternSampling> [] */
    if (sampling && typeof sampling === "object") sampling = sampling.ptr;
    /* precision <float> [] */
    /* step <size_t> [] */
    if (precision === undefined) { this.ptr = _mud_Pattern_Pattern_2(palette, sampling); getCache(Pattern)[this.ptr] = this; return; }
    if (step === undefined) { this.ptr = _mud_Pattern_Pattern_3(palette, sampling, precision); getCache(Pattern)[this.ptr] = this; return; }
    this.ptr = _mud_Pattern_Pattern_4(palette, sampling, precision, step); getCache(Pattern)[this.ptr] = this;
    this.type = Pattern;
};
Pattern.prototype = Object.create(WrapperObject.prototype);
Pattern.prototype.constructor = Pattern;
Pattern.prototype.__class__ = Pattern;
Pattern.__cache__ = {};
Module['Pattern'] = Pattern;
Pattern.prototype["__destroy__"] = Pattern.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Pattern__destroy(self);
};
Module['generate_fract'] = function(resolution, pattern, output_image) {
    var self = this.ptr;
    /* resolution <uvec2> [] */
    resolution = resolution.ptr;
    /* pattern <Pattern> [] */
    pattern = pattern.ptr;
    /* output_image <Image256> [] */
    output_image = output_image.ptr;
    _mud_generate_fract_3(resolution, pattern, output_image);
};

(function() {
    function setup() {
        Circlifier.__type__ = _mud_Circlifier__type();
        Fract.__type__ = _mud_Fract__type();
        FractSample.__type__ = _mud_FractSample__type();
        FractTab.__type__ = _mud_FractTab__type();
        Pattern.__type__ = _mud_Pattern__type();
        // PatternSampling
        Module['PatternSampling'] = Module['PatternSampling'] || {};
        Module['PatternSampling']['X'] = _mud_PatternSampling_X();
        Module['PatternSampling']['XY'] = _mud_PatternSampling_XY();
        Module['PatternSampling']['Depth'] = _mud_PatternSampling_Depth();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
