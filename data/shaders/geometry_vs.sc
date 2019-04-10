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

#define a_morph0 a_texcoord2
#define a_morph1 a_texcoord3
#define a_morph2 a_texcoord4
#define a_morph3 a_texcoord5

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
    
    vec3 position = a_position.xyz;
    
#ifdef MORPHTARGET
    position += a_morph0 * u_morph_weights[0];
    position += a_morph1 * u_morph_weights[1];
    position += a_morph2 * u_morph_weights[2];
    position += a_morph3 * u_morph_weights[3];
#endif

#ifdef DISPLACEMENT
    LitMaterial matlit = read_lit_material(material_index);
    float displace = texture2D(s_displace, v_uv0).x;
    position += normalize(a_normal) * (displace * matlit.displace + matlit.displace_bias);
#endif

    v_view = mul(modelView, vec4(position, 1.0)).xyz;
    
#ifdef QNORMALS
    v_normal = normalize(mul(normalModelView, vec4(a_normal / 255.0 - 0.5, 0.0)).xyz);
    v_tangent = normalize(mul(normalModelView, vec4(a_tangent.xyz / 255.0 - 0.5, 0.0)).xyz);
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

#if defined RENDER_UV
    vec2 uv2ndc = mod(vec2(v_uv0.x, 1.0 - v_uv0.y), vec2(1.0, 1.0)) * 2.0 - 1.0; // uvs are relative to top-left, so we need to reverse y and to NDC for rendering
    gl_Position = vec4(uv2ndc, 0.0, 1.0);
#elif defined RENDER_UV2
    vec2 uv2ndc = mod(vec2(v_uv1.x, 1.0 - v_uv1.y), vec2(1.0, 1.0)) * 2.0 - 1.0; // uvs are relative to top-left, so we need to reverse y and to NDC for rendering
    gl_Position = vec4(uv2ndc, 0.0, 1.0);
#else
    gl_Position = v_position;
#endif

#ifdef VFLIP
    gl_Position.y = -gl_Position.y;
    v_position.y = -v_position.y;
#endif
}

