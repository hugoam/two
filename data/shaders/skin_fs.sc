$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal
#include <encode.sh>
#include <pbr/pbr.sh>
#include <pbr/light.sh>
#include <pbr/light_brdf_three.sh>
#include <pbr/radiance.sh>
#define s_blur1 s_user0
#define s_blur2 s_user1
#define s_blur3 s_user2
#define s_blur4 s_user3
#define s_beckmann s_user4
float fresnelReflectance(vec3 H, vec3 V, float F0)
{
float base = 1.0 - dot(V, H);
float exponential = pow(base, 5.0);
return exponential + F0 * (1.0 - exponential);
}
float KS_Skin_Specular(vec3 N, vec3 L, vec3 V, float m, float rho_s)
{
float result = 0.0;
float ndotl = dot(N, L);
if(ndotl > 0.0)
{
vec3 h = L + V;
vec3 H = normalize(h);
float ndoth = dot(N, H);
float PH = pow(2.0 * texture2D(s_beckmann, vec2(ndoth, m)).x, 10.0);
float F = fresnelReflectance(H, V, 0.028);
float frSpec = max(PH * F / dot(h, h), 0.0);
result = ndotl * rho_s * frSpec;
}
return result;
}
struct SkinMaterial
{
	PhongMaterial phong;
	UserMaterial skin;
};
void direct_skin(vec3 energy, vec3 l, Fragment fragment, SkinMaterial mat, inout vec3 diffuse, inout vec3 specular)
{
float diffuseWeight = max(dot(fragment.normal, l), 0.0);
diffuse += energy * diffuseWeight;
#ifndef PASS_DIFFUSE
float roughness  = mat.skin.p0.x;
float brightness = mat.skin.p0.y;
float specularWeight = KS_Skin_Specular(fragment.normal, l, fragment.view, roughness, brightness);
specular += energy * mat.phong.specular * specularWeight;
#endif
}
#define direct_brdf direct_skin
void main() {
#include <pbr/fs_fragment.sh>
#include <pbr/fs_phong_material.sh>
SkinMaterial material;
material.phong = matphong;
material.skin = matuser;
vec4 texDiffuse = sample_material_texture(s_diffuse, fragment.uv);
texDiffuse *= texDiffuse;
vec4 diffuseColor = vec4(matphong.diffuse, 1.0) * texDiffuse;
#include <pbr/fs_phong.sh>
vec3 light = diffuseColor.rgb * (diffuse + specular);
#ifdef PASS_DIFFUSE
light = sqrt(light);
#else
#ifdef VERSION1
vec3 color = sqrt(light);
#else
vec3 color = light;
#endif
light = vec3(vec3(0.22,  0.437, 0.635) * color + 
vec3(0.101, 0.355, 0.365) * texture2D(s_blur1, v_uv0).rgb + 
vec3(0.119, 0.208, 0.0)   * texture2D(s_blur2, v_uv0).rgb + 
vec3(0.114, 0.0,   0.0)   * texture2D(s_blur3, v_uv0).rgb + 
vec3(0.444, 0.0,   0.0)   * texture2D(s_blur4, v_uv0).rgb);
light *= sqrt(texDiffuse.xyz);
vec3 ambient = zone.ambient;
light += ambient * matphong.diffuse * texDiffuse.xyz + specular;
#ifndef VERSION1
light = sqrt(light);
#endif
#endif
gl_FragColor = vec4(light, diffuseColor.a);
}
