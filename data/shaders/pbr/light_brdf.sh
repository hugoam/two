#include "light.sh"

#define BRDF_ARGS float NoL, float NoH, float LoH, float LoV, float XoH, float RoV, float NoV

float sqr(float a) { return a * a; }

// GGX Specular
// Source: http://www.filmicworlds.com/images/ggx-opt/optimized-ggx.hlsl
float G1V(float NoV, float k)
{
    return 1.0 / (NoV * (1.0 - k) + k);
}

float SchlickFresnel(float u)
{
    float m = 1.0-u;
    float m2 = m*m;
    return m2*m2*m; // pow(m,5)
}

float GTR1(float NoH, float a)
{
    if (a >= 1.0) return 1.0 / M_PI;
    float a2 = a * a;
    float t = 1.0 + (a2 - 1.0) * NoH * NoH;
    return (a2 - 1.0) / (M_PI * log(a2) * t);
}

float diffuse_lambert(BRDF_ARGS, float roughness)
{
	return max(NoL, 0.0);
}

float diffuse_half_lambert(BRDF_ARGS, float roughness)
{
	return NoL * 0.5 + 0.5;
}

vec3 diffuse_oren_nayar(BRDF_ARGS, float roughness, vec3 albedo)
{
    float s = LoV - NoL * NoV;
    float t = mix(1.0, max(NoL, NoV), step(0.0, s));

    float sigma2 = roughness * roughness;
    vec3 alpha = 1.0 + sigma2 * (albedo / (sigma2 + 0.13) + 0.5 / (sigma2 + 0.33));
    float beta = 0.45 * sigma2 / (sigma2 + 0.09);

    return max(0.0, NoL) * (alpha + vec3_splat(beta) * s / t) / M_PI;
}

float diffuse_toon(BRDF_ARGS, float roughness)
{
	return smoothstep(-roughness, max(roughness, 0.01), NoL);
}

float diffuse_burley(BRDF_ARGS, float roughness)
{
    float energyBias = mix(roughness, 0.0, 0.5);
    float energyFactor = mix(roughness, 1.0, 1.0 / 1.51);
    float fd90 = energyBias + 2.0 * LoH * LoH * roughness;
    float f0 = 1.0;
    float lightScatter = f0 + (fd90 - f0) * pow(1.0 - NoL, 5.0);
    float viewScatter = f0 + (fd90 - f0) * pow(1.0 - NoV, 5.0);

    return lightScatter * viewScatter * energyFactor;
}

float specular_blinn(BRDF_ARGS, float roughness)
{
	return pow(NoH, (1.0 - roughness) * 256.0);
}

float specular_phong(BRDF_ARGS, float roughness)
{
	return pow(RoV, (1.0 - roughness) * 256.0);
}

float specular_toon(BRDF_ARGS, float roughness)
{
	float mid = sqr(1.0 - roughness);
	return smoothstep(mid - roughness * 0.5, mid + roughness * 0.5, RoV) * mid;
}

float specular_schlick_GGX(BRDF_ARGS, float roughness, float anisotropy)
{
    float alpha = roughness * roughness;

#ifdef ANISOTROPY
    float aspect = sqrt(1.0 - anisotropy * 0.9);
    float rx = roughness / aspect;
    float ry = roughness * aspect;
    float ax = rx * rx;
    float ay = ry * ry;
    float pi = M_PI;
    float denom = sqr(XoH) / sqr(ax) + sqr(YoH) / sqr(ay) + sqr(NoH);
    float D = 1.0 / ( pi * ax * ay * denom * denom );
#else
    float alpha2 = alpha * alpha;
    float pi = M_PI;
    float denom = NoH * NoH * (alpha2 - 1.0) + 1.0;
    float D = alpha2 / (pi * denom * denom);
#endif
    // F
    float F0 = 1.0;
    float FH = SchlickFresnel( LoH );
    float F = F0 + (1.0 - F0) * (FH);

    // V
    float k = alpha / 2.0f;
    float vis = G1V(NoL, k) * G1V(NoV, k);

    return NoL * D * F * vis;

#ifdef CLEARCOAT
    float Dr = GTR1(NoH, mix(.1, .001, material.clearcoat_gloss));
    float Fr = mix(.04, 1.0, FH);
    float Gr = G1V(NoL, .25) * G1V(NoV, .25);

    specular += .25 * material.clearcoat * Gr * Fr * Dr;
#endif
}

// brdf approximation (Lazarov 2013)
// reference : https://www.unrealengine.com/en-US/blog/physically-based-shading-on-mobile
vec2 specular_brdf(float roughness, float NoV)
{
    const vec4 c0 = vec4(-1.0, -0.0275, -0.572, 0.022);
    const vec4 c1 = vec4( 1.0, 0.0425, 1.04, -0.04);
    vec4 r = roughness * c0 + c1;
    float a004 = min( r.x * r.x, exp2( -9.28 * NoV ) ) * r.x + r.y;
    return vec2( -1.04, 1.04 ) * a004 + r.zw;
}

vec3 brdf_specular_term(Fragment fragment, Material material)
{
    vec2 brdf = specular_brdf(material.roughness, fragment.NoV);
	return material.f0 * brdf.x + brdf.y;
}

#define PASS_BRDF light.NoL, light.NoH, light.LoH, light.LoV, light.XoH, light.RoV, fragment.NoV

void light_brdf(Light light, Fragment fragment, Material material, vec3 attenuation, inout vec3 diffuse, inout vec3 specular)
{
    if(material.metallic < 1.0) {
#if DIFFUSE_MODE == 0
        diffuse += light.energy * attenuation * material.albedo * diffuse_lambert(      PASS_BRDF, material.roughness);
#elif DIFFUSE_MODE == 1
        diffuse += light.energy * attenuation * material.albedo * diffuse_half_lambert( PASS_BRDF, material.roughness);
#elif DIFFUSE_MODE == 2
        diffuse += light.energy * attenuation * material.albedo * diffuse_oren_nayar(   PASS_BRDF, material.roughness, material.albedo);
#elif DIFFUSE_MODE == 3
        diffuse += light.energy * attenuation * material.albedo * diffuse_burley(       PASS_BRDF, material.roughness);
#elif DIFFUSE_MODE == 4
        diffuse += light.energy * attenuation * material.albedo * diffuse_toon(         PASS_BRDF, material.roughness);
#endif
    }
    
#ifdef RIM
	float rim_light = pow(1.0 - fragment.NoV,(1.0 - material.roughness) * 16.0);
	diffuse += rim_light * material.rim * mix(vec3(1.0), material.albedo, material.rim_tint) * light.energy;
#endif

	if (material.roughness > 0.0) {
#if SPECULAR_MODE == 0
        specular += light.energy * attenuation * light.specular * specular_schlick_GGX(PASS_BRDF, material.roughness, material.anisotropy);
#elif SPECULAR_MODE == 1
        specular += light.energy * attenuation * light.specular * specular_blinn(      PASS_BRDF, material.roughness);
#elif SPECULAR_MODE == 2
        specular += light.energy * attenuation * light.specular * specular_phong(      PASS_BRDF, material.roughness);
#elif SPECULAR_MODE == 3
        diffuse += light.energy * attenuation * light.specular * specular_toon(        PASS_BRDF, material.roughness) * material.specular * 2.0;
#elif SPECULAR_MODE == 4
#endif
	}
}
