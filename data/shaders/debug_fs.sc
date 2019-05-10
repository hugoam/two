$input v_color, v_uv0

#include <common.sh>

SAMPLER2D(s_color, 0);

void main()
{
    vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
    
#ifdef COLOR_MAP
    color *= toLinear(texture2D(s_color, v_uv0));
#endif

#ifdef VERTEX_COLOR
    gl_FragColor = v_color * color;
#else
    gl_FragColor = color;
#endif
}
