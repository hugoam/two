//$input v_color, v_texcoord0
$input v_view, v_position, v_normal, v_tangent, v_color, v_texcoord0, v_texcoord1, v_binormal

#include <common.sh>

SAMPLER2D(s_fresnel, 0);

uniform vec4 u_fresnel_value;
uniform vec4 u_fresnel_params;
#define u_fresnel_bias u_fresnel_params.x
#define u_fresnel_scale u_fresnel_params.y
#define u_fresnel_power u_fresnel_params.z
#define u_fresnel_texture u_fresnel_params.w

void main()
{
    vec3 I = normalize(v_view.xyz);
    vec3 N = normalize(v_normal);
    
    float R = u_fresnel_bias + u_fresnel_scale * pow(1.0 + dot(I, N), u_fresnel_power);
    R = max(0.0 , min(1.0 , R));
    
	vec4 color_tex = toLinear(texture2D(s_fresnel, v_texcoord0.xy * 2.0));
    color_tex.a = color_tex.r;
    
    vec4 transparent = vec4_splat(0.0);
	gl_FragColor = mix(transparent, v_color * color_tex * u_fresnel_value, R);
	gl_FragColor = mix(transparent, color_tex * u_fresnel_value, R);
	//gl_FragColor = vec4(normalize(N) * 0.5 + 0.5, 1.0);
}
