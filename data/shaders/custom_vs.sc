$input a_position, a_texcoord0
$output v_uv0
#include <filter.sh>
void main()
{
	int material_index = int(u_state_material_vertex);
	BaseMaterial basic = read_base_material(material_index);
	
   v_uv0 = (a_texcoord0 * basic.uv0_scale) + basic.uv0_offset;
	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
}
