//$input v_color, v_uv0
$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal

#include <common.sh>

void main()
{
    int material_index = int(u_state_material);
    AlphaMaterial matalpha = read_alpha_material(material_index);
    SolidMaterial matsolid = read_solid_material(material_index);

    vec2 uv = v_uv0;
#include "fs_alpha.sh"
#include "fs_alphatest.sh"
    
    vec4 color = matsolid.color;
    color.a *= alpha;
    
    if(u_color_map)
        color *= toLinear(texture2D(s_color, v_uv0));

    if(u_vertex_color)
        gl_FragColor = v_color * color;
    else
        gl_FragColor = color;
}
