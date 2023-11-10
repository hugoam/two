#include <pbr/light.sh>
#include <pbr/bsdf.sh>
#include <pbr/radiance.sh>

#ifdef TOON
uniform sampler2D s_gradient;

vec3 gradient_energy(vec3 energy, vec3 l, vec3 normal)
{
    float dotNL = dot(normal, l);
    vec2 coord = vec2(dotNL * 0.5 + 0.5, 0.0);
#ifdef USE_GRADIENTMAP
    energy *= texture2D(s_gradient, coord).rgb;
#else
    energy *= (coord.x < 0.7) ? vec3_splat(0.7) : vec3_splat(1.0);
#endif
#ifndef PHYSICALLY_CORRECT_LIGHTS
    energy *= PI; // punctual light
#endif
    return energy;
}
#endif

vec3 direct_energy(vec3 energy, vec3 l, vec3 normal)
{
    float dotNL = saturate(dot(normal, l));
    energy *= dotNL;
#ifndef PHYSICALLY_CORRECT_LIGHTS
    energy *= PI; // punctual light
#endif
    return energy;
}

#ifdef BRDF_BLINN_PHONG
#define direct_brdf direct_blinn_phong
#define indirect_brdf indirect_blinn_phong
#define env_brdf_miplevel env_specular_miplevel_phong
#endif

#ifdef BRDF_LAMBERT
#define env_brdf_miplevel env_specular_miplevel_lambert
#endif

void direct_blinn_phong(vec3 energy, vec3 l, Fragment fragment, PhongMaterial material, inout vec3 diffuse, inout vec3 specular) {

#ifdef TOON
    vec3 irradiance = gradient_energy(energy, l, fragment.normal);
#else
    vec3 irradiance = direct_energy(energy, l, fragment.normal);
#endif

    diffuse += irradiance * BRDF_Diffuse_Lambert(material.diffuse);
    specular += irradiance * BRDF_Specular_BlinnPhong(l, fragment, material.specular, material.shininess) * 1.0; //material.specularStrength;
}

void indirect_blinn_phong(Fragment fragment, PhongMaterial material, inout vec3 diffuse, inout vec3 specular) {

    diffuse *= BRDF_Diffuse_Lambert(material.diffuse);
}

// ref: http://casual-effects.blogspot.ca/2011/08/plausible-environment-lighting-in-two.html
float env_shininess_miplevel(float shininess)
{
    float level = RADIANCE_MAX_LOD + 0.79248 - 0.5 * log2(pow2(shininess) + 1.0);

    // clamp to allowable LOD ranges.
    return clamp(level, 0.0, RADIANCE_MAX_LOD);
}

float env_specular_miplevel_phong(PhongMaterial material)
{
    return env_shininess_miplevel(material.shininess);
}

float env_specular_miplevel_lambert(PhongMaterial material)
{
    return 0.0;
}

void env_blend_op(PhongMaterial material, vec3 color, inout vec3 light, float factor)
{
    float specularStrength = 1.0; // can be sampled from a specular map
    float amount = specularStrength * material.reflectivity;
#if ENV_BLEND == 0 // MULTIPLY
    light = mix(light, light * color, amount);
#elif ENV_BLEND == 1 // MIX
    light = mix(light, color * factor, amount);
#elif ENV_BLEND == 2 // ADD
    light += color * factor * amount;
#endif
}

void env_brdf_blend(PhongMaterial material, vec3 color, inout vec3 diffuse, inout vec3 specular)
{
    // lambert stores all light in diffuse
    env_blend_op(material, color, diffuse, 0.5);
    env_blend_op(material, color, specular, 0.5);
}

void env_brdf_simple(Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular)
{
    diffuse *= BRDF_Diffuse_Lambert(material.albedo);
    specular *= BRDF_Specular_GGX_Environment(fragment, material.f0, material.roughness);
}

void env_brdf_multiscatter(Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular)
{
    vec3 singleScattering = vec3_splat(0.0);
    vec3 multiScattering = vec3_splat(0.0);
    vec3 cosineWeightedIrradiance = diffuse * rPI;
    diffuse = vec3_splat(0.0);
    BRDF_Specular_Multiscattering_Environment(fragment, material.f0, material.roughness, singleScattering, multiScattering);
    specular *= singleScattering;
    diffuse += multiScattering * cosineWeightedIrradiance;
    diffuse += material.albedo * cosineWeightedIrradiance;
}

void env_brdf(Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular)
{
    //env_brdf_multiscatter(fragment, material, diffuse, specular);
    env_brdf_simple(fragment, material, diffuse, specular);
}

#ifdef BRDF_PHYSICAL
void env_brdf_physical(Fragment fragment, Material material, vec3 clearcoatSpecular, inout vec3 diffuse, inout vec3 specular)
{
    float dotNV = saturate(dot(fragment.normal, fragment.viewDir));
    float dotNL = dotNV;
    float clearCoatDHR = material.clearCoat * clearCoatDHRApprox(material.clearCoatRoughness, dotNL);
    float clearCoatInv = 1.0 - clearCoatDHR;
    //env_brdf_multiscatter();
    specular *= clearCoatInv * BRDF_Specular_GGX_Environment(fragment, material.f0, material.roughness);
    specular += clearcoatSpecular * material.clearCoat * BRDF_Specular_GGX_Environment(fragment, vec3(DEFAULT_SPECULAR_COEFFICIENT), material.clearCoatRoughness);
}
#endif

#ifdef BRDF_STANDARD
#define direct_brdf direct_standard
#define indirect_brdf indirect_standard
#define env_brdf_miplevel env_specular_miplevel_pbr
#endif

#define MAX_REFLECTANCE 0.16
#define DEFAULT_REFLECTANCE 0.04

float env_specular_miplevel_pbr(Material material)
{
    float shininess = GGXRoughnessToBlinnExponent(material.roughness);
    return env_shininess_miplevel(shininess);
    //return material.roughness * RADIANCE_MAX_LOD;
}

// Clear coat directional hemishperical reflectance (this approximation should be improved)
float clearCoatDHRApprox(float roughness, float dotNL) {

    return MAX_REFLECTANCE + (1.0 - DEFAULT_REFLECTANCE) * (pow(1.0 - dotNL, 5.0) * pow(1.0 - roughness, 2.0));
}

#if NUM_RECT_AREA_LIGHTS > 0
struct RectAreaLight {
    vec3 color;
    vec3 position;
    vec3 halfWidth;
    vec3 halfHeight;
};

// Pre-computed values of LinearTransformedCosine approximation of BRDF
// BRDF approximation Texture is 64x64
uniform sampler2D ltc_1; // RGBA Float
uniform sampler2D ltc_2; // RGBA Float

uniform RectAreaLight rectAreaLights[ NUM_RECT_AREA_LIGHTS ];

void direct_rect_physical(RectAreaLight light, Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular) {

    vec3 rectCoords[4];
    rectCoords[0] = light.position + light.halfWidth - light.halfHeight; // counterclockwise; light shines in local neg z direction
    rectCoords[1] = light.position - light.halfWidth - light.halfHeight;
    rectCoords[2] = light.position - light.halfWidth + light.halfHeight;
    rectCoords[3] = light.position + light.halfWidth + light.halfHeight;

    vec2 uv = LTC_Uv(fragment.normal, fragment.view, material.roughness);

    vec4 t1 = texture2D(ltc_1, uv);
    vec4 t2 = texture2D(ltc_2, uv);

    mat3 mInv = mat3(
        vec3(t1.x, 0, t1.y),
        vec3(0, 1,    0),
        vec3(t1.z, 0, t1.w)
);

    // LTC Fresnel Approximation by Stephen Hill
    // http://blog.selfshadow.com/publications/s2016-advances/s2016_ltc_fresnel.pdf
    vec3 fresnel = (material.f0 * t2.x + (vec3(1.0) - material.f0) * t2.y);

    specular += light.energy * fresnel * LTC_Evaluate(fragment.normal, fragment.view, fragment.position, mInv, rectCoords);

    diffuse += light.energy * material.albedo * LTC_Evaluate(fragment.normal, fragment.view, fragment.position, mat3(1.0), rectCoords);
}
#endif

void direct_standard(vec3 energy, vec3 l, Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular) {

    vec3 irradiance = direct_energy(energy, l, fragment.normal);

    specular += irradiance * BRDF_Specular_GGX(l, fragment, material.f0, material.roughness);

    diffuse += irradiance * BRDF_Diffuse_Lambert(material.albedo);
}

void indirect_standard(Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular) {

    diffuse *= BRDF_Diffuse_Lambert(material.albedo);
    specular *= BRDF_Specular_GGX_Environment(fragment, material.f0, material.roughness);
}

#ifdef BRDF_PHYSICAL
void direct_physical(vec3 energy, vec3 l, Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular) {

    vec3 irradiance = direct_energy(energy, l, fragment.normal);

    float clearCoatDHR = material.clearcoat * clearCoatDHRApprox(material.clearCoatRoughness, dotNL);

    specular += (1.0 - clearCoatDHR) * irradiance * BRDF_Specular_GGX(l, fragment, material.f0, material.roughness);

    diffuse += (1.0 - clearCoatDHR) * irradiance * BRDF_Diffuse_Lambert(material.albedo);

    specular += irradiance * material.clearcoat * BRDF_Specular_GGX(l, fragment, vec3(DEFAULT_SPECULAR_COEFFICIENT), material.clearCoatRoughness);
}

void indirect_physical(vec3 irradiance, vec3 radiance, vec3 radiance_clearcoat, Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular) {

    float dotNV = saturate(dot(fragment.normal, fragment.view));
    float dotNL = dotNV;
    float clearCoatDHR = material.clearCoat * clearCoatDHRApprox(material.clearCoatRoughness, dotNL);

    diffuse += irradiance * BRDF_Diffuse_Lambert(material.albedo);
    specular += (1.0 - clearCoatDHR) * radiance * BRDF_Specular_GGX_Environment(fragment, material.f0, material.roughness);
    specular += radiance_clearcoat * material.clearCoat * BRDF_Specular_GGX_Environment(fragment, vec3(DEFAULT_SPECULAR_COEFFICIENT), material.clearCoatRoughness);
}
#endif

#define BlinnShininessExponent(roughness)   GGXRoughnessToBlinnExponent(roughness)


// ref: https://seblagarde.files.wordpress.com/2015/07/course_notes_moving_frostbite_to_pbr_v32.pdf
float computeSpecularOcclusion(float dotNV, float ambientOcclusion, float roughness) {

    return saturate(pow(dotNV + ambientOcclusion, exp2(- 16.0 * roughness - 1.0)) - 1.0 + ambientOcclusion);
}
