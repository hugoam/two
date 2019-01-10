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

$input a_position, a_normal, a_tangent, a_color0, a_texcoord0, a_texcoord1 SKELETON_INPUTS INSTANCING_INPUTS
$output v_view, v_position, v_normal, v_tangent, v_color, v_texcoord0, v_texcoord1, v_binormal

#include <common.sh>
#include <convert.sh>
#include <skeleton.sh>

void main()
{
#include "modelview.sh"

    mat4 normalModelView = transpose(inverse(modelView));
    
	v_color = a_color0;
	v_texcoord0 = vec4((a_texcoord0.xy * u_uv0_scale) + u_uv0_offset, 0.0, 0.0);
	v_texcoord1 = vec4((a_texcoord1.xy * u_uv1_scale) + u_uv1_offset, 0.0, 0.0);

	v_view = mul(modelView, vec4(a_position, 1.0)).xyz;
#ifdef QNORMALS
    v_normal = normalize(mul(normalModelView, vec4(vec3(a_normal) / 255.0 - 0.5, 0.0)).xyz);
	v_tangent = normalize(mul(normalModelView, vec4(vec3(a_tangent.xyz) / 255.0 - 0.5, 0.0)).xyz);
#else
    v_normal = normalize(mul(normalModelView, vec4(a_normal, 0.0)).xyz);
	v_tangent = normalize(mul(normalModelView, vec4(a_tangent.xyz, 0.0)).xyz);
#endif
    
	vec3 binormal = normalize(a_tangent.a * cross(a_normal, a_tangent.xyz));
	v_binormal = normalize(mul(normalModelView, vec4(binormal, 0.0)).xyz);

//#define DEBUG_BONES
#if defined SKELETON && defined DEBUG_BONES 
    vec3 hsv = vec3(float(a_indices.x) / 64.0, 1.0, 1.0);
    v_color.rgb = hsv_to_rgb(hsv);
#endif

	v_position = mul(u_proj, vec4(v_view, 1.0));
#ifdef RENDER_UV2
    vec2 uv2ndc = vec2(v_texcoord1.x, 1.0 - v_texcoord1.y) * 2.0 - 1.0; // uvs are relative to top-left, so we need to reverse y and to NDC for rendering
	gl_Position = vec4(uv2ndc, 0.0, 1.0);
#else
	gl_Position = v_position;
#endif
}

