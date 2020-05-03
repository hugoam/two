
    vec4 emission = vec4_splat(0.0);
    if(u_emissive)
    {
        vec3 emission_tex = sample_material_texture(s_emissive, fragment.uv).rgb;
        emission = vec4((matlit.emissive + emission_tex) * matlit.energy, matlit.energy);
    }
    