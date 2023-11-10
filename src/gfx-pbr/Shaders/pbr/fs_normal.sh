#ifdef NORMAL_MAP
    vec3 normal_tex = sample_material_texture(s_normal, fragment.uv).rgb;
    normal_tex = normal_tex * 2.0 - 1.0;
    normal_tex.z = sqrt(1.0 - dot(normal_tex.xy, normal_tex.xy));

    // mikktspace formula
    vec3 normal_offset = v_tangent * normal_tex.x + v_binormal * normal_tex.y + v_normal * normal_tex.z;
    fragment.normal = normalize(mix(fragment.normal, normal_offset, matlit.normal_scale));
#else
    fragment.normal *= matlit.normal_scale;
#endif
