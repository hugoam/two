$input a_position, a_color0, a_texcoord0
$output v_dir, v_wpos, v_color, v_uv0

#include <common.sh>

uniform mat4 u_skybox_matrix;

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
	v_color = a_color0;
	v_uv0 = a_texcoord0;
    
    float height = tan(u_fov * 0.5);
    vec2 tex = (2.0 * a_texcoord0 - 1.0) * vec2(u_aspect, height);
    v_dir = instMul(u_skybox_matrix, vec4(tex, 1.0, 0.0)).xyz;
    v_wpos = vec3(u_skybox_matrix[0][3], u_skybox_matrix[1][3], u_skybox_matrix[2][3]);
}
