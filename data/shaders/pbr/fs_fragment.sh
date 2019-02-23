    Fragment fragment;
    fragment.coord = gl_FragCoord;
    fragment.position = v_view.xyz;
    fragment.view = normalize(-v_view.xyz);
    fragment.normal = normalize(v_normal);
    fragment.binormal = normalize(v_binormal);
    fragment.tangent = normalize(v_tangent);
    fragment.uv = v_texcoord0.xy;
    fragment.uv2 = v_texcoord1.xy;
    fragment.color = v_color;
    
#if BGFX_SHADER_LANGUAGE_HLSL
    fragment.coord.z = (fragment.coord.z + 1.0) / 2.0;
    fragment.depth = gl_FragCoord.w;
#else
    fragment.depth = -fragment.position.z;
#endif

#ifdef DOUBLE_SIDED
    fragment.normal = fragment.normal * ( float( gl_FrontFacing ) * 2.0 - 1.0 );
#endif
    
    //fragment.coord.z = fragment.depth;
