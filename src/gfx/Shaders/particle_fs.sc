$input v_color, v_texcoord0

#include <common.sh>

SAMPLER2D(s_texColor, 0);

void main()
{
	//vec4 rgba = texture2D(s_texColor, v_texcoord0.xy).xxxx;
	vec4 rgba = texture2D(s_texColor, v_texcoord0.xy).rgbr;
    
	rgba.rgb = rgba.rgb * v_color.rgb * rgba.a * v_color.a;
	rgba.a   = rgba.a * v_color.a * (1.0f - v_texcoord0.z);
	gl_FragColor = rgba;
}
