    Fragment fragment;
    fragment.coord = gl_FragCoord;
    fragment.position = v_view.xyz;
    fragment.view = normalize(-v_view.xyz);
    if(u_flat_shaded)
        fragment.normal = normalize(cross(dFdx(v_view), dFdy(v_view)));
    else
        fragment.normal = normalize(v_normal);

    fragment.binormal = normalize(v_binormal);
    fragment.tangent = normalize(v_tangent);

    fragment.uv = v_uv0;
    fragment.uv2 = v_uv1;
    fragment.color = v_color;
    
#if !BGFX_SHADER_LANGUAGE_GLSL
    fragment.coord.z = (fragment.coord.z + 1.0) / 2.0;
#endif

#if BGFX_SHADER_LANGUAGE_HLSL
    fragment.depth = gl_FragCoord.w;
#else
    fragment.depth = -fragment.position.z;
#endif

    if(u_double_sided)
        fragment.normal = fragment.normal * (float(gl_FrontFacing) * 2.0 - 1.0);
    
    //fragment.coord.z = fragment.depth;
