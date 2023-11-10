// ShellContext
function ShellContext() {
    
    this.__ptr = _two_ShellContext__construct_0(); getCache(ShellContext)[this.__ptr] = this;
};
ShellContext.prototype = Object.create(WrapperObject.prototype);
ShellContext.prototype.constructor = ShellContext;
ShellContext.prototype.__class = ShellContext;
ShellContext.__cache = {};
Module['ShellContext'] = ShellContext;
Object.defineProperty(ShellContext.prototype, "screen", {
    get: function() {
        return wrapPointer(_two_ShellContext__get_screen(this.__ptr), Widget);
    },
    set: function(value) {
        if (!checkClass(value, Widget)) throw Error('ShellContext.screen: expected Widget');
        _two_ShellContext__set_screen(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(ShellContext.prototype, "dockbar", {
    get: function() {
        return wrapPointer(_two_ShellContext__get_dockbar(this.__ptr), Dockbar);
    },
    set: function(value) {
        if (!checkClass(value, Dockbar)) throw Error('ShellContext.dockbar: expected Dockbar');
        _two_ShellContext__set_dockbar(this.__ptr, value.__ptr);
    }
});
ShellContext.prototype["__destroy"] = ShellContext.prototype.__destroy = function() {
    _two_ShellContext__destroy(this.__ptr);
};
// ShellWindow
function ShellWindow() { throw "cannot construct a ShellWindow, no constructor in IDL" }
ShellWindow.prototype = Object.create(GfxWindow.prototype);
ShellWindow.prototype.constructor = ShellWindow;
ShellWindow.prototype.__class = ShellWindow;
ShellWindow.__base = GfxWindow;
ShellWindow.__cache = {};
Module['ShellWindow'] = ShellWindow;
Object.defineProperty(ShellWindow.prototype, "index", {
    get: function() {
        return _two_ShellWindow__get_index(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('ShellWindow.index: expected integer');
        _two_ShellWindow__set_index(this.__ptr, value);
    }
});
Object.defineProperty(ShellWindow.prototype, "ui_window", {
    get: function() {
        return wrapPointer(_two_ShellWindow__get_ui_window(this.__ptr), UiWindow);
    }});
Object.defineProperty(ShellWindow.prototype, "ui", {
    get: function() {
        return wrapPointer(_two_ShellWindow__get_ui(this.__ptr), Ui);
    },
    set: function(value) {
        if (!checkClass(value, Ui)) throw Error('ShellWindow.ui: expected Ui');
        _two_ShellWindow__set_ui(this.__ptr, value.__ptr);
    }
});
ShellWindow.prototype["__destroy"] = ShellWindow.prototype.__destroy = function() {
    _two_ShellWindow__destroy(this.__ptr);
};
// Shell
function Shell(a0, a1, a2) {
    ensureCache.prepare();
    if (a1 === undefined) { if (typeof a0 !== 'string') throw Error('Shell(0:resource_path): expected string'); }
    else if (a2 === undefined) { if (typeof a0 !== 'string') throw Error('Shell(0:resource_path): expected string'); if (typeof a1 !== 'string') throw Error('Shell(1:exec_path): expected string'); }
    else { if (typeof a0 !== 'string') throw Error('Shell(0:resource_path): expected string'); if (typeof a1 !== 'string') throw Error('Shell(1:exec_path): expected string'); if (typeof a2 !== 'boolean') throw Error('Shell(2:window): expected boolean'); }
    if (a1 === undefined) { this.__ptr = _two_Shell__construct_1(ensureString(/*resource_path*/a0)); getCache(Shell)[this.__ptr] = this; }
    else if (a2 === undefined) { this.__ptr = _two_Shell__construct_2(ensureString(/*resource_path*/a0), ensureString(/*exec_path*/a1)); getCache(Shell)[this.__ptr] = this; }
    else { this.__ptr = _two_Shell__construct_3(ensureString(/*resource_path*/a0), ensureString(/*exec_path*/a1), /*window*/a2); getCache(Shell)[this.__ptr] = this; }
};
Shell.prototype = Object.create(WrapperObject.prototype);
Shell.prototype.constructor = Shell;
Shell.prototype.__class = Shell;
Shell.__cache = {};
Module['Shell'] = Shell;
Shell.prototype["init"] = Shell.prototype.init = function(a0) {
    if (a0 === undefined) {  }
    else { if (typeof a0 !== 'boolean') throw Error('init(0:window): expected boolean'); }
    if (a0 === undefined) { _two_Shell_init_0(this.__ptr); }
    else { _two_Shell_init_1(this.__ptr, /*window*/a0); }
};
Shell.prototype["window"] = Shell.prototype.window = function(a0, a1, a2) {
    ensureCache.prepare();
    if (a2 === undefined) { if (typeof a0 !== 'string') throw Error('window(0:name): expected string'); if (!checkClass(a1, v2_uint)) throw Error('window(1:size): expected v2<uint>'); }
    else { if (typeof a0 !== 'string') throw Error('window(0:name): expected string'); if (!checkClass(a1, v2_uint)) throw Error('window(1:size): expected v2<uint>'); if (typeof a2 !== 'boolean') throw Error('window(2:fullscreen): expected boolean'); }
    if (a2 === undefined) { return wrapPointer(_two_Shell_window_2(this.__ptr, ensureString(/*name*/a0), /*size*/a1.__ptr), ShellWindow); }
    else { return wrapPointer(_two_Shell_window_3(this.__ptr, ensureString(/*name*/a0), /*size*/a1.__ptr, /*fullscreen*/a2), ShellWindow); }
};
Shell.prototype["add_file"] = Shell.prototype.add_file = function(a0, a1) {
    ensureCache.prepare();
    if (typeof a0 !== 'string') throw Error('add_file(0:path): expected string'); 
    _two_Shell_add_file_2(this.__ptr, ensureString(/*path*/a0), ensureInt8(/*data*/a1), /*data*/a1.length);
};
Shell.prototype["begin_frame"] = Shell.prototype.begin_frame = function() {
    
    return !!(_two_Shell_begin_frame_0(this.__ptr));
};
Shell.prototype["end_frame"] = Shell.prototype.end_frame = function() {
    
    _two_Shell_end_frame_0(this.__ptr);
};
Shell.prototype["pump"] = Shell.prototype.pump = function() {
    
    return !!(_two_Shell_pump_0(this.__ptr));
};
Shell.prototype["main_window"] = Shell.prototype.main_window = function() {
    
    return wrapPointer(_two_Shell_main_window_0(this.__ptr), ShellWindow);
};
Object.defineProperty(Shell.prototype, "exec_path", {
    get: function() {
        return UTF8ToString(_two_Shell__get_exec_path(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Shell.exec_path: expected string');
        _two_Shell__set_exec_path(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Shell.prototype, "resource_path", {
    get: function() {
        return UTF8ToString(_two_Shell__get_resource_path(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Shell.resource_path: expected string');
        _two_Shell__set_resource_path(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Shell.prototype, "job_system", {
    get: function() {
        return wrapPointer(_two_Shell__get_job_system(this.__ptr), JobSystem);
    }});
Object.defineProperty(Shell.prototype, "gfx", {
    get: function() {
        return wrapPointer(_two_Shell__get_gfx(this.__ptr), GfxSystem);
    }});
Object.defineProperty(Shell.prototype, "editor", {
    get: function() {
        return wrapPointer(_two_Shell__get_editor(this.__ptr), ShellContext);
    },
    set: function(value) {
        if (!checkClass(value, ShellContext)) throw Error('Shell.editor: expected ShellContext');
        _two_Shell__set_editor(this.__ptr, value.__ptr);
    }
});
Shell.prototype["__destroy"] = Shell.prototype.__destroy = function() {
    _two_Shell__destroy(this.__ptr);
};

(function() {
    function setup() {
        ShellContext.prototype.__type = _two_ShellContext__type();
        ShellWindow.prototype.__type = _two_ShellWindow__type();
        Shell.prototype.__type = _two_Shell__type();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
