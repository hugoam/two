
    int zone_index = int(u_state_zone);
    Zone zone = read_zone(zone_index);
    
    vec3 diffuse = vec3_splat(0.0);
    vec3 specular = vec3_splat(0.0);

#include "fs_indirect.sh"
    diffuse += zone.ambient * PI;
    diffuse *= BRDF_Diffuse_Lambert(matphong.diffuse);
    
#ifdef CLUSTERED
#include "fs_direct_cluster.sh"
#else
#include "fs_direct.sh"
#endif

#include "fs_phong_ibl.sh"
