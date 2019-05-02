//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef TWO_MODULES
module two.uio;
#else
#include <stl/algorithm.h>
#include <refl/Meta.h>
#include <refl/Member.h>
#include <refl/Sequence.h>
#include <refl/Enum.h>
#include <type/DispatchDecl.h>
#include <math/Vec.hpp>
#include <math/Curve.h>
#include <math/Range.h>
#include <ui/Input.hpp>
#include <uio/Types.h>
#include <uio/ValueEdit.h>
#include <uio/Object.h>
#include <uio/Inspector.h>
#include <uio/InjectorEdit.h>
#include <uio/IndexerEdit.h>
#include <uio/MethodEdit.h>
#endif

namespace two
{
	template <class T>
	bool range_edit(Widget& parent, Range<T>& value)
	{
		Widget& self = ui::row(parent);
		static const StatDef<T> def = { T(0), T(100), T(1) };
		bool changed = false;
		changed |= ui::slider_field<T>(self, "min", value.m_min, def);
		changed |= ui::slider_field<T>(self, "max", value.m_max, def);
		return changed;
	}

	template <class T>
	bool curve_edit(Widget& parent, vector<T>& keys)
	{
		bool changed = false;
		for(T& key : keys)
			changed |= ui::input<T>(parent, key);
		if(ui::button(parent, "+").activated())
		{
			changed = true;
			keys.push_back(keys.back());
		}
		if(ui::button(parent, "-").activated() && keys.size() > 1)
		{
			changed = true;
			pop(keys);
		}
		return changed;
	}

	template <>
	bool curve_edit(Widget& parent, vector<float>& keys)
	{
		enum Modes { EDIT_CURVE = 1 << 0 };

		if(ui::modal_button(parent, parent, "+", EDIT_CURVE))
		{
			Widget& widget = ui::auto_modal(parent, EDIT_CURVE, { 300.f, 120.f });
			ui::label(*widget.m_body, "Curve Editor");
			return ui::curve_edit(*widget.m_body, span<float>(keys));
		}

		return false;
	}

	template <class T>
	bool value_track_edit(Widget& parent, ValueTrack<T>& track)
	{
		Widget& self = ui::row(parent);
		static cstring modes[4] = { "Constant", "ConstantRandom", "Curve", "CurveRandom" };

		bool changed = false;
		TrackMode mode = track.m_mode;
		changed |= ui::dropdown_input(self, { modes, 4 }, (uint32_t&)mode, true);
		if(changed)
			track.set_mode(mode);

		if(track.m_mode == TrackMode::Constant)
			changed |= ui::input<T>(self, track.m_value);
		else if(track.m_mode == TrackMode::ConstantRandom)
		{
			changed |= ui::input<T>(self, track.m_min);
			changed |= ui::input<T>(self, track.m_max);
		}
		else if(track.m_mode == TrackMode::Curve)
		{
			curve_edit<T>(self, track.m_curve.m_keys);
		}
		return changed;
	}

	template <class T, bool(*Input)(Widget&, T&)>
	bool value_input(T& value, Widget& parent) { return Input(parent, value); }

	template <class T, bool(*Input)(Widget&, T&, StatDef<T>)>
	bool stat_value_input(T& value, Widget& parent) { return Input(parent, value, { limits<T>::min(), limits<T>::max(), T(1) }); }

	template <class T, bool(*Input)(Widget&, T&, StatDef<T>), int decimal>
	bool stat_value_input(T& value, Widget& parent) { return Input(parent, value, { limits<T>::min(), limits<T>::max(), T(1) / T(decimal) }); }

	DispatchInput::DispatchInput()
	{
		dispatch_branch<bool>(*this, value_input<bool, ui::input<bool>>);
		dispatch_branch<uint8_t>(*this, stat_value_input<uint8_t, ui::number_input<uint8_t>>);
		dispatch_branch<uint16_t>(*this, stat_value_input<uint16_t, ui::number_input<uint16_t>>);
		dispatch_branch<unsigned int>(*this, stat_value_input<unsigned int, ui::number_input<unsigned int>>);
		dispatch_branch<uint64_t>(*this, stat_value_input<uint64_t, ui::number_input<uint64_t>>);
		dispatch_branch<int>(*this, stat_value_input<int, ui::number_input<int>>);
		dispatch_branch<float>(*this, stat_value_input<float, ui::number_input<float>, 10>);
		dispatch_branch<double>(*this, stat_value_input<double, ui::number_input<double>, 100>);
		// @todo : how to do with cstrings ?
		dispatch_branch<string>(*this, value_input<string, ui::input<string>>);

		dispatch_branch<Colour>(*this, value_input<Colour, ui::color_toggle_edit>);
		dispatch_branch<vec2>(*this, value_input<vec2, ui::vec2_edit>);
		dispatch_branch<vec3>(*this, value_input<vec3, ui::vec3_edit>);
		dispatch_branch<quat>(*this, value_input<quat, ui::quat_edit>);

		dispatch_branch<Range<uint32_t>>(*this, value_input<Range<uint32_t>, range_edit<uint32_t>>);
		dispatch_branch<Range<float>>(*this, value_input<Range<float>, range_edit<float>>);

		dispatch_branch<ValueTrack<float>>(*this, value_input<ValueTrack<float>, value_track_edit<float>>);
		dispatch_branch<ValueTrack<uint32_t>>(*this, value_input<ValueTrack<uint32_t>, value_track_edit<uint32_t>>);
		dispatch_branch<ValueTrack<vec3>>(*this, value_input<ValueTrack<vec3>, value_track_edit<vec3>>);
		dispatch_branch<ValueTrack<quat>>(*this, value_input<ValueTrack<quat>, value_track_edit<quat>>);
		dispatch_branch<ValueTrack<Colour>>(*this, value_input<ValueTrack<Colour>, value_track_edit<Colour>>);

		//dispatch_branch<Image256>([](Image256& image, Wedge& parent) -> object<Widget> { return oconstruct<Figure>(Widget::Input{ &parent }, image); });
	}

	bool type_selector(Widget& parent, uint32_t& type, span<Type*> types)
	{
		vector<cstring> type_names;
		for(size_t i = 0; i < types.size(); ++i)
			type_names.push_back(types[i]->m_name);

		return ui::dropdown_input(parent, type_names, type);
	}

	bool value_edit(Widget& parent, Ref& value)
	{
		// @kludge ? fix all value == Ref() in the code
		if(!(value == Ref()) && DispatchInput::me.check(value))
			return DispatchInput::me.dispatch(value, parent);
		return false;
	}

	bool none_edit(Widget& parent, Ref& value)
	{
		UNUSED(value);
		ui::label(parent, "None");
		return false;
	}

	bool enum_edit(Widget& parent, Ref& value)
	{
		Enum& e = enu(value);
		uint32_t index = e.index(value);
		//ui::radio_switch(parent, e.m_names, index);
		if(ui::dropdown_input(parent, e.m_names, index))
		{
			e.varn(index, value);
			return true;
		}
		return false;
	}

	bool object_link_edit(Widget& parent, Ref& value)
	{
		Widget& self = ui::row(parent);
		object_button(self, value);
		return object_selector_modal(self, self, value);
	}

	bool sequence_element_edit(Widget& parent, Ref seq, Ref& value)
	{
		object_item(parent, value);
		if(ui::button(parent, "remove").activated())
			sequence(seq).remove(seq, value);
		return false;
	}

	bool sequence_edit(Widget& parent, Ref& value, EditorHint hint)
	{
		enum Modes { Add = 1 << 0 };

		Widget& self = hint == EditorHint::Inline ? ui::row(parent)
												  : ui::sheet(parent);
		bool changed = false;
		iter(value).iterate(value, [&](Ref element) { changed |= value_edit(self, element); });
		if(ui::modal_button(self, self, "add", Add))
		{
			if(meta(*iter(value).m_element_type).m_empty_var)
			{
				sequence(value).add(value, meta(*iter(value).m_element_type).m_empty_var);
				self.m_switch &= ~Add;
				changed |= true;
			}
			else
			{
				Ref selected = Ref(*value.m_type);
				if(object_selector(self, selected))
				{
					sequence(value).add(value, selected);
					self.m_switch &= ~Add;
					changed |= true;
				}
			}
		}
		return changed;
	}

	bool any_edit(Widget& parent, Ref& value, bool link, EditorHint hint)
	{
		//if(is_struct(*value.m_type) && !nullable && !value)
		//	return object_creator(parent, *value.m_type);

		if(value == Ref() || value == Var() || type(value).is<Type>())
			return false;
		else if(DispatchInput::me.check(value))
			return DispatchInput::me.dispatch(value, parent);
		else if(type(value).is<Creator>())
			return object_creator(parent, val<Creator>(value));
		else if(type(value).is<Call>())
			return call_edit(parent, val<Call>(value));
		else if(is_base_type(type(value)))
			return value_edit(parent, value);
		else if(is_sequence(type(value)))
			return sequence_edit(parent, value, hint);
		else if(is_enum(type(value)))
			return enum_edit(parent, value);
		else if(link || value.m_value == nullptr)
			return object_link_edit(parent, value);
		else
			return object_edit(parent, value, hint);
	}

	bool field_edit(Widget& parent, cstring name, Ref& value, bool nullable)
	{
		Widget& self = ui::row(parent);
		ui::label(self, name);
		return any_edit(self, value, nullable);
	}

	bool modal_edit(Widget& parent, uint32_t mode, cstring name, Ref& value, bool nullable, bool confirm)
	{
		Widget& self = ui::modal(parent.parent_modal());
		bool changed = field_edit(self, name, value, nullable);
		bool done = confirm ? ui::button(self, "Done").activated() || !self.m_open
							: changed || !self.m_open;
		if(done)
			parent.m_switch &= ~mode;
		return done;
	}
}
