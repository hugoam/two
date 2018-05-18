#ifdef EMISSIVE
	vec3 emission_tex = sample_material_texture(s_emissive, fragment.uv).rgb;
	vec3 emission = (u_emissive.rgb + emission_tex) * u_emissive_energy;
#else
	vec3 emission = vec3_splat(0.0);
#endif
