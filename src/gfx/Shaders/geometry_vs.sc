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

$input a_position, a_normal, a_tangent, a_color0, a_texcoord0, a_texcoord1 SKELETON_INPUTS INSTANCING_INPUTS MORPHTARGET_INPUTS
$output v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal

#include <common.sh>
#include <convert.sh>
#include <skeleton.sh>
#include <pbr/pbr.sh>

#define a_morph0 a_texcoord2
#define a_morph1 a_texcoord3
#define a_morph2 a_texcoord4
#define a_morph3 a_texcoord5

//#define DEBUG_BONES

void main()
{
#include "vs_modelview.sh"

#include "vs_geometry.sh"

#include "vs_out.sh"

#if defined SKELETON && defined DEBUG_BONES 
    vec3 hsv = vec3(float(a_indices.x) / 64.0, 1.0, 1.0);
    v_color.rgb = hsv_to_rgb(hsv);
#endif
}

