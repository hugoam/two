// Interpreter
function Interpreter() { throw "cannot construct a Interpreter, no constructor in IDL" }
Interpreter.prototype = Object.create(WrapperObject.prototype);
Interpreter.prototype.constructor = Interpreter;
Interpreter.prototype.__class__ = Interpreter;
Interpreter.__cache__ = {};
Module['Interpreter'] = Interpreter;
Interpreter.prototype["__destroy__"] = Interpreter.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Interpreter__destroy(self);
};
// Pipe
function Pipe() { throw "cannot construct a Pipe, no constructor in IDL" }
Pipe.prototype = Object.create(WrapperObject.prototype);
Pipe.prototype.constructor = Pipe;
Pipe.prototype.__class__ = Pipe;
Pipe.__cache__ = {};
Module['Pipe'] = Pipe;
Pipe.prototype["__destroy__"] = Pipe.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Pipe__destroy(self);
};
// Process
function Process() { throw "cannot construct a Process, no constructor in IDL" }
Process.prototype = Object.create(WrapperObject.prototype);
Process.prototype.constructor = Process;
Process.prototype.__class__ = Process;
Process.__cache__ = {};
Module['Process'] = Process;
Object.defineProperty(Process.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Process__get_type(self), Type);
    }});
Process.prototype["__destroy__"] = Process.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Process__destroy(self);
};
// Script
function Script() { throw "cannot construct a Script, no constructor in IDL" }
Script.prototype = Object.create(WrapperObject.prototype);
Script.prototype.constructor = Script;
Script.prototype.__class__ = Script;
Script.__cache__ = {};
Module['Script'] = Script;
Object.defineProperty(Script.prototype, "index", {
    get: function() {
        var self = this.ptr;
        return _mud_Script__get_index(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Script__set_index(self, value);
    }
});
Object.defineProperty(Script.prototype, "type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Script__get_type(self), Type);
    }});
Object.defineProperty(Script.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Script__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Script__set_name(self, ensureString(value));
    }
});
Object.defineProperty(Script.prototype, "locked", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Script__get_locked(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Script__set_locked(self, value);
    }
});
Script.prototype["__destroy__"] = Script.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Script__destroy(self);
};
// ScriptClass
function ScriptClass(a0, a1) {
    ensureCache.prepare();
    this.ptr = _mud_ScriptClass__construct_2(ensureString(/*name*/a0), /*parts*/a1.ptr); this.type = ScriptClass; getCache(ScriptClass)[this.ptr] = this;
};
ScriptClass.prototype = Object.create(WrapperObject.prototype);
ScriptClass.prototype.constructor = ScriptClass;
ScriptClass.prototype.__class__ = ScriptClass;
ScriptClass.__cache__ = {};
Module['ScriptClass'] = ScriptClass;
Object.defineProperty(ScriptClass.prototype, "name", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_ScriptClass__get_name(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ScriptClass__set_name(self, ensureString(value));
    }
});
Object.defineProperty(ScriptClass.prototype, "class_type", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ScriptClass__get_class_type(self), Type);
    }});
Object.defineProperty(ScriptClass.prototype, "class", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ScriptClass__get_class(self), Class);
    }});
Object.defineProperty(ScriptClass.prototype, "prototype", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ScriptClass__get_prototype(self), Prototype);
    }});
ScriptClass.prototype["__destroy__"] = ScriptClass.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ScriptClass__destroy(self);
};
// ScriptError
function ScriptError() {
    this.ptr = _mud_ScriptError__construct_0(); this.type = ScriptError; getCache(ScriptError)[this.ptr] = this;
};
ScriptError.prototype = Object.create(WrapperObject.prototype);
ScriptError.prototype.constructor = ScriptError;
ScriptError.prototype.__class__ = ScriptError;
ScriptError.__cache__ = {};
Module['ScriptError'] = ScriptError;
ScriptError.prototype["__destroy__"] = ScriptError.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ScriptError__destroy(self);
};
// StreamBranch
function StreamBranch() { throw "cannot construct a StreamBranch, no constructor in IDL" }
StreamBranch.prototype = Object.create(WrapperObject.prototype);
StreamBranch.prototype.constructor = StreamBranch;
StreamBranch.prototype.__class__ = StreamBranch;
StreamBranch.__cache__ = {};
Module['StreamBranch'] = StreamBranch;
StreamBranch.prototype["__destroy__"] = StreamBranch.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_StreamBranch__destroy(self);
};
// Valve
function Valve() { throw "cannot construct a Valve, no constructor in IDL" }
Valve.prototype = Object.create(WrapperObject.prototype);
Valve.prototype.constructor = Valve;
Valve.prototype.__class__ = Valve;
Valve.__cache__ = {};
Module['Valve'] = Valve;
Valve.prototype["__destroy__"] = Valve.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Valve__destroy(self);
};
// LuaInterpreter
function LuaInterpreter() { throw "cannot construct a LuaInterpreter, no constructor in IDL" }
LuaInterpreter.prototype = Object.create(Interpreter.prototype);
LuaInterpreter.prototype.constructor = LuaInterpreter;
LuaInterpreter.prototype.__class__ = LuaInterpreter;
LuaInterpreter.__cache__ = {};
Module['LuaInterpreter'] = LuaInterpreter;
LuaInterpreter.prototype["__destroy__"] = LuaInterpreter.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_LuaInterpreter__destroy(self);
};
// ProcessCallable
function ProcessCallable(a0, a1) {
    this.ptr = _mud_ProcessCallable__construct_2(/*script*/a0.ptr, /*callable*/a1.ptr); this.type = ProcessCallable; getCache(ProcessCallable)[this.ptr] = this;
};
ProcessCallable.prototype = Object.create(Process.prototype);
ProcessCallable.prototype.constructor = ProcessCallable;
ProcessCallable.prototype.__class__ = ProcessCallable;
ProcessCallable.__cache__ = {};
Module['ProcessCallable'] = ProcessCallable;
ProcessCallable.prototype["__destroy__"] = ProcessCallable.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ProcessCallable__destroy(self);
};
// ProcessCreate
function ProcessCreate(a0, a1, a2) {
    this.ptr = _mud_ProcessCreate__construct_3(/*script*/a0.ptr, /*type*/a1.ptr, /*constructor*/a2.ptr); this.type = ProcessCreate; getCache(ProcessCreate)[this.ptr] = this;
};
ProcessCreate.prototype = Object.create(Process.prototype);
ProcessCreate.prototype.constructor = ProcessCreate;
ProcessCreate.prototype.__class__ = ProcessCreate;
ProcessCreate.__cache__ = {};
Module['ProcessCreate'] = ProcessCreate;
ProcessCreate.prototype["__destroy__"] = ProcessCreate.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ProcessCreate__destroy(self);
};
// ProcessDisplay
function ProcessDisplay() { throw "cannot construct a ProcessDisplay, no constructor in IDL" }
ProcessDisplay.prototype = Object.create(Process.prototype);
ProcessDisplay.prototype.constructor = ProcessDisplay;
ProcessDisplay.prototype.__class__ = ProcessDisplay;
ProcessDisplay.__cache__ = {};
Module['ProcessDisplay'] = ProcessDisplay;
ProcessDisplay.prototype["__destroy__"] = ProcessDisplay.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ProcessDisplay__destroy(self);
};
// ProcessFunction
function ProcessFunction(a0, a1) {
    this.ptr = _mud_ProcessFunction__construct_2(/*script*/a0.ptr, /*function*/a1.ptr); this.type = ProcessFunction; getCache(ProcessFunction)[this.ptr] = this;
};
ProcessFunction.prototype = Object.create(ProcessCallable.prototype);
ProcessFunction.prototype.constructor = ProcessFunction;
ProcessFunction.prototype.__class__ = ProcessFunction;
ProcessFunction.__cache__ = {};
Module['ProcessFunction'] = ProcessFunction;
ProcessFunction.prototype["__destroy__"] = ProcessFunction.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ProcessFunction__destroy(self);
};
// ProcessGetMember
function ProcessGetMember(a0, a1) {
    this.ptr = _mud_ProcessGetMember__construct_2(/*script*/a0.ptr, /*member*/a1.ptr); this.type = ProcessGetMember; getCache(ProcessGetMember)[this.ptr] = this;
};
ProcessGetMember.prototype = Object.create(Process.prototype);
ProcessGetMember.prototype.constructor = ProcessGetMember;
ProcessGetMember.prototype.__class__ = ProcessGetMember;
ProcessGetMember.__cache__ = {};
Module['ProcessGetMember'] = ProcessGetMember;
ProcessGetMember.prototype["__destroy__"] = ProcessGetMember.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ProcessGetMember__destroy(self);
};
// ProcessInput
function ProcessInput() { throw "cannot construct a ProcessInput, no constructor in IDL" }
ProcessInput.prototype = Object.create(Process.prototype);
ProcessInput.prototype.constructor = ProcessInput;
ProcessInput.prototype.__class__ = ProcessInput;
ProcessInput.__cache__ = {};
Module['ProcessInput'] = ProcessInput;
ProcessInput.prototype["__destroy__"] = ProcessInput.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ProcessInput__destroy(self);
};
// ProcessMethod
function ProcessMethod(a0, a1) {
    this.ptr = _mud_ProcessMethod__construct_2(/*script*/a0.ptr, /*method*/a1.ptr); this.type = ProcessMethod; getCache(ProcessMethod)[this.ptr] = this;
};
ProcessMethod.prototype = Object.create(ProcessCallable.prototype);
ProcessMethod.prototype.constructor = ProcessMethod;
ProcessMethod.prototype.__class__ = ProcessMethod;
ProcessMethod.__cache__ = {};
Module['ProcessMethod'] = ProcessMethod;
ProcessMethod.prototype["__destroy__"] = ProcessMethod.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ProcessMethod__destroy(self);
};
// ProcessOutput
function ProcessOutput() { throw "cannot construct a ProcessOutput, no constructor in IDL" }
ProcessOutput.prototype = Object.create(Process.prototype);
ProcessOutput.prototype.constructor = ProcessOutput;
ProcessOutput.prototype.__class__ = ProcessOutput;
ProcessOutput.__cache__ = {};
Module['ProcessOutput'] = ProcessOutput;
ProcessOutput.prototype["__destroy__"] = ProcessOutput.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ProcessOutput__destroy(self);
};
// ProcessScript
function ProcessScript(a0, a1) {
    this.ptr = _mud_ProcessScript__construct_2(/*script*/a0.ptr, /*target*/a1.ptr); this.type = ProcessScript; getCache(ProcessScript)[this.ptr] = this;
};
ProcessScript.prototype = Object.create(ProcessCallable.prototype);
ProcessScript.prototype.constructor = ProcessScript;
ProcessScript.prototype.__class__ = ProcessScript;
ProcessScript.__cache__ = {};
Module['ProcessScript'] = ProcessScript;
ProcessScript.prototype["__destroy__"] = ProcessScript.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ProcessScript__destroy(self);
};
// ProcessSetMember
function ProcessSetMember(a0, a1) {
    this.ptr = _mud_ProcessSetMember__construct_2(/*script*/a0.ptr, /*member*/a1.ptr); this.type = ProcessSetMember; getCache(ProcessSetMember)[this.ptr] = this;
};
ProcessSetMember.prototype = Object.create(Process.prototype);
ProcessSetMember.prototype.constructor = ProcessSetMember;
ProcessSetMember.prototype.__class__ = ProcessSetMember;
ProcessSetMember.__cache__ = {};
Module['ProcessSetMember'] = ProcessSetMember;
ProcessSetMember.prototype["__destroy__"] = ProcessSetMember.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ProcessSetMember__destroy(self);
};
// ProcessValue
function ProcessValue(a0, a1) {
    this.ptr = _mud_ProcessValue__construct_2(/*script*/a0.ptr, /*value*/a1.ptr); this.type = ProcessValue; getCache(ProcessValue)[this.ptr] = this;
};
ProcessValue.prototype = Object.create(Process.prototype);
ProcessValue.prototype.constructor = ProcessValue;
ProcessValue.prototype.__class__ = ProcessValue;
ProcessValue.__cache__ = {};
Module['ProcessValue'] = ProcessValue;
ProcessValue.prototype["__destroy__"] = ProcessValue.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ProcessValue__destroy(self);
};
// Stream
function Stream() { throw "cannot construct a Stream, no constructor in IDL" }
Stream.prototype = Object.create(StreamBranch.prototype);
Stream.prototype.constructor = Stream;
Stream.prototype.__class__ = Stream;
Stream.__cache__ = {};
Module['Stream'] = Stream;
Stream.prototype["__destroy__"] = Stream.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Stream__destroy(self);
};
// TextScript
function TextScript(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { this.ptr = _mud_TextScript__construct_2(ensureString(/*name*/a0), /*language*/a1); this.type = TextScript; getCache(TextScript)[this.ptr] = this; return; }
    this.ptr = _mud_TextScript__construct_3(ensureString(/*name*/a0), /*language*/a1, /*signature*/a2.ptr); this.type = TextScript; getCache(TextScript)[this.ptr] = this;
};
TextScript.prototype = Object.create(Script.prototype);
TextScript.prototype.constructor = TextScript;
TextScript.prototype.__class__ = TextScript;
TextScript.__cache__ = {};
Module['TextScript'] = TextScript;
Object.defineProperty(TextScript.prototype, "language", {
    get: function() {
        var self = this.ptr;
        return _mud_TextScript__get_language(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_TextScript__set_language(self, value);
    }
});
Object.defineProperty(TextScript.prototype, "script", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_TextScript__get_script(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_TextScript__set_script(self, ensureString(value));
    }
});
Object.defineProperty(TextScript.prototype, "dirty", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_TextScript__get_dirty(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_TextScript__set_dirty(self, value);
    }
});
TextScript.prototype["__destroy__"] = TextScript.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_TextScript__destroy(self);
};
// VisualScript
function VisualScript(a0, a1) {
    ensureCache.prepare();
    if (a1 === undefined) { this.ptr = _mud_VisualScript__construct_1(ensureString(/*name*/a0)); this.type = VisualScript; getCache(VisualScript)[this.ptr] = this; return; }
    this.ptr = _mud_VisualScript__construct_2(ensureString(/*name*/a0), /*signature*/a1.ptr); this.type = VisualScript; getCache(VisualScript)[this.ptr] = this;
};
VisualScript.prototype = Object.create(Script.prototype);
VisualScript.prototype.constructor = VisualScript;
VisualScript.prototype.__class__ = VisualScript;
VisualScript.__cache__ = {};
Module['VisualScript'] = VisualScript;
VisualScript.prototype["__destroy__"] = VisualScript.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_VisualScript__destroy(self);
};
// WrenInterpreter
function WrenInterpreter() { throw "cannot construct a WrenInterpreter, no constructor in IDL" }
WrenInterpreter.prototype = Object.create(Interpreter.prototype);
WrenInterpreter.prototype.constructor = WrenInterpreter;
WrenInterpreter.prototype.__class__ = WrenInterpreter;
WrenInterpreter.__cache__ = {};
Module['WrenInterpreter'] = WrenInterpreter;
WrenInterpreter.prototype["__destroy__"] = WrenInterpreter.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_WrenInterpreter__destroy(self);
};

(function() {
    function setup() {
        Interpreter.__type__ = _mud_Interpreter__type();
        Pipe.__type__ = _mud_Pipe__type();
        Process.__type__ = _mud_Process__type();
        Script.__type__ = _mud_Script__type();
        ScriptClass.__type__ = _mud_ScriptClass__type();
        ScriptError.__type__ = _mud_ScriptError__type();
        StreamBranch.__type__ = _mud_StreamBranch__type();
        Valve.__type__ = _mud_Valve__type();
        LuaInterpreter.__type__ = _mud_LuaInterpreter__type();
        ProcessCallable.__type__ = _mud_ProcessCallable__type();
        ProcessCreate.__type__ = _mud_ProcessCreate__type();
        ProcessDisplay.__type__ = _mud_ProcessDisplay__type();
        ProcessFunction.__type__ = _mud_ProcessFunction__type();
        ProcessGetMember.__type__ = _mud_ProcessGetMember__type();
        ProcessInput.__type__ = _mud_ProcessInput__type();
        ProcessMethod.__type__ = _mud_ProcessMethod__type();
        ProcessOutput.__type__ = _mud_ProcessOutput__type();
        ProcessScript.__type__ = _mud_ProcessScript__type();
        ProcessSetMember.__type__ = _mud_ProcessSetMember__type();
        ProcessValue.__type__ = _mud_ProcessValue__type();
        Stream.__type__ = _mud_Stream__type();
        TextScript.__type__ = _mud_TextScript__type();
        VisualScript.__type__ = _mud_VisualScript__type();
        WrenInterpreter.__type__ = _mud_WrenInterpreter__type();
        // Language
        Module['Language'] = Module['Language'] || {};
        Module['Language']['Cpp'] = _mud_Language_Cpp();
        Module['Language']['Lua'] = _mud_Language_Lua();
        Module['Language']['Wren'] = _mud_Language_Wren();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
