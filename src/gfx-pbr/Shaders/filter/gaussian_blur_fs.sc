$input v_uv0

#include <filter.sh>
#include <filter/blur.sh>

uniform vec4 u_blur_p0;
#define u_blur_lod u_blur_p0.x
#define u_blur_pass u_blur_p0.y

uniform vec4 u_blur_kernel_0_3;
uniform vec4 u_blur_kernel_4_7;
#define u_kernel_0 u_blur_kernel_0_3.x
#define u_kernel_1 u_blur_kernel_0_3.y
#define u_kernel_2 u_blur_kernel_0_3.z
#define u_kernel_3 u_blur_kernel_0_3.w
#define u_kernel_4 u_blur_kernel_4_7.x
#define u_kernel_5 u_blur_kernel_4_7.y
#define u_kernel_6 u_blur_kernel_4_7.z
#define u_kernel_7 u_blur_kernel_4_7.w

void main()
{
    if(u_blur_pass == 0)
        gl_FragColor = blur_7(s_source_0, v_uv0, u_blur_lod, u_kernel_0, u_kernel_1, u_kernel_2, u_kernel_3, u_kernel_4, u_kernel_5, u_kernel_6);
    else
        gl_FragColor = blur_5(s_source_0, v_uv0, u_blur_lod, u_kernel_0, u_kernel_1, u_kernel_2, u_kernel_3, u_kernel_4);
}
