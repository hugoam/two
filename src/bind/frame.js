// Shell
function Shell(a0, a1) {
    ensureCache.prepare();
    if (a1 === undefined) { this.ptr = _mud_Shell__construct_1(ensureString(/*resource_path*/a0)); this.type = Shell; getCache(Shell)[this.ptr] = this; return; }
    this.ptr = _mud_Shell__construct_2(ensureString(/*resource_path*/a0), ensureString(/*exec_path*/a1)); this.type = Shell; getCache(Shell)[this.ptr] = this;
};
Shell.prototype = Object.create(WrapperObject.prototype);
Shell.prototype.constructor = Shell;
Shell.prototype.__class__ = Shell;
Shell.__cache__ = {};
Module['Shell'] = Shell;
Shell.prototype["begin_frame"] = Shell.prototype.begin_frame = function() {
    var self = this.ptr;
    return !!(_mud_Shell_begin_frame_0(self));
};
Shell.prototype["end_frame"] = Shell.prototype.end_frame = function() {
    var self = this.ptr;
    return !!(_mud_Shell_end_frame_0(self));
};
Shell.prototype["pump"] = Shell.prototype.pump = function() {
    var self = this.ptr;
    return !!(_mud_Shell_pump_0(self));
};
Object.defineProperty(Shell.prototype, "exec_path", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Shell__get_exec_path(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Shell__set_exec_path(self, ensureString(value));
    }
});
Object.defineProperty(Shell.prototype, "resource_path", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Shell__get_resource_path(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Shell__set_resource_path(self, ensureString(value));
    }
});
Object.defineProperty(Shell.prototype, "job_system", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shell__get_job_system(self), JobSystem);
    }});
Object.defineProperty(Shell.prototype, "gfx", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shell__get_gfx(self), GfxSystem);
    }});
Object.defineProperty(Shell.prototype, "editor", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shell__get_editor(self), ShellContext);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Shell__set_editor(self, value.ptr);
    }
});
Object.defineProperty(Shell.prototype, "ui", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shell__get_ui(self), Ui);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Shell__set_ui(self, value.ptr);
    }
});
Shell.prototype["__destroy__"] = Shell.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Shell__destroy(self);
};
// ShellContext
function ShellContext() {
    this.ptr = _mud_ShellContext__construct_0(); this.type = ShellContext; getCache(ShellContext)[this.ptr] = this;
};
ShellContext.prototype = Object.create(WrapperObject.prototype);
ShellContext.prototype.constructor = ShellContext;
ShellContext.prototype.__class__ = ShellContext;
ShellContext.__cache__ = {};
Module['ShellContext'] = ShellContext;
Object.defineProperty(ShellContext.prototype, "screen", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ShellContext__get_screen(self), Widget);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ShellContext__set_screen(self, value.ptr);
    }
});
Object.defineProperty(ShellContext.prototype, "dockbar", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ShellContext__get_dockbar(self), Dockbar);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_ShellContext__set_dockbar(self, value.ptr);
    }
});
ShellContext.prototype["__destroy__"] = ShellContext.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ShellContext__destroy(self);
};
Module['Selection'] = vector_mud_Ref;

(function() {
    function setup() {
        Shell.__type__ = _mud_Shell__type();
        ShellContext.__type__ = _mud_ShellContext__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
