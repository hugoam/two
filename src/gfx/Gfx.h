//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <gfx/Generated/Forward.h>
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
	MUD_GFX_EXPORT _func_ Gnode& node(Gnode& parent, Ref object = {}, const vec3& position = Zero3, const quat& rotation = ZeroQuat, const vec3& scale = Unit3);
	MUD_GFX_EXPORT _func_ Gnode& node(Gnode& parent, Ref object, const Transform& transform);
	MUD_GFX_EXPORT _func_ Gnode& transform(Gnode& parent, Ref object, const vec3& position, const quat& rotation, const vec3& scale);
	MUD_GFX_EXPORT _func_ Gnode& transform(Gnode& parent, Ref object, const vec3& position, const quat& rotation);
	MUD_GFX_EXPORT _func_ Item& node_model(Gnode& parent, const Model& model, const vec3& position, const quat& rotation = ZeroQuat, const vec3& scale = Unit3);
	MUD_GFX_EXPORT _func_ Item& node_shape(Gnode& parent, const Shape& shape, const Symbol& symbol, const vec3& position, const quat& rotation = ZeroQuat, const vec3& scale = Unit3);
	MUD_GFX_EXPORT _func_ Item& shape(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
	MUD_GFX_EXPORT _func_ void draw(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags = 0);
	MUD_GFX_EXPORT _func_ Item& sprite(Gnode& parent, const Image256& image, const vec2& size, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
	MUD_GFX_EXPORT _func_ Item& item(Gnode& parent, const Model& model, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
	MUD_GFX_EXPORT _func_ Item* model(Gnode& parent, const string& name, uint32_t flags = 0, Material* material = nullptr, size_t instances = 0);
	MUD_GFX_EXPORT _func_ Animated& animated(Gnode& parent, Item& item);
	MUD_GFX_EXPORT _func_ Particles& particles(Gnode& parent, const ParticleGenerator& emitter, uint32_t flags = 0, size_t instances = 0);
	MUD_GFX_EXPORT _func_ Light& light(Gnode& parent, LightType type, bool shadows, Colour colour, float range = 0.f, float attenuation = 0.5f);
	MUD_GFX_EXPORT _func_ Light& sun_light(Gnode& parent, float azimuth, float elevation);
	//MUD_GFX_EXPORT _func_ GIProbe& gi_probe(Gnode& parent);
	MUD_GFX_EXPORT _func_ void radiance(Gnode& parent, const string& texture, BackgroundMode background);
	MUD_GFX_EXPORT void manual_job(Gnode& parent, PassType pass, std::function<void(const Pass&)> job);
	MUD_GFX_EXPORT void custom_sky(Gnode& parent, std::function<void(Render&)> func);

	MUD_GFX_EXPORT Light& directional_light_node(Gnode& parent);
	MUD_GFX_EXPORT Light& directional_light_node(Gnode& parent, const quat& rotation);
	MUD_GFX_EXPORT Light& directional_light_node(Gnode& parent, const vec3& direction);
}
}
