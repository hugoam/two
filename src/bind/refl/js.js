
// Bindings utilities
function WrapperObject() {
}
// Call
function Call(callable, arguments) {
    var self = this.ptr;
    /* callable <Callable> [] */
    callable = callable.ptr;
    /* arguments <std::vector<mud::Var>> [] */
    arguments = arguments.ptr;
    if (callable === undefined) { this.ptr = _mud_Call_Call_0(self); getCache(Call)[this.ptr] = this; return; }
    this.ptr = _mud_Call_Call_2(self, callable, arguments); getCache(Call)[this.ptr] = this;
};
Call.prototype = Object.create(WrapperObject.prototype);
Call.prototype.constructor = Call;
Call.prototype.__class__ = Call;
Call.__cache__ = {};
Module['Call'] = Call;
Object.defineProperty(Call.prototype, "result", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Call__get_result(self), mud::Var);
    }});
Call.prototype["__destroy__"] = Call.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Call__destroy(self);
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
    _mud_Callable__destroy(self);
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
    _mud_Class__destroy(self);
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
    _mud_Convert__destroy(self);
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
        return wrapPointer(_mud_Creator__get_type(self), mud::Type);
    }});
Object.defineProperty(Creator.prototype, "construct", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Creator__get_construct(self));
    },
    set: function(construct) {
        var self = this.ptr;
        /* construct <bool> [] */
        _mud_Creator__set_construct(self, construct);
    }
});
Object.defineProperty(Creator.prototype, "prototype", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Creator__get_prototype(self), mud::Type);
    },
    set: function(prototype) {
        var self = this.ptr;
        /* prototype <Type> [] */
        prototype = prototype.ptr;
        _mud_Creator__set_prototype(self, prototype);
    }
});
Object.defineProperty(Creator.prototype, "injector", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Creator__get_injector(self), mud::Injector);
    }});
Creator.prototype["__destroy__"] = Creator.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Creator__destroy(self);
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
    _mud_Enum__destroy(self);
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
    _mud_Member__destroy(self);
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
    _mud_Meta__destroy(self);
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
        return _mud_Module__get_name(self);
    },
    set: function(name) {
        var self = this.ptr;
        /* name <const char*> [] */
        _mud_Module__set_name(self, name);
    }
});
Object.defineProperty(Module.prototype, "path", {
    get: function() {
        var self = this.ptr;
        return _mud_Module__get_path(self);
    },
    set: function(path) {
        var self = this.ptr;
        /* path <const char*> [] */
        _mud_Module__set_path(self, path);
    }
});
Module.prototype["__destroy__"] = Module.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Module__destroy(self);
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
    _mud_Namespace__destroy(self);
};
// Operator
function Operator() {
    var self = this.ptr;
    this.ptr = _mud_Operator_Operator_0(self); getCache(Operator)[this.ptr] = this;
};
Operator.prototype = Object.create(WrapperObject.prototype);
Operator.prototype.constructor = Operator;
Operator.prototype.__class__ = Operator;
Operator.__cache__ = {};
Module['Operator'] = Operator;
Object.defineProperty(Operator.prototype, "function", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Operator__get_function(self), mud::Function);
    },
    set: function(function) {
        var self = this.ptr;
        /* function <Function> [] */
        function = function.ptr;
        _mud_Operator__set_function(self, function);
    }
});
Object.defineProperty(Operator.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Operator__get_type(self), mud::Type);
    },
    set: function(type) {
        var self = this.ptr;
        /* type <Type> [] */
        type = type.ptr;
        _mud_Operator__set_type(self, type);
    }
});
Object.defineProperty(Operator.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return _mud_Operator__get_name(self);
    },
    set: function(name) {
        var self = this.ptr;
        /* name <const char*> [] */
        _mud_Operator__set_name(self, name);
    }
});
Object.defineProperty(Operator.prototype, "sign", {
    get: function() {
        var self = this.ptr;
        return _mud_Operator__get_sign(self);
    },
    set: function(sign) {
        var self = this.ptr;
        /* sign <const char*> [] */
        _mud_Operator__set_sign(self, sign);
    }
});
Operator.prototype["__destroy__"] = Operator.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Operator__destroy(self);
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
    _mud_Param__destroy(self);
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
    _mud_Signature__destroy(self);
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
    _mud_Static__destroy(self);
};
// System
function System() { throw "cannot construct a System, no constructor in IDL" }
System.prototype = Object.create(WrapperObject.prototype);
System.prototype.constructor = System;
System.prototype.__class__ = System;
System.__cache__ = {};
Module['System'] = System;
System.prototype["__destroy__"] = System.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_System__destroy(self);
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
    _mud_Constructor__destroy(self);
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
    _mud_CopyConstructor__destroy(self);
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
    _mud_Destructor__destroy(self);
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
    _mud_Function__destroy(self);
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
    _mud_Injector__destroy(self);
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
    _mud_Method__destroy(self);
};

(function() {
    function setupEnums() {
        // TypeClass
        Module['TypeClass']['None'] = _mud_TypeClass_None();
        Module['TypeClass']['Object'] = _mud_TypeClass_Object();
        Module['TypeClass']['Struct'] = _mud_TypeClass_Struct();
        Module['TypeClass']['Sequence'] = _mud_TypeClass_Sequence();
        Module['TypeClass']['BaseType'] = _mud_TypeClass_BaseType();
        Module['TypeClass']['Enum'] = _mud_TypeClass_Enum();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
