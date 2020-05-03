$input v_color, v_line_distance

#include <common.sh>

void main()
{
    int material_index = int(u_state_material);
    AlphaMaterial matalpha = read_alpha_material(material_index);
    SolidMaterial matsolid = read_solid_material(material_index);
    LineMaterial  matline  = read_line_material(material_index);
    
    float alpha = matalpha.alpha;
#include "fs_alphatest.sh"

    if(u_line_dash)
    {
        if(mod(v_line_distance, matline.dash_size + matline.dash_gap) > matline.dash_size)
            discard;
    }

    vec4 color = vec4(matsolid.color.rgb, matsolid.color.a * alpha);
    if(u_vertex_color)
        color *= v_color;
    gl_FragColor = vec4(color.rgb, color.a);
}
