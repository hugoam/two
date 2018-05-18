#include "pbr/pbr_vs.sc"

/*$input a_position, a_color0, a_texcoord0
$output v_color, v_texcoord0

#include "common.sh"

void main()
{

#ifdef RENDER_DEPTH
	render_depth(v_normal, v_view);
#endif

	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));
	v_color = a_color0;
	v_texcoord0 = a_texcoord0;
}*/
