$input a_position, a_texcoord0
$output v_dir, v_color

#include <common.sh>
#include <filter.sh>

uniform mat4 u_skybox_matrix;

void main()
{
    vec2 uv = a_texcoord0;
     // uvs are relative to top-left, so we need to reverse y to get NDC
    vec2 uvndc = vec2(uv.x, 1.0 - uv.y) * 2.0 - 1.0;
    
#ifdef VFLIP
    uvndc.y = -uvndc.y;
#endif

    float aspect = u_screen_size.x / u_screen_size.y;
    
    float height = tan(radians(u_fov) * 0.5);
    float width = height * u_aspect;
    vec2 corner = uvndc * vec2(width, height);

    v_dir = mul(u_skybox_matrix, vec4(corner, -1.0, 0.0)).xyz;

#ifdef VFLIP
    // if we flip output Y we have to flip cube X too for some reason
    v_dir.x = -v_dir.x;
#endif
    
    //v_color = vec4(uv.x, 0.0, uv.y, 1.0);

    gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
}
