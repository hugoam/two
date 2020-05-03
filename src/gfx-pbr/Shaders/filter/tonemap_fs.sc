$input v_uv0

#include <filter.sh>
#include <tonemap.sh>

#define s_source s_source_0
#define s_color_lut s_source_1
#define s_exposure s_source_2

uniform vec4 u_tonemap_modes;
#define u_tonemap_mode int(u_tonemap_modes.x)

uniform vec4 u_tonemap_opts;
#define u_to_gamma  bool(u_tonemap_opts.x)
#define u_color_lut bool(u_tonemap_opts.y)
#define u_bcs       bool(u_tonemap_opts.z)

uniform vec4 u_exposure_p0;
#define u_exposure u_exposure_p0.x
#define u_exposure_white u_exposure_p0.y
#define u_exposure_grey u_exposure_p0.z

uniform vec4 u_tonemap_bcs;
#define u_brightness u_tonemap_bcs.x
#define u_contrast   u_tonemap_bcs.y
#define u_saturation u_tonemap_bcs.z

void main()
{
    ivec2 ifrag_coord = ivec2(gl_FragCoord.xy);
    //vec3 color = texelFetch(s_source, ifrag_coord, 0).rgb;
    vec3 color = texture2DLod(s_source, v_uv0, 0.0).rgb;
    
#ifdef AUTO_EXPOSURE
	color /= texelFetch(s_exposure, ivec2(0,0), 0).r / auto_exposure_grey;
#endif

    if(u_tonemap_mode == 0)
    {
        color *= u_exposure;
    }
    else if(u_tonemap_mode == 1)
    {
        //color = to_reindhart(color, u_exposure_white);
        color *= u_exposure;
        color = saturate(color / (vec3_splat(1.0) + color));
    }
    else if(u_tonemap_mode == 2)
    {
        color = to_filmic(color, u_exposure_white);
    }
    else if(u_tonemap_mode == 3)
    {
        color = toAcesFilmic(color);
    }

    if(u_to_gamma)
    {
        //color = toGammaAccurate(color);
        //color = LinearToGamma(color, 2.0);
        color = pow(color, vec3_splat(1.0 / 2.0));
    }
    
    if(u_bcs)
    {
        color = mix(vec3_splat(0.0), color, u_brightness);
        color = mix(vec3_splat(0.5), color, u_contrast);
        color = mix(vec3_splat(dot(vec3_splat(1.0), color) * 0.33333), color, u_saturation);
    }

    if(u_color_lut)
    {
        color.r = texture2D(s_color_lut, vec2(color.r, 0.0)).r;
        color.g = texture2D(s_color_lut, vec2(color.g, 0.0)).g;
        color.b = texture2D(s_color_lut, vec2(color.b, 0.0)).b;
    }

	gl_FragColor = vec4(color.rgb, 1.0);
}
