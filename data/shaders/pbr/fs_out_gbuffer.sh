    float emissive = float(emission.a > 0.0);
    vec3 colour = material.albedo * (1.0 - emissive) + emission.rgb * emissive;
    gl_FragData[0] = vec4(fragment.position, fragment.coord.z);
    gl_FragData[1] = vec4(fragment.normal, 1.0);
    gl_FragData[2] = vec4(colour, emissive);
    gl_FragData[3] = vec4(material.roughness, material.metallic, material.specular, 1.0);
