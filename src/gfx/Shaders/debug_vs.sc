$input a_position, a_color0, a_texcoord0
$output v_color, v_uv0

#include <common.sh>

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
	v_color = a_color0;
	v_uv0 = a_texcoord0;
}
