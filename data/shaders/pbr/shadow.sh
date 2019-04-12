#ifndef MUD_SHADER_SHADOW
#define MUD_SHADER_SHADOW

#include <encode.sh>
#include <pbr/light.sh>

#define NO_PCF 0
#define HARD_PCF 1
#define PCF5 2
#define PCF13 3

#if 0 // PCF_LEVEL != HARD_PCF
    SAMPLER2DSHADOW(s_shadow_atlas, 11);
#define samplerShadow sampler2DShadow
#define SHADOW_SAMPLER 1
#else
    SAMPLER2D(s_shadow_atlas, 11);
#define samplerShadow sampler2D
#define SHADOW_SAMPLER 0
#endif

uniform vec4 u_pcf_p0;
#define u_pcf_offset u_pcf_p0.xy
#define u_pcf_radius u_pcf_p0.z

uniform mat4 u_shadow_matrix[MAX_SHADOWS];

uniform vec4 u_shadow_atlas;
#define u_shadow_atlas_size u_shadow_atlas.xy
#define u_shadow_atlas_pixel_size u_shadow_atlas.zw

uniform vec4 u_csm_splits;
uniform vec4 u_csm_p0;
#define u_csm_atlas_pixel_size u_csm_p0.xy

float texture2DCompare(samplerShadow depth, vec2 uv, float compare)
{
#if !SHADOW_SAMPLER
    return step(compare, unpackRgbaToFloat(texture2D(depth, uv)));
    //return step(compare, texture2D(depth, uv).r);
#else
    return shadow2D(depth, vec3(uv, compare));
#endif
}

float texture2DShadowLerp(samplerShadow depth, vec2 size, vec2 uv, float compare)
{
    const vec2 offset = vec2(0.0, 1.0);
    vec2 texelSize = vec2(1.0, 1.0) / size;
    vec2 centroidUV = floor(uv * size + 0.5) / size;
    float lb = texture2DCompare(depth, centroidUV + texelSize * offset.xx, compare);
    float lt = texture2DCompare(depth, centroidUV + texelSize * offset.xy, compare);
    float rb = texture2DCompare(depth, centroidUV + texelSize * offset.yx, compare);
    float rt = texture2DCompare(depth, centroidUV + texelSize * offset.yy, compare);
    vec2 f = fract(uv * size + 0.5);
    float a = mix(lb, lt, f.y);
    float b = mix(rb, rt, f.y);
    float c = mix(a, b, f.x);
    return c;
}

float sample_shadow(samplerShadow shadowmap, vec4 coord, float bias)
{
#if SHADOW_SAMPLER
    return shadow2D(shadowmap, vec3(coord.xy / coord.w, (coord.z - bias) / coord.w));
#else

    vec2 uv = coord.xy / coord.w;

    bool outside = any(greaterThan(uv, vec2_splat(1.0)))
                || any(lessThan   (uv, vec2_splat(0.0)));

    if (outside)
    {
        return 1.0;
    }

    float receiver = (coord.z - bias) / coord.w;
    float occluder = texture2D(shadowmap, uv).r;

    return step(receiver, occluder);
#endif
}

float sample_shadow_hard_pcf(samplerShadow shadowmap, vec4 coord, float bias, vec2 texel_size)
{
    float result = 0.0;
    vec2 offset = u_pcf_offset * texel_size * coord.w;

    result += sample_shadow(shadowmap, coord + vec4(vec2(-1.5, -1.5) * offset, 0.0, 0.0), bias);
    result += sample_shadow(shadowmap, coord + vec4(vec2(-1.5, -0.5) * offset, 0.0, 0.0), bias);
    result += sample_shadow(shadowmap, coord + vec4(vec2(-1.5,  0.5) * offset, 0.0, 0.0), bias);
    result += sample_shadow(shadowmap, coord + vec4(vec2(-1.5,  1.5) * offset, 0.0, 0.0), bias);

    result += sample_shadow(shadowmap, coord + vec4(vec2(-0.5, -1.5) * offset, 0.0, 0.0), bias);
    result += sample_shadow(shadowmap, coord + vec4(vec2(-0.5, -0.5) * offset, 0.0, 0.0), bias);
    result += sample_shadow(shadowmap, coord + vec4(vec2(-0.5,  0.5) * offset, 0.0, 0.0), bias);
    result += sample_shadow(shadowmap, coord + vec4(vec2(-0.5,  1.5) * offset, 0.0, 0.0), bias);

    result += sample_shadow(shadowmap, coord + vec4(vec2(0.5, -1.5) * offset, 0.0, 0.0), bias);
    result += sample_shadow(shadowmap, coord + vec4(vec2(0.5, -0.5) * offset, 0.0, 0.0), bias);
    result += sample_shadow(shadowmap, coord + vec4(vec2(0.5,  0.5) * offset, 0.0, 0.0), bias);
    result += sample_shadow(shadowmap, coord + vec4(vec2(0.5,  1.5) * offset, 0.0, 0.0), bias);

    result += sample_shadow(shadowmap, coord + vec4(vec2(1.5, -1.5) * offset, 0.0, 0.0), bias);
    result += sample_shadow(shadowmap, coord + vec4(vec2(1.5, -0.5) * offset, 0.0, 0.0), bias);
    result += sample_shadow(shadowmap, coord + vec4(vec2(1.5,  0.5) * offset, 0.0, 0.0), bias);
    result += sample_shadow(shadowmap, coord + vec4(vec2(1.5,  1.5) * offset, 0.0, 0.0), bias);

    return result / 16.0;
}

float sample_shadow_pcf(samplerShadow shadowmap, vec4 coord, float bias, vec2 texel_size)
{
	vec2 pos = coord.xy / coord.w;
    float depth = (coord.z - bias) / coord.w;

#if PCF_LEVEL == NO_PCF
#if SHADOW_SAMPLER
	return shadow2D(shadowmap, vec3(pos, depth));
#else
    return step(depth, texture2D(shadowmap, pos).r);
#endif
    //return sample_shadow(shadowmap, coord, bias);
#elif PCF_LEVEL == HARD_PCF
    return sample_shadow_hard_pcf(shadowmap, coord, bias, texel_size);
#elif PCF_LEVEL == PCF5
	float avg = shadow2D(shadowmap, vec3(pos, depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(texel_size.x, 0.0), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(-texel_size.x, 0.0), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(0.0,  texel_size.y), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(0.0, -texel_size.y), depth));
	return avg * (1.0 / 5.0);
#elif PCF_LEVEL == PCF13
	float avg = shadow2D(shadowmap, vec3(pos, depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(texel_size.x, 0.0), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(-texel_size.x, 0.0), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(0.0,  texel_size.y), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(0.0, -texel_size.y), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(texel_size.x,  texel_size.y), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(-texel_size.x,  texel_size.y), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(texel_size.x, -texel_size.y), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(-texel_size.x, -texel_size.y), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(texel_size.x * 2.0, 0.0), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(-texel_size.x * 2.0, 0.0), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(0.0,  texel_size.y * 2.0), depth));
	avg += shadow2D(shadowmap, vec3(pos + vec2(0.0, -texel_size.y * 2.0), depth));
	return avg * (1.0 / 13.0);
#endif
}

float sample_cascade(CSMShadow csm, int index, vec3 frag, float bias, vec2 texel_size)
{
    int matindex = csm.matrices[index];
    vec4 coord = mul(u_shadow_matrix[matindex], vec4(frag, 1.0));
    return sample_shadow_pcf(s_shadow_atlas, coord, bias, texel_size);
}

vec3 debug_sample_cascade(CSMShadow csm, int index, vec3 frag, float bias, vec2 texel_size)
{
    int matindex = csm.matrices[index];
    vec4 coord = mul(u_shadow_matrix[matindex], vec4(frag, 1.0));
	vec2 pos = coord.xy / coord.w;
    float depth = (coord.z - bias) / coord.w;
#if !SHADOW_SAMPLER
    return vec3(pos, depth) * vec3_splat(sample_shadow(s_shadow_atlas, vec4(pos, depth, 0.0), 0.0));
#else
    return vec3(pos, depth) * vec3_splat(shadow2D(s_shadow_atlas, vec3(pos, depth)));
#endif
}

float shadow_csm(CSMShadow csm, vec3 frag, float w)
{
    // alternative / todo : transform to all shadowmap spaces in the vertex shader and select here

    vec4 comparison = vec4(greaterThan(vec4_splat(w), csm.splits));
    float findex = dot(vec4(float(csm.count > 0), float(csm.count > 1), float(csm.count > 2), float(csm.count > 3)), comparison);
    int cascade = int(min(findex, float(csm.count) - 1.0));

    float shadow_bias = 0.0;
    float shadowmap = sample_cascade(csm, cascade, frag, shadow_bias, u_csm_atlas_pixel_size);

#ifdef CSM_BLEND
    if(cascade > 0) {
    
        float amount = smoothstep(1.0 / csm.splits[cascade - 1], 1.0 / csm.splits[cascade], 1.0 / w);
        float blend = sample_cascade(cascade - 1, frag, shadow_bias, u_csm_atlas_pixel_size);

        shadowmap = mix(blend, shadowmap, amount);
    }
#endif

    return saturate(shadowmap);
}

// refs: https://gist.github.com/tschw/da10c43c467ce8afd0c4
//       https://github.com/mrdoob/three.js/pull/7153

vec2 cubeUV(vec3 v, float texelSizeY)
{
    vec3 absV = abs(v);
    float scaleToCube = 1.0 / max(absV.x, max(absV.y, absV.z));
    absV *= scaleToCube;
    v *= scaleToCube * (1.0 - 2.0 * texelSizeY);
    vec2 planar = v.xy;
    float almostATexel = 1.5 * texelSizeY;
    float almostOne = 1.0 - almostATexel;
    if (absV.z >= almostOne) {
        if (v.z > 0.0)
            planar.x = 4.0 - v.x;
    } else if (absV.x >= almostOne) {
        float signX = sign(v.x);
        planar.x = v.z * signX + 2.0 * signX;
    } else if (absV.y >= almostOne) {
        float signY = sign(v.y);
        planar.x = v.x + 2.0 * signY + 2.0;
        planar.y = v.z * signY - 2.0;
    }
    vec2 uv = vec2(0.125, 0.25) * planar + vec2(0.375, 0.75);
    
    // this function calculates coordinates from bottom-left (as it's simpler from NDC cube dir in [-1,+1]), so flip y at the end
    uv.y = 1.0 - uv.y;

    return uv;
}

vec2 atlasCubeUV(vec2 slot, vec2 subdiv, vec3 v, float texelSizeY)
{
    vec2 side = cubeUV(v, texelSizeY);
    vec2 uv = slot + side * subdiv * vec2(4.0, 2.0);
#if !BGFX_SHADER_LANGUAGE_HLSL
    uv.y = 1.0 - uv.y;
#endif
    return uv;
}

float shadow_point(samplerShadow shadowmap, vec2 slot, vec2 subdiv, float bias, vec3 coord, float near, float far)
{
    vec2 texelSize = vec2(1.0, 1.0) / u_shadow_atlas_size;
    float depth = (length(coord) - near) / (far - near);
    depth -= bias;
    vec3 dir = normalize(coord);
#if PCF_LEVEL == HARD_PCF
        float radius = 15.0;
        vec2 deviate = vec2(- 1, 1) * radius * texelSize.y;
        return (
            texture2DCompare(shadowmap, atlasCubeUV(slot, subdiv, dir + deviate.xyy, texelSize.y), depth) +
            texture2DCompare(shadowmap, atlasCubeUV(slot, subdiv, dir + deviate.yyy, texelSize.y), depth) +
            texture2DCompare(shadowmap, atlasCubeUV(slot, subdiv, dir + deviate.xyx, texelSize.y), depth) +
            texture2DCompare(shadowmap, atlasCubeUV(slot, subdiv, dir + deviate.yyx, texelSize.y), depth) +
            texture2DCompare(shadowmap, atlasCubeUV(slot, subdiv, dir, texelSize.y), depth) +
            texture2DCompare(shadowmap, atlasCubeUV(slot, subdiv, dir + deviate.xxy, texelSize.y), depth) +
            texture2DCompare(shadowmap, atlasCubeUV(slot, subdiv, dir + deviate.yxy, texelSize.y), depth) +
            texture2DCompare(shadowmap, atlasCubeUV(slot, subdiv, dir + deviate.xxx, texelSize.y), depth) +
            texture2DCompare(shadowmap, atlasCubeUV(slot, subdiv, dir + deviate.yxx, texelSize.y), depth)
       ) * (1.0 / 9.0);
#elif PCF_LEVEL == NO_PCF
        return texture2DCompare(shadowmap, atlasCubeUV(slot, subdiv, dir, texelSize.y), depth);
#else
        // not implemented
        return texture2DCompare(shadowmap, atlasCubeUV(slot, subdiv, dir, texelSize.y), depth);
#endif
}

float shadow_point(Shadow shadow, vec3 frag)
{
    vec4 coord = mul(u_shadow_matrix[shadow.index], vec4(frag, 1.0));
    return shadow_point(s_shadow_atlas, shadow.atlas_slot, shadow.atlas_subdiv, shadow.bias, coord.xyz, 0.01, shadow.range);
    
#ifdef USE_CONTACT_SHADOWS
    if (shadowmap > 0.01 && shadow.contact > 0.0)
    {
        float contact_shadow = contact_shadow_compute(vertex, normalize(l), min(light_length, shadow.contact));
        shadowmap = min(shadowmap, contact_shadow);

    }
#endif
}

float shadow_spot(Shadow shadow, vec3 frag)
{
    return 1.0;
}

#endif
