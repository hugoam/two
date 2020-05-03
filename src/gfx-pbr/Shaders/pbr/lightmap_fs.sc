$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal

#include <encode.sh>
#include <pbr/pbr.sh>
#include <pbr/light.sh>
#include <gi/conetrace.sh>

void main()
{
#include "fs_fragment.sh"

//#include "fs_depth.sh"
//#include "fs_normal.sh"

	vec3 diffuse = vec3_splat(0.0);

    if(u_gi_conetrace)
    {
        ConeStart cone = cone_start(fragment.position, fragment.normal);
        diffuse += trace_diffuse(s_gi_probe, cone.pos, cone.normal, u_gi_probe_bias) * u_gi_probe_diffuse;
    }

	//gl_FragColor = vec4(diffuse, 1.0);
    gl_FragColor = encodeHDR(diffuse);
    //gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
	//gl_FragColor = vec4(normalize(fragment.normal) * 0.5 + 0.5, 1.0);
}
