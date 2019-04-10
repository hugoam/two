$input v_uv0, v_scale
#include <common.sh>
#include <convert.sh>
void main()
{
	vec4 color = texture2D(s_color, v_uv0);
   vec3 hsl = hsl_to_rgb(vec3(v_scale / 5.0, 1.0, 0.5));
	gl_FragColor = vec4(color.rgb * hsl.rgb, color.a);
	if (color.a < 0.5) discard;
}
