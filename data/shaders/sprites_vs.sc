$input a_position, a_texcoord0, i_data0
$output v_uv0, v_scale
#include <common.sh>
void main()
{
   vec3 i_position = i_data0.xyz;	vec3 timexyz = i_position + vec3_splat(u_time / 2.0);
	float scale =  sin(timexyz.x * 2.1) + sin(timexyz.y * 3.2) + sin(timexyz.z * 4.3);
	v_scale = scale;
	float size = scale * 10.0 + 10.0;
	vec3 view = mul(u_modelView, vec4(i_position, 1.0)).xyz;
	view += a_position.xyz * size;
	v_uv0 = a_texcoord0;
	gl_Position = mul(u_proj, vec4(view, 1.0));
}
