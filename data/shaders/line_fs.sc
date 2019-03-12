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
    SolidMaterial solid = read_solid_material(material_index);
    LineMaterial mat = read_line_material(material_index);
    
#include "fs_alpha.sh"
#include "fs_alphatest.sh"

    #ifdef DASH
        if (mod(v_line_distance, mat.dash_size + mat.dash_gap) > mat.dash_size) discard; // todo - FIX
    #endif

    vec4 diffuse = v_color * vec4(solid.color.rgb, solid.color.a * alpha);

    gl_FragColor = vec4(diffuse.rgb, diffuse.a);
}
