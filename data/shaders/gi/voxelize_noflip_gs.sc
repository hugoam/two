$input g_position, g_normal, g_color, g_texcoord0
$output v_position, v_normal, v_color, v_uv0

#include <bgfx_shader.sh>

void main()
{
    vec3 p1 = g_position[1] - g_position[0];
    vec3 p2 = g_position[2] - g_position[0];
    vec3 p = abs(cross(p1, p2));
    
    for (uint i = 0; i < 3; ++i) {
        v_position = vec4(g_position[i], 1.0);
        v_normal = g_normal[i];
        v_color = g_color[i];
        v_uv0 = g_texcoord0[i];
        
        if (p.z > p.x && p.z > p.y) {
            gl_Position = vec4(v_position.x, v_position.y, 0.0, 1.0);
        }
        else if (p.x > p.y && p.x > p.z) {
            gl_Position = vec4(v_position.y, v_position.z, 0.0, 1.0);
        }
        else {
            gl_Position = vec4(v_position.x, v_position.z, 0.0, 1.0);
        }
        
        EmitVertex();
    }
    
    EndPrimitive();
}
