#ifdef MRT
    gl_FragData[0] = vec4(material.emission.rgb + diffuse + ambient, material.alpha);
    gl_FragData[1] = vec4(specular, material.metallic);
    gl_FragData[2] = vec4(normalize(fragment.normal) * 0.5 + 0.5, material.roughness);
#ifdef SUBSURFACE
    gl_FragData[3] = subsurface;
#endif

#else
    gl_FragColor = vec4(material.emission.rgb + ambient + diffuse + specular, material.alpha);
    //gl_FragColor = vec4(normalize(fragment.normal) * 0.5 + 0.5, 1.0);
    //gl_FragColor = vec4(v_color.rgb, 1.0);
#endif

#if 0
    Light light = read_light(int(u_light_indices[1][LIGHT_POINT]));
    vec3 coord = mul(u_shadow_matrix[light.shadow.index], vec4(fragment.position, 1.0)).xyz;
    vec2 texelSize = vec2(1.0, 1.0) / u_shadow_atlas_size;
    float depth = (length(coord) - 0.01) / (light.range - 0.01);
    vec3 dir = normalize(coord);
    float s = unpackRgbaToFloat(texture2D(s_shadow_atlas, atlasCubeUV(light.shadow.atlas_slot, light.shadow.atlas_subdiv, dir, texelSize.y)));
    gl_FragColor = vec4(vec3_splat(s - depth), 1.0);
    gl_FragColor = vec4(vec3_splat(s), 1.0);
    //gl_FragColor = vec4(vec3_splat(depth), 1.0);
    gl_FragColor = texture2D(s_shadow_atlas, atlasCubeUV(light.shadow.atlas_slot, light.shadow.atlas_subdiv, dir, texelSize.y));
#endif
