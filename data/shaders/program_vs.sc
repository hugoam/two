$input a_position, a_color0
$output v_color

#include <common.sh>

void main()
{
	v_color = a_color0;
	gl_Position = u_modelViewProj * vec4(a_position.xyz, 1.0);

}
