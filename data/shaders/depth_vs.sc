#ifdef SKELETON
#define SKELETON_INPUTS , a_indices, a_weight
#else
#define SKELETON_INPUTS
#endif

#ifdef MORPHTARGET
#define MORPHTARGET_INPUTS , a_texcoord2, a_texcoord3, a_texcoord4, a_texcoord5
#else
#define MORPHTARGET_INPUTS
#endif

#ifdef INSTANCING
#define INSTANCING_INPUTS , i_data0, i_data1, i_data2, i_data3
#else
#define INSTANCING_INPUTS
#endif

$input a_position, a_normal, a_texcoord0 SKELETON_INPUTS INSTANCING_INPUTS MORPHTARGET_INPUTS
$output v_position, v_uv0

#include <common.sh>
#include <skeleton.sh>
#include <depth.sh>

#define a_morph0 a_texcoord2
#define a_morph1 a_texcoord3
#define a_morph2 a_texcoord4
#define a_morph3 a_texcoord5

void main()
{
#include "modelview.sh"

    vec3 position = a_position.xyz;
    
#ifdef MORPHTARGET
    position += a_morph0 * u_morph_weights[0];
    position += a_morph1 * u_morph_weights[1];
    position += a_morph2 * u_morph_weights[2];
    position += a_morph3 * u_morph_weights[3];
#endif

	vec3 vertex = mul(modelView, vec4(position, 1.0)).xyz;
	vec3 normal = mul(modelView, vec4(a_normal, 0.0)).xyz;
    
    int material_index = int(u_state_material_vertex);
    BaseMaterial basic = read_base_material(material_index);
    
	v_uv0 = (a_texcoord0 * basic.uv0_scale) + basic.uv0_offset;
    
	render_depth(normal, vertex);

    v_position = mul(u_proj, vec4(vertex, 1.0));
    //v_position.z = 0.0;
    gl_Position = v_position;
}
