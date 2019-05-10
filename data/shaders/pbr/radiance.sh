#ifndef MUD_SHADER_RADIANCE
#define MUD_SHADER_RADIANCE

#include <spherical.sh>
#include <gpu/zone.sh>

#define RADIANCE_MAX_LOD 7.0

#ifdef RADIANCE_ENVMAP

#ifdef RADIANCE_CUBE
SAMPLERCUBE(s_radiance, 10);
#else
SAMPLER2D(s_radiance, 10);
#endif

vec3 ibl_refract(vec3 view, vec3 normal, float refraction, float level)
{
	vec3 dir = refract(-view, normal, refraction);
	dir = normalize(mul(u_invView, vec4(dir, 0.0)).xyz);
#ifdef RADIANCE_CUBE
	vec3 rad = textureCubeLod(s_radiance, vec3(-dir.x, dir.y, dir.z), level).rgb;
#else
	vec3 rad = textureSpherical2D(s_radiance, dir, level).rgb;
#endif
    return rad;
}

vec3 ibl_reflect(vec3 view, vec3 normal, float level)
{
	vec3 dir = reflect(-view, normal);
	dir = normalize(mul(u_invView, vec4(dir, 0.0)).xyz);
#ifdef RADIANCE_CUBE
	vec3 rad = textureCubeLod(s_radiance, vec3(-dir.x, dir.y, dir.z), level).rgb;
#else
	vec3 rad = textureSpherical2D(s_radiance, dir, level).rgb;
#endif
    return rad;
}

vec3 ibl_reflect0(vec3 view, vec3 normal)
{
	vec3 dir = reflect(-view, normal);
	dir = normalize(mul(u_invView, vec4(dir, 0.0)).xyz);
#ifdef RADIANCE_CUBE
	vec3 rad = textureCube(s_radiance, vec3(-dir.x, dir.y, dir.z)).rgb;
#else
	vec3 rad = textureSpherical2D(s_radiance, dir, 0.0).rgb;
#endif
    return rad;
}

vec3 ibl_diffuse(vec3 normal)
{
    // @todo it seems wrong that last level is too uniform, look into how those are generated
    float level = RADIANCE_MAX_LOD - 3.0;
	vec3 dir = normalize(mul(u_invView, vec4(normal, 0.0)).xyz);
#ifdef RADIANCE_CUBE
	vec3 amb = textureCubeLod(s_radiance, vec3(-dir.x, dir.y, dir.z), level).rgb;
#else
	vec3 amb = textureSpherical2D(s_radiance, dir, level).rgb;
#endif
	return amb;
}
#endif

#endif
