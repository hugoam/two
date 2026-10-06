#include <infra/Cpp20.h>
import two.frame;

#include <cstdarg>

#include "imgui_flags.h"

using namespace two;

// dear imgui, v1.93.0 WIP
// (demo code)

// This is a port of imgui_demo.cpp and of the examples main.cpp of dear imgui (https://github.com/ocornut/imgui) to two.ui
// It maps 1:1 to the original, section by section, and line by line where possible:
// - ImGui::Xxx() calls map to ui::xxx(key(), parent, ...) calls, with the parent widget passed explicitly
// - Begin/End pairs map to the body of the widget they return: if(Widget body = ui::xxx(...).body) { ... }
// - SameLine() maps to declaring the items on the same line in a ui::row()
// - The sections using features two.ui doesn't have yet are kept as is from the original under #if 0, or commented out line by line
// - The functions two.ui doesn't have yet are stubbed below, built from the existing widgets where possible

// dear imgui is licensed under the MIT License, see https://github.com/ocornut/imgui/blob/master/LICENSE.txt
// Copyright (c) 2014-2026 Omar Cornut

// Play it nice with Windows users (Update: May 2018, Notepad now supports Unix-style carriage returns!)
#ifdef _WIN32
#define IM_NEWLINE  "\r\n"
#else
#define IM_NEWLINE  "\n"
#endif

// Helpers
#if defined(_MSC_VER) && !defined(snprintf)
#define snprintf    _snprintf
#endif
#if defined(_MSC_VER) && !defined(vsnprintf)
#define vsnprintf   _vsnprintf
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4127)     // condition expression is constant
#pragma warning (disable: 4996)     // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#endif

// Helpers macros
// We normally try to not use many helpers in imgui_demo.cpp in order to make code easier to copy and paste,
// but making an exception here as those are largely simplifying code...
// In other imgui sources we can use nicer internal functions from imgui_internal.h (ImMin/ImMax) but not in the demo.
#define IM_MIN(A, B)            (((A) < (B)) ? (A) : (B))
#define IM_MAX(A, B)            (((A) >= (B)) ? (A) : (B))
#define IM_CLAMP(V, MN, MX)     ((V) < (MN) ? (MN) : (V) > (MX) ? (MX) : (V))
#define IM_COUNTOF(_ARR)        ((int)(sizeof(_ARR) / sizeof(*(_ARR))))
#define IMGUI_VERSION           "1.93.0 WIP"
#define IMGUI_VERSION_NUM       19297

// Helper to wire demo markers located in code to an interactive browser (e.g. https://pthom.github.io/imgui_explorer)
#define IMGUI_DEMO_MARKER(section)

//-----------------------------------------------------------------------------
// [SECTION] Stubs
//-----------------------------------------------------------------------------
// The functions of the ImGui API used by the demo that two.ui doesn't have yet
// @todo: move them to the ui namespace, as proper widgets, and remove them from here

namespace two
{
namespace ui
{
	// ImGuiIO: the inputs and the configuration of the demo, updated each frame in example_ui()
	// (the configuration flags are only exposed as options in the demo, as in the original)
	struct IO
	{
		ImGuiConfigFlags ConfigFlags = ImGuiConfigFlags_None;
		ImGuiBackendFlags BackendFlags = ImGuiBackendFlags_HasMouseCursors;
		bool ConfigInputTrickleEventQueue = true;
		bool MouseDrawCursor = false;
		bool ConfigNavSwapGamepadButtons = false;
		bool ConfigNavMoveSetMousePos = false;
		bool ConfigNavCaptureKeyboard = true;
		bool ConfigNavEscapeClearFocusItem = true;
		bool ConfigNavEscapeClearFocusWindow = false;
		bool ConfigNavCursorVisibleAuto = true;
		bool ConfigNavCursorVisibleAlways = false;
		bool ConfigWindowsResizeFromEdges = true;
		bool ConfigWindowsMoveFromTitleBarOnly = false;
		bool ConfigWindowsCopyContentsWithCtrlC = false;
		bool ConfigScrollbarScrollByPage = true;
		bool ConfigInputTextCursorBlink = true;
		bool ConfigInputTextEnterKeepActive = false;
		bool ConfigDragClickToInputText = false;
		bool ConfigMacOSXBehaviors = false;
		bool ConfigIniSettingsSaveLastUsedDate = false;
		bool ConfigErrorRecovery = true;
		bool ConfigErrorRecoveryEnableAssert = true;
		bool ConfigErrorRecoveryEnableDebugLog = true;
		bool ConfigErrorRecoveryEnableTooltip = true;
		bool ConfigDebugIsDebuggerPresent = false;
		bool ConfigDebugHighlightIdConflicts = true;
		bool ConfigDebugBeginReturnValueOnce = false;
		bool ConfigDebugBeginReturnValueLoop = false;
		bool ConfigDebugIgnoreFocusLoss = false;
		bool ConfigDebugIniSettings = false;

		double Time = 0.0;
		float DeltaTime = 1.f / 60.f;
		float Framerate = 60.f;
		vec2 MousePos = vec2(0.f);
		bool KeyCtrl = false;
		bool KeyShift = false;
		bool KeyAlt = false;
		bool KeySuper = false;
		vec2 MouseDelta = vec2(0.f);
		bool MouseDown[5] = {};
		float MouseDownDuration[5] = {};
		int MouseClickedCount[5] = {};
		vec2 MouseClickedPos[5] = {};
		float MouseWheel = 0.f;
		vector<char> InputQueueCharacters;
		bool FontAllowUserScaling = false;
		float ConfigMemoryCompactTimer = 60.f;
		vec2 DisplaySize = vec2(0.f);
		vec2 DisplayFramebufferScale = vec2(1.f);

		bool WantCaptureMouse = false;
		bool WantCaptureMouseUnlessPopupClose = false;
		bool WantCaptureKeyboard = false;
		bool WantTextInput = false;
		bool WantSetMousePos = false;
		bool NavActive = false;
		bool NavVisible = false;
	};

	// the lowest value of a number type
	template <class T>
	constexpr T lowest() { if constexpr(is_float<T>) return -limits<T>::max(); else return limits<T>::min(); }

	IO& io() { static IO io; return io; }

	void update_io(Ui& ui)
	{
		static Clock clock;
		static Clock frame_clock;
		IO& io = ui::io();
		io.Time = clock.read();
		io.DeltaTime = max(float(frame_clock.step()), 0.0001f);
		io.Framerate = io.Framerate * 0.95f + (1.f / io.DeltaTime) * 0.05f;
		io.MouseDelta = ui.m_mouse.m_pos - io.MousePos;
		io.MousePos = ui.m_mouse.m_pos;
		io.DisplaySize = vec2(ui.ui_window().m_size);
		io.KeyCtrl = ui.m_keyboard.m_ctrl;
		io.KeyShift = ui.m_keyboard.m_shift;
		io.KeyAlt = ui.m_keyboard.m_alt;
	}

	// Text(), TextColored(), TextDisabled(), TextWrapped(), LabelText(), SeparatorText(), TextLinkOpenURL()

	Widget textf(NodeKey id, Widget parent, cstring fmt, ...)
	{
		char buf[1024];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, sizeof(buf), fmt, args);
		va_end(args);
		return label(id, parent, buf);
	}

	Widget text_colored(NodeKey id, Widget parent, const Colour& colour, cstring text)
	{
		// a style per colour, until widgets can override the colours of their style
		static map<uint32_t, unique<Style>> colour_styles;
		const uint32_t packed = (uint32_t(colour.r * 255.f) << 24) | (uint32_t(colour.g * 255.f) << 16) | (uint32_t(colour.b * 255.f) << 8) | uint32_t(colour.a * 255.f);
		unique<Style>& style = colour_styles[packed];
		if(!style)
		{
			style = make_unique<Style>("TextColored", styles().label, nullptr);
			style->m_skin = styles().label.m_skin;
			style->m_skin.m_text_colour = colour;
			style->prepare();
		}
		return item(id, parent, *style, text);
	}

	Widget text_disabled(NodeKey id, Widget parent, cstring text)
	{
		Widget self = label(id, parent, text);
		self.enable_state(DISABLED);
		return self;
	}

	Widget text_wrapped(NodeKey id, Widget parent, cstring text)
	{
		return ui::text(id, parent, text);
	}

	Widget label_text(NodeKey id, Widget parent, cstring label, cstring value)
	{
		Widget self = row(id, parent);
		ui::label(key(), self, value);
		ui::label(key(), self, label);
		return self;
	}

	Widget separator_text(NodeKey id, Widget parent, cstring label)
	{
		Widget self = row(id, parent);
		if(label && label[0] != '\0')
			ui::label(key(), self, label);
		ui::separator(key(), self);
		return self;
	}

	Widget text_link(NodeKey id, Widget parent, cstring label, cstring url = nullptr)
	{
		Widget self = button(id, parent, styles().label, label);
		tooltip(key(), self, url ? url : label);
		return self;
	}

	// Spacing(), Dummy(), NewLine(), Indent()

	Widget spacing(NodeKey id, Widget parent)
	{
		return dummy(id, parent, vec2(0.f, 4.f));
	}

	// Button(), SmallButton(), ArrowButton(), Checkbox(), CheckboxFlags(), RadioButton()

	Widget small_button(NodeKey id, Widget parent, cstring label)
	{
		return button(id, parent, label);
	}

	enum class Dir { Left, Right, Up, Down };

	Widget arrow_button(NodeKey id, Widget parent, Dir dir)
	{
		cstring arrows[] = { "<", ">", "^", "v" };
		return button(id, parent, arrows[size_t(dir)]);
	}

	bool checkbox(NodeKey id, Widget parent, cstring label, bool& value)
	{
		return field<bool>(id, parent, label, value, true);
	}

	bool checkbox_flags(NodeKey id, Widget parent, cstring label, int& flags, int flags_value)
	{
		bool on = (flags & flags_value) == flags_value;
		if(field<bool>(id, parent, label, on, true))
		{
			if(on)
				flags |= flags_value;
			else
				flags &= ~flags_value;
			return true;
		}
		return false;
	}

	bool radio_button(NodeKey id, Widget parent, cstring label, bool active)
	{
		return radio_choice(id, parent, label, active).activated();
	}

	bool radio_button(NodeKey id, Widget parent, cstring label, int& value, int index)
	{
		if(radio_button(id, parent, label, value == index))
		{
			value = index;
			return true;
		}
		return false;
	}

	// Combo(), BeginCombo(), ListBox(), BeginListBox(), Selectable()

	bool combo(NodeKey id, Widget parent, cstring label, int& current, span<cstring> items)
	{
		uint32_t value = current < 0 ? UINT32_MAX : uint32_t(current);
		const bool changed = dropdown_field(id, parent, label, items, value, true);
		if(changed)
			current = int(value);
		return changed;
	}

	Widget begin_combo(NodeKey id, Widget parent, cstring label, cstring preview)
	{
		Widget self = row(id, parent);
		Dropdown dropdown = ui::dropdown(key(), self, dropdown_styles().dropdown_input, preview, PopupFlags::AutoModal);
		ui::label(key(), self, label);
		return dropdown.body;
	}

	Widget selectable(NodeKey id, Widget parent, cstring label, bool selected)
	{
		Widget self = button(id, parent, dropdown_styles().choice, label);
		self.set_state(SELECTED, selected);
		return self;
	}

	Widget selectable(NodeKey id, Widget parent, cstring label, bool* p_selected)
	{
		Widget self = selectable(id, parent, label, bool(*p_selected));
		if(self.activated())
			*p_selected = !*p_selected;
		return self;
	}

	Widget begin_list_box(NodeKey id, Widget parent, cstring label)
	{
		Widget self = row(id, parent);
		ScrollSheet list = select_list(key(), self);
		if(label && label[0] != '#')
			ui::label(key(), self, label);
		return list.body;
	}

	bool list_box(NodeKey id, Widget parent, cstring label, int& current, span<cstring> items, int height_in_items = -1)
	{
		UNUSED(height_in_items);
		bool changed = false;
		if(Widget body = begin_list_box(id, parent, label))
			for(int n = 0; n < int(items.size()); n++)
				if(selectable(key(), *body, items[n], current == n).activated())
				{
					current = n;
					changed = true;
				}
		return changed;
	}

	// InputText(), InputTextMultiline(), InputInt(), InputFloat(), InputDouble(), InputFloat2/3/4(), InputInt2/3/4()

	// ImGuiInputTextCallbackData: the callbacks of the text inputs
	// @todo: the callbacks are not called yet, two.ui text edits have no hooks for completion, history, edits and character filtering
	struct InputTextCallbackData
	{
		ImGuiInputTextFlags EventFlag = 0;
		ImGuiInputTextFlags Flags = 0;
		void* UserData = nullptr;
		unsigned int EventChar = 0;
		Key EventKey = Key::Unassigned;
		char* Buf = nullptr;
		int BufTextLen = 0;
		int BufSize = 0;
		bool BufDirty = false;
		int CursorPos = 0;
		int SelectionStart = 0;
		int SelectionEnd = 0;
		string* Text = nullptr;

		void DeleteChars(int pos, int bytes_count) { Text->erase(size_t(pos), size_t(bytes_count)); BufDirty = true; }
		void InsertChars(int pos, const char* text, const char* text_end = nullptr) { Text->insert(size_t(pos), text_end ? string(text, text_end) : string(text)); BufDirty = true; }
		void SelectAll() { SelectionStart = 0; SelectionEnd = BufTextLen; }
	};

	using InputTextCallback = int(*)(InputTextCallbackData* data);

	// the characters allowed in a text input with the ImGuiInputTextFlags_CharsXXX flags
	string allowed_chars(ImGuiInputTextFlags flags)
	{
		if(flags & ImGuiInputTextFlags_CharsDecimal) return "0123456789.+-*/";
		if(flags & ImGuiInputTextFlags_CharsHexadecimal) return "0123456789ABCDEFabcdef";
		if(flags & ImGuiInputTextFlags_CharsScientific) return "0123456789.+-*/eE";
		return "";
	}

	TextEditHandle input_text_edit(NodeKey id, Widget parent, cstring label, string& text, ImGuiInputTextFlags flags = 0, InputTextCallback callback = nullptr, void* user_data = nullptr)
	{
		UNUSED(callback); UNUSED(user_data);
		Widget self = row(id, parent);
		TextEditHandle edit = text_box(key(), self, styles().type_in, text, false, 1, allowed_chars(flags));
		edit->m_read_only = (flags & ImGuiInputTextFlags_ReadOnly) != 0;
		if(label && label[0] != '#')
			ui::label(key(), self, label);
		return edit;
	}

	bool input_text(NodeKey id, Widget parent, cstring label, string& text, ImGuiInputTextFlags flags = 0, InputTextCallback callback = nullptr, void* user_data = nullptr)
	{
		TextEdit& edit = *input_text_edit(id, parent, label, text, flags, callback, user_data);
		return (flags & ImGuiInputTextFlags_EnterReturnsTrue) ? edit.m_entered : edit.m_changed;
	}

	bool input_text_with_hint(NodeKey id, Widget parent, cstring label, cstring hint, string& text, ImGuiInputTextFlags flags = 0)
	{
		UNUSED(hint);
		return input_text(id, parent, label, text, flags);
	}

	bool input_text_multiline(NodeKey id, Widget parent, cstring label, string& text, size_t lines = 16, ImGuiInputTextFlags flags = 0)
	{
		UNUSED(label);
		TextEdit& edit = *text_edit(id, parent, text, lines);
		edit.m_read_only = (flags & ImGuiInputTextFlags_ReadOnly) != 0;
		return edit.m_changed;
	}

	bool input_int(NodeKey id, Widget parent, cstring label, int& value, int step = 1)
	{
		return field<int>(id, parent, label, value, { INT_MIN, INT_MAX, step }, true);
	}

	bool input_float(NodeKey id, Widget parent, cstring label, float& value, float step = 0.f)
	{
		return field<float>(id, parent, label, value, { -FLT_MAX, FLT_MAX, step > 0.f ? step : 0.01f }, true);
	}

	bool input_double(NodeKey id, Widget parent, cstring label, double& value, double step = 0.0)
	{
		return do_field(id, [&](Widget self) { return number_input<double>(key(), self, value, { -DBL_MAX, DBL_MAX, step > 0.0 ? step : 0.01 }); }, parent, label, true);
	}

	template <class T>
	bool input_n(NodeKey id, Widget parent, cstring label, T* values, int count, StatDef<T> def)
	{
		Widget self = row(id, parent);
		bool changed = false;
		for(int i = 0; i < count; ++i)
			changed |= number_input<T>(key(), self, values[i], def);
		ui::label(key(), self, label);
		return changed;
	}

	bool input_float2(NodeKey id, Widget parent, cstring label, float* v) { return input_n<float>(id, parent, label, v, 2, { -FLT_MAX, FLT_MAX, 0.01f }); }
	bool input_float3(NodeKey id, Widget parent, cstring label, float* v) { return input_n<float>(id, parent, label, v, 3, { -FLT_MAX, FLT_MAX, 0.01f }); }
	bool input_float4(NodeKey id, Widget parent, cstring label, float* v) { return input_n<float>(id, parent, label, v, 4, { -FLT_MAX, FLT_MAX, 0.01f }); }
	bool input_int2(NodeKey id, Widget parent, cstring label, int* v) { return input_n<int>(id, parent, label, v, 2, { INT_MIN, INT_MAX, 1 }); }
	bool input_int3(NodeKey id, Widget parent, cstring label, int* v) { return input_n<int>(id, parent, label, v, 3, { INT_MIN, INT_MAX, 1 }); }
	bool input_int4(NodeKey id, Widget parent, cstring label, int* v) { return input_n<int>(id, parent, label, v, 4, { INT_MIN, INT_MAX, 1 }); }

	// DragInt(), DragFloat(), DragFloat2/3/4(), DragInt2/3/4(), DragFloatRange2(), DragIntRange2()

	bool drag_int(NodeKey id, Widget parent, cstring label, int& value, float speed = 1.f, int min = 0, int max = 0)
	{
		const bool clamp = min < max;
		return drag_field<int>(id, parent, label, value, { clamp ? min : INT_MIN, clamp ? max : INT_MAX, IM_MAX(int(speed), 1) }, true);
	}

	bool drag_float(NodeKey id, Widget parent, cstring label, float& value, float speed = 1.f, float min = 0.f, float max = 0.f)
	{
		const bool clamp = min < max;
		const bool changed = drag_field<float>(id, parent, label, value, { clamp ? min : -FLT_MAX, clamp ? max : FLT_MAX, speed }, true);
		if(clamp)
			value = IM_CLAMP(value, min, max);
		return changed;
	}

	template <class T>
	bool drag_n(NodeKey id, Widget parent, cstring label, T* values, int count, float speed, T min, T max)
	{
		const bool clamp = min < max;
		Widget self = row(id, parent);
		bool changed = false;
		for(int i = 0; i < count; ++i)
		{
			changed |= drag_input<T>(key(), self, values[i], { clamp ? min : lowest<T>(), clamp ? max : limits<T>::max(), T(IM_MAX(speed, is_float<T> ? 0.f : 1.f)) });
			if(clamp)
				values[i] = IM_CLAMP(values[i], min, max);
		}
		ui::label(key(), self, label);
		return changed;
	}

	bool drag_float2(NodeKey id, Widget parent, cstring label, float* v, float speed = 1.f, float min = 0.f, float max = 0.f) { return drag_n<float>(id, parent, label, v, 2, speed, min, max); }
	bool drag_float3(NodeKey id, Widget parent, cstring label, float* v, float speed = 1.f, float min = 0.f, float max = 0.f) { return drag_n<float>(id, parent, label, v, 3, speed, min, max); }
	bool drag_float4(NodeKey id, Widget parent, cstring label, float* v, float speed = 1.f, float min = 0.f, float max = 0.f) { return drag_n<float>(id, parent, label, v, 4, speed, min, max); }
	bool drag_int2(NodeKey id, Widget parent, cstring label, int* v, float speed = 1.f, int min = 0, int max = 0) { return drag_n<int>(id, parent, label, v, 2, speed, min, max); }
	bool drag_int3(NodeKey id, Widget parent, cstring label, int* v, float speed = 1.f, int min = 0, int max = 0) { return drag_n<int>(id, parent, label, v, 3, speed, min, max); }
	bool drag_int4(NodeKey id, Widget parent, cstring label, int* v, float speed = 1.f, int min = 0, int max = 0) { return drag_n<int>(id, parent, label, v, 4, speed, min, max); }

	bool drag_float_range2(NodeKey id, Widget parent, cstring label, float& begin, float& end, float speed = 1.f, float min = 0.f, float max = 0.f)
	{
		float values[2] = { begin, end };
		const bool changed = drag_n<float>(id, parent, label, values, 2, speed, min, max);
		begin = IM_MIN(values[0], end);
		end = IM_MAX(values[1], begin);
		return changed;
	}

	bool drag_int_range2(NodeKey id, Widget parent, cstring label, int& begin, int& end, float speed = 1.f, int min = 0, int max = 0)
	{
		int values[2] = { begin, end };
		const bool changed = drag_n<int>(id, parent, label, values, 2, speed, min, max);
		begin = IM_MIN(values[0], end);
		end = IM_MAX(values[1], begin);
		return changed;
	}

	// SliderInt(), SliderFloat(), SliderAngle(), SliderFloat2/3/4(), SliderInt2/3/4(), VSliderFloat(), VSliderInt()

	bool slider_int(NodeKey id, Widget parent, cstring label, int& value, int min, int max)
	{
		return slider_field<int>(id, parent, label, value, { min, max, 1 }, true);
	}

	bool slider_float(NodeKey id, Widget parent, cstring label, float& value, float min, float max)
	{
		return slider_field<float>(id, parent, label, value, { min, max, (max - min) / 1000.f }, true);
	}

	bool slider_angle(NodeKey id, Widget parent, cstring label, float& radians, float min_degrees = -360.f, float max_degrees = +360.f)
	{
		float degrees = radians * 360.f / (2.f * c_pi);
		const bool changed = slider_field<float>(id, parent, label, degrees, { min_degrees, max_degrees, 1.f }, true);
		radians = degrees * (2.f * c_pi) / 360.f;
		return changed;
	}

	template <class T>
	bool slider_n(NodeKey id, Widget parent, cstring label, T* values, int count, T min, T max)
	{
		Widget self = row(id, parent);
		bool changed = false;
		for(int i = 0; i < count; ++i)
			changed |= slider_input<T>(key(), self, values[i], { min, max, is_float<T> ? T((max - min) / 1000) : T(1) });
		ui::label(key(), self, label);
		return changed;
	}

	bool slider_float2(NodeKey id, Widget parent, cstring label, float* v, float min, float max) { return slider_n<float>(id, parent, label, v, 2, min, max); }
	bool slider_float3(NodeKey id, Widget parent, cstring label, float* v, float min, float max) { return slider_n<float>(id, parent, label, v, 3, min, max); }
	bool slider_float4(NodeKey id, Widget parent, cstring label, float* v, float min, float max) { return slider_n<float>(id, parent, label, v, 4, min, max); }
	bool slider_int2(NodeKey id, Widget parent, cstring label, int* v, int min, int max) { return slider_n<int>(id, parent, label, v, 2, min, max); }
	bool slider_int3(NodeKey id, Widget parent, cstring label, int* v, int min, int max) { return slider_n<int>(id, parent, label, v, 3, min, max); }
	bool slider_int4(NodeKey id, Widget parent, cstring label, int* v, int min, int max) { return slider_n<int>(id, parent, label, v, 4, min, max); }

	Widget v_slider_float(NodeKey id, Widget parent, const vec2& size, float& value, float min, float max)
	{
		Widget self = dummy(id, parent, size);
		slider_input<float>(key(), self, value, { min, max, (max - min) / 1000.f }, Axis::Y);
		return self;
	}

	Widget v_slider_int(NodeKey id, Widget parent, const vec2& size, int& value, int min, int max)
	{
		Widget self = dummy(id, parent, size);
		slider_input<int>(key(), self, value, { min, max, 1 }, Axis::Y);
		return self;
	}

	// ColorEdit3(), ColorEdit4(), ColorButton(), ColorPicker3(), ColorPicker4()

	bool color_edit(NodeKey id, Widget parent, cstring label, float* col, bool alpha)
	{
		Colour colour = Colour(col[0], col[1], col[2], alpha ? col[3] : 1.f);
		bool changed = false;
		if(label && label[0] == '#')
			changed = color_toggle_edit(id, parent, colour);
		else
			changed = color_field(id, parent, label, colour, true);
		col[0] = colour.r; col[1] = colour.g; col[2] = colour.b;
		if(alpha) col[3] = colour.a;
		return changed;
	}

	bool color_edit3(NodeKey id, Widget parent, cstring label, float* col) { return color_edit(id, parent, label, col, false); }
	bool color_edit4(NodeKey id, Widget parent, cstring label, float* col) { return color_edit(id, parent, label, col, true); }

	Widget color_button(NodeKey id, Widget parent, cstring desc_id, const Colour& colour, const vec2& size = vec2(0.f))
	{
		UNUSED(desc_id); UNUSED(size);
		return color_slab(id, parent, styles().color_toggle, colour);
	}

	bool color_picker(NodeKey id, Widget parent, cstring label, float* col, bool alpha)
	{
		UNUSED(label);
		Colour colour = Colour(col[0], col[1], col[2], alpha ? col[3] : 1.f);
		const bool changed = color_edit(id, parent, colour);
		col[0] = colour.r; col[1] = colour.g; col[2] = colour.b;
		if(alpha) col[3] = colour.a;
		return changed;
	}

	bool color_picker3(NodeKey id, Widget parent, cstring label, float* col) { return color_picker(id, parent, label, col, false); }
	bool color_picker4(NodeKey id, Widget parent, cstring label, float* col) { return color_picker(id, parent, label, col, true); }

	// PlotLines(), PlotHistogram(), ProgressBar()

	Widget plot(NodeKey id, Widget parent, cstring label, vector<float> values, int offset, cstring overlay, float min, float max, vec2 size, bool histogram)
	{
		if(min == FLT_MAX || max == FLT_MAX)
		{
			float v_min = FLT_MAX, v_max = -FLT_MAX;
			for(float v : values) { v_min = IM_MIN(v_min, v); v_max = IM_MAX(v_max, v); }
			if(min == FLT_MAX) min = v_min;
			if(max == FLT_MAX) max = v_max;
		}

		Widget self = row(id, parent);
		Widget graph = dummy(key(), self, vec2(size.x > 0.f ? size.x : 250.f, size.y > 0.f ? size.y : 20.f));
		const Colour colour = histogram ? Colour(0.90f, 0.70f, 0.00f, 1.00f) : Colour(0.61f, 0.61f, 0.61f, 1.00f);
		const Colour background = Colour(0.16f, 0.29f, 0.48f, 0.54f);
		const string text = overlay ? overlay : "";
		graph.custom_draw() = [=](Widget widget, const vec4& rect, Vg& vg)
		{
			UNUSED(widget);
			vg.draw_rect(rect, { background });
			const int count = int(values.size());
			if(count == 0 || max == min) return;
			auto point = [&](int i, float v) { return rect.pos + vec2(rect.size.x * float(i) / float(histogram ? count : count - 1), rect.size.y * (1.f - (clamp(v, min, max) - min) / (max - min))); };
			if(histogram)
			{
				const float base = clamp(0.f, min, max);
				for(int i = 0; i < count; ++i)
				{
					const vec2 top = point(i, values[(i + offset) % count]);
					const vec2 bottom = point(i + 1, base);
					vg.draw_rect({ top.x + 1.f, IM_MIN(top.y, bottom.y), bottom.x - top.x - 1.f, abs(bottom.y - top.y) }, { colour });
				}
			}
			else
			{
				vg.begin_path();
				vg.move_to(point(0, values[offset % count]));
				for(int i = 1; i < count; ++i)
					vg.line_to(point(i, values[(i + offset) % count]));
				vg.stroke({ colour, 1.f });
			}
		};
		graph.mark_dirty(DIRTY_REDRAW);
		if(!text.empty())
			tooltip(key(), graph, text.c_str());
		if(label && label[0] != '#')
			ui::label(key(), self, label);
		return self;
	}

	Widget plot_lines(NodeKey id, Widget parent, cstring label, span<float> values, int offset = 0, cstring overlay = nullptr, float min = FLT_MAX, float max = FLT_MAX, vec2 size = vec2(0.f))
	{
		return plot(id, parent, label, to_vector(values), offset, overlay, min, max, size, false);
	}

	Widget plot_histogram(NodeKey id, Widget parent, cstring label, span<float> values, int offset = 0, cstring overlay = nullptr, float min = FLT_MAX, float max = FLT_MAX, vec2 size = vec2(0.f))
	{
		return plot(id, parent, label, to_vector(values), offset, overlay, min, max, size, true);
	}

	using ValuesGetter = float(*)(void* data, int idx);

	vector<float> plot_values(ValuesGetter getter, void* data, int count)
	{
		vector<float> values;
		for(int i = 0; i < count; ++i)
			values.push_back(getter(data, i));
		return values;
	}

	Widget plot_lines(NodeKey id, Widget parent, cstring label, ValuesGetter getter, void* data, int count, int offset = 0, cstring overlay = nullptr, float min = FLT_MAX, float max = FLT_MAX, vec2 size = vec2(0.f))
	{
		return plot(id, parent, label, plot_values(getter, data, count), offset, overlay, min, max, size, false);
	}

	Widget plot_histogram(NodeKey id, Widget parent, cstring label, ValuesGetter getter, void* data, int count, int offset = 0, cstring overlay = nullptr, float min = FLT_MAX, float max = FLT_MAX, vec2 size = vec2(0.f))
	{
		return plot(id, parent, label, plot_values(getter, data, count), offset, overlay, min, max, size, true);
	}

	Widget progress_bar(NodeKey id, Widget parent, float fraction, const vec2& size = vec2(0.f), cstring overlay = nullptr)
	{
		UNUSED(size); UNUSED(overlay);
		// an indeterminate progress bar is passed a negative fraction
		if(fraction < 0.f)
			fraction = fmodf(-fraction, 1.f);
		return fill_bar(id, parent, IM_CLAMP(fraction, 0.f, 1.f));
	}

	// SetItemTooltip(), BeginItemTooltip(), SetTooltip(), BeginTooltip()

	void set_item_tooltip(NodeKey id, Widget item, cstring text)
	{
		tooltip(id, item, text);
	}

	Widget item_tooltip(NodeKey id, Widget item)
	{
		return hoverbox(id, item);
	}

	// a tooltip not attached to an item: it follows the mouse
	Widget begin_tooltip(NodeKey id, Widget parent)
	{
		Ui& ui = parent.ui();
		Widget self = widget(id, ui, styles().tooltip).layer();
		self.set_position(ui.m_mouse.m_pos + vec2(16.f));
		return self;
	}

	Widget set_tooltip(NodeKey id, Widget parent, cstring text)
	{
		Widget self = begin_tooltip(id, parent);
		label(key(), self, text);
		return self;
	}

	// CollapsingHeader(), TreeNode(), TreeNodeEx()

	Widget collapsing_header(NodeKey id, Widget parent, cstring label, ImGuiTreeNodeFlags flags = 0)
	{
		return expandbox(id, parent, label, (flags & ImGuiTreeNodeFlags_DefaultOpen) != 0).body;
	}

	TreeNode tree_node_ex(NodeKey id, Widget parent, cstring label, ImGuiTreeNodeFlags flags = 0)
	{
		const bool leaf = (flags & ImGuiTreeNodeFlags_Leaf) != 0;
		TreeNode self = tree_node(id, parent, label, leaf, (flags & ImGuiTreeNodeFlags_DefaultOpen) != 0);
		self.header.set_state(SELECTED, (flags & ImGuiTreeNodeFlags_Selected) != 0);
		return self;
	}

	// BeginMenu(), MenuItem()

	Widget begin_menu(NodeKey id, Widget parent, cstring label, bool submenu = false)
	{
		return menu(id, parent, label, submenu).body;
	}

	bool menu_item(NodeKey id, Widget parent, cstring label, cstring shortcut = nullptr, bool* p_selected = nullptr, bool enabled = true)
	{
		Widget self = menu_option(id, parent, label, shortcut, p_selected ? *p_selected : false);
		self.set_state(DISABLED, !enabled);
		if(self.activated() && enabled)
		{
			if(p_selected)
				*p_selected = !*p_selected;
			return true;
		}
		return false;
	}

	bool menu_item(NodeKey id, Widget parent, cstring label, cstring shortcut, bool selected, bool enabled = true)
	{
		bool value = selected;
		return menu_item(id, parent, label, shortcut, &value, enabled);
	}

	// BeginPopup(), OpenPopup(): the popup is attached to the widget that opens it, its open state is stored in the caller

	Widget begin_popup(NodeKey id, Widget parent, bool& open)
	{
		if(!open)
			return nullptr;
		Widget self = popup(id, parent, PopupFlags::Modal);
		if(self.once())
			self.set_position(parent.local_position(parent.ui().m_mouse.m_pos));
		// clicking outside of the popup closes it
		if(MouseEvent event = self.mouse_event(DeviceType::MouseLeft, EventType::Stroked))
			if(!self.frame().inside(event.m_relative))
				self.set_open(false);
		open = self.open();
		return open ? self : nullptr;
	}

	// BeginTable(), TableNextRow(), TableNextColumn(): a table of rows of cells

	struct TableLayout
	{
		Widget table;
		int columns;
		int column = 0;
		Widget line = nullptr;

		Widget next_row() { line = row(key(), table); column = 0; return *line; }
		Widget next_column() { if(!line || column == columns) next_row(); column++; return *line; }
	};

	TableLayout begin_table(NodeKey id, Widget parent, int columns)
	{
		vector<float> weights(size_t(columns), 1.f);
		return { ui::columns(id, parent, weights), columns };
	}

	// Window, Begin(): a window with a bool* p_open, as in ImGui, closing it sets the bool to false

	// the parts of the window of begin(): they are null when the window is closed
	struct BeginWindow
	{
		Widget header = nullptr;
		Widget menu = nullptr;
		Widget body = nullptr;
		explicit operator bool() const { return body != nullptr; }
		BeginWindow* operator->() { return this; }
	};

	BeginWindow begin(NodeKey id, Widget parent, cstring name, bool* p_open = nullptr, WindowState state = WindowState::Default, vec2 size = vec2(0.f))
	{
		if(p_open && !*p_open)
			return {};
		if(!p_open)
			state = WindowState(uint32_t(state) & ~uint32_t(WindowState::Closable));
		Window self = window(id, parent, name, state);
		if(size != vec2(0.f) && self.self.frame().m_size == vec2(480.f, 350.f))
			self.self.set_size(size);
		if(p_open && !self.self.open())
			*p_open = false;
		if(!self.body)
			return {};
		return { self.header, self.menu, self.body };
	}
}
}

//-----------------------------------------------------------------------------
// [SECTION] Forward Declarations
//-----------------------------------------------------------------------------

// Forward Declarations
struct ImGuiDemoWindowData;
static void ShowExampleAppMainMenuBar(Widget parent);
static void ShowExampleAppAssetsBrowser(Widget parent, bool* p_open);
static void ShowExampleAppConsole(Widget parent, bool* p_open);
static void ShowExampleAppCustomRendering(Widget parent, bool* p_open);
static void ShowExampleAppDocuments(Widget parent, bool* p_open);
static void ShowExampleAppImageViewer(Widget parent, bool* p_open);
static void ShowExampleAppLog(Widget parent, bool* p_open);
static void ShowExampleAppLayout(Widget parent, bool* p_open);
static void ShowExampleAppPropertyEditor(Widget parent, bool* p_open, ImGuiDemoWindowData* demo_data);
static void ShowExampleAppSimpleOverlay(Widget parent, bool* p_open);
static void ShowExampleAppAutoResize(Widget parent, bool* p_open);
static void ShowExampleAppConstrainedResize(Widget parent, bool* p_open);
static void ShowExampleAppFullscreen(Widget parent, bool* p_open);
static void ShowExampleAppLongText(Widget parent, bool* p_open);
static void ShowExampleAppWindowTitles(Widget parent, bool* p_open);
static void ShowExampleMenuFile(Widget parent);

// We split the contents of the big ShowDemoWindow() function into smaller functions
// (because the link time of very large functions tends to grow non-linearly)
static void DemoWindowMenuBar(Widget parent, ImGuiDemoWindowData* demo_data);
static void DemoWindowWidgets(Widget parent, ImGuiDemoWindowData* demo_data);
static void DemoWindowLayout(Widget parent);
static void DemoWindowPopups(Widget parent);
static void DemoWindowTables(Widget parent);
static void DemoWindowColumns(Widget parent);
static void DemoWindowInputs(Widget parent);

// Helper tree functions used by Property Editor & Multi-Select demos
struct ExampleTreeNode;
static ExampleTreeNode* ExampleTree_CreateNode(const char* name, int uid, ExampleTreeNode* parent);
static void             ExampleTree_DestroyNode(ExampleTreeNode* node);

// The functions of the ImGui API the demo exposes, as in imgui.h
void ShowDemoWindow(Widget parent, bool* p_open);
void ShowAboutWindow(Widget parent, bool* p_open);
void ShowStyleEditor(Widget parent, ImguiTheme* ref = NULL);
bool ShowStyleSelector(Widget parent, const char* label);
void ShowFontSelector(Widget parent, const char* label);
void ShowUserGuide(Widget parent);

//-----------------------------------------------------------------------------
// [SECTION] Helpers
//-----------------------------------------------------------------------------

// Helper to display a little (?) mark which shows a tooltip when hovered.
// In your own code you may want to display an actual icon if you are using a merged icon fonts (see docs/FONTS.md)
static void HelpMarker(Widget parent, const char* desc)
{
    Widget marker = ui::text_disabled(key(), parent, "(?)");
    if (Widget tooltip = ui::item_tooltip(key(), marker))
    {
        //ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ui::text(key(), *tooltip, desc);
        //ImGui::PopTextWrapPos();
    }
}

namespace two
{
namespace ui
{
	// ImFormatString(): formats a string, for the functions taking a format in ImGui (e.g. BulletText(), TreeNode())

	string format(cstring fmt, ...)
	{
		char buf[2048];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, sizeof(buf), fmt, args);
		va_end(args);
		return buf;
	}

	Widget text_colored(NodeKey id, Widget parent, const Colour& colour, const string& text) { return text_colored(id, parent, colour, text.c_str()); }
	Widget text_wrapped(NodeKey id, Widget parent, const string& text) { return ui::text(id, parent, text.c_str()); }
	Widget set_tooltip(NodeKey id, Widget parent, const string& text) { return set_tooltip(id, parent, text.c_str()); }
	TreeNode tree_node_ex(NodeKey id, Widget parent, const string& label, ImGuiTreeNodeFlags flags = 0) { return tree_node_ex(id, parent, label.c_str(), flags); }

	// Button() with a size

	Widget button(NodeKey id, Widget parent, cstring label, const vec2& size)
	{
		Widget self = button(id, parent, label);
		if(size.x > 0.f || size.y > 0.f)
			self.set_size(max(size, self.frame().m_size));
		return self;
	}

	Widget button(NodeKey id, Widget parent, Style& style, cstring label, const vec2& size)
	{
		Widget self = button(id, parent, style, label);
		if(size.x > 0.f || size.y > 0.f)
			self.set_size(max(size, self.frame().m_size));
		return self;
	}

	// PushStyleColor(ImGuiCol_Button...): a button style with custom colors
	Style& button_style(Style& style, const Colour& colour, const Colour& hovered, const Colour& active)
	{
		style.m_layout = styles().button.m_layout;
		style.m_skin = styles().button.m_skin;
		style.m_skin.m_background_colour = colour;
		style.decline_skin(HOVERED).m_background_colour = hovered;
		style.decline_skin(PRESSED).m_background_colour = active;
		return style;
	}

	// InvisibleButton(), Image(), ImageButton()

	Widget invisible_button(NodeKey id, Widget parent, cstring label, const vec2& size)
	{
		UNUSED(label);
		return dummy(id, parent, size);
	}

	// the texture of the font, the only texture the demo has access to
	Image* font_atlas_texture(Widget parent)
	{
		return parent.ui_window().find_image("proggy");
	}

	Widget image(NodeKey id, Widget parent, Image* image, const vec2& size, const vec2& uv0 = vec2(0.f), const vec2& uv1 = vec2(1.f))
	{
		UNUSED(uv0); UNUSED(uv1);
		Widget self = dummy(id, parent, size);
		if(image)
			self.custom_draw() = [=](Widget widget, const vec4& rect, Vg& vg) { UNUSED(widget); draw_image(vg, *image, rect); };
		return self;
	}

	Widget image_button(NodeKey id, Widget parent, Image* image, const vec2& size, const vec2& uv0 = vec2(0.f), const vec2& uv1 = vec2(1.f))
	{
		Widget self = button(id, parent, styles().button);
		ui::image(key(), self, image, size, uv0, uv1);
		return self;
	}

	// ShowFontAtlas()
	void show_font_atlas(NodeKey id, Widget parent)
	{
		Widget self = stack(id, parent);
		label(key(), self, "Fonts: proggy");
		// @todo: font atlas
	}

	// SameLine(offset, spacing): an offset or a spacing between the items of a line

	Widget same_line_spacing(NodeKey id, Widget line, float spacing)
	{
		return dummy(id, line, vec2(spacing, 0.f));
	}

	Widget same_line_offset(NodeKey id, Widget line, float offset)
	{
		// @todo: position an item at an offset in a line
		UNUSED(offset);
		return dummy(id, line, vec2(8.f, 0.f));
	}

	// a free layout area, where items are positioned with SetCursorScreenPos()
	Widget overlap(NodeKey id, Widget parent, const vec2& size)
	{
		Widget self = dummy(id, parent, size);
		return self;
	}

	// PushItemWidth(), PushItemFlag(), PushStyleVar(), PushFont(), PushTextWrapPos(), BeginDisabled()
	// @todo: those are scoped style overrides, two.ui has no equivalent yet

	void push_item_width(float width) { UNUSED(width); }
	void pop_item_width() {}
	void push_item_flag(ImGuiItemFlags flag, bool enabled) { UNUSED(flag); UNUSED(enabled); }
	void pop_item_flag() {}
	ImGuiItemFlags get_item_flags() { return ImGuiItemFlags_LiveEditOnInputText; }
	void push_style_var(ImGuiStyleVar var, float value) { UNUSED(var); UNUSED(value); }
	void push_style_var(ImGuiStyleVar var, const vec2& value) { UNUSED(var); UNUSED(value); }
	void pop_style_var(int count = 1) { UNUSED(count); }
	void push_font(void* font, float size) { UNUSED(font); UNUSED(size); }
	void pop_font() {}
	void push_text_wrap_pos(float wrap_pos) { UNUSED(wrap_pos); }
	void pop_text_wrap_pos() {}
	void begin_disabled(bool disabled = true) { UNUSED(disabled); }
	void end_disabled() {}

	// the style: GetStyle(), StyleColorsDark(), StyleColorsLight(), StyleColorsClassic(), GetStyleColorName()

	ImguiTheme& get_theme() { static ImguiTheme theme = { ImguiLook(), imgui_colours_dark() }; return theme; }
	ImguiLook& get_look() { return get_theme().look; }

	// applies the style to the styles of two.ui
	void apply_imgui_style(UiWindow& ui_window)
	{
		ui_window.reset_styles();
		style_imgui(ui_window, get_theme().look, get_theme().colours);
		ui_window.m_ui->reset_styles();
	}

	// applies the style to the styles of two.ui, whenever it's edited
	void update_imgui_style(Widget parent)
	{
		static ImguiTheme applied = get_theme();
		if(memcmp(&applied, &get_theme(), sizeof(ImguiTheme)) != 0)
		{
			applied = get_theme();
			apply_imgui_style(parent.ui_window());
		}
	}

	void style_colors_dark(Widget parent) { get_theme().colours = imgui_colours_dark(); apply_imgui_style(parent.ui_window()); }
	void style_colors_light(Widget parent) { get_theme().colours = imgui_colours_light(); apply_imgui_style(parent.ui_window()); }
	void style_colors_classic(Widget parent) { get_theme().colours = imgui_colours_classic(); apply_imgui_style(parent.ui_window()); }
	void style_wonderland(Widget parent) { get_theme() = { imgui_look_wonderland(), imgui_colours_wonderland() }; apply_imgui_style(parent.ui_window()); }

	// sets one of the two.ui styles
	void set_style(Widget parent, void(*style)(UiWindow&))
	{
		UiWindow& ui_window = parent.ui_window();
		ui_window.reset_styles();
		style(ui_window);
		ui_window.m_ui->reset_styles();
	}

	cstring get_style_color_name(int idx)
	{
		static cstring names[] = { "Text","TextDisabled","WindowBg","ChildBg","PopupBg","Border","BorderShadow","FrameBg","FrameBgHovered","FrameBgActive","TitleBg","TitleBgActive","TitleBgCollapsed","MenuBarBg","ScrollbarBg","ScrollbarGrab","ScrollbarGrabHovered","ScrollbarGrabActive","CheckMark","CheckboxSelectedBg","SliderGrab","SliderGrabActive","Button","ButtonHovered","ButtonActive","Header","HeaderHovered","HeaderActive","Separator","SeparatorHovered","SeparatorActive","ResizeGrip","ResizeGripHovered","ResizeGripActive","InputTextCursor","TabHovered","Tab","TabSelected","TabSelectedOverline","TabDimmed","TabDimmedSelected","TabDimmedSelectedOverline","PlotLines","PlotLinesHovered","PlotHistogram","PlotHistogramHovered","TableHeaderBg","TableBorderStrong","TableBorderLight","TableRowBg","TableRowBgAlt","TextLink","TextSelectedBg","TreeLines","DragDropTarget","DragDropTargetBg","UnsavedMarker","NavCursor","NavWindowingHighlight","NavWindowingDimBg","ModalWindowDimBg" };
		static_assert(IM_COUNTOF(names) == ImGuiCol_COUNT);
		return idx >= 0 && idx < ImGuiCol_COUNT ? names[idx] : "Unknown";
	}

	// GetFontSize(), GetTextLineHeight(), GetFrameHeightWithSpacing(), CalcTextSize(), GetContentRegionAvail(), GetWindowWidth()

	float get_font_size() { return get_look().FontSizeBase * get_look().FontScaleMain * get_look().FontScaleDpi; }
	float get_text_line_height() { return get_font_size(); }
	float get_text_line_height_with_spacing() { return get_font_size() + get_look().ItemSpacing.y; }
	float get_frame_height_with_spacing() { return get_font_size() + get_look().FramePadding.y * 2.f + get_look().ItemSpacing.y; }
	vec2 calc_text_size(cstring text) { return vec2(float(strlen(text)) * get_font_size() * 0.5f, get_font_size()); } // @todo: measure with the font
	vec2 get_content_region_avail(Widget parent) { return parent.frame().m_size; }
	float get_window_width(Widget parent) { return parent.frame().m_size.x; }
	int get_frame_count() { static int frame = 0; return frame++; }

	// IsItemXXX(), GetItemRectXXX(): in two.ui an item is queried through the widget declaring it

	bool is_item_hovered(Widget item, ImGuiHoveredFlags flags = 0) { UNUSED(flags); return item.hovered(); }
	bool is_item_active(Widget item) { return item.pressed() || item.focused(); }
	bool is_item_focused(Widget item) { return item.focused(); }
	bool is_item_clicked(Widget item) { return item.activated(); }
	bool is_item_toggled_open(TreeNode& node) { return node.header.activated(); }
	vec2 get_item_rect_min(Widget item) { return item.absolute_position(); }
	vec2 get_item_rect_max(Widget item) { return item.absolute_position() + item.frame().m_size; }
	vec2 get_item_rect_size(Widget item) { return item.frame().m_size; }

	// IsWindowFocused(), IsWindowHovered(): in two.ui a window is queried through the widgets of the window

	bool is_window(Widget widget) { return widget.frame().d_style == &window_styles().window || widget.frame().d_style == &window_styles().dock_window; }

	Widget get_current_window(Widget widget)
	{
		Widget parent = widget;
		while(parent->parent() && !is_window(*parent))
			parent = parent->parent();
		return *parent;
	}

	bool is_window_focused(Widget window, ImGuiFocusedFlags flags = 0) { UNUSED(flags); return window.active(); }
	bool is_window_hovered(Widget window, ImGuiHoveredFlags flags = 0) { UNUSED(flags); return window.hovered(); }

	// IsMouseXXX(), GetMouseDragDelta(), GetMouseCursor(), SetMouseCursor()

	bool is_mouse_pos_valid() { return true; }
	bool is_mouse_down(int button) { return io().MouseDown[button]; }
	bool is_mouse_double_clicked(Widget item) { return bool(item.mouse_event(DeviceType::MouseLeft, EventType::DoubleStroked)); }

	bool is_mouse_dragging(Widget item, int button = 0, float threshold = -1.f)
	{
		UNUSED(button); UNUSED(threshold);
		return bool(item.mouse_event(DeviceType::MouseLeft, EventType::Dragged, InputMod::Any, false));
	}

	vec2 get_mouse_drag_delta(Widget item, int button = 0, float threshold = -1.f)
	{
		UNUSED(button); UNUSED(threshold);
		if(MouseEvent event = item.mouse_event(DeviceType::MouseLeft, EventType::Dragged, InputMod::Any, false))
			return event.m_delta;
		return vec2(0.f);
	}

	void reset_mouse_drag_delta(Widget item) { UNUSED(item); }

	ImGuiMouseCursor get_mouse_cursor(Widget parent) { UNUSED(parent); return ImGuiMouseCursor_Arrow; }
	void set_mouse_cursor(Widget item, ImGuiMouseCursor cursor) { UNUSED(item); UNUSED(cursor); } // @todo: two.ui cursor styles

	// IsKeyDown(), GetKeyName(), Shortcut(), SetNextItemShortcut(), SetKeyboardFocusHere()

	vector<Key> keys_down(Widget parent) { UNUSED(parent); return {}; } // @todo: keyboard state
	cstring get_key_name(Key key) { UNUSED(key); return ""; }

	bool shortcut(Widget parent, InputMod modifiers, Key key, ImGuiInputFlags flags = 0)
	{
		UNUSED(flags);
		return bool(parent.key_stroke(key, modifiers));
	}

	void set_item_shortcut(Widget item, InputMod modifiers, Key key, ImGuiInputFlags flags = 0)
	{
		UNUSED(item); UNUSED(modifiers); UNUSED(key); UNUSED(flags);
	}

	void set_keyboard_focus_here(Widget item) { item.take_focus(); }

	// Scrolling: GetScrollX/Y(), GetScrollMaxX/Y(), SetScrollX/Y(), SetScrollHereX/Y(), SetScrollFromPosX/Y()

	float get_scroll_x(ScrollSheet& sheet) { return -sheet.body.frame().m_position.x; }
	float get_scroll_y(ScrollSheet& sheet) { return -sheet.body.frame().m_position.y; }
	float get_scroll_max_x(ScrollSheet& sheet) { return max(0.f, sheet.body.frame().m_size.x - sheet.scroll_zone.frame().m_size.x); }
	float get_scroll_max_y(ScrollSheet& sheet) { return max(0.f, sheet.body.frame().m_size.y - sheet.scroll_zone.frame().m_size.y); }
	void set_scroll_x(ScrollSheet& sheet, float scroll) { sheet.body.set_position(Axis::X, -clamp(scroll, 0.f, get_scroll_max_x(sheet))); }
	void set_scroll_y(ScrollSheet& sheet, float scroll) { sheet.body.set_position(Axis::Y, -clamp(scroll, 0.f, get_scroll_max_y(sheet))); }
	void set_scroll_from_pos_x(ScrollSheet& sheet, float pos, float ratio) { set_scroll_x(sheet, pos - sheet.scroll_zone.frame().m_size.x * ratio); }
	void set_scroll_from_pos_y(ScrollSheet& sheet, float pos, float ratio) { set_scroll_y(sheet, pos - sheet.scroll_zone.frame().m_size.y * ratio); }
	void set_scroll_here_x(ScrollSheet& sheet, Widget item, float ratio) { set_scroll_from_pos_x(sheet, item.frame().m_position.x, ratio); }
	void set_scroll_here_y(ScrollSheet& sheet, Widget item, float ratio) { set_scroll_from_pos_y(sheet, item.frame().m_position.y, ratio); }

	// BeginChild() returning the scroll sheet, to query and set its scrolling

	ScrollSheet child(NodeKey id, Widget parent, const vec2& size = vec2(0.f), bool borders = false, ImGuiWindowFlags flags = 0)
	{
		UNUSED(size); UNUSED(borders); UNUSED(flags);
		return scroll_sheet(id, parent);
	}

	Widget begin_child(NodeKey id, Widget parent, const vec2& size = vec2(0.f), bool borders = false, ImGuiWindowFlags flags = 0)
	{
		return child(id, parent, size, borders, flags).body;
	}

	// BeginTabItem() with a close button, TabItemButton()

	Widget tab_item(NodeKey id, Tabber& tabber, cstring name, bool* p_open = nullptr)
	{
		// @todo: closable tabs
		UNUSED(p_open);
		return tab(id, tabber, name);
	}

	Widget tab_item_button(NodeKey id, Tabber& tabber, cstring name)
	{
		return button(id, tabber.head, tabber_styles().tab_button, name);
	}

	// BeginPopupContextItem(), BeginPopupContextWindow(), OpenPopupOnItemClick(), CloseCurrentPopup(), BeginPopupModal(), BeginMainMenuBar()

	Widget begin_popup_context_item(NodeKey id, Widget item)
	{
		return context(id, item, 1 << 0);
	}

	Widget begin_popup_context_window(NodeKey id, Widget window)
	{
		return context(id, window, 1 << 1);
	}

	void open_popup_on_item_click(Widget item, bool& open)
	{
		if(item.mouse_event(DeviceType::MouseRight, EventType::Stroked))
			open = true;
	}

	void close_current_popup(Widget popup)
	{
		popup.set_open(false);
	}

	Widget begin_popup_modal(NodeKey id, Widget parent, cstring name, bool& open)
	{
		if(!open)
			return nullptr;
		Widget self = modal(id, parent.ui());
		title_header(key(), self, name);
		return self;
	}

	Widget main_menu_bar(NodeKey id, Widget parent)
	{
		return menubar(id, parent.ui());
	}

	// Drag and drop: BeginDragDropSource(), SetDragDropPayload(), BeginDragDropTarget(), AcceptDragDropPayload()
	// @todo: two.ui has a drop system (Ui::m_drop) for references, but no payloads yet

	struct Payload
	{
		string DataType;
		vector<uint8_t> Data_;
		const void* Data = nullptr;
		int DataSize = 0;
	};

	Widget begin_drag_drop_source(NodeKey id, Widget item)
	{
		if(item.mouse_event(DeviceType::MouseLeft, EventType::Dragged, InputMod::Any, false))
			return begin_tooltip(id, item);
		return nullptr;
	}

	void set_drag_drop_payload(Widget item, cstring type, const void* data, size_t size) { UNUSED(item); UNUSED(type); UNUSED(data); UNUSED(size); }
	bool begin_drag_drop_target(Widget item) { UNUSED(item); return false; }
	const Payload* accept_drag_drop_payload(Widget item, cstring type) { UNUSED(item); UNUSED(type); return nullptr; }

	// InputScalar(), DragScalar(), SliderScalar(): for any number type

	template <class T>
	bool input_scalar(NodeKey id, Widget parent, cstring label, T& value, const T* step = nullptr, cstring format = nullptr, ImGuiInputTextFlags flags = 0)
	{
		UNUSED(format); UNUSED(flags);
		return do_field(id, [&](Widget self) { return number_input<T>(key(), self, value, { lowest<T>(), limits<T>::max(), step ? *step : T(1) }); }, parent, label, true);
	}

	template <class T>
	bool drag_scalar(NodeKey id, Widget parent, cstring label, T& value, float speed, const T* min = nullptr, const T* max = nullptr, cstring format = nullptr, ImGuiSliderFlags flags = 0)
	{
		UNUSED(speed); UNUSED(format); UNUSED(flags);
		return do_field(id, [&](Widget self) { return drag_input<T>(key(), self, value, { min ? *min : lowest<T>(), max ? *max : limits<T>::max(), T(1) }); }, parent, label, true);
	}

	template <class T>
	bool slider_scalar(NodeKey id, Widget parent, cstring label, T& value, const T* min, const T* max, cstring format = nullptr, ImGuiSliderFlags flags = 0)
	{
		UNUSED(format); UNUSED(flags);
		float v = float(value);
		const bool changed = do_field(id, [&](Widget self) { return slider_input<float>(key(), self, v, { float(*min), float(*max), (float(*max) - float(*min)) / 1000.f }); }, parent, label, true);
		if(changed)
			value = T(v);
		return changed;
	}

	// GetForegroundDrawList()->AddLine()
	void foreground_line(NodeKey id, Widget parent, const vec2& a, const vec2& b, const Colour& colour, float thickness)
	{
		Widget self = widget(id, parent.ui(), styles().overlay).layer();
		self.custom_draw() = [=](Widget widget, const vec4& rect, Vg& vg) { UNUSED(widget); UNUSED(rect); vg.path_line(a, b); vg.stroke({ colour, thickness }); };
		self.mark_dirty(DIRTY_REDRAW);
	}

	// ImDrawList::AddText()
	void draw_text(Vg& vg, const vec2& pos, const Colour& colour, cstring text)
	{
		TextPaint paint = { "proggy", colour, get_font_size(), { Align::Left, Align::Left }, true, false };
		vg.draw_text(pos, text, text + strlen(text), paint);
	}
}
}

//-----------------------------------------------------------------------------
// [SECTION] Demo Window / ShowDemoWindow()
//-----------------------------------------------------------------------------

// Data to be shared across different functions of the demo.
struct ImGuiDemoWindowData
{
    // Examples Apps (accessible from the "Examples" menu)
    bool ShowMainMenuBar = false;
    bool ShowAppAssetsBrowser = false;
    bool ShowAppConsole = false;
    bool ShowAppCustomRendering = false;
    bool ShowAppDocuments = false;
    bool ShowAppImageViewer = false;
    bool ShowAppLog = false;
    bool ShowAppLayout = false;
    bool ShowAppPropertyEditor = false;
    bool ShowAppSimpleOverlay = false;
    bool ShowAppAutoResize = false;
    bool ShowAppConstrainedResize = false;
    bool ShowAppFullscreen = false;
    bool ShowAppLongText = false;
    bool ShowAppWindowTitles = false;

    // Dear ImGui Tools (accessible from the "Tools" menu)
    bool ShowMetrics = false;
    bool ShowDebugLog = false;
    bool ShowIDStackTool = false;
    bool ShowStyleEditor = false;
    bool ShowAbout = false;

    // Other data
    bool DisableSections = false;
    bool LiveEditOverride = false;
    ImGuiItemFlags LiveEditFlags = ImGuiItemFlags_LiveEditOnInputText;
    ExampleTreeNode* DemoTree = NULL;

    ~ImGuiDemoWindowData() { if (DemoTree) ExampleTree_DestroyNode(DemoTree); }
};

// Demonstrate most Dear ImGui features (this is big function!)
// You may execute this function to experiment with the UI and understand what it does.
// You may then search for keywords in the code when you are interested by a specific feature.
void ShowDemoWindow(Widget parent, bool* p_open)
{
    // Stored data
    static ImGuiDemoWindowData demo_data;

    // Examples Apps (accessible from the "Examples" menu)
    if (demo_data.ShowMainMenuBar)          { ShowExampleAppMainMenuBar(parent); }
    if (demo_data.ShowAppDocuments)         { ShowExampleAppDocuments(parent, &demo_data.ShowAppDocuments); }
    if (demo_data.ShowAppAssetsBrowser)     { ShowExampleAppAssetsBrowser(parent, &demo_data.ShowAppAssetsBrowser); }
    if (demo_data.ShowAppConsole)           { ShowExampleAppConsole(parent, &demo_data.ShowAppConsole); }
    if (demo_data.ShowAppCustomRendering)   { ShowExampleAppCustomRendering(parent, &demo_data.ShowAppCustomRendering); }
    if (demo_data.ShowAppImageViewer)       { ShowExampleAppImageViewer(parent, &demo_data.ShowAppImageViewer); }
    if (demo_data.ShowAppLog)               { ShowExampleAppLog(parent, &demo_data.ShowAppLog); }
    if (demo_data.ShowAppLayout)            { ShowExampleAppLayout(parent, &demo_data.ShowAppLayout); }
    if (demo_data.ShowAppPropertyEditor)    { ShowExampleAppPropertyEditor(parent, &demo_data.ShowAppPropertyEditor, &demo_data); }
    if (demo_data.ShowAppSimpleOverlay)     { ShowExampleAppSimpleOverlay(parent, &demo_data.ShowAppSimpleOverlay); }
    if (demo_data.ShowAppAutoResize)        { ShowExampleAppAutoResize(parent, &demo_data.ShowAppAutoResize); }
    if (demo_data.ShowAppConstrainedResize) { ShowExampleAppConstrainedResize(parent, &demo_data.ShowAppConstrainedResize); }
    if (demo_data.ShowAppFullscreen)        { ShowExampleAppFullscreen(parent, &demo_data.ShowAppFullscreen); }
    if (demo_data.ShowAppLongText)          { ShowExampleAppLongText(parent, &demo_data.ShowAppLongText); }
    if (demo_data.ShowAppWindowTitles)      { ShowExampleAppWindowTitles(parent, &demo_data.ShowAppWindowTitles); }

    // Dear ImGui Tools (accessible from the "Tools" menu)
    //if (demo_data.ShowMetrics)              { ImGui::ShowMetricsWindow(&demo_data.ShowMetrics); }
    //if (demo_data.ShowDebugLog)             { ImGui::ShowDebugLogWindow(&demo_data.ShowDebugLog); }
    //if (demo_data.ShowIDStackTool)          { ImGui::ShowIDStackToolWindow(&demo_data.ShowIDStackTool); }
    if (demo_data.ShowAbout)                { ShowAboutWindow(parent, &demo_data.ShowAbout); }
    if (demo_data.ShowStyleEditor)
    {
        if (auto window = ui::begin(key(), parent, "Dear ImGui Style Editor", &demo_data.ShowStyleEditor))
        {
            ShowStyleEditor(ui::scroll_sheet(key(), *window->body).body);
        }
    }

    // Demonstrate the various window flags. Typically you would just use the default!
    static bool no_titlebar = false;
    static bool no_scrollbar = false;
    static bool no_menu = false;
    static bool no_move = false;
    static bool no_resize = false;
    static bool no_collapse = false;
    static bool no_close = false;
    static bool no_nav = false;
    static bool no_background = false;
    static bool no_bring_to_front = false;
    static bool unsaved_document = false;

    uint32_t window_flags = uint32_t(WindowState::Closable);
    if (!no_titlebar)       window_flags |= uint32_t(WindowState::Header);
    //if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)           window_flags |= uint32_t(WindowState::Menu);
    if (!no_move)           window_flags |= uint32_t(WindowState::Movable);
    if (!no_resize)         window_flags |= uint32_t(WindowState::Sizable);
    //if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
    //if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
    //if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
    //if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
    //if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;
    if (no_close)           p_open = NULL; // Don't pass our bool* to Begin

    // We specify a default position/size in case there's no data in the .ini file.
    // We only do it to make the demo applications a little more welcoming, but typically this isn't required.
    //const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    //ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    //ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

    // Main body of the Demo window starts here.
    auto window = ui::begin(key(), parent, "Dear ImGui Demo", p_open, WindowState(window_flags), vec2(550, 680));
    if (!window)
    {
        // Early out if the window is collapsed, as an optimization.
        return;
    }

    // The window contents are scrolled by a scroll sheet
    Widget body = no_scrollbar ? *window->body : ui::scroll_sheet(key(), *window->body).body;

    // Most framed widgets share a common width settings. Remaining width is used for the label.
    // The width of the frame may be changed with PushItemWidth() or SetNextItemWidth().
    // - Positive value for absolute size, negative value for right-alignment.
    // - The default value is about GetWindowWidth() * 0.65f.
    // - See 'Demo->Layout->Widgets Width' for details.
    // Here we change the frame width based on how much width we want to give to the label.
    //const float label_width_base = ImGui::GetFontSize() * 12;               // Some amount of width for label, based on font size.
    //const float label_width_max = ImGui::GetContentRegionAvail().x * 0.40f; // ...but always leave some room for framed widgets.
    //const float label_width = IM_MIN(label_width_base, label_width_max);
    //ImGui::PushItemWidth(-label_width);                                     // Right-align: framed items will leave 'label_width' available for the label.
    //ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.40f);       // e.g. Use 40% width for framed widgets, leaving 60% width for labels.
    //ImGui::PushItemWidth(-ImGui::GetContentRegionAvail().x * 0.40f);      // e.g. Use 40% width for labels, leaving 60% width for framed widgets.
    //ImGui::PushItemWidth(ImGui::GetFontSize() * -12);                     // e.g. Use XXX width for labels, leaving the rest for framed widgets.

    // Menu Bar
    if (window->menu)
        DemoWindowMenuBar(*window->menu, &demo_data);

    ui::textf(key(), body, "dear imgui says hello! (%s) (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
    ui::spacing(key(), body);

    if (Widget help = ui::collapsing_header(key(), body, "Help"))
    {
        IMGUI_DEMO_MARKER("Help");
        ui::separator_text(key(), *help, "ABOUT THIS DEMO:");
        ui::bullet(key(), *help, "Sections below are demonstrating many aspects of the library.");
        ui::bullet(key(), *help, "The \"Examples\" menu above leads to more demo contents.");
        ui::bullet(key(), *help, "The \"Tools\" menu above gives access to: About Box, Style Editor,\n"
                                 "and Metrics/Debugger (general purpose Dear ImGui debugging tool).");
        { Widget line = ui::row(key(), *help); ui::bullet(key(), line, "Web demo (w/ source code browser): ");
          ui::text_link(key(), line, "https://pthom.github.io/imgui_explorer"); }

        ui::separator_text(key(), *help, "PROGRAMMER GUIDE:");
        ui::bullet(key(), *help, "See the ShowDemoWindow() code in imgui_demo.cpp. <- you are here!");
        ui::bullet(key(), *help, "See comments in imgui.cpp.");
        ui::bullet(key(), *help, "See example applications in the examples/ folder.");
        { Widget line = ui::row(key(), *help); ui::bullet(key(), line, "Read the FAQ at ");
          ui::text_link(key(), line, "https://www.dearimgui.com/faq/"); }
        ui::bullet(key(), *help, "Set 'io.ConfigFlags |= NavEnableKeyboard' for keyboard controls.");
        ui::bullet(key(), *help, "Set 'io.ConfigFlags |= NavEnableGamepad' for gamepad controls.");

        ui::separator_text(key(), *help, "USER GUIDE:");
        ShowUserGuide(*help);
    }

    if (Widget config = ui::collapsing_header(key(), body, "Configuration"))
    {
        ui::IO& io = ui::io();

        if (Widget n = ui::tree_node_ex(key(), *config, "Configuration##2").body)
        {
            IMGUI_DEMO_MARKER("Configuration");
            ui::separator_text(key(), *n, "General");
            { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "io.ConfigFlags: NavEnableKeyboard",    io.ConfigFlags, ImGuiConfigFlags_NavEnableKeyboard);
              HelpMarker(line, "Enable keyboard controls."); }
            { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "io.ConfigFlags: NavEnableGamepad",     io.ConfigFlags, ImGuiConfigFlags_NavEnableGamepad);
              HelpMarker(line, "Enable gamepad controls. Require backend to set io.BackendFlags |= ImGuiBackendFlags_HasGamepad.\n\nRead instructions in imgui.cpp for details."); }
            { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "io.ConfigFlags: NoMouse",              io.ConfigFlags, ImGuiConfigFlags_NoMouse);
              HelpMarker(line, "Instruct dear imgui to disable mouse inputs and interactions."); }

            // The "NoMouse" option can get us stuck with a disabled mouse! Let's provide an alternative way to fix it:
            if (io.ConfigFlags & ImGuiConfigFlags_NoMouse)
            {
                if (fmodf((float)io.Time, 0.40f) < 0.20f)
                {
                    //ImGui::SameLine();
                    ui::label(key(), *n, "<<PRESS SPACE TO DISABLE>>");
                }
                // Prevent both being checked
                if (n->key_stroke(Key::Space) || (io.ConfigFlags & ImGuiConfigFlags_NoKeyboard))
                    io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
            }

            { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "io.ConfigFlags: NoMouseCursorChange",  io.ConfigFlags, ImGuiConfigFlags_NoMouseCursorChange);
              HelpMarker(line, "Instruct backend to not alter mouse cursor shape and visibility."); }
            { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "io.ConfigFlags: NoKeyboard", io.ConfigFlags, ImGuiConfigFlags_NoKeyboard);
              HelpMarker(line, "Instruct dear imgui to disable keyboard inputs and interactions."); }

            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigInputTrickleEventQueue", io.ConfigInputTrickleEventQueue);
              HelpMarker(line, "Enable input queue trickling: some types of events submitted during the same frame (e.g. button down + up) will be spread over multiple frames, improving interactions with low framerates."); }
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.MouseDrawCursor", io.MouseDrawCursor);
              HelpMarker(line, "Instruct Dear ImGui to render a mouse cursor itself. Note that a mouse cursor rendered via your application GPU rendering path will feel more laggy than hardware cursor, but will be more in sync with your other visuals.\n\nSome desktop applications may use both kinds of cursors (e.g. enable software cursor only when resizing/dragging something)."); }

            ui::separator_text(key(), *n, "Keyboard/Gamepad Navigation");
            ui::checkbox(key(), *n, "io.ConfigNavSwapGamepadButtons", io.ConfigNavSwapGamepadButtons);
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigNavMoveSetMousePos", io.ConfigNavMoveSetMousePos);
              HelpMarker(line, "Directional/tabbing navigation teleports the mouse cursor. May be useful on TV/console systems where moving a virtual mouse is difficult"); }
            ui::checkbox(key(), *n, "io.ConfigNavCaptureKeyboard", io.ConfigNavCaptureKeyboard);
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigNavEscapeClearFocusItem", io.ConfigNavEscapeClearFocusItem);
              HelpMarker(line, "Pressing Escape clears focused item."); }
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigNavEscapeClearFocusWindow", io.ConfigNavEscapeClearFocusWindow);
              HelpMarker(line, "Pressing Escape clears focused window."); }
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigNavCursorVisibleAuto", io.ConfigNavCursorVisibleAuto);
              HelpMarker(line, "Using directional navigation key makes the cursor visible. Mouse click hides the cursor."); }
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigNavCursorVisibleAlways", io.ConfigNavCursorVisibleAlways);
              HelpMarker(line, "Navigation cursor is always visible."); }

            ui::separator_text(key(), *n, "Windows");
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigWindowsResizeFromEdges", io.ConfigWindowsResizeFromEdges);
              HelpMarker(line, "Enable resizing of windows from their edges and from the lower-left corner.\nThis requires ImGuiBackendFlags_HasMouseCursors for better mouse cursor feedback."); }
            ui::checkbox(key(), *n, "io.ConfigWindowsMoveFromTitleBarOnly", io.ConfigWindowsMoveFromTitleBarOnly);
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigWindowsCopyContentsWithCtrlC", io.ConfigWindowsCopyContentsWithCtrlC); // [EXPERIMENTAL]
              HelpMarker(line, "*EXPERIMENTAL* Ctrl+C copy the contents of focused window into the clipboard.\n\nExperimental because:\n- (1) has known issues with nested Begin/End pairs.\n- (2) text output quality varies.\n- (3) text output is in submission order rather than spatial order."); }
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigScrollbarScrollByPage", io.ConfigScrollbarScrollByPage);
              HelpMarker(line, "Enable scrolling page by page when clicking outside the scrollbar grab.\nWhen disabled, always scroll to clicked location.\nWhen enabled, Shift+Click scrolls to clicked location."); }

            ui::separator_text(key(), *n, "Widgets");
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigInputTextCursorBlink", io.ConfigInputTextCursorBlink);
              HelpMarker(line, "Enable blinking cursor (optional as some users consider it to be distracting)."); }
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigInputTextEnterKeepActive", io.ConfigInputTextEnterKeepActive);
              HelpMarker(line, "Pressing Enter will reactivate item and select all text (single-line only)."); }
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigDragClickToInputText", io.ConfigDragClickToInputText);
              HelpMarker(line, "Enable turning DragXXX widgets into text input with a simple mouse click-release (without moving)."); }
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigMacOSXBehaviors", io.ConfigMacOSXBehaviors);
              HelpMarker(line, "Swap Cmd<>Ctrl keys, enable various MacOS style behaviors."); }
            ui::label(key(), *n, "Also see Style->Rendering for rendering options.");

            ui::separator_text(key(), *n, "Settings");
            ui::checkbox(key(), *n, "io.ConfigIniSettingsSaveLastUsedDate", io.ConfigIniSettingsSaveLastUsedDate);

            // Also read: https://github.com/ocornut/imgui/wiki/Error-Handling
            ui::separator_text(key(), *n, "Error Handling");

            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigErrorRecovery", io.ConfigErrorRecovery);
              HelpMarker(line,
                "Options to configure how we handle recoverable errors.\n"
                "- Error recovery is not perfect nor guaranteed! It is a feature to ease development.\n"
                "- You not are not supposed to rely on it in the course of a normal application run.\n"
                "- Possible usage: facilitate recovery from errors triggered from a scripting language or after specific exceptions handlers.\n"
                "- Always ensure that on programmers seat you have at minimum Asserts or Tooltips enabled when making direct imgui API call! "
                "Otherwise it would severely hinder your ability to catch and correct mistakes!"); }
            ui::checkbox(key(), *n, "io.ConfigErrorRecoveryEnableAssert", io.ConfigErrorRecoveryEnableAssert);
            ui::checkbox(key(), *n, "io.ConfigErrorRecoveryEnableDebugLog", io.ConfigErrorRecoveryEnableDebugLog);
            ui::checkbox(key(), *n, "io.ConfigErrorRecoveryEnableTooltip", io.ConfigErrorRecoveryEnableTooltip);
            if (!io.ConfigErrorRecoveryEnableAssert && !io.ConfigErrorRecoveryEnableDebugLog && !io.ConfigErrorRecoveryEnableTooltip)
                io.ConfigErrorRecoveryEnableAssert = io.ConfigErrorRecoveryEnableDebugLog = io.ConfigErrorRecoveryEnableTooltip = true;

            // Also read: https://github.com/ocornut/imgui/wiki/Debug-Tools
            ui::separator_text(key(), *n, "Debug");
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigDebugIsDebuggerPresent", io.ConfigDebugIsDebuggerPresent);
              HelpMarker(line, "Enable various tools calling IM_DEBUG_BREAK().\n\nRequires a debugger being attached, otherwise IM_DEBUG_BREAK() options will appear to crash your application."); }
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigDebugHighlightIdConflicts", io.ConfigDebugHighlightIdConflicts);
              HelpMarker(line, "Highlight and show an error message when multiple items have conflicting identifiers."); }
            //ImGui::BeginDisabled();
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigDebugBeginReturnValueOnce", io.ConfigDebugBeginReturnValueOnce);
            //ImGui::EndDisabled();
              HelpMarker(line, "First calls to Begin()/BeginChild() will return false.\n\nTHIS OPTION IS DISABLED because it needs to be set at application boot-time to make sense. Showing the disabled option is a way to make this feature easier to discover."); }
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigDebugBeginReturnValueLoop", io.ConfigDebugBeginReturnValueLoop);
              HelpMarker(line, "Some calls to Begin()/BeginChild() will return false.\n\nWill cycle through window depths then repeat. Windows should be flickering while running."); }
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigDebugIgnoreFocusLoss", io.ConfigDebugIgnoreFocusLoss);
              HelpMarker(line, "Option to deactivate io.AddFocusEvent(false) handling. May facilitate interactions with a debugger when focus loss leads to clearing inputs data."); }
            { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "io.ConfigDebugIniSettings", io.ConfigDebugIniSettings);
              HelpMarker(line, "Option to save .ini data with extra comments (particularly helpful for Docking, but makes saving slower)."); }

            ui::spacing(key(), *n);
        }

        if (Widget n = ui::tree_node_ex(key(), *config, "Backend Flags").body)
        {
            IMGUI_DEMO_MARKER("Configuration/Backend Flags");
            HelpMarker(*n,
                "Those flags are set by the backends (imgui_impl_xxx files) to specify their capabilities.\n"
                "Here we expose them as read-only fields to avoid breaking interactions with your backend.");

            // FIXME: Maybe we need a BeginReadonly() equivalent to keep label bright?
            //ImGui::BeginDisabled();
            ui::checkbox_flags(key(), *n, "io.BackendFlags: HasGamepad",           io.BackendFlags, ImGuiBackendFlags_HasGamepad);
            ui::checkbox_flags(key(), *n, "io.BackendFlags: HasMouseCursors",      io.BackendFlags, ImGuiBackendFlags_HasMouseCursors);
            ui::checkbox_flags(key(), *n, "io.BackendFlags: HasSetMousePos",       io.BackendFlags, ImGuiBackendFlags_HasSetMousePos);
            ui::checkbox_flags(key(), *n, "io.BackendFlags: RendererHasVtxOffset", io.BackendFlags, ImGuiBackendFlags_RendererHasVtxOffset);
            ui::checkbox_flags(key(), *n, "io.BackendFlags: RendererHasTextures",  io.BackendFlags, ImGuiBackendFlags_RendererHasTextures);
            //ImGui::EndDisabled();

            ui::spacing(key(), *n);
        }

        if (Widget n = ui::tree_node_ex(key(), *config, "Style, Fonts").body)
        {
            IMGUI_DEMO_MARKER("Configuration/Style, Fonts");
            Widget line = ui::row(key(), *n);
            ui::checkbox(key(), line, "Style Editor", demo_data.ShowStyleEditor);
            HelpMarker(line, "The same contents can be accessed in 'Tools->Style Editor' or by calling the ShowStyleEditor() function.");
            ui::spacing(key(), *n);
        }

        if (Widget n = ui::tree_node_ex(key(), *config, "Capture/Logging").body)
        {
            IMGUI_DEMO_MARKER("Configuration/Capture, Logging");
            HelpMarker(*n,
                "The logging API redirects all text output so you can easily capture the content of "
                "a window or a block. Tree nodes can be automatically expanded.\n"
                "Try opening any of the contents below in this window and then click one of the \"Log To\" button.");
            //ImGui::LogButtons();

            HelpMarker(*n, "You can also call ImGui::LogText() to output directly to the log without a visual output.");
            if (ui::button(key(), *n, "Copy \"Hello, world!\" to clipboard").activated())
            {
                n->ui_window().m_clipboard.m_text = "Hello, world!";
                //ImGui::LogToClipboard();
                //ImGui::LogText("Hello, world!");
                //ImGui::LogFinish();
            }
        }
    }

    if (Widget opts = ui::collapsing_header(key(), body, "Window options"))
    {
        IMGUI_DEMO_MARKER("Window options");
        ui::TableLayout table = ui::begin_table(key(), *opts, 3); // ImGui::BeginTable("split", 3)
        {
            ui::checkbox(key(), table.next_column(), "No titlebar", no_titlebar);
            ui::checkbox(key(), table.next_column(), "No scrollbar", no_scrollbar);
            ui::checkbox(key(), table.next_column(), "No menu", no_menu);
            ui::checkbox(key(), table.next_column(), "No move", no_move);
            ui::checkbox(key(), table.next_column(), "No resize", no_resize);
            ui::checkbox(key(), table.next_column(), "No collapse", no_collapse);
            ui::checkbox(key(), table.next_column(), "No close", no_close);
            ui::checkbox(key(), table.next_column(), "No nav", no_nav);
            ui::checkbox(key(), table.next_column(), "No background", no_background);
            ui::checkbox(key(), table.next_column(), "No bring to front", no_bring_to_front);
            ui::checkbox(key(), table.next_column(), "Unsaved document", unsaved_document);
        }
    }

    // All demo contents
    DemoWindowWidgets(body, &demo_data);
    DemoWindowLayout(body);
    DemoWindowPopups(body);
    DemoWindowTables(body);
    DemoWindowInputs(body);

    // End of ShowDemoWindow()
    //ImGui::PopItemWidth();
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowMenuBar()
//-----------------------------------------------------------------------------

static void DemoWindowMenuBar(Widget menubar, ImGuiDemoWindowData* demo_data)
{
    {
        if (Widget menu = ui::begin_menu(key(), menubar, "Menu"))
        {
            IMGUI_DEMO_MARKER("Menu/File");
            ShowExampleMenuFile(*menu);
        }
        if (Widget menu = ui::begin_menu(key(), menubar, "Examples"))
        {
            IMGUI_DEMO_MARKER("Menu/Examples");
            ui::menu_item(key(), *menu, "Main menu bar", NULL, &demo_data->ShowMainMenuBar);

            ui::separator_text(key(), *menu, "Mini apps");
            ui::menu_item(key(), *menu, "Assets Browser", NULL, &demo_data->ShowAppAssetsBrowser);
            ui::menu_item(key(), *menu, "Console", NULL, &demo_data->ShowAppConsole);
            ui::menu_item(key(), *menu, "Custom rendering", NULL, &demo_data->ShowAppCustomRendering);
            ui::menu_item(key(), *menu, "Documents", NULL, &demo_data->ShowAppDocuments);
            ui::menu_item(key(), *menu, "Image Viewer", NULL, &demo_data->ShowAppImageViewer);
            ui::menu_item(key(), *menu, "Log", NULL, &demo_data->ShowAppLog);
            ui::menu_item(key(), *menu, "Property editor", NULL, &demo_data->ShowAppPropertyEditor);
            ui::menu_item(key(), *menu, "Simple layout", NULL, &demo_data->ShowAppLayout);
            ui::menu_item(key(), *menu, "Simple overlay", NULL, &demo_data->ShowAppSimpleOverlay);

            ui::separator_text(key(), *menu, "Concepts");
            ui::menu_item(key(), *menu, "Auto-resizing window", NULL, &demo_data->ShowAppAutoResize);
            ui::menu_item(key(), *menu, "Constrained-resizing window", NULL, &demo_data->ShowAppConstrainedResize);
            ui::menu_item(key(), *menu, "Fullscreen window", NULL, &demo_data->ShowAppFullscreen);
            ui::menu_item(key(), *menu, "Long text display", NULL, &demo_data->ShowAppLongText);
            ui::menu_item(key(), *menu, "Manipulating window titles", NULL, &demo_data->ShowAppWindowTitles);
        }
        //if (ImGui::MenuItem("MenuItem")) {} // You can also use MenuItem() inside a menu bar!
        if (Widget menu = ui::begin_menu(key(), menubar, "Tools"))
        {
            IMGUI_DEMO_MARKER("Menu/Tools");
            ui::IO& io = ui::io();
            const bool has_debug_tools = false;
            ui::menu_item(key(), *menu, "Metrics/Debugger", NULL, &demo_data->ShowMetrics, has_debug_tools);
            if (Widget submenu = ui::begin_menu(key(), *menu, "Debug Options", true))
            {
                //ImGui::BeginDisabled(!has_debug_tools);
                ui::checkbox(key(), *submenu, "Highlight ID Conflicts", io.ConfigDebugHighlightIdConflicts);
                //ImGui::EndDisabled();
                ui::checkbox(key(), *submenu, "Assert on error recovery", io.ConfigErrorRecoveryEnableAssert);
                ui::text_disabled(key(), *submenu, "(see Demo->Configuration for more)");
            }
            ui::menu_item(key(), *menu, "Debug Log", NULL, &demo_data->ShowDebugLog, has_debug_tools);
            ui::menu_item(key(), *menu, "ID Stack Tool", NULL, &demo_data->ShowIDStackTool, has_debug_tools);
            //bool is_debugger_present = io.ConfigDebugIsDebuggerPresent;
            if (ui::menu_item(key(), *menu, "Item Picker", NULL, false, has_debug_tools))// && is_debugger_present))
                {} //ImGui::DebugStartItemPicker();
            //if (!is_debugger_present)
            //    ImGui::SetItemTooltip("Requires io.ConfigDebugIsDebuggerPresent=true to be set.\n\nWe otherwise disable some extra features to avoid casual users crashing the application.");
            ui::menu_item(key(), *menu, "Style Editor", NULL, &demo_data->ShowStyleEditor);
            ui::menu_item(key(), *menu, "About Dear ImGui", NULL, &demo_data->ShowAbout);
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] Helpers: ExampleTreeNode, ExampleMemberInfo (for use by Property Editor & Multi-Select demos)
//-----------------------------------------------------------------------------

// Simple representation for a tree
// (this is designed to be simple to understand for our demos, not to be fancy or efficient etc.)
struct ExampleTreeNode
{
    // Tree structure
    char                        Name[28] = "";
    int                         UID = 0;
    ExampleTreeNode*            Parent = NULL;
    vector<ExampleTreeNode*>    Childs;
    int                         IndexInParent = 0;  // Maintaining this allows us to implement linear traversal more easily

    // Leaf Data
    bool                        HasData = false;    // All leaves have data
    bool                        DataMyBool = true;
    int                         DataMyInt = 128;
    vec2                        DataMyVec2 = vec2(0.0f, 3.141592f);
};

#if 0
// Simple representation of struct metadata/serialization data.
// (this is a minimal version of what a typical advanced application may provide)
struct ExampleMemberInfo
{
    const char*     Name;       // Member name
    ImGuiDataType   DataType;   // Member type
    int             DataCount;  // Member count (1 when scalar)
    int             Offset;     // Offset inside parent structure
};

// Metadata description of ExampleTreeNode struct.
static const ExampleMemberInfo ExampleTreeNodeMemberInfos[]
{
    { "MyName",     ImGuiDataType_String,  1, offsetof(ExampleTreeNode, Name) },
    { "MyBool",     ImGuiDataType_Bool,    1, offsetof(ExampleTreeNode, DataMyBool) },
    { "MyInt",      ImGuiDataType_S32,     1, offsetof(ExampleTreeNode, DataMyInt) },
    { "MyVec2",     ImGuiDataType_Float,   2, offsetof(ExampleTreeNode, DataMyVec2) },
};
#endif

static ExampleTreeNode* ExampleTree_CreateNode(const char* name, int uid, ExampleTreeNode* parent)
{
    ExampleTreeNode* node = new ExampleTreeNode();
    snprintf(node->Name, IM_COUNTOF(node->Name), "%s", name);
    node->UID = uid;
    node->Parent = parent;
    node->IndexInParent = parent ? int(parent->Childs.size()) : 0;
    if (parent)
        parent->Childs.push_back(node);
    return node;
}

static void ExampleTree_DestroyNode(ExampleTreeNode* node)
{
    for (ExampleTreeNode* child_node : node->Childs)
        ExampleTree_DestroyNode(child_node);
    delete node;
}

// Create example tree data
// (warning: this can allocates MANY MANY more times than other code in all of Dear ImGui + demo combined)
// (a real application managing one million nodes would likely store its tree data differently)
static ExampleTreeNode* ExampleTree_CreateDemoTree()
{
    //     20 root nodes ->    211 total nodes,   ~261 allocs.
    //   1000 root nodes ->   ~11K total nodes,   ~14K allocs.
    //  10000 root nodes ->  ~123K total nodes,  ~154K allocs.
    // 100000 root nodes -> ~1338K total nodes, ~1666K allocs.
    const int ROOT_ITEMS_COUNT = 20;

    static const char* category_names[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pear", "Pineapple", "Strawberry", "Watermelon" };
    const int category_count = IM_COUNTOF(category_names);
    const size_t NAME_MAX_LEN = sizeof(ExampleTreeNode::Name);
    char name_buf[NAME_MAX_LEN];
    int uid = 0;
    ExampleTreeNode* node_L0 = ExampleTree_CreateNode("<ROOT>", ++uid, NULL);
    for (int idx_L0 = 0; idx_L0 < ROOT_ITEMS_COUNT; idx_L0++)
    {
        snprintf(name_buf, IM_COUNTOF(name_buf), "%s %d", category_names[idx_L0 / (ROOT_ITEMS_COUNT / category_count)], idx_L0 % (ROOT_ITEMS_COUNT / category_count));
        ExampleTreeNode* node_L1 = ExampleTree_CreateNode(name_buf, ++uid, node_L0);
        const int number_of_childs = (int)strlen(node_L1->Name);
        for (int idx_L1 = 0; idx_L1 < number_of_childs; idx_L1++)
        {
            snprintf(name_buf, IM_COUNTOF(name_buf), "Child %d", idx_L1);
            ExampleTreeNode* node_L2 = ExampleTree_CreateNode(name_buf, ++uid, node_L1);
            node_L2->HasData = true;
            if (idx_L1 == 0)
            {
                snprintf(name_buf, IM_COUNTOF(name_buf), "Sub-child %d", 0);
                ExampleTreeNode* node_L3 = ExampleTree_CreateNode(name_buf, ++uid, node_L2);
                node_L3->HasData = true;
            }
        }
    }
    return node_L0;
}

//-----------------------------------------------------------------------------
// [SECTION] Helpers: ExampleImageViewer
//-----------------------------------------------------------------------------

// The image viewer needs a lower level drawing API (ImDrawList) and texture handles that two.ui doesn't expose yet
#if 0
struct ExampleImageViewerData
{
    ImU32   ImageBgColor = IM_COL32(100, 100, 100, 255);
    ImU32   GridColor = IM_COL32(255, 255, 255, 100);
    bool    GridEnabled = true;
    bool    ViewReset = true;
    ImVec2  ViewOffset; // in image space
    float   Zoom = 10.0f;
    float   ZoomMin = 1.0f;
    float   ZoomMax = 10000.0f;
};

static void ExampleImageViewer_DrawOptions(ExampleImageViewerData* data)
{
    ImGui::SetNextItemShortcut(ImGuiKey_G, ImGuiInputFlags_Tooltip); // | ImGuiInputFlags_RouteGlobal
    ImGui::Checkbox("Grid", &data->GridEnabled);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 10.0f);
    float zoom_100 = data->Zoom * 100.0f;
    if (ImGui::DragFloat("##Zoom", &zoom_100, 5.0f, data->ZoomMin * 100.0f, data->ZoomMax * 100.0f, "%.0f%%", ImGuiSliderFlags_AlwaysClamp))
        data->Zoom = zoom_100 / 100.0f;
}

static void ExampleImageViewer_DrawCanvas(ExampleImageViewerData* data, ImVec2 canvas_size, ImTextureRef image_tex_ref, int image_w, int image_h)
{
    ImGuiIO& io = ImGui::GetIO();
    ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    IM_ASSERT(canvas_size.x >= 0.0f && canvas_size.y >= 0.0f);

    // Layout canvas
    ImGui::InvisibleButton("##Canvas", canvas_size);
    ImVec2 canvas_min = ImGui::GetItemRectMin();
    ImVec2 canvas_max = ImGui::GetItemRectMax();

    if (data->ViewReset)
        data->ViewOffset = ImVec2((canvas_size.x * 0.5f / data->Zoom) - 0.5f, (canvas_size.y * 0.5f / data->Zoom) - 0.5f); // Add half a pixel padding
    data->ViewReset = false;

    // Handle inputs
    if (ImGui::SetItemKeyOwner(ImGuiKey_MouseWheelY))
        if (io.MouseWheel != 0.0f)
            data->Zoom = IM_CLAMP(data->Zoom * (1.0f + io.MouseWheel * 0.10f), data->ZoomMin, data->ZoomMax);
    float zoom = data->Zoom; // (float)(int)ViewZoom;
    if (ImGui::IsItemActive() && ImGui::IsMouseDragging(0))
    {
        data->ViewOffset.x -= io.MouseDelta.x / zoom;
        data->ViewOffset.y -= io.MouseDelta.y / zoom;
    }

    // Display image
    ImVec2 image_min, image_max;
    image_min.x = (float)(int)((canvas_min.x - (data->ViewOffset.x * zoom)) + (canvas_size.x * 0.5f));
    image_min.y = (float)(int)((canvas_min.y - (data->ViewOffset.y * zoom)) + (canvas_size.y * 0.5f));
    image_max.x = (float)(int)(image_min.x + image_w * zoom);
    image_max.y = (float)(int)(image_min.y + image_h * zoom);
    draw_list->AddRect(ImVec2(canvas_min.x - 1.0f, canvas_min.y - 1.0f), ImVec2(canvas_max.x + 1.0f, canvas_max.y + 1.0f), IM_COL32(255, 255, 255, 255));
    draw_list->PushClipRect(canvas_min, canvas_max, true);
    draw_list->AddRectFilled(image_min, image_max, data->ImageBgColor);
    if (platform_io.DrawCallback_SetSamplerNearest != NULL)
        draw_list->AddCallback(platform_io.DrawCallback_SetSamplerNearest);
    draw_list->AddImage(image_tex_ref, image_min, image_max);
    if (platform_io.DrawCallback_SetSamplerLinear != NULL)
        draw_list->AddCallback(ImGui::GetPlatformIO().DrawCallback_SetSamplerLinear);

    // Display grid lines for visible pixels
    if (data->GridEnabled && zoom > 6.0f)
    {
        const float step = (float)zoom;
        for (int px = (int)((canvas_min.x - image_min.x) / step); px <= (int)((canvas_max.x - image_min.x) / step); px++)
            draw_list->AddLineV(image_min.x + px * step, canvas_min.y, canvas_max.y, data->GridColor, 1.0f);
        for (int py = (int)((canvas_min.y - image_min.y) / step); py <= (int)((canvas_max.y - image_min.y) / step); py++)
            draw_list->AddLineH(canvas_min.x, canvas_max.x, image_min.y + py * step, data->GridColor, 1.0f);
    }
    draw_list->PopClipRect();
}
#endif

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsBasic()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsBasic(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Basic").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Basic");
        ui::separator_text(key(), *n, "General");

        IMGUI_DEMO_MARKER("Widgets/Basic/Button");
        static int clicked = 0;
        Widget line0 = ui::row(key(), *n);
        if (ui::button(key(), line0, "Button").activated())
            clicked++;
        if (clicked & 1)
        {
            //ImGui::SameLine();
            ui::label(key(), line0, "Thanks for clicking me!");
        }

        IMGUI_DEMO_MARKER("Widgets/Basic/Checkbox");
        static bool check = true;
        ui::checkbox(key(), *n, "checkbox", check);

        IMGUI_DEMO_MARKER("Widgets/Basic/RadioButton");
        static int e = 0;
        Widget line1 = ui::row(key(), *n);
        ui::radio_button(key(), line1, "radio a", e, 0); //ImGui::SameLine();
        ui::radio_button(key(), line1, "radio b", e, 1); //ImGui::SameLine();
        ui::radio_button(key(), line1, "radio c", e, 2);

        //ImGui::AlignTextToFramePadding();
        ui::text_link(key(), *n, "Hyperlink", "https://github.com/ocornut/imgui/wiki/Error-Handling");

        // Color buttons, demonstrate using PushID() to add unique identifier in the ID stack, and changing style.
        IMGUI_DEMO_MARKER("Widgets/Basic/Buttons (Colored)");
        Widget line2 = ui::row(key(), *n);
        static Style colored[7];
        for (int i = 0; i < 7; i++)
        {
            //if (i > 0)
            //    ImGui::SameLine();
            //ImGui::PushID(i);
            //ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
            //ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
            //ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
            colored[i].m_layout = styles().button.m_layout;
            colored[i].m_skin = styles().button.m_skin;
            colored[i].m_skin.m_background_colour = hsv(i / 7.0f, 0.6f, 0.6f);
            colored[i].decline_skin(HOVERED).m_background_colour = hsv(i / 7.0f, 0.7f, 0.7f);
            colored[i].decline_skin(PRESSED).m_background_colour = hsv(i / 7.0f, 0.8f, 0.8f);
            ui::button(key(i), line2, colored[i], "Click");
            //ImGui::PopStyleColor(3);
            //ImGui::PopID();
        }

        // Use AlignTextToFramePadding() to align text baseline to the baseline of framed widgets elements
        // (otherwise a Text+SameLine+Button sequence will have the text a little too high by default!)
        // See 'Demo->Layout->Text Baseline Alignment' for details.
        //ImGui::AlignTextToFramePadding();
        Widget line3 = ui::row(key(), *n);
        ui::label(key(), line3, "Hold to repeat:");
        //ImGui::SameLine();

        // Arrow buttons with Repeater
        IMGUI_DEMO_MARKER("Widgets/Basic/Buttons (Repeating)");
        static int counter = 0;
        //float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
        //ImGui::PushItemFlag(ImGuiItemFlags_ButtonRepeat, true);
        if (ui::arrow_button(key(), line3, ui::Dir::Left).activated()) { counter--; }
        //ImGui::SameLine(0.0f, spacing);
        if (ui::arrow_button(key(), line3, ui::Dir::Right).activated()) { counter++; }
        //ImGui::PopItemFlag();
        //ImGui::SameLine();
        ui::textf(key(), line3, "%d", counter);

        Widget tooltip_button = ui::button(key(), *n, "Tooltip");
        ui::set_item_tooltip(key(), tooltip_button, "I am a tooltip");

        ui::label_text(key(), *n, "label", "Value");

        ui::separator_text(key(), *n, "Inputs");

        {
            // If you want to use InputText() with std::string or any custom dynamic string type:
            // - For std::string: use the wrapper in misc/cpp/imgui_stdlib.h/.cpp
            // - Otherwise, see the 'Dear ImGui Demo->Widgets->Text Input->Resize Callback' for using ImGuiInputTextFlags_CallbackResize.
            IMGUI_DEMO_MARKER("Widgets/Basic/InputText");
            static string str0 = "Hello, world!";
            Widget line = ui::row(key(), *n);
            ui::input_text(key(), line, "input text", str0);
            HelpMarker(line,
                "USER:\n"
                "Hold Shift or use mouse to select text.\n"
                "Ctrl+Left/Right to word jump.\n"
                "Ctrl+A or Double-Click to select all.\n"
                "Ctrl+X,Ctrl+C,Ctrl+V for clipboard.\n"
                "Ctrl+Z to undo, Ctrl+Y/Ctrl+Shift+Z to redo.\n"
                "Escape to revert.\n\n"
                "PROGRAMMER:\n"
                "You can use the ImGuiInputTextFlags_CallbackResize facility if you need to wire InputText() "
                "to a dynamic string type. See misc/cpp/imgui_stdlib.h for an example (this is not demonstrated "
                "in imgui_demo.cpp).");

            static string str1 = "";
            ui::input_text_with_hint(key(), *n, "input text (w/ hint)", "enter text here", str1);

            IMGUI_DEMO_MARKER("Widgets/Basic/InputInt, InputFloat");
            static int i0 = 123;
            ui::input_int(key(), *n, "input int", i0);

            static float f0 = 0.001f;
            ui::input_float(key(), *n, "input float", f0, 0.01f); // 1.0f, "%.3f");

            static double d0 = 999999.00000001;
            ui::input_double(key(), *n, "input double", d0, 0.01f); // 1.0f, "%.8f");

            static float f1 = 1.e10f;
            Widget line_scientific = ui::row(key(), *n);
            ui::input_float(key(), line_scientific, "input scientific", f1, 0.0f); // 0.0f, "%e");
            HelpMarker(line_scientific,
                "You can input value using the scientific notation,\n"
                "  e.g. \"1e+8\" becomes \"100000000\".");

            static float vec4a[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
            ui::input_float3(key(), *n, "input float3", vec4a);
        }

        ui::separator_text(key(), *n, "Drags");

        {
            IMGUI_DEMO_MARKER("Widgets/Basic/DragInt, DragFloat");
            static int i1 = 50, i2 = 42, i3 = 128;
            Widget line = ui::row(key(), *n);
            ui::drag_int(key(), line, "drag int", i1, 1);
            HelpMarker(line,
                "Click and drag to edit value.\n"
                "Hold Shift/Alt for faster/slower edit.\n"
                "Double-Click or Ctrl+Click to input value.");
            ui::drag_int(key(), *n, "drag int 0..100", i2, 1, 0, 100); // "%d%%", ImGuiSliderFlags_AlwaysClamp);
            ui::drag_int(key(), *n, "drag int wrap 100..200", i3, 1, 100, 200); // "%d", ImGuiSliderFlags_WrapAround);

            static float f1 = 1.00f, f2 = 0.0067f;
            ui::drag_float(key(), *n, "drag float", f1, 0.005f);
            ui::drag_float(key(), *n, "drag small float", f2, 0.0001f, 0.0f, 0.0f); // "%.06f ns");
            //ImGui::DragFloat("drag wrap -1..1", &f3, 0.005f, -1.0f, 1.0f, NULL, ImGuiSliderFlags_WrapAround);
        }

        ui::separator_text(key(), *n, "Sliders");

        {
            IMGUI_DEMO_MARKER("Widgets/Basic/SliderInt, SliderFloat");
            static int i1 = 0;
            Widget line = ui::row(key(), *n);
            ui::slider_int(key(), line, "slider int", i1, -1, 3);
            HelpMarker(line, "Ctrl+Click to input value.");

            static float f1 = 0.123f, f2 = 0.0f;
            ui::slider_float(key(), *n, "slider float", f1, 0.0f, 1.0f); // "ratio = %.3f");
            ui::slider_float(key(), *n, "slider float (log)", f2, -10.0f, 10.0f); // "%.4f", ImGuiSliderFlags_Logarithmic);

            IMGUI_DEMO_MARKER("Widgets/Basic/SliderAngle");
            static float angle = 0.0f;
            ui::slider_angle(key(), *n, "slider angle", angle);

            // Using the format string to display a name instead of an integer.
            // Here we completely omit '%d' from the format string, so it'll only display a name.
            // This technique can also be used with DragInt().
            IMGUI_DEMO_MARKER("Widgets/Basic/Slider (enum)");
            enum Element { Element_Fire, Element_Earth, Element_Air, Element_Water, Element_COUNT };
            static int elem = Element_Fire;
            const char* elems_names[Element_COUNT] = { "Fire", "Earth", "Air", "Water" };
            const char* elem_name = (elem >= 0 && elem < Element_COUNT) ? elems_names[elem] : "Unknown";
            Widget line_enum = ui::row(key(), *n);
            ui::slider_int(key(), line_enum, "slider enum", elem, 0, Element_COUNT - 1); // elem_name); // Use ImGuiSliderFlags_NoInput flag to disable Ctrl+Click here.
            ui::label(key(), line_enum, elem_name);
            HelpMarker(line_enum, "Using the format string parameter to display a name instead of the underlying integer.");
        }

        ui::separator_text(key(), *n, "Selectors/Pickers");

        {
            IMGUI_DEMO_MARKER("Widgets/Basic/ColorEdit3, ColorEdit4");
            static float col1[3] = { 1.0f, 0.0f, 0.2f };
            static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
            Widget line = ui::row(key(), *n);
            ui::color_edit3(key(), line, "color 1", col1);
            HelpMarker(line,
                "Click on the color square to open a color picker.\n"
                "Click and hold to use drag and drop.\n"
                "Right-Click on the color square to show options.\n"
                "Ctrl+Click on individual component to input value.\n");

            ui::color_edit4(key(), *n, "color 2", col2);
        }

        {
            // Using the _simplified_ one-liner Combo() api here
            // See "Combo" section for examples of how to use the more flexible BeginCombo()/EndCombo() api.
            IMGUI_DEMO_MARKER("Widgets/Basic/Combo");
            const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIIIIII", "JJJJ", "KKKKKKK" };
            static int item_current = 0;
            Widget line = ui::row(key(), *n);
            ui::combo(key(), line, "combo", item_current, items);
            HelpMarker(line,
                "Using the simplified one-liner Combo API here.\n"
                "Refer to the \"Combo\" section below for an explanation of how to use the more flexible and general BeginCombo/EndCombo API.");
        }

        {
            // Using the _simplified_ one-liner ListBox() api here
            // See "List boxes" section for examples of how to use the more flexible BeginListBox()/EndListBox() api.
            IMGUI_DEMO_MARKER("Widgets/Basic/ListBox");
            const char* items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" };
            static int item_current = 1;
            Widget line = ui::row(key(), *n);
            ui::list_box(key(), line, "listbox", item_current, items, 4);
            HelpMarker(line,
                "Using the simplified one-liner ListBox API here.\n"
                "Refer to the \"List boxes\" section below for an explanation of how to use the more flexible and general BeginListBox/EndListBox API.");
        }

        // Testing ImGuiOnceUponAFrame helper.
        //static ImGuiOnceUponAFrame once;
        //for (int i = 0; i < 5; i++)
        //    if (once)
        //        ImGui::Text("This will be displayed only once.");
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsBullets()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsBullets(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Bullets").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Bullets");
        ui::bullet(key(), *n, "Bullet point 1");
        ui::bullet(key(), *n, "Bullet point 2\nOn multiple lines");
        if (Widget t = ui::tree_node_ex(key(), *n, "Tree node").body)
        {
            ui::bullet(key(), *t, "Another bullet point");
        }
        { Widget line = ui::row(key(), *n); ui::item(key(), line, styles().bullet); ui::label(key(), line, "Bullet point 3 (two calls)"); }
        { Widget line = ui::row(key(), *n); ui::item(key(), line, styles().bullet); ui::small_button(key(), line, "Button"); }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsCollapsingHeaders()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsCollapsingHeaders(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Collapsing Headers").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Collapsing Headers");
        static bool closable_group = true;
        ui::checkbox(key(), *n, "Show 2nd header", closable_group);
        Expandbox header = ui::expandbox(key(), *n, "Header", false); // ImGuiTreeNodeFlags_None
        if (Widget h = header.body)
        {
            ui::textf(key(), *h, "IsItemHovered: %d", header.header.hovered());
            for (int i = 0; i < 5; i++)
                ui::textf(key(), *h, "Some content %d", i);
        }
        if (closable_group)
        {
            // @todo: closable expandbox (CollapsingHeader with a bool* p_visible)
            Expandbox closable = ui::expandbox(key(), *n, "Header with a close button", false);
            if (Widget h = closable.body)
            {
                ui::textf(key(), *h, "IsItemHovered: %d", closable.header.hovered());
                for (int i = 0; i < 5; i++)
                    ui::textf(key(), *h, "More content %d", i);
            }
        }
        /*
        if (ImGui::CollapsingHeader("Header with a bullet", ImGuiTreeNodeFlags_Bullet))
            ImGui::Text("IsItemHovered: %d", ImGui::IsItemHovered());
        */
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsColorAndPickers()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsColorAndPickers(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Color/Picker Widgets").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Color");
        static float color[4] = { 114.0f / 255.0f, 144.0f / 255.0f, 154.0f / 255.0f, 200.0f / 255.0f };
        static ImGuiColorEditFlags base_flags = ImGuiColorEditFlags_None;

        ui::separator_text(key(), *n, "Options");
        ui::checkbox_flags(key(), *n, "ImGuiColorEditFlags_NoAlpha", base_flags, ImGuiColorEditFlags_NoAlpha);
        ui::checkbox_flags(key(), *n, "ImGuiColorEditFlags_AlphaOpaque", base_flags, ImGuiColorEditFlags_AlphaOpaque);
        ui::checkbox_flags(key(), *n, "ImGuiColorEditFlags_AlphaNoBg", base_flags, ImGuiColorEditFlags_AlphaNoBg);
        ui::checkbox_flags(key(), *n, "ImGuiColorEditFlags_AlphaPreviewHalf", base_flags, ImGuiColorEditFlags_AlphaPreviewHalf);
        { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "ImGuiColorEditFlags_NoOptions", base_flags, ImGuiColorEditFlags_NoOptions); HelpMarker(line, "Right-click on the individual color widget to show options."); }
        ui::checkbox_flags(key(), *n, "ImGuiColorEditFlags_NoDragDrop", base_flags, ImGuiColorEditFlags_NoDragDrop);
        ui::checkbox_flags(key(), *n, "ImGuiColorEditFlags_NoColorMarkers", base_flags, ImGuiColorEditFlags_NoColorMarkers);
        { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "ImGuiColorEditFlags_HDR", base_flags, ImGuiColorEditFlags_HDR); HelpMarker(line, "Currently all this does is to lift the 0..1 limits on dragging widgets."); }

        IMGUI_DEMO_MARKER("Widgets/Color/ColorEdit");
        ui::separator_text(key(), *n, "Inline color editor");
        { Widget line = ui::row(key(), *n); ui::label(key(), line, "Color widget:");
          HelpMarker(line,
            "Click on the color square to open a color picker.\n"
            "Ctrl+Click on individual component to input value.\n"); }
        ui::color_edit3(key(), *n, "MyColor##1", color); // base_flags);

        IMGUI_DEMO_MARKER("Widgets/Color/ColorEdit (HSV, with Alpha)");
        ui::label(key(), *n, "Color widget HSV with Alpha:");
        ui::color_edit4(key(), *n, "MyColor##2", color); // ImGuiColorEditFlags_DisplayHSV | base_flags);

        IMGUI_DEMO_MARKER("Widgets/Color/ColorEdit (float display)");
        ui::label(key(), *n, "Color widget with Float Display:");
        ui::color_edit4(key(), *n, "MyColor##2f", color); // ImGuiColorEditFlags_Float | base_flags);

        IMGUI_DEMO_MARKER("Widgets/Color/ColorButton (with Picker)");
        { Widget line = ui::row(key(), *n); ui::label(key(), line, "Color button with Picker:");
          HelpMarker(line,
            "With the ImGuiColorEditFlags_NoInputs flag you can hide all the slider/text inputs.\n"
            "With the ImGuiColorEditFlags_NoLabel flag you can pass a non-empty label which will only "
            "be used for the tooltip and picker popup."); }
        ui::color_edit4(key(), *n, "MyColor##3", color); // ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | base_flags);

        IMGUI_DEMO_MARKER("Widgets/Color/ColorButton (with custom Picker popup)");
        ui::label(key(), *n, "Color button with Custom Picker Popup:");

        // Generate a default palette. The palette will persist and can be edited.
        static bool saved_palette_init = true;
        static Colour saved_palette[32] = {};
        if (saved_palette_init)
        {
            for (int p = 0; p < IM_COUNTOF(saved_palette); p++)
            {
                saved_palette[p] = hsv(p / 31.0f, 0.8f, 0.8f);
                saved_palette[p].a = 1.0f; // Alpha
            }
            saved_palette_init = false;
        }

        static Colour backup_color;
        static bool mypicker = false;
        Widget line_picker = ui::row(key(), *n);
        Widget color_button = ui::color_button(key(), line_picker, "MyColor##3b", Colour(color[0], color[1], color[2], color[3])); // base_flags);
        bool open_popup = color_button.activated();
        //ImGui::SameLine(0, ImGui::GetStyle().ItemInnerSpacing.x);
        open_popup |= ui::button(key(), line_picker, "Palette").activated();
        if (open_popup)
        {
            mypicker = true; // ImGui::OpenPopup("mypicker");
            backup_color = Colour(color[0], color[1], color[2], color[3]);
        }
        if (Widget popup = ui::begin_popup(key(), line_picker, mypicker))
        {
            ui::label(key(), *popup, "MY CUSTOM COLOR PICKER WITH AN AMAZING PALETTE!");
            ui::separator(key(), *popup);
            Widget line = ui::row(key(), *popup);
            ui::color_picker4(key(), line, "##picker", color); // base_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
            //ImGui::SameLine();

            Widget group = ui::stack(key(), line); // ImGui::BeginGroup(); // Lock X position
            ui::label(key(), group, "Current");
            ui::color_button(key(), group, "##current", Colour(color[0], color[1], color[2], color[3]), vec2(60, 40)); // ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf
            ui::label(key(), group, "Previous");
            if (ui::color_button(key(), group, "##previous", backup_color, vec2(60, 40)).activated()) // ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf
                { color[0] = backup_color.r; color[1] = backup_color.g; color[2] = backup_color.b; color[3] = backup_color.a; }
            ui::separator(key(), group);
            ui::label(key(), group, "Palette");
            Widget palette_line = nullptr;
            for (int p = 0; p < IM_COUNTOF(saved_palette); p++)
            {
                //ImGui::PushID(p);
                if ((p % 8) == 0)
                    palette_line = ui::row(key(), group); //ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.y);

                //ImGuiColorEditFlags palette_button_flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip;
                if (ui::color_button(key(), *palette_line, "##palette", saved_palette[p], vec2(20, 20)).activated())
                    { color[0] = saved_palette[p].r; color[1] = saved_palette[p].g; color[2] = saved_palette[p].b; } // Preserve alpha!

                // Allow user to drop colors into each palette entry. Note that ColorButton() is already a
                // drag source by default, unless specifying the ImGuiColorEditFlags_NoDragDrop flag.
                //if (ImGui::BeginDragDropTarget())
                //{
                //    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
                //        memcpy((float*)&saved_palette[p], payload->Data, sizeof(float) * 3);
                //    if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
                //        memcpy((float*)&saved_palette[p], payload->Data, sizeof(float) * 4);
                //    ImGui::EndDragDropTarget();
                //}

                //ImGui::PopID();
            }
            //ImGui::EndGroup();
        }

        IMGUI_DEMO_MARKER("Widgets/Color/ColorButton (simple)");
        ui::label(key(), *n, "Color button only:");
        static bool no_border = false;
        ui::checkbox(key(), *n, "ImGuiColorEditFlags_NoBorder", no_border);
        ui::color_button(key(), *n, "MyColor##3c", Colour(color[0], color[1], color[2], color[3]), vec2(80, 80)); // base_flags | (no_border ? ImGuiColorEditFlags_NoBorder : 0)

        IMGUI_DEMO_MARKER("Widgets/Color/ColorPicker");
        ui::separator_text(key(), *n, "Color picker");

        static bool ref_color = false;
        static float ref_color_v[4] = { 1.0f, 0.0f, 1.0f, 0.5f };
        static int picker_mode = 0;
        static int display_mode = 0;
        static ImGuiColorEditFlags color_picker_flags = ImGuiColorEditFlags_AlphaBar;

        //ImGui::PushID("Color picker");
        ui::checkbox_flags(key(), *n, "ImGuiColorEditFlags_NoAlpha", color_picker_flags, ImGuiColorEditFlags_NoAlpha);
        ui::checkbox_flags(key(), *n, "ImGuiColorEditFlags_AlphaBar", color_picker_flags, ImGuiColorEditFlags_AlphaBar);
        Widget line_side = ui::row(key(), *n);
        ui::checkbox_flags(key(), line_side, "ImGuiColorEditFlags_NoSidePreview", color_picker_flags, ImGuiColorEditFlags_NoSidePreview);
        if (color_picker_flags & ImGuiColorEditFlags_NoSidePreview)
        {
            //ImGui::SameLine();
            ui::checkbox(key(), line_side, "With Ref Color", ref_color);
            if (ref_color)
            {
                //ImGui::SameLine();
                ui::color_edit4(key(), line_side, "##RefColor", ref_color_v); // ImGuiColorEditFlags_NoInputs | base_flags);
            }
        }
        ui::checkbox_flags(key(), *n, "ImGuiColorEditFlags_PickerNoRotate", color_picker_flags, ImGuiColorEditFlags_PickerNoRotate);

        { Widget line = ui::row(key(), *n); ui::combo(key(), line, "Picker Mode", picker_mode, { "Auto/Current", "ImGuiColorEditFlags_PickerHueBar", "ImGuiColorEditFlags_PickerHueWheel" });
          HelpMarker(line, "When not specified explicitly, user can right-click the picker to change mode."); }

        { Widget line = ui::row(key(), *n); ui::combo(key(), line, "Display Mode", display_mode, { "Auto/Current", "ImGuiColorEditFlags_NoInputs", "ImGuiColorEditFlags_DisplayRGB", "ImGuiColorEditFlags_DisplayHSV", "ImGuiColorEditFlags_DisplayHex" });
          HelpMarker(line,
            "ColorEdit defaults to displaying RGB inputs if you don't specify a display mode, "
            "but the user can change it with a right-click on those inputs.\n\nColorPicker defaults to displaying RGB+HSV+Hex "
            "if you don't specify a display mode.\n\nYou can change the defaults using io.ConfigColorEditFlags."); }

        ImGuiColorEditFlags flags = base_flags | color_picker_flags;
        if (picker_mode == 1)  flags |= ImGuiColorEditFlags_PickerHueBar;
        if (picker_mode == 2)  flags |= ImGuiColorEditFlags_PickerHueWheel;
        if (display_mode == 1) flags |= ImGuiColorEditFlags_NoInputs;       // Disable all RGB/HSV/Hex displays
        if (display_mode == 2) flags |= ImGuiColorEditFlags_DisplayRGB;     // Override display mode
        if (display_mode == 3) flags |= ImGuiColorEditFlags_DisplayHSV;
        if (display_mode == 4) flags |= ImGuiColorEditFlags_DisplayHex;
        ui::color_picker4(key(), *n, "MyColor##4", color); // flags, ref_color ? &ref_color_v.x : NULL);

        { Widget line = ui::row(key(), *n); ui::label(key(), line, "Set defaults in code:");
          HelpMarker(line,
            "io.ConfigColorEditFlags is designed to allow you to set boot-time default.\n"
            "We don't have Push/Pop functions because you can force options on a per-widget basis if needed, "
            "and the user can change non-forced ones with the options menu.\nWe don't have a getter to avoid "
            "encouraging you to persistently save values that aren't forward-compatible."); }
        if (ui::button(key(), *n, "Overwrite default: Uint8 + HSV + Hue Bar").activated())
            {} //ImGui::GetIO().ConfigColorEditFlags = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_PickerHueBar;
        if (ui::button(key(), *n, "Overwrite default: Float + HDR + Hue Wheel").activated())
            {} //ImGui::GetIO().ConfigColorEditFlags = ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel;

        // Always display a small version of both types of pickers
        // (that's in order to make it more visible in the demo to people who are skimming quickly through it)
        ui::label(key(), *n, "Both types:");
        //float w = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.40f;
        //ImGui::SetNextItemWidth(w);
        Widget line_both = ui::row(key(), *n);
        ui::color_picker3(key(), line_both, "##MyColor##5", color); // ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
        //ImGui::SameLine();
        //ImGui::SetNextItemWidth(w);
        ui::color_picker3(key(), line_both, "##MyColor##6", color); // ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);
        //ImGui::PopID();

        // HSV encoded support (to avoid RGB<>HSV round trips and singularities when S==0 or V==0)
        static float color_hsv[4] = { 0.23f, 1.0f, 1.0f, 1.0f }; // Stored as HSV!
        ui::spacing(key(), *n);
        { Widget line = ui::row(key(), *n); ui::label(key(), line, "HSV encoded colors");
          HelpMarker(line,
            "By default, colors are given to ColorEdit and ColorPicker in RGB, but ImGuiColorEditFlags_InputHSV "
            "allows you to store colors as HSV and pass them to ColorEdit and ColorPicker as HSV. This comes with the "
            "added benefit that you can manipulate hue values with the picker even when saturation or value are zero."); }
        ui::label(key(), *n, "Color widget with InputHSV:");
        ui::color_edit4(key(), *n, "HSV shown as RGB##1", color_hsv); // ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_Float);
        ui::color_edit4(key(), *n, "HSV shown as HSV##1", color_hsv); // ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_InputHSV | ImGuiColorEditFlags_Float);
        ui::drag_float4(key(), *n, "Raw HSV values", color_hsv, 0.01f, 0.0f, 1.0f);
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsComboBoxes()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsComboBoxes(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Combo").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Combo");
        // Combo Boxes are also called "Dropdown" in other systems
        // Expose flags as checkbox for the demo
        static ImGuiComboFlags flags = 0;
        { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "ImGuiComboFlags_PopupAlignLeft", flags, ImGuiComboFlags_PopupAlignLeft);
          HelpMarker(line, "Only makes a difference if the popup is larger than the combo"); }
        if (ui::checkbox_flags(key(), *n, "ImGuiComboFlags_NoArrowButton", flags, ImGuiComboFlags_NoArrowButton))
            flags &= ~ImGuiComboFlags_NoPreview;     // Clear incompatible flags
        if (ui::checkbox_flags(key(), *n, "ImGuiComboFlags_NoPreview", flags, ImGuiComboFlags_NoPreview))
            flags &= ~(ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_WidthFitPreview); // Clear incompatible flags
        if (ui::checkbox_flags(key(), *n, "ImGuiComboFlags_WidthFitPreview", flags, ImGuiComboFlags_WidthFitPreview))
            flags &= ~ImGuiComboFlags_NoPreview;

        // Override default popup height
        if (ui::checkbox_flags(key(), *n, "ImGuiComboFlags_HeightSmall", flags, ImGuiComboFlags_HeightSmall))
            flags &= ~(ImGuiComboFlags_HeightMask_ & ~ImGuiComboFlags_HeightSmall);
        if (ui::checkbox_flags(key(), *n, "ImGuiComboFlags_HeightRegular", flags, ImGuiComboFlags_HeightRegular))
            flags &= ~(ImGuiComboFlags_HeightMask_ & ~ImGuiComboFlags_HeightRegular);
        if (ui::checkbox_flags(key(), *n, "ImGuiComboFlags_HeightLargest", flags, ImGuiComboFlags_HeightLargest))
            flags &= ~(ImGuiComboFlags_HeightMask_ & ~ImGuiComboFlags_HeightLargest);

        // Using the generic BeginCombo() API, you have full control over how to display the combo contents.
        // (your selection data could be an index, a pointer to the object, an id for the object, a flag intrusively
        // stored in the object itself, etc.)
        const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
        static int item_selected_idx = 0; // Here we store our selection data as an index.

        // Pass in the preview value visible before opening the combo (it could technically be different contents or not pulled from items[])
        const char* combo_preview_value = items[item_selected_idx];
        if (Widget combo = ui::begin_combo(key(), *n, "combo 1", combo_preview_value)) // flags))
        {
            for (int i = 0; i < IM_COUNTOF(items); i++)
            {
                const bool is_selected = (item_selected_idx == i);
                if (ui::selectable(key(), *combo, items[i], is_selected).activated())
                    item_selected_idx = i;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                //if (is_selected)
                //    ImGui::SetItemDefaultFocus();
            }
        }

        // Show case embedding a filter using a simple trick: displaying the filter inside combo contents.
        // See https://github.com/ocornut/imgui/issues/718 for advanced/esoteric alternatives.
        if (Widget combo = ui::begin_combo(key(), *n, "combo 2 (w/ filter)", combo_preview_value)) // flags))
        {
            static string filter;
            //if (ImGui::IsWindowAppearing())
            //{
            //    ImGui::SetKeyboardFocusHere();
            //    filter.Clear();
            //}
            //ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F);
            //ImGui::SetNextItemWidth(-FLT_MIN);
            ui::input_text_with_hint(key(), *combo, "##Filter", "Filter (incl -excl)", filter);

            for (int i = 0; i < IM_COUNTOF(items); i++)
            {
                const bool is_selected = (item_selected_idx == i);
                if (ui::filter(filter, items[i]))
                    if (ui::selectable(key(), *combo, items[i], is_selected).activated())
                        item_selected_idx = i;
            }
        }

        ui::spacing(key(), *n);
        ui::separator_text(key(), *n, "One-liner variants");
        HelpMarker(*n, "The Combo() function is not greatly useful apart from cases were you want to embed all options in a single strings.\nFlags above don't apply to this section.");

        // Simplified one-liner Combo() API, using values packed in a single constant string
        // This is a convenience for when the selection set is small and known at compile-time.
        static int item_current_2 = 0;
        ui::combo(key(), *n, "combo 3 (one-liner)", item_current_2, { "aaaa", "bbbb", "cccc", "dddd", "eeee" });

        // Simplified one-liner Combo() using an array of const char*
        // This is not very useful (may obsolete): prefer using BeginCombo()/EndCombo() for full control.
        static int item_current_3 = -1; // If the selection isn't within 0..count, Combo won't display a preview
        ui::combo(key(), *n, "combo 4 (array)", item_current_3, items);

        // Simplified one-liner Combo() using an accessor function
        //static int item_current_4 = 0;
        //ImGui::Combo("combo 5 (function)", &item_current_4, [](void* data, int n) { return ((const char**)data)[n]; }, items, IM_COUNTOF(items));
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsDataTypes()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsDataTypes(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Data Types").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Data Types");
        // DragScalar/InputScalar/SliderScalar functions allow various data types
        // - signed/unsigned
        // - 8/16/32/64-bits
        // - integer/float/double
        // To avoid polluting the public API with all possible combinations, we use the ImGuiDataType enum
        // to pass the type, and passing all arguments by pointer.
        // This is the reason the test code below creates local variables to hold "zero" "one" etc. for each type.
        // In practice, if you frequently use a given type that is not covered by the normal API entry points,
        // you can wrap it yourself inside a 1 line function which can take typed argument as value instead of void*,
        // and then pass their address to the generic function. For example:
        //   bool MySliderU64(const char *label, u64* value, u64 min = 0, u64 max = 0, const char* format = "%lld")
        //   {
        //      return SliderScalar(label, ImGuiDataType_U64, value, &min, &max, format);
        //   }

        // Setup limits (as helper variables so we can take their address, as explained above)
        // Note: SliderScalar() functions have a maximum usable range of half the natural type maximum, hence the /2.
        const int8_t   s8_zero  = 0,   s8_one  = 1,   s8_fifty  = 50, s8_min  = -128,        s8_max = 127;
        const uint8_t  u8_zero  = 0,   u8_one  = 1,   u8_fifty  = 50, u8_min  = 0,           u8_max = 255;
        const int16_t  s16_zero = 0,   s16_one = 1,   s16_fifty = 50, s16_min = -32768,      s16_max = 32767;
        const uint16_t u16_zero = 0,   u16_one = 1,   u16_fifty = 50, u16_min = 0,           u16_max = 65535;
        const int32_t  s32_zero = 0,   s32_one = 1,   s32_fifty = 50, s32_min = INT_MIN/2,   s32_max = INT_MAX/2,    s32_hi_a = INT_MAX/2 - 100,    s32_hi_b = INT_MAX/2;
        const uint32_t u32_zero = 0,   u32_one = 1,   u32_fifty = 50, u32_min = 0,           u32_max = UINT_MAX/2,   u32_hi_a = UINT_MAX/2 - 100,   u32_hi_b = UINT_MAX/2;
        const int64_t  s64_zero = 0,   s64_one = 1,   s64_fifty = 50, s64_min = LLONG_MIN/2, s64_max = LLONG_MAX/2,  s64_hi_a = LLONG_MAX/2 - 100,  s64_hi_b = LLONG_MAX/2;
        const uint64_t u64_zero = 0,   u64_one = 1,   u64_fifty = 50, u64_min = 0,           u64_max = ULLONG_MAX/2, u64_hi_a = ULLONG_MAX/2 - 100, u64_hi_b = ULLONG_MAX/2;
        const float    f32_zero = 0.f, f32_one = 1.f, f32_lo_a = -10000000000.0f, f32_hi_a = +10000000000.0f;
        const double   f64_zero = 0.,  f64_one = 1.,  f64_lo_a = -1000000000000000.0, f64_hi_a = +1000000000000000.0;

        // State
        static int8_t   s8_v  = 127;
        static uint8_t  u8_v  = 255;
        static int16_t  s16_v = 32767;
        static uint16_t u16_v = 65535;
        static int32_t  s32_v = -1;
        static uint32_t u32_v = (uint32_t)-1;
        static int64_t  s64_v = -1;
        static uint64_t u64_v = (uint64_t)-1;
        static float    f32_v = 0.123f;
        static double   f64_v = 90000.01234567890123456789;

        const float drag_speed = 0.2f;
        static bool drag_clamp = false;
        IMGUI_DEMO_MARKER("Widgets/Data Types/Drags");
        ui::separator_text(key(), *n, "Drags");
        { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "Clamp integers to 0..50", drag_clamp);
          HelpMarker(line,
            "As with every widget in dear imgui, we never modify values unless there is a user interaction.\n"
            "You can override the clamping limits by using Ctrl+Click to input a value."); }
        ui::drag_scalar(key(), *n, "drag s8",        s8_v,  drag_speed, drag_clamp ? &s8_zero  : NULL, drag_clamp ? &s8_fifty  : NULL);
        ui::drag_scalar(key(), *n, "drag u8",        u8_v,  drag_speed, drag_clamp ? &u8_zero  : NULL, drag_clamp ? &u8_fifty  : NULL, "%u ms");
        ui::drag_scalar(key(), *n, "drag s16",       s16_v, drag_speed, drag_clamp ? &s16_zero : NULL, drag_clamp ? &s16_fifty : NULL);
        ui::drag_scalar(key(), *n, "drag u16",       u16_v, drag_speed, drag_clamp ? &u16_zero : NULL, drag_clamp ? &u16_fifty : NULL, "%u ms");
        ui::drag_scalar(key(), *n, "drag s32",       s32_v, drag_speed, drag_clamp ? &s32_zero : NULL, drag_clamp ? &s32_fifty : NULL);
        ui::drag_scalar(key(), *n, "drag s32 hex",   s32_v, drag_speed, drag_clamp ? &s32_zero : NULL, drag_clamp ? &s32_fifty : NULL, "0x%08X");
        ui::drag_scalar(key(), *n, "drag u32",       u32_v, drag_speed, drag_clamp ? &u32_zero : NULL, drag_clamp ? &u32_fifty : NULL, "%u ms");
        ui::drag_scalar(key(), *n, "drag s64",       s64_v, drag_speed, drag_clamp ? &s64_zero : NULL, drag_clamp ? &s64_fifty : NULL);
        ui::drag_scalar(key(), *n, "drag u64",       u64_v, drag_speed, drag_clamp ? &u64_zero : NULL, drag_clamp ? &u64_fifty : NULL);
        ui::drag_scalar(key(), *n, "drag float",     f32_v, 0.005f,  &f32_zero, &f32_one, "%f");
        ui::drag_scalar(key(), *n, "drag float log", f32_v, 0.005f,  &f32_zero, &f32_one, "%f", ImGuiSliderFlags_Logarithmic);
        ui::drag_scalar(key(), *n, "drag double",    f64_v, 0.0005f, &f64_zero, (const double*)NULL, "%.10f grams");
        ui::drag_scalar(key(), *n, "drag double log",f64_v, 0.0005f, &f64_zero, &f64_one, "0 < %.10f < 1", ImGuiSliderFlags_Logarithmic);

        IMGUI_DEMO_MARKER("Widgets/Data Types/Sliders");
        ui::separator_text(key(), *n, "Sliders");
        ui::slider_scalar(key(), *n, "slider s8 full",       s8_v,  &s8_min,   &s8_max,   "%d");
        ui::slider_scalar(key(), *n, "slider u8 full",       u8_v,  &u8_min,   &u8_max,   "%u");
        ui::slider_scalar(key(), *n, "slider s16 full",      s16_v, &s16_min,  &s16_max,  "%d");
        ui::slider_scalar(key(), *n, "slider u16 full",      u16_v, &u16_min,  &u16_max,  "%u");
        ui::slider_scalar(key(), *n, "slider s32 low",       s32_v, &s32_zero, &s32_fifty,"%d");
        ui::slider_scalar(key(), *n, "slider s32 high",      s32_v, &s32_hi_a, &s32_hi_b, "%d");
        ui::slider_scalar(key(), *n, "slider s32 full",      s32_v, &s32_min,  &s32_max,  "%d");
        ui::slider_scalar(key(), *n, "slider s32 hex",       s32_v, &s32_zero, &s32_fifty, "0x%04X");
        ui::slider_scalar(key(), *n, "slider u32 low",       u32_v, &u32_zero, &u32_fifty,"%u");
        ui::slider_scalar(key(), *n, "slider u32 high",      u32_v, &u32_hi_a, &u32_hi_b, "%u");
        ui::slider_scalar(key(), *n, "slider u32 full",      u32_v, &u32_min,  &u32_max,  "%u");
        ui::slider_scalar(key(), *n, "slider s64 low",       s64_v, &s64_zero, &s64_fifty,"%lld");
        ui::slider_scalar(key(), *n, "slider s64 high",      s64_v, &s64_hi_a, &s64_hi_b, "%lld");
        ui::slider_scalar(key(), *n, "slider s64 full",      s64_v, &s64_min,  &s64_max,  "%lld");
        ui::slider_scalar(key(), *n, "slider u64 low",       u64_v, &u64_zero, &u64_fifty,"%llu ms");
        ui::slider_scalar(key(), *n, "slider u64 high",      u64_v, &u64_hi_a, &u64_hi_b, "%llu ms");
        ui::slider_scalar(key(), *n, "slider u64 full",      u64_v, &u64_min,  &u64_max,  "%llu ms");
        ui::slider_scalar(key(), *n, "slider float low",     f32_v, &f32_zero, &f32_one);
        ui::slider_scalar(key(), *n, "slider float low log", f32_v, &f32_zero, &f32_one,  "%.10f", ImGuiSliderFlags_Logarithmic);
        ui::slider_scalar(key(), *n, "slider float high",    f32_v, &f32_lo_a, &f32_hi_a, "%e");
        ui::slider_scalar(key(), *n, "slider double low",    f64_v, &f64_zero, &f64_one,  "%.10f grams");
        ui::slider_scalar(key(), *n, "slider double low log",f64_v, &f64_zero, &f64_one,  "%.10f", ImGuiSliderFlags_Logarithmic);
        ui::slider_scalar(key(), *n, "slider double high",   f64_v, &f64_lo_a, &f64_hi_a, "%e grams");

        ui::separator_text(key(), *n, "Sliders (reverse)");
        ui::slider_scalar(key(), *n, "slider s8 reverse",    s8_v,  &s8_max,    &s8_min,   "%d");
        ui::slider_scalar(key(), *n, "slider u8 reverse",    u8_v,  &u8_max,    &u8_min,   "%u");
        ui::slider_scalar(key(), *n, "slider s32 reverse",   s32_v, &s32_fifty, &s32_zero, "%d");
        ui::slider_scalar(key(), *n, "slider u32 reverse",   u32_v, &u32_fifty, &u32_zero, "%u");
        ui::slider_scalar(key(), *n, "slider s64 reverse",   s64_v, &s64_fifty, &s64_zero, "%lld");
        ui::slider_scalar(key(), *n, "slider u64 reverse",   u64_v, &u64_fifty, &u64_zero, "%llu ms");

        IMGUI_DEMO_MARKER("Widgets/Data Types/Inputs");
        static bool inputs_step = true;
        static ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
        ui::separator_text(key(), *n, "Inputs");
        ui::checkbox(key(), *n, "Show step buttons", inputs_step);
        ui::checkbox_flags(key(), *n, "ImGuiInputTextFlags_ReadOnly", flags, ImGuiInputTextFlags_ReadOnly);
        ui::checkbox_flags(key(), *n, "ImGuiInputTextFlags_ParseEmptyRefVal", flags, ImGuiInputTextFlags_ParseEmptyRefVal);
        ui::checkbox_flags(key(), *n, "ImGuiInputTextFlags_DisplayEmptyRefVal", flags, ImGuiInputTextFlags_DisplayEmptyRefVal);
        ui::input_scalar(key(), *n, "input s8",      s8_v,  inputs_step ? &s8_one  : NULL, "%d", flags);
        ui::input_scalar(key(), *n, "input u8",      u8_v,  inputs_step ? &u8_one  : NULL, "%u", flags);
        ui::input_scalar(key(), *n, "input s16",     s16_v, inputs_step ? &s16_one : NULL, "%d", flags);
        ui::input_scalar(key(), *n, "input u16",     u16_v, inputs_step ? &u16_one : NULL, "%u", flags);
        ui::input_scalar(key(), *n, "input s32",     s32_v, inputs_step ? &s32_one : NULL, "%d", flags);
        ui::input_scalar(key(), *n, "input s32 hex", s32_v, inputs_step ? &s32_one : NULL, "%04X", flags);
        ui::input_scalar(key(), *n, "input u32",     u32_v, inputs_step ? &u32_one : NULL, "%u", flags);
        ui::input_scalar(key(), *n, "input u32 hex", u32_v, inputs_step ? &u32_one : NULL, "%08X", flags);
        ui::input_scalar(key(), *n, "input s64",     s64_v, inputs_step ? &s64_one : NULL, NULL, flags);
        ui::input_scalar(key(), *n, "input u64",     u64_v, inputs_step ? &u64_one : NULL, NULL, flags);
        ui::input_scalar(key(), *n, "input float",   f32_v, inputs_step ? &f32_one : NULL, NULL, flags);
        ui::input_scalar(key(), *n, "input double",  f64_v, inputs_step ? &f64_one : NULL, NULL, flags);
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsDisableBlocks()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsDisableBlocks(Widget parent, ImGuiDemoWindowData* demo_data)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Disable Blocks").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Disable Blocks");
        Widget line = ui::row(key(), *n);
        ui::checkbox(key(), line, "Disable entire section above", demo_data->DisableSections);
        HelpMarker(line, "Demonstrate using BeginDisabled()/EndDisabled() across other sections.");
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsDragAndDrop()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsDragAndDrop(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Drag and Drop").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Drag and drop");
        if (Widget n0 = ui::tree_node_ex(key(), *n, "Drag and drop in standard widgets").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Drag and drop/Standard widgets");
            // ColorEdit widgets automatically act as drag source and drag target.
            // They are using standardized payload strings IMGUI_PAYLOAD_TYPE_COLOR_3F and IMGUI_PAYLOAD_TYPE_COLOR_4F
            // to allow your own widgets to use colors in their drag and drop interaction.
            // Also see 'Demo->Widgets->Color/Picker Widgets->Palette' demo.
            HelpMarker(*n0, "You can drag from the color squares.");
            static float col1[3] = { 1.0f, 0.0f, 0.2f };
            static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
            ui::color_edit3(key(), *n0, "color 1", col1);
            ui::color_edit4(key(), *n0, "color 2", col2);
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Drag and drop to copy/swap items").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Drag and drop/Copy-swap items");
            enum Mode
            {
                Mode_Copy,
                Mode_Move,
                Mode_Swap
            };
            static int mode = 0;
            Widget line = ui::row(key(), *n0);
            if (ui::radio_button(key(), line, "Copy", mode == Mode_Copy)) { mode = Mode_Copy; } //ImGui::SameLine();
            if (ui::radio_button(key(), line, "Move", mode == Mode_Move)) { mode = Mode_Move; } //ImGui::SameLine();
            if (ui::radio_button(key(), line, "Swap", mode == Mode_Swap)) { mode = Mode_Swap; }
            static const char* names[9] =
            {
                "Bobby", "Beatrice", "Betty",
                "Brianna", "Barry", "Bernard",
                "Bibi", "Blaine", "Bryn"
            };
            Widget names_line = nullptr;
            for (int i = 0; i < IM_COUNTOF(names); i++)
            {
                //ImGui::PushID(i);
                if ((i % 3) == 0)
                    names_line = ui::row(key(), *n0); //ImGui::SameLine();
                Widget button = ui::button(key(i), *names_line, names[i]); // ImVec2(60, 60));

                // Our buttons are both drag sources and drag targets here!
                if (Widget source = ui::begin_drag_drop_source(key(), button)) // ImGuiDragDropFlags_None
                {
                    // Set payload to carry the index of our item (could be anything)
                    ui::set_drag_drop_payload(button, "DND_DEMO_CELL", &i, sizeof(int));

                    // Display preview (could be anything, e.g. when dragging an image we could decide to display
                    // the filename and a small preview of the image, etc.)
                    if (mode == Mode_Copy) { ui::textf(key(), *source, "Copy %s", names[i]); }
                    if (mode == Mode_Move) { ui::textf(key(), *source, "Move %s", names[i]); }
                    if (mode == Mode_Swap) { ui::textf(key(), *source, "Swap %s", names[i]); }
                }
                if (ui::begin_drag_drop_target(button))
                {
                    if (const ui::Payload* payload = ui::accept_drag_drop_payload(button, "DND_DEMO_CELL"))
                    {
                        assert(payload->DataSize == sizeof(int));
                        int payload_n = *(const int*)payload->Data;
                        if (mode == Mode_Copy)
                        {
                            names[i] = names[payload_n];
                        }
                        if (mode == Mode_Move)
                        {
                            names[i] = names[payload_n];
                            names[payload_n] = "";
                        }
                        if (mode == Mode_Swap)
                        {
                            const char* tmp = names[i];
                            names[i] = names[payload_n];
                            names[payload_n] = tmp;
                        }
                    }
                }
                //ImGui::PopID();
            }
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Drag to reorder items (simple)").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Drag and Drop/Drag to reorder items (simple)");
            // FIXME: there is temporary (usually single-frame) ID Conflict during reordering as a same item may be submitting twice.
            // This code was always slightly faulty but in a way which was not easily noticeable.
            // Until we fix this, enable ImGuiItemFlags_AllowDuplicateId to disable detecting the issue.
            //ImGui::PushItemFlag(ImGuiItemFlags_AllowDuplicateId, true);

            // Simple reordering
            HelpMarker(*n0,
                "We don't use the drag and drop api at all here! "
                "Instead we query when the item is held but not hovered, and order items accordingly.");
            static const char* item_names[] = { "Item One", "Item Two", "Item Three", "Item Four", "Item Five" };
            for (int i = 0; i < IM_COUNTOF(item_names); i++)
            {
                const char* item = item_names[i];
                Widget selectable = ui::selectable(key(), *n0, item, false);

                if (ui::is_item_active(selectable) && !ui::is_item_hovered(selectable))
                {
                    int n_next = i + (ui::get_mouse_drag_delta(selectable).y < 0.0f ? -1 : 1);
                    if (n_next >= 0 && n_next < IM_COUNTOF(item_names))
                    {
                        item_names[i] = item_names[n_next];
                        item_names[n_next] = item;
                        ui::reset_mouse_drag_delta(selectable);
                    }
                }
            }

            //ImGui::PopItemFlag();
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Tooltip at target location").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Drag and Drop/Tooltip at target location");
            for (int i = 0; i < 2; i++)
            {
                // Drop targets
                Widget button = ui::button(key(), *n0, i ? "drop here##1" : "drop here##0");
                if (ui::begin_drag_drop_target(button))
                {
                    //ImGuiDragDropFlags drop_target_flags = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoPreviewTooltip;
                    if (const ui::Payload* payload = ui::accept_drag_drop_payload(button, "IMGUI_PAYLOAD_TYPE_COLOR_4F"))
                    {
                        UNUSED(payload);
                        //ImGui::SetMouseCursor(ImGuiMouseCursor_NotAllowed);
                        ui::set_tooltip(key(), button, "Cannot drop here!");
                    }
                }

                // Drop source
                static Colour col4 = { 1.0f, 0.0f, 0.2f, 1.0f };
                if (i == 0)
                    ui::color_button(key(), *n0, "drag me", col4);

            }
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsDragsAndSliders()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsDragsAndSliders(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Drag/Slider Flags").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Drag and Slider Flags");
        // Demonstrate using advanced flags for DragXXX and SliderXXX functions. Note that the flags are the same!
        static ImGuiSliderFlags flags = ImGuiSliderFlags_None;
        ui::checkbox_flags(key(), *n, "ImGuiSliderFlags_AlwaysClamp", flags, ImGuiSliderFlags_AlwaysClamp);
        { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "ImGuiSliderFlags_ClampOnInput", flags, ImGuiSliderFlags_ClampOnInput);
          HelpMarker(line, "Clamp value to min/max bounds when input manually with Ctrl+Click. By default Ctrl+Click allows going out of bounds."); }
        { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "ImGuiSliderFlags_ClampZeroRange", flags, ImGuiSliderFlags_ClampZeroRange);
          HelpMarker(line, "Clamp even if min==max==0.0f. Otherwise DragXXX functions don't clamp."); }
        { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "ImGuiSliderFlags_Logarithmic", flags, ImGuiSliderFlags_Logarithmic);
          HelpMarker(line, "Enable logarithmic editing (more precision for small values)."); }
        { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "ImGuiSliderFlags_NoRoundToFormat", flags, ImGuiSliderFlags_NoRoundToFormat);
          HelpMarker(line, "Disable rounding underlying value to match precision of the format string (e.g. %.3f values are rounded to those 3 digits)."); }
        { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "ImGuiSliderFlags_NoInput", flags, ImGuiSliderFlags_NoInput);
          HelpMarker(line, "Disable Ctrl+Click or Enter key allowing to input text directly into the widget."); }
        { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "ImGuiSliderFlags_NoSpeedTweaks", flags, ImGuiSliderFlags_NoSpeedTweaks);
          HelpMarker(line, "Disable keyboard modifiers altering tweak speed. Useful if you want to alter tweak speed yourself based on your own logic."); }
        { Widget line = ui::row(key(), *n); ui::checkbox_flags(key(), line, "ImGuiSliderFlags_WrapAround", flags, ImGuiSliderFlags_WrapAround);
          HelpMarker(line, "Enable wrapping around from max to min and from min to max (only supported by DragXXX() functions)"); }
        ui::checkbox_flags(key(), *n, "ImGuiSliderFlags_ColorMarkers", flags, ImGuiSliderFlags_ColorMarkers);

        // Drags
        static float drag_f = 0.5f;
        static float drag_f4[4];
        static int drag_i = 50;
        ui::textf(key(), *n, "Underlying float value: %f", drag_f);
        ui::drag_float(key(), *n, "DragFloat (0 -> 1)", drag_f, 0.005f, 0.0f, 1.0f); // "%.3f", flags);
        ui::drag_float(key(), *n, "DragFloat (0 -> +inf)", drag_f, 0.005f, 0.0f, FLT_MAX); // "%.3f", flags);
        ui::drag_float(key(), *n, "DragFloat (-inf -> 1)", drag_f, 0.005f, -FLT_MAX, 1.0f); // "%.3f", flags);
        ui::drag_float(key(), *n, "DragFloat (-inf -> +inf)", drag_f, 0.005f, -FLT_MAX, +FLT_MAX); // "%.3f", flags);
        //ImGui::DragFloat("DragFloat (0 -> 0)", &drag_f, 0.005f, 0.0f, 0.0f, "%.3f", flags);           // To test ClampZeroRange
        //ImGui::DragFloat("DragFloat (100 -> 100)", &drag_f, 0.005f, 100.0f, 100.0f, "%.3f", flags);
        ui::drag_int(key(), *n, "DragInt (0 -> 100)", drag_i, 0.5f, 0, 100); // "%d", flags);
        ui::drag_float4(key(), *n, "DragFloat4 (0 -> 1)", drag_f4, 0.005f, 0.0f, 1.0f); // "%.3f", flags); // Multi-component item, mostly here to document the effect of ImGuiSliderFlags_ColorMarkers.

        // Sliders
        static float slider_f = 0.5f;
        static float slider_f4[4];
        static int slider_i = 50;
        //const ImGuiSliderFlags flags_for_sliders = (flags & ~ImGuiSliderFlags_WrapAround);
        ui::textf(key(), *n, "Underlying float value: %f", slider_f);
        ui::slider_float(key(), *n, "SliderFloat (0 -> 1)", slider_f, 0.0f, 1.0f); // "%.3f", flags_for_sliders);
        ui::slider_int(key(), *n, "SliderInt (0 -> 100)", slider_i, 0, 100); // "%d", flags_for_sliders);
        ui::slider_float4(key(), *n, "SliderFloat4 (0 -> 1)", slider_f4, 0.0f, 1.0f); // "%.3f", flags); // Multi-component item, mostly here to document the effect of ImGuiSliderFlags_ColorMarkers.
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsFonts()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsFonts(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Fonts").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Fonts");
        ui::show_font_atlas(key(), *n); // ImGui::ShowFontAtlas(ImGui::GetIO().Fonts);
        // FIXME-NEWATLAS: Provide a demo to add/create a procedural font?
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsImages()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsImages(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Images").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Images");
        ui::text_wrapped(key(), *n,
            "Below we are displaying the font texture (which is the only texture we have access to in this demo). "
            "Use the 'ImTextureID' type as storage to pass pointers or identifier to your own texture data. "
            "Hover the texture for a zoomed view!");

        // Below we are displaying the font texture because it is the only texture we have access to inside the demo!
        // Read description about ImTextureID/ImTextureRef and FAQ for details about texture identifiers.
        // If you use one of the default imgui_impl_XXXX.cpp rendering backend, they all have comments at the top
        // of their respective source file to specify what they are using as texture identifier, for example:
        // - The imgui_impl_dx11.cpp renderer expect a 'ID3D11ShaderResourceView*' pointer.
        // - The imgui_impl_opengl3.cpp renderer expect a GLuint OpenGL texture identifier, etc.
        // So with the DirectX11 backend, you call ImGui::Image() with a 'ID3D11ShaderResourceView*' cast to ImTextureID.
        // - If you decided that ImTextureID = MyEngineTexture*, then you can pass your MyEngineTexture* pointers
        //   to ImGui::Image(), and gather width/height through your own functions, etc.
        // - You can use ShowMetricsWindow() to inspect the draw data that are being passed to your renderer,
        //   it will help you debug issues if you are confused about it.
        // - Consider using the lower-level ImDrawList::AddImage() API, via ImGui::GetWindowDrawList()->AddImage().
        // - Read https://github.com/ocornut/imgui/blob/master/docs/FAQ.md
        // - Read https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples

        // Grab the current texture identifier used by the font atlas.
        Image* my_tex_id = ui::font_atlas_texture(*n);
        float my_tex_w = my_tex_id ? (float)my_tex_id->d_size.x : 0.f;
        float my_tex_h = my_tex_id ? (float)my_tex_id->d_size.y : 0.f;
        ui::textf(key(), *n, "%.0fx%.0f", my_tex_w, my_tex_h);

        // Basic drawing
        ui::separator_text(key(), *n, "Image()/ImageWithBg() function");
        vec2 uv_min = vec2(0.0f, 0.0f); // Top-left
        vec2 uv_max = vec2(1.0f, 1.0f); // Lower-right
        //ImGui::PushStyleVar(ImGuiStyleVar_ImageBorderSize, IM_MAX(1.0f, ImGui::GetStyle().ImageBorderSize));
        ui::image(key(), *n, my_tex_id, vec2(my_tex_w, my_tex_h), uv_min, uv_max); // ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
        //ImGui::PopStyleVar();

        // Fancy widget
        ui::separator_text(key(), *n, "Interactive Image Viewer");
        //static ExampleImageViewerData image_viewer;
        //ImVec2 canvas_size(ImGui::GetContentRegionAvail().x, my_tex_h * 2.0f);
        //ExampleImageViewer_DrawOptions(&image_viewer);
        //ExampleImageViewer_DrawCanvas(&image_viewer, canvas_size, my_tex_id, (int)my_tex_w, (int)my_tex_h);

        IMGUI_DEMO_MARKER("Widgets/Images/Textured buttons");
        ui::separator_text(key(), *n, "Textured Buttons");
        ui::text_wrapped(key(), *n, "And now some textured buttons..");
        static int pressed_count = 0;
        Widget line = ui::row(key(), *n);
        for (int i = 0; i < 8; i++)
        {
            // UV coordinates are often (0.0f, 0.0f) and (1.0f, 1.0f) to display an entire textures.
            // Here are trying to display only a 32x32 pixels area of the texture, hence the UV computation.
            // Read about UV coordinates here: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples
            //ImGui::PushID(i);
            //if (i > 0)
            //    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(i - 1.0f, i - 1.0f));
            vec2 size = vec2(32.0f, 32.0f);                         // Size of the image we want to make visible
            vec2 uv0 = vec2(0.0f, 0.0f);                            // UV coordinates for lower-left
            vec2 uv1 = vec2(32.0f / my_tex_w, 32.0f / my_tex_h);    // UV coordinates for (32,32) in our texture
            //ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);             // Black background
            //ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);           // No tint
            if (ui::image_button(key(i), line, my_tex_id, size, uv0, uv1).activated())
                pressed_count += 1;
            //if (i > 0)
            //    ImGui::PopStyleVar();
            //ImGui::PopID();
            //ImGui::SameLine();
        }
        //ImGui::NewLine();
        ui::textf(key(), *n, "Pressed %d times.", pressed_count);
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsListBoxes()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsListBoxes(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "List Boxes").body)
    {
        IMGUI_DEMO_MARKER("Widgets/List Boxes");
        // BeginListBox() is essentially a thin wrapper to using BeginChild()/EndChild()
        // using the ImGuiChildFlags_FrameStyle flag for stylistic changes + displaying a label.
        // You may be tempted to simply use BeginChild() directly. However note that BeginChild() requires EndChild()
        // to always be called (inconsistent with BeginListBox()/EndListBox()).

        // Using the generic BeginListBox() API, you have full control over how to display the combo contents.
        // (your selection data could be an index, a pointer to the object, an id for the object, a flag intrusively
        // stored in the object itself, etc.)
        const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
        static int item_selected_idx = 0; // Here we store our selected data as an index.

        static bool item_highlight = false;
        int item_highlighted_idx = -1; // Here we store our highlighted data as an index.
        ui::checkbox(key(), *n, "Highlight hovered item in second listbox", item_highlight);

        Widget line = ui::row(key(), *n);
        if (Widget list = ui::begin_list_box(key(), line, "listbox 1"))
        {
            for (int i = 0; i < IM_COUNTOF(items); i++)
            {
                const bool is_selected = (item_selected_idx == i);
                Widget selectable = ui::selectable(key(), *list, items[i], is_selected);
                if (selectable.activated())
                    item_selected_idx = i;

                if (item_highlight && selectable.hovered())
                    item_highlighted_idx = i;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                //if (is_selected)
                //    ImGui::SetItemDefaultFocus();
            }
        }
        HelpMarker(line, "Here we are sharing selection state between both boxes.");

        // Custom size: use all width, 5 items tall
        ui::label(key(), *n, "Full-width:");
        if (Widget list = ui::begin_list_box(key(), *n, "##listbox 2")) // ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
        {
            for (int i = 0; i < IM_COUNTOF(items); i++)
            {
                const bool is_selected = (item_selected_idx == i);
                //ImGuiSelectableFlags flags = (item_highlighted_idx == i) ? ImGuiSelectableFlags_Highlight : 0;
                Widget selectable = ui::selectable(key(), *list, items[i], is_selected);
                selectable.set_state(HOVERED, item_highlighted_idx == i);
                if (selectable.activated())
                    item_selected_idx = i;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                //if (is_selected)
                //    ImGui::SetItemDefaultFocus();
            }
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsLiveEdit()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsLiveEdit(Widget parent, ImGuiDemoWindowData* demo_data)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Live Edit Flags").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Live Edit Flags");

        ui::text_wrapped(key(), *n, "Select whether to apply keyboard edits to backing variables _while_ typing.");

        ui::checkbox(key(), *n, "Override Live Edit Flags in Demo Window", demo_data->LiveEditOverride);
        if (!demo_data->LiveEditOverride)
            demo_data->LiveEditFlags = ui::get_item_flags();

        ui::begin_disabled(demo_data->LiveEditOverride == false);
        Widget indent = ui::indent(key(), *n); // ImGui::Indent();
        ui::checkbox_flags(key(), indent, "ImGuiItemFlags_LiveEditOnInputText", demo_data->LiveEditFlags, ImGuiItemFlags_LiveEditOnInputText);
        ui::checkbox_flags(key(), indent, "ImGuiItemFlags_LiveEditOnInputScalar", demo_data->LiveEditFlags, ImGuiItemFlags_LiveEditOnInputScalar);
        //ImGui::Unindent();
        ui::end_disabled();

        ui::label(key(), *n, "Try typing '123' and seeing effect on backing value:");
        static string str = "";
        ui::input_text(key(), *n, "str", str);
        ui::textf(key(), *n, "Backing value: \"%s\"", str.c_str());
        static int i = 0;
        ui::input_int(key(), *n, "int", i, 0);
        ui::textf(key(), *n, "Backing value: %d", i);
        static float f = 0.0f;
        ui::slider_float(key(), *n, "float", f, 0.0f, 100.0f);
        ui::textf(key(), *n, "Backing value: %f", f);
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsMixedValues()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsMixedValues(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Mixed Values").body)
    {
        // This is designed for advanced property editors which are generally reusable and data-driven.
        HelpMarker(*n, "Using ImGuiItemFlags_MixedValue.");

        static bool use_liveedit = false;
        static float items[3] = { 12.0f, 0.0f, 0.0f };
        float* item_ref = &items[0];
        ui::checkbox(key(), *n, "ImGuiItemFlags_LiveEditOnInput", use_liveedit);

        ui::separator_text(key(), *n, "Scalar/Text Widgets");
        const bool is_mixed = memcmp(&items[0], &items[1], sizeof(float)) != 0 || memcmp(&items[0], &items[2], sizeof(float)) != 0;

        // Demonstrate Drags, Sliders, Inputs
        ui::push_item_flag(ImGuiItemFlags_LiveEditOnInput, use_liveedit);
        ui::push_item_flag(ImGuiItemFlags_MixedValue, is_mixed);
        bool edited = false;
        edited |= ui::drag_float(key(), *n, "DragFloat", *item_ref);
        edited |= ui::slider_float(key(), *n, "SliderFloat", *item_ref, 0.0f, 100.0f);
        edited |= ui::input_float(key(), *n, "InputFloat", *item_ref, 1.0f);
        if (edited)
            for (float& item : items)
                if (&item != item_ref)
                    item = *item_ref;
        ui::pop_item_flag();

        ui::label(key(), *n, "Underlying data:");
        ui::input_float(key(), *n, "item 0 (ref)", items[0]);
        ui::input_float(key(), *n, "item 1", items[1]);
        ui::input_float(key(), *n, "item 2", items[2]);
        ui::pop_item_flag();

        // Demonstrate Checkbox(), RadioButton(), Combo(), ColorEdit4()
        ui::separator_text(key(), *n, "Others Widgets");
        ui::label(key(), *n, "(note: edits are not applied in this demo)"); // <-- Would need more state tracking.
        bool b_on = true, b_off = false;
        ui::checkbox(key(), *n, "Checkbox On", b_on);
        ui::checkbox(key(), *n, "Checkbox Off", b_off);
        ui::push_item_flag(ImGuiItemFlags_MixedValue, true);
        ui::checkbox(key(), *n, "Checkbox Mixed", b_off);
        Widget line = ui::row(key(), *n);
        ui::radio_button(key(), line, "RadioButton Mixed", true);
        //ImGui::SameLine();
        ui::radio_button(key(), line, "RadioButton Mixed##2", true); // Showing 2 radio buttons makes the example more clear
        int combo_idx = 0;
        ui::combo(key(), *n, "Combo", combo_idx, { "One", "Two", "Three" });
        float color[4] = { 0.5f, 0.5f, 0.5f, 0.5f };
        ui::color_edit4(key(), *n, "ColorEdit4", color);
        ui::pop_item_flag();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsMultiComponents()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsMultiComponents(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Multi-component Widgets").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Multi-component Widgets");
        static float vec4f[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
        static int vec4i[4] = { 1, 5, 100, 255 };

        static ImGuiSliderFlags flags = 0;
        ui::checkbox_flags(key(), *n, "ImGuiSliderFlags_ColorMarkers", flags, ImGuiSliderFlags_ColorMarkers); // Only passing this to Drag/Sliders

        ui::separator_text(key(), *n, "2-wide");
        ui::input_float2(key(), *n, "input float2", vec4f);
        ui::input_int2(key(), *n, "input int2", vec4i);
        ui::drag_float2(key(), *n, "drag float2", vec4f, 0.01f, 0.0f, 1.0f); // NULL, flags);
        ui::drag_int2(key(), *n, "drag int2", vec4i, 1, 0, 255); // NULL, flags);
        ui::slider_float2(key(), *n, "slider float2", vec4f, 0.0f, 1.0f); // NULL, flags);
        ui::slider_int2(key(), *n, "slider int2", vec4i, 0, 255); // NULL, flags);

        ui::separator_text(key(), *n, "3-wide");
        ui::input_float3(key(), *n, "input float3", vec4f);
        ui::input_int3(key(), *n, "input int3", vec4i);
        ui::drag_float3(key(), *n, "drag float3", vec4f, 0.01f, 0.0f, 1.0f); // NULL, flags);
        ui::drag_int3(key(), *n, "drag int3", vec4i, 1, 0, 255); // NULL, flags);
        ui::slider_float3(key(), *n, "slider float3", vec4f, 0.0f, 1.0f); // NULL, flags);
        ui::slider_int3(key(), *n, "slider int3", vec4i, 0, 255); // NULL, flags);

        ui::separator_text(key(), *n, "4-wide");
        ui::input_float4(key(), *n, "input float4", vec4f);
        ui::input_int4(key(), *n, "input int4", vec4i);
        ui::drag_float4(key(), *n, "drag float4", vec4f, 0.01f, 0.0f, 1.0f); // NULL, flags);
        ui::drag_int4(key(), *n, "drag int4", vec4i, 1, 0, 255); // NULL, flags);
        ui::slider_float4(key(), *n, "slider float4", vec4f, 0.0f, 1.0f); // NULL, flags);
        ui::slider_int4(key(), *n, "slider int4", vec4i, 0, 255); // NULL, flags);

        ui::separator_text(key(), *n, "Ranges");
        static float begin = 10, end = 90;
        static int begin_i = 100, end_i = 1000;
        ui::drag_float_range2(key(), *n, "range float", begin, end, 0.25f, 0.0f, 100.0f); // "Min: %.1f %%", "Max: %.1f %%", ImGuiSliderFlags_AlwaysClamp);
        ui::drag_int_range2(key(), *n, "range int", begin_i, end_i, 5, 0, 1000); // "Min: %d units", "Max: %d units");
        ui::drag_int_range2(key(), *n, "range int (no bounds)", begin_i, end_i, 5, 0, 0); // "Min: %d units", "Max: %d units");
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsPlotting()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsPlotting(Widget parent)
{
    // Plot/Graph widgets are not very good.
// Consider using a third-party library such as ImPlot: https://github.com/epezent/implot
// (see others https://github.com/ocornut/imgui/wiki/Useful-Extensions)
    if (Widget n = ui::tree_node_ex(key(), parent, "Plotting").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Plotting");
        ui::label(key(), *n, "Need better plotting and graphing? Consider using ImPlot:");
        ui::text_link(key(), *n, "https://github.com/epezent/implot");
        ui::separator(key(), *n);

        static bool animate = true;
        ui::checkbox(key(), *n, "Animate", animate);

        // Plot as lines and plot as histogram
        static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
        ui::plot_lines(key(), *n, "Frame Times", arr);
        ui::plot_histogram(key(), *n, "Histogram", arr, 0, NULL, 0.0f, 1.0f, vec2(0, 80.0f));
        //ImGui::SameLine(); HelpMarker("Consider using ImPlot instead!");

        // Fill an array of contiguous float values to plot
        // Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float
        // and the sizeof() of your structure in the "stride" parameter.
        static float values[90] = {};
        static int values_offset = 0;
        static double refresh_time = 0.0;
        if (!animate || refresh_time == 0.0)
            refresh_time = ui::io().Time;
        while (refresh_time < ui::io().Time) // Create data at fixed 60 Hz rate for the demo
        {
            static float phase = 0.0f;
            values[values_offset] = cosf(phase);
            values_offset = (values_offset + 1) % IM_COUNTOF(values);
            phase += 0.10f * values_offset;
            refresh_time += 1.0f / 60.0f;
        }

        // Plots can display overlay texts
        // (in this example, we will display an average value)
        {
            float average = 0.0f;
            for (int i = 0; i < IM_COUNTOF(values); i++)
                average += values[i];
            average /= (float)IM_COUNTOF(values);
            char overlay[32];
            sprintf(overlay, "avg %f", average);
            ui::plot_lines(key(), *n, "Lines", values, values_offset, overlay, -1.0f, 1.0f, vec2(0, 80.0f));
        }

        // Use functions to generate output
        // FIXME: This is actually VERY awkward because current plot API only pass in indices.
        // We probably want an API passing floats and user provide sample rate/count.
        struct Funcs
        {
            static float Sin(void*, int i) { return sinf(i * 0.1f); }
            static float Saw(void*, int i) { return (i & 1) ? 1.0f : -1.0f; }
        };
        static int func_type = 0, display_count = 70;
        ui::separator_text(key(), *n, "Functions");
        Widget line = ui::row(key(), *n);
        //ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ui::combo(key(), line, "func", func_type, { "Sin", "Saw" });
        //ImGui::SameLine();
        ui::slider_int(key(), line, "Sample count", display_count, 1, 400);
        float (*func)(void*, int) = (func_type == 0) ? Funcs::Sin : Funcs::Saw;
        ui::plot_lines(key(), *n, "Lines##2", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, vec2(0, 80));
        ui::plot_histogram(key(), *n, "Histogram##2", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, vec2(0, 80));
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsProgressBars()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsProgressBars(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Progress Bars").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Progress Bars");
        // Animate a simple progress bar
        static float progress_accum = 0.0f, progress_dir = 1.0f;
        progress_accum += progress_dir * 0.4f * ui::io().DeltaTime;
        if (progress_accum >= +1.1f) { progress_accum = +1.1f; progress_dir *= -1.0f; }
        if (progress_accum <= -0.1f) { progress_accum = -0.1f; progress_dir *= -1.0f; }

        const float progress = IM_CLAMP(progress_accum, 0.0f, 1.0f);

        // Typically we would use ImVec2(-1.0f,0.0f) or ImVec2(-FLT_MIN,0.0f) to use all available width,
        // or ImVec2(width,0.0f) for a specified width. ImVec2(0.0f,0.0f) uses ItemWidth.
        Widget line0 = ui::row(key(), *n);
        ui::progress_bar(key(), line0, progress, vec2(0.0f, 0.0f));
        //ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
        ui::label(key(), line0, "Progress Bar");

        char buf[32];
        sprintf(buf, "%d/%d", (int)(progress * 1753), 1753);
        ui::progress_bar(key(), *n, progress, vec2(0.0f, 0.0f), buf);

        // Pass an animated negative value, e.g. -1.0f * (float)ImGui::GetTime() is the recommended value.
        // Adjust the factor if you want to adjust the animation speed.
        Widget line1 = ui::row(key(), *n);
        ui::progress_bar(key(), line1, -1.0f * (float)ui::io().Time, vec2(0.0f, 0.0f), "Searching..");
        //ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
        ui::label(key(), line1, "Indeterminate");
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsQueryingStatuses()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsQueryingStatuses(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Querying Item Status (Edited/Active/Hovered etc.)").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Querying Item Status (Edited,Active,Hovered etc.)");
        // Select an item type
        const char* item_names[] =
        {
            "Text", "Button", "Button (w/ repeat)", "Checkbox", "SliderFloat", "InputText", "InputTextMultiline", "InputFloat",
            "InputFloat3", "ColorEdit4", "Selectable", "MenuItem", "TreeNode", "TreeNode (w/ double-click)", "Combo", "ListBox"
        };
        static int item_type = 4;
        static bool item_disabled = false;
        static bool item_mixedvalue = false;
        static bool liveedit_flags_override = false;
        static ImGuiItemFlags liveedit_flags = 0;
        { Widget line = ui::row(key(), *n); ui::combo(key(), line, "Item Type", item_type, item_names); // IM_COUNTOF(item_names));
          //ImGui::SameLine();
          HelpMarker(line, "Testing how various types of items are interacting with the IsItemXXX functions. Note that the bool return value of most ImGui function is generally equivalent to calling ImGui::IsItemHovered()."); }
        ui::checkbox(key(), *n, "Item Disabled", item_disabled);
        ui::checkbox(key(), *n, "Item MixedValue", item_mixedvalue);
        Widget line_liveedit = ui::row(key(), *n);
        ui::checkbox(key(), line_liveedit, "Override LiveEdit:", liveedit_flags_override);
        //ImGui::SameLine();
        if (!liveedit_flags_override)
            liveedit_flags = ui::get_item_flags();
        ui::begin_disabled(liveedit_flags_override == false);
        ui::checkbox_flags(key(), line_liveedit, "_LiveEditOnInput", liveedit_flags, ImGuiItemFlags_LiveEditOnInput);
        //ImGui::SameLine();
        ui::checkbox_flags(key(), line_liveedit, "_LiveEditOnInputText", liveedit_flags, ImGuiItemFlags_LiveEditOnInputText);
        //ImGui::SameLine();
        ui::checkbox_flags(key(), line_liveedit, "_LiveEditOnInputScalar", liveedit_flags, ImGuiItemFlags_LiveEditOnInputScalar);
        ui::end_disabled();
        if (liveedit_flags_override)
        {
            ui::push_item_flag(ImGuiItemFlags_LiveEditOnInputText, (liveedit_flags & ImGuiItemFlags_LiveEditOnInputText) != 0);
            ui::push_item_flag(ImGuiItemFlags_LiveEditOnInputScalar, (liveedit_flags & ImGuiItemFlags_LiveEditOnInputScalar) != 0);
        }

        // Submit selected items so we can query their status in the code following it.
        // In two.ui, the items are queried through the widget returned by the call declaring them
        bool ret = false;
        Widget item = nullptr;
        static bool b = false;
        static float col4f[4] = { 1.0f, 0.5, 0.0f, 1.0f };
        static string str = "";
        if (item_disabled)
            ui::begin_disabled(true);
        if (item_mixedvalue)
            ui::push_item_flag(ImGuiItemFlags_MixedValue, true);
        Widget items = ui::stack(key(), *n);
        if (item_type == 0) { item = ui::label(key(), items, "ITEM: Text"); }                                                // Testing text items with no identifier/interaction
        if (item_type == 1) { item = ui::button(key(), items, "ITEM: Button"); ret = item->activated(); }                    // Testing button
        if (item_type == 2) { ui::push_item_flag(ImGuiItemFlags_ButtonRepeat, true); item = ui::button(key(), items, "ITEM: Button"); ret = item->activated(); ui::pop_item_flag(); } // Testing button (with repeater)
        if (item_type == 3) { ret = ui::checkbox(key(), items, "ITEM: Checkbox", b); }                                        // Testing checkbox
        if (item_type == 4) { ret = ui::slider_float(key(), items, "ITEM: SliderFloat", col4f[0], 0.0f, 1.0f); }             // Testing basic item
        if (item_type == 5) { ret = ui::input_text(key(), items, "ITEM: InputText", str); }                                  // Testing input text (which handles tabbing)
        if (item_type == 6) { ret = ui::input_text_multiline(key(), items, "ITEM: InputTextMultiline", str); }               // Testing input text (which uses a child window)
        if (item_type == 7) { ret = ui::input_float(key(), items, "ITEM: InputFloat", col4f[0], 1.0f); }                     // Testing +/- buttons on scalar input
        if (item_type == 8) { ret = ui::input_float3(key(), items, "ITEM: InputFloat3", col4f); }                            // Testing multi-component items (IsItemXXX flags are reported merged)
        if (item_type == 9) { ret = ui::color_edit4(key(), items, "ITEM: ColorEdit4", col4f); }                              // Testing multi-component items (IsItemXXX flags are reported merged)
        if (item_type == 10) { item = ui::selectable(key(), items, "ITEM: Selectable", false); ret = item->activated(); }    // Testing selectable item
        if (item_type == 11) { ret = ui::menu_item(key(), items, "ITEM: MenuItem"); }                                        // Testing menu item (they use ImGuiButtonFlags_PressedOnRelease button policy)
        if (item_type == 12) { TreeNode node = ui::tree_node_ex(key(), items, "ITEM: TreeNode"); item = node.header; ret = node.body != nullptr; } // Testing tree node
        if (item_type == 13) { TreeNode node = ui::tree_node_ex(key(), items, "ITEM: TreeNode w/ ImGuiTreeNodeFlags_OpenOnDoubleClick", ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_NoTreePushOnOpen); item = node.header; ret = node.body != nullptr; } // Testing tree node with ImGuiButtonFlags_PressedOnDoubleClick button policy.
        if (item_type == 14) { const char* combo_items[] = { "Apple", "Banana", "Cherry", "Kiwi" }; static int current = 1; ret = ui::combo(key(), items, "ITEM: Combo", current, combo_items); }
        if (item_type == 15) { const char* list_items[] = { "Apple", "Banana", "Cherry", "Kiwi" }; static int current = 1; ret = ui::list_box(key(), items, "ITEM: ListBox", current, list_items, IM_COUNTOF(list_items)); }
        if (!item)
            item = items.child(0);

        bool hovered_delay_none = ui::is_item_hovered(*item);
        bool hovered_delay_stationary = ui::is_item_hovered(*item, ImGuiHoveredFlags_Stationary);
        bool hovered_delay_short = ui::is_item_hovered(*item, ImGuiHoveredFlags_DelayShort);
        bool hovered_delay_normal = ui::is_item_hovered(*item, ImGuiHoveredFlags_DelayNormal);
        bool hovered_delay_tooltip = ui::is_item_hovered(*item, ImGuiHoveredFlags_ForTooltip); // = Normal + Stationary

        // Display the values of IsItemHovered() and other common item state functions.
        // Note that the ImGuiHoveredFlags_XXX flags can be combined.
        // Because BulletText is an item itself and that would affect the output of IsItemXXX functions,
        // we query every state in a single call to avoid storing them and to simplify the code.
        char status[2048];
        snprintf(status, sizeof(status),
            "Return value = %d\n"
            "IsItemFocused() = %d\n"
            "IsItemHovered() = %d\n"
            "IsItemHovered(_AllowWhenBlockedByPopup) = %d\n"
            "IsItemHovered(_AllowWhenBlockedByActiveItem) = %d\n"
            "IsItemHovered(_AllowWhenOverlappedByItem) = %d\n"
            "IsItemHovered(_AllowWhenOverlappedByWindow) = %d\n"
            "IsItemHovered(_AllowWhenDisabled) = %d\n"
            "IsItemHovered(_RectOnly) = %d\n"
            "IsItemActive() = %d\n"
            "IsItemEdited() = %d\n"
            "IsItemActivated() = %d\n"
            "IsItemDeactivated() = %d\n"
            "IsItemDeactivatedAfterEdit() = %d\n"
            "IsItemVisible() = %d\n"
            "IsItemClicked() = %d\n"
            "IsItemToggledOpen() = %d\n"
            "GetItemRectMin() = (%.1f, %.1f)\n"
            "GetItemRectMax() = (%.1f, %.1f)\n"
            "GetItemRectSize() = (%.1f, %.1f)",
            ret,
            ui::is_item_focused(*item),
            ui::is_item_hovered(*item),
            ui::is_item_hovered(*item, ImGuiHoveredFlags_AllowWhenBlockedByPopup),
            ui::is_item_hovered(*item, ImGuiHoveredFlags_AllowWhenBlockedByActiveItem),
            ui::is_item_hovered(*item, ImGuiHoveredFlags_AllowWhenOverlappedByItem),
            ui::is_item_hovered(*item, ImGuiHoveredFlags_AllowWhenOverlappedByWindow),
            ui::is_item_hovered(*item, ImGuiHoveredFlags_AllowWhenDisabled),
            ui::is_item_hovered(*item, ImGuiHoveredFlags_RectOnly),
            ui::is_item_active(*item),
            ret, // ImGui::IsItemEdited(),
            ui::is_item_clicked(*item), // ImGui::IsItemActivated(),
            false, // ImGui::IsItemDeactivated(),
            false, // ImGui::IsItemDeactivatedAfterEdit(),
            true, // ImGui::IsItemVisible(),
            ui::is_item_clicked(*item),
            false, // ImGui::IsItemToggledOpen(),
            ui::get_item_rect_min(*item).x, ui::get_item_rect_min(*item).y,
            ui::get_item_rect_max(*item).x, ui::get_item_rect_max(*item).y,
            ui::get_item_rect_size(*item).x, ui::get_item_rect_size(*item).y
        );
        ui::bullet(key(), *n, status);
        ui::bullet(key(), *n, ui::format(
            "with Hovering Delay or Stationary test:\n"
            "IsItemHovered() = %d\n"
            "IsItemHovered(_Stationary) = %d\n"
            "IsItemHovered(_DelayShort) = %d\n"
            "IsItemHovered(_DelayNormal) = %d\n"
            "IsItemHovered(_Tooltip) = %d",
            hovered_delay_none, hovered_delay_stationary, hovered_delay_short, hovered_delay_normal, hovered_delay_tooltip));

        if (liveedit_flags_override)
        {
            ui::pop_item_flag();
            ui::pop_item_flag();
        }
        if (item_mixedvalue)
            ui::pop_item_flag();
        if (item_disabled)
            ui::end_disabled();

        static string buf = "";
        Widget line = ui::row(key(), *n);
        ui::input_text(key(), line, "unused", buf); // ImGuiInputTextFlags_ReadOnly);
        //ImGui::SameLine();
        HelpMarker(line, "This widget is only here to be able to tab-out of the widgets above and see e.g. Deactivated() status.");
    }

    if (Widget n = ui::tree_node_ex(key(), parent, "Querying Window Status (Focused/Hovered etc.)").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Querying Window Status (Focused,Hovered etc.)");
        static bool embed_all_inside_a_child_window = false;
        ui::checkbox(key(), *n, "Embed everything inside a child window for testing _RootWindow flag.", embed_all_inside_a_child_window);
        Widget body = n;
        if (embed_all_inside_a_child_window)
            body = ui::begin_child(key(), *n, vec2(0, 13.f * 20.0f), true); // ImGuiChildFlags_Borders

        // In two.ui, the window status is queried through the widgets of the window
        Widget window = ui::get_current_window(*body);

        // Testing IsWindowFocused() function with its various flags.
        ui::bullet(key(), *body, ui::format(
            "IsWindowFocused() = %d\n"
            "IsWindowFocused(_ChildWindows) = %d\n"
            "IsWindowFocused(_ChildWindows|_NoPopupHierarchy) = %d\n"
            "IsWindowFocused(_ChildWindows|_RootWindow) = %d\n"
            "IsWindowFocused(_ChildWindows|_RootWindow|_NoPopupHierarchy) = %d\n"
            "IsWindowFocused(_RootWindow) = %d\n"
            "IsWindowFocused(_RootWindow|_NoPopupHierarchy) = %d\n"
            "IsWindowFocused(_AnyWindow) = %d\n",
            ui::is_window_focused(window),
            ui::is_window_focused(window, ImGuiFocusedFlags_ChildWindows),
            ui::is_window_focused(window, ImGuiFocusedFlags_ChildWindows | ImGuiFocusedFlags_NoPopupHierarchy),
            ui::is_window_focused(window, ImGuiFocusedFlags_ChildWindows | ImGuiFocusedFlags_RootWindow),
            ui::is_window_focused(window, ImGuiFocusedFlags_ChildWindows | ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_NoPopupHierarchy),
            ui::is_window_focused(window, ImGuiFocusedFlags_RootWindow),
            ui::is_window_focused(window, ImGuiFocusedFlags_RootWindow | ImGuiFocusedFlags_NoPopupHierarchy),
            ui::is_window_focused(window, ImGuiFocusedFlags_AnyWindow)));

        // Testing IsWindowHovered() function with its various flags.
        ui::bullet(key(), *body, ui::format(
            "IsWindowHovered() = %d\n"
            "IsWindowHovered(_AllowWhenBlockedByPopup) = %d\n"
            "IsWindowHovered(_AllowWhenBlockedByActiveItem) = %d\n"
            "IsWindowHovered(_ChildWindows) = %d\n"
            "IsWindowHovered(_ChildWindows|_NoPopupHierarchy) = %d\n"
            "IsWindowHovered(_ChildWindows|_RootWindow) = %d\n"
            "IsWindowHovered(_ChildWindows|_RootWindow|_NoPopupHierarchy) = %d\n"
            "IsWindowHovered(_RootWindow) = %d\n"
            "IsWindowHovered(_RootWindow|_NoPopupHierarchy) = %d\n"
            "IsWindowHovered(_ChildWindows|_AllowWhenBlockedByPopup) = %d\n"
            "IsWindowHovered(_AnyWindow) = %d\n"
            "IsWindowHovered(_Stationary) = %d\n",
            ui::is_window_hovered(window),
            ui::is_window_hovered(window, ImGuiHoveredFlags_AllowWhenBlockedByPopup),
            ui::is_window_hovered(window, ImGuiHoveredFlags_AllowWhenBlockedByActiveItem),
            ui::is_window_hovered(window, ImGuiHoveredFlags_ChildWindows),
            ui::is_window_hovered(window, ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_NoPopupHierarchy),
            ui::is_window_hovered(window, ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_RootWindow),
            ui::is_window_hovered(window, ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_NoPopupHierarchy),
            ui::is_window_hovered(window, ImGuiHoveredFlags_RootWindow),
            ui::is_window_hovered(window, ImGuiHoveredFlags_RootWindow | ImGuiHoveredFlags_NoPopupHierarchy),
            ui::is_window_hovered(window, ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_AllowWhenBlockedByPopup),
            ui::is_window_hovered(window, ImGuiHoveredFlags_AnyWindow),
            ui::is_window_hovered(window, ImGuiHoveredFlags_Stationary)));

        if (Widget child = ui::begin_child(key(), *body, vec2(0, 50), true)) // ImGuiChildFlags_Borders
            ui::label(key(), *child, "This is another child window for testing the _ChildWindows flag.");

        // Calling IsItemHovered() after begin returns the hovered status of the title bar.
        // This is useful in particular if you want to create a context menu associated to the title bar of a window.
        static bool test_window = false;
        ui::checkbox(key(), *n, "Hovered/Active tests after Begin() for title bar testing", test_window);
        if (test_window)
        {
            if (auto test = ui::begin(key(), n->ui(), "Title bar Hovered/Active tests", &test_window))
            {
                if (Widget popup = ui::begin_popup_context_item(key(), *test->header)) // <-- This is using IsItemHovered()
                {
                    if (ui::menu_item(key(), *popup, "Close")) { test_window = false; }
                }
                ui::textf(key(), *test->body,
                    "IsItemHovered() after begin = %d (== is title bar hovered)\n"
                    "IsItemActive() after begin = %d (== is window being clicked/moved)\n",
                    ui::is_item_hovered(*test->header), ui::is_item_active(*test->header));
            }
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsSelectables()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsSelectables(Widget parent)
{
    //ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (Widget n = ui::tree_node_ex(key(), parent, "Selectables").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Selectables");
        // Selectable() has 2 overloads:
        // - The one taking "bool selected" as a read-only selection information.
        //   When Selectable() has been clicked it returns true and you can alter selection state accordingly.
        // - The one taking "bool* p_selected" as a read-write selection information (convenient in some cases)
        // The earlier is more flexible, as in real application your selection may be stored in many different ways
        // and not necessarily inside a bool value (e.g. in flags within objects, as an external list, etc).
        IMGUI_DEMO_MARKER("Widgets/Selectables/Basic");
        if (Widget n0 = ui::tree_node_ex(key(), *n, "Basic").body)
        {
            static bool selection[5] = { false, true, false, false };
            ui::selectable(key(), *n0, "1. I am selectable", &selection[0]);
            ui::selectable(key(), *n0, "2. I am selectable", &selection[1]);
            ui::selectable(key(), *n0, "3. I am selectable", &selection[2]);
            Widget double_clickable = ui::selectable(key(), *n0, "4. I am double clickable", selection[3] != 0); // ImGuiSelectableFlags_AllowDoubleClick
            if (double_clickable.activated())
                if (ui::is_mouse_double_clicked(double_clickable))
                    selection[3] = !selection[3];
        }

        IMGUI_DEMO_MARKER("Widgets/Selectables/Rendering more items on the same line");
        if (Widget n0 = ui::tree_node_ex(key(), *n, "Multiple items on the same line").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Selectables/Multiple items on the same line");
            // - Using SetNextItemAllowOverlap()
            // - Using the Selectable() override that takes "bool* p_selected" parameter, the bool value is toggled automatically.
            {
                static bool selected[3] = {};
                { Widget line = ui::row(key(), *n0); /*ImGui::SetNextItemAllowOverlap();*/ ui::selectable(key(), line, "main.c", &selected[0]); /*ImGui::SameLine();*/ ui::small_button(key(), line, "Link 1"); }
                { Widget line = ui::row(key(), *n0); /*ImGui::SetNextItemAllowOverlap();*/ ui::selectable(key(), line, "hello.cpp", &selected[1]); /*ImGui::SameLine();*/ ui::small_button(key(), line, "Link 2"); }
                { Widget line = ui::row(key(), *n0); /*ImGui::SetNextItemAllowOverlap();*/ ui::selectable(key(), line, "hello.h", &selected[2]); /*ImGui::SameLine();*/ ui::small_button(key(), line, "Link 3"); }
            }

            // (2)
            // - Using ImGuiSelectableFlags_AllowOverlap is a shortcut for calling SetNextItemAllowOverlap()
            // - No visible label, display contents inside the selectable bounds.
            // - We don't maintain actual selection in this example to keep things simple.
            ui::spacing(key(), *n0);
            {
                static bool checked[5] = {};
                static int selected_n = 0;
                //const float color_marker_w = ImGui::CalcTextSize("x").x;
                for (int i = 0; i < 5; i++)
                {
                    //ImGui::PushID(i);
                    //ImGui::AlignTextToFramePadding();
                    Widget selectable = ui::selectable(key(), *n0, "", selected_n == i); // ImGuiSelectableFlags_AllowOverlap
                    if (selectable.activated())
                        selected_n = i;
                    //ImGui::SameLine(0, 0);
                    Widget line = ui::row(key(), selectable);
                    ui::checkbox(key(), line, checked[i]);
                    //ImGui::SameLine();
                    Colour color((i & 1) ? 1.0f : 0.2f, (i & 2) ? 1.0f : 0.2f, 0.2f, 1.0f);
                    ui::color_button(key(), line, "##color", color); // ImGuiColorEditFlags_NoTooltip, ImVec2(color_marker_w, 0));
                    //ImGui::SameLine();
                    ui::label(key(), line, "Some label");
                    //ImGui::PopID();
                }
            }
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "In Tables").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Selectables/In Tables");
            static bool selected[10] = {};

            {
                ui::TableLayout table = ui::begin_table(key(), *n0, 3); // ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders
                for (int i = 0; i < 10; i++)
                {
                    char label[32];
                    sprintf(label, "Item %d", i);
                    ui::selectable(key(), table.next_column(), label, &selected[i]); // FIXME-TABLE: Selection overlap
                }
            }
            ui::spacing(key(), *n0);
            {
                ui::TableLayout table = ui::begin_table(key(), *n0, 3); // ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders
                for (int i = 0; i < 10; i++)
                {
                    char label[32];
                    sprintf(label, "Item %d", i);
                    table.next_row();
                    ui::selectable(key(), table.next_column(), label, &selected[i]); // ImGuiSelectableFlags_SpanAllColumns
                    ui::label(key(), table.next_column(), "Some other contents");
                    ui::label(key(), table.next_column(), "123456");
                }
            }
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Grid").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Selectables/Grid");
            static char selected[4][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0, 0, 1 } };

            // Add in a bit of silly fun...
            const float time = (float)ui::io().Time;
            const bool winning_state = memchr(selected, 0, sizeof(selected)) == NULL; // If all cells are selected...
            if (winning_state)
                ui::push_style_var(ImGuiStyleVar_SelectableTextAlign, vec2(0.5f + 0.5f * cosf(time * 2.0f), 0.5f + 0.5f * sinf(time * 3.0f)));

            //const float size = ImGui::CalcTextSize("Sailor").x;
            for (int y = 0; y < 4; y++)
            {
                Widget line = ui::row(key(), *n0);
                for (int x = 0; x < 4; x++)
                {
                    //if (x > 0)
                    //    ImGui::SameLine();
                    //ImGui::PushID(y * 4 + x);
                    if (ui::selectable(key(), line, "Sailor", selected[y][x] != 0).activated()) // 0, ImVec2(size, size)))
                    {
                        // Toggle clicked cell + toggle neighbors
                        selected[y][x] ^= 1;
                        if (x > 0) { selected[y][x - 1] ^= 1; }
                        if (x < 3) { selected[y][x + 1] ^= 1; }
                        if (y > 0) { selected[y - 1][x] ^= 1; }
                        if (y < 3) { selected[y + 1][x] ^= 1; }
                    }
                    //ImGui::PopID();
                }
            }

            if (winning_state)
                ui::pop_style_var();
        }
        if (Widget n0 = ui::tree_node_ex(key(), *n, "Alignment").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Selectables/Alignment");
            HelpMarker(*n0,
                "By default, Selectables uses style.SelectableTextAlign but it can be overridden on a per-item "
                "basis using PushStyleVar(). You'll probably want to always keep your default situation to "
                "left-align otherwise it becomes difficult to layout multiple items on a same line");

            static bool selected[3 * 3] = { true, false, true, false, true, false, true, false, true };
            //const float size = ImGui::CalcTextSize("(1.0,1.0)").x;
            for (int y = 0; y < 3; y++)
            {
                Widget line = ui::row(key(), *n0);
                for (int x = 0; x < 3; x++)
                {
                    vec2 alignment = vec2((float)x / 2.0f, (float)y / 2.0f);
                    char name[32];
                    sprintf(name, "(%.1f,%.1f)", alignment.x, alignment.y);
                    //if (x > 0) ImGui::SameLine();
                    ui::push_style_var(ImGuiStyleVar_SelectableTextAlign, alignment);
                    ui::selectable(key(), line, name, &selected[3 * y + x]); // ImGuiSelectableFlags_None, ImVec2(size, size));
                    ui::pop_style_var();
                }
            }
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsSelectionAndMultiSelect()
//-----------------------------------------------------------------------------
// Multi-selection demos
// Also read: https://github.com/ocornut/imgui/wiki/Multi-Select
//-----------------------------------------------------------------------------

static const char* ExampleNames[] =
{
    "Artichoke", "Arugula", "Asparagus", "Avocado", "Bamboo Shoots", "Bean Sprouts", "Beans", "Beet", "Belgian Endive", "Bell Pepper",
    "Bitter Gourd", "Bok Choy", "Broccoli", "Brussels Sprouts", "Burdock Root", "Cabbage", "Calabash", "Capers", "Carrot", "Cassava",
    "Cauliflower", "Celery", "Celery Root", "Celcuce", "Chayote", "Chinese Broccoli", "Corn", "Cucumber"
};

// The multi-select API (BeginMultiSelect(), ImGuiSelectionBasicStorage) has no equivalent in two.ui yet
#if 0
// Extra functions to add deletion support to ImGuiSelectionBasicStorage
struct ExampleSelectionWithDeletion : ImGuiSelectionBasicStorage
{
    // Find which item should be Focused after deletion.
    // Call _before_ item submission. Return an index in the before-deletion item list, your item loop should call SetKeyboardFocusHere() on it.
    // The subsequent ApplyDeletionPostLoop() code will use it to apply Selection.
    // - We cannot provide this logic in core Dear ImGui because we don't have access to selection data.
    // - We don't actually manipulate the ImVector<> here, only in ApplyDeletionPostLoop(), but using similar API for consistency and flexibility.
    // - Important: Deletion only works if the underlying ImGuiID for your items are stable: aka not depend on their index, but on e.g. item id/ptr.
    // FIXME-MULTISELECT: Doesn't take account of the possibility focus target will be moved during deletion. Need refocus or scroll offset.
    int ApplyDeletionPreLoop(ImGuiMultiSelectIO* ms_io, int items_count)
    {
        if (Size == 0)
            return -1;

        // If focused item is not selected...
        const int focused_idx = (int)ms_io->NavIdItem;  // Index of currently focused item
        if (ms_io->NavIdSelected == false)  // This is merely a shortcut, == Contains(adapter->IndexToStorage(items, focused_idx))
        {
            ms_io->RangeSrcReset = true;    // Request to recover RangeSrc from NavId next frame. Would be ok to reset even when NavIdSelected==true, but it would take an extra frame to recover RangeSrc when deleting a selected item.
            return focused_idx;             // Request to focus same item after deletion.
        }

        // If focused item is selected: land on first unselected item after focused item.
        for (int idx = focused_idx + 1; idx < items_count; idx++)
            if (!Contains(GetStorageIdFromIndex(idx)))
                return idx;

        // If focused item is selected: otherwise return last unselected item before focused item.
        for (int idx = IM_MIN(focused_idx, items_count) - 1; idx >= 0; idx--)
            if (!Contains(GetStorageIdFromIndex(idx)))
                return idx;

        return -1;
    }

    // Rewrite item list (delete items) + update selection.
    // - Call after EndMultiSelect()
    // - We cannot provide this logic in core Dear ImGui because we don't have access to your items, nor to selection data.
    template<typename ITEM_TYPE>
    void ApplyDeletionPostLoop(ImGuiMultiSelectIO* ms_io, ImVector<ITEM_TYPE>& items, int item_curr_idx_to_select)
    {
        // Rewrite item list (delete items) + convert old selection index (before deletion) to new selection index (after selection).
        // If NavId was not part of selection, we will stay on same item.
        ImVector<ITEM_TYPE> new_items;
        new_items.reserve(items.Size - Size);
        int item_next_idx_to_select = -1;
        for (int idx = 0; idx < items.Size; idx++)
        {
            if (!Contains(GetStorageIdFromIndex(idx)))
                new_items.push_back(items[idx]);
            if (item_curr_idx_to_select == idx)
                item_next_idx_to_select = new_items.Size - 1;
        }
        items.swap(new_items);

        // Update selection
        Clear();
        if (item_next_idx_to_select != -1 && ms_io->NavIdSelected)
            SetItemSelected(GetStorageIdFromIndex(item_next_idx_to_select), true);
    }
};

// Example: Implement dual list box storage and interface
struct ExampleDualListBox
{
    ImVector<ImGuiID>           Items[2];               // ID is index into ExampleName[]
    ImGuiSelectionBasicStorage  Selections[2];          // Store ExampleItemId into selection
    bool                        OptKeepSorted = true;

    void MoveAll(int src, int dst)
    {
        IM_ASSERT((src == 0 && dst == 1) || (src == 1 && dst == 0));
        for (ImGuiID item_id : Items[src])
            Items[dst].push_back(item_id);
        Items[src].clear();
        SortItems(dst);
        Selections[src].Swap(Selections[dst]);
        Selections[src].Clear();
    }
    void MoveSelected(int src, int dst)
    {
        for (int src_n = 0; src_n < Items[src].Size; src_n++)
        {
            ImGuiID item_id = Items[src][src_n];
            if (!Selections[src].Contains(item_id))
                continue;
            Items[src].erase(&Items[src][src_n]); // FIXME-OPT: Could be implemented more optimally (rebuild src items and swap)
            Items[dst].push_back(item_id);
            src_n--;
        }
        if (OptKeepSorted)
            SortItems(dst);
        Selections[src].Swap(Selections[dst]);
        Selections[src].Clear();
    }
    void ApplySelectionRequests(ImGuiMultiSelectIO* ms_io, int side)
    {
        // In this example we store item id in selection (instead of item index)
        Selections[side].UserData = Items[side].Data;
        Selections[side].AdapterIndexToStorageId = [](ImGuiSelectionBasicStorage* self, int idx) { ImGuiID* items = (ImGuiID*)self->UserData; return items[idx]; };
        Selections[side].ApplyRequests(ms_io);
    }
    static int IMGUI_CDECL CompareItemsByValue(const void* lhs, const void* rhs)
    {
        const int* a = (const int*)lhs;
        const int* b = (const int*)rhs;
        return *a - *b;
    }
    void SortItems(int n)
    {
        qsort(Items[n].Data, (size_t)Items[n].Size, sizeof(Items[n][0]), CompareItemsByValue);
    }
    void Show()
    {
        //if (ImGui::Checkbox("Sorted", &OptKeepSorted) && OptKeepSorted) { SortItems(0); SortItems(1); }
        if (ImGui::BeginTable("split", 3, ImGuiTableFlags_None))
        {
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch);    // Left side
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);      // Buttons
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch);    // Right side
            ImGui::TableNextRow();

            int request_move_selected = -1;
            int request_move_all = -1;
            float child_height_0 = 0.0f;
            for (int side = 0; side < 2; side++)
            {
                // FIXME-MULTISELECT: Dual List Box: Add context menus
                // FIXME-NAV: Using ImGuiWindowFlags_NavFlattened exhibit many issues.
                ImVector<ImGuiID>& items = Items[side];
                ImGuiSelectionBasicStorage& selection = Selections[side];

                ImGui::TableSetColumnIndex((side == 0) ? 0 : 2);
                ImGui::Text("%s (%d)", (side == 0) ? "Available" : "Basket", items.Size);

                // Submit scrolling range to avoid glitches on moving/deletion
                const float items_height = ImGui::GetTextLineHeightWithSpacing();
                ImGui::SetNextWindowContentSize(ImVec2(0.0f, items.Size * items_height));

                bool child_visible;
                if (side == 0)
                {
                    // Left child is resizable
                    ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, ImGui::GetFrameHeightWithSpacing() * 4), ImVec2(FLT_MAX, FLT_MAX));
                    child_visible = ImGui::BeginChild("0", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY);
                    child_height_0 = ImGui::GetWindowSize().y;
                }
                else
                {
                    // Right child use same height as left one
                    child_visible = ImGui::BeginChild("1", ImVec2(-FLT_MIN, child_height_0), ImGuiChildFlags_FrameStyle);
                }
                if (child_visible)
                {
                    ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_BoxSelect1d;
                    ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, items.Size);
                    ApplySelectionRequests(ms_io, side);

                    for (int item_n = 0; item_n < items.Size; item_n++)
                    {
                        ImGuiID item_id = items[item_n];
                        bool item_is_selected = selection.Contains(item_id);
                        ImGui::SetNextItemSelectionUserData(item_n);
                        ImGui::Selectable(ExampleNames[item_id], item_is_selected, ImGuiSelectableFlags_AllowDoubleClick);
                        if (ImGui::IsItemFocused())
                        {
                            // FIXME-MULTISELECT: Dual List Box: Transfer focus
                            if (ImGui::IsKeyPressed(ImGuiKey_Enter) || ImGui::IsKeyPressed(ImGuiKey_KeypadEnter))
                                request_move_selected = side;
                            if (ImGui::IsMouseDoubleClicked(0)) // FIXME-MULTISELECT: Double-click on multi-selection?
                                request_move_selected = side;
                        }
                    }

                    ms_io = ImGui::EndMultiSelect();
                    ApplySelectionRequests(ms_io, side);
                }
                ImGui::EndChild();
            }

            // Buttons columns
            ImGui::TableSetColumnIndex(1);
            ImGui::NewLine();
            //ImVec2 button_sz = { ImGui::CalcTextSize(">>").x + ImGui::GetStyle().FramePadding.x * 2.0f, ImGui::GetFrameHeight() + padding.y * 2.0f };
            ImVec2 button_sz = { ImGui::GetFrameHeight(), ImGui::GetFrameHeight() };

            // (Using BeginDisabled()/EndDisabled() works but feels distracting given how it is currently visualized)
            if (ImGui::Button(">>", button_sz))
                request_move_all = 0;
            if (ImGui::Button(">", button_sz))
                request_move_selected = 0;
            if (ImGui::Button("<", button_sz))
                request_move_selected = 1;
            if (ImGui::Button("<<", button_sz))
                request_move_all = 1;

            // Process requests
            if (request_move_all != -1)
                MoveAll(request_move_all, request_move_all ^ 1);
            if (request_move_selected != -1)
                MoveSelected(request_move_selected, request_move_selected ^ 1);

            // FIXME-MULTISELECT: Support action from outside
            /*
            if (OptKeepSorted == false)
            {
                ImGui::NewLine();
                if (ImGui::ArrowButton("MoveUp", ImGuiDir_Up)) {}
                if (ImGui::ArrowButton("MoveDown", ImGuiDir_Down)) {}
            }
            */

            ImGui::EndTable();
        }
    }
};
#endif

static void DemoWindowWidgetsSelectionAndMultiSelect(Widget parent, ImGuiDemoWindowData* demo_data)
{
    UNUSED(demo_data);
    if (Widget n = ui::tree_node_ex(key(), parent, "Selection State & Multi-Select").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Selection State & Multi-Select");
        HelpMarker(*n, "Selections can be built using Selectable(), TreeNode() or other widgets. Selection state is owned by application code/data.");

        { Widget line = ui::row(key(), *n); ui::bullet(key(), line, "Wiki page:");
          //ImGui::SameLine();
          ui::text_link(key(), line, "imgui/wiki/Multi-Select", "https://github.com/ocornut/imgui/wiki/Multi-Select"); }

        // Without any fancy API: manage single-selection yourself.
        if (Widget n0 = ui::tree_node_ex(key(), *n, "Single-Select").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Single-Select");
            static int selected = -1;
            for (int i = 0; i < 5; i++)
            {
                char buf[32];
                sprintf(buf, "Object %d", i);
                if (ui::selectable(key(), *n0, buf, selected == i).activated())
                    selected = i;
            }
        }

        // Demonstrate implementation a most-basic form of multi-selection manually
        // This doesn't support the Shift modifier which requires BeginMultiSelect()!
        if (Widget n0 = ui::tree_node_ex(key(), *n, "Multi-Select (manual/simplified, without BeginMultiSelect)").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (manual/simplified, without BeginMultiSelect)");
            HelpMarker(*n0, "Hold Ctrl and Click to select multiple items.");
            static bool selection[5] = { false, false, false, false, false };
            for (int i = 0; i < 5; i++)
            {
                char buf[32];
                sprintf(buf, "Object %d", i);
                if (ui::selectable(key(), *n0, buf, selection[i] != 0).activated())
                {
                    if (!ui::io().KeyCtrl) // Clear selection when Ctrl is not held
                        memset(selection, 0, sizeof(selection));
                    selection[i] ^= 1; // Toggle current item
                }
            }
        }

#if 0
        // Demonstrate handling proper multi-selection using the BeginMultiSelect/EndMultiSelect API.
        // Shift+Click w/ Ctrl and other standard features are supported.
        // We use the ImGuiSelectionBasicStorage helper which you may freely reimplement.
        if (ImGui::TreeNode("Multi-Select"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select");
            ImGui::Text("Supported features:");
            ImGui::BulletText("Keyboard navigation (arrows, page up/down, home/end, space).");
            ImGui::BulletText("Ctrl modifier to preserve and toggle selection.");
            ImGui::BulletText("Shift modifier for range selection.");
            ImGui::BulletText("Ctrl+A to select all.");
            ImGui::BulletText("Escape to clear selection.");
            ImGui::BulletText("Click and drag to box-select.");
            ImGui::Text("Tip: Use 'Demo->Tools->Debug Log->Selection' to see selection requests as they happen.");

            // Use default selection.Adapter: Pass index to SetNextItemSelectionUserData(), store index in Selection
            const int ITEMS_COUNT = 50;
            static ImGuiSelectionBasicStorage selection;
            ImGui::Text("Selection: %d/%d", selection.Size, ITEMS_COUNT);

            // The BeginChild() has no purpose for selection logic, other that offering a scrolling region.
            if (ImGui::BeginChild("##Basket", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY))
            {
                ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_BoxSelect1d;
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, ITEMS_COUNT);
                selection.ApplyRequests(ms_io);

                for (int n = 0; n < ITEMS_COUNT; n++)
                {
                    char label[64];
                    sprintf(label, "Object %05d: %s", n, ExampleNames[n % IM_COUNTOF(ExampleNames)]);
                    bool item_is_selected = selection.Contains((ImGuiID)n);
                    ImGui::SetNextItemSelectionUserData(n);
                    ImGui::Selectable(label, item_is_selected);
                }

                ms_io = ImGui::EndMultiSelect();
                selection.ApplyRequests(ms_io);
            }
            ImGui::EndChild();
            ImGui::TreePop();
        }

        // Demonstrate using the clipper with BeginMultiSelect()/EndMultiSelect()
        if (ImGui::TreeNode("Multi-Select (with clipper)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (with clipper)");
            // Use default selection.Adapter: Pass index to SetNextItemSelectionUserData(), store index in Selection
            static ImGuiSelectionBasicStorage selection;

            ImGui::Text("Added features:");
            ImGui::BulletText("Using ImGuiListClipper.");

            const int ITEMS_COUNT = 10000;
            ImGui::Text("Selection: %d/%d", selection.Size, ITEMS_COUNT);
            if (ImGui::BeginChild("##Basket", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY))
            {
                ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_BoxSelect1d;
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, ITEMS_COUNT);
                selection.ApplyRequests(ms_io);

                ImGuiListClipper clipper;
                clipper.Begin(ITEMS_COUNT);
                if (ms_io->RangeSrcItem != -1)
                    clipper.IncludeItemByIndex((int)ms_io->RangeSrcItem); // Ensure RangeSrc item is not clipped.
                while (clipper.Step())
                {
                    for (int n = clipper.DisplayStart; n < clipper.DisplayEnd; n++)
                    {
                        char label[64];
                        sprintf(label, "Object %05d: %s", n, ExampleNames[n % IM_COUNTOF(ExampleNames)]);
                        bool item_is_selected = selection.Contains((ImGuiID)n);
                        ImGui::SetNextItemSelectionUserData(n);
                        ImGui::Selectable(label, item_is_selected);
                    }
                }

                ms_io = ImGui::EndMultiSelect();
                selection.ApplyRequests(ms_io);
            }
            ImGui::EndChild();
            ImGui::TreePop();
        }

        // Demonstrate dynamic item list + deletion support using the BeginMultiSelect/EndMultiSelect API.
        // In order to support Deletion without any glitches you need to:
        // - (1) If items are submitted in their own scrolling area, submit contents size SetNextWindowContentSize() ahead of time to prevent one-frame readjustment of scrolling.
        // - (2) Items needs to have persistent ID Stack identifier = ID needs to not depends on their index. PushID(index) = KO. PushID(item_id) = OK. This is in order to focus items reliably after a selection.
        // - (3) BeginXXXX process
        // - (4) Focus process
        // - (5) EndXXXX process
        if (ImGui::TreeNode("Multi-Select (with deletion)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (with deletion)");
            // Storing items data separately from selection data.
            // (you may decide to store selection data inside your item (aka intrusive storage) if you don't need multiple views over same items)
            // Use a custom selection.Adapter: store item identifier in Selection (instead of index)
            static ImVector<ImGuiID> items;
            static ExampleSelectionWithDeletion selection;
            selection.UserData = (void*)&items;
            selection.AdapterIndexToStorageId = [](ImGuiSelectionBasicStorage* self, int idx) { ImVector<ImGuiID>* p_items = (ImVector<ImGuiID>*)self->UserData; return (*p_items)[idx]; }; // Index -> ID

            ImGui::Text("Added features:");
            ImGui::BulletText("Dynamic list with Delete key support.");
            ImGui::Text("Selection size: %d/%d", selection.Size, items.Size);

            // Initialize default list with 50 items + button to add/remove items.
            static ImGuiID items_next_id = 0;
            if (items_next_id == 0)
                for (ImGuiID n = 0; n < 50; n++)
                    items.push_back(items_next_id++);
            if (ImGui::SmallButton("Add 20 items"))     { for (int n = 0; n < 20; n++) { items.push_back(items_next_id++); } }
            ImGui::SameLine();
            if (ImGui::SmallButton("Remove 20 items"))  { for (int n = IM_MIN(20, items.Size); n > 0; n--) { selection.SetItemSelected(items.back(), false); items.pop_back(); } }

            // (1) Extra to support deletion: Submit scrolling range to avoid glitches on deletion
            const float items_height = ImGui::GetTextLineHeightWithSpacing();
            ImGui::SetNextWindowContentSize(ImVec2(0.0f, items.Size * items_height));

            if (ImGui::BeginChild("##Basket", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY))
            {
                ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_BoxSelect1d;
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, items.Size);
                selection.ApplyRequests(ms_io);

                const bool want_delete = ImGui::Shortcut(ImGuiKey_Delete, ImGuiInputFlags_Repeat) && (selection.Size > 0);
                const int item_curr_idx_to_focus = want_delete ? selection.ApplyDeletionPreLoop(ms_io, items.Size) : -1;

                for (int n = 0; n < items.Size; n++)
                {
                    const ImGuiID item_id = items[n];
                    char label[64];
                    sprintf(label, "Object %05u: %s", item_id, ExampleNames[item_id % IM_COUNTOF(ExampleNames)]);

                    bool item_is_selected = selection.Contains(item_id);
                    ImGui::SetNextItemSelectionUserData(n);
                    ImGui::Selectable(label, item_is_selected);
                    if (item_curr_idx_to_focus == n)
                        ImGui::SetKeyboardFocusHere(-1);
                }

                // Apply multi-select requests
                ms_io = ImGui::EndMultiSelect();
                selection.ApplyRequests(ms_io);
                if (want_delete)
                    selection.ApplyDeletionPostLoop(ms_io, items, item_curr_idx_to_focus);
            }
            ImGui::EndChild();
            ImGui::TreePop();
        }

        // Implement a Dual List Box (#6648)
        if (ImGui::TreeNode("Multi-Select (dual list box)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (dual list box)");
            // Init default state
            static ExampleDualListBox dlb;
            if (dlb.Items[0].Size == 0 && dlb.Items[1].Size == 0)
                for (int item_id = 0; item_id < IM_COUNTOF(ExampleNames); item_id++)
                    dlb.Items[0].push_back((ImGuiID)item_id);

            // Show
            dlb.Show();

            ImGui::TreePop();
        }

        // Demonstrate using the clipper with BeginMultiSelect()/EndMultiSelect()
        if (ImGui::TreeNode("Multi-Select (in a table)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (in a table)");
            static ImGuiSelectionBasicStorage selection;

            const int ITEMS_COUNT = 10000;
            ImGui::Text("Selection: %d/%d", selection.Size, ITEMS_COUNT);
            if (ImGui::BeginTable("##Basket", 2, ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter, ImVec2(0.0f, ImGui::GetFontSize() * 20)))
            {
                ImGui::TableSetupColumn("Object");
                ImGui::TableSetupColumn("Action");
                ImGui::TableSetupScrollFreeze(0, 1);
                ImGui::TableHeadersRow();

                ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_BoxSelect1d;
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, ITEMS_COUNT);
                selection.ApplyRequests(ms_io);

                ImGuiListClipper clipper;
                clipper.Begin(ITEMS_COUNT);
                if (ms_io->RangeSrcItem != -1)
                    clipper.IncludeItemByIndex((int)ms_io->RangeSrcItem); // Ensure RangeSrc item is not clipped.
                while (clipper.Step())
                {
                    for (int n = clipper.DisplayStart; n < clipper.DisplayEnd; n++)
                    {
                        ImGui::TableNextRow();
                        ImGui::TableNextColumn();
                        ImGui::PushID(n);
                        char label[64];
                        sprintf(label, "Object %05d: %s", n, ExampleNames[n % IM_COUNTOF(ExampleNames)]);
                        bool item_is_selected = selection.Contains((ImGuiID)n);
                        ImGui::SetNextItemSelectionUserData(n);
                        ImGui::Selectable(label, item_is_selected, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap);
                        ImGui::TableNextColumn();
                        ImGui::SmallButton("hello");
                        ImGui::PopID();
                    }
                }

                ms_io = ImGui::EndMultiSelect();
                selection.ApplyRequests(ms_io);
                ImGui::EndTable();
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Multi-Select (checkboxes)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (checkboxes)");
            ImGui::Text("In a list of checkboxes (not selectable):");
            ImGui::BulletText("Using _NoAutoSelect + _NoAutoClear flags.");
            ImGui::BulletText("Shift+Click to check multiple boxes.");
            ImGui::BulletText("Shift+Keyboard to copy current value to other boxes.");

            // If you have an array of checkboxes, you may want to use NoAutoSelect + NoAutoClear and the ImGuiSelectionExternalStorage helper.
            static bool items[20] = {};
            static ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_NoAutoSelect | ImGuiMultiSelectFlags_NoAutoClear | ImGuiMultiSelectFlags_ClearOnEscape;
            ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoAutoSelect", &flags, ImGuiMultiSelectFlags_NoAutoSelect);
            ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoAutoClear", &flags, ImGuiMultiSelectFlags_NoAutoClear);
            ImGui::CheckboxFlags("ImGuiMultiSelectFlags_BoxSelect2d", &flags, ImGuiMultiSelectFlags_BoxSelect2d); // Cannot use ImGuiMultiSelectFlags_BoxSelect1d as checkboxes are varying width.

            if (ImGui::BeginChild("##Basket", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeY))
            {
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, -1, IM_COUNTOF(items));
                ImGuiSelectionExternalStorage storage_wrapper;
                storage_wrapper.UserData = (void*)items;
                storage_wrapper.AdapterSetItemSelected = [](ImGuiSelectionExternalStorage* self, int n, bool selected) { bool* array = (bool*)self->UserData; array[n] = selected; };
                storage_wrapper.ApplyRequests(ms_io);
                for (int n = 0; n < 20; n++)
                {
                    char label[32];
                    sprintf(label, "Item %d", n);
                    ImGui::SetNextItemSelectionUserData(n);
                    ImGui::Checkbox(label, &items[n]);
                }
                ms_io = ImGui::EndMultiSelect();
                storage_wrapper.ApplyRequests(ms_io);
            }
            ImGui::EndChild();

            ImGui::TreePop();
        }

        // Demonstrate individual selection scopes in same window
        if (ImGui::TreeNode("Multi-Select (multiple scopes)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (multiple scopes)");
            // Use default select: Pass index to SetNextItemSelectionUserData(), store index in Selection
            const int SCOPES_COUNT = 3;
            const int ITEMS_COUNT = 8; // Per scope
            static ImGuiSelectionBasicStorage selections_data[SCOPES_COUNT];

            // Use ImGuiMultiSelectFlags_ScopeRect to not affect other selections in same window.
            static ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_ScopeRect | ImGuiMultiSelectFlags_ClearOnEscape;// | ImGuiMultiSelectFlags_ClearOnClickVoid;
            if (ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ScopeWindow", &flags, ImGuiMultiSelectFlags_ScopeWindow) && (flags & ImGuiMultiSelectFlags_ScopeWindow))
                flags &= ~ImGuiMultiSelectFlags_ScopeRect;
            if (ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ScopeRect", &flags, ImGuiMultiSelectFlags_ScopeRect) && (flags & ImGuiMultiSelectFlags_ScopeRect))
                flags &= ~ImGuiMultiSelectFlags_ScopeWindow;
            ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ClearOnClickVoid", &flags, ImGuiMultiSelectFlags_ClearOnClickVoid);
            ImGui::CheckboxFlags("ImGuiMultiSelectFlags_BoxSelect1d", &flags, ImGuiMultiSelectFlags_BoxSelect1d);

            for (int selection_scope_n = 0; selection_scope_n < SCOPES_COUNT; selection_scope_n++)
            {
                ImGui::PushID(selection_scope_n);
                ImGuiSelectionBasicStorage* selection = &selections_data[selection_scope_n];
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection->Size, ITEMS_COUNT);
                selection->ApplyRequests(ms_io);

                ImGui::SeparatorText("Selection scope");
                ImGui::Text("Selection size: %d/%d", selection->Size, ITEMS_COUNT);

                for (int n = 0; n < ITEMS_COUNT; n++)
                {
                    char label[64];
                    sprintf(label, "Object %05d: %s", n, ExampleNames[n % IM_COUNTOF(ExampleNames)]);
                    bool item_is_selected = selection->Contains((ImGuiID)n);
                    ImGui::SetNextItemSelectionUserData(n);
                    ImGui::Selectable(label, item_is_selected);
                }

                // Apply multi-select requests
                ms_io = ImGui::EndMultiSelect();
                selection->ApplyRequests(ms_io);
                ImGui::PopID();
            }
            ImGui::TreePop();
        }

        // See ShowExampleAppAssetsBrowser()
        if (ImGui::TreeNode("Multi-Select (tiled assets browser)"))
        {
            ImGui::Checkbox("Assets Browser", &demo_data->ShowAppAssetsBrowser);
            ImGui::Text("(also access from 'Examples->Assets Browser' in menu)");
            ImGui::TreePop();
        }

        // Demonstrate supporting multiple-selection in a tree.
        // - We don't use linear indices for selection user data, but our ExampleTreeNode* pointer directly!
        //   This showcase how SetNextItemSelectionUserData() never assume indices!
        // - The difficulty here is to "interpolate" from RangeSrcItem to RangeDstItem in the SetAll/SetRange request.
        //   We want this interpolation to match what the user sees: in visible order, skipping closed nodes.
        //   This is implemented by our TreeGetNextNodeInVisibleOrder() user-space helper.
        // - Important: In a real codebase aiming to implement full-featured selectable tree with custom filtering, you
        //   are more likely to build an array mapping sequential indices to visible tree nodes, since your
        //   filtering/search + clipping process will benefit from it. Having this will make this interpolation much easier.
        // - Consider this a prototype: we are working toward simplifying some of it.
        if (ImGui::TreeNode("Multi-Select (trees)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (trees)");
            HelpMarker(
                "This is rather advanced and experimental. If you are getting started with multi-select, "
                "please don't start by looking at how to use it for a tree!\n\n"
                "Future versions will try to simplify and formalize some of this.");

            struct ExampleTreeFuncs
            {
                static void DrawNode(ExampleTreeNode* node, ImGuiSelectionBasicStorage* selection)
                {
                    ImGuiTreeNodeFlags tree_node_flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                    tree_node_flags |= ImGuiTreeNodeFlags_NavLeftJumpsToParent; // Enable pressing left to jump to parent
                    if (node->Childs.Size == 0)
                        tree_node_flags |= ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_Leaf;
                    if (selection->Contains((ImGuiID)node->UID))
                        tree_node_flags |= ImGuiTreeNodeFlags_Selected;

                    // Using SetNextItemStorageID() to specify storage id, so we can easily peek into
                    // the storage holding open/close stage, using our TreeNodeGetOpen/TreeNodeSetOpen() functions.
                    ImGui::SetNextItemSelectionUserData((ImGuiSelectionUserData)(intptr_t)node);
                    ImGui::SetNextItemStorageID((ImGuiID)node->UID);
                    if (ImGui::TreeNodeEx(node->Name, tree_node_flags))
                    {
                        for (ExampleTreeNode* child : node->Childs)
                            DrawNode(child, selection);
                        ImGui::TreePop();
                    }
                    else if (ImGui::IsItemToggledOpen())
                    {
                        TreeCloseAndUnselectChildNodes(node, selection);
                    }
                }

                // When closing a node: 1) close and unselect all child nodes, 2) select parent if any child was selected.
                // FIXME: This is currently handled by user logic but I'm hoping to eventually provide tree node
                // features to do this automatically, e.g. a ImGuiTreeNodeFlags_AutoCloseChildNodes etc.
                static int TreeCloseAndUnselectChildNodes(ExampleTreeNode* node, ImGuiSelectionBasicStorage* selection, int depth = 0)
                {
                    // Recursive close (the test for depth == 0 is because we call this on a node that was just closed!)
                    int unselected_count = selection->Contains((ImGuiID)node->UID) ? 1 : 0;
                    if (depth == 0 || ImGui::TreeNodeGetOpen((ImGuiID)node->UID))
                    {
                        for (ExampleTreeNode* child : node->Childs)
                            unselected_count += TreeCloseAndUnselectChildNodes(child, selection, depth + 1);
                        ImGui::TreeNodeSetOpen((ImGuiID)node->UID, false);
                    }

                    // Select root node if any of its child was selected, otherwise unselect
                    selection->SetItemSelected((ImGuiID)node->UID, (depth == 0 && unselected_count > 0));
                    return unselected_count;
                }

                // Apply multi-selection requests
                static void ApplySelectionRequests(ImGuiMultiSelectIO* ms_io, ExampleTreeNode* tree, ImGuiSelectionBasicStorage* selection)
                {
                    for (ImGuiSelectionRequest& req : ms_io->Requests)
                    {
                        if (req.Type == ImGuiSelectionRequestType_SetAll)
                        {
                            if (req.Selected)
                                TreeSetAllInOpenNodes(tree, selection, req.Selected);
                            else
                                selection->Clear();
                        }
                        else if (req.Type == ImGuiSelectionRequestType_SetRange)
                        {
                            ExampleTreeNode* first_node = (ExampleTreeNode*)(intptr_t)req.RangeFirstItem;
                            ExampleTreeNode* last_node = (ExampleTreeNode*)(intptr_t)req.RangeLastItem;
                            for (ExampleTreeNode* node = first_node; node != NULL; node = TreeGetNextNodeInVisibleOrder(node, last_node))
                                selection->SetItemSelected((ImGuiID)node->UID, req.Selected);
                        }
                    }
                }

                static void TreeSetAllInOpenNodes(ExampleTreeNode* node, ImGuiSelectionBasicStorage* selection, bool selected)
                {
                    if (node->Parent != NULL) // Root node isn't visible nor selectable in our scheme
                        selection->SetItemSelected((ImGuiID)node->UID, selected);
                    if (node->Parent == NULL || ImGui::TreeNodeGetOpen((ImGuiID)node->UID))
                        for (ExampleTreeNode* child : node->Childs)
                            TreeSetAllInOpenNodes(child, selection, selected);
                }

                // Interpolate in *user-visible order* AND only *over opened nodes*.
                // If you have a sequential mapping tables (e.g. generated after a filter/search pass) this would be simpler.
                // Here the tricks are that:
                // - we store/maintain ExampleTreeNode::IndexInParent which allows implementing a linear iterator easily, without searches, without recursion.
                //   this could be replaced by a search in parent, aka 'int index_in_parent = curr_node->Parent->Childs.find_index(curr_node)'
                //   which would only be called when crossing from child to a parent, aka not too much.
                // - we call SetNextItemStorageID() before our TreeNode() calls with an ID which doesn't relate to UI stack,
                //   making it easier to call TreeNodeGetOpen()/TreeNodeSetOpen() from any location.
                static ExampleTreeNode* TreeGetNextNodeInVisibleOrder(ExampleTreeNode* curr_node, ExampleTreeNode* last_node)
                {
                    // Reached last node
                    if (curr_node == last_node)
                        return NULL;

                    // Recurse into childs. Query storage to tell if the node is open.
                    if (curr_node->Childs.Size > 0 && ImGui::TreeNodeGetOpen((ImGuiID)curr_node->UID))
                        return curr_node->Childs[0];

                    // Next sibling, then into our own parent
                    while (curr_node->Parent != NULL)
                    {
                        if (curr_node->IndexInParent + 1 < curr_node->Parent->Childs.Size)
                            return curr_node->Parent->Childs[curr_node->IndexInParent + 1];
                        curr_node = curr_node->Parent;
                    }
                    return NULL;
                }

            }; // ExampleTreeFuncs

            static ImGuiSelectionBasicStorage selection;
            if (demo_data->DemoTree == NULL)
                demo_data->DemoTree = ExampleTree_CreateDemoTree(); // Create tree once
            ImGui::Text("Selection size: %d", selection.Size);

            if (ImGui::BeginChild("##Tree", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY))
            {
                ExampleTreeNode* tree = demo_data->DemoTree;
                ImGuiMultiSelectFlags ms_flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_BoxSelect2d;
                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(ms_flags, selection.Size, -1);
                ExampleTreeFuncs::ApplySelectionRequests(ms_io, tree, &selection);
                for (ExampleTreeNode* node : tree->Childs)
                    ExampleTreeFuncs::DrawNode(node, &selection);
                ms_io = ImGui::EndMultiSelect();
                ExampleTreeFuncs::ApplySelectionRequests(ms_io, tree, &selection);
            }
            ImGui::EndChild();

            ImGui::TreePop();
        }

        // Advanced demonstration of BeginMultiSelect()
        // - Showcase clipping.
        // - Showcase deletion.
        // - Showcase basic drag and drop.
        // - Showcase TreeNode variant (note that tree node don't expand in the demo: supporting expanding tree nodes + clipping a separate thing).
        // - Showcase using inside a table.
        //ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        if (ImGui::TreeNode("Multi-Select (advanced)"))
        {
            IMGUI_DEMO_MARKER("Widgets/Selection State/Multi-Select (advanced)");
            // Options
            enum WidgetType { WidgetType_Selectable, WidgetType_TreeNode };
            static bool use_clipper = true;
            static bool use_deletion = true;
            static bool use_drag_drop = true;
            static bool show_in_table = false;
            static bool show_color_button = true;
            static ImGuiMultiSelectFlags flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_BoxSelect1d;
            static WidgetType widget_type = WidgetType_Selectable;

            if (ImGui::TreeNode("Options"))
            {
                if (ImGui::RadioButton("Selectables", widget_type == WidgetType_Selectable)) { widget_type = WidgetType_Selectable; }
                ImGui::SameLine();
                if (ImGui::RadioButton("Tree nodes", widget_type == WidgetType_TreeNode)) { widget_type = WidgetType_TreeNode; }
                ImGui::SameLine();
                HelpMarker("TreeNode() is technically supported but... using this correctly is more complicated (you need some sort of linear/random access to your tree, which is suited to advanced trees setups already implementing filters and clipper. We will work toward simplifying and demoing this.\n\nFor now the tree demo is actually a little bit meaningless because it is an empty tree with only root nodes.");
                ImGui::Checkbox("Enable clipper", &use_clipper);
                ImGui::Checkbox("Enable deletion", &use_deletion);
                ImGui::Checkbox("Enable drag & drop", &use_drag_drop);
                ImGui::Checkbox("Show in a table", &show_in_table);
                ImGui::Checkbox("Show color button", &show_color_button);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_SingleSelect", &flags, ImGuiMultiSelectFlags_SingleSelect);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoSelectAll", &flags, ImGuiMultiSelectFlags_NoSelectAll);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoRangeSelect", &flags, ImGuiMultiSelectFlags_NoRangeSelect);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoAutoSelect", &flags, ImGuiMultiSelectFlags_NoAutoSelect);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoAutoClear", &flags, ImGuiMultiSelectFlags_NoAutoClear);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoAutoClearOnReselect", &flags, ImGuiMultiSelectFlags_NoAutoClearOnReselect);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_NoSelectOnRightClick", &flags, ImGuiMultiSelectFlags_NoSelectOnRightClick);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_BoxSelect1d", &flags, ImGuiMultiSelectFlags_BoxSelect1d);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_BoxSelect2d", &flags, ImGuiMultiSelectFlags_BoxSelect2d);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_BoxSelectNoScroll", &flags, ImGuiMultiSelectFlags_BoxSelectNoScroll);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ClearOnEscape", &flags, ImGuiMultiSelectFlags_ClearOnEscape);
                ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ClearOnClickVoid", &flags, ImGuiMultiSelectFlags_ClearOnClickVoid);
                if (ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ScopeWindow", &flags, ImGuiMultiSelectFlags_ScopeWindow) && (flags & ImGuiMultiSelectFlags_ScopeWindow))
                    flags &= ~ImGuiMultiSelectFlags_ScopeRect;
                if (ImGui::CheckboxFlags("ImGuiMultiSelectFlags_ScopeRect", &flags, ImGuiMultiSelectFlags_ScopeRect) && (flags & ImGuiMultiSelectFlags_ScopeRect))
                    flags &= ~ImGuiMultiSelectFlags_ScopeWindow;
                if (ImGui::CheckboxFlags("ImGuiMultiSelectFlags_SelectOnAuto", &flags, ImGuiMultiSelectFlags_SelectOnAuto))
                    flags &= ~(ImGuiMultiSelectFlags_SelectOnMask_ ^ ImGuiMultiSelectFlags_SelectOnAuto);
                ImGui::SameLine(); HelpMarker("Apply selection on mouse down when clicking on unselected item, on mouse up when clicking on selected item. (Default)");
                if (ImGui::CheckboxFlags("ImGuiMultiSelectFlags_SelectOnClickAlways", &flags, ImGuiMultiSelectFlags_SelectOnClickAlways))
                    flags &= ~(ImGuiMultiSelectFlags_SelectOnMask_ ^ ImGuiMultiSelectFlags_SelectOnClickAlways);
                ImGui::SameLine(); HelpMarker("Prevents Drag and Drop from being used on multi-selection, but allows e.g. BoxSelect to always reselect even when clicking inside an existing selection. (Excel style behavior)");
                if (ImGui::CheckboxFlags("ImGuiMultiSelectFlags_SelectOnClickRelease", &flags, ImGuiMultiSelectFlags_SelectOnClickRelease))
                    flags &= ~(ImGuiMultiSelectFlags_SelectOnMask_ ^ ImGuiMultiSelectFlags_SelectOnClickRelease);
                ImGui::SameLine(); HelpMarker("Allow dragging an unselected item without altering selection.");
                ImGui::TreePop();
            }

            // Initialize default list with 1000 items.
            // Use default selection.Adapter: Pass index to SetNextItemSelectionUserData(), store index in Selection
            static ImVector<int> items;
            static int items_next_id = 0;
            if (items_next_id == 0) { for (int n = 0; n < 1000; n++) { items.push_back(items_next_id++); } }
            static ExampleSelectionWithDeletion selection;
            static bool request_deletion_from_menu = false; // Queue deletion triggered from context menu

            ImGui::Text("Selection size: %d/%d", selection.Size, items.Size);

            const float items_height = (widget_type == WidgetType_TreeNode) ? ImGui::GetTextLineHeight() : ImGui::GetTextLineHeightWithSpacing();
            ImGui::SetNextWindowContentSize(ImVec2(0.0f, items.Size * items_height));
            if (ImGui::BeginChild("##Basket", ImVec2(-FLT_MIN, ImGui::GetFontSize() * 20), ImGuiChildFlags_FrameStyle | ImGuiChildFlags_ResizeY))
            {
                ImVec2 color_button_sz(ImGui::GetFontSize(), ImGui::GetFontSize());
                if (widget_type == WidgetType_TreeNode)
                    ImGui::PushStyleVarY(ImGuiStyleVar_ItemSpacing, 0.0f);

                ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(flags, selection.Size, items.Size);
                selection.ApplyRequests(ms_io);

                const bool want_delete = (ImGui::Shortcut(ImGuiKey_Delete, ImGuiInputFlags_Repeat) && (selection.Size > 0)) || request_deletion_from_menu;
                const int item_curr_idx_to_focus = want_delete ? selection.ApplyDeletionPreLoop(ms_io, items.Size) : -1;
                request_deletion_from_menu = false;

                if (show_in_table)
                {
                    if (widget_type == WidgetType_TreeNode)
                        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(0.0f, 0.0f));
                    ImGui::BeginTable("##Split", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_NoPadOuterX);
                    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch, 0.70f);
                    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch, 0.30f);
                    //ImGui::PushStyleVarY(ImGuiStyleVar_ItemSpacing, 0.0f);
                }

                ImGuiListClipper clipper;
                if (use_clipper)
                {
                    clipper.Begin(items.Size);
                    if (item_curr_idx_to_focus != -1)
                        clipper.IncludeItemByIndex(item_curr_idx_to_focus); // Ensure focused item is not clipped.
                    if (ms_io->RangeSrcItem != -1)
                        clipper.IncludeItemByIndex((int)ms_io->RangeSrcItem); // Ensure RangeSrc item is not clipped.
                }

                while (!use_clipper || clipper.Step())
                {
                    const int item_begin = use_clipper ? clipper.DisplayStart : 0;
                    const int item_end = use_clipper ? clipper.DisplayEnd : items.Size;
                    for (int n = item_begin; n < item_end; n++)
                    {
                        if (show_in_table)
                            ImGui::TableNextColumn();

                        const int item_id = items[n];
                        const char* item_category = ExampleNames[item_id % IM_COUNTOF(ExampleNames)];
                        char label[64];
                        sprintf(label, "Object %05d: %s", item_id, item_category);

                        // IMPORTANT: for deletion refocus to work we need object ID to be stable,
                        // aka not depend on their index in the list. Here we use our persistent item_id
                        // instead of index to build a unique ID that will persist.
                        // (If we used PushID(index) instead, focus wouldn't be restored correctly after deletion).
                        ImGui::PushID(item_id);

                        // Emit a color button, to test that Shift+LeftArrow landing on an item that is not part
                        // of the selection scope doesn't erroneously alter our selection.
                        if (show_color_button)
                        {
                            ImU32 dummy_col = (ImU32)((unsigned int)n * 0xC250B74B) | IM_COL32_A_MASK;
                            ImGui::ColorButton("##", ImColor(dummy_col), ImGuiColorEditFlags_NoTooltip, color_button_sz);
                            ImGui::SameLine();
                        }

                        // Submit item
                        bool item_is_selected = selection.Contains((ImGuiID)n);
                        bool item_is_open = false;
                        ImGui::SetNextItemSelectionUserData(n);
                        if (widget_type == WidgetType_Selectable)
                        {
                            ImGui::Selectable(label, item_is_selected, ImGuiSelectableFlags_None);
                        }
                        else if (widget_type == WidgetType_TreeNode)
                        {
                            ImGuiTreeNodeFlags tree_node_flags = ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                            if (item_is_selected)
                                tree_node_flags |= ImGuiTreeNodeFlags_Selected;
                            item_is_open = ImGui::TreeNodeEx(label, tree_node_flags);
                        }

                        // Focus (for after deletion)
                        if (item_curr_idx_to_focus == n)
                            ImGui::SetKeyboardFocusHere(-1);

                        // Drag and Drop
                        if (use_drag_drop && ImGui::BeginDragDropSource())
                        {
                            // Create payload with full selection OR single unselected item.
                            // (the later is only possible when using ImGuiMultiSelectFlags_SelectOnClickRelease)
                            if (ImGui::GetDragDropPayload() == NULL)
                            {
                                ImVector<int> payload_items;
                                void* it = NULL;
                                ImGuiID id = 0;
                                if (!item_is_selected)
                                    payload_items.push_back(item_id);
                                else
                                    while (selection.GetNextSelectedItem(&it, &id))
                                        payload_items.push_back((int)id);
                                ImGui::SetDragDropPayload("MULTISELECT_DEMO_ITEMS", payload_items.Data, (size_t)payload_items.size_in_bytes());
                            }

                            // Display payload content in tooltip
                            const ImGuiPayload* payload = ImGui::GetDragDropPayload();
                            const int* payload_items = (int*)payload->Data;
                            const int payload_count = (int)payload->DataSize / (int)sizeof(int);
                            if (payload_count == 1)
                                ImGui::Text("Object %05d: %s", payload_items[0], ExampleNames[payload_items[0] % IM_COUNTOF(ExampleNames)]);
                            else
                                ImGui::Text("Dragging %d objects", payload_count);

                            ImGui::EndDragDropSource();
                        }

                        if (widget_type == WidgetType_TreeNode && item_is_open)
                            ImGui::TreePop();

                        // Right-click: context menu
                        if (ImGui::BeginPopupContextItem())
                        {
                            ImGui::BeginDisabled(!use_deletion || selection.Size == 0);
                            sprintf(label, "Delete %d item(s)###DeleteSelected", selection.Size);
                            if (ImGui::Selectable(label))
                                request_deletion_from_menu = true;
                            ImGui::EndDisabled();
                            ImGui::Selectable("Close");
                            ImGui::EndPopup();
                        }

                        // Demo content within a table
                        if (show_in_table)
                        {
                            ImGui::TableNextColumn();
                            ImGui::SetNextItemWidth(-FLT_MIN);
                            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                            ImGui::InputText("##NoLabel", (char*)(void*)item_category, strlen(item_category), ImGuiInputTextFlags_ReadOnly);
                            ImGui::PopStyleVar();
                        }

                        ImGui::PopID();
                    }
                    if (!use_clipper)
                        break;
                }

                if (show_in_table)
                {
                    ImGui::EndTable();
                    if (widget_type == WidgetType_TreeNode)
                        ImGui::PopStyleVar();
                }

                // Apply multi-select requests
                ms_io = ImGui::EndMultiSelect();
                selection.ApplyRequests(ms_io);
                if (want_delete)
                    selection.ApplyDeletionPostLoop(ms_io, items, item_curr_idx_to_focus);

                if (widget_type == WidgetType_TreeNode)
                    ImGui::PopStyleVar();
            }
            ImGui::EndChild();
            ImGui::TreePop();
        }
#endif
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTabs()
//-----------------------------------------------------------------------------

static void EditTabBarFittingPolicyFlags(Widget parent, ImGuiTabBarFlags* p_flags)
{
    if ((*p_flags & ImGuiTabBarFlags_FittingPolicyMask_) == 0)
        *p_flags |= ImGuiTabBarFlags_FittingPolicyDefault_;
    if (ui::checkbox_flags(key(), parent, "ImGuiTabBarFlags_FittingPolicyMixed", *p_flags, ImGuiTabBarFlags_FittingPolicyMixed))
        *p_flags &= ~(ImGuiTabBarFlags_FittingPolicyMask_ ^ ImGuiTabBarFlags_FittingPolicyMixed);
    if (ui::checkbox_flags(key(), parent, "ImGuiTabBarFlags_FittingPolicyShrink", *p_flags, ImGuiTabBarFlags_FittingPolicyShrink))
        *p_flags &= ~(ImGuiTabBarFlags_FittingPolicyMask_ ^ ImGuiTabBarFlags_FittingPolicyShrink);
    if (ui::checkbox_flags(key(), parent, "ImGuiTabBarFlags_FittingPolicyScroll", *p_flags, ImGuiTabBarFlags_FittingPolicyScroll))
        *p_flags &= ~(ImGuiTabBarFlags_FittingPolicyMask_ ^ ImGuiTabBarFlags_FittingPolicyScroll);
}

static void DemoWindowWidgetsTabs(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Tabs").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Tabs");
        if (Widget n0 = ui::tree_node_ex(key(), *n, "Basic").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Tabs/Basic");
            //ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
            Tabber tab_bar = ui::tabber(key(), *n0); // ImGui::BeginTabBar("MyTabBar", tab_bar_flags)
            {
                if (Widget tab = ui::tab(key(), tab_bar, "Avocado"))
                {
                    ui::label(key(), *tab, "This is the Avocado tab!\nblah blah blah blah blah");
                }
                if (Widget tab = ui::tab(key(), tab_bar, "Broccoli"))
                {
                    ui::label(key(), *tab, "This is the Broccoli tab!\nblah blah blah blah blah");
                }
                if (Widget tab = ui::tab(key(), tab_bar, "Cucumber"))
                {
                    ui::label(key(), *tab, "This is the Cucumber tab!\nblah blah blah blah blah");
                }
            }
            ui::separator(key(), *n0);
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Advanced & Close Button").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Tabs/Advanced & Close Button");
            // Expose a couple of the available flags. In most cases you may just call BeginTabBar() with no flags (0).
            static ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_Reorderable;
            ui::checkbox_flags(key(), *n0, "ImGuiTabBarFlags_Reorderable", tab_bar_flags, ImGuiTabBarFlags_Reorderable);
            ui::checkbox_flags(key(), *n0, "ImGuiTabBarFlags_AutoSelectNewTabs", tab_bar_flags, ImGuiTabBarFlags_AutoSelectNewTabs);
            ui::checkbox_flags(key(), *n0, "ImGuiTabBarFlags_TabListPopupButton", tab_bar_flags, ImGuiTabBarFlags_TabListPopupButton);
            ui::checkbox_flags(key(), *n0, "ImGuiTabBarFlags_NoCloseWithMiddleMouseButton", tab_bar_flags, ImGuiTabBarFlags_NoCloseWithMiddleMouseButton);
            ui::checkbox_flags(key(), *n0, "ImGuiTabBarFlags_DrawSelectedOverline", tab_bar_flags, ImGuiTabBarFlags_DrawSelectedOverline);
            EditTabBarFittingPolicyFlags(*n0, &tab_bar_flags);

            // Tab Bar
            //ImGui::AlignTextToFramePadding();
            Widget line = ui::row(key(), *n0);
            ui::label(key(), line, "Opened:");
            const char* names[4] = { "Artichoke", "Beetroot", "Celery", "Daikon" };
            static bool opened[4] = { true, true, true, true }; // Persistent user state
            for (int i = 0; i < IM_COUNTOF(opened); i++)
            {
                //ImGui::SameLine();
                ui::checkbox(key(), line, names[i], opened[i]);
            }

            // Passing a bool* to BeginTabItem() is similar to passing one to Begin():
            // the underlying bool will be set to false when the tab is closed.
            Tabber tab_bar = ui::tabber(key(), *n0); // ImGui::BeginTabBar("MyTabBar", tab_bar_flags)
            {
                for (int i = 0; i < IM_COUNTOF(opened); i++)
                    if (opened[i])
                        if (Widget tab = ui::tab_item(key(i), tab_bar, names[i], &opened[i])) // ImGuiTabItemFlags_None
                        {
                            ui::textf(key(), *tab, "This is the %s tab!", names[i]);
                            if (i & 1)
                                ui::label(key(), *tab, "I am an odd tab.");
                        }
            }
            ui::separator(key(), *n0);
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "TabItemButton & Leading/Trailing flags").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Tabs/TabItemButton & Leading-Trailing flags");
            static vector<int> active_tabs;
            static int next_tab_id = 0;
            if (next_tab_id == 0) // Initialize with some default tabs
                for (int i = 0; i < 3; i++)
                    active_tabs.push_back(next_tab_id++);

            // TabItemButton() and Leading/Trailing flags are distinct features which we will demo together.
            // (It is possible to submit regular tabs with Leading/Trailing flags, or TabItemButton tabs without Leading/Trailing flags...
            // but they tend to make more sense together)
            static bool show_leading_button = true;
            static bool show_trailing_button = true;
            static bool show_leading_trailing_tabs = false;
            ui::checkbox(key(), *n0, "Show Leading TabItemButton()", show_leading_button);
            ui::checkbox(key(), *n0, "Show Trailing TabItemButton()", show_trailing_button);
            ui::checkbox(key(), *n0, "Show Leading+Trailing TabItem()", show_leading_trailing_tabs);

            // Expose some other flags which are useful to showcase how they interact with Leading/Trailing tabs
            static ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_Reorderable | ImGuiTabBarFlags_FittingPolicyMixed;
            EditTabBarFittingPolicyFlags(*n0, &tab_bar_flags);

            Tabber tab_bar = ui::tabber(key(), *n0); // ImGui::BeginTabBar("MyTabBar", tab_bar_flags)
            {
                // Demo a Leading TabItemButton(): click the "?" button to open a menu
                static bool help_menu = false;
                if (show_leading_button)
                {
                    Widget button = ui::tab_item_button(key(), tab_bar, "?"); // ImGuiTabItemFlags_Leading | ImGuiTabItemFlags_NoTooltip
                    if (button.activated())
                        help_menu = true; // ImGui::OpenPopup("MyHelpMenu");
                    if (Widget popup = ui::begin_popup(key(), button, help_menu))
                    {
                        ui::selectable(key(), *popup, "Hello!", false);
                    }
                }

                // Demo Leading/Trailing Tabs
                if (show_leading_trailing_tabs)
                {
                    ui::tab(key(), tab_bar, "Leading"); // NULL, ImGuiTabItemFlags_Leading
                    ui::tab(key(), tab_bar, "Trailing"); // NULL, ImGuiTabItemFlags_Trailing
                }

                // Demo Trailing Tabs: click the "+" button to add a new tab.
                // (In your app you may want to use a font icon instead of the "+")
                // We submit it before the regular tabs, but thanks to the ImGuiTabItemFlags_Trailing flag it will always appear at the end.
                if (show_trailing_button)
                    if (ui::tab_item_button(key(), tab_bar, "+").activated()) // ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip
                        active_tabs.push_back(next_tab_id++); // Add new tab

                // Submit our regular tabs
                for (int i = 0; i < int(active_tabs.size()); )
                {
                    bool open = true;
                    char name[16];
                    snprintf(name, IM_COUNTOF(name), "%04d", active_tabs[i]);
                    if (Widget tab = ui::tab_item(key(active_tabs[i]), tab_bar, name, &open)) // ImGuiTabItemFlags_None
                    {
                        ui::textf(key(), *tab, "This is the %s tab!", name);
                    }

                    if (!open)
                        active_tabs.erase(active_tabs.begin() + i);
                    else
                        i++;
                }
            }
            ui::separator(key(), *n0);
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsText()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsText(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Text").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Text");
        if (Widget n0 = ui::tree_node_ex(key(), *n, "Colorful Text").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Text/Colored Text");
            // Using shortcut. You can use PushStyleColor()/PopStyleColor() for more flexibility.
            ui::text_colored(key(), *n0, Colour(1.0f, 0.0f, 1.0f, 1.0f), "Pink");
            ui::text_colored(key(), *n0, Colour(1.0f, 1.0f, 0.0f, 1.0f), "Yellow");
            Widget line = ui::row(key(), *n0);
            ui::text_disabled(key(), line, "Disabled");
            HelpMarker(line, "The TextDisabled color is stored in ImGuiStyle.");
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Font Size").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Text/Font Size");
            ImguiLook& style = ui::get_look();
            const float global_scale = style.FontScaleMain * style.FontScaleDpi;
            ui::textf(key(), *n0, "style.FontScaleMain = %0.2f", style.FontScaleMain);
            ui::textf(key(), *n0, "style.FontScaleDpi = %0.2f", style.FontScaleDpi);
            ui::textf(key(), *n0, "global_scale = ~%0.2f", global_scale); // This is not technically accurate as internal scales may apply, but conceptually let's pretend it is.
            ui::textf(key(), *n0, "FontSize = %0.2f", ui::get_font_size());

            ui::separator_text(key(), *n0, "");
            static float custom_size = 16.0f;
            ui::slider_float(key(), *n0, "custom_size", custom_size, 10.0f, 100.0f); // "%.0f");
            ui::label(key(), *n0, "ImGui::PushFont(nullptr, custom_size);");
            ui::push_font(NULL, custom_size);
            ui::textf(key(), *n0, "FontSize = %.2f (== %.2f * global_scale)", ui::get_font_size(), custom_size);
            ui::pop_font();

            ui::separator_text(key(), *n0, "");
            static float custom_scale = 1.0f;
            ui::slider_float(key(), *n0, "custom_scale", custom_scale, 0.5f, 4.0f); // "%.2f");
            ui::label(key(), *n0, "ImGui::PushFont(nullptr, style.FontSizeBase * custom_scale);");
            ui::push_font(NULL, style.FontSizeBase * custom_scale);
            ui::textf(key(), *n0, "FontSize = %.2f (== style.FontSizeBase * %.2f * global_scale)", ui::get_font_size(), custom_scale);
            ui::pop_font();

            ui::separator_text(key(), *n0, "");
            for (float scaling = 0.5f; scaling <= 4.0f; scaling += 0.5f)
            {
                ui::push_font(NULL, style.FontSizeBase * scaling);
                ui::textf(key(), *n0, "FontSize = %.2f (== style.FontSizeBase * %.2f * global_scale)", ui::get_font_size(), scaling);
                ui::pop_font();
            }
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Word Wrapping").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Text/Word Wrapping");
            // Using shortcut. You can use PushTextWrapPos()/PopTextWrapPos() for more flexibility.
            ui::text_wrapped(key(), *n0,
                "This text should automatically wrap on the edge of the window. The current implementation "
                "for text wrapping follows simple rules suitable for English and possibly other languages.");
            ui::spacing(key(), *n0);

            static float wrap_width = 200.0f;
            ui::slider_float(key(), *n0, "Wrap width", wrap_width, -20, 600); // "%.0f");

            //ImDrawList* draw_list = ImGui::GetWindowDrawList();
            for (int i = 0; i < 2; i++)
            {
                ui::textf(key(), *n0, "Test paragraph %d:", i);
                //ImVec2 pos = ImGui::GetCursorScreenPos();
                //ImVec2 marker_min = ImVec2(pos.x + wrap_width, pos.y);
                //ImVec2 marker_max = ImVec2(pos.x + wrap_width + 10, pos.y + ImGui::GetTextLineHeight());
                ui::push_text_wrap_pos(wrap_width);
                if (i == 0)
                    ui::text_wrapped(key(), *n0, ui::format("The lazy dog is a good dog. This paragraph should fit within %.0f pixels. Testing a 1 character word. The quick brown fox jumps over the lazy dog.", wrap_width));
                else
                    ui::text_wrapped(key(), *n0, "aaaaaaaa bbbbbbbb, c cccccccc,dddddddd. d eeeeeeee   ffffffff. gggggggg!hhhhhhhh");

                // Draw actual text bounding box, following by marker of our expected limit (should not overlap!)
                //draw_list->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 0, 255));
                //draw_list->AddRectFilled(marker_min, marker_max, IM_COL32(255, 0, 255, 255));
                ui::pop_text_wrap_pos();
            }
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "UTF-8 Text").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Text/UTF-8 Text");
            // UTF-8 test with Japanese characters
            // (Needs a suitable font? Try "Google Noto" or "Arial Unicode". See docs/FONTS.md for details.)
            // - From C++11 you can use the u8"my text" syntax to encode literal strings as UTF-8
            // - For earlier compiler, you may be able to encode your sources as UTF-8 (e.g. in Visual Studio, you
            //   can save your source files as 'UTF-8 without signature').
            // - FOR THIS DEMO FILE ONLY, BECAUSE WE WANT TO SUPPORT OLD COMPILERS, WE ARE *NOT* INCLUDING RAW UTF-8
            //   CHARACTERS IN THIS SOURCE FILE. Instead we are encoding a few strings with hexadecimal constants.
            //   Don't do this in your application! Please use u8"text in any language" in your application!
            // Note that characters values are preserved even by InputText() if the font cannot be displayed,
            // so you can safely copy & paste garbled characters into another application.
            ui::text_wrapped(key(), *n0,
                "CJK text will only appear if the font was loaded with the appropriate CJK character ranges. "
                "Call io.Fonts->AddFontFromFileTTF() manually to load extra character ranges. "
                "Read docs/FONTS.md for details.");
            ui::label(key(), *n0, "Hiragana: \xe3\x81\x8b\xe3\x81\x8d\xe3\x81\x8f\xe3\x81\x91\xe3\x81\x93 (kakikukeko)");
            ui::label(key(), *n0, "Kanjis: \xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e (nihongo)");
            static string buf = "\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e";
            //static char buf[32] = u8"NIHONGO"; // <- this is how you would write it with C++11, using real kanjis
            ui::input_text(key(), *n0, "UTF-8 input", buf);
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTextFilter()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsTextFilter(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Text Filter").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Text Filter");
        // Helper class to easy setup a text filter.
        // You may want to implement a more feature-full filtering scheme in your own application.
        HelpMarker(*n, "Not a widget per-se, but ImGuiTextFilter is a helper to perform simple filtering on text strings.");
        static string filter;
        ui::label(key(), *n, "Filter usage:\n"
            "  \"\"         display all lines\n"
            "  xxx        display lines containing \"xxx\"\n"
            "  xxx yyy    display lines containing \"xxx\" and \"yyy\"\n"
            "  \"xxx yyy\"  display lines containing \"xxx yyy\"\n"
            "  xxx,yyy    display lines containing \"xxx\" or \"yyy\"\n"
            "  -xxx       hide lines containing \"xxx\"");
        //ImGui::SetNextItemWidth(-FLT_MIN);
        ui::input_text_with_hint(key(), *n, "##Filter", "Filter (incl -excl)", filter);
        if (Widget child = ui::begin_child(key(), *n, vec2(-FLT_MIN, 13.f * 15))) // ImGuiChildFlags_FrameStyle
        {
            const char* lines[] = { "aaa1.c", "bbb1.c", "ccc1.c", "aaa2.cpp", "bbb2.cpp", "ccc2.cpp", "abc.h", "hello, world" };
            for (const char* item : lines)
                if (ui::filter(filter, item))
                    ui::label(key(), *child, item);
            for (const char* item : ExampleNames)
                if (ui::filter(filter, item))
                    ui::label(key(), *child, item);
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTextInput()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsTextInput(Widget parent)
{
    // To wire InputText() with std::string or any other custom string type,
    // see the "Text Input > Resize Callback" section of this demo, and the misc/cpp/imgui_stdlib.h file.
    if (Widget n = ui::tree_node_ex(key(), parent, "Text Input").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Text Input");
        if (Widget n0 = ui::tree_node_ex(key(), *n, "Multi-line Text Input").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Multi-line Text Input");
            // WE ARE USING A FIXED-SIZE BUFFER FOR SIMPLICITY HERE.
            // If you want to use InputText() with std::string or any custom dynamic string type:
            // - For std::string: use the wrapper in misc/cpp/imgui_stdlib.h/.cpp
            // - Otherwise, see the 'Dear ImGui Demo->Widgets->Text Input->Resize Callback' for using ImGuiInputTextFlags_CallbackResize.
            static string text =
                "/*\n"
                " The Pentium F00F bug, shorthand for F0 0F C7 C8,\n"
                " the hexadecimal encoding of one offending instruction,\n"
                " more formally, the invalid operand with locked CMPXCHG8B\n"
                " instruction bug, is a design flaw in the majority of\n"
                " Intel Pentium, Pentium MMX, and Pentium OverDrive\n"
                " processors (all in the P5 microarchitecture).\n"
                "*/\n\n"
                "label:\n"
                "\tlock cmpxchg8b eax\n";

            static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
            HelpMarker(*n0, "You can use the ImGuiInputTextFlags_CallbackResize facility if you need to wire InputTextMultiline() to a dynamic string type. See misc/cpp/imgui_stdlib.h for an example. (This is not demonstrated in imgui_demo.cpp because we don't want to include <string> in here)");
            ui::checkbox_flags(key(), *n0, "ImGuiInputTextFlags_ReadOnly", flags, ImGuiInputTextFlags_ReadOnly);
            { Widget line = ui::row(key(), *n0); ui::checkbox_flags(key(), line, "ImGuiInputTextFlags_WordWrap", flags, ImGuiInputTextFlags_WordWrap);
              HelpMarker(line, "Feature is currently in Beta. Please read comments in imgui.h"); }
            { Widget line = ui::row(key(), *n0); ui::checkbox_flags(key(), line, "ImGuiInputTextFlags_AllowTabInput", flags, ImGuiInputTextFlags_AllowTabInput);
              HelpMarker(line, "When _AllowTabInput is set, passing through the widget with Tabbing doesn't automatically activate it, in order to also cycling through subsequent widgets."); }
            ui::checkbox_flags(key(), *n0, "ImGuiInputTextFlags_CtrlEnterForNewLine", flags, ImGuiInputTextFlags_CtrlEnterForNewLine);
            ui::input_text_multiline(key(), *n0, "##source", text, 16, flags); // ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16)
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Filtered Text Input").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Filtered Text Input");
            struct TextFilters
            {
                // Modify character input by altering 'data->Eventchar' (ImGuiInputTextFlags_CallbackCharFilter callback)
                static int FilterCasingSwap(ui::InputTextCallbackData* data)
                {
                    if (data->EventChar >= 'a' && data->EventChar <= 'z') { data->EventChar -= 'a' - 'A'; } // Lowercase becomes uppercase
                    else if (data->EventChar >= 'A' && data->EventChar <= 'Z') { data->EventChar += 'a' - 'A'; } // Uppercase becomes lowercase
                    return 0;
                }

                // Return 0 (pass) if the character is 'i' or 'm' or 'g' or 'u' or 'i', otherwise return 1 (filter out)
                static int FilterImGuiLetters(ui::InputTextCallbackData* data)
                {
                    if (data->EventChar < 256 && strchr("imgui", (char)data->EventChar))
                        return 0;
                    return 1;
                }
            };

            static string buf1 = ""; ui::input_text(key(), *n0, "default", buf1);
            static string buf2 = ""; ui::input_text(key(), *n0, "decimal", buf2, ImGuiInputTextFlags_CharsDecimal);
            static string buf3 = ""; ui::input_text(key(), *n0, "hexadecimal", buf3, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
            static string buf4 = ""; ui::input_text(key(), *n0, "uppercase", buf4, ImGuiInputTextFlags_CharsUppercase);
            static string buf5 = ""; ui::input_text(key(), *n0, "no blank", buf5, ImGuiInputTextFlags_CharsNoBlank);
            static string buf6 = ""; ui::input_text(key(), *n0, "casing swap", buf6, ImGuiInputTextFlags_CallbackCharFilter, TextFilters::FilterCasingSwap); // Use CharFilter callback to replace characters.
            static string buf7 = ""; ui::input_text(key(), *n0, "\"imgui\"", buf7, ImGuiInputTextFlags_CallbackCharFilter, TextFilters::FilterImGuiLetters); // Use CharFilter callback to disable some characters.
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Password Input").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Password input");
            static string password = "password123";
            { Widget line = ui::row(key(), *n0); ui::input_text(key(), line, "password", password, ImGuiInputTextFlags_Password);
              HelpMarker(line, "Display all characters as '*'.\nDisable clipboard cut and copy.\nDisable logging.\n"); }
            ui::input_text_with_hint(key(), *n0, "password (w/ hint)", "<password>", password, ImGuiInputTextFlags_Password);
            ui::input_text(key(), *n0, "password (clear)", password);
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Completion, History, Edit Callbacks").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Completion, History, Edit Callbacks");
            struct Funcs
            {
                static int MyCallback(ui::InputTextCallbackData* data)
                {
                    if (data->EventFlag == ImGuiInputTextFlags_CallbackCompletion)
                    {
                        data->InsertChars(data->CursorPos, "..");
                    }
                    else if (data->EventFlag == ImGuiInputTextFlags_CallbackHistory)
                    {
                        if (data->EventKey == Key::Up)
                        {
                            data->DeleteChars(0, data->BufTextLen);
                            data->InsertChars(0, "Pressed Up!");
                            data->SelectAll();
                        }
                        else if (data->EventKey == Key::Down)
                        {
                            data->DeleteChars(0, data->BufTextLen);
                            data->InsertChars(0, "Pressed Down!");
                            data->SelectAll();
                        }
                    }
                    else if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit)
                    {
                        // Toggle casing of first character
                        char c = data->Buf[0];
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) data->Buf[0] ^= 32;
                        data->BufDirty = true;

                        // Increment a counter
                        int* p_int = (int*)data->UserData;
                        *p_int = *p_int + 1;
                    }
                    return 0;
                }
            };
            static string buf1;
            { Widget line = ui::row(key(), *n0); ui::input_text(key(), line, "Completion", buf1, ImGuiInputTextFlags_CallbackCompletion, Funcs::MyCallback);
              HelpMarker(line,
                "Here we append \"..\" each time Tab is pressed. "
                "See 'Examples>Console' for a more meaningful demonstration of using this callback."); }

            static string buf2;
            { Widget line = ui::row(key(), *n0); ui::input_text(key(), line, "History", buf2, ImGuiInputTextFlags_CallbackHistory, Funcs::MyCallback);
              HelpMarker(line,
                "Here we replace and select text each time Up/Down are pressed. "
                "See 'Examples>Console' for a more meaningful demonstration of using this callback."); }

            static string buf3;
            static int edit_count = 0;
            { Widget line = ui::row(key(), *n0); ui::input_text(key(), line, "Edit", buf3, ImGuiInputTextFlags_CallbackEdit, Funcs::MyCallback, (void*)&edit_count);
              HelpMarker(line,
                "Here we toggle the casing of the first character on every edit + count edits.");
              ui::textf(key(), line, "(%d)", edit_count); }
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Resize Callback").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Resize Callback");
            // To wire InputText() with std::string or any other custom string type,
            // you can use the ImGuiInputTextFlags_CallbackResize flag + create a custom ImGui::InputText() wrapper
            // using your preferred type. See misc/cpp/imgui_stdlib.h for an implementation of this using std::string.
            HelpMarker(*n0,
                "Using ImGuiInputTextFlags_CallbackResize to wire your custom string type to InputText().\n\n"
                "See misc/cpp/imgui_stdlib.h for an implementation of this for std::string.");
            // In two.ui, text inputs edit a string directly: there is no need for a resize callback

            // For this demo we are using ImVector as a string container.
            // Note that because we need to store a terminating zero character, our size/capacity are 1 more
            // than usually reported by a typical string class.
            static ImGuiInputTextFlags flags = ImGuiInputTextFlags_None;
            ui::checkbox_flags(key(), *n0, "ImGuiInputTextFlags_WordWrap", flags, ImGuiInputTextFlags_WordWrap);

            static string my_str;
            ui::input_text_multiline(key(), *n0, "##MyStr", my_str, 16, flags); // ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16)
            ui::textf(key(), *n0, "Data: %p\nSize: %d\nCapacity: %d", (void*)my_str.data(), int(my_str.size()), int(my_str.capacity()));
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Eliding, Alignment").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Eliding, Alignment");
            static string buf1 = "/path/to/some/folder/with/long/filename.cpp";
            static ImGuiInputTextFlags flags = ImGuiInputTextFlags_ElideLeft;
            ui::checkbox_flags(key(), *n0, "ImGuiInputTextFlags_ElideLeft", flags, ImGuiInputTextFlags_ElideLeft);
            ui::input_text(key(), *n0, "Path", buf1, flags);
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Miscellaneous").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Text Input/Miscellaneous");
            static string buf1;
            static ImGuiInputTextFlags flags = ImGuiInputTextFlags_EscapeClearsAll;
            ui::checkbox_flags(key(), *n0, "ImGuiInputTextFlags_EscapeClearsAll", flags, ImGuiInputTextFlags_EscapeClearsAll);
            ui::checkbox_flags(key(), *n0, "ImGuiInputTextFlags_ReadOnly", flags, ImGuiInputTextFlags_ReadOnly);
            ui::checkbox_flags(key(), *n0, "ImGuiInputTextFlags_NoUndoRedo", flags, ImGuiInputTextFlags_NoUndoRedo);
            ui::input_text(key(), *n0, "Hello", buf1, flags);
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTooltips()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsTooltips(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Tooltips").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Tooltips");
        // Tooltips are windows following the mouse. They do not take focus away.
        ui::separator_text(key(), *n, "General");

        // Typical use cases:
        // - Short-form (text only):      SetItemTooltip("Hello");
        // - Short-form (any contents):   if (BeginItemTooltip()) { Text("Hello"); EndTooltip(); }

        // - Full-form (text only):       if (IsItemHovered(...)) { SetTooltip("Hello"); }
        // - Full-form (any contents):    if (IsItemHovered(...) && BeginTooltip()) { Text("Hello"); EndTooltip(); }

        HelpMarker(*n,
            "Tooltip are typically created by using a IsItemHovered() + SetTooltip() sequence.\n\n"
            "We provide a helper SetItemTooltip() function to perform the two with standards flags.");

        //ImVec2 sz = ImVec2(-FLT_MIN, 0.0f);

        Widget basic = ui::button(key(), *n, "Basic"); // sz
        ui::set_item_tooltip(key(), basic, "I am a tooltip");

        Widget fancy = ui::button(key(), *n, "Fancy"); // sz
        if (Widget tooltip = ui::item_tooltip(key(), fancy))
        {
            ui::label(key(), *tooltip, "I am a fancy tooltip");
            static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
            ui::plot_lines(key(), *tooltip, "Curve", arr);
            ui::textf(key(), *tooltip, "Sin(time) = %f", sinf((float)ui::io().Time));
        }

        ui::separator_text(key(), *n, "Always On");

        // Showcase NOT relying on a IsItemHovered() to emit a tooltip.
        // Here the tooltip is always emitted when 'always_on == true'.
        static int always_on = 0;
        Widget line = ui::row(key(), *n);
        ui::radio_button(key(), line, "Off", always_on, 0);
        //ImGui::SameLine();
        ui::radio_button(key(), line, "Always On (Simple)", always_on, 1);
        //ImGui::SameLine();
        ui::radio_button(key(), line, "Always On (Advanced)", always_on, 2);
        if (always_on == 1)
            ui::set_tooltip(key(), *n, "I am following you around.");
        else if (always_on == 2)
        {
            Widget tooltip = ui::begin_tooltip(key(), *n);
            ui::progress_bar(key(), tooltip, sinf((float)ui::io().Time) * 0.5f + 0.5f, vec2(13.f * 25, 0.0f));
        }

        ui::separator_text(key(), *n, "Custom");

        HelpMarker(*n,
            "Passing ImGuiHoveredFlags_ForTooltip to IsItemHovered() is the preferred way to standardize "
            "tooltip activation details across your application. You may however decide to use custom "
            "flags for a specific tooltip instance.");

        // The following examples are passed for documentation purpose but may not be useful to most users.
        // Passing ImGuiHoveredFlags_ForTooltip to IsItemHovered() will pull ImGuiHoveredFlags flags values from
        // 'style.HoverFlagsForTooltipMouse' or 'style.HoverFlagsForTooltipNav' depending on whether mouse or keyboard/gamepad is being used.
        // With default settings, ImGuiHoveredFlags_ForTooltip is equivalent to ImGuiHoveredFlags_DelayShort + ImGuiHoveredFlags_Stationary.
        Widget manual = ui::button(key(), *n, "Manual"); // sz
        if (ui::is_item_hovered(manual, ImGuiHoveredFlags_ForTooltip))
            ui::set_tooltip(key(), manual, "I am a manually emitted tooltip.");

        Widget delay_none = ui::button(key(), *n, "DelayNone"); // sz
        if (ui::is_item_hovered(delay_none, ImGuiHoveredFlags_DelayNone))
            ui::set_tooltip(key(), delay_none, "I am a tooltip with no delay.");

        Widget delay_short = ui::button(key(), *n, "DelayShort"); // sz
        if (ui::is_item_hovered(delay_short, ImGuiHoveredFlags_DelayShort | ImGuiHoveredFlags_NoSharedDelay))
            ui::set_tooltip(key(), delay_short, ui::format("I am a tooltip with a short delay (%0.2f sec).", ui::get_look().HoverDelayShort));

        Widget delay_long = ui::button(key(), *n, "DelayLong"); // sz
        if (ui::is_item_hovered(delay_long, ImGuiHoveredFlags_DelayNormal | ImGuiHoveredFlags_NoSharedDelay))
            ui::set_tooltip(key(), delay_long, ui::format("I am a tooltip with a long delay (%0.2f sec).", ui::get_look().HoverDelayNormal));

        Widget stationary = ui::button(key(), *n, "Stationary"); // sz
        if (ui::is_item_hovered(stationary, ImGuiHoveredFlags_Stationary))
            ui::set_tooltip(key(), stationary, "I am a tooltip requiring mouse to be stationary before activating.");

        // Using ImGuiHoveredFlags_ForTooltip will pull flags from 'style.HoverFlagsForTooltipMouse' or 'style.HoverFlagsForTooltipNav',
        // which default value include the ImGuiHoveredFlags_AllowWhenDisabled flag.
        ui::begin_disabled();
        Widget disabled = ui::button(key(), *n, "Disabled item"); // sz
        disabled.enable_state(DISABLED);
        if (ui::is_item_hovered(disabled, ImGuiHoveredFlags_ForTooltip))
            ui::set_tooltip(key(), disabled, "I am a tooltip for a disabled item.");
        ui::end_disabled();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsTreeNodes()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsTreeNodes(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Tree Nodes").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Tree Nodes");
        // See see "Examples -> Property Editor" (ShowExampleAppPropertyEditor() function) for a fancier, data-driven tree.
        if (Widget n0 = ui::tree_node_ex(key(), *n, "Basic Trees").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Tree Nodes/Basic Trees");
            for (int i = 0; i < 5; i++)
            {
                // Use SetNextItemOpen() so set the default state of a node to be open. We could
                // also use TreeNodeEx() with the ImGuiTreeNodeFlags_DefaultOpen flag to achieve the same thing!
                ImGuiTreeNodeFlags flags = 0;
                if (i == 0)
                    flags |= ImGuiTreeNodeFlags_DefaultOpen; // ImGui::SetNextItemOpen(true, ImGuiCond_Once);

                // Here we use PushID() to generate a unique base ID, and then the "" used as TreeNode id won't conflict.
                // An alternative to using 'PushID() + TreeNode("", ...)' to generate a unique ID is to use 'TreeNode((void*)(intptr_t)i, ...)',
                // aka generate a dummy pointer-sized value to be hashed. The demo below uses that technique. Both are fine.
                //ImGui::PushID(i);
                if (Widget child = ui::tree_node_ex(key(i), *n0, ui::format("Child %d", i), flags).body)
                {
                    Widget line = ui::row(key(), *child);
                    ui::label(key(), line, "blah blah");
                    //ImGui::SameLine();
                    if (ui::small_button(key(), line, "button").activated()) {}
                }
                //ImGui::PopID();
            }
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Hierarchy Lines").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Tree Nodes/Hierarchy Lines");
            static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_DrawLinesFull | ImGuiTreeNodeFlags_DefaultOpen;
            HelpMarker(*n0, "Default option for DrawLinesXXX is stored in style.TreeLinesFlags");
            ui::checkbox_flags(key(), *n0, "ImGuiTreeNodeFlags_DrawLinesNone", base_flags, ImGuiTreeNodeFlags_DrawLinesNone);
            ui::checkbox_flags(key(), *n0, "ImGuiTreeNodeFlags_DrawLinesFull", base_flags, ImGuiTreeNodeFlags_DrawLinesFull);
            ui::checkbox_flags(key(), *n0, "ImGuiTreeNodeFlags_DrawLinesToNodes", base_flags, ImGuiTreeNodeFlags_DrawLinesToNodes);

            if (Widget tree = ui::tree_node_ex(key(), *n0, "Parent", base_flags).body)
            {
                if (Widget child = ui::tree_node_ex(key(), *tree, "Child 1", base_flags).body)
                {
                    ui::button(key(), *child, "Button for Child 1");
                }
                if (Widget child = ui::tree_node_ex(key(), *tree, "Child 2", base_flags).body)
                {
                    ui::button(key(), *child, "Button for Child 2");
                }
                ui::label(key(), *tree, "Remaining contents");
                ui::label(key(), *tree, "Remaining contents");
            }
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Clipping Large Trees").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Tree Nodes/Clipping Large Trees");
            ui::text_wrapped(key(), *n0,
                "- Using ImGuiListClipper with trees is a less easy than on arrays or grids.\n"
                "- Refer to 'Demo->Examples->Property Editor' for an example of how to do that.\n"
                "- Discuss in #3823");
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Selectable Nodes").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Tree Nodes/Selectable Nodes");
            HelpMarker(*n0,
                "Manually implemented selectable nodes.\n"
                "Click to select, Ctrl+Click to toggle, click on arrows or double-click to open.\n\n"
                "You may also use the multi-select API (see 'Demo->Widgets->Selection State & Multi-Select') for more advanced multi-selection features.");

            // Hold in 'selection_mask' a simple representation of what may be user-side selection state.
            // - You may retain selection state inside or outside your objects in whatever format you see fit.
            //   You may use ImGuiSelectionBasicStorage which is conceptually close to a set<> of identifiers.
            // - We record which node was clicked and then apply selection at the end of the loop.
            // - This is a manual and simplified reimplementation of multi-selection, which the full
            //   BeginMultiSelect() API implements better, but which is not trivial to wire for trees.
            static int selection_mask = 0x00;
            int node_clicked_idx = -1;
            for (int node_n = 0; node_n < 6; node_n++)
            {
                // Disable the default "open on single-click behavior" + set Selected flag according to our selection.
                // To alter selection we use if 'IsItemClicked() && !IsItemToggledOpen()', so clicking on an arrow doesn't alter selection.
                // In a BeginMultiSelect()/EndMultiSelect() we could use IsItemToggledSelection() but here we reimplement and use our own logic.
                ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
                if (selection_mask & (1 << node_n))
                    flags |= ImGuiTreeNodeFlags_Selected;

                TreeNode node = ui::tree_node_ex(key(node_n), *n0, ui::format("Selectable Node %d", node_n), flags);
                if (ui::is_item_clicked(node.header) && !ui::is_item_toggled_open(node))
                    node_clicked_idx = node_n;
                if (Widget body = node.body)
                {
                    ui::bullet(key(), *body, "<Node contents here>");
                }
            }
            if (node_clicked_idx != -1)
            {
                // Update selection state (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
                if (ui::io().KeyCtrl)
                    selection_mask ^= (1 << node_clicked_idx);          // Ctrl+Click to toggle
                else //if (!(selection_mask & (1 << node_clicked_idx))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
                    selection_mask = (1 << node_clicked_idx);           // Click to single-select
            }
        }

        if (Widget n0 = ui::tree_node_ex(key(), *n, "Advanced").body)
        {
            IMGUI_DEMO_MARKER("Widgets/Tree Nodes/Advanced");
            static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
            static bool align_label_with_current_x_position = false;
            static bool use_drag_and_drop = false;
            ui::checkbox_flags(key(), *n0, "ImGuiTreeNodeFlags_OpenOnArrow", base_flags, ImGuiTreeNodeFlags_OpenOnArrow);
            ui::checkbox_flags(key(), *n0, "ImGuiTreeNodeFlags_OpenOnDoubleClick", base_flags, ImGuiTreeNodeFlags_OpenOnDoubleClick);
            { Widget line = ui::row(key(), *n0); ui::checkbox_flags(key(), line, "ImGuiTreeNodeFlags_SpanAvailWidth", base_flags, ImGuiTreeNodeFlags_SpanAvailWidth); HelpMarker(line, "Extend hit area to all available width instead of allowing more items to be laid out after the node."); }
            ui::checkbox_flags(key(), *n0, "ImGuiTreeNodeFlags_SpanFullWidth", base_flags, ImGuiTreeNodeFlags_SpanFullWidth);
            { Widget line = ui::row(key(), *n0); ui::checkbox_flags(key(), line, "ImGuiTreeNodeFlags_SpanLabelWidth", base_flags, ImGuiTreeNodeFlags_SpanLabelWidth); HelpMarker(line, "Reduce hit area to the text label and a bit of margin."); }
            { Widget line = ui::row(key(), *n0); ui::checkbox_flags(key(), line, "ImGuiTreeNodeFlags_SpanAllColumns", base_flags, ImGuiTreeNodeFlags_SpanAllColumns); HelpMarker(line, "For use in Tables only."); }
            ui::checkbox_flags(key(), *n0, "ImGuiTreeNodeFlags_AllowOverlap", base_flags, ImGuiTreeNodeFlags_AllowOverlap);
            { Widget line = ui::row(key(), *n0); ui::checkbox_flags(key(), line, "ImGuiTreeNodeFlags_Framed", base_flags, ImGuiTreeNodeFlags_Framed); HelpMarker(line, "Draw frame with background (e.g. for CollapsingHeader)"); }
            ui::checkbox_flags(key(), *n0, "ImGuiTreeNodeFlags_FramePadding", base_flags, ImGuiTreeNodeFlags_FramePadding);
            ui::checkbox_flags(key(), *n0, "ImGuiTreeNodeFlags_NavLeftJumpsToParent", base_flags, ImGuiTreeNodeFlags_NavLeftJumpsToParent);

            HelpMarker(*n0, "Default option for DrawLinesXXX is stored in style.TreeLinesFlags");
            ui::checkbox_flags(key(), *n0, "ImGuiTreeNodeFlags_DrawLinesNone", base_flags, ImGuiTreeNodeFlags_DrawLinesNone);
            ui::checkbox_flags(key(), *n0, "ImGuiTreeNodeFlags_DrawLinesFull", base_flags, ImGuiTreeNodeFlags_DrawLinesFull);
            ui::checkbox_flags(key(), *n0, "ImGuiTreeNodeFlags_DrawLinesToNodes", base_flags, ImGuiTreeNodeFlags_DrawLinesToNodes);

            ui::checkbox(key(), *n0, "Align label with current X position", align_label_with_current_x_position);
            ui::checkbox(key(), *n0, "Make Tree Nodes as drag & drop sources", use_drag_and_drop);
            //if (align_label_with_current_x_position)
            //    ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

            for (int node_n = 0; node_n < 6; node_n++)
            {
                ImGuiTreeNodeFlags node_flags = base_flags;
                if (node_n < 3)
                {
                    // Items 0..2 are Tree Node
                    TreeNode node = ui::tree_node_ex(key(node_n), *n0, ui::format("Selectable Node %d", node_n), node_flags);
                    if (use_drag_and_drop)
                        if (Widget source = ui::begin_drag_drop_source(key(), node.header))
                        {
                            ui::set_drag_drop_payload(node.header, "MY_TREENODE_PAYLOAD_TYPE", NULL, 0);
                            ui::label(key(), *source, "This is a drag and drop source");
                        }
                    if (node_n == 2 && (base_flags & ImGuiTreeNodeFlags_SpanLabelWidth))
                    {
                        // Item 2 has an additional inline button to help demonstrate SpanLabelWidth.
                        //ImGui::SameLine();
                        if (ui::small_button(key(), node.header, "button").activated()) {}
                    }
                    if (Widget body = node.body)
                    {
                        Widget line = ui::row(key(), *body);
                        ui::bullet(key(), line, "Blah blah\nBlah Blah");
                        //ImGui::SameLine();
                        ui::small_button(key(), line, "Button");
                    }
                }
                else
                {
                    // Items 3..5 are Tree Leaves
                    // The only reason we use TreeNode at all is to allow selection of the leaf. Otherwise we can
                    // use BulletText() or advance the cursor by GetTreeNodeToLabelSpacing() and call Text().
                    node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
                    TreeNode node = ui::tree_node_ex(key(node_n), *n0, ui::format("Selectable Leaf %d", node_n), node_flags);
                    if (use_drag_and_drop)
                        if (Widget source = ui::begin_drag_drop_source(key(), node.header))
                        {
                            ui::set_drag_drop_payload(node.header, "MY_TREENODE_PAYLOAD_TYPE", NULL, 0);
                            ui::label(key(), *source, "This is a drag and drop source");
                        }
                }
            }
            //if (align_label_with_current_x_position)
            //    ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgetsVerticalSliders()
//-----------------------------------------------------------------------------

static void DemoWindowWidgetsVerticalSliders(Widget parent)
{
    if (Widget n = ui::tree_node_ex(key(), parent, "Vertical Sliders").body)
    {
        IMGUI_DEMO_MARKER("Widgets/Vertical Sliders");
        const float spacing = 4;
        ui::push_style_var(ImGuiStyleVar_ItemSpacing, vec2(spacing, spacing));

        Widget line = ui::row(key(), *n);
        static int int_value = 0;
        ui::v_slider_int(key(), line, vec2(18, 160), int_value, 0, 5);
        //ImGui::SameLine();

        static float values[7] = { 0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f };
        //ImGui::PushID("set1");
        static Style frames[7];
        for (int i = 0; i < 7; i++)
        {
            //if (i > 0) ImGui::SameLine();
            //ImGui::PushID(i);
            //ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(i / 7.0f, 0.5f, 0.5f));
            //ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.5f));
            //ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.5f));
            //ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(i / 7.0f, 0.9f, 0.9f));
            Widget slider = ui::v_slider_float(key(i), line, vec2(18, 160), values[i], 0.0f, 1.0f); // "");
            if (ui::is_item_active(slider) || ui::is_item_hovered(slider))
                ui::set_tooltip(key(), slider, ui::format("%.3f", values[i]));
            //ImGui::PopStyleColor(4);
            //ImGui::PopID();
        }
        //ImGui::PopID();

        //ImGui::SameLine();
        //ImGui::PushID("set2");
        static float values2[4] = { 0.20f, 0.80f, 0.40f, 0.25f };
        const int rows = 3;
        const vec2 small_slider_size(18, (float)(int)((160.0f - (rows - 1) * spacing) / rows));
        for (int nx = 0; nx < 4; nx++)
        {
            //if (nx > 0) ImGui::SameLine();
            Widget group = ui::stack(key(nx), line); // ImGui::BeginGroup();
            for (int ny = 0; ny < rows; ny++)
            {
                //ImGui::PushID(nx * rows + ny);
                Widget slider = ui::v_slider_float(key(ny), group, small_slider_size, values2[nx], 0.0f, 1.0f); // "");
                if (ui::is_item_active(slider) || ui::is_item_hovered(slider))
                    ui::set_tooltip(key(), slider, ui::format("%.3f", values2[nx]));
                //ImGui::PopID();
            }
            //ImGui::EndGroup();
        }
        //ImGui::PopID();

        //ImGui::SameLine();
        //ImGui::PushID("set3");
        for (int i = 0; i < 4; i++)
        {
            //if (i > 0) ImGui::SameLine();
            //ImGui::PushID(i);
            ui::push_style_var(ImGuiStyleVar_GrabMinSize, 40);
            ui::v_slider_float(key(i), line, vec2(40, 160), values[i], 0.0f, 1.0f); // "%.2f\nsec");
            ui::pop_style_var();
            //ImGui::PopID();
        }
        //ImGui::PopID();
        ui::pop_style_var();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowWidgets()
//-----------------------------------------------------------------------------

static void DemoWindowWidgets(Widget parent, ImGuiDemoWindowData* demo_data)
{
    //ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    Widget body = ui::collapsing_header(key(), parent, "Widgets");
    if (!body)
        return;
    // IMGUI_DEMO_MARKER("Widgets");

    const bool disable_all = demo_data->DisableSections; // The Checkbox for that is inside the "Disabled" section at the bottom
    const bool override_liveedit = demo_data->LiveEditOverride;
    if (disable_all)
        ui::begin_disabled();
    if (override_liveedit)
    {
        ui::push_item_flag(ImGuiItemFlags_LiveEditOnInputText, (demo_data->LiveEditFlags & ImGuiItemFlags_LiveEditOnInputText) != 0);
        ui::push_item_flag(ImGuiItemFlags_LiveEditOnInputScalar, (demo_data->LiveEditFlags & ImGuiItemFlags_LiveEditOnInputScalar) != 0);
    }

    DemoWindowWidgetsBasic(*body);
    DemoWindowWidgetsBullets(*body);
    DemoWindowWidgetsCollapsingHeaders(*body);
    DemoWindowWidgetsComboBoxes(*body);
    DemoWindowWidgetsColorAndPickers(*body);
    DemoWindowWidgetsDataTypes(*body);

    if (disable_all)
        ui::end_disabled();
    DemoWindowWidgetsDisableBlocks(*body, demo_data);
    if (disable_all)
        ui::begin_disabled();

    DemoWindowWidgetsDragAndDrop(*body);
    DemoWindowWidgetsDragsAndSliders(*body);
    DemoWindowWidgetsFonts(*body);
    DemoWindowWidgetsImages(*body);
    DemoWindowWidgetsListBoxes(*body);
    DemoWindowWidgetsLiveEdit(*body, demo_data);
    DemoWindowWidgetsMixedValues(*body);
    DemoWindowWidgetsMultiComponents(*body);
    DemoWindowWidgetsPlotting(*body);
    DemoWindowWidgetsProgressBars(*body);
    DemoWindowWidgetsQueryingStatuses(*body);
    DemoWindowWidgetsSelectables(*body);
    DemoWindowWidgetsSelectionAndMultiSelect(*body, demo_data);
    DemoWindowWidgetsTabs(*body);
    DemoWindowWidgetsText(*body);
    DemoWindowWidgetsTextFilter(*body);
    DemoWindowWidgetsTextInput(*body);
    DemoWindowWidgetsTooltips(*body);
    DemoWindowWidgetsTreeNodes(*body);
    DemoWindowWidgetsVerticalSliders(*body);

    if (override_liveedit)
    {
        ui::pop_item_flag();
        ui::pop_item_flag();
    }
    if (disable_all)
        ui::end_disabled();
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowLayout()
//-----------------------------------------------------------------------------

static void DemoWindowLayout(Widget parent)
{
    Widget body = ui::collapsing_header(key(), parent, "Layout & Scrolling");
    if (!body)
        return;

    if (Widget n = ui::tree_node_ex(key(), *body, "Child windows").body)
    {
        IMGUI_DEMO_MARKER("Layout/Child windows");
        ui::separator_text(key(), *n, "Child windows");

        HelpMarker(*n, "Use child windows to begin into a self-contained independent scrolling/clipping regions within a host window.");
        static bool disable_mouse_wheel = false;
        static bool disable_menu = false;
        ui::checkbox(key(), *n, "Disable Mouse Wheel", disable_mouse_wheel);
        ui::checkbox(key(), *n, "Disable Menu", disable_menu);

        Widget line = ui::row(key(), *n);
        // Child 1: no border, enable horizontal scrollbar
        {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
            if (disable_mouse_wheel)
                window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
            if (Widget child = ui::begin_child(key(), line, vec2(ui::get_content_region_avail(line).x * 0.5f, 260), false, window_flags))
                for (int i = 0; i < 100; i++)
                    ui::textf(key(), *child, "%04d: scrollable region", i);
        }

        //ImGui::SameLine();

        // Child 2: rounded border
        {
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
            if (disable_mouse_wheel)
                window_flags |= ImGuiWindowFlags_NoScrollWithMouse;
            if (!disable_menu)
                window_flags |= ImGuiWindowFlags_MenuBar;
            ui::push_style_var(ImGuiStyleVar_ChildRounding, 5.0f);
            if (Widget child = ui::begin_child(key(), line, vec2(0, 260), true, window_flags))
            {
                if (!disable_menu)
                {
                    Widget menubar = ui::menubar(key(), *child);
                    if (Widget menu = ui::begin_menu(key(), menubar, "Menu"))
                    {
                        ShowExampleMenuFile(*menu);
                    }
                }
                ui::TableLayout table = ui::begin_table(key(), *child, 2); // ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings
                {
                    for (int i = 0; i < 100; i++)
                    {
                        char buf[32];
                        sprintf(buf, "%03d", i);
                        ui::button(key(), table.next_column(), buf); // ImVec2(-FLT_MIN, 0.0f)
                    }
                }
            }
            ui::pop_style_var();
        }

        // Child 3: manual-resize
        ui::separator_text(key(), *n, "Manual-resize");
        {
            HelpMarker(*n, "Drag bottom border to resize. Double-click bottom border to auto-fit to vertical contents.");
            //if (ImGui::Button("Set Height to 200"))
            //    ImGui::SetNextWindowSize(ImVec2(-FLT_MIN, 200.0f));

            //ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_FrameBg));
            if (Widget child = ui::begin_child(key(), *n, vec2(-FLT_MIN, 17.f * 8), true)) // ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeY
                for (int i = 0; i < 10; i++)
                    ui::textf(key(), *child, "Line %04d", i);
            //ImGui::PopStyleColor();
        }

        // Child 4: auto-resizing height with a limit
        ui::separator_text(key(), *n, "Auto-resize with constraints");
        {
            static int draw_lines = 3;
            static int max_height_in_lines = 10;
            //ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
            ui::drag_int(key(), *n, "Lines Count", draw_lines, 0.2f);
            //ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
            ui::drag_int(key(), *n, "Max Height (in Lines)", max_height_in_lines, 0.2f);

            //ImGui::SetNextWindowSizeConstraints(ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 1), ImVec2(FLT_MAX, ImGui::GetTextLineHeightWithSpacing() * max_height_in_lines));
            if (Widget child = ui::begin_child(key(), *n, vec2(-FLT_MIN, 0.0f), true)) // ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY
                for (int i = 0; i < draw_lines; i++)
                    ui::textf(key(), *child, "Line %04d", i);
        }

        ui::separator_text(key(), *n, "Misc/Advanced");

        // Demonstrate a few extra things
        // - Changing ImGuiCol_ChildBg (which is transparent black in default styles)
        // - Using SetCursorPos() to position child window (the child window is an item from the POV of parent window)
        //   You can also call SetNextWindowPos() to position the child window. The parent window will effectively
        //   layout from this position.
        // - Using ImGui::GetItemRectMin/Max() to query the "item" state (because the child window is an item from
        //   the POV of the parent window). See 'Demo->Querying Status (Edited/Active/Hovered etc.)' for details.
        {
            static int offset_x = 0;
            static bool override_bg_color = true;
            static ImGuiChildFlags child_flags = ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX | ImGuiChildFlags_ResizeY;
            //ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
            ui::drag_int(key(), *n, "Offset X", offset_x, 1.0f, -1000, 1000);
            ui::checkbox(key(), *n, "Override ChildBg color", override_bg_color);
            ui::checkbox_flags(key(), *n, "ImGuiChildFlags_Borders", child_flags, ImGuiChildFlags_Borders);
            ui::checkbox_flags(key(), *n, "ImGuiChildFlags_AlwaysUseWindowPadding", child_flags, ImGuiChildFlags_AlwaysUseWindowPadding);
            ui::checkbox_flags(key(), *n, "ImGuiChildFlags_ResizeX", child_flags, ImGuiChildFlags_ResizeX);
            ui::checkbox_flags(key(), *n, "ImGuiChildFlags_ResizeY", child_flags, ImGuiChildFlags_ResizeY);
            { Widget flags_line = ui::row(key(), *n); ui::checkbox_flags(key(), flags_line, "ImGuiChildFlags_FrameStyle", child_flags, ImGuiChildFlags_FrameStyle);
              HelpMarker(flags_line, "Style the child window like a framed item: use FrameBg, FrameRounding, FrameBorderSize, FramePadding instead of ChildBg, ChildRounding, ChildBorderSize, WindowPadding."); }
            if (child_flags & ImGuiChildFlags_FrameStyle)
                override_bg_color = false;

            //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (float)offset_x);
            //if (override_bg_color)
            //    ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(255, 0, 0, 100));
            Widget child = ui::begin_child(key(), *n, vec2(200, 100), (child_flags & ImGuiChildFlags_Borders) != 0); // child_flags, ImGuiWindowFlags_None);
            //if (override_bg_color)
            //    ImGui::PopStyleColor();

            for (int i = 0; i < 50; i++)
                ui::textf(key(), *child, "Some test %d", i);
            bool child_is_hovered = ui::is_item_hovered(*child);
            vec2 child_rect_min = ui::get_item_rect_min(*child);
            vec2 child_rect_max = ui::get_item_rect_max(*child);
            ui::textf(key(), *n, "Hovered: %d", child_is_hovered);
            ui::textf(key(), *n, "Rect of child window is: (%.0f,%.0f) (%.0f,%.0f)", child_rect_min.x, child_rect_min.y, child_rect_max.x, child_rect_max.y);
        }
    }

    if (Widget n = ui::tree_node_ex(key(), *body, "Widgets Width").body)
    {
        IMGUI_DEMO_MARKER("Layout/Widgets Width");
        static float f = 0.0f;
        static bool show_indented_items = true;
        ui::checkbox(key(), *n, "Show indented items", show_indented_items);

        // Use SetNextItemWidth() to set the width of a single upcoming item.
        // Use PushItemWidth()/PopItemWidth() to set the width of a group of items.
        // In real code use you'll probably want to choose width values that are proportional to your font size
        // e.g. Using '20.0f * GetFontSize()' as width instead of '200.0f', etc.

        { Widget line = ui::row(key(), *n); ui::label(key(), line, "SetNextItemWidth/PushItemWidth(100)");
          HelpMarker(line, "Fixed width."); }
        ui::push_item_width(100);
        ui::drag_float(key(), *n, "float##1b", f);
        if (show_indented_items)
        {
            Widget indent = ui::indent(key(), *n);
            ui::drag_float(key(), indent, "float (indented)##1b", f);
        }
        ui::pop_item_width();

        { Widget line = ui::row(key(), *n); ui::label(key(), line, "SetNextItemWidth/PushItemWidth(-100)");
          HelpMarker(line, "Align to right edge minus 100"); }
        ui::push_item_width(-100);
        ui::drag_float(key(), *n, "float##2a", f);
        if (show_indented_items)
        {
            Widget indent = ui::indent(key(), *n);
            ui::drag_float(key(), indent, "float (indented)##2b", f);
        }
        ui::pop_item_width();

        { Widget line = ui::row(key(), *n); ui::label(key(), line, "SetNextItemWidth/PushItemWidth(GetContentRegionAvail().x * 0.5f)");
          HelpMarker(line, "Half of available width.\n(~ right-cursor_pos)\n(works within a column set)"); }
        ui::push_item_width(ui::get_content_region_avail(*n).x * 0.5f);
        ui::drag_float(key(), *n, "float##3a", f);
        if (show_indented_items)
        {
            Widget indent = ui::indent(key(), *n);
            ui::drag_float(key(), indent, "float (indented)##3b", f);
        }
        ui::pop_item_width();

        { Widget line = ui::row(key(), *n); ui::label(key(), line, "SetNextItemWidth/PushItemWidth(-GetContentRegionAvail().x * 0.5f)");
          HelpMarker(line, "Align to right edge minus half"); }
        ui::push_item_width(-ui::get_content_region_avail(*n).x * 0.5f);
        ui::drag_float(key(), *n, "float##4a", f);
        if (show_indented_items)
        {
            Widget indent = ui::indent(key(), *n);
            ui::drag_float(key(), indent, "float (indented)##4b", f);
        }
        ui::pop_item_width();

        ui::label(key(), *n, "SetNextItemWidth/PushItemWidth(-Min(GetContentRegionAvail().x * 0.40f, GetFontSize() * 12))");
        ui::push_item_width(-IM_MIN(ui::get_font_size() * 12, ui::get_content_region_avail(*n).x * 0.40f));
        ui::drag_float(key(), *n, "float##5a", f);
        if (show_indented_items)
        {
            Widget indent = ui::indent(key(), *n);
            ui::drag_float(key(), indent, "float (indented)##5b", f);
        }
        ui::pop_item_width();

        // Demonstrate using PushItemWidth to surround three items.
        // Calling SetNextItemWidth() before each of them would have the same effect.
        { Widget line = ui::row(key(), *n); ui::label(key(), line, "SetNextItemWidth/PushItemWidth(-FLT_MIN)");
          HelpMarker(line, "Align to right edge"); }
        ui::push_item_width(-FLT_MIN);
        ui::drag_float(key(), *n, "##float6a", f);
        if (show_indented_items)
        {
            Widget indent = ui::indent(key(), *n);
            ui::drag_float(key(), indent, "float (indented)##6b", f);
        }
        ui::pop_item_width();
    }

    if (Widget n = ui::tree_node_ex(key(), *body, "Basic Horizontal Layout").body)
    {
        IMGUI_DEMO_MARKER("Layout/Basic Horizontal Layout");
        ui::text_wrapped(key(), *n, "(Use ImGui::SameLine() to keep adding items to the right of the preceding item)");

        // Text
        IMGUI_DEMO_MARKER("Layout/Basic Horizontal Layout/SameLine");
        { Widget line = ui::row(key(), *n); ui::label(key(), line, "Two items: Hello"); //ImGui::SameLine();
          ui::text_colored(key(), line, Colour(1, 1, 0, 1), "Sailor"); }

        // Adjust spacing
        { Widget line = ui::row(key(), *n); ui::label(key(), line, "More spacing: Hello"); ui::same_line_spacing(key(), line, 20); //ImGui::SameLine(0, 20);
          ui::text_colored(key(), line, Colour(1, 1, 0, 1), "Sailor"); }

        // Button
        //ImGui::AlignTextToFramePadding();
        { Widget line = ui::row(key(), *n); ui::label(key(), line, "Normal buttons"); //ImGui::SameLine();
          ui::button(key(), line, "Banana"); //ImGui::SameLine();
          ui::button(key(), line, "Apple"); //ImGui::SameLine();
          ui::button(key(), line, "Corniflower"); }

        // Button
        { Widget line = ui::row(key(), *n); ui::label(key(), line, "Small buttons"); //ImGui::SameLine();
          ui::small_button(key(), line, "Like this one"); //ImGui::SameLine();
          ui::label(key(), line, "can fit within a text block."); }

        // Aligned to arbitrary position. Easy/cheap column.
        IMGUI_DEMO_MARKER("Layout/Basic Horizontal Layout/SameLine (with offset)");
        { Widget line = ui::row(key(), *n); ui::label(key(), line, "Aligned");
          ui::same_line_offset(key(), line, 150); ui::label(key(), line, "x=150");
          ui::same_line_offset(key(), line, 300); ui::label(key(), line, "x=300"); }
        { Widget line = ui::row(key(), *n); ui::label(key(), line, "Aligned");
          ui::same_line_offset(key(), line, 150); ui::small_button(key(), line, "x=150");
          ui::same_line_offset(key(), line, 300); ui::small_button(key(), line, "x=300"); }

        // Checkbox
        IMGUI_DEMO_MARKER("Layout/Basic Horizontal Layout/SameLine (more)");
        static bool c1 = false, c2 = false, c3 = false, c4 = false;
        { Widget line = ui::row(key(), *n); ui::checkbox(key(), line, "My", c1); //ImGui::SameLine();
          ui::checkbox(key(), line, "Tailor", c2); //ImGui::SameLine();
          ui::checkbox(key(), line, "Is", c3); //ImGui::SameLine();
          ui::checkbox(key(), line, "Rich", c4); }

        // Various
        static float f0 = 1.0f, f1 = 2.0f, f2 = 3.0f;
        ui::push_item_width(ui::calc_text_size("AAAAAAA").x);
        const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD" };
        static int item = -1;
        { Widget line = ui::row(key(), *n); ui::combo(key(), line, "Combo", item, items); //ImGui::SameLine();
          ui::slider_float(key(), line, "X", f0, 0.0f, 5.0f); //ImGui::SameLine();
          ui::slider_float(key(), line, "Y", f1, 0.0f, 5.0f); //ImGui::SameLine();
          ui::slider_float(key(), line, "Z", f2, 0.0f, 5.0f); }

        ui::label(key(), *n, "Lists:");
        static int selection[4] = { 0, 1, 2, 3 };
        Widget lists = ui::row(key(), *n);
        for (int i = 0; i < 4; i++)
        {
            //if (i > 0) ImGui::SameLine();
            //ImGui::PushID(i);
            ui::list_box(key(i), lists, "", selection[i], items);
            //ImGui::PopID();
            //ImGui::SetItemTooltip("ListBox %d hovered", i);
        }
        ui::pop_item_width();

        // Dummy
        IMGUI_DEMO_MARKER("Layout/Basic Horizontal Layout/Dummy");
        vec2 button_sz(40, 40);
        { Widget line = ui::row(key(), *n); ui::button(key(), line, "A", button_sz); //ImGui::SameLine();
          ui::dummy(key(), line, button_sz); //ImGui::SameLine();
          ui::button(key(), line, "B", button_sz); }

        // Manually wrapping
        // (we should eventually provide this as an automatic layout feature, but for now you can do it manually)
        IMGUI_DEMO_MARKER("Layout/Basic Horizontal Layout/Manual wrapping");
        ui::label(key(), *n, "Manual wrapping:");
        ImguiLook& style = ui::get_look();
        int buttons_count = 20;
        float window_visible_x2 = ui::get_content_region_avail(*n).x;
        Widget wrap_line = ui::row(key(), *n);
        float last_button_x2 = 0.f;
        for (int i = 0; i < buttons_count; i++)
        {
            //ImGui::PushID(i);
            ui::button(key(i), *wrap_line, "Box", button_sz);
            last_button_x2 += style.ItemSpacing.x + button_sz.x; // ImGui::GetItemRectMax().x;
            float next_button_x2 = last_button_x2 + style.ItemSpacing.x + button_sz.x; // Expected position if next button was on same line
            if (i + 1 < buttons_count && next_button_x2 >= window_visible_x2)
            {
                wrap_line = ui::row(key(i), *n); //ImGui::SameLine();
                last_button_x2 = 0.f;
            }
            //ImGui::PopID();
        }
    }

    if (Widget n = ui::tree_node_ex(key(), *body, "Groups").body)
    {
        IMGUI_DEMO_MARKER("Layout/Groups");
        HelpMarker(*n,
            "BeginGroup() basically locks the horizontal position for new line. "
            "EndGroup() bundles the whole group so that you can use \"item\" functions such as "
            "IsItemHovered()/IsItemActive() or SameLine() etc. on the whole group.");
        Widget line = ui::row(key(), *n);
        Widget group0 = ui::stack(key(), line); // ImGui::BeginGroup();
        {
            Widget group1 = ui::row(key(), group0); // ImGui::BeginGroup();
            ui::button(key(), group1, "AAA");
            //ImGui::SameLine();
            ui::button(key(), group1, "BBB");
            //ImGui::SameLine();
            Widget group2 = ui::stack(key(), group1); // ImGui::BeginGroup();
            ui::button(key(), group2, "CCC");
            ui::button(key(), group2, "DDD");
            //ImGui::EndGroup();
            //ImGui::SameLine();
            ui::button(key(), group1, "EEE");
            //ImGui::EndGroup();
            ui::set_item_tooltip(key(), group1, "First group hovered");
        }
        // Capture the group size and create widgets using the same size
        vec2 size = ui::get_item_rect_size(group0.child(0));
        static float values[5] = { 0.5f, 0.20f, 0.80f, 0.60f, 0.25f };
        ui::plot_histogram(key(), group0, "##values", values, 0, NULL, 0.0f, 1.0f, size);

        Widget actions = ui::row(key(), group0);
        ui::button(key(), actions, "ACTION", vec2((size.x - ui::get_look().ItemSpacing.x) * 0.5f, size.y));
        //ImGui::SameLine();
        ui::button(key(), actions, "REACTION", vec2((size.x - ui::get_look().ItemSpacing.x) * 0.5f, size.y));
        //ImGui::EndGroup();
        //ImGui::SameLine();

        ui::button(key(), line, "LEVERAGE\nBUZZWORD", size);
        //ImGui::SameLine();

        if (Widget list = ui::begin_list_box(key(), line, "List")) // size
        {
            ui::selectable(key(), *list, "Selected", true);
            ui::selectable(key(), *list, "Not Selected", false);
        }
    }

    if (Widget n = ui::tree_node_ex(key(), *body, "Text Baseline Alignment").body)
    {
        IMGUI_DEMO_MARKER("Layout/Text Baseline Alignment");
        {
            { Widget line = ui::row(key(), *n); ui::bullet(key(), line, "Text baseline:");
              HelpMarker(line,
                "This is testing the vertical alignment that gets applied on text to keep it aligned with widgets. "
                "Lines only composed of text or \"small\" widgets use less vertical space than lines with framed widgets."); }
            Widget indent = ui::indent(key(), *n); // ImGui::Indent();

            { Widget line = ui::row(key(), indent); ui::label(key(), line, "KO Blahblah"); //ImGui::SameLine();
              ui::button(key(), line, "Some framed item"); //ImGui::SameLine();
              HelpMarker(line, "Baseline of button will look misaligned with text.."); }

            // If your line starts with text, call AlignTextToFramePadding() to align text to upcoming widgets.
            // (because we don't know what's coming after the Text() statement, we need to move the text baseline
            // down by FramePadding.y ahead of time)
            //ImGui::AlignTextToFramePadding();
            { Widget line = ui::row(key(), indent); ui::label(key(), line, "OK Blahblah"); //ImGui::SameLine();
              ui::button(key(), line, "Some framed item##2"); //ImGui::SameLine();
              HelpMarker(line, "We call AlignTextToFramePadding() to vertically align the text baseline by +FramePadding.y"); }

            // SmallButton() uses the same vertical padding as Text
            { Widget line = ui::row(key(), indent); ui::button(key(), line, "TEST##1"); //ImGui::SameLine();
              ui::label(key(), line, "TEST"); //ImGui::SameLine();
              ui::small_button(key(), line, "TEST##2"); }

            // If your line starts with text, call AlignTextToFramePadding() to align text to upcoming widgets.
            //ImGui::AlignTextToFramePadding();
            { Widget line = ui::row(key(), indent); ui::label(key(), line, "Text aligned to framed item"); //ImGui::SameLine();
              ui::button(key(), line, "Item##1"); //ImGui::SameLine();
              ui::label(key(), line, "Item"); //ImGui::SameLine();
              ui::small_button(key(), line, "Item##2"); //ImGui::SameLine();
              ui::button(key(), line, "Item##3"); }

            //ImGui::Unindent();
        }

        ui::spacing(key(), *n);

        {
            ui::bullet(key(), *n, "Multi-line text:");
            Widget indent = ui::indent(key(), *n); // ImGui::Indent();
            { Widget line = ui::row(key(), indent); ui::label(key(), line, "One\nTwo\nThree"); //ImGui::SameLine();
              ui::label(key(), line, "Hello\nWorld"); //ImGui::SameLine();
              ui::label(key(), line, "Banana"); }

            { Widget line = ui::row(key(), indent); ui::label(key(), line, "Banana"); //ImGui::SameLine();
              ui::label(key(), line, "Hello\nWorld"); //ImGui::SameLine();
              ui::label(key(), line, "One\nTwo\nThree"); }

            { Widget line = ui::row(key(), indent); ui::button(key(), line, "HOP##1"); //ImGui::SameLine();
              ui::label(key(), line, "Banana"); //ImGui::SameLine();
              ui::label(key(), line, "Hello\nWorld"); //ImGui::SameLine();
              ui::label(key(), line, "Banana"); }

            { Widget line = ui::row(key(), indent); ui::button(key(), line, "HOP##2"); //ImGui::SameLine();
              ui::label(key(), line, "Hello\nWorld"); //ImGui::SameLine();
              ui::label(key(), line, "Banana"); }
            //ImGui::Unindent();
        }

        ui::spacing(key(), *n);

        {
            ui::bullet(key(), *n, "Misc items:");
            Widget indent = ui::indent(key(), *n); // ImGui::Indent();

            // SmallButton() sets FramePadding to zero. Text baseline is aligned to match baseline of previous Button.
            { Widget line = ui::row(key(), indent); ui::button(key(), line, "80x80", vec2(80, 80));
              //ImGui::SameLine();
              ui::button(key(), line, "50x50", vec2(50, 50));
              //ImGui::SameLine();
              ui::button(key(), line, "Button()");
              //ImGui::SameLine();
              ui::small_button(key(), line, "SmallButton()"); }

            // Tree
            // (here the node appears after a button and has odd intent, so we use ImGuiTreeNodeFlags_DrawLinesNone to disable hierarchy outline)
            //const float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
            { Widget line = ui::row(key(), indent); ui::button(key(), line, "Button##1"); // Will make line higher
              //ImGui::SameLine(0.0f, spacing);
              if (Widget node = ui::tree_node_ex(key(), line, "Node##1", ImGuiTreeNodeFlags_DrawLinesNone).body)
              {
                  // Placeholder tree data
                  for (int i = 0; i < 6; i++)
                      ui::bullet(key(), *node, ui::format("Item %d..", i));
              } }

            //const float padding = (float)(int)(ImGui::GetFontSize() * 1.20f); // Large padding
            { Widget line = ui::row(key(), indent);
              //ImGui::PushStyleVarY(ImGuiStyleVar_FramePadding, padding);
              ui::button(key(), line, "Button##2");
              //ImGui::PopStyleVar();
              //ImGui::SameLine(0.0f, spacing);
              ui::tree_node_ex(key(), line, "Node##2", ImGuiTreeNodeFlags_DrawLinesNone); }

            // Vertically align text node a bit lower so it'll be vertically centered with upcoming widget.
            // Otherwise you can use SmallButton() (smaller fit).
            //ImGui::AlignTextToFramePadding();

            // Common mistake to avoid: if we want to SameLine after TreeNode we need to do it before we add
            // other contents "inside" the node.
            TreeNode node3 = ui::tree_node_ex(key(), indent, "Node##3");
            //ImGui::SameLine(0.0f, spacing);
            ui::button(key(), node3.header, "Button##3");
            if (Widget node = node3.body)
            {
                // Placeholder tree data
                for (int i = 0; i < 6; i++)
                    ui::bullet(key(), *node, ui::format("Item %d..", i));
            }

            // Bullet
            { Widget line = ui::row(key(), indent); ui::button(key(), line, "Button##4");
              //ImGui::SameLine(0.0f, spacing);
              ui::bullet(key(), line, "Bullet text"); }

            //ImGui::AlignTextToFramePadding();
            { Widget line = ui::row(key(), indent); ui::bullet(key(), line, "Node");
              //ImGui::SameLine(0.0f, spacing);
              ui::button(key(), line, "Button##5"); }
            //ImGui::Unindent();
        }
    }

    if (Widget n = ui::tree_node_ex(key(), *body, "Scrolling").body)
    {
        IMGUI_DEMO_MARKER("Layout/Scrolling/Vertical");
        // Vertical scroll functions
        HelpMarker(*n, "Use SetScrollHereY() or SetScrollFromPosY() to scroll to a given vertical position.");

        static int track_item = 50;
        static bool enable_track = true;
        static bool enable_extra_decorations = false;
        static float scroll_to_off_px = 0.0f;
        static float scroll_to_pos_px = 200.0f;

        ui::checkbox(key(), *n, "Decoration", enable_extra_decorations);

        ui::push_item_width(ui::get_font_size() * 10);
        Widget line0 = ui::row(key(), *n);
        enable_track |= ui::drag_int(key(), line0, "##item", track_item, 0.25f, 0, 99); // "Item = %d");
        //ImGui::SameLine();
        ui::checkbox(key(), line0, "Track", enable_track);

        Widget line1 = ui::row(key(), *n);
        bool scroll_to_off = ui::drag_float(key(), line1, "##off", scroll_to_off_px, 1.00f, 0, FLT_MAX); // "+%.0f px");
        //ImGui::SameLine();
        scroll_to_off |= ui::button(key(), line1, "Scroll Offset").activated();

        Widget line2 = ui::row(key(), *n);
        bool scroll_to_pos = ui::drag_float(key(), line2, "##pos", scroll_to_pos_px, 1.00f, -10, FLT_MAX); // "X/Y = %.0f px");
        //ImGui::SameLine();
        scroll_to_pos |= ui::button(key(), line2, "Scroll To Pos").activated();
        ui::pop_item_width();

        if (scroll_to_off || scroll_to_pos)
            enable_track = false;

        ImguiLook& style = ui::get_look();
        float child_w = (ui::get_content_region_avail(*n).x - 4 * style.ItemSpacing.x) / 5;
        if (child_w < 1.0f)
            child_w = 1.0f;
        //ImGui::PushID("##VerticalScrolling");
        Widget vertical = ui::row(key(), *n);
        for (int i = 0; i < 5; i++)
        {
            //if (i > 0) ImGui::SameLine();
            Widget group = ui::stack(key(i), vertical); // ImGui::BeginGroup();
            const char* names[] = { "Top", "25%", "Center", "75%", "Bottom" };
            ui::label(key(), group, names[i]);

            const ImGuiWindowFlags child_flags = enable_extra_decorations ? ImGuiWindowFlags_MenuBar : 0;
            ScrollSheet child = ui::child(key(), group, vec2(child_w, 200.0f), true, child_flags); // ImGuiChildFlags_Borders
            if (enable_extra_decorations)
            {
                Widget menubar = ui::menubar(key(), child.body);
                ui::label(key(), menubar, "abc");
            }
            if (scroll_to_off)
                ui::set_scroll_y(child, scroll_to_off_px);
            if (scroll_to_pos)
                ui::set_scroll_from_pos_y(child, scroll_to_pos_px, i * 0.25f); // ImGui::GetCursorStartPos().y + scroll_to_pos_px
            {
                for (int item = 0; item < 100; item++)
                {
                    if (enable_track && item == track_item)
                    {
                        Widget tracked = ui::text_colored(key(), child.body, Colour(1, 1, 0, 1), ui::format("Item %d", item));
                        ui::set_scroll_here_y(child, tracked, i * 0.25f); // 0.0f:top, 0.5f:center, 1.0f:bottom
                    }
                    else
                    {
                        ui::textf(key(), child.body, "Item %d", item);
                    }
                }
            }
            float scroll_y = ui::get_scroll_y(child);
            float scroll_max_y = ui::get_scroll_max_y(child);
            ui::textf(key(), group, "%.0f/%.0f", scroll_y, scroll_max_y);
            //ImGui::EndGroup();
        }
        //ImGui::PopID();

        // Horizontal scroll functions
        IMGUI_DEMO_MARKER("Layout/Scrolling/Horizontal");
        ui::spacing(key(), *n);
        HelpMarker(*n,
            "Use SetScrollHereX() or SetScrollFromPosX() to scroll to a given horizontal position.\n\n"
            "Because the clipping rectangle of most window hides half worth of WindowPadding on the "
            "left/right, using SetScrollFromPosX(+1) will usually result in clipped text whereas the "
            "equivalent SetScrollFromPosY(+1) wouldn't.");
        //ImGui::PushID("##HorizontalScrolling");
        for (int i = 0; i < 5; i++)
        {
            float child_height = ui::get_text_line_height() + style.ScrollbarSize + style.WindowPadding.y * 2.0f;
            ImGuiWindowFlags child_flags = ImGuiWindowFlags_HorizontalScrollbar | (enable_extra_decorations ? ImGuiWindowFlags_AlwaysVerticalScrollbar : 0);
            Widget line = ui::row(key(i), *n);
            ScrollSheet child = ui::child(key(), line, vec2(-100, child_height), true, child_flags); // ImGuiChildFlags_Borders
            if (scroll_to_off)
                ui::set_scroll_x(child, scroll_to_off_px);
            if (scroll_to_pos)
                ui::set_scroll_from_pos_x(child, scroll_to_pos_px, i * 0.25f); // ImGui::GetCursorStartPos().x + scroll_to_pos_px
            {
                Widget items_line = ui::row(key(), child.body);
                for (int item = 0; item < 100; item++)
                {
                    //if (item > 0)
                    //    ImGui::SameLine();
                    if (enable_track && item == track_item)
                    {
                        Widget tracked = ui::text_colored(key(), items_line, Colour(1, 1, 0, 1), ui::format("Item %d", item));
                        ui::set_scroll_here_x(child, tracked, i * 0.25f); // 0.0f:left, 0.5f:center, 1.0f:right
                    }
                    else
                    {
                        ui::textf(key(), items_line, "Item %d", item);
                    }
                }
            }
            float scroll_x = ui::get_scroll_x(child);
            float scroll_max_x = ui::get_scroll_max_x(child);
            //ImGui::SameLine();
            const char* names[] = { "Left", "25%", "Center", "75%", "Right" };
            ui::textf(key(), line, "%s\n%.0f/%.0f", names[i], scroll_x, scroll_max_x);
            ui::spacing(key(i), *n);
        }
        //ImGui::PopID();

        // Miscellaneous Horizontal Scrolling Demo
        IMGUI_DEMO_MARKER("Layout/Scrolling/Horizontal (more)");
        HelpMarker(*n,
            "Horizontal scrolling for a window is enabled via the ImGuiWindowFlags_HorizontalScrollbar flag.\n\n"
            "You may want to also explicitly specify content width by using SetNextWindowContentWidth() before Begin().");
        static int lines = 7;
        ui::slider_int(key(), *n, "Lines", lines, 1, 15);
        ui::push_style_var(ImGuiStyleVar_FrameRounding, 3.0f);
        ui::push_style_var(ImGuiStyleVar_FramePadding, vec2(2.0f, 1.0f));
        vec2 scrolling_child_size = vec2(0, ui::get_frame_height_with_spacing() * 7 + 30);
        ScrollSheet scrolling = ui::child(key(), *n, scrolling_child_size, true, ImGuiWindowFlags_HorizontalScrollbar); // ImGuiChildFlags_Borders
        static Style fizzbuzz[400];
        for (int line = 0; line < lines; line++)
        {
            // Display random stuff. For the sake of this trivial demo we are using basic Button() + SameLine()
            // If you want to create your own time line for a real application you may be better off manipulating
            // the cursor position yourself, aka using SetCursorPos/SetCursorScreenPos to position the widgets
            // yourself. You may also want to use the lower-level ImDrawList API.
            Widget buttons = ui::row(key(line), scrolling.body);
            const int num_buttons = 10 + ((line & 1) ? line * 9 : line * 3);
            const float base_w = ui::get_font_size() * 3;
            for (int i = 0; i < num_buttons; i++)
            {
                //if (i > 0) ImGui::SameLine();
                //ImGui::PushID(i + line * 1000);
                char num_buf[16];
                sprintf(num_buf, "%d", i);
                const char* label = (!(i % 15)) ? "FizzBuzz" : (!(i % 3)) ? "Fizz" : (!(i % 5)) ? "Buzz" : num_buf;
                float hue = i * 0.05f;
                //ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue, 0.6f, 0.6f));
                //ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue, 0.7f, 0.7f));
                //ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue, 0.8f, 0.8f));
                Style& style_button = ui::button_style(fizzbuzz[i], hsv(hue, 0.6f, 0.6f), hsv(hue, 0.7f, 0.7f), hsv(hue, 0.8f, 0.8f));
                ui::button(key(i), buttons, style_button, label, vec2(base_w + sinf((float)(line + i)) * base_w * 0.5f, 0.0f));
                //ImGui::PopStyleColor(3);
                //ImGui::PopID();
            }
        }
        float scroll_x = ui::get_scroll_x(scrolling);
        float scroll_max_x = ui::get_scroll_max_x(scrolling);
        ui::pop_style_var(2);
        float scroll_x_delta = 0.0f;
        Widget scroll_line = ui::row(key(), *n);
        Widget scroll_left = ui::small_button(key(), scroll_line, "<<");
        if (ui::is_item_active(scroll_left))
            scroll_x_delta = -ui::io().DeltaTime * 1000.0f;
        //ImGui::SameLine();
        ui::label(key(), scroll_line, "Scroll from code"); //ImGui::SameLine();
        Widget scroll_right = ui::small_button(key(), scroll_line, ">>");
        if (ui::is_item_active(scroll_right))
            scroll_x_delta = +ui::io().DeltaTime * 1000.0f;
        //ImGui::SameLine();
        ui::textf(key(), scroll_line, "%.0f/%.0f", scroll_x, scroll_max_x);
        if (scroll_x_delta != 0.0f)
        {
            // Demonstrate a trick: you can use Begin to set yourself in the context of another window
            // (here we are already out of your child window)
            ui::set_scroll_x(scrolling, ui::get_scroll_x(scrolling) + scroll_x_delta);
        }
        ui::spacing(key(), *n);

        static bool show_horizontal_contents_size_demo_window = false;
        ui::checkbox(key(), *n, "Show Horizontal contents size demo window", show_horizontal_contents_size_demo_window);

        if (show_horizontal_contents_size_demo_window)
        {
            static bool show_h_scrollbar = true;
            static bool show_button = true;
            static bool show_tree_nodes = true;
            static bool show_text_wrapped = false;
            static bool show_columns = true;
            static bool show_tab_bar = true;
            static bool show_child = false;
            static bool explicit_content_size = false;
            static float contents_size_x = 300.0f;
            //if (explicit_content_size)
            //    ImGui::SetNextWindowContentSize(ImVec2(contents_size_x, 0.0f));
            if (auto window = ui::begin(key(), n->ui(), "Horizontal contents size demo window", &show_horizontal_contents_size_demo_window)) // show_h_scrollbar ? ImGuiWindowFlags_HorizontalScrollbar : 0
            {
                ScrollSheet sheet = ui::scroll_sheet(key(), *window->body);
                Widget w = sheet.body;
                IMGUI_DEMO_MARKER("Layout/Scrolling/Horizontal contents size demo window");
                ui::push_style_var(ImGuiStyleVar_ItemSpacing, vec2(2, 0));
                ui::push_style_var(ImGuiStyleVar_FramePadding, vec2(2, 0));
                HelpMarker(w,
                    "Test how different widgets react and impact the work rectangle growing when horizontal scrolling is enabled.\n\n"
                    "Use 'Metrics->Tools->Show windows rectangles' to visualize rectangles.");
                ui::checkbox(key(), w, "H-scrollbar", show_h_scrollbar);
                ui::checkbox(key(), w, "Button", show_button);            // Will grow contents size (unless explicitly overwritten)
                ui::checkbox(key(), w, "Tree nodes", show_tree_nodes);    // Will grow contents size and display highlight over full width
                ui::checkbox(key(), w, "Text wrapped", show_text_wrapped);// Will grow and use contents size
                ui::checkbox(key(), w, "Columns", show_columns);          // Will use contents size
                ui::checkbox(key(), w, "Tab bar", show_tab_bar);          // Will use contents size
                ui::checkbox(key(), w, "Child", show_child);              // Will grow and use contents size
                ui::checkbox(key(), w, "Explicit content size", explicit_content_size);
                Widget line = ui::row(key(), w);
                ui::textf(key(), line, "Scroll %.1f/%.1f %.1f/%.1f", ui::get_scroll_x(sheet), ui::get_scroll_max_x(sheet), ui::get_scroll_y(sheet), ui::get_scroll_max_y(sheet));
                if (explicit_content_size)
                {
                    //ImGui::SameLine();
                    //ImGui::SetNextItemWidth(ImGui::CalcTextSize("123456").x);
                    ui::drag_float(key(), line, "##csx", contents_size_x);
                    //ImVec2 p = ImGui::GetCursorScreenPos();
                    //ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + 10, p.y + 10), IM_COL32_WHITE);
                    //ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(p.x + contents_size_x - 10, p.y), ImVec2(p.x + contents_size_x, p.y + 10), IM_COL32_WHITE);
                    ui::dummy(key(), w, vec2(0, 10));
                }
                ui::pop_style_var(2);
                ui::separator(key(), w);
                if (show_button)
                {
                    ui::button(key(), w, "this is a 300-wide button", vec2(300, 0));
                }
                if (show_tree_nodes)
                {
                    //bool open = true;
                    if (Widget node = ui::tree_node_ex(key(), w, "this is a tree node").body)
                    {
                        if (Widget node2 = ui::tree_node_ex(key(), *node, "another one of those tree node...").body)
                        {
                            ui::label(key(), *node2, "Some tree contents");
                        }
                    }
                    ui::collapsing_header(key(), w, "CollapsingHeader"); // &open
                }
                if (show_text_wrapped)
                {
                    ui::text_wrapped(key(), w, "This text should automatically wrap on the edge of the work rectangle.");
                }
                if (show_columns)
                {
                    ui::label(key(), w, "Tables:");
                    {
                        ui::TableLayout table = ui::begin_table(key(), w, 4); // ImGuiTableFlags_Borders
                        for (int i = 0; i < 4; i++)
                        {
                            Widget cell = table.next_column();
                            ui::textf(key(), cell, "Width %.2f", ui::get_content_region_avail(cell).x);
                        }
                    }
                    ui::label(key(), w, "Columns:");
                    {
                        ui::TableLayout columns = ui::begin_table(key(), w, 4); // ImGui::Columns(4);
                        for (int i = 0; i < 4; i++)
                        {
                            Widget cell = columns.next_column();
                            ui::textf(key(), cell, "Width %.2f", ui::get_content_region_avail(cell).x); // ImGui::GetColumnWidth()
                            //ImGui::NextColumn();
                        }
                        //ImGui::Columns(1);
                    }
                }
                if (show_tab_bar)
                {
                    Tabber tab_bar = ui::tabber(key(), w); // ImGui::BeginTabBar("Hello")
                    ui::tab(key(), tab_bar, "OneOneOne");
                    ui::tab(key(), tab_bar, "TwoTwoTwo");
                    ui::tab(key(), tab_bar, "ThreeThreeThree");
                    ui::tab(key(), tab_bar, "FourFourFour");
                }
                if (show_child)
                {
                    ui::begin_child(key(), w, vec2(0, 0), true); // ImGuiChildFlags_Borders
                }
            }
        }
    }

    if (Widget n = ui::tree_node_ex(key(), *body, "Text Clipping").body)
    {
        IMGUI_DEMO_MARKER("Layout/Text Clipping");
        static vec2 size(100.0f, 100.0f);
        static vec2 offset(30.0f, 30.0f);
        ui::drag_float2(key(), *n, "size", (float*)&size, 0.5f, 1.0f, 200.0f); // "%.0f");
        ui::text_wrapped(key(), *n, "(Click and drag to scroll)");

        HelpMarker(*n,
            "(Left) Using ImGui::PushClipRect():\n"
            "Will alter ImGui hit-testing logic + ImDrawList rendering.\n"
            "(use this if you want your clipping rectangle to affect interactions)\n\n"
            "(Center) Using ImDrawList::PushClipRect():\n"
            "Will alter ImDrawList rendering only.\n"
            "(use this as a shortcut if you are only using ImDrawList calls)\n\n"
            "(Right) Using ImDrawList::AddText() with a fine ClipRect:\n"
            "Will alter only this specific ImDrawList::AddText() rendering.\n"
            "This is often used internally to avoid altering the clipping rectangle and minimize draw calls.");

        Widget line = ui::row(key(), *n);
        for (int i = 0; i < 3; i++)
        {
            //if (i > 0)
            //    ImGui::SameLine();

            //ImGui::PushID(i);
            Widget canvas = ui::invisible_button(key(i), line, "##canvas", size);
            if (ui::is_item_active(canvas) && ui::is_mouse_dragging(canvas))
            {
                offset.x += ui::get_mouse_drag_delta(canvas).x;
                offset.y += ui::get_mouse_drag_delta(canvas).y;
                ui::reset_mouse_drag_delta(canvas);
            }
            //ImGui::PopID();
            //if (!ImGui::IsItemVisible()) // Skip rendering as ImDrawList elements are not clipped.
            //    continue;

            const char* text_str = "Line 1 hello\nLine 2 clip me!";
            const vec2 text_pos = offset;
            // In two.ui, the custom rendering of a widget is done in its custom draw function, with the Vg API, in the space of the widget
            canvas.custom_draw() = [=](Widget widget, const vec4& rect, Vg& vg)
            {
                UNUSED(widget);
                switch (i)
                {
                case 0:
                case 1:
                    vg.clip(rect); // ImGui::PushClipRect(p0, p1, true); / draw_list->PushClipRect(p0, p1, true);
                    vg.draw_rect(rect, { to_colour(90, 90, 120, 255) });
                    ui::draw_text(vg, rect.pos + text_pos, Colour::White, text_str);
                    vg.unclip();
                    break;
                case 2:
                    vg.draw_rect(rect, { to_colour(90, 90, 120, 255) });
                    vg.clip(rect); // AddText() with a clip rect
                    ui::draw_text(vg, rect.pos + text_pos, Colour::White, text_str);
                    vg.unclip();
                    break;
                }
            };
            canvas.mark_dirty(DIRTY_REDRAW);
        }
    }

    if (Widget n = ui::tree_node_ex(key(), *body, "Overlap Mode").body)
    {
        IMGUI_DEMO_MARKER("Layout/Overlap Mode");
        static bool enable_allow_overlap = true;

        HelpMarker(*n,
            "Hit-testing is by default performed in item submission order, which generally is perceived as 'back-to-front'.\n\n"
            "By using SetNextItemAllowOverlap() you can notify that an item may be overlapped by another. "
            "Doing so alters the hovering logic: items using AllowOverlap mode requires an extra frame to accept hovered state.");
        ui::checkbox(key(), *n, "Enable AllowOverlap", enable_allow_overlap);

        // In two.ui, items are positioned freely in a free layout (e.g a screen)
        Widget overlap = ui::overlap(key(), *n, vec2(130.f, 130.f));
        vec2 button1_pos = vec2(0.f); // ImGui::GetCursorScreenPos();
        vec2 button2_pos = vec2(button1_pos.x + 50.0f, button1_pos.y + 50.0f);
        //if (enable_allow_overlap)
        //    ImGui::SetNextItemAllowOverlap();
        ui::button(key(), overlap, "Button 1", vec2(80, 80)).set_position(button1_pos);
        //ImGui::SetCursorScreenPos(button2_pos);
        ui::button(key(), overlap, "Button 2", vec2(80, 80)).set_position(button2_pos);

        // This is typically used with width-spanning items.
        // (note that Selectable() has a dedicated flag ImGuiSelectableFlags_AllowOverlap, which is a shortcut
        // for using SetNextItemAllowOverlap(). For demo purpose we use SetNextItemAllowOverlap() here.)
        //if (enable_allow_overlap)
        //    ImGui::SetNextItemAllowOverlap();
        Widget selectable = ui::selectable(key(), *n, "Some Selectable", false);
        //ImGui::SameLine();
        ui::small_button(key(), selectable, "++");
    }
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowPopups()
//-----------------------------------------------------------------------------

static void DemoWindowPopups(Widget parent)
{
    Widget body = ui::collapsing_header(key(), parent, "Popups & Modal windows");
    if (!body)
        return;

    // The properties of popups windows are:
    // - They block normal mouse hovering detection outside them. (*)
    // - Unless modal, they can be closed by clicking anywhere outside them, or by pressing ESCAPE.
    // - Their visibility state (~bool) is held internally by Dear ImGui instead of being held by the programmer as
    //   we are used to with regular Begin() calls. User can manipulate the visibility state by calling OpenPopup().
    // (*) One can use IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup) to bypass it and detect hovering even
    //     when normally blocked by a popup.
    // Those three properties are connected. The library needs to hold their visibility state BECAUSE it can close
    // popups at any time.

    // Typical use for regular windows:
    //   bool my_tool_is_active = false; if (ImGui::Button("Open")) my_tool_is_active = true; [...] if (my_tool_is_active) Begin("My Tool", &my_tool_is_active) { [...] } End();
    // Typical use for popups:
    //   if (ImGui::Button("Open")) ImGui::OpenPopup("MyPopup"); if (ImGui::BeginPopup("MyPopup")) { [...] EndPopup(); }

    // With popups we have to go through a library call (here OpenPopup) to manipulate the visibility state.
    // This may be a bit confusing at first but it should quickly make sense. Follow on the examples below.

    // In two.ui, the visibility state of a popup is held by the programmer, as for regular windows: OpenPopup() maps to setting a bool

    if (Widget n = ui::tree_node_ex(key(), *body, "Popups").body)
    {
        IMGUI_DEMO_MARKER("Popups/Popups");
        ui::text_wrapped(key(), *n,
            "When a popup is active, it inhibits interacting with windows that are behind the popup. "
            "Clicking outside the popup closes it.");

        static int selected_fish = -1;
        const char* names[] = { "Bream", "Haddock", "Mackerel", "Pollock", "Tilefish" };
        static bool toggles[] = { true, false, false, false, false };

        // Simple selection popup (if you want to show the current selection inside the Button itself,
        // you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
        static bool my_select_popup = false;
        Widget line = ui::row(key(), *n);
        if (ui::button(key(), line, "Select..").activated())
            my_select_popup = true; // ImGui::OpenPopup("my_select_popup");
        //ImGui::SameLine();
        ui::label(key(), line, selected_fish == -1 ? "<None>" : names[selected_fish]);
        if (Widget popup = ui::begin_popup(key(), line, my_select_popup))
        {
            ui::separator_text(key(), *popup, "Aquarium");
            for (int i = 0; i < IM_COUNTOF(names); i++)
                if (ui::selectable(key(), *popup, names[i], false).activated())
                {
                    selected_fish = i;
                    my_select_popup = false;
                }
        }

        // Showing a menu with toggles
        static bool my_toggle_popup = false;
        Widget toggle = ui::button(key(), *n, "Toggle..");
        if (toggle.activated())
            my_toggle_popup = true; // ImGui::OpenPopup("my_toggle_popup");
        if (Widget popup = ui::begin_popup(key(), toggle, my_toggle_popup))
        {
            for (int i = 0; i < IM_COUNTOF(names); i++)
                ui::menu_item(key(), *popup, names[i], "", &toggles[i]);
            if (Widget menu = ui::begin_menu(key(), *popup, "Sub-menu", true))
            {
                ui::menu_item(key(), *menu, "Click me");
            }

            ui::separator(key(), *popup);
            Widget tooltip_here = ui::label(key(), *popup, "Tooltip here");
            ui::set_item_tooltip(key(), tooltip_here, "I am a tooltip over a popup");

            static bool another_popup = false;
            Widget stacked = ui::button(key(), *popup, "Stacked Popup");
            if (stacked.activated())
                another_popup = true; // ImGui::OpenPopup("another popup");
            if (Widget another = ui::begin_popup(key(), stacked, another_popup))
            {
                for (int i = 0; i < IM_COUNTOF(names); i++)
                    ui::menu_item(key(), *another, names[i], "", &toggles[i]);
                if (Widget menu = ui::begin_menu(key(), *another, "Sub-menu", true))
                {
                    ui::menu_item(key(), *menu, "Click me");
                    static bool last_popup = false;
                    Widget stacked_last = ui::button(key(), *menu, "Stacked Popup");
                    if (stacked_last.activated())
                        last_popup = true; // ImGui::OpenPopup("another popup");
                    if (Widget last = ui::begin_popup(key(), stacked_last, last_popup))
                    {
                        ui::label(key(), *last, "I am the last one here.");
                    }
                }
            }
        }

        // Call the more complete ShowExampleMenuFile which we use in various places of this demo
        static bool my_file_popup = false;
        Widget with_menu = ui::button(key(), *n, "With a menu..");
        if (with_menu.activated())
            my_file_popup = true; // ImGui::OpenPopup("my_file_popup");
        if (Widget popup = ui::begin_popup(key(), with_menu, my_file_popup)) // ImGuiWindowFlags_MenuBar
        {
            Widget menubar = ui::menubar(key(), *popup);
            {
                if (Widget menu = ui::begin_menu(key(), menubar, "File"))
                {
                    ShowExampleMenuFile(*menu);
                }
                if (Widget menu = ui::begin_menu(key(), menubar, "Edit"))
                {
                    ui::menu_item(key(), *menu, "Dummy");
                }
            }
            ui::label(key(), *popup, "Hello from popup!");
            ui::button(key(), *popup, "This is a dummy button..");
        }
    }

    if (Widget n = ui::tree_node_ex(key(), *body, "Context menus").body)
    {
        IMGUI_DEMO_MARKER("Popups/Context menus");
        HelpMarker(*n, "\"Context\" functions are simple helpers to associate a Popup to a given Item or Window identifier.");

        // BeginPopupContextItem() is a helper to provide common/simple popup behavior of essentially doing:
        //     if (id == 0)
        //         id = GetItemID(); // Use last item id
        //     if (IsItemHovered() && IsMouseReleased(ImGuiMouseButton_Right))
        //         OpenPopup(id);
        //     return BeginPopup(id);
        // For advanced uses you may want to replicate and customize this code.
        // See more details in BeginPopupContextItem().

        // Example 1
        // When used after an item that has an ID (e.g. Button), we can skip providing an ID to BeginPopupContextItem(),
        // and BeginPopupContextItem() will use the last item ID as the popup ID.
        {
            const char* names[5] = { "Label1", "Label2", "Label3", "Label4", "Label5" };
            static int selected = -1;
            for (int i = 0; i < 5; i++)
            {
                Widget selectable = ui::selectable(key(), *n, names[i], selected == i);
                if (selectable.activated())
                    selected = i;
                if (Widget popup = ui::begin_popup_context_item(key(), selectable)) // <-- use last item id as popup id
                {
                    selected = i;
                    ui::textf(key(), *popup, "This is a popup for \"%s\"!", names[i]);
                    if (ui::button(key(), *popup, "Close").activated())
                        ui::close_current_popup(*popup);
                }
                ui::set_item_tooltip(key(), selectable, "Right-click to open popup");
            }
        }

        // Example 2
        // Popup on a Text() element which doesn't have an identifier: we need to provide an identifier to BeginPopupContextItem().
        // Using an explicit identifier is also convenient if you want to activate the popups from different locations.
        {
            HelpMarker(*n, "Text() elements don't have stable identifiers so we need to provide one.");
            static float value = 0.5f;
            static bool my_popup = false;
            Widget text1 = ui::textf(key(), *n, "Value = %.3f <-- (1) right-click this text", value);
            ui::open_popup_on_item_click(text1, my_popup); // ImGui::BeginPopupContextItem("my popup")
            if (Widget popup = ui::begin_popup(key(), text1, my_popup))
            {
                if (ui::selectable(key(), *popup, "Set to zero", false).activated()) value = 0.0f;
                if (ui::selectable(key(), *popup, "Set to PI", false).activated()) value = 3.1415f;
                //ImGui::SetNextItemWidth(-FLT_MIN);
                ui::drag_float(key(), *popup, "##Value", value, 0.1f, 0.0f, 0.0f);
            }

            // We can also use OpenPopupOnItemClick() to toggle the visibility of a given popup.
            // Here we make it that right-clicking this other text element opens the same popup as above.
            // The popup itself will be submitted by the code above.
            Widget text2 = ui::label(key(), *n, "(2) Or right-click this text");
            ui::open_popup_on_item_click(text2, my_popup); // ImGuiPopupFlags_MouseButtonRight

            // Back to square one: manually open the same popup.
            if (ui::button(key(), *n, "(3) Or click this button").activated())
                my_popup = true; // ImGui::OpenPopup("my popup");
        }

        // Example 3
        // When using BeginPopupContextItem() with an implicit identifier (NULL == use last item ID),
        // we need to make sure your item identifier is stable.
        // In this example we showcase altering the item label while preserving its identifier, using the ### operator (see FAQ).
        {
            HelpMarker(*n, "Showcase using a popup ID linked to item ID, with the item having a changing label + stable ID using the ### operator.");
            static string name = "Label1";
            char buf[64];
            sprintf(buf, "Button: %s", name.c_str()); // ### operator override ID ignoring the preceding label
            Widget line = ui::row(key(), *n);
            Widget button = ui::button(key(), line, buf);
            if (Widget popup = ui::begin_popup_context_item(key(), button))
            {
                ui::label(key(), *popup, "Edit name:");
                ui::input_text(key(), *popup, "##edit", name);
                if (ui::button(key(), *popup, "Close").activated())
                    ui::close_current_popup(*popup);
            }
            //ImGui::SameLine();
            ui::label(key(), line, "(<-- right-click here)");
        }
    }

    if (Widget n = ui::tree_node_ex(key(), *body, "Modals").body)
    {
        IMGUI_DEMO_MARKER("Popups/Modals");
        ui::text_wrapped(key(), *n, "Modal windows are like popups but the user cannot close them by clicking outside.");

        static bool delete_popup = false;
        if (ui::button(key(), *n, "Delete..").activated())
            delete_popup = true; // ImGui::OpenPopup("Delete?");

        // Always center this window when appearing
        //ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        //ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (Widget modal = ui::begin_popup_modal(key(), *n, "Delete?", delete_popup)) // NULL, ImGuiWindowFlags_AlwaysAutoResize
        {
            ui::label(key(), *modal, "All those beautiful files will be deleted.\nThis operation cannot be undone!");
            ui::separator(key(), *modal);

            //static int unused_i = 0;
            //ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

            static bool dont_ask_me_next_time = false;
            ui::push_style_var(ImGuiStyleVar_FramePadding, vec2(0, 0));
            ui::checkbox(key(), *modal, "Don't ask me next time", dont_ask_me_next_time);
            ui::pop_style_var();

            Widget line = ui::row(key(), *modal);
            if (ui::button(key(), line, "OK", vec2(120, 0)).activated()) { delete_popup = false; } // ImGui::CloseCurrentPopup();
            //ImGui::SetItemDefaultFocus();
            //ImGui::SameLine();
            if (ui::button(key(), line, "Cancel", vec2(120, 0)).activated()) { delete_popup = false; } // ImGui::CloseCurrentPopup();
        }

        static bool stacked_1 = false;
        if (ui::button(key(), *n, "Stacked modals..").activated())
            stacked_1 = true; // ImGui::OpenPopup("Stacked 1");
        if (Widget modal = ui::begin_popup_modal(key(), *n, "Stacked 1", stacked_1)) // NULL, ImGuiWindowFlags_MenuBar
        {
            Widget menubar = ui::menubar(key(), *modal);
            {
                if (Widget menu = ui::begin_menu(key(), menubar, "File"))
                {
                    if (ui::menu_item(key(), *menu, "Some menu item")) {}
                }
            }
            ui::label(key(), *modal, "Hello from Stacked The First\nUsing style.Colors[ImGuiCol_ModalWindowDimBg] behind it.");

            // Testing behavior of widgets stacking their own regular popups over the modal.
            static int item = 1;
            static float color[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
            ui::combo(key(), *modal, "Combo", item, { "aaaa", "bbbb", "cccc", "dddd", "eeee" });
            ui::color_edit4(key(), *modal, "Color", color);

            static bool stacked_2 = false;
            if (ui::button(key(), *modal, "Add another modal..").activated())
                stacked_2 = true; // ImGui::OpenPopup("Stacked 2");

            // Also demonstrate passing a bool* to BeginPopupModal(), this will create a regular close button which
            // will close the popup. Note that the visibility state of popups is owned by imgui, so the input value
            // of the bool actually doesn't matter here.
            //bool unused_open = true;
            if (Widget modal2 = ui::begin_popup_modal(key(), *modal, "Stacked 2", stacked_2))
            {
                ui::label(key(), *modal2, "Hello from Stacked The Second!");
                ui::color_edit4(key(), *modal2, "Color", color); // Allow opening another nested popup
                if (ui::button(key(), *modal2, "Close").activated())
                    stacked_2 = false; // ImGui::CloseCurrentPopup();
            }

            if (ui::button(key(), *modal, "Close").activated())
                stacked_1 = false; // ImGui::CloseCurrentPopup();
        }
    }

    if (Widget n = ui::tree_node_ex(key(), *body, "Menus inside a regular window").body)
    {
        IMGUI_DEMO_MARKER("Popups/Menus inside a regular window");
        ui::text_wrapped(key(), *n, "Below we are testing adding menu items to a regular window. It's rather unusual but should work!");
        ui::separator(key(), *n);

        ui::menu_item(key(), *n, "Menu item", "Ctrl+M");
        if (Widget menu = ui::begin_menu(key(), *n, "Menu inside a regular window"))
        {
            ShowExampleMenuFile(*menu);
        }
        ui::separator(key(), *n);
    }
}

// The tables API (BeginTable(), TableSetupColumn(), TableHeadersRow(), sorting, clipping...) and the legacy columns API
// have no equivalent in two.ui yet: the Tables & Columns section is kept as is from the original, under #if 0
#if 0

// Dummy data structure that we use for the Table demo.
// (pre-C++11 doesn't allow us to instantiate ImVector<MyItem> template if this structure is defined inside the demo function)
namespace
{
// We are passing our own identifier to TableSetupColumn() to facilitate identifying columns in the sorting code.
// This identifier will be passed down into ImGuiTableSortSpec::ColumnUserID.
// But it is possible to omit the user id parameter of TableSetupColumn() and just use the column index instead! (ImGuiTableSortSpec::ColumnIndex)
// If you don't use sorting, you will generally never care about giving column an ID!
enum MyItemColumnID
{
    MyItemColumnID_ID,
    MyItemColumnID_Name,
    MyItemColumnID_Action,
    MyItemColumnID_Quantity,
    MyItemColumnID_Description
};

struct MyItem
{
    int         ID;
    const char* Name;
    int         Quantity;

    // We have a problem which is affecting _only this demo_ and should not affect your code:
    // As we don't rely on std:: or other third-party library to compile dear imgui, we only have reliable access to qsort(),
    // however qsort doesn't allow passing user data to comparing function.
    // As a workaround, we are storing the sort specs in a static/global for the comparing function to access.
    // In your own use case you would probably pass the sort specs to your sorting/comparing functions directly and not use a global.
    // We could technically call ImGui::TableGetSortSpecs() in CompareWithSortSpecs(), but considering that this function is called
    // very often by the sorting algorithm it would be a little wasteful.
    static const ImGuiTableSortSpecs* s_current_sort_specs;

    static void SortWithSortSpecs(ImGuiTableSortSpecs* sort_specs, MyItem* items, int items_count)
    {
        s_current_sort_specs = sort_specs; // Store in variable accessible by the sort function.
        if (items_count > 1)
            qsort(items, (size_t)items_count, sizeof(items[0]), MyItem::CompareWithSortSpecs);
        s_current_sort_specs = NULL;
    }

    // Compare function to be used by qsort()
    static int IMGUI_CDECL CompareWithSortSpecs(const void* lhs, const void* rhs)
    {
        const MyItem* a = (const MyItem*)lhs;
        const MyItem* b = (const MyItem*)rhs;
        for (int n = 0; n < s_current_sort_specs->SpecsCount; n++)
        {
            // Here we identify columns using the ColumnUserID value that we ourselves passed to TableSetupColumn()
            // We could also choose to identify columns based on their index (sort_spec->ColumnIndex), which is simpler!
            const ImGuiTableColumnSortSpecs* sort_spec = &s_current_sort_specs->Specs[n];
            int delta = 0;
            switch (sort_spec->ColumnUserID)
            {
            case MyItemColumnID_ID:             delta = (a->ID - b->ID);                break;
            case MyItemColumnID_Name:           delta = (strcmp(a->Name, b->Name));     break;
            case MyItemColumnID_Quantity:       delta = (a->Quantity - b->Quantity);    break;
            case MyItemColumnID_Description:    delta = (strcmp(a->Name, b->Name));     break;
            default: IM_ASSERT(0); break;
            }
            if (delta > 0)
                return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? +1 : -1;
            if (delta < 0)
                return (sort_spec->SortDirection == ImGuiSortDirection_Ascending) ? -1 : +1;
        }

        // qsort() is instable so always return a way to differentiate items.
        // Your own compare function may want to avoid fallback on implicit sort specs.
        // e.g. a Name compare if it wasn't already part of the sort specs.
        return a->ID - b->ID;
    }
};
const ImGuiTableSortSpecs* MyItem::s_current_sort_specs = NULL;
}

// Make the UI compact because there are so many fields
static void PushStyleCompact()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImGui::PushStyleVarY(ImGuiStyleVar_FramePadding, (float)(int)(style.FramePadding.y * 0.60f));
    ImGui::PushStyleVarY(ImGuiStyleVar_ItemSpacing, (float)(int)(style.ItemSpacing.y * 0.60f));
}

static void PopStyleCompact()
{
    ImGui::PopStyleVar(2);
}

// Show a combo box with a choice of sizing policies
static void EditTableSizingFlags(ImGuiTableFlags* p_flags)
{
    struct EnumDesc { ImGuiTableFlags Value; const char* Name; const char* Tooltip; };
    static const EnumDesc policies[] =
    {
        { ImGuiTableFlags_None,               "Default",                            "Use default sizing policy:\n- ImGuiTableFlags_SizingFixedFit if ScrollX is on or if host window has ImGuiWindowFlags_AlwaysAutoResize.\n- ImGuiTableFlags_SizingStretchSame otherwise." },
        { ImGuiTableFlags_SizingFixedFit,     "ImGuiTableFlags_SizingFixedFit",     "Columns default to _WidthFixed (if resizable) or _WidthAuto (if not resizable), matching contents width." },
        { ImGuiTableFlags_SizingFixedSame,    "ImGuiTableFlags_SizingFixedSame",    "Columns are all the same width, matching the maximum contents width.\nImplicitly disable ImGuiTableFlags_Resizable and enable ImGuiTableFlags_NoKeepColumnsVisible." },
        { ImGuiTableFlags_SizingStretchProp,  "ImGuiTableFlags_SizingStretchProp",  "Columns default to _WidthStretch with weights proportional to their widths." },
        { ImGuiTableFlags_SizingStretchSame,  "ImGuiTableFlags_SizingStretchSame",  "Columns default to _WidthStretch with same weights." }
    };
    int idx;
    for (idx = 0; idx < IM_COUNTOF(policies); idx++)
        if (policies[idx].Value == (*p_flags & ImGuiTableFlags_SizingMask_))
            break;
    const char* preview_text = (idx < IM_COUNTOF(policies)) ? policies[idx].Name + (idx > 0 ? strlen("ImGuiTableFlags") : 0) : "";
    if (ImGui::BeginCombo("Sizing Policy", preview_text))
    {
        for (int n = 0; n < IM_COUNTOF(policies); n++)
            if (ImGui::Selectable(policies[n].Name, idx == n))
                *p_flags = (*p_flags & ~ImGuiTableFlags_SizingMask_) | policies[n].Value;
        ImGui::EndCombo();
    }
    ImGui::SameLine();
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 50.0f);
        for (int m = 0; m < IM_COUNTOF(policies); m++)
        {
            ImGui::Separator();
            ImGui::Text("%s:", policies[m].Name);
            ImGui::Separator();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetStyle().IndentSpacing * 0.5f);
            ImGui::TextUnformatted(policies[m].Tooltip);
        }
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

static void EditTableColumnsFlags(ImGuiTableColumnFlags* p_flags)
{
    ImGui::CheckboxFlags("_Disabled", p_flags, ImGuiTableColumnFlags_Disabled); ImGui::SameLine(); HelpMarker("Master disable flag (also hide from context menu)");
    ImGui::CheckboxFlags("_DefaultHide", p_flags, ImGuiTableColumnFlags_DefaultHide);
    ImGui::CheckboxFlags("_DefaultSort", p_flags, ImGuiTableColumnFlags_DefaultSort);
    if (ImGui::CheckboxFlags("_WidthStretch", p_flags, ImGuiTableColumnFlags_WidthStretch))
        *p_flags &= ~(ImGuiTableColumnFlags_WidthMask_ ^ ImGuiTableColumnFlags_WidthStretch);
    if (ImGui::CheckboxFlags("_WidthFixed", p_flags, ImGuiTableColumnFlags_WidthFixed))
        *p_flags &= ~(ImGuiTableColumnFlags_WidthMask_ ^ ImGuiTableColumnFlags_WidthFixed);
    ImGui::CheckboxFlags("_NoResize", p_flags, ImGuiTableColumnFlags_NoResize);
    ImGui::CheckboxFlags("_NoReorder", p_flags, ImGuiTableColumnFlags_NoReorder);
    ImGui::CheckboxFlags("_NoHide", p_flags, ImGuiTableColumnFlags_NoHide);
    ImGui::CheckboxFlags("_NoClip", p_flags, ImGuiTableColumnFlags_NoClip);
    ImGui::CheckboxFlags("_NoSort", p_flags, ImGuiTableColumnFlags_NoSort);
    ImGui::CheckboxFlags("_NoSortAscending", p_flags, ImGuiTableColumnFlags_NoSortAscending);
    ImGui::CheckboxFlags("_NoSortDescending", p_flags, ImGuiTableColumnFlags_NoSortDescending);
    ImGui::CheckboxFlags("_NoHeaderLabel", p_flags, ImGuiTableColumnFlags_NoHeaderLabel);
    ImGui::CheckboxFlags("_NoHeaderWidth", p_flags, ImGuiTableColumnFlags_NoHeaderWidth);
    ImGui::CheckboxFlags("_PreferSortAscending", p_flags, ImGuiTableColumnFlags_PreferSortAscending);
    ImGui::CheckboxFlags("_PreferSortDescending", p_flags, ImGuiTableColumnFlags_PreferSortDescending);
    ImGui::CheckboxFlags("_IndentEnable", p_flags, ImGuiTableColumnFlags_IndentEnable); ImGui::SameLine(); HelpMarker("Default for column 0");
    ImGui::CheckboxFlags("_IndentDisable", p_flags, ImGuiTableColumnFlags_IndentDisable); ImGui::SameLine(); HelpMarker("Default for column >0");
    ImGui::CheckboxFlags("_AngledHeader", p_flags, ImGuiTableColumnFlags_AngledHeader);
}

static void ShowTableColumnsStatusFlags(ImGuiTableColumnFlags flags)
{
    ImGui::CheckboxFlags("_IsEnabled", &flags, ImGuiTableColumnFlags_IsEnabled);
    ImGui::CheckboxFlags("_IsVisible", &flags, ImGuiTableColumnFlags_IsVisible);
    ImGui::CheckboxFlags("_IsSorted", &flags, ImGuiTableColumnFlags_IsSorted);
    ImGui::CheckboxFlags("_IsHovered", &flags, ImGuiTableColumnFlags_IsHovered);
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowTables()
//-----------------------------------------------------------------------------

static void DemoWindowTables()
{
    //ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    if (!ImGui::CollapsingHeader("Tables & Columns"))
        return;

    // Using those as a base value to create width/height that are factor of the size of our font
    const float TEXT_BASE_WIDTH = ImGui::CalcTextSize("A").x;
    const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();

    ImGui::PushID("Tables");

    int open_action = -1;
    if (ImGui::Button("Expand all"))
        open_action = 1;
    ImGui::SameLine();
    if (ImGui::Button("Collapse all"))
        open_action = 0;
    ImGui::SameLine();

    // Options
    static bool disable_indent = false;
    ImGui::Checkbox("Disable tree indentation", &disable_indent);
    ImGui::SameLine();
    HelpMarker("Disable the indenting of tree nodes so demo tables can use the full window width.");
    ImGui::Separator();
    if (disable_indent)
        ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 0.0f);

    // About Styling of tables
    // Most settings are configured on a per-table basis via the flags passed to BeginTable() and TableSetupColumns APIs.
    // There are however a few settings that a shared and part of the ImGuiStyle structure:
    //   style.CellPadding                          // Padding within each cell
    //   style.Colors[ImGuiCol_TableHeaderBg]       // Table header background
    //   style.Colors[ImGuiCol_TableBorderStrong]   // Table outer and header borders
    //   style.Colors[ImGuiCol_TableBorderLight]    // Table inner borders
    //   style.Colors[ImGuiCol_TableRowBg]          // Table row background when ImGuiTableFlags_RowBg is enabled (even rows)
    //   style.Colors[ImGuiCol_TableRowBgAlt]       // Table row background when ImGuiTableFlags_RowBg is enabled (odds rows)

    // Demos
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Basic"))
    {
        IMGUI_DEMO_MARKER("Tables/Basic");
        // Here we will showcase three different ways to output a table.
        // They are very simple variations of a same thing!

        // [Method 1] Using TableNextRow() to create a new row, and TableSetColumnIndex() to select the column.
        // In many situations, this is the most flexible and easy to use pattern.
        HelpMarker("Using TableNextRow() + calling TableSetColumnIndex() _before_ each cell, in a loop.");
        if (ImGui::BeginTable("table1", 3))
        {
            for (int row = 0; row < 4; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("Row %d Column %d", row, column);
                }
            }
            ImGui::EndTable();
        }

        // [Method 2] Using TableNextColumn() called multiple times, instead of using a for loop + TableSetColumnIndex().
        // This is generally more convenient when you have code manually submitting the contents of each column.
        HelpMarker("Using TableNextRow() + calling TableNextColumn() _before_ each cell, manually.");
        if (ImGui::BeginTable("table2", 3))
        {
            for (int row = 0; row < 4; row++)
            {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Row %d", row);
                ImGui::TableNextColumn();
                ImGui::Text("Some contents");
                ImGui::TableNextColumn();
                ImGui::Text("123.456");
            }
            ImGui::EndTable();
        }

        // [Method 3] We call TableNextColumn() _before_ each cell. We never call TableNextRow(),
        // as TableNextColumn() will automatically wrap around and create new rows as needed.
        // This is generally more convenient when your cells all contains the same type of data.
        HelpMarker(
            "Only using TableNextColumn(), which tends to be convenient for tables where every cell contains "
            "the same type of contents.\n This is also more similar to the old NextColumn() function of the "
            "Columns API, and provided to facilitate the Columns->Tables API transition.");
        if (ImGui::BeginTable("table3", 3))
        {
            for (int item = 0; item < 14; item++)
            {
                ImGui::TableNextColumn();
                ImGui::Text("Item %d", item);
            }
            ImGui::EndTable();
        }

        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Borders, background"))
    {
        IMGUI_DEMO_MARKER("Tables/Borders, background");
        // Expose a few Borders related flags interactively
        enum ContentsType { CT_Text, CT_FillButton };
        static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
        static bool display_headers = false;
        static int contents_type = CT_Text;

        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_RowBg", &flags, ImGuiTableFlags_RowBg);
        ImGui::CheckboxFlags("ImGuiTableFlags_Borders", &flags, ImGuiTableFlags_Borders);
        ImGui::SameLine(); HelpMarker("ImGuiTableFlags_Borders\n = ImGuiTableFlags_BordersInnerV\n | ImGuiTableFlags_BordersOuterV\n | ImGuiTableFlags_BordersInnerH\n | ImGuiTableFlags_BordersOuterH");
        ImGui::Indent();

        ImGui::CheckboxFlags("ImGuiTableFlags_BordersH", &flags, ImGuiTableFlags_BordersH);
        ImGui::Indent();
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuterH", &flags, ImGuiTableFlags_BordersOuterH);
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersInnerH", &flags, ImGuiTableFlags_BordersInnerH);
        ImGui::Unindent();

        ImGui::CheckboxFlags("ImGuiTableFlags_BordersV", &flags, ImGuiTableFlags_BordersV);
        ImGui::Indent();
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuterV", &flags, ImGuiTableFlags_BordersOuterV);
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersInnerV", &flags, ImGuiTableFlags_BordersInnerV);
        ImGui::Unindent();

        ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuter", &flags, ImGuiTableFlags_BordersOuter);
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersInner", &flags, ImGuiTableFlags_BordersInner);
        ImGui::Unindent();

        ImGui::AlignTextToFramePadding(); ImGui::Text("Cell contents:");
        ImGui::SameLine(); ImGui::RadioButton("Text", &contents_type, CT_Text);
        ImGui::SameLine(); ImGui::RadioButton("FillButton", &contents_type, CT_FillButton);
        ImGui::Checkbox("Display headers", &display_headers);
        ImGui::CheckboxFlags("ImGuiTableFlags_NoBordersInBody", &flags, ImGuiTableFlags_NoBordersInBody); ImGui::SameLine(); HelpMarker("Disable vertical borders in columns Body (borders will always appear in Headers)");
        PopStyleCompact();

        if (ImGui::BeginTable("table1", 3, flags))
        {
            // Display headers so we can inspect their interaction with borders
            // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them now. See other sections for details)
            if (display_headers)
            {
                ImGui::TableSetupColumn("One");
                ImGui::TableSetupColumn("Two");
                ImGui::TableSetupColumn("Three");
                ImGui::TableHeadersRow();
            }

            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    char buf[32];
                    sprintf(buf, "Hello %d,%d", column, row);
                    if (contents_type == CT_Text)
                        ImGui::TextUnformatted(buf);
                    else if (contents_type == CT_FillButton)
                        ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Resizable, stretch"))
    {
        IMGUI_DEMO_MARKER("Tables/Resizable, stretch");
        // By default, if we don't enable ScrollX the sizing policy for each column is "Stretch"
        // All columns maintain a sizing weight, and they will occupy all available width.
        static ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;
        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_Resizable", &flags, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersV", &flags, ImGuiTableFlags_BordersV);
        ImGui::SameLine(); HelpMarker(
            "Using the _Resizable flag automatically enables the _BordersInnerV flag as well, "
            "this is why the resize borders are still showing when unchecking this.");
        PopStyleCompact();

        if (ImGui::BeginTable("table1", 3, flags))
        {
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("Hello %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Resizable, fixed"))
    {
        IMGUI_DEMO_MARKER("Tables/Resizable, fixed");
        // Here we use ImGuiTableFlags_SizingFixedFit (even though _ScrollX is not set)
        // So columns will adopt the "Fixed" policy and will maintain a fixed width regardless of the whole available width (unless table is small)
        // If there is not enough available width to fit all columns, they will however be resized down.
        // FIXME-TABLE: Providing a stretch-on-init would make sense especially for tables which don't have saved settings
        HelpMarker(
            "Using _Resizable + _SizingFixedFit flags.\n"
            "Fixed-width columns generally makes more sense if you want to use horizontal scrolling.\n\n"
            "Double-click a column border to auto-fit the column to its contents.");
        PushStyleCompact();
        static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;
        ImGui::CheckboxFlags("ImGuiTableFlags_NoHostExtendX", &flags, ImGuiTableFlags_NoHostExtendX);
        PopStyleCompact();

        if (ImGui::BeginTable("table1", 3, flags))
        {
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("Hello %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Resizable, mixed"))
    {
        IMGUI_DEMO_MARKER("Tables/Resizable, mixed");
        HelpMarker(
            "Using TableSetupColumn() to alter resizing policy on a per-column basis.\n\n"
            "When combining Fixed and Stretch columns, generally you only want one, maybe two trailing columns to use _WidthStretch.");
        static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

        if (ImGui::BeginTable("table1", 3, flags))
        {
            ImGui::TableSetupColumn("AAA", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("BBB", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("CCC", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("%s %d,%d", (column == 2) ? "Stretch" : "Fixed", column, row);
                }
            }
            ImGui::EndTable();
        }
        if (ImGui::BeginTable("table2", 6, flags))
        {
            ImGui::TableSetupColumn("AAA", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("BBB", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("CCC", ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_DefaultHide);
            ImGui::TableSetupColumn("DDD", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("EEE", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("FFF", ImGuiTableColumnFlags_WidthStretch | ImGuiTableColumnFlags_DefaultHide);
            ImGui::TableHeadersRow();
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 6; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("%s %d,%d", (column >= 3) ? "Stretch" : "Fixed", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Reorderable, hideable, with headers"))
    {
        IMGUI_DEMO_MARKER("Tables/Reorderable, hideable, with headers");
        HelpMarker(
            "Click and drag column headers to reorder columns.\n\n"
            "Right-click on a header to open a context menu.");
        static ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV;
        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_Resizable", &flags, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags("ImGuiTableFlags_Reorderable", &flags, ImGuiTableFlags_Reorderable);
        ImGui::CheckboxFlags("ImGuiTableFlags_Hideable", &flags, ImGuiTableFlags_Hideable);
        ImGui::CheckboxFlags("ImGuiTableFlags_NoBordersInBody", &flags, ImGuiTableFlags_NoBordersInBody);
        ImGui::CheckboxFlags("ImGuiTableFlags_NoBordersInBodyUntilResize", &flags, ImGuiTableFlags_NoBordersInBodyUntilResize); ImGui::SameLine(); HelpMarker("Disable vertical borders in columns Body until hovered for resize (borders will always appear in Headers)");
        ImGui::CheckboxFlags("ImGuiTableFlags_HighlightHoveredColumn", &flags, ImGuiTableFlags_HighlightHoveredColumn);
        PopStyleCompact();

        if (ImGui::BeginTable("table1", 3, flags))
        {
            // Submit columns name with TableSetupColumn() and call TableHeadersRow() to create a row with a header in each column.
            // (Later we will show how TableSetupColumn() has other uses, optional flags, sizing weight etc.)
            ImGui::TableSetupColumn("One");
            ImGui::TableSetupColumn("Two");
            ImGui::TableSetupColumn("Three");
            ImGui::TableHeadersRow();
            for (int row = 0; row < 6; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("Hello %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }

        // Use outer_size.x == 0.0f instead of default to make the table as tight as possible
        // (only valid when no scrolling and no stretch column)
        if (ImGui::BeginTable("table2", 3, flags | ImGuiTableFlags_SizingFixedFit, ImVec2(0.0f, 0.0f)))
        {
            ImGui::TableSetupColumn("One");
            ImGui::TableSetupColumn("Two");
            ImGui::TableSetupColumn("Three");
            ImGui::TableHeadersRow();
            for (int row = 0; row < 6; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("Fixed %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Padding"))
    {
        IMGUI_DEMO_MARKER("Tables/Padding");
        // First example: showcase use of padding flags and effect of BorderOuterV/BorderInnerV on X padding.
        // We don't expose BorderOuterH/BorderInnerH here because they have no effect on X padding.
        HelpMarker(
            "We often want outer padding activated when any using features which makes the edges of a column visible:\n"
            "e.g.:\n"
            "- BorderOuterV\n"
            "- any form of row selection\n"
            "Because of this, activating BorderOuterV sets the default to PadOuterX. "
            "Using PadOuterX or NoPadOuterX you can override the default.\n\n"
            "Actual padding values are using style.CellPadding.\n\n"
            "In this demo we don't show horizontal borders to emphasize how they don't affect default horizontal padding.");

        static ImGuiTableFlags flags1 = ImGuiTableFlags_BordersV;
        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_PadOuterX", &flags1, ImGuiTableFlags_PadOuterX);
        ImGui::SameLine(); HelpMarker("Enable outer-most padding (default if ImGuiTableFlags_BordersOuterV is set)");
        ImGui::CheckboxFlags("ImGuiTableFlags_NoPadOuterX", &flags1, ImGuiTableFlags_NoPadOuterX);
        ImGui::SameLine(); HelpMarker("Disable outer-most padding (default if ImGuiTableFlags_BordersOuterV is not set)");
        ImGui::CheckboxFlags("ImGuiTableFlags_NoPadInnerX", &flags1, ImGuiTableFlags_NoPadInnerX);
        ImGui::SameLine(); HelpMarker("Disable inner padding between columns (double inner padding if BordersOuterV is on, single inner padding if BordersOuterV is off)");
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuterV", &flags1, ImGuiTableFlags_BordersOuterV);
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersInnerV", &flags1, ImGuiTableFlags_BordersInnerV);
        static bool show_headers = false;
        ImGui::Checkbox("show_headers", &show_headers);
        PopStyleCompact();

        if (ImGui::BeginTable("table_padding", 3, flags1))
        {
            if (show_headers)
            {
                ImGui::TableSetupColumn("One");
                ImGui::TableSetupColumn("Two");
                ImGui::TableSetupColumn("Three");
                ImGui::TableHeadersRow();
            }

            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    if (row == 0)
                    {
                        ImGui::Text("Avail %.2f", ImGui::GetContentRegionAvail().x);
                    }
                    else
                    {
                        char buf[32];
                        sprintf(buf, "Hello %d,%d", column, row);
                        ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
                    }
                    //if (ImGui::TableGetColumnFlags() & ImGuiTableColumnFlags_IsHovered)
                    //    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, IM_COL32(0, 100, 0, 255));
                }
            }
            ImGui::EndTable();
        }

        // Second example: set style.CellPadding to (0.0) or a custom value.
        // FIXME-TABLE: Vertical border effectively not displayed the same way as horizontal one...
        HelpMarker("Setting style.CellPadding to (0,0) or a custom value.");
        static ImGuiTableFlags flags2 = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
        static ImVec2 cell_padding(0.0f, 0.0f);
        static bool show_widget_frame_bg = true;

        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_Borders", &flags2, ImGuiTableFlags_Borders);
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersH", &flags2, ImGuiTableFlags_BordersH);
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersV", &flags2, ImGuiTableFlags_BordersV);
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersInner", &flags2, ImGuiTableFlags_BordersInner);
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuter", &flags2, ImGuiTableFlags_BordersOuter);
        ImGui::CheckboxFlags("ImGuiTableFlags_RowBg", &flags2, ImGuiTableFlags_RowBg);
        ImGui::CheckboxFlags("ImGuiTableFlags_Resizable", &flags2, ImGuiTableFlags_Resizable);
        ImGui::Checkbox("show_widget_frame_bg", &show_widget_frame_bg);
        ImGui::SliderFloat2("CellPadding", &cell_padding.x, 0.0f, 10.0f, "%.0f");
        PopStyleCompact();

        ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, cell_padding);
        if (ImGui::BeginTable("table_padding_2", 3, flags2))
        {
            static char text_bufs[3 * 5][16]; // Mini text storage for 3x5 cells
            static bool init = true;
            if (!show_widget_frame_bg)
                ImGui::PushStyleColor(ImGuiCol_FrameBg, 0);
            for (int cell = 0; cell < 3 * 5; cell++)
            {
                ImGui::TableNextColumn();
                if (init)
                    strcpy(text_bufs[cell], "edit me");
                ImGui::SetNextItemWidth(-FLT_MIN);
                ImGui::PushID(cell);
                ImGui::InputText("##cell", text_bufs[cell], IM_COUNTOF(text_bufs[cell]));
                ImGui::PopID();
            }
            if (!show_widget_frame_bg)
                ImGui::PopStyleColor();
            init = false;
            ImGui::EndTable();
        }
        ImGui::PopStyleVar();

        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Sizing policies"))
    {
        IMGUI_DEMO_MARKER("Tables/Explicit widths");
        static ImGuiTableFlags flags1 = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_RowBg | ImGuiTableFlags_ContextMenuInBody;
        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_Resizable", &flags1, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags("ImGuiTableFlags_NoHostExtendX", &flags1, ImGuiTableFlags_NoHostExtendX);
        PopStyleCompact();

        static ImGuiTableFlags sizing_policy_flags[4] = { ImGuiTableFlags_SizingFixedFit, ImGuiTableFlags_SizingFixedSame, ImGuiTableFlags_SizingStretchProp, ImGuiTableFlags_SizingStretchSame };
        for (int table_n = 0; table_n < 4; table_n++)
        {
            ImGui::PushID(table_n);
            ImGui::SetNextItemWidth(TEXT_BASE_WIDTH * 30);
            EditTableSizingFlags(&sizing_policy_flags[table_n]);

            // To make it easier to understand the different sizing policy,
            // For each policy: we display one table where the columns have equal contents width,
            // and one where the columns have different contents width.
            if (ImGui::BeginTable("table1", 3, sizing_policy_flags[table_n] | flags1))
            {
                for (int row = 0; row < 3; row++)
                {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn(); ImGui::Text("Oh dear");
                    ImGui::TableNextColumn(); ImGui::Text("Oh dear");
                    ImGui::TableNextColumn(); ImGui::Text("Oh dear");
                }
                ImGui::EndTable();
            }
            if (ImGui::BeginTable("table2", 3, sizing_policy_flags[table_n] | flags1))
            {
                for (int row = 0; row < 3; row++)
                {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn(); ImGui::Text("AAAA");
                    ImGui::TableNextColumn(); ImGui::Text("BBBBBBBB");
                    ImGui::TableNextColumn(); ImGui::Text("CCCCCCCCCCCC");
                }
                ImGui::EndTable();
            }
            ImGui::PopID();
        }

        ImGui::Spacing();
        ImGui::TextUnformatted("Advanced");
        ImGui::SameLine();
        HelpMarker(
            "This section allows you to interact and see the effect of various sizing policies "
            "depending on whether Scroll is enabled and the contents of your columns.");

        enum ContentsType { CT_ShowWidth, CT_ShortText, CT_LongText, CT_Button, CT_FillButton, CT_InputText };
        static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_Resizable;
        static int contents_type = CT_ShowWidth;
        static int column_count = 3;

        PushStyleCompact();
        ImGui::PushID("Advanced");
        ImGui::PushItemWidth(TEXT_BASE_WIDTH * 30);
        EditTableSizingFlags(&flags);
        ImGui::Combo("Contents", &contents_type, "Show width\0Short Text\0Long Text\0Button\0Fill Button\0InputText\0");
        if (contents_type == CT_FillButton)
        {
            ImGui::SameLine();
            HelpMarker(
                "Be mindful that using right-alignment (e.g. size.x = -FLT_MIN) creates a feedback loop "
                "where contents width can feed into auto-column width can feed into contents width.");
        }
        ImGui::DragInt("Columns", &column_count, 0.1f, 1, 64, "%d", ImGuiSliderFlags_AlwaysClamp);
        ImGui::CheckboxFlags("ImGuiTableFlags_Resizable", &flags, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags("ImGuiTableFlags_PreciseWidths", &flags, ImGuiTableFlags_PreciseWidths);
        ImGui::SameLine(); HelpMarker("Disable distributing remainder width to stretched columns (width allocation on a 100-wide table with 3 columns: Without this flag: 33,33,34. With this flag: 33,33,33). With larger number of columns, resizing will appear to be less smooth.");
        ImGui::CheckboxFlags("ImGuiTableFlags_ScrollX", &flags, ImGuiTableFlags_ScrollX);
        ImGui::CheckboxFlags("ImGuiTableFlags_ScrollY", &flags, ImGuiTableFlags_ScrollY);
        ImGui::CheckboxFlags("ImGuiTableFlags_NoClip", &flags, ImGuiTableFlags_NoClip);
        ImGui::PopItemWidth();
        ImGui::PopID();
        PopStyleCompact();

        if (ImGui::BeginTable("table2", column_count, flags, ImVec2(0.0f, TEXT_BASE_HEIGHT * 7)))
        {
            for (int cell = 0; cell < 10 * column_count; cell++)
            {
                ImGui::TableNextColumn();
                int column = ImGui::TableGetColumnIndex();
                int row = ImGui::TableGetRowIndex();

                ImGui::PushID(cell);
                char label[32];
                static char text_buf[32] = "";
                sprintf(label, "Hello %d,%d", column, row);
                switch (contents_type)
                {
                case CT_ShortText:  ImGui::TextUnformatted(label); break;
                case CT_LongText:   ImGui::Text("Some %s text %d,%d\nOver two lines..", column == 0 ? "long" : "longeeer", column, row); break;
                case CT_ShowWidth:  ImGui::Text("W: %.1f", ImGui::GetContentRegionAvail().x); break;
                case CT_Button:     ImGui::Button(label); break;
                case CT_FillButton: ImGui::Button(label, ImVec2(-FLT_MIN, 0.0f)); break;
                case CT_InputText:  ImGui::SetNextItemWidth(-FLT_MIN); ImGui::InputText("##", text_buf, IM_COUNTOF(text_buf)); break;
                }
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Vertical scrolling, with clipping"))
    {
        IMGUI_DEMO_MARKER("Tables/Vertical scrolling, with clipping");
        HelpMarker(
            "Here we activate ScrollY, which will create a child window container to allow hosting scrollable contents.\n\n"
            "We also demonstrate using ImGuiListClipper to virtualize the submission of many items.");
        static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;

        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_ScrollY", &flags, ImGuiTableFlags_ScrollY);
        PopStyleCompact();

        // When using ScrollX or ScrollY we need to specify a size for our table container!
        // Otherwise by default the table will fit all available space, like a BeginChild() call.
        ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 8);
        if (ImGui::BeginTable("table_scrolly", 3, flags, outer_size))
        {
            ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
            ImGui::TableSetupColumn("One", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("Two", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("Three", ImGuiTableColumnFlags_None);
            ImGui::TableHeadersRow();

            // Demonstrate using clipper for large vertical lists
            ImGuiListClipper clipper;
            clipper.Begin(1000);
            while (clipper.Step())
            {
                for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
                {
                    ImGui::TableNextRow();
                    for (int column = 0; column < 3; column++)
                    {
                        ImGui::TableSetColumnIndex(column);
                        ImGui::Text("Hello %d,%d", column, row);
                    }
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Horizontal scrolling"))
    {
        IMGUI_DEMO_MARKER("Tables/Horizontal scrolling");
        HelpMarker(
            "When ScrollX is enabled, the default sizing policy becomes ImGuiTableFlags_SizingFixedFit, "
            "as automatically stretching columns doesn't make much sense with horizontal scrolling.\n\n"
            "Also note that as of the current version, you will almost always want to enable ScrollY along with ScrollX, "
            "because the container window won't automatically extend vertically to fix contents "
            "(this may be improved in future versions).");
        static ImGuiTableFlags flags = ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;
        static int freeze_cols = 1;
        static int freeze_rows = 1;

        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_Resizable", &flags, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags("ImGuiTableFlags_ScrollX", &flags, ImGuiTableFlags_ScrollX);
        ImGui::CheckboxFlags("ImGuiTableFlags_ScrollY", &flags, ImGuiTableFlags_ScrollY);
        ImGui::SetNextItemWidth(ImGui::GetFrameHeight());
        ImGui::DragInt("freeze_cols", &freeze_cols, 0.2f, 0, 9, NULL, ImGuiSliderFlags_NoInput);
        ImGui::SetNextItemWidth(ImGui::GetFrameHeight());
        ImGui::DragInt("freeze_rows", &freeze_rows, 0.2f, 0, 9, NULL, ImGuiSliderFlags_NoInput);
        PopStyleCompact();

        // When using ScrollX or ScrollY we need to specify a size for our table container!
        // Otherwise by default the table will fit all available space, like a BeginChild() call.
        ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 8);
        if (ImGui::BeginTable("table_scrollx", 7, flags, outer_size))
        {
            ImGui::TableSetupScrollFreeze(freeze_cols, freeze_rows);
            ImGui::TableSetupColumn("Line #", ImGuiTableColumnFlags_NoHide); // Make the first column not hideable to match our use of TableSetupScrollFreeze()
            ImGui::TableSetupColumn("One");
            ImGui::TableSetupColumn("Two");
            ImGui::TableSetupColumn("Three");
            ImGui::TableSetupColumn("Four");
            ImGui::TableSetupColumn("Five");
            ImGui::TableSetupColumn("Six");
            ImGui::TableHeadersRow();
            for (int row = 0; row < 20; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 7; column++)
                {
                    // Both TableNextColumn() and TableSetColumnIndex() return true when a column is visible or performing width measurement.
                    // Because here we know that:
                    // - A) all our columns are contributing the same to row height
                    // - B) column 0 is always visible,
                    // We only always submit this one column and can skip others.
                    // More advanced per-column clipping behaviors may benefit from polling the status flags via TableGetColumnFlags().
                    if (!ImGui::TableSetColumnIndex(column) && column > 0)
                        continue;
                    if (column == 0)
                        ImGui::Text("Line %d", row);
                    else
                        ImGui::Text("Hello world %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }

        ImGui::Spacing();
        ImGui::TextUnformatted("Stretch + ScrollX");
        ImGui::SameLine();
        HelpMarker(
            "Showcase using Stretch columns + ScrollX together: "
            "this is rather unusual and only makes sense when specifying an 'inner_width' for the table!\n"
            "Without an explicit value, inner_width is == outer_size.x and therefore using Stretch columns "
            "along with ScrollX doesn't make sense.");
        static ImGuiTableFlags flags2 = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_RowBg | ImGuiTableFlags_ContextMenuInBody;
        static float inner_width = 1000.0f;
        PushStyleCompact();
        ImGui::PushID("flags3");
        ImGui::PushItemWidth(TEXT_BASE_WIDTH * 30);
        ImGui::CheckboxFlags("ImGuiTableFlags_ScrollX", &flags2, ImGuiTableFlags_ScrollX);
        ImGui::DragFloat("inner_width", &inner_width, 1.0f, 0.0f, FLT_MAX, "%.1f");
        ImGui::PopItemWidth();
        ImGui::PopID();
        PopStyleCompact();
        if (ImGui::BeginTable("table2", 7, flags2, outer_size, inner_width))
        {
            for (int cell = 0; cell < 20 * 7; cell++)
            {
                ImGui::TableNextColumn();
                ImGui::Text("Hello world %d,%d", ImGui::TableGetColumnIndex(), ImGui::TableGetRowIndex());
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Columns flags"))
    {
        IMGUI_DEMO_MARKER("Tables/Columns flags");
        // Create a first table just to show all the options/flags we want to make visible in our example!
        const int column_count = 3;
        const char* column_names[column_count] = { "One", "Two", "Three" };
        static ImGuiTableColumnFlags column_flags[column_count] = { ImGuiTableColumnFlags_DefaultSort, ImGuiTableColumnFlags_None, ImGuiTableColumnFlags_DefaultHide };
        static ImGuiTableColumnFlags column_flags_out[column_count] = { 0, 0, 0 }; // Output from TableGetColumnFlags()

        if (ImGui::BeginTable("table_columns_flags_checkboxes", column_count, ImGuiTableFlags_None))
        {
            PushStyleCompact();
            for (int column = 0; column < column_count; column++)
            {
                ImGui::TableNextColumn();
                ImGui::PushID(column);
                ImGui::AlignTextToFramePadding(); // FIXME-TABLE: Workaround for wrong text baseline propagation across columns
                ImGui::Text("'%s'", column_names[column]);
                ImGui::Spacing();
                ImGui::Text("Input flags:");
                EditTableColumnsFlags(&column_flags[column]);
                ImGui::Spacing();
                ImGui::Text("Output flags:");
                ImGui::BeginDisabled();
                ShowTableColumnsStatusFlags(column_flags_out[column]);
                ImGui::EndDisabled();
                ImGui::PopID();
            }
            PopStyleCompact();
            ImGui::EndTable();
        }

        // Create the real table we care about for the example!
        // We use a scrolling table to be able to showcase the difference between the _IsEnabled and _IsVisible flags above,
        // otherwise in a non-scrolling table columns are always visible (unless using ImGuiTableFlags_NoKeepColumnsVisible
        // + resizing the parent window down).
        const ImGuiTableFlags flags
            = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
            | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV
            | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable;
        ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 9);
        if (ImGui::BeginTable("table_columns_flags", column_count, flags, outer_size))
        {
            bool has_angled_header = false;
            for (int column = 0; column < column_count; column++)
            {
                has_angled_header |= (column_flags[column] & ImGuiTableColumnFlags_AngledHeader) != 0;
                ImGui::TableSetupColumn(column_names[column], column_flags[column]);
            }
            if (has_angled_header)
                ImGui::TableAngledHeadersRow();
            ImGui::TableHeadersRow();
            for (int column = 0; column < column_count; column++)
                column_flags_out[column] = ImGui::TableGetColumnFlags(column);
            float indent_step = (float)((int)TEXT_BASE_WIDTH / 2);
            for (int row = 0; row < 8; row++)
            {
                // Add some indentation to demonstrate usage of per-column IndentEnable/IndentDisable flags.
                ImGui::Indent(indent_step);
                ImGui::TableNextRow();
                for (int column = 0; column < column_count; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("%s %s", (column == 0) ? "Indented" : "Hello", ImGui::TableGetColumnName(column));
                }
            }
            ImGui::Unindent(indent_step * 8.0f);

            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Columns widths"))
    {
        IMGUI_DEMO_MARKER("Tables/Columns widths");
        HelpMarker("Using TableSetupColumn() to setup default width.");

        static ImGuiTableFlags flags1 = ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBodyUntilResize;
        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_Resizable", &flags1, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags("ImGuiTableFlags_NoBordersInBodyUntilResize", &flags1, ImGuiTableFlags_NoBordersInBodyUntilResize);
        PopStyleCompact();
        if (ImGui::BeginTable("table1", 3, flags1))
        {
            // We could also set ImGuiTableFlags_SizingFixedFit on the table and all columns will default to ImGuiTableColumnFlags_WidthFixed.
            ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 100.0f); // Default to 100.0f
            ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, 200.0f); // Default to 200.0f
            ImGui::TableSetupColumn("three", ImGuiTableColumnFlags_WidthFixed);       // Default to auto
            ImGui::TableHeadersRow();
            for (int row = 0; row < 4; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    if (row == 0)
                        ImGui::Text("(w: %5.1f)", ImGui::GetContentRegionAvail().x);
                    else
                        ImGui::Text("Hello %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }

        HelpMarker(
            "Using TableSetupColumn() to setup explicit width.\n\nUnless _NoKeepColumnsVisible is set, "
            "fixed columns with set width may still be shrunk down if there's not enough space in the host.");

        static ImGuiTableFlags flags2 = ImGuiTableFlags_None;
        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_NoKeepColumnsVisible", &flags2, ImGuiTableFlags_NoKeepColumnsVisible);
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersInnerV", &flags2, ImGuiTableFlags_BordersInnerV);
        ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuterV", &flags2, ImGuiTableFlags_BordersOuterV);
        PopStyleCompact();
        if (ImGui::BeginTable("table2", 4, flags2))
        {
            // We could also set ImGuiTableFlags_SizingFixedFit on the table and then all columns
            // will default to ImGuiTableColumnFlags_WidthFixed.
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 100.0f);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 15.0f);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 30.0f);
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 15.0f);
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 4; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    if (row == 0)
                        ImGui::Text("(w: %5.1f)", ImGui::GetContentRegionAvail().x);
                    else
                        ImGui::Text("Hello %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Nested tables"))
    {
        IMGUI_DEMO_MARKER("Tables/Nested tables");
        HelpMarker("This demonstrates embedding a table into another table cell.");

        if (ImGui::BeginTable("table_nested1", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable))
        {
            ImGui::TableSetupColumn("A0");
            ImGui::TableSetupColumn("A1");
            ImGui::TableHeadersRow();

            ImGui::TableNextColumn();
            ImGui::Text("A0 Row 0");
            {
                float rows_height = (TEXT_BASE_HEIGHT * 2.0f) + (ImGui::GetStyle().CellPadding.y * 2.0f);
                if (ImGui::BeginTable("table_nested2", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable))
                {
                    ImGui::TableSetupColumn("B0");
                    ImGui::TableSetupColumn("B1");
                    ImGui::TableHeadersRow();

                    ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                    ImGui::TableNextColumn();
                    ImGui::Text("B0 Row 0");
                    ImGui::TableNextColumn();
                    ImGui::Text("B1 Row 0");
                    ImGui::TableNextRow(ImGuiTableRowFlags_None, rows_height);
                    ImGui::TableNextColumn();
                    ImGui::Text("B0 Row 1");
                    ImGui::TableNextColumn();
                    ImGui::Text("B1 Row 1");

                    ImGui::EndTable();
                }
            }
            ImGui::TableNextColumn(); ImGui::Text("A1 Row 0");
            ImGui::TableNextColumn(); ImGui::Text("A0 Row 1");
            ImGui::TableNextColumn(); ImGui::Text("A1 Row 1");
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Row height"))
    {
        IMGUI_DEMO_MARKER("Tables/Row height");
        HelpMarker(
            "You can pass a 'min_row_height' to TableNextRow().\n\nRows are padded with 'style.CellPadding.y' on top and bottom, "
            "so effectively the minimum row height will always be >= 'style.CellPadding.y * 2.0f'.\n\n"
            "We cannot honor a _maximum_ row height as that would require a unique clipping rectangle per row.");
        if (ImGui::BeginTable("table_row_height", 1, ImGuiTableFlags_Borders))
        {
            for (int row = 0; row < 8; row++)
            {
                float min_row_height = (float)(int)(TEXT_BASE_HEIGHT * 0.30f * row + ImGui::GetStyle().CellPadding.y * 2.0f);
                ImGui::TableNextRow(ImGuiTableRowFlags_None, min_row_height);
                ImGui::TableNextColumn();
                ImGui::Text("min_row_height = %.2f", min_row_height);
            }
            ImGui::EndTable();
        }

        HelpMarker(
            "Showcase using SameLine(0,0) to share Current Line Height between cells.\n\n"
            "Please note that Tables Row Height is not the same thing as Current Line Height, "
            "as a table cell may contains multiple lines.");
        if (ImGui::BeginTable("table_share_lineheight", 2, ImGuiTableFlags_Borders))
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::ColorButton("##1", ImVec4(0.13f, 0.26f, 0.40f, 1.0f), ImGuiColorEditFlags_None, ImVec2(40, 40));
            ImGui::TableNextColumn();
            ImGui::Text("Line 1");
            ImGui::Text("Line 2");

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::ColorButton("##2", ImVec4(0.13f, 0.26f, 0.40f, 1.0f), ImGuiColorEditFlags_None, ImVec2(40, 40));
            ImGui::TableNextColumn();
            ImGui::SameLine(0.0f, 0.0f); // Reuse line height from previous column
            ImGui::Text("Line 1, with SameLine(0,0)");
            ImGui::Text("Line 2");

            ImGui::EndTable();
        }

        HelpMarker("Showcase altering CellPadding.y between rows. Note that CellPadding.x is locked for the entire table.");
        if (ImGui::BeginTable("table_changing_cellpadding_y", 1, ImGuiTableFlags_Borders))
        {
            ImGuiStyle& style = ImGui::GetStyle();
            for (int row = 0; row < 8; row++)
            {
                if ((row % 3) == 2)
                    ImGui::PushStyleVarY(ImGuiStyleVar_CellPadding, 20.0f);
                ImGui::TableNextRow(ImGuiTableRowFlags_None);
                ImGui::TableNextColumn();
                ImGui::Text("CellPadding.y = %.2f", style.CellPadding.y);
                if ((row % 3) == 2)
                    ImGui::PopStyleVar();
            }
            ImGui::EndTable();
        }

        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Outer size"))
    {
        IMGUI_DEMO_MARKER("Tables/Outer size");
        // Showcasing use of ImGuiTableFlags_NoHostExtendX and ImGuiTableFlags_NoHostExtendY
        // Important to that note how the two flags have slightly different behaviors!
        ImGui::Text("Using NoHostExtendX and NoHostExtendY:");
        PushStyleCompact();
        static ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_ContextMenuInBody | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoHostExtendX;
        ImGui::CheckboxFlags("ImGuiTableFlags_NoHostExtendX", &flags, ImGuiTableFlags_NoHostExtendX);
        ImGui::SameLine(); HelpMarker("Make outer width auto-fit to columns, overriding outer_size.x value.\n\nOnly available when ScrollX/ScrollY are disabled and Stretch columns are not used.");
        ImGui::CheckboxFlags("ImGuiTableFlags_NoHostExtendY", &flags, ImGuiTableFlags_NoHostExtendY);
        ImGui::SameLine(); HelpMarker("Make outer height stop exactly at outer_size.y (prevent auto-extending table past the limit).\n\nOnly available when ScrollX/ScrollY are disabled. Data below the limit will be clipped and not visible.");
        PopStyleCompact();

        ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 5.5f);
        if (ImGui::BeginTable("table1", 3, flags, outer_size))
        {
            for (int row = 0; row < 10; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableNextColumn();
                    ImGui::Text("Cell %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::SameLine();
        ImGui::Text("Hello!");

        ImGui::Spacing();

        ImGui::Text("Using explicit size:");
        if (ImGui::BeginTable("table2", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg, ImVec2(TEXT_BASE_WIDTH * 30, 0.0f)))
        {
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableNextColumn();
                    ImGui::Text("Cell %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }
        ImGui::SameLine();
        if (ImGui::BeginTable("table3", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg, ImVec2(TEXT_BASE_WIDTH * 30, 0.0f)))
        {
            const float rows_height = TEXT_BASE_HEIGHT * 1.5f + ImGui::GetStyle().CellPadding.y * 2.0f;
            for (int row = 0; row < 3; row++)
            {
                ImGui::TableNextRow(0, rows_height);
                for (int column = 0; column < 3; column++)
                {
                    ImGui::TableNextColumn();
                    ImGui::Text("Cell %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }

        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Background color"))
    {
        IMGUI_DEMO_MARKER("Tables/Background color");
        static ImGuiTableFlags flags = ImGuiTableFlags_RowBg;
        static int row_bg_type = 1;
        static int row_bg_target = 1;
        static int cell_bg_type = 1;

        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_Borders", &flags, ImGuiTableFlags_Borders);
        ImGui::CheckboxFlags("ImGuiTableFlags_RowBg", &flags, ImGuiTableFlags_RowBg);
        ImGui::SameLine(); HelpMarker("ImGuiTableFlags_RowBg automatically sets RowBg0 to alternative colors pulled from the Style.");
        ImGui::Combo("row bg type", (int*)&row_bg_type, "None\0Red\0Gradient\0");
        ImGui::Combo("row bg target", (int*)&row_bg_target, "RowBg0\0RowBg1\0"); ImGui::SameLine(); HelpMarker("Target RowBg0 to override the alternating odd/even colors,\nTarget RowBg1 to blend with them.");
        ImGui::Combo("cell bg type", (int*)&cell_bg_type, "None\0Blue\0"); ImGui::SameLine(); HelpMarker("We are colorizing cells to B1->C2 here.");
        IM_ASSERT(row_bg_type >= 0 && row_bg_type <= 2);
        IM_ASSERT(row_bg_target >= 0 && row_bg_target <= 1);
        IM_ASSERT(cell_bg_type >= 0 && cell_bg_type <= 1);
        PopStyleCompact();

        if (ImGui::BeginTable("table1", 5, flags))
        {
            for (int row = 0; row < 6; row++)
            {
                ImGui::TableNextRow();

                // Demonstrate setting a row background color with 'ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBgX, ...)'
                // We use a transparent color so we can see the one behind in case our target is RowBg1 and RowBg0 was already targeted by the ImGuiTableFlags_RowBg flag.
                if (row_bg_type != 0)
                {
                    ImU32 row_bg_color = ImGui::GetColorU32(row_bg_type == 1 ? ImVec4(0.7f, 0.3f, 0.3f, 0.65f) : ImVec4(0.2f + row * 0.1f, 0.2f, 0.2f, 0.65f)); // Flat or Gradient?
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0 + row_bg_target, row_bg_color);
                }

                // Fill cells
                for (int column = 0; column < 5; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("%c%c", 'A' + row, '0' + column);

                    // Change background of Cells B1->C2
                    // Demonstrate setting a cell background color with 'ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ...)'
                    // (the CellBg color will be blended over the RowBg and ColumnBg colors)
                    // We can also pass a column number as a third parameter to TableSetBgColor() and do this outside the column loop.
                    if (row >= 1 && row <= 2 && column >= 1 && column <= 2 && cell_bg_type == 1)
                    {
                        ImU32 cell_bg_color = ImGui::GetColorU32(ImVec4(0.3f, 0.3f, 0.7f, 0.65f));
                        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, cell_bg_color);
                    }
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Tree view"))
    {
        IMGUI_DEMO_MARKER("Tables/Tree view");
        static ImGuiTableFlags table_flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;

        static ImGuiTreeNodeFlags tree_node_flags_base = ImGuiTreeNodeFlags_SpanAllColumns | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_DrawLinesFull;
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanFullWidth",  &tree_node_flags_base, ImGuiTreeNodeFlags_SpanFullWidth);
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanLabelWidth",  &tree_node_flags_base, ImGuiTreeNodeFlags_SpanLabelWidth);
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanAllColumns", &tree_node_flags_base, ImGuiTreeNodeFlags_SpanAllColumns);
        ImGui::CheckboxFlags("ImGuiTreeNodeFlags_LabelSpanAllColumns", &tree_node_flags_base, ImGuiTreeNodeFlags_LabelSpanAllColumns);
        ImGui::SameLine(); HelpMarker("Useful if you know that you aren't displaying contents in other columns");

        HelpMarker("See \"Columns flags\" section to configure how indentation is applied to individual columns.");
        if (ImGui::BeginTable("3ways", 3, table_flags))
        {
            // The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_NoHide);
            ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 12.0f);
            ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, TEXT_BASE_WIDTH * 18.0f);
            ImGui::TableHeadersRow();

            // Simple storage to output a dummy file-system.
            struct MyTreeNode
            {
                const char*     Name;
                const char*     Type;
                int             Size;
                int             ChildIdx;
                int             ChildCount;
                static void DisplayNode(const MyTreeNode* node, const MyTreeNode* all_nodes)
                {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    const bool is_folder = (node->ChildCount > 0);

                    ImGuiTreeNodeFlags node_flags = tree_node_flags_base;
                    if (node != &all_nodes[0])
                        node_flags &= ~ImGuiTreeNodeFlags_LabelSpanAllColumns; // Only demonstrate this on the root node.

                    if (is_folder)
                    {
                        bool open = ImGui::TreeNodeEx(node->Name, node_flags);
                        if ((node_flags & ImGuiTreeNodeFlags_LabelSpanAllColumns) == 0)
                        {
                            ImGui::TableNextColumn();
                            ImGui::TextDisabled("--");
                            ImGui::TableNextColumn();
                            ImGui::TextUnformatted(node->Type);
                        }
                        if (open)
                        {
                            for (int child_n = 0; child_n < node->ChildCount; child_n++)
                                DisplayNode(&all_nodes[node->ChildIdx + child_n], all_nodes);
                            ImGui::TreePop();
                        }
                    }
                    else
                    {
                        ImGui::TreeNodeEx(node->Name, node_flags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen);
                        ImGui::TableNextColumn();
                        ImGui::Text("%d", node->Size);
                        ImGui::TableNextColumn();
                        ImGui::TextUnformatted(node->Type);
                    }
                }
            };
            static const MyTreeNode nodes[] =
            {
                { "Root with Long Name",          "Folder",       -1,       1, 3    }, // 0
                { "Music",                        "Folder",       -1,       4, 2    }, // 1
                { "Textures",                     "Folder",       -1,       6, 3    }, // 2
                { "desktop.ini",                  "System file",  1024,    -1,-1    }, // 3
                { "File1_a.wav",                  "Audio file",   123000,  -1,-1    }, // 4
                { "File1_b.wav",                  "Audio file",   456000,  -1,-1    }, // 5
                { "Image001.png",                 "Image file",   203128,  -1,-1    }, // 6
                { "Copy of Image001.png",         "Image file",   203256,  -1,-1    }, // 7
                { "Copy of Image001 (Final2).png","Image file",   203512,  -1,-1    }, // 8
            };

            MyTreeNode::DisplayNode(&nodes[0], nodes);

            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Item width"))
    {
        IMGUI_DEMO_MARKER("Tables/Item width");
        HelpMarker(
            "Showcase using PushItemWidth() and how it is preserved on a per-column basis.\n\n"
            "Note that on auto-resizing non-resizable fixed columns, querying the content width for "
            "e.g. right-alignment doesn't make sense.");
        if (ImGui::BeginTable("table_item_width", 3, ImGuiTableFlags_Borders))
        {
            ImGui::TableSetupColumn("small");
            ImGui::TableSetupColumn("half");
            ImGui::TableSetupColumn("right-align");
            ImGui::TableHeadersRow();

            for (int row = 0; row < 3; row++)
            {
                ImGui::TableNextRow();
                if (row == 0)
                {
                    // Setup ItemWidth once (instead of setting up every time, which is also possible but less efficient)
                    ImGui::TableSetColumnIndex(0);
                    ImGui::PushItemWidth(TEXT_BASE_WIDTH * 3.0f); // Small
                    ImGui::TableSetColumnIndex(1);
                    ImGui::PushItemWidth(-ImGui::GetContentRegionAvail().x * 0.5f);
                    ImGui::TableSetColumnIndex(2);
                    ImGui::PushItemWidth(-FLT_MIN); // Right-aligned
                }

                // Draw our contents
                static float dummy_f = 0.0f;
                ImGui::PushID(row);
                ImGui::TableSetColumnIndex(0);
                ImGui::SliderFloat("float0", &dummy_f, 0.0f, 1.0f);
                ImGui::TableSetColumnIndex(1);
                ImGui::SliderFloat("float1", &dummy_f, 0.0f, 1.0f);
                ImGui::TableSetColumnIndex(2);
                ImGui::SliderFloat("##float2", &dummy_f, 0.0f, 1.0f); // No visible label since right-aligned
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    // Demonstrate using TableHeader() calls instead of TableHeadersRow()
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Custom headers"))
    {
        IMGUI_DEMO_MARKER("Tables/Custom headers");
        const int COLUMNS_COUNT = 3;
        if (ImGui::BeginTable("table_custom_headers", COLUMNS_COUNT, ImGuiTableFlags_Borders | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable))
        {
            ImGui::TableSetupColumn("Apricot");
            ImGui::TableSetupColumn("Banana");
            ImGui::TableSetupColumn("Cherry");

            // Dummy entire-column selection storage
            // FIXME: It would be nice to actually demonstrate full-featured selection using those checkbox.
            static bool column_selected[3] = {};

            // Instead of calling TableHeadersRow() we'll submit custom headers ourselves.
            // (A different approach is also possible:
            //    - Specify ImGuiTableColumnFlags_NoHeaderLabel in some TableSetupColumn() call.
            //    - Call TableHeadersRow() normally. This will submit TableHeader() with no name.
            //    - Then call TableSetColumnIndex() to position yourself in the column and submit your stuff e.g. Checkbox().)
            ImGui::TableNextRow(ImGuiTableRowFlags_Headers);
            for (int column = 0; column < COLUMNS_COUNT; column++)
            {
                ImGui::TableSetColumnIndex(column);
                const char* column_name = ImGui::TableGetColumnName(column); // Retrieve name passed to TableSetupColumn()
                ImGui::PushID(column);
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
                ImGui::Checkbox("##checkall", &column_selected[column]);
                ImGui::PopStyleVar();
                ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                ImGui::TableHeader(column_name);
                ImGui::PopID();
            }

            // Submit table contents
            for (int row = 0; row < 5; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++)
                {
                    char buf[32];
                    sprintf(buf, "Cell %d,%d", column, row);
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Selectable(buf, column_selected[column]);
                }
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    // Demonstrate using ImGuiTableColumnFlags_AngledHeader flag to create angled headers
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Angled headers"))
    {
        IMGUI_DEMO_MARKER("Tables/Angled headers");
        const char* column_names[] = { "Track", "cabasa", "ride", "smash", "tom-hi", "tom-mid", "tom-low", "hihat-o", "hihat-c", "snare-s", "snare-c", "clap", "rim", "kick" };
        const int columns_count = IM_COUNTOF(column_names);
        const int rows_count = 12;

        static ImGuiTableFlags table_flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_Hideable | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_HighlightHoveredColumn;
        static ImGuiTableColumnFlags column_flags = ImGuiTableColumnFlags_AngledHeader | ImGuiTableColumnFlags_WidthFixed;
        static bool bools[columns_count * rows_count] = {}; // Dummy storage selection storage
        static int frozen_cols = 1;
        static int frozen_rows = 2;
        ImGui::CheckboxFlags("_ScrollX", &table_flags, ImGuiTableFlags_ScrollX);
        ImGui::CheckboxFlags("_ScrollY", &table_flags, ImGuiTableFlags_ScrollY);
        ImGui::CheckboxFlags("_Resizable", &table_flags, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags("_Sortable", &table_flags, ImGuiTableFlags_Sortable);
        ImGui::CheckboxFlags("_NoBordersInBody", &table_flags, ImGuiTableFlags_NoBordersInBody);
        ImGui::CheckboxFlags("_HighlightHoveredColumn", &table_flags, ImGuiTableFlags_HighlightHoveredColumn);
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ImGui::SliderInt("Frozen columns", &frozen_cols, 0, 2);
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ImGui::SliderInt("Frozen rows", &frozen_rows, 0, 2);
        ImGui::CheckboxFlags("Disable header contributing to column width", &column_flags, ImGuiTableColumnFlags_NoHeaderWidth);

        if (ImGui::TreeNode("Style settings"))
        {
            ImGui::SameLine();
            HelpMarker("Giving access to some ImGuiStyle value in this demo for convenience.");
            ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
            ImGui::SliderAngle("style.TableAngledHeadersAngle", &ImGui::GetStyle().TableAngledHeadersAngle, -50.0f, +50.0f);
            ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
            ImGui::SliderFloat2("style.TableAngledHeadersTextAlign", (float*)&ImGui::GetStyle().TableAngledHeadersTextAlign, 0.0f, 1.0f, "%.2f");
            ImGui::TreePop();
        }

        if (ImGui::BeginTable("table_angled_headers", columns_count, table_flags, ImVec2(0.0f, TEXT_BASE_HEIGHT * 12)))
        {
            ImGui::TableSetupColumn(column_names[0], ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoReorder);
            for (int n = 1; n < columns_count; n++)
                ImGui::TableSetupColumn(column_names[n], column_flags);
            ImGui::TableSetupScrollFreeze(frozen_cols, frozen_rows);

            ImGui::TableAngledHeadersRow(); // Draw angled headers for all columns with the ImGuiTableColumnFlags_AngledHeader flag.
            ImGui::TableHeadersRow();       // Draw remaining headers and allow access to context-menu and other functions.
            for (int row = 0; row < rows_count; row++)
            {
                ImGui::PushID(row);
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::AlignTextToFramePadding();
                ImGui::Text("Track %d", row);
                for (int column = 1; column < columns_count; column++)
                    if (ImGui::TableSetColumnIndex(column))
                    {
                        ImGui::PushID(column);
                        ImGui::Checkbox("", &bools[row * columns_count + column]);
                        ImGui::PopID();
                    }
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    // Demonstrate creating custom context menus inside columns,
    // while playing it nice with context menus provided by TableHeadersRow()/TableHeader()
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Context menus"))
    {
        IMGUI_DEMO_MARKER("Tables/Context menus");
        HelpMarker(
            "By default, right-clicking over a TableHeadersRow()/TableHeader() line will open the default context-menu.\n"
            "Using ImGuiTableFlags_ContextMenuInBody we also allow right-clicking over columns body.");
        static ImGuiTableFlags flags1 = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Borders | ImGuiTableFlags_ContextMenuInBody;

        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_ContextMenuInBody", &flags1, ImGuiTableFlags_ContextMenuInBody);
        PopStyleCompact();

        // Context Menus: first example
        // [1.1] Right-click on the TableHeadersRow() line to open the default table context menu.
        // [1.2] Right-click in columns also open the default table context menu (if ImGuiTableFlags_ContextMenuInBody is set)
        const int COLUMNS_COUNT = 3;
        if (ImGui::BeginTable("table_context_menu", COLUMNS_COUNT, flags1))
        {
            ImGui::TableSetupColumn("One");
            ImGui::TableSetupColumn("Two");
            ImGui::TableSetupColumn("Three");

            // [1.1]] Right-click on the TableHeadersRow() line to open the default table context menu.
            ImGui::TableHeadersRow();

            // Submit dummy contents
            for (int row = 0; row < 4; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < COLUMNS_COUNT; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("Cell %d,%d", column, row);
                }
            }
            ImGui::EndTable();
        }

        // Context Menus: second example
        // [2.1] Right-click on the TableHeadersRow() line to open the default table context menu.
        // [2.2] Right-click on the ".." to open a custom popup
        // [2.3] Right-click in columns to open another custom popup
        HelpMarker(
            "Demonstrate mixing table context menu (over header), item context button (over button) "
            "and custom per-column context menu (over column body).");
        ImGuiTableFlags flags2 = ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Borders;
        if (ImGui::BeginTable("table_context_menu_2", COLUMNS_COUNT, flags2))
        {
            ImGui::TableSetupColumn("One");
            ImGui::TableSetupColumn("Two");
            ImGui::TableSetupColumn("Three");

            // [2.1] Right-click on the TableHeadersRow() line to open the default table context menu.
            ImGui::TableHeadersRow();
            for (int row = 0; row < 4; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < COLUMNS_COUNT; column++)
                {
                    // Submit dummy contents
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("Cell %d,%d", column, row);
                    ImGui::SameLine();

                    // [2.2] Right-click on the ".." to open a custom popup
                    ImGui::PushID(row * COLUMNS_COUNT + column);
                    ImGui::SmallButton("..");
                    if (ImGui::BeginPopupContextItem())
                    {
                        ImGui::Text("This is the popup for Button(\"..\") in Cell %d,%d", column, row);
                        if (ImGui::Button("Close"))
                            ImGui::CloseCurrentPopup();
                        ImGui::EndPopup();
                    }
                    ImGui::PopID();
                }
            }

            // [2.3] Right-click anywhere in columns to open another custom popup
            // (instead of testing for !IsAnyItemHovered() we could also call OpenPopup() with ImGuiPopupFlags_NoOpenOverExistingPopup
            // to manage popup priority as the popups triggers, here "are we hovering a column" are overlapping)
            int hovered_column = -1;
            for (int column = 0; column < COLUMNS_COUNT + 1; column++)
            {
                ImGui::PushID(column);
                if (ImGui::TableGetColumnFlags(column) & ImGuiTableColumnFlags_IsHovered)
                    hovered_column = column;
                if (hovered_column == column && !ImGui::IsAnyItemHovered() && ImGui::IsMouseReleased(1))
                    ImGui::OpenPopup("MyPopup");
                if (ImGui::BeginPopup("MyPopup"))
                {
                    if (column == COLUMNS_COUNT)
                        ImGui::Text("This is a custom popup for unused space after the last column.");
                    else
                        ImGui::Text("This is a custom popup for Column %d", column);
                    if (ImGui::Button("Close"))
                        ImGui::CloseCurrentPopup();
                    ImGui::EndPopup();
                }
                ImGui::PopID();
            }

            ImGui::EndTable();
            ImGui::Text("Hovered column: %d", hovered_column);
        }
        ImGui::TreePop();
    }

    // Demonstrate creating multiple tables with the same ID
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Synced instances"))
    {
        IMGUI_DEMO_MARKER("Tables/Synced instances");
        HelpMarker("Multiple tables with the same identifier will share their settings, width, visibility, order etc.");

        static ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoSavedSettings;
        ImGui::CheckboxFlags("ImGuiTableFlags_Resizable", &flags, ImGuiTableFlags_Resizable);
        ImGui::CheckboxFlags("ImGuiTableFlags_ScrollY", &flags, ImGuiTableFlags_ScrollY);
        ImGui::CheckboxFlags("ImGuiTableFlags_SizingFixedFit", &flags, ImGuiTableFlags_SizingFixedFit);
        ImGui::CheckboxFlags("ImGuiTableFlags_HighlightHoveredColumn", &flags, ImGuiTableFlags_HighlightHoveredColumn);
        for (int n = 0; n < 3; n++)
        {
            char buf[32];
            sprintf(buf, "Synced Table %d", n);
            bool open = ImGui::CollapsingHeader(buf, ImGuiTreeNodeFlags_DefaultOpen);
            if (open && ImGui::BeginTable("Table", 3, flags, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 5)))
            {
                ImGui::TableSetupColumn("One");
                ImGui::TableSetupColumn("Two");
                ImGui::TableSetupColumn("Three");
                ImGui::TableHeadersRow();
                const int cell_count = (n == 1) ? 27 : 9; // Make second table have a scrollbar to verify that additional decoration is not affecting column positions.
                for (int cell = 0; cell < cell_count; cell++)
                {
                    ImGui::TableNextColumn();
                    ImGui::Text("this cell %d", cell);
                }
                ImGui::EndTable();
            }
        }
        ImGui::TreePop();
    }

    // Demonstrate using Sorting facilities
    // This is a simplified version of the "Advanced" example, where we mostly focus on the code necessary to handle sorting.
    // Note that the "Advanced" example also showcase manually triggering a sort (e.g. if item quantities have been modified)
    static const char* template_items_names[] =
    {
        "Banana", "Apple", "Cherry", "Watermelon", "Grapefruit", "Strawberry", "Mango",
        "Kiwi", "Orange", "Pineapple", "Blueberry", "Plum", "Coconut", "Pear", "Apricot"
    };
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Sorting"))
    {
        IMGUI_DEMO_MARKER("Tables/Sorting");
        // Create item list
        static ImVector<MyItem> items;
        if (items.Size == 0)
        {
            items.resize(50, MyItem());
            for (int n = 0; n < items.Size; n++)
            {
                const int template_n = n % IM_COUNTOF(template_items_names);
                MyItem& item = items[n];
                item.ID = n;
                item.Name = template_items_names[template_n];
                item.Quantity = (n * n - n) % 20; // Assign default quantities
            }
        }

        // Options
        static ImGuiTableFlags flags =
            ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
            | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
            | ImGuiTableFlags_ScrollY;
        PushStyleCompact();
        ImGui::CheckboxFlags("ImGuiTableFlags_SortMulti", &flags, ImGuiTableFlags_SortMulti);
        ImGui::SameLine(); HelpMarker("When sorting is enabled: hold shift when clicking headers to sort on multiple column. TableGetSortSpecs() may return specs where (SpecsCount > 1).");
        ImGui::CheckboxFlags("ImGuiTableFlags_SortTristate", &flags, ImGuiTableFlags_SortTristate);
        ImGui::SameLine(); HelpMarker("When sorting is enabled: allow no sorting, disable default sorting. TableGetSortSpecs() may return specs where (SpecsCount == 0).");
        PopStyleCompact();

        if (ImGui::BeginTable("table_sorting", 4, flags, ImVec2(0.0f, TEXT_BASE_HEIGHT * 15), 0.0f))
        {
            // Declare columns
            // We use the "user_id" parameter of TableSetupColumn() to specify a user id that will be stored in the sort specifications.
            // This is so our sort function can identify a column given our own identifier. We could also identify them based on their index!
            // Demonstrate using a mixture of flags among available sort-related flags:
            // - ImGuiTableColumnFlags_DefaultSort
            // - ImGuiTableColumnFlags_NoSort / ImGuiTableColumnFlags_NoSortAscending / ImGuiTableColumnFlags_NoSortDescending
            // - ImGuiTableColumnFlags_PreferSortAscending / ImGuiTableColumnFlags_PreferSortDescending
            ImGui::TableSetupColumn("ID",       ImGuiTableColumnFlags_DefaultSort          | ImGuiTableColumnFlags_WidthFixed,   0.0f, MyItemColumnID_ID);
            ImGui::TableSetupColumn("Name",                                                  ImGuiTableColumnFlags_WidthFixed,   0.0f, MyItemColumnID_Name);
            ImGui::TableSetupColumn("Action",   ImGuiTableColumnFlags_NoSort               | ImGuiTableColumnFlags_WidthFixed,   0.0f, MyItemColumnID_Action);
            ImGui::TableSetupColumn("Quantity", ImGuiTableColumnFlags_PreferSortDescending | ImGuiTableColumnFlags_WidthStretch, 0.0f, MyItemColumnID_Quantity);
            ImGui::TableSetupScrollFreeze(0, 1); // Make row always visible
            ImGui::TableHeadersRow();

            // Sort our data if sort specs have been changed!
            if (ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs())
                if (sort_specs->SpecsDirty)
                {
                    MyItem::SortWithSortSpecs(sort_specs, items.Data, items.Size);
                    sort_specs->SpecsDirty = false;
                }

            // Demonstrate using clipper for large vertical lists
            ImGuiListClipper clipper;
            clipper.Begin(items.Size);
            while (clipper.Step())
                for (int row_n = clipper.DisplayStart; row_n < clipper.DisplayEnd; row_n++)
                {
                    // Display a data item
                    MyItem* item = &items[row_n];
                    ImGui::PushID(item->ID);
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::Text("%04d", item->ID);
                    ImGui::TableNextColumn();
                    ImGui::TextUnformatted(item->Name);
                    ImGui::TableNextColumn();
                    ImGui::SmallButton("None");
                    ImGui::TableNextColumn();
                    ImGui::Text("%d", item->Quantity);
                    ImGui::PopID();
                }
            ImGui::EndTable();
        }
        ImGui::TreePop();
    }

    // In this example we'll expose most table flags and settings.
    // For specific flags and settings refer to the corresponding section for more detailed explanation.
    // This section is mostly useful to experiment with combining certain flags or settings with each others.
    //ImGui::SetNextItemOpen(true, ImGuiCond_Once); // [DEBUG]
    if (open_action != -1)
        ImGui::SetNextItemOpen(open_action != 0);
    if (ImGui::TreeNode("Advanced"))
    {
        IMGUI_DEMO_MARKER("Tables/Advanced");
        static ImGuiTableFlags flags =
            ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable
            | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
            | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_NoBordersInBody
            | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
            | ImGuiTableFlags_SizingFixedFit;
        static ImGuiTableColumnFlags columns_base_flags = ImGuiTableColumnFlags_None;

        enum ContentsType { CT_Text, CT_Button, CT_SmallButton, CT_FillButton, CT_Selectable, CT_SelectableSpanRow };
        static int contents_type = CT_SelectableSpanRow;
        const char* contents_type_names[] = { "Text", "Button", "SmallButton", "FillButton", "Selectable", "Selectable (span row)" };
        static int freeze_cols = 1;
        static int freeze_rows = 1;
        static int items_count = IM_COUNTOF(template_items_names) * 2;
        static ImVec2 outer_size_value = ImVec2(0.0f, TEXT_BASE_HEIGHT * 12);
        static float row_min_height = 0.0f; // Auto
        static float inner_width_with_scroll = 0.0f; // Auto-extend
        static bool outer_size_enabled = true;
        static bool show_headers = true;
        static bool show_wrapped_text = false;
        //static ImGuiTextFilter filter;
        //ImGui::SetNextItemOpen(true, ImGuiCond_Once); // FIXME-TABLE: Enabling this results in initial clipped first pass on table which tend to affect column sizing
        if (ImGui::TreeNode("Options"))
        {
            // Make the UI compact because there are so many fields
            PushStyleCompact();
            ImGui::PushItemWidth(TEXT_BASE_WIDTH * 28.0f);

            if (ImGui::TreeNodeEx("Features:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::CheckboxFlags("ImGuiTableFlags_Resizable", &flags, ImGuiTableFlags_Resizable);
                ImGui::CheckboxFlags("ImGuiTableFlags_Reorderable", &flags, ImGuiTableFlags_Reorderable);
                ImGui::CheckboxFlags("ImGuiTableFlags_Hideable", &flags, ImGuiTableFlags_Hideable);
                ImGui::CheckboxFlags("ImGuiTableFlags_Sortable", &flags, ImGuiTableFlags_Sortable);
                ImGui::CheckboxFlags("ImGuiTableFlags_NoSavedSettings", &flags, ImGuiTableFlags_NoSavedSettings);
                ImGui::CheckboxFlags("ImGuiTableFlags_ContextMenuInBody", &flags, ImGuiTableFlags_ContextMenuInBody);
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx("Decorations:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::CheckboxFlags("ImGuiTableFlags_RowBg", &flags, ImGuiTableFlags_RowBg);
                ImGui::CheckboxFlags("ImGuiTableFlags_BordersV", &flags, ImGuiTableFlags_BordersV);
                ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuterV", &flags, ImGuiTableFlags_BordersOuterV);
                ImGui::CheckboxFlags("ImGuiTableFlags_BordersInnerV", &flags, ImGuiTableFlags_BordersInnerV);
                ImGui::CheckboxFlags("ImGuiTableFlags_BordersH", &flags, ImGuiTableFlags_BordersH);
                ImGui::CheckboxFlags("ImGuiTableFlags_BordersOuterH", &flags, ImGuiTableFlags_BordersOuterH);
                ImGui::CheckboxFlags("ImGuiTableFlags_BordersInnerH", &flags, ImGuiTableFlags_BordersInnerH);
                ImGui::CheckboxFlags("ImGuiTableFlags_NoBordersInBody", &flags, ImGuiTableFlags_NoBordersInBody); ImGui::SameLine(); HelpMarker("Disable vertical borders in columns Body (borders will always appear in Headers)");
                ImGui::CheckboxFlags("ImGuiTableFlags_NoBordersInBodyUntilResize", &flags, ImGuiTableFlags_NoBordersInBodyUntilResize); ImGui::SameLine(); HelpMarker("Disable vertical borders in columns Body until hovered for resize (borders will always appear in Headers)");
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx("Sizing:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                EditTableSizingFlags(&flags);
                ImGui::SameLine(); HelpMarker("In the Advanced demo we override the policy of each column so those table-wide settings have less effect that typical.");
                ImGui::CheckboxFlags("ImGuiTableFlags_NoHostExtendX", &flags, ImGuiTableFlags_NoHostExtendX);
                ImGui::SameLine(); HelpMarker("Make outer width auto-fit to columns, overriding outer_size.x value.\n\nOnly available when ScrollX/ScrollY are disabled and Stretch columns are not used.");
                ImGui::CheckboxFlags("ImGuiTableFlags_NoHostExtendY", &flags, ImGuiTableFlags_NoHostExtendY);
                ImGui::SameLine(); HelpMarker("Make outer height stop exactly at outer_size.y (prevent auto-extending table past the limit).\n\nOnly available when ScrollX/ScrollY are disabled. Data below the limit will be clipped and not visible.");
                ImGui::CheckboxFlags("ImGuiTableFlags_NoKeepColumnsVisible", &flags, ImGuiTableFlags_NoKeepColumnsVisible);
                ImGui::SameLine(); HelpMarker("Only available if ScrollX is disabled.");
                ImGui::CheckboxFlags("ImGuiTableFlags_PreciseWidths", &flags, ImGuiTableFlags_PreciseWidths);
                ImGui::SameLine(); HelpMarker("Disable distributing remainder width to stretched columns (width allocation on a 100-wide table with 3 columns: Without this flag: 33,33,34. With this flag: 33,33,33). With larger number of columns, resizing will appear to be less smooth.");
                ImGui::CheckboxFlags("ImGuiTableFlags_NoClip", &flags, ImGuiTableFlags_NoClip);
                ImGui::SameLine(); HelpMarker("Disable clipping rectangle for every individual columns (reduce draw command count, items will be able to overflow into other columns). Generally incompatible with ScrollFreeze options.");
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx("Padding:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::CheckboxFlags("ImGuiTableFlags_PadOuterX", &flags, ImGuiTableFlags_PadOuterX);
                ImGui::CheckboxFlags("ImGuiTableFlags_NoPadOuterX", &flags, ImGuiTableFlags_NoPadOuterX);
                ImGui::CheckboxFlags("ImGuiTableFlags_NoPadInnerX", &flags, ImGuiTableFlags_NoPadInnerX);
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx("Scrolling:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::CheckboxFlags("ImGuiTableFlags_ScrollX", &flags, ImGuiTableFlags_ScrollX);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(ImGui::GetFrameHeight());
                ImGui::DragInt("freeze_cols", &freeze_cols, 0.2f, 0, 9, NULL, ImGuiSliderFlags_NoInput);
                ImGui::CheckboxFlags("ImGuiTableFlags_ScrollY", &flags, ImGuiTableFlags_ScrollY);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(ImGui::GetFrameHeight());
                ImGui::DragInt("freeze_rows", &freeze_rows, 0.2f, 0, 9, NULL, ImGuiSliderFlags_NoInput);
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx("Sorting:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::CheckboxFlags("ImGuiTableFlags_SortMulti", &flags, ImGuiTableFlags_SortMulti);
                ImGui::SameLine(); HelpMarker("When sorting is enabled: hold shift when clicking headers to sort on multiple column. TableGetSortSpecs() may return specs where (SpecsCount > 1).");
                ImGui::CheckboxFlags("ImGuiTableFlags_SortTristate", &flags, ImGuiTableFlags_SortTristate);
                ImGui::SameLine(); HelpMarker("When sorting is enabled: allow no sorting, disable default sorting. TableGetSortSpecs() may return specs where (SpecsCount == 0).");
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx("Headers:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Checkbox("show_headers", &show_headers);
                ImGui::CheckboxFlags("ImGuiTableFlags_HighlightHoveredColumn", &flags, ImGuiTableFlags_HighlightHoveredColumn);
                ImGui::CheckboxFlags("ImGuiTableColumnFlags_AngledHeader", &columns_base_flags, ImGuiTableColumnFlags_AngledHeader);
                ImGui::SameLine(); HelpMarker("Enable AngledHeader on all columns. Best enabled on selected narrow columns (see \"Angled headers\" section of the demo).");
                ImGui::TreePop();
            }

            if (ImGui::TreeNodeEx("Other:", ImGuiTreeNodeFlags_DefaultOpen))
            {
                ImGui::Checkbox("show_wrapped_text", &show_wrapped_text);

                ImGui::DragFloat2("##OuterSize", &outer_size_value.x);
                ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
                ImGui::Checkbox("outer_size", &outer_size_enabled);
                ImGui::SameLine();
                HelpMarker("If scrolling is disabled (ScrollX and ScrollY not set):\n"
                    "- The table is output directly in the parent window.\n"
                    "- OuterSize.x < 0.0f will right-align the table.\n"
                    "- OuterSize.x = 0.0f will narrow fit the table unless there are any Stretch columns.\n"
                    "- OuterSize.y then becomes the minimum size for the table, which will extend vertically if there are more rows (unless NoHostExtendY is set).");

                // From a user point of view we will tend to use 'inner_width' differently depending on whether our table is embedding scrolling.
                // To facilitate toying with this demo we will actually pass 0.0f to the BeginTable() when ScrollX is disabled.
                ImGui::DragFloat("inner_width (when ScrollX active)", &inner_width_with_scroll, 1.0f, 0.0f, FLT_MAX);

                ImGui::DragFloat("row_min_height", &row_min_height, 1.0f, 0.0f, FLT_MAX);
                ImGui::SameLine(); HelpMarker("Specify height of the Selectable item.");

                ImGui::DragInt("items_count", &items_count, 0.1f, 0, 9999);
                ImGui::Combo("items_type (first column)", &contents_type, contents_type_names, IM_COUNTOF(contents_type_names));
                //filter.Draw("filter");
                ImGui::TreePop();
            }

            ImGui::PopItemWidth();
            PopStyleCompact();
            ImGui::Spacing();
            ImGui::TreePop();
        }

        // Update item list if we changed the number of items
        static ImVector<MyItem> items;
        static ImVector<int> selection;
        static bool items_need_sort = false;
        if (items.Size != items_count)
        {
            items.resize(items_count, MyItem());
            for (int n = 0; n < items_count; n++)
            {
                const int template_n = n % IM_COUNTOF(template_items_names);
                MyItem& item = items[n];
                item.ID = n;
                item.Name = template_items_names[template_n];
                item.Quantity = (template_n == 3) ? 10 : (template_n == 4) ? 20 : 0; // Assign default quantities
            }
        }

        const ImDrawList* parent_draw_list = ImGui::GetWindowDrawList();
        const int parent_draw_list_draw_cmd_count = parent_draw_list->CmdBuffer.Size;
        ImVec2 table_scroll_cur, table_scroll_max; // For debug display
        const ImDrawList* table_draw_list = NULL;  // "

        // Submit table
        const float inner_width_to_use = (flags & ImGuiTableFlags_ScrollX) ? inner_width_with_scroll : 0.0f;
        if (ImGui::BeginTable("table_advanced", 6, flags, outer_size_enabled ? outer_size_value : ImVec2(0, 0), inner_width_to_use))
        {
            // Declare columns
            // We use the "user_id" parameter of TableSetupColumn() to specify a user id that will be stored in the sort specifications.
            // This is so our sort function can identify a column given our own identifier. We could also identify them based on their index!
            ImGui::TableSetupColumn("ID",           columns_base_flags | ImGuiTableColumnFlags_DefaultSort | ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoHide, 0.0f, MyItemColumnID_ID);
            ImGui::TableSetupColumn("Name",         columns_base_flags | ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Name);
            ImGui::TableSetupColumn("Action",       columns_base_flags | ImGuiTableColumnFlags_NoSort | ImGuiTableColumnFlags_WidthFixed, 0.0f, MyItemColumnID_Action);
            ImGui::TableSetupColumn("Quantity",     columns_base_flags | ImGuiTableColumnFlags_PreferSortDescending, 0.0f, MyItemColumnID_Quantity);
            ImGui::TableSetupColumn("Description",  columns_base_flags | ((flags & ImGuiTableFlags_NoHostExtendX) ? 0 : ImGuiTableColumnFlags_WidthStretch), 0.0f, MyItemColumnID_Description);
            ImGui::TableSetupColumn("Hidden",       columns_base_flags |  ImGuiTableColumnFlags_DefaultHide | ImGuiTableColumnFlags_NoSort);
            ImGui::TableSetupScrollFreeze(freeze_cols, freeze_rows);

            // Sort our data if sort specs have been changed!
            ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs();
            if (sort_specs && sort_specs->SpecsDirty)
                items_need_sort = true;
            if (sort_specs && items_need_sort && items.Size > 1)
            {
                MyItem::SortWithSortSpecs(sort_specs, items.Data, items.Size);
                sort_specs->SpecsDirty = false;
            }
            items_need_sort = false;

            // Take note of whether we are currently sorting based on the Quantity field,
            // we will use this to trigger sorting when we know the data of this column has been modified.
            const bool sorts_specs_using_quantity = (ImGui::TableGetColumnFlags(3) & ImGuiTableColumnFlags_IsSorted) != 0;

            // Show headers
            if (show_headers && (columns_base_flags & ImGuiTableColumnFlags_AngledHeader) != 0)
                ImGui::TableAngledHeadersRow();
            if (show_headers)
                ImGui::TableHeadersRow();

            // Show data
            // FIXME-TABLE FIXME-NAV: How we can get decent up/down even though we have the buttons here?
#if 1
            // Demonstrate using clipper for large vertical lists
            ImGuiListClipper clipper;
            clipper.Begin(items.Size);
            while (clipper.Step())
            {
                for (int row_n = clipper.DisplayStart; row_n < clipper.DisplayEnd; row_n++)
#else
            // Without clipper
            {
                for (int row_n = 0; row_n < items.Size; row_n++)
#endif
                {
                    MyItem* item = &items[row_n];
                    //if (!filter.PassFilter(item->Name))
                    //    continue;

                    const bool item_is_selected = selection.contains(item->ID);
                    ImGui::PushID(item->ID);
                    ImGui::TableNextRow(ImGuiTableRowFlags_None, row_min_height);

                    // For the demo purpose we can select among different type of items submitted in the first column
                    ImGui::TableSetColumnIndex(0);
                    char label[32];
                    sprintf(label, "%04d", item->ID);
                    if (contents_type == CT_Text)
                        ImGui::TextUnformatted(label);
                    else if (contents_type == CT_Button)
                        ImGui::Button(label);
                    else if (contents_type == CT_SmallButton)
                        ImGui::SmallButton(label);
                    else if (contents_type == CT_FillButton)
                        ImGui::Button(label, ImVec2(-FLT_MIN, 0.0f));
                    else if (contents_type == CT_Selectable || contents_type == CT_SelectableSpanRow)
                    {
                        ImGuiSelectableFlags selectable_flags = (contents_type == CT_SelectableSpanRow) ? ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap : ImGuiSelectableFlags_None;
                        if (ImGui::Selectable(label, item_is_selected, selectable_flags, ImVec2(0, row_min_height)))
                        {
                            if (ImGui::GetIO().KeyCtrl)
                            {
                                if (item_is_selected)
                                    selection.find_erase_unsorted(item->ID);
                                else
                                    selection.push_back(item->ID);
                            }
                            else
                            {
                                selection.clear();
                                selection.push_back(item->ID);
                            }
                        }
                    }

                    if (ImGui::TableSetColumnIndex(1))
                        ImGui::TextUnformatted(item->Name);

                    // Here we demonstrate marking our data set as needing to be sorted again if we modified a quantity,
                    // and we are currently sorting on the column showing the Quantity.
                    // To avoid triggering a sort while holding the button, we only trigger it when the button has been released.
                    // You will probably need some extra logic if you want to automatically sort when a specific entry changes.
                    if (ImGui::TableSetColumnIndex(2))
                    {
                        if (ImGui::SmallButton("Chop")) { item->Quantity += 1; }
                        if (sorts_specs_using_quantity && ImGui::IsItemDeactivated()) { items_need_sort = true; }
                        ImGui::SameLine();
                        if (ImGui::SmallButton("Eat")) { item->Quantity -= 1; }
                        if (sorts_specs_using_quantity && ImGui::IsItemDeactivated()) { items_need_sort = true; }
                    }

                    if (ImGui::TableSetColumnIndex(3))
                        ImGui::Text("%d", item->Quantity);

                    ImGui::TableSetColumnIndex(4);
                    if (show_wrapped_text)
                        ImGui::TextWrapped("Lorem ipsum dolor sit amet");
                    else
                        ImGui::Text("Lorem ipsum dolor sit amet");

                    if (ImGui::TableSetColumnIndex(5))
                        ImGui::Text("1234");

                    ImGui::PopID();
                }
            }

            // Store some info to display debug details below
            table_scroll_cur = ImVec2(ImGui::GetScrollX(), ImGui::GetScrollY());
            table_scroll_max = ImVec2(ImGui::GetScrollMaxX(), ImGui::GetScrollMaxY());
            table_draw_list = ImGui::GetWindowDrawList();
            ImGui::EndTable();
        }
        static bool show_debug_details = false;
        ImGui::Checkbox("Debug details", &show_debug_details);
        if (show_debug_details && table_draw_list)
        {
            ImGui::SameLine(0.0f, 0.0f);
            const int table_draw_list_draw_cmd_count = table_draw_list->CmdBuffer.Size;
            if (table_draw_list == parent_draw_list)
                ImGui::Text(": DrawCmd: +%d (in same window)",
                    table_draw_list_draw_cmd_count - parent_draw_list_draw_cmd_count);
            else
                ImGui::Text(": DrawCmd: +%d (in child window), Scroll: (%.f/%.f) (%.f/%.f)",
                    table_draw_list_draw_cmd_count - 1, table_scroll_cur.x, table_scroll_max.x, table_scroll_cur.y, table_scroll_max.y);
        }
        ImGui::TreePop();
    }

    ImGui::PopID();

    DemoWindowColumns();

    if (disable_indent)
        ImGui::PopStyleVar();
}

// Demonstrate old/legacy Columns API!
// [2020: Columns are under-featured and not maintained. Prefer using the more flexible and powerful BeginTable() API!]
static void DemoWindowColumns()
{
    bool open = ImGui::TreeNode("Legacy Columns API");
    ImGui::SameLine();
    HelpMarker("Columns() is an old API! Prefer using the more flexible and powerful BeginTable() API!");
    if (!open)
        return;

    // Basic columns
    if (ImGui::TreeNode("Basic"))
    {
        IMGUI_DEMO_MARKER("Columns (legacy API)/Basic");
        ImGui::Text("Without border:");
        ImGui::Columns(3, "mycolumns3", false);  // 3-ways, no border
        ImGui::Separator();
        for (int n = 0; n < 14; n++)
        {
            char label[32];
            sprintf(label, "Item %d", n);
            if (ImGui::Selectable(label)) {}
            //if (ImGui::Button(label, ImVec2(-FLT_MIN,0.0f))) {}
            ImGui::NextColumn();
        }
        ImGui::Columns(1);
        ImGui::Separator();

        ImGui::Text("With border:");
        ImGui::Columns(4, "mycolumns"); // 4-ways, with border
        ImGui::Separator();
        ImGui::Text("ID"); ImGui::NextColumn();
        ImGui::Text("Name"); ImGui::NextColumn();
        ImGui::Text("Path"); ImGui::NextColumn();
        ImGui::Text("Hovered"); ImGui::NextColumn();
        ImGui::Separator();
        const char* names[3] = { "One", "Two", "Three" };
        const char* paths[3] = { "/path/one", "/path/two", "/path/three" };
        static int selected = -1;
        for (int i = 0; i < 3; i++)
        {
            char label[32];
            sprintf(label, "%04d", i);
            if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
                selected = i;
            bool hovered = ImGui::IsItemHovered();
            ImGui::NextColumn();
            ImGui::Text(names[i]); ImGui::NextColumn();
            ImGui::Text(paths[i]); ImGui::NextColumn();
            ImGui::Text("%d", hovered); ImGui::NextColumn();
        }
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Borders"))
    {
        IMGUI_DEMO_MARKER("Columns (legacy API)/Borders");
        // NB: Future columns API should allow automatic horizontal borders.
        static bool h_borders = true;
        static bool v_borders = true;
        static int columns_count = 4;
        const int lines_count = 3;
        ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
        ImGui::DragInt("##columns_count", &columns_count, 0.1f, 2, 10, "%d columns");
        if (columns_count < 2)
            columns_count = 2;
        ImGui::SameLine();
        ImGui::Checkbox("horizontal", &h_borders);
        ImGui::SameLine();
        ImGui::Checkbox("vertical", &v_borders);
        ImGui::Columns(columns_count, NULL, v_borders);
        for (int i = 0; i < columns_count * lines_count; i++)
        {
            if (h_borders && ImGui::GetColumnIndex() == 0)
                ImGui::Separator();
            ImGui::PushID(i);
            ImGui::Text("%c%c%c", 'a' + i, 'a' + i, 'a' + i);
            ImGui::Text("Width %.2f", ImGui::GetColumnWidth());
            ImGui::Text("Avail %.2f", ImGui::GetContentRegionAvail().x);
            ImGui::Text("Offset %.2f", ImGui::GetColumnOffset());
            ImGui::Text("Long text that is likely to clip");
            ImGui::Button("Button", ImVec2(-FLT_MIN, 0.0f));
            ImGui::PopID();
            ImGui::NextColumn();
        }
        ImGui::Columns(1);
        if (h_borders)
            ImGui::Separator();
        ImGui::TreePop();
    }

    // Create multiple items in a same cell before switching to next column
    if (ImGui::TreeNode("Mixed items"))
    {
        IMGUI_DEMO_MARKER("Columns (legacy API)/Mixed items");
        ImGui::Columns(3, "mixed");
        ImGui::Separator();

        ImGui::Text("Hello");
        ImGui::Button("Banana");
        ImGui::NextColumn();

        ImGui::Text("ImGui");
        ImGui::Button("Apple");
        static float foo = 1.0f;
        ImGui::InputFloat("red", &foo, 0.05f, 0, "%.3f");
        ImGui::Text("An extra line here.");
        ImGui::NextColumn();

        ImGui::Text("Sailor");
        ImGui::Button("Corniflower");
        static float bar = 1.0f;
        ImGui::InputFloat("blue", &bar, 0.05f, 0, "%.3f");
        ImGui::NextColumn();

        if (ImGui::CollapsingHeader("Category A")) { ImGui::Text("Blah blah blah"); } ImGui::NextColumn();
        if (ImGui::CollapsingHeader("Category B")) { ImGui::Text("Blah blah blah"); } ImGui::NextColumn();
        if (ImGui::CollapsingHeader("Category C")) { ImGui::Text("Blah blah blah"); } ImGui::NextColumn();
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::TreePop();
    }

    // Word wrapping
    if (ImGui::TreeNode("Word-wrapping"))
    {
        IMGUI_DEMO_MARKER("Columns (legacy API)/Word-wrapping");
        ImGui::Columns(2, "word-wrapping");
        ImGui::Separator();
        ImGui::TextWrapped("The quick brown fox jumps over the lazy dog.");
        ImGui::TextWrapped("Hello Left");
        ImGui::NextColumn();
        ImGui::TextWrapped("The quick brown fox jumps over the lazy dog.");
        ImGui::TextWrapped("Hello Right");
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Horizontal Scrolling"))
    {
        IMGUI_DEMO_MARKER("Columns (legacy API)/Horizontal Scrolling");
        ImGui::SetNextWindowContentSize(ImVec2(1500.0f, 0.0f));
        ImVec2 child_size = ImVec2(0, ImGui::GetFontSize() * 20.0f);
        ImGui::BeginChild("##ScrollingRegion", child_size, ImGuiChildFlags_None, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::Columns(10);

        // Also demonstrate using clipper for large vertical lists
        int ITEMS_COUNT = 2000;
        ImGuiListClipper clipper;
        clipper.Begin(ITEMS_COUNT);
        while (clipper.Step())
        {
            for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                for (int j = 0; j < 10; j++)
                {
                    ImGui::Text("Line %d Column %d...", i, j);
                    ImGui::NextColumn();
                }
        }
        ImGui::Columns(1);
        ImGui::EndChild();
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Tree"))
    {
        IMGUI_DEMO_MARKER("Columns (legacy API)/Tree");
        ImGui::Columns(2, "tree", true);
        for (int x = 0; x < 3; x++)
        {
            bool open1 = ImGui::TreeNode((void*)(intptr_t)x, "Node%d", x);
            ImGui::NextColumn();
            ImGui::Text("Node contents");
            ImGui::NextColumn();
            if (open1)
            {
                for (int y = 0; y < 3; y++)
                {
                    bool open2 = ImGui::TreeNode((void*)(intptr_t)y, "Node%d.%d", x, y);
                    ImGui::NextColumn();
                    ImGui::Text("Node contents");
                    if (open2)
                    {
                        ImGui::Text("Even more contents");
                        if (ImGui::TreeNode("Tree in column"))
                        {
                            ImGui::Text("The quick brown fox jumps over the lazy dog");
                            ImGui::TreePop();
                        }
                    }
                    ImGui::NextColumn();
                    if (open2)
                        ImGui::TreePop();
                }
                ImGui::TreePop();
            }
        }
        ImGui::Columns(1);
        ImGui::TreePop();
    }

    ImGui::TreePop();
}

//-----------------------------------------------------------------------------
#endif

static void DemoWindowTables(Widget parent)
{
    //ImGui::SetNextItemOpen(true, ImGuiCond_Once);
    Widget body = ui::collapsing_header(key(), parent, "Tables & Columns");
    if (!body)
        return;

    // @todo: port the Tables & Columns section once two.ui has a tables API, see the original under #if 0 above
    ui::text_wrapped(key(), *body, "The tables API has no equivalent in two.ui yet.");
    DemoWindowColumns(*body);
}

static void DemoWindowColumns(Widget parent)
{
    UNUSED(parent);
}

//-----------------------------------------------------------------------------
// [SECTION] DemoWindowInputs()
//-----------------------------------------------------------------------------

static void DemoWindowInputs(Widget parent)
{
    if (Widget body = ui::collapsing_header(key(), parent, "Inputs & Focus"))
    {
        ui::IO& io = ui::io();

        // Display inputs submitted to ImGuiIO
        //ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        TreeNode inputs = ui::tree_node_ex(key(), *body, "Inputs", ImGuiTreeNodeFlags_DefaultOpen);
        //ImGui::SameLine();
        HelpMarker(inputs.header,
            "This is a simplified view. See more detailed input state:\n"
            "- in 'Tools->Metrics/Debugger->Inputs'.\n"
            "- in 'Tools->Debug Log->IO'.");
        if (Widget n = inputs.body)
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Inputs");
            if (ui::is_mouse_pos_valid())
                ui::textf(key(), *n, "Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
            else
                ui::label(key(), *n, "Mouse pos: <INVALID>");
            ui::textf(key(), *n, "Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);
            Widget line0 = ui::row(key(), *n);
            ui::label(key(), line0, "Mouse down:");
            for (int i = 0; i < IM_COUNTOF(io.MouseDown); i++) if (ui::is_mouse_down(i)) { /*ImGui::SameLine();*/ ui::textf(key(i), line0, "b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
            ui::textf(key(), *n, "Mouse wheel: %.1f", io.MouseWheel);
            Widget line1 = ui::row(key(), *n);
            ui::label(key(), line1, "Mouse clicked count:");
            for (int i = 0; i < IM_COUNTOF(io.MouseDown); i++) if (io.MouseClickedCount[i] > 0) { /*ImGui::SameLine();*/ ui::textf(key(i), line1, "b%d: %d", i, io.MouseClickedCount[i]); }

            // We iterate both legacy native range and named ImGuiKey ranges. This is a little unusual/odd but this allows
            // displaying the data for old/new backends.
            // User code should never have to go through such hoops!
            // You can generally iterate between ImGuiKey_NamedKey_BEGIN and ImGuiKey_NamedKey_END.
            Widget line2 = ui::row(key(), *n);
            ui::label(key(), line2, "Keys down:");         for (Key key_down : ui::keys_down(*n)) { /*ImGui::SameLine();*/ ui::textf(key(uint64_t(key_down)), line2, "\"%s\" %d", ui::get_key_name(key_down), int(key_down)); }
            ui::textf(key(), *n, "Keys mods: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");
            Widget line3 = ui::row(key(), *n);
            ui::label(key(), line3, "Chars queue:");       for (int i = 0; i < int(io.InputQueueCharacters.size()); i++) { char c = io.InputQueueCharacters[i]; /*ImGui::SameLine();*/ ui::textf(key(i), line3, "\'%c\' (0x%04X)", (c > ' ') ? (char)c : '?', c); } // FIXME: We should convert 'c' to UTF-8 here but the functions are not public.
        }

        // Display ImGuiIO output flags
        //ImGui::SetNextItemOpen(true, ImGuiCond_Once);
        TreeNode outputs = ui::tree_node_ex(key(), *body, "Outputs", ImGuiTreeNodeFlags_DefaultOpen);
        //ImGui::SameLine();
        HelpMarker(outputs.header,
            "The value of io.WantCaptureMouse and io.WantCaptureKeyboard are normally set by Dear ImGui "
            "to instruct your application of how to route inputs. Typically, when a value is true, it means "
            "Dear ImGui wants the corresponding inputs and we expect the underlying application to ignore them.\n\n"
            "The most typical case is: when hovering a window, Dear ImGui set io.WantCaptureMouse to true, "
            "and underlying application should ignore mouse inputs (in practice there are many and more subtle "
            "rules leading to how those flags are set).");
        if (Widget n = outputs.body)
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Outputs");
            ui::textf(key(), *n, "io.WantCaptureMouse: %d", io.WantCaptureMouse);
            ui::textf(key(), *n, "io.WantCaptureMouseUnlessPopupClose: %d", io.WantCaptureMouseUnlessPopupClose);
            ui::textf(key(), *n, "io.WantCaptureKeyboard: %d", io.WantCaptureKeyboard);
            ui::textf(key(), *n, "io.WantTextInput: %d", io.WantTextInput);
            ui::textf(key(), *n, "io.WantSetMousePos: %d", io.WantSetMousePos);
            ui::textf(key(), *n, "io.NavActive: %d, io.NavVisible: %d", io.NavActive, io.NavVisible);

            IMGUI_DEMO_MARKER("Inputs & Focus/Outputs/WantCapture override");
            if (Widget n0 = ui::tree_node_ex(key(), *n, "WantCapture override").body)
            {
                HelpMarker(*n0,
                    "Hovering the colored canvas will override io.WantCaptureXXX fields.\n"
                    "Notice how normally (when set to none), the value of io.WantCaptureKeyboard would be false when hovering "
                    "and true when clicking.");
                static int capture_override_mouse = -1;
                static int capture_override_keyboard = -1;
                const char* capture_override_desc[] = { "None", "Set to false", "Set to true" };
                //ImGui::SetNextItemWidth(ImGui::GetFontSize() * 15);
                { Widget line = ui::row(key(), *n0); ui::slider_int(key(), line, "SetNextFrameWantCaptureMouse() on hover", capture_override_mouse, -1, +1); ui::label(key(), line, capture_override_desc[capture_override_mouse + 1]); } // ImGuiSliderFlags_AlwaysClamp
                //ImGui::SetNextItemWidth(ImGui::GetFontSize() * 15);
                { Widget line = ui::row(key(), *n0); ui::slider_int(key(), line, "SetNextFrameWantCaptureKeyboard() on hover", capture_override_keyboard, -1, +1); ui::label(key(), line, capture_override_desc[capture_override_keyboard + 1]); } // ImGuiSliderFlags_AlwaysClamp

                Widget panel = ui::color_button(key(), *n0, "##panel", Colour(0.7f, 0.1f, 0.7f, 1.0f), vec2(128.0f, 96.0f)); // ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop // Dummy item
                if (ui::is_item_hovered(panel) && capture_override_mouse != -1)
                    io.WantCaptureMouse = capture_override_mouse == 1; // ImGui::SetNextFrameWantCaptureMouse(capture_override_mouse == 1);
                if (ui::is_item_hovered(panel) && capture_override_keyboard != -1)
                    io.WantCaptureKeyboard = capture_override_keyboard == 1; // ImGui::SetNextFrameWantCaptureKeyboard(capture_override_keyboard == 1);
            }
        }

        // Demonstrate using Shortcut() and Routing Policies.
        // The general flow is:
        // - Code interested in a chord (e.g. "Ctrl+A") declares their intent.
        // - Multiple locations may be interested in same chord! Routing helps find a winner.
        // - Every frame, we resolve all claims and assign one owner if the modifiers are matching.
        // - The lower-level function is 'bool SetShortcutRouting()', returns true when caller got the route.
        // - Most of the times, SetShortcutRouting() is not called directly. User mostly calls Shortcut() with routing flags.
        // - If you call Shortcut() WITHOUT any routing option, it uses ImGuiInputFlags_RouteFocused.
        // TL;DR: Most uses will simply be:
        // - Shortcut(ImGuiMod_Ctrl | ImGuiKey_A); // Use ImGuiInputFlags_RouteFocused policy.
        if (Widget n = ui::tree_node_ex(key(), *body, "Shortcuts").body)
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Shortcuts");
            static ImGuiInputFlags route_options = ImGuiInputFlags_Repeat;
            static ImGuiInputFlags route_type = ImGuiInputFlags_RouteFocused;
            ui::checkbox_flags(key(), *n, "ImGuiInputFlags_Repeat", route_options, ImGuiInputFlags_Repeat);
            ui::radio_button(key(), *n, "ImGuiInputFlags_RouteActive", route_type, ImGuiInputFlags_RouteActive);
            ui::radio_button(key(), *n, "ImGuiInputFlags_RouteFocused (default)", route_type, ImGuiInputFlags_RouteFocused);
            {
                Widget indent = ui::indent(key(), *n); // ImGui::Indent();
                ui::begin_disabled(route_type != ImGuiInputFlags_RouteFocused);
                ui::checkbox_flags(key(), indent, "ImGuiInputFlags_RouteOverActive##0", route_options, ImGuiInputFlags_RouteOverActive);
                ui::end_disabled();
                //ImGui::Unindent();
            }
            ui::radio_button(key(), *n, "ImGuiInputFlags_RouteGlobal", route_type, ImGuiInputFlags_RouteGlobal);
            {
                Widget indent = ui::indent(key(), *n); // ImGui::Indent();
                ui::begin_disabled(route_type != ImGuiInputFlags_RouteGlobal);
                ui::checkbox_flags(key(), indent, "ImGuiInputFlags_RouteOverFocused", route_options, ImGuiInputFlags_RouteOverFocused);
                ui::checkbox_flags(key(), indent, "ImGuiInputFlags_RouteOverActive", route_options, ImGuiInputFlags_RouteOverActive);
                ui::checkbox_flags(key(), indent, "ImGuiInputFlags_RouteUnlessBgFocused", route_options, ImGuiInputFlags_RouteUnlessBgFocused);
                ui::end_disabled();
                //ImGui::Unindent();
            }
            ui::radio_button(key(), *n, "ImGuiInputFlags_RouteAlways", route_type, ImGuiInputFlags_RouteAlways);
            ImGuiInputFlags flags = route_type | route_options; // Merged flags
            if (route_type != ImGuiInputFlags_RouteGlobal)
                flags &= ~(ImGuiInputFlags_RouteOverFocused | ImGuiInputFlags_RouteOverActive | ImGuiInputFlags_RouteUnlessBgFocused);

            ui::separator_text(key(), *n, "Using SetNextItemShortcut()");
            ui::label(key(), *n, "Ctrl+S");
            Widget save = ui::button(key(), *n, "Save");
            ui::set_item_shortcut(save, InputMod::Ctrl, Key::S, flags | ImGuiInputFlags_Tooltip);
            ui::label(key(), *n, "Alt+F");
            static float f = 0.5f;
            ui::slider_float(key(), *n, "Factor", f, 0.0f, 1.0f); // ImGui::SetNextItemShortcut(ImGuiMod_Alt | ImGuiKey_F, flags | ImGuiInputFlags_Tooltip);

            ui::separator_text(key(), *n, "Using Shortcut()");
            const float line_height = ui::get_text_line_height_with_spacing();
            //const ImGuiKeyChord key_chord = ImGuiMod_Ctrl | ImGuiKey_A;

            ui::label(key(), *n, "Ctrl+A");
            Widget window = ui::get_current_window(*n);
            ui::textf(key(), *n, "IsWindowFocused: %d, Shortcut: %s", ui::is_window_focused(window), ui::shortcut(*n, InputMod::Ctrl, Key::A, flags) ? "PRESSED" : "...");

            //ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.0f, 0.0f, 1.0f, 0.1f));

            if (Widget window_a = ui::begin_child(key(), *n, vec2(-FLT_MIN, line_height * 14), true))
            {
                ui::label(key(), *window_a, "Press Ctrl+A and see who receives it!");
                ui::separator(key(), *window_a);

                // 1: Window polling for Ctrl+A
                ui::label(key(), *window_a, "(in WindowA)");
                ui::textf(key(), *window_a, "IsWindowFocused: %d, Shortcut: %s", ui::is_window_focused(window), ui::shortcut(*window_a, InputMod::Ctrl, Key::A, flags) ? "PRESSED" : "...");

                // 2: InputText also polling for Ctrl+A: it always uses _RouteFocused internally (gets priority when active)
                // (Commented because the owner-aware version of Shortcut() is still in imgui_internal.h)
                //char str[16] = "Press Ctrl+A";
                //ImGui::Spacing();
                //ImGui::InputText("InputTextB", str, IM_COUNTOF(str), ImGuiInputTextFlags_ReadOnly);
                //ImGuiID item_id = ImGui::GetItemID();
                //ImGui::SameLine(); HelpMarker("Internal widgets always use _RouteFocused");
                //ImGui::Text("IsWindowFocused: %d, Shortcut: %s", ImGui::IsWindowFocused(), ImGui::Shortcut(key_chord, flags, item_id) ? "PRESSED" : "...");

                // 3: Dummy child is not claiming the route: focusing them shouldn't steal route away from WindowA
                if (Widget child_d = ui::begin_child(key(), *window_a, vec2(-FLT_MIN, line_height * 4), true))
                {
                    ui::label(key(), *child_d, "(in ChildD: not using same Shortcut)");
                    ui::textf(key(), *child_d, "IsWindowFocused: %d", ui::is_window_focused(window));
                }

                // 4: Child window polling for Ctrl+A. It is deeper than WindowA and gets priority when focused.
                if (Widget child_e = ui::begin_child(key(), *window_a, vec2(-FLT_MIN, line_height * 4), true))
                {
                    ui::label(key(), *child_e, "(in ChildE: using same Shortcut)");
                    ui::textf(key(), *child_e, "IsWindowFocused: %d, Shortcut: %s", ui::is_window_focused(window), ui::shortcut(*child_e, InputMod::Ctrl, Key::A, flags) ? "PRESSED" : "...");
                }

                // 5: In a popup
                static bool popup_f = false;
                Widget open_popup = ui::button(key(), *window_a, "Open Popup");
                if (open_popup.activated())
                    popup_f = true; // ImGui::OpenPopup("PopupF");
                if (Widget popup = ui::begin_popup(key(), open_popup, popup_f))
                {
                    ui::label(key(), *popup, "(in PopupF)");
                    ui::textf(key(), *popup, "IsWindowFocused: %d, Shortcut: %s", ui::is_window_focused(window), ui::shortcut(*popup, InputMod::Ctrl, Key::A, flags) ? "PRESSED" : "...");
                    // (Commented because the owner-aware version of Shortcut() is still in imgui_internal.h)
                    //ImGui::InputText("InputTextG", str, IM_COUNTOF(str), ImGuiInputTextFlags_ReadOnly);
                    //ImGui::Text("IsWindowFocused: %d, Shortcut: %s", ImGui::IsWindowFocused(), ImGui::Shortcut(key_chord, flags, ImGui::GetItemID()) ? "PRESSED" : "...");
                }
            }
            //ImGui::PopStyleColor();
        }

        // Display mouse cursors
        if (Widget n = ui::tree_node_ex(key(), *body, "Mouse Cursors").body)
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Mouse Cursors");
            const char* mouse_cursors_names[] = { "Arrow", "TextInput", "ResizeAll", "ResizeNS", "ResizeEW", "ResizeNESW", "ResizeNWSE", "Hand", "Wait", "Progress", "NotAllowed" };
            static_assert(IM_COUNTOF(mouse_cursors_names) == ImGuiMouseCursor_COUNT);

            ImGuiMouseCursor current = ui::get_mouse_cursor(*n);
            const char* cursor_name = (current >= ImGuiMouseCursor_Arrow) && (current < ImGuiMouseCursor_COUNT) ? mouse_cursors_names[current] : "N/A";
            ui::textf(key(), *n, "Current mouse cursor = %d: %s", current, cursor_name);
            ui::begin_disabled(true);
            ui::checkbox_flags(key(), *n, "io.BackendFlags: HasMouseCursors", io.BackendFlags, ImGuiBackendFlags_HasMouseCursors);
            ui::end_disabled();

            { Widget line = ui::row(key(), *n); ui::label(key(), line, "Hover to see mouse cursors:");
              HelpMarker(line,
                "Your application can render a different mouse cursor based on what ImGui::GetMouseCursor() returns. "
                "If software cursor rendering (io.MouseDrawCursor) is set ImGui will draw the right cursor for you, "
                "otherwise your backend needs to handle it."); }
            for (int i = 0; i < ImGuiMouseCursor_COUNT; i++)
            {
                char label[32];
                sprintf(label, "Mouse cursor %d: %s", i, mouse_cursors_names[i]);
                Widget line = ui::row(key(i), *n);
                ui::item(key(), line, styles().bullet); Widget selectable = ui::selectable(key(), line, label, false);
                if (ui::is_item_hovered(selectable))
                    ui::set_mouse_cursor(selectable, i);
            }
        }

        if (Widget n = ui::tree_node_ex(key(), *body, "Tabbing").body)
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Tabbing");
            ui::label(key(), *n, "Use Tab/Shift+Tab to cycle through keyboard editable fields.");
            static string buf = "hello";
            ui::input_text(key(), *n, "1", buf);
            ui::input_text(key(), *n, "2", buf);
            ui::input_text(key(), *n, "3", buf);
            ui::push_item_flag(ImGuiItemFlags_NoTabStop, true);
            { Widget line = ui::row(key(), *n); ui::input_text(key(), line, "4 (tab skip)", buf);
              HelpMarker(line, "Item won't be cycled through when using TAB or Shift+Tab."); }
            ui::pop_item_flag();
            ui::input_text(key(), *n, "5", buf);
        }

        if (Widget n = ui::tree_node_ex(key(), *body, "Focus from code").body)
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Focus from code");
            Widget line = ui::row(key(), *n);
            bool focus_1 = ui::button(key(), line, "Focus on 1").activated(); //ImGui::SameLine();
            bool focus_2 = ui::button(key(), line, "Focus on 2").activated(); //ImGui::SameLine();
            bool focus_3 = ui::button(key(), line, "Focus on 3").activated();
            int has_focus = 0;
            static string buf = "click on a button to set focus";

            TextEditHandle input1 = ui::input_text_edit(key(), *n, "1", buf);
            if (focus_1) ui::set_keyboard_focus_here(input1.self());
            if (ui::is_item_active(input1.self())) has_focus = 1;

            TextEditHandle input2 = ui::input_text_edit(key(), *n, "2", buf);
            if (focus_2) ui::set_keyboard_focus_here(input2.self());
            if (ui::is_item_active(input2.self())) has_focus = 2;

            ui::push_item_flag(ImGuiItemFlags_NoTabStop, true);
            Widget line3 = ui::row(key(), *n);
            TextEditHandle input3 = ui::input_text_edit(key(), line3, "3 (tab skip)", buf);
            if (focus_3) ui::set_keyboard_focus_here(input3.self());
            if (ui::is_item_active(input3.self())) has_focus = 3;
            HelpMarker(line3, "Item won't be cycled through when using TAB or Shift+Tab.");
            ui::pop_item_flag();

            if (has_focus)
                ui::textf(key(), *n, "Item with focus: %d", has_focus);
            else
                ui::label(key(), *n, "Item with focus: <none>");

            // Use >= 0 parameter to SetKeyboardFocusHere() to focus an upcoming item
            static float f3[3] = { 0.0f, 0.0f, 0.0f };
            int focus_ahead = -1;
            Widget line_xyz = ui::row(key(), *n);
            if (ui::button(key(), line_xyz, "Focus on X").activated()) { focus_ahead = 0; } //ImGui::SameLine();
            if (ui::button(key(), line_xyz, "Focus on Y").activated()) { focus_ahead = 1; } //ImGui::SameLine();
            if (ui::button(key(), line_xyz, "Focus on Z").activated()) { focus_ahead = 2; }
            //if (focus_ahead != -1) ImGui::SetKeyboardFocusHere(focus_ahead);
            UNUSED(focus_ahead);
            ui::slider_float3(key(), *n, "Float3", &f3[0], 0.0f, 1.0f);

            ui::text_wrapped(key(), *n, "NB: Cursor & selection are preserved when refocusing last used item in code.");
        }

        if (Widget n = ui::tree_node_ex(key(), *body, "Dragging").body)
        {
            IMGUI_DEMO_MARKER("Inputs & Focus/Dragging");
            ui::text_wrapped(key(), *n, "You can use ImGui::GetMouseDragDelta(0) to query for the dragged amount on any widget.");
            for (int button = 0; button < 3; button++)
            {
                ui::textf(key(button), *n, "IsMouseDragging(%d):", button);
                ui::textf(key(button), *n, "  w/ default threshold: %d,", ui::is_mouse_dragging(*n, button));
                ui::textf(key(button), *n, "  w/ zero threshold: %d,", ui::is_mouse_dragging(*n, button, 0.0f));
                ui::textf(key(button), *n, "  w/ large threshold: %d,", ui::is_mouse_dragging(*n, button, 20.0f));
            }

            Widget drag_me = ui::button(key(), *n, "Drag Me");
            if (ui::is_item_active(drag_me))
                ui::foreground_line(key(), *n, io.MouseClickedPos[0], io.MousePos, Colour(0.26f, 0.59f, 0.98f, 0.40f), 4.0f); // Draw a line between the button and the mouse cursor

            // Drag operations gets "unlocked" when the mouse has moved past a certain threshold
            // (the default threshold is stored in io.MouseDragThreshold). You can request a lower or higher
            // threshold using the second parameter of IsMouseDragging() and GetMouseDragDelta().
            vec2 value_raw = ui::get_mouse_drag_delta(drag_me, 0, 0.0f);
            vec2 value_with_lock_threshold = ui::get_mouse_drag_delta(drag_me, 0);
            vec2 mouse_delta = io.MouseDelta;
            ui::label(key(), *n, "GetMouseDragDelta(0):");
            ui::textf(key(), *n, "  w/ default threshold: (%.1f, %.1f)", value_with_lock_threshold.x, value_with_lock_threshold.y);
            ui::textf(key(), *n, "  w/ zero threshold: (%.1f, %.1f)", value_raw.x, value_raw.y);
            ui::textf(key(), *n, "io.MouseDelta: (%.1f, %.1f)", mouse_delta.x, mouse_delta.y);
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] About Window / ShowAboutWindow()
// Access from Dear ImGui Demo -> Tools -> About
//-----------------------------------------------------------------------------

void ShowAboutWindow(Widget parent, bool* p_open)
{
    auto window = ui::begin(key(), parent, "About Dear ImGui", p_open); // ImGuiWindowFlags_AlwaysAutoResize
    if (!window)
    {
        return;
    }
    Widget body = *window->body;
    IMGUI_DEMO_MARKER("Tools/About Dear ImGui");
    ui::textf(key(), body, "Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);

    Widget links = ui::row(key(), body);
    ui::text_link(key(), links, "Homepage", "https://github.com/ocornut/imgui");
    //ImGui::SameLine();
    ui::text_link(key(), links, "FAQ", "https://github.com/ocornut/imgui/blob/master/docs/FAQ.md");
    //ImGui::SameLine();
    ui::text_link(key(), links, "Wiki", "https://github.com/ocornut/imgui/wiki");
    //ImGui::SameLine();
    ui::text_link(key(), links, "Extensions", "https://github.com/ocornut/imgui/wiki/Useful-Extensions");
    //ImGui::SameLine();
    ui::text_link(key(), links, "Releases", "https://github.com/ocornut/imgui/releases");
    //ImGui::SameLine();
    ui::text_link(key(), links, "Funding", "https://github.com/ocornut/imgui/wiki/Funding");

    ui::separator(key(), body);
    ui::label(key(), body, "(c) 2014-2026 Omar Cornut");
    ui::label(key(), body, "Developed by Omar Cornut and all Dear ImGui contributors.");
    ui::label(key(), body, "Dear ImGui is licensed under the MIT License, see LICENSE for more information.");
    ui::label(key(), body, "If your company uses this, please consider funding the project.");

    static bool show_config_info = false;
    ui::checkbox(key(), body, "Config/Build Information", show_config_info);
    if (show_config_info)
    {
        ui::IO& io = ui::io();
        ImguiLook& style = ui::get_look();

        bool copy_to_clipboard = ui::button(key(), body, "Copy to clipboard").activated();
        vec2 child_size = vec2(0, ui::get_text_line_height_with_spacing() * 18);
        Widget child = *ui::begin_child(key(), body, child_size); // ImGuiChildFlags_FrameStyle
        string log;
        auto text = [&](NodeKey id, const string& line) { ui::text(id, child, line); log += line + "\n"; };
        if (copy_to_clipboard)
        {
            log += "// (Copy from the next line. Keep the ``` markers for formatting.)\n";
            log += "```cpp\n"; // Back quotes will make text appears without formatting when pasting on GitHub
        }

        text(key(), ui::format("Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM));
        ui::separator(key(), child);
        text(key(), ui::format("sizeof(size_t): %d, sizeof(ImDrawIdx): %d, sizeof(ImDrawVert): %d", (int)sizeof(size_t), 0, 0));
        text(key(), ui::format("define: __cplusplus=%d", (int)__cplusplus));
#ifdef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
        text(key(), "define: IMGUI_DISABLE_OBSOLETE_FUNCTIONS");
#endif
#ifdef _WIN32
        text(key(), "define: _WIN32");
#endif
#ifdef _WIN64
        text(key(), "define: _WIN64");
#endif
#ifdef __linux__
        text(key(), "define: __linux__");
#endif
#ifdef __APPLE__
        text(key(), "define: __APPLE__");
#endif
#ifdef _MSC_VER
        text(key(), ui::format("define: _MSC_VER=%d", _MSC_VER));
#endif
#ifdef _MSVC_LANG
        text(key(), ui::format("define: _MSVC_LANG=%d", (int)_MSVC_LANG));
#endif
#ifdef __MINGW32__
        text(key(), "define: __MINGW32__");
#endif
#ifdef __MINGW64__
        text(key(), "define: __MINGW64__");
#endif
#ifdef __GNUC__
        text(key(), ui::format("define: __GNUC__=%d", (int)__GNUC__));
#endif
#ifdef __clang_version__
        text(key(), ui::format("define: __clang_version__=%s", __clang_version__));
#endif
#ifdef __EMSCRIPTEN__
        text(key(), "define: __EMSCRIPTEN__");
#endif
#ifdef NDEBUG
        text(key(), "define: NDEBUG");
#endif

        // Heuristic to detect no-op IM_ASSERT() macros
        // - This is designed so people opening bug reports would convey and notice that they have disabled asserts for Dear ImGui code.
        // - 16 is > strlen("((void)(_EXPR))") which we suggested in our imconfig.h template as a possible way to disable.
        //int assert_runs_expression = 0;
        //IM_ASSERT(++assert_runs_expression);
        //int assert_expand_len = (int)strlen(IM_STRINGIFY((IM_ASSERT(true))));
        //bool assert_maybe_disabled = (!assert_runs_expression || assert_expand_len <= 16);
        //ImGui::Text("IM_ASSERT: runs expression: %s. expand size: %s%s",
        //    assert_runs_expression ? "OK" : "KO", (assert_expand_len > 16) ? "OK" : "KO", assert_maybe_disabled ? " (MAYBE DISABLED?!)" : "");
        //if (assert_maybe_disabled)
        //{
        //    ImGui::SameLine();
        //    HelpMarker("IM_ASSERT() calls assert() by default. Compiling with NDEBUG will usually strip out assert() to nothing, which is NOT recommended because we use asserts to notify of programmer mistakes!");
        //}

        ui::separator(key(), child);
        text(key(), ui::format("io.BackendPlatformName: %s", "two"));
        text(key(), ui::format("io.BackendRendererName: %s", "two.ui"));
        text(key(), ui::format("io.ConfigFlags: 0x%08X", io.ConfigFlags));
        if (io.ConfigFlags & ImGuiConfigFlags_NavEnableKeyboard)        text(key(), " NavEnableKeyboard");
        if (io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad)         text(key(), " NavEnableGamepad");
        if (io.ConfigFlags & ImGuiConfigFlags_NoMouse)                  text(key(), " NoMouse");
        if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)      text(key(), " NoMouseCursorChange");
        if (io.ConfigFlags & ImGuiConfigFlags_NoKeyboard)               text(key(), " NoKeyboard");
        if (io.MouseDrawCursor)                                         text(key(), "io.MouseDrawCursor");
        if (io.ConfigMacOSXBehaviors)                                   text(key(), "io.ConfigMacOSXBehaviors");
        if (io.ConfigNavMoveSetMousePos)                                text(key(), "io.ConfigNavMoveSetMousePos");
        if (io.ConfigNavCaptureKeyboard)                                text(key(), "io.ConfigNavCaptureKeyboard");
        if (io.ConfigInputTextCursorBlink)                              text(key(), "io.ConfigInputTextCursorBlink");
        if (io.ConfigWindowsResizeFromEdges)                            text(key(), "io.ConfigWindowsResizeFromEdges");
        if (io.ConfigWindowsMoveFromTitleBarOnly)                       text(key(), "io.ConfigWindowsMoveFromTitleBarOnly");
        if (io.ConfigMemoryCompactTimer >= 0.0f)                        text(key(), ui::format("io.ConfigMemoryCompactTimer = %.1f", io.ConfigMemoryCompactTimer));
        text(key(), ui::format("io.BackendFlags: 0x%08X", io.BackendFlags));
        if (io.BackendFlags & ImGuiBackendFlags_HasGamepad)             text(key(), " HasGamepad");
        if (io.BackendFlags & ImGuiBackendFlags_HasMouseCursors)        text(key(), " HasMouseCursors");
        if (io.BackendFlags & ImGuiBackendFlags_HasSetMousePos)         text(key(), " HasSetMousePos");
        if (io.BackendFlags & ImGuiBackendFlags_RendererHasVtxOffset)   text(key(), " RendererHasVtxOffset");
        if (io.BackendFlags & ImGuiBackendFlags_RendererHasTextures)    text(key(), " RendererHasTextures");
        ui::separator(key(), child);
        //ImGui::Text("io.Fonts: %d fonts, Flags: 0x%08X, TexSize: %d,%d", io.Fonts->Fonts.Size, io.Fonts->Flags, io.Fonts->TexData->Width, io.Fonts->TexData->Height);
        //ImGui::Text("io.Fonts->FontLoaderName: %s", io.Fonts->FontLoaderName ? io.Fonts->FontLoaderName : "NULL");
        text(key(), ui::format("io.DisplaySize: %.2f,%.2f", io.DisplaySize.x, io.DisplaySize.y));
        text(key(), ui::format("io.DisplayFramebufferScale: %.2f,%.2f", io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y));
        ui::separator(key(), child);
        text(key(), ui::format("style.WindowPadding: %.2f,%.2f", style.WindowPadding.x, style.WindowPadding.y));
        text(key(), ui::format("style.WindowBorderSize: %.2f", style.WindowBorderSize));
        text(key(), ui::format("style.FramePadding: %.2f,%.2f", style.FramePadding.x, style.FramePadding.y));
        text(key(), ui::format("style.FrameRounding: %.2f", style.FrameRounding));
        text(key(), ui::format("style.FrameBorderSize: %.2f", style.FrameBorderSize));
        text(key(), ui::format("style.ItemSpacing: %.2f,%.2f", style.ItemSpacing.x, style.ItemSpacing.y));
        text(key(), ui::format("style.ItemInnerSpacing: %.2f,%.2f", style.ItemInnerSpacing.x, style.ItemInnerSpacing.y));

        if (copy_to_clipboard)
        {
            log += "\n```\n";
            parent.ui_window().m_clipboard.m_text = log; // ImGui::LogFinish();
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] Style Editor / ShowStyleEditor()
//-----------------------------------------------------------------------------
// - ShowStyleSelector()
// - ShowStyleEditor()
//-----------------------------------------------------------------------------

// Demo helper function to select among default colors. See ShowStyleEditor() for more advanced options.
bool ShowStyleSelector(Widget parent, const char* label)
{
    // FIXME: This is a bit tricky to get right as style are functions, they don't register a name nor the fact that one is active.
    // So we keep track of last active one among our limited selection.
    static int style_idx = -1;
    // The two.ui styles are listed after the dear imgui ones, and the dear imgui v1.70 ones, kept for reference
    const char* style_names[] = { "Dark", "Light", "Classic", "Dark (v1.70)", "Light (v1.70)", "Classic (v1.70)", "Minimal", "Vector", "Blendish (Light)", "Blendish (Dark)", "Wonderland" };
    bool ret = false;
    if (Widget combo = ui::begin_combo(key(), parent, label, (style_idx >= 0 && style_idx < IM_COUNTOF(style_names)) ? style_names[style_idx] : ""))
    {
        for (int n = 0; n < IM_COUNTOF(style_names); n++)
        {
            if (ui::selectable(key(), *combo, style_names[n], style_idx == n).activated()) // ImGuiSelectableFlags_SelectOnNav
            {
                style_idx = n;
                ret = true;
                switch (style_idx)
                {
                case 0: ui::style_colors_dark(parent); break;
                case 1: ui::style_colors_light(parent); break;
                case 2: ui::style_colors_classic(parent); break;
                case 3: ui::set_style(parent, style_imgui_legacy_dark); break;
                case 4: ui::set_style(parent, style_imgui_legacy_light); break;
                case 5: ui::set_style(parent, style_imgui_legacy_classic); break;
                case 6: ui::set_style(parent, style_minimal); break;
                case 7: ui::set_style(parent, style_vector); break;
                case 8: ui::set_style(parent, style_blendish_light); break;
                case 9: ui::set_style(parent, style_blendish_dark); break;
                case 10: ui::style_wonderland(parent); break;
                }
            }
            //else if (style_idx == n)
            //    ImGui::SetItemDefaultFocus();
        }
    }
    return ret;
}

static const char* GetTreeLinesFlagsName(ImGuiTreeNodeFlags flags)
{
    if (flags == ImGuiTreeNodeFlags_DrawLinesNone) return "DrawLinesNone";
    if (flags == ImGuiTreeNodeFlags_DrawLinesFull) return "DrawLinesFull";
    if (flags == ImGuiTreeNodeFlags_DrawLinesToNodes) return "DrawLinesToNodes";
    return "";
}

// We omit the ImGui:: prefix in this function, as we don't expect user to be copy and pasting this code.
void ShowStyleEditor(Widget parent, ImguiTheme* ref)
{
    using namespace ui;

    IMGUI_DEMO_MARKER("Tools/Style Editor");
    // You can pass in a reference ImGuiStyle structure to compare to, revert to and save to
    // (without a reference style pointer, we will use one compared locally as a reference)
    ImguiTheme& style = get_theme();
    static ImguiTheme ref_saved_style;

    // Default to using internal storage as reference
    static bool init = true;
    if (init && ref == NULL)
        ref_saved_style = style;
    init = false;
    if (ref == NULL)
        ref = &ref_saved_style;

    // The logic behind dynamically changing 'max_border_size' is to not encourage people to increase border size too much: it'll likely reveal lots of subtle rendering artifacts and this isn't a priority right now.
    // Note that _MainScale is currently internal PLEASE DO NOT USE IN YOUR CODE.
    const float default_border_size = 1.0f; // (float)(int)style._MainScale;
    const float max_border_size = IM_MAX(default_border_size, 2.0f);

    push_item_width(get_window_width(parent) * 0.50f);

    {
        // General
        separator_text(key(), parent, "General");
        if ((io().BackendFlags & ImGuiBackendFlags_RendererHasTextures) == 0)
        {
            bullet(key(), parent, "Warning: Font scaling will NOT be smooth, because\nImGuiBackendFlags_RendererHasTextures is not set!");
            Widget line = row(key(), parent);
            bullet(key(), line, "For instructions, see:");
            //SameLine();
            text_link(key(), line, "docs/BACKENDS.md", "https://github.com/ocornut/imgui/blob/master/docs/BACKENDS.md");
        }

        if (ShowStyleSelector(parent, "Colors##Selector"))
            ref_saved_style = style;
        ShowFontSelector(parent, "Fonts##Selector");
        Widget font_line = row(key(), parent);
        if (drag_float(key(), font_line, "FontSizeBase", style.look.FontSizeBase, 0.20f, 5.0f, 100.0f)) // "%.0f"
            {} //style._NextFrameFontSizeBase = style.FontSizeBase; // FIXME: Temporary hack until we finish remaining work.
        /*SameLine(0.0f, 0.0f);*/ textf(key(), font_line, " (out %.2f)", get_font_size());
        drag_float(key(), parent, "FontScaleMain", style.look.FontScaleMain, 0.02f, 0.5f, 4.0f);
        //BeginDisabled(GetIO().ConfigDpiScaleFonts);
        drag_float(key(), parent, "FontScaleDpi", style.look.FontScaleDpi, 0.02f, 0.5f, 4.0f);
        //SetItemTooltip("When io.ConfigDpiScaleFonts is set, this value is automatically overwritten.");
        //EndDisabled();

        // Simplified Settings (expose floating-pointer border sizes as boolean representing 0.0f or 1.0f)
        if (slider_float(key(), parent, "FrameRounding", style.look.FrameRounding, 0.0f, 12.0f)) // "%.0f"
            style.look.GrabRounding = style.look.FrameRounding; // Make GrabRounding always the same value as FrameRounding
        Widget borders = row(key(), parent);
        { bool border = (style.look.WindowBorderSize > 0.0f); if (checkbox(key(), borders, "WindowBorder", border)) { style.look.WindowBorderSize = border ? default_border_size : 0.0f; } }
        //SameLine();
        { bool border = (style.look.FrameBorderSize > 0.0f);  if (checkbox(key(), borders, "FrameBorder", border)) { style.look.FrameBorderSize = border ? default_border_size : 0.0f; } }
        //SameLine();
        { bool border = (style.look.PopupBorderSize > 0.0f);  if (checkbox(key(), borders, "PopupBorder", border)) { style.look.PopupBorderSize = border ? default_border_size : 0.0f; } }
    }

    // Save/Revert button
    Widget save_revert = row(key(), parent);
    if (button(key(), save_revert, "Save Ref").activated())
        *ref = ref_saved_style = style;
    //SameLine();
    if (button(key(), save_revert, "Revert Ref").activated())
        style = *ref;
    //SameLine();
    HelpMarker(save_revert,
        "Save/Revert in local non-persistent storage. Default Colors definition are not affected. "
        "Use \"Export\" below to save them somewhere.");

    separator_text(key(), parent, "Details");
    Tabber tab_bar = tabber(key(), parent); // BeginTabBar("##tabs", ImGuiTabBarFlags_None)
    {
        if (Widget tab_sizes = tab(key(), tab_bar, "Sizes"))
        {
            Widget t = *tab_sizes;
            ImguiLook& look = style.look;
            separator_text(key(), t, "Main");
            slider_float2(key(), t, "WindowPadding", (float*)&look.WindowPadding, 0.0f, 20.0f); // "%.0f"
            slider_float2(key(), t, "FramePadding", (float*)&look.FramePadding, 0.0f, 20.0f); // "%.0f"
            slider_float2(key(), t, "ItemSpacing", (float*)&look.ItemSpacing, 0.0f, 20.0f); // "%.0f"
            slider_float2(key(), t, "ItemInnerSpacing", (float*)&look.ItemInnerSpacing, 0.0f, 20.0f); // "%.0f"
            slider_float2(key(), t, "TouchExtraPadding", (float*)&look.TouchExtraPadding, 0.0f, 10.0f); // "%.0f"
            slider_float(key(), t, "IndentSpacing", look.IndentSpacing, 0.0f, 30.0f); // "%.0f"
            slider_float(key(), t, "GrabMinSize", look.GrabMinSize, 1.0f, 20.0f); // "%.0f"

            separator_text(key(), t, "Borders");
            slider_float(key(), t, "WindowBorderSize", look.WindowBorderSize, 0.0f, max_border_size); // "%.0f"
            slider_float(key(), t, "ChildBorderSize", look.ChildBorderSize, 0.0f, max_border_size); // "%.0f"
            slider_float(key(), t, "PopupBorderSize", look.PopupBorderSize, 0.0f, max_border_size); // "%.0f"
            slider_float(key(), t, "FrameBorderSize", look.FrameBorderSize, 0.0f, max_border_size); // "%.0f"

            separator_text(key(), t, "Rounding");
            slider_float(key(), t, "WindowRounding", look.WindowRounding, 0.0f, 12.0f); // "%.0f"
            slider_float(key(), t, "ChildRounding", look.ChildRounding, 0.0f, 12.0f); // "%.0f"
            slider_float(key(), t, "FrameRounding", look.FrameRounding, 0.0f, 12.0f); // "%.0f"
            slider_float(key(), t, "PopupRounding", look.PopupRounding, 0.0f, 12.0f); // "%.0f"
            slider_float(key(), t, "GrabRounding", look.GrabRounding, 0.0f, 12.0f); // "%.0f"
            slider_float(key(), t, "MenuItemRounding", look.MenuItemRounding, 0.0f, 12.0f); // "%.0f"
            // NB: SelectableRounding is intentionally NOT made visible here. We don't want to encourage people using that.

            separator_text(key(), t, "Scrollbar");
            slider_float(key(), t, "ScrollbarSize", look.ScrollbarSize, 1.0f, 20.0f); // "%.0f"
            slider_float(key(), t, "ScrollbarRounding", look.ScrollbarRounding, 0.0f, 12.0f); // "%.0f"
            slider_float(key(), t, "ScrollbarPadding", look.ScrollbarPadding, 0.0f, 10.0f); // "%.0f"

            separator_text(key(), t, "Tabs");
            slider_float(key(), t, "TabBorderSize", look.TabBorderSize, 0.0f, max_border_size); // "%.0f"
            slider_float(key(), t, "TabBarBorderSize", look.TabBarBorderSize, 0.0f, max_border_size); // "%.0f"
            { Widget line = row(key(), t); slider_float(key(), line, "TabBarOverlineSize", look.TabBarOverlineSize, 0.0f, IM_MAX(3.0f, max_border_size)); // "%.0f"
              /*SameLine();*/ HelpMarker(line, "Overline is only drawn over the selected tab when ImGuiTabBarFlags_DrawSelectedOverline is set."); }
            drag_float(key(), t, "TabMinWidthBase", look.TabMinWidthBase, 0.5f, 1.0f, 500.0f); // "%.0f"
            drag_float(key(), t, "TabMinWidthShrink", look.TabMinWidthShrink, 0.5f, 1.0f, 500.0f); // "%0.f"
            drag_float(key(), t, "TabCloseButtonMinWidthSelected", look.TabCloseButtonMinWidthSelected, 0.5f, -1.0f, 100.0f); // (style.TabCloseButtonMinWidthSelected < 0.0f) ? "%.0f (Always)" : "%.0f"
            drag_float(key(), t, "TabCloseButtonMinWidthUnselected", look.TabCloseButtonMinWidthUnselected, 0.5f, -1.0f, 100.0f); // (style.TabCloseButtonMinWidthUnselected < 0.0f) ? "%.0f (Always)" : "%.0f"
            slider_float(key(), t, "TabRounding", look.TabRounding, 0.0f, 12.0f); // "%.0f"

            separator_text(key(), t, "Tables");
            slider_float2(key(), t, "CellPadding", (float*)&look.CellPadding, 0.0f, 20.0f); // "%.0f"
            slider_angle(key(), t, "TableAngledHeadersAngle", look.TableAngledHeadersAngle, -50.0f, +50.0f);
            slider_float2(key(), t, "TableAngledHeadersTextAlign", (float*)&look.TableAngledHeadersTextAlign, 0.0f, 1.0f); // "%.2f"

            separator_text(key(), t, "Trees");
            Widget tree_lines = row(key(), t);
            Widget combo_open = begin_combo(key(), tree_lines, "TreeLinesFlags", GetTreeLinesFlagsName(look.TreeLinesFlags));
            //SameLine();
            HelpMarker(tree_lines, "[Experimental] Tree lines may not work in all situations (e.g. using a clipper) and may incurs slight traversal overhead.\n\nImGuiTreeNodeFlags_DrawLinesFull is faster than ImGuiTreeNodeFlags_DrawLinesToNode.");
            if (combo_open)
            {
                const ImGuiTreeNodeFlags options[] = { ImGuiTreeNodeFlags_DrawLinesNone, ImGuiTreeNodeFlags_DrawLinesFull, ImGuiTreeNodeFlags_DrawLinesToNodes };
                for (ImGuiTreeNodeFlags option : options)
                    if (selectable(key(), *combo_open, GetTreeLinesFlagsName(option), look.TreeLinesFlags == option).activated())
                        look.TreeLinesFlags = option;
            }
            slider_float(key(), t, "TreeLinesSize", look.TreeLinesSize, 0.0f, max_border_size); // "%.0f"
            slider_float(key(), t, "TreeLinesRounding", look.TreeLinesRounding, 0.0f, 12.0f); // "%.0f"

            separator_text(key(), t, "Windows");
            slider_float2(key(), t, "WindowTitleAlign", (float*)&look.WindowTitleAlign, 0.0f, 1.0f); // "%.2f"
            slider_float(key(), t, "WindowBorderHoverPadding", look.WindowBorderHoverPadding, 1.0f, 20.0f); // "%.0f"
            int window_menu_button_position = look.WindowMenuButtonPosition + 1;
            if (combo(key(), t, "WindowMenuButtonPosition", window_menu_button_position, { "None", "Left", "Right" }))
                look.WindowMenuButtonPosition = window_menu_button_position - 1;

            separator_text(key(), t, "Widgets");
            slider_float(key(), t, "ColorMarkerSize", look.ColorMarkerSize, 0.0f, 8.0f); // "%.0f"
            combo(key(), t, "ColorButtonPosition", look.ColorButtonPosition, { "Left", "Right" });
            { Widget line = row(key(), t); slider_float2(key(), line, "ButtonTextAlign", (float*)&look.ButtonTextAlign, 0.0f, 1.0f); // "%.2f"
              /*SameLine();*/ HelpMarker(line, "Alignment applies when a button is larger than its text content."); }
            { Widget line = row(key(), t); slider_float2(key(), line, "SelectableTextAlign", (float*)&look.SelectableTextAlign, 0.0f, 1.0f); // "%.2f"
              /*SameLine();*/ HelpMarker(line, "Alignment applies when a selectable is larger than its text content."); }
            slider_float(key(), t, "SeparatorSize", look.SeparatorSize, 0.0f, 10.0f); // "%.0f"
            slider_float(key(), t, "SeparatorTextBorderSize", look.SeparatorTextBorderSize, 0.0f, 10.0f); // "%.0f"
            slider_float2(key(), t, "SeparatorTextAlign", (float*)&look.SeparatorTextAlign, 0.0f, 1.0f); // "%.2f"
            slider_float2(key(), t, "SeparatorTextPadding", (float*)&look.SeparatorTextPadding, 0.0f, 40.0f); // "%.0f"
            slider_float(key(), t, "LogSliderDeadzone", look.LogSliderDeadzone, 0.0f, 12.0f); // "%.0f"
            slider_float(key(), t, "ImageRounding", look.ImageRounding, 0.0f, 12.0f); // "%.0f"
            slider_float(key(), t, "ImageBorderSize", look.ImageBorderSize, 0.0f, max_border_size); // "%.0f"

            separator_text(key(), t, "Tooltips");
            for (int n = 0; n < 2; n++)
                if (Widget node = tree_node_ex(key(n), t, n == 0 ? "HoverFlagsForTooltipMouse" : "HoverFlagsForTooltipNav").body)
                {
                    ImGuiHoveredFlags* p = (n == 0) ? &look.HoverFlagsForTooltipMouse : &look.HoverFlagsForTooltipNav;
                    checkbox_flags(key(), *node, "ImGuiHoveredFlags_DelayNone", *p, ImGuiHoveredFlags_DelayNone);
                    checkbox_flags(key(), *node, "ImGuiHoveredFlags_DelayShort", *p, ImGuiHoveredFlags_DelayShort);
                    checkbox_flags(key(), *node, "ImGuiHoveredFlags_DelayNormal", *p, ImGuiHoveredFlags_DelayNormal);
                    checkbox_flags(key(), *node, "ImGuiHoveredFlags_Stationary", *p, ImGuiHoveredFlags_Stationary);
                    checkbox_flags(key(), *node, "ImGuiHoveredFlags_NoSharedDelay", *p, ImGuiHoveredFlags_NoSharedDelay);
                }

            separator_text(key(), t, "Misc");
            { Widget line = row(key(), t); slider_float2(key(), line, "DisplayWindowPadding", (float*)&look.DisplayWindowPadding, 0.0f, 30.0f); /*SameLine();*/ HelpMarker(line, "Apply to regular windows: amount which we enforce to keep visible when moving near edges of your screen."); } // "%.0f"
            { Widget line = row(key(), t); slider_float2(key(), line, "DisplaySafeAreaPadding", (float*)&look.DisplaySafeAreaPadding, 0.0f, 30.0f); /*SameLine();*/ HelpMarker(line, "Apply to every windows, menus, popups, tooltips: amount where we avoid displaying contents. Adjust if you cannot see the edges of your screen (e.g. on a TV where scaling has not been configured)."); } // "%.0f"
        }

        if (Widget tab_colors = tab(key(), tab_bar, "Colors"))
        {
            Widget t = *tab_colors;
            static int output_dest = 0;
            static bool output_only_modified = true;
            Widget export_line = row(key(), t);
            if (button(key(), export_line, "Export").activated())
            {
                string log;
                log += "ImVec4* colors = GetStyle().Colors;" IM_NEWLINE;
                for (int i = 0; i < ImGuiCol_COUNT; i++)
                {
                    const Colour& col = style.colours[i];
                    const char* name = get_style_color_name(i);
                    if (!output_only_modified || memcmp(&col, &ref->colours[i], sizeof(Colour)) != 0)
                        log += format("colors[ImGuiCol_%s]%*s= ImVec4(%.2ff, %.2ff, %.2ff, %.2ff);" IM_NEWLINE,
                            name, 23 - (int)strlen(name), "", col.r, col.g, col.b, col.a);
                }
                if (output_dest == 0)
                    parent.ui_window().m_clipboard.m_text = log; // LogToClipboard();
                else
                    printf("%s", log.c_str()); // LogToTTY();
            }
            /*SameLine(); SetNextItemWidth(GetFontSize() * 10);*/ combo(key(), export_line, "##output_type", output_dest, { "To Clipboard", "To TTY" });
            /*SameLine();*/ checkbox(key(), export_line, "Only Modified Colors", output_only_modified);

            static ImGuiColorEditFlags alpha_flags = 0;
            Widget alpha_line = row(key(), t);
            if (radio_button(key(), alpha_line, "Opaque", alpha_flags == ImGuiColorEditFlags_AlphaOpaque))       { alpha_flags = ImGuiColorEditFlags_AlphaOpaque; } //SameLine();
            if (radio_button(key(), alpha_line, "Alpha",  alpha_flags == ImGuiColorEditFlags_None))              { alpha_flags = ImGuiColorEditFlags_None; } //SameLine();
            if (radio_button(key(), alpha_line, "Both",   alpha_flags == ImGuiColorEditFlags_AlphaPreviewHalf))  { alpha_flags = ImGuiColorEditFlags_AlphaPreviewHalf; } //SameLine();
            HelpMarker(alpha_line,
                "In the color list:\n"
                "Left-click on color square to open color picker,\n"
                "Right-click to open edit options menu.");

            static string filter;
            //SetNextItemWidth(-FLT_MIN);
            input_text_with_hint(key(), t, "##FilterColors", "Filter Colors (incl -excl)", filter);

            //SetNextWindowSizeConstraints(ImVec2(0.0f, GetTextLineHeightWithSpacing() * 10), ImVec2(FLT_MAX, FLT_MAX));
            Widget colors_child = *begin_child(key(), t, vec2(0, 0), true); // ImGuiChildFlags_Borders | ImGuiChildFlags_NavFlattened, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar
            push_item_width(get_font_size() * -12);
            for (int i = 0; i < ImGuiCol_COUNT; i++)
            {
                const char* name = get_style_color_name(i);
                if (!ui::filter(filter, name))
                    continue;
                //PushID(i);
                Widget line = row(key(i), colors_child);
                //if (Button("?"))
                //    DebugFlashStyleColor((ImGuiCol)i);
                //SetItemTooltip("Flash given color to identify places where it is used.");
                //SameLine();
                color_edit4(key(), line, "##color", &style.colours[i].r); // ImGuiColorEditFlags_AlphaBar | alpha_flags
                if (memcmp(&style.colours[i], &ref->colours[i], sizeof(Colour)) != 0)
                {
                    // Tips: in a real user application, you may want to merge and use an icon font into the main font,
                    // so instead of "Save"/"Revert" you'd use icons!
                    // Read the FAQ and docs/FONTS.md about using icon fonts. It's really easy and super convenient!
                    /*SameLine(0.0f, style.ItemInnerSpacing.x);*/ if (button(key(), line, "Save").activated()) { ref->colours[i] = style.colours[i]; }
                    /*SameLine(0.0f, style.ItemInnerSpacing.x);*/ if (button(key(), line, "Revert").activated()) { style.colours[i] = ref->colours[i]; }
                }
                //SameLine(0.0f, style.ItemInnerSpacing.x);
                label(key(), line, name);
                //PopID();
            }
            pop_item_width();
        }

        if (Widget tab_fonts = tab(key(), tab_bar, "Fonts"))
        {
            show_font_atlas(key(), *tab_fonts); // ShowFontAtlas(atlas);

            // Post-baking font scaling. Note that this is NOT the nice way of scaling fonts, read below.
            // (we enforce hard clamping manually as by default DragFloat/SliderFloat allows Ctrl+Click text to get out of bounds).
            /*
            SeparatorText("Legacy Scaling");
            const float MIN_SCALE = 0.3f;
            const float MAX_SCALE = 2.0f;
            HelpMarker(
                "Those are old settings provided for convenience.\n"
                "However, the _correct_ way of scaling your UI is currently to reload your font at the designed size, "
                "rebuild the font atlas, and call style.ScaleAllSizes() on a reference ImGuiStyle structure.\n"
                "Using those settings here will give you poor quality results.");
            PushItemWidth(GetFontSize() * 8);
            DragFloat("global scale", &io.FontGlobalScale, 0.005f, MIN_SCALE, MAX_SCALE, "%.2f", ImGuiSliderFlags_AlwaysClamp); // Scale everything
            //static float window_scale = 1.0f;
            //if (DragFloat("window scale", &window_scale, 0.005f, MIN_SCALE, MAX_SCALE, "%.2f", ImGuiSliderFlags_AlwaysClamp)) // Scale only this window
            //    SetWindowFontScale(window_scale);
            PopItemWidth();
            */
        }

        if (Widget tab_rendering = tab(key(), tab_bar, "Rendering"))
        {
            Widget t = *tab_rendering;
            ImguiLook& look = style.look;
            { Widget line = row(key(), t); checkbox(key(), line, "Anti-aliased lines", look.AntiAliasedLines);
              //SameLine();
              HelpMarker(line, "When disabling anti-aliasing lines, you'll probably want to disable borders in your style as well."); }

            { Widget line = row(key(), t); checkbox(key(), line, "Anti-aliased lines use texture", look.AntiAliasedLinesUseTex);
              //SameLine();
              HelpMarker(line, "Faster lines using texture data. Require backend to render with bilinear filtering (not point/nearest filtering)."); }

            checkbox(key(), t, "Anti-aliased fill", look.AntiAliasedFill);
            push_item_width(get_font_size() * 8);
            drag_float(key(), t, "Curve Tessellation Max Error", look.CurveTessellationMaxError, 0.02f, 0.10f, 10.0f); // "%.2f"
            if (look.CurveTessellationMaxError < 0.10f)
                look.CurveTessellationMaxError = 0.10f;

            // When editing the "Circle Segment Max Error" value, draw a preview of its effect on auto-tessellated circles.
            Widget circle_line = row(key(), t);
            drag_float(key(), circle_line, "Circle Tessellation Max Error", look.CircleTessellationMaxError , 0.005f, 0.10f, 5.0f); // "%.2f", ImGuiSliderFlags_AlwaysClamp
            const bool show_samples = is_item_active(circle_line);
            //if (show_samples)
            //    SetNextWindowPos(GetCursorScreenPos());
            if (show_samples)
            {
                Widget tooltip = begin_tooltip(key(), t);
                label(key(), tooltip, "(R = radius, N = approx number of segments)");
                spacing(key(), tooltip);
                Widget circles = row(key(), tooltip);
                const float min_widget_width = calc_text_size("R: MMM\nN: MMM").x;
                for (int n = 0; n < 8; n++)
                {
                    const float RAD_MIN = 5.0f;
                    const float RAD_MAX = 70.0f;
                    const float rad = RAD_MIN + (RAD_MAX - RAD_MIN) * (float)n / (8.0f - 1.0f);

                    Widget group = stack(key(n), circles); // BeginGroup();

                    // N is not always exact here due to how PathArcTo() function work internally
                    textf(key(), group, "R: %.f\nN: %d", rad, 0); // draw_list->_CalcCircleAutoSegmentCount(rad)

                    const float canvas_width = IM_MAX(min_widget_width, rad * 2.0f);
                    const float offset_x     = floorf(canvas_width * 0.5f);
                    const float offset_y     = floorf(RAD_MAX);

                    Widget canvas = dummy(key(), group, vec2(canvas_width, RAD_MAX * 2));
                    const Colour text_colour = style.colours[ImGuiCol_Text];
                    canvas.custom_draw() = [=](Widget widget, const vec4& rect, Vg& vg)
                    {
                        UNUSED(widget);
                        vg.path_circle(rect.pos + vec2(offset_x, offset_y), rad);
                        vg.stroke({ text_colour, 1.f }); // draw_list->AddCircle(ImVec2(p1.x + offset_x, p1.y + offset_y), rad, GetColorU32(ImGuiCol_Text));
                    };

                    /*
                    const ImVec2 p2 = GetCursorScreenPos();
                    draw_list->AddCircleFilled(ImVec2(p2.x + offset_x, p2.y + offset_y), rad, GetColorU32(ImGuiCol_Text));
                    Dummy(ImVec2(canvas_width, RAD_MAX * 2));
                    */

                    //EndGroup();
                    //SameLine();
                }
            }
            //SameLine();
            HelpMarker(circle_line, "When drawing circle primitives with \"num_segments == 0\" tessellation will be calculated automatically.");

            drag_float(key(), t, "Global Alpha", look.Alpha, 0.005f, 0.20f, 1.0f); // "%.2f" // Not exposing zero here so user doesn't "lose" the UI (zero alpha clips all widgets). But application code could have a toggle to switch between zero and non-zero.
            { Widget line = row(key(), t); drag_float(key(), line, "Disabled Alpha", look.DisabledAlpha, 0.005f, 0.0f, 1.0f); /*SameLine();*/ HelpMarker(line, "Additional alpha multiplier for disabled items (multiply over current value of Alpha)."); } // "%.2f"
            pop_item_width();
        }
    }
    pop_item_width();

    // In two.ui, the style is applied to the widget styles when it changes
    update_imgui_style(parent);
}

void ShowFontSelector(Widget parent, const char* label)
{
    // two.ui has a single font for now
    ui::label_text(key(), parent, label, "proggy");
}

//-----------------------------------------------------------------------------
// [SECTION] User Guide / ShowUserGuide()
//-----------------------------------------------------------------------------

// We omit the ImGui:: prefix in this function, as we don't expect user to be copy and pasting this code.
void ShowUserGuide(Widget parent)
{
    using namespace ui;

    IO& io = ui::io();
    bullet(key(), parent, "Double-click on title bar to collapse window.");
    bullet(key(), parent,
        "Click and drag on lower corner or border to resize window.\n"
        "(double-click to auto fit window to its contents)");
    bullet(key(), parent, "Ctrl+Click on a slider or drag box to input value as text.");
    bullet(key(), parent, "Tab/Shift+Tab to cycle through keyboard editable fields.");
    bullet(key(), parent, "Ctrl+Tab/Ctrl+Shift+Tab to focus windows.");
    if (io.FontAllowUserScaling)
        bullet(key(), parent, "Ctrl+Mouse Wheel to zoom window contents.");
    bullet(key(), parent, "While inputting text:\n");
    {
        Widget i = indent(key(), parent); // Indent();
        bullet(key(), i, "Ctrl+Left/Right to word jump.");
        bullet(key(), i, "Ctrl+A or double-click to select all.");
        bullet(key(), i, "Ctrl+X/C/V to use clipboard cut/copy/paste.");
        bullet(key(), i, "Ctrl+Z to undo, Ctrl+Y/Ctrl+Shift+Z to redo.");
        bullet(key(), i, "Escape to revert.");
        //Unindent();
    }
    bullet(key(), parent, "With Keyboard controls enabled:");
    {
        Widget i = indent(key(), parent); // Indent();
        bullet(key(), i, "Arrow keys or Home/End/PageUp/PageDown to navigate.");
        bullet(key(), i, "Space to activate a widget.");
        bullet(key(), i, "Return to input text into a widget.");
        bullet(key(), i, "Escape to deactivate a widget, close popup,\nexit a child window or the menu layer, clear focus.");
        bullet(key(), i, "Alt to jump to the menu layer of a window.");
        bullet(key(), i, "Menu or Shift+F10 to open a context menu.");
        //Unindent();
    }
    bullet(key(), parent, "With Gamepad controls enabled:");
    {
        Widget i = indent(key(), parent); // Indent();
        bullet(key(), i, "D-Pad: Navigate / Tweak / Resize (in Windowing mode).");
        bullet(key(), i, format("%s Face button: Activate / Open / Toggle. Hold: activate with text input.", io.ConfigNavSwapGamepadButtons ? "East" : "South"));
        bullet(key(), i, format("%s Face button: Cancel / Close / Exit.", io.ConfigNavSwapGamepadButtons ? "South" : "East"));
        bullet(key(), i, "West Face button: Toggle Menu. Hold for Windowing mode (Focus/Move/Resize windows).");
        bullet(key(), i, "North Face button: Open Context Menu.");
        bullet(key(), i, "L1/R1: Tweak Slower/Faster, Focus Previous/Next (in Windowing Mode).");
        //Unindent();
    }
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Main Menu Bar / ShowExampleAppMainMenuBar()
//-----------------------------------------------------------------------------
// - ShowExampleAppMainMenuBar()
// - ShowExampleMenuFile()
//-----------------------------------------------------------------------------

// Demonstrate creating a "main" fullscreen menu bar and populating it.
// Note the difference between BeginMainMenuBar() and BeginMenuBar():
// - BeginMenuBar() = menu-bar inside current window (which needs the ImGuiWindowFlags_MenuBar flag!)
// - BeginMainMenuBar() = helper to create menu-bar-sized window at the top of the main viewport + call BeginMenuBar() into it.
static void ShowExampleAppMainMenuBar(Widget parent)
{
    Widget menubar = ui::main_menu_bar(key(), parent); // ImGui::BeginMainMenuBar()
    {
        if (Widget menu = ui::begin_menu(key(), menubar, "File"))
        {
            IMGUI_DEMO_MARKER("Menu/File");
            ShowExampleMenuFile(*menu);
        }
        if (Widget menu = ui::begin_menu(key(), menubar, "Edit"))
        {
            IMGUI_DEMO_MARKER("Menu/Edit");
            if (ui::menu_item(key(), *menu, "Undo", "Ctrl+Z")) {}
            if (ui::menu_item(key(), *menu, "Redo", "Ctrl+Y", false, false)) {} // Disabled item
            ui::separator(key(), *menu);
            if (ui::menu_item(key(), *menu, "Cut", "Ctrl+X")) {}
            if (ui::menu_item(key(), *menu, "Copy", "Ctrl+C")) {}
            if (ui::menu_item(key(), *menu, "Paste", "Ctrl+V")) {}
        }
    }
}

// Note that shortcuts are currently provided for display only
// (future version will add explicit flags to BeginMenu() to request processing shortcuts)
static void ShowExampleMenuFile(Widget parent)
{
    IMGUI_DEMO_MARKER("Examples/Menu");
    ui::menu_item(key(), parent, "(demo menu)", NULL, false, false);
    if (ui::menu_item(key(), parent, "New")) {}
    if (ui::menu_item(key(), parent, "Open", "Ctrl+O")) {}
    if (Widget menu = ui::begin_menu(key(), parent, "Open Recent", true))
    {
        ui::menu_item(key(), *menu, "fish_hat.c");
        ui::menu_item(key(), *menu, "fish_hat.inl");
        ui::menu_item(key(), *menu, "fish_hat.h");
        if (Widget more = ui::begin_menu(key(), *menu, "More..", true))
        {
            ui::menu_item(key(), *more, "Hello");
            ui::menu_item(key(), *more, "Sailor");
            if (Widget recurse = ui::begin_menu(key(), *more, "Recurse..", true))
            {
                ShowExampleMenuFile(*recurse);
            }
        }
    }
    if (ui::menu_item(key(), parent, "Save", "Ctrl+S")) {}
    if (ui::menu_item(key(), parent, "Save As..")) {}

    ui::separator(key(), parent);
    if (Widget menu = ui::begin_menu(key(), parent, "Options", true))
    {
        IMGUI_DEMO_MARKER("Examples/Menu/Options");
        static bool enabled = true;
        ui::menu_item(key(), *menu, "Enabled", "", &enabled);
        if (Widget child = ui::begin_child(key(), *menu, vec2(0, ui::get_text_line_height_with_spacing() * 5.0f), true)) // ImGuiChildFlags_Borders
            for (int i = 0; i < 10; i++)
                ui::textf(key(), *child, "Scrolling Text %d", i);
        static float f = 0.5f;
        static int n = 0;
        ui::slider_float(key(), *menu, "Value", f, 0.0f, 1.0f);
        ui::input_float(key(), *menu, "Input", f, 0.1f);
        ui::combo(key(), *menu, "Combo", n, { "Yes", "No", "Maybe" });

        // Here we demonstrate appending again to the "Options" menu (which we already created above)
        // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
        // In a real code-base using it would make senses to use this feature from very different code locations.
        // In two.ui, a widget can't be appended to after it's declared: the contents of the second BeginMenu("Options") are declared here
        IMGUI_DEMO_MARKER("Examples/Menu/Append to an existing menu");
        static bool b = true;
        ui::checkbox(key(), *menu, "SomeOption", b);
    }

    if (Widget menu = ui::begin_menu(key(), parent, "Colors", true))
    {
        IMGUI_DEMO_MARKER("Examples/Menu/Colors");
        float sz = ui::get_text_line_height();
        for (int i = 0; i < ImGuiCol_COUNT; i++)
        {
            const char* name = ui::get_style_color_name((ImGuiCol)i);
            Widget line = ui::row(key(i), *menu);
            //ImVec2 p = ImGui::GetCursorScreenPos();
            //ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
            ui::color_button(key(), line, name, ui::get_theme().colours[i], vec2(sz, sz)); // ImGui::Dummy(ImVec2(sz, sz));
            //ImGui::SameLine();
            ui::menu_item(key(), line, name);
        }
    }

    // Here we demonstrate appending again to the "Options" menu (which we already created above)
    // Of course in this demo it is a little bit silly that this function calls BeginMenu("Options") twice.
    // In a real code-base using it would make senses to use this feature from very different code locations.
    //if (ImGui::BeginMenu("Options")) // <-- Append!
    //{
    //    IMGUI_DEMO_MARKER("Examples/Menu/Append to an existing menu");
    //    static bool b = true;
    //    ImGui::Checkbox("SomeOption", &b);
    //    ImGui::EndMenu();
    //}

    if (Widget menu = ui::begin_menu(key(), parent, "Disabled", true)) // Disabled
    {
        menu->enable_state(DISABLED); // IM_ASSERT(0);
    }
    if (ui::menu_item(key(), parent, "Checked", NULL, true)) {}
    ui::separator(key(), parent);
    if (ui::menu_item(key(), parent, "Quit", "Alt+F4")) {}
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Debug Console / ShowExampleAppConsole()
//-----------------------------------------------------------------------------

// Demonstrate creating a simple console window, with scrolling, filtering, completion and history.
// For the console example, we are using a more C++ like approach of declaring a class to hold both data and functions.
struct ExampleAppConsole
{
    string                InputBuf;
    vector<string>        Items;
    vector<const char*>   Commands;
    vector<string>        History;
    int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    string                Filter;
    bool                  AutoScroll;
    bool                  ScrollToBottom;
    bool                  OptionsPopup = false;

    ExampleAppConsole()
    {
        ClearLog();
        HistoryPos = -1;

        // "CLASSIFY" is here to provide the test case where "C"+[tab] completes to "CL" and display multiple matches.
        Commands.push_back("HELP");
        Commands.push_back("HISTORY");
        Commands.push_back("CLEAR");
        Commands.push_back("CLASSIFY");
        AutoScroll = true;
        ScrollToBottom = false;
        AddLog("Welcome to Dear ImGui!");
    }
    ~ExampleAppConsole()
    {
        ClearLog();
    }

    // Portable helpers
    static int   Stricmp(const char* s1, const char* s2)         { int d; while ((d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; } return d; }
    static int   Strnicmp(const char* s1, const char* s2, int n) { int d = 0; while (n > 0 && (d = toupper(*s2) - toupper(*s1)) == 0 && *s1) { s1++; s2++; n--; } return d; }
    static void  Strtrimblanks(string& s)                        { while (!s.empty() && s.back() == ' ') s.pop_back(); }

    void    ClearLog()
    {
        Items.clear();
    }

    void    AddLog(const char* fmt, ...)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, IM_COUNTOF(buf), fmt, args);
        buf[IM_COUNTOF(buf)-1] = 0;
        va_end(args);
        Items.push_back(buf);
    }

    void    Draw(Widget parent, const char* title, bool* p_open)
    {
        auto window = ui::begin(key(), parent, title, p_open, WindowState::Default, vec2(520, 600));
        if (!window)
        {
            return;
        }
        Widget body = *window->body;
        IMGUI_DEMO_MARKER("Examples/Console");

        // As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar.
        // So e.g. IsItemHovered() will return true when hovering the title bar.
        // Here we create a context menu only available from the title bar.
        if (Widget popup = ui::begin_popup_context_item(key(), *window->header))
        {
            if (ui::menu_item(key(), *popup, "Close Console"))
                *p_open = false;
        }

        ui::text_wrapped(key(), body,
            "This example implements a console with basic coloring, completion (TAB key) and history (Up/Down keys). A more elaborate "
            "implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
        ui::text_wrapped(key(), body, "Enter 'HELP' for help.");

        // TODO: display items starting from the bottom

        Widget buttons = ui::row(key(), body);
        if (ui::small_button(key(), buttons, "Add Debug Text").activated())  { AddLog("%d some text", int(Items.size())); AddLog("some more text"); AddLog("display very important message here!"); }
        //ImGui::SameLine();
        if (ui::small_button(key(), buttons, "Add Debug Error").activated()) { AddLog("[error] something went wrong"); }
        //ImGui::SameLine();
        if (ui::small_button(key(), buttons, "Clear").activated())           { ClearLog(); }
        //ImGui::SameLine();
        bool copy_to_clipboard = ui::small_button(key(), buttons, "Copy").activated();
        //static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

        ui::separator(key(), body);

        // Options, Filter
        Widget options_line = ui::row(key(), body);
        Widget options = ui::button(key(), options_line, "Options");
        ui::set_item_shortcut(options, InputMod::Ctrl, Key::O, ImGuiInputFlags_Tooltip);
        if (options.activated())
            OptionsPopup = true; // ImGui::OpenPopup("Options");
        //ImGui::SameLine();

        // Options menu
        if (Widget popup = ui::begin_popup(key(), options, OptionsPopup))
        {
            ui::checkbox(key(), *popup, "Auto-scroll", AutoScroll);
        }

        //ImGui::SetNextItemShortcut(ImGuiMod_Ctrl | ImGuiKey_F, ImGuiInputFlags_Tooltip);
        //ImGui::SetNextItemWidth(-FLT_MIN);
        ui::input_text_with_hint(key(), options_line, "##Filter", "Filter (incl -excl)", Filter);
        ui::separator(key(), body);

        // Reserve enough left-over height for 1 separator + 1 input text
        ImguiLook& style = ui::get_look();
        const float footer_height_to_reserve = style.SeparatorSize + style.ItemSpacing.y + ui::get_frame_height_with_spacing();
        ScrollSheet scrolling = ui::child(key(), body, vec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // ImGuiChildFlags_NavFlattened
        {
            Widget region = scrolling.body;
            if (Widget popup = ui::begin_popup_context_window(key(), scrolling))
            {
                if (ui::selectable(key(), *popup, "Clear", false).activated()) ClearLog();
            }

            // Display every line as a separate entry so we can change their color or add custom widgets.
            // If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
            // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping
            // to only process visible items. The clipper will automatically measure the height of your first item and then
            // "seek" to display only items in the visible area.
            // To use the clipper we can replace your standard loop:
            //      for (int i = 0; i < Items.Size; i++)
            //   With:
            //      ImGuiListClipper clipper;
            //      clipper.Begin(Items.Size);
            //      while (clipper.Step())
            //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
            // - That your items are evenly spaced (same height)
            // - That you have cheap random access to your elements (you can access them given their index,
            //   without processing all the ones before)
            // You cannot this code as-is if a filter is active because it breaks the 'cheap random-access' property.
            // We would need random-access on the post-filtered list.
            // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices
            // or offsets of items that passed the filtering test, recomputing this array when user changes the filter,
            // and appending newly elements as they are inserted. This is left as a task to the user until we can manage
            // to improve this example code!
            // If your items are of variable height:
            // - Split them into same height items would be simpler and facilitate random-seeking into your list.
            // - Consider using manual call to IsRectVisible() and skipping extraneous decoration from your items.
            ui::push_style_var(ImGuiStyleVar_ItemSpacing, vec2(4, 1)); // Tighten spacing
            string log;
            for (const string& item : Items)
            {
                if (!ui::filter(Filter, item))
                    continue;

                // Normally you would store more information in your item than just a string.
                // (e.g. make Items[] an array of structure, store color/type etc.)
                Colour color;
                bool has_color = false;
                if (strstr(item.c_str(), "[error]")) { color = Colour(1.0f, 0.4f, 0.4f, 1.0f); has_color = true; }
                else if (strncmp(item.c_str(), "# ", 2) == 0) { color = Colour(1.0f, 0.8f, 0.6f, 1.0f); has_color = true; }
                if (has_color)
                    ui::text_colored(key(), region, color, item.c_str()); // ImGui::PushStyleColor(ImGuiCol_Text, color);
                else
                    ui::label(key(), region, item);
                if (copy_to_clipboard)
                    log += item + "\n";
            }
            if (copy_to_clipboard)
                parent.ui_window().m_clipboard.m_text = log; // ImGui::LogToClipboard(); ImGui::LogFinish();

            // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
            // Using a scrollbar or mouse-wheel will take away from the bottom edge.
            if (ScrollToBottom || (AutoScroll && ui::get_scroll_y(scrolling) >= ui::get_scroll_max_y(scrolling)))
                ui::set_scroll_y(scrolling, ui::get_scroll_max_y(scrolling)); // ImGui::SetScrollHereY(1.0f);
            ScrollToBottom = false;

            ui::pop_style_var();
        }
        ui::separator(key(), body);

        // Command-line
        bool reclaim_focus = false;
        ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_EscapeClearsAll | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
        TextEditHandle input = ui::input_text_edit(key(), body, "Input", InputBuf, input_text_flags, &TextEditCallbackStub, (void*)this);
        if (input->m_entered)
        {
            string& s = InputBuf;
            Strtrimblanks(s);
            if (s[0])
                ExecCommand(s.c_str());
            s = "";
            reclaim_focus = true;
        }

        // Auto-focus on window apparition
        //ImGui::SetItemDefaultFocus();
        if (reclaim_focus)
            ui::set_keyboard_focus_here(input.self()); // Auto focus previous widget
    }

    void    ExecCommand(const char* command_line)
    {
        AddLog("# %s\n", command_line);

        // Insert into history. First find match and delete it so it can be pushed to the back.
        // This isn't trying to be smart or optimal.
        HistoryPos = -1;
        for (int i = int(History.size()) - 1; i >= 0; i--)
            if (Stricmp(History[i].c_str(), command_line) == 0)
            {
                History.erase(History.begin() + i);
                break;
            }
        History.push_back(command_line);

        // Process command
        if (Stricmp(command_line, "CLEAR") == 0)
        {
            ClearLog();
        }
        else if (Stricmp(command_line, "HELP") == 0)
        {
            AddLog("Commands:");
            for (int i = 0; i < int(Commands.size()); i++)
                AddLog("- %s", Commands[i]);
        }
        else if (Stricmp(command_line, "HISTORY") == 0)
        {
            int first = int(History.size()) - 10;
            for (int i = first > 0 ? first : 0; i < int(History.size()); i++)
                AddLog("%3d: %s\n", i, History[i].c_str());
        }
        else
        {
            AddLog("Unknown command: '%s'\n", command_line);
        }

        // On command input, we scroll to bottom even if AutoScroll==false
        ScrollToBottom = true;
    }

    // In C++11 you'd be better off using lambdas for this sort of forwarding callbacks
    static int TextEditCallbackStub(ui::InputTextCallbackData* data)
    {
        ExampleAppConsole* console = (ExampleAppConsole*)data->UserData;
        return console->TextEditCallback(data);
    }

    int     TextEditCallback(ui::InputTextCallbackData* data)
    {
        //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
        switch (data->EventFlag)
        {
        case ImGuiInputTextFlags_CallbackCompletion:
            {
                // Example of TEXT COMPLETION

                // Locate beginning of current word
                const char* word_end = data->Buf + data->CursorPos;
                const char* word_start = word_end;
                while (word_start > data->Buf)
                {
                    const char c = word_start[-1];
                    if (c == ' ' || c == '\t' || c == ',' || c == ';')
                        break;
                    word_start--;
                }

                // Build a list of candidates
                vector<const char*> candidates;
                for (int i = 0; i < int(Commands.size()); i++)
                    if (Strnicmp(Commands[i], word_start, (int)(word_end - word_start)) == 0)
                        candidates.push_back(Commands[i]);

                if (candidates.size() == 0)
                {
                    // No match
                    AddLog("No match for \"%.*s\"!\n", (int)(word_end - word_start), word_start);
                }
                else if (candidates.size() == 1)
                {
                    // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing.
                    data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                    data->InsertChars(data->CursorPos, candidates[0]);
                    data->InsertChars(data->CursorPos, " ");
                }
                else
                {
                    // Multiple matches. Complete as much as we can..
                    // So inputting "C"+Tab will complete to "CL" then display "CLEAR" and "CLASSIFY" as matches.
                    int match_len = (int)(word_end - word_start);
                    for (;;)
                    {
                        int c = 0;
                        bool all_candidates_matches = true;
                        for (int i = 0; i < int(candidates.size()) && all_candidates_matches; i++)
                            if (i == 0)
                                c = toupper(candidates[i][match_len]);
                            else if (c == 0 || c != toupper(candidates[i][match_len]))
                                all_candidates_matches = false;
                        if (!all_candidates_matches)
                            break;
                        match_len++;
                    }

                    if (match_len > 0)
                    {
                        data->DeleteChars((int)(word_start - data->Buf), (int)(word_end - word_start));
                        data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
                    }

                    // List matches
                    AddLog("Possible matches:\n");
                    for (int i = 0; i < int(candidates.size()); i++)
                        AddLog("- %s\n", candidates[i]);
                }

                break;
            }
        case ImGuiInputTextFlags_CallbackHistory:
            {
                // Example of HISTORY
                const int prev_history_pos = HistoryPos;
                if (data->EventKey == Key::Up)
                {
                    if (HistoryPos == -1)
                        HistoryPos = int(History.size()) - 1;
                    else if (HistoryPos > 0)
                        HistoryPos--;
                }
                else if (data->EventKey == Key::Down)
                {
                    if (HistoryPos != -1)
                        if (++HistoryPos >= int(History.size()))
                            HistoryPos = -1;
                }

                // A better implementation would preserve the data on the current input line along with cursor position.
                if (prev_history_pos != HistoryPos)
                {
                    const char* history_str = (HistoryPos >= 0) ? History[HistoryPos].c_str() : "";
                    data->DeleteChars(0, data->BufTextLen);
                    data->InsertChars(0, history_str);
                }
            }
        }
        return 0;
    }
};

static void ShowExampleAppConsole(Widget parent, bool* p_open)
{
    static ExampleAppConsole console;
    console.Draw(parent, "Example: Console", p_open);
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Image Viewer / ShowExampleAppImageViewer()
//-----------------------------------------------------------------------------

static void ShowExampleAppImageViewer(Widget parent, bool* p_open)
{
    Image* tex_ref = ui::font_atlas_texture(parent); // We don't have access to other textures in this demo!
    int tex_w = tex_ref ? int(tex_ref->d_size.x) : 0;
    int tex_h = tex_ref ? int(tex_ref->d_size.y) : 0;
    if (auto window = ui::begin(key(), parent, "Example: Image Viewer", p_open))
    {
        // @todo: the image viewer (ExampleImageViewerData) is kept under #if 0, see above
        //static ExampleImageViewerData image_viewer;
        //ExampleImageViewer_DrawOptions(&image_viewer);
        //ImVec2 canvas_size = ImGui::GetContentRegionAvail();
        //ImVec2 canvas_min_size = ImGui::IsWindowAppearing() ? ImVec2(3.0f * tex_w, 4.0f * tex_h) : ImVec2(1.0f, 1.0f);
        //canvas_size = ImVec2(IM_MAX(canvas_size.x, canvas_min_size.x), IM_MAX(canvas_size.y, canvas_min_size.y));
        //ExampleImageViewer_DrawCanvas(&image_viewer, canvas_size, tex_ref, tex_w, tex_h);
        ui::image(key(), *window->body, tex_ref, vec2(float(tex_w), float(tex_h)));
    }
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Debug Log / ShowExampleAppLog()
//-----------------------------------------------------------------------------

// Usage:
//  static ExampleAppLog my_log;
//  my_log.AddLog("Hello %d world\n", 123);
//  my_log.Draw("title");
struct ExampleAppLog
{
    string              Buf;
    string              Filter;
    vector<int>         LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool                AutoScroll;  // Keep scrolling if already at the bottom.
    bool                OptionsPopup = false;

    ExampleAppLog()
    {
        AutoScroll = true;
        Clear();
    }

    void    Clear()
    {
        Buf.clear();
        LineOffsets.clear();
        LineOffsets.push_back(0);
    }

    void    AddLog(const char* fmt, ...)
    {
        int old_size = int(Buf.size());
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, IM_COUNTOF(buf), fmt, args);
        va_end(args);
        Buf += buf;
        for (int new_size = int(Buf.size()); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size + 1);
    }

    void    Draw(Widget parent, const char* title, bool* p_open = NULL)
    {
        auto window = ui::begin(key(), parent, title, p_open);
        if (!window)
        {
            return;
        }
        Widget body = *window->body;

        // Main window
        Widget line = ui::row(key(), body);
        Widget options = ui::button(key(), line, "Options");
        if (options.activated())
            OptionsPopup = true; // ImGui::OpenPopup("Options");

        // Options menu
        if (Widget popup = ui::begin_popup(key(), options, OptionsPopup))
        {
            ui::checkbox(key(), *popup, "Auto-scroll", AutoScroll);
        }

        //ImGui::SameLine();
        bool clear = ui::button(key(), line, "Clear").activated();
        //ImGui::SameLine();
        bool copy = ui::button(key(), line, "Copy").activated();
        //ImGui::SameLine();
        //ImGui::SetNextItemWidth(-FLT_MIN);
        ui::input_text_with_hint(key(), line, "##Filter", "Filter (incl -excl)", Filter);

        ui::separator(key(), body);

        ScrollSheet scrolling = ui::child(key(), body, vec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar); // ImGuiChildFlags_None
        {
            Widget region = scrolling.body;
            if (clear)
                Clear();
            if (copy)
                parent.ui_window().m_clipboard.m_text = Buf; // ImGui::LogToClipboard();

            ui::push_style_var(ImGuiStyleVar_ItemSpacing, vec2(0, 0));
            const char* buf = Buf.c_str();
            const char* buf_end = Buf.c_str() + Buf.size();
            if (!Filter.empty()) // Filter.IsActive()
            {
                // In this example we don't use the clipper when Filter is enabled.
                // This is because we don't have random access to the result of our filter.
                // A real application processing logs with ten of thousands of entries may want to store the result of
                // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
                for (int line_no = 0; line_no < int(LineOffsets.size()); line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < int(LineOffsets.size())) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    const string text = string(line_start, line_end);
                    if (ui::filter(Filter, text))
                        ui::label(key(), region, text);
                }
            }
            else
            {
                // The simplest and easy way to display the entire buffer:
                //   ImGui::TextUnformatted(buf_begin, buf_end);
                // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
                // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
                // within the visible area.
                // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
                // on your side is recommended. Using ImGuiListClipper requires
                // - A) random access into your data
                // - B) items all being the  same height,
                // both of which we can handle since we have an array pointing to the beginning of each line of text.
                // When using the filter (in the block of code above) we don't have random access into the data to display
                // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
                // it possible (and would be recommended if you want to search through tens of thousands of entries).
                // @todo: ImGuiListClipper, in two.ui all the lines are declared
                for (int line_no = 0; line_no < int(LineOffsets.size()); line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end = (line_no + 1 < int(LineOffsets.size())) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    ui::label(key(), region, string(line_start, line_end));
                }
            }
            ui::pop_style_var();

            // Keep up at the bottom of the scroll region if we were already at the bottom at the beginning of the frame.
            // Using a scrollbar or mouse-wheel will take away from the bottom edge.
            if (AutoScroll && ui::get_scroll_y(scrolling) >= ui::get_scroll_max_y(scrolling))
                ui::set_scroll_y(scrolling, ui::get_scroll_max_y(scrolling)); // ImGui::SetScrollHereY(1.0f);
        }
    }
};

// Demonstrate creating a simple log window with basic filtering.
static void ShowExampleAppLog(Widget parent, bool* p_open)
{
    static ExampleAppLog log;

    // For the demo: add a debug button _BEFORE_ the normal log window contents
    // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
    // Most of the contents of the window will be added by the log.Draw() call.
    // In two.ui, a window can't be appended to after it's declared: the debug button is declared in a window above the log window
    if (auto window = ui::begin(key(), parent, "Example: Log (debug)", p_open, WindowState::Default, vec2(500, 100)))
    {
        IMGUI_DEMO_MARKER("Examples/Log");
        if (ui::small_button(key(), *window->body, "[Debug] Add 5 entries").activated())
        {
            static int counter = 0;
            const char* categories[3] = { "info", "warn", "error" };
            const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
            for (int n = 0; n < 5; n++)
            {
                const char* category = categories[counter % IM_COUNTOF(categories)];
                const char* word = words[counter % IM_COUNTOF(words)];
                log.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
                    ui::get_frame_count(), category, ui::io().Time, word);
                counter++;
            }
        }
    }

    // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
    log.Draw(parent, "Example: Log", p_open);
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Simple Layout / ShowExampleAppLayout()
//-----------------------------------------------------------------------------

// Demonstrate create a window with multiple child windows.
static void ShowExampleAppLayout(Widget parent, bool* p_open)
{
    if (auto window = ui::begin(key(), parent, "Example: Simple layout", p_open, WindowState(uint32_t(WindowState::Default) | uint32_t(WindowState::Menu)), vec2(500, 440)))
    {
        IMGUI_DEMO_MARKER("Examples/Simple layout");
        if (window->menu)
        {
            if (Widget menu = ui::begin_menu(key(), *window->menu, "File"))
            {
                if (ui::menu_item(key(), *menu, "Close", "Ctrl+W")) { *p_open = false; }
            }
        }

        Widget line = ui::row(key(), *window->body);
        // Left
        static int selected = 0;
        {
            Widget left = *ui::begin_child(key(), line, vec2(150, 0), true); // ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX
            for (int i = 0; i < 100; i++)
            {
                char label[128];
                sprintf(label, "MyObject %d", i);
                if (ui::selectable(key(), left, label, selected == i).activated()) // ImGuiSelectableFlags_SelectOnNav
                    selected = i;
            }
        }
        //ImGui::SameLine();

        // Right
        {
            Widget group = ui::stack(key(), line); // ImGui::BeginGroup();
            Widget item_view = *ui::begin_child(key(), group, vec2(0, -ui::get_frame_height_with_spacing())); // Leave room for 1 line below us
            ui::textf(key(), item_view, "MyObject: %d", selected);
            ui::separator(key(), item_view);
            Tabber tab_bar = ui::tabber(key(), item_view); // ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None)
            {
                if (Widget tab = ui::tab(key(), tab_bar, "Description"))
                {
                    ui::text_wrapped(key(), *tab, "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
                }
                if (Widget tab = ui::tab(key(), tab_bar, "Details"))
                {
                    ui::label(key(), *tab, "ID: 0123456789");
                }
            }
            Widget buttons = ui::row(key(), group);
            if (ui::button(key(), buttons, "Revert").activated()) {}
            //ImGui::SameLine();
            if (ui::button(key(), buttons, "Save").activated()) {}
            //ImGui::EndGroup();
        }
    }
}

//-----------------------------------------------------------------------------
// [SECTION] Example App: Property Editor, Long Text, Auto Resize, Constrained Resize, Simple overlay, Fullscreen window,
//           Manipulating window titles, Custom Rendering, Documents Handling, Assets Browser
//-----------------------------------------------------------------------------
// @todo: port the remaining example apps

static void ShowExampleAppPropertyEditor(Widget parent, bool* p_open, ImGuiDemoWindowData* demo_data) { UNUSED(parent); UNUSED(p_open); UNUSED(demo_data); }
static void ShowExampleAppLongText(Widget parent, bool* p_open) { UNUSED(parent); UNUSED(p_open); }
static void ShowExampleAppAutoResize(Widget parent, bool* p_open) { UNUSED(parent); UNUSED(p_open); }
static void ShowExampleAppConstrainedResize(Widget parent, bool* p_open) { UNUSED(parent); UNUSED(p_open); }
static void ShowExampleAppSimpleOverlay(Widget parent, bool* p_open) { UNUSED(parent); UNUSED(p_open); }
static void ShowExampleAppFullscreen(Widget parent, bool* p_open) { UNUSED(parent); UNUSED(p_open); }
static void ShowExampleAppWindowTitles(Widget parent, bool* p_open) { UNUSED(parent); UNUSED(p_open); }
static void ShowExampleAppCustomRendering(Widget parent, bool* p_open) { UNUSED(parent); UNUSED(p_open); }
static void ShowExampleAppDocuments(Widget parent, bool* p_open) { UNUSED(parent); UNUSED(p_open); }
static void ShowExampleAppAssetsBrowser(Widget parent, bool* p_open) { UNUSED(parent); UNUSED(p_open); }

// End of Demo code

//-----------------------------------------------------------------------------
// [SECTION] Example Application / examples/example_glfw_opengl3/main.cpp
//-----------------------------------------------------------------------------
// The application of the dear imgui examples: the demo window, a simple window, and another window

void switchUiTheme(UiWindow& ui_window, const string& name)
{
    UNUSED(ui_window); UNUSED(name);
}

void example_ui(Widget root_sheet)
{
    ui::update_io(root_sheet.ui());
    ui::IO& io = ui::io();

    // Our state
    static bool show_demo_window = true;
    static bool show_another_window = false;
    static Colour clear_color = Colour(0.45f, 0.55f, 0.60f, 1.00f);

    // The background, cleared to clear_color
    Widget background = ui::board(key(), root_sheet);
    background.custom_draw() = [](Widget widget, const vec4& rect, Vg& vg) { UNUSED(widget); vg.draw_rect(rect, { clear_color }); };
    background.mark_dirty(DIRTY_REDRAW);

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window)
        ShowDemoWindow(root_sheet, &show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        if (auto window = ui::begin(key(), root_sheet, "Hello, world!"))   // Create a window called "Hello, world!" and append into it.
        {
            Widget body = *window->body;
            ui::label(key(), body, "This is some useful text.");                // Display some text (you can use a format strings too)
            ui::checkbox(key(), body, "Demo Window", show_demo_window);         // Edit bools storing our window open/close state
            ui::checkbox(key(), body, "Another Window", show_another_window);

            ui::slider_float(key(), body, "float", f, 0.0f, 1.0f);              // Edit 1 float using a slider from 0.0f to 1.0f
            ui::color_edit3(key(), body, "clear color", &clear_color.r);        // Edit 3 floats representing a color

            Widget line = ui::row(key(), body);
            if (ui::button(key(), line, "Button").activated())                 // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            //ImGui::SameLine();
            ui::textf(key(), line, "counter = %d", counter);

            ui::textf(key(), body, "Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        }
    }

    // 3. Show another simple window.
    if (show_another_window)
    {
        if (auto window = ui::begin(key(), root_sheet, "Another Window", &show_another_window))   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        {
            ui::label(key(), *window->body, "Hello from another window!");
            if (ui::button(key(), *window->body, "Close Me").activated())
                show_another_window = false;
        }
    }
}

#ifdef _00_IMGUI_EXE
bool pump(RenderSystem& render_system, BgfxContext& context, UiWindow& ui_window)
{
	bool pursue = context.begin_frame();
	pursue &= ui_window.input_frame();
	example_ui(ui_window.m_ui->begin());
	context.render_frame();
	ui_window.render_frame(240);
	render_system.end_frame();
	return pursue;
}

#ifdef TWO_PLATFORM_EMSCRIPTEN
	#include <emscripten/emscripten.h>

	RenderSystem* g_render_system = nullptr;
	BgfxContext* g_context = nullptr;
	UiWindow* g_window = nullptr;
	void iterate() { pump(*g_render_system, *g_context, *g_window); }
#endif

int main(int argc, char *argv[])
{
	UNUSED(argc); UNUSED(argv);
#ifdef SCRIPT
	System::instance().load_modules({ &two_obj::m(), &two_math::m(), &two_lang::m(), &two_ui::m() });
#endif

#ifdef TWO_RENDERER_GL
	static GlSystem render_system = { TWO_RESOURCE_PATH };
#elif defined TWO_RENDERER_BGFX
	static BgfxSystem render_system = { TWO_RESOURCE_PATH };
#endif

	static BgfxContext context = BgfxContext(render_system, "Dear ImGui two.ui example", uvec2(1280, 800), false, true);

	static VgVg vg = VgVg(TWO_RESOURCE_PATH, &render_system.allocator());
	vg.setup_context();

	static UiWindow ui_window = UiWindow(context, vg);

	ui_window.init();

	// Setup Dear ImGui style
	style_imgui_dark(ui_window);
	//style_imgui_light(ui_window);

#ifdef TWO_PLATFORM_EMSCRIPTEN
	g_render_system = &render_system;
	g_context = &context;
	g_window = &ui_window;
	emscripten_set_main_loop(iterate, 0, 1);
#else
	bool pursue = true;
	while(pursue)
		pump(render_system, context, ui_window);
#endif
}
#endif
