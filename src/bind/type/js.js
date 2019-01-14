// Index
function Index() { throw "cannot construct a Index, no constructor in IDL" }
Index.prototype = Object.create(WrapperObject.prototype);
Index.prototype.constructor = Index;
Index.prototype.__class__ = Index;
Index.__cache__ = {};
Module['Index'] = Index;
Index.prototype["indexer"] = Index.prototype.indexer = function(self, type) {
    var self = this.ptr;
    /* type <Type> [] */
    type = type.ptr;
    return wrapPointer(_mud_Index_indexer_1(self, type), Indexer);
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
    }});
Indexer.prototype["__destroy__"] = Indexer.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Indexer__destroy(self);
};
// Ref
function Ref(value, type) {
    /* value <void*> [] */
    /* type <Type> [] */
    if(typeof type !== "undefined" && type !== null) { type = type.ptr; }
    if (value === undefined) { this.ptr = _mud_Ref_Ref_0(); getCache(Ref)[this.ptr] = this; return; }
    this.ptr = _mud_Ref_Ref_2(value, type); getCache(Ref)[this.ptr] = this;
    this.type = Ref;
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
        /* value <Type> [] */
        value = value.ptr;
        _mud_Ref__set_type(self, value);
    }
});
Object.defineProperty(Ref.prototype, "value", {
    get: function() {
        var self = this.ptr;
        return _mud_Ref__get_value(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <void*> [] */
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
        /* value <mud::Id> [] */
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
        /* value <const char*> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_Type__set_name(self, value);
    }
});
Object.defineProperty(Type.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return _mud_Type__get_size(self);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <size_t> [] */
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
        /* value <Type> [] */
        value = value.ptr;
        _mud_Type__set_base(self, value);
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
Module['indexed'] = function(type, id) {
    var self = this.ptr;
    /* type <Type> [] */
    type = type.ptr;
    /* id <uint32_t> [] */
    return wrapPointer(_mud_indexed_2(type, id), Ref);
};

(function() {
    function setup() {
        Index.__type__ = _mud_Index__type();
        Indexer.__type__ = _mud_Indexer__type();
        Ref.__type__ = _mud_Ref__type();
        Type.__type__ = _mud_Type__type();
        Var.__type__ = _mud_Var__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
