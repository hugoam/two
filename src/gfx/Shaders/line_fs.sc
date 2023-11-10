#ifdef DASH
#define DASH_PARAMS , v_line_distance
#else
#define DASH_PARAMS
#endif

$input v_color DASH_PARAMS

#include <common.sh>

void main()
{
    int material_index = int(u_state_material);
    AlphaMaterial matalpha = read_alpha_material(material_index);
    SolidMaterial matsolid = read_solid_material(material_index);
    LineMaterial  matline  = read_line_material(material_index);
    
#include "fs_alpha.sh"
#include "fs_alphatest.sh"

#ifdef DASH
    if (mod(v_line_distance, matline.dash_size + matline.dash_gap) > matline.dash_size) discard; // todo - FIX
#endif

    vec4 color = vec4(matsolid.color.rgb, matsolid.color.a * alpha);
#ifdef VERTEX_COLOR
    color *= v_color;
#endif

    gl_FragColor = vec4(color.rgb, color.a);
}
