$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal
#include <encode.sh>
#include <pbr/pbr.sh>
#include <pbr/light.sh>
#include <pbr/light_brdf_three.sh>
#include <pbr/radiance.sh>
#define s_thickness s_user0
struct TranslucentMaterial
{
	PhongMaterial phong;
	UserMaterial scatter;
};
void direct_scatter(vec3 energy, vec3 l, Fragment fragment, TranslucentMaterial mat, inout vec3 diffuse, inout vec3 specular)
{
direct_blinn_phong(energy, l, fragment, mat.phong, diffuse, specular);
float power       = mat.scatter.p0.x;
float scale       = mat.scatter.p0.y;
float distortion  = mat.scatter.p0.z;
float ambient     = mat.scatter.p0.w;
float attenuation = mat.scatter.p1.x;
vec3  color       = mat.scatter.p1.yzw;
vec3 thickness = color * texture2D(s_thickness, fragment.uv).r;
vec3 scatteringHalf = normalize(l + (fragment.normal * distortion));
float scatteringDot = pow(saturate(dot(fragment.view, -scatteringHalf)), power) * scale;
vec3 scatteringIllu = (scatteringDot + ambient) * thickness;
diffuse += scatteringIllu * attenuation * energy;
}
#define direct_brdf direct_scatter
void main()
{
#include <pbr/fs_fragment.sh>
#include <pbr/fs_phong_material.sh>
TranslucentMaterial material;
material.phong = matphong;
material.scatter = matuser;
#include <pbr/fs_phong.sh>
#include <pbr/fs_out_pbr.sh>
}
