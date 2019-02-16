#ifdef EMISSIVE
	vec3 emission_tex = sample_material_texture(s_emissive, fragment.uv).rgb;
	emission = vec4((pbr.emissive + emission_tex) * pbr.emissive_energy, pbr.emissive_energy);
#endif
