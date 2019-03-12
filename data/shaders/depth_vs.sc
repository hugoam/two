#ifdef SKELETON
#define SKELETON_INPUTS , a_indices, a_weight
#else
#define SKELETON_INPUTS
#endif

#ifdef INSTANCING
#define INSTANCING_INPUTS , i_data0, i_data1, i_data2, i_data3
#else
#define INSTANCING_INPUTS
#endif

$input a_position, a_normal, a_texcoord0 SKELETON_INPUTS INSTANCING_INPUTS
$output v_position, v_uv0

#include <common.sh>
#include <skeleton.sh>
#include <depth.sh>

void main()
{
#include "modelview.sh"

	vec3 vertex = mul(modelView, vec4(a_position.xyz, 1.0)).xyz;
	vec3 normal = mul(modelView, vec4(a_normal, 0.0)).xyz;
    
    int material_index = int(u_state_material);
    BaseMaterial basic = read_base_material(material_index);
    
	v_uv0 = (a_texcoord0 * basic.uv0_scale) + basic.uv0_offset;
    
	render_depth(normal, vertex);

    v_position = mul(u_proj, vec4(vertex, 1.0));
    //v_position.z = 0.0;
    gl_Position = v_position;
}
