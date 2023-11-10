#ifdef MRT
    gl_FragData[0] = vec4(emission.rgb + diffuse, alpha);
    gl_FragData[1] = vec4(specular, material.metallic);
    gl_FragData[2] = vec4(normalize(fragment.normal) * 0.5 + 0.5, material.roughness);
#ifdef SUBSURFACE
    gl_FragData[3] = subsurface;
#endif

#else
    gl_FragColor = vec4(emission.rgb + diffuse + specular, alpha);
    //gl_FragColor = vec4(normalize(fragment.normal) * 0.5 + 0.5, 1.0);
    //gl_FragColor = vec4(ibl_diffuse(fragment.normal) * material.albedo, 1.0);
    //gl_FragColor = vec4(v_color.rgb, 1.0);
#endif
