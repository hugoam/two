$input v_uv0

#include <filter.sh>

#define s_source_taps s_source_0
#define s_source_color s_source_1

#define DOF_DISK_KERNEL

// 11 x 11 separated kernel weights. This does not dictate the blur kernel for depth of field; it is scaled to the actual kernel at each pixel.
CONST(int) kernel_taps = 6;
#ifdef DOF_DISK_KERNEL
CONST(ARRAY_BEGIN(float, kernel, 7)) 1.00 , 1.00 , 0.90 , 0.75 , 0.60 , 0.50 , 0.00 ARRAY_END();
#else
CONST(ARRAY_BEGIN(float, kernel, 7)) 0.13425804976814 , 0.12815541114232 , 0.11143948794984 , 0.08822292796029 , 0.06352050813141 , 0.04153263993208 , 0.00000000000000 ARRAY_END();
#endif

uniform vec4 u_dof_near_p0;
#define u_dof_near_begin u_dof_near_p0.x
#define u_dof_near_end u_dof_near_p0.y
#define u_dof_near_radius u_dof_near_p0.z
#define u_dof_near_inv_radius u_dof_near_p0.w

uniform vec4 u_dof_far_p0;
#define u_dof_far_begin u_dof_far_p0.x
#define u_dof_far_end u_dof_far_p0.y
#define u_dof_far_radius u_dof_far_p0.z

uniform vec4 u_dof_p0;
#define u_max_coc_pixels u_dof_p0.x
//#define u_dof_focus_plane_z u_dof_p0.x
//#define u_dof_focus_scale u_dof_p0.y

bool in_near_field(float radius)
{
    return radius > 0.25;
}

#define MODEL 1

float coc_radius(vec2 uv)
{
    float nearNormalize = 1.0 / (u_dof_near_end - u_dof_near_begin);
    float farNormalize = 1.0 / (u_dof_far_begin - u_dof_far_end);
    
    float depth = linear_depth(texture2DLod(s_source_depth, uv, 0.0).r);

#if MODEL == 0 // PHYSICAL
        return (depth - u_dof_focus_plane_z) * scale;
#elif MODEL == 1 // ARTIST
        if (depth < u_dof_near_begin) {
            return (max(depth, u_dof_near_end) - u_dof_near_begin) * nearNormalize;
        } else if (depth < u_dof_far_begin) {
            return 0.0;
        } else {
            return (min(depth, u_dof_far_end) - u_dof_far_begin) * farNormalize;
        }
#endif
}

void main() {

#ifdef DOF_FIRST_PASS
    vec2 direction = vec2(1.0, 0.0);
#else
    vec2 direction = vec2(0.0, 1.0);
#endif

	vec4 far_color_sum = vec4_splat(0.0);
	float far_weight_sum = 0.0;

	vec4 near_color_sum = vec4_splat(0.0);
	float near_weight_sum = 0.0;
    
    float norm_radius = coc_radius(v_uv0);
    float radius = norm_radius * u_max_coc_pixels;
    float is_near = float(radius > 0.0);
    
    for (int delta = int(-u_max_coc_pixels); delta <= int(u_max_coc_pixels); ++delta)
    {
        vec2 tap_coord = v_uv0 + direction * float(delta) * u_pixel_size;

        vec4 tap_color = texture2DLod(s_source_taps, tap_coord, 0.0);
        float tap_radius = coc_radius(tap_coord) * u_max_coc_pixels;
        
        int offset = int(clamp(float(abs(delta) * (kernel_taps - 1)) / (0.001 + abs(tap_radius * 0.8)), 0.0, float(kernel_taps)));
        float blur_weight = kernel[offset];
        float wNormal = float(!in_near_field(tap_radius)) * blur_weight;

        float far_tap_weight = mix(wNormal, 1.0, is_near);

        far_color_sum += tap_color * far_tap_weight;
        far_weight_sum += far_tap_weight;
        
        float near_coverage = float(abs(delta) <= tap_radius) * saturate(tap_radius * u_dof_near_inv_radius * 4.0);
		near_coverage *= near_coverage * near_coverage; // increase edge fade contrast in the near field
        vec4 near_tap = vec4(tap_color.rgb, near_coverage);

        // box blur instead of kernel blur like above
        float near_tap_weight =  float(abs(delta) < u_dof_near_radius);
        near_color_sum += near_tap * near_tap_weight;
        near_weight_sum += near_tap_weight;
    }

    vec4 far_color = far_color_sum / far_weight_sum;
    vec4 near_color = near_color_sum / max(near_weight_sum, 0.00001); 
    
#ifdef DOF_FIRST_PASS
	gl_FragColor = mix(far_color, near_color, near_color.a);
#else
	vec4 color = texture2DLod(s_source_color, v_uv0, 0.0);
    gl_FragColor = mix(color, far_color, abs(norm_radius)) * (1.0 - near_color.a) + near_color * near_color.a;
    
    //gl_FragColor += vec4(saturate(norm_radius), saturate(-norm_radius), 0.0, 0.0);
#endif
    
}
