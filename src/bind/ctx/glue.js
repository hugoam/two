
// Bindings utilities
function WrapperObject() {
}
// Context
function Context() { throw "cannot construct a Context, no constructor in IDL" }
Context.prototype = Object.create(WrapperObject.prototype);
Context.prototype.constructor = Context;
Context.prototype.__class__ = Context;
Context.__cache__ = {};
Module['Context'] = Context;
Context.prototype["init_input"] = Context.prototype.init_input = function(mouse, keyboard) {
    /* mouse <Mouse> [] */
    mouse = mouse.ptr;
    /* keyboard <Keyboard> [] */
    keyboard = keyboard.ptr;
    _Context_init_input_2(mouse, keyboard);
};
Context.prototype["lock_mouse"] = Context.prototype.lock_mouse = function(locked) {
    /* locked <bool> [] */
    _Context_lock_mouse_1(locked);
};
Context.prototype["next_frame"] = Context.prototype.next_frame = function() {
    return !!(_Context_next_frame_0());
};
Context.prototype["reset"] = Context.prototype.reset = function(width, height) {
    /* width <uint16_t> [] */
    /* height <uint16_t> [] */
    _Context_reset_2(width, height);
};
Object.defineProperty(Context.prototype, "resource_path", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_Context_get_resource_path(self));
    }});
Object.defineProperty(Context.prototype, "title", {
    get: function() {
        var self = this.ptr;
        return Pointer_stringify(_Context_get_title(self));
    },
    set: function(title) {
        var self = this.ptr;
        /* title <std::string> [] */
        if (title && typeof title === "object") title = title.ptr;
        else title = ensureString(title);
        _Context_set_title(self, title);
    }
});
Object.defineProperty(Context.prototype, "width", {
    get: function() {
        var self = this.ptr;
        return _Context_get_width(self);
    },
    set: function(width) {
        var self = this.ptr;
        /* width <unsigned int> [] */
        _Context_set_width(self, width);
    }
});
Object.defineProperty(Context.prototype, "height", {
    get: function() {
        var self = this.ptr;
        return _Context_get_height(self);
    },
    set: function(height) {
        var self = this.ptr;
        /* height <unsigned int> [] */
        _Context_set_height(self, height);
    }
});
Object.defineProperty(Context.prototype, "full_screen", {
    get: function() {
        var self = this.ptr;
        return !!(_Context_get_full_screen(self));
    },
    set: function(full_screen) {
        var self = this.ptr;
        /* full_screen <bool> [] */
        _Context_set_full_screen(self, full_screen);
    }
});
Object.defineProperty(Context.prototype, "active", {
    get: function() {
        var self = this.ptr;
        return !!(_Context_get_active(self));
    },
    set: function(active) {
        var self = this.ptr;
        /* active <bool> [] */
        _Context_set_active(self, active);
    }
});
Object.defineProperty(Context.prototype, "shutdown", {
    get: function() {
        var self = this.ptr;
        return !!(_Context_get_shutdown(self));
    },
    set: function(shutdown) {
        var self = this.ptr;
        /* shutdown <bool> [] */
        _Context_set_shutdown(self, shutdown);
    }
});
Object.defineProperty(Context.prototype, "cursor", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_Context_get_cursor(self), mud::vec2);
    },
    set: function(cursor) {
        var self = this.ptr;
        /* cursor <vec2> [] */
        cursor = cursor.ptr;
        _Context_set_cursor(self, cursor);
    }
});
Object.defineProperty(Context.prototype, "mouse_lock", {
    get: function() {
        var self = this.ptr;
        return !!(_Context_get_mouse_lock(self));
    },
    set: function(mouse_lock) {
        var self = this.ptr;
        /* mouse_lock <bool> [] */
        _Context_set_mouse_lock(self, mouse_lock);
    }
});
Context.prototype["__destroy__"] = Context.prototype.__destroy__ = function() {
    var self = this.ptr;
    _Context___destroy__(self);
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
    _ControlNode___destroy__(self);
};
// InputEvent
function InputEvent() {
    var self = this.ptr;
    this.ptr = _InputEvent_InputEvent_0(self); getCache(InputEvent)[this.ptr] = this;
};
InputEvent.prototype = Object.create(WrapperObject.prototype);
InputEvent.prototype.constructor = InputEvent;
InputEvent.prototype.__class__ = InputEvent;
InputEvent.__cache__ = {};
Module['InputEvent'] = InputEvent;
InputEvent.prototype["consume"] = InputEvent.prototype.consume = function(consumer) {
    /* consumer <ControlNode> [] */
    consumer = consumer.ptr;
    return wrapPointer(_InputEvent_consume_1(consumer), mud::InputEvent);
};
InputEvent.prototype["valid"] = InputEvent.prototype.valid = function() {
    return !!(_InputEvent_valid_0());
};
Object.defineProperty(InputEvent.prototype, "deviceType", {
    get: function() {
        var self = this.ptr;
        return _InputEvent_get_deviceType(self);
    },
    set: function(deviceType) {
        var self = this.ptr;
        /* deviceType <DeviceType> [] */
        if (deviceType && typeof deviceType === "object") deviceType = deviceType.ptr;
        _InputEvent_set_deviceType(self, deviceType);
    }
});
Object.defineProperty(InputEvent.prototype, "eventType", {
    get: function() {
        var self = this.ptr;
        return _InputEvent_get_eventType(self);
    },
    set: function(eventType) {
        var self = this.ptr;
        /* eventType <EventType> [] */
        if (eventType && typeof eventType === "object") eventType = eventType.ptr;
        _InputEvent_set_eventType(self, eventType);
    }
});
Object.defineProperty(InputEvent.prototype, "receiver", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_InputEvent_get_receiver(self), mud::ControlNode);
    },
    set: function(receiver) {
        var self = this.ptr;
        /* receiver <ControlNode> [] */
        receiver = receiver.ptr;
        _InputEvent_set_receiver(self, receiver);
    }
});
Object.defineProperty(InputEvent.prototype, "consumer", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_InputEvent_get_consumer(self), mud::ControlNode);
    },
    set: function(consumer) {
        var self = this.ptr;
        /* consumer <ControlNode> [] */
        consumer = consumer.ptr;
        _InputEvent_set_consumer(self, consumer);
    }
});
Object.defineProperty(InputEvent.prototype, "abort", {
    get: function() {
        var self = this.ptr;
        return !!(_InputEvent_get_abort(self));
    },
    set: function(abort) {
        var self = this.ptr;
        /* abort <bool> [] */
        _InputEvent_set_abort(self, abort);
    }
});
Object.defineProperty(InputEvent.prototype, "modifiers", {
    get: function() {
        var self = this.ptr;
        return _InputEvent_get_modifiers(self);
    },
    set: function(modifiers) {
        var self = this.ptr;
        /* modifiers <InputMod> [] */
        if (modifiers && typeof modifiers === "object") modifiers = modifiers.ptr;
        _InputEvent_set_modifiers(self, modifiers);
    }
});
Object.defineProperty(InputEvent.prototype, "key", {
    get: function() {
        var self = this.ptr;
        return _InputEvent_get_key(self);
    },
    set: function(key) {
        var self = this.ptr;
        /* key <int> [] */
        _InputEvent_set_key(self, key);
    }
});
InputEvent.prototype["__destroy__"] = InputEvent.prototype.__destroy__ = function() {
    var self = this.ptr;
    _InputEvent___destroy__(self);
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
    _Keyboard___destroy__(self);
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
    _Mouse___destroy__(self);
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
    _RenderSystem___destroy__(self);
};
// KeyEvent
function KeyEvent() {
    var self = this.ptr;
    this.ptr = _KeyEvent_KeyEvent_0(self); getCache(KeyEvent)[this.ptr] = this;
};
KeyEvent.prototype = Object.create(WrapperObject.prototype);
KeyEvent.prototype.constructor = KeyEvent;
KeyEvent.prototype.__class__ = KeyEvent;
KeyEvent.__cache__ = {};
Module['KeyEvent'] = KeyEvent;
Object.defineProperty(KeyEvent.prototype, "code", {
    get: function() {
        var self = this.ptr;
        return _KeyEvent_get_code(self);
    },
    set: function(code) {
        var self = this.ptr;
        /* code <Key> [] */
        if (code && typeof code === "object") code = code.ptr;
        _KeyEvent_set_code(self, code);
    }
});
Object.defineProperty(KeyEvent.prototype, "char", {
    get: function() {
        var self = this.ptr;
        return _KeyEvent_get_char(self);
    },
    set: function(char) {
        var self = this.ptr;
        /* char <char> [] */
        _KeyEvent_set_char(self, char);
    }
});
KeyEvent.prototype["__destroy__"] = KeyEvent.prototype.__destroy__ = function() {
    var self = this.ptr;
    _KeyEvent___destroy__(self);
};
// MouseEvent
function MouseEvent() {
    var self = this.ptr;
    this.ptr = _MouseEvent_MouseEvent_0(self); getCache(MouseEvent)[this.ptr] = this;
};
MouseEvent.prototype = Object.create(WrapperObject.prototype);
MouseEvent.prototype.constructor = MouseEvent;
MouseEvent.prototype.__class__ = MouseEvent;
MouseEvent.__cache__ = {};
Module['MouseEvent'] = MouseEvent;
Object.defineProperty(MouseEvent.prototype, "pos", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_MouseEvent_get_pos(self), mud::vec2);
    },
    set: function(pos) {
        var self = this.ptr;
        /* pos <vec2> [] */
        pos = pos.ptr;
        _MouseEvent_set_pos(self, pos);
    }
});
Object.defineProperty(MouseEvent.prototype, "relative", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_MouseEvent_get_relative(self), mud::vec2);
    },
    set: function(relative) {
        var self = this.ptr;
        /* relative <vec2> [] */
        relative = relative.ptr;
        _MouseEvent_set_relative(self, relative);
    }
});
Object.defineProperty(MouseEvent.prototype, "delta", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_MouseEvent_get_delta(self), mud::vec2);
    },
    set: function(delta) {
        var self = this.ptr;
        /* delta <vec2> [] */
        delta = delta.ptr;
        _MouseEvent_set_delta(self, delta);
    }
});
Object.defineProperty(MouseEvent.prototype, "deltaZ", {
    get: function() {
        var self = this.ptr;
        return _MouseEvent_get_deltaZ(self);
    },
    set: function(deltaZ) {
        var self = this.ptr;
        /* deltaZ <float> [] */
        _MouseEvent_set_deltaZ(self, deltaZ);
    }
});
Object.defineProperty(MouseEvent.prototype, "pressed", {
    get: function() {
        var self = this.ptr;
        return wrapPointer(_MouseEvent_get_pressed(self), mud::vec2);
    },
    set: function(pressed) {
        var self = this.ptr;
        /* pressed <vec2> [] */
        pressed = pressed.ptr;
        _MouseEvent_set_pressed(self, pressed);
    }
});
Object.defineProperty(MouseEvent.prototype, "button", {
    get: function() {
        var self = this.ptr;
        return _MouseEvent_get_button(self);
    },
    set: function(button) {
        var self = this.ptr;
        /* button <MouseButtonCode> [] */
        if (button && typeof button === "object") button = button.ptr;
        _MouseEvent_set_button(self, button);
    }
});
MouseEvent.prototype["__destroy__"] = MouseEvent.prototype.__destroy__ = function() {
    var self = this.ptr;
    _MouseEvent___destroy__(self);
};

(function() {
    function setupEnums() {
        // DeviceType
        Module['DeviceType']['None'] = _DeviceType_None();
        Module['DeviceType']['Keyboard'] = _DeviceType_Keyboard();
        Module['DeviceType']['Mouse'] = _DeviceType_Mouse();
        Module['DeviceType']['MouseLeft'] = _DeviceType_MouseLeft();
        Module['DeviceType']['MouseRight'] = _DeviceType_MouseRight();
        Module['DeviceType']['MouseMiddle'] = _DeviceType_MouseMiddle();
        Module['DeviceType']['Touch'] = _DeviceType_Touch();
        Module['DeviceType']['Count'] = _DeviceType_Count();
        // EventType
        Module['EventType']['None'] = _EventType_None();
        Module['EventType']['Heartbeat'] = _EventType_Heartbeat();
        Module['EventType']['Moved'] = _EventType_Moved();
        Module['EventType']['Pressed'] = _EventType_Pressed();
        Module['EventType']['Released'] = _EventType_Released();
        Module['EventType']['Stroked'] = _EventType_Stroked();
        Module['EventType']['DoubleStroked'] = _EventType_DoubleStroked();
        Module['EventType']['Dragged'] = _EventType_Dragged();
        Module['EventType']['DraggedTarget'] = _EventType_DraggedTarget();
        Module['EventType']['DragStarted'] = _EventType_DragStarted();
        Module['EventType']['DragEnded'] = _EventType_DragEnded();
        Module['EventType']['Dropped'] = _EventType_Dropped();
        Module['EventType']['Count'] = _EventType_Count();
        // InputMod
        Module['InputMod']['None'] = _InputMod_None();
        Module['InputMod']['Shift'] = _InputMod_Shift();
        Module['InputMod']['Ctrl'] = _InputMod_Ctrl();
        Module['InputMod']['Alt'] = _InputMod_Alt();
        Module['InputMod']['Any'] = _InputMod_Any();
        // Key
        Module['Key']['Unassigned'] = _Key_Unassigned();
        Module['Key']['Escape'] = _Key_Escape();
        Module['Key']['Num1'] = _Key_Num1();
        Module['Key']['Num2'] = _Key_Num2();
        Module['Key']['Num3'] = _Key_Num3();
        Module['Key']['Num4'] = _Key_Num4();
        Module['Key']['Num5'] = _Key_Num5();
        Module['Key']['Num6'] = _Key_Num6();
        Module['Key']['Num7'] = _Key_Num7();
        Module['Key']['Num8'] = _Key_Num8();
        Module['Key']['Num9'] = _Key_Num9();
        Module['Key']['Num0'] = _Key_Num0();
        Module['Key']['Minus'] = _Key_Minus();
        Module['Key']['Equals'] = _Key_Equals();
        Module['Key']['Back'] = _Key_Back();
        Module['Key']['Tab'] = _Key_Tab();
        Module['Key']['Q'] = _Key_Q();
        Module['Key']['W'] = _Key_W();
        Module['Key']['E'] = _Key_E();
        Module['Key']['R'] = _Key_R();
        Module['Key']['T'] = _Key_T();
        Module['Key']['Y'] = _Key_Y();
        Module['Key']['U'] = _Key_U();
        Module['Key']['I'] = _Key_I();
        Module['Key']['O'] = _Key_O();
        Module['Key']['P'] = _Key_P();
        Module['Key']['LeftBracket'] = _Key_LeftBracket();
        Module['Key']['RightBracket'] = _Key_RightBracket();
        Module['Key']['Return'] = _Key_Return();
        Module['Key']['LeftControl'] = _Key_LeftControl();
        Module['Key']['A'] = _Key_A();
        Module['Key']['S'] = _Key_S();
        Module['Key']['D'] = _Key_D();
        Module['Key']['F'] = _Key_F();
        Module['Key']['G'] = _Key_G();
        Module['Key']['H'] = _Key_H();
        Module['Key']['J'] = _Key_J();
        Module['Key']['K'] = _Key_K();
        Module['Key']['L'] = _Key_L();
        Module['Key']['Semicolon'] = _Key_Semicolon();
        Module['Key']['Apostrophe'] = _Key_Apostrophe();
        Module['Key']['Grave'] = _Key_Grave();
        Module['Key']['LeftShift'] = _Key_LeftShift();
        Module['Key']['Backslash'] = _Key_Backslash();
        Module['Key']['Z'] = _Key_Z();
        Module['Key']['X'] = _Key_X();
        Module['Key']['C'] = _Key_C();
        Module['Key']['V'] = _Key_V();
        Module['Key']['B'] = _Key_B();
        Module['Key']['N'] = _Key_N();
        Module['Key']['M'] = _Key_M();
        Module['Key']['Comma'] = _Key_Comma();
        Module['Key']['Period'] = _Key_Period();
        Module['Key']['Slash'] = _Key_Slash();
        Module['Key']['RightShift'] = _Key_RightShift();
        Module['Key']['Multiply'] = _Key_Multiply();
        Module['Key']['LeftAlt'] = _Key_LeftAlt();
        Module['Key']['Space'] = _Key_Space();
        Module['Key']['Capital'] = _Key_Capital();
        Module['Key']['F1'] = _Key_F1();
        Module['Key']['F2'] = _Key_F2();
        Module['Key']['F3'] = _Key_F3();
        Module['Key']['F4'] = _Key_F4();
        Module['Key']['F5'] = _Key_F5();
        Module['Key']['F6'] = _Key_F6();
        Module['Key']['F7'] = _Key_F7();
        Module['Key']['F8'] = _Key_F8();
        Module['Key']['F9'] = _Key_F9();
        Module['Key']['F10'] = _Key_F10();
        Module['Key']['Numlock'] = _Key_Numlock();
        Module['Key']['ScrollLock'] = _Key_ScrollLock();
        Module['Key']['Numpad7'] = _Key_Numpad7();
        Module['Key']['Numpad8'] = _Key_Numpad8();
        Module['Key']['Numpad9'] = _Key_Numpad9();
        Module['Key']['Subtract'] = _Key_Subtract();
        Module['Key']['Numpad4'] = _Key_Numpad4();
        Module['Key']['Numpad5'] = _Key_Numpad5();
        Module['Key']['Numpad6'] = _Key_Numpad6();
        Module['Key']['Add'] = _Key_Add();
        Module['Key']['Numpad1'] = _Key_Numpad1();
        Module['Key']['Numpad2'] = _Key_Numpad2();
        Module['Key']['Numpad3'] = _Key_Numpad3();
        Module['Key']['Numpad0'] = _Key_Numpad0();
        Module['Key']['Decimal'] = _Key_Decimal();
        Module['Key']['F11'] = _Key_F11();
        Module['Key']['F12'] = _Key_F12();
        Module['Key']['F13'] = _Key_F13();
        Module['Key']['F14'] = _Key_F14();
        Module['Key']['F15'] = _Key_F15();
        Module['Key']['NumpadEquals'] = _Key_NumpadEquals();
        Module['Key']['NumpadEnter'] = _Key_NumpadEnter();
        Module['Key']['RightControl'] = _Key_RightControl();
        Module['Key']['Mute'] = _Key_Mute();
        Module['Key']['NumpadComma'] = _Key_NumpadComma();
        Module['Key']['Divide'] = _Key_Divide();
        Module['Key']['RightAlt'] = _Key_RightAlt();
        Module['Key']['Pause'] = _Key_Pause();
        Module['Key']['Home'] = _Key_Home();
        Module['Key']['Up'] = _Key_Up();
        Module['Key']['PageUp'] = _Key_PageUp();
        Module['Key']['Left'] = _Key_Left();
        Module['Key']['Right'] = _Key_Right();
        Module['Key']['End'] = _Key_End();
        Module['Key']['Down'] = _Key_Down();
        Module['Key']['PageDown'] = _Key_PageDown();
        Module['Key']['Insert'] = _Key_Insert();
        Module['Key']['Delete'] = _Key_Delete();
        Module['Key']['LeftWin'] = _Key_LeftWin();
        Module['Key']['RightWin'] = _Key_RightWin();
        Module['Key']['Translated'] = _Key_Translated();
        // MouseButtonCode
        Module['LEFT_BUTTON'] = _MouseButtonCode_LEFT_BUTTON();
        Module['RIGHT_BUTTON'] = _MouseButtonCode_RIGHT_BUTTON();
        Module['MIDDLE_BUTTON'] = _MouseButtonCode_MIDDLE_BUTTON();
        Module['NO_BUTTON'] = _MouseButtonCode_NO_BUTTON();
    }
    if (Module['calledRun']) setupEnums();
    else addOnPreMain(setupEnums);
})();
