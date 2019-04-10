$input v_uv0

#include <filter.sh>

#include <pbr/pbr.sh>
#include <pbr/light.sh>
#include <pbr/radiance.sh>

#ifdef FOG
#include <pbr/fog.sh>
#endif

#define s_gposition s_source_0
#define s_gnormal s_source_1
#define s_galbedo s_source_2
#define s_gsurface s_source_3

float to_depth(float device_depth)
{
#if BGFX_SHADER_LANGUAGE_HLSL || BGFX_SHADER_LANGUAGE_PSSL || BGFX_SHADER_LANGUAGE_METAL
	return device_depth;
#else
	return device_depth * 2.0 - 1.0;
#endif
}

vec3 clip_to_world(mat4 inv_view_proj, vec3 clip_position)
{
	vec4 wpos = mul(inv_view_proj, vec4(clip_position, 1.0) );
	return wpos.xyz / wpos.w;
}

vec3 reconstruct_position(vec2 uv, mat4 inv_view_proj, float device_depth)
{
	float depth = to_depth(device_depth);
    
	vec3 clip = vec3(uv * 2.0 - 1.0, depth);
#if BGFX_SHADER_LANGUAGE_HLSL || BGFX_SHADER_LANGUAGE_PSSL || BGFX_SHADER_LANGUAGE_METAL
	clip.y = -clip.y;
#endif
	return clip_to_world(inv_view_proj, clip);
}

void main()
{
    // @todo we can get rid of one buffer by reconstructing position from depth
	//float device_depth = texture2D(s_depth, v_uv0).x
	//vec3 position = reconstruct_position(v_uv0, u_view_proj, device_depth);
    
    Fragment fragment;
    fragment.coord = gl_FragCoord;
    vec4 position = texture2DLod(s_gposition, v_uv0, 0.0);
	fragment.position = position.xyz;
    fragment.coord.z = position.w;
	fragment.normal = texture2DLod(s_gnormal, v_uv0, 0.0).rgb;
	fragment.view = normalize(-fragment.position);
    fragment.depth = -fragment.position.z;

    Material material;
    vec4 surface = texture2DLod(s_gsurface, v_uv0, 0.0).rgba;
	vec4 colour = texture2DLod(s_galbedo, v_uv0, 0.0).rgba;
    material.albedo = colour.rgb;
    material.roughness = surface.x;
	material.metallic = surface.y;
    material.specular = surface.z;
    
	float alpha = 1.0;
    
    vec4 emission = vec4(colour.rgb * colour.a, colour.a);
    
#include "fs_pbr.sh"

#include "fs_out_pbr.sh"
}
