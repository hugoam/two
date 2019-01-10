$input v_texcoord0

#include <common.sh>
#include <filter/filter.sh>

#if defined SOURCE_DEPTH || defined UNPACK_DEPTH
CONST(float) depth_value_pow = 500.0;
#endif

void main()
{
#if defined SOURCE_0_CUBE
	vec4 color = textureCube(s_source_0, normalize(v_texcoord0.xy));
#elif defined SOURCE_0_ARRAY
	vec4 color = texture2DArray(s_source_0, vec3(v_texcoord0.xy, u_source_0_level));
#elif defined TEXEL_COPY
	ivec2 ifrag_coord = ivec2(gl_FragCoord.xy);
	vec4 color = texelFetch(s_source_0, ifrag_coord, 0).rgba;
#else
	vec4 color = texture2DLod(s_source_0, v_texcoord0.xy, u_source_0_level);
#endif

#ifdef SOURCE_DEPTH
	color = vec4(vec3_splat(pow(color.r, depth_value_pow)), 1.0);
#endif

#ifdef UNPACK_DEPTH
    float depth = unpackRgbaToFloat(color);
    color = vec4(vec3_splat(pow(depth, depth_value_pow), 1.0));
#endif

#ifdef TO_SRGB
	color.rgb = toGammaAccurate(color.rgb);
#endif

#ifdef TO_LINEAR
	color.rgb = toLinear(color.rgb);
#endif

	gl_FragColor = color;
#ifdef FILTER_DEBUG_UV
	gl_FragColor = vec4(v_texcoord0.xy, 1.0, 1.0);
#endif
}

