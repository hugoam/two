
    int zone_index = int(u_state_zone);
    Zone zone = read_zone(zone_index);
    
    vec3 diffuse = vec3_splat(0.0);
    vec3 specular = vec3_splat(0.0);

#include "fs_indirect.sh"
    diffuse += zone.ambient * PI;
    diffuse *= BRDF_Diffuse_Lambert(material.diffuse);

    vec3 direct = vec3_splat(0.0);
#ifdef DOUBLE_SIDED
    direct = (gl_FrontFacing) ? v_light : v_light_back;
#else
    direct = v_light;
#endif
    direct *= BRDF_Diffuse_Lambert(material.diffuse); // * getShadowMask();
    diffuse += direct;

#include "fs_phong_ibl.sh"
