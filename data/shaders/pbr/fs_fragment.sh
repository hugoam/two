    Fragment fragment;
    fragment.coord = gl_FragCoord;
    fragment.position = v_view.xyz;
    fragment.view = normalize(-v_view.xyz);
#ifdef FLAT_SHADED
    fragment.normal = normalize(cross(dFdx(v_view), dFdy(v_view)));
#else
    fragment.normal = normalize(v_normal);
#endif
#ifdef ANISOTROPY
    fragment.binormal = normalize(v_binormal);
    fragment.tangent = normalize(v_tangent);
#endif
    fragment.uv = v_uv0;
    fragment.uv2 = v_uv1;
    fragment.color = v_color;
    
#if BGFX_SHADER_LANGUAGE_HLSL
    fragment.coord.z = (fragment.coord.z + 1.0) / 2.0;
    //fragment.coord.z = (fragment.coord.z + 0.5) / 2.0;
    fragment.depth = gl_FragCoord.w;
#else
    fragment.depth = -fragment.position.z;
#endif

#ifdef DOUBLE_SIDED
    fragment.normal = fragment.normal * (float(gl_FrontFacing) * 2.0 - 1.0);
#endif
    
    //fragment.coord.z = fragment.depth;
