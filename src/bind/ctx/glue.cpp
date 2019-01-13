#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <ctx/Api.h>
#include <emscripten.h>


extern "C" {
	
	// Not using size_t for array indices as the values used by the javascript code are signed.
	void array_bounds_check(const int array_size, const int array_idx) {
		  if (array_idx < 0 || array_idx >= array_size) {
			    EM_ASM({
				      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';
				    }, array_idx, array_size);
			  }
	}
	// Context
	void EMSCRIPTEN_KEEPALIVE Context_reset_2(mud::Context* self, uint16_t width, uint16_t height) {
		self->reset(width, height);
	}
	void EMSCRIPTEN_KEEPALIVE Context_init_input_2(mud::Context* self, mud::Mouse* mouse, mud::Keyboard* keyboard) {
		self->init_input(*mouse, *keyboard);
	}
	bool EMSCRIPTEN_KEEPALIVE Context_next_frame_0(mud::Context* self) {
		return self->next_frame();
	}
	void EMSCRIPTEN_KEEPALIVE Context_lock_mouse_1(mud::Context* self, bool locked) {
		self->lock_mouse(locked);
	}
	const std::string EMSCRIPTEN_KEEPALIVE Context_get_resource_path(mud::Context* self) {
		return self->m_resource_path;
	}
	std::string EMSCRIPTEN_KEEPALIVE Context_get_title(mud::Context* self) {
		return self->m_title;
	}
	unsigned int EMSCRIPTEN_KEEPALIVE Context_get_width(mud::Context* self) {
		return self->m_width;
	}
	unsigned int EMSCRIPTEN_KEEPALIVE Context_get_height(mud::Context* self) {
		return self->m_height;
	}
	bool EMSCRIPTEN_KEEPALIVE Context_get_full_screen(mud::Context* self) {
		return self->m_full_screen;
	}
	bool EMSCRIPTEN_KEEPALIVE Context_get_active(mud::Context* self) {
		return self->m_active;
	}
	bool EMSCRIPTEN_KEEPALIVE Context_get_shutdown(mud::Context* self) {
		return self->m_shutdown;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE Context_get_cursor(mud::Context* self) {
		static mud::vec2 temp;
		return (temp = &self->m_cursor, &temp);
	}
	bool EMSCRIPTEN_KEEPALIVE Context_get_mouse_lock(mud::Context* self) {
		return self->m_mouse_lock;
	}
	void EMSCRIPTEN_KEEPALIVE Context___destroy__(mud::Context* self) {
		delete self;
	}
	// ControlNode
	void EMSCRIPTEN_KEEPALIVE ControlNode___destroy__(mud::ControlNode* self) {
		delete self;
	}
	// InputEvent
	mud::InputEvent* EMSCRIPTEN_KEEPALIVE InputEvent_InputEvent_0() {
		return new mud::InputEvent();
	}
	mud::InputEvent* EMSCRIPTEN_KEEPALIVE InputEvent_consume_1(mud::InputEvent* self, mud::ControlNode* consumer) {
		return &self->consume(*consumer);
	}
	bool EMSCRIPTEN_KEEPALIVE InputEvent_valid_0(mud::InputEvent* self) {
		return self->valid();
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE InputEvent_get_deviceType(mud::InputEvent* self) {
		static mud::DeviceType temp;
		return (temp = &self->m_deviceType, &temp);
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE InputEvent_get_eventType(mud::InputEvent* self) {
		static mud::EventType temp;
		return (temp = &self->m_eventType, &temp);
	}
	mud::ControlNode* EMSCRIPTEN_KEEPALIVE InputEvent_get_receiver(mud::InputEvent* self) {
		return self->m_receiver;
	}
	mud::ControlNode* EMSCRIPTEN_KEEPALIVE InputEvent_get_consumer(mud::InputEvent* self) {
		return self->m_consumer;
	}
	bool EMSCRIPTEN_KEEPALIVE InputEvent_get_abort(mud::InputEvent* self) {
		return self->m_abort;
	}
	mud::InputMod EMSCRIPTEN_KEEPALIVE InputEvent_get_modifiers(mud::InputEvent* self) {
		static mud::InputMod temp;
		return (temp = &self->m_modifiers, &temp);
	}
	int EMSCRIPTEN_KEEPALIVE InputEvent_get_key(mud::InputEvent* self) {
		return self->m_key;
	}
	void EMSCRIPTEN_KEEPALIVE InputEvent___destroy__(mud::InputEvent* self) {
		delete self;
	}
	// Keyboard
	void EMSCRIPTEN_KEEPALIVE Keyboard___destroy__(mud::Keyboard* self) {
		delete self;
	}
	// Mouse
	void EMSCRIPTEN_KEEPALIVE Mouse___destroy__(mud::Mouse* self) {
		delete self;
	}
	// RenderSystem
	void EMSCRIPTEN_KEEPALIVE RenderSystem___destroy__(mud::RenderSystem* self) {
		delete self;
	}
	// KeyEvent
	mud::KeyEvent* EMSCRIPTEN_KEEPALIVE KeyEvent_KeyEvent_0() {
		return new mud::KeyEvent();
	}
	mud::Key EMSCRIPTEN_KEEPALIVE KeyEvent_get_code(mud::KeyEvent* self) {
		static mud::Key temp;
		return (temp = &self->m_code, &temp);
	}
	char EMSCRIPTEN_KEEPALIVE KeyEvent_get_char(mud::KeyEvent* self) {
		return self->m_char;
	}
	void EMSCRIPTEN_KEEPALIVE KeyEvent___destroy__(mud::KeyEvent* self) {
		delete self;
	}
	// MouseEvent
	mud::MouseEvent* EMSCRIPTEN_KEEPALIVE MouseEvent_MouseEvent_0() {
		return new mud::MouseEvent();
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE MouseEvent_get_pos(mud::MouseEvent* self) {
		static mud::vec2 temp;
		return (temp = &self->m_pos, &temp);
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE MouseEvent_get_relative(mud::MouseEvent* self) {
		static mud::vec2 temp;
		return (temp = &self->m_relative, &temp);
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE MouseEvent_get_delta(mud::MouseEvent* self) {
		static mud::vec2 temp;
		return (temp = &self->m_delta, &temp);
	}
	float EMSCRIPTEN_KEEPALIVE MouseEvent_get_deltaZ(mud::MouseEvent* self) {
		return self->m_deltaZ;
	}
	mud::vec2* EMSCRIPTEN_KEEPALIVE MouseEvent_get_pressed(mud::MouseEvent* self) {
		static mud::vec2 temp;
		return (temp = &self->m_pressed, &temp);
	}
	mud::MouseButtonCode EMSCRIPTEN_KEEPALIVE MouseEvent_get_button(mud::MouseEvent* self) {
		static mud::MouseButtonCode temp;
		return (temp = &self->m_button, &temp);
	}
	void EMSCRIPTEN_KEEPALIVE MouseEvent___destroy__(mud::MouseEvent* self) {
		delete self;
	}
	// DeviceType
	mud::DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_None() {
		return mud::DeviceType::None;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_Keyboard() {
		return mud::DeviceType::Keyboard;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_Mouse() {
		return mud::DeviceType::Mouse;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_MouseLeft() {
		return mud::DeviceType::MouseLeft;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_MouseRight() {
		return mud::DeviceType::MouseRight;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_MouseMiddle() {
		return mud::DeviceType::MouseMiddle;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_Touch() {
		return mud::DeviceType::Touch;
	}
	mud::DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_Count() {
		return mud::DeviceType::Count;
	}
	// EventType
	mud::EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_None() {
		return mud::EventType::None;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Heartbeat() {
		return mud::EventType::Heartbeat;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Moved() {
		return mud::EventType::Moved;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Pressed() {
		return mud::EventType::Pressed;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Released() {
		return mud::EventType::Released;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Stroked() {
		return mud::EventType::Stroked;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_DoubleStroked() {
		return mud::EventType::DoubleStroked;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Dragged() {
		return mud::EventType::Dragged;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_DraggedTarget() {
		return mud::EventType::DraggedTarget;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_DragStarted() {
		return mud::EventType::DragStarted;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_DragEnded() {
		return mud::EventType::DragEnded;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Dropped() {
		return mud::EventType::Dropped;
	}
	mud::EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Count() {
		return mud::EventType::Count;
	}
	// InputMod
	mud::InputMod EMSCRIPTEN_KEEPALIVE emscripten_enum_InputMod_None() {
		return mud::InputMod::None;
	}
	mud::InputMod EMSCRIPTEN_KEEPALIVE emscripten_enum_InputMod_Shift() {
		return mud::InputMod::Shift;
	}
	mud::InputMod EMSCRIPTEN_KEEPALIVE emscripten_enum_InputMod_Ctrl() {
		return mud::InputMod::Ctrl;
	}
	mud::InputMod EMSCRIPTEN_KEEPALIVE emscripten_enum_InputMod_Alt() {
		return mud::InputMod::Alt;
	}
	mud::InputMod EMSCRIPTEN_KEEPALIVE emscripten_enum_InputMod_Any() {
		return mud::InputMod::Any;
	}
	// Key
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Unassigned() {
		return mud::Key::Unassigned;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Escape() {
		return mud::Key::Escape;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num1() {
		return mud::Key::Num1;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num2() {
		return mud::Key::Num2;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num3() {
		return mud::Key::Num3;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num4() {
		return mud::Key::Num4;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num5() {
		return mud::Key::Num5;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num6() {
		return mud::Key::Num6;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num7() {
		return mud::Key::Num7;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num8() {
		return mud::Key::Num8;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num9() {
		return mud::Key::Num9;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num0() {
		return mud::Key::Num0;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Minus() {
		return mud::Key::Minus;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Equals() {
		return mud::Key::Equals;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Back() {
		return mud::Key::Back;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Tab() {
		return mud::Key::Tab;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Q() {
		return mud::Key::Q;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_W() {
		return mud::Key::W;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_E() {
		return mud::Key::E;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_R() {
		return mud::Key::R;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_T() {
		return mud::Key::T;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Y() {
		return mud::Key::Y;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_U() {
		return mud::Key::U;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_I() {
		return mud::Key::I;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_O() {
		return mud::Key::O;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_P() {
		return mud::Key::P;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_LeftBracket() {
		return mud::Key::LeftBracket;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_RightBracket() {
		return mud::Key::RightBracket;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Return() {
		return mud::Key::Return;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_LeftControl() {
		return mud::Key::LeftControl;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_A() {
		return mud::Key::A;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_S() {
		return mud::Key::S;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_D() {
		return mud::Key::D;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F() {
		return mud::Key::F;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_G() {
		return mud::Key::G;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_H() {
		return mud::Key::H;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_J() {
		return mud::Key::J;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_K() {
		return mud::Key::K;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_L() {
		return mud::Key::L;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Semicolon() {
		return mud::Key::Semicolon;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Apostrophe() {
		return mud::Key::Apostrophe;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Grave() {
		return mud::Key::Grave;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_LeftShift() {
		return mud::Key::LeftShift;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Backslash() {
		return mud::Key::Backslash;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Z() {
		return mud::Key::Z;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_X() {
		return mud::Key::X;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_C() {
		return mud::Key::C;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_V() {
		return mud::Key::V;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_B() {
		return mud::Key::B;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_N() {
		return mud::Key::N;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_M() {
		return mud::Key::M;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Comma() {
		return mud::Key::Comma;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Period() {
		return mud::Key::Period;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Slash() {
		return mud::Key::Slash;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_RightShift() {
		return mud::Key::RightShift;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Multiply() {
		return mud::Key::Multiply;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_LeftAlt() {
		return mud::Key::LeftAlt;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Space() {
		return mud::Key::Space;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Capital() {
		return mud::Key::Capital;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F1() {
		return mud::Key::F1;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F2() {
		return mud::Key::F2;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F3() {
		return mud::Key::F3;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F4() {
		return mud::Key::F4;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F5() {
		return mud::Key::F5;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F6() {
		return mud::Key::F6;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F7() {
		return mud::Key::F7;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F8() {
		return mud::Key::F8;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F9() {
		return mud::Key::F9;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F10() {
		return mud::Key::F10;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numlock() {
		return mud::Key::Numlock;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_ScrollLock() {
		return mud::Key::ScrollLock;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad7() {
		return mud::Key::Numpad7;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad8() {
		return mud::Key::Numpad8;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad9() {
		return mud::Key::Numpad9;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Subtract() {
		return mud::Key::Subtract;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad4() {
		return mud::Key::Numpad4;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad5() {
		return mud::Key::Numpad5;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad6() {
		return mud::Key::Numpad6;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Add() {
		return mud::Key::Add;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad1() {
		return mud::Key::Numpad1;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad2() {
		return mud::Key::Numpad2;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad3() {
		return mud::Key::Numpad3;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad0() {
		return mud::Key::Numpad0;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Decimal() {
		return mud::Key::Decimal;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F11() {
		return mud::Key::F11;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F12() {
		return mud::Key::F12;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F13() {
		return mud::Key::F13;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F14() {
		return mud::Key::F14;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F15() {
		return mud::Key::F15;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_NumpadEquals() {
		return mud::Key::NumpadEquals;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_NumpadEnter() {
		return mud::Key::NumpadEnter;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_RightControl() {
		return mud::Key::RightControl;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Mute() {
		return mud::Key::Mute;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_NumpadComma() {
		return mud::Key::NumpadComma;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Divide() {
		return mud::Key::Divide;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_RightAlt() {
		return mud::Key::RightAlt;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Pause() {
		return mud::Key::Pause;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Home() {
		return mud::Key::Home;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Up() {
		return mud::Key::Up;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_PageUp() {
		return mud::Key::PageUp;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Left() {
		return mud::Key::Left;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Right() {
		return mud::Key::Right;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_End() {
		return mud::Key::End;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Down() {
		return mud::Key::Down;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_PageDown() {
		return mud::Key::PageDown;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Insert() {
		return mud::Key::Insert;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Delete() {
		return mud::Key::Delete;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_LeftWin() {
		return mud::Key::LeftWin;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_RightWin() {
		return mud::Key::RightWin;
	}
	mud::Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Translated() {
		return mud::Key::Translated;
	}
	// MouseButtonCode
	mud::MouseButtonCode EMSCRIPTEN_KEEPALIVE emscripten_enum_MouseButtonCode_LEFT_BUTTON() {
		return mud::LEFT_BUTTON;
	}
	mud::MouseButtonCode EMSCRIPTEN_KEEPALIVE emscripten_enum_MouseButtonCode_RIGHT_BUTTON() {
		return mud::RIGHT_BUTTON;
	}
	mud::MouseButtonCode EMSCRIPTEN_KEEPALIVE emscripten_enum_MouseButtonCode_MIDDLE_BUTTON() {
		return mud::MIDDLE_BUTTON;
	}
	mud::MouseButtonCode EMSCRIPTEN_KEEPALIVE emscripten_enum_MouseButtonCode_NO_BUTTON() {
		return mud::NO_BUTTON;
	}
	
}


