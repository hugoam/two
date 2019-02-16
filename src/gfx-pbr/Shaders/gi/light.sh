#ifndef MUD_SHADER_GI_LIGHT
#define MUD_SHADER_GI_LIGHT

#include <common.sh>
#include <pbr/pbr.sh>
#include <pbr/light.sh>
#include <pbr/shadow.sh>
#include <gi/gi.sh>

float attenuate(const float dist)
{
	return 1.0 / (dist * dist);
}

#if 0
float attenuate(float dist, float constant, float linear, float quadratic)
{
    return 1.0 / (constant * 1.0)
         + 1.0 / (linear * dist)
         + 1.0 / (quadratic * dist * dist);
}
#endif

vec3 accumulate_light(vec3 voxel_position, vec3 voxel_color, vec3 voxel_normal, int light_index, int light_type)
{
    Light light = preread_light(light_index, light_type);
    
    vec3 lp = light.position - voxel_position;
    
    float visibility;
    vec3 l;
    if (light.type == LIGHT_DIRECT) { l = -light.direction; visibility = 1.0; }
    else { l = normalize(lp); visibility = attenuate(length(lp)); }

    float dotNL = max(dot(voxel_normal, l), 0.0);
    if (dotNL == 0.0) return vec3_splat(0.0);

#ifdef SHADOWS
    //if (light.shadow == 1)
    //{
    //    vec4 light_position = u_LVP * vec4(voxel_position, 1.0);
    //    vec3 lPos = light_position.xyz / light_position.w;
    //    // if (light_position.w > 0.0)
    //    if (texture(s_shadowmap, lPos.xy).r < lPos.z - u_shadow_bias) visibility = 0.0;
    //    // visibility = shadowTest(shadowMap, lPos, u_shadow_bias, shadowmapSize);
    //}
    //else if (light.shadow == 2)
    //{
    //    visibility *= float(texture(u_shadowmap_cube, -l).r + u_shadow_bias > lpToDepth(lp, u_light_proj));
    //}
#endif

    if (light.type == LIGHT_SPOT)
    {
        float spot_effect = dot(-light.direction, l);
        if (spot_effect < light.spot_cutoff)
        {
            visibility *= smoothstep(light.spot_cutoff, light.spot_inner, spot_effect);
        }
    }

    return voxel_color * visibility * light.energy * dotNL;
}

vec3 compute_voxel_lights(vec3 voxel_position, vec3 voxel_color, vec3 voxel_normal)
{
    vec3 diffuse = vec3_splat(0.0);
    
#ifdef DIRECT_LIGHT
    diffuse += accumulate_light(voxel_position, voxel_color, voxel_normal, 0, LIGHT_DIRECT);
#ifdef CSM_SHADOW
    diffuse *= sample_cascade(0, voxel_position, 0.0, u_csm_atlas_pixel_size);
    //diffuse = debug_sample_cascade(0, voxel_position, 0.0, u_csm_atlas_pixel_size);
#endif
#endif

    for(int i = 0; i < int(u_light_counts[LIGHT_OMNI]); i++)
    {
        diffuse += accumulate_light(voxel_position, voxel_color, voxel_normal, int(u_light_indices[i][LIGHT_OMNI]), LIGHT_OMNI);
    }
    
    for(int j = 0; j < int(u_light_counts[LIGHT_SPOT]); j++)
    {
        diffuse += accumulate_light(voxel_position, voxel_color, voxel_normal, int(u_light_indices[j][LIGHT_SPOT]), LIGHT_SPOT);
    }
    
    diffuse = clamp(diffuse, vec3_splat(0.0), vec3_splat(1.0));
    return diffuse;
}

#endif
