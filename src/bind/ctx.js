// RenderSystem
function RenderSystem() { throw "cannot construct a RenderSystem, no constructor in IDL" }
RenderSystem.prototype = Object.create(WrapperObject.prototype);
RenderSystem.prototype.constructor = RenderSystem;
RenderSystem.prototype.__class = RenderSystem;
RenderSystem.__cache = {};
Module['RenderSystem'] = RenderSystem;
RenderSystem.prototype["__destroy"] = RenderSystem.prototype.__destroy = function() {
    _two_RenderSystem__destroy(this.__ptr);
};
// Context
function Context() { throw "cannot construct a Context, no constructor in IDL" }
Context.prototype = Object.create(WrapperObject.prototype);
Context.prototype.constructor = Context;
Context.prototype.__class = Context;
Context.__cache = {};
Module['Context'] = Context;
Context.prototype["reset_fb"] = Context.prototype.reset_fb = function(a0) {
    if (!checkClass(a0, v2_uint)) throw Error('reset_fb(0:size): expected v2<uint>');
    _two_Context_reset_fb_1(this.__ptr, /*size*/a0.__ptr);
};
Context.prototype["init_input"] = Context.prototype.init_input = function(a0, a1) {
    if (!checkClass(a0, Mouse)) throw Error('init_input(0:mouse): expected Mouse'); if (!checkClass(a1, Keyboard)) throw Error('init_input(1:keyboard): expected Keyboard');
    _two_Context_init_input_2(this.__ptr, /*mouse*/a0.__ptr, /*keyboard*/a1.__ptr);
};
Context.prototype["begin_frame"] = Context.prototype.begin_frame = function() {
    
    return !!(_two_Context_begin_frame_0(this.__ptr));
};
Context.prototype["render_frame"] = Context.prototype.render_frame = function() {
    
    _two_Context_render_frame_0(this.__ptr);
};
Context.prototype["end_frame"] = Context.prototype.end_frame = function() {
    
    _two_Context_end_frame_0(this.__ptr);
};
Context.prototype["lock_mouse"] = Context.prototype.lock_mouse = function(a0) {
    if (typeof a0 !== 'boolean') throw Error('lock_mouse(0:locked): expected boolean');
    _two_Context_lock_mouse_1(this.__ptr, /*locked*/a0);
};
Object.defineProperty(Context.prototype, "resource_path", {
    get: function() {
        return UTF8ToString(_two_Context__get_resource_path(this.__ptr));
    }});
Object.defineProperty(Context.prototype, "title", {
    get: function() {
        return UTF8ToString(_two_Context__get_title(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'string') throw Error('Context.title: expected string');
        _two_Context__set_title(this.__ptr, ensureString(value));
    }
});
Object.defineProperty(Context.prototype, "size", {
    get: function() {
        return wrapPointer(_two_Context__get_size(this.__ptr), v2_uint);
    },
    set: function(value) {
        if (!checkClass(value, v2_uint)) throw Error('Context.size: expected v2<uint>');
        _two_Context__set_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Context.prototype, "fb_size", {
    get: function() {
        return wrapPointer(_two_Context__get_fb_size(this.__ptr), v2_uint);
    },
    set: function(value) {
        if (!checkClass(value, v2_uint)) throw Error('Context.fb_size: expected v2<uint>');
        _two_Context__set_fb_size(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Context.prototype, "fullscreen", {
    get: function() {
        return !!(_two_Context__get_fullscreen(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Context.fullscreen: expected boolean');
        _two_Context__set_fullscreen(this.__ptr, value);
    }
});
Object.defineProperty(Context.prototype, "is_main", {
    get: function() {
        return !!(_two_Context__get_is_main(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Context.is_main: expected boolean');
        _two_Context__set_is_main(this.__ptr, value);
    }
});
Object.defineProperty(Context.prototype, "pixel_ratio", {
    get: function() {
        return _two_Context__get_pixel_ratio(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('Context.pixel_ratio: expected number');
        _two_Context__set_pixel_ratio(this.__ptr, value);
    }
});
Object.defineProperty(Context.prototype, "active", {
    get: function() {
        return !!(_two_Context__get_active(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Context.active: expected boolean');
        _two_Context__set_active(this.__ptr, value);
    }
});
Object.defineProperty(Context.prototype, "shutdown", {
    get: function() {
        return !!(_two_Context__get_shutdown(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Context.shutdown: expected boolean');
        _two_Context__set_shutdown(this.__ptr, value);
    }
});
Object.defineProperty(Context.prototype, "cursor", {
    get: function() {
        return wrapPointer(_two_Context__get_cursor(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('Context.cursor: expected v2<float>');
        _two_Context__set_cursor(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(Context.prototype, "mouse_lock", {
    get: function() {
        return !!(_two_Context__get_mouse_lock(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('Context.mouse_lock: expected boolean');
        _two_Context__set_mouse_lock(this.__ptr, value);
    }
});
Context.prototype["__destroy"] = Context.prototype.__destroy = function() {
    _two_Context__destroy(this.__ptr);
};
// InputEvent
function InputEvent() {
    
    this.__ptr = _two_InputEvent__construct_0(); getCache(InputEvent)[this.__ptr] = this;
};
InputEvent.prototype = Object.create(WrapperObject.prototype);
InputEvent.prototype.constructor = InputEvent;
InputEvent.prototype.__class = InputEvent;
InputEvent.__cache = {};
Module['InputEvent'] = InputEvent;
InputEvent.prototype["consume"] = InputEvent.prototype.consume = function(a0) {
    if (!checkClass(a0, ControlNode)) throw Error('consume(0:consumer): expected ControlNode');
    return wrapPointer(_two_InputEvent_consume_1(this.__ptr, /*consumer*/a0.__ptr), InputEvent);
};
InputEvent.prototype["valid"] = InputEvent.prototype.valid = function() {
    
    return !!(_two_InputEvent_valid_0(this.__ptr));
};
Object.defineProperty(InputEvent.prototype, "deviceType", {
    get: function() {
        return _two_InputEvent__get_deviceType(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('InputEvent.deviceType: expected integer');
        _two_InputEvent__set_deviceType(this.__ptr, value);
    }
});
Object.defineProperty(InputEvent.prototype, "eventType", {
    get: function() {
        return _two_InputEvent__get_eventType(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('InputEvent.eventType: expected integer');
        _two_InputEvent__set_eventType(this.__ptr, value);
    }
});
Object.defineProperty(InputEvent.prototype, "receiver", {
    get: function() {
        return wrapPointer(_two_InputEvent__get_receiver(this.__ptr), ControlNode);
    },
    set: function(value) {
        if (!checkClass(value, ControlNode)) throw Error('InputEvent.receiver: expected ControlNode');
        _two_InputEvent__set_receiver(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InputEvent.prototype, "consumer", {
    get: function() {
        return wrapPointer(_two_InputEvent__get_consumer(this.__ptr), ControlNode);
    },
    set: function(value) {
        if (!checkClass(value, ControlNode)) throw Error('InputEvent.consumer: expected ControlNode');
        _two_InputEvent__set_consumer(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(InputEvent.prototype, "abort", {
    get: function() {
        return !!(_two_InputEvent__get_abort(this.__ptr));
    },
    set: function(value) {
        if (typeof value !== 'boolean') throw Error('InputEvent.abort: expected boolean');
        _two_InputEvent__set_abort(this.__ptr, value);
    }
});
Object.defineProperty(InputEvent.prototype, "modifiers", {
    get: function() {
        return _two_InputEvent__get_modifiers(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('InputEvent.modifiers: expected integer');
        _two_InputEvent__set_modifiers(this.__ptr, value);
    }
});
Object.defineProperty(InputEvent.prototype, "key", {
    get: function() {
        return _two_InputEvent__get_key(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('InputEvent.key: expected integer');
        _two_InputEvent__set_key(this.__ptr, value);
    }
});
InputEvent.prototype["__destroy"] = InputEvent.prototype.__destroy = function() {
    _two_InputEvent__destroy(this.__ptr);
};
// MouseEvent
function MouseEvent() {
    
    this.__ptr = _two_MouseEvent__construct_0(); getCache(MouseEvent)[this.__ptr] = this;
};
MouseEvent.prototype = Object.create(InputEvent.prototype);
MouseEvent.prototype.constructor = MouseEvent;
MouseEvent.prototype.__class = MouseEvent;
MouseEvent.__base = InputEvent;
MouseEvent.__cache = {};
Module['MouseEvent'] = MouseEvent;
Object.defineProperty(MouseEvent.prototype, "pos", {
    get: function() {
        return wrapPointer(_two_MouseEvent__get_pos(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('MouseEvent.pos: expected v2<float>');
        _two_MouseEvent__set_pos(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MouseEvent.prototype, "relative", {
    get: function() {
        return wrapPointer(_two_MouseEvent__get_relative(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('MouseEvent.relative: expected v2<float>');
        _two_MouseEvent__set_relative(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MouseEvent.prototype, "delta", {
    get: function() {
        return wrapPointer(_two_MouseEvent__get_delta(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('MouseEvent.delta: expected v2<float>');
        _two_MouseEvent__set_delta(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MouseEvent.prototype, "deltaZ", {
    get: function() {
        return _two_MouseEvent__get_deltaZ(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('MouseEvent.deltaZ: expected number');
        _two_MouseEvent__set_deltaZ(this.__ptr, value);
    }
});
Object.defineProperty(MouseEvent.prototype, "pressed", {
    get: function() {
        return wrapPointer(_two_MouseEvent__get_pressed(this.__ptr), v2_float);
    },
    set: function(value) {
        if (!checkClass(value, v2_float)) throw Error('MouseEvent.pressed: expected v2<float>');
        _two_MouseEvent__set_pressed(this.__ptr, value.__ptr);
    }
});
Object.defineProperty(MouseEvent.prototype, "button", {
    get: function() {
        return _two_MouseEvent__get_button(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('MouseEvent.button: expected integer');
        _two_MouseEvent__set_button(this.__ptr, value);
    }
});
MouseEvent.prototype["__destroy"] = MouseEvent.prototype.__destroy = function() {
    _two_MouseEvent__destroy(this.__ptr);
};
// KeyEvent
function KeyEvent() {
    
    this.__ptr = _two_KeyEvent__construct_0(); getCache(KeyEvent)[this.__ptr] = this;
};
KeyEvent.prototype = Object.create(InputEvent.prototype);
KeyEvent.prototype.constructor = KeyEvent;
KeyEvent.prototype.__class = KeyEvent;
KeyEvent.__base = InputEvent;
KeyEvent.__cache = {};
Module['KeyEvent'] = KeyEvent;
Object.defineProperty(KeyEvent.prototype, "code", {
    get: function() {
        return _two_KeyEvent__get_code(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('KeyEvent.code: expected integer');
        _two_KeyEvent__set_code(this.__ptr, value);
    }
});
Object.defineProperty(KeyEvent.prototype, "char", {
    get: function() {
        return _two_KeyEvent__get_char(this.__ptr);
    },
    set: function(value) {
        if (typeof value !== 'number') throw Error('KeyEvent.char: expected integer');
        _two_KeyEvent__set_char(this.__ptr, value);
    }
});
KeyEvent.prototype["__destroy"] = KeyEvent.prototype.__destroy = function() {
    _two_KeyEvent__destroy(this.__ptr);
};
// ControlNode
function ControlNode() { throw "cannot construct a ControlNode, no constructor in IDL" }
ControlNode.prototype = Object.create(WrapperObject.prototype);
ControlNode.prototype.constructor = ControlNode;
ControlNode.prototype.__class = ControlNode;
ControlNode.__cache = {};
Module['ControlNode'] = ControlNode;
ControlNode.prototype["__destroy"] = ControlNode.prototype.__destroy = function() {
    _two_ControlNode__destroy(this.__ptr);
};
// Keyboard
function Keyboard() { throw "cannot construct a Keyboard, no constructor in IDL" }
Keyboard.prototype = Object.create(WrapperObject.prototype);
Keyboard.prototype.constructor = Keyboard;
Keyboard.prototype.__class = Keyboard;
Keyboard.__cache = {};
Module['Keyboard'] = Keyboard;
Keyboard.prototype["__destroy"] = Keyboard.prototype.__destroy = function() {
    _two_Keyboard__destroy(this.__ptr);
};
// Mouse
function Mouse() { throw "cannot construct a Mouse, no constructor in IDL" }
Mouse.prototype = Object.create(WrapperObject.prototype);
Mouse.prototype.constructor = Mouse;
Mouse.prototype.__class = Mouse;
Mouse.__cache = {};
Module['Mouse'] = Mouse;
Mouse.prototype["__destroy"] = Mouse.prototype.__destroy = function() {
    _two_Mouse__destroy(this.__ptr);
};

(function() {
    function setup() {
        RenderSystem.prototype.__type = _two_RenderSystem__type();
        Context.prototype.__type = _two_Context__type();
        InputEvent.prototype.__type = _two_InputEvent__type();
        MouseEvent.prototype.__type = _two_MouseEvent__type();
        KeyEvent.prototype.__type = _two_KeyEvent__type();
        ControlNode.prototype.__type = _two_ControlNode__type();
        Keyboard.prototype.__type = _two_Keyboard__type();
        Mouse.prototype.__type = _two_Mouse__type();
        // Key
        Module['Key'] = Module['Key'] || {};
        Module['Key']['Unassigned'] = _two_Key_Unassigned();
        Module['Key']['Escape'] = _two_Key_Escape();
        Module['Key']['Num1'] = _two_Key_Num1();
        Module['Key']['Num2'] = _two_Key_Num2();
        Module['Key']['Num3'] = _two_Key_Num3();
        Module['Key']['Num4'] = _two_Key_Num4();
        Module['Key']['Num5'] = _two_Key_Num5();
        Module['Key']['Num6'] = _two_Key_Num6();
        Module['Key']['Num7'] = _two_Key_Num7();
        Module['Key']['Num8'] = _two_Key_Num8();
        Module['Key']['Num9'] = _two_Key_Num9();
        Module['Key']['Num0'] = _two_Key_Num0();
        Module['Key']['Minus'] = _two_Key_Minus();
        Module['Key']['Equals'] = _two_Key_Equals();
        Module['Key']['Back'] = _two_Key_Back();
        Module['Key']['Tab'] = _two_Key_Tab();
        Module['Key']['Q'] = _two_Key_Q();
        Module['Key']['W'] = _two_Key_W();
        Module['Key']['E'] = _two_Key_E();
        Module['Key']['R'] = _two_Key_R();
        Module['Key']['T'] = _two_Key_T();
        Module['Key']['Y'] = _two_Key_Y();
        Module['Key']['U'] = _two_Key_U();
        Module['Key']['I'] = _two_Key_I();
        Module['Key']['O'] = _two_Key_O();
        Module['Key']['P'] = _two_Key_P();
        Module['Key']['LeftBracket'] = _two_Key_LeftBracket();
        Module['Key']['RightBracket'] = _two_Key_RightBracket();
        Module['Key']['Return'] = _two_Key_Return();
        Module['Key']['LeftControl'] = _two_Key_LeftControl();
        Module['Key']['A'] = _two_Key_A();
        Module['Key']['S'] = _two_Key_S();
        Module['Key']['D'] = _two_Key_D();
        Module['Key']['F'] = _two_Key_F();
        Module['Key']['G'] = _two_Key_G();
        Module['Key']['H'] = _two_Key_H();
        Module['Key']['J'] = _two_Key_J();
        Module['Key']['K'] = _two_Key_K();
        Module['Key']['L'] = _two_Key_L();
        Module['Key']['Semicolon'] = _two_Key_Semicolon();
        Module['Key']['Apostrophe'] = _two_Key_Apostrophe();
        Module['Key']['Grave'] = _two_Key_Grave();
        Module['Key']['LeftShift'] = _two_Key_LeftShift();
        Module['Key']['Backslash'] = _two_Key_Backslash();
        Module['Key']['Z'] = _two_Key_Z();
        Module['Key']['X'] = _two_Key_X();
        Module['Key']['C'] = _two_Key_C();
        Module['Key']['V'] = _two_Key_V();
        Module['Key']['B'] = _two_Key_B();
        Module['Key']['N'] = _two_Key_N();
        Module['Key']['M'] = _two_Key_M();
        Module['Key']['Comma'] = _two_Key_Comma();
        Module['Key']['Period'] = _two_Key_Period();
        Module['Key']['Slash'] = _two_Key_Slash();
        Module['Key']['RightShift'] = _two_Key_RightShift();
        Module['Key']['Multiply'] = _two_Key_Multiply();
        Module['Key']['LeftAlt'] = _two_Key_LeftAlt();
        Module['Key']['Space'] = _two_Key_Space();
        Module['Key']['Capital'] = _two_Key_Capital();
        Module['Key']['F1'] = _two_Key_F1();
        Module['Key']['F2'] = _two_Key_F2();
        Module['Key']['F3'] = _two_Key_F3();
        Module['Key']['F4'] = _two_Key_F4();
        Module['Key']['F5'] = _two_Key_F5();
        Module['Key']['F6'] = _two_Key_F6();
        Module['Key']['F7'] = _two_Key_F7();
        Module['Key']['F8'] = _two_Key_F8();
        Module['Key']['F9'] = _two_Key_F9();
        Module['Key']['F10'] = _two_Key_F10();
        Module['Key']['Numlock'] = _two_Key_Numlock();
        Module['Key']['ScrollLock'] = _two_Key_ScrollLock();
        Module['Key']['Numpad7'] = _two_Key_Numpad7();
        Module['Key']['Numpad8'] = _two_Key_Numpad8();
        Module['Key']['Numpad9'] = _two_Key_Numpad9();
        Module['Key']['Subtract'] = _two_Key_Subtract();
        Module['Key']['Numpad4'] = _two_Key_Numpad4();
        Module['Key']['Numpad5'] = _two_Key_Numpad5();
        Module['Key']['Numpad6'] = _two_Key_Numpad6();
        Module['Key']['Add'] = _two_Key_Add();
        Module['Key']['Numpad1'] = _two_Key_Numpad1();
        Module['Key']['Numpad2'] = _two_Key_Numpad2();
        Module['Key']['Numpad3'] = _two_Key_Numpad3();
        Module['Key']['Numpad0'] = _two_Key_Numpad0();
        Module['Key']['Decimal'] = _two_Key_Decimal();
        Module['Key']['F11'] = _two_Key_F11();
        Module['Key']['F12'] = _two_Key_F12();
        Module['Key']['F13'] = _two_Key_F13();
        Module['Key']['F14'] = _two_Key_F14();
        Module['Key']['F15'] = _two_Key_F15();
        Module['Key']['NumpadEquals'] = _two_Key_NumpadEquals();
        Module['Key']['NumpadEnter'] = _two_Key_NumpadEnter();
        Module['Key']['RightControl'] = _two_Key_RightControl();
        Module['Key']['Mute'] = _two_Key_Mute();
        Module['Key']['NumpadComma'] = _two_Key_NumpadComma();
        Module['Key']['Divide'] = _two_Key_Divide();
        Module['Key']['RightAlt'] = _two_Key_RightAlt();
        Module['Key']['Pause'] = _two_Key_Pause();
        Module['Key']['Home'] = _two_Key_Home();
        Module['Key']['Up'] = _two_Key_Up();
        Module['Key']['PageUp'] = _two_Key_PageUp();
        Module['Key']['Left'] = _two_Key_Left();
        Module['Key']['Right'] = _two_Key_Right();
        Module['Key']['End'] = _two_Key_End();
        Module['Key']['Down'] = _two_Key_Down();
        Module['Key']['PageDown'] = _two_Key_PageDown();
        Module['Key']['Insert'] = _two_Key_Insert();
        Module['Key']['Delete'] = _two_Key_Delete();
        Module['Key']['LeftWin'] = _two_Key_LeftWin();
        Module['Key']['RightWin'] = _two_Key_RightWin();
        Module['Key']['Translated'] = _two_Key_Translated();
        // MouseButtonCode
        Module['LEFT_BUTTON'] = _two_MouseButtonCode_LEFT_BUTTON();
        Module['RIGHT_BUTTON'] = _two_MouseButtonCode_RIGHT_BUTTON();
        Module['MIDDLE_BUTTON'] = _two_MouseButtonCode_MIDDLE_BUTTON();
        Module['NO_BUTTON'] = _two_MouseButtonCode_NO_BUTTON();
        // InputMod
        Module['InputMod'] = Module['InputMod'] || {};
        Module['InputMod']['None'] = _two_InputMod_None();
        Module['InputMod']['Shift'] = _two_InputMod_Shift();
        Module['InputMod']['Ctrl'] = _two_InputMod_Ctrl();
        Module['InputMod']['Alt'] = _two_InputMod_Alt();
        Module['InputMod']['Any'] = _two_InputMod_Any();
        // DeviceType
        Module['DeviceType'] = Module['DeviceType'] || {};
        Module['DeviceType']['None'] = _two_DeviceType_None();
        Module['DeviceType']['Keyboard'] = _two_DeviceType_Keyboard();
        Module['DeviceType']['Mouse'] = _two_DeviceType_Mouse();
        Module['DeviceType']['MouseLeft'] = _two_DeviceType_MouseLeft();
        Module['DeviceType']['MouseRight'] = _two_DeviceType_MouseRight();
        Module['DeviceType']['MouseMiddle'] = _two_DeviceType_MouseMiddle();
        Module['DeviceType']['Touch'] = _two_DeviceType_Touch();
        Module['DeviceType']['Count'] = _two_DeviceType_Count();
        // EventType
        Module['EventType'] = Module['EventType'] || {};
        Module['EventType']['None'] = _two_EventType_None();
        Module['EventType']['Heartbeat'] = _two_EventType_Heartbeat();
        Module['EventType']['Moved'] = _two_EventType_Moved();
        Module['EventType']['Pressed'] = _two_EventType_Pressed();
        Module['EventType']['Released'] = _two_EventType_Released();
        Module['EventType']['Stroked'] = _two_EventType_Stroked();
        Module['EventType']['DoubleStroked'] = _two_EventType_DoubleStroked();
        Module['EventType']['Dragged'] = _two_EventType_Dragged();
        Module['EventType']['DraggedTarget'] = _two_EventType_DraggedTarget();
        Module['EventType']['DragStarted'] = _two_EventType_DragStarted();
        Module['EventType']['DragEnded'] = _two_EventType_DragEnded();
        Module['EventType']['Dropped'] = _two_EventType_Dropped();
        Module['EventType']['Count'] = _two_EventType_Count();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
