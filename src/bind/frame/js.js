Module['glm'] = Module['glm'] || {};
Module['gfx'] = Module['gfx'] || {};
Module['ui'] = Module['ui'] || {};
// Shell
function Shell(resource_path, exec_path) {
    ensureCache.prepare();
    /* resource_path <const char*> [] */
    if (resource_path && typeof resource_path === "object") resource_path = resource_path.ptr;
    else resource_path = ensureString(resource_path);
    /* exec_path <const char*> [] */
    if (exec_path && typeof exec_path === "object") exec_path = exec_path.ptr;
    else exec_path = ensureString(exec_path);
    if (exec_path === undefined) { this.ptr = _mud_Shell_Shell_1(resource_path); getCache(Shell)[this.ptr] = this; return; }
    this.ptr = _mud_Shell_Shell_2(resource_path, exec_path); getCache(Shell)[this.ptr] = this;
    this.type = Shell;
};
Shell.prototype = Object.create(WrapperObject.prototype);
Shell.prototype.constructor = Shell;
Shell.prototype.__class__ = Shell;
Shell.__cache__ = {};
Module['Shell'] = Shell;
Shell.prototype["pump"] = Shell.prototype.pump = function(self) {
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
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_Shell__set_exec_path(self, value);
    }
});
Object.defineProperty(Shell.prototype, "resource_path", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Shell__get_resource_path(self));
    },
    set: function(value) {
        var self = this.ptr;
        /* value <string> [] */
        if (value && typeof value === "object") value = value.ptr;
        else value = ensureString(value);
        _mud_Shell__set_resource_path(self, value);
    }
});
Object.defineProperty(Shell.prototype, "job_system", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shell__get_job_system(self), JobSystem);
    }});
Object.defineProperty(Shell.prototype, "gfx_system", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shell__get_gfx_system(self), GfxSystem);
    }});
Object.defineProperty(Shell.prototype, "editor", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shell__get_editor(self), ShellContext);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <ShellContext> [] */
        value = value.ptr;
        _mud_Shell__set_editor(self, value);
    }
});
Object.defineProperty(Shell.prototype, "ui", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shell__get_ui(self), Ui);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Ui> [] */
        value = value.ptr;
        _mud_Shell__set_ui(self, value);
    }
});
Shell.prototype["__destroy__"] = Shell.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Shell__destroy(self);
};
// ShellContext
function ShellContext() {
    this.ptr = _mud_ShellContext_ShellContext_0(); getCache(ShellContext)[this.ptr] = this;
    this.type = ShellContext;
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
        /* value <Widget> [] */
        value = value.ptr;
        _mud_ShellContext__set_screen(self, value);
    }
});
Object.defineProperty(ShellContext.prototype, "dockbar", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ShellContext__get_dockbar(self), Dockbar);
    },
    set: function(value) {
        var self = this.ptr;
        /* value <Dockbar> [] */
        value = value.ptr;
        _mud_ShellContext__set_dockbar(self, value);
    }
});
ShellContext.prototype["__destroy__"] = ShellContext.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ShellContext__destroy(self);
};

(function() {
    function setup() {
        Shell.__type__ = _mud_Shell__type();
        ShellContext.__type__ = _mud_ShellContext__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
