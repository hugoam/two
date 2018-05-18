$input a_position, a_normal
$output v_position, v_view, v_normal

#include "common.sh"

void main()
{
	vec3 pos = a_position;
	vec3 normal = a_normal.xyz*2.0 - 1.0;

	gl_Position = mul(u_modelViewProj, vec4(pos, 1.0));
	v_position = gl_Position;
	v_view = mul(u_modelView, vec4(pos, 1.0)).xyz;

	v_normal = mul(u_modelView, vec4(normal, 0.0)).xyz;
}
