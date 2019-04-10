$input v_color
#include <common.sh>
void main()
{
	if (v_color.a > 0.0) {
		gl_FragColor = vec4(v_color.rgb, 1.0);
	} else {
		discard;
	}
}
