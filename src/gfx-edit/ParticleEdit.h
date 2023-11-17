//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx-edit/Forward.h>

namespace two
{
	TWO_GFX_EDIT_EXPORT void particle_edit(Widget& parent, GfxSystem& system, Flow& generator);
	TWO_GFX_EDIT_EXPORT void particle_edit(Widget& parent, GfxSystem& system, Call& particles);
	TWO_GFX_EDIT_EXPORT void particle_editor(Widget& parent, GfxSystem& system);
}
