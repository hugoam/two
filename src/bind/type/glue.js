
// Bindings utilities
function WrapperObject() {
}
// Index
function Index() { throw "cannot construct a Index, no constructor in IDL" }
Index.prototype = Object.create(WrapperObject.prototype);
Index.prototype.constructor = Index;
Index.prototype.__class__ = Index;
Index.__cache__ = {};
Module['Index'] = Index;
Index.prototype["indexer"] = Index.prototype.indexer = function(type) {
    /* type <Type> [] */
    type = type.ptr;
    return wrapPointer(_Index_indexer_1(type), mud::Indexer);
};
Index.prototype["__destroy__"] = Index.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Index___destroy__(self);
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
        return wrapPointer(_Indexer_get_type(self), mud::Type);
    }});
Indexer.prototype["__destroy__"] = Indexer.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Indexer___destroy__(self);
};
// Ref
function Ref() { throw "cannot construct a Ref, no constructor in IDL" }
Ref.prototype = Object.create(WrapperObject.prototype);
Ref.prototype.constructor = Ref;
Ref.prototype.__class__ = Ref;
Ref.__cache__ = {};
Module['Ref'] = Ref;
Ref.prototype["__destroy__"] = Ref.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Ref___destroy__(self);
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
        return _Type_get_id(self);
    },
    set: function(id) {
        var self = this.ptr;
        /* id <mud::Id> [] */
        _Type_set_id(self, id);
    }
});
Object.defineProperty(Type.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return _Type_get_name(self);
    },
    set: function(name) {
        var self = this.ptr;
        /* name <const char*> [] */
        _Type_set_name(self, name);
    }
});
Object.defineProperty(Type.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return _Type_get_size(self);
    },
    set: function(size) {
        var self = this.ptr;
        /* size <size_t> [] */
        _Type_set_size(self, size);
    }
});
Object.defineProperty(Type.prototype, "base", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_Type_get_base(self), mud::Type);
    },
    set: function(base) {
        var self = this.ptr;
        /* base <Type> [] */
        base = base.ptr;
        _Type_set_base(self, base);
    }
});
Type.prototype["__destroy__"] = Type.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Type___destroy__(self);
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
    _Var___destroy__(self);
};

(function() {
    function setupEnums() {
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
