#ifndef MUD_SHADER_BLUR
#define MUD_SHADER_BLUR

vec4 blur_7(sampler2D tex, vec2 uv, float lod, float k0, float k1, float k2, float k3, float k4, float k5, float k6)
{
	vec2 pixel_size = u_pixel_size * u_source_crop.zw;
	vec4 color = texture2DLod(tex, uv + vec2( 0.0, 0.0) * pixel_size, lod) * k0;
	color +=     texture2DLod(tex, uv + vec2( 1.0, 0.0) * pixel_size, lod) * k1;
	color +=     texture2DLod(tex, uv + vec2( 2.0, 0.0) * pixel_size, lod) * k2;
	color +=     texture2DLod(tex, uv + vec2( 3.0, 0.0) * pixel_size, lod) * k3;
	color +=     texture2DLod(tex, uv + vec2(-1.0, 0.0) * pixel_size, lod) * k4;
	color +=     texture2DLod(tex, uv + vec2(-2.0, 0.0) * pixel_size, lod) * k5;
	color +=     texture2DLod(tex, uv + vec2(-3.0, 0.0) * pixel_size, lod) * k6;
	return color;
}

vec4 blur_5(sampler2D tex, vec2 uv, float lod, float k0, float k1, float k2, float k3, float k4)
{
	vec2 pixel_size = u_pixel_size * u_source_crop.zw;
	vec4 color = texture2DLod(tex, uv + vec2( 0.0,  0.0) * pixel_size, lod) * k0;
	color +=     texture2DLod(tex, uv + vec2( 0.0,  1.0) * pixel_size, lod) * k1;
	color +=     texture2DLod(tex, uv + vec2( 0.0,  2.0) * pixel_size, lod) * k2;
	color +=     texture2DLod(tex, uv + vec2( 0.0, -1.0) * pixel_size, lod) * k3;
	color +=     texture2DLod(tex, uv + vec2( 0.0, -2.0) * pixel_size, lod) * k4;
	return color;
}

#endif
