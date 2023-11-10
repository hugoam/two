$input v_color, v_uv0

#include <common.sh>

void main()
{
    int material_index = int(u_state_material);
    AlphaMaterial matalpha = read_alpha_material(material_index);
    SolidMaterial matsolid = read_solid_material(material_index);
    
#include "fs_alpha.sh"
#include "fs_alphatest.sh"
    
    vec4 color = matsolid.color;
    color.a *= alpha;
    
#ifdef COLOR_MAP
    color *= toLinear(texture2D(s_color, v_uv0));
#endif

#ifdef VERTEX_COLOR
    gl_FragColor = v_color * color;
#else
    gl_FragColor = color;
#endif
}
