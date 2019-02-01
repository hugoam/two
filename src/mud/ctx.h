#pragma once

#include <mud/math.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifndef MUD_MODULES
#include <stl/string.h>
#endif



#ifndef MUD_CTX_EXPORT
#define MUD_CTX_EXPORT MUD_IMPORT
#endif

#include <stdint.h>

namespace mud
{
    enum class Key : uint16_t;
    enum MouseButtonCode : unsigned int;
    enum class InputMod : uint8_t;
    enum class DeviceType : unsigned int;
    enum class DeviceMask : unsigned int;
    enum class EventType : unsigned int;
    
    
    class RenderSystem;
    class Context;
    struct InputEvent;
    struct MouseEvent;
    struct KeyEvent;
    struct ModalControl;
    class ControlNode;
    struct EventBatch;
    class EventDispatcher;
    class InputDevice;
    class Keyboard;
    class MouseButton;
    class Mouse;
}

namespace mud
{
	using cstring = const char*;

	export_ class refl_ MUD_CTX_EXPORT RenderSystem
	{
	public:
		RenderSystem(const string& resource_path, bool manual_render);
		virtual ~RenderSystem() {}

		virtual void begin_frame() = 0;
		virtual bool next_frame() = 0;

		virtual object<Context> create_context(const string& name, int width, int height, bool fullScreen) = 0;
		
		const string m_resource_path;
		const bool m_manual_render;
	};

	export_ class refl_ MUD_CTX_EXPORT Context : public NonCopy
	{
	public:
		Context(RenderSystem& render_system, const string& title, int width, int height, bool full_screen = false);
		virtual ~Context();

		RenderSystem& m_render_system;
		attr_ const string m_resource_path;

		attr_ string m_title;
		attr_ unsigned int m_width;
		attr_ unsigned int m_height;
		attr_ bool m_full_screen;

		size_t m_handle = 0;
		void* m_native_handle = nullptr;
		void* m_native_target = nullptr;

		attr_ bool m_active = true;
		attr_ bool m_shutdown = false;

		attr_ vec2 m_cursor;
		attr_ bool m_mouse_lock = false;

		meth_ virtual void reset(uint16_t width, uint16_t height) = 0;
		meth_ virtual void init_input(Mouse& mouse, Keyboard& keyboard) = 0;

		meth_ virtual bool next_frame() = 0;

		meth_ virtual void lock_mouse(bool locked) = 0;
	};

}




#ifndef MUD_MODULES
#endif



#include <stdint.h>

export_ namespace mud
{}

namespace mud
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

	inline Key translate(Key key) { return Key(unsigned(key) | unsigned(Key::Translated)); }

	export_ enum refl_ MouseButtonCode : unsigned int
	{
		LEFT_BUTTON = 0,
		RIGHT_BUTTON,
		MIDDLE_BUTTON,
		NO_BUTTON
	};
}

namespace mud
{
	export_ enum class refl_ InputMod : uint8_t
	{
		None = 0,
		Shift = 1 << 0,
		Ctrl = 1 << 1,
		Alt = 1 << 2,
		Any = Shift | Ctrl | Alt
	};

	export_ enum class refl_ DeviceType : unsigned int
	{
		None = 0,
		Keyboard = 1,
		Mouse = 2,
		MouseLeft = 3,
		MouseRight = 4,
		MouseMiddle = 5,
		Touch = 6,
		Count = 7
	};

	export_ constexpr uint32_t device_mask(DeviceType device_type) { return (1 << uint32_t(device_type)); }

	export_ enum class DeviceMask : unsigned int
	{
		AllMouse = device_mask(DeviceType::Mouse) | device_mask(DeviceType::MouseLeft) | device_mask(DeviceType::MouseRight) | device_mask(DeviceType::MouseMiddle),
		All = device_mask(DeviceType::Keyboard) | AllMouse
	};

	export_ enum class refl_ EventType : unsigned int
	{
		None = 0,
		Heartbeat = 1,
		Moved = 2,
		Pressed = 3,
		Released = 4,
		Stroked = 5,
		DoubleStroked = 6,
		Dragged = 7,
		DraggedTarget = 8,
		DragStarted = 9,
		DragEnded = 10,
		Dropped = 11,
		Count = 12
	};

	export_ struct refl_ MUD_CTX_EXPORT InputEvent
	{
		attr_ DeviceType m_deviceType = DeviceType::None;
		attr_ EventType m_eventType = EventType::None;
		attr_ ControlNode* m_receiver = nullptr;
		attr_ ControlNode* m_consumer = nullptr;
		attr_ bool m_abort = false;
		attr_ InputMod m_modifiers = InputMod::None;
		attr_ int m_key = -1;

		InputEvent() {}
		InputEvent(DeviceType deviceType, EventType eventType, InputMod modifiers = InputMod::None) : m_deviceType(deviceType), m_eventType(eventType), m_modifiers(modifiers) {}
		
		meth_ inline InputEvent& consume(ControlNode& consumer) { m_consumer = &consumer; return *this; }
		meth_ inline bool valid() { return m_deviceType != DeviceType::None && m_consumer == nullptr; }
		operator bool() { return this->valid(); }

		//bool operator==(const InputEvent& other) const { UNUSED(other); return false; }
	};

	export_ struct refl_ MUD_CTX_EXPORT MouseEvent : public InputEvent
	{
		attr_ vec2 m_pos = { 0.f, 0.f };
		attr_ vec2 m_relative = { 0.f, 0.f };
		attr_ vec2 m_delta = { 0.f, 0.f };
		attr_ float m_deltaZ = 0.f;
		attr_ vec2 m_pressed = { 0.f, 0.f };
		refl_ ControlNode* m_target = nullptr;

		attr_ MouseButtonCode m_button = NO_BUTTON;

		MouseEvent() : InputEvent() {}
		MouseEvent(DeviceType deviceType, EventType eventType, vec2 pos, InputMod modifiers = InputMod::None)
			: InputEvent(deviceType, eventType, modifiers), m_pos(pos)
		{
			if(deviceType == DeviceType::MouseLeft)
				m_button = LEFT_BUTTON;
			else if(deviceType == DeviceType::MouseRight)
				m_button = RIGHT_BUTTON;
			else if(deviceType == DeviceType::MouseMiddle || true)
				m_button = MIDDLE_BUTTON;
		}

		MouseEvent(DeviceType deviceType, EventType eventType, MouseEvent& source)
			: MouseEvent(deviceType, eventType, source.m_pos, source.m_modifiers)
		{
			m_relative = source.m_relative; m_delta = source.m_delta; m_pressed = source.m_pressed;
		}

		MouseEvent& consume(ControlNode& consumer) { m_consumer = &consumer; return *this; }

		//bool operator==(const MouseEvent& other) const { UNUSED(other); return false; }
	};

	export_ struct refl_ MUD_CTX_EXPORT KeyEvent : public InputEvent
	{
		attr_ Key m_code;
		attr_ char m_char;

		KeyEvent() : InputEvent() {}
		KeyEvent(DeviceType deviceType, EventType eventType, Key code, char c, InputMod modifiers)
			: InputEvent(deviceType, eventType, modifiers), m_code(code), m_char(c)
		{
			m_key = int(code);
		}

		//bool operator==(const KeyEvent& other) const { UNUSED(other); return false; }
	};
}

#ifndef MUD_CPP_20
#include <stdint.h>
#endif

namespace mud
{
	export_ struct ModalControl
	{
		ControlNode* m_parent = nullptr;
		ControlNode* m_modal = nullptr;
		uint32_t m_mask = UINT32_MAX;
	};

	export_ class refl_ MUD_CTX_EXPORT ControlNode
	{
	public:
		virtual ControlNode* control_event(InputEvent& event) = 0;
		virtual ControlNode* propagate_event(InputEvent& inputEvent) = 0;
		virtual void receive_event(InputEvent& inputEvent) = 0;

		virtual void take_modal(uint32_t device_filter = uint32_t(DeviceMask::All)) = 0;
		virtual void yield_modal() = 0;

		EventBatch* m_events = nullptr;
		ModalControl m_control = {};
	};
}


#ifndef MUD_MODULES
#include <stl/vector.h>
#endif


#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/vector.h>
#include <stl/map.h>
#endif

namespace mud
{
	export_ template <class T_Element>
	struct EventMap
	{
		enum_array<DeviceType, enum_array<EventType, T_Element>> m_events = {};
		enum_array<DeviceType, enum_array<EventType, map<int, T_Element>>> m_keyed_events = {};

		void clear() { *this = {}; }

		T_Element& event(DeviceType device_type, EventType event_type) { return m_events[size_t(device_type)][size_t(event_type)]; }
		T_Element& event(DeviceType device_type, EventType event_type, int key) { return m_keyed_events[size_t(device_type)][size_t(event_type)][key]; }
	};

	export_ struct MUD_CTX_EXPORT EventBatch : public EventMap<InputEvent*>
	{
		ControlNode* m_control_node = nullptr;
	};

	export_ class MUD_CTX_EXPORT EventDispatcher
	{
	public:
		EventDispatcher(ControlNode* control_node);

		void update();

		ControlNode* dispatch_event(InputEvent& event, ControlNode* top_receiver = nullptr);
		void receive_event(InputEvent& event, ControlNode& receiver);

		ControlNode& m_control_node;
		vector<EventBatch> m_event_batches;
		size_t m_top = 0;
	};
}

namespace mud
{
	export_ class MUD_CTX_EXPORT InputDevice
	{
	public:
		InputDevice(EventDispatcher& dispatcher);

		EventDispatcher& m_dispatcher;
	};

	export_ class refl_ MUD_CTX_EXPORT Keyboard : public InputDevice
	{
	public:
		Keyboard(EventDispatcher& dispatcher);

		void dispatch_event(KeyEvent evt);

		void update_modifiers(bool shift, bool ctrl, bool alt);
		InputMod modifiers();

		void key_pressed(Key key, Key translated);
		void key_pressed(Key key, Key translated, InputMod mods);
		void key_released(Key key, Key translated);
		void key_released(Key key, Key translated, InputMod mods);
		void key_stroke(Key key, Key translated);
		void key_stroke(Key key, Key translated, InputMod mods);
		void key_char(char c);

		bool m_shift = false;
		bool m_ctrl = false;
		bool m_alt = false;

		vector<KeyEvent> m_events;
	};

	export_ class MUD_CTX_EXPORT MouseButton : public InputDevice
	{
	public:
		MouseButton(Mouse& mouse, DeviceType deviceType);

		void pressed(vec2 pos);
		void pressed(vec2 pos, InputMod modifiers);
		void released(vec2 pos);

		void drag_start(MouseEvent& mouse_event);
		void drag_end(MouseEvent& mouse_event);
		void drag(MouseEvent& mouse_event);
		void click(MouseEvent& mouse_event);

		Mouse& m_mouse;
		DeviceType m_deviceType;

		ControlNode* m_pressed = nullptr;
		bool m_dragging = false;

		MouseEvent m_pressed_event = {};
	};

	export_ class refl_ MUD_CTX_EXPORT Mouse : public InputDevice
	{
	public:
		Mouse(EventDispatcher& dispatcher, Keyboard& keyboard);

		MouseEvent& dispatch_event(MouseEvent evt);
		MouseEvent& dispatch_secondary(MouseEvent evt, ControlNode* pressed, vec2 pressed_pos, ControlNode* target = nullptr);

		MouseEvent& heartbeat();
		void moved(vec2 pos, vec2* offset = nullptr);
		void wheeled(vec2 pos, float amount);

		void fix_press(ControlNode& node);

	public:
		Keyboard& m_keyboard;
		vec2 m_pos;
		vec2 m_last_pos;
		MouseButton m_buttons[3];

		vector<MouseEvent> m_events;
	};
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <stdint.h>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_CTX_EXPORT Type& type<mud::DeviceType>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::EventType>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::InputMod>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::Key>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::MouseButtonCode>();
    
    export_ template <> MUD_CTX_EXPORT Type& type<mud::Context>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::ControlNode>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::InputEvent>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::Keyboard>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::Mouse>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::RenderSystem>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::KeyEvent>();
    export_ template <> MUD_CTX_EXPORT Type& type<mud::MouseEvent>();
    
    export_ template <> MUD_CTX_EXPORT Type& type<vector<mud::Context*>>();
    export_ template <> MUD_CTX_EXPORT Type& type<vector<mud::ControlNode*>>();
    export_ template <> MUD_CTX_EXPORT Type& type<vector<mud::InputEvent*>>();
    export_ template <> MUD_CTX_EXPORT Type& type<vector<mud::Keyboard*>>();
    export_ template <> MUD_CTX_EXPORT Type& type<vector<mud::Mouse*>>();
    export_ template <> MUD_CTX_EXPORT Type& type<vector<mud::RenderSystem*>>();
    export_ template <> MUD_CTX_EXPORT Type& type<vector<mud::KeyEvent*>>();
    export_ template <> MUD_CTX_EXPORT Type& type<vector<mud::MouseEvent*>>();
}

