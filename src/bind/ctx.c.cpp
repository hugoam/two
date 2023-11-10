#include <infra/Api.h>
#include <type/Api.h>
#include <math/Api.h>
#include <ctx/Api.h>

#ifdef TWO_PLATFORM_EMSCRIPTEN
#include <emscripten.h>
#define DECL EMSCRIPTEN_KEEPALIVE
#else
#define DECL
#endif


extern "C" {
	
	// RenderSystem
	two::Type* DECL two_RenderSystem__type() {
		return &two::type<two::RenderSystem>();
	}
	void DECL two_RenderSystem__destroy(two::RenderSystem* self) {
		delete self;
	}
	// Context
	two::Type* DECL two_Context__type() {
		return &two::type<two::Context>();
	}
	void DECL two_Context_reset_fb_1(two::Context* self, const two::uvec2* size) {
		self->reset_fb(*size);
	}
	void DECL two_Context_init_input_2(two::Context* self, two::Mouse* mouse, two::Keyboard* keyboard) {
		self->init_input(*mouse, *keyboard);
	}
	bool DECL two_Context_begin_frame_0(two::Context* self) {
		return self->begin_frame();
	}
	void DECL two_Context_render_frame_0(two::Context* self) {
		self->render_frame();
	}
	void DECL two_Context_end_frame_0(two::Context* self) {
		self->end_frame();
	}
	void DECL two_Context_lock_mouse_1(two::Context* self, bool locked) {
		self->lock_mouse(locked);
	}
	const char* DECL two_Context__get_resource_path(two::Context* self) {
		return self->m_resource_path.c_str();
	}
	const char* DECL two_Context__get_title(two::Context* self) {
		return self->m_title.c_str();
	}
	void DECL two_Context__set_title(two::Context* self, const char* value) {
		self->m_title = value;
	}
	two::uvec2* DECL two_Context__get_size(two::Context* self) {
		return &self->m_size;
	}
	void DECL two_Context__set_size(two::Context* self, two::uvec2* value) {
		self->m_size = *value;
	}
	two::uvec2* DECL two_Context__get_fb_size(two::Context* self) {
		return &self->m_fb_size;
	}
	void DECL two_Context__set_fb_size(two::Context* self, two::uvec2* value) {
		self->m_fb_size = *value;
	}
	bool DECL two_Context__get_fullscreen(two::Context* self) {
		return self->m_fullscreen;
	}
	void DECL two_Context__set_fullscreen(two::Context* self, bool value) {
		self->m_fullscreen = value;
	}
	bool DECL two_Context__get_is_main(two::Context* self) {
		return self->m_is_main;
	}
	void DECL two_Context__set_is_main(two::Context* self, bool value) {
		self->m_is_main = value;
	}
	float DECL two_Context__get_pixel_ratio(two::Context* self) {
		return self->m_pixel_ratio;
	}
	void DECL two_Context__set_pixel_ratio(two::Context* self, float value) {
		self->m_pixel_ratio = value;
	}
	bool DECL two_Context__get_active(two::Context* self) {
		return self->m_active;
	}
	void DECL two_Context__set_active(two::Context* self, bool value) {
		self->m_active = value;
	}
	bool DECL two_Context__get_shutdown(two::Context* self) {
		return self->m_shutdown;
	}
	void DECL two_Context__set_shutdown(two::Context* self, bool value) {
		self->m_shutdown = value;
	}
	two::vec2* DECL two_Context__get_cursor(two::Context* self) {
		return &self->m_cursor;
	}
	void DECL two_Context__set_cursor(two::Context* self, two::vec2* value) {
		self->m_cursor = *value;
	}
	bool DECL two_Context__get_mouse_lock(two::Context* self) {
		return self->m_mouse_lock;
	}
	void DECL two_Context__set_mouse_lock(two::Context* self, bool value) {
		self->m_mouse_lock = value;
	}
	void DECL two_Context__destroy(two::Context* self) {
		delete self;
	}
	// InputEvent
	two::Type* DECL two_InputEvent__type() {
		return &two::type<two::InputEvent>();
	}
	two::InputEvent* DECL two_InputEvent__construct_0() {
		return new two::InputEvent();
	}
	two::InputEvent* DECL two_InputEvent_consume_1(two::InputEvent* self, two::ControlNode* consumer) {
		return &self->consume(*consumer);
	}
	bool DECL two_InputEvent_valid_0(two::InputEvent* self) {
		return self->valid();
	}
	two::DeviceType DECL two_InputEvent__get_deviceType(two::InputEvent* self) {
		return self->m_deviceType;
	}
	void DECL two_InputEvent__set_deviceType(two::InputEvent* self, two::DeviceType value) {
		self->m_deviceType = value;
	}
	two::EventType DECL two_InputEvent__get_eventType(two::InputEvent* self) {
		return self->m_eventType;
	}
	void DECL two_InputEvent__set_eventType(two::InputEvent* self, two::EventType value) {
		self->m_eventType = value;
	}
	two::ControlNode* DECL two_InputEvent__get_receiver(two::InputEvent* self) {
		return self->m_receiver;
	}
	void DECL two_InputEvent__set_receiver(two::InputEvent* self, two::ControlNode* value) {
		self->m_receiver = value;
	}
	two::ControlNode* DECL two_InputEvent__get_consumer(two::InputEvent* self) {
		return self->m_consumer;
	}
	void DECL two_InputEvent__set_consumer(two::InputEvent* self, two::ControlNode* value) {
		self->m_consumer = value;
	}
	bool DECL two_InputEvent__get_abort(two::InputEvent* self) {
		return self->m_abort;
	}
	void DECL two_InputEvent__set_abort(two::InputEvent* self, bool value) {
		self->m_abort = value;
	}
	two::InputMod DECL two_InputEvent__get_modifiers(two::InputEvent* self) {
		return self->m_modifiers;
	}
	void DECL two_InputEvent__set_modifiers(two::InputEvent* self, two::InputMod value) {
		self->m_modifiers = value;
	}
	int DECL two_InputEvent__get_key(two::InputEvent* self) {
		return self->m_key;
	}
	void DECL two_InputEvent__set_key(two::InputEvent* self, int value) {
		self->m_key = value;
	}
	void DECL two_InputEvent__destroy(two::InputEvent* self) {
		delete self;
	}
	// MouseEvent
	two::Type* DECL two_MouseEvent__type() {
		return &two::type<two::MouseEvent>();
	}
	two::MouseEvent* DECL two_MouseEvent__construct_0() {
		return new two::MouseEvent();
	}
	two::vec2* DECL two_MouseEvent__get_pos(two::MouseEvent* self) {
		return &self->m_pos;
	}
	void DECL two_MouseEvent__set_pos(two::MouseEvent* self, two::vec2* value) {
		self->m_pos = *value;
	}
	two::vec2* DECL two_MouseEvent__get_relative(two::MouseEvent* self) {
		return &self->m_relative;
	}
	void DECL two_MouseEvent__set_relative(two::MouseEvent* self, two::vec2* value) {
		self->m_relative = *value;
	}
	two::vec2* DECL two_MouseEvent__get_delta(two::MouseEvent* self) {
		return &self->m_delta;
	}
	void DECL two_MouseEvent__set_delta(two::MouseEvent* self, two::vec2* value) {
		self->m_delta = *value;
	}
	float DECL two_MouseEvent__get_deltaZ(two::MouseEvent* self) {
		return self->m_deltaZ;
	}
	void DECL two_MouseEvent__set_deltaZ(two::MouseEvent* self, float value) {
		self->m_deltaZ = value;
	}
	two::vec2* DECL two_MouseEvent__get_pressed(two::MouseEvent* self) {
		return &self->m_pressed;
	}
	void DECL two_MouseEvent__set_pressed(two::MouseEvent* self, two::vec2* value) {
		self->m_pressed = *value;
	}
	two::MouseButtonCode DECL two_MouseEvent__get_button(two::MouseEvent* self) {
		return self->m_button;
	}
	void DECL two_MouseEvent__set_button(two::MouseEvent* self, two::MouseButtonCode value) {
		self->m_button = value;
	}
	void DECL two_MouseEvent__destroy(two::MouseEvent* self) {
		delete self;
	}
	// KeyEvent
	two::Type* DECL two_KeyEvent__type() {
		return &two::type<two::KeyEvent>();
	}
	two::KeyEvent* DECL two_KeyEvent__construct_0() {
		return new two::KeyEvent();
	}
	two::Key DECL two_KeyEvent__get_code(two::KeyEvent* self) {
		return self->m_code;
	}
	void DECL two_KeyEvent__set_code(two::KeyEvent* self, two::Key value) {
		self->m_code = value;
	}
	char DECL two_KeyEvent__get_char(two::KeyEvent* self) {
		return self->m_char;
	}
	void DECL two_KeyEvent__set_char(two::KeyEvent* self, char value) {
		self->m_char = value;
	}
	void DECL two_KeyEvent__destroy(two::KeyEvent* self) {
		delete self;
	}
	// ControlNode
	two::Type* DECL two_ControlNode__type() {
		return &two::type<two::ControlNode>();
	}
	two::KeyEvent* DECL two_ControlNode_key_event_2(two::ControlNode* self, two::Key code, two::EventType event_type) {
		static two::KeyEvent temp;
		return (temp = self->key_event(code, event_type), &temp);
	}
	two::KeyEvent* DECL two_ControlNode_key_event_3(two::ControlNode* self, two::Key code, two::EventType event_type, two::InputMod modifier) {
		static two::KeyEvent temp;
		return (temp = self->key_event(code, event_type, modifier), &temp);
	}
	two::KeyEvent* DECL two_ControlNode_key_stroke_1(two::ControlNode* self, two::Key code) {
		static two::KeyEvent temp;
		return (temp = self->key_stroke(code), &temp);
	}
	two::KeyEvent* DECL two_ControlNode_key_stroke_2(two::ControlNode* self, two::Key code, two::InputMod modifier) {
		static two::KeyEvent temp;
		return (temp = self->key_stroke(code, modifier), &temp);
	}
	two::KeyEvent* DECL two_ControlNode_char_stroke_1(two::ControlNode* self, two::Key code) {
		static two::KeyEvent temp;
		return (temp = self->char_stroke(code), &temp);
	}
	two::KeyEvent* DECL two_ControlNode_char_stroke_2(two::ControlNode* self, two::Key code, two::InputMod modifier) {
		static two::KeyEvent temp;
		return (temp = self->char_stroke(code, modifier), &temp);
	}
	two::MouseEvent* DECL two_ControlNode_mouse_event_2(two::ControlNode* self, two::DeviceType device, two::EventType event_type) {
		static two::MouseEvent temp;
		return (temp = self->mouse_event(device, event_type), &temp);
	}
	two::MouseEvent* DECL two_ControlNode_mouse_event_3(two::ControlNode* self, two::DeviceType device, two::EventType event_type, two::InputMod modifier) {
		static two::MouseEvent temp;
		return (temp = self->mouse_event(device, event_type, modifier), &temp);
	}
	two::MouseEvent* DECL two_ControlNode_mouse_event_4(two::ControlNode* self, two::DeviceType device, two::EventType event_type, two::InputMod modifier, bool consume) {
		static two::MouseEvent temp;
		return (temp = self->mouse_event(device, event_type, modifier, consume), &temp);
	}
	void DECL two_ControlNode__destroy(two::ControlNode* self) {
		delete self;
	}
	// Keyboard
	two::Type* DECL two_Keyboard__type() {
		return &two::type<two::Keyboard>();
	}
	void DECL two_Keyboard__destroy(two::Keyboard* self) {
		delete self;
	}
	// Mouse
	two::Type* DECL two_Mouse__type() {
		return &two::type<two::Mouse>();
	}
	void DECL two_Mouse__destroy(two::Mouse* self) {
		delete self;
	}
	// Key
	two::Key DECL two_Key_Unassigned() {
		return two::Key::Unassigned;
	}
	two::Key DECL two_Key_Escape() {
		return two::Key::Escape;
	}
	two::Key DECL two_Key_Num1() {
		return two::Key::Num1;
	}
	two::Key DECL two_Key_Num2() {
		return two::Key::Num2;
	}
	two::Key DECL two_Key_Num3() {
		return two::Key::Num3;
	}
	two::Key DECL two_Key_Num4() {
		return two::Key::Num4;
	}
	two::Key DECL two_Key_Num5() {
		return two::Key::Num5;
	}
	two::Key DECL two_Key_Num6() {
		return two::Key::Num6;
	}
	two::Key DECL two_Key_Num7() {
		return two::Key::Num7;
	}
	two::Key DECL two_Key_Num8() {
		return two::Key::Num8;
	}
	two::Key DECL two_Key_Num9() {
		return two::Key::Num9;
	}
	two::Key DECL two_Key_Num0() {
		return two::Key::Num0;
	}
	two::Key DECL two_Key_Minus() {
		return two::Key::Minus;
	}
	two::Key DECL two_Key_Equals() {
		return two::Key::Equals;
	}
	two::Key DECL two_Key_Back() {
		return two::Key::Back;
	}
	two::Key DECL two_Key_Tab() {
		return two::Key::Tab;
	}
	two::Key DECL two_Key_Q() {
		return two::Key::Q;
	}
	two::Key DECL two_Key_W() {
		return two::Key::W;
	}
	two::Key DECL two_Key_E() {
		return two::Key::E;
	}
	two::Key DECL two_Key_R() {
		return two::Key::R;
	}
	two::Key DECL two_Key_T() {
		return two::Key::T;
	}
	two::Key DECL two_Key_Y() {
		return two::Key::Y;
	}
	two::Key DECL two_Key_U() {
		return two::Key::U;
	}
	two::Key DECL two_Key_I() {
		return two::Key::I;
	}
	two::Key DECL two_Key_O() {
		return two::Key::O;
	}
	two::Key DECL two_Key_P() {
		return two::Key::P;
	}
	two::Key DECL two_Key_LeftBracket() {
		return two::Key::LeftBracket;
	}
	two::Key DECL two_Key_RightBracket() {
		return two::Key::RightBracket;
	}
	two::Key DECL two_Key_Return() {
		return two::Key::Return;
	}
	two::Key DECL two_Key_LeftControl() {
		return two::Key::LeftControl;
	}
	two::Key DECL two_Key_A() {
		return two::Key::A;
	}
	two::Key DECL two_Key_S() {
		return two::Key::S;
	}
	two::Key DECL two_Key_D() {
		return two::Key::D;
	}
	two::Key DECL two_Key_F() {
		return two::Key::F;
	}
	two::Key DECL two_Key_G() {
		return two::Key::G;
	}
	two::Key DECL two_Key_H() {
		return two::Key::H;
	}
	two::Key DECL two_Key_J() {
		return two::Key::J;
	}
	two::Key DECL two_Key_K() {
		return two::Key::K;
	}
	two::Key DECL two_Key_L() {
		return two::Key::L;
	}
	two::Key DECL two_Key_Semicolon() {
		return two::Key::Semicolon;
	}
	two::Key DECL two_Key_Apostrophe() {
		return two::Key::Apostrophe;
	}
	two::Key DECL two_Key_Grave() {
		return two::Key::Grave;
	}
	two::Key DECL two_Key_LeftShift() {
		return two::Key::LeftShift;
	}
	two::Key DECL two_Key_Backslash() {
		return two::Key::Backslash;
	}
	two::Key DECL two_Key_Z() {
		return two::Key::Z;
	}
	two::Key DECL two_Key_X() {
		return two::Key::X;
	}
	two::Key DECL two_Key_C() {
		return two::Key::C;
	}
	two::Key DECL two_Key_V() {
		return two::Key::V;
	}
	two::Key DECL two_Key_B() {
		return two::Key::B;
	}
	two::Key DECL two_Key_N() {
		return two::Key::N;
	}
	two::Key DECL two_Key_M() {
		return two::Key::M;
	}
	two::Key DECL two_Key_Comma() {
		return two::Key::Comma;
	}
	two::Key DECL two_Key_Period() {
		return two::Key::Period;
	}
	two::Key DECL two_Key_Slash() {
		return two::Key::Slash;
	}
	two::Key DECL two_Key_RightShift() {
		return two::Key::RightShift;
	}
	two::Key DECL two_Key_Multiply() {
		return two::Key::Multiply;
	}
	two::Key DECL two_Key_LeftAlt() {
		return two::Key::LeftAlt;
	}
	two::Key DECL two_Key_Space() {
		return two::Key::Space;
	}
	two::Key DECL two_Key_Capital() {
		return two::Key::Capital;
	}
	two::Key DECL two_Key_F1() {
		return two::Key::F1;
	}
	two::Key DECL two_Key_F2() {
		return two::Key::F2;
	}
	two::Key DECL two_Key_F3() {
		return two::Key::F3;
	}
	two::Key DECL two_Key_F4() {
		return two::Key::F4;
	}
	two::Key DECL two_Key_F5() {
		return two::Key::F5;
	}
	two::Key DECL two_Key_F6() {
		return two::Key::F6;
	}
	two::Key DECL two_Key_F7() {
		return two::Key::F7;
	}
	two::Key DECL two_Key_F8() {
		return two::Key::F8;
	}
	two::Key DECL two_Key_F9() {
		return two::Key::F9;
	}
	two::Key DECL two_Key_F10() {
		return two::Key::F10;
	}
	two::Key DECL two_Key_Numlock() {
		return two::Key::Numlock;
	}
	two::Key DECL two_Key_ScrollLock() {
		return two::Key::ScrollLock;
	}
	two::Key DECL two_Key_Numpad7() {
		return two::Key::Numpad7;
	}
	two::Key DECL two_Key_Numpad8() {
		return two::Key::Numpad8;
	}
	two::Key DECL two_Key_Numpad9() {
		return two::Key::Numpad9;
	}
	two::Key DECL two_Key_Subtract() {
		return two::Key::Subtract;
	}
	two::Key DECL two_Key_Numpad4() {
		return two::Key::Numpad4;
	}
	two::Key DECL two_Key_Numpad5() {
		return two::Key::Numpad5;
	}
	two::Key DECL two_Key_Numpad6() {
		return two::Key::Numpad6;
	}
	two::Key DECL two_Key_Add() {
		return two::Key::Add;
	}
	two::Key DECL two_Key_Numpad1() {
		return two::Key::Numpad1;
	}
	two::Key DECL two_Key_Numpad2() {
		return two::Key::Numpad2;
	}
	two::Key DECL two_Key_Numpad3() {
		return two::Key::Numpad3;
	}
	two::Key DECL two_Key_Numpad0() {
		return two::Key::Numpad0;
	}
	two::Key DECL two_Key_Decimal() {
		return two::Key::Decimal;
	}
	two::Key DECL two_Key_F11() {
		return two::Key::F11;
	}
	two::Key DECL two_Key_F12() {
		return two::Key::F12;
	}
	two::Key DECL two_Key_F13() {
		return two::Key::F13;
	}
	two::Key DECL two_Key_F14() {
		return two::Key::F14;
	}
	two::Key DECL two_Key_F15() {
		return two::Key::F15;
	}
	two::Key DECL two_Key_NumpadEquals() {
		return two::Key::NumpadEquals;
	}
	two::Key DECL two_Key_NumpadEnter() {
		return two::Key::NumpadEnter;
	}
	two::Key DECL two_Key_RightControl() {
		return two::Key::RightControl;
	}
	two::Key DECL two_Key_Mute() {
		return two::Key::Mute;
	}
	two::Key DECL two_Key_NumpadComma() {
		return two::Key::NumpadComma;
	}
	two::Key DECL two_Key_Divide() {
		return two::Key::Divide;
	}
	two::Key DECL two_Key_RightAlt() {
		return two::Key::RightAlt;
	}
	two::Key DECL two_Key_Pause() {
		return two::Key::Pause;
	}
	two::Key DECL two_Key_Home() {
		return two::Key::Home;
	}
	two::Key DECL two_Key_Up() {
		return two::Key::Up;
	}
	two::Key DECL two_Key_PageUp() {
		return two::Key::PageUp;
	}
	two::Key DECL two_Key_Left() {
		return two::Key::Left;
	}
	two::Key DECL two_Key_Right() {
		return two::Key::Right;
	}
	two::Key DECL two_Key_End() {
		return two::Key::End;
	}
	two::Key DECL two_Key_Down() {
		return two::Key::Down;
	}
	two::Key DECL two_Key_PageDown() {
		return two::Key::PageDown;
	}
	two::Key DECL two_Key_Insert() {
		return two::Key::Insert;
	}
	two::Key DECL two_Key_Delete() {
		return two::Key::Delete;
	}
	two::Key DECL two_Key_LeftWin() {
		return two::Key::LeftWin;
	}
	two::Key DECL two_Key_RightWin() {
		return two::Key::RightWin;
	}
	two::Key DECL two_Key_Translated() {
		return two::Key::Translated;
	}
	// MouseButtonCode
	two::MouseButtonCode DECL two_MouseButtonCode_LEFT_BUTTON() {
		return two::LEFT_BUTTON;
	}
	two::MouseButtonCode DECL two_MouseButtonCode_RIGHT_BUTTON() {
		return two::RIGHT_BUTTON;
	}
	two::MouseButtonCode DECL two_MouseButtonCode_MIDDLE_BUTTON() {
		return two::MIDDLE_BUTTON;
	}
	two::MouseButtonCode DECL two_MouseButtonCode_NO_BUTTON() {
		return two::NO_BUTTON;
	}
	// InputMod
	two::InputMod DECL two_InputMod_None() {
		return two::InputMod::None;
	}
	two::InputMod DECL two_InputMod_Shift() {
		return two::InputMod::Shift;
	}
	two::InputMod DECL two_InputMod_Ctrl() {
		return two::InputMod::Ctrl;
	}
	two::InputMod DECL two_InputMod_Alt() {
		return two::InputMod::Alt;
	}
	two::InputMod DECL two_InputMod_Any() {
		return two::InputMod::Any;
	}
	// DeviceType
	two::DeviceType DECL two_DeviceType_None() {
		return two::DeviceType::None;
	}
	two::DeviceType DECL two_DeviceType_Keyboard() {
		return two::DeviceType::Keyboard;
	}
	two::DeviceType DECL two_DeviceType_Mouse() {
		return two::DeviceType::Mouse;
	}
	two::DeviceType DECL two_DeviceType_MouseLeft() {
		return two::DeviceType::MouseLeft;
	}
	two::DeviceType DECL two_DeviceType_MouseRight() {
		return two::DeviceType::MouseRight;
	}
	two::DeviceType DECL two_DeviceType_MouseMiddle() {
		return two::DeviceType::MouseMiddle;
	}
	two::DeviceType DECL two_DeviceType_Touch() {
		return two::DeviceType::Touch;
	}
	two::DeviceType DECL two_DeviceType_Count() {
		return two::DeviceType::Count;
	}
	// EventType
	two::EventType DECL two_EventType_None() {
		return two::EventType::None;
	}
	two::EventType DECL two_EventType_Heartbeat() {
		return two::EventType::Heartbeat;
	}
	two::EventType DECL two_EventType_Moved() {
		return two::EventType::Moved;
	}
	two::EventType DECL two_EventType_Pressed() {
		return two::EventType::Pressed;
	}
	two::EventType DECL two_EventType_Released() {
		return two::EventType::Released;
	}
	two::EventType DECL two_EventType_Stroked() {
		return two::EventType::Stroked;
	}
	two::EventType DECL two_EventType_DoubleStroked() {
		return two::EventType::DoubleStroked;
	}
	two::EventType DECL two_EventType_Dragged() {
		return two::EventType::Dragged;
	}
	two::EventType DECL two_EventType_DraggedTarget() {
		return two::EventType::DraggedTarget;
	}
	two::EventType DECL two_EventType_DragStarted() {
		return two::EventType::DragStarted;
	}
	two::EventType DECL two_EventType_DragEnded() {
		return two::EventType::DragEnded;
	}
	two::EventType DECL two_EventType_Dropped() {
		return two::EventType::Dropped;
	}
	two::EventType DECL two_EventType_Count() {
		return two::EventType::Count;
	}
	
}


