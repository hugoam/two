//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Array.h>
#endif
#include <gfx/Forward.h>
#include <gfx/Node3.h>
#include <gfx/Light.h>

#ifndef MUD_CPP_20
#include <string>
#include <functional>
#endif

namespace mud
{
	using string = std::string;

namespace gfx
{
	export_ MUD_GFX_EXPORT func_ void update_item_lights(Item& item);
	export_ MUD_GFX_EXPORT func_ void update_item_aabb(Item& item);

	export_ MUD_GFX_EXPORT func_ Gnode& node(Gnode& parent, Ref object = {}, const vec3& position = Zero3, const quat& rotation = ZeroQuat, const vec3& scale = Unit3);
	export_ MUD_GFX_EXPORT Gnode& node(Gnode& parent, Ref object, const mat4& transform);
	export_ MUD_GFX_EXPORT Gnode& node(Gnode& parent, Ref object, const Transform& transform);
	export_ MUD_GFX_EXPORT Gnode& transform(Gnode& parent, Ref object, const vec3& position, const quat& rotation, const vec3& scale);
	export_ MUD_GFX_EXPORT Gnode& transform(Gnode& parent, Ref object, const vec3& position, const quat& rotation);
	export_ MUD_GFX_EXPORT func_ Item& shape(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
	export_ MUD_GFX_EXPORT void draw(Scene& scene, const mat4& transform, const Shape& shape, const Symbol& symbol, uint32_t flags = 0);
	export_ MUD_GFX_EXPORT func_ void draw(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags = 0);
	export_ MUD_GFX_EXPORT func_ Item& sprite(Gnode& parent, const Image256& image, const vec2& size, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
	export_ MUD_GFX_EXPORT func_ Item& item(Gnode& parent, const Model& model, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0, array<mat4> transforms = {});
	export_ MUD_GFX_EXPORT func_ void prefab(Gnode& parent, const Prefab& prefab, bool transform = true, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0, array<mat4> transforms = {});
	export_ MUD_GFX_EXPORT func_ Item* model(Gnode& parent, const string& name, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
	export_ MUD_GFX_EXPORT func_ Animated& animated(Gnode& parent, Item& item);
	export_ MUD_GFX_EXPORT func_ Particles& particles(Gnode& parent, const ParticleGenerator& emitter, uint32_t flags = 0, size_t instances = 0);
	export_ MUD_GFX_EXPORT func_ Light& light(Gnode& parent, LightType type, bool shadows, Colour colour, float range = 0.f, float attenuation = 0.5f);
	export_ MUD_GFX_EXPORT func_ Light& sun_light(Gnode& parent, float azimuth, float elevation);
	export_ MUD_GFX_EXPORT func_ void radiance(Gnode& parent, const string& texture, BackgroundMode background);
	export_ MUD_GFX_EXPORT void manual_job(Gnode& parent, PassType pass, std::function<void(const Pass&)> job);
	export_ MUD_GFX_EXPORT void custom_sky(Gnode& parent, std::function<void(Render&)> func);

	export_ MUD_GFX_EXPORT Light& direct_light_node(Gnode& parent);
	export_ MUD_GFX_EXPORT Light& direct_light_node(Gnode& parent, const quat& rotation);
	export_ MUD_GFX_EXPORT Light& direct_light_node(Gnode& parent, const vec3& direction);

	export_ MUD_GFX_EXPORT Material& pbr_material(GfxSystem& gfx, cstring name, const PbrMaterialBlock& pbr_block);
	export_ MUD_GFX_EXPORT Material& pbr_material(GfxSystem& gfx, cstring name, const Colour& albedo, float metallic = 0.f, float roughness = 1.f);
}
}
