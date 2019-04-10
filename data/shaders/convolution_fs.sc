$input v_uv0
#include <filter.sh>
uniform vec4 u_kernel[8];
uniform vec4 u_bloom_blur_p0;
#define u_increment u_bloom_blur_p0.xy
void main()
{
vec2 uv = v_uv0;
vec4 sum = vec4(0.0, 0.0, 0.0, 0.0);
for(int i = 0; i < KERNEL_SIZE; i++)
{
sum += texture2D(s_source_0, uv) * u_kernel[i/4][i%4];
uv += u_increment;
}
gl_FragColor = sum;
}
