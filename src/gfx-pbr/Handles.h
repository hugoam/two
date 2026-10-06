//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx-pbr/Forward.h>

namespace two
{
	export_ enum class GIProbeIndex : uint32_t {};
	export_ enum class LightmapAtlasIndex : uint32_t {};
	export_ enum class ReflectionProbeIndex : uint32_t {};

	template <> struct TypeIndex<GIProbe> { using Index = GIProbeIndex; };
	template <> struct TypeIndex<LightmapAtlas> { using Index = LightmapAtlasIndex; };
	template <> struct TypeIndex<ReflectionProbe> { using Index = ReflectionProbeIndex; };

	template <> struct TypedBuffer<Tonemap> { static uint32_t index() { return 0; } };
	template <> struct TypedBuffer<BCS> { static uint32_t index() { return 1; } };
	template <> struct TypedBuffer<Glow> { static uint32_t index() { return 2; } };
	template <> struct TypedBuffer<DofBlur> { static uint32_t index() { return 3; } };

	// a handle to the node of a global illumination probe, the probe in its state reached through ->
	export_ struct refl_ struct_ GIProbeHandle : public GnodeHandle
	{
		GIProbeHandle() {}
		GIProbeHandle(nullptr_t) {}
		inline explicit GIProbeHandle(Gnode self);

		attr_ inline Gnode self() const;
		attr_ inline GIProbe& probe() const;

		inline GIProbe* operator->() const;
		inline GIProbe& operator*() const;
	};

	// a handle to the node of a lightmap atlas, the atlas in its state reached through ->
	export_ struct refl_ struct_ LightmapAtlasHandle : public GnodeHandle
	{
		LightmapAtlasHandle() {}
		LightmapAtlasHandle(nullptr_t) {}
		inline explicit LightmapAtlasHandle(Gnode self);
		inline LightmapAtlasHandle(Scene& scene, LightmapAtlasIndex index);

		attr_ inline Gnode self() const;
		attr_ inline LightmapAtlas& atlas() const;

		inline LightmapAtlas* operator->() const;
		inline LightmapAtlas& operator*() const;
	};
}
