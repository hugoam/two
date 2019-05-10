
$input v_view, v_normal

#include <encode.sh>
#include <pbr/pbr.sh>
#include <pbr/light.sh>
#define BRDF_BLINN_PHONG
#include <pbr/light_brdf_three.sh>
#include <pbr/radiance.sh>
#include <fog.sh>

void main()
{
    Fragment fragment;
    fragment.coord = gl_FragCoord;
    fragment.position = v_view.xyz;
    fragment.view = normalize(-v_view.xyz);
    fragment.normal = normalize(v_normal);
#ifdef DOUBLE_SIDED
    fragment.normal = fragment.normal * (float(gl_FrontFacing) * 2.0 - 1.0);
#endif

#include <pbr/fs_phong_material.sh>
    PhongMaterial material = matphong;

    int zone_index = int(u_state_zone);
    Zone zone = read_zone(zone_index);
        
    vec3 diffuse = vec3_splat(0.0);
    vec3 specular = vec3_splat(0.0);

#include <pbr/fs_indirect.sh>
    diffuse += zone.ambient * PI;
    diffuse *= BRDF_Diffuse_Lambert(matphong.diffuse);

    int i = 0;

    for(i = 0; i < int(u_light_counts[LIGHT_POINT]); i++)
    {
        Light light = read_light(int(u_light_indices[i][LIGHT_POINT]));
        vec3 l = light.position - fragment.position;
        float a = omni_attenuation(l, light);
        direct_brdf(light.energy * a, normalize(l), fragment, material, diffuse, specular);
    }

    #include <pbr/fs_phong_ibl.sh>
    #include <pbr/fs_out_pbr.sh>
    #include <fs_fog_simple.sh>
}
