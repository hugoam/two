#ifndef MUD_SHADER_TRIPLANAR
#define MUD_SHADER_TRIPLANAR

vec4 textureTriplanar(sampler2D tex, vec3 weights, vec3 world_pos)
{
	vec4 color = vec4_splat(0.0);
	color += texture2D(tex, world_pos.xy) * weights.z;
	color += texture2D(tex, world_pos.xz) * weights.y;
	color += texture2D(tex, world_pos.zy * vec2(-1.0,1.0)) * weights.x;
	return color;
}

vec4 sample_material_texture(sampler2D tex, vec2 uv)
{
    return texture2D(tex, uv);
}

#endif
