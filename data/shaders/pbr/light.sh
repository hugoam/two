#ifndef MUD_SHADER_LIGHT
#define MUD_SHADER_LIGHT

#include <common.sh>
#include <convert.sh>
#include <pbr/pbr.sh>
#include <gpu/light.sh>

#ifndef ZONES_TEXTURE
uniform vec4 u_light_counts;
uniform vec4 u_light_indices[MAX_LIGHTS];
#endif

#define LIGHT_DIRECT 0
#define LIGHT_POINT 1
#define LIGHT_SPOT 2

float omni_attenuation(vec3 l, float range, float attenuation_factor, float lower_bound)
{
	float normalized_distance = length(l) / range;
    float attenuation = pow(max(1.0 - normalized_distance, lower_bound), attenuation_factor);
	return attenuation;
}

float spot_attenuation(vec3 l, vec3 spot_direction, float range, float attenuation_factor, float spot_attenuation, float spot_cutoff)
{
	float attenuation = omni_attenuation(l, range, attenuation_factor, 0.001);
	float scos = max(dot(normalize(l), -spot_direction), spot_cutoff);
	float spot_rim = (1.0 - scos) / (1.0 - spot_cutoff);
	return attenuation * (1.0 - pow(max(spot_rim, 0.001), spot_attenuation));
}

float omni_attenuation(vec3 l, Light light)
{
    return omni_attenuation(l, light.range, light.attenuation, 0.0);
}

float spot_attenuation(vec3 l, Light light)
{
    return spot_attenuation(l, light.direction, light.range, light.attenuation, light.spot_attenuation, light.spot_cutoff);
}

#include "light_brdf.sh"
#include "shadow.sh"

void apply_lights(Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular)
{
	for(int i = 0; i < int(u_light_counts[LIGHT_POINT]); i++)
	{
        Light light = read_light(int(u_light_indices[i][LIGHT_POINT]));
        vec3 l = light.position - fragment.position;
        float a = omni_attenuation(l, light);
        //a *= light.shadows ? shadow_point(light, light.shadow, fragment.position) : 1.0;
        light_brdf(light, l, fragment, material, a, diffuse, specular);
	}

	for(int j = 0; j < int(u_light_counts[LIGHT_SPOT]); j++)
	{
        Light light = read_light(int(u_light_indices[j][LIGHT_SPOT]));
        vec3 l = light.position - fragment.position;
        float a = spot_attenuation(l, light);
        //a *= light.shadows ? shadow_spot(light, light.shadow, fragment.position) : 1.0;
        light_brdf(light, l, fragment, material, a, diffuse, specular);
	}
}

#ifdef CLUSTERED
#include "light_cluster.sh"

void apply_cluster_lights(Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular)
{
    uint cluster_index = fragment_cluster_index(fragment.coord.xyz);
    LightCluster cluster = get_light_cluster(cluster_index);

    uint index = cluster.record_offset;

    for(uint last_point = index + cluster.point_count; index < last_point; index++)
    {
        Light light = read_cluster_light(index);
        vec3 l = light.position - fragment.position;
        float a = omni_attenuation(l, light);
        //a *= light.shadows ? shadow_point(light, light.shadow, fragment.position) : 1.0;
        light_brdf(light, l, fragment, material, a, diffuse, specular);
    }

    for(uint last_spot = index + cluster.spot_count; index < last_spot; index++)
    {
        Light light = read_cluster_light(index);
        vec3 l = light.position - fragment.position;
        float a = spot_attenuation(l, light);
        //a *= light.shadows ? shadow_spot(light, light.shadow, fragment.position) : 1.0;
        light_brdf(light, l, fragment, material, a, diffuse, specular);
    }
}
#endif

#ifdef DIRECT_LIGHT
void direct_light(Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular)
{
    Light light = read_light(0);
    
#ifdef CSM_SHADOW
    float factor = shadow_csm(light, light.shadow, fragment.position, fragment.depth);
#else
	float factor = 1.0;
#endif

	light_brdf(light, -light.direction, fragment, material, factor, diffuse, specular);
}
#endif

#endif
