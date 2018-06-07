//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <ui/Ui.h>
#include <ui/Input.h>
#include <gfx/Particles.h>
#endif
#include <edit/Generated/Forward.h>

namespace mud
{
	template <class T>
	bool value_track_edit(Widget& parent, ValueTrack<T>& track)
	{
		Widget& self = ui::row(parent);
		static cstring modes[4] = { "Constant", "ConstantRandom", "Curve", "CurveRandom" };

		bool changed = false;
		TrackMode mode = track.m_mode;
		changed |= ui::dropdown_input(self, { modes, 4 }, (size_t&)mode, true);
		if(changed)
			track.set_mode(mode);

		if(track.m_mode == TrackMode::Constant)
			changed |= ui::input<T>(self, track.m_curve.m_keys[0]);
		else if(track.m_mode == TrackMode::ConstantRandom)
		{
			changed |= ui::input<T>(self, track.m_min_curve.m_keys[0]);
			changed |= ui::input<T>(self, track.m_max_curve.m_keys[0]);
		}
		else if(track.m_mode == TrackMode::Curve)
		{
			for(T& key : track.m_curve.m_keys)
				changed |= ui::input<T>(self, key);
			if(ui::button(self, "+").activated())
			{
				changed = true;
				track.m_curve.m_keys.push_back(track.m_curve.m_keys.back());
			}
			if(ui::button(self, "-").activated() && track.m_curve.m_keys.size() > 1)
			{
				changed = true;
				vector_pop(track.m_curve.m_keys);
			}
		}
		return changed;
	}

	MUD_EDIT_EXPORT void particle_edit(Widget& parent, GfxSystem& system, ParticleGenerator& generator);
	MUD_EDIT_EXPORT void particle_edit(Widget& parent, GfxSystem& system, Call& particles);
	MUD_EDIT_EXPORT void particle_editor(Widget& parent, GfxSystem& system);
}
