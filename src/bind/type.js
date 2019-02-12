Module['stl'] = Module['stl'] || {};
// Index
function Index() { throw "cannot construct a Index, no constructor in IDL" }
Index.prototype = Object.create(WrapperObject.prototype);
Index.prototype.constructor = Index;
Index.prototype.__class__ = Index;
Index.__cache__ = {};
Module['Index'] = Index;
Index.prototype["indexer"] = Index.prototype.indexer = function(a0) {
    var self = this.ptr;
    return wrapPointer(_mud_Index_indexer_1(self, /*type*/a0.ptr), Indexer);
};
Index.prototype["__destroy__"] = Index.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Index__destroy(self);
};
// Indexer
function Indexer() { throw "cannot construct a Indexer, no constructor in IDL" }
Indexer.prototype = Object.create(WrapperObject.prototype);
Indexer.prototype.constructor = Indexer;
Indexer.prototype.__class__ = Indexer;
Indexer.__cache__ = {};
Module['Indexer'] = Indexer;
Object.defineProperty(Indexer.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Indexer__get_type(self), Type);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Indexer__set_type(self, value.ptr);
    }
});
Indexer.prototype["__destroy__"] = Indexer.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Indexer__destroy(self);
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
    _mud_Prototype__destroy(self);
};
// Ref
function Ref(a0, a1) {
    if (a0 === undefined) { this.ptr = _mud_Ref__construct_0(); this.type = Ref; getCache(Ref)[this.ptr] = this; return; }
    this.ptr = _mud_Ref__construct_2(/*value*/a0, /*type*/a1.ptr); this.type = Ref; getCache(Ref)[this.ptr] = this;
};
Ref.prototype = Object.create(WrapperObject.prototype);
Ref.prototype.constructor = Ref;
Ref.prototype.__class__ = Ref;
Ref.__cache__ = {};
Module['Ref'] = Ref;
Object.defineProperty(Ref.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Ref__get_type(self), Type);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Ref__set_type(self, value.ptr);
    }
});
Object.defineProperty(Ref.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return _mud_Ref__get_value(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Ref__set_value(self, value);
    }
});
Ref.prototype["__destroy__"] = Ref.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Ref__destroy(self);
};
// Type
function Type() { throw "cannot construct a Type, no constructor in IDL" }
Type.prototype = Object.create(WrapperObject.prototype);
Type.prototype.constructor = Type;
Type.prototype.__class__ = Type;
Type.__cache__ = {};
Module['Type'] = Type;
Object.defineProperty(Type.prototype, "id", {
    get: function() {
        var self = this.ptr;
        return _mud_Type__get_id(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Type__set_id(self, value);
    }
});
Object.defineProperty(Type.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Type__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Type__set_name(self, ensureString(value));
    }
});
Object.defineProperty(Type.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return _mud_Type__get_size(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Type__set_size(self, value);
    }
});
Object.defineProperty(Type.prototype, "base", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Type__get_base(self), Type);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Type__set_base(self, value.ptr);
    }
});
Type.prototype["__destroy__"] = Type.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Type__destroy(self);
};
// Var
function Var() { throw "cannot construct a Var, no constructor in IDL" }
Var.prototype = Object.create(WrapperObject.prototype);
Var.prototype.constructor = Var;
Var.prototype.__class__ = Var;
Var.__cache__ = {};
Module['Var'] = Var;
Var.prototype["__destroy__"] = Var.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Var__destroy(self);
};
Module['indexed'] = function(a0, a1) {
    return wrapPointer(_mud_indexed_2(/*type*/a0.ptr, /*id*/a1), Ref);
};

(function() {
    function setup() {
        Index.__type__ = _mud_Index__type();
        Indexer.__type__ = _mud_Indexer__type();
        Prototype.__type__ = _mud_Prototype__type();
        Ref.__type__ = _mud_Ref__type();
        Type.__type__ = _mud_Type__type();
        Var.__type__ = _mud_Var__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
