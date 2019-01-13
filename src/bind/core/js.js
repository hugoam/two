
// Bindings utilities
function WrapperObject() {
}
// Shell
function Shell(resource_path, exec_path) {
    var self = this.ptr;
    /* resource_path <const char*> [] */
    /* exec_path <const char*> [] */
    if (exec_path === undefined) { this.ptr = _mud_Shell_Shell_1(self, resource_path); getCache(Shell)[this.ptr] = this; return; }
    this.ptr = _mud_Shell_Shell_2(self, resource_path, exec_path); getCache(Shell)[this.ptr] = this;
};
Shell.prototype = Object.create(WrapperObject.prototype);
Shell.prototype.constructor = Shell;
Shell.prototype.__class__ = Shell;
Shell.__cache__ = {};
Module['Shell'] = Shell;
Shell.prototype["pump"] = Shell.prototype.pump = function() {
    return !!(_mud_Shell_pump_0());
};
Object.defineProperty(Shell.prototype, "exec_path", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Shell__get_exec_path(self));
    },
    set: function(exec_path) {
        var self = this.ptr;
        /* exec_path <std::string> [] */
        if (exec_path && typeof exec_path === "object") exec_path = exec_path.ptr;
        else exec_path = ensureString(exec_path);
        _mud_Shell__set_exec_path(self, exec_path);
    }
});
Object.defineProperty(Shell.prototype, "resource_path", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Shell__get_resource_path(self));
    },
    set: function(resource_path) {
        var self = this.ptr;
        /* resource_path <std::string> [] */
        if (resource_path && typeof resource_path === "object") resource_path = resource_path.ptr;
        else resource_path = ensureString(resource_path);
        _mud_Shell__set_resource_path(self, resource_path);
    }
});
Object.defineProperty(Shell.prototype, "job_system", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shell__get_job_system(self), mud::JobSystem);
    }});
Object.defineProperty(Shell.prototype, "gfx_system", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shell__get_gfx_system(self), mud::GfxSystem);
    }});
Object.defineProperty(Shell.prototype, "editor", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shell__get_editor(self), mud::ShellContext);
    },
    set: function(editor) {
        var self = this.ptr;
        /* editor <ShellContext> [] */
        editor = editor.ptr;
        _mud_Shell__set_editor(self, editor);
    }
});
Object.defineProperty(Shell.prototype, "ui", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Shell__get_ui(self), mud::Ui);
    },
    set: function(ui) {
        var self = this.ptr;
        /* ui <Ui> [] */
        ui = ui.ptr;
        _mud_Shell__set_ui(self, ui);
    }
});
Shell.prototype["__destroy__"] = Shell.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Shell__destroy(self);
};
// ShellContext
function ShellContext() {
    var self = this.ptr;
    this.ptr = _mud_ShellContext_ShellContext_0(self); getCache(ShellContext)[this.ptr] = this;
};
ShellContext.prototype = Object.create(WrapperObject.prototype);
ShellContext.prototype.constructor = ShellContext;
ShellContext.prototype.__class__ = ShellContext;
ShellContext.__cache__ = {};
Module['ShellContext'] = ShellContext;
Object.defineProperty(ShellContext.prototype, "screen", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ShellContext__get_screen(self), mud::Widget);
    },
    set: function(screen) {
        var self = this.ptr;
        /* screen <Widget> [] */
        screen = screen.ptr;
        _mud_ShellContext__set_screen(self, screen);
    }
});
Object.defineProperty(ShellContext.prototype, "dockbar", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_ShellContext__get_dockbar(self), mud::Dockbar);
    },
    set: function(dockbar) {
        var self = this.ptr;
        /* dockbar <Dockbar> [] */
        dockbar = dockbar.ptr;
        _mud_ShellContext__set_dockbar(self, dockbar);
    }
});
ShellContext.prototype["__destroy__"] = ShellContext.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ShellContext__destroy(self);
};

(function() {
    function setupEnums() {
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
