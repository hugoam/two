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

#include <common.sh>
#include <skeleton.sh>

void main()
{
#include "modelview.sh"

	vec3 vertex = mul(modelView, vec4(a_position, 1.0)).xyz;
    gl_Position = mul(u_proj, vec4(vertex, 1.0));
}
