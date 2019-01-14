#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <ctx/Api.h>

#ifdef MUD_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// Context
	mud::Type* DECL mud_Context__type() {
		return mud::type<mud::Context>();
	}
	void DECL mud_Context_init_input_2(mud::Context* self, mud::Mouse* mouse, mud::Keyboard* keyboard) {
		self->init_input(*mouse, *keyboard);
	}
	void DECL mud_Context_lock_mouse_1(mud::Context* self, bool locked) {
		self->lock_mouse(locked);
	}
	bool DECL mud_Context_next_frame_0(mud::Context* self) {
		return self->next_frame();
	}
	void DECL mud_Context_reset_2(mud::Context* self, uint16_t width, uint16_t height) {
		self->reset(width, height);
	}
	const char* DECL mud_Context__get_resource_path(mud::Context* self) {
		return self->m_resource_path.c_str();
	}
	const char* DECL mud_Context__get_title(mud::Context* self) {
		return self->m_title.c_str();
	}
	void DECL mud_Context__set_title(mud::Context* self, const char* value) {
		self->m_title = value;
	}
	unsigned int DECL mud_Context__get_width(mud::Context* self) {
		return self->m_width;
	}
	void DECL mud_Context__set_width(mud::Context* self, unsigned int value) {
		self->m_width = value;
	}
	unsigned int DECL mud_Context__get_height(mud::Context* self) {
		return self->m_height;
	}
	void DECL mud_Context__set_height(mud::Context* self, unsigned int value) {
		self->m_height = value;
	}
	bool DECL mud_Context__get_full_screen(mud::Context* self) {
		return self->m_full_screen;
	}
	void DECL mud_Context__set_full_screen(mud::Context* self, bool value) {
		self->m_full_screen = value;
	}
	bool DECL mud_Context__get_active(mud::Context* self) {
		return self->m_active;
	}
	void DECL mud_Context__set_active(mud::Context* self, bool value) {
		self->m_active = value;
	}
	bool DECL mud_Context__get_shutdown(mud::Context* self) {
		return self->m_shutdown;
	}
	void DECL mud_Context__set_shutdown(mud::Context* self, bool value) {
		self->m_shutdown = value;
	}
	mud::vec2* DECL mud_Context__get_cursor(mud::Context* self) {
		static mud::vec2 temp;
		return (temp = self->m_cursor, &temp);
	}
	void DECL mud_Context__set_cursor(mud::Context* self, mud::vec2* value) {
		self->m_cursor = *value;
	}
	bool DECL mud_Context__get_mouse_lock(mud::Context* self) {
		return self->m_mouse_lock;
	}
	void DECL mud_Context__set_mouse_lock(mud::Context* self, bool value) {
		self->m_mouse_lock = value;
	}
	void DECL mud_Context__destroy(mud::Context* self) {
		delete self;
	}
	// ControlNode
	mud::Type* DECL mud_ControlNode__type() {
		return mud::type<mud::ControlNode>();
	}
	void DECL mud_ControlNode__destroy(mud::ControlNode* self) {
		delete self;
	}
	// InputEvent
	mud::Type* DECL mud_InputEvent__type() {
		return mud::type<mud::InputEvent>();
	}
	mud::InputEvent* DECL mud_InputEvent_InputEvent_0() {
		return new mud::InputEvent();
	}
	mud::InputEvent* DECL mud_InputEvent_consume_1(mud::InputEvent* self, mud::ControlNode* consumer) {
		return &self->consume(*consumer);
	}
	bool DECL mud_InputEvent_valid_0(mud::InputEvent* self) {
		return self->valid();
	}
	mud::DeviceType DECL mud_InputEvent__get_deviceType(mud::InputEvent* self) {
		return self->m_deviceType;
	}
	void DECL mud_InputEvent__set_deviceType(mud::InputEvent* self, mud::DeviceType value) {
		self->m_deviceType = value;
	}
	mud::EventType DECL mud_InputEvent__get_eventType(mud::InputEvent* self) {
		return self->m_eventType;
	}
	void DECL mud_InputEvent__set_eventType(mud::InputEvent* self, mud::EventType value) {
		self->m_eventType = value;
	}
	mud::ControlNode* DECL mud_InputEvent__get_receiver(mud::InputEvent* self) {
		return self->m_receiver;
	}
	void DECL mud_InputEvent__set_receiver(mud::InputEvent* self, mud::ControlNode* value) {
		self->m_receiver = value;
	}
	mud::ControlNode* DECL mud_InputEvent__get_consumer(mud::InputEvent* self) {
		return self->m_consumer;
	}
	void DECL mud_InputEvent__set_consumer(mud::InputEvent* self, mud::ControlNode* value) {
		self->m_consumer = value;
	}
	bool DECL mud_InputEvent__get_abort(mud::InputEvent* self) {
		return self->m_abort;
	}
	void DECL mud_InputEvent__set_abort(mud::InputEvent* self, bool value) {
		self->m_abort = value;
	}
	mud::InputMod DECL mud_InputEvent__get_modifiers(mud::InputEvent* self) {
		return self->m_modifiers;
	}
	void DECL mud_InputEvent__set_modifiers(mud::InputEvent* self, mud::InputMod value) {
		self->m_modifiers = value;
	}
	int DECL mud_InputEvent__get_key(mud::InputEvent* self) {
		return self->m_key;
	}
	void DECL mud_InputEvent__set_key(mud::InputEvent* self, int value) {
		self->m_key = value;
	}
	void DECL mud_InputEvent__destroy(mud::InputEvent* self) {
		delete self;
	}
	// Keyboard
	mud::Type* DECL mud_Keyboard__type() {
		return mud::type<mud::Keyboard>();
	}
	void DECL mud_Keyboard__destroy(mud::Keyboard* self) {
		delete self;
	}
	// Mouse
	mud::Type* DECL mud_Mouse__type() {
		return mud::type<mud::Mouse>();
	}
	void DECL mud_Mouse__destroy(mud::Mouse* self) {
		delete self;
	}
	// RenderSystem
	mud::Type* DECL mud_RenderSystem__type() {
		return mud::type<mud::RenderSystem>();
	}
	void DECL mud_RenderSystem__destroy(mud::RenderSystem* self) {
		delete self;
	}
	// KeyEvent
	mud::Type* DECL mud_KeyEvent__type() {
		return mud::type<mud::KeyEvent>();
	}
	mud::KeyEvent* DECL mud_KeyEvent_KeyEvent_0() {
		return new mud::KeyEvent();
	}
	mud::Key DECL mud_KeyEvent__get_code(mud::KeyEvent* self) {
		return self->m_code;
	}
	void DECL mud_KeyEvent__set_code(mud::KeyEvent* self, mud::Key value) {
		self->m_code = value;
	}
	char DECL mud_KeyEvent__get_char(mud::KeyEvent* self) {
		return self->m_char;
	}
	void DECL mud_KeyEvent__set_char(mud::KeyEvent* self, char value) {
		self->m_char = value;
	}
	void DECL mud_KeyEvent__destroy(mud::KeyEvent* self) {
		delete self;
	}
	// MouseEvent
	mud::Type* DECL mud_MouseEvent__type() {
		return mud::type<mud::MouseEvent>();
	}
	mud::MouseEvent* DECL mud_MouseEvent_MouseEvent_0() {
		return new mud::MouseEvent();
	}
	mud::vec2* DECL mud_MouseEvent__get_pos(mud::MouseEvent* self) {
		static mud::vec2 temp;
		return (temp = self->m_pos, &temp);
	}
	void DECL mud_MouseEvent__set_pos(mud::MouseEvent* self, mud::vec2* value) {
		self->m_pos = *value;
	}
	mud::vec2* DECL mud_MouseEvent__get_relative(mud::MouseEvent* self) {
		static mud::vec2 temp;
		return (temp = self->m_relative, &temp);
	}
	void DECL mud_MouseEvent__set_relative(mud::MouseEvent* self, mud::vec2* value) {
		self->m_relative = *value;
	}
	mud::vec2* DECL mud_MouseEvent__get_delta(mud::MouseEvent* self) {
		static mud::vec2 temp;
		return (temp = self->m_delta, &temp);
	}
	void DECL mud_MouseEvent__set_delta(mud::MouseEvent* self, mud::vec2* value) {
		self->m_delta = *value;
	}
	float DECL mud_MouseEvent__get_deltaZ(mud::MouseEvent* self) {
		return self->m_deltaZ;
	}
	void DECL mud_MouseEvent__set_deltaZ(mud::MouseEvent* self, float value) {
		self->m_deltaZ = value;
	}
	mud::vec2* DECL mud_MouseEvent__get_pressed(mud::MouseEvent* self) {
		static mud::vec2 temp;
		return (temp = self->m_pressed, &temp);
	}
	void DECL mud_MouseEvent__set_pressed(mud::MouseEvent* self, mud::vec2* value) {
		self->m_pressed = *value;
	}
	mud::MouseButtonCode DECL mud_MouseEvent__get_button(mud::MouseEvent* self) {
		return self->m_button;
	}
	void DECL mud_MouseEvent__set_button(mud::MouseEvent* self, mud::MouseButtonCode value) {
		self->m_button = value;
	}
	void DECL mud_MouseEvent__destroy(mud::MouseEvent* self) {
		delete self;
	}
	// DeviceType
	mud::DeviceType DECL mud_DeviceType_None() {
		return mud::DeviceType::None;
	}
	mud::DeviceType DECL mud_DeviceType_Keyboard() {
		return mud::DeviceType::Keyboard;
	}
	mud::DeviceType DECL mud_DeviceType_Mouse() {
		return mud::DeviceType::Mouse;
	}
	mud::DeviceType DECL mud_DeviceType_MouseLeft() {
		return mud::DeviceType::MouseLeft;
	}
	mud::DeviceType DECL mud_DeviceType_MouseRight() {
		return mud::DeviceType::MouseRight;
	}
	mud::DeviceType DECL mud_DeviceType_MouseMiddle() {
		return mud::DeviceType::MouseMiddle;
	}
	mud::DeviceType DECL mud_DeviceType_Touch() {
		return mud::DeviceType::Touch;
	}
	mud::DeviceType DECL mud_DeviceType_Count() {
		return mud::DeviceType::Count;
	}
	// EventType
	mud::EventType DECL mud_EventType_None() {
		return mud::EventType::None;
	}
	mud::EventType DECL mud_EventType_Heartbeat() {
		return mud::EventType::Heartbeat;
	}
	mud::EventType DECL mud_EventType_Moved() {
		return mud::EventType::Moved;
	}
	mud::EventType DECL mud_EventType_Pressed() {
		return mud::EventType::Pressed;
	}
	mud::EventType DECL mud_EventType_Released() {
		return mud::EventType::Released;
	}
	mud::EventType DECL mud_EventType_Stroked() {
		return mud::EventType::Stroked;
	}
	mud::EventType DECL mud_EventType_DoubleStroked() {
		return mud::EventType::DoubleStroked;
	}
	mud::EventType DECL mud_EventType_Dragged() {
		return mud::EventType::Dragged;
	}
	mud::EventType DECL mud_EventType_DraggedTarget() {
		return mud::EventType::DraggedTarget;
	}
	mud::EventType DECL mud_EventType_DragStarted() {
		return mud::EventType::DragStarted;
	}
	mud::EventType DECL mud_EventType_DragEnded() {
		return mud::EventType::DragEnded;
	}
	mud::EventType DECL mud_EventType_Dropped() {
		return mud::EventType::Dropped;
	}
	mud::EventType DECL mud_EventType_Count() {
		return mud::EventType::Count;
	}
	// InputMod
	mud::InputMod DECL mud_InputMod_None() {
		return mud::InputMod::None;
	}
	mud::InputMod DECL mud_InputMod_Shift() {
		return mud::InputMod::Shift;
	}
	mud::InputMod DECL mud_InputMod_Ctrl() {
		return mud::InputMod::Ctrl;
	}
	mud::InputMod DECL mud_InputMod_Alt() {
		return mud::InputMod::Alt;
	}
	mud::InputMod DECL mud_InputMod_Any() {
		return mud::InputMod::Any;
	}
	// Key
	mud::Key DECL mud_Key_Unassigned() {
		return mud::Key::Unassigned;
	}
	mud::Key DECL mud_Key_Escape() {
		return mud::Key::Escape;
	}
	mud::Key DECL mud_Key_Num1() {
		return mud::Key::Num1;
	}
	mud::Key DECL mud_Key_Num2() {
		return mud::Key::Num2;
	}
	mud::Key DECL mud_Key_Num3() {
		return mud::Key::Num3;
	}
	mud::Key DECL mud_Key_Num4() {
		return mud::Key::Num4;
	}
	mud::Key DECL mud_Key_Num5() {
		return mud::Key::Num5;
	}
	mud::Key DECL mud_Key_Num6() {
		return mud::Key::Num6;
	}
	mud::Key DECL mud_Key_Num7() {
		return mud::Key::Num7;
	}
	mud::Key DECL mud_Key_Num8() {
		return mud::Key::Num8;
	}
	mud::Key DECL mud_Key_Num9() {
		return mud::Key::Num9;
	}
	mud::Key DECL mud_Key_Num0() {
		return mud::Key::Num0;
	}
	mud::Key DECL mud_Key_Minus() {
		return mud::Key::Minus;
	}
	mud::Key DECL mud_Key_Equals() {
		return mud::Key::Equals;
	}
	mud::Key DECL mud_Key_Back() {
		return mud::Key::Back;
	}
	mud::Key DECL mud_Key_Tab() {
		return mud::Key::Tab;
	}
	mud::Key DECL mud_Key_Q() {
		return mud::Key::Q;
	}
	mud::Key DECL mud_Key_W() {
		return mud::Key::W;
	}
	mud::Key DECL mud_Key_E() {
		return mud::Key::E;
	}
	mud::Key DECL mud_Key_R() {
		return mud::Key::R;
	}
	mud::Key DECL mud_Key_T() {
		return mud::Key::T;
	}
	mud::Key DECL mud_Key_Y() {
		return mud::Key::Y;
	}
	mud::Key DECL mud_Key_U() {
		return mud::Key::U;
	}
	mud::Key DECL mud_Key_I() {
		return mud::Key::I;
	}
	mud::Key DECL mud_Key_O() {
		return mud::Key::O;
	}
	mud::Key DECL mud_Key_P() {
		return mud::Key::P;
	}
	mud::Key DECL mud_Key_LeftBracket() {
		return mud::Key::LeftBracket;
	}
	mud::Key DECL mud_Key_RightBracket() {
		return mud::Key::RightBracket;
	}
	mud::Key DECL mud_Key_Return() {
		return mud::Key::Return;
	}
	mud::Key DECL mud_Key_LeftControl() {
		return mud::Key::LeftControl;
	}
	mud::Key DECL mud_Key_A() {
		return mud::Key::A;
	}
	mud::Key DECL mud_Key_S() {
		return mud::Key::S;
	}
	mud::Key DECL mud_Key_D() {
		return mud::Key::D;
	}
	mud::Key DECL mud_Key_F() {
		return mud::Key::F;
	}
	mud::Key DECL mud_Key_G() {
		return mud::Key::G;
	}
	mud::Key DECL mud_Key_H() {
		return mud::Key::H;
	}
	mud::Key DECL mud_Key_J() {
		return mud::Key::J;
	}
	mud::Key DECL mud_Key_K() {
		return mud::Key::K;
	}
	mud::Key DECL mud_Key_L() {
		return mud::Key::L;
	}
	mud::Key DECL mud_Key_Semicolon() {
		return mud::Key::Semicolon;
	}
	mud::Key DECL mud_Key_Apostrophe() {
		return mud::Key::Apostrophe;
	}
	mud::Key DECL mud_Key_Grave() {
		return mud::Key::Grave;
	}
	mud::Key DECL mud_Key_LeftShift() {
		return mud::Key::LeftShift;
	}
	mud::Key DECL mud_Key_Backslash() {
		return mud::Key::Backslash;
	}
	mud::Key DECL mud_Key_Z() {
		return mud::Key::Z;
	}
	mud::Key DECL mud_Key_X() {
		return mud::Key::X;
	}
	mud::Key DECL mud_Key_C() {
		return mud::Key::C;
	}
	mud::Key DECL mud_Key_V() {
		return mud::Key::V;
	}
	mud::Key DECL mud_Key_B() {
		return mud::Key::B;
	}
	mud::Key DECL mud_Key_N() {
		return mud::Key::N;
	}
	mud::Key DECL mud_Key_M() {
		return mud::Key::M;
	}
	mud::Key DECL mud_Key_Comma() {
		return mud::Key::Comma;
	}
	mud::Key DECL mud_Key_Period() {
		return mud::Key::Period;
	}
	mud::Key DECL mud_Key_Slash() {
		return mud::Key::Slash;
	}
	mud::Key DECL mud_Key_RightShift() {
		return mud::Key::RightShift;
	}
	mud::Key DECL mud_Key_Multiply() {
		return mud::Key::Multiply;
	}
	mud::Key DECL mud_Key_LeftAlt() {
		return mud::Key::LeftAlt;
	}
	mud::Key DECL mud_Key_Space() {
		return mud::Key::Space;
	}
	mud::Key DECL mud_Key_Capital() {
		return mud::Key::Capital;
	}
	mud::Key DECL mud_Key_F1() {
		return mud::Key::F1;
	}
	mud::Key DECL mud_Key_F2() {
		return mud::Key::F2;
	}
	mud::Key DECL mud_Key_F3() {
		return mud::Key::F3;
	}
	mud::Key DECL mud_Key_F4() {
		return mud::Key::F4;
	}
	mud::Key DECL mud_Key_F5() {
		return mud::Key::F5;
	}
	mud::Key DECL mud_Key_F6() {
		return mud::Key::F6;
	}
	mud::Key DECL mud_Key_F7() {
		return mud::Key::F7;
	}
	mud::Key DECL mud_Key_F8() {
		return mud::Key::F8;
	}
	mud::Key DECL mud_Key_F9() {
		return mud::Key::F9;
	}
	mud::Key DECL mud_Key_F10() {
		return mud::Key::F10;
	}
	mud::Key DECL mud_Key_Numlock() {
		return mud::Key::Numlock;
	}
	mud::Key DECL mud_Key_ScrollLock() {
		return mud::Key::ScrollLock;
	}
	mud::Key DECL mud_Key_Numpad7() {
		return mud::Key::Numpad7;
	}
	mud::Key DECL mud_Key_Numpad8() {
		return mud::Key::Numpad8;
	}
	mud::Key DECL mud_Key_Numpad9() {
		return mud::Key::Numpad9;
	}
	mud::Key DECL mud_Key_Subtract() {
		return mud::Key::Subtract;
	}
	mud::Key DECL mud_Key_Numpad4() {
		return mud::Key::Numpad4;
	}
	mud::Key DECL mud_Key_Numpad5() {
		return mud::Key::Numpad5;
	}
	mud::Key DECL mud_Key_Numpad6() {
		return mud::Key::Numpad6;
	}
	mud::Key DECL mud_Key_Add() {
		return mud::Key::Add;
	}
	mud::Key DECL mud_Key_Numpad1() {
		return mud::Key::Numpad1;
	}
	mud::Key DECL mud_Key_Numpad2() {
		return mud::Key::Numpad2;
	}
	mud::Key DECL mud_Key_Numpad3() {
		return mud::Key::Numpad3;
	}
	mud::Key DECL mud_Key_Numpad0() {
		return mud::Key::Numpad0;
	}
	mud::Key DECL mud_Key_Decimal() {
		return mud::Key::Decimal;
	}
	mud::Key DECL mud_Key_F11() {
		return mud::Key::F11;
	}
	mud::Key DECL mud_Key_F12() {
		return mud::Key::F12;
	}
	mud::Key DECL mud_Key_F13() {
		return mud::Key::F13;
	}
	mud::Key DECL mud_Key_F14() {
		return mud::Key::F14;
	}
	mud::Key DECL mud_Key_F15() {
		return mud::Key::F15;
	}
	mud::Key DECL mud_Key_NumpadEquals() {
		return mud::Key::NumpadEquals;
	}
	mud::Key DECL mud_Key_NumpadEnter() {
		return mud::Key::NumpadEnter;
	}
	mud::Key DECL mud_Key_RightControl() {
		return mud::Key::RightControl;
	}
	mud::Key DECL mud_Key_Mute() {
		return mud::Key::Mute;
	}
	mud::Key DECL mud_Key_NumpadComma() {
		return mud::Key::NumpadComma;
	}
	mud::Key DECL mud_Key_Divide() {
		return mud::Key::Divide;
	}
	mud::Key DECL mud_Key_RightAlt() {
		return mud::Key::RightAlt;
	}
	mud::Key DECL mud_Key_Pause() {
		return mud::Key::Pause;
	}
	mud::Key DECL mud_Key_Home() {
		return mud::Key::Home;
	}
	mud::Key DECL mud_Key_Up() {
		return mud::Key::Up;
	}
	mud::Key DECL mud_Key_PageUp() {
		return mud::Key::PageUp;
	}
	mud::Key DECL mud_Key_Left() {
		return mud::Key::Left;
	}
	mud::Key DECL mud_Key_Right() {
		return mud::Key::Right;
	}
	mud::Key DECL mud_Key_End() {
		return mud::Key::End;
	}
	mud::Key DECL mud_Key_Down() {
		return mud::Key::Down;
	}
	mud::Key DECL mud_Key_PageDown() {
		return mud::Key::PageDown;
	}
	mud::Key DECL mud_Key_Insert() {
		return mud::Key::Insert;
	}
	mud::Key DECL mud_Key_Delete() {
		return mud::Key::Delete;
	}
	mud::Key DECL mud_Key_LeftWin() {
		return mud::Key::LeftWin;
	}
	mud::Key DECL mud_Key_RightWin() {
		return mud::Key::RightWin;
	}
	mud::Key DECL mud_Key_Translated() {
		return mud::Key::Translated;
	}
	// MouseButtonCode
	mud::MouseButtonCode DECL mud_MouseButtonCode_LEFT_BUTTON() {
		return mud::LEFT_BUTTON;
	}
	mud::MouseButtonCode DECL mud_MouseButtonCode_RIGHT_BUTTON() {
		return mud::RIGHT_BUTTON;
	}
	mud::MouseButtonCode DECL mud_MouseButtonCode_MIDDLE_BUTTON() {
		return mud::MIDDLE_BUTTON;
	}
	mud::MouseButtonCode DECL mud_MouseButtonCode_NO_BUTTON() {
		return mud::NO_BUTTON;
	}
	
}


