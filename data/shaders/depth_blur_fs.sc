$input v_uv0
#define PERSPECTIVE_CAMERA 1
#include <filter.sh>
#define s_diffuse s_source_0
#define s_depth s_source_depth
uniform vec4 u_sao_blur_p0;
#define u_inv_size     u_sao_blur_p0.xy
#define u_depth_cutoff u_sao_blur_p0.z
uniform vec4 u_sao_blur_samples[16];
float getViewZ(float depth) {
#if PERSPECTIVE_CAMERA == 1
	return perspectiveDepthToViewZ(depth);
#else
	return orthographicDepthToViewZ(depth);
#endif
}
void main() {
	float depth = texture2D(s_source_depth, v_uv0).x;
	if(depth >= (1.0 - EPSILON)) {
		discard;
	}
	float centerViewZ = -getViewZ(depth);
	bool rBreak = false, lBreak = false;
	float weightSum = u_sao_blur_samples[0].z;
	vec4 diffuseSum = texture2D(s_diffuse, v_uv0) * weightSum;
	for(int i = 1; i <= KERNEL_RADIUS; i ++) {
		float weight = u_sao_blur_samples[i].z;
		vec2 offset = u_sao_blur_samples[i].xy * u_inv_size;
		vec2 uv = v_uv0 + offset;
		float viewZ = -getViewZ(texture2D(s_source_depth, uv).x);
		if(abs(viewZ - centerViewZ) > u_depth_cutoff) rBreak = true;
		if(!rBreak) {
			diffuseSum += texture2D(s_diffuse, uv) * weight;
			weightSum += weight;
		}
		uv = v_uv0 - offset;
		viewZ = -getViewZ(texture2D(s_source_depth, uv).x);
		if(abs(viewZ - centerViewZ) > u_depth_cutoff) lBreak = true;
		if(!lBreak) {
			diffuseSum += texture2D(s_diffuse, uv) * weight;
			weightSum += weight;
		}
	}
	gl_FragColor = diffuseSum / weightSum;
}
