$input v_uv0

#include <filter.sh>
#include <tonemap.sh>

#define s_source s_source_0
#define s_color_lut s_source_1
#define s_exposure s_source_2

uniform vec4 u_exposure_p0;
#define u_exposure u_exposure_p0.x
#define u_exposure_white u_exposure_p0.y
#define u_exposure_grey u_exposure_p0.z

uniform vec4 u_tonemap_bcs;
#define u_brightness u_tonemap_bcs.x
#define u_contrast u_tonemap_bcs.y
#define u_saturation u_tonemap_bcs.z

void main()
{
    ivec2 ifrag_coord = ivec2(gl_FragCoord.xy);
    //vec3 color = texelFetch(s_source, ifrag_coord, 0).rgb;
    vec3 color = texture2DLod(s_source, v_uv0, 0.0).rgb;
    
#ifdef AUTO_EXPOSURE
	color /= texelFetch(s_exposure, ivec2(0,0), 0).r / auto_exposure_grey;
#endif

#if TONEMAP_MODE == 0
    color *= u_exposure;
#elif TONEMAP_MODE == 1
    //color = to_reindhart(color, u_exposure_white);
    color *= u_exposure;
    color = saturate(color / (vec3_splat(1.0) + color));
#elif TONEMAP_MODE == 2
    color = to_filmic(color, u_exposure_white);
#elif TONEMAP_MODE == 3
    color = toAcesFilmic(color);
#endif

#ifdef TO_GAMMA
    //color = toGammaAccurate(color);
    //color = LinearToGamma(color, 2.0);
    color = pow(color, vec3_splat(1.0 / 2.0));
#endif
    
#ifdef ADJUST_BCS
	color = mix(vec3_splat(0.0), color, u_brightness);
	color = mix(vec3_splat(0.5), color, u_contrast);
	color = mix(vec3_splat(dot(vec3_splat(1.0), color) * 0.33333), color, u_saturation);
#endif

#ifdef COLOR_LUT
	color.r = texture2D(s_color_lut, vec2(color.r, 0.0)).r;
	color.g = texture2D(s_color_lut, vec2(color.g, 0.0)).g;
	color.b = texture2D(s_color_lut, vec2(color.b, 0.0)).b;
#endif

	gl_FragColor = vec4(color.rgb, 1.0);
}
