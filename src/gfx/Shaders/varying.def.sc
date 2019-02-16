vec4 v_texcoord0	    : TEXCOORD0 = vec4(0.0, 0.0, 0.0, 0.0);
vec3 v_wpos			    : TEXCOORD1 = vec3(0.0, 0.0, 0.0);
vec3 v_dir			    : TEXCOORD2 = vec3(0.0, 0.0, 0.0);
vec3 v_view			    : TEXCOORD2 = vec3(0.0, 0.0, 0.0);
vec4 v_position		    : TEXCOORD3 = vec4(0.0, 0.0, 0.0, 0.0);
vec3 v_binormal		    : TEXCOORD4 = vec3(0.0, 0.0, 0.0);
vec4 v_texcoord1 	    : TEXCOORD5 = vec4(0.0, 0.0, 0.0, 0.0);
vec3 v_normal		    : NORMAL    = vec3(0.0, 0.0, 1.0);
vec3 v_tangent		    : TANGENT   = vec3(1.0, 0.0, 0.0);
vec3 v_bitangent	    : BINORMAL  = vec3(0.0, 1.0, 0.0);
vec4 v_color            : COLOR0	= vec4(1.0, 1.0, 1.0, 1.0);
vec4 v_diffuse_light    : TEXCOORD6 = vec4(0.0, 0.0, 0.0, 0.0);
vec4 v_specular_light   : TEXCOORD7 = vec4(0.0, 0.0, 0.0, 0.0);

vec3 g_position         : TEXCOORD3 = vec3(0.0, 0.0, 0.0);
vec4 g_texcoord0	    : TEXCOORD0 = vec4(0.0, 0.0, 0.0, 0.0);
vec3 g_normal		    : NORMAL    = vec3(0.0, 0.0, 1.0);
vec4 g_color            : COLOR0	= vec4(1.0, 1.0, 1.0, 1.0);

vec3 a_position		: POSITION;
vec4 a_color0		: COLOR0;
vec3 a_normal		: NORMAL;
vec4 a_tangent		: TANGENT;
vec4 a_texcoord0	: TEXCOORD0;
vec4 a_texcoord1	: TEXCOORD1;
vec4 a_weight		: BLENDWEIGHT;
ivec4 a_indices		: BLENDINDICES;

vec4 i_data0     : TEXCOORD7;
vec4 i_data1     : TEXCOORD6;
vec4 i_data2     : TEXCOORD5;
vec4 i_data3     : TEXCOORD4;
vec4 i_data4     : TEXCOORD3;
vec4 i_data5     : TEXCOORD2;
vec4 i_data6     : TEXCOORD1;
vec4 i_data7	 : TEXCOORD0;
