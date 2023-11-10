
    int zone_index = int(u_state_zone);
    Zone zone = read_zone(zone_index);

    material.f0 = mix(vec3_splat(DEFAULT_REFLECTANCE), material.albedo, material.metallic);
    material.albedo = material.albedo * (1.0 - material.metallic);
    material.roughness = clamp(material.roughness, 0.04, 1.0);

    //fragment.NoV = dot(fragment.normal, fragment.view);
    //fragment.cNoV = max(dot(fragment.normal, fragment.view), 0.0);

#ifdef BRDF_PHYSICAL
	material.f0 = mix(vec3_splat(MAX_REFLECTANCE * pow2(reflectivity)), material.albedo, material.metallic);
	material.clearCoat = saturate(clearCoat); // Burley clearcoat model
	material.clearCoatRoughness = clamp(clearCoatRoughness, 0.04, 1.0);
#endif

    vec3 diffuse = vec3_splat(0.0);
    vec3 specular = vec3_splat(0.0);

#include "fs_indirect_ibl.sh"
#include "fs_indirect.sh"
    env_brdf(fragment, material, diffuse, specular);

#ifdef CLUSTERED
#include "fs_direct_cluster.sh"
#else
#include "fs_direct.sh"
#endif
