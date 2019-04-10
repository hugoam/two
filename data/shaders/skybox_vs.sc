$input a_position, a_texcoord0
$output v_dir, v_uv0

#include <common.sh>
#include <filter.sh>

uniform mat4 u_skybox_matrix;

void main()
{
    v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;

     // uvs are relative to top-left, so we need to reverse y to get NDC
    vec2 uv0ndc = vec2(v_uv0.x, 1.0 - v_uv0.y) * 2.0 - 1.0;

#ifdef VFLIP
    uv0ndc.y = -uv0ndc.y;
#endif

    float height = tan(radians(u_fov) * 0.5);
    float width = height * u_aspect;
    vec2 corner = uv0ndc * vec2(width, height);

    v_dir = mul(u_skybox_matrix, vec4(corner, -1.0, 0.0)).xyz;

#ifdef VFLIP
    // if we flip output Y we have to flip cube X too for some reason
    v_dir.x = -v_dir.x;
#endif

    gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
}
