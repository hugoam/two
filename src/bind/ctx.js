// Context
function Context() { throw "cannot construct a Context, no constructor in IDL" }
Context.prototype = Object.create(WrapperObject.prototype);
Context.prototype.constructor = Context;
Context.prototype.__class__ = Context;
Context.__cache__ = {};
Module['Context'] = Context;
Context.prototype["reset_fb"] = Context.prototype.reset_fb = function(a0) {
    var self = this.ptr;
    _mud_Context_reset_fb_1(self, /*size*/a0.ptr);
};
Context.prototype["init_input"] = Context.prototype.init_input = function(a0, a1) {
    var self = this.ptr;
    _mud_Context_init_input_2(self, /*mouse*/a0.ptr, /*keyboard*/a1.ptr);
};
Context.prototype["next_frame"] = Context.prototype.next_frame = function() {
    var self = this.ptr;
    return !!(_mud_Context_next_frame_0(self));
};
Context.prototype["lock_mouse"] = Context.prototype.lock_mouse = function(a0) {
    var self = this.ptr;
    _mud_Context_lock_mouse_1(self, /*locked*/a0);
};
Object.defineProperty(Context.prototype, "resource_path", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Context__get_resource_path(self));
    }});
Object.defineProperty(Context.prototype, "title", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_mud_Context__get_title(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Context__set_title(self, ensureString(value));
    }
});
Object.defineProperty(Context.prototype, "size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Context__get_size(self), v2_uint);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Context__set_size(self, value.ptr);
    }
});
Object.defineProperty(Context.prototype, "fb_size", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Context__get_fb_size(self), v2_uint);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Context__set_fb_size(self, value.ptr);
    }
});
Object.defineProperty(Context.prototype, "full_screen", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Context__get_full_screen(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Context__set_full_screen(self, value);
    }
});
Object.defineProperty(Context.prototype, "pixel_ratio", {
    get: function() {
        var self = this.ptr;
        return _mud_Context__get_pixel_ratio(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Context__set_pixel_ratio(self, value);
    }
});
Object.defineProperty(Context.prototype, "active", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Context__get_active(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Context__set_active(self, value);
    }
});
Object.defineProperty(Context.prototype, "shutdown", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Context__get_shutdown(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Context__set_shutdown(self, value);
    }
});
Object.defineProperty(Context.prototype, "cursor", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_Context__get_cursor(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Context__set_cursor(self, value.ptr);
    }
});
Object.defineProperty(Context.prototype, "mouse_lock", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_Context__get_mouse_lock(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_Context__set_mouse_lock(self, value);
    }
});
Context.prototype["__destroy__"] = Context.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Context__destroy(self);
};
// ControlNode
function ControlNode() { throw "cannot construct a ControlNode, no constructor in IDL" }
ControlNode.prototype = Object.create(WrapperObject.prototype);
ControlNode.prototype.constructor = ControlNode;
ControlNode.prototype.__class__ = ControlNode;
ControlNode.__cache__ = {};
Module['ControlNode'] = ControlNode;
ControlNode.prototype["__destroy__"] = ControlNode.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_ControlNode__destroy(self);
};
// InputEvent
function InputEvent() {
    this.ptr = _mud_InputEvent__construct_0(); this.type = InputEvent; getCache(InputEvent)[this.ptr] = this;
};
InputEvent.prototype = Object.create(WrapperObject.prototype);
InputEvent.prototype.constructor = InputEvent;
InputEvent.prototype.__class__ = InputEvent;
InputEvent.__cache__ = {};
Module['InputEvent'] = InputEvent;
InputEvent.prototype["consume"] = InputEvent.prototype.consume = function(a0) {
    var self = this.ptr;
    return wrapPointer(_mud_InputEvent_consume_1(self, /*consumer*/a0.ptr), InputEvent);
};
InputEvent.prototype["valid"] = InputEvent.prototype.valid = function() {
    var self = this.ptr;
    return !!(_mud_InputEvent_valid_0(self));
};
Object.defineProperty(InputEvent.prototype, "deviceType", {
    get: function() {
        var self = this.ptr;
        return _mud_InputEvent__get_deviceType(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InputEvent__set_deviceType(self, value);
    }
});
Object.defineProperty(InputEvent.prototype, "eventType", {
    get: function() {
        var self = this.ptr;
        return _mud_InputEvent__get_eventType(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InputEvent__set_eventType(self, value);
    }
});
Object.defineProperty(InputEvent.prototype, "receiver", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InputEvent__get_receiver(self), ControlNode);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InputEvent__set_receiver(self, value.ptr);
    }
});
Object.defineProperty(InputEvent.prototype, "consumer", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_InputEvent__get_consumer(self), ControlNode);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InputEvent__set_consumer(self, value.ptr);
    }
});
Object.defineProperty(InputEvent.prototype, "abort", {
    get: function() {
        var self = this.ptr;
        return !!(_mud_InputEvent__get_abort(self));
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InputEvent__set_abort(self, value);
    }
});
Object.defineProperty(InputEvent.prototype, "modifiers", {
    get: function() {
        var self = this.ptr;
        return _mud_InputEvent__get_modifiers(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InputEvent__set_modifiers(self, value);
    }
});
Object.defineProperty(InputEvent.prototype, "key", {
    get: function() {
        var self = this.ptr;
        return _mud_InputEvent__get_key(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_InputEvent__set_key(self, value);
    }
});
InputEvent.prototype["__destroy__"] = InputEvent.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_InputEvent__destroy(self);
};
// Keyboard
function Keyboard() { throw "cannot construct a Keyboard, no constructor in IDL" }
Keyboard.prototype = Object.create(WrapperObject.prototype);
Keyboard.prototype.constructor = Keyboard;
Keyboard.prototype.__class__ = Keyboard;
Keyboard.__cache__ = {};
Module['Keyboard'] = Keyboard;
Keyboard.prototype["__destroy__"] = Keyboard.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Keyboard__destroy(self);
};
// Mouse
function Mouse() { throw "cannot construct a Mouse, no constructor in IDL" }
Mouse.prototype = Object.create(WrapperObject.prototype);
Mouse.prototype.constructor = Mouse;
Mouse.prototype.__class__ = Mouse;
Mouse.__cache__ = {};
Module['Mouse'] = Mouse;
Mouse.prototype["__destroy__"] = Mouse.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_Mouse__destroy(self);
};
// RenderSystem
function RenderSystem() { throw "cannot construct a RenderSystem, no constructor in IDL" }
RenderSystem.prototype = Object.create(WrapperObject.prototype);
RenderSystem.prototype.constructor = RenderSystem;
RenderSystem.prototype.__class__ = RenderSystem;
RenderSystem.__cache__ = {};
Module['RenderSystem'] = RenderSystem;
RenderSystem.prototype["__destroy__"] = RenderSystem.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_RenderSystem__destroy(self);
};
// KeyEvent
function KeyEvent() {
    this.ptr = _mud_KeyEvent__construct_0(); this.type = KeyEvent; getCache(KeyEvent)[this.ptr] = this;
};
KeyEvent.prototype = Object.create(InputEvent.prototype);
KeyEvent.prototype.constructor = KeyEvent;
KeyEvent.prototype.__class__ = KeyEvent;
KeyEvent.__cache__ = {};
Module['KeyEvent'] = KeyEvent;
Object.defineProperty(KeyEvent.prototype, "code", {
    get: function() {
        var self = this.ptr;
        return _mud_KeyEvent__get_code(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_KeyEvent__set_code(self, value);
    }
});
Object.defineProperty(KeyEvent.prototype, "char", {
    get: function() {
        var self = this.ptr;
        return _mud_KeyEvent__get_char(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_KeyEvent__set_char(self, value);
    }
});
KeyEvent.prototype["__destroy__"] = KeyEvent.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_KeyEvent__destroy(self);
};
// MouseEvent
function MouseEvent() {
    this.ptr = _mud_MouseEvent__construct_0(); this.type = MouseEvent; getCache(MouseEvent)[this.ptr] = this;
};
MouseEvent.prototype = Object.create(InputEvent.prototype);
MouseEvent.prototype.constructor = MouseEvent;
MouseEvent.prototype.__class__ = MouseEvent;
MouseEvent.__cache__ = {};
Module['MouseEvent'] = MouseEvent;
Object.defineProperty(MouseEvent.prototype, "pos", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_MouseEvent__get_pos(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_MouseEvent__set_pos(self, value.ptr);
    }
});
Object.defineProperty(MouseEvent.prototype, "relative", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_MouseEvent__get_relative(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_MouseEvent__set_relative(self, value.ptr);
    }
});
Object.defineProperty(MouseEvent.prototype, "delta", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_MouseEvent__get_delta(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_MouseEvent__set_delta(self, value.ptr);
    }
});
Object.defineProperty(MouseEvent.prototype, "deltaZ", {
    get: function() {
        var self = this.ptr;
        return _mud_MouseEvent__get_deltaZ(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_MouseEvent__set_deltaZ(self, value);
    }
});
Object.defineProperty(MouseEvent.prototype, "pressed", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_mud_MouseEvent__get_pressed(self), v2_float);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_MouseEvent__set_pressed(self, value.ptr);
    }
});
Object.defineProperty(MouseEvent.prototype, "button", {
    get: function() {
        var self = this.ptr;
        return _mud_MouseEvent__get_button(self);
    },
    set: function(value) {
        var self = this.ptr;
        _mud_MouseEvent__set_button(self, value);
    }
});
MouseEvent.prototype["__destroy__"] = MouseEvent.prototype.__destroy__ = function() {
    var self = this.ptr;
    _mud_MouseEvent__destroy(self);
};

(function() {
    function setup() {
        Context.__type__ = _mud_Context__type();
        ControlNode.__type__ = _mud_ControlNode__type();
        InputEvent.__type__ = _mud_InputEvent__type();
        Keyboard.__type__ = _mud_Keyboard__type();
        Mouse.__type__ = _mud_Mouse__type();
        RenderSystem.__type__ = _mud_RenderSystem__type();
        KeyEvent.__type__ = _mud_KeyEvent__type();
        MouseEvent.__type__ = _mud_MouseEvent__type();
        // DeviceType
        Module['DeviceType'] = Module['DeviceType'] || {};
        Module['DeviceType']['None'] = _mud_DeviceType_None();
        Module['DeviceType']['Keyboard'] = _mud_DeviceType_Keyboard();
        Module['DeviceType']['Mouse'] = _mud_DeviceType_Mouse();
        Module['DeviceType']['MouseLeft'] = _mud_DeviceType_MouseLeft();
        Module['DeviceType']['MouseRight'] = _mud_DeviceType_MouseRight();
        Module['DeviceType']['MouseMiddle'] = _mud_DeviceType_MouseMiddle();
        Module['DeviceType']['Touch'] = _mud_DeviceType_Touch();
        Module['DeviceType']['Count'] = _mud_DeviceType_Count();
        // EventType
        Module['EventType'] = Module['EventType'] || {};
        Module['EventType']['None'] = _mud_EventType_None();
        Module['EventType']['Heartbeat'] = _mud_EventType_Heartbeat();
        Module['EventType']['Moved'] = _mud_EventType_Moved();
        Module['EventType']['Pressed'] = _mud_EventType_Pressed();
        Module['EventType']['Released'] = _mud_EventType_Released();
        Module['EventType']['Stroked'] = _mud_EventType_Stroked();
        Module['EventType']['DoubleStroked'] = _mud_EventType_DoubleStroked();
        Module['EventType']['Dragged'] = _mud_EventType_Dragged();
        Module['EventType']['DraggedTarget'] = _mud_EventType_DraggedTarget();
        Module['EventType']['DragStarted'] = _mud_EventType_DragStarted();
        Module['EventType']['DragEnded'] = _mud_EventType_DragEnded();
        Module['EventType']['Dropped'] = _mud_EventType_Dropped();
        Module['EventType']['Count'] = _mud_EventType_Count();
        // InputMod
        Module['InputMod'] = Module['InputMod'] || {};
        Module['InputMod']['None'] = _mud_InputMod_None();
        Module['InputMod']['Shift'] = _mud_InputMod_Shift();
        Module['InputMod']['Ctrl'] = _mud_InputMod_Ctrl();
        Module['InputMod']['Alt'] = _mud_InputMod_Alt();
        Module['InputMod']['Any'] = _mud_InputMod_Any();
        // Key
        Module['Key'] = Module['Key'] || {};
        Module['Key']['Unassigned'] = _mud_Key_Unassigned();
        Module['Key']['Escape'] = _mud_Key_Escape();
        Module['Key']['Num1'] = _mud_Key_Num1();
        Module['Key']['Num2'] = _mud_Key_Num2();
        Module['Key']['Num3'] = _mud_Key_Num3();
        Module['Key']['Num4'] = _mud_Key_Num4();
        Module['Key']['Num5'] = _mud_Key_Num5();
        Module['Key']['Num6'] = _mud_Key_Num6();
        Module['Key']['Num7'] = _mud_Key_Num7();
        Module['Key']['Num8'] = _mud_Key_Num8();
        Module['Key']['Num9'] = _mud_Key_Num9();
        Module['Key']['Num0'] = _mud_Key_Num0();
        Module['Key']['Minus'] = _mud_Key_Minus();
        Module['Key']['Equals'] = _mud_Key_Equals();
        Module['Key']['Back'] = _mud_Key_Back();
        Module['Key']['Tab'] = _mud_Key_Tab();
        Module['Key']['Q'] = _mud_Key_Q();
        Module['Key']['W'] = _mud_Key_W();
        Module['Key']['E'] = _mud_Key_E();
        Module['Key']['R'] = _mud_Key_R();
        Module['Key']['T'] = _mud_Key_T();
        Module['Key']['Y'] = _mud_Key_Y();
        Module['Key']['U'] = _mud_Key_U();
        Module['Key']['I'] = _mud_Key_I();
        Module['Key']['O'] = _mud_Key_O();
        Module['Key']['P'] = _mud_Key_P();
        Module['Key']['LeftBracket'] = _mud_Key_LeftBracket();
        Module['Key']['RightBracket'] = _mud_Key_RightBracket();
        Module['Key']['Return'] = _mud_Key_Return();
        Module['Key']['LeftControl'] = _mud_Key_LeftControl();
        Module['Key']['A'] = _mud_Key_A();
        Module['Key']['S'] = _mud_Key_S();
        Module['Key']['D'] = _mud_Key_D();
        Module['Key']['F'] = _mud_Key_F();
        Module['Key']['G'] = _mud_Key_G();
        Module['Key']['H'] = _mud_Key_H();
        Module['Key']['J'] = _mud_Key_J();
        Module['Key']['K'] = _mud_Key_K();
        Module['Key']['L'] = _mud_Key_L();
        Module['Key']['Semicolon'] = _mud_Key_Semicolon();
        Module['Key']['Apostrophe'] = _mud_Key_Apostrophe();
        Module['Key']['Grave'] = _mud_Key_Grave();
        Module['Key']['LeftShift'] = _mud_Key_LeftShift();
        Module['Key']['Backslash'] = _mud_Key_Backslash();
        Module['Key']['Z'] = _mud_Key_Z();
        Module['Key']['X'] = _mud_Key_X();
        Module['Key']['C'] = _mud_Key_C();
        Module['Key']['V'] = _mud_Key_V();
        Module['Key']['B'] = _mud_Key_B();
        Module['Key']['N'] = _mud_Key_N();
        Module['Key']['M'] = _mud_Key_M();
        Module['Key']['Comma'] = _mud_Key_Comma();
        Module['Key']['Period'] = _mud_Key_Period();
        Module['Key']['Slash'] = _mud_Key_Slash();
        Module['Key']['RightShift'] = _mud_Key_RightShift();
        Module['Key']['Multiply'] = _mud_Key_Multiply();
        Module['Key']['LeftAlt'] = _mud_Key_LeftAlt();
        Module['Key']['Space'] = _mud_Key_Space();
        Module['Key']['Capital'] = _mud_Key_Capital();
        Module['Key']['F1'] = _mud_Key_F1();
        Module['Key']['F2'] = _mud_Key_F2();
        Module['Key']['F3'] = _mud_Key_F3();
        Module['Key']['F4'] = _mud_Key_F4();
        Module['Key']['F5'] = _mud_Key_F5();
        Module['Key']['F6'] = _mud_Key_F6();
        Module['Key']['F7'] = _mud_Key_F7();
        Module['Key']['F8'] = _mud_Key_F8();
        Module['Key']['F9'] = _mud_Key_F9();
        Module['Key']['F10'] = _mud_Key_F10();
        Module['Key']['Numlock'] = _mud_Key_Numlock();
        Module['Key']['ScrollLock'] = _mud_Key_ScrollLock();
        Module['Key']['Numpad7'] = _mud_Key_Numpad7();
        Module['Key']['Numpad8'] = _mud_Key_Numpad8();
        Module['Key']['Numpad9'] = _mud_Key_Numpad9();
        Module['Key']['Subtract'] = _mud_Key_Subtract();
        Module['Key']['Numpad4'] = _mud_Key_Numpad4();
        Module['Key']['Numpad5'] = _mud_Key_Numpad5();
        Module['Key']['Numpad6'] = _mud_Key_Numpad6();
        Module['Key']['Add'] = _mud_Key_Add();
        Module['Key']['Numpad1'] = _mud_Key_Numpad1();
        Module['Key']['Numpad2'] = _mud_Key_Numpad2();
        Module['Key']['Numpad3'] = _mud_Key_Numpad3();
        Module['Key']['Numpad0'] = _mud_Key_Numpad0();
        Module['Key']['Decimal'] = _mud_Key_Decimal();
        Module['Key']['F11'] = _mud_Key_F11();
        Module['Key']['F12'] = _mud_Key_F12();
        Module['Key']['F13'] = _mud_Key_F13();
        Module['Key']['F14'] = _mud_Key_F14();
        Module['Key']['F15'] = _mud_Key_F15();
        Module['Key']['NumpadEquals'] = _mud_Key_NumpadEquals();
        Module['Key']['NumpadEnter'] = _mud_Key_NumpadEnter();
        Module['Key']['RightControl'] = _mud_Key_RightControl();
        Module['Key']['Mute'] = _mud_Key_Mute();
        Module['Key']['NumpadComma'] = _mud_Key_NumpadComma();
        Module['Key']['Divide'] = _mud_Key_Divide();
        Module['Key']['RightAlt'] = _mud_Key_RightAlt();
        Module['Key']['Pause'] = _mud_Key_Pause();
        Module['Key']['Home'] = _mud_Key_Home();
        Module['Key']['Up'] = _mud_Key_Up();
        Module['Key']['PageUp'] = _mud_Key_PageUp();
        Module['Key']['Left'] = _mud_Key_Left();
        Module['Key']['Right'] = _mud_Key_Right();
        Module['Key']['End'] = _mud_Key_End();
        Module['Key']['Down'] = _mud_Key_Down();
        Module['Key']['PageDown'] = _mud_Key_PageDown();
        Module['Key']['Insert'] = _mud_Key_Insert();
        Module['Key']['Delete'] = _mud_Key_Delete();
        Module['Key']['LeftWin'] = _mud_Key_LeftWin();
        Module['Key']['RightWin'] = _mud_Key_RightWin();
        Module['Key']['Translated'] = _mud_Key_Translated();
        // MouseButtonCode
        Module['LEFT_BUTTON'] = _mud_MouseButtonCode_LEFT_BUTTON();
        Module['RIGHT_BUTTON'] = _mud_MouseButtonCode_RIGHT_BUTTON();
        Module['MIDDLE_BUTTON'] = _mud_MouseButtonCode_MIDDLE_BUTTON();
        Module['NO_BUTTON'] = _mud_MouseButtonCode_NO_BUTTON();
    }
    if (Module['calledRun']) setup();
    else addOnPreMain(setup);
})();
