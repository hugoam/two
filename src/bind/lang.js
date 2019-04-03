// Interpreter
function Interpreter() { throw "cannot construct a Interpreter, no constructor in IDL" }
Interpreter.prototype = Object.create(WrapperObject.prototype);
Interpreter.prototype.constructor = Interpreter;
Interpreter.prototype.__class = Interpreter;
Interpreter.__cache = {};
Module['Interpreter'] = Interpreter;
Interpreter.prototype["__destroy"] = Interpreter.prototype.__destroy = function() {
    _mud_Interpreter__destroy(this.__ptr);
};
// Pipe
function Pipe() { throw "cannot construct a Pipe, no constructor in IDL" }
Pipe.prototype = Object.create(WrapperObject.prototype);
Pipe.prototype.constructor = Pipe;
Pipe.prototype.__class = Pipe;
Pipe.__cache = {};
Module['Pipe'] = Pipe;
Pipe.prototype["__destroy"] = Pipe.prototype.__destroy = function() {
    _mud_Pipe__destroy(this.__ptr);
};
// Process
function Process() { throw "cannot construct a Process, no constructor in IDL" }
Process.prototype = Object.create(WrapperObject.prototype);
Process.prototype.constructor = Process;
Process.prototype.__class = Process;
Process.__cache = {};
Module['Process'] = Process;
Object.defineProperty(Process.prototype, "type", {
    get: function() {
        return wrapPointer(_mud_Process__get_type(this.__ptr), Type);
    }});
Process.prototype["__destroy"] = Process.prototype.__destroy = function() {
    _mud_Process__destroy(this.__ptr);
};
// ScriptClass
ScriptClass.prototype = Object.create(WrapperObject.prototype);
ScriptClass.prototype.constructor = ScriptClass;
ScriptClass.prototype.__class = ScriptClass;
ScriptClass.__cache = {};
Module['ScriptClass'] = ScriptClass;
Object.defineProperty(ScriptClass.prototype, "name", {
    get: function() {
        return UTF8ToString(_mud_ScriptClass__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_ScriptClass__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(ScriptClass.prototype, "class_type", {
    get: function() {
        return wrapPointer(_mud_ScriptClass__get_class_type(this.__ptr), Type);
    }});
Object.defineProperty(ScriptClass.prototype, "class", {
    get: function() {
        return wrapPointer(_mud_ScriptClass__get_class(this.__ptr), Class);
    }});
Object.defineProperty(ScriptClass.prototype, "prototype", {
    get: function() {
        return wrapPointer(_mud_ScriptClass__get_prototype(this.__ptr), Prototype);
    }});
ScriptClass.prototype["__destroy"] = ScriptClass.prototype.__destroy = function() {
    _mud_ScriptClass__destroy(this.__ptr);
};
// ScriptError
function ScriptError() {
    this.__ptr = _mud_ScriptError__construct_0(); this.__type = ScriptError.__type; getCache(ScriptError)[this.__ptr] = this;
};
ScriptError.prototype = Object.create(WrapperObject.prototype);
ScriptError.prototype.constructor = ScriptError;
ScriptError.prototype.__class = ScriptError;
ScriptError.__cache = {};
Module['ScriptError'] = ScriptError;
ScriptError.prototype["__destroy"] = ScriptError.prototype.__destroy = function() {
    _mud_ScriptError__destroy(this.__ptr);
};
// StreamBranch
function StreamBranch() { throw "cannot construct a StreamBranch, no constructor in IDL" }
StreamBranch.prototype = Object.create(WrapperObject.prototype);
StreamBranch.prototype.constructor = StreamBranch;
StreamBranch.prototype.__class = StreamBranch;
StreamBranch.__cache = {};
Module['StreamBranch'] = StreamBranch;
StreamBranch.prototype["__destroy"] = StreamBranch.prototype.__destroy = function() {
    _mud_StreamBranch__destroy(this.__ptr);
};
// Valve
function Valve() { throw "cannot construct a Valve, no constructor in IDL" }
Valve.prototype = Object.create(WrapperObject.prototype);
Valve.prototype.constructor = Valve;
Valve.prototype.__class = Valve;
Valve.__cache = {};
Module['Valve'] = Valve;
Valve.prototype["__destroy"] = Valve.prototype.__destroy = function() {
    _mud_Valve__destroy(this.__ptr);
};
// LuaInterpreter
function LuaInterpreter() { throw "cannot construct a LuaInterpreter, no constructor in IDL" }
LuaInterpreter.prototype = Object.create(Interpreter.prototype);
LuaInterpreter.prototype.constructor = LuaInterpreter;
LuaInterpreter.prototype.__class = LuaInterpreter;
LuaInterpreter.__cache = {};
Module['LuaInterpreter'] = LuaInterpreter;
LuaInterpreter.prototype["__destroy"] = LuaInterpreter.prototype.__destroy = function() {
    _mud_LuaInterpreter__destroy(this.__ptr);
};
// ProcessCallable
function ProcessCallable(a0, a1) {
    this.__ptr = _mud_ProcessCallable__construct_2(/*script*/a0.__ptr, /*callable*/a1.__ptr); this.__type = ProcessCallable.__type; getCache(ProcessCallable)[this.__ptr] = this;
};
ProcessCallable.prototype = Object.create(Process.prototype);
ProcessCallable.prototype.constructor = ProcessCallable;
ProcessCallable.prototype.__class = ProcessCallable;
ProcessCallable.__cache = {};
Module['ProcessCallable'] = ProcessCallable;
ProcessCallable.prototype["__destroy"] = ProcessCallable.prototype.__destroy = function() {
    _mud_ProcessCallable__destroy(this.__ptr);
};
// ProcessCreate
function ProcessCreate(a0, a1, a2) {
    this.__ptr = _mud_ProcessCreate__construct_3(/*script*/a0.__ptr, /*type*/a1.__ptr, /*constructor*/a2.__ptr); this.__type = ProcessCreate.__type; getCache(ProcessCreate)[this.__ptr] = this;
};
ProcessCreate.prototype = Object.create(Process.prototype);
ProcessCreate.prototype.constructor = ProcessCreate;
ProcessCreate.prototype.__class = ProcessCreate;
ProcessCreate.__cache = {};
Module['ProcessCreate'] = ProcessCreate;
ProcessCreate.prototype["__destroy"] = ProcessCreate.prototype.__destroy = function() {
    _mud_ProcessCreate__destroy(this.__ptr);
};
// ProcessDisplay
function ProcessDisplay() { throw "cannot construct a ProcessDisplay, no constructor in IDL" }
ProcessDisplay.prototype = Object.create(Process.prototype);
ProcessDisplay.prototype.constructor = ProcessDisplay;
ProcessDisplay.prototype.__class = ProcessDisplay;
ProcessDisplay.__cache = {};
Module['ProcessDisplay'] = ProcessDisplay;
ProcessDisplay.prototype["__destroy"] = ProcessDisplay.prototype.__destroy = function() {
    _mud_ProcessDisplay__destroy(this.__ptr);
};
// ProcessFunction
function ProcessFunction(a0, a1) {
    this.__ptr = _mud_ProcessFunction__construct_2(/*script*/a0.__ptr, /*function*/a1.__ptr); this.__type = ProcessFunction.__type; getCache(ProcessFunction)[this.__ptr] = this;
};
ProcessFunction.prototype = Object.create(ProcessCallable.prototype);
ProcessFunction.prototype.constructor = ProcessFunction;
ProcessFunction.prototype.__class = ProcessFunction;
ProcessFunction.__cache = {};
Module['ProcessFunction'] = ProcessFunction;
ProcessFunction.prototype["__destroy"] = ProcessFunction.prototype.__destroy = function() {
    _mud_ProcessFunction__destroy(this.__ptr);
};
// ProcessGetMember
function ProcessGetMember(a0, a1) {
    this.__ptr = _mud_ProcessGetMember__construct_2(/*script*/a0.__ptr, /*member*/a1.__ptr); this.__type = ProcessGetMember.__type; getCache(ProcessGetMember)[this.__ptr] = this;
};
ProcessGetMember.prototype = Object.create(Process.prototype);
ProcessGetMember.prototype.constructor = ProcessGetMember;
ProcessGetMember.prototype.__class = ProcessGetMember;
ProcessGetMember.__cache = {};
Module['ProcessGetMember'] = ProcessGetMember;
ProcessGetMember.prototype["__destroy"] = ProcessGetMember.prototype.__destroy = function() {
    _mud_ProcessGetMember__destroy(this.__ptr);
};
// ProcessInput
function ProcessInput() { throw "cannot construct a ProcessInput, no constructor in IDL" }
ProcessInput.prototype = Object.create(Process.prototype);
ProcessInput.prototype.constructor = ProcessInput;
ProcessInput.prototype.__class = ProcessInput;
ProcessInput.__cache = {};
Module['ProcessInput'] = ProcessInput;
ProcessInput.prototype["__destroy"] = ProcessInput.prototype.__destroy = function() {
    _mud_ProcessInput__destroy(this.__ptr);
};
// ProcessMethod
function ProcessMethod(a0, a1) {
    this.__ptr = _mud_ProcessMethod__construct_2(/*script*/a0.__ptr, /*method*/a1.__ptr); this.__type = ProcessMethod.__type; getCache(ProcessMethod)[this.__ptr] = this;
};
ProcessMethod.prototype = Object.create(ProcessCallable.prototype);
ProcessMethod.prototype.constructor = ProcessMethod;
ProcessMethod.prototype.__class = ProcessMethod;
ProcessMethod.__cache = {};
Module['ProcessMethod'] = ProcessMethod;
ProcessMethod.prototype["__destroy"] = ProcessMethod.prototype.__destroy = function() {
    _mud_ProcessMethod__destroy(this.__ptr);
};
// ProcessOutput
function ProcessOutput() { throw "cannot construct a ProcessOutput, no constructor in IDL" }
ProcessOutput.prototype = Object.create(Process.prototype);
ProcessOutput.prototype.constructor = ProcessOutput;
ProcessOutput.prototype.__class = ProcessOutput;
ProcessOutput.__cache = {};
Module['ProcessOutput'] = ProcessOutput;
ProcessOutput.prototype["__destroy"] = ProcessOutput.prototype.__destroy = function() {
    _mud_ProcessOutput__destroy(this.__ptr);
};
// ProcessScript
function ProcessScript(a0, a1) {
    this.__ptr = _mud_ProcessScript__construct_2(/*script*/a0.__ptr, /*target*/a1.__ptr); this.__type = ProcessScript.__type; getCache(ProcessScript)[this.__ptr] = this;
};
ProcessScript.prototype = Object.create(ProcessCallable.prototype);
ProcessScript.prototype.constructor = ProcessScript;
ProcessScript.prototype.__class = ProcessScript;
ProcessScript.__cache = {};
Module['ProcessScript'] = ProcessScript;
ProcessScript.prototype["__destroy"] = ProcessScript.prototype.__destroy = function() {
    _mud_ProcessScript__destroy(this.__ptr);
};
// ProcessSetMember
function ProcessSetMember(a0, a1) {
    this.__ptr = _mud_ProcessSetMember__construct_2(/*script*/a0.__ptr, /*member*/a1.__ptr); this.__type = ProcessSetMember.__type; getCache(ProcessSetMember)[this.__ptr] = this;
};
ProcessSetMember.prototype = Object.create(Process.prototype);
ProcessSetMember.prototype.constructor = ProcessSetMember;
ProcessSetMember.prototype.__class = ProcessSetMember;
ProcessSetMember.__cache = {};
Module['ProcessSetMember'] = ProcessSetMember;
ProcessSetMember.prototype["__destroy"] = ProcessSetMember.prototype.__destroy = function() {
    _mud_ProcessSetMember__destroy(this.__ptr);
};
// ProcessValue
function ProcessValue(a0, a1) {
    this.__ptr = _mud_ProcessValue__construct_2(/*script*/a0.__ptr, /*value*/a1.__ptr); this.__type = ProcessValue.__type; getCache(ProcessValue)[this.__ptr] = this;
};
ProcessValue.prototype = Object.create(Process.prototype);
ProcessValue.prototype.constructor = ProcessValue;
ProcessValue.prototype.__class = ProcessValue;
ProcessValue.__cache = {};
Module['ProcessValue'] = ProcessValue;
ProcessValue.prototype["__destroy"] = ProcessValue.prototype.__destroy = function() {
    _mud_ProcessValue__destroy(this.__ptr);
};
// Script
function Script() { throw "cannot construct a Script, no constructor in IDL" }
Script.prototype = Object.create(Callable.prototype);
Script.prototype.constructor = Script;
Script.prototype.__class = Script;
Script.__cache = {};
Module['Script'] = Script;
Object.defineProperty(Script.prototype, "index", {
    get: function() {
        return _mud_Script__get_index(this.__ptr);
    },
    set: function(value) {
        _mud_Script__set_index(this.__ptr, value);
    }
});
Object.defineProperty(Script.prototype, "type", {
    get: function() {
        return wrapPointer(_mud_Script__get_type(this.__ptr), Type);
    }});
Object.defineProperty(Script.prototype, "name", {
    get: function() {
        return UTF8ToString(_mud_Script__get_name(this.__ptr));
    },
    set: function(value) {
        _mud_Script__set_name(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Script.prototype, "locked", {
    get: function() {
        return !!(_mud_Script__get_locked(this.__ptr));
    },
    set: function(value) {
        _mud_Script__set_locked(this.__ptr, value);
    }
});
Script.prototype["__destroy"] = Script.prototype.__destroy = function() {
    _mud_Script__destroy(this.__ptr);
};
// Stream
function Stream() { throw "cannot construct a Stream, no constructor in IDL" }
Stream.prototype = Object.create(StreamBranch.prototype);
Stream.prototype.constructor = Stream;
Stream.prototype.__class = Stream;
Stream.__cache = {};
Module['Stream'] = Stream;
Stream.prototype["__destroy"] = Stream.prototype.__destroy = function() {
    _mud_Stream__destroy(this.__ptr);
};
// TextScript
function TextScript(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { this.__ptr = _mud_TextScript__construct_2(ensureString(/*name*/a0), /*language*/a1); this.__type = TextScript.__type; getCache(TextScript)[this.__ptr] = this; return; }
    this.__ptr = _mud_TextScript__construct_3(ensureString(/*name*/a0), /*language*/a1, /*signature*/a2.__ptr); this.__type = TextScript.__type; getCache(TextScript)[this.__ptr] = this;
};
TextScript.prototype = Object.create(Script.prototype);
TextScript.prototype.constructor = TextScript;
TextScript.prototype.__class = TextScript;
TextScript.__cache = {};
Module['TextScript'] = TextScript;
Object.defineProperty(TextScript.prototype, "language", {
    get: function() {
        return _mud_TextScript__get_language(this.__ptr);
    },
    set: function(value) {
        _mud_TextScript__set_language(this.__ptr, value);
    }
});
Object.defineProperty(TextScript.prototype, "script", {
    get: function() {
        return UTF8ToString(_mud_TextScript__get_script(this.__ptr));
    },
    set: function(value) {
        _mud_TextScript__set_script(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(TextScript.prototype, "dirty", {
    get: function() {
        return !!(_mud_TextScript__get_dirty(this.__ptr));
    },
    set: function(value) {
        _mud_TextScript__set_dirty(this.__ptr, value);
    }
});
TextScript.prototype["__destroy"] = TextScript.prototype.__destroy = function() {
    _mud_TextScript__destroy(this.__ptr);
};
// VisualScript
function VisualScript(a0, a1) {
    ensureCache.prepare();
    if (a1 === undefined) { this.__ptr = _mud_VisualScript__construct_1(ensureString(/*name*/a0)); this.__type = VisualScript.__type; getCache(VisualScript)[this.__ptr] = this; return; }
    this.__ptr = _mud_VisualScript__construct_2(ensureString(/*name*/a0), /*signature*/a1.__ptr); this.__type = VisualScript.__type; getCache(VisualScript)[this.__ptr] = this;
};
VisualScript.prototype = Object.create(Script.prototype);
VisualScript.prototype.constructor = VisualScript;
VisualScript.prototype.__class = VisualScript;
VisualScript.__cache = {};
Module['VisualScript'] = VisualScript;
VisualScript.prototype["__destroy"] = VisualScript.prototype.__destroy = function() {
    _mud_VisualScript__destroy(this.__ptr);
};
// WrenInterpreter
function WrenInterpreter() { throw "cannot construct a WrenInterpreter, no constructor in IDL" }
WrenInterpreter.prototype = Object.create(Interpreter.prototype);
WrenInterpreter.prototype.constructor = WrenInterpreter;
WrenInterpreter.prototype.__class = WrenInterpreter;
WrenInterpreter.__cache = {};
Module['WrenInterpreter'] = WrenInterpreter;
WrenInterpreter.prototype["__destroy"] = WrenInterpreter.prototype.__destroy = function() {
    _mud_WrenInterpreter__destroy(this.__ptr);
};

(function() {
    function setup() {
        Interpreter.__type = _mud_Interpreter__type();
        Pipe.__type = _mud_Pipe__type();
        Process.__type = _mud_Process__type();
        ScriptClass.__type = _mud_ScriptClass__type();
        ScriptError.__type = _mud_ScriptError__type();
        StreamBranch.__type = _mud_StreamBranch__type();
        Valve.__type = _mud_Valve__type();
        LuaInterpreter.__type = _mud_LuaInterpreter__type();
        ProcessCallable.__type = _mud_ProcessCallable__type();
        ProcessCreate.__type = _mud_ProcessCreate__type();
        ProcessDisplay.__type = _mud_ProcessDisplay__type();
        ProcessFunction.__type = _mud_ProcessFunction__type();
        ProcessGetMember.__type = _mud_ProcessGetMember__type();
        ProcessInput.__type = _mud_ProcessInput__type();
        ProcessMethod.__type = _mud_ProcessMethod__type();
        ProcessOutput.__type = _mud_ProcessOutput__type();
        ProcessScript.__type = _mud_ProcessScript__type();
        ProcessSetMember.__type = _mud_ProcessSetMember__type();
        ProcessValue.__type = _mud_ProcessValue__type();
        Script.__type = _mud_Script__type();
        Stream.__type = _mud_Stream__type();
        TextScript.__type = _mud_TextScript__type();
        VisualScript.__type = _mud_VisualScript__type();
        WrenInterpreter.__type = _mud_WrenInterpreter__type();
        // Language
        Module['Language'] = Module['Language'] || {};
        Module['Language']['Cpp'] = _mud_Language_Cpp();
        Module['Language']['Lua'] = _mud_Language_Lua();
        Module['Language']['Wren'] = _mud_Language_Wren();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
