$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal

#include <pbr/pbr.sh>

void main()
{
#include "fs_fragment.sh"
#include "fs_material.sh"
#include "fs_out_gbuffer.sh"
}
