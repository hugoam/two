Module['stl'] = Module['stl'] || {};
// Index
function Index() { throw "cannot construct a Index, no constructor in IDL" }
Index.prototype = Object.create(WrapperObject.prototype);
Index.prototype.constructor = Index;
Index.prototype.__class = Index;
Index.__cache = {};
Module['Index'] = Index;
Index.prototype["indexer"] = Index.prototype.indexer = function(a0) {
    if (!checkClass(a0, Type) throw Error('indexer(0:type): expected Type');
    return wrapPointer(_mud_Index_indexer_1(this.__ptr, /*type*/a0.__ptr), Indexer);
};
Index.prototype["__destroy"] = Index.prototype.__destroy = function() {
    _mud_Index__destroy(this.__ptr);
};
// Indexer
function Indexer() { throw "cannot construct a Indexer, no constructor in IDL" }
Indexer.prototype = Object.create(WrapperObject.prototype);
Indexer.prototype.constructor = Indexer;
Indexer.prototype.__class = Indexer;
Indexer.__cache = {};
Module['Indexer'] = Indexer;
Object.defineProperty(Indexer.prototype, "type", {
    get: function() {
        return wrapPointer(_mud_Indexer__get_type(this.__ptr), Type);
    },
    set: function(value) {
        _mud_Indexer__set_type(this.__ptr, value.__ptr);
    }
});
Indexer.prototype["__destroy"] = Indexer.prototype.__destroy = function() {
    _mud_Indexer__destroy(this.__ptr);
};
// Prototype
function Prototype() { throw "cannot construct a Prototype, no constructor in IDL" }
Prototype.prototype = Object.create(WrapperObject.prototype);
Prototype.prototype.constructor = Prototype;
Prototype.prototype.__class = Prototype;
Prototype.__cache = {};
Module['Prototype'] = Prototype;
Prototype.prototype["__destroy"] = Prototype.prototype.__destroy = function() {
    _mud_Prototype__destroy(this.__ptr);
};
// Ref
function Ref(a0, a1) {
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'number') throw Error('Ref(0:value): expected integer'); if (!checkClass(a1, Type) throw Error('Ref(1:type): expected Type'); }
    if (a0 === undefined) { this.__ptr = _mud_Ref__construct_0(); getCache(Ref)[this.__ptr] = this; }
    else { this.__ptr = _mud_Ref__construct_2(/*value*/a0, /*type*/a1.__ptr); getCache(Ref)[this.__ptr] = this; }
};
Ref.prototype = Object.create(WrapperObject.prototype);
Ref.prototype.constructor = Ref;
Ref.prototype.__class = Ref;
Ref.__cache = {};
Module['Ref'] = Ref;
Object.defineProperty(Ref.prototype, "type", {
    get: function() {
        return wrapPointer(_mud_Ref__get_type(this.__ptr), Type);
    },
    set: function(value) {
        _mud_Ref__set_type(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Ref.prototype, "value", {
    get: function() {
        return _mud_Ref__get_value(this.__ptr);
    },
    set: function(value) {
        _mud_Ref__set_value(this.__ptr, value);
    }
});
Ref.prototype["__destroy"] = Ref.prototype.__destroy = function() {
    _mud_Ref__destroy(this.__ptr);
};
// Type
function Type() { throw "cannot construct a Type, no constructor in IDL" }
Type.prototype = Object.create(WrapperObject.prototype);
Type.prototype.constructor = Type;
Type.prototype.__class = Type;
Type.__cache = {};
Module['Type'] = Type;
Object.defineProperty(Type.prototype, "id", {
    get: function() {
        return _mud_Type__get_id(this.__ptr);
    },
    set: function(value) {
        _mud_Type__set_id(this.__ptr, value);
    }
});
Object.defineProperty(Type.prototype, "name", {
    get: function() {
        return UTF8ToString(_mud_Type__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Type__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Type.prototype, "size", {
    get: function() {
        return _mud_Type__get_size(this.__ptr);
    },
    set: function(value) {
        _mud_Type__set_size(this.__ptr, value);
    }
});
Object.defineProperty(Type.prototype, "base", {
    get: function() {
        return wrapPointer(_mud_Type__get_base(this.__ptr), Type);
    },
    set: function(value) {
        _mud_Type__set_base(this.__ptr, value.__ptr);
    }
});
Type.prototype["__destroy"] = Type.prototype.__destroy = function() {
    _mud_Type__destroy(this.__ptr);
};
// Var
function Var() { throw "cannot construct a Var, no constructor in IDL" }
Var.prototype = Object.create(WrapperObject.prototype);
Var.prototype.constructor = Var;
Var.prototype.__class = Var;
Var.__cache = {};
Module['Var'] = Var;
Var.prototype["__destroy"] = Var.prototype.__destroy = function() {
    _mud_Var__destroy(this.__ptr);
};
Module['indexed'] = function(a0, a1) {
    if (!checkClass(a0, Type) throw Error('indexed(0:type): expected Type'); if (typeof a1 !== 'number') throw Error('indexed(1:id): expected integer');
    return wrapPointer(_mud_indexed_2(/*type*/a0.__ptr, /*id*/a1), Ref);
};

(function() {
    function setup() {
        Index.prototype.__type = _mud_Index__type();
        Indexer.prototype.__type = _mud_Indexer__type();
        Prototype.prototype.__type = _mud_Prototype__type();
        Ref.prototype.__type = _mud_Ref__type();
        Type.prototype.__type = _mud_Type__type();
        Var.prototype.__type = _mud_Var__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
