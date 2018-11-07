// reference: https://learnopengl.com/Advanced-Lighting/Parallax-Mapping

#ifdef DEPTH_MAPPING

#if BGFX_SHADER_LANGUAGE_HLSL
    vec3 view_dir = normalize(mul(mat3(v_tangent, v_binormal, v_normal), fragment.view));
#else
    vec3 view_dir = normalize(mul(transpose(mat3(v_tangent, v_binormal, v_normal)), fragment.view));
#endif

#ifdef DEEP_PARALLAX
    float num_layers = mix(float(8), float(32), abs(dot(vec3(0.0, 0.0, 1.0), view_dir)));
    float layer_depth = 1.0 / num_layers;
    vec2 P = view_dir.xy * u_depth_scale;
    vec2 delta = P / num_layers;
    float depth = texture2D(s_depth, fragment.uv).r;
    float current_depth = 0.0;
    vec2 current_uv = fragment.uv;
    while(current_depth < depth)
    {
        current_uv -= delta;
        depth = texture2DLod(s_depth, current_uv, 0.0).r;
        current_depth += layer_depth;
    }
    vec2 prev_uv = current_uv + delta;
    float after_depth  = depth - current_depth;
    float before_depth = texture2D(s_depth, prev_uv).r - current_depth + layer_depth;
    float weight = after_depth / (after_depth - before_depth);
    fragment.uv = mix(current_uv, prev_uv, weight);
#else
    float depth = texture2D(s_depth, fragment.uv).r;
    fragment.uv -= view_dir.xy / view_dir.z * (depth * u_depth_scale);
#endif

#endif
