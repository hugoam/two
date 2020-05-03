    if(u_occlusion)
    {
#ifdef AO_ON_UV2
        matlit.ao = sample_material_texture(s_ambient_occlusion, fragment.uv2).r;
#else
        matlit.ao = sample_material_texture(s_ambient_occlusion, fragment.uv).r;
#endif
    }
