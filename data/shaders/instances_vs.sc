$input a_position, i_data0, i_data1, i_data2, i_data3
$output v_position, v_color
#define i_offset i_data0.xyz
#define i_color i_data1
#define i_rotation_start i_data2
#define i_rotation_end i_data3
#include <common.sh>
void main()
{
	float t = sin(u_time * 0.2);
	vec3 position = i_offset * max(abs(t * 2.0 + 1.0), 0.5) + a_position.xyz;
	vec4 rotation = normalize(mix(i_rotation_start, i_rotation_end, t));
	vec3 vcV = cross(rotation.xyz, position);
	position = vcV * (2.0 * rotation.w) + (cross(rotation.xyz, vcV) * 2.0 + position);
	v_color = i_color;
   v_position = vec4(position, 1.0);
	gl_Position = mul(u_modelViewProj, vec4(position, 1.0));
}
