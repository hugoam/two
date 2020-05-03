$input v_uv0

#include <common.sh>
#include <encode.sh>
#include <filter.sh>
#include <encode.sh>
#include <spherical.sh>

CONST(float) depth_value_pow = 1.0;

void main()
{
#if defined SOURCE_0_CUBE
    vec3 dir = invertedSphericalUV(v_uv0);
	vec4 color = textureCubeLod(s_source_0, dir, float(u_source_0_level));
#elif defined SOURCE_0_ARRAY
	vec4 color = texture2DArray(s_source_0, vec3(v_uv0, u_source_0_level));
#elif defined TEXEL_COPY
	ivec2 ifrag_coord = ivec2(gl_FragCoord.xy);
	vec4 color = texelFetch(s_source_0, ifrag_coord, 0).rgba;
#else
	vec4 color = texture2DLod(s_source_0, v_uv0, u_source_0_level);
#endif

    if(u_source_depth)
    {
        color = vec4(vec3_splat(pow(color.r, depth_value_pow)), 1.0);
    }

    if(u_unpack_depth)
    {
        float depth = unpackRgbaToFloat(color);
        color = vec4(vec3_splat(pow(depth, depth_value_pow)), 1.0);
    }
    
#ifdef TO_SRGB
	color.rgb = toGammaAccurate(color.rgb);
#endif

#ifdef TO_LINEAR
	color.rgb = toLinear(color.rgb);
#endif

	gl_FragColor = u_multiply * color;
#ifdef FILTER_DEBUG_UV
	gl_FragColor = vec4(v_uv0, 1.0, 1.0);
#endif
}

