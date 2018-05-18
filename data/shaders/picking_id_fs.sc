$input v_position, v_view, v_normal

#include "common.sh"

uniform vec4 u_picking_id;

void main()
{
	gl_FragColor.rgba = u_picking_id.rgba;
}
