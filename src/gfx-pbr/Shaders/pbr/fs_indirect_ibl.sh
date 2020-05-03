
    if(u_radiance_envmap)
    {
        diffuse += ibl_diffuse(fragment.normal) * PI * zone.energy;
        vec3 envspec;
        if(u_refraction)
            envspec = ibl_refract(fragment.view, fragment.normal, matlit.refraction, env_brdf_miplevel(material));
        else
            envspec = ibl_reflect(fragment.view, fragment.normal, env_brdf_miplevel(material));
        specular += envspec * zone.radiance * zone.energy;
    }
    diffuse += zone.ambient * PI;

