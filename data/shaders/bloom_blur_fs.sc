$input v_uv0
#include <filter.sh>
#include <convert.sh>
#define SIGMA KERNEL_RADIUS
uniform vec4 u_glow_blur_p0;
#define u_direction u_glow_blur_p0.xy
#define u_level_size u_glow_blur_p0.zw
float gaussianPdf(float x, float sigma) {
	return 0.39894 * exp(-0.5 * x * x / (sigma * sigma)) / sigma;
}
void main() {
vec2 invSize = 1.0 / u_level_size;
float fSigma = float(SIGMA);
float weightSum = gaussianPdf(0.0, fSigma);
vec3 diffuseSum = texture2DLod(s_source_0, v_uv0, float(u_source_0_level)).rgb * weightSum;
for(int i = 1; i < KERNEL_RADIUS; i++) {
float x = float(i);
float w = gaussianPdf(x, fSigma);
vec2 uvOffset = u_direction * invSize * x;
vec3 sample1 = texture2DLod(s_source_0, v_uv0 + uvOffset, float(u_source_0_level)).rgb;
vec3 sample2 = texture2DLod(s_source_0, v_uv0 - uvOffset, float(u_source_0_level)).rgb;
diffuseSum += (sample1 + sample2) * w;
weightSum += 2.0 * w;
}
gl_FragColor = vec4(diffuseSum / weightSum, 1.0);
}
