    if(u_skylight)
    {
        Skylight skylight = read_skylight();
        diffuse += light_hemisphere(skylight.direction, skylight.ground, skylight.color, fragment);
    }

    if(u_lightmap)
    {
        vec4 lightmap = sample_material_texture(s_lightmap, fragment.uv2);
        //diffuse += lightmap.rgb;
        diffuse += decodeHDR(lightmap) * PI;
        //specular = trace_specular(s_gi_probe, cone.pos, cone.refl, material.roughness * material.roughness, u_gi_probe_bias) * u_gi_probe_specular;
    }
#ifdef GI_CONETRACE
    else if(u_gi_conetrace)
    {
        ConeStart cone = cone_start(fragment.position, fragment.normal);
        trace_gi_probe(cone, material.roughness, diffuse, specular);
        //gl_FragColor = vec4(gi_probe_debug(fragment.position, 0.0), 1.0);
        //gl_FragColor = vec4(debug_trace_diffuse(s_gi_probe, mul(u_gi_probe_transform, vec4(fragment.normal, 0.0)).xyz), 1.0);
        //return;
    }
#endif

    if(u_occlusion)
        diffuse *= matlit.ao;

    //apply_reflections(specular, ambient);
