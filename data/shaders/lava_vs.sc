$input a_position, a_texcoord0
$output v_position, v_uv0
#include <common.sh>
void main()
{
	int material_index = int(u_state_material_vertex);
	BaseMaterial basic = read_base_material(material_index);
   v_uv0 = (a_texcoord0 * basic.uv0_scale) + basic.uv0_offset;
	vec4 view = mul(u_modelView, vec4(a_position.xyz, 1.0));
	v_position = mul(u_proj, view);
	gl_Position = v_position;
}
