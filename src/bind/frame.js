// Shell
function Shell(a0, a1) {
    ensureCache.prepare();
    if (a1 === undefined) { this.__ptr = _mud_Shell__construct_1(ensureString(/*resource_path*/a0)); this.__type = Shell.__type; getCache(Shell)[this.__ptr] = this; return; }
    this.__ptr = _mud_Shell__construct_2(ensureString(/*resource_path*/a0), ensureString(/*exec_path*/a1)); this.__type = Shell.__type; getCache(Shell)[this.__ptr] = this;
};
Shell.prototype = Object.create(WrapperObject.prototype);
Shell.prototype.constructor = Shell;
Shell.prototype.__class = Shell;
Shell.__cache = {};
Module['Shell'] = Shell;
Shell.prototype["begin_frame"] = Shell.prototype.begin_frame = function() {
    return !!(_mud_Shell_begin_frame_0(this.__ptr));
};
Shell.prototype["end_frame"] = Shell.prototype.end_frame = function() {
    return !!(_mud_Shell_end_frame_0(this.__ptr));
};
Shell.prototype["pump"] = Shell.prototype.pump = function() {
    return !!(_mud_Shell_pump_0(this.__ptr));
};
Object.defineProperty(Shell.prototype, "exec_path", {
    get: function() {
        return Pointer_stringify(_mud_Shell__get_exec_path(this.__ptr));
    },
    set: function(value) {
        _mud_Shell__set_exec_path(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Shell.prototype, "resource_path", {
    get: function() {
        return Pointer_stringify(_mud_Shell__get_resource_path(this.__ptr));
    },
    set: function(value) {
        _mud_Shell__set_resource_path(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Shell.prototype, "job_system", {
    get: function() {
        return wrapPointer(_mud_Shell__get_job_system(this.__ptr), JobSystem);
    }});
Object.defineProperty(Shell.prototype, "gfx", {
    get: function() {
        return wrapPointer(_mud_Shell__get_gfx(this.__ptr), GfxSystem);
    }});
Object.defineProperty(Shell.prototype, "editor", {
    get: function() {
        return wrapPointer(_mud_Shell__get_editor(this.__ptr), ShellContext);
    },
    set: function(value) {
        _mud_Shell__set_editor(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Shell.prototype, "ui", {
    get: function() {
        return wrapPointer(_mud_Shell__get_ui(this.__ptr), Ui);
    },
    set: function(value) {
        _mud_Shell__set_ui(this.__ptr, value.__ptr);
    }
});
Shell.prototype["__destroy"] = Shell.prototype.__destroy = function() {
    _mud_Shell__destroy(this.__ptr);
};
// ShellContext
function ShellContext() {
    this.__ptr = _mud_ShellContext__construct_0(); this.__type = ShellContext.__type; getCache(ShellContext)[this.__ptr] = this;
};
ShellContext.prototype = Object.create(WrapperObject.prototype);
ShellContext.prototype.constructor = ShellContext;
ShellContext.prototype.__class = ShellContext;
ShellContext.__cache = {};
Module['ShellContext'] = ShellContext;
Object.defineProperty(ShellContext.prototype, "screen", {
    get: function() {
        return wrapPointer(_mud_ShellContext__get_screen(this.__ptr), Widget);
    },
    set: function(value) {
        _mud_ShellContext__set_screen(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ShellContext.prototype, "dockbar", {
    get: function() {
        return wrapPointer(_mud_ShellContext__get_dockbar(this.__ptr), Dockbar);
    },
    set: function(value) {
        _mud_ShellContext__set_dockbar(this.__ptr, value.__ptr);
    }
});
ShellContext.prototype["__destroy"] = ShellContext.prototype.__destroy = function() {
    _mud_ShellContext__destroy(this.__ptr);
};

(function() {
    function setup() {
        Shell.__type = _mud_Shell__type();
        ShellContext.__type = _mud_ShellContext__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
