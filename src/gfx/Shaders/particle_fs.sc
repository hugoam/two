$input v_color, v_uv0, v_particle

#include <common.sh>

SAMPLER2D(s_texColor, 0);

void main()
{
	//vec4 rgba = texture2D(s_texColor, v_uv0).xxxx;
	vec4 rgba = texture2D(s_texColor, v_uv0).rgbr;
    
	rgba.rgb = rgba.rgb * v_color.rgb * rgba.a * v_color.a;
	rgba.a   = rgba.a * v_color.a * (1.0f - v_particle.x);
	gl_FragColor = rgba;
}
