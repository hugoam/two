#include <pbr/light.sh>
#include <pbr/radiance.sh>

struct LightRay
{
    //vec3 l;

    float NoL;
    float NoH;
    float LoH;

    float cNoL;
    float cNoH;
    float cLoH;
    
    float LoV;
#ifdef ANISOTROPY
    float XoH;
    float YoH;
#endif

    float RoV;
    float cRoV;
};

LightRay calc_light_ray(Fragment fragment, vec3 l)
{
    vec3 V = fragment.view;
    vec3 N = fragment.normal;
    vec3 L = l; //normalize(l);
    vec3 H = normalize(V + L);
	vec3 R = normalize(-reflect(L, N));
    
#ifdef ANISOTROPY
    vec3 B = fragment.binormal;
    vec3 T = fragment.tangent;
#endif

    LightRay r;
    //r.l = l;
    r.NoL = dot(N, L);
    r.NoH = dot(N, H);
    r.LoH = dot(L, H);
    r.cNoL = max(dot(N, L), 0.0);
    r.cNoH = max(dot(N, H), 0.0);
    r.cLoH = max(dot(L, H), 0.0);
    
    r.LoV = dot(L, V);
#ifdef ANISOTROPY
    r.XoH = dot(T, H);
    r.YoH = dot(B, H);
#endif
    
    r.RoV = dot(R, V);
    r.cRoV = max(dot(R, V), 0.0);
    return r;
}

float sqr(float a) { return a * a; }

// GGX Specular
// Source: http://www.filmicworlds.com/images/ggx-opt/optimized-ggx.hlsl
float G1V(float cNoV, float k)
{
    return 1.0 / (cNoV * (1.0 - k) + k);
}

float SchlickFresnel(float u)
{
    float m = 1.0-u;
    float m2 = m*m;
    return m2*m2*m; // pow(m,5)
}

float GTR1(float NoH, float a)
{
    if (a >= 1.0) return 1.0 / PI;
    float a2 = a * a;
    float t = 1.0 + (a2 - 1.0) * NoH * NoH;
    return (a2 - 1.0) / (PI * log(a2) * t);
}

// This returns the G_GGX function divided by 2 cos_theta_m, where in practice cos_theta_m is either N.L or N.V.
// We're dividing this factor off because the overall term we'll end up looks like
// (see, for example, the first unnumbered equation in B. Burley, "Physically Based Shading at Disney", SIGGRAPH 2012):
//
//   F(L.V) D(N.H) G(N.L) G(N.V) / (4 N.L N.V)
//
// We're basically regouping this as
//
//   F(L.V) D(N.H) [G(N.L)/(2 N.L)] [G(N.V) / (2 N.V)]
//
// and thus, this function implements the [G(N.m)/(2 N.m)] part with m = L or V.
//
// The contents of the D and G (G1) functions (GGX) are taken from
// E. Heitz, "Understanding the Masking-Shadowing Function in Microfacet-Based BRDFs", J. Comp. Graph. Tech. 3 (2) (2014).
// Eqns 71-72 and 85-86 (see also Eqns 43 and 80).

float G_GGX_2cos(float cos_theta_m, float alpha)
{
    // Schlick's approximation
    // C. Schlick, "An Inexpensive BRDF Model for Physically-based Rendering", Computer Graphics Forum. 13 (3): 233 (1994)
    // Eq. (19), although see Heitz (2014) about the problems with his derivation.
    // It nevertheless approximates GGX well with k = alpha/2.
    float k = 0.5 * alpha;
    return 0.5 / (cos_theta_m * (1.0 - k) + k);

    // float cos2 = cos_theta_m * cos_theta_m;
    // float sin2 = (1.0 - cos2);
    // return 1.0 / (cos_theta_m + sqrt(cos2 + alpha * alpha * sin2));
}

float D_GGX(float cos_theta_m, float alpha)
{
    float alpha2 = alpha * alpha;
    float d = 1.0 + (alpha2 - 1.0) * cos_theta_m * cos_theta_m;
    return alpha2 / (PI * d * d);
}

float G_GGX_anisotropic_2cos(float cos_theta_m, float alpha_x, float alpha_y, float cos_phi, float sin_phi)
{
    float cos2 = cos_theta_m * cos_theta_m;
    float sin2 = (1.0 - cos2);
    float s_x = alpha_x * cos_phi;
    float s_y = alpha_y * sin_phi;
    return 1.0 / max(cos_theta_m + sqrt(cos2 + (s_x * s_x + s_y * s_y) * sin2), 0.001);
}

float D_GGX_anisotropic(float cos_theta_m, float alpha_x, float alpha_y, float cos_phi, float sin_phi)
{
    float cos2 = cos_theta_m * cos_theta_m;
    float sin2 = (1.0 - cos2);
    float r_x = cos_phi / alpha_x;
    float r_y = sin_phi / alpha_y;
    float d = cos2 + sin2 * (r_x * r_x + r_y * r_y);
    return 1.0 / max(PI * alpha_x * alpha_y * d * d, 0.001);
}

float diffuse_lambert(LightRay l, float cNoV, float roughness)
{
    return max(l.NoL, 0.0);
    //return l.cNoL * (1.0 / PI);
}

float diffuse_half_lambert(LightRay l, float cNoV, float roughness)
{
    //return l.NoL * 0.5 + 0.5;
    return max(0.0, (l.NoL + roughness) / ((1.0 + roughness) * (1.0 + roughness)));
}

vec3 diffuse_oren_nayar(LightRay l, float NoV, float roughness, vec3 albedo)
{
    float s = l.LoV - l.NoL * NoV;
    float t = mix(1.0, max(l.NoL, NoV), step(0.0, s));

    float sigma2 = roughness * roughness;
    vec3 alpha = 1.0 + sigma2 * (albedo / (sigma2 + 0.13) + 0.5 / (sigma2 + 0.33));
    float beta = 0.45 * sigma2 / (sigma2 + 0.09);

    return max(0.0, l.cNoL) * (alpha + vec3_splat(beta) * s / t) / PI;
}

float diffuse_toon(LightRay l, float cNoV, float roughness)
{
	return smoothstep(-roughness, max(roughness, 0.01), l.NoL);
}

float diffuse_burley(LightRay l, float cNoV, float roughness)
{
    float FD90_minus_1 = 2.0 * l.LoH * l.LoH * roughness - 0.5;
    float FdV = 1.0 + FD90_minus_1 * SchlickFresnel(cNoV);
    float FdL = 1.0 + FD90_minus_1 * SchlickFresnel(l.cNoL);
    return (1.0 / PI) * FdV * FdL * l.cNoL;

    //float energyBias = mix(roughness, 0.0, 0.5);
    //float energyFactor = mix(roughness, 1.0, 1.0 / 1.51);
    //float fd90 = energyBias + 2.0 * l.LoH * l.LoH * roughness;
    //float f0 = 1.0;
    //float lightScatter = f0 + (fd90 - f0) * pow(1.0 - l.cNoL, 5.0);
    //float viewScatter = f0 + (fd90 - f0) * pow(1.0 - cNoV, 5.0);
    //
    //return lightScatter * viewScatter * energyFactor;
}

float specular_blinn(LightRay l, float cNoV, float roughness)
{
    //return pow(l.cNoH, (1.0 - roughness) * 256.0);
    
    float shininess = exp2(15.0 * (1.0 - roughness) + 1.0) * 0.25;
    float blinn = pow(l.cNoH, shininess);
    blinn *= (shininess + 8.0) * (1.0 / (8.0 * PI));
    return blinn / max(4.0 * cNoV * l.cNoL, 0.75);
}

float specular_phong(LightRay l, float cNoV, float roughness)
{
    //return pow(l.RoV, (1.0 - roughness) * 256.0);
    
    float shininess = exp2(15.0 * (1.0 - roughness) + 1.0) * 0.25;
    float phong = pow(l.cRoV, shininess);
    phong *= (shininess + 8.0) * (1.0 / (8.0 * PI));
    return phong / max(4.0 * cNoV * l.cNoL, 0.75);
}

float specular_toon(LightRay l, float cNoV, float roughness)
{
    float mid = sqr(1.0 - roughness);
    return smoothstep(mid - roughness * 0.5, mid + roughness * 0.5, l.RoV) * mid;
}

vec3 F0(float metallic, float specular, vec3 albedo)
{
    float dielectric = 0.16 * specular * specular;
    // use albedo * metallic as colored specular reflectance at 0 angle for metallic materials;
    // see https://google.github.io/filament/Filament.md.html
    return mix(vec3_splat(dielectric), albedo, metallic);
}

vec3 specular_schlick_GGX(LightRay l, float cNoV, float roughness, vec3 f0, float anisotropy)
{
    float alpha = roughness * roughness;

#ifdef ANISOTROPY
    float aspect = sqrt(1.0 - anisotropy * 0.9);
    float ax = alpha / aspect;
    float ay = alpha * aspect;
    float D = D_GGX_anisotropic(l.cNoH, ax, ay, l.XoH, l.YoH);
    float G = G_GGX_anisotropic_2cos(cNdotL, ax, ay, l.XoH, l.YoH) * G_GGX_anisotropic_2cos(cNoV, ax, ay, l.XoH, l.YoH);
#else
    float D = D_GGX(l.cNoH, alpha);
    float G = G_GGX_2cos(l.cNoL, alpha) * G_GGX_2cos(cNoV, alpha);
#endif
    // F
    //vec3 f0 = F0(metallic, specular, diffuse_color);
    float cLdotH5 = SchlickFresnel(l.cLoH);
    vec3 F = mix(vec3_splat(cLdotH5), vec3_splat(1.0), f0);

    return l.cNoL * D * F * G;

#ifdef CLEARCOAT
    float Dr = GTR1(l.NoH, mix(.1, .001, material.clearcoat_gloss));
    float Fr = mix(.04, 1.0, FH);
    float Gr = G1V(l.NoL, .25) * G1V(cNoV, .25);

    specular += .25 * material.clearcoat * Gr * Fr * Dr;
#endif
}

float specular_schlick_GGX_old(LightRay l, float cNoV, float roughness, vec3 f0, float anisotropy)
{
    float alpha = roughness * roughness;

#ifdef ANISOTROPY
    float aspect = sqrt(1.0 - anisotropy * 0.9);
    float rx = roughness / aspect;
    float ry = roughness * aspect;
    float ax = rx * rx;
    float ay = ry * ry;
    float pi = PI;
    float denom = sqr(l.XoH) / sqr(ax) + sqr(l.YoH) / sqr(ay) + sqr(l.NoH);
    float D = 1.0 / ( pi * ax * ay * denom * denom );
#else
    float alpha2 = alpha * alpha;
    float pi = PI;
    float denom = l.cNoH * l.NoH * (alpha2 - 1.0) + 1.0;
    float D = alpha2 / (pi * denom * denom);
#endif
    // F
    float F0 = 1.0;
    float FH = SchlickFresnel( l.LoH );
    float F = F0 + (1.0 - F0) * (FH);

    // V
    float k = alpha / 2.0f;
    float vis = G1V(l.NoL, k) * G1V(cNoV, k);

    return l.cNoL * D * F * vis;

#ifdef CLEARCOAT
    float Dr = GTR1(l.NoH, mix(.1, .001, material.clearcoat_gloss));
    float Fr = mix(.04, 1.0, FH);
    float Gr = G1V(l.NoL, .25) * G1V(cNoV, .25);

    specular += .25 * material.clearcoat * Gr * Fr * Dr;
#endif
}

// brdf approximation (Lazarov 2013)
// reference : https://www.unrealengine.com/en-US/blog/physically-based-shading-on-mobile
vec2 specular_brdf(float roughness, float cNoV)
{
    const vec4 c0 = vec4(-1.0, -0.0275, -0.572, 0.022);
    const vec4 c1 = vec4( 1.0, 0.0425, 1.04, -0.04);
    vec4 r = roughness * c0 + c1;
    float a004 = min( r.x * r.x, exp2( -9.28 * cNoV ) ) * r.x + r.y;
    return vec2( -1.04, 1.04 ) * a004 + r.zw;
}

vec3 brdf_specular_term(Fragment fragment, vec3 f0, float roughness)
{
    vec2 brdf = specular_brdf(roughness, fragment.cNoV);
	return f0 * brdf.x + brdf.y;
}

#define LAMBERT 0
#define HALF_LAMBERT 1
#define OREN_NAYAR 2
#define BURLEY 3
#define DIFFUSE_TOON 5

#define SHLICK_GGX 0
#define BLINN 1
#define PHONG 2
#define SPECULAR_TOON 3
#define NO_SPECULAR 4

float env_brdf_miplevel(Material material)
{
    return material.roughness * RADIANCE_MAX_LOD;
}

void env_brdf(Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular)
{
    diffuse *= material.albedo * rPI; // lambert brdf
    specular *= brdf_specular_term(fragment, material.f0, material.roughness);
}

void direct_brdf(vec3 energy, vec3 l, Fragment fragment, Material material, inout vec3 diffuse, inout vec3 specular)
{
    LightRay ray = calc_light_ray(fragment, l);
 
    if(material.metallic < 1.0) {
#if DIFFUSE_MODE == LAMBERT
        diffuse += energy * material.albedo * diffuse_lambert(      ray, fragment.cNoV, material.roughness);
#elif DIFFUSE_MODE == HALF_LAMBERT
        diffuse += energy * material.albedo * diffuse_half_lambert( ray, fragment.cNoV, material.roughness);
#elif DIFFUSE_MODE == OREN_NAYAR
        diffuse += energy * material.albedo * diffuse_oren_nayar(   ray, fragment.NoV, material.roughness, material.albedo);
#elif DIFFUSE_MODE == BURLEY
        diffuse += energy * material.albedo * diffuse_burley(       ray, fragment.cNoV, material.roughness);
#elif DIFFUSE_MODE == DIFFUSE_TOON
        diffuse += energy * material.albedo * diffuse_toon(         ray, fragment.cNoV, material.roughness);
#endif
    }
    
#ifdef RIM
	float rim_light = pow(1.0 - fragment.cNoV,(1.0 - material.roughness) * 16.0);
	diffuse += energy * rim_light * material.rim * mix(vec3(1.0), material.albedo, material.rim_tint);
#endif

	if (material.roughness > 0.0) {
#if SPECULAR_MODE == SHLICK_GGX
        specular += energy * specular_schlick_GGX(ray, fragment.cNoV, material.roughness, material.f0, material.anisotropy);
#elif SPECULAR_MODE == BLINN
        specular += energy * specular_blinn(      ray, fragment.cNoV, material.roughness);
#elif SPECULAR_MODE == PHONG
        specular += energy * specular_phong(      ray, fragment.cNoV, material.roughness);
#elif SPECULAR_MODE == SPECULAR_TOON
        diffuse  += energy * specular_toon(       ray, fragment.cNoV, material.roughness) * material.specular * 2.0;
#elif SPECULAR_MODE == NO_SPECULAR
#endif
	}
}
