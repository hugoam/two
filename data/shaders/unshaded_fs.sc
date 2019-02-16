//$input v_color, v_texcoord0
$input v_view, v_position, v_normal, v_tangent, v_color, v_texcoord0, v_texcoord1, v_binormal

#include <common.sh>

SAMPLER2D(s_color, 0);

void main()
{
    int material_index = int(u_state_material);
    UnshadedMaterial material = read_unshaded_material(material_index);
    
    vec4 color_tex = toLinear(texture2D(s_color, v_texcoord0.xy));
    gl_FragColor = v_color * color_tex * material.color;
}
