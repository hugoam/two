#ifdef ANISOTROPY
    vec3 anisotropy_tex = sample_material_texture(s_anisotropy, fragment.uv).rga;
    material.anisotropy = matpbr.anisotropy * anisotropy_tex.b;

    if (anisotropy > 0.01) {
        vec2 flow = anisotropy_tex.rg * 2.0 - 1.0;
        
        mat3 rotation = mat3(fragment.tangent, fragment.binormal, fragment.normal);
        fragment.tangent = normalize(rotation * vec3(flow.x, flow.y, 0.0));
        fragment.binormal = normalize(rotation * vec3(-flow.y, flow.x, 0.0));
    }
#endif
