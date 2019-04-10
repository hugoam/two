$input v_uv0
#include <filter.sh>
float readDepth(sampler2D depthSampler, vec2 coord)
{
	float depth = texture2D(depthSampler, coord).x;
	float viewZ = perspectiveDepthToViewZ(depth);
	return viewZToOrthographicDepth(viewZ);
}
void main() {
	float depth = readDepth(s_source_depth, v_uv0);
	gl_FragColor = vec4(1.0 - vec3_splat(depth), 1.0);
}
