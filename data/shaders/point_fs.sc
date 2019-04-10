$input v_color, v_uv0

#include <common.sh>

void main()
{
    int material_index = int(u_state_material);
    AlphaMaterial matalpha = read_alpha_material(material_index);
    SolidMaterial matsolid = read_solid_material(material_index);
    
#include "fs_alpha.sh"
#include "fs_alphatest.sh"
    
    vec4 color_tex = toLinear(texture2D(s_color, v_uv0));
    color_tex.a *= alpha;
    gl_FragColor = v_color * color_tex * matsolid.color;
    //gl_FragColor = matsolid.color;
}
