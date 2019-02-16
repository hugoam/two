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

$input a_position, a_normal, a_color0 SKELETON_INPUTS INSTANCING_INPUTS
$output v_position, v_color

#include <common.sh>
#include <skeleton.sh>
#include <depth.sh>

void main()
{
#include "modelview.sh"

	vec3 vertex = mul(modelView, vec4(a_position, 1.0)).xyz;
	vec3 normal = mul(modelView, vec4(a_normal, 0.0)).xyz;
    
	render_depth(normal, vertex);

    v_color = a_color0;
    v_position = mul(u_proj, vec4(vertex, 1.0));
    gl_Position = v_position;
}
