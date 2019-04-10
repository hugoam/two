$input v_uv0
#include <filter.sh>
void main() {
	float depth = texture2D(s_source_depth, v_uv0).x;
	depth = -perspectiveDepthToViewZ(depth) / u_z_far;
	depth = clamp(depth, 0.0, 1.0);
	gl_FragColor = vec4(1.0 - depth, 0.0, 0.0, 0.0);
}
