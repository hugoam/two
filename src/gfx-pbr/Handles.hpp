//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx-pbr/Handles.h>
#include <gfx-pbr/VoxelGI.h>
#include <gfx-pbr/Lightmap.h>

namespace two
{
	GIProbeHandle::GIProbeHandle(Gnode self) : GnodeHandle(self) {}
	Gnode GIProbeHandle::self() const { return this->get(); }
	GIProbe& GIProbeHandle::probe() const { return *this->get().find_state<GIProbe>(); }
	GIProbe* GIProbeHandle::operator->() const { return &this->probe(); }
	GIProbe& GIProbeHandle::operator*() const { return this->probe(); }

	LightmapAtlasHandle::LightmapAtlasHandle(Gnode self) : GnodeHandle(self) {}
	Gnode LightmapAtlasHandle::self() const { return this->get(); }
	LightmapAtlas& LightmapAtlasHandle::atlas() const { return *this->get().find_state<LightmapAtlas>(); }
	LightmapAtlas* LightmapAtlasHandle::operator->() const { return &this->atlas(); }
	LightmapAtlas& LightmapAtlasHandle::operator*() const { return this->atlas(); }
}
