#ifndef MUD_SHADER_RADIANCE
#define MUD_SHADER_RADIANCE

#include <spherical.sh>

uniform vec4 u_radiance_color_energy;
#define u_radiance_color u_radiance_color_energy.rgb
#define u_radiance_energy u_radiance_color_energy.w

uniform vec4 u_ambient_params;
#define u_ambient u_ambient_params.x

uniform vec4 u_pbr_globals;
#define u_roughness_levels u_pbr_globals.x

#ifdef RADIANCE_ENVMAP
#define RADIANCE_MAX_LOD 7.0

#ifdef RADIANCE_ARRAY
SAMPLER2DARRAY(s_radiance_map, 8);
#else
SAMPLER2D(s_radiance_map, 8);
#endif

vec3 radiance_reflection(vec3 view, vec3 normal, float roughness)
{
    float roughness_level = roughness * RADIANCE_MAX_LOD;
	vec3 reflection = reflect(-view, normal);
	reflection = normalize(mul(u_invView, vec4(reflection, 0.0)).xyz);
#ifdef RADIANCE_ARRAY
	return textureSpherical2DArray(s_radiance_map, reflection, roughness_level).rgb * u_radiance_color * u_radiance_energy;
#else
	return textureSpherical2D(s_radiance_map, reflection, roughness_level).rgb * u_radiance_color * u_radiance_energy;
#endif
}

vec3 radiance_ambient(vec3 normal)
{
	vec3 ambient_dir = normalize(mul(u_invView, vec4(normal, 0.0)).xyz);
#ifdef RADIANCE_ARRAY
	vec3 tex_ambient = textureSpherical2DArray(s_radiance_map, ambient_dir, RADIANCE_MAX_LOD).rgb * u_radiance_color;
#else
	vec3 tex_ambient = textureSpherical2D(s_radiance_map, ambient_dir, RADIANCE_MAX_LOD).rgb * u_radiance_color;
#endif
	return tex_ambient * u_ambient;
}
#endif

#endif
