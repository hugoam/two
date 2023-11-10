
    int zone_index = int(u_state_zone);
    Zone zone = read_zone(zone_index);
    
    // metallic energy conservation
    vec3 dielectric = vec3_splat(0.034) * material.specular * 2.0;
    material.f0 = mix(dielectric, material.albedo, material.metallic);
    material.albedo = mix(material.albedo, vec3_splat(0.0), material.metallic);

    fragment.NoV = dot(fragment.normal, fragment.view);
    fragment.cNoV = max(dot(fragment.normal, fragment.view), 0.0);

    // Radiance radiance;
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

#if DIFFUSE_MODE == DIFFUSE_TOON
    specular *= material.specular * material.metallic * material.albedo * 2.0;
#endif
