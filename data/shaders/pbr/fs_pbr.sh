    // metallic energy conservation
    vec3 dielectric = vec3_splat(0.034) * material.specular * 2.0;
    material.f0 = mix(dielectric, material.albedo, material.metallic);
    material.albedo = mix(material.albedo, vec3_splat(0.0), material.metallic);

    fragment.NoV = saturate(dot(fragment.normal, fragment.view));
    
    // Radiance radiance;
    vec3 specular = vec3_splat(0.0);
    vec3 diffuse = vec3_splat(0.0);
    vec3 ambient = vec3_splat(0.0);

    int zone_index = int(u_state_zone);
    Zone zone = read_zone(zone_index);
    
#ifdef RADIANCE_ENVMAP
    ambient += radiance_ambient(zone, fragment.normal);
    specular += radiance_reflection(zone, fragment.view, fragment.normal, material.roughness);
#else
    ambient += zone.radiance_color * zone.ambient;
#endif

#if defined LIGHTMAP
    vec4 lightmap = sample_material_texture(s_lightmap, fragment.uv2);
    //ambient = lightmap.rgb;
    ambient = decodeHDR(lightmap);
    //specular = trace_specular(s_gi_probe, cone.pos, cone.refl, material.roughness * material.roughness, u_gi_probe_bias) * u_gi_probe_specular;
#elif defined GI_CONETRACE
    ConeStart cone = cone_start(fragment.position, fragment.normal);
    trace_gi_probe(cone, material.roughness, ambient,  specular);
    //gl_FragColor = vec4(gi_probe_debug(fragment.position, 0.0), 1.0);
    //gl_FragColor = vec4(debug_trace_diffuse(s_gi_probe, mul(u_gi_probe_transform, vec4(fragment.normal, 0.0)).xyz), 1.0);
    //return;
#endif

#ifdef AMBIENT_OCCLUSION
    ambient *= material.ao;
#endif
    ambient *= material.albedo;

    //apply_reflections(specular, ambient);
    
#ifdef DIRECT_LIGHT
	direct_light(fragment, material, diffuse, specular);
#endif

#ifdef CLUSTERED
    apply_cluster_lights(fragment, material, diffuse, specular);
#else
    apply_lights(fragment, material, diffuse, specular);
#endif
    
#ifdef DIFFUSE_TOON
    specular *= material.specular * material.metallic * material.albedo * 2.0;
#else
    specular *= brdf_specular_term(fragment, material);
#endif

#ifdef FOG
    //apply_fog(fragment, material.emission, ambient, diffuse, specular);
    apply_fog_0(fragment, material.emission.rgb);
#endif
