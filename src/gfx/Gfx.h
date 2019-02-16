//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/span.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Light.h>

namespace mud
{
namespace gfx
{
	export_ MUD_GFX_EXPORT func_ void setup_pipeline_minimal(GfxSystem& gfx);

	export_ MUD_GFX_EXPORT meth_ TPool<Node3>&  nodes(Scene& scene);
	export_ MUD_GFX_EXPORT meth_ TPool<Item>&   items(Scene& scene);
	export_ MUD_GFX_EXPORT meth_ TPool<Mime>&   mimes(Scene& scene);
	export_ MUD_GFX_EXPORT meth_ TPool<Light>&  lights(Scene& scene);
	export_ MUD_GFX_EXPORT meth_ TPool<Flare>&	flares(Scene& scene);

	export_ MUD_GFX_EXPORT func_ void update_item_aabb(Item& item);
	export_ MUD_GFX_EXPORT func_ void update_item_lights(Scene& scene, Item& item);

	export_ MUD_GFX_EXPORT func_ Gnode& node(Gnode& parent, Ref object = {}, const vec3& position = vec3(0.f), const quat& rotation = ZeroQuat, const vec3& scale = vec3(1.f));
	export_ MUD_GFX_EXPORT Gnode& node(Gnode& parent, Ref object, const mat4& transform);
	export_ MUD_GFX_EXPORT Gnode& node(Gnode& parent, Ref object, const Transform& transform);
	export_ MUD_GFX_EXPORT Gnode& transform(Gnode& parent, Ref object, const vec3& position, const quat& rotation, const vec3& scale);
	export_ MUD_GFX_EXPORT Gnode& transform(Gnode& parent, Ref object, const vec3& position, const quat& rotation);
	export_ MUD_GFX_EXPORT func_ Item& shape(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
	export_ MUD_GFX_EXPORT void draw(Scene& scene, const mat4& transform, const Shape& shape, const Symbol& symbol, uint32_t flags = 0);
	export_ MUD_GFX_EXPORT func_ void draw(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags = 0);
	export_ MUD_GFX_EXPORT func_ Item& sprite(Gnode& parent, const Image256& image, const vec2& size, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
	export_ MUD_GFX_EXPORT func_ Item& item(Gnode& parent, const Model& model, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0, span<mat4> transforms = {});
	export_ MUD_GFX_EXPORT func_ void prefab(Gnode& parent, const Prefab& prefab, bool transform = true, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0, span<mat4> transforms = {});
	export_ MUD_GFX_EXPORT func_ Item* model(Gnode& parent, const string& name, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
	export_ MUD_GFX_EXPORT func_ Mime& animated(Gnode& parent, Item& item);
	export_ MUD_GFX_EXPORT func_ Flare& flows(Gnode& parent, const Flow& emitter, uint32_t flags = 0, size_t instances = 0);
	export_ MUD_GFX_EXPORT func_ Light& light(Gnode& parent, LightType type, bool shadows, Colour colour, float range = 0.f, float attenuation = 0.5f);
	export_ MUD_GFX_EXPORT func_ Light& sun_light(Gnode& parent, float azimuth, float elevation);
	export_ MUD_GFX_EXPORT func_ void radiance(Gnode& parent, const string& texture, BackgroundMode background);

	using ManualJob = void(*)(Render&, const Pass&);
	using CustomSky = void(*)(Render&);

	export_ MUD_GFX_EXPORT void manual_job(Gnode& parent, PassType pass, ManualJob job);
	export_ MUD_GFX_EXPORT void custom_sky(Gnode& parent, CustomSky func);

	export_ MUD_GFX_EXPORT Light& direct_light_node(Gnode& parent);
	export_ MUD_GFX_EXPORT Light& direct_light_node(Gnode& parent, const quat& rotation);
	export_ MUD_GFX_EXPORT func_ Light& direct_light_node(Gnode& parent, const vec3& direction);

	export_ MUD_GFX_EXPORT func_ Material& unshaded_material(GfxSystem& gfx, cstring name, const Colour& colour);

	export_ MUD_GFX_EXPORT Material& pbr_material(GfxSystem& gfx, cstring name, const MaterialPbr& pbr_block);
	export_ MUD_GFX_EXPORT func_ Material& pbr_material(GfxSystem& gfx, cstring name, const Colour& albedo, float metallic = 0.f, float roughness = 1.f);
}
}
