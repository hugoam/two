Module['stl'] = Module['stl'] || {};
// QualType
function QualType() {
    
    this.__ptr = _two_QualType__construct_0(); getCache(QualType)[this.__ptr] = this;
};
QualType.prototype = Object.create(WrapperObject.prototype);
QualType.prototype.constructor = QualType;
QualType.prototype.__class = QualType;
QualType.__cache = {};
Module['QualType'] = QualType;
QualType.prototype["__destroy"] = QualType.prototype.__destroy = function() {
    _two_QualType__destroy(this.__ptr);
};
// Param
function Param() { throw "cannot construct a Param, no constructor in IDL" }
Param.prototype = Object.create(WrapperObject.prototype);
Param.prototype.constructor = Param;
Param.prototype.__class = Param;
Param.__cache = {};
Module['Param'] = Param;
Param.prototype["__destroy"] = Param.prototype.__destroy = function() {
    _two_Param__destroy(this.__ptr);
};
// Signature
function Signature() { throw "cannot construct a Signature, no constructor in IDL" }
Signature.prototype = Object.create(WrapperObject.prototype);
Signature.prototype.constructor = Signature;
Signature.prototype.__class = Signature;
Signature.__cache = {};
Module['Signature'] = Signature;
Signature.prototype["__destroy"] = Signature.prototype.__destroy = function() {
    _two_Signature__destroy(this.__ptr);
};
// Callable
function Callable() { throw "cannot construct a Callable, no constructor in IDL" }
Callable.prototype = Object.create(WrapperObject.prototype);
Callable.prototype.constructor = Callable;
Callable.prototype.__class = Callable;
Callable.__cache = {};
Module['Callable'] = Callable;
Callable.prototype["__destroy"] = Callable.prototype.__destroy = function() {
    _two_Callable__destroy(this.__ptr);
};
// Function
function Function() { throw "cannot construct a Function, no constructor in IDL" }
Function.prototype = Object.create(Callable.prototype);
Function.prototype.constructor = Function;
Function.prototype.__class = Function;
Function.__base = Callable;
Function.__cache = {};
Module['Function'] = Function;
Function.prototype["__destroy"] = Function.prototype.__destroy = function() {
    _two_Function__destroy(this.__ptr);
};
// Operator
function Operator() {
    
    this.__ptr = _two_Operator__construct_0(); getCache(Operator)[this.__ptr] = this;
};
Operator.prototype = Object.create(WrapperObject.prototype);
Operator.prototype.constructor = Operator;
Operator.prototype.__class = Operator;
Operator.__cache = {};
Module['Operator'] = Operator;
Object.defineProperty(Operator.prototype, "function", {
    get: function() {
        return wrapPointer(_two_Operator__get_function(this.__ptr), Function);
    },
    set: function(value) {
        if (!checkClass(value, Function)) throw Error('Operator.function: expected Function');
        _two_Operator__set_function(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Operator.prototype, "type", {
    get: function() {
        return wrapPointer(_two_Operator__get_type(this.__ptr), Type);
    },
    set: function(value) {
        if (!checkClass(value, Type)) throw Error('Operator.type: expected Type');
        _two_Operator__set_type(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Operator.prototype, "name", {
    get: function() {
        return UTF8ToString(_two_Operator__get_name(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Operator.name: expected string');
        _two_Operator__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Operator.prototype, "sign", {
    get: function() {
        return UTF8ToString(_two_Operator__get_sign(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Operator.sign: expected string');
        _two_Operator__set_sign(this.__ptr, ensureString(value));
    }
});
Operator.prototype["__destroy"] = Operator.prototype.__destroy = function() {
    _two_Operator__destroy(this.__ptr);
};
// Method
function Method() { throw "cannot construct a Method, no constructor in IDL" }
Method.prototype = Object.create(Callable.prototype);
Method.prototype.constructor = Method;
Method.prototype.__class = Method;
Method.__base = Callable;
Method.__cache = {};
Module['Method'] = Method;
Method.prototype["__destroy"] = Method.prototype.__destroy = function() {
    _two_Method__destroy(this.__ptr);
};
// Constructor
function Constructor() { throw "cannot construct a Constructor, no constructor in IDL" }
Constructor.prototype = Object.create(Callable.prototype);
Constructor.prototype.constructor = Constructor;
Constructor.prototype.__class = Constructor;
Constructor.__base = Callable;
Constructor.__cache = {};
Module['Constructor'] = Constructor;
Constructor.prototype["__destroy"] = Constructor.prototype.__destroy = function() {
    _two_Constructor__destroy(this.__ptr);
};
// CopyConstructor
function CopyConstructor() { throw "cannot construct a CopyConstructor, no constructor in IDL" }
CopyConstructor.prototype = Object.create(Callable.prototype);
CopyConstructor.prototype.constructor = CopyConstructor;
CopyConstructor.prototype.__class = CopyConstructor;
CopyConstructor.__base = Callable;
CopyConstructor.__cache = {};
Module['CopyConstructor'] = CopyConstructor;
CopyConstructor.prototype["__destroy"] = CopyConstructor.prototype.__destroy = function() {
    _two_CopyConstructor__destroy(this.__ptr);
};
// Destructor
function Destructor() { throw "cannot construct a Destructor, no constructor in IDL" }
Destructor.prototype = Object.create(Callable.prototype);
Destructor.prototype.constructor = Destructor;
Destructor.prototype.__class = Destructor;
Destructor.__base = Callable;
Destructor.__cache = {};
Module['Destructor'] = Destructor;
Destructor.prototype["__destroy"] = Destructor.prototype.__destroy = function() {
    _two_Destructor__destroy(this.__ptr);
};
// Call
function Call() {
    
    this.__ptr = _two_Call__construct_0(); getCache(Call)[this.__ptr] = this;
};
Call.prototype = Object.create(WrapperObject.prototype);
Call.prototype.constructor = Call;
Call.prototype.__class = Call;
Call.__cache = {};
Module['Call'] = Call;
Object.defineProperty(Call.prototype, "vargs", {
    get: function() {
        return _two_Call__get_vargs(this.__ptr);
    }});
Object.defineProperty(Call.prototype, "result", {
    get: function() {
        return wrapPointer(_two_Call__get_result(this.__ptr), Var);
    }});
Call.prototype["__destroy"] = Call.prototype.__destroy = function() {
    _two_Call__destroy(this.__ptr);
};
// Meta
function Meta() { throw "cannot construct a Meta, no constructor in IDL" }
Meta.prototype = Object.create(WrapperObject.prototype);
Meta.prototype.constructor = Meta;
Meta.prototype.__class = Meta;
Meta.__cache = {};
Module['Meta'] = Meta;
Meta.prototype["__destroy"] = Meta.prototype.__destroy = function() {
    _two_Meta__destroy(this.__ptr);
};
// Convert
function Convert() { throw "cannot construct a Convert, no constructor in IDL" }
Convert.prototype = Object.create(WrapperObject.prototype);
Convert.prototype.constructor = Convert;
Convert.prototype.__class = Convert;
Convert.__cache = {};
Module['Convert'] = Convert;
Convert.prototype["__destroy"] = Convert.prototype.__destroy = function() {
    _two_Convert__destroy(this.__ptr);
};
// Static
function Static() { throw "cannot construct a Static, no constructor in IDL" }
Static.prototype = Object.create(WrapperObject.prototype);
Static.prototype.constructor = Static;
Static.prototype.__class = Static;
Static.__cache = {};
Module['Static'] = Static;
Static.prototype["__destroy"] = Static.prototype.__destroy = function() {
    _two_Static__destroy(this.__ptr);
};
// Member
function Member() { throw "cannot construct a Member, no constructor in IDL" }
Member.prototype = Object.create(WrapperObject.prototype);
Member.prototype.constructor = Member;
Member.prototype.__class = Member;
Member.__cache = {};
Module['Member'] = Member;
Member.prototype["__destroy"] = Member.prototype.__destroy = function() {
    _two_Member__destroy(this.__ptr);
};
// Class
function Class() { throw "cannot construct a Class, no constructor in IDL" }
Class.prototype = Object.create(WrapperObject.prototype);
Class.prototype.constructor = Class;
Class.prototype.__class = Class;
Class.__cache = {};
Module['Class'] = Class;
Class.prototype["__destroy"] = Class.prototype.__destroy = function() {
    _two_Class__destroy(this.__ptr);
};
// Enum
function Enum() { throw "cannot construct a Enum, no constructor in IDL" }
Enum.prototype = Object.create(WrapperObject.prototype);
Enum.prototype.constructor = Enum;
Enum.prototype.__class = Enum;
Enum.__cache = {};
Module['Enum'] = Enum;
Enum.prototype["__destroy"] = Enum.prototype.__destroy = function() {
    _two_Enum__destroy(this.__ptr);
};
// Injector
function Injector() { throw "cannot construct a Injector, no constructor in IDL" }
Injector.prototype = Object.create(Call.prototype);
Injector.prototype.constructor = Injector;
Injector.prototype.__class = Injector;
Injector.__base = Call;
Injector.__cache = {};
Module['Injector'] = Injector;
Injector.prototype["__destroy"] = Injector.prototype.__destroy = function() {
    _two_Injector__destroy(this.__ptr);
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
        return wrapPointer(_two_Creator__get_type(this.__ptr), Type);
    }});
Object.defineProperty(Creator.prototype, "construct", {
    get: function() {
        return !!(_two_Creator__get_construct(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Creator.construct: expected boolean');
        _two_Creator__set_construct(this.__ptr, value);
    }
});
Object.defineProperty(Creator.prototype, "prototype", {
    get: function() {
        return wrapPointer(_two_Creator__get_prototype(this.__ptr), Type);
    },
    set: function(value) {
        if (!checkClass(value, Type)) throw Error('Creator.prototype: expected Type');
        _two_Creator__set_prototype(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Creator.prototype, "injector", {
    get: function() {
        return wrapPointer(_two_Creator__get_injector(this.__ptr), Injector);
    }});
Creator.prototype["__destroy"] = Creator.prototype.__destroy = function() {
    _two_Creator__destroy(this.__ptr);
};
// Namespace
function Namespace() { throw "cannot construct a Namespace, no constructor in IDL" }
Namespace.prototype = Object.create(WrapperObject.prototype);
Namespace.prototype.constructor = Namespace;
Namespace.prototype.__class = Namespace;
Namespace.__cache = {};
Module['Namespace'] = Namespace;
Namespace.prototype["__destroy"] = Namespace.prototype.__destroy = function() {
    _two_Namespace__destroy(this.__ptr);
};
// Alias
function Alias() {
    
    this.__ptr = _two_Alias__construct_0(); getCache(Alias)[this.__ptr] = this;
};
Alias.prototype = Object.create(WrapperObject.prototype);
Alias.prototype.constructor = Alias;
Alias.prototype.__class = Alias;
Alias.__cache = {};
Module['Alias'] = Alias;
Alias.prototype["__destroy"] = Alias.prototype.__destroy = function() {
    _two_Alias__destroy(this.__ptr);
};
// System
function System() { throw "cannot construct a System, no constructor in IDL" }
System.prototype = Object.create(WrapperObject.prototype);
System.prototype.constructor = System;
System.prototype.__class = System;
System.__cache = {};
Module['System'] = System;
System.prototype["__destroy"] = System.prototype.__destroy = function() {
    _two_System__destroy(this.__ptr);
};
Module['system'] = function() {
    
    return wrapPointer(_two_system_0(), System);
};

(function() {
    function setup() {
        QualType.prototype.__type = _two_QualType__type();
        Param.prototype.__type = _two_Param__type();
        Signature.prototype.__type = _two_Signature__type();
        Callable.prototype.__type = _two_Callable__type();
        Function.prototype.__type = _two_Function__type();
        Operator.prototype.__type = _two_Operator__type();
        Method.prototype.__type = _two_Method__type();
        Constructor.prototype.__type = _two_Constructor__type();
        CopyConstructor.prototype.__type = _two_CopyConstructor__type();
        Destructor.prototype.__type = _two_Destructor__type();
        Call.prototype.__type = _two_Call__type();
        Meta.prototype.__type = _two_Meta__type();
        Convert.prototype.__type = _two_Convert__type();
        Static.prototype.__type = _two_Static__type();
        Member.prototype.__type = _two_Member__type();
        Class.prototype.__type = _two_Class__type();
        Enum.prototype.__type = _two_Enum__type();
        Injector.prototype.__type = _two_Injector__type();
        Creator.prototype.__type = _two_Creator__type();
        Namespace.prototype.__type = _two_Namespace__type();
        Alias.prototype.__type = _two_Alias__type();
        System.prototype.__type = _two_System__type();
        // TypeClass
        Module['TypeClass'] = Module['TypeClass'] || {};
        Module['TypeClass']['None'] = _two_TypeClass_None();
        Module['TypeClass']['Object'] = _two_TypeClass_Object();
        Module['TypeClass']['Struct'] = _two_TypeClass_Struct();
        Module['TypeClass']['Sequence'] = _two_TypeClass_Sequence();
        Module['TypeClass']['BaseType'] = _two_TypeClass_BaseType();
        Module['TypeClass']['Enum'] = _two_TypeClass_Enum();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
