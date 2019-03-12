#ifndef MUD_SHADER_RADIANCE
#define MUD_SHADER_RADIANCE

#include <spherical.sh>
#include <gpu/zone.sh>

//uniform vec4 u_pbr_globals;
//#define u_roughness_levels u_pbr_globals.x

#ifdef RADIANCE_ENVMAP
#define RADIANCE_MAX_LOD 7.0

#ifdef RADIANCE_ARRAY
SAMPLER2DARRAY(s_radiance, 10);
#else
SAMPLER2D(s_radiance, 10);
#endif

vec3 radiance_reflection(Zone zone, vec3 view, vec3 normal, float roughness)
{
    float roughness_level = roughness * RADIANCE_MAX_LOD;
	vec3 reflection = reflect(-view, normal);
	reflection = normalize(mul(u_invView, vec4(reflection, 0.0)).xyz);
#ifdef RADIANCE_ARRAY
	vec3 tex_radiance = textureSpherical2DArray(s_radiance, reflection, roughness_level).rgb;
#else
	vec3 tex_radiance = textureSpherical2D(s_radiance, reflection, roughness_level).rgb;
#endif
    return tex_radiance * zone.radiance_color * zone.radiance_energy;
}

vec3 radiance_ambient(Zone zone, vec3 normal)
{
	vec3 ambient_dir = normalize(mul(u_invView, vec4(normal, 0.0)).xyz);
#ifdef RADIANCE_ARRAY
	vec3 tex_ambient = textureSpherical2DArray(s_radiance, ambient_dir, RADIANCE_MAX_LOD).rgb;
#else
	vec3 tex_ambient = textureSpherical2D(s_radiance, ambient_dir, RADIANCE_MAX_LOD).rgb;
#endif
	return tex_ambient * zone.radiance_color * zone.ambient;
}
#endif

#endif
