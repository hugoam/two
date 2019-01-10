#pragma once

#include <ui/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
	export_ template <> inline void from_string(const string& str, mud::Align& val) { val = static_cast<mud::Align>(enu<mud::Align>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Align& val, string& str) { str = enu<mud::Align>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::AutoLayout& val) { val = static_cast<mud::AutoLayout>(enu<mud::AutoLayout>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::AutoLayout& val, string& str) { str = enu<mud::AutoLayout>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::Clipping& val) { val = static_cast<mud::Clipping>(enu<mud::Clipping>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Clipping& val, string& str) { str = enu<mud::Clipping>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::Dim& val) { val = static_cast<mud::Dim>(enu<mud::Dim>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Dim& val, string& str) { str = enu<mud::Dim>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::Flow& val) { val = static_cast<mud::Flow>(enu<mud::Flow>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Flow& val, string& str) { str = enu<mud::Flow>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::FlowAxis& val) { val = static_cast<mud::FlowAxis>(enu<mud::FlowAxis>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::FlowAxis& val, string& str) { str = enu<mud::FlowAxis>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::LayoutSolver& val) { val = static_cast<mud::LayoutSolver>(enu<mud::LayoutSolver>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::LayoutSolver& val, string& str) { str = enu<mud::LayoutSolver>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::Opacity& val) { val = static_cast<mud::Opacity>(enu<mud::Opacity>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Opacity& val, string& str) { str = enu<mud::Opacity>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::Pivot& val) { val = static_cast<mud::Pivot>(enu<mud::Pivot>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Pivot& val, string& str) { str = enu<mud::Pivot>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::ui::PopupFlags& val) { val = static_cast<mud::ui::PopupFlags>(enu<mud::ui::PopupFlags>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::ui::PopupFlags& val, string& str) { str = enu<mud::ui::PopupFlags>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::Sizing& val) { val = static_cast<mud::Sizing>(enu<mud::Sizing>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::Sizing& val, string& str) { str = enu<mud::Sizing>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::SpacePreset& val) { val = static_cast<mud::SpacePreset>(enu<mud::SpacePreset>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::SpacePreset& val, string& str) { str = enu<mud::SpacePreset>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::WidgetState& val) { val = static_cast<mud::WidgetState>(enu<mud::WidgetState>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::WidgetState& val, string& str) { str = enu<mud::WidgetState>().m_map[size_t(val)]; };
	
	export_ template <> inline void from_string(const string& str, mud::WindowState& val) { val = static_cast<mud::WindowState>(enu<mud::WindowState>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::WindowState& val, string& str) { str = enu<mud::WindowState>().m_map[size_t(val)]; };
	
	
	export_ template <> inline void from_string(const string& str, mud::Dim2<bool>& val) { string_to_fixed_vector<mud::Dim2<bool>, bool>(str, val); };
	export_ template <> inline void to_string(const mud::Dim2<bool>& val, string& str) { fixed_vector_to_string<mud::Dim2<bool>, 2>(val, str); };
	
	export_ template <> inline void from_string(const string& str, mud::Dim2<mud::Align>& val) { string_to_fixed_vector<mud::Dim2<mud::Align>, mud::Align>(str, val); };
	export_ template <> inline void to_string(const mud::Dim2<mud::Align>& val, string& str) { fixed_vector_to_string<mud::Dim2<mud::Align>, 2>(val, str); };
	
	export_ template <> inline void from_string(const string& str, mud::Dim2<mud::AutoLayout>& val) { string_to_fixed_vector<mud::Dim2<mud::AutoLayout>, mud::AutoLayout>(str, val); };
	export_ template <> inline void to_string(const mud::Dim2<mud::AutoLayout>& val, string& str) { fixed_vector_to_string<mud::Dim2<mud::AutoLayout>, 2>(val, str); };
	
	export_ template <> inline void from_string(const string& str, mud::Dim2<mud::Pivot>& val) { string_to_fixed_vector<mud::Dim2<mud::Pivot>, mud::Pivot>(str, val); };
	export_ template <> inline void to_string(const mud::Dim2<mud::Pivot>& val, string& str) { fixed_vector_to_string<mud::Dim2<mud::Pivot>, 2>(val, str); };
	
	export_ template <> inline void from_string(const string& str, mud::Dim2<mud::Sizing>& val) { string_to_fixed_vector<mud::Dim2<mud::Sizing>, mud::Sizing>(str, val); };
	export_ template <> inline void to_string(const mud::Dim2<mud::Sizing>& val, string& str) { fixed_vector_to_string<mud::Dim2<mud::Sizing>, 2>(val, str); };
	
	export_ template <> inline void from_string(const string& str, mud::Dim2<size_t>& val) { string_to_fixed_vector<mud::Dim2<size_t>, size_t>(str, val); };
	export_ template <> inline void to_string(const mud::Dim2<size_t>& val, string& str) { fixed_vector_to_string<mud::Dim2<size_t>, 2>(val, str); };
	
}
