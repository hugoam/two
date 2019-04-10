$input v_uv0
#include <filter.sh>
#define NUM_SAMPLES 7
#define NUM_RINGS 4
#define s_normal  s_source_0
uniform vec4 u_sao_p0;
#define u_scale     u_sao_p0.x
#define u_intensity u_sao_p0.y
#define u_bias      u_sao_p0.z
#define u_seed      u_sao_p0.w
uniform vec4 u_sao_p1;
#define u_kernelRadius  u_sao_p1.x
#define u_minResolution u_sao_p1.y
#define u_size          u_sao_p1.zw
uniform mat4 u_sao_invproj;
float toClipSpaceDepth(float depth)
{
#if BGFX_SHADER_LANGUAGE_HLSL || BGFX_SHADER_LANGUAGE_PSSL || BGFX_SHADER_LANGUAGE_METAL
	return depth;
#else
	return depth * 2.0 - 1.0;
#endif
}
vec3 toClipSpace(vec2 uv, float depth)
{
	vec3 clip = vec3(uv * 2.0 - 1.0, toClipSpaceDepth(depth));
#if BGFX_SHADER_LANGUAGE_HLSL || BGFX_SHADER_LANGUAGE_PSSL || BGFX_SHADER_LANGUAGE_METAL
	clip.y = -clip.y;
#endif
	return clip;
}
vec3 clipToView(vec3 clip)
{
	vec4 wpos = mul(u_sao_invproj, vec4(clip, 1.0) );
	return wpos.xyz / wpos.w;
}
vec3 getViewPosition(vec2 uv, float depth) {
	vec3 clip = toClipSpace(uv, depth);
	return clipToView(clip);
}
vec3 unpackRGBToNormal(vec3 rgb) {
	return 2.0 * rgb.xyz - 1.0;
}
vec3 getViewNormal(vec3 viewPosition, vec2 uv) {
	return unpackRGBToNormal(texture2D(s_normal, uv).xyz);
}
float getOcclusion(vec3 position, vec3 normal, vec3 samplePosition, float scale, float offset) {
	vec3 delta = samplePosition - position;
	float distance = length(delta);
	distance = scale * distance;
	return max(0.0, (dot(normal, delta) - offset) / distance - u_bias) / (1.0 + pow2(distance));
}
CONST(float) ANGLE_STEP = PI2 * float(NUM_RINGS) / float(NUM_SAMPLES);
CONST(float) INV_NUM_SAMPLES = 1.0 / float(NUM_SAMPLES);
void main() {
	float depth = texture2D(s_source_depth, v_uv0).x;
	if(depth >= (1.0 - EPSILON)) {
		discard;
	}
	vec3 position = getViewPosition(v_uv0, depth);
	// precompute some variables require in getOcclusion.
	float scaleDividedByCameraFar = u_scale / u_z_far;
	float minResolutionMultipliedByCameraFar = u_minResolution * u_z_far;
	vec3 normal = getViewNormal(position, v_uv0);
	// jsfiddle that shows sample pattern: https://jsfiddle.net/a16ff1p7/
	float angle = rand(v_uv0 + u_seed) * PI2;
	vec2 radius = vec2_splat(u_kernelRadius * INV_NUM_SAMPLES) / u_size;
	vec2 step = radius;
	float occlusionSum = 0.0;
	float weightSum = 0.0;
	for(int i = 0; i < NUM_SAMPLES; i ++) {
		vec2 uv = v_uv0 + vec2(cos(angle), sin(angle)) * radius;
		radius += step;
		angle += ANGLE_STEP;
		float sampleDepth = texture2D(s_source_depth, uv).x;
		if(sampleDepth >= (1.0 - EPSILON)) {
			continue;
		}
		vec3 samplePosition = getViewPosition(uv, sampleDepth);
		occlusionSum += getOcclusion(position, normal, samplePosition, scaleDividedByCameraFar, minResolutionMultipliedByCameraFar);
		weightSum += 1.0;
	}
	if(weightSum == 0.0) discard;
	float ambientOcclusion = occlusionSum * (u_intensity / weightSum);
	gl_FragColor = vec4(vec3_splat(1.0 - ambientOcclusion), 1.0);
}
