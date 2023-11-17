//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ctx/Forward.h>

export_ namespace two
{}

namespace two
{
	//! Keyboard scan codes
	export_ enum class refl_ Key : uint16_t
	{
		Unassigned  = 0x00,
		Escape      = 0x01,
		Num1        = 0x02,
		Num2        = 0x03,
		Num3        = 0x04,
		Num4        = 0x05,
		Num5        = 0x06,
		Num6        = 0x07,
		Num7        = 0x08,
		Num8        = 0x09,
		Num9        = 0x0A,
		Num0        = 0x0B,
		Minus       = 0x0C,    // - on main keyboard
		Equals      = 0x0D,
		Back        = 0x0E,    // backspace
		Tab         = 0x0F,
		Q           = 0x10,
		W           = 0x11,
		E           = 0x12,
		R           = 0x13,
		T           = 0x14,
		Y           = 0x15,
		U           = 0x16,
		I           = 0x17,
		O           = 0x18,
		P           = 0x19,
		LeftBracket = 0x1A,
		RightBracket= 0x1B,
		Return      = 0x1C,    // Enter on main keyboard
		LeftControl = 0x1D,
		A           = 0x1E,
		S           = 0x1F,
		D           = 0x20,
		F           = 0x21,
		G           = 0x22,
		H           = 0x23,
		J           = 0x24,
		K           = 0x25,
		L           = 0x26,
		Semicolon   = 0x27,
		Apostrophe  = 0x28,
		Grave       = 0x29,    // accent
		LeftShift   = 0x2A,
		Backslash   = 0x2B,
		Z           = 0x2C,
		X           = 0x2D,
		C           = 0x2E,
		V           = 0x2F,
		B           = 0x30,
		N           = 0x31,
		M           = 0x32,
		Comma       = 0x33,
		Period      = 0x34,    // . on main keyboard
		Slash       = 0x35,    // / on main keyboard
		RightShift  = 0x36,
		Multiply    = 0x37,    // * on numeric keypad
		LeftAlt     = 0x38,    // left Alt
		Space       = 0x39,
		Capital     = 0x3A,
		F1          = 0x3B,
		F2          = 0x3C,
		F3          = 0x3D,
		F4          = 0x3E,
		F5          = 0x3F,
		F6          = 0x40,
		F7          = 0x41,
		F8          = 0x42,
		F9          = 0x43,
		F10         = 0x44,
		Numlock     = 0x45,
		ScrollLock  = 0x46,    // Scroll Lock
		Numpad7     = 0x47,
		Numpad8     = 0x48,
		Numpad9     = 0x49,
		Subtract    = 0x4A,    // - on numeric keypad
		Numpad4     = 0x4B,
		Numpad5     = 0x4C,
		Numpad6     = 0x4D,
		Add         = 0x4E,    // + on numeric keypad
		Numpad1     = 0x4F,
		Numpad2     = 0x50,
		Numpad3     = 0x51,
		Numpad0     = 0x52,
		Decimal     = 0x53,    // . on numeric keypad
		//OEM_102     = 0x56,    // < > | on UK/Germany keyboards
		F11         = 0x57,
		F12         = 0x58,
		F13         = 0x64,    //                     (NEC PC98)
		F14         = 0x65,    //                     (NEC PC98)
		F15         = 0x66,    //                     (NEC PC98)
		//KANA        = 0x70,    // (Japanese keyboard)
		//ABNT_C1     = 0x73,    // / ? on Portugese (Brazilian) keyboards
		//CONVERT     = 0x79,    // (Japanese keyboard)
		//NOCONVERT   = 0x7B,    // (Japanese keyboard)
		//YEN         = 0x7D,    // (Japanese keyboard)
		//ABNT_C2     = 0x7E,    // Numpad . on Portugese (Brazilian) keyboards
		NumpadEquals= 0x8D,    // = on numeric keypad (NEC PC98)
		//PREVTRACK   = 0x90,    // Previous Track (Key::CIRCUMFLEX on Japanese keyboard)
		//AT          = 0x91,    //                     (NEC PC98)
		//COLON       = 0x92,    //                     (NEC PC98)
		//UNDERLINE   = 0x93,    //                     (NEC PC98)
		//KANJI       = 0x94,    // (Japanese keyboard)
		//STOP        = 0x95,    //                     (NEC PC98)
		//AX          = 0x96,    //                     (Japan AX)
		//UNLABELED   = 0x97,    //                        (J3100)
		//NEXTTRACK   = 0x99,    // Next Track
		NumpadEnter = 0x9C,    // Enter on numeric keypad
		RightControl= 0x9D,
		Mute        = 0xA0,    // Mute
		//CALCULATOR  = 0xA1,    // Calculator
		//PLAYPAUSE   = 0xA2,    // Play / Pause
		//MEDIASTOP   = 0xA4,    // Media Stop
		//VOLUMEDOWN  = 0xAE,    // Volume -
		//VOLUMEUP    = 0xB0,    // Volume +
		//WEBHOME     = 0xB2,    // Web home
		NumpadComma = 0xB3,    // , on numeric keypad (NEC PC98)
		Divide      = 0xB5,    // / on numeric keypad
		//SYSRQ       = 0xB7,
		RightAlt       = 0xB8,    // right Alt
		Pause       = 0xC5,    // Pause
		Home        = 0xC7,    // Home on arrow keypad
		Up          = 0xC8,    // UpArrow on arrow keypad
		PageUp      = 0xC9,    // PgUp on arrow keypad
		Left        = 0xCB,    // LeftArrow on arrow keypad
		Right       = 0xCD,    // RightArrow on arrow keypad
		End         = 0xCF,    // End on arrow keypad
		Down        = 0xD0,    // DownArrow on arrow keypad
		PageDown    = 0xD1,    // PgDn on arrow keypad
		Insert      = 0xD2,    // Insert on arrow keypad
		Delete      = 0xD3,    // Delete on arrow keypad
		LeftWin     = 0xDB,    // Left Windows key
		RightWin    = 0xDC,    // Right Windows key
		//APPS        = 0xDD,    // AppMenu key
		//POWER       = 0xDE,    // System Power
		//SLEEP       = 0xDF,    // System Sleep
		//WAKE        = 0xE3,    // System Wake
		//WEBSEARCH   = 0xE5,    // Web Search
		//WEBFAVORITES= 0xE6,    // Web Favorites
		//WEBREFRESH  = 0xE7,    // Web Refresh
		//WEBSTOP     = 0xE8,    // Web Stop
		//WEBFORWARD  = 0xE9,    // Web Forward
		//WEBBACK     = 0xEA,    // Web Back
		//MYCOMPUTER  = 0xEB,    // My Computer
		//MAIL        = 0xEC,    // Mail
		//MEDIASELECT = 0xED     // Media Select
		Translated = uint16_t(1 << 15) // last bit reserved for translated flag
	};

	export_ inline Key translate(Key key) { return Key(unsigned(key) | unsigned(Key::Translated)); }

	export_ enum refl_ MouseButtonCode : unsigned int
	{
		LEFT_BUTTON = 0,
		RIGHT_BUTTON,
		MIDDLE_BUTTON,
		NO_BUTTON
	};
}
