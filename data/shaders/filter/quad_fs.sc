$input v_uv0

#include <common.sh>
#include <filter.sh>

void main()
{
	gl_FragColor = vec4(v_uv0, 1.0, 1.0);
}

