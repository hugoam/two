#pragma once

#include <two/ui.h>
#include <two/refl.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <ui/Types.h>

#ifndef TWO_UI_REFL_EXPORT
#define TWO_UI_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_UI_REFL_EXPORT two_ui : public two::Module
	{
	private:
		two_ui();
		
	public:
		static two_ui& m() { static two_ui instance; return instance; }
	};
}

#ifdef TWO_UI_MODULE
extern "C"
TWO_UI_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::FlowAxis& val) { val = two::FlowAxis(enu<two::FlowAxis>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::FlowAxis& val, string& str) { str = enu<two::FlowAxis>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Pivot& val) { val = two::Pivot(enu<two::Pivot>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Pivot& val, string& str) { str = enu<two::Pivot>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Align& val) { val = two::Align(enu<two::Align>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Align& val, string& str) { str = enu<two::Align>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Solver& val) { val = two::Solver(enu<two::Solver>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Solver& val, string& str) { str = enu<two::Solver>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::AutoLayout& val) { val = two::AutoLayout(enu<two::AutoLayout>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::AutoLayout& val, string& str) { str = enu<two::AutoLayout>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::LayoutFlow& val) { val = two::LayoutFlow(enu<two::LayoutFlow>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::LayoutFlow& val, string& str) { str = enu<two::LayoutFlow>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Sizing& val) { val = two::Sizing(enu<two::Sizing>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Sizing& val, string& str) { str = enu<two::Sizing>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Preset& val) { val = two::Preset(enu<two::Preset>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Preset& val, string& str) { str = enu<two::Preset>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Clip& val) { val = two::Clip(enu<two::Clip>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Clip& val, string& str) { str = enu<two::Clip>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::Opacity& val) { val = two::Opacity(enu<two::Opacity>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::Opacity& val, string& str) { str = enu<two::Opacity>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::WidgetState& val) { val = two::WidgetState(enu<two::WidgetState>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::WidgetState& val, string& str) { str = enu<two::WidgetState>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::ui::PopupFlags& val) { val = two::ui::PopupFlags(enu<two::ui::PopupFlags>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::ui::PopupFlags& val, string& str) { str = enu<two::ui::PopupFlags>().name(uint32_t(val)); };
	
	export_ template <> inline void to_value(const string& str, two::WindowState& val) { val = two::WindowState(enu<two::WindowState>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::WindowState& val, string& str) { str = enu<two::WindowState>().name(uint32_t(val)); };
	
	
}
