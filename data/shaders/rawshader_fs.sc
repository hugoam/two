$input v_position, v_color
#include <common.sh>
void main()
{
	vec4 color = vec4(v_color);
	color.r += sin(v_position.x * 10.0 + u_time) * 0.5;
	gl_FragColor = color;
}
