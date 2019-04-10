#ifndef MUD_SHADER_LIGHT
#define MUD_SHADER_LIGHT

#include <common.sh>
#include <convert.sh>
#include <pbr/pbr.sh>
#include <gpu/light.sh>

#ifndef ZONES_TEXTURE
uniform vec4 u_light_counts;
uniform vec4 u_shadow_counts;
uniform vec4 u_light_indices[MAX_LIGHTS];
#endif

#define LIGHT_DIRECT 0
#define LIGHT_POINT 1
#define LIGHT_SPOT 2

float point_light_decay(float lightDistance, float cutoffDistance, float decayExponent) {

#ifdef PHYSICALLY_CORRECT_LIGHTS
    // based upon Frostbite 3 Moving to Physically-based Rendering
    // page 32, equation 26: E[window1]
    // https://seblagarde.files.wordpress.com/2015/07/course_notes_moving_frostbite_to_pbr_v32.pdf
    // this is intended to be used on spot and point lights who are represented as luminous intensity
    // but who must be converted to luminous irradiance for surface lighting calculation
    float distanceFalloff = 1.0 / max(pow(lightDistance, decayExponent), 0.01);

    if(cutoffDistance > 0.0) {
        distanceFalloff *= pow2(saturate(1.0 - pow4(lightDistance / cutoffDistance)));
    }

    return distanceFalloff;

#else
    if(cutoffDistance > 0.0 && decayExponent > 0.0) {
        return pow(saturate(-lightDistance / cutoffDistance + 1.0), decayExponent);
    }

    return 1.0;
#endif

}

float omni_attenuation_three(vec3 l, float range, float factor)
{
    return point_light_decay(length(l), range, factor);
}

float omni_attenuation(vec3 l, float range, float factor, float cap)
{
    return omni_attenuation_three(l, range, factor);
    //float normalized_distance = length(l) / range;
    //float attenuation = pow(max(1.0 - normalized_distance, cap), factor);
    //return attenuation;
}

float spot_attenuation(vec3 l, vec3 direction, float range, float factor, float spot_attenuation, float spot_cutoff)
{
    float attenuation = omni_attenuation(l, range, factor, 0.001);
    float scos = max(dot(normalize(l), -direction), spot_cutoff);
    float spot_rim = (1.0 - scos) / (1.0 - spot_cutoff);
    return attenuation * (1.0 - pow(max(spot_rim, 0.001), spot_attenuation));
}

float spot_attenuation_three(vec3 l, vec3 direction, float range, float factor, float cone_cos, float penumbra_cos)
{
    float attenuation = omni_attenuation(l, range, factor, 0.001);
    float angle_cos = dot(normalize(l), direction);
    if (angle_cos > cone_cos) {
        return attenuation * smoothstep(cone_cos, penumbra_cos, angle_cos);
    } else {
        return 0.0;
    }
}
    
float omni_attenuation(vec3 l, Light light)
{
    return omni_attenuation(l, light.range, light.attenuation, 0.0);
}

float spot_attenuation(vec3 l, Light light)
{
    return spot_attenuation(l, light.direction, light.range, light.attenuation, light.spot_attenuation, light.spot_cutoff);
}

vec3 light_hemisphere(vec3 l, vec3 ground, vec3 sky, Fragment fragment) {

    float dotNL = dot(fragment.normal, l);
    float weight = 0.5 * dotNL + 0.5;

    vec3 irradiance = mix(ground, sky, weight);

#ifndef PHYSICALLY_CORRECT_LIGHTS
    irradiance *= PI;
#endif

    return irradiance;
}

#include <pbr/shadow.sh>

#ifdef CLUSTERED
#include <pbr/light_cluster.sh>
#endif

#endif
