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

$input a_position, a_normal, a_tangent, a_color0, a_texcoord0/*, a_texcoord1*/ SKELETON_INPUTS INSTANCING_INPUTS
$output v_view, v_position, v_normal, v_tangent, v_color, v_texcoord0/*, v_texcoord1*/, v_binormal

#include "common.sh"
#include "pbr.sh"
#include "skeleton.sh"

void main()
{
#include "modelview.sh"

	v_color = a_color0;
	v_texcoord0 = a_texcoord0;
	//v_texcoord1 = a_texcoord1;

	v_view = mul(modelView, vec4(a_position, 1.0)).xyz;
    v_normal = normalize(mul(modelView, vec4(a_normal.xyz, 0.0)).xyz);
	v_tangent = normalize(mul(modelView, vec4(a_tangent.xyz, 0.0)).xyz);
    
	vec3 binormal = normalize(a_tangent.a * cross(a_normal.xyz, a_tangent.xyz));
	v_binormal = normalize(mul(modelView, vec4(binormal, 0.0)).xyz);

//#define DEBUG_BONES
#if defined SKELETON && defined DEBUG_BONES 
    vec3 hsv = vec3(float(a_indices.x) / 64.0, 1.0, 1.0);
    v_color.rgb = hsv_to_rgb(hsv);
#endif

	v_position = mul(u_proj, vec4(v_view, 1.0));
	gl_Position = v_position;
}

