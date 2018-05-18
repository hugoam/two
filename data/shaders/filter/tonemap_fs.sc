$input v_texcoord0

#include "filter.sh"

#define s_source s_source_0
#define s_color_correction s_source_1
#define s_exposure s_source_2

uniform vec4 u_exposure_params;
#define u_exposure u_exposure_params.x
#define u_exposure_white u_exposure_params.y
#define u_exposure_grey u_exposure_params.z

uniform vec4 u_tonemap_bcs;
#define u_brightness u_tonemap_bcs.x
#define u_contrast u_tonemap_bcs.y
#define u_saturation u_tonemap_bcs.z

void main()
{
	ivec2 ifrag_coord = ivec2(gl_FragCoord.xy);
	//vec3 color = texelFetch(s_source, ifrag_coord, 0).rgb;
    vec3 color = texture2DLod(s_source, v_texcoord0.xy, 0.0).rgb;
    
#ifdef AUTO_EXPOSURE
	color /= texelFetch(s_exposure, ivec2(0,0), 0).r / auto_exposure_grey;
#endif
	color *= u_exposure;

#if TONEMAP_MODE == 1
    color.rgb = to_reindhart(color.rgb, u_exposure_white);
#elif TONEMAP_MODE == 2
    color.rgb = to_filmic(color.rgb, u_exposure_white);
#elif TONEMAP_MODE == 3
    color.rgb = toAcesFilmic(color.rgb);
#endif

    color.rgb = toGammaAccurate(color.rgb);
    
#ifdef ADJUST_BCS
	color.rgb = mix(vec3_splat(0.0), color.rgb, u_brightness);
	color.rgb = mix(vec3_splat(0.5), color.rgb, u_contrast);
	color.rgb = mix(vec3_splat(dot(vec3_splat(1.0), color.rgb) * 0.33333), color.rgb, u_saturation);
#endif

#ifdef COLOR_CORRECTION
	color.r = texture2D(s_color_correction, vec2(color.r, 0.0)).r;
	color.g = texture2D(s_color_correction, vec2(color.g, 0.0)).g;
	color.b = texture2D(s_color_correction, vec2(color.b, 0.0)).b;
#endif

	gl_FragColor = vec4(color.rgb, 1.0);
}
