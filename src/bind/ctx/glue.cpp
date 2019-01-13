#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <ctx/Api.h>
#include <emscripten.h>
#include <cstdint>


extern "C" {
	
	// Context
	void EMSCRIPTEN_KEEPALIVE mud_Context_init_input_2(mud::Context* self, mud::Mouse* mouse, mud::Keyboard* keyboard) {
		self->init_input(*mouse, *keyboard);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Context_lock_mouse_1(mud::Context* self, bool locked) {
		self->lock_mouse(locked);
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Context_next_frame_0(mud::Context* self) {
		return self->next_frame();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Context_reset_2(mud::Context* self, uint16_t width, uint16_t height) {
		self->reset(width, height);
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_Context_get_resource_path(mud::Context* self) {
		return self->m_resource_path.c_str();
	}
	const char* EMSCRIPTEN_KEEPALIVE mud_Context_get_title(mud::Context* self) {
		return self->m_title.c_str();
	}
	void EMSCRIPTEN_KEEPALIVE mud_Context_set_title(mud::Context* self, const char* value) {
		self->m_title = value;
	}
	unsigned int EMSCRIPTEN_KEEPALIVE mud_Context_get_width(mud::Context* self) {
		return self->m_width;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Context_set_width(mud::Context* self, unsigned int value) {
		self->m_width = value;
	}
	unsigned int EMSCRIPTEN_KEEPALIVE mud_Context_get_height(mud::Context* self) {
		return self->m_height;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Context_set_height(mud::Context* self, unsigned int value) {
		self->m_height = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Context_get_full_screen(mud::Context* self) {
		return self->m_full_screen;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Context_set_full_screen(mud::Context* self, bool value) {
		self->m_full_screen = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Context_get_active(mud::Context* self) {
		return self->m_active;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Context_set_active(mud::Context* self, bool value) {
		self->m_active = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Context_get_shutdown(mud::Context* self) {
		return self->m_shutdown;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Context_set_shutdown(mud::Context* self, bool value) {
		self->m_shutdown = value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_Context_get_cursor(mud::Context* self) {
		static mud::vec2 temp;
		return (temp = self->m_cursor, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_Context_set_cursor(mud::Context* self, mud::vec2* value) {
		self->m_cursor = *value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_Context_get_mouse_lock(mud::Context* self) {
		return self->m_mouse_lock;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Context_set_mouse_lock(mud::Context* self, bool value) {
		self->m_mouse_lock = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_Context___destroy__(mud::Context* self) {
		delete self;
	}
	// ControlNode
	void EMSCRIPTEN_KEEPALIVE mud_ControlNode___destroy__(mud::ControlNode* self) {
		delete self;
	}
	// InputEvent
	mud::InputEvent* EMSCRIPTEN_KEEPALIVE mud_InputEvent_InputEvent_0() {
		return new mud::InputEvent();
	}
	mud::InputEvent* EMSCRIPTEN_KEEPALIVE mud_InputEvent_consume_1(mud::InputEvent* self, mud::ControlNode* consumer) {
		return &self->consume(*consumer);
	}
	bool EMSCRIPTEN_KEEPALIVE mud_InputEvent_valid_0(mud::InputEvent* self) {
		return self->valid();
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE mud_InputEvent_get_deviceType(mud::InputEvent* self) {
		return self->m_deviceType;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InputEvent_set_deviceType(mud::InputEvent* self, mud::DeviceType value) {
		self->m_deviceType = value;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_InputEvent_get_eventType(mud::InputEvent* self) {
		return self->m_eventType;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InputEvent_set_eventType(mud::InputEvent* self, mud::EventType value) {
		self->m_eventType = value;
	}
	mud::ControlNode* EMSCRIPTEN_KEEPALIVE mud_InputEvent_get_receiver(mud::InputEvent* self) {
		return self->m_receiver;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InputEvent_set_receiver(mud::InputEvent* self, mud::ControlNode* value) {
		self->m_receiver = value;
	}
	mud::ControlNode* EMSCRIPTEN_KEEPALIVE mud_InputEvent_get_consumer(mud::InputEvent* self) {
		return self->m_consumer;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InputEvent_set_consumer(mud::InputEvent* self, mud::ControlNode* value) {
		self->m_consumer = value;
	}
	bool EMSCRIPTEN_KEEPALIVE mud_InputEvent_get_abort(mud::InputEvent* self) {
		return self->m_abort;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InputEvent_set_abort(mud::InputEvent* self, bool value) {
		self->m_abort = value;
	}
	mud::InputMod EMSCRIPTEN_KEEPALIVE mud_InputEvent_get_modifiers(mud::InputEvent* self) {
		return self->m_modifiers;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InputEvent_set_modifiers(mud::InputEvent* self, mud::InputMod value) {
		self->m_modifiers = value;
	}
	int EMSCRIPTEN_KEEPALIVE mud_InputEvent_get_key(mud::InputEvent* self) {
		return self->m_key;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InputEvent_set_key(mud::InputEvent* self, int value) {
		self->m_key = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_InputEvent___destroy__(mud::InputEvent* self) {
		delete self;
	}
	// Keyboard
	void EMSCRIPTEN_KEEPALIVE mud_Keyboard___destroy__(mud::Keyboard* self) {
		delete self;
	}
	// Mouse
	void EMSCRIPTEN_KEEPALIVE mud_Mouse___destroy__(mud::Mouse* self) {
		delete self;
	}
	// RenderSystem
	void EMSCRIPTEN_KEEPALIVE mud_RenderSystem___destroy__(mud::RenderSystem* self) {
		delete self;
	}
	// KeyEvent
	mud::KeyEvent* EMSCRIPTEN_KEEPALIVE mud_KeyEvent_KeyEvent_0() {
		return new mud::KeyEvent();
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_KeyEvent_get_code(mud::KeyEvent* self) {
		return self->m_code;
	}
	void EMSCRIPTEN_KEEPALIVE mud_KeyEvent_set_code(mud::KeyEvent* self, mud::Key value) {
		self->m_code = value;
	}
	char EMSCRIPTEN_KEEPALIVE mud_KeyEvent_get_char(mud::KeyEvent* self) {
		return self->m_char;
	}
	void EMSCRIPTEN_KEEPALIVE mud_KeyEvent_set_char(mud::KeyEvent* self, char value) {
		self->m_char = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_KeyEvent___destroy__(mud::KeyEvent* self) {
		delete self;
	}
	// MouseEvent
	mud::MouseEvent* EMSCRIPTEN_KEEPALIVE mud_MouseEvent_MouseEvent_0() {
		return new mud::MouseEvent();
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_MouseEvent_get_pos(mud::MouseEvent* self) {
		static mud::vec2 temp;
		return (temp = self->m_pos, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_MouseEvent_set_pos(mud::MouseEvent* self, mud::vec2* value) {
		self->m_pos = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_MouseEvent_get_relative(mud::MouseEvent* self) {
		static mud::vec2 temp;
		return (temp = self->m_relative, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_MouseEvent_set_relative(mud::MouseEvent* self, mud::vec2* value) {
		self->m_relative = *value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_MouseEvent_get_delta(mud::MouseEvent* self) {
		static mud::vec2 temp;
		return (temp = self->m_delta, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_MouseEvent_set_delta(mud::MouseEvent* self, mud::vec2* value) {
		self->m_delta = *value;
	}
	float EMSCRIPTEN_KEEPALIVE mud_MouseEvent_get_deltaZ(mud::MouseEvent* self) {
		return self->m_deltaZ;
	}
	void EMSCRIPTEN_KEEPALIVE mud_MouseEvent_set_deltaZ(mud::MouseEvent* self, float value) {
		self->m_deltaZ = value;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE mud_MouseEvent_get_pressed(mud::MouseEvent* self) {
		static mud::vec2 temp;
		return (temp = self->m_pressed, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE mud_MouseEvent_set_pressed(mud::MouseEvent* self, mud::vec2* value) {
		self->m_pressed = *value;
	}
	mud::MouseButtonCode EMSCRIPTEN_KEEPALIVE mud_MouseEvent_get_button(mud::MouseEvent* self) {
		return self->m_button;
	}
	void EMSCRIPTEN_KEEPALIVE mud_MouseEvent_set_button(mud::MouseEvent* self, mud::MouseButtonCode value) {
		self->m_button = value;
	}
	void EMSCRIPTEN_KEEPALIVE mud_MouseEvent___destroy__(mud::MouseEvent* self) {
		delete self;
	}
	// DeviceType
	mud::DeviceType EMSCRIPTEN_KEEPALIVE mud_DeviceType_None() {
		return mud::DeviceType::None;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE mud_DeviceType_Keyboard() {
		return mud::DeviceType::Keyboard;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE mud_DeviceType_Mouse() {
		return mud::DeviceType::Mouse;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE mud_DeviceType_MouseLeft() {
		return mud::DeviceType::MouseLeft;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE mud_DeviceType_MouseRight() {
		return mud::DeviceType::MouseRight;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE mud_DeviceType_MouseMiddle() {
		return mud::DeviceType::MouseMiddle;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE mud_DeviceType_Touch() {
		return mud::DeviceType::Touch;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE mud_DeviceType_Count() {
		return mud::DeviceType::Count;
	}
	// EventType
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_EventType_None() {
		return mud::EventType::None;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_EventType_Heartbeat() {
		return mud::EventType::Heartbeat;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_EventType_Moved() {
		return mud::EventType::Moved;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_EventType_Pressed() {
		return mud::EventType::Pressed;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_EventType_Released() {
		return mud::EventType::Released;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_EventType_Stroked() {
		return mud::EventType::Stroked;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_EventType_DoubleStroked() {
		return mud::EventType::DoubleStroked;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_EventType_Dragged() {
		return mud::EventType::Dragged;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_EventType_DraggedTarget() {
		return mud::EventType::DraggedTarget;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_EventType_DragStarted() {
		return mud::EventType::DragStarted;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_EventType_DragEnded() {
		return mud::EventType::DragEnded;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_EventType_Dropped() {
		return mud::EventType::Dropped;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE mud_EventType_Count() {
		return mud::EventType::Count;
	}
	// InputMod
	mud::InputMod EMSCRIPTEN_KEEPALIVE mud_InputMod_None() {
		return mud::InputMod::None;
	}
	mud::InputMod EMSCRIPTEN_KEEPALIVE mud_InputMod_Shift() {
		return mud::InputMod::Shift;
	}
	mud::InputMod EMSCRIPTEN_KEEPALIVE mud_InputMod_Ctrl() {
		return mud::InputMod::Ctrl;
	}
	mud::InputMod EMSCRIPTEN_KEEPALIVE mud_InputMod_Alt() {
		return mud::InputMod::Alt;
	}
	mud::InputMod EMSCRIPTEN_KEEPALIVE mud_InputMod_Any() {
		return mud::InputMod::Any;
	}
	// Key
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Unassigned() {
		return mud::Key::Unassigned;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Escape() {
		return mud::Key::Escape;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Num1() {
		return mud::Key::Num1;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Num2() {
		return mud::Key::Num2;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Num3() {
		return mud::Key::Num3;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Num4() {
		return mud::Key::Num4;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Num5() {
		return mud::Key::Num5;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Num6() {
		return mud::Key::Num6;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Num7() {
		return mud::Key::Num7;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Num8() {
		return mud::Key::Num8;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Num9() {
		return mud::Key::Num9;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Num0() {
		return mud::Key::Num0;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Minus() {
		return mud::Key::Minus;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Equals() {
		return mud::Key::Equals;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Back() {
		return mud::Key::Back;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Tab() {
		return mud::Key::Tab;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Q() {
		return mud::Key::Q;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_W() {
		return mud::Key::W;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_E() {
		return mud::Key::E;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_R() {
		return mud::Key::R;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_T() {
		return mud::Key::T;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Y() {
		return mud::Key::Y;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_U() {
		return mud::Key::U;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_I() {
		return mud::Key::I;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_O() {
		return mud::Key::O;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_P() {
		return mud::Key::P;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_LeftBracket() {
		return mud::Key::LeftBracket;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_RightBracket() {
		return mud::Key::RightBracket;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Return() {
		return mud::Key::Return;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_LeftControl() {
		return mud::Key::LeftControl;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_A() {
		return mud::Key::A;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_S() {
		return mud::Key::S;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_D() {
		return mud::Key::D;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F() {
		return mud::Key::F;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_G() {
		return mud::Key::G;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_H() {
		return mud::Key::H;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_J() {
		return mud::Key::J;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_K() {
		return mud::Key::K;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_L() {
		return mud::Key::L;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Semicolon() {
		return mud::Key::Semicolon;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Apostrophe() {
		return mud::Key::Apostrophe;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Grave() {
		return mud::Key::Grave;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_LeftShift() {
		return mud::Key::LeftShift;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Backslash() {
		return mud::Key::Backslash;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Z() {
		return mud::Key::Z;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_X() {
		return mud::Key::X;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_C() {
		return mud::Key::C;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_V() {
		return mud::Key::V;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_B() {
		return mud::Key::B;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_N() {
		return mud::Key::N;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_M() {
		return mud::Key::M;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Comma() {
		return mud::Key::Comma;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Period() {
		return mud::Key::Period;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Slash() {
		return mud::Key::Slash;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_RightShift() {
		return mud::Key::RightShift;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Multiply() {
		return mud::Key::Multiply;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_LeftAlt() {
		return mud::Key::LeftAlt;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Space() {
		return mud::Key::Space;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Capital() {
		return mud::Key::Capital;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F1() {
		return mud::Key::F1;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F2() {
		return mud::Key::F2;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F3() {
		return mud::Key::F3;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F4() {
		return mud::Key::F4;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F5() {
		return mud::Key::F5;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F6() {
		return mud::Key::F6;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F7() {
		return mud::Key::F7;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F8() {
		return mud::Key::F8;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F9() {
		return mud::Key::F9;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F10() {
		return mud::Key::F10;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Numlock() {
		return mud::Key::Numlock;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_ScrollLock() {
		return mud::Key::ScrollLock;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Numpad7() {
		return mud::Key::Numpad7;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Numpad8() {
		return mud::Key::Numpad8;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Numpad9() {
		return mud::Key::Numpad9;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Subtract() {
		return mud::Key::Subtract;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Numpad4() {
		return mud::Key::Numpad4;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Numpad5() {
		return mud::Key::Numpad5;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Numpad6() {
		return mud::Key::Numpad6;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Add() {
		return mud::Key::Add;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Numpad1() {
		return mud::Key::Numpad1;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Numpad2() {
		return mud::Key::Numpad2;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Numpad3() {
		return mud::Key::Numpad3;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Numpad0() {
		return mud::Key::Numpad0;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Decimal() {
		return mud::Key::Decimal;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F11() {
		return mud::Key::F11;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F12() {
		return mud::Key::F12;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F13() {
		return mud::Key::F13;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F14() {
		return mud::Key::F14;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_F15() {
		return mud::Key::F15;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_NumpadEquals() {
		return mud::Key::NumpadEquals;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_NumpadEnter() {
		return mud::Key::NumpadEnter;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_RightControl() {
		return mud::Key::RightControl;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Mute() {
		return mud::Key::Mute;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_NumpadComma() {
		return mud::Key::NumpadComma;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Divide() {
		return mud::Key::Divide;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_RightAlt() {
		return mud::Key::RightAlt;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Pause() {
		return mud::Key::Pause;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Home() {
		return mud::Key::Home;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Up() {
		return mud::Key::Up;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_PageUp() {
		return mud::Key::PageUp;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Left() {
		return mud::Key::Left;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Right() {
		return mud::Key::Right;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_End() {
		return mud::Key::End;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Down() {
		return mud::Key::Down;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_PageDown() {
		return mud::Key::PageDown;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Insert() {
		return mud::Key::Insert;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Delete() {
		return mud::Key::Delete;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_LeftWin() {
		return mud::Key::LeftWin;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_RightWin() {
		return mud::Key::RightWin;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE mud_Key_Translated() {
		return mud::Key::Translated;
	}
	// MouseButtonCode
	mud::MouseButtonCode EMSCRIPTEN_KEEPALIVE mud_MouseButtonCode_LEFT_BUTTON() {
		return mud::LEFT_BUTTON;
	}
	mud::MouseButtonCode EMSCRIPTEN_KEEPALIVE mud_MouseButtonCode_RIGHT_BUTTON() {
		return mud::RIGHT_BUTTON;
	}
	mud::MouseButtonCode EMSCRIPTEN_KEEPALIVE mud_MouseButtonCode_MIDDLE_BUTTON() {
		return mud::MIDDLE_BUTTON;
	}
	mud::MouseButtonCode EMSCRIPTEN_KEEPALIVE mud_MouseButtonCode_NO_BUTTON() {
		return mud::NO_BUTTON;
	}
	
}


