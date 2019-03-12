$input v_uv0

#include <filter.sh>
#include <filter/glow.sh>

#define s_diffuse s_source_0
#define s_glow s_source_1

#ifdef GLOW_FILTER_BICUBIC
#include <cubic.sh>

vec4 textureGlow(sampler2D tex, vec2 uv, int level, float amount)
{
    if(amount > 0.0)
        return texture2DBicubic(tex, uv, u_glow_texture_size, level) * amount;
    else
        return vec4_splat(0.0);
}
#else
vec4 textureGlow(sampler2D tex, vec2 uv, int level, float amount)
{
    if(amount > 0.0)
        return texture2DLod(tex, uv, float(level)) * amount;
    else
        return vec4_splat(0.0);
}
#endif

void main()
{
    vec3 color = texture2D(s_diffuse, v_uv0).rgb;
    
	vec3 glow = vec3_splat(0.0);
    
	glow += textureGlow(s_glow, v_uv0, 1, u_glow_level_1).rgb;
	glow += textureGlow(s_glow, v_uv0, 2, u_glow_level_2).rgb;
	//glow += textureGlow(s_glow, v_uv0, 3, u_glow_level_3).rgb;
	//glow += textureGlow(s_glow, v_uv0, 4, u_glow_level_4).rgb;
	//glow += textureGlow(s_glow, v_uv0, 5, u_glow_level_5).rgb;
	//glow += textureGlow(s_glow, v_uv0, 6, u_glow_level_6).rgb;
	//glow += textureGlow(s_glow, v_uv0, 7, u_glow_level_7).rgb;
	//glow += textureGlow(s_glow, v_uv0, 8, u_glow_level_8).rgb;
	glow *= u_glow_intensity;
    
	gl_FragColor = vec4(color + glow, 1.0);
}

