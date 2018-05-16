#ifndef MUD_SHADER_SHADOW
#define MUD_SHADER_SHADOW

#include <pbr/light.sh>

#if CSM_PCF_LEVEL > 0
#define SHADOW_SAMPLER
#endif

SAMPLER2DSHADOW(s_shadow_atlas, 5);

#ifdef CSM_SHADOW

uniform vec4 u_csm_params;
#define u_csm_atlas_pixel_size u_csm_params.xy
#define u_csm_pcf_offset u_csm_params.zw

#ifdef SHADOW_SAMPLER
    SAMPLER2DSHADOW(s_csm_atlas, 6);
#define samplerShadow sampler2DShadow
#else
    SAMPLER2D(s_csm_atlas, 6);
#define samplerShadow sampler2D
#endif

float hardShadow(samplerShadow shadow, vec4 shadow_coord, float bias)
{
#ifdef SHADOW_SAMPLER
	return shadow2D(shadow, vec3(shadow_coord.xy / shadow_coord.w, (shadow_coord.z - bias) / shadow_coord.w));
#else

	vec2 texCoord = shadow_coord.xy / shadow_coord.w;
    
	bool outside = any(greaterThan(texCoord, vec2_splat(1.0)))
				|| any(lessThan   (texCoord, vec2_splat(0.0)));

	if (outside)
	{
		return 1.0;
	}

	float receiver = (shadow_coord.z - bias) / shadow_coord.w;
	float occluder = texture2D(shadow, texCoord).r;

	return step(receiver, occluder);
#endif
}

float PCF(samplerShadow shadow, vec4 shadow_coord, float bias, vec2 texel_size)
{
	float result = 0.0;
	vec2 offset = u_csm_pcf_offset * texel_size * shadow_coord.w;
    
    result += hardShadow(shadow, shadow_coord + vec4(vec2(-1.5, -1.5) * offset, 0.0, 0.0), bias);
	result += hardShadow(shadow, shadow_coord + vec4(vec2(-1.5, -0.5) * offset, 0.0, 0.0), bias);
	result += hardShadow(shadow, shadow_coord + vec4(vec2(-1.5,  0.5) * offset, 0.0, 0.0), bias);
	result += hardShadow(shadow, shadow_coord + vec4(vec2(-1.5,  1.5) * offset, 0.0, 0.0), bias);

	result += hardShadow(shadow, shadow_coord + vec4(vec2(-0.5, -1.5) * offset, 0.0, 0.0), bias);
	result += hardShadow(shadow, shadow_coord + vec4(vec2(-0.5, -0.5) * offset, 0.0, 0.0), bias);
	result += hardShadow(shadow, shadow_coord + vec4(vec2(-0.5,  0.5) * offset, 0.0, 0.0), bias);
	result += hardShadow(shadow, shadow_coord + vec4(vec2(-0.5,  1.5) * offset, 0.0, 0.0), bias);

	result += hardShadow(shadow, shadow_coord + vec4(vec2(0.5, -1.5) * offset, 0.0, 0.0), bias);
	result += hardShadow(shadow, shadow_coord + vec4(vec2(0.5, -0.5) * offset, 0.0, 0.0), bias);
	result += hardShadow(shadow, shadow_coord + vec4(vec2(0.5,  0.5) * offset, 0.0, 0.0), bias);
	result += hardShadow(shadow, shadow_coord + vec4(vec2(0.5,  1.5) * offset, 0.0, 0.0), bias);

	result += hardShadow(shadow, shadow_coord + vec4(vec2(1.5, -1.5) * offset, 0.0, 0.0), bias);
	result += hardShadow(shadow, shadow_coord + vec4(vec2(1.5, -0.5) * offset, 0.0, 0.0), bias);
	result += hardShadow(shadow, shadow_coord + vec4(vec2(1.5,  0.5) * offset, 0.0, 0.0), bias);
	result += hardShadow(shadow, shadow_coord + vec4(vec2(1.5,  1.5) * offset, 0.0, 0.0), bias);

	return result / 16.0;
}

float sample_shadow(samplerShadow shadow, vec4 shadow_coord, float bias, vec2 texel_size)
{
	vec2 pos = shadow_coord.xy / shadow_coord.w;
    float depth = (shadow_coord.z - bias / shadow_coord.w);
    
#if CSM_PCF_LEVEL == 0
    return PCF(shadow, shadow_coord, bias, texel_size);
	//return shadow2D(shadow, vec3(pos, depth));
#elif CSM_PCF_LEVEL == 1
	float avg = shadow2D(shadow, vec3(pos, depth));
	avg += shadow2D(shadow, vec3(pos + vec2( texel_size.x, 0.0), depth));
	avg += shadow2D(shadow, vec3(pos + vec2(-texel_size.x, 0.0), depth));
	avg += shadow2D(shadow, vec3(pos + vec2(0.0,  texel_size.y), depth));
	avg += shadow2D(shadow, vec3(pos + vec2(0.0, -texel_size.y), depth));
	return avg * (1.0 / 5.0);
#elif CSM_PCF_LEVEL == 2
	float avg = shadow2D(shadow, vec3(pos, depth));
	avg += shadow2D(shadow, vec3(pos + vec2( texel_size.x, 0.0), depth));
	avg += shadow2D(shadow, vec3(pos + vec2(-texel_size.x, 0.0), depth));
	avg += shadow2D(shadow, vec3(pos + vec2(0.0,  texel_size.y), depth));
	avg += shadow2D(shadow, vec3(pos + vec2(0.0, -texel_size.y), depth));
	avg += shadow2D(shadow, vec3(pos + vec2( texel_size.x,  texel_size.y), depth));
	avg += shadow2D(shadow, vec3(pos + vec2(-texel_size.x,  texel_size.y), depth));
	avg += shadow2D(shadow, vec3(pos + vec2( texel_size.x, -texel_size.y), depth));
	avg += shadow2D(shadow, vec3(pos + vec2(-texel_size.x, -texel_size.y), depth));
	avg += shadow2D(shadow, vec3(pos + vec2( texel_size.x * 2.0, 0.0), depth));
	avg += shadow2D(shadow, vec3(pos + vec2(-texel_size.x * 2.0, 0.0), depth));
	avg += shadow2D(shadow, vec3(pos + vec2(0.0,  texel_size.y * 2.0), depth));
	avg += shadow2D(shadow, vec3(pos + vec2(0.0, -texel_size.y * 2.0), depth));
	return avg * (1.0 / 13.0);
//#else
	//return shadow2D(shadow, vec3(pos, depth));
#endif
}

float sample_cascade(int cascade_index, vec3 vertex, float bias, vec2 texel_size)
{
    vec4 shadow_coord = mul(u_csm_matrix[cascade_index], vec4(vertex, 1.0));
    return sample_shadow(s_csm_atlas, shadow_coord, bias, u_csm_atlas_pixel_size);
}

vec3 csm_shadow(Light light, vec3 vertex, vec3 normal, float frag_w)
{
    // alternative / todo : transform to all shadow spaces in the vertex shader and select here
#if CSM_NUM_CASCADES > 1
    vec4 comparison = vec4(greaterThan(vec4_splat(frag_w), u_csm_splits));
    float findex = dot(vec4(float(CSM_NUM_CASCADES > 0), float(CSM_NUM_CASCADES > 1), float(CSM_NUM_CASCADES > 2), float(CSM_NUM_CASCADES > 3)), comparison);
    int cascade_index = int(min(findex, float(CSM_NUM_CASCADES) - 1.0));
#else
    int cascade_index = 0;
#endif

    float shadow_bias = 0.0;

    float shadow = sample_cascade(cascade_index, vertex, shadow_bias, u_csm_atlas_pixel_size);

#ifdef CSM_BLEND
    if(cascade_index > 0) {
    
        float amount = smoothstep(1.0 / u_csm_splits[cascade_index - 1], 1.0 / u_csm_splits[cascade_index], 1.0 / frag_w);
        float blend = sample_cascade(cascade_index - 1, vertex, shadow_bias, u_csm_atlas_pixel_size);

        shadow = mix(blend, shadow, amount);
    }
#endif

    return mix(light.shadow_color, vec3_splat(1.0), saturate(shadow));
}
#endif

#endif
