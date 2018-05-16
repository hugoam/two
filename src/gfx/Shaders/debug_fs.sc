$input v_color, v_texcoord0

#include <common.sh>

SAMPLER2D(s_color, 0);

void main()
{
	vec4 color_tex = toLinear(texture2D(s_color, v_texcoord0.xy));
	gl_FragColor.rgb = v_color * color_tex.rgb;
}
