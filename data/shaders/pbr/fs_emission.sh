#ifdef EMISSIVE
	vec3 emission_tex = sample_material_texture(s_emissive, fragment.uv).rgb;
	emission = vec4((u_emissive.rgb + emission_tex) * u_emissive_energy, u_emissive_energy);
#endif
