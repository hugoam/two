#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
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
	void EMSCRIPTEN_KEEPALIVE Context_init_input_2(mud::Context* self, Mouse mouse, Keyboard keyboard) {
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
	vec2 EMSCRIPTEN_KEEPALIVE Context_get_cursor(mud::Context* self) {
		return self->m_cursor;
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
	InputEvent EMSCRIPTEN_KEEPALIVE InputEvent_consume_1(mud::InputEvent* self, ControlNode consumer) {
		return self->consume(*consumer);
	}
	bool EMSCRIPTEN_KEEPALIVE InputEvent_valid_0(mud::InputEvent* self) {
		return self->valid();
	}
	DeviceType EMSCRIPTEN_KEEPALIVE InputEvent_get_deviceType(mud::InputEvent* self) {
		return self->m_deviceType;
	}
	EventType EMSCRIPTEN_KEEPALIVE InputEvent_get_eventType(mud::InputEvent* self) {
		return self->m_eventType;
	}
	ControlNode EMSCRIPTEN_KEEPALIVE InputEvent_get_receiver(mud::InputEvent* self) {
		return self->m_receiver;
	}
	ControlNode EMSCRIPTEN_KEEPALIVE InputEvent_get_consumer(mud::InputEvent* self) {
		return self->m_consumer;
	}
	bool EMSCRIPTEN_KEEPALIVE InputEvent_get_abort(mud::InputEvent* self) {
		return self->m_abort;
	}
	InputMod EMSCRIPTEN_KEEPALIVE InputEvent_get_modifiers(mud::InputEvent* self) {
		return self->m_modifiers;
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
	Key EMSCRIPTEN_KEEPALIVE KeyEvent_get_code(mud::KeyEvent* self) {
		return self->m_code;
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
	vec2 EMSCRIPTEN_KEEPALIVE MouseEvent_get_pos(mud::MouseEvent* self) {
		return self->m_pos;
	}
	vec2 EMSCRIPTEN_KEEPALIVE MouseEvent_get_relative(mud::MouseEvent* self) {
		return self->m_relative;
	}
	vec2 EMSCRIPTEN_KEEPALIVE MouseEvent_get_delta(mud::MouseEvent* self) {
		return self->m_delta;
	}
	float EMSCRIPTEN_KEEPALIVE MouseEvent_get_deltaZ(mud::MouseEvent* self) {
		return self->m_deltaZ;
	}
	vec2 EMSCRIPTEN_KEEPALIVE MouseEvent_get_pressed(mud::MouseEvent* self) {
		return self->m_pressed;
	}
	MouseButtonCode EMSCRIPTEN_KEEPALIVE MouseEvent_get_button(mud::MouseEvent* self) {
		return self->m_button;
	}
	void EMSCRIPTEN_KEEPALIVE MouseEvent___destroy__(mud::MouseEvent* self) {
		delete self;
	}
	
}


// 'DeviceType'
DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_None() {
	return mud::DeviceType::None;
}
DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_Keyboard() {
	return mud::DeviceType::Keyboard;
}
DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_Mouse() {
	return mud::DeviceType::Mouse;
}
DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_MouseLeft() {
	return mud::DeviceType::MouseLeft;
}
DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_MouseRight() {
	return mud::DeviceType::MouseRight;
}
DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_MouseMiddle() {
	return mud::DeviceType::MouseMiddle;
}
DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_Touch() {
	return mud::DeviceType::Touch;
}
DeviceType EMSCRIPTEN_KEEPALIVE emscripten_enum_DeviceType_Count() {
	return mud::DeviceType::Count;
}
// 'EventType'
EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_None() {
	return mud::EventType::None;
}
EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Heartbeat() {
	return mud::EventType::Heartbeat;
}
EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Moved() {
	return mud::EventType::Moved;
}
EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Pressed() {
	return mud::EventType::Pressed;
}
EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Released() {
	return mud::EventType::Released;
}
EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Stroked() {
	return mud::EventType::Stroked;
}
EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_DoubleStroked() {
	return mud::EventType::DoubleStroked;
}
EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Dragged() {
	return mud::EventType::Dragged;
}
EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_DraggedTarget() {
	return mud::EventType::DraggedTarget;
}
EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_DragStarted() {
	return mud::EventType::DragStarted;
}
EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_DragEnded() {
	return mud::EventType::DragEnded;
}
EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Dropped() {
	return mud::EventType::Dropped;
}
EventType EMSCRIPTEN_KEEPALIVE emscripten_enum_EventType_Count() {
	return mud::EventType::Count;
}
// 'InputMod'
InputMod EMSCRIPTEN_KEEPALIVE emscripten_enum_InputMod_None() {
	return mud::InputMod::None;
}
InputMod EMSCRIPTEN_KEEPALIVE emscripten_enum_InputMod_Shift() {
	return mud::InputMod::Shift;
}
InputMod EMSCRIPTEN_KEEPALIVE emscripten_enum_InputMod_Ctrl() {
	return mud::InputMod::Ctrl;
}
InputMod EMSCRIPTEN_KEEPALIVE emscripten_enum_InputMod_Alt() {
	return mud::InputMod::Alt;
}
InputMod EMSCRIPTEN_KEEPALIVE emscripten_enum_InputMod_Any() {
	return mud::InputMod::Any;
}
// 'Key'
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Unassigned() {
	return mud::Key::Unassigned;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Escape() {
	return mud::Key::Escape;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num1() {
	return mud::Key::Num1;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num2() {
	return mud::Key::Num2;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num3() {
	return mud::Key::Num3;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num4() {
	return mud::Key::Num4;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num5() {
	return mud::Key::Num5;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num6() {
	return mud::Key::Num6;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num7() {
	return mud::Key::Num7;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num8() {
	return mud::Key::Num8;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num9() {
	return mud::Key::Num9;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Num0() {
	return mud::Key::Num0;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Minus() {
	return mud::Key::Minus;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Equals() {
	return mud::Key::Equals;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Back() {
	return mud::Key::Back;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Tab() {
	return mud::Key::Tab;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Q() {
	return mud::Key::Q;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_W() {
	return mud::Key::W;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_E() {
	return mud::Key::E;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_R() {
	return mud::Key::R;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_T() {
	return mud::Key::T;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Y() {
	return mud::Key::Y;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_U() {
	return mud::Key::U;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_I() {
	return mud::Key::I;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_O() {
	return mud::Key::O;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_P() {
	return mud::Key::P;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_LeftBracket() {
	return mud::Key::LeftBracket;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_RightBracket() {
	return mud::Key::RightBracket;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Return() {
	return mud::Key::Return;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_LeftControl() {
	return mud::Key::LeftControl;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_A() {
	return mud::Key::A;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_S() {
	return mud::Key::S;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_D() {
	return mud::Key::D;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F() {
	return mud::Key::F;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_G() {
	return mud::Key::G;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_H() {
	return mud::Key::H;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_J() {
	return mud::Key::J;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_K() {
	return mud::Key::K;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_L() {
	return mud::Key::L;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Semicolon() {
	return mud::Key::Semicolon;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Apostrophe() {
	return mud::Key::Apostrophe;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Grave() {
	return mud::Key::Grave;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_LeftShift() {
	return mud::Key::LeftShift;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Backslash() {
	return mud::Key::Backslash;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Z() {
	return mud::Key::Z;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_X() {
	return mud::Key::X;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_C() {
	return mud::Key::C;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_V() {
	return mud::Key::V;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_B() {
	return mud::Key::B;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_N() {
	return mud::Key::N;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_M() {
	return mud::Key::M;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Comma() {
	return mud::Key::Comma;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Period() {
	return mud::Key::Period;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Slash() {
	return mud::Key::Slash;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_RightShift() {
	return mud::Key::RightShift;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Multiply() {
	return mud::Key::Multiply;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_LeftAlt() {
	return mud::Key::LeftAlt;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Space() {
	return mud::Key::Space;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Capital() {
	return mud::Key::Capital;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F1() {
	return mud::Key::F1;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F2() {
	return mud::Key::F2;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F3() {
	return mud::Key::F3;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F4() {
	return mud::Key::F4;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F5() {
	return mud::Key::F5;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F6() {
	return mud::Key::F6;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F7() {
	return mud::Key::F7;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F8() {
	return mud::Key::F8;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F9() {
	return mud::Key::F9;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F10() {
	return mud::Key::F10;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numlock() {
	return mud::Key::Numlock;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_ScrollLock() {
	return mud::Key::ScrollLock;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad7() {
	return mud::Key::Numpad7;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad8() {
	return mud::Key::Numpad8;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad9() {
	return mud::Key::Numpad9;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Subtract() {
	return mud::Key::Subtract;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad4() {
	return mud::Key::Numpad4;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad5() {
	return mud::Key::Numpad5;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad6() {
	return mud::Key::Numpad6;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Add() {
	return mud::Key::Add;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad1() {
	return mud::Key::Numpad1;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad2() {
	return mud::Key::Numpad2;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad3() {
	return mud::Key::Numpad3;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Numpad0() {
	return mud::Key::Numpad0;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Decimal() {
	return mud::Key::Decimal;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F11() {
	return mud::Key::F11;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F12() {
	return mud::Key::F12;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F13() {
	return mud::Key::F13;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F14() {
	return mud::Key::F14;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_F15() {
	return mud::Key::F15;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_NumpadEquals() {
	return mud::Key::NumpadEquals;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_NumpadEnter() {
	return mud::Key::NumpadEnter;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_RightControl() {
	return mud::Key::RightControl;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Mute() {
	return mud::Key::Mute;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_NumpadComma() {
	return mud::Key::NumpadComma;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Divide() {
	return mud::Key::Divide;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_RightAlt() {
	return mud::Key::RightAlt;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Pause() {
	return mud::Key::Pause;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Home() {
	return mud::Key::Home;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Up() {
	return mud::Key::Up;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_PageUp() {
	return mud::Key::PageUp;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Left() {
	return mud::Key::Left;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Right() {
	return mud::Key::Right;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_End() {
	return mud::Key::End;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Down() {
	return mud::Key::Down;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_PageDown() {
	return mud::Key::PageDown;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Insert() {
	return mud::Key::Insert;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Delete() {
	return mud::Key::Delete;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_LeftWin() {
	return mud::Key::LeftWin;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_RightWin() {
	return mud::Key::RightWin;
}
Key EMSCRIPTEN_KEEPALIVE emscripten_enum_Key_Translated() {
	return mud::Key::Translated;
}
// 'MouseButtonCode'
MouseButtonCode EMSCRIPTEN_KEEPALIVE emscripten_enum_MouseButtonCode_LEFT_BUTTON() {
	return mud::LEFT_BUTTON;
}
MouseButtonCode EMSCRIPTEN_KEEPALIVE emscripten_enum_MouseButtonCode_RIGHT_BUTTON() {
	return mud::RIGHT_BUTTON;
}
MouseButtonCode EMSCRIPTEN_KEEPALIVE emscripten_enum_MouseButtonCode_MIDDLE_BUTTON() {
	return mud::MIDDLE_BUTTON;
}
MouseButtonCode EMSCRIPTEN_KEEPALIVE emscripten_enum_MouseButtonCode_NO_BUTTON() {
	return mud::NO_BUTTON;
}
