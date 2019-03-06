Module['stl'] = Module['stl'] || {};
// Alias
function Alias() {
    this.__ptr = _mud_Alias__construct_0(); this.__type = Alias.__type; getCache(Alias)[this.__ptr] = this;
};
Alias.prototype = Object.create(WrapperObject.prototype);
Alias.prototype.constructor = Alias;
Alias.prototype.__class = Alias;
Alias.__cache = {};
Module['Alias'] = Alias;
Alias.prototype["__destroy"] = Alias.prototype.__destroy = function() {
    _mud_Alias__destroy(this.__ptr);
};
// Call
function Call() {
    this.__ptr = _mud_Call__construct_0(); this.__type = Call.__type; getCache(Call)[this.__ptr] = this;
};
Call.prototype = Object.create(WrapperObject.prototype);
Call.prototype.constructor = Call;
Call.prototype.__class = Call;
Call.__cache = {};
Module['Call'] = Call;
Object.defineProperty(Call.prototype, "vargs", {
    get: function() {
        return _mud_Call__get_vargs(this.__ptr);
    }});
Object.defineProperty(Call.prototype, "result", {
    get: function() {
        return wrapPointer(_mud_Call__get_result(this.__ptr), Var);
    }});
Call.prototype["__destroy"] = Call.prototype.__destroy = function() {
    _mud_Call__destroy(this.__ptr);
};
// Callable
function Callable() { throw "cannot construct a Callable, no constructor in IDL" }
Callable.prototype = Object.create(WrapperObject.prototype);
Callable.prototype.constructor = Callable;
Callable.prototype.__class = Callable;
Callable.__cache = {};
Module['Callable'] = Callable;
Callable.prototype["__destroy"] = Callable.prototype.__destroy = function() {
    _mud_Callable__destroy(this.__ptr);
};
// Class
function Class() { throw "cannot construct a Class, no constructor in IDL" }
Class.prototype = Object.create(WrapperObject.prototype);
Class.prototype.constructor = Class;
Class.prototype.__class = Class;
Class.__cache = {};
Module['Class'] = Class;
Class.prototype["__destroy"] = Class.prototype.__destroy = function() {
    _mud_Class__destroy(this.__ptr);
};
// Convert
function Convert() { throw "cannot construct a Convert, no constructor in IDL" }
Convert.prototype = Object.create(WrapperObject.prototype);
Convert.prototype.constructor = Convert;
Convert.prototype.__class = Convert;
Convert.__cache = {};
Module['Convert'] = Convert;
Convert.prototype["__destroy"] = Convert.prototype.__destroy = function() {
    _mud_Convert__destroy(this.__ptr);
};
// Creator
function Creator() { throw "cannot construct a Creator, no constructor in IDL" }
Creator.prototype = Object.create(WrapperObject.prototype);
Creator.prototype.constructor = Creator;
Creator.prototype.__class = Creator;
Creator.__cache = {};
Module['Creator'] = Creator;
Object.defineProperty(Creator.prototype, "type", {
    get: function() {
        return wrapPointer(_mud_Creator__get_type(this.__ptr), Type);
    }});
Object.defineProperty(Creator.prototype, "construct", {
    get: function() {
        return !!(_mud_Creator__get_construct(this.__ptr));
    },
    set: function(value) {
        _mud_Creator__set_construct(this.__ptr, value);
    }
});
Object.defineProperty(Creator.prototype, "prototype", {
    get: function() {
        return wrapPointer(_mud_Creator__get_prototype(this.__ptr), Type);
    },
    set: function(value) {
        _mud_Creator__set_prototype(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Creator.prototype, "injector", {
    get: function() {
        return wrapPointer(_mud_Creator__get_injector(this.__ptr), Injector);
    }});
Creator.prototype["__destroy"] = Creator.prototype.__destroy = function() {
    _mud_Creator__destroy(this.__ptr);
};
// Enum
function Enum() { throw "cannot construct a Enum, no constructor in IDL" }
Enum.prototype = Object.create(WrapperObject.prototype);
Enum.prototype.constructor = Enum;
Enum.prototype.__class = Enum;
Enum.__cache = {};
Module['Enum'] = Enum;
Enum.prototype["__destroy"] = Enum.prototype.__destroy = function() {
    _mud_Enum__destroy(this.__ptr);
};
// Member
function Member() { throw "cannot construct a Member, no constructor in IDL" }
Member.prototype = Object.create(WrapperObject.prototype);
Member.prototype.constructor = Member;
Member.prototype.__class = Member;
Member.__cache = {};
Module['Member'] = Member;
Member.prototype["__destroy"] = Member.prototype.__destroy = function() {
    _mud_Member__destroy(this.__ptr);
};
// Meta
function Meta() { throw "cannot construct a Meta, no constructor in IDL" }
Meta.prototype = Object.create(WrapperObject.prototype);
Meta.prototype.constructor = Meta;
Meta.prototype.__class = Meta;
Meta.__cache = {};
Module['Meta'] = Meta;
Meta.prototype["__destroy"] = Meta.prototype.__destroy = function() {
    _mud_Meta__destroy(this.__ptr);
};
// Module
function Module() { throw "cannot construct a Module, no constructor in IDL" }
Module.prototype = Object.create(WrapperObject.prototype);
Module.prototype.constructor = Module;
Module.prototype.__class = Module;
Module.__cache = {};
Module['Module'] = Module;
Object.defineProperty(Module.prototype, "name", {
    get: function() {
        return Pointer_stringify(_mud_Module__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Module__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Module.prototype, "path", {
    get: function() {
        return Pointer_stringify(_mud_Module__get_path(this.__ptr));
    },
    set: function(value) {
        _mud_Module__set_path(this.__ptr, ensureString(value));
    }
});
Module.prototype["__destroy"] = Module.prototype.__destroy = function() {
    _mud_Module__destroy(this.__ptr);
};
// Namespace
function Namespace() { throw "cannot construct a Namespace, no constructor in IDL" }
Namespace.prototype = Object.create(WrapperObject.prototype);
Namespace.prototype.constructor = Namespace;
Namespace.prototype.__class = Namespace;
Namespace.__cache = {};
Module['Namespace'] = Namespace;
Namespace.prototype["__destroy"] = Namespace.prototype.__destroy = function() {
    _mud_Namespace__destroy(this.__ptr);
};
// Operator
function Operator() {
    this.__ptr = _mud_Operator__construct_0(); this.__type = Operator.__type; getCache(Operator)[this.__ptr] = this;
};
Operator.prototype = Object.create(WrapperObject.prototype);
Operator.prototype.constructor = Operator;
Operator.prototype.__class = Operator;
Operator.__cache = {};
Module['Operator'] = Operator;
Object.defineProperty(Operator.prototype, "function", {
    get: function() {
        return wrapPointer(_mud_Operator__get_function(this.__ptr), Function);
    },
    set: function(value) {
        _mud_Operator__set_function(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Operator.prototype, "type", {
    get: function() {
        return wrapPointer(_mud_Operator__get_type(this.__ptr), Type);
    },
    set: function(value) {
        _mud_Operator__set_type(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Operator.prototype, "name", {
    get: function() {
        return Pointer_stringify(_mud_Operator__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Operator__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Operator.prototype, "sign", {
    get: function() {
        return Pointer_stringify(_mud_Operator__get_sign(this.__ptr));
    },
    set: function(value) {
        _mud_Operator__set_sign(this.__ptr, ensureString(value));
    }
});
Operator.prototype["__destroy"] = Operator.prototype.__destroy = function() {
    _mud_Operator__destroy(this.__ptr);
};
// Param
function Param() { throw "cannot construct a Param, no constructor in IDL" }
Param.prototype = Object.create(WrapperObject.prototype);
Param.prototype.constructor = Param;
Param.prototype.__class = Param;
Param.__cache = {};
Module['Param'] = Param;
Param.prototype["__destroy"] = Param.prototype.__destroy = function() {
    _mud_Param__destroy(this.__ptr);
};
// QualType
function QualType() {
    this.__ptr = _mud_QualType__construct_0(); this.__type = QualType.__type; getCache(QualType)[this.__ptr] = this;
};
QualType.prototype = Object.create(WrapperObject.prototype);
QualType.prototype.constructor = QualType;
QualType.prototype.__class = QualType;
QualType.__cache = {};
Module['QualType'] = QualType;
QualType.prototype["__destroy"] = QualType.prototype.__destroy = function() {
    _mud_QualType__destroy(this.__ptr);
};
// Signature
function Signature() { throw "cannot construct a Signature, no constructor in IDL" }
Signature.prototype = Object.create(WrapperObject.prototype);
Signature.prototype.constructor = Signature;
Signature.prototype.__class = Signature;
Signature.__cache = {};
Module['Signature'] = Signature;
Signature.prototype["__destroy"] = Signature.prototype.__destroy = function() {
    _mud_Signature__destroy(this.__ptr);
};
// Static
function Static() { throw "cannot construct a Static, no constructor in IDL" }
Static.prototype = Object.create(WrapperObject.prototype);
Static.prototype.constructor = Static;
Static.prototype.__class = Static;
Static.__cache = {};
Module['Static'] = Static;
Static.prototype["__destroy"] = Static.prototype.__destroy = function() {
    _mud_Static__destroy(this.__ptr);
};
// System
function System() { throw "cannot construct a System, no constructor in IDL" }
System.prototype = Object.create(WrapperObject.prototype);
System.prototype.constructor = System;
System.prototype.__class = System;
System.__cache = {};
Module['System'] = System;
System.prototype["__destroy"] = System.prototype.__destroy = function() {
    _mud_System__destroy(this.__ptr);
};
// Constructor
function Constructor() { throw "cannot construct a Constructor, no constructor in IDL" }
Constructor.prototype = Object.create(Callable.prototype);
Constructor.prototype.constructor = Constructor;
Constructor.prototype.__class = Constructor;
Constructor.__cache = {};
Module['Constructor'] = Constructor;
Constructor.prototype["__destroy"] = Constructor.prototype.__destroy = function() {
    _mud_Constructor__destroy(this.__ptr);
};
// CopyConstructor
function CopyConstructor() { throw "cannot construct a CopyConstructor, no constructor in IDL" }
CopyConstructor.prototype = Object.create(Callable.prototype);
CopyConstructor.prototype.constructor = CopyConstructor;
CopyConstructor.prototype.__class = CopyConstructor;
CopyConstructor.__cache = {};
Module['CopyConstructor'] = CopyConstructor;
CopyConstructor.prototype["__destroy"] = CopyConstructor.prototype.__destroy = function() {
    _mud_CopyConstructor__destroy(this.__ptr);
};
// Destructor
function Destructor() { throw "cannot construct a Destructor, no constructor in IDL" }
Destructor.prototype = Object.create(Callable.prototype);
Destructor.prototype.constructor = Destructor;
Destructor.prototype.__class = Destructor;
Destructor.__cache = {};
Module['Destructor'] = Destructor;
Destructor.prototype["__destroy"] = Destructor.prototype.__destroy = function() {
    _mud_Destructor__destroy(this.__ptr);
};
// Function
function Function() { throw "cannot construct a Function, no constructor in IDL" }
Function.prototype = Object.create(Callable.prototype);
Function.prototype.constructor = Function;
Function.prototype.__class = Function;
Function.__cache = {};
Module['Function'] = Function;
Function.prototype["__destroy"] = Function.prototype.__destroy = function() {
    _mud_Function__destroy(this.__ptr);
};
// Injector
function Injector() { throw "cannot construct a Injector, no constructor in IDL" }
Injector.prototype = Object.create(Call.prototype);
Injector.prototype.constructor = Injector;
Injector.prototype.__class = Injector;
Injector.__cache = {};
Module['Injector'] = Injector;
Injector.prototype["__destroy"] = Injector.prototype.__destroy = function() {
    _mud_Injector__destroy(this.__ptr);
};
// Method
function Method() { throw "cannot construct a Method, no constructor in IDL" }
Method.prototype = Object.create(Callable.prototype);
Method.prototype.constructor = Method;
Method.prototype.__class = Method;
Method.__cache = {};
Module['Method'] = Method;
Method.prototype["__destroy"] = Method.prototype.__destroy = function() {
    _mud_Method__destroy(this.__ptr);
};
Module['system'] = function() {
    return wrapPointer(_mud_system_0(), System);
};

(function() {
    function setup() {
        Alias.__type = _mud_Alias__type();
        Call.__type = _mud_Call__type();
        Callable.__type = _mud_Callable__type();
        Class.__type = _mud_Class__type();
        Convert.__type = _mud_Convert__type();
        Creator.__type = _mud_Creator__type();
        Enum.__type = _mud_Enum__type();
        Member.__type = _mud_Member__type();
        Meta.__type = _mud_Meta__type();
        Module.__type = _mud_Module__type();
        Namespace.__type = _mud_Namespace__type();
        Operator.__type = _mud_Operator__type();
        Param.__type = _mud_Param__type();
        QualType.__type = _mud_QualType__type();
        Signature.__type = _mud_Signature__type();
        Static.__type = _mud_Static__type();
        System.__type = _mud_System__type();
        Constructor.__type = _mud_Constructor__type();
        CopyConstructor.__type = _mud_CopyConstructor__type();
        Destructor.__type = _mud_Destructor__type();
        Function.__type = _mud_Function__type();
        Injector.__type = _mud_Injector__type();
        Method.__type = _mud_Method__type();
        // TypeClass
        Module['TypeClass'] = Module['TypeClass'] || {};
        Module['TypeClass']['None'] = _mud_TypeClass_None();
        Module['TypeClass']['Object'] = _mud_TypeClass_Object();
        Module['TypeClass']['Struct'] = _mud_TypeClass_Struct();
        Module['TypeClass']['Sequence'] = _mud_TypeClass_Sequence();
        Module['TypeClass']['BaseType'] = _mud_TypeClass_BaseType();
        Module['TypeClass']['Enum'] = _mud_TypeClass_Enum();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
