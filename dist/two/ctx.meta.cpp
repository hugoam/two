#include <two/infra.h>

module;
module two.ctx.meta;

using namespace two;

void two_Key__to_string(void* val, string& str) { str = g_enu[type<two::Key>().m_id]->name(uint32_t((*static_cast<two::Key*>(val)))); }
void two_Key__to_value(const string& str, void* val) { (*static_cast<two::Key*>(val)) = two::Key(g_enu[type<two::Key>().m_id]->value(str.c_str())); }
void two_MouseButtonCode__to_string(void* val, string& str) { str = g_enu[type<two::MouseButtonCode>().m_id]->name(uint32_t((*static_cast<two::MouseButtonCode*>(val)))); }
void two_MouseButtonCode__to_value(const string& str, void* val) { (*static_cast<two::MouseButtonCode*>(val)) = two::MouseButtonCode(g_enu[type<two::MouseButtonCode>().m_id]->value(str.c_str())); }
void two_InputMod__to_string(void* val, string& str) { str = g_enu[type<two::InputMod>().m_id]->name(uint32_t((*static_cast<two::InputMod*>(val)))); }
void two_InputMod__to_value(const string& str, void* val) { (*static_cast<two::InputMod*>(val)) = two::InputMod(g_enu[type<two::InputMod>().m_id]->value(str.c_str())); }
void two_DeviceType__to_string(void* val, string& str) { str = g_enu[type<two::DeviceType>().m_id]->name(uint32_t((*static_cast<two::DeviceType*>(val)))); }
void two_DeviceType__to_value(const string& str, void* val) { (*static_cast<two::DeviceType*>(val)) = two::DeviceType(g_enu[type<two::DeviceType>().m_id]->value(str.c_str())); }
void two_EventType__to_string(void* val, string& str) { str = g_enu[type<two::EventType>().m_id]->name(uint32_t((*static_cast<two::EventType*>(val)))); }
void two_EventType__to_value(const string& str, void* val) { (*static_cast<two::EventType*>(val)) = two::EventType(g_enu[type<two::EventType>().m_id]->value(str.c_str())); }
void two_Context_reset_fb(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Context*>(object)).reset_fb(*static_cast<two::uvec2*>(args[0])); }
void two_Context_init_input(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Context*>(object)).init_input(*static_cast<two::Mouse*>(args[0]), *static_cast<two::Keyboard*>(args[1])); }
void two_Context_begin_frame(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::Context*>(object)).begin_frame(); }
void two_Context_render_frame(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Context*>(object)).render_frame(); }
void two_Context_end_frame(void* object, span<void*> args, void*& result) { UNUSED(result); UNUSED(args); (*static_cast<two::Context*>(object)).end_frame(); }
void two_Context_lock_mouse(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::Context*>(object)).lock_mouse(*static_cast<bool*>(args[0])); }
void two_InputEvent__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::InputEvent(  ); }
void two_InputEvent__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::InputEvent((*static_cast<two::InputEvent*>(other))); }
void two_InputEvent_consume(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::InputEvent*>(object)).consume(*static_cast<two::ControlNode*>(args[0])); }
void two_InputEvent_valid(void* object, span<void*> args, void*& result) { UNUSED(args); (*static_cast<bool*>(result)) = (*static_cast<two::InputEvent*>(object)).valid(); }
void two_MouseEvent__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::MouseEvent(  ); }
void two_MouseEvent__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::MouseEvent((*static_cast<two::MouseEvent*>(other))); }
void two_KeyEvent__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::KeyEvent(  ); }
void two_KeyEvent__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::KeyEvent((*static_cast<two::KeyEvent*>(other))); }
void two_ControlNode_key_event(void* object, span<void*> args, void*& result) { (*static_cast<two::KeyEvent*>(result)) = (*static_cast<two::ControlNode*>(object)).key_event(*static_cast<two::Key*>(args[0]), *static_cast<two::EventType*>(args[1]), *static_cast<two::InputMod*>(args[2])); }
void two_ControlNode_key_stroke(void* object, span<void*> args, void*& result) { (*static_cast<two::KeyEvent*>(result)) = (*static_cast<two::ControlNode*>(object)).key_stroke(*static_cast<two::Key*>(args[0]), *static_cast<two::InputMod*>(args[1])); }
void two_ControlNode_char_stroke(void* object, span<void*> args, void*& result) { (*static_cast<two::KeyEvent*>(result)) = (*static_cast<two::ControlNode*>(object)).char_stroke(*static_cast<two::Key*>(args[0]), *static_cast<two::InputMod*>(args[1])); }
void two_ControlNode_mouse_event(void* object, span<void*> args, void*& result) { (*static_cast<two::MouseEvent*>(result)) = (*static_cast<two::ControlNode*>(object)).mouse_event(*static_cast<two::DeviceType*>(args[0]), *static_cast<two::EventType*>(args[1]), *static_cast<two::InputMod*>(args[2]), *static_cast<bool*>(args[3])); }

namespace two
{
	void two_ctx_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::Key>();
		static Meta meta = { t, &namspc({ "two" }), "Key", sizeof(two::Key), TypeClass::Enum };
		static cstring ids[] = { "Unassigned", "Escape", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "Num0", "Minus", "Equals", "Back", "Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "LeftBracket", "RightBracket", "Return", "LeftControl", "A", "S", "D", "F", "G", "H", "J", "K", "L", "Semicolon", "Apostrophe", "Grave", "LeftShift", "Backslash", "Z", "X", "C", "V", "B", "N", "M", "Comma", "Period", "Slash", "RightShift", "Multiply", "LeftAlt", "Space", "Capital", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "Numlock", "ScrollLock", "Numpad7", "Numpad8", "Numpad9", "Subtract", "Numpad4", "Numpad5", "Numpad6", "Add", "Numpad1", "Numpad2", "Numpad3", "Numpad0", "Decimal", "F11", "F12", "F13", "F14", "F15", "NumpadEquals", "NumpadEnter", "RightControl", "Mute", "NumpadComma", "Divide", "RightAlt", "Pause", "Home", "Up", "PageUp", "Left", "Right", "End", "Down", "PageDown", "Insert", "Delete", "LeftWin", "RightWin", "Translated" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 87, 88, 100, 101, 102, 141, 156, 157, 160, 179, 181, 184, 197, 199, 200, 201, 203, 205, 207, 208, 209, 210, 211, 219, 220, 32768 };
		static two::Key vars[] = { two::Key::Unassigned, two::Key::Escape, two::Key::Num1, two::Key::Num2, two::Key::Num3, two::Key::Num4, two::Key::Num5, two::Key::Num6, two::Key::Num7, two::Key::Num8, two::Key::Num9, two::Key::Num0, two::Key::Minus, two::Key::Equals, two::Key::Back, two::Key::Tab, two::Key::Q, two::Key::W, two::Key::E, two::Key::R, two::Key::T, two::Key::Y, two::Key::U, two::Key::I, two::Key::O, two::Key::P, two::Key::LeftBracket, two::Key::RightBracket, two::Key::Return, two::Key::LeftControl, two::Key::A, two::Key::S, two::Key::D, two::Key::F, two::Key::G, two::Key::H, two::Key::J, two::Key::K, two::Key::L, two::Key::Semicolon, two::Key::Apostrophe, two::Key::Grave, two::Key::LeftShift, two::Key::Backslash, two::Key::Z, two::Key::X, two::Key::C, two::Key::V, two::Key::B, two::Key::N, two::Key::M, two::Key::Comma, two::Key::Period, two::Key::Slash, two::Key::RightShift, two::Key::Multiply, two::Key::LeftAlt, two::Key::Space, two::Key::Capital, two::Key::F1, two::Key::F2, two::Key::F3, two::Key::F4, two::Key::F5, two::Key::F6, two::Key::F7, two::Key::F8, two::Key::F9, two::Key::F10, two::Key::Numlock, two::Key::ScrollLock, two::Key::Numpad7, two::Key::Numpad8, two::Key::Numpad9, two::Key::Subtract, two::Key::Numpad4, two::Key::Numpad5, two::Key::Numpad6, two::Key::Add, two::Key::Numpad1, two::Key::Numpad2, two::Key::Numpad3, two::Key::Numpad0, two::Key::Decimal, two::Key::F11, two::Key::F12, two::Key::F13, two::Key::F14, two::Key::F15, two::Key::NumpadEquals, two::Key::NumpadEnter, two::Key::RightControl, two::Key::Mute, two::Key::NumpadComma, two::Key::Divide, two::Key::RightAlt, two::Key::Pause, two::Key::Home, two::Key::Up, two::Key::PageUp, two::Key::Left, two::Key::Right, two::Key::End, two::Key::Down, two::Key::PageDown, two::Key::Insert, two::Key::Delete, two::Key::LeftWin, two::Key::RightWin, two::Key::Translated};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11], &vars[12], &vars[13], &vars[14], &vars[15], &vars[16], &vars[17], &vars[18], &vars[19], &vars[20], &vars[21], &vars[22], &vars[23], &vars[24], &vars[25], &vars[26], &vars[27], &vars[28], &vars[29], &vars[30], &vars[31], &vars[32], &vars[33], &vars[34], &vars[35], &vars[36], &vars[37], &vars[38], &vars[39], &vars[40], &vars[41], &vars[42], &vars[43], &vars[44], &vars[45], &vars[46], &vars[47], &vars[48], &vars[49], &vars[50], &vars[51], &vars[52], &vars[53], &vars[54], &vars[55], &vars[56], &vars[57], &vars[58], &vars[59], &vars[60], &vars[61], &vars[62], &vars[63], &vars[64], &vars[65], &vars[66], &vars[67], &vars[68], &vars[69], &vars[70], &vars[71], &vars[72], &vars[73], &vars[74], &vars[75], &vars[76], &vars[77], &vars[78], &vars[79], &vars[80], &vars[81], &vars[82], &vars[83], &vars[84], &vars[85], &vars[86], &vars[87], &vars[88], &vars[89], &vars[90], &vars[91], &vars[92], &vars[93], &vars[94], &vars[95], &vars[96], &vars[97], &vars[98], &vars[99], &vars[100], &vars[101], &vars[102], &vars[103], &vars[104], &vars[105], &vars[106], &vars[107], &vars[108], &vars[109]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_Key__to_string,
		                           two_Key__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::MouseButtonCode>();
		static Meta meta = { t, &namspc({ "two" }), "MouseButtonCode", sizeof(two::MouseButtonCode), TypeClass::Enum };
		static cstring ids[] = { "LEFT_BUTTON", "RIGHT_BUTTON", "MIDDLE_BUTTON", "NO_BUTTON" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static two::MouseButtonCode vars[] = { two::LEFT_BUTTON, two::RIGHT_BUTTON, two::MIDDLE_BUTTON, two::NO_BUTTON};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, false, ids, values, refs };
		static Convert convert = { two_MouseButtonCode__to_string,
		                           two_MouseButtonCode__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::InputMod>();
		static Meta meta = { t, &namspc({ "two" }), "InputMod", sizeof(two::InputMod), TypeClass::Enum };
		static cstring ids[] = { "None", "Shift", "Ctrl", "Alt", "Any" };
		static uint32_t values[] = { 0, 1, 2, 4, 7 };
		static two::InputMod vars[] = { two::InputMod::None, two::InputMod::Shift, two::InputMod::Ctrl, two::InputMod::Alt, two::InputMod::Any};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_InputMod__to_string,
		                           two_InputMod__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::DeviceType>();
		static Meta meta = { t, &namspc({ "two" }), "DeviceType", sizeof(two::DeviceType), TypeClass::Enum };
		static cstring ids[] = { "None", "Keyboard", "Mouse", "MouseLeft", "MouseRight", "MouseMiddle", "Touch", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		static two::DeviceType vars[] = { two::DeviceType::None, two::DeviceType::Keyboard, two::DeviceType::Mouse, two::DeviceType::MouseLeft, two::DeviceType::MouseRight, two::DeviceType::MouseMiddle, two::DeviceType::Touch, two::DeviceType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_DeviceType__to_string,
		                           two_DeviceType__to_value };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<two::EventType>();
		static Meta meta = { t, &namspc({ "two" }), "EventType", sizeof(two::EventType), TypeClass::Enum };
		static cstring ids[] = { "None", "Heartbeat", "Moved", "Pressed", "Released", "Stroked", "DoubleStroked", "Dragged", "DraggedTarget", "DragStarted", "DragEnded", "Dropped", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		static two::EventType vars[] = { two::EventType::None, two::EventType::Heartbeat, two::EventType::Moved, two::EventType::Pressed, two::EventType::Released, two::EventType::Stroked, two::EventType::DoubleStroked, two::EventType::Dragged, two::EventType::DraggedTarget, two::EventType::DragStarted, two::EventType::DragEnded, two::EventType::Dropped, two::EventType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11], &vars[12]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_EventType__to_string,
		                           two_EventType__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// two::RenderSystem
	{
		Type& t = type<two::RenderSystem>();
		static Meta meta = { t, &namspc({ "two" }), "RenderSystem", sizeof(two::RenderSystem), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Context
	{
		Type& t = type<two::Context>();
		static Meta meta = { t, &namspc({ "two" }), "Context", sizeof(two::Context), TypeClass::Object };
		// bases
		// defaults
		static bool fullscreen_default = false;
		static bool is_main_default = true;
		static float pixel_ratio_default = 1.f;
		static bool active_default = true;
		static bool shutdown_default = false;
		static bool mouse_lock_default = false;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Context, m_resource_path), type<stl::string>(), "resource_path", nullptr, Member::Flags(Member::Value|Member::NonMutable), nullptr },
			{ t, offsetof(two::Context, m_title), type<stl::string>(), "title", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Context, m_size), type<two::uvec2>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Context, m_fb_size), type<two::uvec2>(), "fb_size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Context, m_fullscreen), type<bool>(), "fullscreen", &fullscreen_default, Member::Value, nullptr },
			{ t, offsetof(two::Context, m_is_main), type<bool>(), "is_main", &is_main_default, Member::Value, nullptr },
			{ t, offsetof(two::Context, m_pixel_ratio), type<float>(), "pixel_ratio", &pixel_ratio_default, Member::Value, nullptr },
			{ t, offsetof(two::Context, m_active), type<bool>(), "active", &active_default, Member::Value, nullptr },
			{ t, offsetof(two::Context, m_shutdown), type<bool>(), "shutdown", &shutdown_default, Member::Value, nullptr },
			{ t, offsetof(two::Context, m_cursor), type<two::vec2>(), "cursor", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Context, m_mouse_lock), type<bool>(), "mouse_lock", &mouse_lock_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "reset_fb", Address(), two_Context_reset_fb, { { "size", type<two::uvec2>(),  } }, g_qvoid },
			{ t, "init_input", Address(), two_Context_init_input, { { "mouse", type<two::Mouse>(),  }, { "keyboard", type<two::Keyboard>(),  } }, g_qvoid },
			{ t, "begin_frame", Address(), two_Context_begin_frame, {}, { &type<bool>(), QualType::None } },
			{ t, "render_frame", Address(), two_Context_render_frame, {}, g_qvoid },
			{ t, "end_frame", Address(), two_Context_end_frame, {}, g_qvoid },
			{ t, "lock_mouse", Address(), two_Context_lock_mouse, { { "locked", type<bool>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, methods, {}, };
	}
	// two::InputEvent
	{
		Type& t = type<two::InputEvent>();
		static Meta meta = { t, &namspc({ "two" }), "InputEvent", sizeof(two::InputEvent), TypeClass::Struct };
		// bases
		// defaults
		static two::DeviceType deviceType_default = two::DeviceType::None;
		static two::EventType eventType_default = two::EventType::None;
		static two::ControlNode* receiver_default = nullptr;
		static two::ControlNode* consumer_default = nullptr;
		static bool abort_default = false;
		static two::InputMod modifiers_default = two::InputMod::None;
		static int key_default = -1;
		// constructors
		static Constructor constructors[] = {
			{ t, two_InputEvent__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_InputEvent__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::InputEvent, m_deviceType), type<two::DeviceType>(), "deviceType", &deviceType_default, Member::Value, nullptr },
			{ t, offsetof(two::InputEvent, m_eventType), type<two::EventType>(), "eventType", &eventType_default, Member::Value, nullptr },
			{ t, offsetof(two::InputEvent, m_receiver), type<two::ControlNode>(), "receiver", receiver_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::InputEvent, m_consumer), type<two::ControlNode>(), "consumer", consumer_default, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::InputEvent, m_abort), type<bool>(), "abort", &abort_default, Member::Value, nullptr },
			{ t, offsetof(two::InputEvent, m_modifiers), type<two::InputMod>(), "modifiers", &modifiers_default, Member::Value, nullptr },
			{ t, offsetof(two::InputEvent, m_key), type<int>(), "key", &key_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "consume", Address(), two_InputEvent_consume, { { "consumer", type<two::ControlNode>(),  } }, { &type<two::InputEvent>(), QualType::None } },
			{ t, "valid", Address(), two_InputEvent_valid, {}, { &type<bool>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, methods, {}, };
	}
	// two::MouseEvent
	{
		Type& t = type<two::MouseEvent>();
		static Meta meta = { t, &namspc({ "two" }), "MouseEvent", sizeof(two::MouseEvent), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::InputEvent>() };
		static size_t bases_offsets[] = { base_offset<two::MouseEvent, two::InputEvent>() };
		// defaults
		static two::vec2 pos_default = {0.f,0.f};
		static two::vec2 relative_default = {0.f,0.f};
		static two::vec2 delta_default = {0.f,0.f};
		static float deltaZ_default = 0.f;
		static two::vec2 pressed_default = {0.f,0.f};
		static two::MouseButtonCode button_default = NO_BUTTON;
		// constructors
		static Constructor constructors[] = {
			{ t, two_MouseEvent__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_MouseEvent__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::MouseEvent, m_pos), type<two::vec2>(), "pos", &pos_default, Member::Value, nullptr },
			{ t, offsetof(two::MouseEvent, m_relative), type<two::vec2>(), "relative", &relative_default, Member::Value, nullptr },
			{ t, offsetof(two::MouseEvent, m_delta), type<two::vec2>(), "delta", &delta_default, Member::Value, nullptr },
			{ t, offsetof(two::MouseEvent, m_deltaZ), type<float>(), "deltaZ", &deltaZ_default, Member::Value, nullptr },
			{ t, offsetof(two::MouseEvent, m_pressed), type<two::vec2>(), "pressed", &pressed_default, Member::Value, nullptr },
			{ t, offsetof(two::MouseEvent, m_button), type<two::MouseButtonCode>(), "button", &button_default, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::KeyEvent
	{
		Type& t = type<two::KeyEvent>();
		static Meta meta = { t, &namspc({ "two" }), "KeyEvent", sizeof(two::KeyEvent), TypeClass::Struct };
		// bases
		static Type* bases[] = { &type<two::InputEvent>() };
		static size_t bases_offsets[] = { base_offset<two::KeyEvent, two::InputEvent>() };
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_KeyEvent__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_KeyEvent__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::KeyEvent, m_code), type<two::Key>(), "code", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::KeyEvent, m_char), type<char>(), "char", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, constructors, copy_constructor, members, {}, {}, };
	}
	// two::ControlNode
	{
		Type& t = type<two::ControlNode>();
		static Meta meta = { t, &namspc({ "two" }), "ControlNode", sizeof(two::ControlNode), TypeClass::Object };
		// bases
		// defaults
		static two::InputMod key_event_0_modifier_default = two::InputMod::Any;
		static two::InputMod key_stroke_0_modifier_default = two::InputMod::Any;
		static two::InputMod char_stroke_0_modifier_default = two::InputMod::Any;
		static two::InputMod mouse_event_0_modifier_default = two::InputMod::None;
		static bool mouse_event_0_consume_default = true;
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "key_event", Address(), two_ControlNode_key_event, { { "code", type<two::Key>(),  }, { "event_type", type<two::EventType>(),  }, { "modifier", type<two::InputMod>(), Param::Default, &key_event_0_modifier_default } }, { &type<two::KeyEvent>(), QualType::None } },
			{ t, "key_stroke", Address(), two_ControlNode_key_stroke, { { "code", type<two::Key>(),  }, { "modifier", type<two::InputMod>(), Param::Default, &key_stroke_0_modifier_default } }, { &type<two::KeyEvent>(), QualType::None } },
			{ t, "char_stroke", Address(), two_ControlNode_char_stroke, { { "code", type<two::Key>(),  }, { "modifier", type<two::InputMod>(), Param::Default, &char_stroke_0_modifier_default } }, { &type<two::KeyEvent>(), QualType::None } },
			{ t, "mouse_event", Address(), two_ControlNode_mouse_event, { { "device", type<two::DeviceType>(),  }, { "event_type", type<two::EventType>(),  }, { "modifier", type<two::InputMod>(), Param::Default, &mouse_event_0_modifier_default }, { "consume", type<bool>(), Param::Default, &mouse_event_0_consume_default } }, { &type<two::MouseEvent>(), QualType::None } }
		};
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, methods, {}, };
	}
	// two::Keyboard
	{
		Type& t = type<two::Keyboard>();
		static Meta meta = { t, &namspc({ "two" }), "Keyboard", sizeof(two::Keyboard), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Mouse
	{
		Type& t = type<two::Mouse>();
		static Meta meta = { t, &namspc({ "two" }), "Mouse", sizeof(two::Mouse), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<two::RenderSystem>());
		m.m_types.push_back(&type<two::Context>());
		m.m_types.push_back(&type<two::Key>());
		m.m_types.push_back(&type<two::MouseButtonCode>());
		m.m_types.push_back(&type<two::InputMod>());
		m.m_types.push_back(&type<two::DeviceType>());
		m.m_types.push_back(&type<two::EventType>());
		m.m_types.push_back(&type<two::InputEvent>());
		m.m_types.push_back(&type<two::MouseEvent>());
		m.m_types.push_back(&type<two::KeyEvent>());
		m.m_types.push_back(&type<two::ControlNode>());
		m.m_types.push_back(&type<two::Keyboard>());
		m.m_types.push_back(&type<two::Mouse>());
	}
}

namespace two
{
	two_ctx::two_ctx()
		: Module("two::ctx", { &two_infra::m(), &two_type::m(), &two_math::m() })
	{
		// setup reflection meta data
		two_ctx_meta(*this);
	}
}

#ifdef TWO_CTX_MODULE
extern "C"
Module& getModule()
{
	return two_ctx::m();
}
#endif
