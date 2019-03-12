#ifndef MUD_SHADER_GLOW
#define MUD_SHADER_GLOW

#include <filter.sh>

uniform vec4 u_glow_p0;
#define u_glow_strength        u_glow_p0.x
#define u_glow_bloom           u_glow_p0.y
#define u_glow_bleed_threshold u_glow_p0.z
#define u_glow_bleed_scale     u_glow_p0.w

uniform vec4 u_glow_p1;
#define u_glow_intensity u_glow_p1.x
#define u_glow_texture_size u_glow_p1.zw

uniform vec4 u_glow_levels_1_4;
uniform vec4 u_glow_levels_5_8;
#define u_glow_level_1 u_glow_levels_1_4.x
#define u_glow_level_2 u_glow_levels_1_4.y
#define u_glow_level_3 u_glow_levels_1_4.z
#define u_glow_level_4 u_glow_levels_1_4.w
#define u_glow_level_5 u_glow_levels_5_8.x
#define u_glow_level_6 u_glow_levels_5_8.y
#define u_glow_level_7 u_glow_levels_5_8.z
#define u_glow_level_8 u_glow_levels_5_8.w

#endif
