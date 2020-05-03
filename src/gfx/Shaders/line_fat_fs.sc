$input v_color, v_uv0, v_line_distance

#include <common.sh>

void main()
{
    int material_index = int(u_state_material);
    AlphaMaterial matalpha = read_alpha_material(material_index);
    SolidMaterial matsolid = read_solid_material(material_index);
    LineMaterial  matline  = read_line_material(material_index);
    
    vec2 uv = v_uv0;
#include "fs_alpha.sh"
#include "fs_alphatest.sh"
    
    if(u_line_dash)
    {
        if (uv.y < - 1.0 || uv.y > 1.0) discard; // discard endcaps
        if (mod(v_line_distance, matline.dash_size + matline.dash_gap) > matline.dash_size) discard; // todo - FIX
    }
    
    if (abs(uv.y) > 1.0)
    {
        float a = uv.x;
        float b = (uv.y > 0.0) ? uv.y - 1.0 : uv.y + 1.0;
        float len2 = a * a + b * b;

        if (len2 > 1.0) discard;
    }

    vec4 diffuse = v_color * vec4(matsolid.color.rgb, matsolid.color.a * alpha);

    gl_FragColor = vec4(diffuse.rgb, diffuse.a);
}
