$input a_position, a_color0, a_texcoord0, i_data0, i_data1, i_data2
$output v_color, v_uv0

#include <common.sh>
#include <convert.sh>

void main()
{
    int material_index = int(u_state_material);
    BaseMaterial basic = read_base_material(material_index);
    
#ifdef INSTANCING
    vec3 position = i_data0.xyz;
    vec2 size = i_data1.xy;
    vec4 colour = i_data2;
    float scale = 1.0;
    vec3 view = mul(u_modelView, vec4(position, 1.0)).xyz;
    //view.xy += scale * (a_position.xy - size);
    view.xy += a_position.xy * size;
#else
    vec4 colour = vec4_splat(1.0);
    vec3 view = mul(u_modelView, vec4(a_position.xyz, 1.0)).xyz;
#endif

    //v_color = a_color0 * colour;
    v_color = colour;
    v_uv0 = (a_texcoord0 * basic.uv0_scale) + basic.uv0_offset;

    gl_Position = mul(u_proj, vec4(view, 1.0));
}
