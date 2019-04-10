#ifndef MUD_SHADER_SPHERICAL
#define MUD_SHADER_SPHERICAL

#include <common.sh>

CONST(vec2) inv_atan = vec2(0.1591, 0.3183);
vec2 sphericalUV(vec3 v)
{
    vec2 uv = 0.5 + vec2(atan2(v.z, v.x), asin(v.y)) * inv_atan;
    uv.y = 1.0 - uv.y; // spherical uvs are sampled from bottom left
    return uv;
}

// reference: http://paulbourke.net/miscellaneous/cubemaps/
vec3 invertedSphericalUV(vec2 uv)
{
    uv.y = 1.0 - uv.y; // spherical uvs are sampled from bottom left
	float theta = (uv.x * 2.0 - 1.0) * PI;
	float phi = (uv.y * 2.0 - 1.0) * PI / 2.0; 
    //float phi = asin(uv.y); // for spherical vertical distortion

	return vec3(cos(phi) * cos(theta), sin(phi), cos(phi) * sin(theta));
}

vec4 textureSpherical2D(sampler2D tex, vec3 dir, float level)
{
	vec2 uv = sphericalUV(dir);
	return texture2DLod(tex, uv, level);
}

vec4 textureSpherical3D(sampler3D tex, vec3 dir, float level)
{
	vec2 uv = sphericalUV(dir);
	return texture3D(tex, vec3(uv, level));
}

#if BGFX_SHADER_LANGUAGE_GLSL > 120
vec4 textureSpherical2DArray(sampler2DArray tex, vec3 dir, float level)
{
	vec2 uv = sphericalUV(dir);
	return texture2DArray(tex, vec3(uv, level));
}
#endif

#endif
