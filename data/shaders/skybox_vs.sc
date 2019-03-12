$input a_position, a_texcoord0
$output v_dir, v_uv0

#include <common.sh>
#include <filter.sh>

uniform mat4 u_skybox_matrix;

void main()
{
	v_uv0 = a_texcoord0;
	v_uv0 = u_source_0_crop.xy + v_uv0 * u_source_0_crop.zw;
    if(!bool(u_origin_bottom_left))
    {
        // spherical uvs are sampled from bottom left: we flip uvs when input texture is NOT inverted
        v_uv0.y = 1.0 - v_uv0.y;
    }
    
    float height = tan(radians(u_fov) * 0.5);
    float width = height * u_aspect;
    vec2 corner = (2.0 * v_uv0 - 1.0) * vec2(width, height);

    v_dir = mul(u_skybox_matrix, vec4(corner, -1.0, 0.0)).xyz;
    
    gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
}
