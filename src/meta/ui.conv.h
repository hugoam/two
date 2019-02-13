#pragma once

#include <ui/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringOps.h>
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::Align& val) { val = mud::Align(enu<mud::Align>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Align& val, string& str) { str = enu<mud::Align>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::AutoLayout& val) { val = mud::AutoLayout(enu<mud::AutoLayout>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::AutoLayout& val, string& str) { str = enu<mud::AutoLayout>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Clip& val) { val = mud::Clip(enu<mud::Clip>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Clip& val, string& str) { str = enu<mud::Clip>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::FlowAxis& val) { val = mud::FlowAxis(enu<mud::FlowAxis>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::FlowAxis& val, string& str) { str = enu<mud::FlowAxis>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::LayoutFlow& val) { val = mud::LayoutFlow(enu<mud::LayoutFlow>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::LayoutFlow& val, string& str) { str = enu<mud::LayoutFlow>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Opacity& val) { val = mud::Opacity(enu<mud::Opacity>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Opacity& val, string& str) { str = enu<mud::Opacity>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Pivot& val) { val = mud::Pivot(enu<mud::Pivot>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Pivot& val, string& str) { str = enu<mud::Pivot>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::ui::PopupFlags& val) { val = mud::ui::PopupFlags(enu<mud::ui::PopupFlags>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::ui::PopupFlags& val, string& str) { str = enu<mud::ui::PopupFlags>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Preset& val) { val = mud::Preset(enu<mud::Preset>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Preset& val, string& str) { str = enu<mud::Preset>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Sizing& val) { val = mud::Sizing(enu<mud::Sizing>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Sizing& val, string& str) { str = enu<mud::Sizing>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::Solver& val) { val = mud::Solver(enu<mud::Solver>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Solver& val, string& str) { str = enu<mud::Solver>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::WidgetState& val) { val = mud::WidgetState(enu<mud::WidgetState>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::WidgetState& val, string& str) { str = enu<mud::WidgetState>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, mud::WindowState& val) { val = mud::WindowState(enu<mud::WindowState>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::WindowState& val, string& str) { str = enu<mud::WindowState>().name(uint32_t(val)); };
	
	
}
