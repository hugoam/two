#ifndef MUD_SHADER_BSDF_THREE
#define MUD_SHADER_BSDF_THREE

// Analytical approximation of the DFG LUT, one half of the
// split-sum approximation used in indirect specular lighting.
// via 'environmentBRDF' from "Physically Based Shading on Mobile"
// https://www.unrealengine.com/blog/physically-based-shading-on-mobile - environmentBRDF for GGX on mobile

vec2 integrateSpecularBRDF(float dotNV, float roughness) {
    const vec4 c0 = vec4(-1, -0.0275, -0.572, 0.022);

    const vec4 c1 = vec4(1, 0.0425, 1.04, -0.04);

    vec4 r = roughness * c0 + c1;

    float a004 = min(r.x * r.x, exp2(-9.28 * dotNV)) * r.x + r.y;

    return vec2(-1.04, 1.04) * a004 + r.zw;
}

vec3 BRDF_Diffuse_Lambert(vec3 diffuseColor) {

    return rPI * diffuseColor;

} // validated

vec3 F_Schlick(vec3 specularColor, float dotLH) {

    // Original approximation by Christophe Schlick '94
    // float fresnel = pow(1.0 - dotLH, 5.0);

    // Optimized variant (presented by Epic at SIGGRAPH '13)
    // https://cdn2.unrealengine.com/Resources/files/2013SiggraphPresentationsNotes-26915738.pdf
    float fresnel = exp2((-5.55473 * dotLH - 6.98316) * dotLH);

    return (1.0 - specularColor) * fresnel + specularColor;

} // validated

// Microfacet Models for Refraction through Rough Surfaces - equation (34)
// http://graphicrants.blogspot.com/2013/08/specular-brdf-reference.html
// alpha is "roughness squared" in Disney’s reparameterization
float G_GGX_Smith(float alpha, float dotNL, float dotNV) {

    // fragment term (normalized) = G(l)⋅G(v) / 4(n⋅l)(n⋅v)
    // also see #12151

    float a2 = pow2(alpha);

    float gl = dotNL + sqrt(a2 + (1.0 - a2) * pow2(dotNL));
    float gv = dotNV + sqrt(a2 + (1.0 - a2) * pow2(dotNV));

    return 1.0 / (gl * gv);

} // validated

// Moving Frostbite to Physically Based Rendering 3.0 - page 12, listing 2
// https://seblagarde.files.wordpress.com/2015/07/course_notes_moving_frostbite_to_pbr_v32.pdf
float G_GGX_SmithCorrelated(float alpha, float dotNL, float dotNV) {

    float a2 = pow2(alpha);

    // dotNL and dotNV are explicitly swapped. This is not a mistake.
    float gv = dotNL * sqrt(a2 + (1.0 - a2) * pow2(dotNV));
    float gl = dotNV * sqrt(a2 + (1.0 - a2) * pow2(dotNL));

    return 0.5 / max(gv + gl, EPSILON);

}

// Microfacet Models for Refraction through Rough Surfaces - equation (33)
// http://graphicrants.blogspot.com/2013/08/specular-brdf-reference.html
// alpha is "roughness squared" in Disney’s reparameterization
float D_GGX(float alpha, float dotNH) {

    float a2 = pow2(alpha);

    float denom = pow2(dotNH) * (a2 - 1.0) + 1.0; // avoid alpha = 0 with dotNH = 1

    return rPI * a2 / pow2(denom);

}

// GGX Distribution, Schlick Fresnel, GGX-Smith Visibility
vec3 BRDF_Specular_GGX(vec3 l, Fragment fragment, vec3 specularColor, float roughness) {

    float alpha = pow2(roughness); // UE4's roughness

    vec3 halfDir = normalize(l + fragment.view);

    float dotNL = saturate(dot(fragment.normal, l));
    float dotNV = saturate(dot(fragment.normal, fragment.view));
    float dotNH = saturate(dot(fragment.normal, halfDir));
    float dotLH = saturate(dot(l, halfDir));

    vec3 F = F_Schlick(specularColor, dotLH);

    float G = G_GGX_SmithCorrelated(alpha, dotNL, dotNV);

    float D = D_GGX(alpha, dotNH);

    return F * (G * D);

} // validated

#if NUM_RECT_AREA_LIGHTS > 0
// Rect Area Light

// Real-Time Polygonal-Light Shading with Linearly Transformed Cosines
// by Eric Heitz, Jonathan Dupuy, Stephen Hill and David Neubelt
// code: https://github.com/selfshadow/ltc_code/

vec2 LTC_Uv(vec3 N, vec3 V, float roughness) {

    const float LUT_SIZE  = 64.0;
    const float LUT_SCALE = (LUT_SIZE - 1.0) / LUT_SIZE;
    const float LUT_BIAS  = 0.5 / LUT_SIZE;

    float dotNV = saturate(dot(N, V));

    // texture parameterized by sqrt(GGX alpha) and sqrt(1 - cos(theta))
    vec2 uv = vec2(roughness, sqrt(1.0 - dotNV));

    uv = uv * LUT_SCALE + LUT_BIAS;

    return uv;

}

float LTC_ClippedSphereFormFactor(vec3 f) {

    // Real-Time Area Lighting: a Journey from Research to Production (p.102)
    // An approximation of the form factor of a horizon-clipped rectangle.

    float l = length(f);

    return max((l * l + f.z) / (l + 1.0), 0.0);
}

vec3 LTC_EdgeVectorFormFactor(vec3 v1, vec3 v2) {

    float x = dot(v1, v2);

    float y = abs(x);

    // rational polynomial approximation to theta / sin(theta) / 2PI
    float a = 0.8543985 + (0.4965155 + 0.0145206 * y) * y;
    float b = 3.4175940 + (4.1616724 + y) * y;
    float v = a / b;

    float theta_sintheta = (x > 0.0) ? v : 0.5 * inversesqrt(max(1.0 - x * x, 1e-7)) - v;

    return cross(v1, v2) * theta_sintheta;
}

vec3 LTC_Evaluate(vec3 N, vec3 V, vec3 P, mat3 mInv, vec3 rectCoords[4]) {

    // bail if point is on back side of plane of light
    // assumes ccw winding order of light vertices
    vec3 v1 = rectCoords[1] - rectCoords[0];
    vec3 v2 = rectCoords[3] - rectCoords[0];
    vec3 lightNormal = cross(v1, v2);

    if(dot(lightNormal, P - rectCoords[0]) < 0.0) return vec3_splat(0.0);

    // construct orthonormal basis around N
    vec3 T1, T2;
    T1 = normalize(V - N * dot(V, N));
    T2 = - cross(N, T1); // negated from paper; possibly due to a different handedness of world coordinate system

    // compute transform
    mat3 mat = mInv * transpose(mat3(T1, T2, N));

    // transform rect
    vec3 coords[4];
    coords[0] = mul(mat, (rectCoords[0] - P));
    coords[1] = mul(mat, (rectCoords[1] - P));
    coords[2] = mul(mat, (rectCoords[2] - P));
    coords[3] = mul(mat, (rectCoords[3] - P));

    // project rect onto sphere
    coords[0] = normalize(coords[0]);
    coords[1] = normalize(coords[1]);
    coords[2] = normalize(coords[2]);
    coords[3] = normalize(coords[3]);

    // calculate vector form factor
    vec3 vectorFormFactor = vec3_splat(0.0);
    vectorFormFactor += LTC_EdgeVectorFormFactor(coords[0], coords[1]);
    vectorFormFactor += LTC_EdgeVectorFormFactor(coords[1], coords[2]);
    vectorFormFactor += LTC_EdgeVectorFormFactor(coords[2], coords[3]);
    vectorFormFactor += LTC_EdgeVectorFormFactor(coords[3], coords[0]);

    // adjust for horizon clipping
    float result = LTC_ClippedSphereFormFactor(vectorFormFactor);

/*
    // alternate method of adjusting for horizon clipping (see referece)
    // refactoring required
    float len = length(vectorFormFactor);
    float z = vectorFormFactor.z / len;

    const float LUT_SIZE  = 64.0;
    const float LUT_SCALE = (LUT_SIZE - 1.0) / LUT_SIZE;
    const float LUT_BIAS  = 0.5 / LUT_SIZE;

    // tabulated horizon-clipped sphere, apparently...
    vec2 uv = vec2(z * 0.5 + 0.5, len);
    uv = uv * LUT_SCALE + LUT_BIAS;

    float scale = texture2D(ltc_2, uv).w;

    float result = len * scale;
*/

    return vec3_splat(result);

}
#endif

// End Rect Area Light

// ref: https://www.unrealengine.com/blog/physically-based-shading-on-mobile - environmentBRDF for GGX on mobile
vec3 BRDF_Specular_GGX_Environment(Fragment fragment, vec3 specularColor, float roughness) {

    float dotNV = saturate(dot(fragment.normal, fragment.view));

    vec2 brdf = integrateSpecularBRDF(dotNV, roughness);

    return specularColor * brdf.x + brdf.y;

} // validated

// Fdez-Agüera's "Multiple-Scattering Microfacet Model for Real-Time Image Based Lighting"
// Approximates multiscattering in order to preserve energy.
// http://www.jcgt.org/published/0008/01/03/
void BRDF_Specular_Multiscattering_Environment(Fragment fragment, vec3 specularColor, float roughness, inout vec3 singleScatter, inout vec3 multiScatter) {

    float dotNV = saturate(dot(fragment.normal, fragment.view));

    vec3 F = F_Schlick(specularColor, dotNV);
    vec2 brdf = integrateSpecularBRDF(dotNV, roughness);
    vec3 FssEss = F * brdf.x + brdf.y;

    float Ess = brdf.x + brdf.y;
    float Ems = 1.0 - Ess;

    // Paper incorrect indicates coefficient is PI/21, and will
    // be corrected to 1/21 in future updates.
    vec3 Favg = specularColor + (1.0 - specularColor) * 0.047619; // 1/21
    vec3 Fms = FssEss * Favg / (1.0 - Ems * Favg);

    singleScatter += FssEss;
    multiScatter += Fms * Ems;

}

float G_BlinnPhong_Implicit(/* float dotNL, float dotNV */) {

    // fragment term is (n dot l)(n dot v) / 4(n dot l)(n dot v)
    return 0.25;

}

float D_BlinnPhong(float shininess, float dotNH) {

    return rPI * (shininess * 0.5 + 1.0) * pow(dotNH, shininess);

}

vec3 BRDF_Specular_BlinnPhong(vec3 l, Fragment fragment, vec3 specular, float shininess) {

    vec3 halfDir = normalize(l + fragment.view);

    //float dotNL = saturate(dot(fragment.normal, l));
    //float dotNV = saturate(dot(fragment.normal, fragment));
    float dotNH = saturate(dot(fragment.normal, halfDir));
    float dotLH = saturate(dot(l, halfDir));

    vec3 F = F_Schlick(specular, dotLH);

    float G = G_BlinnPhong_Implicit(/* dotNL, dotNV */);

    float D = D_BlinnPhong(shininess, dotNH);

    return F * (G * D);

} // validated

// source: http://simonstechblog.blogspot.ca/2011/12/microfacet-brdf.html
float GGXRoughnessToBlinnExponent(float ggxRoughness) {
    return (2.0 / pow2(ggxRoughness + 0.0001) - 2.0);
}

float BlinnExponentToGGXRoughness(float blinnExponent) {
    return sqrt(2.0 / (blinnExponent + 2.0));
}

#endif
