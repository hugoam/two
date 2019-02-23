//$input v_color, v_texcoord0
$input v_view, v_position, v_normal, v_tangent, v_color, v_texcoord0, v_texcoord1, v_binormal

#include <common.sh>

void main()
{
    int material_index = int(u_state_material);
    UnshadedMaterial unshaded = read_unshaded_material(material_index);
    
#include "fs_alpha.sh"
#include "fs_alphatest.sh"
    
    vec4 color_tex = toLinear(texture2D(s_color, v_texcoord0.xy));
    color_tex.a *= alpha;
    gl_FragColor = v_color * color_tex * unshaded.color;
}
