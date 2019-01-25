#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ctx;
#else
#include <type/Vector.h>
#include <type/Any.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/math/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ctx/Convert.h>
#endif

#include <ctx/Api.h>

namespace mud
{
	void mud_ctx_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::DeviceType>();
		static Meta meta = { t, &namspc({ "mud" }), "DeviceType", sizeof(mud::DeviceType), TypeClass::Enum };
		static cstring ids[] = { "None", "Keyboard", "Mouse", "MouseLeft", "MouseRight", "MouseMiddle", "Touch", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		static mud::DeviceType vars[] = { mud::DeviceType::None, mud::DeviceType::Keyboard, mud::DeviceType::Mouse, mud::DeviceType::MouseLeft, mud::DeviceType::MouseRight, mud::DeviceType::MouseMiddle, mud::DeviceType::Touch, mud::DeviceType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::DeviceType>();
	}
	{
		Type& t = type<mud::EventType>();
		static Meta meta = { t, &namspc({ "mud" }), "EventType", sizeof(mud::EventType), TypeClass::Enum };
		static cstring ids[] = { "None", "Heartbeat", "Moved", "Pressed", "Released", "Stroked", "DoubleStroked", "Dragged", "DraggedTarget", "DragStarted", "DragEnded", "Dropped", "Count" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
		static mud::EventType vars[] = { mud::EventType::None, mud::EventType::Heartbeat, mud::EventType::Moved, mud::EventType::Pressed, mud::EventType::Released, mud::EventType::Stroked, mud::EventType::DoubleStroked, mud::EventType::Dragged, mud::EventType::DraggedTarget, mud::EventType::DragStarted, mud::EventType::DragEnded, mud::EventType::Dropped, mud::EventType::Count};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11], &vars[12]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::EventType>();
	}
	{
		Type& t = type<mud::InputMod>();
		static Meta meta = { t, &namspc({ "mud" }), "InputMod", sizeof(mud::InputMod), TypeClass::Enum };
		static cstring ids[] = { "None", "Shift", "Ctrl", "Alt", "Any" };
		static uint32_t values[] = { 0, 1, 2, 4, 7 };
		static mud::InputMod vars[] = { mud::InputMod::None, mud::InputMod::Shift, mud::InputMod::Ctrl, mud::InputMod::Alt, mud::InputMod::Any};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::InputMod>();
	}
	{
		Type& t = type<mud::Key>();
		static Meta meta = { t, &namspc({ "mud" }), "Key", sizeof(mud::Key), TypeClass::Enum };
		static cstring ids[] = { "Unassigned", "Escape", "Num1", "Num2", "Num3", "Num4", "Num5", "Num6", "Num7", "Num8", "Num9", "Num0", "Minus", "Equals", "Back", "Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "LeftBracket", "RightBracket", "Return", "LeftControl", "A", "S", "D", "F", "G", "H", "J", "K", "L", "Semicolon", "Apostrophe", "Grave", "LeftShift", "Backslash", "Z", "X", "C", "V", "B", "N", "M", "Comma", "Period", "Slash", "RightShift", "Multiply", "LeftAlt", "Space", "Capital", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "Numlock", "ScrollLock", "Numpad7", "Numpad8", "Numpad9", "Subtract", "Numpad4", "Numpad5", "Numpad6", "Add", "Numpad1", "Numpad2", "Numpad3", "Numpad0", "Decimal", "F11", "F12", "F13", "F14", "F15", "NumpadEquals", "NumpadEnter", "RightControl", "Mute", "NumpadComma", "Divide", "RightAlt", "Pause", "Home", "Up", "PageUp", "Left", "Right", "End", "Down", "PageDown", "Insert", "Delete", "LeftWin", "RightWin", "Translated" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 87, 88, 100, 101, 102, 141, 156, 157, 160, 179, 181, 184, 197, 199, 200, 201, 203, 205, 207, 208, 209, 210, 211, 219, 220, uint16_t(1 << 15) };
		static mud::Key vars[] = { mud::Key::Unassigned, mud::Key::Escape, mud::Key::Num1, mud::Key::Num2, mud::Key::Num3, mud::Key::Num4, mud::Key::Num5, mud::Key::Num6, mud::Key::Num7, mud::Key::Num8, mud::Key::Num9, mud::Key::Num0, mud::Key::Minus, mud::Key::Equals, mud::Key::Back, mud::Key::Tab, mud::Key::Q, mud::Key::W, mud::Key::E, mud::Key::R, mud::Key::T, mud::Key::Y, mud::Key::U, mud::Key::I, mud::Key::O, mud::Key::P, mud::Key::LeftBracket, mud::Key::RightBracket, mud::Key::Return, mud::Key::LeftControl, mud::Key::A, mud::Key::S, mud::Key::D, mud::Key::F, mud::Key::G, mud::Key::H, mud::Key::J, mud::Key::K, mud::Key::L, mud::Key::Semicolon, mud::Key::Apostrophe, mud::Key::Grave, mud::Key::LeftShift, mud::Key::Backslash, mud::Key::Z, mud::Key::X, mud::Key::C, mud::Key::V, mud::Key::B, mud::Key::N, mud::Key::M, mud::Key::Comma, mud::Key::Period, mud::Key::Slash, mud::Key::RightShift, mud::Key::Multiply, mud::Key::LeftAlt, mud::Key::Space, mud::Key::Capital, mud::Key::F1, mud::Key::F2, mud::Key::F3, mud::Key::F4, mud::Key::F5, mud::Key::F6, mud::Key::F7, mud::Key::F8, mud::Key::F9, mud::Key::F10, mud::Key::Numlock, mud::Key::ScrollLock, mud::Key::Numpad7, mud::Key::Numpad8, mud::Key::Numpad9, mud::Key::Subtract, mud::Key::Numpad4, mud::Key::Numpad5, mud::Key::Numpad6, mud::Key::Add, mud::Key::Numpad1, mud::Key::Numpad2, mud::Key::Numpad3, mud::Key::Numpad0, mud::Key::Decimal, mud::Key::F11, mud::Key::F12, mud::Key::F13, mud::Key::F14, mud::Key::F15, mud::Key::NumpadEquals, mud::Key::NumpadEnter, mud::Key::RightControl, mud::Key::Mute, mud::Key::NumpadComma, mud::Key::Divide, mud::Key::RightAlt, mud::Key::Pause, mud::Key::Home, mud::Key::Up, mud::Key::PageUp, mud::Key::Left, mud::Key::Right, mud::Key::End, mud::Key::Down, mud::Key::PageDown, mud::Key::Insert, mud::Key::Delete, mud::Key::LeftWin, mud::Key::RightWin, mud::Key::Translated};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7], &vars[8], &vars[9], &vars[10], &vars[11], &vars[12], &vars[13], &vars[14], &vars[15], &vars[16], &vars[17], &vars[18], &vars[19], &vars[20], &vars[21], &vars[22], &vars[23], &vars[24], &vars[25], &vars[26], &vars[27], &vars[28], &vars[29], &vars[30], &vars[31], &vars[32], &vars[33], &vars[34], &vars[35], &vars[36], &vars[37], &vars[38], &vars[39], &vars[40], &vars[41], &vars[42], &vars[43], &vars[44], &vars[45], &vars[46], &vars[47], &vars[48], &vars[49], &vars[50], &vars[51], &vars[52], &vars[53], &vars[54], &vars[55], &vars[56], &vars[57], &vars[58], &vars[59], &vars[60], &vars[61], &vars[62], &vars[63], &vars[64], &vars[65], &vars[66], &vars[67], &vars[68], &vars[69], &vars[70], &vars[71], &vars[72], &vars[73], &vars[74], &vars[75], &vars[76], &vars[77], &vars[78], &vars[79], &vars[80], &vars[81], &vars[82], &vars[83], &vars[84], &vars[85], &vars[86], &vars[87], &vars[88], &vars[89], &vars[90], &vars[91], &vars[92], &vars[93], &vars[94], &vars[95], &vars[96], &vars[97], &vars[98], &vars[99], &vars[100], &vars[101], &vars[102], &vars[103], &vars[104], &vars[105], &vars[106], &vars[107], &vars[108], &vars[109]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::Key>();
	}
	{
		Type& t = type<mud::MouseButtonCode>();
		static Meta meta = { t, &namspc({ "mud" }), "MouseButtonCode", sizeof(mud::MouseButtonCode), TypeClass::Enum };
		static cstring ids[] = { "LEFT_BUTTON", "RIGHT_BUTTON", "MIDDLE_BUTTON", "NO_BUTTON" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::MouseButtonCode vars[] = { mud::LEFT_BUTTON, mud::RIGHT_BUTTON, mud::MIDDLE_BUTTON, mud::NO_BUTTON};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::MouseButtonCode>();
	}
	
	// Sequences
	
	// mud::Context
	{
		Type& t = type<mud::Context>();
		static Meta meta = { t, &namspc({ "mud" }), "Context", sizeof(mud::Context), TypeClass::Object };
		// defaults
		static bool active_default = true;
		static bool shutdown_default = false;
		static bool mouse_lock_default = false;
		static Class cls = { t,
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
				{ t, member_address(&mud::Context::m_resource_path), type<string>(), "resource_path", Ref(), Member::Flags(Member::Value|Member::NonMutable), nullptr },
				{ t, member_address(&mud::Context::m_title), type<string>(), "title", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Context::m_width), type<unsigned int>(), "width", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Context::m_height), type<unsigned int>(), "height", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Context::m_full_screen), type<bool>(), "full_screen", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Context::m_active), type<bool>(), "active", Ref(&active_default), Member::Value, nullptr },
				{ t, member_address(&mud::Context::m_shutdown), type<bool>(), "shutdown", Ref(&shutdown_default), Member::Value, nullptr },
				{ t, member_address(&mud::Context::m_cursor), type<mud::vec2>(), "cursor", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Context::m_mouse_lock), type<bool>(), "mouse_lock", Ref(&mouse_lock_default), Member::Value, nullptr }
			},
			// methods
			{
				{ t, "reset", member_address<void(mud::Context::*)(uint16_t, uint16_t)>(&mud::Context::reset), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Context>(object).reset(val<uint16_t>(args[0]), val<uint16_t>(args[1])); }, { { "width", var(uint16_t()) }, { "height", var(uint16_t()) } }, Var() },
				{ t, "init_input", member_address<void(mud::Context::*)(mud::Mouse&, mud::Keyboard&)>(&mud::Context::init_input), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Context>(object).init_input(val<mud::Mouse>(args[0]), val<mud::Keyboard>(args[1])); }, { { "mouse", Ref(type<mud::Mouse>()) }, { "keyboard", Ref(type<mud::Keyboard>()) } }, Var() },
				{ t, "next_frame", member_address<bool(mud::Context::*)()>(&mud::Context::next_frame), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<bool>(result) = val<mud::Context>(object).next_frame(); }, {}, var(bool()) },
				{ t, "lock_mouse", member_address<void(mud::Context::*)(bool)>(&mud::Context::lock_mouse), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Context>(object).lock_mouse(val<bool>(args[0])); }, { { "locked", var(bool()) } }, Var() }
			},
			// static members
			{
			}
		};
		meta_class<mud::Context>();
	}
	// mud::ControlNode
	{
		Type& t = type<mud::ControlNode>();
		static Meta meta = { t, &namspc({ "mud" }), "ControlNode", sizeof(mud::ControlNode), TypeClass::Object };
		// defaults
		static Class cls = { t,
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
		Type& t = type<mud::InputEvent>();
		static Meta meta = { t, &namspc({ "mud" }), "InputEvent", sizeof(mud::InputEvent), TypeClass::Struct };
		// defaults
		static mud::DeviceType deviceType_default = mud::DeviceType::None;
		static mud::EventType eventType_default = mud::EventType::None;
		static mud::ControlNode* receiver_default = nullptr;
		static mud::ControlNode* consumer_default = nullptr;
		static bool abort_default = false;
		static mud::InputMod modifiers_default = mud::InputMod::None;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::InputEvent>(ref)) mud::InputEvent(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::InputEvent>(ref)) mud::InputEvent(val<mud::InputEvent>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::InputEvent::m_deviceType), type<mud::DeviceType>(), "deviceType", Ref(&deviceType_default), Member::Value, nullptr },
				{ t, member_address(&mud::InputEvent::m_eventType), type<mud::EventType>(), "eventType", Ref(&eventType_default), Member::Value, nullptr },
				{ t, member_address(&mud::InputEvent::m_receiver), type<mud::ControlNode>(), "receiver", Ref(receiver_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::InputEvent::m_consumer), type<mud::ControlNode>(), "consumer", Ref(consumer_default), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::InputEvent::m_abort), type<bool>(), "abort", Ref(&abort_default), Member::Value, nullptr },
				{ t, member_address(&mud::InputEvent::m_modifiers), type<mud::InputMod>(), "modifiers", Ref(&modifiers_default), Member::Value, nullptr },
				{ t, member_address(&mud::InputEvent::m_key), type<int>(), "key", Ref(), Member::Value, nullptr }
			},
			// methods
			{
				{ t, "consume", member_address<mud::InputEvent&(mud::InputEvent::*)(mud::ControlNode&)>(&mud::InputEvent::consume), [](Ref object, array<Var> args, Var& result) { val<mud::InputEvent>(result) = val<mud::InputEvent>(object).consume(val<mud::ControlNode>(args[0])); }, { { "consumer", Ref(type<mud::ControlNode>()) } }, var(mud::InputEvent()) },
				{ t, "valid", member_address<bool(mud::InputEvent::*)()>(&mud::InputEvent::valid), [](Ref object, array<Var> args, Var& result) { UNUSED(args); val<bool>(result) = val<mud::InputEvent>(object).valid(); }, {}, var(bool()) }
			},
			// static members
			{
			}
		};
		meta_class<mud::InputEvent>();
	}
	// mud::Keyboard
	{
		Type& t = type<mud::Keyboard>();
		static Meta meta = { t, &namspc({ "mud" }), "Keyboard", sizeof(mud::Keyboard), TypeClass::Object };
		// defaults
		static Class cls = { t,
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
		Type& t = type<mud::Mouse>();
		static Meta meta = { t, &namspc({ "mud" }), "Mouse", sizeof(mud::Mouse), TypeClass::Object };
		// defaults
		static Class cls = { t,
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
		Type& t = type<mud::RenderSystem>();
		static Meta meta = { t, &namspc({ "mud" }), "RenderSystem", sizeof(mud::RenderSystem), TypeClass::Object };
		// defaults
		static Class cls = { t,
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
		Type& t = type<mud::KeyEvent>();
		static Meta meta = { t, &namspc({ "mud" }), "KeyEvent", sizeof(mud::KeyEvent), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::InputEvent>() },
			{ base_offset<mud::KeyEvent, mud::InputEvent>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::KeyEvent>(ref)) mud::KeyEvent(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::KeyEvent>(ref)) mud::KeyEvent(val<mud::KeyEvent>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::KeyEvent::m_code), type<mud::Key>(), "code", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::KeyEvent::m_char), type<char>(), "char", Ref(), Member::Value, nullptr }
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
		Type& t = type<mud::MouseEvent>();
		static Meta meta = { t, &namspc({ "mud" }), "MouseEvent", sizeof(mud::MouseEvent), TypeClass::Struct };
		// defaults
		static mud::vec2 pos_default = {0.f,0.f};
		static mud::vec2 relative_default = {0.f,0.f};
		static mud::vec2 delta_default = {0.f,0.f};
		static float deltaZ_default = 0.f;
		static mud::vec2 pressed_default = {0.f,0.f};
		static mud::MouseButtonCode button_default = NO_BUTTON;
		static Class cls = { t,
			// bases
			{ &type<mud::InputEvent>() },
			{ base_offset<mud::MouseEvent, mud::InputEvent>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::MouseEvent>(ref)) mud::MouseEvent(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::MouseEvent>(ref)) mud::MouseEvent(val<mud::MouseEvent>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::MouseEvent::m_pos), type<mud::vec2>(), "pos", Ref(&pos_default), Member::Value, nullptr },
				{ t, member_address(&mud::MouseEvent::m_relative), type<mud::vec2>(), "relative", Ref(&relative_default), Member::Value, nullptr },
				{ t, member_address(&mud::MouseEvent::m_delta), type<mud::vec2>(), "delta", Ref(&delta_default), Member::Value, nullptr },
				{ t, member_address(&mud::MouseEvent::m_deltaZ), type<float>(), "deltaZ", Ref(&deltaZ_default), Member::Value, nullptr },
				{ t, member_address(&mud::MouseEvent::m_pressed), type<mud::vec2>(), "pressed", Ref(&pressed_default), Member::Value, nullptr },
				{ t, member_address(&mud::MouseEvent::m_button), type<mud::MouseButtonCode>(), "button", Ref(&button_default), Member::Value, nullptr }
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

namespace mud
{
	mud_ctx::mud_ctx()
		: Module("mud::ctx", { &mud_infra::m(), &mud_type::m(), &mud_math::m() })
	{
		// setup reflection meta data
		mud_ctx_meta(*this);
	}
}

#ifdef MUD_CTX_MODULE
extern "C"
Module& getModule()
{
		return mud_ctx::m();
}
#endif
