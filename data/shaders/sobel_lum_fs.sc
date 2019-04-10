$input v_uv0
#include <filter.sh>
float linearToRelativeLuminance(const in vec3 color) {
	vec3 weights = vec3(0.2126, 0.7152, 0.0722);
	return dot(weights, color.rgb);
}
void main()
{
vec4 texel = texture2D(s_source_0, v_uv0);
float l = linearToRelativeLuminance(texel.rgb);
gl_FragColor = vec4(l, l, l, texel.w);
}