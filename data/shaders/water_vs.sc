$input a_position
$output v_world, v_mirrored
#include <common.sh>
uniform mat4 u_mirror;
void main() {
	vec4 world = mul(u_model[0], vec4(a_position.xyz, 1.0));
	v_world = world.xyz;
	v_mirrored = mul(u_mirror, world);
	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
}
