

#pragma once

#ifndef MUD_MODULES
#include <meta/ctx/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_ctx_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::Key>(), &namspc({ "mud" }), "Key", sizeof(mud::Key), TypeClass::Enum };
        static Enum enu = { type<mud::Key>(),
            true,
            { "Unassigned", "Escape", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "Num0", "Minus", "Equals", "Back", "Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "LeftBracket", "RightBracket", "Return", "LeftControl", "A", "S", "D", "F", "G", "H", "J", "K", "L", "Semicolon", "Apostrophe", "Grave", "LeftShift", "Backslash", "Z", "X", "C", "V", "B", "N", "M", "Comma", "Period", "Slash", "RightShift", "Multiply", "LeftAlt", "Space", "Capital", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "Numlock", "ScrollLock", "Numpad7", "Numpad8", "Numpad9", "Subtract", "Numpad4", "Numpad5", "Numpad6", "Add", "Numpad1", "Numpad2", "Numpad3", "Numpad0", "Decimal", "F11", "F12", "F13", "F14", "F15", "NumpadEquals", "NumpadEnter", "RightControl", "Mute", "NumpadComma", "Divide", "RightAlt", "Pause", "Home", "Up", "PageUp", "Left", "Right", "End", "Down", "PageDown", "Insert", "Delete", "LeftWin", "RightWin" },
            { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 87, 88, 100, 101, 102, 141, 156, 157, 160, 179, 181, 184, 197, 199, 200, 201, 203, 205, 207, 208, 209, 210, 211, 219, 220 },
            { var(mud::Key::Unassigned), var(mud::Key::Escape), var(mud::Key::Num1), var(mud::Key::Num2), var(mud::Key::Num3), var(mud::Key::Num4), var(mud::Key::Num5), var(mud::Key::Num6), var(mud::Key::Num7), var(mud::Key::Num8), var(mud::Key::Num9), var(mud::Key::Num0), var(mud::Key::Minus), var(mud::Key::Equals), var(mud::Key::Back), var(mud::Key::Tab), var(mud::Key::Q), var(mud::Key::W), var(mud::Key::E), var(mud::Key::R), var(mud::Key::T), var(mud::Key::Y), var(mud::Key::U), var(mud::Key::I), var(mud::Key::O), var(mud::Key::P), var(mud::Key::LeftBracket), var(mud::Key::RightBracket), var(mud::Key::Return), var(mud::Key::LeftControl), var(mud::Key::A), var(mud::Key::S), var(mud::Key::D), var(mud::Key::F), var(mud::Key::G), var(mud::Key::H), var(mud::Key::J), var(mud::Key::K), var(mud::Key::L), var(mud::Key::Semicolon), var(mud::Key::Apostrophe), var(mud::Key::Grave), var(mud::Key::LeftShift), var(mud::Key::Backslash), var(mud::Key::Z), var(mud::Key::X), var(mud::Key::C), var(mud::Key::V), var(mud::Key::B), var(mud::Key::N), var(mud::Key::M), var(mud::Key::Comma), var(mud::Key::Period), var(mud::Key::Slash), var(mud::Key::RightShift), var(mud::Key::Multiply), var(mud::Key::LeftAlt), var(mud::Key::Space), var(mud::Key::Capital), var(mud::Key::F1), var(mud::Key::F2), var(mud::Key::F3), var(mud::Key::F4), var(mud::Key::F5), var(mud::Key::F6), var(mud::Key::F7), var(mud::Key::F8), var(mud::Key::F9), var(mud::Key::F10), var(mud::Key::Numlock), var(mud::Key::ScrollLock), var(mud::Key::Numpad7), var(mud::Key::Numpad8), var(mud::Key::Numpad9), var(mud::Key::Subtract), var(mud::Key::Numpad4), var(mud::Key::Numpad5), var(mud::Key::Numpad6), var(mud::Key::Add), var(mud::Key::Numpad1), var(mud::Key::Numpad2), var(mud::Key::Numpad3), var(mud::Key::Numpad0), var(mud::Key::Decimal), var(mud::Key::F11), var(mud::Key::F12), var(mud::Key::F13), var(mud::Key::F14), var(mud::Key::F15), var(mud::Key::NumpadEquals), var(mud::Key::NumpadEnter), var(mud::Key::RightControl), var(mud::Key::Mute), var(mud::Key::NumpadComma), var(mud::Key::Divide), var(mud::Key::RightAlt), var(mud::Key::Pause), var(mud::Key::Home), var(mud::Key::Up), var(mud::Key::PageUp), var(mud::Key::Left), var(mud::Key::Right), var(mud::Key::End), var(mud::Key::Down), var(mud::Key::PageDown), var(mud::Key::Insert), var(mud::Key::Delete), var(mud::Key::LeftWin), var(mud::Key::RightWin) }
        };
        meta_enum<mud::Key>();
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
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Context>();
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
    
    
    
    

    
        m.m_types.push_back(&type<mud::Context>());
        m.m_types.push_back(&type<mud::EventMap<mud::InputEvent*>>());
        m.m_types.push_back(&type<mud::Key>());
        m.m_types.push_back(&type<mud::RenderSystem>());
    
    }
}
