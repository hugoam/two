vec2 v_uv0          : TEXCOORD0 = vec2(0.0, 0.0);
vec3 v_world        : TEXCOORD1 = vec3(0.0, 0.0, 0.0);
vec3 v_dir          : TEXCOORD2 = vec3(0.0, 0.0, 0.0);
vec3 v_view         : TEXCOORD2 = vec3(0.0, 0.0, 0.0);
vec4 v_position     : TEXCOORD3 = vec4(0.0, 0.0, 0.0, 0.0);
vec3 v_binormal     : TEXCOORD4 = vec3(0.0, 0.0, 0.0);
vec2 v_uv1          : TEXCOORD5 = vec2(0.0, 0.0);
vec3 v_normal       : NORMAL    = vec3(0.0, 0.0, 1.0);
vec3 v_tangent      : TANGENT   = vec3(1.0, 0.0, 0.0);
vec3 v_bitangent    : BINORMAL  = vec3(0.0, 1.0, 0.0);
vec4 v_color        : COLOR0    = vec4(1.0, 1.0, 1.0, 1.0);
vec3 v_light        : TEXCOORD6 = vec3(0.0, 0.0, 0.0);
vec4 v_diffuse      : TEXCOORD6 = vec4(0.0, 0.0, 0.0, 0.0);
vec4 v_specular     : TEXCOORD7 = vec4(0.0, 0.0, 0.0, 0.0);
vec2 v_particle     : TEXCOORD1 = vec2(0.0, 0.0);

float v_scale       : TEXCOORD6 = 0.0;
float v_line_distance : TEXCOORD6 = 0.0;

vec4 v_mirrored     : TEXCOORD4 = vec4(0.0, 0.0, 0.0, 0.0);

vec3 v_sundir       : TEXCOORD4 = vec3(0.0, 0.0, -1.0);
vec2 v_sunp0        : TEXCOORD5 = vec2(0.0, 0.0);
vec3 v_betaR        : TEXCOORD6 = vec3(0.0, 0.0, 0.0);
vec3 v_betaM        : TEXCOORD7 = vec3(0.0, 0.0, 0.0);

vec3 g_position     : TEXCOORD3 = vec3(0.0, 0.0, 0.0);
vec4 g_texcoord0    : TEXCOORD0 = vec4(0.0, 0.0, 0.0, 0.0);
vec3 g_normal       : NORMAL    = vec3(0.0, 0.0, 1.0);
vec4 g_color        : COLOR0    = vec4(1.0, 1.0, 1.0, 1.0);

vec4 a_position     : POSITION;
vec4 a_color0       : COLOR0;
vec3 a_normal       : NORMAL;
vec4 a_tangent      : TANGENT;
vec2 a_texcoord0    : TEXCOORD0;
vec2 a_texcoord1    : TEXCOORD1;
vec4 a_weight       : BLENDWEIGHT;
ivec4 a_indices     : BLENDINDICES;
vec3 a_texcoord2    : TEXCOORD2;
vec3 a_texcoord3    : TEXCOORD3;
vec3 a_texcoord4    : TEXCOORD4;
vec3 a_texcoord5    : TEXCOORD5;

vec4 i_data0     : TEXCOORD7;
vec4 i_data1     : TEXCOORD6;
vec4 i_data2     : TEXCOORD5;
vec4 i_data3     : TEXCOORD4;
vec4 i_data4     : TEXCOORD3;
vec4 i_data5     : TEXCOORD2;
vec4 i_data6     : TEXCOORD1;
vec4 i_data7     : TEXCOORD0;
