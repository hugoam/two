$input g_position, g_normal, g_color, g_texcoord0
$output v_position, v_normal, v_color, v_uv0

#include <bgfx_shader.sh>

void main()
{
    vec3 p1 = g_position[1] - g_position[0];
    vec3 p2 = g_position[2] - g_position[0];
    vec3 n = cross(p1, p2);
    vec3 p = abs(n);
    
    for (uint i = 0; i < 3; ++i)
    {
        uint j = i;
        vec2 projected;
        
        if (p.z > p.x && p.z > p.y) {
            if(n.z < 0.0) j = 2 - i; // flip
            projected = vec2(g_position[j].x, g_position[j].y);
        }
        else if (p.x > p.y && p.x > p.z) {
            if(n.x < 0.0) j = 2 - i; // flip
            projected = vec2(g_position[j].y, g_position[j].z);
        }
        else {
            if(n.y > 0.0) j = 2 - i; // flip
            projected = vec2(g_position[j].x, g_position[j].z);
        }
        
        v_position = vec4(g_position[j], 1.0);
        v_normal = g_normal[j];
        v_color = g_color[j];
        v_uv0 = g_texcoord0[j];
        
        gl_Position = vec4(projected, 0.0, 1.0);

        EmitVertex();
    }
    
    EndPrimitive();
}
