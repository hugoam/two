$input v_view, v_position, v_normal, v_tangent, v_color, v_texcoord0, v_texcoord1, v_binormal

#include <encode.sh>
#include <pbr/pbr.sh>
#include <pbr/light.sh>

#ifdef GI_CONETRACE
#include <gi/conetrace.sh>
#endif

void main()
{
    Fragment fragment;
    fragment.coord = gl_FragCoord;
	fragment.position = v_view.xyz;
	fragment.view = normalize(-v_view.xyz);
	fragment.normal = normalize(v_normal);
	fragment.binormal = normalize(v_binormal);
	fragment.tangent = normalize(v_tangent);
	fragment.uv = v_texcoord0.xy;
	fragment.uv2 = v_texcoord1.xy;
	fragment.color = v_color;
    
#if BGFX_SHADER_LANGUAGE_HLSL
    fragment.coord.z = (fragment.coord.z + 1.0) / 2.0;
    fragment.depth = gl_FragCoord.w;
#else
    fragment.depth = -fragment.position.z;
#endif

    //fragment.coord.z = fragment.depth;

//#include "fs_depth.sh"
//#include "fs_normal.sh"

	vec3 diffuse = vec3_splat(0.0);

#ifdef GI_CONETRACE
    ConeStart cone = cone_start(fragment.position, fragment.normal);
    diffuse += trace_diffuse(s_gi_probe, cone.pos, cone.normal, u_gi_probe_bias) * u_gi_probe_diffuse;
#endif

	//gl_FragColor = vec4(diffuse, 1.0);
    gl_FragColor = encodeHDR(diffuse);
    //gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
	//gl_FragColor = vec4(normalize(fragment.normal) * 0.5 + 0.5, 1.0);
}
