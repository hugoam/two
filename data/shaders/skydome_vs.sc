$input a_position, a_texcoord0
$output v_world
#include <common.sh>
void main()
{
	vec4 world = mul(u_model[0], vec4(a_position.xyz, 1.0));
	v_world = world.xyz;
	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
}
