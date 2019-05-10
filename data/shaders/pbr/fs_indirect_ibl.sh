#ifdef RADIANCE_ENVMAP
    diffuse += ibl_diffuse(fragment.normal) * PI * zone.energy;
#ifdef REFRACTION
    vec3 envspec = ibl_refract(fragment.view, fragment.normal, material.refraction, env_brdf_miplevel(material));
#else
    vec3 envspec = ibl_reflect(fragment.view, fragment.normal, env_brdf_miplevel(material));
#endif
    specular += envspec * zone.radiance * zone.energy;
#endif
    diffuse += zone.ambient * PI;

