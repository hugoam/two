$input v_uv0

#include <filter.sh>
#include <filter/glow.sh>

#define s_diffuse s_source_0

uniform float u_exposure;

void main()
{
	vec4 color = texture2D(s_diffuse, v_uv0);
	//color *= u_exposure;

	float luminance = max(color.r, max(color.g, color.b));
    float bleed = smoothstep(u_glow_bleed_threshold, u_glow_bleed_threshold + u_glow_bleed_scale, luminance);
	float feedback = max(bleed, u_glow_bloom);

	gl_FragColor = color * feedback;
}

