#include <pbr/light.sh>

struct LightRay
{
    vec3 l;
    
    float NoL;
    float NoH;
    float LoH;

    float LoV;
    float XoH;
    float YoH;

	float RoV;
};

LightRay calc_light_ray(Fragment fragment, vec3 l)
{
    vec3 V = fragment.view;
    vec3 N = fragment.normal;
    vec3 B = fragment.binormal;
    vec3 T = fragment.tangent;
    vec3 L = normalize(l);
    vec3 H = normalize(V + L);
	vec3 R = normalize(-reflect(L, N));
    
    LightRay r;
    r.l = l;
    r.NoL = max(dot(N, L), 0.0);
    r.NoH = max(dot(N, H), 0.0);
    r.LoH = max(dot(L, H), 0.0);
    
    r.LoV = dot(L, V);
    r.XoH = dot(T, H);
    r.YoH = dot(B, H);
    
	r.RoV = max(dot(R, V), 0.0);
    return r;
}

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

float diffuse_lambert(LightRay l, float NoV, float roughness)
{
	return max(l.NoL, 0.0);
}

float diffuse_half_lambert(LightRay l, float NoV, float roughness)
{
	return l.NoL * 0.5 + 0.5;
}

vec3 diffuse_oren_nayar(LightRay l, float NoV, float roughness, vec3 albedo)
{
    float s = l.LoV - l.NoL * NoV;
    float t = mix(1.0, max(l.NoL, NoV), step(0.0, s));

    float sigma2 = roughness * roughness;
    vec3 alpha = 1.0 + sigma2 * (albedo / (sigma2 + 0.13) + 0.5 / (sigma2 + 0.33));
    float beta = 0.45 * sigma2 / (sigma2 + 0.09);

    return max(0.0, l.NoL) * (alpha + vec3_splat(beta) * s / t) / M_PI;
}

float diffuse_toon(LightRay l, float NoV, float roughness)
{
	return smoothstep(-roughness, max(roughness, 0.01), l.NoL);
}

float diffuse_burley(LightRay l, float NoV, float roughness)
{
    float energyBias = mix(roughness, 0.0, 0.5);
    float energyFactor = mix(roughness, 1.0, 1.0 / 1.51);
    float fd90 = energyBias + 2.0 * l.LoH * l.LoH * roughness;
    float f0 = 1.0;
    float lightScatter = f0 + (fd90 - f0) * pow(1.0 - l.NoL, 5.0);
    float viewScatter = f0 + (fd90 - f0) * pow(1.0 - NoV, 5.0);

    return lightScatter * viewScatter * energyFactor;
}

float specular_blinn(LightRay l, float NoV, float roughness)
{
	return pow(l.NoH, (1.0 - roughness) * 256.0);
}

float specular_phong(LightRay l, float NoV, float roughness)
{
	return pow(l.RoV, (1.0 - roughness) * 256.0);
}

float specular_toon(LightRay l, float NoV, float roughness)
{
	float mid = sqr(1.0 - roughness);
	return smoothstep(mid - roughness * 0.5, mid + roughness * 0.5, l.RoV) * mid;
}

float specular_schlick_GGX(LightRay l, float NoV, float roughness, float anisotropy)
{
    float alpha = roughness * roughness;

#ifdef ANISOTROPY
    float aspect = sqrt(1.0 - anisotropy * 0.9);
    float rx = roughness / aspect;
    float ry = roughness * aspect;
    float ax = rx * rx;
    float ay = ry * ry;
    float pi = M_PI;
    float denom = sqr(l.XoH) / sqr(ax) + sqr(l.YoH) / sqr(ay) + sqr(l.NoH);
    float D = 1.0 / ( pi * ax * ay * denom * denom );
#else
    float alpha2 = alpha * alpha;
    float pi = M_PI;
    float denom = l.NoH * l.NoH * (alpha2 - 1.0) + 1.0;
    float D = alpha2 / (pi * denom * denom);
#endif
    // F
    float F0 = 1.0;
    float FH = SchlickFresnel( l.LoH );
    float F = F0 + (1.0 - F0) * (FH);

    // V
    float k = alpha / 2.0f;
    float vis = G1V(l.NoL, k) * G1V(NoV, k);

    return l.NoL * D * F * vis;

#ifdef CLEARCOAT
    float Dr = GTR1(l.NoH, mix(.1, .001, material.clearcoat_gloss));
    float Fr = mix(.04, 1.0, FH);
    float Gr = G1V(l.NoL, .25) * G1V(NoV, .25);

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

void light_brdf(Light light, vec3 l, Fragment fragment, Material material, float factor, inout vec3 diffuse, inout vec3 specular)
{
    LightRay ray = calc_light_ray(fragment, l);
 
    if(material.metallic < 1.0) {
#if DIFFUSE_MODE == 0
        diffuse += light.energy * factor * material.albedo * diffuse_lambert(      ray, fragment.NoV, material.roughness);
#elif DIFFUSE_MODE == 1
        diffuse += light.energy * factor * material.albedo * diffuse_half_lambert( ray, fragment.NoV, material.roughness);
#elif DIFFUSE_MODE == 2
        diffuse += light.energy * factor * material.albedo * diffuse_oren_nayar(   ray, fragment.NoV, material.roughness, material.albedo);
#elif DIFFUSE_MODE == 3
        diffuse += light.energy * factor * material.albedo * diffuse_burley(       ray, fragment.NoV, material.roughness);
#elif DIFFUSE_MODE == 4
        diffuse += light.energy * factor * material.albedo * diffuse_toon(         ray, fragment.NoV, material.roughness);
#endif
    }
    
#ifdef RIM
	float rim_light = pow(1.0 - fragment.NoV,(1.0 - material.roughness) * 16.0);
	diffuse += rim_light * material.rim * mix(vec3(1.0), material.albedo, material.rim_tint) * light.energy;
#endif

	if (material.roughness > 0.0) {
#if SPECULAR_MODE == 0
        specular += light.energy * factor * light.specular * specular_schlick_GGX(ray, fragment.NoV, material.roughness, material.anisotropy);
#elif SPECULAR_MODE == 1
        specular += light.energy * factor * light.specular * specular_blinn(      ray, fragment.NoV, material.roughness);
#elif SPECULAR_MODE == 2
        specular += light.energy * factor * light.specular * specular_phong(      ray, fragment.NoV, material.roughness);
#elif SPECULAR_MODE == 3
        diffuse += light.energy * factor * light.specular * specular_toon(        ray, fragment.NoV, material.roughness) * material.specular * 2.0;
#elif SPECULAR_MODE == 4
#endif
	}
}
