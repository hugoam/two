$input v_normal, v_uv0
#include <common.sh>
void main()
{
vec4 c = vec4(abs(v_normal) + vec3(v_uv0, 0.0), 0.0);
gl_FragColor = c;
}