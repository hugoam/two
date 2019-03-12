$input v_position, v_uv0

#include <common.sh>
#include <pbr/fog.sh>

void main()
{
   vec2 uv = v_uv0;	vec2 position = - 1.0 + 2.0 * uv;

	vec4 noise = texture2D(s_user0, uv);
	vec2 T1 = uv + vec2(1.5, - 1.5) * u_time * 0.02;
	vec2 T2 = uv + vec2(- 0.5, 2.0) * u_time * 0.01;

	T1.x += noise.x * 2.0;
	T1.y += noise.y * 2.0;
	T2.x -= noise.y * 0.2;
	T2.y += noise.z * 0.2;

	float p = texture2D(s_user0, T1 * 2.0).a;

	vec4 lava = texture2D(s_user1, T2 * 2.0);
	vec4 color = lava * (vec4(p, p, p, p) * 2.0) + (lava * lava - 0.1);

	if(color.r > 1.0) { color.bg += clamp(color.r - 2.0, 0.0, 100.0); }
	if(color.g > 1.0) { color.rb += color.g - 1.0; }
	if(color.b > 1.0) { color.rg += color.b - 1.0; }

	gl_FragColor = color;

#if BGFX_SHADER_LANGUAGE_HLSL
	float depth = gl_FragCoord.z * gl_FragCoord.w;
#else
	float depth = gl_FragCoord.z / gl_FragCoord.w;
#endif
	const float LOG2 = 1.442695;
	float fogFactor = exp2(-u_fog_density * u_fog_density * depth * depth * LOG2);
	fogFactor = 1.0 - clamp(fogFactor, 0.0, 1.0);

	gl_FragColor = mix(color, vec4(vec3(0.0, 0.0, 0.0), color.w), fogFactor);

}
