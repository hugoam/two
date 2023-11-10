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

$input a_position, a_normal, a_color0, a_texcoord0, a_texcoord1 SKELETON_INPUTS INSTANCING_INPUTS
$output v_view, v_position, v_normal, v_color, v_uv0, v_uv1, v_light

#include <common.sh>
#include <convert.sh>
#include <skeleton.sh>
#include <pbr/light.sh>

void main()
{
#include "modelview.sh"

    //mat4 normalModelView = transpose(inverse(modelView));
    mat4 normalModelView = modelView;

    int material_index = int(u_state_material_vertex);
    BaseMaterial basic = read_base_material(material_index);

    v_color = a_color0;
    v_uv0 = (a_texcoord0 * basic.uv0_scale) + basic.uv0_offset;
    v_uv1 = (a_texcoord1 * basic.uv1_scale) + basic.uv1_offset;

    v_view = mul(modelView, vec4(a_position.xyz, 1.0)).xyz;
    
#ifdef QNORMALS
    v_normal = normalize(mul(normalModelView, vec4(vec3(a_normal) / 255.0 - 0.5, 0.0)).xyz);
#else
    v_normal = normalize(mul(normalModelView, vec4(a_normal, 0.0)).xyz);
#endif

    v_position = mul(u_proj, vec4(v_view, 1.0));

#ifdef VFLIP
    v_position.y = -v_position.y;
#endif

#include "vs_direct.sh"

#if defined RENDER_UV
    vec2 uv2ndc = vec2(v_uv0.x, 1.0 - v_uv0.y) * 2.0 - 1.0; // uvs are relative to top-left, so we need to reverse y and to NDC for rendering
    gl_Position = vec4(uv2ndc, 0.0, 1.0);
#elif defined RENDER_UV2
    vec2 uv2ndc = vec2(v_uv1.x, 1.0 - v_uv1.y) * 2.0 - 1.0; // uvs are relative to top-left, so we need to reverse y and to NDC for rendering
    gl_Position = vec4(uv2ndc, 0.0, 1.0);
#else
    gl_Position = v_position;
#endif
}
