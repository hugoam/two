#ifdef DASH
#define DASH_PARAMS , v_line_distance
#else
#define DASH_PARAMS
#endif

$input a_position, a_texcoord0, i_data0, i_data1, i_data2, i_data3
$output v_color, v_uv0 DASH_PARAMS

#define i_start i_data0.xyz
#define i_end i_data1.xyz
#define i_distance_start i_data0.w
#define i_distance_end i_data1.w
#define i_color_start i_data2.rgb
#define i_color_end i_data3.rgb

#include <common.sh>

void trimSegment(vec4 start, inout vec4 end)
{
    // trim end segment so it terminates between the camera plane and the near plane

    // conservative estimate of the near plane
    float a = u_proj[2][2]; // 3nd entry in 3th column
    float b = u_proj[3][2]; // 3nd entry in 4th column
    float nearEstimate = - 0.5 * b / a;

    float alpha = (nearEstimate - start.z) / (end.z - start.z);

    end.xyz = mix(start.xyz, end.xyz, alpha);
}

void main()
{
    int material_index = int(u_state_material_vertex);
    LineMaterial mat = read_line_material(material_index);
    
    #if 1 //def USE_COLOR
        v_color = vec4((a_position.y < 0.5) ? i_color_start : i_color_end, 1.0);
    #endif

    #ifdef DASH
        v_line_distance = (a_position.y < 0.5) ? mat.dash_scale * i_distance_start : mat.dash_scale * i_distance_end;
    #endif

    v_uv0 = a_texcoord0;

    // camera space
    vec4 start = mul(u_modelView, vec4(i_start, 1.0));
    vec4 end = mul(u_modelView, vec4(i_end, 1.0));

    // special case for perspective projection, and segments that terminate either in, or behind, the camera plane
    // clearly the gpu firmware has a way of addressing this issue when projecting into ndc space
    // but we need to perform ndc-space calculations in the shader, so we must address this issue directly
    // perhaps there is a more elegant solution -- WestLangley

    bool perspective = (u_proj[2][3] == - 1.0); // 4th entry in the 3rd column

    if (perspective) {

        if (start.z < 0.0 && end.z >= 0.0) {
            trimSegment(start, end);
        } else if (end.z < 0.0 && start.z >= 0.0) {
            trimSegment(end, start);
        }

    }

    // clip space
    vec4 clipStart = mul(u_proj, start);
    vec4 clipEnd = mul(u_proj, end);

    // ndc space
    vec2 ndcStart = clipStart.xy / clipStart.w;
    vec2 ndcEnd = clipEnd.xy / clipEnd.w;

    // direction
    vec2 dir = ndcEnd - ndcStart;

    // account for clip-space aspect ratio
    dir.x *= u_aspect;
    dir = normalize(dir);

    // perpendicular to dir
    vec2 offset = vec2(dir.y, - dir.x);

    // undo aspect ratio adjustment
    dir.x /= u_aspect;
    offset.x /= u_aspect;

    // sign flip
    if (a_position.x < 0.0) offset *= - 1.0;

    // endcaps
    if (a_position.y < 0.0) {
        offset += - dir;
    } else if (a_position.y > 1.0) {
        offset += dir;
    }

    // adjust for linewidth
    offset *= mat.line_width;

    // adjust for clip-space to screen-space conversion // maybe resolution should be based on viewport ...
    offset /= u_screen_size.y;

    // select end
    vec4 clip = (a_position.y < 0.5) ? clipStart : clipEnd;

    // back to clip space
    offset *= clip.w;

    clip.xy += offset;

    gl_Position = clip;

    vec4 v_position = (a_position.y < 0.5) ? start : end; // this is an approximation

    //#include <logdepthbuf_vertex>
    //#include <clipping_planes_vertex>
    //#include <fog_vertex>
}
