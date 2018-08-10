$input v_texcoord0

#include <common.sh>
#include <filter/filter.sh>

void main()
{
	gl_FragColor = vec4(v_texcoord0.xy, 1.0, 1.0);
}

