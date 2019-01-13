
// Bindings utilities
function WrapperObject() {
}
// Call
function Call(callable, arguments) {
    var self = this.ptr;
    /* callable <Callable> [] */
    /* arguments <std::vector<mud::Var>> [] */
    if (callable === undefined) { this.ptr = _Call_Call_0(self); getCache(Call)[this.ptr] = this; return; }
    this.ptr = _Call_Call_2(self, callable, arguments); getCache(Call)[this.ptr] = this;
};
Call.prototype = Object.create(WrapperObject.prototype);
Call.prototype.constructor = Call;
Call.prototype.__class__ = Call;
Call.__cache__ = {};
Module['Call'] = Call;
Object.defineProperty(Call.prototype, "arguments", {
    get: function() {
        var self = this.ptr;
        return _Call_get_arguments(self);
    },
    set: function(arguments) {
        var self = this.ptr;
        /* arguments <std::vector<mud::Var>> [] */
        _Call_set_arguments(self, arguments);
    }
});
Object.defineProperty(Call.prototype, "result", {
    get: function() {
        var self = this.ptr;
        return _Call_get_result(self);
    },
    set: function(result) {
        var self = this.ptr;
        /* result <Var> [] */
        _Call_set_result(self, result);
    }
});
Call.prototype["__destroy__"] = Call.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Call___destroy__(self);
};
// Callable
function Callable() { throw "cannot construct a Callable, no constructor in IDL" }
Callable.prototype = Object.create(WrapperObject.prototype);
Callable.prototype.constructor = Callable;
Callable.prototype.__class__ = Callable;
Callable.__cache__ = {};
Module['Callable'] = Callable;
Callable.prototype["__destroy__"] = Callable.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Callable___destroy__(self);
};
// Class
function Class() { throw "cannot construct a Class, no constructor in IDL" }
Class.prototype = Object.create(WrapperObject.prototype);
Class.prototype.constructor = Class;
Class.prototype.__class__ = Class;
Class.__cache__ = {};
Module['Class'] = Class;
Class.prototype["__destroy__"] = Class.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Class___destroy__(self);
};
// Convert
function Convert() { throw "cannot construct a Convert, no constructor in IDL" }
Convert.prototype = Object.create(WrapperObject.prototype);
Convert.prototype.constructor = Convert;
Convert.prototype.__class__ = Convert;
Convert.__cache__ = {};
Module['Convert'] = Convert;
Convert.prototype["__destroy__"] = Convert.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Convert___destroy__(self);
};
// Creator
function Creator() { throw "cannot construct a Creator, no constructor in IDL" }
Creator.prototype = Object.create(WrapperObject.prototype);
Creator.prototype.constructor = Creator;
Creator.prototype.__class__ = Creator;
Creator.__cache__ = {};
Module['Creator'] = Creator;
Object.defineProperty(Creator.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return _Creator_get_type(self);
    },
    set: function(type) {
        var self = this.ptr;
        /* type <Type> [] */
        _Creator_set_type(self, type);
    }
});
Object.defineProperty(Creator.prototype, "construct", {
    get: function() {
        var self = this.ptr;
        return !!(_Creator_get_construct(self));
    },
    set: function(construct) {
        var self = this.ptr;
        /* construct <bool> [] */
        _Creator_set_construct(self, construct);
    }
});
Object.defineProperty(Creator.prototype, "prototype", {
    get: function() {
        var self = this.ptr;
        return _Creator_get_prototype(self);
    },
    set: function(prototype) {
        var self = this.ptr;
        /* prototype <Type> [] */
        _Creator_set_prototype(self, prototype);
    }
});
Object.defineProperty(Creator.prototype, "injector", {
    get: function() {
        var self = this.ptr;
        return _Creator_get_injector(self);
    },
    set: function(injector) {
        var self = this.ptr;
        /* injector <Injector> [] */
        _Creator_set_injector(self, injector);
    }
});
Creator.prototype["__destroy__"] = Creator.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Creator___destroy__(self);
};
// Enum
function Enum() { throw "cannot construct a Enum, no constructor in IDL" }
Enum.prototype = Object.create(WrapperObject.prototype);
Enum.prototype.constructor = Enum;
Enum.prototype.__class__ = Enum;
Enum.__cache__ = {};
Module['Enum'] = Enum;
Enum.prototype["__destroy__"] = Enum.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Enum___destroy__(self);
};
// Member
function Member() { throw "cannot construct a Member, no constructor in IDL" }
Member.prototype = Object.create(WrapperObject.prototype);
Member.prototype.constructor = Member;
Member.prototype.__class__ = Member;
Member.__cache__ = {};
Module['Member'] = Member;
Member.prototype["__destroy__"] = Member.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Member___destroy__(self);
};
// Meta
function Meta() { throw "cannot construct a Meta, no constructor in IDL" }
Meta.prototype = Object.create(WrapperObject.prototype);
Meta.prototype.constructor = Meta;
Meta.prototype.__class__ = Meta;
Meta.__cache__ = {};
Module['Meta'] = Meta;
Meta.prototype["__destroy__"] = Meta.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Meta___destroy__(self);
};
// Module
function Module() { throw "cannot construct a Module, no constructor in IDL" }
Module.prototype = Object.create(WrapperObject.prototype);
Module.prototype.constructor = Module;
Module.prototype.__class__ = Module;
Module.__cache__ = {};
Module['Module'] = Module;
Object.defineProperty(Module.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_Module_get_name(self));
    }});
Object.defineProperty(Module.prototype, "deps", {
    get: function() {
        var self = this.ptr;
        return _Module_get_deps(self);
    },
    set: function(deps) {
        var self = this.ptr;
        /* deps <std::vector<mud::Module*>> [] */
        _Module_set_deps(self, deps);
    }
});
Object.defineProperty(Module.prototype, "types", {
    get: function() {
        var self = this.ptr;
        return _Module_get_types(self);
    },
    set: function(types) {
        var self = this.ptr;
        /* types <std::vector<mud::Type*>> [] */
        _Module_set_types(self, types);
    }
});
Object.defineProperty(Module.prototype, "functions", {
    get: function() {
        var self = this.ptr;
        return _Module_get_functions(self);
    },
    set: function(functions) {
        var self = this.ptr;
        /* functions <std::vector<mud::Function*>> [] */
        _Module_set_functions(self, functions);
    }
});
Object.defineProperty(Module.prototype, "path", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_Module_get_path(self));
    }});
Module.prototype["__destroy__"] = Module.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Module___destroy__(self);
};
// Namespace
function Namespace() { throw "cannot construct a Namespace, no constructor in IDL" }
Namespace.prototype = Object.create(WrapperObject.prototype);
Namespace.prototype.constructor = Namespace;
Namespace.prototype.__class__ = Namespace;
Namespace.__cache__ = {};
Module['Namespace'] = Namespace;
Namespace.prototype["__destroy__"] = Namespace.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Namespace___destroy__(self);
};
// Operator
function Operator() {
    var self = this.ptr;
    this.ptr = _Operator_Operator_0(self); getCache(Operator)[this.ptr] = this;
};
Operator.prototype = Object.create(WrapperObject.prototype);
Operator.prototype.constructor = Operator;
Operator.prototype.__class__ = Operator;
Operator.__cache__ = {};
Module['Operator'] = Operator;
Object.defineProperty(Operator.prototype, "function", {
    get: function() {
        var self = this.ptr;
        return _Operator_get_function(self);
    },
    set: function(function) {
        var self = this.ptr;
        /* function <Function> [] */
        _Operator_set_function(self, function);
    }
});
Object.defineProperty(Operator.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return _Operator_get_type(self);
    },
    set: function(type) {
        var self = this.ptr;
        /* type <Type> [] */
        _Operator_set_type(self, type);
    }
});
Object.defineProperty(Operator.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_Operator_get_name(self));
    }});
Object.defineProperty(Operator.prototype, "sign", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_Operator_get_sign(self));
    }});
Operator.prototype["__destroy__"] = Operator.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Operator___destroy__(self);
};
// Param
function Param() { throw "cannot construct a Param, no constructor in IDL" }
Param.prototype = Object.create(WrapperObject.prototype);
Param.prototype.constructor = Param;
Param.prototype.__class__ = Param;
Param.__cache__ = {};
Module['Param'] = Param;
Param.prototype["__destroy__"] = Param.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Param___destroy__(self);
};
// Signature
function Signature() { throw "cannot construct a Signature, no constructor in IDL" }
Signature.prototype = Object.create(WrapperObject.prototype);
Signature.prototype.constructor = Signature;
Signature.prototype.__class__ = Signature;
Signature.__cache__ = {};
Module['Signature'] = Signature;
Signature.prototype["__destroy__"] = Signature.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Signature___destroy__(self);
};
// Static
function Static() { throw "cannot construct a Static, no constructor in IDL" }
Static.prototype = Object.create(WrapperObject.prototype);
Static.prototype.constructor = Static;
Static.prototype.__class__ = Static;
Static.__cache__ = {};
Module['Static'] = Static;
Static.prototype["__destroy__"] = Static.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Static___destroy__(self);
};
// System
function System() { throw "cannot construct a System, no constructor in IDL" }
System.prototype = Object.create(WrapperObject.prototype);
System.prototype.constructor = System;
System.prototype.__class__ = System;
System.__cache__ = {};
Module['System'] = System;
Object.defineProperty(System.prototype, "modules", {
    get: function() {
        var self = this.ptr;
        return _System_get_modules(self);
    },
    set: function(modules) {
        var self = this.ptr;
        /* modules <std::vector<mud::Module*>> [] */
        _System_set_modules(self, modules);
    }
});
Object.defineProperty(System.prototype, "types", {
    get: function() {
        var self = this.ptr;
        return _System_get_types(self);
    },
    set: function(types) {
        var self = this.ptr;
        /* types <std::vector<mud::Type*>> [] */
        _System_set_types(self, types);
    }
});
Object.defineProperty(System.prototype, "functions", {
    get: function() {
        var self = this.ptr;
        return _System_get_functions(self);
    },
    set: function(functions) {
        var self = this.ptr;
        /* functions <std::vector<mud::Function*>> [] */
        _System_set_functions(self, functions);
    }
});
System.prototype["__destroy__"] = System.prototype.__destroy__ = function() {
    var self = this.ptr;
    _System___destroy__(self);
};
// Constructor
function Constructor() { throw "cannot construct a Constructor, no constructor in IDL" }
Constructor.prototype = Object.create(WrapperObject.prototype);
Constructor.prototype.constructor = Constructor;
Constructor.prototype.__class__ = Constructor;
Constructor.__cache__ = {};
Module['Constructor'] = Constructor;
Constructor.prototype["__destroy__"] = Constructor.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Constructor___destroy__(self);
};
// CopyConstructor
function CopyConstructor() { throw "cannot construct a CopyConstructor, no constructor in IDL" }
CopyConstructor.prototype = Object.create(WrapperObject.prototype);
CopyConstructor.prototype.constructor = CopyConstructor;
CopyConstructor.prototype.__class__ = CopyConstructor;
CopyConstructor.__cache__ = {};
Module['CopyConstructor'] = CopyConstructor;
CopyConstructor.prototype["__destroy__"] = CopyConstructor.prototype.__destroy__ = function() {
    var self = this.ptr;
    _CopyConstructor___destroy__(self);
};
// Destructor
function Destructor() { throw "cannot construct a Destructor, no constructor in IDL" }
Destructor.prototype = Object.create(WrapperObject.prototype);
Destructor.prototype.constructor = Destructor;
Destructor.prototype.__class__ = Destructor;
Destructor.__cache__ = {};
Module['Destructor'] = Destructor;
Destructor.prototype["__destroy__"] = Destructor.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Destructor___destroy__(self);
};
// Function
function Function() { throw "cannot construct a Function, no constructor in IDL" }
Function.prototype = Object.create(WrapperObject.prototype);
Function.prototype.constructor = Function;
Function.prototype.__class__ = Function;
Function.__cache__ = {};
Module['Function'] = Function;
Function.prototype["__destroy__"] = Function.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Function___destroy__(self);
};
// Injector
function Injector() { throw "cannot construct a Injector, no constructor in IDL" }
Injector.prototype = Object.create(WrapperObject.prototype);
Injector.prototype.constructor = Injector;
Injector.prototype.__class__ = Injector;
Injector.__cache__ = {};
Module['Injector'] = Injector;
Injector.prototype["__destroy__"] = Injector.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Injector___destroy__(self);
};
// Method
function Method() { throw "cannot construct a Method, no constructor in IDL" }
Method.prototype = Object.create(WrapperObject.prototype);
Method.prototype.constructor = Method;
Method.prototype.__class__ = Method;
Method.__cache__ = {};
Module['Method'] = Method;
Method.prototype["__destroy__"] = Method.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Method___destroy__(self);
};

(function() {
    function setupEnums() {
        
        // 'TypeClass'
        Module['TypeClass']['None'] = _emscripten_enum_TypeClass_None();
        Module['TypeClass']['Object'] = _emscripten_enum_TypeClass_Object();
        Module['TypeClass']['Struct'] = _emscripten_enum_TypeClass_Struct();
        Module['TypeClass']['Sequence'] = _emscripten_enum_TypeClass_Sequence();
        Module['TypeClass']['BaseType'] = _emscripten_enum_TypeClass_BaseType();
        Module['TypeClass']['Enum'] = _emscripten_enum_TypeClass_Enum();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
