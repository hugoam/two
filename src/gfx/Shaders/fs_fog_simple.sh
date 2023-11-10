#ifdef FOG
    #ifdef FOG_EXP2
        float fog_amount = 1.0 - saturate(exp2(-u_fog_density * u_fog_density * -v_view.z * -v_view.z * LOG2));
    #else
        float fog_amount = smoothstep(u_fog_near, u_fog_far, -v_view.z);
    #endif
    gl_FragColor.rgb = mix(gl_FragColor.rgb, u_fog_color, fog_amount);
#endif
