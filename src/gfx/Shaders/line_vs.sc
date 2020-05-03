$input a_position, a_color0
$output v_color, v_line_distance

#include <common.sh>

void main()
{
    int material_index = int(u_state_material_vertex);
    LineMaterial mat = read_line_material(material_index);
    
    v_color = a_color0;
    v_line_distance = mat.dash_scale * a_position.w;

    vec4 position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    gl_Position = position;
}
