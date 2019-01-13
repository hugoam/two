
// Bindings utilities
function WrapperObject() {
}
// Complex
function Complex(id, type, parts) {
    var self = this.ptr;
    /* id <mud::Id> [] */
    /* type <Type> [] */
    type = type.ptr;
    /* parts <std::vector<mud::Ref>> [] */
    parts = parts.ptr;
    if (parts === undefined) { this.ptr = _Complex_Complex_2(self, id, type); getCache(Complex)[this.ptr] = this; return; }
    this.ptr = _Complex_Complex_3(self, id, type, parts); getCache(Complex)[this.ptr] = this;
};
Complex.prototype = Object.create(WrapperObject.prototype);
Complex.prototype.constructor = Complex;
Complex.prototype.__class__ = Complex;
Complex.__cache__ = {};
Module['Complex'] = Complex;
Complex.prototype["has_part"] = Complex.prototype.has_part = function(type) {
    /* type <Type> [] */
    type = type.ptr;
    return !!(_Complex_has_part_1(type));
};
Object.defineProperty(Complex.prototype, "id", {
    get: function() {
        var self = this.ptr;
        return _Complex_get_id(self);
    },
    set: function(id) {
        var self = this.ptr;
        /* id <mud::Id> [] */
        _Complex_set_id(self, id);
    }
});
Object.defineProperty(Complex.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_Complex_get_type(self), mud::Type);
    },
    set: function(type) {
        var self = this.ptr;
        /* type <Type> [] */
        type = type.ptr;
        _Complex_set_type(self, type);
    }
});
Object.defineProperty(Complex.prototype, "prototype", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_Complex_get_prototype(self), mud::Prototype);
    },
    set: function(prototype) {
        var self = this.ptr;
        /* prototype <Prototype> [] */
        prototype = prototype.ptr;
        _Complex_set_prototype(self, prototype);
    }
});
Complex.prototype["__destroy__"] = Complex.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Complex___destroy__(self);
};
// Entity
function Entity() {
    var self = this.ptr;
    this.ptr = _Entity_Entity_0(self); getCache(Entity)[this.ptr] = this;
};
Entity.prototype = Object.create(WrapperObject.prototype);
Entity.prototype.constructor = Entity;
Entity.prototype.__class__ = Entity;
Entity.__cache__ = {};
Module['Entity'] = Entity;
Entity.prototype["__destroy__"] = Entity.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Entity___destroy__(self);
};
// Prototype
function Prototype() { throw "cannot construct a Prototype, no constructor in IDL" }
Prototype.prototype = Object.create(WrapperObject.prototype);
Prototype.prototype.constructor = Prototype;
Prototype.prototype.__class__ = Prototype;
Prototype.__cache__ = {};
Module['Prototype'] = Prototype;
Prototype.prototype["__destroy__"] = Prototype.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Prototype___destroy__(self);
};

(function() {
    function setupEnums() {
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
