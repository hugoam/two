#ifdef AMBIENT_OCCLUSION
	#ifdef AO_ON_UV2
		material.ao = sample_material_texture(s_ambient_occlusion, fragment.uv2).r;
	#else
		material.ao = sample_material_texture(s_ambient_occlusion, fragment.uv).r;
	#endif
#endif
