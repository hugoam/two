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
$output v_position, v_texcoord0

#include <common.sh>
#include <skeleton.sh>
#include <depth.sh>

void main()
{
#include "modelview.sh"

    vec3 vertex = mul(model, vec4(a_position, 1.0)).xyz;
    vec3 normal = mul(model, vec4(a_normal, 0.0)).xyz;

    int material_index = int(u_state_material);
    BaseMaterial basic = read_base_material(material_index);
    
    v_texcoord0 = vec4((a_texcoord0.xy * basic.uv0_scale) + basic.uv0_offset, 0.0, 0.0);

    //render_depth(normal, vertex);

    v_position = vec4(vertex, 1.0);
    
    gl_Position = mul(u_viewProj, vec4(vertex, 1.0));
}
