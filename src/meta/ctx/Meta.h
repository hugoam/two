#pragma once

#ifndef MUD_MODULES
#include <meta/ctx/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_ctx_meta(Module& m)
    {
    UNUSED(m);
    
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::DeviceType>(), &namspc({ "mud" }), "DeviceType", sizeof(mud::DeviceType), TypeClass::Enum };
        static Enum enu = { type<mud::DeviceType>(),
            true,
            { "None", "Keyboard", "Mouse", "MouseLeft", "MouseRight", "MouseMiddle", "Touch", "Count" },
            { 0, 1, 2, 3, 4, 5, 6, 7 },
            { var(mud::DeviceType::None), var(mud::DeviceType::Keyboard), var(mud::DeviceType::Mouse), var(mud::DeviceType::MouseLeft), var(mud::DeviceType::MouseRight), var(mud::DeviceType::MouseMiddle), var(mud::DeviceType::Touch), var(mud::DeviceType::Count) }
        };
        meta_enum<mud::DeviceType>();
    }
    {
        static Meta meta = { type<mud::EventType>(), &namspc({ "mud" }), "EventType", sizeof(mud::EventType), TypeClass::Enum };
        static Enum enu = { type<mud::EventType>(),
            true,
            { "None", "Heartbeat", "Moved", "Pressed", "Released", "Stroked", "DoubleStroked", "Dragged", "DraggedTarget", "DragStarted", "DragEnded", "Dropped", "Count" },
            { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
            { var(mud::EventType::None), var(mud::EventType::Heartbeat), var(mud::EventType::Moved), var(mud::EventType::Pressed), var(mud::EventType::Released), var(mud::EventType::Stroked), var(mud::EventType::DoubleStroked), var(mud::EventType::Dragged), var(mud::EventType::DraggedTarget), var(mud::EventType::DragStarted), var(mud::EventType::DragEnded), var(mud::EventType::Dropped), var(mud::EventType::Count) }
        };
        meta_enum<mud::EventType>();
    }
    {
        static Meta meta = { type<mud::InputMod>(), &namspc({ "mud" }), "InputMod", sizeof(mud::InputMod), TypeClass::Enum };
        static Enum enu = { type<mud::InputMod>(),
            true,
            { "None", "Shift", "Ctrl", "Alt", "Any" },
            { 0, 1, 2, 4, 7 },
            { var(mud::InputMod::None), var(mud::InputMod::Shift), var(mud::InputMod::Ctrl), var(mud::InputMod::Alt), var(mud::InputMod::Any) }
        };
        meta_enum<mud::InputMod>();
    }
    {
        static Meta meta = { type<mud::Key>(), &namspc({ "mud" }), "Key", sizeof(mud::Key), TypeClass::Enum };
        static Enum enu = { type<mud::Key>(),
            true,
            { "Unassigned", "Escape", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "Num0", "Minus", "Equals", "Back", "Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "LeftBracket", "RightBracket", "Return", "LeftControl", "A", "S", "D", "F", "G", "H", "J", "K", "L", "Semicolon", "Apostrophe", "Grave", "LeftShift", "Backslash", "Z", "X", "C", "V", "B", "N", "M", "Comma", "Period", "Slash", "RightShift", "Multiply", "LeftAlt", "Space", "Capital", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "Numlock", "ScrollLock", "Numpad7", "Numpad8", "Numpad9", "Subtract", "Numpad4", "Numpad5", "Numpad6", "Add", "Numpad1", "Numpad2", "Numpad3", "Numpad0", "Decimal", "F11", "F12", "F13", "F14", "F15", "NumpadEquals", "NumpadEnter", "RightControl", "Mute", "NumpadComma", "Divide", "RightAlt", "Pause", "Home", "Up", "PageUp", "Left", "Right", "End", "Down", "PageDown", "Insert", "Delete", "LeftWin", "RightWin", "Translated" },
            { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 87, 88, 100, 101, 102, 141, 156, 157, 160, 179, 181, 184, 197, 199, 200, 201, 203, 205, 207, 208, 209, 210, 211, 219, 220, uint16_t(1 << 15) },
            { var(mud::Key::Unassigned), var(mud::Key::Escape), var(mud::Key::Num1), var(mud::Key::Num2), var(mud::Key::Num3), var(mud::Key::Num4), var(mud::Key::Num5), var(mud::Key::Num6), var(mud::Key::Num7), var(mud::Key::Num8), var(mud::Key::Num9), var(mud::Key::Num0), var(mud::Key::Minus), var(mud::Key::Equals), var(mud::Key::Back), var(mud::Key::Tab), var(mud::Key::Q), var(mud::Key::W), var(mud::Key::E), var(mud::Key::R), var(mud::Key::T), var(mud::Key::Y), var(mud::Key::U), var(mud::Key::I), var(mud::Key::O), var(mud::Key::P), var(mud::Key::LeftBracket), var(mud::Key::RightBracket), var(mud::Key::Return), var(mud::Key::LeftControl), var(mud::Key::A), var(mud::Key::S), var(mud::Key::D), var(mud::Key::F), var(mud::Key::G), var(mud::Key::H), var(mud::Key::J), var(mud::Key::K), var(mud::Key::L), var(mud::Key::Semicolon), var(mud::Key::Apostrophe), var(mud::Key::Grave), var(mud::Key::LeftShift), var(mud::Key::Backslash), var(mud::Key::Z), var(mud::Key::X), var(mud::Key::C), var(mud::Key::V), var(mud::Key::B), var(mud::Key::N), var(mud::Key::M), var(mud::Key::Comma), var(mud::Key::Period), var(mud::Key::Slash), var(mud::Key::RightShift), var(mud::Key::Multiply), var(mud::Key::LeftAlt), var(mud::Key::Space), var(mud::Key::Capital), var(mud::Key::F1), var(mud::Key::F2), var(mud::Key::F3), var(mud::Key::F4), var(mud::Key::F5), var(mud::Key::F6), var(mud::Key::F7), var(mud::Key::F8), var(mud::Key::F9), var(mud::Key::F10), var(mud::Key::Numlock), var(mud::Key::ScrollLock), var(mud::Key::Numpad7), var(mud::Key::Numpad8), var(mud::Key::Numpad9), var(mud::Key::Subtract), var(mud::Key::Numpad4), var(mud::Key::Numpad5), var(mud::Key::Numpad6), var(mud::Key::Add), var(mud::Key::Numpad1), var(mud::Key::Numpad2), var(mud::Key::Numpad3), var(mud::Key::Numpad0), var(mud::Key::Decimal), var(mud::Key::F11), var(mud::Key::F12), var(mud::Key::F13), var(mud::Key::F14), var(mud::Key::F15), var(mud::Key::NumpadEquals), var(mud::Key::NumpadEnter), var(mud::Key::RightControl), var(mud::Key::Mute), var(mud::Key::NumpadComma), var(mud::Key::Divide), var(mud::Key::RightAlt), var(mud::Key::Pause), var(mud::Key::Home), var(mud::Key::Up), var(mud::Key::PageUp), var(mud::Key::Left), var(mud::Key::Right), var(mud::Key::End), var(mud::Key::Down), var(mud::Key::PageDown), var(mud::Key::Insert), var(mud::Key::Delete), var(mud::Key::LeftWin), var(mud::Key::RightWin), var(mud::Key::Translated) }
        };
        meta_enum<mud::Key>();
    }
    {
        static Meta meta = { type<mud::MouseButtonCode>(), &namspc({ "mud" }), "MouseButtonCode", sizeof(mud::MouseButtonCode), TypeClass::Enum };
        static Enum enu = { type<mud::MouseButtonCode>(),
            false,
            { "LEFT_BUTTON", "RIGHT_BUTTON", "MIDDLE_BUTTON", "NO_BUTTON" },
            { 0, 1, 2, 3 },
            { var(mud::LEFT_BUTTON), var(mud::RIGHT_BUTTON), var(mud::MIDDLE_BUTTON), var(mud::NO_BUTTON) }
        };
        meta_enum<mud::MouseButtonCode>();
    }
    
    // Sequences
    
    // mud::Context
    {
        static Meta meta = { type<mud::Context>(), &namspc({ "mud" }), "Context", sizeof(mud::Context), TypeClass::Object };
        static Class cls = { type<mud::Context>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Context>(), member_address(&mud::Context::m_resource_path), type<string>(), "resource_path", var(string()), Member::Flags(Member::Value|Member::NonMutable), nullptr },
                { type<mud::Context>(), member_address(&mud::Context::m_title), type<string>(), "title", var(string()), Member::Value, nullptr },
                { type<mud::Context>(), member_address(&mud::Context::m_width), type<uint>(), "width", var(unsigned int()), Member::Value, nullptr },
                { type<mud::Context>(), member_address(&mud::Context::m_height), type<uint>(), "height", var(unsigned int()), Member::Value, nullptr },
                { type<mud::Context>(), member_address(&mud::Context::m_full_screen), type<bool>(), "full_screen", var(bool()), Member::Value, nullptr },
                { type<mud::Context>(), member_address(&mud::Context::m_active), type<bool>(), "active", var(bool(true)), Member::Value, nullptr },
                { type<mud::Context>(), member_address(&mud::Context::m_shutdown), type<bool>(), "shutdown", var(bool(false)), Member::Value, nullptr },
                { type<mud::Context>(), member_address(&mud::Context::m_cursor), type<mud::vec2>(), "cursor", var(mud::vec2()), Member::Value, nullptr },
                { type<mud::Context>(), member_address(&mud::Context::m_mouse_lock), type<bool>(), "mouse_lock", var(bool(false)), Member::Value, nullptr }
            },
            // methods
            {
                { type<mud::Context>(), "reset", member_address<void(mud::Context::*)(uint16_t, uint16_t)>(&mud::Context::reset), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Context>(object).reset(val<uint16_t>(args[0]), val<uint16_t>(args[1])); }, { { "width", var(uint16_t()) }, { "height", var(uint16_t()) } }, Var() },
                { type<mud::Context>(), "init_input", member_address<void(mud::Context::*)(mud::Mouse&, mud::Keyboard&)>(&mud::Context::init_input), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Context>(object).init_input(val<mud::Mouse>(args[0]), val<mud::Keyboard>(args[1])); }, { { "mouse", Ref(type<mud::Mouse>()) }, { "keyboard", Ref(type<mud::Keyboard>()) } }, Var() },
                { type<mud::Context>(), "next_frame", member_address<bool(mud::Context::*)()>(&mud::Context::next_frame), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<bool>(result) = val<mud::Context>(object).next_frame(); }, {}, var(bool()) },
                { type<mud::Context>(), "lock_mouse", member_address<void(mud::Context::*)(bool)>(&mud::Context::lock_mouse), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Context>(object).lock_mouse(val<bool>(args[0])); }, { { "locked", var(bool()) } }, Var() }
            },
            // static members
            {
            }
        };
        meta_class<mud::Context>();
    }
    // mud::ControlNode
    {
        static Meta meta = { type<mud::ControlNode>(), &namspc({ "mud" }), "ControlNode", sizeof(mud::ControlNode), TypeClass::Object };
        static Class cls = { type<mud::ControlNode>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::ControlNode>();
    }
    // mud::InputEvent
    {
        static Meta meta = { type<mud::InputEvent>(), &namspc({ "mud" }), "InputEvent", sizeof(mud::InputEvent), TypeClass::Struct };
        static Class cls = { type<mud::InputEvent>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::InputEvent>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::InputEvent>(ref)) mud::InputEvent(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::InputEvent>(), [](Ref ref, Ref other) { new(&val<mud::InputEvent>(ref)) mud::InputEvent(val<mud::InputEvent>(other)); } }
            },
            // members
            {
                { type<mud::InputEvent>(), member_address(&mud::InputEvent::m_deviceType), type<mud::DeviceType>(), "deviceType", var(mud::DeviceType::None), Member::Value, nullptr },
                { type<mud::InputEvent>(), member_address(&mud::InputEvent::m_eventType), type<mud::EventType>(), "eventType", var(mud::EventType::None), Member::Value, nullptr },
                { type<mud::InputEvent>(), member_address(&mud::InputEvent::m_receiver), type<mud::ControlNode>(), "receiver", Ref(type<mud::ControlNode>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::InputEvent>(), member_address(&mud::InputEvent::m_consumer), type<mud::ControlNode>(), "consumer", Ref(type<mud::ControlNode>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::InputEvent>(), member_address(&mud::InputEvent::m_abort), type<bool>(), "abort", var(bool(false)), Member::Value, nullptr },
                { type<mud::InputEvent>(), member_address(&mud::InputEvent::m_modifiers), type<mud::InputMod>(), "modifiers", var(mud::InputMod::None), Member::Value, nullptr },
                { type<mud::InputEvent>(), member_address(&mud::InputEvent::m_key), type<int>(), "key", var(int()), Member::Value, nullptr }
            },
            // methods
            {
                { type<mud::InputEvent>(), "consume", member_address<mud::InputEvent&(mud::InputEvent::*)(mud::ControlNode&)>(&mud::InputEvent::consume), [](Ref object, array<Var> args, Var& result) { val<mud::InputEvent>(result) = val<mud::InputEvent>(object).consume(val<mud::ControlNode>(args[0])); }, { { "consumer", Ref(type<mud::ControlNode>()) } }, var(mud::InputEvent()) },
                { type<mud::InputEvent>(), "valid", member_address<bool(mud::InputEvent::*)()>(&mud::InputEvent::valid), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<bool>(result) = val<mud::InputEvent>(object).valid(); }, {}, var(bool()) }
            },
            // static members
            {
            }
        };
        meta_class<mud::InputEvent>();
    }
    // mud::Keyboard
    {
        static Meta meta = { type<mud::Keyboard>(), &namspc({ "mud" }), "Keyboard", sizeof(mud::Keyboard), TypeClass::Object };
        static Class cls = { type<mud::Keyboard>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Keyboard>();
    }
    // mud::Mouse
    {
        static Meta meta = { type<mud::Mouse>(), &namspc({ "mud" }), "Mouse", sizeof(mud::Mouse), TypeClass::Object };
        static Class cls = { type<mud::Mouse>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Mouse>();
    }
    // mud::RenderSystem
    {
        static Meta meta = { type<mud::RenderSystem>(), &namspc({ "mud" }), "RenderSystem", sizeof(mud::RenderSystem), TypeClass::Object };
        static Class cls = { type<mud::RenderSystem>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::RenderSystem>();
    }
    // mud::KeyEvent
    {
        static Meta meta = { type<mud::KeyEvent>(), &namspc({ "mud" }), "KeyEvent", sizeof(mud::KeyEvent), TypeClass::Struct };
        static Class cls = { type<mud::KeyEvent>(),
            // bases
            { &type<mud::InputEvent>() },
            { base_offset<mud::KeyEvent, mud::InputEvent>() },
            // constructors
            {
                { type<mud::KeyEvent>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::KeyEvent>(ref)) mud::KeyEvent(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::KeyEvent>(), [](Ref ref, Ref other) { new(&val<mud::KeyEvent>(ref)) mud::KeyEvent(val<mud::KeyEvent>(other)); } }
            },
            // members
            {
                { type<mud::KeyEvent>(), member_address(&mud::KeyEvent::m_code), type<mud::Key>(), "code", var(mud::Key()), Member::Value, nullptr },
                { type<mud::KeyEvent>(), member_address(&mud::KeyEvent::m_char), type<char>(), "char", var(char()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::KeyEvent>();
    }
    // mud::MouseEvent
    {
        static Meta meta = { type<mud::MouseEvent>(), &namspc({ "mud" }), "MouseEvent", sizeof(mud::MouseEvent), TypeClass::Struct };
        static Class cls = { type<mud::MouseEvent>(),
            // bases
            { &type<mud::InputEvent>() },
            { base_offset<mud::MouseEvent, mud::InputEvent>() },
            // constructors
            {
                { type<mud::MouseEvent>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::MouseEvent>(ref)) mud::MouseEvent(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::MouseEvent>(), [](Ref ref, Ref other) { new(&val<mud::MouseEvent>(ref)) mud::MouseEvent(val<mud::MouseEvent>(other)); } }
            },
            // members
            {
                { type<mud::MouseEvent>(), member_address(&mud::MouseEvent::m_pos), type<mud::vec2>(), "pos", var(mud::vec2{0.f,0.f}), Member::Value, nullptr },
                { type<mud::MouseEvent>(), member_address(&mud::MouseEvent::m_relative), type<mud::vec2>(), "relative", var(mud::vec2{0.f,0.f}), Member::Value, nullptr },
                { type<mud::MouseEvent>(), member_address(&mud::MouseEvent::m_delta), type<mud::vec2>(), "delta", var(mud::vec2{0.f,0.f}), Member::Value, nullptr },
                { type<mud::MouseEvent>(), member_address(&mud::MouseEvent::m_deltaZ), type<float>(), "deltaZ", var(float(0.f)), Member::Value, nullptr },
                { type<mud::MouseEvent>(), member_address(&mud::MouseEvent::m_pressed), type<mud::vec2>(), "pressed", var(mud::vec2{0.f,0.f}), Member::Value, nullptr },
                { type<mud::MouseEvent>(), member_address(&mud::MouseEvent::m_button), type<mud::MouseButtonCode>(), "button", var(mud::MouseButtonCode(NO_BUTTON)), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::MouseEvent>();
    }
        m.m_types.push_back(&type<mud::Context>());
        m.m_types.push_back(&type<mud::ControlNode>());
        m.m_types.push_back(&type<mud::DeviceType>());
        m.m_types.push_back(&type<mud::EventType>());
        m.m_types.push_back(&type<mud::InputEvent>());
        m.m_types.push_back(&type<mud::InputMod>());
        m.m_types.push_back(&type<mud::Key>());
        m.m_types.push_back(&type<mud::Keyboard>());
        m.m_types.push_back(&type<mud::Mouse>());
        m.m_types.push_back(&type<mud::MouseButtonCode>());
        m.m_types.push_back(&type<mud::RenderSystem>());
        m.m_types.push_back(&type<mud::KeyEvent>());
        m.m_types.push_back(&type<mud::MouseEvent>());
    }
}
